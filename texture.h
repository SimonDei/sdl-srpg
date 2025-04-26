//
// Created by Simon on 21.04.2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "utils.h"

typedef struct SDL_Texture SDL_Texture;

typedef struct _Texture {
    SDL_Texture* pBitmap;
    FLOAT fWidth;
    FLOAT fHeight;
    PCSTR pszFilename;
} Texture;

_Ret_maybenull_
Texture* CreateTexture(
    _In_z_ PCSTR pszFilename
    );

_Check_return_opt_
bool DestroyTexture(
    _Inout_ _Pre_valid_ _Post_invalid_ Texture* pTexture
    );

#endif //TEXTURE_H
