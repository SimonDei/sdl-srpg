//
// Created by Simon on 21.04.2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct _Window {
    SDL_Window* pDisplay;
    SDL_Renderer* pRenderer;
    bool bRunning;
    UINT uWidth;
    UINT uHeight;
    PCSTR pszTitle;
} Window;

/**
 * Creates and initializes a new Window with the specified position, size, and title.
 *
 * @param x        The horizontal position of the window.
 * @param y        The vertical position of the window.
 * @param uWidth   The width of the window in pixels.
 * @param uHeight  The height of the window in pixels.
 * @param pszTitle A null-terminated string representing the window title.
 *
 * @returns A pointer to the newly created Window, or NULL on failure.
 */
_Ret_maybenull_ Window* CreateWindow(
    _In_   INT x,
    _In_   INT y,
    _In_   UINT uWidth,
    _In_   UINT uHeight,
    _In_z_ PCSTR pszTitle
    );

_Check_return_ bool IsWindowOpen(
    _In_ Window* pWindow
    );

/**
 * Retrieves the time elapsed during the last frame.
 *
 * @returns The duration of the last frame in seconds as a floating-point value.
 */
_Check_return_ FLOAT GetFrameTime(
    void
    );

_Check_return_ bool IsKeyDown(
    _In_ INT iKey
    );

_Check_return_ bool IsKeyUp(
    _In_ INT iKey
    );

_Check_return_ bool LeftMousePressed(
    void
    );

_Check_return_ bool RightMousePressed(
    void
    );

void ClearWindow(
    _In_ BYTE byRed,
    _In_ BYTE byGreen,
    _In_ BYTE byBlue
    );

void DisplayWindow(
    void
    );

_Check_return_ INT GetWindowWidth(
    void
    );

_Check_return_ INT GetWindowHeight(
    void
    );

_Check_return_ FLOAT GetMouseX(
    void
    );

_Check_return_ FLOAT GetMouseY(
    void
    );

_Check_return_ SDL_Renderer* GetWindowRenderer(
    void
    );

/**
 * Destroys the specified window and frees any associated resources.
 *
 * @param pWindow Pointer to the Window to be destroyed.
 *
 * @returns true if the window was successfully destroyed; otherwise, false.
 */
_Check_return_opt_ bool DestroyWindow(
    _Inout_ _Pre_valid_ _Post_invalid_ Window* pWindow
    );

#endif //WINDOW_H
