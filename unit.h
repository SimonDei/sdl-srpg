#ifndef UNIT_H
#define UNIT_H

#include "point.h"
#include "utils.h"

typedef struct _Tilemap Tilemap;
typedef struct _AnimatedSprite AnimatedSprite;

typedef struct _Unit {
    AnimatedSprite* pAnimSprite;
    Point ptTilePosition;
    INT hp;
    INT attack;
    INT defense;
    INT moveSpeed;
} Unit;

/**
 * Creates a unit from an animated sprite.
 * 
 * @param ppAnimSprite Pointer to the animated sprite to use for the unit.
 * @param iTileX The x-coordinate of the tile position.
 * @param iTileY The y-coordinate of the tile position.
 * 
 * @return A pointer to the created unit, or NULL on failure.
 */
_Check_return_ _Ret_maybenull_ Unit* CreateUnitFromSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite** ppAnimSprite,
    _In_ INT iTileX,
    _In_ INT iTileY
);

void DrawUnit(
    _In_ const Unit* pUnit,
    _In_ const Tilemap* pTilemap
);

void MoveUnit(
    _Inout_ Unit* pUnit,
    _In_    INT dx,
    _In_    INT dy
);

_Check_return_
Unit* GetUnitAtScreenPosition(
    _In_reads_(nCount) Unit* pUnits,
    _In_               INT nCount,
    _In_               const Tilemap* pTilemap,
    _In_               FLOAT fMouseX,
    _In_               FLOAT fMouseY
);

_Check_return_opt_
bool DestroyUnit(
    _Inout_ _Pre_valid_ _Post_invalid_ Unit* pUnit
);

#endif
