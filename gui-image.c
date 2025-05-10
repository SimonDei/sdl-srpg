//
// Created by Simon on 09.05.2025.
//

#include "gui-image.h"

#include "gui.h"
#include "sprite.h"

GuiElement* GuiImage_Create(
    _In_ const Texture* pTexture,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    GuiElement* element = malloc(sizeof(GuiElement));
    element->type = GUI_TYPE_IMAGE;
    element->image.pSprite = Sprite_Create(pTexture, x, y);
    return element;
}

void GuiImage_Draw(
    _In_ const GuiImage* pGuiImage
) {
    Sprite_Draw(pGuiImage->pSprite);
}

bool GuiImage_Destroy(
    _Inout_ GuiImage* pGuiImage
) {
    if (!pGuiImage) {
        return false;
    }

    Sprite_Destroy(pGuiImage->pSprite);
    return true;
}
