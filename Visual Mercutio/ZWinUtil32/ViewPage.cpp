//## begin module%334FC463032D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC463032D.cm

//## begin module%334FC463032D.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC463032D.cp

//## Module: ViewPage%334FC463032D; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ViewPage.cpp

//## begin module%334FC463032D.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC463032D.additionalIncludes

//## begin module%334FC463032D.includes preserve=yes
//## end module%334FC463032D.includes

// ViewPage
#include "ViewPage.h"
//## begin module%334FC463032D.declarations preserve=no
//## end module%334FC463032D.declarations

//## begin module%334FC463032D.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIViewPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZIViewPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%334FC463032D.additionalDeclarations


// Class ZIViewPage 

ZIViewPage::ZIViewPage (ZAApplicationOption* pApplicationOptions)
  //## begin ZIViewPage::ZIViewPage%923121235.hasinit preserve=no
  //## end ZIViewPage::ZIViewPage%923121235.hasinit
  //## begin ZIViewPage::ZIViewPage%923121235.initialization preserve=yes
    : ZIGenericPropPage(ZIViewPage::IDD, pApplicationOptions)
  //## end ZIViewPage::ZIViewPage%923121235.initialization
{
  //## begin ZIViewPage::ZIViewPage%923121235.body preserve=yes
  //## end ZIViewPage::ZIViewPage%923121235.body
}


ZIViewPage::~ZIViewPage()
{
  //## begin ZIViewPage::~ZIViewPage%.body preserve=yes
  //## end ZIViewPage::~ZIViewPage%.body
}



//## Other Operations (implementation)
void ZIViewPage::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZIViewPage::DoDataExchange%827992043.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIViewPage)
    DDX_Check(pDX, IDC_CALCULATEDFIELD, m_bCalculatedField);
    DDX_Check(pDX, IDC_SHOWHIDDENFIELDS, m_bShowHiddenField);
    DDX_Check(pDX, IDC_ANIMATION, m_bAnimationShow);
    DDX_Check(pDX, IDC_SHOWBOUNDSRECT, m_bShowBoundsRect);
    DDX_Check(pDX, IDC_AUTOCREATEFIELDNAME, m_AutomaticCreateFieldName);
    //}}AFX_DATA_MAP
  //## end ZIViewPage::DoDataExchange%827992043.body
}

void ZIViewPage::SaveValuesToObject ()
{
  //## begin ZIViewPage::SaveValuesToObject%923121236.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );

    ((ZAApplicationOption&)GetObject()).SetbAnimationShow( m_bAnimationShow );
    ((ZAApplicationOption&)GetObject()).SetbCalculateFieldShow( m_bCalculatedField );
    ((ZAApplicationOption&)GetObject()).SetbShowHiddenField( m_bShowHiddenField );
    ((ZAApplicationOption&)GetObject()).SetbShowBoundsRect( m_bShowBoundsRect );
    ((ZAApplicationOption&)GetObject()).SetAutomaticFieldNameCreation( m_AutomaticCreateFieldName );
  //## end ZIViewPage::SaveValuesToObject%923121236.body
}

// Additional Declarations
  //## begin ZIViewPage%334FC4610072.declarations preserve=yes
BOOL ZIViewPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();

    m_bCalculatedField = ((ZAApplicationOption&)GetObject()).GetbCalculateFieldShow();
    m_bShowHiddenField = ((ZAApplicationOption&)GetObject()).GetbShowHiddenField();
    m_bAnimationShow = ((ZAApplicationOption&)GetObject()).GetbAnimationShow();
    m_bShowBoundsRect = ((ZAApplicationOption&)GetObject()).GetbShowBoundsRect();
    m_AutomaticCreateFieldName = ((ZAApplicationOption&)GetObject()).GetAutomaticFieldNameCreation();
      
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZIViewPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}

  //## end ZIViewPage%334FC4610072.declarations
//## begin module%334FC463032D.epilog preserve=yes
//## end module%334FC463032D.epilog
