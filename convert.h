#ifndef CONVERT_H
#define CONVERT_H

#include "utils.h"

_Check_return_
static PCSTR IntToStr(
    _In_ const INT nValue
) {
    char szBuffer[32];
    snprintf(szBuffer, sizeof(szBuffer), "%d", nValue);
    return szBuffer;
}

_Check_return_
static PCSTR UlongToStr(
    _In_ const UINT64 uValue
) {
    char szBuffer[32];
    snprintf(szBuffer, sizeof(szBuffer), "%llu", uValue);
    return szBuffer;
}

_Check_return_
static PCSTR FloatToStr(
    _In_ const FLOAT fValue
) {
    char szBuffer[32];
    snprintf(szBuffer, sizeof(szBuffer), "%.2f", fValue);
    return szBuffer;
}

_Check_return_
static INT StrToInt(
    _In_z_ const PCSTR pszValue
) {
    PSTR pszEnd;
    const LONG lValue = strtol(pszValue, &pszEnd, 10);
    if (pszEnd == pszValue) {
        return 0;
    }
    return (INT)lValue;
}

_Check_return_
static UINT64 StrToUlong(
    _In_z_ const PCSTR pszValue
) {
    PSTR pszEnd;
    const ULONG uValue = strtoull(pszValue, &pszEnd, 10);
    if (pszEnd == pszValue) {
        return 0;
    }
    return uValue;
}

_Check_return_
static FLOAT StrToFloat(
    _In_z_ const PCSTR pszValue
) {
    PSTR pszEnd;
    const FLOAT fValue = strtof(pszValue, &pszEnd);
    if (pszEnd == pszValue) {
        return 0.0f;
    }
    return fValue;
}

#endif //CONVERT_H
