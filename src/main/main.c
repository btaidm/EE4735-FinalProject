#include <msp430x22x4.h>
#include <stdint.h>
#include "pinger.h"
#include "helper.h"
#include "uart.h"
#include <string.h>

//static char temp[10] = {0};

#define MAX_TICKS 10000        // Blink length (loop passes)

pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0}, \
                        .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 2}, \
                        .echoTime = 0, \
                        .ledpin = 1
                      };

pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1}, \
                         .echo = { .in = &P2OUT, .dir = &P2DIR, .sel = &P2SEL, .pin = 3}, \
                         .echoTime = 0, \
                         .ledpin = 0
                       };

uart_config_t config = { .baud = 9600 };

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
            leftPinger.echoTime = totalTime;

            start_pinger(&rightPinger);
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

            uint16_t currStamp = TACCR1;

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
                    rightPinger.echoTime = totalTime;
                    __low_power_mode_off_on_exit();
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
            start_pinger(&leftPinger);
            break;
        }

        default:
            break;
    }
}

void setup_timer(void)
{
    TACTL   = TASSEL_2 | ID_0 | MC_2;
    TACCTL0 = CM_1 | CCIS_1 | SCS | CAP | CCIE;
    TACCTL1 = CM_1 | CCIS_1 | CAP | SCS | CCIE;
    //TACCTL2 = CM0 | CCIS_1 | CAP | SCS | CCIE;
}

void setup_clock(void)
{
    BCSCTL1 = CALBC1_1MHZ;                // DCO = 1 MHz
    //BCSCTL2 |= DIVS_3;
    DCOCTL  = CALDCO_1MHZ;                // DCO = 1 MHz
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
    P2SEL = 0;
    setup_timer();
    setup_pinger(&leftPinger);
    setup_pinger(&rightPinger);

    setup_clock();

    uart_init(&config);

    uart_puts("STARTCOL");

    P1DIR |= 0x03;                            // Set pin P1.0 to output
    P1OUT &= ~0x03;

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
        __disable_interrupt();

        //uart_puts("Hello World\n");
        //uart_puts("\nLeft Pinger:\t");
        uart_putsUint32(leftPinger.echoTime);

        //uart_puts("\tRight Pinger:\t");
        uart_putsUint32(rightPinger.echoTime);
        //volatile uint16_t i = 100;

        //while (i--);

        // i = 10000;

        // while (i--);
    }
}