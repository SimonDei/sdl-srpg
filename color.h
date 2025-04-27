#ifndef COLOR_H
#define COLOR_H

#include "utils.h"

typedef struct _Color {
    BYTE r;
    BYTE g;
    BYTE b;
    BYTE a;
} Color;

inline Color CreateColor(
    _In_ BYTE r,
    _In_ BYTE g,
    _In_ BYTE b,
    _In_ BYTE a
) {
    return (Color) { r, g, b, a };
}

inline Color CreateColorRGB(
    _In_ BYTE r,
    _In_ BYTE g,
    _In_ BYTE b
) {
    return (Color) { r, g, b, 255 };
}

#endif
