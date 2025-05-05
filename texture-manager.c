//
// Created by Simon on 21.04.2025.
//

#include "texture-manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "utils.h"

_Check_return_ _Ret_maybenull_
TextureManager* TextureManager_Create(
    void
) {
    TextureManager* pManager = malloc(sizeof(TextureManager));
    if (!pManager) {
        printf("Failed to allocate memory for TextureManager\n");
        return NULL;
    }

    pManager->nCount = 0;
    pManager->nCapacity = 10;
    pManager->arrTextureEntries = malloc(pManager->nCapacity * sizeof(TextureEntry));
    if (!pManager->arrTextureEntries) {
        printf("Failed to allocate memory for textures\n");
        SafeFree(pManager);
        return NULL;
    }

    return pManager;
}

_Check_return_opt_
Result TextureManager_LoadTexture(
    _In_   TextureManager* pManager,
    _In_z_ PCSTR pszName,
    _In_z_ PCSTR pszFilename
) {
    if (pManager->nCount >= pManager->nCapacity) {
        pManager->nCapacity += 10;
        TextureEntry* arrEntries = realloc(pManager->arrTextureEntries, pManager->nCapacity * sizeof(TextureEntry));
        if (!arrEntries) {
            return RESULT_REALLOC_FAILED;
        }
        pManager->arrTextureEntries = arrEntries;
    }

    Texture* pTexture = Texture_Create(pszFilename);
    if (!pTexture) {
        return RESULT_MALLOC_FAILED;
    }

    pManager->arrTextureEntries[pManager->nCount].pszName = pszName;
    pManager->arrTextureEntries[pManager->nCount].pTexture = pTexture;
    pManager->nCount++;

    return RESULT_SUCCESS;
}

_Check_return_
Texture* TextureManager_GetTexture(
    _In_   const TextureManager* pManager,
    _In_z_ PCSTR pszName
) {
    for (int i = 0; i < pManager->nCount; i++) {
        if (strcmp(pManager->arrTextureEntries[i].pszName, pszName) == 0) {
            return pManager->arrTextureEntries[i].pTexture;
        }
    }
    return NULL;
}

_Check_return_opt_
Result TextureManager_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ TextureManager* pManager
) {
    if (!pManager || !pManager->arrTextureEntries) {
        return RESULT_NULL_POINTER;
    }

    for (int i = 0; i < pManager->nCount; i++) {
        Texture_Destroy(pManager->arrTextureEntries[i].pTexture);
    }

    SafeFree(pManager->arrTextureEntries);
    SafeFree(pManager);
    return RESULT_SUCCESS;
}
