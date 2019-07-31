// WelcomP.cpp : implementation file
//

#include "stdafx.h"
#include "WelcomP.h"

#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP(ZIWelcomeProcess, PSS_WelcomeDialog)
    //{{AFX_MSG_MAP(ZIWelcomeProcess)
    ON_BN_CLICKED(ID_WELCOME_CREATE_NEWMODEL, OnWelcomeCreateNewModel)
    ON_BN_CLICKED(ID_WELCOME_CREATE_NEWPROJECT, OnWelcomeCreateNewProject)
    ON_BN_CLICKED(ID_WELCOME_OPENMODEL, OnWelcomeOpenModel)
    ON_BN_CLICKED(ID_WELCOME_OPENPROJECT, OnWelcomeOpenProject)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeProcess dialog

ZIWelcomeProcess::ZIWelcomeProcess( ZAApplicationOption* pApplicationOptions,
                                    BOOL                 EnableMoveToGeneral,
                                    CWnd*                pParent) :
    PSS_WelcomeDialog(ZIWelcomeProcess::IDD,
                      IDB_WELCOME_P,
                      pApplicationOptions,
                      EnableMoveToGeneral,
                      pParent)
{}

void ZIWelcomeProcess::DoDataExchange(CDataExchange* pDX)
{
    PSS_WelcomeDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZIWelcomeProcess)
    DDX_Control(pDX, ID_WELCOME_OPENMODEL, m_OpenModel);
    DDX_Control(pDX, ID_WELCOME_OPENPROJECT, m_OpenProject);
    DDX_Control(pDX, ID_WELCOME_CREATE_NEWMODEL, m_CreateNewModel);
    DDX_Control(pDX, ID_WELCOME_CREATE_NEWPROJECT, m_CreateNewProject);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeProcess message handlers

void ZIWelcomeProcess::OnWelcomeCreateNewModel() 
{
    SaveState();
    EndDialog( ID_WELCOME_CREATE_NEWMODEL );
}

void ZIWelcomeProcess::OnWelcomeCreateNewProject() 
{
    SaveState();
    EndDialog( ID_WELCOME_CREATE_NEWPROJECT );
}

void ZIWelcomeProcess::OnWelcomeOpenModel() 
{
    SaveState();
    EndDialog( ID_WELCOME_OPENMODEL );
}

void ZIWelcomeProcess::OnWelcomeOpenProject() 
{
    SaveState();
    EndDialog( ID_WELCOME_OPENPROJECT );
}

BOOL ZIWelcomeProcess::OnInitDialog()
{
    PSS_WelcomeDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
