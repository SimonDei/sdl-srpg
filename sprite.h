//
// Created by Simon on 21.04.2025.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "utils.h"
#include "vector2.h"

typedef struct _Texture Texture;

typedef struct _Sprite {
    Texture* pTexture;
    FLOAT x;
    FLOAT y;
    FLOAT fScaleX;
    FLOAT fScaleY;
} Sprite;

_Ret_maybenull_
Sprite* CreateSprite(
    _In_ Texture* pTexture,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

void SetSpriteScale(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT fScaleX,
    _In_    FLOAT fScaleY
    );

void SetSpriteX(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT x
    );

void SetSpriteY(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT y
    );

void SetSpritePosition(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT x,
    _In_    FLOAT y
    );

void SetSpriteTexture(
    _Inout_ Sprite* pSprite,
    _In_    const Texture* pTexture
    );

void DrawSprite(
    _In_ const Sprite* pSprite
    );

_Check_return_
Vector2 GetSpritePositionV(
    _In_ const Sprite* pSprite
    );

_Check_return_opt_
bool DestroySprite(
    _Inout_ _Pre_valid_ _Post_invalid_ Sprite* pSprite
    );

#endif //SPRITE_H
