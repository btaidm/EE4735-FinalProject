/**
 *  File: pinger.h
 */
#ifndef PINGER_H_
#define PINGER_H_

#include <stdint.h>
#include "helper.h"

/// Struct contains information about Pinger Ports, Pins, and Echo Time
typedef struct
{
    struct
    {
        PORT_TYPE* out; // GPIO Output Register for trigger pulse
        PORT_TYPE* dir; // GPIO Direction Register for trigger pulse
        uint8_t pin;    // GPIO Pin for trigger pulse
    } trigger; // Trigger Pulse Information

    struct
    {
        PORT_TYPE* sel; // GPIO Select Register for echo pulse
        PORT_TYPE* dir; // GPIO Direction Register for echo pulse
        uint8_t pin;    // GPIO Pin for echo pulse
    } echo; // Echo Pulse Information
    volatile uint32_t echoTime; // Echo Time for Pinger given in Cycles
    uint8_t ledpin; // Pin for toggling on board led for visual debugging

} pinger_t;

/// ------------------------------------------------
/// Func: Setups up a pingers GPIO pins
/// Args: pingerPtr = pointer to pinger to setup
///                   uses pointer to decrease data 
///                   usage on stack
/// ------------------------------------------------
void SetupPinger(pinger_t* pingerPtr);

/// ------------------------------------------------
/// Func: Send Trigger pulse to pinger GPIO
/// Args: pingerPtr = pointer to pinger to trigger
///                   uses pointer to decrease data 
///                   usage on stack
/// ------------------------------------------------
void StartPinger(pinger_t* pingerPtr);

#endif