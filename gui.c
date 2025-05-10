#include "gui.h"

#include <SFML/Graphics.h>

#include "sprite.h"

_Check_return_ _Ret_maybenull_
Gui* Gui_Create(
    void
) {
    Gui* pGui = malloc(sizeof(Gui));
    if (!pGui) {
        printf("Failed to allocate memory for GUI\n");
        return NULL;
    }

    pGui->cElements = 0;
    pGui->nMaxElements = 10;
    pGui->arrElements = malloc(pGui->nMaxElements * sizeof(GuiElement*));
    if (!pGui->arrElements) {
        printf("Failed to allocate memory for GUI textures\n");
        SafeFree(pGui);
        return NULL;
    }

    return pGui;
}

void Gui_AddElement(
    _Inout_ Gui* pGui,
    _In_    GuiElement* pElement
) {
    if (pGui->cElements >= pGui->nMaxElements) {
        pGui->nMaxElements += 10;
        GuiElement** pElements = realloc(pGui->arrElements, pGui->nMaxElements * sizeof(GuiElement*));
        if (!pElements) {
            printf("Failed to reallocate memory for GUI elements\n");
            return;
        }
        pGui->arrElements = pElements;
    }
    pGui->arrElements[pGui->cElements++] = pElement;
}

void Gui_Draw(
    _In_ const Gui* pGui
) {
    for (INT i = 0; i < pGui->cElements; i++) {
        const GuiElement* pCurrentElement = pGui->arrElements[i];
        switch (pCurrentElement->type) {
            case GUI_TYPE_IMAGE:
                GuiImage_Draw(&pCurrentElement->image);
                break;
            default:
                break;
        }
    }
}

_Check_return_opt_
bool GuiElement_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ GuiElement* pGuiElement
) {
    if (!pGuiElement) {
        return false;
    }

    switch (pGuiElement->type) {
        case GUI_TYPE_IMAGE:
            GuiImage_Destroy(&pGuiElement->image);
            break;
        default:
            break;
    }

    SafeFree(pGuiElement);

    return true;
}

_Check_return_opt_
bool Gui_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Gui* pGui
) {
    if (!pGui || !pGui->arrElements) {
        return false;
    }

    for (int i = 0; i < pGui->cElements; i++) {
        GuiElement_Destroy(pGui->arrElements[i]);
    }

    SafeFree(pGui->arrElements);
    SafeFree(pGui);

    return true;
}
