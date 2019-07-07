/****************************************************************************
 * ==> PSS_PublishModelGenerate --------------------------------------------*
 ****************************************************************************
 * Description : Dialog box showing the model publication progression       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelGenerate.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelGenerate, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelGenerate)
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelGenerate
//---------------------------------------------------------------------------
PSS_PublishModelGenerate::PSS_PublishModelGenerate() :
    ZIWizardDialog(),
    m_RequestCancel(false),
    m_Destination(_T(""))
{}
//---------------------------------------------------------------------------
bool PSS_PublishModelGenerate::Create(CWnd* pParent)
{
    return ZIWizardDialog::Create(PSS_PublishModelGenerate::IDD,
                                  IDB_WZBMP1,
                                  0,
                                  0,
                                  IDS_PUBLISHMODELGENERATE_S,
                                  IDS_PUBLISHMODELGENERATE_T,
                                  TRUE,
                                  FALSE,
                                  pParent);
}
//---------------------------------------------------------------------------
void PSS_PublishModelGenerate::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelGenerate)
    DDX_Control(pDX, IDC_AVIFILEMOVE, m_FileMoveAnimation);
    DDX_Text(pDX, IDC_FILEDESTINATION, m_Destination);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_PublishModelGenerate::SetDestination(const CString& destination)
{
    m_Destination = destination;
    UpdateData(FALSE);
    MSG msg;

    // perform Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelGenerate::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    m_FileMoveAnimation.Open(IDR_FILEMOVE);
    m_FileMoveAnimation.ShowWindow(SW_SHOW);
    m_FileMoveAnimation.Play(0, -1, -1);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelGenerate::OnCancel()
{
    m_RequestCancel = true;
}
//---------------------------------------------------------------------------
HBRUSH PSS_PublishModelGenerate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT ctlColor)
{
    // update the animated object background
    if (pWnd && pDC && pWnd->GetDlgCtrlID() == IDC_AVIFILEMOVE)
    {
        pDC->SetBkColor(RGB(192, 192, 192));
        return HBRUSH(GetStockObject(NULL_BRUSH));
    }

    return ZIWizardDialog::OnCtlColor(pDC, pWnd, ctlColor);
}
//---------------------------------------------------------------------------
