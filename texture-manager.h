//
// Created by Simon on 21.04.2025.
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "utils.h"

typedef struct _Texture Texture;

typedef struct _TextureEntry {
    Texture* pTexture;
    PCSTR pszName;
} TextureEntry;

typedef struct _TextureManager {
    TextureEntry* arrTextureEntries;
    INT nCount;
    INT nCapacity;
} TextureManager;

_Ret_maybenull_
TextureManager* CreateTextureManager(
    void
    );

_Check_return_opt_
bool LoadTexture(
    _In_   TextureManager* pManager,
    _In_z_ PCSTR pszName,
    _In_z_ PCSTR pszFilename
    );

_Check_return_
Texture* GetTexture(
    _In_   const TextureManager* pManager,
    _In_z_ PCSTR pszName
    );

_Check_return_opt_
bool DestroyTextureManager(
    _Inout_ _Pre_valid_ _Post_invalid_ TextureManager* pManager
    );

#endif //TEXTURE_MANAGER_H
