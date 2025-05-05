//
// Created by Simon on 22.04.2025.
//

#ifndef TILEMAP_H
#define TILEMAP_H

#include "utils.h"
#include "point.h"
#include "vector2.h"

typedef struct _Layer Layer;
typedef struct _Texture Texture;
typedef struct sfSprite sfSprite;

typedef struct _Tilemap {
    sfSprite* pSpriteHandle;
    Layer* arrLayers;
    INT nCount;
    INT nCapacity;
    FLOAT fTileWidth;
    FLOAT fTileHeight;
    const Texture* pTilesetTexture;
} Tilemap;

/**
 * @brief Creates a new tilemap.
 *
 * This function creates and initializes a new `Tilemap` with the specified tile width and height. The tilemap
 * is created without any tile data, and additional operations like adding tiles or loading map data can be performed later.
 *
 * @param fTileWidth  The width (in pixels) of each tile in the tilemap.
 * @param fTileHeight The height (in pixels) of each tile in the tilemap.
 *
 * @return A pointer to the newly created `Tilemap`, or `NULL` if the creation failed.
 */
_Check_return_ _Ret_maybenull_ Tilemap* Tilemap_Create(
    _In_ FLOAT fTileWidth,
    _In_ FLOAT fTileHeight
    );

/**
 * @brief Loads a tilemap layer from a file into the specified tilemap.
 *
 * This function loads a tilemap layer from a file and adds it to the provided `Tilemap`. The layer data is
 * read from the specified file and the tilemap is updated accordingly. The file format should match the expected
 * format for tilemap layers (e.g., a grid of tile indices).
 *
 * @param pTilemap  Pointer to the `Tilemap` where the layer will be loaded.
 * @param pszFilename The path to the file containing the tilemap layer data to be loaded.
 *
 * @note The file should be in the correct format expected by the system. This function will overwrite any existing
 *       layer data in the tilemap.
 */
void Tilemap_LoadLayer(
    _Inout_ Tilemap* pTilemap,
    _In_z_  PCSTR pszFilename
    );

/**
 * @brief Sets the texture for a tilemap.
 *
 * This function assigns a texture to the specified `Tilemap`. The texture is used to render the tiles in the tilemap.
 * The texture should typically be a tileset image that contains all the tiles used in the map.
 *
 * @param pTilemap  Pointer to the `Tilemap` for which the texture will be set.
 * @param pTexture  Pointer to the `Texture` that will be assigned to the tilemap.
 *
 * @note The texture should contain the necessary tiles in the expected layout for proper rendering.
 */
void Tilemap_SetTexture(
    _Inout_ Tilemap* pTilemap,
    _In_    const Texture* pTexture
    );

/**
 * @brief Renders a tilemap to the screen.
 *
 * This function draws the entire tilemap to the screen using the texture assigned to the tilemap. Each tile
 * in the tilemap is rendered according to its position and the texture it uses.
 *
 * @param pTilemap Pointer to the `Tilemap` to be rendered. The function assumes that the tilemap has been properly
 *                 initialized and contains valid tile data.
 *
 * @note The function uses the current rendering context, so ensure that the camera, projection, and other settings
 *       are correctly configured before drawing the tilemap.
 */
void Tilemap_Draw(
    _In_ const Tilemap* pTilemap
    );

/**
 * @brief Converts world coordinates to tile coordinates in a tilemap.
 *
 * This function takes a position in world space (given by `x` and `y` coordinates) and converts it to the corresponding
 * tile coordinates within the specified `Tilemap`. The returned `Point` represents the tile's position in terms of
 * the tile grid (i.e., the tile's row and column).
 *
 * @param pTilemap Pointer to the `Tilemap` for which the world position will be converted to tile coordinates.
 * @param x        The x-coordinate in world space (usually in pixels).
 * @param y        The y-coordinate in world space (usually in pixels).
 *
 * @return A `Point` structure containing the tile's row (`x`) and column (`y`) corresponding to the given world
 *         position.
 */
_Check_return_ Point MapPositionToTile(
    _In_ const Tilemap* pTilemap,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

_Check_return_ Point MapPositionToTileV(
    _In_ const Tilemap* pTilemap,
    _In_ Vector2 position
    );

/**
 * @brief Destroys a tilemap and frees its resources.
 *
 * This function deallocates the memory and resources associated with the specified `Tilemap`, effectively destroying
 * it. Any tiles, textures, or other resources associated with the tilemap will also be cleaned up. After calling
 * this function, the `Tilemap` pointer is no longer valid.
 *
 * @param pTilemap Pointer to the `Tilemap` to be destroyed. After the function call, the pointer will be invalid.
 *
 * @return `true` if the tilemap was successfully destroyed, or `false` if an error occurred.
 *
 * @note The caller should ensure that the `Tilemap` is no longer used after it has been destroyed.
 */
_Check_return_opt_ bool Tilemap_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Tilemap* pTilemap
    );

#endif //TILEMAP_H
