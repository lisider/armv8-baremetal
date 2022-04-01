/* SPDX-License-Identifier: MIT */

#include "stdio.h"
#include "vsprintf.h"
#include "uart.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))


int snprintf(char *buffer, size_t size, const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsnprintf(buffer, size, fmt, args);
    va_end(args);
    return i;
}

int debug_printf(const char *fmt, ...)
{
    va_list args;
    char buffer[512];
    int i;

    va_start(args, fmt);
    i = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    uart_write(buffer, min(i, (int)(sizeof(buffer) - 1)));

    return i;
}

