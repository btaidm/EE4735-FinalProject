//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430x22x4.h>
#include <stdint.h>

#define MAX_TICKS 10000        // Blink length (loop passes)

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    volatile int16_t i;                       // Generic loop idx

    P1DIR |= 0x01;                            // Set pin P1.0 to output

    while (1)                                 // Infinite loop
    {
        P1OUT ^= 0x01;                          // Toggle P1.0 = toggle LED

        for (i = MAX_TICKS; i != 0; i--) {} ;   // Empty S-Ware delay loop
    }
}
