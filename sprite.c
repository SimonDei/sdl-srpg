//
// Created by Simon on 21.04.2025.
//

#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "window.h"
#include "camera.h"
#include "texture.h"

_Check_return_ _Ret_maybenull_
Sprite* Sprite_Create(
    _In_ Texture* pTexture,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    Sprite* pSprite = malloc(sizeof(Sprite));
    if (!pSprite) {
        printf("Failed to allocate memory for Sprite\n");
        return NULL;
    }

    pSprite->pSpriteHandle = sfSprite_create();
    if (!pSprite->pSpriteHandle) {
        printf("Failed to create sprite handle\n");
        SafeFree(pSprite);
        return NULL;
    }

    sfSprite_setTexture(pSprite->pSpriteHandle, pTexture->pBitmap, true);
    sfSprite_setPosition(pSprite->pSpriteHandle, (sfVector2f) { x, y });

    pSprite->x = x;
    pSprite->y = y;
    pSprite->fScaleX = 1.0f;
    pSprite->fScaleY = 1.0f;
    pSprite->bVisible = true;

    return pSprite;
}

void Sprite_SetVisible(
    _Inout_ Sprite* pSprite,
    _In_    const bool bVisible
) {
    pSprite->bVisible = bVisible;
}

void Sprite_SetScale(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT fScaleX,
    _In_    const FLOAT fScaleY
) {
    pSprite->fScaleX = fScaleX;
    pSprite->fScaleY = fScaleY;
    sfSprite_setScale(pSprite->pSpriteHandle, (sfVector2f) { fScaleX, fScaleY });
}

void Sprite_SetX(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x
) {
    pSprite->x = x;
    sfSprite_setPosition(pSprite->pSpriteHandle, (sfVector2f) { x, pSprite->y });
}

void Sprite_SetY(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT y
) {
    pSprite->y = y;
    sfSprite_setPosition(pSprite->pSpriteHandle, (sfVector2f) { pSprite->x, y });
}

void Sprite_SetPosition(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pSprite->x = x;
    pSprite->y = y;
    sfSprite_setPosition(pSprite->pSpriteHandle, (sfVector2f) { x, y });
}

void Sprite_SetTexture(
    _Inout_ Sprite* pSprite,
    _In_    const Texture* pTexture
) {
    sfSprite_setTexture(pSprite->pSpriteHandle, pTexture->pBitmap, true);
}

void Sprite_Draw(
    _In_ const Sprite* pSprite
) {
    if (!pSprite->bVisible) {
        return;
    }

    sfRenderWindow_drawSprite(Window_GetRenderWindow(), pSprite->pSpriteHandle, NULL);
}

_Check_return_
Vector2 Sprite_GetPositionV(
    _In_ const Sprite* pSprite
) {
    return (Vector2) { pSprite->x, pSprite->y };
}

_Check_return_
FLOAT Sprite_GetWidth(
    _In_ const Sprite* pSprite
) {
    return sfTexture_getSize(sfSprite_getTexture(pSprite->pSpriteHandle)).x;
}

_Check_return_
FLOAT Sprite_GetHeight(
    _In_ const Sprite* pSprite
) {
    return sfTexture_getSize(sfSprite_getTexture(pSprite->pSpriteHandle)).y;
}

_Check_return_
bool Sprite_GetVisible(
    _In_ const Sprite* pSprite
) {
    return pSprite->bVisible;
}

_Check_return_opt_
bool Sprite_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Sprite* pSprite
) {
    if (!pSprite) {
        return false;
    }

    sfSprite_destroy(pSprite->pSpriteHandle);
    SafeFree(pSprite);
    return true;
}
