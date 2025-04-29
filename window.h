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
 * @brief Creates a new window.
 *
 * This function creates and initializes a new window with the specified position, size, and title. The window
 * can be used to render graphical content, handle input events, and more. The window is created using the system's
 * native windowing system.
 *
 * @param x         The x-coordinate of the window's position on the screen (in pixels).
 * @param y         The y-coordinate of the window's position on the screen (in pixels).
 * @param uWidth    The width of the window (in pixels).
 * @param uHeight   The height of the window (in pixels).
 * @param pszTitle  The title of the window, which appears in the window's title bar.
 *
 * @return A pointer to the newly created `Window`, or `NULL` if the window creation failed.
 *
 * @note If the window creation fails, `NULL` will be returned. The caller should handle any potential errors
 *       (e.g., by checking the returned value before using the window).
 */
_Ret_maybenull_ Window* CreateWindow(
    _In_   INT x,
    _In_   INT y,
    _In_   UINT uWidth,
    _In_   UINT uHeight,
    _In_z_ PCSTR pszTitle
    );

/**
 * @brief Checks if the specified window is still open.
 *
 * This function checks whether the provided window is still open and has not been closed by the user or system.
 * It is typically used to determine if the application should continue running or if it should clean up and exit.
 *
 * @param pWindow Pointer to the `Window` to check for its open status.
 *
 * @return `true` if the window is still open, or `false` if the window has been closed.
 */
_Check_return_ bool IsWindowOpen(
    _In_ Window* pWindow
    );

/**
 * @brief Retrieves the time duration of the last frame.
 *
 * This function returns the time elapsed (in seconds) for the most recent frame rendered by the application.
 * This value can be used to synchronize animations, control frame rates, or perform time-based calculations.
 *
 * @return The time elapsed during the last frame, in seconds.
 *
 * @note The frame time is typically updated each time the application renders a frame, and the returned value
 *       may vary depending on the system's performance and rendering loop timing.
 */
_Check_return_ FLOAT GetFrameTime(
    void
    );

/**
 * @brief Checks if a specific key is currently being held down.
 *
 * This function returns `true` if the specified key is currently pressed (held down), and `false` otherwise.
 * It is typically used for continuous input detection, such as movement or held actions in games.
 *
 * @param iKey The key code to check.
 *
 * @return `true` if the specified key is currently down, `false` otherwise.
 */
_Check_return_ bool IsKeyDown(
    _In_ INT iKey
    );

/**
 * @brief Checks if a specific key is currently released (not held down).
 *
 * This function returns `true` if the given key is currently not pressed, and `false` if it is being held down.
 * It is useful for logic that should only run when a key is no longer active.
 *
 * @param iKey The key code to check, typically an SDL key code (e.g., `SDLK_w`, `SDLK_ESCAPE`).
 *
 * @return `true` if the key is up (not pressed), `false` if the key is currently down.
 */
_Check_return_ bool IsKeyUp(
    _In_ INT iKey
    );

/**
 * @brief Checks if the left mouse button is currently pressed.
 *
 * This function returns a boolean indicating whether the left mouse button is actively held down
 * at the time the function is called. It is commonly used for selecting, dragging, or initiating actions.
 *
 * @return `true` if the left mouse button is pressed, `false` otherwise.
 *
 * @note This reflects the real-time state of the button. To detect clicks (press and release),
 *       additional state tracking may be needed.
 */
_Check_return_ bool LeftMousePressed(
    void
    );

/**
 * @brief Checks if the right mouse button is currently pressed.
 *
 * This function returns a boolean indicating whether the right mouse button is being held down
 * at the time of the call. It is typically used for handling context-specific actions or alternate controls.
 *
 * @return `true` if the right mouse button is pressed, `false` otherwise.
 *
 * @note This function reflects the real-time state of the mouse. For edge detection (i.e., detecting
 *       when the button was just pressed), additional logic is usually required.
 */
_Check_return_ bool RightMousePressed(
    void
    );

/**
 * @brief Clears the window with a solid color.
 *
 * This function clears the entire window by filling it with a specified color, defined by the red, green, and
 * blue components. The color is applied as an RGBA value, with alpha implicitly set to 255 (fully opaque).
 * This is typically used at the beginning of each frame to reset the window before drawing new content.
 *
 * @param byRed   The red component of the color (0-255).
 * @param byGreen The green component of the color (0-255).
 * @param byBlue  The blue component of the color (0-255).
 *
 * @note This function clears the window to the specified color, potentially overwriting any existing content on the screen.
 */
void ClearWindow(
    _In_ BYTE byRed,
    _In_ BYTE byGreen,
    _In_ BYTE byBlue
    );

/**
 * @brief Displays the contents of the window.
 *
 * This function presents the current contents of the window to the screen. It is typically called at the end
 * of each frame to update the window with the rendered content. The contents displayed depend on the rendering
 * that occurred since the last call to `ClearWindow` or previous drawing operations.
 *
 * @note This function is usually part of a render loop and should be called after all drawing and rendering
 *       operations for the current frame have been completed.
 */
void DisplayWindow(
    void
    );

/**
 * @brief Retrieves the width of the application window in pixels.
 *
 * This function returns the current width of the window's drawable client area. It is typically
 * used for calculations related to layout, rendering, or mouse/input positioning.
 *
 * @return The width of the window in pixels.
 *
 * @note This value may change if the window is resizable and the user or application resizes it.
 */
_Check_return_ INT GetWindowWidth(
    void
    );

/**
 * @brief Retrieves the height of the application window in pixels.
 *
 * This function returns the current height of the window's drawable client area. It is typically
 * used for layout, rendering, or input calculations that depend on window dimensions.
 *
 * @return The height of the window in pixels.
 *
 * @note This value may change if the window is resized, depending on whether window resizing is enabled.
 */
_Check_return_ INT GetWindowHeight(
    void
    );

/**
 * @brief Retrieves the current X-coordinate of the mouse cursor.
 *
 * This function returns the X-coordinate (horizontal position) of the mouse cursor relative to the window's client
 * area. The value is typically in pixels and represents the distance from the left edge of the window to the
 * current position of the mouse cursor.
 *
 * @return The X-coordinate of the mouse cursor in pixels.
 *
 * @note This value updates dynamically as the mouse moves. It is commonly used during the game loop or in
 *       response to input events to track user interaction.
 */
_Check_return_ FLOAT GetMouseX(
    void
    );

/**
 * @brief Retrieves the current Y-coordinate of the mouse cursor.
 *
 * This function returns the Y-coordinate (vertical position) of the mouse cursor relative to the window's client
 * area. The value returned is typically in pixels, and it represents the distance from the top of the window
 * to the mouse cursor's current position.
 *
 * @return The Y-coordinate of the mouse cursor in pixels.
 *
 * @note The returned value may change dynamically as the mouse is moved. This function is typically called in
 *       response to input events or during the game loop to track the mouse position.
 */
_Check_return_ FLOAT GetMouseY(
    void
    );

/**
 * @brief Retrieves the renderer associated with the current window.
 *
 * This function returns the `SDL_Renderer` used for rendering content in the current window. The renderer is
 * responsible for drawing textures, shapes, and other graphical elements to the window. This function is typically
 * used to obtain a reference to the renderer so that it can be used for rendering operations in the game loop.
 *
 * @return A pointer to the `SDL_Renderer` associated with the current window. If the renderer is unavailable,
 *         the function will return `NULL`.
 *
 * @note The returned renderer should be used in conjunction with SDL rendering functions. The caller should not
 *       modify or destroy the renderer directly unless appropriate cleanup is performed.
 */
_Check_return_ SDL_Renderer* GetWindowRenderer(
    void
    );

/**
 * @brief Destroys a window and frees its resources.
 *
 * This function deallocates the memory and resources associated with the specified `Window`, effectively destroying
 * it. After calling this function, the window pointer is no longer valid, and the window will be closed.
 * All resources related to the window, such as textures or other window-specific data, will be cleaned up.
 *
 * @param pWindow Pointer to the `Window` to be destroyed. After the function call, the pointer will be invalid.
 *
 * @return `true` if the window was successfully destroyed, or `false` if an error occurred during destruction.
 *
 * @note The caller should ensure that the window is no longer used after it has been destroyed.
 */
_Check_return_opt_ bool DestroyWindow(
    _Inout_ _Pre_valid_ _Post_invalid_ Window* pWindow
    );

#endif //WINDOW_H
