#include <msp430x22x4.h>
#include "helper.h"
#include <stdint.h>
#include <string.h>
#include "uart.h"


struct baud_value
{
    uint32_t baud;
    uint16_t UCAxBR0;
    uint16_t UCAxBR1;
    uint16_t UCAxMCTL;
};

const struct baud_value baud_tbl[] =
{
    {9600, 104, 0, 0x2}
};


int uart_init(uart_config_t* config)
{
    P3SEL = 0x30;                         // P3.4,5 = USCI_A0 TXD/RXD
    int status = -1;

    /* USCI should be in reset before configuring - only configure once */
    if (UCA0CTL1 & UCSWRST)
    {
        size_t i;

        /* Set clock source to SMCLK */
        UCA0CTL1 |= UCSSEL_2;

        /* Find the settings from the baud rate table */
        for (i = 0; i < ARRAY_SIZE(baud_tbl); i++)
        {
            if (baud_tbl[i].baud == config->baud)
            {
                break;
            }
        }

        if (i < ARRAY_SIZE(baud_tbl))
        {
            /* Set the baud rate */
            UCA0BR0 = baud_tbl[i].UCAxBR0;
            UCA0BR1 = baud_tbl[i].UCAxBR1;
            UCA0MCTL = baud_tbl[i].UCAxMCTL;

            /* Enable the USCI peripheral (take it out of reset) */
            UCA0CTL1 &= ~UCSWRST;
            status = 0;
        };
    }

    return status;
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


uint16_t uint16ToChar(uint16_t num, char* temp)
{
    uint16_t a = num;
    int i = 0;

    while (a)
    {
        a = a / 10;
        i++;
    }

    a = i;
    temp[i] = 0;

    while (i > 0)
    {
        temp[i - 1] = (a % 10) + 48;
        a = a / 10;
        i--;
    }

    return a;

}

uint32_t uint32ToChar(uint32_t num, char* temp)
{
    uint32_t a = num;
    int i = 0;

    while (a)
    {
        a = a / 10;
        i++;
    }

    a = i;
    temp[i] = 0;

    while (i > 0)
    {
        temp[i - 1] = (a % 10) + 48;
        a = a / 10;
        i--;
    }

    return a;
}

uint8_t uint8ToChar(uint8_t num, char* temp)
{
    uint8_t a = num;
    int i = 0;

    while (a)
    {
        a = a / 10;
        i++;
    }

    a = i;
    temp[i] = 0;

    while (i > 0)
    {
        temp[i - 1] = (a % 10) + 48;
        a = a / 10;
        i--;
    }

    return a;
}