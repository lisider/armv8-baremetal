/* SPDX-License-Identifier: MIT */

#ifndef TYPES_H
#define TYPES_H

#ifndef __ASSEMBLER__

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef u64 uintptr_t;
typedef s64 ptrdiff_t;

typedef s64 ssize_t;

#endif

#endif
