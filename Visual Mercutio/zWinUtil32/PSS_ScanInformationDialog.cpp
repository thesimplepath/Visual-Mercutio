/****************************************************************************
 * ==> PSS_ScanInformationDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan information dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ScanInformationDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ScanInformationDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_ScanInformationDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ScanInformationDialog
//---------------------------------------------------------------------------
PSS_ScanInformationDialog::PSS_ScanInformationDialog(const CString& name, const CString& description, CWnd* pParent) :
    ZIWizardDialog(PSS_ScanInformationDialog::IDD,
                   IDB_WZBMP3,
                   0,
                   0,
                   IDS_SCANNINGINFO_S,
                   IDS_SCANNINGINFO_T),
    m_Name(name),
    m_Description(description)
{}
//---------------------------------------------------------------------------
void PSS_ScanInformationDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ScanInformationDialog)
    DDX_Text(pDX, IDC_SCAN_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_SCAN_NAME,        m_Name);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ScanInformationDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ScanInformationDialog::OnOK()
{
    if (m_Name.IsEmpty())
        return;
    
    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
