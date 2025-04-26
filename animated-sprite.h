#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "utils.h"

typedef struct _Sprite Sprite;
typedef struct _Texture Texture;

typedef struct _Animation {
    PCSTR pszName;
    INT iCurrentFrame;
    INT nFrameCount;
    FLOAT fFrameSize;
    UINT64 u64LastTime;
    UINT64 u64FrameTime;
} Animation;

typedef struct _AnimatedSprite {
    Sprite* pSprite;
    Animation* pActiveAnimation;
    Animation* arrAnimations;
    INT nCount;
    INT nCapacity;
} AnimatedSprite;

_Ret_maybenull_
AnimatedSprite* CreateAnimatedSprite(
    _In_ Texture* pTexture,
    _In_ FLOAT x,
    _In_ FLOAT y
    );

_Check_return_opt_
_Success_(return == 0)
RESULT AllocateAnimatedSprite(
    _In_                          Texture* pTexture,
    _In_                          FLOAT x,
    _In_                          FLOAT y,
    _Outptr_result_nullonfailure_ AnimatedSprite** ppAnimSprite
    );

RESULT AddAnimatedSpriteAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName,
    _In_    INT iStartFrame,
    _In_    INT nFrameCount,
    _In_    UINT64 u64FrameTime
    );

void SetActiveAnimatedSpriteAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName
    );

void DrawAnimatedSprite(
    _In_ const AnimatedSprite* pAnimSprite
    );

void UpdateAnimatedSprite(
    _In_ const AnimatedSprite* pAnimSprite
    );

void SetAnimatedSpriteFrame(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   INT iFrame
    );

void SetAnimatedSpriteSpeed(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   UINT64 u64Speed
    );

_Check_return_
PCSTR GetCurrentAnimatedSpriteName(
    _In_ const AnimatedSprite* pAnimSprite
    );

_Check_return_opt_
RESULT DestroyAnimatedSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite* pAnimSprite
    );

#endif
