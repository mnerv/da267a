#include "ElevatorSim.h"

#define ELEVATOR_SPEED 25

void InitElevator(Elevator* elevator) {
    elevator->CurrentFloor   = 0;
    elevator->RequestedFloor = 0;
    for (int32_t i = 0; i < ELEVATOR_MAX_FLOOR; i++) {
        elevator->InButtonFloor[i]  = ELEVATOR_FALSE;
        elevator->OutButtonFloor[i] = ELEVATOR_FALSE;
    }

    elevator->IsGoingDown = ELEVATOR_FALSE;
    elevator->IsGoingUp   = ELEVATOR_FALSE;
}
void ElevatorUpdate(Elevator* elevator) {
    for (int32_t i = 0; i < ELEVATOR_MAX_FLOOR; i++) {
        elevator->LastInButtonState[i]  = elevator->InButtonFloor[i];
        elevator->LastOutButtonState[i] = elevator->OutButtonFloor[i];
    }
}
void ElevatorPollEvent(ElevatorEvent* event) {
}

void ElevatorPressInButton(Elevator* elevator, int32_t button) {
    elevator->InButtonFloor[button] = ELEVATOR_TRUE;
}
void ElevatorReleaseInButton(Elevator* elevator, int32_t button) {
    elevator->InButtonFloor[button] = ELEVATOR_FALSE;
}
void ElevatorPressOutButton(Elevator* elevator, int32_t button) {
    elevator->OutButtonFloor[button] = ELEVATOR_TRUE;
}
void ElevatorReleaseOutButton(Elevator* elevator, int32_t button) {
    elevator->OutButtonFloor[button] = ELEVATOR_FALSE;
}

