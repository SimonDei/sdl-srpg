#ifndef POINT_H
#define POINT_H

#include "utils.h"

/**
 Represents a 2D point or coordinate in integer space.
 */
typedef struct _POINT {
    /**
     The horizontal coordinate (X axis).
     */
    INT32 x;
    /**
     The vertical coordinate (Y axis).
     */
    INT32 y;
} POINT;

_Check_return_
static inline bool Point_IsEqual(
    _In_ const POINT* pt1,
    _In_ const POINT* pt2
) {
    return pt1->x == pt2->x && pt1->y == pt2->y;
}

#endif //POINT_H
