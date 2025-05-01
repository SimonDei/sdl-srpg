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
    bool bVisible;
} Sprite;

/**
 * @brief Creates a new sprite with a given texture and position.
 *
 * This function allocates and initializes a new sprite, setting its texture and position on screen.
 * The sprite is created at the specified (x, y) coordinates.
 *
 * @param pTexture Pointer to the Texture to be applied to the sprite.
 * @param x        X coordinate for the initial position of the sprite.
 * @param y        Y coordinate for the initial position of the sprite.
 * @return A pointer to the newly created sprite, or `NULL` if the creation failed.
 */
_Ret_maybenull_ Sprite* Sprite_Create(
    _In_ Texture* pTexture,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

/**
 * @brief Sets the visibility of a sprite.
 *
 * This function changes the visibility state of the specified sprite.
 * When a sprite is marked as invisible, it may be excluded from rendering.
 *
 * @param pSprite Pointer to the Sprite whose visibility will be changed.
 * @param bVisible Boolean flag indicating whether the sprite should be visible (`true`) or hidden (`false`).
 */
void Sprite_SetVisible(
    _Inout_ Sprite* pSprite,
    _In_    bool bVisible
    );

/**
 * @brief Sets the scale of a sprite.
 *
 * This function adjusts the horizontal and vertical scale factors of the specified sprite.
 * Scaling affects how the sprite is rendered on screen, allowing it to appear larger or smaller.
 *
 * @param pSprite Pointer to the Sprite whose scale will be modified.
 * @param fScaleX Horizontal scale factor. A value of 1.0 means no scaling.
 * @param fScaleY Vertical scale factor. A value of 1.0 means no scaling.
 */
void Sprite_SetScale(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT fScaleX,
    _In_    FLOAT fScaleY
    );

/**
 * @brief Sets the horizontal position of a sprite.
 *
 * Updates the X coordinate of the specified sprite, determining its horizontal placement on screen.
 *
 * @param pSprite Pointer to the Sprite whose X position will be set.
 * @param x       New X coordinate for the sprite.
 */
void Sprite_SetX(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT x
    );

/**
 * @brief Sets the vertical position of a sprite.
 *
 * Updates the Y coordinate of the specified sprite, determining its vertical placement on screen.
 *
 * @param pSprite Pointer to the Sprite whose Y position will be set.
 * @param y       New Y coordinate for the sprite.
 */
void Sprite_SetY(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT y
    );

/**
 * @brief Sets the position of a sprite.
 *
 * Updates both the X and Y coordinates of the specified sprite, determining its placement on screen.
 *
 * @param pSprite Pointer to the Sprite whose position will be set.
 * @param x       New X coordinate for the sprite.
 * @param y       New Y coordinate for the sprite.
 */
void Sprite_SetPosition(
    _Inout_ Sprite* pSprite,
    _In_    FLOAT x,
    _In_    FLOAT y
    );

/**
 * @brief Sets the texture of a sprite.
 *
 * Updates the sprite's texture, changing the image or appearance rendered on screen.
 *
 * @param pSprite Pointer to the Sprite whose texture will be set.
 * @param pTexture Pointer to the Texture to be applied to the sprite.
 */
void Sprite_SetTexture(
    _Inout_ Sprite* pSprite,
    _In_    const Texture* pTexture
    );

void Sprite_Draw(
    _In_ const Sprite* pSprite
    );

/**
 * @brief Retrieves the position of a sprite as a vector.
 *
 * This function returns the X and Y coordinates of the specified sprite as a `Vector2` struct.
 *
 * @param pSprite Pointer to the Sprite whose position is to be retrieved.
 * @return A `Vector2` struct containing the X and Y position of the sprite.
 */
_Check_return_ Vector2 Sprite_GetPositionV(
    _In_ const Sprite* pSprite
    );

/**
 * @brief Retrieves the width of a sprite.
 *
 * This function returns the width of the specified sprite, which can be used for positioning,
 * collision detection, or rendering calculations.
 *
 * @param pSprite Pointer to the Sprite whose width is to be retrieved.
 * @return The width of the sprite as a `FLOAT` value.
 */
_Check_return_ FLOAT Sprite_GetWidth(
    _In_ const Sprite* pSprite
    );

/**
 * @brief Retrieves the height of a sprite.
 *
 * This function returns the height of the specified sprite, which can be used for positioning,
 * collision detection, or rendering calculations.
 *
 * @param pSprite Pointer to the Sprite whose height is to be retrieved.
 * @return The height of the sprite as a `FLOAT` value.
 */
_Check_return_ FLOAT Sprite_GetHeight(
    _In_ const Sprite* pSprite
    );

/**
 * @brief Retrieves the visibility state of a sprite.
 *
 * This function checks if the specified sprite is visible or hidden.
 *
 * @param pSprite Pointer to the Sprite whose visibility state is to be checked.
 * @return `true` if the sprite is visible, `false` if it is hidden.
 */
_Check_return_ bool Sprite_GetVisible(
    _In_ const Sprite* pSprite
    );

/**
 * @brief Destroys a sprite and frees its resources.
 *
 * This function deallocates the memory used by the sprite and invalidates the sprite pointer.
 * It is important to ensure that the sprite pointer is not used after calling this function.
 *
 * @param pSprite Pointer to the Sprite to be destroyed. After this function call, the sprite is no longer valid.
 * @return `true` if the sprite was successfully destroyed, `false` otherwise.
 */
_Check_return_opt_ bool Sprite_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Sprite* pSprite
    );

#endif //SPRITE_H
