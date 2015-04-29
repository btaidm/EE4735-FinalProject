#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"

void SetupPinger(pinger_t* pinger)
{
    *(pinger->trigger.dir) |= 0x01 << pinger->trigger.pin;
    *(pinger->trigger.out) &= ~( 0x01 << pinger->trigger.pin);
    *(pinger->echo.dir) &= ~( 0x01 << pinger->echo.pin);
    *(pinger->echo.sel) |= ( 0x01 << pinger->echo.pin);
}

void StartPinger(pinger_t* pinger)
{
    P1OUT ^= ( 0x01 << pinger->ledpin);
    *(pinger->trigger.out) |= ( 0x01 << pinger->trigger.pin);

    volatile uint16_t i = 1;

    while (i--) {};

    *(pinger->trigger.out) &= ~( 0x01 << pinger->trigger.pin);
}