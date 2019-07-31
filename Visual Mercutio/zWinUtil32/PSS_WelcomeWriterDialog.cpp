/****************************************************************************
 * ==> PSS_WelcomeWriterDialog ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a welcome writer dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_WelcomeWriterDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WelcomeWriterDialog, PSS_WelcomeDialog)
    //{{AFX_MSG_MAP(PSS_WelcomeWriterDialog)
    ON_BN_CLICKED(ID_WELCOME_FILEOPEN, OnWelcomeFileOpen)
    ON_BN_CLICKED(ID_WELCOME_PROCESSOPEN, OnWelcomeProcessFileOpen)
    ON_BN_CLICKED(ID_WELCOME_NEWFORM, OnWelcomeSartForm)
    ON_BN_CLICKED(ID_WELCOME_NEWPROCESS, OnWelcomeStartProcess)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WelcomeWriterDialog
//---------------------------------------------------------------------------
PSS_WelcomeWriterDialog::PSS_WelcomeWriterDialog(ZAApplicationOption* pApplicationOptions,
                                                 BOOL                 enableMoveToGeneral,
                                                 CWnd*                pParent) :
    PSS_WelcomeDialog(PSS_WelcomeWriterDialog::IDD, IDB_WELCOME, pApplicationOptions, enableMoveToGeneral, pParent)
{}
//---------------------------------------------------------------------------
void PSS_WelcomeWriterDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WelcomeDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WelcomeWriterDialog)
    DDX_Control(pDX, ID_WELCOME_PROCESSOPEN, m_FileOpenProcess);
    DDX_Control(pDX, ID_WELCOME_NEWPROCESS,  m_StartProcess);
    DDX_Control(pDX, ID_WELCOME_NEWFORM,     m_StartForm);
    DDX_Control(pDX, ID_WELCOME_FILEOPEN,    m_FileOpen);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_WelcomeWriterDialog::OnWelcomeFileOpen()
{
    SaveState();
    EndDialog(ID_WELCOME_FILEOPEN);
}
//---------------------------------------------------------------------------
void PSS_WelcomeWriterDialog::OnWelcomeProcessFileOpen()
{
    SaveState();
    EndDialog(ID_WELCOME_PROCESSOPEN);
}
//---------------------------------------------------------------------------
void PSS_WelcomeWriterDialog::OnWelcomeSartForm()
{
    SaveState();
    EndDialog(ID_WELCOME_NEWFORM);
}
//---------------------------------------------------------------------------
void PSS_WelcomeWriterDialog::OnWelcomeStartProcess()
{
    SaveState();
    EndDialog(ID_WELCOME_NEWPROCESS);
}
//---------------------------------------------------------------------------
