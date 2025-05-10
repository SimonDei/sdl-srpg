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

typedef enum _Result {
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_NULL_POINTER,
    RESULT_MALLOC_FAILED,
    RESULT_REALLOC_FAILED
} Result;

#define Succeeded(result) ((result) == RESULT_SUCCESS)
#define Failed(result) ((result) != RESULT_SUCCESS)

#define ArraySize(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * @brief Suppresses compiler warnings for unused function parameters.
 *
 * This macro is used to explicitly mark a function parameter as intentionally unused,
 * preventing compiler warnings (especially in release builds) about unused parameters.
 *
 * @param var The name of the unused parameter.
 */
#define UnusedParam(var)

/**
 * @brief Safely frees a dynamically allocated pointer and sets it to NULL.
 *
 * This macro checks if a pointer is not `NULL` before freeing it. After calling `free()`, it sets the pointer
 * to `NULL` to prevent accidental use of a dangling pointer.
 *
 * This helps avoid common issues such as double-free errors or accessing freed memory.
 *
 * @code
 * char* pData = malloc(100);
 * SafeFree(pData);  // Frees pData and sets it to NULL
 * @endcode
 *
 * @param ptr Pointer to dynamically allocated memory to be freed.
 *
 * @note This macro is designed for pointers allocated with `malloc`, `calloc`, or `realloc`.
 *       It should not be used on non-heap memory (e.g., stack variables or string literals).
 */
#define SafeFree(ptr) do { \
    if ((ptr) != NULL) { \
        free(ptr); \
        (ptr) = NULL; \
    } \
} while (0)

#endif
