/****************************************************************************
 * ==> PSS_InsertModelNewPageDlg -------------------------------------------*
 ****************************************************************************
 * Description : Provides an insert model new page dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InsertModelNewPageDlg.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelSet.h"
#include "PSS_Symbol.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InsertModelNewPageDlg, PSS_FilteredDialog)
    //{{AFX_MSG_MAP(PSS_InsertModelNewPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InsertModelNewPageDlg
//---------------------------------------------------------------------------
PSS_InsertModelNewPageDlg::PSS_InsertModelNewPageDlg(PSS_ProcessGraphModelMdl*    pModel,
                                                     const CString&               newPageName,
                                                     CStringArray*                pArrayPageName,
                                                     PSS_RuntimeClassSet*         pSet,
                                                     CWnd*                        pParent) :
    PSS_FilteredDialog(PSS_InsertModelNewPageDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pParentModel(pModel),
    m_pSet(pSet),
    m_pPageNameArray(pArrayPageName),
    m_PageName(newPageName)
{}
//---------------------------------------------------------------------------
PSS_InsertModelNewPageDlg::~PSS_InsertModelNewPageDlg()
{}
//---------------------------------------------------------------------------
void PSS_InsertModelNewPageDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InsertModelNewPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Text   (pDX, IDC_PAGENAME,        m_PageName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InsertModelNewPageDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet DocumentModelSet;
        DocumentModelSet.AddModel(m_pModel);

        m_SymbolTree.Initialize(_T("Document"), &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
        m_SymbolTree.SelectItemName(m_pModel->GetModelName());
    }

    CheckControls();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InsertModelNewPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    *pResult = 0;

    CheckControls();
}
//---------------------------------------------------------------------------
void PSS_InsertModelNewPageDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_PageName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
        return;
    }

    m_pParentModel = m_SymbolTree.GetSelectedOwnerModel();

    // if a page is selected, reset the parent model
    if (m_SymbolTree.GetSelectedPage())
        m_pParentModel = NULL;

    if (!m_pParentModel)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_NEWMODELPAGE_EMPTY, MB_OK);
        return;
    }

    // assign the model path name
    m_ParentModelFullName = m_pParentModel->GetAbsolutePath();

    // check if a new page name exists
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
void PSS_InsertModelNewPageDlg::CheckControls()
{
    PSS_ProcessGraphModelMdl* pParentModel = m_SymbolTree.GetSelectedOwnerModel();

    // if a page is selected, reset the parent model
    if (m_SymbolTree.GetSelectedPage())
        pParentModel = NULL;

    if (pParentModel)
    {
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
    else
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);
}
//---------------------------------------------------------------------------
