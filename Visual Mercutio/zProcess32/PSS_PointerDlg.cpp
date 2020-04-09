/****************************************************************************
 * ==> PSS_PointerDlg ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a pointer dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PointerDlg.h"

// processsoft
#include "ZAApp.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PointerDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_PointerDlg)
    ON_WM_CLOSE()
    ON_MESSAGE(UM_NOTIFY_POINTEROBJSELECTED, OnNotifyPointerObjSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PointerDlg
//---------------------------------------------------------------------------
PSS_PointerDlg::PSS_PointerDlg(CWnd* pParent) :
    CDialog(PSS_PointerDlg::IDD, pParent),
    m_ID(-1),
    m_pObj(NULL)
{}
//---------------------------------------------------------------------------
PSS_PointerDlg::~PSS_PointerDlg()
{
    Close();
    DestroyWindow();
}
//---------------------------------------------------------------------------
void PSS_PointerDlg::Create(CWnd* pParent)
{
    CDialog::Create(PSS_PointerDlg::IDD, pParent);
}
//---------------------------------------------------------------------------
void PSS_PointerDlg::Close()
{
    m_ID = IDCANCEL;
}
//---------------------------------------------------------------------------
int PSS_PointerDlg::DoModal()
{
    ZAApp* pApp = ZAApp::ZAGetApp();

    if (!pApp)
        return IDABORT;

    PSS_Document* pDoc = pApp->GetActiveDocument();

    if (!pDoc)
        return IDABORT;

    m_PointerWindow.AssignMessageWnd(::AfxGetMainWnd());

    pApp->SetCurrentDocument(pDoc);

    // initialize the identifier
    m_ID = -1;

    SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

    MSG msg;

    while (m_ID == -1)
        if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
        {
            ::GetMessage(&msg, NULL, NULL, NULL);

            if (!IsWindow(GetSafeHwnd()) || !IsDialogMessage(&msg))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }

    TRACE("END MODAL");
    ShowWindow(SW_HIDE);

    return m_ID;
}
//---------------------------------------------------------------------------
void PSS_PointerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PointerDlg)
    DDX_Text(pDX, IDC_FIELD, m_Field);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
LONG PSS_PointerDlg::OnNotifyPointerObjSelected(UINT message, LONG wParam)
{
    if (message != UM_NOTIFY_POINTEROBJSELECTED)
        return 0;

    if (!IsWindowVisible())
        return 0;

    PSS_PlanFinObject* pObj = (PSS_PlanFinObject*)wParam;

    if (!pObj)
        return 1;

    m_pObj  = pObj;
    m_Field = pObj->GetObjectName();

    UpdateData(FALSE);
    return 1;
}
//---------------------------------------------------------------------------
void PSS_PointerDlg::OnClose()
{
    Close();
}
//---------------------------------------------------------------------------
BOOL PSS_PointerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CWnd* pFrame = GetDlgItem(IDC_POINTERWINDOW);

    CRect rect;
    pFrame->GetWindowRect(&rect);
    ScreenToClient(&rect);
    m_PointerWindow.Create(NULL, rect, this);

    return TRUE;
}
//---------------------------------------------------------------------------
