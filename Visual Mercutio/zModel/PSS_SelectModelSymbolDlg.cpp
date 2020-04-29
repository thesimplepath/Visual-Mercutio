/****************************************************************************
 * ==> PSS_SelectModelSymbolDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a select model symbol dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectModelSymbolDlg.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_ModelSet.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectModelSymbolDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_SelectModelSymbolDlg)
    ON_WM_CONTEXTMENU()
    ON_NOTIFY(TVN_SELCHANGED, IDC_SYMBOLTREE, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectModelSymbolDlg
//---------------------------------------------------------------------------
PSS_SelectModelSymbolDlg::PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                                   const CString&            title,
                                                   int                       selectableItem,
                                                   PSS_RuntimeClassSet*      pSet,
                                                   CWnd*                     pParent) :
    PSS_Dialog(PSS_SelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedPage(NULL),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(NULL),
    m_pSet(pSet),
    m_Title(title),
    m_SelectableItem(selectableItem)
{}
//---------------------------------------------------------------------------
PSS_SelectModelSymbolDlg::PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                                   const CString&            title,
                                                   CRuntimeClass*            pSelectableClass,
                                                   PSS_RuntimeClassSet*      pSet,
                                                   CWnd*                     pParent) :
    PSS_Dialog(PSS_SelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedPage(NULL),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(pSelectableClass),
    m_pSet(pSet),
    m_Title(title),
    m_SelectableItem(0)
{}
//---------------------------------------------------------------------------
PSS_SelectModelSymbolDlg::PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                                   UINT                      resTitleID,
                                                   int                       selectableItem,
                                                   PSS_RuntimeClassSet*      pSet,
                                                   CWnd*                     pParent) :
    PSS_Dialog(PSS_SelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedPage(NULL),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(NULL),
    m_pSet(pSet),
    m_SelectableItem(selectableItem)
{
    m_Title.LoadString(resTitleID);
}
//---------------------------------------------------------------------------
PSS_SelectModelSymbolDlg::PSS_SelectModelSymbolDlg(PSS_ProcessGraphModelMdl* pModel,
                                                   UINT                      resTitleID,
                                                   CRuntimeClass*            pSelectableClass,
                                                   PSS_RuntimeClassSet*      pSet,
                                                   CWnd*                     pParent) :
    PSS_Dialog(PSS_SelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedPage(NULL),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(pSelectableClass),
    m_pSet(pSet),
    m_SelectableItem(0)
{
    m_Title.LoadString(resTitleID);
}
//---------------------------------------------------------------------------
PSS_SelectModelSymbolDlg::~PSS_SelectModelSymbolDlg()
{}
//---------------------------------------------------------------------------
void PSS_SelectModelSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectModelSymbolDlg)
    DDX_Text   (pDX, IDC_SYMBOLNAME, m_SymbolName);
    DDX_Text   (pDX, IDC_SYMBOLPATH, m_SymbolPath);
    DDX_Control(pDX, IDC_SYMBOLTREE, m_SymbolTree);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectModelSymbolDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet docModelSet;
        docModelSet.AddModel(m_pModel);
        m_SymbolTree.Initialize(_T("Document"), &docModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
    }

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectModelSymbolDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    PSS_ProcessGraphPage* pSelectedPage = m_SymbolTree.GetSelectedPage();
    bool                  enable        = false;

    if (pSelectedPage)
    {
        // if the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (pSelectedPage->IsKindOf(m_pSelectableClass))
                enable = true;
        }
        else
        if (m_SelectableItem & g_Selectable_GraphPage)
            enable = true;

        PSS_ProcessGraphModelMdl* pProcessGraphModel = pSelectedPage->GetModel();

        if (pProcessGraphModel)
        {
            m_SymbolPath = pProcessGraphModel->GetAbsolutePath();
            m_SymbolName = pProcessGraphModel->GetModelName();
        }
        else
        {
            m_SymbolPath = _T("");
            m_SymbolName = _T("");
        }
    }
    else
    {
        CODSymbolComponent* pSelectedComp       = m_SymbolTree.GetSelectedSymbol();
        PSS_Symbol*         pSelectedSymbol     =                          dynamic_cast<PSS_Symbol*>(pSelectedComp);
        PSS_LinkSymbol*     pSelectedLinkSymbol = pSelectedSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSelectedComp);

        if (pSelectedSymbol)
        {
            // if the check must be done by runtime class
            if (m_pSelectableClass)
            {
                if (pSelectedSymbol->IsKindOf(m_pSelectableClass))
                    enable = true;
            }
            else
            if (m_SelectableItem & g_Selectable_Symbol)
                enable = true;

            m_SymbolPath = pSelectedSymbol->GetAbsolutePath();
            m_SymbolName = pSelectedSymbol->GetSymbolName();

            PSS_ProcessGraphModelMdl* pProcessGraphModel =
                    dynamic_cast<PSS_ProcessGraphModelMdl*>(pSelectedSymbol->GetChildModel());

            // if contains a model
            if (pProcessGraphModel && !pSelectedSymbol->IsChildModelRef())
            {
                if (!m_pSelectableClass && (m_SelectableItem & g_Selectable_Model))
                    enable = true;

                m_SymbolPath = pProcessGraphModel->GetAbsolutePath();
                m_SymbolName = pProcessGraphModel->GetModelName();
            }
        }
        else
        if (pSelectedLinkSymbol)
        {
            // if the check must be done by runtime class
            if (m_pSelectableClass)
            {
                if (pSelectedLinkSymbol->IsKindOf(m_pSelectableClass))
                    enable = true;
            }
            else
            if (m_SelectableItem & g_Selectable_LinkSymbol)
                enable = true;

            m_SymbolPath = pSelectedLinkSymbol->GetAbsolutePath();
            m_SymbolName = pSelectedLinkSymbol->GetSymbolName();
        }
        else
        if (!pSelectedComp && !m_pSelectableClass)
            if (m_SymbolTree.IsDocumentSelected() && (m_SelectableItem & g_Selectable_Document))
                enable = true;
            else
            if (m_SymbolTree.IsRootSelected() && (m_SelectableItem & g_Selectable_RootModel))
                enable = true;
    }

    UpdateData(FALSE);

    // enable or not the ok button
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(enable);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectModelSymbolDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (m_SymbolTree.HasContextMenu(pWnd, point) != -1)
    {
        m_SymbolTree.ShowContextMenu(pWnd, point);
        return;
    }
}
//---------------------------------------------------------------------------
void PSS_SelectModelSymbolDlg::OnOK()
{
    PSS_ProcessGraphPage* pSelectedPage = m_SymbolTree.GetSelectedPage();

    // assign values
    if (pSelectedPage)
    {
        // if the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (pSelectedPage->IsKindOf(m_pSelectableClass))
            {
                m_pSelectedPage   = pSelectedPage;
                m_pSelectedModel  = NULL;
                m_pSelectedSymbol = NULL;
            }

            m_SymbolPath = _T("");
            m_SymbolName = _T("");

            if (m_pSelectedPage)
            {
                PSS_ProcessGraphModelMdl* pProcessGraphModel = m_pSelectedPage->GetModel();

                if (pProcessGraphModel)
                {
                    m_SymbolPath = pProcessGraphModel->GetAbsolutePath();
                    m_SymbolName = pProcessGraphModel->GetModelName();
                }
            }
        }
        else
        {
            if (m_SelectableItem & g_Selectable_GraphPage)
            {
                m_pSelectedPage   = m_SymbolTree.GetSelectedPage();
                m_pSelectedModel  = NULL;
                m_pSelectedSymbol = NULL;
                m_SymbolPath      = _T("");
                m_SymbolName      = _T("");

                PSS_ProcessGraphModelMdl* pProcessGraphModel = m_pSelectedPage->GetModel();

                if (pProcessGraphModel)
                {
                    m_SymbolPath = pProcessGraphModel->GetAbsolutePath();
                    m_SymbolName = pProcessGraphModel->GetModelName();
                }
            }
            else
                // not possible, should have been checked before
                THROW("Internal corruption");
        }
    }
    else
    {
        m_pSelectedSymbol                   = m_SymbolTree.GetSelectedSymbol();
        PSS_Symbol*     pSelectedSymbol     =                          dynamic_cast<PSS_Symbol*>(m_pSelectedSymbol);
        PSS_LinkSymbol* pSelectedLinkSymbol = pSelectedSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSelectedSymbol);

        // if the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (m_pSelectedSymbol && m_pSelectedSymbol->IsKindOf(m_pSelectableClass))
            {
                if (pSelectedSymbol)
                {
                    m_SymbolPath = pSelectedSymbol->GetAbsolutePath();
                    m_SymbolName = pSelectedSymbol->GetSymbolName();
                }
                else
                if (pSelectedLinkSymbol)
                {
                    m_SymbolPath = pSelectedLinkSymbol->GetAbsolutePath();
                    m_SymbolName = pSelectedLinkSymbol->GetSymbolName();
                }
                else
                {
                    m_SymbolPath = _T("");
                    m_SymbolName = _T("");
                }
            }
            else
                // not possible, should have been checked before
                THROW("Internal corruption");
        }
        else
        if (pSelectedSymbol)
        {
            if (m_SelectableItem & g_Selectable_Symbol)
            {
                m_SymbolPath = pSelectedSymbol->GetAbsolutePath();
                m_SymbolName = pSelectedSymbol->GetSymbolName();
            }

            PSS_ProcessGraphModelMdl* pProcessGraphModelMdl =
                    dynamic_cast<PSS_ProcessGraphModelMdl*>(pSelectedSymbol->GetChildModel());

            // if contains a model
            if (pProcessGraphModelMdl && !pSelectedSymbol->IsChildModelRef())
                if (m_SelectableItem & g_Selectable_Model)
                {
                    // assign the model
                    m_pSelectedModel = pProcessGraphModelMdl;
                    m_SymbolPath     = pProcessGraphModelMdl->GetAbsolutePath();
                    m_SymbolName     = pProcessGraphModelMdl->GetModelName();
                }
        }
        else
        if (pSelectedLinkSymbol)
        {
            if (m_SelectableItem & g_Selectable_LinkSymbol)
            {
                m_SymbolPath = pSelectedLinkSymbol->GetAbsolutePath();
                m_SymbolName = pSelectedLinkSymbol->GetSymbolName();
            }
            else
                // not possible, should have been checked before
                THROW("Internal corruption");
        }
    }

    UpdateData(FALSE);

    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
