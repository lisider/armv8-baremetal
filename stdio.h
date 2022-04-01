/* SPDX-License-Identifier: MIT */

#ifndef STDIO_H
#define STDIO_H

#include "types.h"
#define printf(...) debug_printf(__VA_ARGS__)
#define puts(X) printf("%s\n",X)

extern int debug_printf(const char *fmt, ...);
extern int snprintf(char *buffer, size_t size, const char *fmt, ...);

#endif
