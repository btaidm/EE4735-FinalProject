#ifndef UART_H_
#define UART_H_
#include <stdint.h>

/// ----------------------------------------
/// Func: Sets up UART for 9600 8-N-1
///       for communication to computer
/// Retn: Always zero unless compiler breaks
/// ----------------------------------------
int UartInit(void);

/// ----------------------------------------
/// Func: Receives Char from UART
/// Retn: Character from UART
/// ----------------------------------------
char UartGetChar(void);

/// ----------------------------------------
/// Func: Sends Char over UART
/// Args: c = Char to send
/// Retn: Always zero
/// ----------------------------------------
int UartPutChar(char c);

/// --------------------------------------
/// Func: Sends a string over UART
/// Args: str = String to send
/// Retn: -1 if srt is NULL
///        0 otherwise
/// --------------------------------------
int UartPuts(const char* str);

/// ------------------------------------------
/// Func: Sends a uint32 over UART in binary
/// Args: num = uint32 to send
/// Retn: Always 0
/// ------------------------------------------
int UartPutsUint32(uint32_t num);
#endif