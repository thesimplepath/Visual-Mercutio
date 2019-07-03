//**************************************************************************
// FontCombo.cpp : implementation file
//

#include "stdafx.h"
#include "FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_INITFONTS          (WM_USER + 123)
//I chose 123 cos nobody might use the same exact number.. I can improve this by use RegisterWindowMessage..

///////////////////////////////////////////////////////////////////////////
//
// ZCFontComboBox

//Initial values of the text and highlight stuff

ZCFontComboBox::ZCFontComboBox()
{
     m_enStyle = FONTS;
     m_clrHilight = GetSysColor (COLOR_HIGHLIGHT);
     m_clrNormalText = GetSysColor (COLOR_WINDOWTEXT);
     m_clrHilightText = GetSysColor (COLOR_HIGHLIGHTTEXT);
     m_clrBkgnd = GetSysColor (COLOR_WINDOW);
     m_bInitOver = FALSE;

}


ZCFontComboBox::ZCFontComboBox (STYLE enStyle)
{
     m_enStyle = enStyle;
     m_clrHilight = GetSysColor (COLOR_HIGHLIGHT);
     m_clrNormalText = GetSysColor (COLOR_WINDOWTEXT);
     m_clrHilightText = GetSysColor (COLOR_HIGHLIGHTTEXT);
     m_clrBkgnd = GetSysColor (COLOR_WINDOW);
     m_bInitOver =FALSE;
}

ZCFontComboBox::~ZCFontComboBox()
{
}


BOOL ZCFontComboBox::SetCurrentFont( LPLOGFONT lplf )
{
    if (lplf)
        return SetCurrentFont( lplf->lfFaceName );
    return FALSE;
}

BOOL ZCFontComboBox::SetCurrentFont( LPCTSTR lpszFontName )
{
    int nCount = GetCount();
    for (int i = 0; i < nCount; i++)
    {
       if (strcmp(((LOGFONT*)GetItemData(i))->lfFaceName, lpszFontName) == 0)
       {
           SetCurSel( i );
           return TRUE;
       }
    }
    return FALSE;
}

BEGIN_MESSAGE_MAP(ZCFontComboBox, CComboBox)
     //{{AFX_MSG_MAP(ZCFontComboBox)
     ON_WM_CREATE()
     ON_WM_DESTROY()
     //}}AFX_MSG_MAP
     ON_MESSAGE (WM_INITFONTS,OnInitFonts)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
//
// ZCFontComboBox message handlers


void ZCFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
     //I might want to add something else someday
     switch (m_enStyle)
     {
     case FONTS:
          DrawFont(lpDrawItemStruct);
          break;
     }
}


//I dont need the MeasureItem to do anything. Whatever the system says, it stays

void ZCFontComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
}

void ZCFontComboBox::DrawFont(LPDRAWITEMSTRUCT lpDIS)
{
     CDC* pDC = CDC::FromHandle(lpDIS->hDC);
     CRect rect;

     TRACE0 ("In Draw Font\n");

    // draw the colored rectangle portion
     rect.CopyRect(&lpDIS->rcItem);

     pDC->SetBkMode( TRANSPARENT );

     if (lpDIS->itemState & ODS_SELECTED)
     {
          pDC->FillSolidRect (rect,m_clrHilight);
          pDC->SetTextColor (m_clrHilightText);
     }
     else
     {
          pDC->FillSolidRect (rect,m_clrBkgnd);
          pDC->SetTextColor (m_clrNormalText);
     }

     if ((int)(lpDIS->itemID) < 0) // Well its negetive so no need to draw text
     {
     }
     else
     {
          CString strText;
          GetLBText (lpDIS->itemID,strText);
          CFont newFont;
          CFont *pOldFont;

          ((LOGFONT*)lpDIS->itemData)->lfHeight = 90; //9 point size
          ((LOGFONT*)lpDIS->itemData)->lfWidth = 0;
          newFont.CreatePointFontIndirect ((LOGFONT*)lpDIS->itemData);
          pOldFont = pDC->SelectObject (&newFont);
          pDC->DrawText(strText, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
          pDC->SelectObject (pOldFont);
          newFont.DeleteObject ();
     }
}

void ZCFontComboBox::InitFonts ()
{
     CDC *pDC = GetDC ();
     ResetContent (); //Delete whatever is there
     EnumFonts (pDC->GetSafeHdc(),NULL,(FONTENUMPROC) EnumFontProc,(LPARAM)this);//Enumerate
     m_bInitOver = TRUE;
}

BOOL CALLBACK ZCFontComboBox::EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
     if (dwType == TRUETYPE_FONTTYPE) //Add only TTF fellows, If you want you can change it to check for others
     {
          int index = ((ZCFontComboBox *) lpData)->AddString(lplf->lfFaceName);
          LPLOGFONT lpLF;
          lpLF = new LOGFONT;
          CopyMemory ((PVOID) lpLF,(CONST VOID *) lplf,sizeof (LOGFONT));
          ((ZCFontComboBox *) lpData)->SetItemData (index,(DWORD) lpLF);
     }
     return TRUE;
}

int ZCFontComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
     if (CComboBox::OnCreate(lpCreateStruct) == -1)
          return -1;

     // TODO: Add your specialized creation code here
     if (m_enStyle == FONTS)
     {
          PostMessage (WM_INITFONTS,0,0);
     }
     return 0;
}

long ZCFontComboBox::OnInitFonts (WPARAM, LPARAM)
{
     InitFonts ();
     return 0L;
}


void ZCFontComboBox::OnDestroy()
{

     if (m_enStyle == FONTS)
     {
          int nCount;
          nCount = GetCount ();
          for (int i = 0; i <  nCount; i++)
          {
               delete ((LOGFONT*)GetItemData (i)); //delete the LOGFONTS actually created..
          }
     }
     // TODO: Add your message handler code here
     CComboBox::OnDestroy();
}

void ZCFontComboBox::FillFonts ()
{
     m_enStyle = FONTS;
     PostMessage (WM_INITFONTS,0,0); //Process in one place
}

int  ZCFontComboBox::GetSelFont (LOGFONT& lf)
{
     int index = GetCurSel ();
     if (index == LB_ERR)
          return LB_ERR;
     LPLOGFONT lpLF = (LPLOGFONT) GetItemData (index);
     CopyMemory ((PVOID)&lf, (CONST VOID *) lpLF, sizeof (LOGFONT));
     return index; //return the index here.. Maybe the user needs it:-)
}

void ZCFontComboBox::PreSubclassWindow()
{
     // TODO: Add your specialized code here and/or call the base class
     //Tried to do what Roger Onslow did for the button.. Did not work..?? Any R&D guys around :-)
}
