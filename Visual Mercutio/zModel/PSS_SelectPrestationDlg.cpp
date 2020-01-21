/****************************************************************************
 * ==> PSS_SelectPrestationDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestation selection dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectPrestationDlg.h"

// processsoft
#include "PSS_LogicalPrestationsEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectPrestationDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectPrestationDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_PRESTATIONS_TREE, OnSelchangedPrestationsTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectPrestationDlg
//---------------------------------------------------------------------------
PSS_SelectPrestationDlg::PSS_SelectPrestationDlg(const CString&                title,
                                                 PSS_LogicalPrestationsEntity* pMainPrestation,
                                                 bool                          allowPrestationSelection,
                                                 CWnd*                         pParent) :
    CDialog(PSS_SelectPrestationDlg::IDD, pParent),
    m_pPrestationEntity(NULL),
    m_pMainPrestation(pMainPrestation),
    m_Title(title),
    m_AllowPrestationSelection(allowPrestationSelection)
{}
//---------------------------------------------------------------------------
PSS_SelectPrestationDlg::PSS_SelectPrestationDlg(UINT                          titleID,
                                                 PSS_LogicalPrestationsEntity* pMainPrestation,
                                                 bool                          allowPrestationSelection,
                                                 CWnd*                         pParent) :
    CDialog(PSS_SelectPrestationDlg::IDD, pParent),
    m_pPrestationEntity(NULL),
    m_pMainPrestation(pMainPrestation),
    m_AllowPrestationSelection(allowPrestationSelection)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectPrestationDlg::~PSS_SelectPrestationDlg()
{
    // NOTE the fully qualified name is used here to avoid to call a pure virtual function during the destruction
    PSS_SelectPrestationDlg::Release();
}
//---------------------------------------------------------------------------
void PSS_SelectPrestationDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
void PSS_SelectPrestationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectPrestationDlg)
    DDX_Control(pDX, IDC_PRESTATIONS_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectPrestationDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString text;
    text.LoadString(IDS_PRESTATION_ROOT_T);
    m_Ctrl.Initialize(text, m_pMainPrestation);

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectPrestationDlg::OnSelchangedPrestationsTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_AllowPrestationSelection &&
                                       dynamic_cast<PSS_LogicalPrestationsEntity*>(m_Ctrl.GetSelectedPrestationEntity()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectPrestationDlg::OnOK()
{
    // Save the selected item
    m_pPrestationEntity = m_Ctrl.GetSelectedPrestationEntity();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
