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

#include "msp430x22x4.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    P1DIR |= 0x01;                  // Set P1.0 to output direction
    while (1) {
        /* Wait for 200000 cycles */
        __delay_cycles(200000);
        /* Toggle P1.0 output */
        P1OUT ^= 0x01;
    }
}
