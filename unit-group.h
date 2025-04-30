//
// Created by Simon on 30.04.2025.
//

#ifndef UNIT_GROUP_H
#define UNIT_GROUP_H

#include "utils.h"

typedef struct _Unit Unit;
typedef struct _Tilemap Tilemap;

typedef struct _UnitGroup {
    Unit** arrUnits;
    INT nCount;
    INT nCapacity;
} UnitGroup;

_Check_return_ UnitGroup* CreateUnitGroup(
    void
    );

_Check_return_opt_ bool AddUnitToGroup(
    _Inout_ UnitGroup* pUnitGroup,
    _In_    Unit* pUnit
    );

void DrawUnitGroup(
    _In_ const UnitGroup* pUnitGroup,
    _In_ const Tilemap* pTilemap
    );

_Check_return_opt_ bool DestroyUnitGroup(
    _Inout_ _Pre_valid_ _Post_invalid_ UnitGroup* pUnitGroup
    );

#endif //UNIT_GROUP_H
