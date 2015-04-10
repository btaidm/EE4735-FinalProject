#ifndef UART_H_
#define UART_H_

#include <stdint.h>

typedef struct
{
    uint32_t baud;
} uart_config_t;


int uart_init(uart_config_t* config);

char uart_getchar(void);

int uart_putchar(char c);

int uart_puts(const char* str);

int uart_putsUint32(uint32_t num);

#endif