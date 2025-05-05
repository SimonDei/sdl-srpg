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

/**
 * @brief Creates a new tilemap manager.
 *
 * This function creates and initializes a new `TilemapManager` that can be used to manage multiple tilemaps in the game.
 * The tilemap manager is responsible for handling tilemap loading, storage, and manipulation.
 *
 * @return A pointer to the newly created `TilemapManager`, or `NULL` if the creation failed.
 */
_Check_return_ _Ret_maybenull_ TilemapManager* TilemapManager_Create(
    void
    );

/**
 * @brief Adds a new tilemap to the tilemap manager.
 *
 * This function creates and adds a new `Tilemap` to the specified `TilemapManager`. The tilemap is initialized
 * with the specified name, tile width, and tile height, and is ready to be used for rendering and manipulation.
 *
 * @param pManager    Pointer to the `TilemapManager` to which the new tilemap will be added.
 * @param pszName     The name of the tilemap, which can be used to identify and reference the tilemap.
 * @param fTileWidth  The width (in pixels) of each tile in the tilemap.
 * @param fTileHeight The height (in pixels) of each tile in the tilemap.
 *
 * @return A pointer to the newly added `Tilemap`, or `NULL` if the operation failed.
 */
_Check_return_ _Ret_maybenull_ Tilemap* TilemapManager_AddTilemap(
    _Inout_ TilemapManager* pManager,
    _In_z_  PCSTR pszName,
    _In_    FLOAT fTileWidth,
    _In_    FLOAT fTileHeight
    );

/**
 * @brief Destroys a tilemap manager and frees its resources.
 *
 * This function deallocates the memory and resources associated with the specified `TilemapManager`. It cleans up
 * all tilemaps managed by the `TilemapManager`, and the manager itself will no longer be valid after the call.
 *
 * @param pManager Pointer to the `TilemapManager` to be destroyed. After the function call, the pointer will be invalid.
 *
 * @return `RESULT_SUCCESS` if the destruction was successful, or an error code if the operation failed.
 *
 * @note The caller should ensure that the `TilemapManager` is no longer used after it has been destroyed.
 */
_Check_return_opt_ Result TilemapManager_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ TilemapManager* pManager
    );

#endif //TILEMAP_MANAGER_H
