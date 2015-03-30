#ifndef PINGER_H_
#define PINGER_H_

#include "helper.h"
#include <stdint.h>

typedef struct
{
    struct
    {
        PORT_TYPE* out;
        PORT_TYPE* dir;
        uint8_t pin;
    } trigger;

    struct
    {
        PORT_TYPE* sel;
        PORT_TYPE* dir;
        PORT_TYPE* in;
        uint8_t pin;
    } echo;
    uint32_t echoTime;

} pinger_t;

void setup_pinger(pinger_t pinger);

void start_pinger(pinger_t pinger);

#endif