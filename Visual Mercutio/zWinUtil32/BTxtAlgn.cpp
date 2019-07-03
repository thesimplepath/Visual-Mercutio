//## begin module%334FC46400B6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46400B6.cm

//## begin module%334FC46400B6.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46400B6.cp

//## Module: BTxtAlgn%334FC46400B6; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\BTxtAlgn.cpp

//## begin module%334FC46400B6.additionalIncludes preserve=no
//## end module%334FC46400B6.additionalIncludes

//## begin module%334FC46400B6.includes preserve=yes
#include <StdAfx.h>
//## end module%334FC46400B6.includes

// BTxtAlgn
#include "BTxtAlgn.h"
//## begin module%334FC46400B6.declarations preserve=no
//## end module%334FC46400B6.declarations

//## begin module%334FC46400B6.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(ZITextAlignButton, CBitmapButton)


BEGIN_MESSAGE_MAP(ZITextAlignButton, CBitmapButton)
    //{{AFX_MSG_MAP(ZITextAlignButton)
    ON_WM_DRAWITEM()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%334FC46400B6.additionalDeclarations


// Class ZITextAlignButton 






ZITextAlignButton::ZITextAlignButton (const CString sText, UINT nStyle, BOOL bCheck, CWnd* pParentWnd, UINT nID)
  //## begin ZITextAlignButton::ZITextAlignButton%833240214.hasinit preserve=no
  //## end ZITextAlignButton::ZITextAlignButton%833240214.hasinit
  //## begin ZITextAlignButton::ZITextAlignButton%833240214.initialization preserve=yes
  : m_sText(sText), m_nStyle(nStyle), m_bCheck(bCheck),
      m_pParentWnd(pParentWnd), m_nID(nID)
  //## end ZITextAlignButton::ZITextAlignButton%833240214.initialization
{
  //## begin ZITextAlignButton::ZITextAlignButton%833240214.body preserve=yes
      if (m_pParentWnd)
          SubclassDlgItem( m_nID, m_pParentWnd );
//          CButton::Create( m_sText, BS_OWNERDRAW, CRect(0,0,0,0), m_pParentWnd, m_nID );
  //## end ZITextAlignButton::ZITextAlignButton%833240214.body
}


ZITextAlignButton::~ZITextAlignButton()
{
  //## begin ZITextAlignButton::~ZITextAlignButton%.body preserve=yes
  //## end ZITextAlignButton::~ZITextAlignButton%.body
}



//## Other Operations (implementation)
void ZITextAlignButton::Create (const CString sText, UINT nStyle, BOOL bCheck, CWnd* pParentWnd, UINT nID)
{
  //## begin ZITextAlignButton::Create%833240214.body preserve=yes
      m_sText = sText;
      m_nStyle = nStyle;
      m_bCheck = bCheck;
      m_pParentWnd = pParentWnd;
      m_nID = nID;
    SubclassDlgItem( m_nID, m_pParentWnd );
  //## end ZITextAlignButton::Create%833240214.body
}

void ZITextAlignButton::DrawItem (LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  //## begin ZITextAlignButton::DrawItem%833240215.body preserve=yes
    CPen*    OldPen;
    CPen    NewPen( PS_SOLID, 1, defCOLOR_BLACK );
    CPen    ShadowPen( PS_SOLID, 1, defCOLOR_WHITE );
    CBrush*    OldBrush;
    CBrush    NewBrush;
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    ASSERT(pDC != NULL);

    CRect    rect;
    GetClientRect( &rect );
    
    if (GetCheck())
        NewBrush.CreateSolidBrush( defCOLOR_BLUE ); 
    else
        NewBrush.CreateSolidBrush( defCOLOR_LTLTGRAY ); 
        
    OldPen = pDC->SelectObject( &NewPen );
    OldBrush = pDC->SelectObject( &NewBrush );
    pDC->Rectangle( rect );
    pDC->SelectObject( &ShadowPen );
    pDC->MoveTo( rect.left-1, rect.bottom-1);
    pDC->LineTo( rect.right, rect.bottom-1);
    pDC->MoveTo( rect.right-1, rect.top-1);
    pDC->LineTo( rect.right-1, rect.bottom);
    pDC->SetBkMode( TRANSPARENT );
    rect.InflateRect( -2, -2 );
    pDC->SetTextColor( defCOLOR_WHITE );
    pDC->DrawText( m_sText, -1, &rect, m_nStyle );
    rect.OffsetRect( 2, 2 );
    pDC->SetTextColor( defCOLOR_BLACK );
    pDC->DrawText( m_sText, -1, &rect, m_nStyle );
    rect.OffsetRect( -1, -1 );
    pDC->SetTextColor( defCOLOR_GRAY );
    pDC->DrawText( m_sText, -1, &rect, m_nStyle );
    pDC->SelectObject( OldPen );
    pDC->SelectObject( OldBrush );
  //## end ZITextAlignButton::DrawItem%833240215.body
}

// Additional Declarations
  //## begin ZITextAlignButton%334FC46300FB.declarations preserve=yes
  //## end ZITextAlignButton%334FC46300FB.declarations

//## begin module%334FC46400B6.epilog preserve=yes
//## end module%334FC46400B6.epilog
