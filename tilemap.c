//
// Created by Simon on 22.04.2025.
//

#include "tilemap.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>

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
        printf("Failed to open layer file: %s\n", pszFilename);
        return (Layer){ 0 };
    }

    char buffer[1024];
    fgets(buffer, 1024, pFile);
    layer.usWidth = (UINT16)strtol(buffer, NULL, 10);

    fgets(buffer, 1024, pFile);
    layer.usHeight = (UINT16)strtol(buffer, NULL, 10);

    layer.arrTiles = malloc((size_t)(layer.usWidth * layer.usHeight) * sizeof(BYTE));
    if (!layer.arrTiles) {
        printf("Failed to allocate memory for layer tiles\n");
        fclose(pFile);
        return (Layer){ 0 };
    }

    int nIndex = 0;

    while (fgets(buffer, 1024, pFile)) {
        const char* pszTileId = strtok(buffer, ",");
        while (pszTileId != NULL) {
            if (nIndex < layer.usWidth * layer.usHeight) {
                layer.arrTiles[nIndex] = (BYTE)strtol(pszTileId, NULL, 10);
                nIndex++;
            }
            pszTileId = strtok(NULL, ",");
        }
    }

    fclose(pFile);
    return layer;
}

_Check_return_ _Ret_maybenull_
Tilemap* Tilemap_Create(
    _In_ const FLOAT fTileWidth,
    _In_ const FLOAT fTileHeight
) {
    Tilemap* pTilemap = malloc(sizeof(Tilemap));
    if (!pTilemap) {
        printf("Failed to allocate memory for Tilemap\n");
        return NULL;
    }

    pTilemap->pSpriteHandle = sfSprite_create();
    pTilemap->fTileWidth = fTileWidth;
    pTilemap->fTileHeight = fTileHeight;
    pTilemap->nCount = 0;
    pTilemap->nCapacity = 10;
    pTilemap->arrLayers = malloc(10 * sizeof(Layer));

    return pTilemap;
}

void Tilemap_LoadLayer(
    _Inout_ Tilemap* pTilemap,
    _In_z_  PCSTR pszFilename
) {
    pTilemap->arrLayers[pTilemap->nCount] = LoadLayer(pszFilename);
    pTilemap->nCount++;
}

void Tilemap_SetTexture(
    _Inout_ Tilemap* pTilemap,
    _In_    const Texture* pTexture
) {
    pTilemap->pTilesetTexture = pTexture;
    sfSprite_setTexture(
        pTilemap->pSpriteHandle,
        pTexture->pBitmap,
        true
    );
}

void Tilemap_Draw(
    _In_ const Tilemap* pTilemap
) {
    for (int nLayer = 0; nLayer < pTilemap->nCount; nLayer++) {
        for (int nTile = 0; nTile < pTilemap->arrLayers[nLayer].usWidth * pTilemap->arrLayers[nLayer].usHeight; nTile++) {
            const int iTileX = pTilemap->arrLayers[nLayer].arrTiles[nTile] % (int)(pTilemap->pTilesetTexture->fWidth / pTilemap->fTileWidth);
            const int iTileY = pTilemap->arrLayers[nLayer].arrTiles[nTile] / (int)(pTilemap->pTilesetTexture->fWidth / pTilemap->fTileWidth);

            sfSprite_setTextureRect(
                pTilemap->pSpriteHandle,
                (sfIntRect) {
                    iTileX * (int)pTilemap->fTileWidth,
                    iTileY * (int)pTilemap->fTileHeight,
                    (int)pTilemap->fTileWidth,
                    (int)pTilemap->fTileHeight
                }
            );

            sfSprite_setPosition(
                pTilemap->pSpriteHandle,
                (sfVector2f) {
                    nTile % pTilemap->arrLayers[nLayer].usWidth * pTilemap->fTileWidth,
                    nTile / pTilemap->arrLayers[nLayer].usWidth * pTilemap->fTileHeight
                }
            );

            sfRenderWindow_drawSprite(Window_GetRenderWindow(), pTilemap->pSpriteHandle, NULL);
        }
    }
}

_Check_return_
POINT MapPositionToTile(
    _In_ const Tilemap* pTilemap,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    return (POINT) {
        (int)floorf(x / pTilemap->fTileWidth),
        (int)floorf(y / pTilemap->fTileHeight)
    };
}

_Check_return_
POINT MapPositionToTileV(
    _In_ const Tilemap* pTilemap,
    _In_ const VECTOR2 position
) {
    return (POINT) {
        (int)floorf(position.x / pTilemap->fTileWidth),
        (int)floorf(position.y / pTilemap->fTileHeight)
    };
}

_Check_return_opt_
bool Tilemap_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Tilemap* pTilemap
) {
    if (!pTilemap) {
        return false;
    }

    sfSprite_destroy(pTilemap->pSpriteHandle);

    for (int i = 0; i < pTilemap->nCount; i++) {
        SafeFree(pTilemap->arrLayers[i].arrTiles);
    }

    SafeFree(pTilemap->arrLayers);
    SafeFree(pTilemap);

    return true;
}
