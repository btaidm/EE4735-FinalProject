#ifndef UART_H_
#define UART_H_
#include <stdint.h>

int UartInit(void);

char UartGetChar(void);

int UartPutChar(char c);

int UartPuts(const char* str);

int UartPutsUint32(uint32_t num);
#endif