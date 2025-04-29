#ifndef COLOR_H
#define COLOR_H

#include "utils.h"

typedef struct _Color {
    BYTE r;
    BYTE g;
    BYTE b;
    BYTE a;
} Color;

/**
 * @brief Creates a color using RGBA values.
 *
 * This function creates a `Color` struct initialized with the provided RGBA (red, green, blue, alpha) values.
 * The resulting color can be used for texture tinting, sprite rendering, and other graphics operations.
 *
 * @param r Red component of the color (0-255).
 * @param g Green component of the color (0-255).
 * @param b Blue component of the color (0-255).
 * @param a Alpha component (transparency) of the color (0-255).
 * @return A `Color` struct initialized with the specified RGBA values.
 */
_Check_return_ inline Color CreateColor(
    _In_ BYTE r,
    _In_ BYTE g,
    _In_ BYTE b,
    _In_ BYTE a
) {
    return (Color) { r, g, b, a };
}

/**
 * @brief Creates a color using RGB values with full opacity (alpha = 255).
 *
 * This function creates a `Color` struct initialized with the provided RGB (red, green, blue) values
 * and sets the alpha (transparency) component to 255, representing full opacity.
 *
 * @param r Red component of the color (0-255).
 * @param g Green component of the color (0-255).
 * @param b Blue component of the color (0-255).
 * @return A `Color` struct initialized with the specified RGB values and full opacity (alpha = 255).
 */
_Check_return_ inline Color CreateColorRGB(
    _In_ BYTE r,
    _In_ BYTE g,
    _In_ BYTE b
) {
    return (Color) { r, g, b, 255 };
}

#endif //COLOR_H
