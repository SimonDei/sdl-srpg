//
// Created by Simon on 21.04.2025.
//

#include "camera.h"

#include <math.h>
#include <string.h>
#include <SFML/Graphics.h>

#include "window.h"

static Camera* s_pCurrentCamera;

_Check_return_ _Ret_maybenull_
Camera* Camera_Create(
    _In_ const FLOAT x,
    _In_ const FLOAT y,
    _In_ const FLOAT fWidth,
    _In_ const FLOAT fHeight,
    _In_ const FLOAT fRotation
) {
    Camera* pCamera = malloc(sizeof(Camera));
    if (!pCamera) {
        printf("Failed to allocate memory for Camera\n");
        return NULL;
    }

    pCamera->x = x;
    pCamera->y = y;
    pCamera->fWidth = fWidth;
    pCamera->fHeight = fHeight;
    pCamera->fRotation = fRotation;
    pCamera->fZoom = 1.0f;
    pCamera->pView = sfView_create();

    sfView_setCenter(pCamera->pView, (sfVector2f) { x + fWidth / 2.0f, y + fHeight / 2.0f });
    sfView_setRotation(pCamera->pView, fRotation);
    sfView_setSize(pCamera->pView, (sfVector2f) { fWidth, fHeight });

    return pCamera;
}

void Camera_SetZoom(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fZoom
) {
    pCamera->fZoom = fZoom;

}

void Camera_SetRotation(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT fRotation
) {
    pCamera->fRotation = fRotation;
    sfView_setRotation(pCamera->pView, fRotation);
    sfRenderWindow_setView(Window_GetRenderWindow(), pCamera->pView);
}

void Camera_SetPosition(
    _Inout_ Camera* pCamera,
    _In_    const FLOAT x,
    _In_    const FLOAT y
) {
    pCamera->x = x;
    pCamera->y = y;
    sfView_setCenter(pCamera->pView, (sfVector2f) { x, y });
    sfRenderWindow_setView(Window_GetRenderWindow(), pCamera->pView);
}

void Camera_SetPositionV(
    _Inout_ Camera* pCamera,
    _In_    const VECTOR2 target
) {
    pCamera->x = target.x;
    pCamera->y = target.y;
    sfView_setCenter(pCamera->pView, (sfVector2f) { target.x, target.y });
    sfRenderWindow_setView(Window_GetRenderWindow(), pCamera->pView);
}

void Camera_MovePosition(
    _Inout_ Camera* pCamera,
    _In_    FLOAT dx,
    _In_    FLOAT dy
) {
    if (dx != 0.0f && dy != 0.0f) {
        const float fScale = 1.0f / sqrtf(2.0f);
        dx *= fScale;
        dy *= fScale;
    }

    pCamera->x += dx;
    pCamera->y += dy;
    sfView_move(pCamera->pView, (sfVector2f) { dx, dy });
    sfRenderWindow_setView(Window_GetRenderWindow(), pCamera->pView);
}

void Camera_Use(
    _In_opt_ Camera* pCamera
) {
    s_pCurrentCamera = pCamera;
    if (pCamera == NULL) {
        const sfView* pView = sfRenderWindow_getDefaultView(Window_GetRenderWindow());
        sfRenderWindow_setView(Window_GetRenderWindow(), pView);
        return;
    }
    sfRenderWindow_setView(Window_GetRenderWindow(), pCamera->pView);
}

_Check_return_
VECTOR2 WorldToScreen(
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    const sfVector2i screen = sfRenderWindow_mapCoordsToPixel(
        Window_GetRenderWindow(),
        (sfVector2f) { x, y },
        s_pCurrentCamera->pView
    );

    return (VECTOR2) { (FLOAT)screen.x, (FLOAT)screen.y };
}

_Check_return_
VECTOR2 WorldToScreenV(
    _In_ const VECTOR2 world
) {
    const sfVector2i screen = sfRenderWindow_mapCoordsToPixel(
        Window_GetRenderWindow(),
        (sfVector2f) { world.x, world.y },
        s_pCurrentCamera->pView
    );

    return (VECTOR2) { (FLOAT)screen.x, (FLOAT)screen.y };
}

_Check_return_
VECTOR2 ScreenToWorld(
    _In_ const INT x,
    _In_ const INT y
) {
    const sfVector2f world = sfRenderWindow_mapPixelToCoords(
        Window_GetRenderWindow(),
        (sfVector2i) { x, y },
        s_pCurrentCamera->pView
    );

    return (VECTOR2) { world.x, world.y };
}

_Check_return_
VECTOR2 ScreenToWorldV(
    _In_ const POINT screen
) {
    const sfVector2f world = sfRenderWindow_mapPixelToCoords(
        Window_GetRenderWindow(),
        (sfVector2i) { screen.x, screen.y },
        s_pCurrentCamera->pView
    );

    return (VECTOR2) { world.x, world.y };
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

_Check_return_opt_
bool Camera_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Camera* pCamera
) {
    if (pCamera == NULL) {
        return false;
    }

    sfView_destroy(pCamera->pView);

    SafeFree(pCamera);

    return true;
}
