/****************************************************************************
 * ==> PSS_DeleteModelPageDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a delete model page dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DeleteModelPageDlg.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelSet.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DeleteModelPageDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_DeleteModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DeleteModelPageDlg
//---------------------------------------------------------------------------
PSS_DeleteModelPageDlg::PSS_DeleteModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                                               PSS_RuntimeClassSet*      pSet,
                                               CWnd*                     pParent) :
    PSS_Dialog(PSS_DeleteModelPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pRootPage(NULL),
    m_pSelectedPage(NULL),
    m_pSet(pSet)
{}
//---------------------------------------------------------------------------
void PSS_DeleteModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DeleteModelPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Text   (pDX, IDC_PAGENAME,        m_PageName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DeleteModelPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet documentModelSet;
        documentModelSet.AddModel(m_pModel);
        m_SymbolTree.Initialize("Document", &documentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);

        // get the root page
        m_pRootPage = m_pModel->GetRoot()->FindModelPage(m_pModel->GetRoot(), true);

        // disable the Ok button at startup
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DeleteModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (m_SymbolTree.GetSelectedPage() && m_pRootPage != m_SymbolTree.GetSelectedPage())
    {
        m_PageName      = m_pSelectedPage->GetPageName();
        m_pSelectedPage = m_SymbolTree.GetSelectedPage();

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
    else
    {
        m_PageName      = _T("");
        m_pSelectedPage = NULL;

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    UpdateData(FALSE);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DeleteModelPageDlg::OnOK()
{
    // todo -cFeature -oJean: Add extra validation here
    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
