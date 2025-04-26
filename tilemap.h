//
// Created by Simon on 22.04.2025.
//

#ifndef TILEMAP_H
#define TILEMAP_H

#include "utils.h"
#include "point.h"

typedef struct _Layer Layer;
typedef struct _Texture Texture;

typedef struct _Tilemap {
    Layer* arrLayers;
    INT nCount;
    INT nCapacity;
    FLOAT fTileWidth;
    FLOAT fTileHeight;
    Texture* pTilesetTexture;
} Tilemap;

_Check_return_
Tilemap* CreateTilemap(
    _In_ FLOAT fTileWidth,
    _In_ FLOAT fTileHeight
    );

void LoadTilemapLayer(
    _Inout_ Tilemap* pTilemap,
    _In_z_  PCSTR pszFilename
    );

void SetTilemapTexture(
    _Inout_ Tilemap* pTilemap,
    _In_    Texture* pTexture
    );

void DrawTilemap(
    _In_ const Tilemap* pTilemap
    );

_Check_return_
Point MapPositionToTile(
    _In_ const Tilemap* pTilemap,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

_Check_return_opt_
bool DestroyTilemap(
    _Inout_ _Pre_valid_ _Post_invalid_ Tilemap* pTilemap
    );

#endif //TILEMAP_H
