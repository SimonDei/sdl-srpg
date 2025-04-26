//
// Created by Simon on 22.04.2025.
//

#ifndef TILEMAP_MANAGER_H
#define TILEMAP_MANAGER_H

#include "utils.h"

typedef struct _Tilemap Tilemap;

typedef struct _TilemapEntry {
    Tilemap* pTilemap;
    PCSTR pszName;
} TilemapEntry;

typedef struct _TilemapManager {
    TilemapEntry* arrTilemapEntries;
    INT nCount;
    INT nCapacity;
} TilemapManager;

_Check_return_
TilemapManager* CreateTilemapManager(
    void
    );

_Check_return_
Tilemap* AddTilemap(
    _Inout_ TilemapManager* pManager,
    _In_z_  PCSTR pszName,
    _In_    INT iTileWidth,
    _In_    INT iTileHeight
    );

_Check_return_opt_
bool DestroyTilemapManager(
    _Inout_ _Pre_valid_ _Post_invalid_ TilemapManager* pManager
    );

#endif //TILEMAP_MANAGER_H
