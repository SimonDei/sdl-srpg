#ifndef GUI_H
#define GUI_H

#include "utils.h"
#include "gui-image.h"

typedef enum _GuiType {
    GUI_TYPE_IMAGE,
    GUI_TYPE_TEXT,
    GUI_TYPE_BUTTON
} GuiType;

typedef struct _GuiElement {
    GuiType type;
    union {
        GuiImage image;
    };
} GuiElement;

typedef struct _Gui {
    GuiElement** arrElements; // << Array of elements
    INT cElements;            // << Number of elements in the array
    INT nMaxElements;         // << Maximum number of elements that can be stored
} Gui;

/**
 * @brief Initializes the GUI system.
 *
 * This function sets up the GUI system, preparing it for use. It may involve loading resources,
 * initializing components, and setting up the rendering context.
 *
 * @return A pointer to the initialized GUI object, or NULL on failure.
 */
_Check_return_ _Ret_maybenull_ Gui* Gui_Create(
    void
    );

/**
 * @brief Adds a static texture to the GUI.
 *
 * This function adds a static texture to the GUI at the specified position. The texture is identified
 * by its text representation, which may be a file path or resource identifier.
 *
 * @param pGui Pointer to the GUI object where the texture will be added.
 * @param pElement The texture to be added.
 */
void Gui_AddElement(
    _Inout_ Gui* pGui,
    _In_    GuiElement* pElement
    );

void Gui_Draw(
    _In_ const Gui* pGui
    );

_Check_return_opt_ bool GuiElement_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ GuiElement* pGuiElement
    );

/**
 * @brief Destroys the GUI system.
 *
 * This function cleans up and deallocates any resources used by the GUI system. It should be called
 * when the GUI is no longer needed to prevent memory leaks.
 *
 * @param pGui Pointer to the GUI object to be destroyed.
 */
_Check_return_opt_ bool Gui_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Gui* pGui
    );

#endif //GUI_H
