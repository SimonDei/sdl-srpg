#include "animated-sprite.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>

#include "window.h"
#include "camera.h"
#include "sprite.h"
#include "texture.h"

_Ret_maybenull_
AnimatedSprite* CreateAnimatedSprite(
    _In_ Texture* pTexture,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    AnimatedSprite* pAnimSprite = malloc(sizeof(AnimatedSprite));
    if (!pAnimSprite) {
        SDL_Log("Failed to allocate memory for animated sprite.\n");
        return NULL;
    }

    pAnimSprite->nCount = 0;
    pAnimSprite->nCapacity = 5;
    pAnimSprite->pSprite = CreateSprite(pTexture, x, y);
    pAnimSprite->arrAnimations = malloc(pAnimSprite->nCapacity * sizeof(Animation));
    if (!pAnimSprite->arrAnimations) {
        SDL_Log("Failed to allocate memory for animated sprite frames.\n");
        SafeFree(pAnimSprite);
        return NULL;
    }

    return pAnimSprite;
}

_Check_return_opt_
_Success_(return == 0)
RESULT AllocateAnimatedSprite(
    _In_                          Texture* pTexture,
    _In_                          const FLOAT x,
    _In_                          const FLOAT y,
    _Outptr_result_nullonfailure_ AnimatedSprite** ppAnimSprite
) {
    *ppAnimSprite = malloc(sizeof(AnimatedSprite));
    if (!*ppAnimSprite) {
        SDL_Log("Failed to allocate memory for animated sprite.\n");
        return RESULT_MALLOC_FAILED;
    }

    (*ppAnimSprite)->nCount = 0;
    (*ppAnimSprite)->nCapacity = 5;
    (*ppAnimSprite)->pSprite = CreateSprite(pTexture, x, y);
    (*ppAnimSprite)->arrAnimations = malloc((*ppAnimSprite)->nCapacity * sizeof(Animation));
    if (!(*ppAnimSprite)->arrAnimations) {
        SDL_Log("Failed to allocate memory for animated sprite frames.\n");
        SafeFree(*ppAnimSprite);
        return RESULT_MALLOC_FAILED;
    }

    return RESULT_SUCCESS;
}

RESULT AddAnimatedSpriteAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName,
    _In_    const INT iStartFrame,
    _In_    const INT nFrameCount,
    _In_    const UINT64 u64FrameTime
) {
    if (pAnimSprite->nCount >= pAnimSprite->nCapacity) {
        pAnimSprite->nCapacity += 5;
        Animation* arrAnimations = realloc(pAnimSprite->arrAnimations, pAnimSprite->nCapacity * sizeof(Animation));
        if (!arrAnimations) {
            return RESULT_REALLOC_FAILED;
        }
        pAnimSprite->arrAnimations = arrAnimations;
    }

    pAnimSprite->arrAnimations[pAnimSprite->nCount].pszName = pszName;
    pAnimSprite->arrAnimations[pAnimSprite->nCount].iCurrentFrame = iStartFrame;
    pAnimSprite->arrAnimations[pAnimSprite->nCount].nFrameCount = nFrameCount;
    pAnimSprite->arrAnimations[pAnimSprite->nCount].u64LastTime = 0;
    pAnimSprite->arrAnimations[pAnimSprite->nCount].u64FrameTime = u64FrameTime;
    pAnimSprite->arrAnimations[pAnimSprite->nCount].fFrameSize = pAnimSprite->pSprite->pTexture->fWidth / nFrameCount;
    pAnimSprite->nCount++;

    return RESULT_SUCCESS;
}

void SetActiveAnimatedSpriteAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName
) {
    for (int i = 0; i < pAnimSprite->nCount; i++) {
        if (strcmp(pAnimSprite->arrAnimations[i].pszName, pszName) == 0) {
            pAnimSprite->pActiveAnimation = &pAnimSprite->arrAnimations[i];
            break;
        }
    }
}

void DrawAnimatedSprite(
    _In_ const AnimatedSprite* pAnimSprite
) {
    const int iSourceX = pAnimSprite->pActiveAnimation->iCurrentFrame % (int)(pAnimSprite->pSprite->pTexture->fWidth / pAnimSprite->pActiveAnimation->fFrameSize);
    const int iSourceY = pAnimSprite->pActiveAnimation->iCurrentFrame / (int)(pAnimSprite->pSprite->pTexture->fWidth / pAnimSprite->pActiveAnimation->fFrameSize);

    const SDL_FRect srcRect = {
        (float)iSourceX * pAnimSprite->pActiveAnimation->fFrameSize,
        (float)iSourceY * pAnimSprite->pActiveAnimation->fFrameSize,
        pAnimSprite->pActiveAnimation->fFrameSize,
        pAnimSprite->pActiveAnimation->fFrameSize
    };

    const Vector2 screenPos = WorldToScreen(pAnimSprite->pSprite->x, pAnimSprite->pSprite->y);

    const SDL_FRect dstRect = {
        screenPos.x,
        screenPos.y,
        pAnimSprite->pActiveAnimation->fFrameSize * GetCameraZoom(),
        pAnimSprite->pActiveAnimation->fFrameSize * GetCameraZoom()
    };
    
    SDL_RenderTexture(
        GetWindowRenderer(),
        pAnimSprite->pSprite->pTexture->pBitmap,
        &srcRect,
        &dstRect
    );
}

void UpdateAnimatedSprite(
    _In_ const AnimatedSprite* pAnimSprite
) {
    const UINT64 u64Time = SDL_GetTicks();
    if (u64Time - pAnimSprite->pActiveAnimation->u64LastTime >= pAnimSprite->pActiveAnimation->u64FrameTime) {
        pAnimSprite->pActiveAnimation->u64LastTime = u64Time;
        pAnimSprite->pActiveAnimation->iCurrentFrame++;
        if (pAnimSprite->pActiveAnimation->iCurrentFrame >= pAnimSprite->pActiveAnimation->nFrameCount) {
            pAnimSprite->pActiveAnimation->iCurrentFrame = 0;
        }
    }
}

void SetAnimatedSpriteFrame(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   const INT iFrame
) {
    for (int i = 0; i < pAnimSprite->nCount; i++) {
        if (strcmp(pAnimSprite->arrAnimations[i].pszName, pszName) == 0) {
            pAnimSprite->arrAnimations[i].iCurrentFrame = iFrame;
        }
    }
}

void SetAnimatedSpriteSpeed(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   UINT64 u64Speed
) {
    for (int i = 0; i < pAnimSprite->nCount; i++) {
        if (strcmp(pAnimSprite->arrAnimations[i].pszName, pszName) == 0) {
            pAnimSprite->arrAnimations[i].u64FrameTime = u64Speed;
        }
    }
}

_Check_return_
PCSTR GetCurrentAnimatedSpriteName(
    _In_ const AnimatedSprite* pAnimSprite
) {
    return pAnimSprite->pActiveAnimation->pszName;
}

_Check_return_opt_
RESULT DestroyAnimatedSprite(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite* pAnimSprite
) {
    if (!pAnimSprite) {
        return RESULT_NULL_POINTER;
    }

    DestroySprite(pAnimSprite->pSprite);

    SafeFree(pAnimSprite->arrAnimations);
    SafeFree(pAnimSprite);

    return RESULT_SUCCESS;
}
