//
// Created by Simon on 21.04.2025.
//

#ifndef TILESET_H
#define TILESET_H

#include "utils.h"

typedef struct _Texture Texture;

typedef struct _Tileset {
    Texture* pTexture;
    FLOAT fTileWidth;
    FLOAT fTileHeight;
} Tileset;

_Check_return_
Tileset CreateTileset(
    _In_ Texture* pTexture,
    _In_ FLOAT fTileWidth,
    _In_ FLOAT fTileHeight
    );

void DrawTile(
    _In_ const Tileset* pTileset,
    _In_ INT iTileX,
    _In_ INT iTileY,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

void DrawTileIndex(
    _In_ const Tileset* pTileset,
    _In_ INT nTileIndex,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

#endif //TILESET_H
