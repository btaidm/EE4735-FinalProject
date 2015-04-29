#ifndef UART_H_
#define UART_H_

#include <stdint.h>


int uart_init(void);

char uart_getchar(void);

int uart_putchar(char c);

int uart_puts(const char* str);

int uart_putsUint32(uint32_t num);
#endif