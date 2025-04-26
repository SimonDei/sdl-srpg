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
    float cos_r = cosf(pCamera->fRotation);
    float sin_r = sinf(pCamera->fRotation);

    float sx = pCamera->fZoom;
    float sy = pCamera->fZoom;

    float tx = -pCamera->x;
    float ty = -pCamera->y;

    float cx = (float)GetWindowWidth() / 2.0f;
    float cy = (float)GetWindowHeight() / 2.0f;

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
Camera CreateCamera(
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

void SetCameraZoom(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fZoom
) {
    pCamera->fZoom = fZoom;
    RecalculateViewMatrix(pCamera);
}

void SetCameraRotation(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fRotation
) {
    pCamera->fRotation = fRotation;
    RecalculateViewMatrix(pCamera);
}

void SetCameraPosition(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pCamera->x = x;
    pCamera->y = y;
    RecalculateViewMatrix(pCamera);
}

void SetCameraPositionV(
    _Inout_ Camera* pCamera,
    _In_    const Vector2 target
) {
    pCamera->x = target.x;
    pCamera->y = target.y;
    RecalculateViewMatrix(pCamera);
}

void MoveCameraPosition(
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

void UseCamera(
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
FLOAT GetCameraZoom(
    void
) {
    return s_pCurrentCamera->fZoom;
}

_Check_return_
FLOAT GetCameraX(
    void
) {
    return s_pCurrentCamera->x;
}

_Check_return_
FLOAT GetCameraY(
    void
) {
    return s_pCurrentCamera->y;
}

_Check_return_
const Camera* GetCurrentCamera(
    void
) {
    return s_pCurrentCamera;
}
