#include <stdint.h>

#include "driver/gpio.h"
#include "esp32/rom/ets_sys.h"
#include "esp_task_wdt.h"

extern "C" {
#include "Pins.h"
}

//
// States:
//      Moving
//      Idle
//      Loading
//      Unloading
//
// Events:
//      Push button on lower level
//      Push external button on upper level
//      Done loading
//      Done unloading
//      Arrive to floor
//
// Transitions:
//      Idle      -> Moving
//      Idle      -> Loading
//      Loading   -> Moving
//      Moving    -> Loading
//      Unloading -> Moving
//
// Datas:
//      Current State
//      Current position
//

int32_t floor_num = 0;

enum class EventType : int32_t {
    UNKNOWN        = -1,
    BUTTON_LOWER   =  0,
    BUTTON_UPPER   =  1,
    DONE_LOADING   =  2,
    DONE_UNLOADING =  3,
    ARRIVE_FLOOR   =  4,
};
enum class RetCode : int32_t {
    OK,
};
enum class StateType : int32_t {
    Moving    = 0,
    Idle      = 1,
    Loading   = 2,
    Unloading = 3,
};

StateType MovingState(EventType event) {
    if (event == EventType::ARRIVE_FLOOR) {
        return StateType::Unloading;
    }

    printf("State::Moving\n");
    // Moving the elevator
    return StateType::Moving;
}
StateType IdleState(EventType event) {
    StateType state = StateType::Idle;

    if (event == EventType::BUTTON_LOWER) {
        if (floor_num == 0)
            state = StateType::Loading;
        else
            state = StateType::Moving;
    } else if (event == EventType::BUTTON_UPPER) {
        if (floor_num == 1)
            state = StateType::Loading;
        else
            state = StateType::Moving;
    }

    printf("State::Idle\n");
    // Door close
    return state;
}

// BAD CODE
uint64_t lastLoadingTime = 0;
bool     isLoadingDone   = false;

StateType LoadingState(EventType event) {
    uint64_t now = esp_timer_get_time();
    StateType state = StateType::Loading;
    if (event == EventType::DONE_LOADING) {
        // Close door
        state = StateType::Moving;
    }

    // Should not be here
    // Shitty code
    if ((now - lastLoadingTime) > 2000000) {
        isLoadingDone = true;
        lastLoadingTime = now;
    }

    printf("State::Loading\n");
    // Keeps door open
    return state;
}
StateType UnloadingState(EventType event) {
    StateType state = StateType::Unloading;
    if (event == EventType::DONE_UNLOADING) {
        state = StateType::Idle;
    }

    printf("State::Unloading\n");
    // Open Doors
    return state;
}
StateType (*StateFuncs[])(EventType) = {
    MovingState,
    IdleState,
    LoadingState,
    UnloadingState
};

EventType PollEvents() {
    if (!ReadButtonA())
        return EventType::BUTTON_UPPER;
    if (!ReadButtonB())
        return EventType::BUTTON_LOWER;
    if (!ReadButtonC())
        return EventType::ARRIVE_FLOOR;
    if (ReadButtonC())
        return EventType::DONE_UNLOADING;
    if (isLoadingDone) {
        isLoadingDone = false;
        return EventType::DONE_LOADING;
    }

    return EventType::UNKNOWN;
}

void sleep_ms(uint32_t ms) {
    TickType_t delay = ms / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

extern "C" void app_main() {
    InitPins();
    StateType currentState = StateType::Idle;
    StateType (*stateFunction)(EventType) = StateFuncs[static_cast<int32_t>(currentState)];

    while (true) {
        EventType event = PollEvents();

        StateType newState = stateFunction(event);
        stateFunction      = StateFuncs[static_cast<int32_t>(newState)];
        sleep_ms(250);
    }
}

