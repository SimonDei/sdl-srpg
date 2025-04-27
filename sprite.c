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
Sprite* CreateSprite(
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
    pSprite->color = (Color){ 255, 255, 255, 255 };

    return pSprite;
}

void SetSpriteScale(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT fScaleX,
    _In_    const FLOAT fScaleY
) {
    pSprite->fScaleX = fScaleX;
    pSprite->fScaleY = fScaleY;
}

void SetSpriteX(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x
) {
    pSprite->x = x;
}

void SetSpriteY(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT y
) {
    pSprite->y = y;
}

void SetSpritePosition(
    _Inout_ Sprite* pSprite,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pSprite->x = x;
    pSprite->y = y;
}

void SetSpriteTexture(
    _Inout_ Sprite* pSprite,
    _In_    const Texture* pTexture
) {
    pSprite->pTexture = pTexture;
}

void DrawSprite(
    _In_ const Sprite* pSprite
) {
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
        pSprite->pTexture->fWidth * pSprite->fScaleX * GetCameraZoom(),
        pSprite->pTexture->fHeight * pSprite->fScaleY * GetCameraZoom()
    };

    SDL_RenderTexture(
        GetWindowRenderer(),
        pSprite->pTexture->pBitmap,
        &srcRect,
        &dstRect
    );
}

_Check_return_
Vector2 GetSpritePositionV(
    _In_ const Sprite* pSprite
) {
    return (Vector2){ pSprite->x, pSprite->y };
}

_Check_return_opt_
bool DestroySprite(
    _Inout_ _Pre_valid_ _Post_invalid_ Sprite* pSprite
) {
    if (!pSprite) {
        return false;
    }

    SafeFree(pSprite);
    return true;
}
