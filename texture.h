//
// Created by Simon on 21.04.2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "utils.h"
#include "color.h"

typedef struct SDL_Texture SDL_Texture;

typedef struct _Texture {
    SDL_Texture* pBitmap;
    FLOAT fWidth;
    FLOAT fHeight;
    PCSTR pszFilename;
    Color color;
} Texture;

/**
 * @brief Creates a texture from a file.
 *
 * This function loads a texture from the specified file and creates a texture object.
 * The texture can be applied to sprites or other objects for rendering.
 *
 * @param pszFilename Path to the texture file to be loaded.
 * @return A pointer to the created texture, or `NULL` if the texture could not be loaded.
 */
_Ret_maybenull_ Texture* CreateTexture(
    _In_z_ PCSTR pszFilename
    );

/**
 * @brief Sets the color tint of a texture.
 *
 * This function applies a color tint to the specified texture, modifying its appearance
 * when rendered. The color tint can be used for effects such as color filtering.
 *
 * @param pTexture Pointer to the Texture whose color will be changed.
 * @param color    The color to apply to the texture. This color will be blended with the texture.
 */
void SetTextureColor(
    _Inout_ Texture* pTexture,
    _In_    Color color
    );

/**
 * @brief Destroys a texture and frees its resources.
 *
 * This function deallocates the memory used by the texture and invalidates the texture pointer.
 * After calling this function, the texture pointer should not be used.
 *
 * @param pTexture Pointer to the Texture to be destroyed. After the function call, the texture is no longer valid.
 * @return `true` if the texture was successfully destroyed, `false` otherwise.
 */
_Check_return_opt_ bool DestroyTexture(
    _Inout_ _Pre_valid_ _Post_invalid_ Texture* pTexture
    );

#endif //TEXTURE_H
