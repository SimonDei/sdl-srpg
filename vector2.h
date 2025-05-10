//
// Created by Simon on 21.04.2025.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include "utils.h"

/**
 * Represents a 2D vector with floating-point precision.
 */
typedef struct _VECTOR2 {
    /**
     * The horizontal component (X axis).
     */
    FLOAT x;

    /**
     * The vertical component (Y axis).
     */
    FLOAT y;
} VECTOR2;

/**
 * Creates a new Vector2 from the given X and Y components.
 *
 * @param x The horizontal component (X axis).
 * @param y The vertical component (Y axis).
 *
 * @returns A Vector2 initialized with the specified coordinates.
 */
_Check_return_ VECTOR2 CreateVector2(
    _In_ FLOAT x,
    _In_ FLOAT y
    );

/**
 * Returns a Vector2 with both X and Y components set to zero.
 *
 * @returns A zero-initialized Vector2 representing the origin (0, 0).
 */
_Check_return_ VECTOR2 Vector2Zero(
    void
    );

/**
 * Returns a Vector2 with both X and Y components set to one.
 *
 * @returns A Vector2 with values (1.0f, 1.0f), often used for uniform scaling or default values.
 */
_Check_return_ VECTOR2 Vector2One(
    void
    );

/**
 * Adds the specified Vector2 to the given vector, modifying the original vector.
 *
 * @param pVector Pointer to the Vector2 to be modified.
 * @param addVector The Vector2 to add to the original vector.
 */
void Vector2Add(
    _Inout_ VECTOR2* pVector,
    _In_    VECTOR2 addVector
    );

/**
 * Subtracts the specified Vector2 from the given vector, modifying the original vector.
 *
 * @param pVector Pointer to the Vector2 to be modified.
 * @param subVector The Vector2 to subtract from the original vector.
 */
void Vector2Subtract(
    _Inout_ VECTOR2* pVector,
    _In_    VECTOR2 subVector
    );

/**
 * Scales the given vector by a scalar value, modifying the original vector.
 *
 * @param pVector Pointer to the Vector2 to be scaled.
 * @param fScale The scalar value to multiply both X and Y components by.
 */
void Vector2Scale(
    _Inout_ VECTOR2* pVector,
    _In_    FLOAT fScale
    );

/**
 * Normalizes the given vector to have a length of 1, preserving its direction.
 *
 * @param pVector Pointer to the Vector2 to be normalized.
 */
void Vector2Normalize(
    _Inout_ VECTOR2* pVector
    );

/**
 * Calculates the length (magnitude) of the given vector.
 *
 * @param vector The Vector2 whose length will be computed.
 *
 * @returns The length of the vector as a floating-point value.
 */
_Check_return_ FLOAT Vector2Length(
    _In_ VECTOR2 vector
    );

/**
 * Compares two vectors for equality.
 *
 * @param vec1 The first Vector2 to compare.
 * @param vec2 The second Vector2 to compare.
 *
 * @returns true if both vectors have equal X and Y components; otherwise, false.
 */
_Check_return_ bool Vector2Equal(
    _In_ VECTOR2 vec1,
    _In_ VECTOR2 vec2
    );

#endif //VECTOR2_H
