/****************************************************************************
 * ==> PSS_RenameModelPageDlg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a rename model page dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RenameModelPageDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
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
BEGIN_MESSAGE_MAP(PSS_RenameModelPageDlg, PSS_FilteredDialog)
    //{{AFX_MSG_MAP(PSS_RenameModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RenameModelPageDlg
//---------------------------------------------------------------------------
PSS_RenameModelPageDlg::PSS_RenameModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                                               CStringArray*             pPageNameArray,
                                               PSS_ProcessGraphPage*     pPageToRename,
                                               PSS_RuntimeClassSet*      pSet,
                                               CWnd*                     pParent) :
    PSS_FilteredDialog(PSS_RenameModelPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedPage(NULL),
    m_pPageToRename(pPageToRename),
    m_pPageNameArray(pPageNameArray),
    m_pSet(pSet)
{
    // if a page to rename is defined, assign the selected page
    if (m_pPageToRename)
        m_pSelectedPage = m_pPageToRename;
}
//---------------------------------------------------------------------------
PSS_RenameModelPageDlg::~PSS_RenameModelPageDlg()
{}
//---------------------------------------------------------------------------
void PSS_RenameModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RenameModelPageDlg)
    DDX_Text   (pDX, IDC_PAGENAME,        m_PageName);
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RenameModelPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet documentModelSet;
        documentModelSet.AddModel(m_pModel);

        m_SymbolTree.Initialize(_T("Document"), &documentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);

        // set the OK disabled at startup
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    if (m_pPageToRename)
    {
        m_SymbolTree.SelectItemName(m_pPageToRename->GetPageName());
        m_SymbolTree.EnableWindow(FALSE);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RenameModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (m_SymbolTree.GetSelectedPage() != NULL)
    {
        m_pSelectedPage = m_SymbolTree.GetSelectedPage();
        m_PageName      = m_pSelectedPage->GetPageName();

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
    else
    {
        m_pSelectedPage = NULL;
        m_PageName      = _T("");

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    UpdateData(FALSE);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_RenameModelPageDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_PageName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
        return;
    }

    // check if new page name already exists
    if (m_pPageNameArray)
    {
        const int pageNameCount = m_pPageNameArray->GetSize();

        for (int i = 0; i < pageNameCount; ++i)
            if (m_PageName == m_pPageNameArray->GetAt(i))
            {
                // show error message
                PSS_MsgBox mBox;
                mBox.Show(IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK);
                return;
            }
    }

    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
