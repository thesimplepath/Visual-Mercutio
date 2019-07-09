/****************************************************************************
 * ==> PSS_PublishModelGenerateDialog --------------------------------------*
 ****************************************************************************
 * Description : Dialog box showing the model publication progression       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelGenerateDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelGenerateDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelGenerateDialog)
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelGenerate
//---------------------------------------------------------------------------
PSS_PublishModelGenerateDialog::PSS_PublishModelGenerateDialog() :
    ZIWizardDialog(),
    m_CancelRequested(false),
    m_Destination(_T(""))
{}
//---------------------------------------------------------------------------
bool PSS_PublishModelGenerateDialog::Create(CWnd* pParent)
{
    return ZIWizardDialog::Create(PSS_PublishModelGenerateDialog::IDD,
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
void PSS_PublishModelGenerateDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelGenerateDialog)
    DDX_Control(pDX, IDC_AVIFILEMOVE, m_FileMoveAnimation);
    DDX_Text(pDX, IDC_FILEDESTINATION, m_Destination);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_PublishModelGenerateDialog::SetDestination(const CString& destination)
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
BOOL PSS_PublishModelGenerateDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    m_FileMoveAnimation.Open(IDR_FILEMOVE);
    m_FileMoveAnimation.ShowWindow(SW_SHOW);
    m_FileMoveAnimation.Play(0, -1, -1);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelGenerateDialog::OnCancel()
{
    m_CancelRequested = true;
    ZIWizardDialog::OnCancel();
}
//---------------------------------------------------------------------------
HBRUSH PSS_PublishModelGenerateDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT ctlColor)
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
