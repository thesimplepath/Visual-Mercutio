/****************************************************************************
 * ==> PSS_PrestationsInfoDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an prestations info dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsInfoDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_LogicalPrestationsEntity.h"

// resources
#include "zBaseLib\zBaseLibRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PrestationsInfoDlg, PSS_FilteredDialogBox)
    //{{AFX_MSG_MAP(PSS_PrestationsInfoDlg)
    ON_EN_KILLFOCUS(IDC_PRESTATION_NAME, OnEnKillfocusPrestationName)
    ON_EN_SETFOCUS(IDC_PRESTATION_NAME, OnEnSetfocusPrestationName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PrestationsInfoDlg
//---------------------------------------------------------------------------
PSS_PrestationsInfoDlg::PSS_PrestationsInfoDlg(UINT                          titleID,
                                               PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                               const CString&                name,
                                               const CString&                description,
                                               bool                          modifyMode,
                                               CWnd*                         pParent) :
    PSS_FilteredDialogBox(PSS_PrestationsInfoDlg::IDD, pParent),
    m_pPrestation(pLogicalPrestation),
    m_Name(name),
    m_Description(description),
    m_ModifyMode(modifyMode)
{
    if (titleID != -1)
        m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_PrestationsInfoDlg::~PSS_PrestationsInfoDlg()
{}
//---------------------------------------------------------------------------
void PSS_PrestationsInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PrestationsInfoDlg)
    DDX_Text(pDX, IDC_PRESTATION_NAME,        m_Name);
    DDX_Text(pDX, IDC_PRESTATION_DESCRIPTION, m_Description);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
afx_msg BOOL PSS_PrestationsInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (m_ModifyMode)
        if (GetDlgItem(IDC_PRESTATION_NAME))
            GetDlgItem(IDC_PRESTATION_NAME)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
afx_msg void PSS_PrestationsInfoDlg::OnEnSetfocusPrestationName()
{
    EnableCharFilter(true);
}
//---------------------------------------------------------------------------
afx_msg void PSS_PrestationsInfoDlg::OnEnKillfocusPrestationName()
{
    EnableCharFilter(false);
}
//---------------------------------------------------------------------------
afx_msg void PSS_PrestationsInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ModifyMode)
        if (m_pPrestation && m_pPrestation->PrestationExist(m_Name))
        {
            // already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_PRESTATION_ALREADYEXIST, MB_OK);
            return;
        }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
