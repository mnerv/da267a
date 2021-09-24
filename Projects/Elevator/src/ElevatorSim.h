/**
 * @file   ElevatorSim.h
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  
 * @date   2021-09-24
 *
 * @copyright Copyright (c) 2021
 */
#ifndef ELEVATORSIM_H_
#define HELLOTORSIM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define ELEVATOR_MAX_FLOOR 2
#define ELEVATOR_TRUE      1
#define ELEVATOR_FALSE     0

typedef enum {
    Unknown       = -1,
    ButtonPress   =  0,
    ButtonRelease =  1,
    Moving        =  2,
    Arrive        =  3,
    DoorOpening   =  4,
    DoorClosing   =  5
} ElevatorEventType;

typedef struct {
    ElevatorEventType Type;
    void*             Event;
} ElevatorEvent;

typedef struct {
    int32_t Button;
} ButtonEvent;

typedef struct {
    int32_t Target;
    int32_t Current;
    int32_t Direction;
} MovingEvent;

typedef struct {
    uint8_t Floor;
} ArriveEvent;

typedef struct {
    int32_t CurrentFloor;
    int32_t RequestedFloor;

    uint8_t InButtonFloor[ELEVATOR_MAX_FLOOR];
    uint8_t OutButtonFloor[ELEVATOR_MAX_FLOOR];

    uint8_t IsGoingUp;
    uint8_t IsGoingDown;

    uint8_t LastInButtonState[ELEVATOR_MAX_FLOOR];
    uint8_t LastOutButtonState[ELEVATOR_MAX_FLOOR];
} Elevator;

void InitElevator(Elevator* elevator);
void ElevatorUpdate(Elevator* elevator);
void ElevatorPollEvent(ElevatorEvent* event);

void ElevatorPressInButton(Elevator* elevator, int32_t button);
void ElevatorReleaseInButton(Elevator* elevator, int32_t button);
void ElevatorPressOutButton(Elevator* elevator, int32_t button);
void ElevatorReleaseOutButton(Elevator* elevator, int32_t button);

#ifdef __cplusplus
}
#endif
#endif
