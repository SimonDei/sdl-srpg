#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "utils.h"

typedef struct _Sprite Sprite;
typedef struct _Texture Texture;

typedef struct _Animation {
    PSTR pszName;
    INT iStartFrame;
    INT iCurrentFrame;
    INT nFrameCount;
    FLOAT fFrameSizeX;
    FLOAT fFrameSizeY;
    UINT64 u64LastTime;
    UINT64 u64FrameTime;
    bool bPlaying;
} Animation;

typedef struct _AnimatedSprite {
    Sprite* pSprite;
    Animation* pActiveAnimation;
    Animation* arrAnimations;
    INT nCount;
    INT nCapacity;
} AnimatedSprite;

/**
 * @brief Creates a new animated sprite.
 *
 * This function initializes an `AnimatedSprite` using the specified texture and position.
 * The created animated sprite can be used for rendering sprites with animation.
 *
 * @param pTexture Pointer to the `Texture` used for the animated sprite's frames.
 * @param x        The X coordinate in world space for the initial position of the animated sprite.
 * @param y        The Y coordinate in world space for the initial position of the animated sprite.
 * @return A pointer to an `AnimatedSprite` object, or `NULL` if the sprite could not be created.
 */
_Check_return_ _Ret_maybenull_ AnimatedSprite* AnimatedSprite_Create(
    _In_ Texture* pTexture,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

/**
 * @brief Allocates memory for a new animated sprite and initializes it.
 *
 * This function allocates memory for an `AnimatedSprite` and initializes it using the specified texture and position.
 * If the allocation and initialization are successful, a pointer to the created animated sprite is returned
 * via the `ppAnimSprite` parameter.
 *
 * @param pTexture        Pointer to the `Texture` used for the animated sprite's frames.
 * @param x               The X coordinate in world space for the initial position of the animated sprite.
 * @param y               The Y coordinate in world space for the initial position of the animated sprite.
 * @param ppAnimSprite    Output parameter that will point to the allocated and initialized `AnimatedSprite` on success.
 *                        It will be set to `NULL` if the allocation fails.
 * @return `0` if the animated sprite was successfully allocated and initialized, or a non-zero error code if the operation failed.
 *
 * @note The caller is responsible for freeing the allocated memory when it is no longer needed.
 */
_Check_return_opt_ _Success_(return == 0) Result
AnimatedSprite_Allocate(
    _In_                          Texture* pTexture,
    _In_                          FLOAT x,
    _In_                          FLOAT y,
    _Outptr_result_nullonfailure_ AnimatedSprite** ppAnimSprite
    );

/**
 * @brief Adds a new animation to an animated sprite.
 *
 * This function adds a new animation to the specified `AnimatedSprite`. The animation is defined by a name,
 * the starting frame index, the total number of frames in the animation, and the frame time (duration for each frame).
 * The new animation can then be played or managed using the sprite's animation system.
 *
 * @param pAnimSprite  Pointer to the `AnimatedSprite` to which the animation will be added.
 * @param pszName      The name of the animation. This will be used to identify and play the animation.
 * @param fFrameSizeX  The width of each frame in the animation.
 * @param fFrameSizeY  The height of each frame in the animation.
 * @param iStartFrame  The index of the starting frame for the animation.
 * @param nFrameCount  The total number of frames in the animation.
 * @param u64FrameTime The duration (in milliseconds) for each frame of the animation.
 * @return `RESULT` indicating the success or failure of the operation.
 *         A successful result should return `0`, while non-zero values indicate failure.
 */
Result AnimatedSprite_AddAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName,
    _In_    FLOAT fFrameSizeX,
    _In_    FLOAT fFrameSizeY,
    _In_    INT iStartFrame,
    _In_    INT nFrameCount,
    _In_    UINT64 u64FrameTime
    );

void AnimatedSprite_LoadAnimationsFromFile(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszFileName
    );

/**
 * @brief Sets the active animation for an animated sprite.
 *
 * This function sets the specified animation as the active animation for the given `AnimatedSprite`.
 * The active animation will be played, and the sprite will update to the frames of this animation.
 *
 * @param pAnimSprite  Pointer to the `AnimatedSprite` whose active animation will be set.
 * @param pszName      The name of the animation to be set as active.
 *
 * @note If the animation name does not exist or is invalid, the function may have no effect.
 */
void AnimatedSprite_SetActiveAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName
    );

/**
 * @brief Draws the current frame of an animated sprite.
 *
 * This function renders the current frame of the specified `AnimatedSprite` to the screen. The sprite will
 * be drawn using its current active animation and the appropriate frame based on the animation's progress.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` to be drawn. The sprite must have an active animation set
 *                    and the animation must be updated to display the correct frame.
 */
void AnimatedSprite_Draw(
    _In_ const AnimatedSprite* pAnimSprite
    );

/**
 * @brief Updates the animation state of the specified animated sprite.
 *
 * This function updates the current animation of the `AnimatedSprite`, advancing its frame based on the
 * frame time and animation logic. It should be called regularly (e.g., once per frame) to ensure that the
 * sprite's animation progresses correctly.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` whose animation state will be updated.
 *                    The function will update the animation's current frame based on the elapsed time.
 *
 * @note The function does not perform any rendering. It only updates the sprite's animation state.
 */
void AnimatedSprite_Update(
    _In_ const AnimatedSprite* pAnimSprite
    );

/**
 * @brief Sets a specific frame for an animation in the animated sprite.
 *
 * This function allows you to set the current frame of a specific animation within the `AnimatedSprite`.
 * By specifying the animation name and the frame index, this function will directly set the sprite to
 * the given frame of the selected animation.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` whose animation frame will be updated.
 * @param pszName     The name of the animation whose frame is to be set.
 * @param iFrame      The frame index to set within the specified animation.
 *
 * @note This function bypasses the normal animation progression and directly sets the sprite to the
 *       specified frame. Ensure that the frame index is within the valid range of frames for the specified animation.
 */
void AnimatedSprite_SetFrame(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   INT iFrame
    );

/**
 * @brief Sets the animation speed for a specific animation in the animated sprite.
 *
 * This function adjusts the speed at which a specific animation progresses in the `AnimatedSprite`. The speed
 * is specified in terms of time (usually milliseconds) per frame. A lower value will make the animation progress
 * faster, while a higher value will slow it down.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` whose animation speed will be set.
 * @param pszName     The name of the animation whose speed is to be adjusted.
 * @param u64Speed    The speed of the animation, typically the time (in milliseconds) each frame should be displayed.
 *
 * @note Adjusting the animation speed affects how quickly the frames of the animation change. Ensure that the speed
 *       value is appropriate for the intended effect. A speed of `0` may result in the animation not progressing.
 */
void AnimatedSprite_SetSpeed(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   UINT64 u64Speed
    );

void AnimatedSprite_SetScale(
    _In_ const AnimatedSprite* pAnimSprite,
    _In_ FLOAT fScale
    );

void AnimatedSprite_SetPlaying(
    _Inout_ const AnimatedSprite* pAnimSprite,
    _In_    bool bPlaying
    );

/**
 * @brief Gets the name of the currently active animation in an animated sprite.
 *
 * This function retrieves the name of the currently active animation in the specified `AnimatedSprite`.
 * The active animation is the one currently being played by the sprite.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` whose active animation name will be retrieved.
 * @return A string representing the name of the currently active animation, or `NULL` if no animation is active.
 */
_Check_return_ PCSTR AnimatedSprite_GetCurrentName(
    _In_ const AnimatedSprite* pAnimSprite
    );

/**
 * @brief Destroys an animated sprite and frees its resources.
 *
 * This function deallocates the memory associated with an `AnimatedSprite` and releases any resources it may have
 * allocated. After calling this function, the `AnimatedSprite` pointer is no longer valid.
 *
 * @param pAnimSprite Pointer to the `AnimatedSprite` to be destroyed. After the function call, the pointer will be invalid.
 * @return `RESULT` indicating the success or failure of the operation. A return value of `0` typically indicates success,
 *         while non-zero values indicate failure.
 *
 * @note The caller is responsible for ensuring that the sprite is no longer used after being destroyed.
 */
_Check_return_opt_ Result AnimatedSprite_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite* pAnimSprite
    );

#endif //ANIMATED_SPRITE_H
