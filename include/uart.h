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

uint16_t uint16ToChar(uint16_t num, char* temp);
uint32_t uint32ToChar(uint32_t num, char* temp);
uint8_t uint8ToChar(uint8_t num, char* temp);



#endif