//
// Created by Simon on 21.04.2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "vector2.h"

typedef struct _Camera {
    FLOAT x;
    FLOAT y;
    FLOAT fWidth;
    FLOAT fHeight;
    FLOAT fRotation;
    FLOAT fZoom;
    FLOAT pfViewMatrix[3][3];
} Camera;

_Check_return_
Camera CreateCamera(
    _In_ FLOAT x,
    _In_ FLOAT y,
    _In_ FLOAT fWidth,
    _In_ FLOAT fHeight,
    _In_ FLOAT fRotation,
    _In_ FLOAT fZoom
    );

void SetCameraZoom(
    _Inout_ Camera* pCamera,
    _In_    FLOAT fZoom
    );

void SetCameraRotation(
    _Inout_ Camera* pCamera,
    _In_    FLOAT fRotation
    );

void SetCameraPosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT x,
    _In_    FLOAT y
    );

void SetCameraPositionV(
    _Inout_ Camera* pCamera,
    _In_    Vector2 target
    );

void MoveCameraPosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT dx,
    _In_    FLOAT dy
    );

void UseCamera(
    _In_ Camera* pCamera
    );

_Check_return_
Vector2 WorldToScreen(
    _In_ FLOAT x,
    _In_ FLOAT y
    );

_Check_return_
Vector2 WorldToScreenV(
    _In_ Vector2 world
    );

_Check_return_
FLOAT GetCameraZoom(
    void
    );

_Check_return_
FLOAT GetCameraX(
    void
    );

_Check_return_
FLOAT GetCameraY(
    void
    );

_Check_return_
const Camera* GetCurrentCamera(
    void
    );

#endif //CAMERA_H
