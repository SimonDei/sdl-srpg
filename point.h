#ifndef POINT_H
#define POINT_H

#include "utils.h"

/**
 Represents a 2D point or coordinate in integer space.
 */
typedef struct _Point {
    /**
     The horizontal coordinate (X axis).
     */
    INT32 x;

    /**
     The vertical coordinate (Y axis).
     */
    INT32 y;
} Point;

#endif // POINT_H
