/****************************************************************************
 * ==> PSS_FindSymbolDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a find a symbol dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FindSymbolDlg.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FindSymbolDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_FindSymbolDlg)
    ON_BN_CLICKED(IDC_FIND, OnFind)
    ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
    ON_EN_CHANGE(IDC_SYMBOLNAME, OnChangeSymbolName)
    ON_NOTIFY(NM_CLICK, IDC_FINDRESULT_LIST, OnClickFindResultList)
    ON_NOTIFY(NM_DBLCLK, IDC_FINDRESULT_LIST, OnDblclkFindResultList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FindSymbolDlg
//---------------------------------------------------------------------------
PSS_FindSymbolDlg::PSS_FindSymbolDlg(PSS_ProcessGraphModelMdl& model, UINT resID, CWnd* pParent) :
    PSS_Dialog(PSS_FindSymbolDlg::IDD, TRUE, pParent),
    m_Model(model),
    m_pSymbol(NULL),
    m_ResID(resID),
    m_InAllModels(TRUE),
    m_CaseSensitive(FALSE),
    m_PartialSearch(TRUE)
{}
//---------------------------------------------------------------------------
PSS_FindSymbolDlg::~PSS_FindSymbolDlg()
{}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_FindSymbolDlg)
    DDX_Control(pDX, IDC_FINDRESULT_LIST, m_ResultList);
    DDX_Text   (pDX, IDC_SYMBOLNAME,      m_SymbolName);
    DDX_Check  (pDX, IDC_INALLMODELS,     m_InAllModels);
    DDX_Check  (pDX, IDC_CASESENSITIVE,   m_CaseSensitive);
    DDX_Check  (pDX, IDC_PARTIAL,         m_PartialSearch);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_FindSymbolDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    m_ResultList.Initialize(NULL, m_ResID);
    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::OnFind()
{
    UpdateData();

    PSS_ProcessGraphModelMdl* pModel = &m_Model;

    if (m_InAllModels)
        pModel = m_Model.GetRoot();

    CODComponentSet* pSet = NULL;

    if (m_PartialSearch)
        pSet = pModel->FindSymbolPartialName(m_SymbolName, m_InAllModels, m_CaseSensitive, false);
    else
        pSet = pModel->FindSymbol(m_SymbolName, "", m_InAllModels, m_CaseSensitive, false);

    m_ResultList.Initialize(pSet, m_ResID);
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::OnBrowse()
{
    if (m_ResultList.GetSelectedSymbol())
        m_pSymbol = m_ResultList.GetSelectedSymbol();

    EndDialog(IDC_BROWSE);
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::OnChangeSymbolName()
{
    // if this is a RICHEDIT control, it will not send this notification unless
    // the ZIDialog::OnInitDialog() function is overridden, and the CRichEditCtrl().SetEventMask()
    // is called with the ENM_CHANGE flag in the mask
    CheckControlState();

    // set default to search button
    if (GetDlgItem(IDC_FIND))
        SetDefID(IDC_FIND);
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::OnClickFindResultList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    // set default to browse button
    if (GetDlgItem(IDC_BROWSE))
        SetDefID(IDC_BROWSE);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::OnDblclkFindResultList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();
    OnBrowse();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_FindSymbolDlg::CheckControlState()
{
    UpdateData();

    if (GetDlgItem(IDC_FIND))
        GetDlgItem(IDC_FIND)->EnableWindow(!m_SymbolName.IsEmpty());

    if (GetDlgItem(IDC_BROWSE))
        GetDlgItem(IDC_BROWSE)->EnableWindow(m_ResultList.GetSelectedSymbol() != NULL);
}
//---------------------------------------------------------------------------
