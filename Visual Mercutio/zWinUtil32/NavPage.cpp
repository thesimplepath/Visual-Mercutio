//## begin module%35B620A4013D.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35B620A4013D.cm

//## begin module%35B620A4013D.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%35B620A4013D.cp

//## Module: NavPage%35B620A4013D; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\NavPage.cpp

//## begin module%35B620A4013D.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%35B620A4013D.additionalIncludes

//## begin module%35B620A4013D.includes preserve=yes
//## end module%35B620A4013D.includes

// NavPage
#include "NavPage.h"
//## begin module%35B620A4013D.declarations preserve=no
//## end module%35B620A4013D.declarations

//## begin module%35B620A4013D.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZINavigationPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZINavigationPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%35B620A4013D.additionalDeclarations


// Class ZINavigationPage 

ZINavigationPage::ZINavigationPage (ZAApplicationOption* pApplicationOptions)
  //## begin ZINavigationPage::ZINavigationPage%923121243.hasinit preserve=no
  //## end ZINavigationPage::ZINavigationPage%923121243.hasinit
  //## begin ZINavigationPage::ZINavigationPage%923121243.initialization preserve=yes
    : ZIGenericPropPage(ZINavigationPage::IDD, pApplicationOptions)
  //## end ZINavigationPage::ZINavigationPage%923121243.initialization
{
  //## begin ZINavigationPage::ZINavigationPage%923121243.body preserve=yes
  //## end ZINavigationPage::ZINavigationPage%923121243.body
}


ZINavigationPage::~ZINavigationPage()
{
  //## begin ZINavigationPage::~ZINavigationPage%.body preserve=yes
  //## end ZINavigationPage::~ZINavigationPage%.body
}



//## Other Operations (implementation)
void ZINavigationPage::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZINavigationPage::DoDataExchange%901127513.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZINavigationPage)
    DDX_Check(pDX, IDC_GONEXTEDIT, m_GoNextEdit);
    //}}AFX_DATA_MAP
  //## end ZINavigationPage::DoDataExchange%901127513.body
}

void ZINavigationPage::SaveValuesToObject ()
{
  //## begin ZINavigationPage::SaveValuesToObject%923121244.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );
    ((ZAApplicationOption&)GetObject()).SetGoNextEdit( m_GoNextEdit );
  //## end ZINavigationPage::SaveValuesToObject%923121244.body
}

// Additional Declarations
  //## begin ZINavigationPage%35B61F1D02AD.declarations preserve=yes

BOOL ZINavigationPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();
      
    m_GoNextEdit = ((ZAApplicationOption&)GetObject()).GetGoNextEdit();
    CDialog::OnInitDialog();
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZINavigationPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}

  //## end ZINavigationPage%35B61F1D02AD.declarations
//## begin module%35B620A4013D.epilog preserve=yes
//## end module%35B620A4013D.epilog
