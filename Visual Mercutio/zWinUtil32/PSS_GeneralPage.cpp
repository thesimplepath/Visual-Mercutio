/****************************************************************************
 * ==> PSS_GeneralPage -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a general page                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_GeneralPage.h"

// processsoft
#include "zBaseLib\msgbox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GeneralPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_GeneralPage)
    ON_BN_CLICKED(IDC_RELOADLASTFILE, OnReloadLastFile)
    ON_BN_CLICKED(IDC_STARTUPOPENFILE, OnStartupOpenFile)
    ON_BN_CLICKED(IDC_SHOWWELCOME, OnShowWelcomeScreen)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GeneralPage
//---------------------------------------------------------------------------
PSS_GeneralPage::PSS_GeneralPage(PSS_ApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(PSS_GeneralPage::IDD, pApplicationOptions)
{}
//---------------------------------------------------------------------------
PSS_GeneralPage::PSS_GeneralPage(const PSS_GeneralPage& other) :
    PSS_GenericPropPage(PSS_GeneralPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_GeneralPage::~PSS_GeneralPage()
{}
//---------------------------------------------------------------------------
const PSS_GeneralPage& PSS_GeneralPage::operator = (const PSS_GeneralPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
    {
        UpdateData(TRUE);

        // get application options container
        PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

        // update application options
        appOpt.SetShowWelcomeScreen     (BOOL(m_BtnShowWelcome.GetCheck()));
        appOpt.SetMaximizeFormOnOpen    (BOOL(m_BtnMaximizeForm.GetCheck()));
        appOpt.SetScreenPos             (BOOL(m_BtnScreenPos.GetCheck()));
        appOpt.SetCreateOnStartup       (BOOL(m_BtnStartupOpenFile.GetCheck()));
        appOpt.SetOpenLastLoadedFile    (BOOL(m_BtnReloadLastFile.GetCheck()));
        appOpt.SetDontShowTaskList      (m_DontShowTaskList);
        appOpt.SetDontShowToolTip       (m_DontShowTips);
        appOpt.SetForceNetworkConnection(m_ForceNetwork);
    }
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_GeneralPage)
    DDX_Control(pDX, IDC_MAXIMIZE_FORMS,   m_BtnMaximizeForm);
    DDX_Control(pDX, IDC_SHOWWELCOME,      m_BtnShowWelcome);
    DDX_Control(pDX, IDC_RELOADLASTFILE,   m_BtnReloadLastFile);
    DDX_Control(pDX, IDC_STARTUPOPENFILE,  m_BtnStartupOpenFile);
    DDX_Control(pDX, IDC_SCREENPOS,        m_BtnScreenPos);
    DDX_Check  (pDX, IDC_DONTSHOWTASKLIST, m_DontShowTaskList);
    DDX_Check  (pDX, IDC_DONTSHOWTIPS,     m_DontShowTips);
    DDX_Check  (pDX, IDC_FORCENETWORK,     m_ForceNetwork);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_GeneralPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    // get application options container
    PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

    m_DontShowTaskList = appOpt.GetDontShowTaskList();
    m_DontShowTips     = appOpt.GetDontShowToolTip();
    m_ForceNetwork     = appOpt.GetForceNetworkConnection();

    CDialog::OnInitDialog();

    m_BtnShowWelcome.SetCheck    (INT(appOpt.GetShowWelcomeScreen()));
    m_BtnStartupOpenFile.SetCheck(INT(appOpt.GetCreateOnStartup()));
    m_BtnScreenPos.SetCheck      (INT(appOpt.GetScreenPos()));
    m_BtnMaximizeForm.SetCheck   (INT(appOpt.GetMaximizeFormOnOpen()));
    m_BtnReloadLastFile.SetCheck (INT(appOpt.GetOpenLastLoadedFile()));

    OnShowWelcomeScreen();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::OnShowWelcomeScreen()
{
    m_BtnReloadLastFile.EnableWindow(!m_BtnShowWelcome.GetCheck());
    m_BtnStartupOpenFile.EnableWindow(!m_BtnShowWelcome.GetCheck());
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::OnReloadLastFile()
{
    if (m_BtnReloadLastFile.GetCheck())
        m_BtnStartupOpenFile.SetCheck(FALSE);
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::OnStartupOpenFile()
{
    if (m_BtnStartupOpenFile.GetCheck())
        m_BtnReloadLastFile.SetCheck(FALSE);
}
//---------------------------------------------------------------------------
void PSS_GeneralPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
