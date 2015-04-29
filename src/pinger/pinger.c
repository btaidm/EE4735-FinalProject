/**
 *  File: pinger.c
 */
#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"

void SetupPinger(pinger_t* pingerPtr)
{
    // Setup Trigger Pin
    *(pingerPtr->trigger.dir) |= 0x01 << pingerPtr->trigger.pin; // Dir. = Out
    *(pingerPtr->trigger.out) &= ~( 0x01 << pingerPtr->trigger.pin); // Trigger = Low

    // Setup Echo Pin
    *(pingerPtr->echo.dir) &= ~( 0x01 << pingerPtr->echo.pin); // Dir. = In
    *(pingerPtr->echo.sel) |= ( 0x01 << pingerPtr->echo.pin);  // Capture input
}

void StartPinger(pinger_t* pingerPtr)
{
    P1OUT ^= ( 0x01 << pingerPtr->ledpin); // Toggle LED Light
    *(pingerPtr->trigger.out) |= ( 0x01 << pingerPtr->trigger.pin); // Start Trigger

    // Wait for loop to allow trigger proper time 
    volatile uint16_t triggerWait = 1;
    while (triggerWait--) {};

    // Trigger Done, wait for echo
    *(pingerPtr->trigger.out) &= ~( 0x01 << pingerPtr->trigger.pin);
}