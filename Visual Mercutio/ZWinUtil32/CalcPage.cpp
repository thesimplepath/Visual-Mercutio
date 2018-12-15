//## begin module%334FC463032A.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC463032A.cm

//## begin module%334FC463032A.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC463032A.cp

//## Module: CalcPage%334FC463032A; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\CalcPage.cpp

//## begin module%334FC463032A.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC463032A.additionalIncludes

//## begin module%334FC463032A.includes preserve=yes
//## end module%334FC463032A.includes

// CalcPage
#include "CalcPage.h"
//## begin module%334FC463032A.declarations preserve=no
//## end module%334FC463032A.declarations

//## begin module%334FC463032A.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZICalculationPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZICalculationPage)
    ON_BN_CLICKED(IDC_AUTOCALCULATION, OnAutocalculation)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%334FC463032A.additionalDeclarations


// Class ZICalculationPage 

ZICalculationPage::ZICalculationPage (ZAApplicationOption* pApplicationOptions)
  //## begin ZICalculationPage::ZICalculationPage%923121237.hasinit preserve=no
  //## end ZICalculationPage::ZICalculationPage%923121237.hasinit
  //## begin ZICalculationPage::ZICalculationPage%923121237.initialization preserve=yes
    : ZIGenericPropPage(ZICalculationPage::IDD, pApplicationOptions)
  //## end ZICalculationPage::ZICalculationPage%923121237.initialization
{
  //## begin ZICalculationPage::ZICalculationPage%923121237.body preserve=yes
  //## end ZICalculationPage::ZICalculationPage%923121237.body
}


ZICalculationPage::~ZICalculationPage()
{
  //## begin ZICalculationPage::~ZICalculationPage%.body preserve=yes
  //## end ZICalculationPage::~ZICalculationPage%.body
}



//## Other Operations (implementation)
void ZICalculationPage::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZICalculationPage::DoDataExchange%827992043.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZICalculationPage)
    DDX_Check(pDX, IDC_AUTOCALCULATION, m_bAutoCalculate);
    //}}AFX_DATA_MAP
  //## end ZICalculationPage::DoDataExchange%827992043.body
}

void ZICalculationPage::SaveValuesToObject ()
{
  //## begin ZICalculationPage::SaveValuesToObject%923121238.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );

    ((ZAApplicationOption&)GetObject()).SetbAutoCalculate( GetAutoCalculate() );
  //## end ZICalculationPage::SaveValuesToObject%923121238.body
}

// Additional Declarations
  //## begin ZICalculationPage%334FC4610046.declarations preserve=yes

BOOL ZICalculationPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();
      
    m_bAutoCalculate = ((ZAApplicationOption&)GetObject()).GetbAutoCalculate();

    CDialog::OnInitDialog();

    return TRUE;  // return TRUE  unless you set the focus to a control
}




void ZICalculationPage::OnAutocalculation()
{
    UpdateData();
}

void ZICalculationPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}

  //## end ZICalculationPage%334FC4610046.declarations
//## begin module%334FC463032A.epilog preserve=yes
//## end module%334FC463032A.epilog
