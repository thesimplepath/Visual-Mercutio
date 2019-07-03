//## begin module%334FC46302C0.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302C0.cm

//## begin module%334FC46302C0.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302C0.cp

//## Module: GenPage%334FC46302C0; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\GenPage.cpp

//## begin module%334FC46302C0.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302C0.additionalIncludes

//## begin module%334FC46302C0.includes preserve=yes
#include "zBaseLib\msgbox.h"
#ifndef _WIN32
    #include "Opendird.h"
#endif
#ifdef _WIN32
    #include "Opendird32.h"
#endif
//## end module%334FC46302C0.includes

// GenPage
#include "GenPage.h"
//## begin module%334FC46302C0.declarations preserve=no
//## end module%334FC46302C0.declarations

//## begin module%334FC46302C0.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIGeneralPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(ZIGeneralPage)
    ON_BN_CLICKED(IDC_RELOADLASTFILE, OnReloadLastFile)
    ON_BN_CLICKED(IDC_STARTUPOPENFILE, OnStartupOpenFile)
    ON_BN_CLICKED(IDC_SHOWWELCOME, OnShowWelcomeScreen)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%334FC46302C0.additionalDeclarations


// Class ZIGeneralPage 

ZIGeneralPage::ZIGeneralPage (ZAApplicationOption* pApplicationOptions)
  //## begin ZIGeneralPage::ZIGeneralPage%923121234.hasinit preserve=no
  //## end ZIGeneralPage::ZIGeneralPage%923121234.hasinit
  //## begin ZIGeneralPage::ZIGeneralPage%923121234.initialization preserve=yes
    : ZIGenericPropPage(ZIGeneralPage::IDD, pApplicationOptions)
  //## end ZIGeneralPage::ZIGeneralPage%923121234.initialization
{
  //## begin ZIGeneralPage::ZIGeneralPage%923121234.body preserve=yes
  //## end ZIGeneralPage::ZIGeneralPage%923121234.body
}


ZIGeneralPage::~ZIGeneralPage()
{
  //## begin ZIGeneralPage::~ZIGeneralPage%.body preserve=yes
  //## end ZIGeneralPage::~ZIGeneralPage%.body
}



//## Other Operations (implementation)
void ZIGeneralPage::DoDataExchange (CDataExchange* pDX)
{
  //## begin ZIGeneralPage::DoDataExchange%827992043.body preserve=yes
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIGeneralPage)
    DDX_Control(pDX, IDC_MAXIMIZE_FORMS, m_btnMaximizeForm);
    DDX_Control(pDX, IDC_SHOWWELCOME, m_btnShowWelcome);
    DDX_Control(pDX, IDC_RELOADLASTFILE, m_btnReloadLastFile);
    DDX_Control(pDX, IDC_STARTUPOPENFILE, m_btnStartupOpenFile);
    DDX_Control(pDX, IDC_SCREENPOS, m_btnScreenPos);
    DDX_Check(pDX, IDC_DONTSHOWTASKLIST, m_DontShowTaskList);
    DDX_Check(pDX, IDC_DONTSHOWTIPS, m_DontShowTips);
    DDX_Check(pDX, IDC_FORCENETWORK, m_ForceNetwork);
    //}}AFX_DATA_MAP
  //## end ZIGeneralPage::DoDataExchange%827992043.body
}

void ZIGeneralPage::SaveValuesToObject ()
{
  //## begin ZIGeneralPage::SaveValuesToObject%923121226.body preserve=yes
    if (::IsWindow(GetSafeHwnd()))
    {
        UpdateData( TRUE );

        ((ZAApplicationOption&)GetObject()).SetShowWelcomeScreen( (BOOL)m_btnShowWelcome.GetCheck() );
        ((ZAApplicationOption&)GetObject()).SetMaximizeFormOnOpen( (BOOL)m_btnMaximizeForm.GetCheck() );

        ((ZAApplicationOption&)GetObject()).SetbScreenPos( (BOOL)m_btnScreenPos.GetCheck() );

        ((ZAApplicationOption&)GetObject()).SetbCreateOnStartup( (BOOL)m_btnStartupOpenFile.GetCheck() );
        ((ZAApplicationOption&)GetObject()).SetbOpenLastLoadedFile( (BOOL)m_btnReloadLastFile.GetCheck() );

        ((ZAApplicationOption&)GetObject()).SetDontShowTaskList( m_DontShowTaskList );
        ((ZAApplicationOption&)GetObject()).SetDontShowToolTip( m_DontShowTips );
        ((ZAApplicationOption&)GetObject()).SetForceNetworkConnection( m_ForceNetwork );

    }
  //## end ZIGeneralPage::SaveValuesToObject%923121226.body
}

// Additional Declarations
  //## begin ZIGeneralPage%334FC461003C.declarations preserve=yes

BOOL ZIGeneralPage::OnInitDialog()
{
    // Set initialisation flag
      SetInitialized();

    m_DontShowTaskList = ((ZAApplicationOption&)GetObject()).GetDontShowTaskList();
    m_DontShowTips = ((ZAApplicationOption&)GetObject()).GetDontShowToolTip();
    m_ForceNetwork = ((ZAApplicationOption&)GetObject()).GetForceNetworkConnection();


    CDialog::OnInitDialog();
    m_btnShowWelcome.SetCheck( (INT) ((ZAApplicationOption&)GetObject()).GetShowWelcomeScreen() );
    m_btnStartupOpenFile.SetCheck( (INT) ((ZAApplicationOption&)GetObject()).GetbCreateOnStartup() );
    m_btnScreenPos.SetCheck( (INT) ((ZAApplicationOption&)GetObject()).GetbScreenPos() );
    m_btnMaximizeForm.SetCheck( (INT) ((ZAApplicationOption&)GetObject()).GetMaximizeFormOnOpen() );
    m_btnReloadLastFile.SetCheck( (INT) ((ZAApplicationOption&)GetObject()).GetbOpenLastLoadedFile() );

    //    OnSavesettings();    // Set state of items
    OnShowWelcomeScreen();    // Set state of items
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}


void ZIGeneralPage::OnShowWelcomeScreen()
{
    m_btnReloadLastFile.EnableWindow( !m_btnShowWelcome.GetCheck() );
    m_btnStartupOpenFile.EnableWindow( !m_btnShowWelcome.GetCheck() );
}

void ZIGeneralPage::OnReloadLastFile()
{
    if (m_btnReloadLastFile.GetCheck())
        m_btnStartupOpenFile.SetCheck( FALSE );
}

void ZIGeneralPage::OnStartupOpenFile()
{
    if (m_btnStartupOpenFile.GetCheck())
        m_btnReloadLastFile.SetCheck( FALSE );
}

void ZIGeneralPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}

  //## end ZIGeneralPage%334FC461003C.declarations
//## begin module%334FC46302C0.epilog preserve=yes
//## end module%334FC46302C0.epilog
