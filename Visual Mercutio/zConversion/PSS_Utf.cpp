/****************************************************************************
 * ==> PSS_StringConversion ------------------------------------------------*
 ****************************************************************************
 * Description : Utf8 <=> Utf16 conversion helper class                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_Utf.h"

//---------------------------------------------------------------------------
// Global variables and defines
//---------------------------------------------------------------------------
// Conversion UTF8/UTF16 - Unicode 3 standard compliant
char g_BytesFromUTF8[256] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,    3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};
//---------------------------------------------------------------------------
typedef unsigned short UTF16;
typedef unsigned char  UTF8;
typedef unsigned long  UCS4;
typedef unsigned short UCS2;
//---------------------------------------------------------------------------
UCS4 offsetsFromUTF8[6] =
{
    0x00000000UL,
    0x00003080UL,
    0x000E2080UL,
    0x03C82080UL,
    0xFA082080UL,
    0x82082080UL
};
//---------------------------------------------------------------------------
UTF8 firstByteMark[7] =
{
    0x00,
    0x00,
    0xC0,
    0xE0,
    0xF0,
    0xF8,
    0xFC
};
//---------------------------------------------------------------------------
const UCS4 g_ReplacementCharacter = 0x0000FFFDUL;
const UCS4 g_MaximumUCS2          = 0x0000FFFFUL;
const UCS4 g_MaximumUTF16         = 0x0010FFFFUL;
const UCS4 g_MaximumUCS4          = 0x7FFFFFFFUL;
const int  g_HalfShift            = 10;
const UCS4 g_HalfBase             = 0x0010000UL;
const UCS4 g_HalfMask             = 0x3FFUL;
const UCS4 g_SurrogateHighStart   = 0xD800UL;
const UCS4 g_SurrogateHighEnd     = 0xDBFFUL;
const UCS4 g_SurrogateLowStart    = 0xDC00UL;
const UCS4 g_SurrogateLowEnd      = 0xDFFFUL;
//---------------------------------------------------------------------------
typedef enum
{
    ok,              // conversion successful
    sourceExhausted, // partial character in source, but hit end
    targetExhausted  // insuff. room in target for conversion
} ConversionResult;
//---------------------------------------------------------------------------
// Global functions
//---------------------------------------------------------------------------
ConversionResult ConvertUTF16toUTF8(UTF16** pSourceStart,
                              const UTF16*  pSourceEnd,
                                    UTF8**  pTargetStart,
                              const UTF8*   pTargetEnd)
{
    ConversionResult result  = ok;
    register UTF16*  pSource = *pSourceStart;
    register UTF8*   pTarget = *pTargetStart;

    while (pSource < pSourceEnd)
    {
        register UCS4           ch;
        register unsigned short bytesToWrite = 0;
        register const UCS4     byteMask     = 0xBF;
        register const UCS4     byteMark     = 0x80; 

        ch = *pSource++;

        if (ch >= g_SurrogateHighStart && ch <= g_SurrogateHighEnd && pSource < pSourceEnd)
        {
            register UCS4 ch2 = *pSource;

            if (ch2 >= g_SurrogateLowStart && ch2 <= g_SurrogateLowEnd)
            {
                ch = ((ch - g_SurrogateHighStart) << g_HalfShift ) + (ch2 - g_SurrogateLowStart) + g_HalfBase;
                ++pSource;
            }
        }

        if (ch < 0x80)
            bytesToWrite = 1;
        else
        if (ch < 0x800)
            bytesToWrite = 2;
        else
        if (ch < 0x10000)
            bytesToWrite = 3;
        else
        if (ch < 0x200000)
            bytesToWrite = 4;
        else
        if (ch < 0x4000000)
            bytesToWrite = 5;
        else
        if (ch <= g_MaximumUCS4)
            bytesToWrite = 6;
        else
        {
            bytesToWrite = 2;
            ch           = g_ReplacementCharacter;
        }

        // I wish there were a smart way to avoid this conditional
        pTarget += bytesToWrite;

        if (pTarget > pTargetEnd)
        {
            pTarget -= bytesToWrite;
            result   = targetExhausted;
            break;
        }

        // NOTE code falls through cases!
        switch (bytesToWrite)
        {
            case 6:
                *--pTarget = UTF8((ch | byteMark) & byteMask);
                ch >>= 6;

            case 5:
                *--pTarget = UTF8((ch | byteMark) & byteMask);
                ch >>= 6;

            case 4:
                *--pTarget = UTF8((ch | byteMark) & byteMask);
                ch >>= 6;

            case 3:
                *--pTarget = UTF8((ch | byteMark) & byteMask);
                ch >>= 6;

            case 2:
                *--pTarget = UTF8((ch | byteMark) & byteMask);
                ch >>= 6;

            case 1:
                *--pTarget = UTF8(ch | firstByteMark[bytesToWrite]);
        }

        pTarget += bytesToWrite;
    }

    *pSourceStart = pSource;
    *pTargetStart = pTarget;

    return result;
}
//---------------------------------------------------------------------------
ConversionResult ConvertUTF8toUTF16(UTF8**  pSourceStart,
                                    UTF8*   pSourceEnd,
                                    UTF16** pTargetStart,
                              const UTF16*  pTargetEnd)
{
    ConversionResult result  = ok;
    register UTF8*   pSource = *pSourceStart;
    register UTF16*  pTarget = *pTargetStart;

    while (pSource < pSourceEnd)
    {
        register UCS4           ch                   = 0;
        register unsigned short extraBytesToWrite    = g_BytesFromUTF8[*pSource];

        if (pSource + extraBytesToWrite > pSourceEnd)
        {
            result = sourceExhausted;
            break;
        }

        // NOTE code falls through cases!
        switch (extraBytesToWrite)
        {
            case 5:
                ch += *pSource++;
                ch <<= 6;

            case 4:
                ch += *pSource++;
                ch <<= 6;

            case 3:
                ch += *pSource++;
                ch <<= 6;

            case 2:
                ch += *pSource++;
                ch <<= 6;

            case 1:
                ch += *pSource++;
                ch <<= 6;

            case 0:
                ch += *pSource++;
        }

        ch -= offsetsFromUTF8[extraBytesToWrite];

        if (pTarget >= pTargetEnd)
        {
            result = targetExhausted;
            break;
        }

        if (ch <= g_MaximumUCS2)
            *pTarget++ = UTF16(ch);
        else
        if (ch > g_MaximumUTF16)
            *pTarget++ = g_ReplacementCharacter;
        else
        {
            if (pTarget + 1 >= pTargetEnd)
            {
                result = targetExhausted;
                break;
            }

            ch         -= g_HalfBase;
            *pTarget++  = UTF16((ch >> g_HalfShift) + g_SurrogateHighStart);
            *pTarget++  = UTF16((ch &  g_HalfMask)  + g_SurrogateLowStart);
        }
    }

    *pSourceStart = pSource;
    *pTargetStart = pTarget;

    return result;
}
//---------------------------------------------------------------------------
std::string PSS_Utf::UTF16toUTF8(const PSS_String16& str)
{
    const int len     = std::wcslen(str) + 1;
    char*     pTrg    = new char[len * 2 + 2];
    char*     pOutput = pTrg;

    try
    {
        if (ConvertUTF16toUTF8((UTF16**)&str,
            (const UTF16*)(str + len),
            (UTF8**)&pTrg,
            (const UTF8*)(pTrg + len * 2)) != ok)
        {
            delete[] pOutput;
            return _T("");
        }
    }
    catch (...)
    {
        delete[] pOutput;
        throw;
    }

    std::string ret = pOutput;
    delete[] pOutput;

    return ret;
}
//---------------------------------------------------------------------------
PSS_String16 PSS_Utf::UTF8toUTF16(const std::string& str)
{
    const int   len     = str.length() + 1;
    wchar_t*    pTrg    = new wchar_t[len * 2 + 2];
    wchar_t*    pOutput = pTrg;
    const char* pSrcPtr = str.c_str();

    try
    {
        if (ConvertUTF8toUTF16((UTF8**)&(pSrcPtr),
                               (UTF8*)(pSrcPtr + len),
                               (UTF16**)&(pTrg),
                               (const UTF16*)(pTrg + len * 2)) != ok)
        {
            delete[] pOutput;
            return _T("");
        }
    }
    catch (...)
    {
        delete[] pOutput;
        throw;
    }

    PSS_String16 ret(pOutput);
    delete[] pOutput;

    return ret;
}
//---------------------------------------------------------------------------
