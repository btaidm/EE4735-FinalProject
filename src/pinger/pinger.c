#include <msp430f2274.h>
#include <stdint.h>
#include "pinger.h"

void setup_pinger(pinger_t pinger)
{
    *(pinger.trigger.dir) |= 0x01 << pinger.trigger.pin;
    *(pinger.trigger.out) &= ~( 0x01 << pinger.trigger.pin);
    *(pinger.echo.dir) &= ~( 0x01 << pinger.echo.pin);
    *(pinger.echo.sel) |= ( 0x01 << pinger.echo.pin);
}

void start_pinger(pinger_t pinger)
{
    *(pinger.trigger.out) ^= ( 0x01 << pinger.trigger.pin);

    int i = 10;

    while (i--);

    *(pinger.trigger.out) &= ~( 0x01 << pinger.trigger.pin);
}