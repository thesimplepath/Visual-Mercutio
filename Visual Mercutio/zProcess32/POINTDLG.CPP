// pointdlg.cpp : implementation file
//

#include "stdafx.h"
#include "PointDlg.h"
#include "ZAApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDPointerDlg dialog


ZDPointerDlg::ZDPointerDlg(CWnd* pParent /*=NULL*/)
 : m_ID( -1 ), m_Obj( NULL )
{
    //{{AFX_DATA_INIT(ZDPointerDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void    ZDPointerDlg::Create( CWnd* pParent )
{
    CDialog::Create( ZDPointerDlg::IDD, pParent );
}


ZDPointerDlg::~ZDPointerDlg()
{
    Close();
    DestroyWindow();
}

void ZDPointerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZDPointerDlg)
    DDX_Text(pDX, IDC_FIELD, m_sField);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZDPointerDlg, CDialog)
    //{{AFX_MSG_MAP(ZDPointerDlg)
    ON_WM_CLOSE()
    ON_MESSAGE(UM_NOTIFY_POINTEROBJSELECTED, OnNotifyPointerObjSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZDPointerDlg::Close()
{
    m_ID = IDCANCEL;
}


BOOL ZDPointerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Create the pointer window
    CWnd*    pFrame = GetDlgItem( IDC_POINTERWINDOW );
    CRect    rect;
    pFrame->GetWindowRect( &rect );
    ScreenToClient( &rect );
    m_PointerWindow.Create( NULL, rect, this );

    return TRUE;
}


int ZDPointerDlg::DoModal()
{
    PSS_Document*    pDoc = ZAApp::ZAGetApp()->GetActiveDocument();
    ASSERT( pDoc );

    m_PointerWindow.AssignMessageWnd( AfxGetMainWnd() );
    
    ZAApp::ZAGetApp()->SetCurrentDocument( pDoc );
    // Initialize the ID.
    m_ID = -1;

    SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW );
    MSG    msg;
    while (m_ID == -1) 
    { 
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
        {
            GetMessage( &msg, NULL, NULL, NULL );
            if (!IsWindow(GetSafeHwnd()) || !IsDialogMessage(&msg))
            { 
                TranslateMessage(&msg);         
                DispatchMessage(&msg);     
            } 
        }
    }
    TRACE( "END MODAL" );
    ShowWindow( SW_HIDE );
    return m_ID;
}

/////////////////////////////////////////////////////////////////////////////
// ZDPointerDlg message handlers


afx_msg LONG ZDPointerDlg::OnNotifyPointerObjSelected(UINT message, LONG wParam)
{                
    // Not for us
    if (message != UM_NOTIFY_POINTEROBJSELECTED)
        return 0;
    // Not for us
    if (!IsWindowVisible())
        return 0;
    PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)wParam;
    // If no object, return
    if (!pObj)
        return 1;
    m_Obj = pObj;        
    m_sField = pObj->GetObjectName();

    UpdateData( FALSE );
    return 1;
}


void ZDPointerDlg::OnClose()
{
    Close();
}
