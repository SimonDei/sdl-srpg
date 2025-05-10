#ifndef UNIT_H
#define UNIT_H

#include "point.h"
#include "utils.h"
#include "vector2.h"

typedef struct _Tilemap Tilemap;
typedef struct _AnimatedSprite AnimatedSprite;

typedef struct _Unit {
    AnimatedSprite* pAnimSprite;
    POINT ptTilePosition; // << Position on the map eg. (1, 1)
    VECTOR2 vStart;       // << Moving start vector in world space eg. (16, 16)
    VECTOR2 vTarget;      // << Moving target vector in world space eg. (48, 32)
    FLOAT fMoveDuration;  // << Time it should take to move
    FLOAT fMoveElapsed;   // << Time spent moving so far
    FLOAT fMoveSpeed;     // << Speed of the unit in pixels per second
    bool bIsMoving;       // << Is the unit currently moving?
    INT nHp;
    INT nAttack;
    INT nDefense;
    INT nMoveSpeed;
    bool bAnimated;
} Unit;

/**
 * Creates a unit from an animated sprite.
 * Takes ownership of the animated sprite pointer.
 * 
 * @param ppAnimSprite Pointer to the animated sprite to use for the unit.
 * @param pTilemap Pointer to the tilemap used for positioning the unit.
 * 
 * @return A pointer to the created unit, or NULL on failure.
 */
_Check_return_ _Ret_maybenull_ Unit* Unit_CreateFromAnimatedSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite** ppAnimSprite,
    _In_ const Tilemap* pTilemap
    );

/**
 * @brief Draws a unit on the screen based on its position on the tilemap.
 *
 * This function renders the specified unit at its position on the screen, using information from the
 * provided tilemap to correctly place the unit within the game world. The unit will be drawn with
 * its current properties, such as sprite, position, and other visual characteristics.
 *
 * @param pUnit    Pointer to the `Unit` that will be drawn.
 * @param pTilemap Pointer to the `Tilemap` used to determine the unit's placement in the game world.
 */
void Unit_Draw(
    _Inout_ Unit* pUnit,
    _In_    const Tilemap* pTilemap
    );

/**
 * @brief Moves the unit by a specified offset.
 *
 * This function updates the position of the specified unit by adding the given offsets to its
 * current position. The offsets are applied to the unit's X and Y coordinates, effectively moving
 * the unit by the specified amount in both directions.
 *
 * @param pUnit Pointer to the `Unit` whose position will be updated.
 * @param dx    The amount to move the unit along the X-axis.
 * @param dy    The amount to move the unit along the Y-axis.
 */
void Unit_Move(
    _Inout_ Unit* pUnit,
    _In_    INT dx,
    _In_    INT dy
    );

void Unit_StartMoveToTile(
    _Inout_ Unit* pUnit,
    _In_    const Tilemap* pTilemap,
    _In_    POINT ptTarget
    );

/**
 * @brief Retrieves the unit at the specified screen position.
 *
 * This function checks the screen position (given by `fMouseX` and `fMouseY`) and determines which
 * unit is located at that position, based on the provided list of units and the tilemap. The function
 * returns a pointer to the unit found at the given screen coordinates.
 *
 * @param pUnits   Pointer to an array of `Unit` objects.
 * @param nCount   The number of units in the `pUnits` array.
 * @param pTilemap Pointer to the `Tilemap` used to map screen coordinates to world coordinates.
 * @param fMouseX  The X coordinate of the mouse in screen space.
 * @param fMouseY  The Y coordinate of the mouse in screen space.
 * @return A pointer to the `Unit` at the specified screen position, or `NULL` if no unit is found.
 */
_Check_return_ _Ret_maybenull_ Unit* Unit_GetAtScreenPosition(
    _In_reads_(nCount) Unit* pUnits,
    _In_               INT nCount,
    _In_               const Tilemap* pTilemap,
    _In_               FLOAT fMouseX,
    _In_               FLOAT fMouseY
    );

/**
 * @brief Destroys the specified unit, releasing its resources.
 *
 * This function deletes the specified unit and frees any associated resources. After this function is
 * called, the `Unit` pointer is no longer valid, and further access to it should be avoided.
 *
 * @param pUnit Pointer to the `Unit` that will be destroyed.
 * @return `true` if the unit was successfully destroyed, `false` otherwise.
 */
_Check_return_opt_ bool Unit_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Unit* pUnit
    );

#endif //UNIT_H
