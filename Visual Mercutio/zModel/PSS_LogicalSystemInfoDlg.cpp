/****************************************************************************
 * ==> PSS_LogicalSystemInfoDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system info dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemInfoDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_LogicalSystemEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_LogicalSystemInfoDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_LogicalSystemInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_LogicalSystemInfoDlg
//---------------------------------------------------------------------------
PSS_LogicalSystemInfoDlg::PSS_LogicalSystemInfoDlg(UINT                     titleID,
                                                   PSS_LogicalSystemEntity* pLogicalSystem,
                                                   const CString&           name,
                                                   const CString&           description,
                                                   bool                     modifyMode,
                                                   CWnd*                    pParent) :
    CDialog(PSS_LogicalSystemInfoDlg::IDD, pParent),
    m_pLogicalSystem(pLogicalSystem),
    m_Name(name),
    m_Description(description),
    m_ModifyMode(modifyMode)
{
    // assign also the initial cost
    if (titleID != -1)
        m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemInfoDlg::~PSS_LogicalSystemInfoDlg()
{}
//---------------------------------------------------------------------------
void PSS_LogicalSystemInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_LogicalSystemInfoDlg)
    DDX_Text(pDX, IDC_LOGICALSYSTEM_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_LOGICALSYSTEM_NAME,        m_Name);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalSystemInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (m_ModifyMode)
    {
        if (GetDlgItem(IDC_LOGICALSYSTEM_NAME))
            GetDlgItem(IDC_LOGICALSYSTEM_NAME)->EnableWindow(FALSE);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_LogicalSystemInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ModifyMode)
        if (m_pLogicalSystem && m_pLogicalSystem->SystemExist(m_Name))
        {
            // already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_LOGICALSYSTEM_ALREADYEXIST, MB_OK);
            return;
        }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
