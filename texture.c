//
// Created by Simon on 21.04.2025.
//

#include "texture.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "window.h"

_Ret_maybenull_
Texture* Texture_Create(
    _In_z_ PCSTR pszFilename
) {
    Texture* pTexture = malloc(sizeof(Texture));
    if (!pTexture) {
        SDL_Log("Failed to allocate memory for texture\n");
        return NULL;
    }

    pTexture->color = (Color){ 255, 255, 255, 255 };
    pTexture->pszFilename = pszFilename;
    pTexture->pBitmap = IMG_LoadTexture(Window_GetRenderer(), pszFilename);
    if (!pTexture->pBitmap) {
        SDL_Log("Failed to load texture from %s\n", pszFilename);
        SafeFree(pTexture);
        return NULL;
    }

    SDL_SetTextureScaleMode(pTexture->pBitmap, SDL_SCALEMODE_NEAREST);
    SDL_GetTextureSize(pTexture->pBitmap, &pTexture->fWidth, &pTexture->fHeight);

    return pTexture;
}

void Texture_SetColor(
    _Inout_ Texture* pTexture,
    _In_    const Color color
) {
    pTexture->color = color;
    SDL_SetTextureColorMod(pTexture->pBitmap, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(pTexture->pBitmap, color.a);
}

_Check_return_opt_
bool Texture_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Texture* pTexture
) {
    if (!pTexture || !pTexture->pBitmap) {
        return false;
    }

    SDL_DestroyTexture(pTexture->pBitmap);
    SafeFree(pTexture);
    return true;
}
