//
// Created by Simon on 22.04.2025.
//

#include "tilemap-manager.h"

#include <stdio.h>
#include <stdlib.h>

#include "tilemap.h"

_Check_return_ _Ret_maybenull_
TilemapManager* TilemapManager_Create(
    void
) {
    TilemapManager* pManager = malloc(sizeof(TilemapManager));
    if (!pManager) {
        printf("Failed to allocate memory for TilemapManager\n");
        return NULL;
    }

    pManager->nCount = 0;
    pManager->nCapacity = 10;
    pManager->arrTilemapEntries = malloc(pManager->nCapacity * sizeof(TilemapEntry));
    if (!pManager->arrTilemapEntries) {
        printf("Failed to allocate memory for tilemap entries\n");
        SafeFree(pManager);
        return NULL;
    }

    return pManager;
}

_Check_return_ _Ret_maybenull_
Tilemap* TilemapManager_AddTilemap(
    _Inout_ TilemapManager* pManager,
    _In_z_  PCSTR pszName,
    _In_    const FLOAT fTileWidth,
    _In_    const FLOAT fTileHeight
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
    pManager->arrTilemapEntries[pManager->nCount].pTilemap = Tilemap_Create(fTileWidth, fTileHeight);

    pManager->nCount++;

    return pManager->arrTilemapEntries[pManager->nCount - 1].pTilemap;
}

_Check_return_opt_
Result TilemapManager_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ TilemapManager* pManager
) {
    if (!pManager) {
        return RESULT_NULL_POINTER;
    }

    for (int i = 0; i < pManager->nCount; i++) {
        assert(pManager->arrTilemapEntries[i].pTilemap);
        Tilemap_Destroy(pManager->arrTilemapEntries[i].pTilemap);
    }

    SafeFree(pManager->arrTilemapEntries);
    SafeFree(pManager);
    return RESULT_SUCCESS;
}
