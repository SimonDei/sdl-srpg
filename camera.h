//
// Created by Simon on 21.04.2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "point.h"
#include "vector2.h"

typedef struct sfView sfView;

typedef struct _Camera {
    FLOAT x;
    FLOAT y;
    FLOAT fWidth;
    FLOAT fHeight;
    FLOAT fRotation;
    FLOAT fZoom;
    sfView* pView;
} Camera;

/**
 * @brief Creates a camera with the specified properties.
 *
 * This function initializes a `Camera` struct with the specified position, size, rotation, and zoom level.
 * The camera can be used for viewing and rendering parts of the scene with specific transformations.
 *
 * @param x        X coordinate for the camera's position.
 * @param y        Y coordinate for the camera's position.
 * @param fWidth   Width of the camera's viewing area.
 * @param fHeight  Height of the camera's viewing area.
 * @param fRotation Rotation angle (in radians) for the camera.
 * @param fZoom    Zoom factor for the camera (1.0 for no zoom, greater than 1.0 for zoom-in, less than 1.0 for zoom-out).
 * @return A `Camera` struct initialized with the provided properties.
 */
_Check_return_ _Ret_maybenull_ Camera* Camera_Create(
    _In_ FLOAT x,
    _In_ FLOAT y,
    _In_ FLOAT fWidth,
    _In_ FLOAT fHeight,
    _In_ FLOAT fRotation
    );

/**
 * @brief Sets the zoom level of the camera.
 *
 * This function updates the zoom factor for the specified camera. A zoom factor of 1.0 represents
 * no zoom, values greater than 1.0 zoom in, and values less than 1.0 zoom out.
 *
 * @param pCamera Pointer to the `Camera` whose zoom level will be updated.
 * @param fZoom   New zoom level for the camera. A value of 1.0 means no zoom, with higher values
 *                indicating zooming in, and lower values indicating zooming out.
 */
void Camera_SetZoom(
    _Inout_ Camera* pCamera,
    _In_    FLOAT fZoom
    );

/**
 * @brief Sets the rotation of the camera.
 *
 * This function updates the rotation angle for the specified camera. The rotation is applied in radians,
 * where a value of 0.0 represents no rotation. Positive values rotate the camera counterclockwise,
 * while negative values rotate it clockwise.
 *
 * @param pCamera Pointer to the `Camera` whose rotation will be updated.
 * @param fRotation New rotation angle for the camera in radians. A value of 0.0 means no rotation.
 */
void Camera_SetRotation(
    _Inout_ Camera* pCamera,
    _In_    FLOAT fRotation
    );

/**
 * @brief Sets the position of the camera.
 *
 * This function updates the position of the specified camera. The camera's position is defined by
 * the X and Y coordinates, determining where the camera is placed in the scene.
 *
 * @param pCamera Pointer to the `Camera` whose position will be updated.
 * @param x       New X coordinate for the camera's position.
 * @param y       New Y coordinate for the camera's position.
 */
void Camera_SetPosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT x,
    _In_    FLOAT y
    );

/**
 * @brief Sets the position of the camera using a `Vector2` object.
 *
 * This function updates the position of the specified camera using a `Vector2` struct, which contains
 * the X and Y coordinates that define the camera's position in the scene.
 *
 * @param pCamera Pointer to the `Camera` whose position will be updated.
 * @param target  A `Vector2` struct containing the new X and Y coordinates for the camera's position.
 */
void Camera_SetPositionV(
    _Inout_ Camera* pCamera,
    _In_    VECTOR2 target
    );

/**
 * @brief Moves the camera's position by a specified offset.
 *
 * This function updates the position of the specified camera by adding the given offsets to its
 * current position. The offsets are applied to the camera's X and Y coordinates, effectively moving
 * the camera by the specified amount in both directions.
 *
 * @param pCamera Pointer to the `Camera` whose position will be updated.
 * @param dx The amount to move the camera along the X-axis.
 * @param dy The amount to move the camera along the Y-axis.
 */
void Camera_MovePosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT dx,
    _In_    FLOAT dy
    );

/**
 * @brief Activates the specified camera for rendering.
 *
 * This function applies the transformations (position, rotation, zoom, etc.) of the specified camera
 * to the rendering context. Once this function is called, subsequent rendering operations will be affected
 * by the camera's properties, such as its position and zoom level.
 *
 * @param pCamera Pointer to the `Camera` to be used for rendering.
 */
void Camera_Use(
    _In_opt_ Camera* pCamera
    );

/**
 * @brief Converts world coordinates to screen coordinates.
 *
 * This function takes world coordinates (X, Y) and converts them to screen coordinates,
 * taking into account the current camera's position, rotation, and zoom.
 * This is useful for translating world space positions to screen space for rendering.
 *
 * @param x The X coordinate in world space.
 * @param y The Y coordinate in world space.
 * @return A `Vector2` struct containing the corresponding X and Y coordinates in screen space.
 */
_Check_return_ VECTOR2 WorldToScreen(
    _In_ FLOAT x,
    _In_ FLOAT y
    );

/**
 * @brief Converts world coordinates to screen coordinates using a `Vector2` struct.
 *
 * This function takes a `Vector2` representing world coordinates (X, Y) and converts it to screen coordinates,
 * considering the current camera's position, rotation, and zoom. This is useful for translating world space positions
 * to screen space for rendering.
 *
 * @param world A `Vector2` struct representing the X and Y coordinates in world space.
 * @return A `Vector2` struct containing the corresponding X and Y coordinates in screen space.
 */
_Check_return_ VECTOR2 WorldToScreenV(
    _In_ VECTOR2 world
    );

/**
 * @brief Converts screen coordinates to world coordinates.
 *
 * This function takes screen coordinates (X, Y) and converts them to world coordinates,
 * taking into account the current camera's position, rotation, and zoom.
 * This is useful for translating screen space positions (e.g., mouse click locations) to world space.
 *
 * @param x The X coordinate in screen space.
 * @param y The Y coordinate in screen space.
 * @return A `Vector2` struct containing the corresponding X and Y coordinates in world space.
 */
_Check_return_ VECTOR2 ScreenToWorld(
    _In_ INT x,
    _In_ INT y
    );

/**
 * @brief Converts screen coordinates to world coordinates using a `Vector2` struct.
 *
 * This function takes a `Vector2` representing screen coordinates (X, Y) and converts it to world coordinates,
 * considering the current camera's position, rotation, and zoom. This is useful for translating screen space positions
 * (e.g., mouse click locations) to world space.
 *
 * @param screen A `Vector2` struct representing the X and Y coordinates in screen space.
 * @return A `Vector2` struct containing the corresponding X and Y coordinates in world space.
 */
_Check_return_ VECTOR2 ScreenToWorldV(
    _In_ POINT screen
    );

/**
 * @brief Gets the current zoom level of the camera.
 *
 * This function retrieves the current zoom factor of the active camera. A zoom factor of 1.0 represents
 * no zoom, values greater than 1.0 indicate zooming in, and values less than 1.0 indicate zooming out.
 *
 * @return The current zoom level of the camera.
 */
_Check_return_ FLOAT Camera_GetZoom(
    void
    );

/**
 * @brief Gets the current X position of the camera.
 *
 * This function retrieves the current X coordinate of the camera's position in the world space.
 * It reflects the camera's horizontal position, which can be adjusted by panning or moving the camera.
 *
 * @return The current X position of the camera.
 */
_Check_return_ FLOAT Camera_GetX(
    void
    );

/**
 * @brief Gets the current Y position of the camera.
 *
 * This function retrieves the current Y coordinate of the camera's position in the world space.
 * It reflects the camera's vertical position, which can be adjusted by panning or moving the camera.
 *
 * @return The current Y position of the camera.
 */
_Check_return_ FLOAT Camera_GetY(
    void
    );

/**
 * @brief Retrieves the currently active camera.
 *
 * This function returns a pointer to the camera that is currently being used for rendering or transformations.
 * The returned camera can be used to retrieve its properties such as position, rotation, zoom, etc.
 *
 * @return A pointer to the currently active `Camera`, or `NULL` if no camera is currently active.
 */
_Check_return_ const Camera* Camera_GetCurrent(
    void
    );

_Check_return_opt_ bool Camera_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Camera* pCamera
    );

#endif //CAMERA_H
