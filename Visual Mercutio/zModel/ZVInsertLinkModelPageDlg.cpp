// ZVInsertLinkModelPageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVInsertLinkModelPageDlg.h"

#include "ProcGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "ZBModelSet.h"
#include "ZBSymbol.h"
#include "zBaseLib\PSS_MsgBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVInsertLinkModelPageDlg dialog


ZVInsertLinkModelPageDlg::ZVInsertLinkModelPageDlg(ZDProcessGraphModelMdl* pModel, const CString NewPageName /*= ""*/, CStringArray* pArrayPageName /*= NULL*/, ZBRuntimeClassSet* pSet /*= NULL*/, CWnd* pParent /*=NULL*/)
    : PSS_Dialog(ZVInsertLinkModelPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pArrayPageName(pArrayPageName),
    m_pParentModel(NULL),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVInsertLinkModelPageDlg)
    m_NewPageName = NewPageName;
    m_InsertOrLink = 0;
    //}}AFX_DATA_INIT
}


void ZVInsertLinkModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVInsertLinkModelPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Control(pDX, IDC_EXISTINGPAGES, m_ExistingPages);
    DDX_Text(pDX, IDC_NEWPAGENAME, m_NewPageName);
    DDX_Radio(pDX, IDC_INS_LINK, m_InsertOrLink);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVInsertLinkModelPageDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(ZVInsertLinkModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPAGES, OnSelchangedExistingPagetree)
    ON_BN_CLICKED(IDC_INS_LINK, OnInsLink)
    ON_BN_CLICKED(IDC_INS_LINK2, OnInsLink2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVInsertLinkModelPageDlg message handlers

void ZVInsertLinkModelPageDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_InsertOrLink == 1)
    {
        m_PageName = m_ExistingPages.GetSelectedPage()->GetPageName();
        if (m_PageName.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
            return;
        }
        // No parent model is selection of an existing page
        m_pParentModel = NULL;
        // Clear the model pathname
        m_ParentModelFullName.Empty();
        // To save back the NewPageName
        UpdateData(FALSE);
    }
    else
    {
        // Assigns the final page name
        m_PageName = m_NewPageName;
        // Cannot be empty
        if (m_PageName.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
            return;
        }
        m_pParentModel = m_SymbolTree.GetSelectedOwnerModel();
        if (m_SymbolTree.GetSelectedPage())
            m_pParentModel = NULL;
        // Check if the right parent model selected
        if (!m_pParentModel)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
            return;
        }
        // Assigns the model pathname
        m_ParentModelFullName = m_pParentModel->GetAbsolutePath();
        // Check existence of new page name
        if (m_pArrayPageName)
        {
            for (int i = 0; i < m_pArrayPageName->GetSize(); ++i)
            {
                if (m_PageName == m_pArrayPageName->GetAt(i))
                {
                    // Display error message
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK);
                    return;
                }
            }
        }
    }
    PSS_Dialog::OnOK();
}

void ZVInsertLinkModelPageDlg::OnInsLink()
{
    CheckControlState();
}

void ZVInsertLinkModelPageDlg::OnInsLink2()
{
    // when called no parent model possible
    m_pParentModel = NULL;
    CheckControlState();
}

void ZVInsertLinkModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    *pResult = 0;

    CheckControlState();

}


void ZVInsertLinkModelPageDlg::OnSelchangedExistingPagetree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    *pResult = 0;

    CheckControlState();

}

BOOL ZVInsertLinkModelPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        m_pParentModel = m_pModel;
        ZBModelSet    DocumentModelSet;
        DocumentModelSet.AddModel(m_pModel);

        // Initialize symbol model tree
        m_SymbolTree.Initialize("Document", &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
        m_SymbolTree.SelectItemName(m_pModel->GetModelName());
        // Initialize existing pages tree
        m_ExistingPages.Initialize("Document", &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
        m_ExistingPages.SelectItemName(m_pModel->GetModelName());

    }

    CheckControlState();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void ZVInsertLinkModelPageDlg::CheckControlState()
{
    UpdateData(TRUE);

    if (GetDlgItem(IDC_NEWPAGENAME))
        GetDlgItem(IDC_NEWPAGENAME)->EnableWindow(m_InsertOrLink == 0);
    if (GetDlgItem(IDC_EXISTINGPROCESS))
        GetDlgItem(IDC_EXISTINGPROCESS)->EnableWindow(m_InsertOrLink == 0);

    if (GetDlgItem(IDC_EXISTINGPAGES))
        GetDlgItem(IDC_EXISTINGPAGES)->EnableWindow(m_InsertOrLink == 1);

    if (m_InsertOrLink == 0)
    {
        if (m_SymbolTree.GetSelectedOwnerModel() && !m_SymbolTree.GetSelectedPage())
        {
            if (GetDlgItem(IDOK))
                GetDlgItem(IDOK)->EnableWindow(TRUE);
            return;
        }

        // not the right symbol selected
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }
    else
    {
        if (m_ExistingPages.GetSelectedPage() != NULL)
        {
            // Assigns the pagename for display
            m_NewPageName = m_ExistingPages.GetSelectedPage()->GetPageName();
            if (GetDlgItem(IDOK))
                GetDlgItem(IDOK)->EnableWindow(TRUE);

        }
        else
        {
            // Assigns no page selected for display
            m_NewPageName = _T("");
            if (GetDlgItem(IDOK))
                GetDlgItem(IDOK)->EnableWindow(FALSE);
        }
    }
}
