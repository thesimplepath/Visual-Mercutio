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
#include "ViewPgR.h"
//## begin module%334FC463032D.declarations preserve=no
//## end module%334FC463032D.declarations

//## begin module%334FC463032D.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIViewPageReduced, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZIViewPageReduced)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%334FC463032D.additionalDeclarations


// Class ZIViewPageReduced 

ZIViewPageReduced::ZIViewPageReduced (ZAApplicationOption* pApplicationOptions)
  //## begin ZIViewPageReduced::ZIViewPageReduced%923121235.hasinit preserve=no
  //## end ZIViewPageReduced::ZIViewPageReduced%923121235.hasinit
  //## begin ZIViewPageReduced::ZIViewPageReduced%923121235.initialization preserve=yes
    : ZIGenericPropPage(ZIViewPageReduced::IDD, pApplicationOptions)
  //## end ZIViewPageReduced::ZIViewPageReduced%923121235.initialization
{
  //## begin ZIViewPageReduced::ZIViewPageReduced%923121235.body preserve=yes
  //## end ZIViewPageReduced::ZIViewPageReduced%923121235.body
}


ZIViewPageReduced::~ZIViewPageReduced()
{
  //## begin ZIViewPageReduced::~ZIViewPageReduced%.body preserve=yes
  //## end ZIViewPageReduced::~ZIViewPageReduced%.body
}



//## Other Operations (implementation)
void ZIViewPageReduced::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZIViewPageReduced::DoDataExchange%827992043.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIViewPageReduced)
    DDX_Check(pDX, IDC_CALCULATEDFIELD, m_bCalculatedField);
    DDX_Check(pDX, IDC_SHOWHIDDENFIELDS, m_bShowHiddenField);
    DDX_Check(pDX, IDC_ANIMATION, m_bAnimationShow);
    //}}AFX_DATA_MAP
  //## end ZIViewPageReduced::DoDataExchange%827992043.body
}

void ZIViewPageReduced::SaveValuesToObject ()
{
  //## begin ZIViewPageReduced::SaveValuesToObject%923121236.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );

    ((ZAApplicationOption&)GetObject()).SetbAnimationShow( m_bAnimationShow );
    ((ZAApplicationOption&)GetObject()).SetbCalculateFieldShow( m_bCalculatedField );
    ((ZAApplicationOption&)GetObject()).SetbShowHiddenField( m_bShowHiddenField );
  //## end ZIViewPageReduced::SaveValuesToObject%923121236.body
}

// Additional Declarations
  //## begin ZIViewPageReduced%334FC4610072.declarations preserve=yes
BOOL ZIViewPageReduced::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();

    m_bCalculatedField = ((ZAApplicationOption&)GetObject()).GetbCalculateFieldShow();
    m_bShowHiddenField = ((ZAApplicationOption&)GetObject()).GetbShowHiddenField();
    m_bAnimationShow = ((ZAApplicationOption&)GetObject()).GetbAnimationShow();
      
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZIViewPageReduced::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}


  //## end ZIViewPageReduced%334FC4610072.declarations
//## begin module%334FC463032D.epilog preserve=yes
//## end module%334FC463032D.epilog
