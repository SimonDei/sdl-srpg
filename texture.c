//
// Created by Simon on 21.04.2025.
//

#include "texture.h"

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "window.h"

_Check_return_ _Ret_maybenull_
Texture* Texture_Create(
    _In_z_ PCSTR pszFilename
) {
    Texture* pTexture = malloc(sizeof(Texture));
    if (!pTexture) {
        printf("Failed to allocate memory for texture\n");
        return NULL;
    }

    pTexture->color = (Color) { 255, 255, 255, 255 };
    pTexture->pszFilename = pszFilename;
    pTexture->pBitmap = sfTexture_createFromFile(pszFilename, NULL);
    if (!pTexture->pBitmap) {
        printf("Failed to load texture from %s\n", pszFilename);
        SafeFree(pTexture);
        return NULL;
    }

    const sfVector2u vTextureSize = sfTexture_getSize(pTexture->pBitmap);
    pTexture->fWidth = (FLOAT)vTextureSize.x;
    pTexture->fHeight = (FLOAT)vTextureSize.y;

    // SDL_SetTextureScaleMode(pTexture->pBitmap, SDL_SCALEMODE_NEAREST);

    return pTexture;
}

void Texture_SetColor(
    _Inout_ Texture* pTexture,
    _In_    const Color color
) {
    pTexture->color = color;
    // SDL_SetTextureColorMod(pTexture->pBitmap, color.r, color.g, color.b);
    // SDL_SetTextureAlphaMod(pTexture->pBitmap, color.a);
}

_Check_return_opt_
bool Texture_Destroy(
    _Inout_ _Post_invalid_ Texture* pTexture
) {
    if (!pTexture || !pTexture->pBitmap) {
        return false;
    }

    sfTexture_destroy(pTexture->pBitmap);
    SafeFree(pTexture);
    return true;
}
