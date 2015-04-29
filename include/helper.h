#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>

#define STRINGIFY(a) #a

// Defines the type of port for the GPIO registers
#define PORT_TYPE volatile unsigned char


// Defines a macro for Interrupts the Works with GCC and IAR
#if defined(__ICC430__) // Check for IAR vs GCC
#define __INTERRUPT(x) \
    _Pragma( STRINGIFY( vector=  x ) ) \
    __interrupt
#elif defined(__GNUC__)
#define __INTERRUPT(x) __interrupt(x)
#else
#define __INTERRUPT(x)
#endif

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

static inline int8_t sign32(int32_t x)
{
    return (x >> 31) | ((uint32_t) - x >> 31);
}

static inline int8_t sign16(int16_t x)
{
    return (x >> 15) | ((uint16_t) - x >> 15);
}

static inline int8_t sign8(int8_t x)
{
    return (x >> 7) | ((uint8_t) - x >> 7);
}

#endif