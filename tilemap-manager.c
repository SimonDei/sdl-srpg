//
// Created by Simon on 22.04.2025.
//

#include "tilemap-manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include "tilemap.h"

_Check_return_
TilemapManager* CreateTilemapManager(
    void
) {
    TilemapManager* pManager = malloc(sizeof(TilemapManager));
    if (!pManager) {
        SDL_Log("Failed to allocate memory for TilemapManager\n");
        return NULL;
    }

    pManager->nCount = 0;
    pManager->nCapacity = 10;
    pManager->arrTilemapEntries = malloc(pManager->nCapacity * sizeof(TilemapEntry));
    if (!pManager->arrTilemapEntries) {
        SDL_Log("Failed to allocate memory for tilemap entries\n");
        SafeFree(pManager);
        return NULL;
    }

    return pManager;
}

_Check_return_
Tilemap* AddTilemap(
    _Inout_ TilemapManager* pManager,
    _In_z_  PCSTR pszName,
    _In_    const INT iTileWidth,
    _In_    const INT iTileHeight
) {
    if (pManager->nCount >= pManager->nCapacity) {
        pManager->nCapacity += 10;
        TilemapEntry* arrEntries = realloc(pManager->arrTilemapEntries, pManager->nCapacity * sizeof(TilemapEntry));
        if (!arrEntries) {
            return NULL;
        }
        pManager->arrTilemapEntries = arrEntries;
    }

    pManager->arrTilemapEntries[pManager->nCount].pszName = pszName;
    pManager->arrTilemapEntries[pManager->nCount].pTilemap = CreateTilemap(iTileWidth, iTileHeight);

    pManager->nCount++;

    return pManager->arrTilemapEntries[pManager->nCount - 1].pTilemap;
}

_Check_return_opt_
bool DestroyTilemapManager(
    _Inout_ _Pre_valid_ _Post_invalid_ TilemapManager* pManager
) {
    if (!pManager) {
        return false;
    }

    for (int i = 0; i < pManager->nCount; i++) {
        if (pManager->arrTilemapEntries[i].pTilemap) {
            DestroyTilemap(pManager->arrTilemapEntries[i].pTilemap);
        }
    }

    SafeFree(pManager->arrTilemapEntries);
    SafeFree(pManager);
    return true;
}
