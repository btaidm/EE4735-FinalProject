#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"

void SetupPinger(pinger_t* pingerPtr)
{
    // Setup Trigger Pin
    *(pinger->trigger.dir) |= 0x01 << pinger->trigger.pin; // Dir. = Out
    *(pinger->trigger.out) &= ~( 0x01 << pinger->trigger.pin); // Trigger = Low

    // Setup Echo Pin
    *(pinger->echo.dir) &= ~( 0x01 << pinger->echo.pin); // Dir. = In
    *(pinger->echo.sel) |= ( 0x01 << pinger->echo.pin);  // Capture input
}

void StartPinger(pinger_t* pingerPtr)
{
    P1OUT ^= ( 0x01 << pinger->ledpin); // Toggle LED Light
    *(pinger->trigger.out) |= ( 0x01 << pinger->trigger.pin); // Start Trigger

    // Wait for loop to allow trigger proper time 
    volatile uint16_t triggerWait = 1;
    while (triggerWait--) {};

    // Trigger Done, wait for echo
    *(pinger->trigger.out) &= ~( 0x01 << pinger->trigger.pin);
}