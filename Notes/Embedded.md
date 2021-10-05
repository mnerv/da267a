# Embedded Notes

This contains the notes for the embedded system side of the course.

## Hardware

 - [ESP32](https://esp32.com)

32-bit architecture.

## C language

### Fundamental types

Basic type such as `int` is platform dependent, meaning that depending on which
system you're on its size might be different. In C/C++ standard `int` is at
least `16-bit` but it can be `32-bit` size on `32-bit` or `64-bit` systems.

Use `stdint.h` library which defines the "[Fixed width integer
types](https://en.cppreference.com/w/c/types/integer)" you can use. With it you
can use `int32_t` to get a `32-bit` size integer. Check [Arithmetic types from
cppreference.com](https://en.cppreference.com/w/c/language/arithmetic_types) for
more info.

### Source and Header Files

The declaration and implementation are usually separated into two separate files
in C/C++. The declaration are in the header file and its implementation is in
the source file.

#### Example header file: `Hello.h`

```c
#ifndef HELLO_H_
#define HELLO_H_
#ifdef __cplusplus
extern "C" {
#endif

void HelloWorld();

#ifdef __cplusplus
}
#endif
#endif
```

#### Example source file: `Hello.c`

```c
#include "Hello.h"
#include <stdio.h>

void HelloWorld() {
    printf("Hello, World!\n");
}
```

