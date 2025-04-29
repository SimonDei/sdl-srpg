//
// Created by Simon on 21.04.2025.
//

#include "window.h"

#include <stdio.h>
#include <SDL3/SDL.h>

static bool bInitialized = false;
static INT s_iWindowWidth;
static INT s_iWindowHeight;
static SDL_Window* s_pWindow;
static SDL_Renderer* s_pRenderer;
static SDL_Event lastEvent;
static const bool* s_pKeyboardState;
static SDL_MouseButtonFlags s_mouseState;
static FLOAT s_fMouseX;
static FLOAT s_fMouseY;
static UINT64 u64LastTime = 0;
static UINT64 u64CurrentTime = 0;
static UINT64 u64DeltaTime = 0;

static void InitializeSDL(
    void
) {
    SDL_Init(SDL_INIT_VIDEO);
}

_Ret_maybenull_
Window* CreateWindow(
    _In_   const INT x,
    _In_   const INT y,
    _In_   const UINT uWidth,
    _In_   const UINT uHeight,
    _In_z_ PCSTR pszTitle
) {
    Window* pWindow = malloc(sizeof(Window));
    if (!pWindow) {
        SDL_Log("Failed to allocate memory for window\n");
        return NULL;
    }

    pWindow->pszTitle = pszTitle;
    pWindow->uWidth = uWidth;
    pWindow->uHeight = uHeight;

    if (!bInitialized) {
        InitializeSDL();
        bInitialized = true;
    }

    if (uWidth > INT32_MAX || uHeight > INT32_MAX) {
        SDL_Log("Width or height exceeds maximum value\n");
        SafeFree(pWindow);
        return NULL;
    }

    pWindow->pDisplay = SDL_CreateWindow(pszTitle, (int)uWidth, (int)uHeight, SDL_WINDOW_HIDDEN);
    if (!pWindow->pDisplay) {
        SDL_Log("Failed to create display\n");
        SafeFree(pWindow);
        return NULL;
    }

    SDL_SetWindowPosition(pWindow->pDisplay, x, y);
    SDL_ShowWindow(pWindow->pDisplay);

    pWindow->pRenderer = SDL_CreateRenderer(pWindow->pDisplay, NULL);
    if (!pWindow->pRenderer) {
        SDL_DestroyWindow(pWindow->pDisplay);
        SDL_Log("Failed to create renderer\n");
        SafeFree(pWindow);
        return NULL;
    }

    s_pWindow = pWindow->pDisplay;
    s_pRenderer = pWindow->pRenderer;
    s_iWindowWidth = (int)uWidth;
    s_iWindowHeight = (int)uHeight;
    pWindow->bRunning = true;
    u64LastTime = SDL_GetTicks();

    return pWindow;
}

_Check_return_
bool IsWindowOpen(
    _In_ Window* pWindow
) {
    while (SDL_PollEvent(&lastEvent)) {
        switch (lastEvent.type) {
            case SDL_EVENT_QUIT:
                pWindow->bRunning = false;
                break;
        }
    }
    s_pKeyboardState = SDL_GetKeyboardState(NULL);
    s_mouseState = SDL_GetMouseState(&s_fMouseX, &s_fMouseY);

    u64CurrentTime = SDL_GetTicks();
    u64DeltaTime = u64CurrentTime - u64LastTime;
    u64LastTime = u64CurrentTime;

    return pWindow->bRunning;
}

_Check_return_
FLOAT GetFrameTime(
    void
) {
    return (float)u64DeltaTime / 1000.0f;
}

_Check_return_
bool IsKeyDown(
    _In_ const INT iKey
) {
    return s_pKeyboardState[iKey];
}

_Check_return_
bool IsKeyUp(
    _In_ const INT iKey
) {
    return !s_pKeyboardState[iKey];
}

_Check_return_
bool LeftMousePressed(
    void
) {
    return s_mouseState & SDL_BUTTON_LMASK;
}

_Check_return_
bool RightMousePressed(
    void
) {
    return s_mouseState & SDL_BUTTON_RMASK;
}

void ClearWindow(
    _In_ const BYTE byRed,
    _In_ const BYTE byGreen,
    _In_ const BYTE byBlue
) {
    SDL_SetRenderDrawColor(s_pRenderer, byRed, byGreen, byBlue, 255);
    SDL_RenderClear(s_pRenderer);
}

void DisplayWindow(
    void
) {
    SDL_RenderPresent(s_pRenderer);
}

_Check_return_
INT GetWindowWidth(
    void
) {
    return s_iWindowWidth;
}

_Check_return_
INT GetWindowHeight(
    void
) {
    return s_iWindowHeight;
}

_Check_return_
FLOAT GetMouseX(
    void
) {
    return s_fMouseX;
}

_Check_return_
FLOAT GetMouseY(
    void
) {
    return s_fMouseY;
}

_Check_return_
SDL_Renderer* GetWindowRenderer(
    void
) {
    return s_pRenderer;
}

_Check_return_opt_
bool DestroyWindow(
    _Inout_ _Pre_valid_ _Post_invalid_ Window* pWindow
) {
    if (!pWindow || !pWindow->pDisplay) {
        return false;
    }

    SDL_DestroyRenderer(pWindow->pRenderer);
    SDL_DestroyWindow(pWindow->pDisplay);
    SafeFree(pWindow);

    SDL_Quit();
    return true;
}
