/**
 *  File: helper.h
 */
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

/// ----------------------------------------
/// Func: Gets the sign of a 32 bit number
/// Args: Num = Number to get sign of
/// Retn: Sign of Number: -1 being negative,
///	      0 for zero, and 1 for positive
/// ----------------------------------------
static inline int8_t Sign32(int32_t num)
{
    return (num >> 31) | ((uint32_t) - num >> 31);
}

/// ----------------------------------------
/// Func: Gets the sign of a 16 bit number
/// Args: Num = Number to get sign of
/// Retn: Sign of Number: -1 being negative,
///	      0 for zero, and 1 for positive
/// ----------------------------------------
static inline int8_t Sign16(int16_t num)
{
    return (num >> 15) | ((uint16_t) - num >> 15);
}

/// ----------------------------------------
/// Func: Gets the sign of a 8 bit number
/// Args: Num = Number to get sign of
/// Retn: Sign of Number: -1 being negative,
///	      0 for zero, and 1 for positive
/// ----------------------------------------
static inline int8_t Sign8(int8_t num)
{
    return (num >> 7) | ((uint8_t) - num >> 7);
}

#endif