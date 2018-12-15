//## begin module%35B620C102CF.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35B620C102CF.cm

//## begin module%35B620C102CF.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%35B620C102CF.cp

//## Module: ExpPage%35B620C102CF; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\ExpPage.cpp

//## begin module%35B620C102CF.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%35B620C102CF.additionalIncludes

//## begin module%35B620C102CF.includes preserve=yes
// FileDlg
#include "zBaseLib\FileDlg.h"
#include "zBaseLib\Export.h"
//## end module%35B620C102CF.includes

// ExpPage
#include "ExpPage.h"
//## begin module%35B620C102CF.declarations preserve=no
//## end module%35B620C102CF.declarations

//## begin module%35B620C102CF.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIExportPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZIExportPage)
//    ON_BN_CLICKED(IDC_SELECT, OnSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%35B620C102CF.additionalDeclarations


// Class ZIExportPage 

ZIExportPage::ZIExportPage (ZAApplicationOption* pApplicationOptions)
  //## begin ZIExportPage::ZIExportPage%923121241.hasinit preserve=no
  //## end ZIExportPage::ZIExportPage%923121241.hasinit
  //## begin ZIExportPage::ZIExportPage%923121241.initialization preserve=yes
    : ZIGenericPropPage(ZIExportPage::IDD, pApplicationOptions)
  //## end ZIExportPage::ZIExportPage%923121241.initialization
{
  //## begin ZIExportPage::ZIExportPage%923121241.body preserve=yes
  //## end ZIExportPage::ZIExportPage%923121241.body
}


ZIExportPage::~ZIExportPage()
{
  //## begin ZIExportPage::~ZIExportPage%.body preserve=yes
  //## end ZIExportPage::~ZIExportPage%.body
}



//## Other Operations (implementation)
void ZIExportPage::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZIExportPage::DoDataExchange%901127512.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIExportPage)
//    DDX_Text(pDX, IDC_SVMFILE, m_SVMFile);
    DDX_Radio(pDX, IDC_PROPAGATION, m_Propagation);
    DDX_Text(pDX, IDC_SCHEMANAME, m_SchemaName);
    DDX_Check(pDX, IDC_EMPTYWHENZERO, m_EmptyWhenZero);
    //}}AFX_DATA_MAP
  //## end ZIExportPage::DoDataExchange%901127512.body
}

void ZIExportPage::SaveValuesToObject ()
{
  //## begin ZIExportPage::SaveValuesToObject%923121242.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
        UpdateData( TRUE );

//    ((ZAApplicationOption&)GetObject()).SetExportFilename( m_SVMFile );
    ((ZAApplicationOption&)GetObject()).SetExportSchemaName( m_SchemaName );
    ((ZAApplicationOption&)GetObject()).SetEmptyWhenZero( m_EmptyWhenZero );

    switch (m_Propagation)
    {
        case 0:
        {
            ((ZAApplicationOption&)GetObject()).SetExportPropagationMode( LocatePageOnly );
            break;
        }
        case 1:
        {
            ((ZAApplicationOption&)GetObject()).SetExportPropagationMode( LocateForwardPage );
            break;
        }
        case 2:
        {
            ((ZAApplicationOption&)GetObject()).SetExportPropagationMode( LocateAllPages );
            break;
        }
        default:
        {
            ((ZAApplicationOption&)GetObject()).SetExportPropagationMode( LocateForwardPage );
            break;
        }
    }
  //## end ZIExportPage::SaveValuesToObject%923121242.body
}

// Additional Declarations
  //## begin ZIExportPage%35B620390175.declarations preserve=yes

BOOL ZIExportPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();
      
//    m_SVMFile = ((ZAApplicationOption&)GetObject()).GetExportFilename();
    m_SchemaName = ((ZAApplicationOption&)GetObject()).GetExportSchemaName();
    m_EmptyWhenZero = ((ZAApplicationOption&)GetObject()).GetEmptyWhenZero();
    
    switch (((ZAApplicationOption&)GetObject()).GetExportPropagationMode())
    {
        case LocatePageOnly:
        {
            m_Propagation = 0;
            break;
        }
        case LocateForwardPage:
        {
            m_Propagation = 1;
            break;
        }
        case LocateAllPages:
        {
            m_Propagation = 2;
            break;
        }
        default:
        {
            m_Propagation = 1;
            break;
        }
    }
    
    CDialog::OnInitDialog();
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void ZIExportPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}

  //## end ZIExportPage%35B620390175.declarations
//## begin module%35B620C102CF.epilog preserve=yes
//## end module%35B620C102CF.epilog
