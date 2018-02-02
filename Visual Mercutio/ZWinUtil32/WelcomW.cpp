// WelcomW.cpp : implementation file
//

#include "stdafx.h"
#include "WelcomW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeWriter dialog


ZIWelcomeWriter::ZIWelcomeWriter(ZAApplicationOption* pApplicationOptions, BOOL EnableMoveToGeneral, CWnd* pParent /*=NULL*/)
	: ZIWelcomeDialog(ZIWelcomeWriter::IDD, IDB_WELCOME, pApplicationOptions, EnableMoveToGeneral, pParent)
{
	//{{AFX_DATA_INIT(ZIWelcomeWriter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZIWelcomeWriter::DoDataExchange(CDataExchange* pDX)
{
	ZIWelcomeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIWelcomeWriter)
	DDX_Control(pDX, ID_WELCOME_PROCESSOPEN, m_FileOpenProcess);
	DDX_Control(pDX, ID_WELCOME_NEWPROCESS, m_StartProcess);
	DDX_Control(pDX, ID_WELCOME_NEWFORM, m_StartForm);
	DDX_Control(pDX, ID_WELCOME_FILEOPEN, m_FileOpen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIWelcomeWriter, ZIWelcomeDialog)
	//{{AFX_MSG_MAP(ZIWelcomeWriter)
	ON_BN_CLICKED(ID_WELCOME_FILEOPEN, OnWelcomeFileOpen)
	ON_BN_CLICKED(ID_WELCOME_NEWFORM, OnWelcomeSartFormulaire)
	ON_BN_CLICKED(ID_WELCOME_NEWPROCESS, OnWelcomeStartProcess)
	ON_BN_CLICKED(ID_WELCOME_PROCESSOPEN, OnWelcomeProcessFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeWriter message handlers

void ZIWelcomeWriter::OnWelcomeFileOpen() 
{
	SaveState();
	EndDialog( ID_WELCOME_FILEOPEN );
}

void ZIWelcomeWriter::OnWelcomeSartFormulaire() 
{
	SaveState();
	EndDialog( ID_WELCOME_NEWFORM );
}

void ZIWelcomeWriter::OnWelcomeStartProcess() 
{
	SaveState();
	EndDialog( ID_WELCOME_NEWPROCESS );
}

void ZIWelcomeWriter::OnWelcomeProcessFileOpen() 
{
	SaveState();
	EndDialog( ID_WELCOME_PROCESSOPEN );
}
