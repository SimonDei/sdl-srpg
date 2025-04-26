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

_Check_return_
Unit* CreateUnit(
    _In_ AnimatedSprite* pAnimSprite,
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
