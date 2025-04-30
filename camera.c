//
// Created by Simon on 21.04.2025.
//

#include "camera.h"

#include <math.h>
#include <string.h>

#include "window.h"

static Camera* s_pCurrentCamera;

static void RecalculateViewMatrix(
    _Inout_ Camera* pCamera
) {
    const float cos_r = cosf(pCamera->fRotation);
    const float sin_r = sinf(pCamera->fRotation);

    const float sx = pCamera->fZoom;
    const float sy = pCamera->fZoom;

    const float tx = -pCamera->x;
    const float ty = -pCamera->y;

    const float cx = (float)Window_GetWidth() / 2.0f;
    const float cy = (float)Window_GetHeight() / 2.0f;

    pCamera->pfViewMatrix[0][0] = cos_r * sx;
    pCamera->pfViewMatrix[0][1] = -sin_r * sy;
    pCamera->pfViewMatrix[0][2] = 0;

    pCamera->pfViewMatrix[1][0] = sin_r * sx;
    pCamera->pfViewMatrix[1][1] = cos_r * sy;
    pCamera->pfViewMatrix[1][2] = 0;

    pCamera->pfViewMatrix[2][0] = cos_r * sx * tx + -sin_r * sy * ty + cx;
    pCamera->pfViewMatrix[2][1] = sin_r * sx * tx + cos_r * sy * ty + cy;
    pCamera->pfViewMatrix[2][2] = 1;
}

_Check_return_
Camera Camera_Create(
    _In_ const FLOAT x,
    _In_ const FLOAT y,
    _In_ const FLOAT fWidth,
    _In_ const FLOAT fHeight,
    _In_ const FLOAT fRotation,
    _In_ const FLOAT fZoom
) {
    Camera camera = { 0 };

    camera.x = x;
    camera.y = y;
    camera.fWidth = fWidth;
    camera.fHeight = fHeight;
    camera.fRotation = fRotation;
    camera.fZoom = fZoom;

    RecalculateViewMatrix(&camera);

    return camera;
}

void Camera_SetZoom(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fZoom
) {
    pCamera->fZoom = fZoom;
    RecalculateViewMatrix(pCamera);
}

void Camera_SetRotation(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fRotation
) {
    pCamera->fRotation = fRotation;
    RecalculateViewMatrix(pCamera);
}

void Camera_SetPosition(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pCamera->x = x;
    pCamera->y = y;
    RecalculateViewMatrix(pCamera);
}

void Camera_SetPositionV(
    _Inout_ Camera* pCamera,
    _In_    const Vector2 target
) {
    pCamera->x = target.x;
    pCamera->y = target.y;
    RecalculateViewMatrix(pCamera);
}

void Camera_MovePosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT dx,
    _In_    FLOAT dy
) {
    if (dx != 0 && dy != 0) {
        const float fScale = 1.0f / sqrtf(2.0f);
        dx *= fScale;
        dy *= fScale;
    }

    pCamera->x += dx;
    pCamera->y += dy;
    RecalculateViewMatrix(pCamera);
}

void Camera_Use(
    _In_ Camera* pCamera
) {
    s_pCurrentCamera = pCamera;
}

_Check_return_
Vector2 WorldToScreen(
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    Vector2 screen = { 0 };

    screen.x = x * s_pCurrentCamera->pfViewMatrix[0][0] + y * s_pCurrentCamera->pfViewMatrix[1][0] + s_pCurrentCamera->pfViewMatrix[2][0];
    screen.y = x * s_pCurrentCamera->pfViewMatrix[0][1] + y * s_pCurrentCamera->pfViewMatrix[1][1] + s_pCurrentCamera->pfViewMatrix[2][1];

    return screen;
}

_Check_return_
Vector2 WorldToScreenV(
    _In_ const Vector2 world
) {
    Vector2 screen = { 0 };
    
    screen.x = world.x * s_pCurrentCamera->pfViewMatrix[0][0] + world.y * s_pCurrentCamera->pfViewMatrix[1][0] + s_pCurrentCamera->pfViewMatrix[2][0];
    screen.y = world.x * s_pCurrentCamera->pfViewMatrix[0][1] + world.y * s_pCurrentCamera->pfViewMatrix[1][1] + s_pCurrentCamera->pfViewMatrix[2][1];

    return screen;
}

_Check_return_
Vector2 ScreenToWorld(
    _In_ FLOAT x,
    _In_ FLOAT y
) {
    Vector2 world = { 0 };

    x -= s_pCurrentCamera->pfViewMatrix[2][0];
    y -= s_pCurrentCamera->pfViewMatrix[2][1];

    const float cos_r = cosf(-s_pCurrentCamera->fRotation);
    const float sin_r = sinf(-s_pCurrentCamera->fRotation);
    const float invZoom = 1.0f / s_pCurrentCamera->fZoom;

    world.x = (x * cos_r - y * sin_r) * invZoom;
    world.y = (x * sin_r + y * cos_r) * invZoom;

    return world;
}

_Check_return_
Vector2 ScreenToWorldV(
    _In_ Vector2 screen
) {
    Vector2 world = { 0 };

    screen.x -= s_pCurrentCamera->pfViewMatrix[2][0];
    screen.y -= s_pCurrentCamera->pfViewMatrix[2][1];

    const float cos_r = cosf(-s_pCurrentCamera->fRotation);
    const float sin_r = sinf(-s_pCurrentCamera->fRotation);
    const float invZoom = 1.0f / s_pCurrentCamera->fZoom;

    world.x = (screen.x * cos_r - screen.y * sin_r) * invZoom;
    world.y = (screen.x * sin_r + screen.y * cos_r) * invZoom;

    return world;
}

_Check_return_
FLOAT Camera_GetZoom(
    void
) {
    return s_pCurrentCamera->fZoom;
}

_Check_return_
FLOAT Camera_GetX(
    void
) {
    return s_pCurrentCamera->x;
}

_Check_return_
FLOAT Camera_GetY(
    void
) {
    return s_pCurrentCamera->y;
}

_Check_return_
const Camera* Camera_GetCurrent(
    void
) {
    return s_pCurrentCamera;
}
