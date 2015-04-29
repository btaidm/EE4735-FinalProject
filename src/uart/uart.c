#include <msp430x22x4.h>
#include "helper.h"
#include <stdint.h>
#include <string.h>
#include "uart.h"




int uart_init(void)
{
    P3SEL = 0x30;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;
    UCA0CTL1 &= ~UCSWRST;
    return 0;
}


char uart_getchar(void)
{
    int chr = -1;

    if (IFG2 & UCA0RXIFG)
    {
        chr = UCA0RXBUF;
    }

    return chr;
}

int uart_putchar(char c)
{
    /* Wait for the transmit buffer to be ready */
    while (!(IFG2 & UCA0TXIFG));

    /* Transmit data */
    UCA0TXBUF = (char ) c;

    return 0;
}

int uart_puts(const char* str)
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



int uart_putsUint32(uint32_t num)
{

    while (!(IFG2 & UCA0TXIFG)) {};

    UCA0TXBUF = (uint8_t)((num & 0xFF000000) >> 24);

    while (!(IFG2 & UCA0TXIFG)) {};

    UCA0TXBUF = (uint8_t)((num & 0x00FF0000) >> 16);

    while (!(IFG2 & UCA0TXIFG)) {};

    UCA0TXBUF = (uint8_t)((num & 0x0000FF00) >> 8);

    while (!(IFG2 & UCA0TXIFG)) {};

    UCA0TXBUF = (uint8_t)((num & 0x000000FF) >> 0);

    return 0;
}

