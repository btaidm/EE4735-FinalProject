#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"
#include "helper.h"
#include "uart.h"
#include <string.h>

char temp[35] = {0};

#define MAX_TICKS 10000        // Blink length (loop passes)

volatile pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0}, \
                                 .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 2}, \
                                 .echoTime = 0
                               };

volatile pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1}, \
                                  .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 3}, \
                                  .echoTime = 0
                                };

__INTERRUPT(TIMERA0_VECTOR) void timara0_isr(void)
{
    static uint8_t edge_1 = 0;
    static uint16_t reTime_1 = 0;

    uint16_t currStamp = TACCR0;

    TACCTL0 ^= CM1 | CM0;

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
            //start_pinger(leftPinger);
            break;
        }
    }
}

__INTERRUPT(TIMERA1_VECTOR) void timera1_isr(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case TAIV_TACCR1:
        {
            static uint8_t edge_2 = 0;
            static uint16_t reTime_2 = 0;

            uint16_t currStamp = TACCR2;

            TACCTL1 &= ~CCIFG;
            TACCTL1 ^= CM1 | CM0;

            // P1OUT ^= 0x01;                            // Set pin P1.0 to output

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
                    start_pinger(rightPinger);
                    break;
                }
            }

            break;
        }

        case TAIV_TACCR2:
            break;

        case TAIV_TAIFG:
        {
            TACTL &= ~(TAIE | TAIFG);
            start_pinger(rightPinger);
            break;
        }

        default:
            break;
    }
}

void setup_timer()
{
    TACTL   = TASSEL_2 | ID_0 | MC_2;
    TACCTL0 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    TACCTL1 = CM_1 | CCIS_1 | CAP | SCS | CCIE;
    //TACCTL2 = CM0 | CCIS_1 | CAP | SCS | CCIE;
}


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    P2SEL = 0;
    setup_timer();
    setup_pinger(leftPinger);
    setup_pinger(rightPinger);
    P1DIR |= 0x01;                            // Set pin P1.0 to output
    P1OUT &= ~0x01;

    //P2SEL2 = 0;

    while ( 1)
    {
        // Get the Pinger Distances
        //start_pinger(leftPinger);
        // start_pinger(rightPinger);
        //Go to low Power Mode

        // Calc new location and send to base
        TACTL   |= TAIE;
        __enable_interrupt();
        __low_power_mode_1();

        uint32_t digets = uint32ToChar(rightPinger.echoTime, temp);
        temp[digets] = '\n';
        temp[digets + 1] = 0;

        uart_puts(temp);
        volatile uint16_t i = 1000;

        while (i--);

        // i = 10000;

        // while (i--);
    }
}