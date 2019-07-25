/****************************************************************************
 * ==> PSS_FontComboBox ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font combo box                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FontComboBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define WM_INITFONTS (WM_USER + 123)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FontComboBox, CComboBox)
    //{{AFX_MSG_MAP(PSS_FontComboBox)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
    ON_MESSAGE(WM_INITFONTS, OnInitFonts)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FontComboBox
//---------------------------------------------------------------------------
PSS_FontComboBox::PSS_FontComboBox() :
    CComboBox(),
    m_Style(E_FS_Fonts),
    m_ClrHighlight(::GetSysColor(COLOR_HIGHLIGHT)),
    m_ClrNormalText(::GetSysColor(COLOR_WINDOWTEXT)),
    m_ClrHighlightText(::GetSysColor(COLOR_HIGHLIGHTTEXT)),
    m_ClrBkgnd(::GetSysColor(COLOR_WINDOW)),
    m_InitOver(FALSE)
{}
//---------------------------------------------------------------------------
PSS_FontComboBox::PSS_FontComboBox(EFontStyle style) :
    CComboBox(),
    m_Style(style),
    m_ClrHighlight(::GetSysColor(COLOR_HIGHLIGHT)),
    m_ClrNormalText(::GetSysColor(COLOR_WINDOWTEXT)),
    m_ClrHighlightText(::GetSysColor(COLOR_HIGHLIGHTTEXT)),
    m_ClrBkgnd(::GetSysColor(COLOR_WINDOW)),
    m_InitOver(FALSE)
{}
//---------------------------------------------------------------------------
PSS_FontComboBox::~PSS_FontComboBox()
{}
//---------------------------------------------------------------------------
BOOL PSS_FontComboBox::SetCurrentFont(LPLOGFONT pFont)
{
    if (pFont)
        return SetCurrentFont(pFont->lfFaceName);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FontComboBox::SetCurrentFont(LPCTSTR pFontName)
{
    const int count = GetCount();

    for (int i = 0; i < count; ++i)
       if (!std::strcmp(((LOGFONT*)GetItemData(i))->lfFaceName, pFontName))
       {
           SetCurSel(i);
           return TRUE;
       }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::FillFonts()
{
    m_Style = E_FS_Fonts;
    PostMessage(WM_INITFONTS, 0, 0);
}
//---------------------------------------------------------------------------
int PSS_FontComboBox::GetSelFont(LOGFONT& font)
{
    const int index = GetCurSel();

    if (index == LB_ERR)
        return LB_ERR;

    LPLOGFONT pLogFont = LPLOGFONT(GetItemData(index));
    CopyMemory((PVOID)&font, (CONST VOID*)pLogFont, sizeof(LOGFONT));

    // return the index here... Maybe the user needs it:-)
    return index;
}
//---------------------------------------------------------------------------
BOOL CALLBACK PSS_FontComboBox::EnumFontProc(LPLOGFONT pFont, LPTEXTMETRIC pTextMetric, DWORD type, LPARAM pData)
{
    // add only TTF fonts, change here if other fonts should also be supported
    if (type == TRUETYPE_FONTTYPE)
    {
        if (!pFont || !pData)
        {
            TRACE("EnumFontProc - Font and/or data are missing");
            return TRUE;
        }

        const int       index    = ((PSS_FontComboBox*)pData)->AddString(pFont->lfFaceName);
              LPLOGFONT pLogFont = NULL;

        try
        {
            pLogFont = new LOGFONT;
            CopyMemory(PVOID(pLogFont), (CONST VOID*)pFont, sizeof(LOGFONT));
            ((PSS_FontComboBox*)pData)->SetItemData(index, DWORD(pLogFont));
        }
        catch (...)
        {
            if (pLogFont)
                delete pLogFont;

            throw;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_FontComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CComboBox::OnCreate(lpCreateStruct) == -1)
        return -1;

    // todo -cFeature -oJean: Add specialized creation code here
    if (m_Style == E_FS_Fonts)
        PostMessage(WM_INITFONTS, 0, 0);

    return 0;
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::OnDestroy()
{
    if (m_Style == E_FS_Fonts)
    {
        const int count = GetCount();

        // delete the LOGFONTS actually created
        for (int i = 0; i < count; ++i)
            delete ((LOGFONT*)GetItemData(i));
    }

    // todo -cFeature -oJean: Add a message handler code here
    CComboBox::OnDestroy();
}
//---------------------------------------------------------------------------
long PSS_FontComboBox::OnInitFonts(WPARAM wParam, LPARAM lParam)
{
    InitFonts();
    return 0L;
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::PreSubclassWindow()
{
    // todo -cFeature -oJean: Add specialized code here and/or call the base class
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{}
//---------------------------------------------------------------------------
void PSS_FontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
     switch (m_Style)
     {
         case E_FS_Fonts:
              DrawFont(lpDrawItemStruct);
              break;
     }
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::DrawFont(LPDRAWITEMSTRUCT pDrawStruct)
{
    TRACE0("In Draw Font\n");

    CDC*  pDC = CDC::FromHandle(pDrawStruct->hDC);
    CRect rect;

    // draw the colored rectangle area
    rect.CopyRect(&pDrawStruct->rcItem);

    pDC->SetBkMode(TRANSPARENT);

    if (pDrawStruct->itemState & ODS_SELECTED)
    {
        pDC->FillSolidRect(rect, m_ClrHighlight);
        pDC->SetTextColor(m_ClrHighlightText);
    }
    else
    {
        pDC->FillSolidRect(rect, m_ClrBkgnd);
        pDC->SetTextColor(m_ClrNormalText);
    }

    // well its negetive so no need to draw text
    if (int(pDrawStruct->itemID) >= 0)
    {
        CString text;
        GetLBText(pDrawStruct->itemID, text);

        CFont  newFont;
        CFont *pOldFont;

        // 9 point size
        ((LOGFONT*)pDrawStruct->itemData)->lfHeight = 90;
        ((LOGFONT*)pDrawStruct->itemData)->lfWidth  = 0;
        newFont.CreatePointFontIndirect((LOGFONT*)pDrawStruct->itemData);

        pOldFont = pDC->SelectObject(&newFont);
        pDC->DrawText(text, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
        pDC->SelectObject(pOldFont);
        newFont.DeleteObject();
    }
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::InitFonts ()
{
     CDC* pDC = GetDC();

     // delete whatever is there
     ResetContent();

     // enumerate
     EnumFonts(pDC->GetSafeHdc(), NULL, FONTENUMPROC(EnumFontProc), LPARAM(this));

     m_InitOver = TRUE;
}
//---------------------------------------------------------------------------
