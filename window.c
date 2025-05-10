//
// Created by Simon on 21.04.2025.
//

#include "window.h"

#include <stdio.h>
#include <SFML/Graphics.h>

static INT s_iWindowWidth;
static INT s_iWindowHeight;
static sfRenderWindow* s_pWindow;
static sfEvent lastEvent;
static FLOAT s_fMouseX;
static FLOAT s_fMouseY;
static sfTime s_deltaTime;
static sfClock* s_pDeltaClock;
static sfClock* s_pClock;

_Check_return_ _Ret_maybenull_
Window* Window_Create(
    _In_   const INT x,
    _In_   const INT y,
    _In_   const UINT uWidth,
    _In_   const UINT uHeight,
    _In_z_ PCSTR pszTitle
) {
    Window* pWindow = malloc(sizeof(Window));
    if (!pWindow) {
        printf("Failed to allocate memory for window\n");
        return NULL;
    }

    pWindow->pszTitle = pszTitle;
    pWindow->uWidth = uWidth;
    pWindow->uHeight = uHeight;

    if (uWidth > INT32_MAX || uHeight > INT32_MAX) {
        printf("Width or height exceeds maximum value\n");
        SafeFree(pWindow);
        return NULL;
    }

    pWindow->pDisplay = sfRenderWindow_create((sfVideoMode) { uWidth, uHeight, 32 }, pszTitle, sfResize | sfClose, NULL);
    if (!pWindow->pDisplay) {
        printf("Failed to create display\n");
        SafeFree(pWindow);
        return NULL;
    }

    sfRenderWindow_setPosition(pWindow->pDisplay, (sfVector2i) { x, y });

    s_pWindow = pWindow->pDisplay;
    s_iWindowWidth = (int)uWidth;
    s_iWindowHeight = (int)uHeight;
    
    s_pDeltaClock = sfClock_create();
    if (!s_pDeltaClock) {
        printf("Failed to create delta clock\n");
        sfRenderWindow_destroy(pWindow->pDisplay);
        SafeFree(pWindow);
        return NULL;
    }

    s_pClock = sfClock_create();
    if (!s_pClock) {
        printf("Failed to create clock\n");
        sfClock_destroy(s_pDeltaClock);
        sfRenderWindow_destroy(pWindow->pDisplay);
        SafeFree(pWindow);
        return NULL;
    }

    sfClock_restart(s_pClock);
    sfClock_restart(s_pDeltaClock);

    return pWindow;
}

_Check_return_
bool Window_IsOpen(
    _In_ const Window* pWindow
) {
    while (sfRenderWindow_pollEvent(s_pWindow, &lastEvent)) {
        switch (lastEvent.type) {
            case sfEvtClosed:
                sfRenderWindow_close(pWindow->pDisplay);
                break;
        }
    }

    s_deltaTime = sfClock_restart(s_pDeltaClock);

    return sfRenderWindow_isOpen(pWindow->pDisplay);
}

_Check_return_
INT GetTime(
    void
) {
    return sfTime_asMilliseconds(sfClock_getElapsedTime(s_pClock));
}

_Check_return_
INT64 GetFrameTime(
    void
) {
    return sfTime_asMilliseconds(s_deltaTime);
}

_Check_return_
bool IsKeyDown(
    _In_ const INT iKey
) {
    return sfKeyboard_isKeyPressed(iKey);
}

_Check_return_
bool IsKeyUp(
    _In_ const INT iKey
) {
    return !sfKeyboard_isKeyPressed(iKey);
}

_Check_return_
bool LeftMousePressed(
    void
) {
    return sfMouse_isButtonPressed(sfMouseLeft);
}

_Check_return_
bool RightMousePressed(
    void
) {
    return sfMouse_isButtonPressed(sfMouseRight);
}

void Window_Clear(
    _In_ const BYTE byRed,
    _In_ const BYTE byGreen,
    _In_ const BYTE byBlue
) {
    sfRenderWindow_clear(s_pWindow, (sfColor) { 0, 0, 0, 255 });
}

void Window_Display(
    void
) {
    sfRenderWindow_display(s_pWindow);
}

_Check_return_
INT Window_GetWidth(
    void
) {
    return s_iWindowWidth;
}

_Check_return_
INT Window_GetHeight(
    void
) {
    return s_iWindowHeight;
}

_Check_return_
sfRenderWindow* Window_GetRenderWindow(
    void
) {
    return s_pWindow;
}

_Check_return_
INT GetMouseX(
    void
) {
    return sfMouse_getPositionRenderWindow(s_pWindow).x;
}

_Check_return_
INT GetMouseY(
    void
) {
    return sfMouse_getPositionRenderWindow(s_pWindow).y;
}

_Check_return_opt_
bool Window_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ Window* pWindow
) {
    if (!pWindow || !pWindow->pDisplay) {
        return false;
    }

    sfRenderWindow_destroy(pWindow->pDisplay);
    sfClock_destroy(s_pClock);
    sfClock_destroy(s_pDeltaClock);
    SafeFree(pWindow);

    return true;
}
