//
// Created by Simon on 21.04.2025.
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "utils.h"

typedef struct _Texture Texture;

typedef struct _TextureEntry {
    Texture* pTexture;
    PCSTR pszName;
} TextureEntry;

typedef struct _TextureManager {
    TextureEntry* arrTextureEntries;
    INT nCount;
    INT nCapacity;
} TextureManager;

/**
 * @brief Creates a new texture manager.
 *
 * This function allocates and initializes a new texture manager, which can be used to
 * manage and handle multiple textures within the application.
 *
 * @return A pointer to the newly created `TextureManager` object, or `NULL` if the creation failed.
 */
_Ret_maybenull_ TextureManager* CreateTextureManager(
    void
    );

/**
 * @brief Loads a texture into the texture manager.
 *
 * This function loads a texture from a file and adds it to the specified texture manager.
 * The texture can later be retrieved and applied to sprites or other objects.
 *
 * @param pManager Pointer to the `TextureManager` where the texture will be loaded.
 * @param pszName  The name to associate with the loaded texture.
 * @param pszFilename Path to the texture file to be loaded.
 * @return `true` if the texture was successfully loaded, `false` otherwise (e.g., if the file could not be loaded).
 */
_Check_return_opt_ bool LoadTexture(
    _In_   TextureManager* pManager,
    _In_z_ PCSTR pszName,
    _In_z_ PCSTR pszFilename
    );

/**
 * @brief Retrieves a texture by its name from the texture manager.
 *
 * This function looks up a texture by its associated name and returns a pointer to the
 * texture if it is found. The texture can then be used for rendering or other operations.
 *
 * @param pManager Pointer to the `TextureManager` from which the texture will be retrieved.
 * @param pszName  The name associated with the texture to retrieve.
 * @return A pointer to the `Texture` if found, or `NULL` if no texture is associated with the given name.
 */
_Check_return_ Texture* GetTexture(
    _In_   const TextureManager* pManager,
    _In_z_ PCSTR pszName
    );

/**
 * @brief Destroys the texture manager and frees its resources.
 *
 * This function deallocates all textures managed by the specified texture manager and
 * invalidates the texture manager pointer. After calling this function, the texture manager
 * pointer should not be used.
 *
 * @param pManager Pointer to the `TextureManager` to be destroyed. After the function call, the manager is no longer valid.
 * @return `true` if the texture manager was successfully destroyed and all resources freed, `false` otherwise.
 */
_Check_return_opt_ bool DestroyTextureManager(
    _Inout_ _Pre_valid_ _Post_invalid_ TextureManager* pManager
    );

#endif //TEXTURE_MANAGER_H
