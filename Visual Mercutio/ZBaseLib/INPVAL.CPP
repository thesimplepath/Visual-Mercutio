// InpVal.cpp : implementation file
//
#include <StdAfx.h>

#include "InpVal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIInputValue dialog


ZIInputValue::ZIInputValue(CString Title, CString Value, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZIInputValue::IDD, TRUE, pParent), m_Title( Title )
{
	//{{AFX_DATA_INIT(ZIInputValue)
	m_sValue = Value;
	//}}AFX_DATA_INIT
}

ZIInputValue::ZIInputValue(UINT nTitleID, CString Value, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZIInputValue::IDD, TRUE, pParent)
{
	//{{AFX_DATA_INIT(ZIInputValue)
	m_sValue = Value;
	//}}AFX_DATA_INIT

	m_Title.LoadString( nTitleID );
}

void ZIInputValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIInputValue)
	DDX_Text(pDX, IDC_VALUE, m_sValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIInputValue, CDialog)
	//{{AFX_MSG_MAP(ZIInputValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIInputValue message handlers

BOOL ZIInputValue::OnInitDialog()
{
	ZIDialog::OnInitDialog();
	
	if (!m_Title.IsEmpty())
		SetWindowText( m_Title );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
