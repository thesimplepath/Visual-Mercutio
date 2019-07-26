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
BEGIN_MESSAGE_MAP(PSS_GeneralPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(PSS_GeneralPage)
    ON_BN_CLICKED(IDC_RELOADLASTFILE, OnReloadLastFile)
    ON_BN_CLICKED(IDC_STARTUPOPENFILE, OnStartupOpenFile)
    ON_BN_CLICKED(IDC_SHOWWELCOME, OnShowWelcomeScreen)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GeneralPage
//---------------------------------------------------------------------------
PSS_GeneralPage::PSS_GeneralPage(ZAApplicationOption* pApplicationOptions) :
    ZIGenericPropPage(PSS_GeneralPage::IDD, pApplicationOptions)
{}
//---------------------------------------------------------------------------
PSS_GeneralPage::PSS_GeneralPage(const PSS_GeneralPage& other) :
    ZIGenericPropPage(PSS_GeneralPage::IDD, NULL)
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

        ((ZAApplicationOption&)GetObject()).SetShowWelcomeScreen(BOOL(m_BtnShowWelcome.GetCheck()));
        ((ZAApplicationOption&)GetObject()).SetMaximizeFormOnOpen(BOOL(m_BtnMaximizeForm.GetCheck()));
        ((ZAApplicationOption&)GetObject()).SetbScreenPos(BOOL(m_BtnScreenPos.GetCheck()));
        ((ZAApplicationOption&)GetObject()).SetbCreateOnStartup(BOOL(m_BtnStartupOpenFile.GetCheck()));
        ((ZAApplicationOption&)GetObject()).SetbOpenLastLoadedFile(BOOL(m_BtnReloadLastFile.GetCheck()));
        ((ZAApplicationOption&)GetObject()).SetDontShowTaskList(m_DontShowTaskList);
        ((ZAApplicationOption&)GetObject()).SetDontShowToolTip(m_DontShowTips);
        ((ZAApplicationOption&)GetObject()).SetForceNetworkConnection(m_ForceNetwork);
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

    m_DontShowTaskList = ((ZAApplicationOption&)GetObject()).GetDontShowTaskList();
    m_DontShowTips     = ((ZAApplicationOption&)GetObject()).GetDontShowToolTip();
    m_ForceNetwork     = ((ZAApplicationOption&)GetObject()).GetForceNetworkConnection();

    CDialog::OnInitDialog();

    m_BtnShowWelcome.SetCheck    (INT(((ZAApplicationOption&)GetObject()).GetShowWelcomeScreen()));
    m_BtnStartupOpenFile.SetCheck(INT(((ZAApplicationOption&)GetObject()).GetbCreateOnStartup()));
    m_BtnScreenPos.SetCheck      (INT(((ZAApplicationOption&)GetObject()).GetbScreenPos()));
    m_BtnMaximizeForm.SetCheck   (INT(((ZAApplicationOption&)GetObject()).GetMaximizeFormOnOpen()));
    m_BtnReloadLastFile.SetCheck (INT(((ZAApplicationOption&)GetObject()).GetbOpenLastLoadedFile()));

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
    if (HasBeenInitialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
