#ifndef __UART_H__
#define __UART_H__

#include "types.h"
void print_uart0(const char *s);
void uart_write(const void *buf, size_t count);

#endif /* __UART_H__ */
