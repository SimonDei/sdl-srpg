//
// Created by Simon on 09.05.2025.
//

#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "utils.h"

typedef struct _GuiElement GuiElement;
typedef struct _Sprite Sprite;
typedef struct _Texture Texture;

typedef struct _GuiImage {
    Sprite* pSprite; // Pointer to the sprite object
} GuiImage;

_Check_return_ _Ret_maybenull_ GuiElement* GuiImage_Create(
    _In_ const Texture* pTexture,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

void GuiImage_Draw(
    _In_ const GuiImage* pGuiImage
    );

bool GuiImage_Destroy(
    _Inout_ GuiImage* pGuiImage
    );

#endif //GUI_IMAGE_H
