// stopprt.cpp : implementation file
//

#include "stdafx.h"

#include "stopprt.h"
#include "code.h"

#include "zRes32\zRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIStopPrint dialog


ZIStopPrint::ZIStopPrint(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CANTCONTINUE, pParent)
{
	//{{AFX_DATA_INIT(ZIStopPrint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void ZIStopPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIStopPrint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIStopPrint, CDialog)
	//{{AFX_MSG_MAP(ZIStopPrint)
	ON_BN_CLICKED(IDDELOCK, OnDelock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIStopPrint message handlers



void ZIStopPrint::OnDelock()
{
	// Start the code entry
	ZICode		Code;
	if (Code.DoModal() == IDOK)
	{
		m_Code = Code.GetCode();
		EndDialog( IDCHANGE );
	}
	else	
		EndDialog( IDOK );
}

BOOL ZIStopPrint::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Put the window in the right of the screen	
	CRect	rect;
	GetClientRect( &rect );
	CRect	ClientRect;
	UINT	uiX, uiY;
	uiX = GetSystemMetrics( SM_CXFULLSCREEN );
	uiY = GetSystemMetrics( SM_CYFULLSCREEN );
	SetWindowPos( NULL, (uiX - rect.right) / 2, (uiY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
