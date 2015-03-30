#ifndef HELPER_H
#define HELPER_H

#define STRINGIFY(a) #a

#define PORT_TYPE volatile unsigned char

#if defined(__ICC430__) // Check for IAR vs GCC
#define __INTERRUPT(x) \
    _Pragma( STRINGIFY( vector=  x ) ) \
    __interrupt
#elif defined(__GNUC__)
#define __INTERRUPT(x) __interrupt(x)
#else
#define __INTERRUPT(x)
#endif

#endif