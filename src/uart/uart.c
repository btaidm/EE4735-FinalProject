#include <msp430x22x4.h>
#include "helper.h"
#include <stdint.h>
#include <string.h>
#include "uart.h"




int UartInit(void)
{
    P3SEL = 0x30;           // Set P3.4 and P3.5 to Tx/Rx
    UCA0CTL1 |= UCSSEL_2;   // Use SMCLK
    UCA0BR0 = 104;          // Buad Rate to 9600
    UCA0BR1 = 0;            // Buad Rate to 9600
    UCA0MCTL = UCBRS0;      // Map 1MHz -> 9600
    UCA0CTL1 &= ~UCSWRST;   // State UART State Machine
    return 0;
}


char UartGetChar(void)
{
    int chr = -1;
    // Wait for RX Buf
    if (IFG2 & UCA0RXIFG)
    {
        // Receive Data
        chr = UCA0RXBUF;
    }
    return chr;
}

int UartPutChar(char c)
{
    // Wait for the transmit buffer to be ready
    while (!(IFG2 & UCA0TXIFG)) {};
    // Transmit data
    UCA0TXBUF = (char ) c;

    return 0;
}

int UartPuts(const char* str)
{
    int status = -1;

    if (str != NULL)
    {
        status = 0;
        while (*str != '\0')
        {
            /* Wait for the transmit buffer to be ready */
            while (!(IFG2 & UCA0TXIFG));
            /* Transmit data */
            UCA0TXBUF = *str;

            /*  If there is a line-feed, add a carriage return */
            if (*str == '\n')
            {
                /* Wait for the transmit buffer to be ready */
                while (!(IFG2 & UCA0TXIFG));
                UCA0TXBUF = '\r';
            }
            str++;
        }
    }

    return status;
}



int UartPutsUint32(uint32_t num)
{
    // Send Upper Byte
    while (!(IFG2 & UCA0TXIFG)) {};
    UCA0TXBUF = (uint8_t)((num & 0xFF000000) >> 24);

    // Send Upper Middle Byte
    while (!(IFG2 & UCA0TXIFG)) {};
    UCA0TXBUF = (uint8_t)((num & 0x00FF0000) >> 16);

    // Send Lower Middle Byte
    while (!(IFG2 & UCA0TXIFG)) {};
    UCA0TXBUF = (uint8_t)((num & 0x0000FF00) >> 8);

    // Send Lower Byte
    while (!(IFG2 & UCA0TXIFG)) {};
    UCA0TXBUF = (uint8_t)((num & 0x000000FF) >> 0);

    return 0;
}

