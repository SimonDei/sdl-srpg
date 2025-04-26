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
Texture* CreateTexture(
    _In_z_ PCSTR pszFilename
) {
    Texture* pTexture = malloc(sizeof(Texture));
    if (!pTexture) {
        SDL_Log("Failed to allocate memory for texture\n");
        return NULL;
    }

    pTexture->pszFilename = pszFilename;
    pTexture->pBitmap = IMG_LoadTexture(GetWindowRenderer(), pszFilename);
    if (!pTexture->pBitmap) {
        SDL_Log("Failed to load texture from %s\n", pszFilename);
        SafeFree(pTexture);
        return NULL;
    }

    SDL_SetTextureScaleMode(pTexture->pBitmap, SDL_SCALEMODE_NEAREST);
    SDL_GetTextureSize(pTexture->pBitmap, &pTexture->fWidth, &pTexture->fHeight);

    return pTexture;
}

_Check_return_opt_
bool DestroyTexture(
    _Inout_ _Pre_valid_ _Post_invalid_ Texture* pTexture
) {
    if (!pTexture || !pTexture->pBitmap) {
        return false;
    }

    SDL_DestroyTexture(pTexture->pBitmap);
    SafeFree(pTexture);
    return true;
}
