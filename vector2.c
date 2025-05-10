//
// Created by Simon on 21.04.2025.
//

#include "vector2.h"

#include <math.h>

_Check_return_
VECTOR2 CreateVector2(
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    return (VECTOR2){ x, y };
}

_Check_return_
VECTOR2 Vector2Zero(
    void
) {
    return (VECTOR2){ 0.0f, 0.0f };
}

_Check_return_
VECTOR2 Vector2One(
    void
) {
    return (VECTOR2){ 1.0f, 1.0f };
}

void Vector2Add(
    _Inout_ VECTOR2* pVector,
    _In_    VECTOR2 addVector
) {
    pVector->x += addVector.x;
    pVector->y += addVector.y;
}

void Vector2Subtract(
    _Inout_ VECTOR2* pVector,
    _In_    VECTOR2 subVector
) {
    pVector->x -= subVector.x;
    pVector->y -= subVector.y;
}

void Vector2Scale(
    _Inout_ VECTOR2* pVector,
    _In_    const FLOAT fScale
) {
    pVector->x *= fScale;
    pVector->y *= fScale;
}

void Vector2Normalize(
    _Inout_ VECTOR2* pVector
) {
    const float length = sqrtf(pVector->x * pVector->x + pVector->y * pVector->y);
    if (length != 0.0f) {
        pVector->x /= length;
        pVector->y /= length;
    } else {
        pVector->x = 0.0f;
        pVector->y = 0.0f;
    }
}

_Check_return_
FLOAT Vector2Length(
    _In_ const VECTOR2 vector
) {
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

_Check_return_
bool Vector2Equal(
    _In_ const VECTOR2 vec1,
    _In_ const VECTOR2 vec2
) {
    return vec1.x == vec2.x && vec1.y == vec2.y;
}
