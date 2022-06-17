/****************************************************************************
 * ==> PSS_ScanContinueSelectDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a scan continue select dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ScanContinueSelectDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ScanContinueSelectDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ScanContinueSelectDialog)
    ON_BN_CLICKED(IDCONTINUE, OnContinue)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ScanContinueSelectDialog
//---------------------------------------------------------------------------
PSS_ScanContinueSelectDialog::PSS_ScanContinueSelectDialog(bool firstTime, CWnd* pParent) :
    PSS_WizardDialog(PSS_ScanContinueSelectDialog::IDD,
                     IDB_WZBMP3,
                     0,
                     0,
                     IDS_SCANNINGSELECT_S,
                     IDS_SCANNINGSELECT_T),
    m_ScanType(1),
    m_FirstTime(firstTime)
{
    m_File.SetSearchType(PSS_SearchEditButton::IEType::IE_T_File, _T(""));
}
//---------------------------------------------------------------------------
void PSS_ScanContinueSelectDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ScanContinueSelectDialog)
    DDX_Control(pDX, IDC_FILE_SCAN, m_File);
    DDX_Radio  (pDX, IDC_SCAN_TYPE, m_ScanType);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ScanContinueSelectDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (m_FirstTime && GetDlgItem(IDOK))
        GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ScanContinueSelectDialog::OnContinue()
{
    CString fileName;
    m_File.GetWindowText(fileName);

    if (fileName.IsEmpty())
        return;

    // assign the new file name
    m_CompleteFileName = fileName;

    // ok to continue
    EndDialog(IDCONTINUE);
}
//---------------------------------------------------------------------------
