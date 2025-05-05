#include "animated-sprite.h"

#include <string.h>
#include <SFML/Graphics.h>

#include "window.h"
#include "camera.h"
#include "sprite.h"
#include "texture.h"
#include "file.h"
#include "convert.h"
#include "xml.h"

_Check_return_ _Ret_maybenull_
AnimatedSprite* AnimatedSprite_Create(
    _In_ Texture* pTexture,
    _In_ const FLOAT x,
    _In_ const FLOAT y
) {
    AnimatedSprite* pAnimSprite = malloc(sizeof(AnimatedSprite));
    if (!pAnimSprite) {
        printf("Failed to allocate memory for animated sprite.\n");
        return NULL;
    }

    pAnimSprite->nCount = 0;
    pAnimSprite->nCapacity = 5;
    pAnimSprite->pSprite = Sprite_Create(pTexture, x, y);
    pAnimSprite->arrAnimations = malloc(pAnimSprite->nCapacity * sizeof(Animation));
    if (!pAnimSprite->arrAnimations) {
        printf("Failed to allocate memory for animated sprite frames.\n");
        SafeFree(pAnimSprite);
        return NULL;
    }

    return pAnimSprite;
}

_Check_return_opt_
_Success_(return == 0)
Result AnimatedSprite_Allocate(
    _In_                          Texture* pTexture,
    _In_                          const FLOAT x,
    _In_                          const FLOAT y,
    _Outptr_result_nullonfailure_ AnimatedSprite** ppAnimSprite
) {
    *ppAnimSprite = malloc(sizeof(AnimatedSprite));
    if (!*ppAnimSprite) {
        printf("Failed to allocate memory for animated sprite.\n");
        return RESULT_MALLOC_FAILED;
    }

    (*ppAnimSprite)->nCount = 0;
    (*ppAnimSprite)->nCapacity = 5;
    (*ppAnimSprite)->pSprite = Sprite_Create(pTexture, x, y);
    (*ppAnimSprite)->arrAnimations = malloc((*ppAnimSprite)->nCapacity * sizeof(Animation));
    if (!(*ppAnimSprite)->arrAnimations) {
        printf("Failed to allocate memory for animated sprite frames.\n");
        SafeFree(*ppAnimSprite);
        return RESULT_MALLOC_FAILED;
    }

    return RESULT_SUCCESS;
}

Result AnimatedSprite_AddAnimation(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszName,
    _In_    const FLOAT fFrameSizeX,
    _In_    const FLOAT fFrameSizeY,
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

    Animation* pAnimation = &pAnimSprite->arrAnimations[pAnimSprite->nCount];
    pAnimation->pszName = _strdup(pszName);
    pAnimation->iStartFrame = iStartFrame;
    pAnimation->iCurrentFrame = iStartFrame;
    pAnimation->nFrameCount = nFrameCount;
    pAnimation->u64LastTime = 0;
    pAnimation->u64FrameTime = u64FrameTime;
    pAnimation->fFrameSizeX = fFrameSizeX;
    pAnimation->fFrameSizeY = fFrameSizeY;
    pAnimation->bPlaying = true;

    pAnimSprite->nCount++;

    return RESULT_SUCCESS;
}

static void ParseXmlNodeContentFloat(
    _Out_ FLOAT* pfValue,
    _In_  struct xml_node* pXmlNode,
    _In_  const INT iNode
) {
    BYTE* pNodeContent = xml_easy_content(xml_node_child(pXmlNode, iNode));
    *pfValue = StrToFloat((PCSTR)pNodeContent);
    SafeFree(pNodeContent);
}

static void ParseXmlNodeContentInt(
    _Out_ INT* pnValue,
    _In_  struct xml_node* pXmlNode,
    _In_  const INT iNode
) {
    BYTE* pNodeContent = xml_easy_content(xml_node_child(pXmlNode, iNode));
    *pnValue = StrToInt((PCSTR)pNodeContent);
    SafeFree(pNodeContent);
}

static void ParseXmlNodeContentUlong(
    _Out_ ULONG* pu64Value,
    _In_  struct xml_node* pXmlNode,
    _In_  const INT iNode
) {
    BYTE* pNodeContent = xml_easy_content(xml_node_child(pXmlNode, iNode));
    *pu64Value = StrToUlong((PCSTR)pNodeContent);
    SafeFree(pNodeContent);
}

void AnimatedSprite_LoadAnimationsFromFile(
    _Inout_ AnimatedSprite* pAnimSprite,
    _In_z_  PCSTR pszFileName
) {
    File* pAnimationFile = File_Open(pszFileName);
    if (!pAnimationFile) {
        printf("Failed to open file: %s\n", pszFileName);
        return;
    }

    PSTR pszBuffer = File_ReadAllBytes(pAnimationFile, NULL);
    if (!pszBuffer) {
        printf("Failed to read file: %s\n", pszFileName);
        File_Close(pAnimationFile);
        return;
    }

    File_Close(pAnimationFile);

    struct xml_document* pXmlDocument = xml_parse_document((uint8_t*)pszBuffer, strlen(pszBuffer));
    if (!pXmlDocument) {
        printf("Failed to parse file: %s\n", pszFileName);
        SafeFree(pszBuffer);
        return;
    }

    struct xml_node* pRootElement = xml_document_root(pXmlDocument);
    const ULONG nAnimations = xml_node_children(pRootElement);

    if (pAnimSprite->nCapacity <= nAnimations) {
        pAnimSprite->nCapacity = (int)nAnimations + 1;
        Animation* arrAnimations = realloc(pAnimSprite->arrAnimations, pAnimSprite->nCapacity * sizeof(Animation));
        if (!arrAnimations) {
            printf("Failed to allocate memory for animated sprite frames.\n");
            xml_document_free(pXmlDocument, false);
            SafeFree(pszBuffer);
            return;
        }
        pAnimSprite->arrAnimations = arrAnimations;
    }

    for (int i = 0; i < nAnimations; i++) {
        struct xml_node* pXmlAnimationNode = xml_node_child(pRootElement, i);

        Animation* pAnimation = &pAnimSprite->arrAnimations[i];

        pAnimation->pszName = (PSTR)xml_easy_content(xml_node_child(pXmlAnimationNode, 0));

        ParseXmlNodeContentFloat(&pAnimation->fFrameSizeX, pXmlAnimationNode, 1);
        ParseXmlNodeContentFloat(&pAnimation->fFrameSizeY, pXmlAnimationNode, 2);
        ParseXmlNodeContentInt(&pAnimation->iStartFrame, pXmlAnimationNode, 3);
        ParseXmlNodeContentInt(&pAnimation->nFrameCount, pXmlAnimationNode, 4);
        ParseXmlNodeContentUlong(&pAnimation->u64FrameTime, pXmlAnimationNode, 5);

        pAnimation->iCurrentFrame = pAnimation->iStartFrame;
        pAnimation->u64LastTime = 0;
        pAnimation->bPlaying = true;

        pAnimSprite->nCount++;
    }

    xml_document_free(pXmlDocument, false);
    SafeFree(pszBuffer);
}

void AnimatedSprite_SetActiveAnimation(
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

void AnimatedSprite_Draw(
    _In_ const AnimatedSprite* pAnimSprite
) {
    const int iSourceX = pAnimSprite->pActiveAnimation->iCurrentFrame % (int)(Sprite_GetWidth(pAnimSprite->pSprite) / pAnimSprite->pActiveAnimation->fFrameSizeX);
    const int iSourceY = pAnimSprite->pActiveAnimation->iCurrentFrame / (int)(Sprite_GetWidth(pAnimSprite->pSprite) / pAnimSprite->pActiveAnimation->fFrameSizeX);

    /*
    const Vector2 screenPos = WorldToScreen(pAnimSprite->pSprite->x, pAnimSprite->pSprite->y);

    const SDL_FRect dstRect = {
        screenPos.x,
        screenPos.y,
        pAnimSprite->pActiveAnimation->fFrameSizeX * pAnimSprite->pSprite->fScaleX * Camera_GetZoom(),
        pAnimSprite->pActiveAnimation->fFrameSizeY * pAnimSprite->pSprite->fScaleY * Camera_GetZoom()
    };
    */

    sfSprite_setTextureRect(
        pAnimSprite->pSprite->pSpriteHandle,
        (sfIntRect) {
            iSourceX * (int)pAnimSprite->pActiveAnimation->fFrameSizeX,
            iSourceY * (int)pAnimSprite->pActiveAnimation->fFrameSizeY,
            (int)pAnimSprite->pActiveAnimation->fFrameSizeX,
            (int)pAnimSprite->pActiveAnimation->fFrameSizeY
        }
    );
    
    Sprite_Draw(pAnimSprite->pSprite);
}

void AnimatedSprite_Update(
    _In_ const AnimatedSprite* pAnimSprite
) {
    if (!pAnimSprite->pActiveAnimation->bPlaying) {
        return;
    }

    const INT nTime = GetTime();
    if (nTime - pAnimSprite->pActiveAnimation->u64LastTime >= pAnimSprite->pActiveAnimation->u64FrameTime) {
        pAnimSprite->pActiveAnimation->u64LastTime = nTime;
        pAnimSprite->pActiveAnimation->iCurrentFrame++;
        if (pAnimSprite->pActiveAnimation->iCurrentFrame >= pAnimSprite->pActiveAnimation->nFrameCount + pAnimSprite->pActiveAnimation->iStartFrame) {
            pAnimSprite->pActiveAnimation->iCurrentFrame = pAnimSprite->pActiveAnimation->iStartFrame;
        }
    }
}

void AnimatedSprite_SetFrame(
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

void AnimatedSprite_SetSpeed(
    _In_   const AnimatedSprite* pAnimSprite,
    _In_z_ PCSTR pszName,
    _In_   const UINT64 u64Speed
) {
    for (int i = 0; i < pAnimSprite->nCount; i++) {
        if (strcmp(pAnimSprite->arrAnimations[i].pszName, pszName) == 0) {
            pAnimSprite->arrAnimations[i].u64FrameTime = u64Speed;
        }
    }
}

void AnimatedSprite_SetScale(
    _In_ const AnimatedSprite* pAnimSprite,
    _In_ const FLOAT fScale
) {
    Sprite_SetScale(pAnimSprite->pSprite, fScale, fScale);
}

void AnimatedSprite_SetPlaying(
    _Inout_ const AnimatedSprite* pAnimSprite,
    _In_    const bool bPlaying
) {
    pAnimSprite->pActiveAnimation->bPlaying = bPlaying;
}

_Check_return_
PCSTR AnimatedSprite_GetCurrentName(
    _In_ const AnimatedSprite* pAnimSprite
) {
    return pAnimSprite->pActiveAnimation->pszName;
}

_Check_return_opt_
Result AnimatedSprite_Destroy(
    _Inout_ _Pre_valid_ _Post_invalid_ AnimatedSprite* pAnimSprite
) {
    if (!pAnimSprite) {
        return RESULT_NULL_POINTER;
    }

    Sprite_Destroy(pAnimSprite->pSprite);

    for (int i = 0; i < pAnimSprite->nCount; i++) {
        SafeFree(pAnimSprite->arrAnimations[i].pszName);
    }

    SafeFree(pAnimSprite->arrAnimations);
    SafeFree(pAnimSprite);

    return RESULT_SUCCESS;
}
