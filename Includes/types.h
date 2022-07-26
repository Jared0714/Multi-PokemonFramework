#pragma once
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define U64_MAX UINT64_MAX
#ifndef SSIZE_MAX
#ifdef  SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef u32 Handle;
typedef s32 Result;

// Thread Entrypoint function
typedef void (*ThreadFunc)(void*);
typedef void (*voidfn)(void);

// Fix intellisense errors
#ifdef _MSC_VER
    #define ALIGN(m)
    #define PACKED
    #define USED
    #define UNUSED
    #define DEPRECATED
    #define NAKED
    #define NORETURN

#else
    #define ALIGN(m) __attribute__((aligned(m)))
    #define PACKED __attribute__((packed))
    #define USED __attribute__((used))
    #define UNUSED __attribute__((unused))

    #ifndef LIBCTRU_NO_DEPRECATION
        #define DEPRECATED __attribute__ ((deprecated))

    #else
        #define DEPRECATED

    #endif

    #define NAKED __attribute__((naked))
    #define NORETURN __attribute__((noreturn))

#endif

#define CUR_THREAD_HANDLE  0xFFFF8000
#define CUR_PROCESS_HANDLE 0xFFFF8001

#endif