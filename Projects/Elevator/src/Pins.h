#ifndef PINS_H_
#define PINS_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t InitPins();
uint8_t ReadButtonA();
uint8_t ReadButtonB();

#ifdef __cplusplus
}
#endif
#endif

