#ifndef FILE_H
#define FILE_H

#include "utils.h"

typedef struct _File {
    PSTR pszFilename;
    LONG cbSize;
    FILE* pFileHandle;
} File;

_Check_return_ _Ret_maybenull_
File* File_Open(
    _In_z_ PCSTR pszFilename
    );

_Check_return_
bool File_Exists(
    _In_z_ PCSTR pszFilename
    );

_Check_return_
BYTE File_ReadByte(
    _In_ const File* pFile
    );

_Check_return_
INT File_ReadInt(
    _In_ const File* pFile
    );

_Check_return_
FLOAT File_ReadFloat(
    _In_ const File* pFile
    );

_Check_return_ _Ret_maybenull_
_Success_(return != NULL)
PSTR File_ReadLine(
    _In_      const File* pFile,
    _Out_opt_ ULONG* pcchBufferSize
    );

_Check_return_ _Ret_maybenull_
_Success_(return != NULL)
PSTR File_ReadAllBytes(
    _In_      const File* pFile,
    _Out_opt_ ULONG* pcchBufferSize
    );

_Check_return_
bool File_IsOpen(
    _In_ const File* pFile
    );

_Check_return_ _Ret_z_
PCSTR File_GetFilename(
    _In_ const File* pFile
    );

_Check_return_
LONG File_GetSize(
    _In_ const File* pFile
    );

_Check_return_opt_
bool File_Close(
    _Inout_ _Pre_valid_ _Post_invalid_ File* pFile
    );

#endif //FILE_H
