#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <sal.h>

typedef char* PSTR;
typedef const char* PCSTR;

typedef int8_t INT8, CHAR;
typedef int16_t INT16, SHORT;
typedef int32_t INT32, INT;
typedef int64_t INT64, LONG;

typedef uint8_t UINT8, UCHAR, BYTE;
typedef uint16_t UINT16, USHORT, WORD;
typedef uint32_t UINT, DWORD;
typedef uint64_t UINT64, ULONG;

typedef float FLOAT, FLOAT32;
typedef double DOUBLE, FLOAT64;

typedef enum _RESULT {
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_NULL_POINTER,
    RESULT_MALLOC_FAILED,
    RESULT_REALLOC_FAILED
} RESULT;

#define UnusedParam(var)

#define SafeFree(ptr) do { \
    if ((ptr) != NULL) { \
        free(ptr); \
        (ptr) = NULL; \
    } \
} while (0)

#endif
