/****************************************************************************
 * ==> PSS_InsertLinkModelPageDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides an insert link model page dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InsertLinkModelPageDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelSet.h"
#include "PSS_Symbol.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InsertLinkModelPageDlg, PSS_FilteredDialog)
    //{{AFX_MSG_MAP(PSS_InsertLinkModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPAGES, OnSelchangedExistingPagetree)
    ON_BN_CLICKED(IDC_INS_LINK, OnInsLink)
    ON_BN_CLICKED(IDC_INS_LINK2, OnInsLink2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InsertLinkModelPageDlg
//---------------------------------------------------------------------------
PSS_InsertLinkModelPageDlg::PSS_InsertLinkModelPageDlg(PSS_ProcessGraphModelMdl* pModel,
                                                       const CString&            newPageName,
                                                       CStringArray*             pArrayPageName,
                                                       PSS_RuntimeClassSet*      pSet,
                                                       CWnd*                     pParent) :
    PSS_FilteredDialog(PSS_InsertLinkModelPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pParentModel(NULL),
    m_pSet(pSet),
    m_pArrayPageName(pArrayPageName),
    m_NewPageName(newPageName),
    m_InsertOrLink(0)
{}
//---------------------------------------------------------------------------
PSS_InsertLinkModelPageDlg::~PSS_InsertLinkModelPageDlg()
{}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InsertLinkModelPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Control(pDX, IDC_EXISTINGPAGES,   m_ExistingPages);
    DDX_Text   (pDX, IDC_NEWPAGENAME,     m_NewPageName);
    DDX_Radio  (pDX, IDC_INS_LINK,        m_InsertOrLink);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InsertLinkModelPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        m_pParentModel = m_pModel;

        PSS_ModelSet documentModelSet;
        documentModelSet.AddModel(m_pModel);

        // initialize symbol model tree
        m_SymbolTree.Initialize(_T("Document"), &documentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
        m_SymbolTree.SelectItemName(m_pModel->GetModelName());

        // Initialize existing pages tree
        m_ExistingPages.Initialize(_T("Document"), &documentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
        m_ExistingPages.SelectItemName(m_pModel->GetModelName());

    }

    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    *pResult                 = 0;

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::OnSelchangedExistingPagetree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    *pResult                 = 0;

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::OnInsLink()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::OnInsLink2()
{
    // when called, no parent model is possible
    m_pParentModel = NULL;
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::OnOK()
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

        // no parent model while an existing page is seleted
        m_pParentModel = NULL;

        // clear the model path name
        m_ParentModelFullName.Empty();

        // to save back the new page name
        UpdateData(FALSE);
    }
    else
    {
        // assign the final page name
        m_PageName = m_NewPageName;

        // cannot be empty
        if (m_PageName.IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
            return;
        }

        m_pParentModel = m_SymbolTree.GetSelectedOwnerModel();

        if (m_SymbolTree.GetSelectedPage())
            m_pParentModel = NULL;

        // check if a parent model is selected
        if (!m_pParentModel)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
            return;
        }

        // assign the model path name
        m_ParentModelFullName = m_pParentModel->GetAbsolutePath();

        // check if the new page name exists
        if (m_pArrayPageName)
        {
            const int pageNameCount = m_pArrayPageName->GetSize();

            for (int i = 0; i < pageNameCount; ++i)
                if (m_PageName == m_pArrayPageName->GetAt(i))
                {
                    // show error message
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK);
                    return;
                }
        }
    }

    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_InsertLinkModelPageDlg::CheckControlState()
{
    UpdateData(TRUE);

    if (GetDlgItem(IDC_NEWPAGENAME))
        GetDlgItem(IDC_NEWPAGENAME)->EnableWindow(!m_InsertOrLink);

    if (GetDlgItem(IDC_EXISTINGPROCESS))
        GetDlgItem(IDC_EXISTINGPROCESS)->EnableWindow(!m_InsertOrLink);

    if (GetDlgItem(IDC_EXISTINGPAGES))
        GetDlgItem(IDC_EXISTINGPAGES)->EnableWindow(m_InsertOrLink == 1);

    if (!m_InsertOrLink)
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
        if (m_ExistingPages.GetSelectedPage())
        {
            // get the new page name
            m_NewPageName = m_ExistingPages.GetSelectedPage()->GetPageName();

            if (GetDlgItem(IDOK))
                GetDlgItem(IDOK)->EnableWindow(TRUE);
        }
        else
        {
            m_NewPageName = _T("");

            if (GetDlgItem(IDOK))
                GetDlgItem(IDOK)->EnableWindow(FALSE);
        }
    }
}
//---------------------------------------------------------------------------
