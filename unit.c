#include "unit.h"

#include "window.h"
#include "camera.h"
#include "tilemap.h"
#include "sprite.h"
#include "animated-sprite.h"

_Check_return_ _Ret_maybenull_
Unit* Unit_CreateFromAnimatedSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite** ppAnimSprite,
    _In_ const Tilemap* pTilemap
) {
    Unit* pUnit = calloc(1, sizeof(Unit));
    if (!pUnit) {
        printf("Failed to allocate memory for Unit\n");
        return NULL;
    }

    pUnit->pAnimSprite = *ppAnimSprite;
    pUnit->ptTilePosition.x = (INT)floorf(pUnit->pAnimSprite->pSprite->x / pTilemap->fTileWidth);
    pUnit->ptTilePosition.y = (INT)floorf(pUnit->pAnimSprite->pSprite->y / pTilemap->fTileHeight);
    pUnit->fMoveSpeed = 100.0f;
    pUnit->bAnimated = true;

    *ppAnimSprite = NULL;

    return pUnit;
}

void Unit_Draw(
    _In_ Unit* pUnit,
    _In_ const Tilemap* pTilemap
) {
    AnimatedSprite_Draw(pUnit->pAnimSprite);

    if (pUnit->bAnimated) {
        AnimatedSprite_Update(pUnit->pAnimSprite);
    }

    if (pUnit->bIsMoving) {
        pUnit->fMoveElapsed += GetFrameTime();
        FLOAT t = pUnit->fMoveElapsed / pUnit->fMoveDuration;

        if (t >= 1.0f) {
            t = 1.0f;
            pUnit->bIsMoving = false;
        }

        Sprite_SetPosition(
            pUnit->pAnimSprite->pSprite,
            pUnit->vStartPos.x + (pUnit->vTargetPos.x - pUnit->vStartPos.x) * t,
            pUnit->vStartPos.y + (pUnit->vTargetPos.y - pUnit->vStartPos.y) * t
        );
    }
}

void Unit_Move(
    _Inout_ Unit* pUnit,
    _In_    const INT dx,
    _In_    const INT dy
) {
    pUnit->ptTilePosition.x += dx;
    pUnit->ptTilePosition.y += dy;
}

void Unit_StartMoveToTile(
    _Inout_ Unit* pUnit,
    _In_    const Tilemap* pTilemap,
    _In_    Point ptTarget
) {
    if (!pUnit || !pTilemap) {
        return;
    }

    pUnit->ptTilePosition = ptTarget;

    Vector2 vStartPos = CreateVector2(
        pUnit->pAnimSprite->pSprite->x,
        pUnit->pAnimSprite->pSprite->y
    );
    Vector2 vTargetPos = CreateVector2(
        (FLOAT)ptTarget.x * pTilemap->fTileWidth,
        (FLOAT)ptTarget.y * pTilemap->fTileHeight
    );

    FLOAT dx = vTargetPos.x - vStartPos.x;
    FLOAT dy = vTargetPos.y - vStartPos.y;
    FLOAT distance = sqrtf(dx * dx + dy * dy);

    if (distance == 0.0f) {
        return;
    }

    FLOAT duration = distance / pUnit->fMoveSpeed;

    pUnit->vStartPos = vStartPos;
    pUnit->vTargetPos = vTargetPos;
    pUnit->fMoveDuration = duration;
    pUnit->fMoveElapsed = 0.0f;
    pUnit->bIsMoving = true;
}

_Check_return_ _Ret_maybenull_
Unit* Unit_GetAtScreenPosition(
    _In_reads_(nCount) Unit* pUnits,
    _In_               const INT nCount,
    _In_               const Tilemap* pTilemap,
    _In_               const FLOAT fMouseX,
    _In_               const FLOAT fMouseY
) {
    const Camera* pCamera = Camera_GetCurrent();
    Vector2 world = { 0 };

    const FLOAT invZoom = 1.0f / pCamera->fZoom;
    world.x = (fMouseX - (FLOAT)Window_GetWidth() / 2.0f) * invZoom + pCamera->x;
    world.y = (fMouseY - (FLOAT)Window_GetHeight() / 2.0f) * invZoom + pCamera->y;

    const Point tilePos = MapPositionToTile(pTilemap, world.x, world.y);

    for (INT i = 0; i < nCount; i++) {
        if (pUnits[i].ptTilePosition.x == tilePos.x && pUnits[i].ptTilePosition.y == tilePos.y) {
            return &pUnits[i];
        }
    }

    return NULL;
}

_Check_return_opt_
bool Unit_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Unit* pUnit
) {
    if (!pUnit) {
        return false;
    }

    AnimatedSprite_Destroy(pUnit->pAnimSprite);
    SafeFree(pUnit);
    
    return true;
}
