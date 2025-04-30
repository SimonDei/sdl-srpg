//
// Created by Simon on 30.04.2025.
//

#include "unit-group.h"

#include "unit.h"

_Check_return_
UnitGroup* CreateUnitGroup(
    void
) {
    UnitGroup* pUnitGroup = malloc(sizeof(UnitGroup));
    if (!pUnitGroup) {
        return NULL;
    }

    pUnitGroup->nCount = 0;
    pUnitGroup->nCapacity = 10;
    pUnitGroup->arrUnits = malloc(pUnitGroup->nCapacity * sizeof(Unit*));

    return pUnitGroup;
}

_Check_return_opt_
bool AddUnitToGroup(
    _Inout_ UnitGroup* pUnitGroup,
    _In_    Unit* pUnit
) {
    if (pUnitGroup->nCount >= pUnitGroup->nCapacity) {
        pUnitGroup->nCapacity += 10;
        Unit** arrUnits = realloc(pUnitGroup->arrUnits, pUnitGroup->nCapacity * sizeof(Unit*));
        if (!arrUnits) {
            return false;
        }
        pUnitGroup->arrUnits = arrUnits;
    }

    pUnitGroup->arrUnits[pUnitGroup->nCount] = pUnit;
    pUnitGroup->nCount++;

    return true;
}

void DrawUnitGroup(
    _In_ const UnitGroup* pUnitGroup,
    _In_ const Tilemap* pTilemap
) {
    for (int i = 0; i < pUnitGroup->nCount; i++) {
        Unit_Draw(pUnitGroup->arrUnits[i], pTilemap);
    }
}

_Check_return_opt_
bool DestroyUnitGroup(
    _Inout_ _Pre_valid_ _Post_invalid_ UnitGroup* pUnitGroup
) {
    if (!pUnitGroup) {
        return false;
    }

    SafeFree(pUnitGroup->arrUnits);
    SafeFree(pUnitGroup);
    return true;
}
