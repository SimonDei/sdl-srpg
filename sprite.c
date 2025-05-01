//
// Created by Simon on 21.04.2025.
//

#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include "window.h"
#include "camera.h"
#include "texture.h"

_Ret_maybenull_
Sprite* Sprite_Create(
    _In_ Texture* pTexture,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    Sprite* pSprite = malloc(sizeof(Sprite));
    if (!pSprite) {
        SDL_Log("Failed to allocate memory for Sprite\n");
        return NULL;
    }

    pSprite->pTexture = pTexture;
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
}

void Sprite_SetX(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x
) {
    pSprite->x = x;
}

void Sprite_SetY(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT y
) {
    pSprite->y = y;
}

void Sprite_SetPosition(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pSprite->x = x;
    pSprite->y = y;
}

void Sprite_SetTexture(
    _Inout_ Sprite* pSprite,
    _In_    const Texture* pTexture
) {
    pSprite->pTexture = pTexture;
}

void Sprite_Draw(
    _In_ const Sprite* pSprite
) {
    if (!pSprite->bVisible) {
        return;
    }

    const SDL_FRect srcRect = {
        0,
        0,
        pSprite->pTexture->fWidth,
        pSprite->pTexture->fHeight
    };

    const Vector2 screenPos = WorldToScreen(pSprite->x, pSprite->y);

    const SDL_FRect dstRect = {
        screenPos.x,
        screenPos.y,
        pSprite->pTexture->fWidth * pSprite->fScaleX * Camera_GetZoom(),
        pSprite->pTexture->fHeight * pSprite->fScaleY * Camera_GetZoom()
    };

    SDL_RenderTexture(
        Window_GetRenderer(),
        pSprite->pTexture->pBitmap,
        &srcRect,
        &dstRect
    );
}

_Check_return_
Vector2 Sprite_GetPositionV(
    _In_ const Sprite* pSprite
) {
    return (Vector2){ pSprite->x, pSprite->y };
}

_Check_return_
FLOAT Sprite_GetWidth(
    _In_ const Sprite* pSprite
) {
    return pSprite->pTexture->fWidth;
}

_Check_return_
FLOAT Sprite_GetHeight(
    _In_ const Sprite* pSprite
) {
    return pSprite->pTexture->fHeight;
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

    SafeFree(pSprite);
    return true;
}
