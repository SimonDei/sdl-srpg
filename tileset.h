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

/**
 * @brief Creates a new tileset using the provided texture and tile dimensions.
 *
 * This function initializes a new `Tileset` using the specified texture and the dimensions of
 * the individual tiles (width and height). The resulting tileset can then be used to render
 * tiles in a tilemap.
 *
 * @param pTexture     Pointer to the `Texture` containing the tiles for the tileset.
 * @param fTileWidth   The width of each tile in the tileset.
 * @param fTileHeight  The height of each tile in the tileset.
 * @return A `Tileset` struct initialized with the provided texture and tile dimensions.
 */
_Check_return_ Tileset CreateTileset(
    _In_ Texture* pTexture,
    _In_ FLOAT fTileWidth,
    _In_ FLOAT fTileHeight
    );

/**
 * @brief Draws a tile from a tileset at a specified position.
 *
 * This function renders a single tile from the specified tileset at the given world coordinates.
 * The tile to be drawn is determined by its position in the tileset, using the `iTileX` and `iTileY`
 * coordinates to identify the correct tile within the texture. The tile is then drawn at the screen
 * position specified by `x` and `y`.
 *
 * @param pTileset Pointer to the `Tileset` containing the tiles.
 * @param iTileX   The X index of the tile within the tileset (tile's horizontal position).
 * @param iTileY   The Y index of the tile within the tileset (tile's vertical position).
 * @param x        The X coordinate in world space where the tile will be drawn.
 * @param y        The Y coordinate in world space where the tile will be drawn.
 */
void DrawTile(
    _In_ const Tileset* pTileset,
    _In_ INT iTileX,
    _In_ INT iTileY,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

/**
 * @brief Draws a tile from a tileset using a tile index at a specified position.
 *
 * This function renders a single tile from the specified tileset, determined by its index (`nTileIndex`),
 * at the given world coordinates (`x`, `y`). The tile index is used to calculate the position of the tile
 * within the tileset texture. The tile is then drawn at the specified position in the world space.
 *
 * @param pTileset     Pointer to the `Tileset` containing the tiles.
 * @param nTileIndex   The index of the tile within the tileset.
 * @param x            The X coordinate in world space where the tile will be drawn.
 * @param y            The Y coordinate in world space where the tile will be drawn.
 */
void DrawTileIndex(
    _In_ const Tileset* pTileset,
    _In_ INT nTileIndex,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

#endif //TILESET_H
