#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"
#include "helper.h"

#define MAX_TICKS 10000        // Blink length (loop passes)

volatile pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0}, \
                                 .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 4},
                                 .echoTime = 0
                               };

volatile pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1}, \
                                  .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 3},
                                  .echoTime = 0
                                };

__INTERRUPT(TIMERA1_VECTOR) void timera1_isr(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case TAIV_TACCR2:
        {
            static uint8_t edge_2 = 0;
            static uint16_t reTime_2 = 0;

            uint16_t currStamp = TACCR2;

            TACCTL2 &= ~CCIFG;
            TACCTL2 ^= CM1 | CM0;
            P1OUT ^= 0x01;                            // Set pin P1.0 to output

            switch (edge_2)
            {
                case 0:
                {
                    reTime_2 = currStamp;
                    edge_2 = 1;
                    break;
                }

                case 1:
                {
                    edge_2 = 0;
                    uint32_t totalTime = 0;

                    if (currStamp < reTime_2)
                    {
                        totalTime = currStamp;
                        currStamp = 0xFFFF;
                    }

                    totalTime += (currStamp - reTime_2);
                    leftPinger.echoTime = totalTime;
                    //__low_power_mode_off_on_exit();
                    break;
                }
            }

            break;
        }

        case TAIV_TACCR1:
        {
            static uint8_t edge_1 = 0;
            static uint16_t reTime_1 = 0;

            uint16_t currStamp = TACCR1;

            TACCTL1 &= ~CCIFG;
            TACCTL1 ^= CM1 | CM0;

            switch (edge_1)
            {
                case 0:
                {
                    reTime_1 = currStamp;
                    edge_1 = 1;
                    break;
                }

                case 1:
                {
                    edge_1 = 0;
                    uint32_t totalTime = 0;

                    if (currStamp < reTime_1)
                    {
                        totalTime = currStamp;
                        currStamp = 0xFFFF;
                    }

                    totalTime += (currStamp - reTime_1);
                    rightPinger.echoTime = totalTime;
                    __low_power_mode_off_on_exit();
                    break;
                }
            }

            break;
        }

        case TAIV_TAIFG:
        default:
            break;
    }
}

void setup_timer()
{
    TACTL = TASSEL_2 | ID_0 | MC_2;
    TACCTL1 = CM0 | CCIS0 | CAP | SCS | CCIE;
    TACCTL2 = CM0 | CCIS0 | CAP | SCS | CCIE;
}


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    setup_timer();
    setup_pinger(leftPinger);
    P1DIR |= 0x01;                            // Set pin P1.0 to output

    while ( 1)
    {
        // Get the Pinger Distances
        start_pinger(leftPinger);

        //Go to low Power Mode
        _BIS_SR(LPM1_bits | GIE);

        // Calc new location and send to base

    }
}