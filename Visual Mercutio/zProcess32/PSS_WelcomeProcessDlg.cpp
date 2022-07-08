/****************************************************************************
 * ==> PSS_WelcomeProcessDlg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the welcome process dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WelcomeProcessDlg.h"

// resources
#include "resource.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WelcomeProcessDlg, PSS_WelcomeDialog)
    //{{AFX_MSG_MAP(PSS_WelcomeProcessDlg)
    ON_BN_CLICKED(ID_WELCOME_CREATE_NEWMODEL, OnWelcomeCreateNewModel)
    ON_BN_CLICKED(ID_WELCOME_CREATE_NEWPROJECT, OnWelcomeCreateNewProject)
    ON_BN_CLICKED(ID_WELCOME_OPENMODEL, OnWelcomeOpenModel)
    ON_BN_CLICKED(ID_WELCOME_OPENPROJECT, OnWelcomeOpenProject)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WelcomeProcessDlg
//---------------------------------------------------------------------------
PSS_WelcomeProcessDlg::PSS_WelcomeProcessDlg(PSS_ApplicationOption* pApplicationOptions,
                                             BOOL                   enableMoveToGeneral,
                                             CWnd*                  pParent) :
    PSS_WelcomeDialog(PSS_WelcomeProcessDlg::IDD,
                      IDB_WELCOME_P,
                      pApplicationOptions,
                      enableMoveToGeneral,
                      pParent)
{}
//---------------------------------------------------------------------------
PSS_WelcomeProcessDlg::~PSS_WelcomeProcessDlg()
{}
//---------------------------------------------------------------------------
void PSS_WelcomeProcessDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WelcomeDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WelcomeProcessDlg)
    DDX_Control(pDX, ID_WELCOME_OPENMODEL,         m_OpenModel);
    DDX_Control(pDX, ID_WELCOME_OPENPROJECT,       m_OpenProject);
    DDX_Control(pDX, ID_WELCOME_CREATE_NEWMODEL,   m_CreateNewModel);
    DDX_Control(pDX, ID_WELCOME_CREATE_NEWPROJECT, m_CreateNewProject);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WelcomeProcessDlg::OnInitDialog()
{
    PSS_WelcomeDialog::OnInitDialog();

    SetFocus();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WelcomeProcessDlg::OnWelcomeCreateNewModel()
{
    SaveState();
    EndDialog(ID_WELCOME_CREATE_NEWMODEL);
}
//---------------------------------------------------------------------------
void PSS_WelcomeProcessDlg::OnWelcomeCreateNewProject()
{
    SaveState();
    EndDialog(ID_WELCOME_CREATE_NEWPROJECT);
}
//---------------------------------------------------------------------------
void PSS_WelcomeProcessDlg::OnWelcomeOpenModel()
{
    SaveState();
    EndDialog(ID_WELCOME_OPENMODEL);
}
//---------------------------------------------------------------------------
void PSS_WelcomeProcessDlg::OnWelcomeOpenProject()
{
    SaveState();
    EndDialog(ID_WELCOME_OPENPROJECT);
}
//---------------------------------------------------------------------------
