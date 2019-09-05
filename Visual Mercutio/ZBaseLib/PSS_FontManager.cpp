/****************************************************************************
 * ==> PSS_FontManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font manager                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FontManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FontManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FontManager
//---------------------------------------------------------------------------
PSS_FontManager::PSS_FontManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_FontManager::PSS_FontManager(const PSS_FontManager& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FontManager::~PSS_FontManager()
{
    const int fontCount = m_FontArray.GetSize();

    for (int i = 0; i < fontCount; ++i)
        delete m_FontArray[i];

    m_FontArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_FontManager & PSS_FontManager::operator = (const PSS_FontManager& other)
{
    if (other.m_FontArray.GetSize() <= 0)
        return *this;

    const int fontCount = other.m_FontArray.GetSize();

    m_FontArray.SetSize(fontCount);

    for (int i = 0; i < fontCount; ++i)
        if (other.m_FontArray[i])
            m_FontArray.InsertAt(i, static_cast<PSS_Font*>(other.m_FontArray[i])->Clone());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_FontManager::RemoveFont(PSS_Font::FontHandle hFont)
{
    const int fontCount = m_FontArray.GetSize();

    for (int i = 0; i < fontCount; ++i)
    {
        PSS_Font* pCurFont = static_cast<PSS_Font*>(m_FontArray[i]);

        if (pCurFont && pCurFont->GetFontHandle() == hFont)
        {
            // free memory at location
            delete m_FontArray[i];

            // remove the element from the array
            m_FontArray.RemoveAt(i);

            return TRUE;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_Font::FontHandle PSS_FontManager::SearchFont(LOGFONT* pLogFont, COLORREF color)
{
    const int fontCount = m_FontArray.GetSize();
    LOGFONT   lf;

    for (int i = 0; i < fontCount; ++i)
    {
        PSS_Font* pCurFont = static_cast<PSS_Font*>(m_FontArray[i]);

        if (!pCurFont)
            continue;

        // check the color
        if (pCurFont->GetFontColor() != color)
            continue;

        // check each LOGFONT element
        pCurFont->GetObject(sizeof(LOGFONT), &lf);

        if (pLogFont                                                             &&
            std::strcmp(pLogFont->lfFaceName, lf.lfFaceName) == 0                &&
            pLogFont->lfHeight                               == lf.lfHeight      &&
            pLogFont->lfWidth                                == lf.lfWidth       &&
            pLogFont->lfEscapement                           == lf.lfEscapement  &&
            pLogFont->lfOrientation                          == lf.lfOrientation &&
            pLogFont->lfWeight                               == lf.lfWeight      &&
            pLogFont->lfItalic                               == lf.lfItalic      &&
            pLogFont->lfUnderline                            == lf.lfUnderline   &&
            pLogFont->lfStrikeOut                            == lf.lfStrikeOut   &&
            pLogFont->lfCharSet                              == lf.lfCharSet)
            return pCurFont->GetFontHandle();
    }

    return g_NoFontDefined;
}
//---------------------------------------------------------------------------
PSS_Font::FontHandle PSS_FontManager::SearchFont(PSS_Font* pFont)
{
    const int fontCount = m_FontArray.GetSize();

    for (int i = 0; i < fontCount; ++i)
    {
        PSS_Font* pCurFont = static_cast<PSS_Font*>(m_FontArray[i]);

        if (pCurFont && pCurFont == pFont)
            return pCurFont->GetFontHandle();
    }

    return g_NoFontDefined;
}
//---------------------------------------------------------------------------
PSS_Font::FontHandle PSS_FontManager::RotateFont(PSS_Font::FontHandle hFont, int angle)
{
    LOGFONT   lf;
    PSS_Font* pInitialFont = GetFont(hFont);

    if (!pInitialFont)
        return g_NoFontDefined;

    pInitialFont->GetObject(sizeof(LOGFONT), &lf);

    // set the new angle
    lf.lfEscapement = angle;

    PSS_Font::FontHandle hRetFont;

    // return the specific assigned font
    if ((hRetFont = SearchFont(&lf, pInitialFont->GetFontColor())) == g_NoFontDefined)
    {
        std::unique_ptr<PSS_Font> pFont(new PSS_Font());
        pFont->Create(&lf, pInitialFont->GetFontColor());
        hRetFont = AddFont(pFont.get());
        pFont.release();
    }

    return hRetFont;
}
//---------------------------------------------------------------------------
void PSS_FontManager::Serialize(CArchive& ar)
{
    m_FontArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FontManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FontManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
