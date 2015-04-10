#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>

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

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

#define TO_HEX(i) (i <= 9? '0' + i : 'A' - 10 + i)

inline uint16_t uint16ToChar(uint16_t num, char* temp)
{
    temp[0] = TO_HEX((num & 0xF000)>>12);
    temp[1] = TO_HEX((num & 0x0F00)>>8);
    temp[2] = TO_HEX((num & 0x00F0)>>4);
    temp[3] = TO_HEX((num & 0x000F)>>0);
    temp[4] = 0;

    return 4;

}

inline uint32_t uint32ToChar(uint32_t num, char* temp)
{
    temp[0] = TO_HEX((num & 0xF0000000)>>28);
    temp[1] = TO_HEX((num & 0x0F000000)>>24);
    temp[2] = TO_HEX((num & 0x00F00000)>>20);
    temp[3] = TO_HEX((num & 0x000F0000)>>16);
    temp[4] = TO_HEX((num & 0x0000F000)>>12);
    temp[5] = TO_HEX((num & 0x00000F00)>>8);
    temp[6] = TO_HEX((num & 0x000000F0)>>4);
    temp[7] = TO_HEX((num & 0x0000000F)>>0);
    temp[8] = 0;

    return 8;
}

inline uint8_t uint8ToChar(uint8_t num, char* temp)
{
    temp[0] = TO_HEX((num & 0xF0)>>4);
    temp[1] = TO_HEX((num & 0x0F)>>0);
    temp[2] = 0;

    return 2;
}

#endif