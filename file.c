#include "file.h"

#include <string.h>

_Check_return_ _Ret_maybenull_
File* File_Open(
    _In_z_ PCSTR pszFilename
) {
    FILE* pFileHandle = NULL;
    fopen_s(&pFileHandle, pszFilename, "r");
    if (pFileHandle == NULL) {
        return NULL;
    }

    File* pFile = malloc(sizeof(File));
    if (pFile == NULL) {
        fclose(pFileHandle);
        return NULL;
    }

    fseek(pFileHandle, 0, SEEK_END);
    pFile->cbSize = ftell(pFileHandle);
    fseek(pFileHandle, 0, SEEK_SET);

    pFile->pszFilename = strdup(pszFilename);
    pFile->pFileHandle = pFileHandle;

    return pFile;
}

_Check_return_
bool File_Exists(
    _In_z_ PCSTR pszFilename
) {
    FILE* pFileHandle = NULL;
    fopen_s(&pFileHandle, pszFilename, "r");
    if (pFileHandle) {
        fclose(pFileHandle);
        return true;
    }
    return false;
}

_Check_return_
BYTE File_ReadByte(
    _In_ const File* pFile
) {
    if (!pFile || !pFile->pFileHandle) {
        return 0;
    }
    const BYTE byte = (BYTE)fgetc(pFile->pFileHandle);
    if (feof(pFile->pFileHandle)) {
        return 0;
    }
    return byte;
}

_Check_return_
INT File_ReadInt(
    _In_ const File* pFile
) {
    if (!pFile || !pFile->pFileHandle) {
        return 0;
    }
    INT value = 0;
    fread(&value, sizeof(INT), 1, pFile->pFileHandle);
    if (feof(pFile->pFileHandle)) {
        return 0;
    }
    return value;
}

_Check_return_
FLOAT File_ReadFloat(
    _In_ const File* pFile
) {
    if (!pFile || !pFile->pFileHandle) {
        return 0.0f;
    }
    FLOAT value = 0.0f;
    fread(&value, sizeof(FLOAT), 1, pFile->pFileHandle);
    if (feof(pFile->pFileHandle)) {
        return 0.0f;
    }
    return value;
}

_Check_return_ _Ret_maybenull_
_Success_(return != NULL)
PSTR File_ReadLine(
    _In_      const File* pFile,
    _Out_opt_ ULONG* pcchBufferSize
) {
    if (!pFile || !pFile->pFileHandle) {
        return NULL;
    }

    ULONG nMaxBufferSize = 128;
    ULONG iCurrentChar = 0;
    PSTR pstrBuffer = malloc(nMaxBufferSize * sizeof(char));
    if (!pstrBuffer) {
        return NULL;
    }

    int ch;
    while ((ch = fgetc(pFile->pFileHandle)) != EOF) {
        if (iCurrentChar + 1 >= nMaxBufferSize) {
            nMaxBufferSize *= 2;
            PSTR pstrNewBuffer = realloc(pstrBuffer, nMaxBufferSize);
            if (!pstrNewBuffer) {
                SafeFree(pstrBuffer);
                return NULL;
            }
            pstrBuffer = pstrNewBuffer;
        }

        pstrBuffer[iCurrentChar++] = (char)ch;
        if (ch == '\n') {
            break;
        }
    }

    if (iCurrentChar == 0 && feof(pFile->pFileHandle)) {
        SafeFree(pstrBuffer);
        return NULL;
    }

    pstrBuffer[iCurrentChar] = '\0';

    if (pcchBufferSize != NULL) {
        *pcchBufferSize = iCurrentChar;
    }

    return pstrBuffer;
}

_Check_return_ _Ret_maybenull_
_Success_(return != NULL)
PSTR File_ReadAllBytes(
    _In_      const File* pFile,
    _Out_opt_ ULONG* pcchBufferSize
) {
    if (!pFile || !pFile->pFileHandle) {
        return NULL;
    }

    const ULONG bufferSize = pFile->cbSize + 1;
    PSTR pstrBuffer = malloc(bufferSize * sizeof(char));
    if (!pstrBuffer) {
        return NULL;
    }

    const ULONG cchBuffer = fread(pstrBuffer, sizeof(char), pFile->cbSize, pFile->pFileHandle);
    if (cchBuffer == 0 && ferror(pFile->pFileHandle)) {
        SafeFree(pstrBuffer);
        return NULL;
    }

    pstrBuffer[cchBuffer] = '\0';
    if (pcchBufferSize != NULL) {
        *pcchBufferSize = cchBuffer;
    }

    return pstrBuffer;
}

_Check_return_
bool File_IsOpen(
    _In_ const File* pFile
) {
    return pFile != NULL && pFile->pFileHandle != NULL;
}

_Check_return_ _Ret_z_
PCSTR File_GetFilename(
    _In_ const File* pFile
) {
    return pFile->pszFilename;
}

_Check_return_
LONG File_GetSize(
    _In_ const File* pFile
) {
    return pFile->cbSize;
}

_Check_return_opt_
bool File_Close(
    _Inout_ _Pre_valid_ _Post_invalid_ File* pFile
) {
    if (pFile == NULL) {
        return false;
    }

    if (pFile->pFileHandle != NULL) {
        fclose(pFile->pFileHandle);
        pFile->pFileHandle = NULL;
    }

    SafeFree(pFile->pszFilename);
    SafeFree(pFile);
    return true;
}
