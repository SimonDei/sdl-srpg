//
// Created by Simon on 21.04.2025.
//

#include "tileset.h"

#include <SDL3/SDL.h>

#include "window.h"
#include "camera.h"
#include "texture.h"

_Check_return_
Tileset CreateTileset(
    _In_ Texture* pTexture,
    _In_ const FLOAT fTileWidth,
    _In_ const FLOAT fTileHeight
) {
    Tileset tileset = { 0 };

    tileset.pTexture = pTexture;
    tileset.fTileWidth = fTileWidth;
    tileset.fTileHeight = fTileHeight;

    return tileset;
}

void DrawTile(
    _In_ const Tileset* pTileset,
    _In_ const INT iTileX,
    _In_ const INT iTileY,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    const SDL_FRect srcRect = {
        (float)iTileX * pTileset->fTileWidth,
        (float)iTileY * pTileset->fTileHeight,
        pTileset->fTileWidth,
        pTileset->fTileHeight
    };

    const Vector2 screenPos = WorldToScreen(x, y);

    const SDL_FRect dstRect = {
        screenPos.x,
        screenPos.y,
        pTileset->fTileWidth * Camera_GetZoom(),
        pTileset->fTileHeight * Camera_GetZoom()
    };

    SDL_RenderTexture(
        Window_GetRenderer(),
        pTileset->pTexture->pBitmap,
        &srcRect,
        &dstRect
    );
}

void DrawTileIndex(
    _In_ const Tileset* pTileset,
    _In_ const INT nTileIndex,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    const int iTileX = nTileIndex % (int)(pTileset->pTexture->fWidth / pTileset->fTileWidth);
    const int iTileY = nTileIndex / (int)(pTileset->pTexture->fWidth / pTileset->fTileWidth);

    DrawTile(pTileset, iTileX, iTileY, x, y);
}
