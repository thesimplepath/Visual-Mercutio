// CnfDelMsg.cpp : implementation file
//

#include "stdafx.h"
#include "CnfDelMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIConfirmDeleteMessage dialog


ZIConfirmDeleteMessage::ZIConfirmDeleteMessage(ZBEventActivity& EventActivity, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZIConfirmDeleteMessage::IDD, TRUE, pParent)
{
	//{{AFX_DATA_INIT(ZIConfirmDeleteMessage)
	//}}AFX_DATA_INIT
	m_ActivityName = EventActivity.GetActivityName();
	m_Message = EventActivity.GetComments();
	m_ProcessName = EventActivity.GetProcessName();
	m_Status = EventActivity.GetActivityStatusString();
}


void ZIConfirmDeleteMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIConfirmDeleteMessage)
	DDX_Control(pDX, IDOK, m_Delete);
	DDX_Control(pDX, IDCANCEL, m_DoNotDelete);
	DDX_Text(pDX, IDC_ACTIVITY_NAME, m_ActivityName);
	DDX_Text(pDX, IDC_MESSAGE_TEXT, m_Message);
	DDX_Text(pDX, IDC_PROCESS_NAME, m_ProcessName);
	DDX_Text(pDX, IDC_STATUS_TEXT, m_Status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIConfirmDeleteMessage, CDialog)
	//{{AFX_MSG_MAP(ZIConfirmDeleteMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIConfirmDeleteMessage message handlers

