/****************************************************************************
 * ==> PSS_StringConversion ------------------------------------------------*
 ****************************************************************************
 * Description : String conversion helper class                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StringTools.h"

// processsoft
#include "PSS_Encoding.h"
#include "PSS_Utf.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_DoCharacterConversionMethod = 1; // 0 = no, 1 = utf-8, 2 = iso8859
//---------------------------------------------------------------------------
// PSS_StringConversion
//---------------------------------------------------------------------------
PSS_String16 PSS_StringTools::ConvertFrom(const std::string& str)
{
    if (!str.length())
        return PSS_String16(_T(""));

    switch (g_DoCharacterConversionMethod)
    {
        case 0:  throw _T("convertFrom (0) : not implemented");
        case 1:  return PSS_Utf::UTF8toUTF16(str);
        case 2:  throw _T("convertFrom (2) : not implemented");
        default: return PSS_String16(_T(""));
    }
}
//---------------------------------------------------------------------------
std::string PSS_StringTools::ConvertTo(const PSS_String16& str)
{
    if (!str.Length())
        return _T("");

    std::string result = _T("");

    switch (g_DoCharacterConversionMethod)
    {
        case 0:
            throw _T("convertTo(0) : not implemented");

        case 1:
        {
            const wchar_t* pPtr = str;
            std::string    tmp = PSS_Utf::UTF16toUTF8(str);

            char xxx[111];
            sprintf_s(xxx, sizeof(xxx), _T("L=%d"), tmp.length());
            OutputDebugString(xxx);
            OutputDebugString(_T("<\n"));

            result = PSS_Encoding::Base64Encode((char*)tmp.c_str(), tmp.length());
            break;
        }

        case 2:
            throw _T("convertTo(2) : not implemented");
    }

    return result;
}
//---------------------------------------------------------------------------
CString PSS_StringTools::ConvertSpecialChar(const CString& str)
{
    CString result = str;

    // get access to string memory
    char* pC = result.GetBuffer(result.GetLength() + 1);

    // iterate through string chars
    while (*pC)
    {
        // convert some symbols
        switch (*pC)
        {
            case ' ':
            case '.':
            case ':':
            case '¨':
            case '?':
            case '<':
            case '>':
            case '=':
            case '!':
            case '\'':
            case '\n':
            case '\r':
            case '\t':
            case '~':  *pC = '_'; break;

            case 'é':
            case 'è':
            case 'ê':  *pC = 'e'; break;

            case 'à':
            case 'ä':
            case 'â':  *pC = 'a'; break;

            case 'ï':
            case 'î':  *pC = 'i'; break;

            case 'ô':  *pC = 'o'; break;

            case 'ç':  *pC = 'c'; break;

            case 'û':
            case 'ü':
            case 'ù':  *pC = 'u'; break;
        }

        ++pC;
    }

    // don't forget to release the buffer
    result.ReleaseBuffer(-1);

    return result;
}
//---------------------------------------------------------------------------
