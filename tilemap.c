//
// Created by Simon on 22.04.2025.
//

#include "tilemap.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>

#include "window.h"
#include "camera.h"
#include "layer.h"
#include "texture.h"

_Check_return_
static Layer LoadLayer(
    _In_z_ PCSTR pszFilename
) {
    Layer layer = { 0 };

    FILE* pFile = fopen(pszFilename, "r");
    if (!pFile) {
        SDL_Log("Failed to open layer file: %s\n", pszFilename);
        return (Layer){ 0 };
    }

    char buffer[1024];
    fgets(buffer, 1024, pFile);
    layer.usWidth = (unsigned short)strtol(buffer, NULL, 10);

    fgets(buffer, 1024, pFile);
    layer.usHeight = (unsigned short)strtol(buffer, NULL, 10);

    layer.arrTiles = malloc((size_t)(layer.usWidth * layer.usHeight) * sizeof(unsigned char));
    if (!layer.arrTiles) {
        SDL_Log("Failed to allocate memory for layer tiles\n");
        fclose(pFile);
        return (Layer){ 0 };
    }

    int nIndex = 0;

    while (fgets(buffer, 1024, pFile)) {
        const char* pszTileId = strtok(buffer, ",");
        while (pszTileId != NULL) {
            if (nIndex < layer.usWidth * layer.usHeight) {
                layer.arrTiles[nIndex] = (unsigned char)strtol(pszTileId, NULL, 10);
                nIndex++;
            }
            pszTileId = strtok(NULL, ",");
        }
    }

    fclose(pFile);
    return layer;
}

_Check_return_
Tilemap* CreateTilemap(
    _In_ const FLOAT fTileWidth,
    _In_ const FLOAT fTileHeight
) {
    Tilemap* pTilemap = malloc(sizeof(Tilemap));
    if (!pTilemap) {
        SDL_Log("Failed to allocate memory for Tilemap\n");
        return NULL;
    }

    pTilemap->fTileWidth = fTileWidth;
    pTilemap->fTileHeight = fTileHeight;
    pTilemap->nCount = 0;
    pTilemap->nCapacity = 10;
    pTilemap->arrLayers = malloc(10 * sizeof(Layer));

    return pTilemap;
}

void LoadTilemapLayer(
    _Inout_ Tilemap* pTilemap,
    _In_z_  PCSTR pszFilename
) {
    pTilemap->arrLayers[pTilemap->nCount] = LoadLayer(pszFilename);
    pTilemap->nCount++;
}

void SetTilemapTexture(
    _Inout_ Tilemap* pTilemap,
    _In_    Texture* pTexture
) {
    pTilemap->pTilesetTexture = pTexture;
}

void DrawTilemap(
    _In_ const Tilemap* pTilemap
) {
    for (int nLayer = 0; nLayer < pTilemap->nCount; nLayer++) {
        for (int nTile = 0; nTile < pTilemap->arrLayers[nLayer].usWidth * pTilemap->arrLayers[nLayer].usHeight; nTile++) {
            const int iTileX = pTilemap->arrLayers[nLayer].arrTiles[nTile] % (int)(pTilemap->pTilesetTexture->fWidth / pTilemap->fTileWidth);
            const int iTileY = pTilemap->arrLayers[nLayer].arrTiles[nTile] / (int)(pTilemap->pTilesetTexture->fWidth / pTilemap->fTileWidth);

            const SDL_FRect srcRect = {
                (float)iTileX * pTilemap->fTileWidth,
                (float)iTileY * pTilemap->fTileHeight,
                pTilemap->fTileWidth,
                pTilemap->fTileHeight
            };

            const Vector2 screenPos = WorldToScreen(
                (float)(nTile % pTilemap->arrLayers[nLayer].usWidth) * pTilemap->fTileWidth,
                floorf((float)nTile / (float)pTilemap->arrLayers[nLayer].usWidth) * pTilemap->fTileHeight
            );

            const SDL_FRect dstRect = {
                screenPos.x,
                screenPos.y,
                pTilemap->fTileWidth * GetCameraZoom(),
                pTilemap->fTileHeight * GetCameraZoom()
            };

            SDL_RenderTexture(
                GetWindowRenderer(),
                pTilemap->pTilesetTexture->pBitmap,
                &srcRect,
                &dstRect
            );
        }
    }
}

_Check_return_
Point MapPositionToTile(
    _In_ const Tilemap* pTilemap,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    return (Point) {
        (int)(floorf(x / GetCameraZoom()) / pTilemap->fTileWidth),
        (int)(floorf(y / GetCameraZoom()) / pTilemap->fTileHeight)
    };
}

_Check_return_opt_
bool DestroyTilemap(
    _Inout_ _Pre_valid_ _Post_invalid_ Tilemap* pTilemap
) {
    if (!pTilemap) {
        return false;
    }

    for (int i = 0; i < pTilemap->nCount; i++) {
        SafeFree(pTilemap->arrLayers[i].arrTiles);
    }

    SafeFree(pTilemap->arrLayers);
    SafeFree(pTilemap);

    return true;
}
