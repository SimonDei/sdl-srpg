#include "unit.h"

#include <SDL3/SDL.h>

#include "window.h"
#include "camera.h"
#include "tilemap.h"
#include "sprite.h"
#include "animated-sprite.h"

_Check_return_ _Ret_maybenull_
Unit* CreateUnitFromSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite** ppAnimSprite,
    _In_ const INT iTileX,
    _In_ const INT iTileY
) {
    Unit* pUnit = calloc(1, sizeof(Unit));
    if (!pUnit) {
        SDL_Log("Failed to allocate memory for Unit\n");
        return NULL;
    }

    pUnit->pAnimSprite = *ppAnimSprite;
    pUnit->ptTilePosition.x = iTileX;
    pUnit->ptTilePosition.y = iTileY;

    *ppAnimSprite = NULL;

    return pUnit;
}

void DrawUnit(
    _In_ const Unit* pUnit,
    _In_ const Tilemap* pTilemap
) {
    const FLOAT x = pUnit->ptTilePosition.x * pTilemap->fTileWidth;
    const FLOAT y = pUnit->ptTilePosition.y * pTilemap->fTileHeight;
    SetSpritePosition(pUnit->pAnimSprite->pSprite, x, y);
    DrawAnimatedSprite(pUnit->pAnimSprite);
}

void MoveUnit(
    _Inout_ Unit* pUnit,
    _In_    const INT dx,
    _In_    const INT dy
) {
    pUnit->ptTilePosition.x += dx;
    pUnit->ptTilePosition.y += dy;
}

_Check_return_
Unit* GetUnitAtScreenPosition(
    _In_reads_(nCount) Unit* pUnits,
    _In_               const INT nCount,
    _In_               const Tilemap* pTilemap,
    _In_               const FLOAT fMouseX,
    _In_               const FLOAT fMouseY
) {
    const Camera* pCamera = GetCurrentCamera();
    Vector2 world = { 0 };

    const FLOAT invZoom = 1.0f / pCamera->fZoom;
    world.x = (fMouseX - (FLOAT)GetWindowWidth() / 2.0f) * invZoom + pCamera->x;
    world.y = (fMouseY - (FLOAT)GetWindowHeight() / 2.0f) * invZoom + pCamera->y;

    const Point tilePos = MapPositionToTile(pTilemap, world.x, world.y);

    for (INT i = 0; i < nCount; i++) {
        if (pUnits[i].ptTilePosition.x == tilePos.x && pUnits[i].ptTilePosition.y == tilePos.y) {
            return &pUnits[i];
        }
    }

    return NULL;
}

_Check_return_opt_
bool DestroyUnit(
    _Inout_ _Pre_valid_ _Post_invalid_ Unit* pUnit
) {
    if (!pUnit) {
        return false;
    }

    DestroyAnimatedSprite(pUnit->pAnimSprite);
    SafeFree(pUnit);
    
    return true;
}
