/****************************************************************************
 * ==> PSS_Font ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font object                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Font.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Font, CFont, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Font
//---------------------------------------------------------------------------
PSS_Font::PSS_Font() :
    CFont(),
    m_hFontNumber(-1)
{}
//---------------------------------------------------------------------------
PSS_Font::PSS_Font(const PSS_Font& other) :
    CFont(),
    m_hFontNumber(-1)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Font::~PSS_Font()
{}
//---------------------------------------------------------------------------
const PSS_Font& PSS_Font::operator = (const PSS_Font& other)
{
    LOGFONT lf;
    other.GetObject(sizeof(LOGFONT), &lf);

    ::CreateFont(lf.lfHeight,
                 lf.lfWidth,
                 lf.lfEscapement,
                 lf.lfOrientation,
                 lf.lfWeight,
                 lf.lfItalic,
                 lf.lfUnderline,
                 lf.lfStrikeOut,
                 lf.lfCharSet,
                 OUT_CHARACTER_PRECIS,
                 CLIP_CHARACTER_PRECIS,
                 DEFAULT_QUALITY,
                 DEFAULT_PITCH,
                 lf.lfFaceName);

    m_ColFont     = other.m_ColFont;
    m_hFontNumber = other.m_hFontNumber;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_Font::Create(LOGFONT* pLogFont, COLORREF col)
{
    m_ColFont     = col;
    m_hFontNumber = g_NoFontDefined;

    return BOOL(::CreateFont(pLogFont->lfHeight,
                             pLogFont->lfWidth,
                             pLogFont->lfEscapement,
                             pLogFont->lfOrientation,
                             pLogFont->lfWeight,
                             pLogFont->lfItalic,
                             pLogFont->lfUnderline,
                             pLogFont->lfStrikeOut,
                             pLogFont->lfCharSet,
                             OUT_CHARACTER_PRECIS,
                             CLIP_CHARACTER_PRECIS,
                             DEFAULT_QUALITY,
                             DEFAULT_PITCH,
                             pLogFont->lfFaceName));
}
//---------------------------------------------------------------------------
PSS_Font* PSS_Font::Clone() const
{
    return new PSS_Font(*this);
}
//---------------------------------------------------------------------------
void PSS_Font::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements$
        LOGFONT lf;
        GetObject(sizeof(LOGFONT), &lf);

        #ifndef _WIN32        
            ar << lf.lfFaceName;
        #else
            ar << CString(lf.lfFaceName);
        #endif
        ar << WORD(lf.lfHeight);
        ar << WORD(lf.lfWidth);
        ar << WORD(lf.lfEscapement);
        ar << WORD(lf.lfOrientation);
        ar << WORD(lf.lfWeight);
        ar << lf.lfItalic;
        ar << lf.lfUnderline;
        ar << lf.lfStrikeOut;
        ar << lf.lfCharSet;
        ar << m_ColFont;
        ar << m_hFontNumber;
    }
    else
    {
        CString faceName;
        ar >> faceName;

        WORD wValue;
        ar >> wValue;
        const short height = short(wValue);

        ar >> wValue;
        const short width = short(wValue);

        ar >> wValue;
        const short escape = short(wValue);

        ar >> wValue;
        const short orientation = short(wValue);

        ar >> wValue;
        const short weight = short(wValue);

        BYTE italic;
        BYTE under;
        BYTE strikeOut;
        BYTE charSet;

        ar >> italic;
        ar >> under;
        ar >> strikeOut;
        ar >> charSet;

        ::CreateFont(height,
                     width,
                     escape,
                     orientation,
                     height,
                     italic,
                     under,
                     strikeOut,
                     charSet,
                     OUT_CHARACTER_PRECIS,
                     CLIP_CHARACTER_PRECIS,
                     DEFAULT_QUALITY,
                     DEFAULT_PITCH,
                     faceName);

        ar >> m_ColFont;
        ar >> m_hFontNumber;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Font::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Font::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
