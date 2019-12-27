// ZVSelectModelSymbolDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVSelectModelSymbolDlg.h"

#include "PSS_ProcessGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "PSS_ModelSet.h"

#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVSelectModelSymbolDlg dialog

BEGIN_MESSAGE_MAP(ZVSelectModelSymbolDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(ZVSelectModelSymbolDlg)
    ON_WM_CONTEXTMENU()
    ON_NOTIFY(TVN_SELCHANGED, IDC_SYMBOLTREE, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg(PSS_ProcessGraphModelMdl*    pModel,
                                               const CString            Title            /*= ""*/,
                                               int                        SelectableItem    /*= Selectable_All*/,
                                               PSS_RuntimeClassSet*        pSet            /*= NULL*/,
                                               CWnd*                    pParent            /*=NULL*/)
    : PSS_Dialog(ZVSelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectedPage(NULL),
    m_pSelectableClass(NULL),
    m_Title(Title),
    m_SelectableItem(SelectableItem),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVSelectModelSymbolDlg)
    m_SymbolPath = _T("");
    m_SymbolName = _T("");
    //}}AFX_DATA_INIT
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg(PSS_ProcessGraphModelMdl*    pModel,
                                               const CString            Title,
                                               CRuntimeClass*            pSelectableClass,
                                               PSS_RuntimeClassSet*        pSet                /*= NULL*/,
                                               CWnd*                    pParent                /*=NULL*/)
    : PSS_Dialog(ZVSelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectedPage(NULL),
    m_Title(Title),
    m_pSelectableClass(pSelectableClass),
    m_SelectableItem(0),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    m_SymbolName = _T("");
    //}}AFX_DATA_INIT
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg(PSS_ProcessGraphModelMdl*    pModel,
                                               UINT                    nIDResTitle,
                                               int                        SelectableItem    /*= Selectable_All*/,
                                               PSS_RuntimeClassSet*        pSet            /*= NULL*/,
                                               CWnd*                    pParent            /*=NULL*/)
    : PSS_Dialog(ZVSelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectableClass(NULL),
    m_pSelectedPage(NULL),
    m_SelectableItem(SelectableItem),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVSelectModelSymbolDlg)
    m_SymbolPath = _T("");
    m_SymbolName = _T("");
    //}}AFX_DATA_INIT
    m_Title.LoadString(nIDResTitle);
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg(PSS_ProcessGraphModelMdl*    pModel,
                                               UINT                    nIDResTitle,
                                               CRuntimeClass*            pSelectableClass,
                                               PSS_RuntimeClassSet*        pSet                /*= NULL*/,
                                               CWnd*                    pParent                /*=NULL*/)
    : PSS_Dialog(ZVSelectModelSymbolDlg::IDD, TRUE, pParent),
    m_pModel(pModel),
    m_pSelectedModel(NULL),
    m_pSelectedSymbol(NULL),
    m_pSelectedPage(NULL),
    m_pSelectableClass(pSelectableClass),
    m_SelectableItem(0),
    m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
    m_SymbolPath = _T("");
    m_SymbolName = _T("");
    //}}AFX_DATA_INIT
    m_Title.LoadString(nIDResTitle);
}

void ZVSelectModelSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVSelectModelSymbolDlg)
    DDX_Control(pDX, IDC_SYMBOLTREE, m_SymbolTree);
    DDX_Text(pDX, IDC_SYMBOLPATH, m_SymbolPath);
    DDX_Text(pDX, IDC_SYMBOLNAME, m_SymbolName);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectModelSymbolDlg message handlers

void ZVSelectModelSymbolDlg::OnOK()
{
    // Assign values
    if (m_SymbolTree.GetSelectedPage() != NULL)
    {
        // If the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (m_SymbolTree.GetSelectedPage() && m_SymbolTree.GetSelectedPage()->IsKindOf(m_pSelectableClass))
            {
                m_pSelectedPage = m_SymbolTree.GetSelectedPage();
                m_pSelectedModel = NULL;
                m_pSelectedSymbol = NULL;
            }

            if (m_pSelectedPage->GetModel())
            {
                m_SymbolPath = m_pSelectedPage->GetModel()->GetAbsolutePath();
                m_SymbolName = m_pSelectedPage->GetModel()->GetModelName();
            }
            else
            {
                m_SymbolPath = _T("");
                m_SymbolName = _T("");
            }
        }
        else
        {
            if (m_SelectableItem & Selectable_GraphPage)
            {
                m_pSelectedPage = m_SymbolTree.GetSelectedPage();
                m_pSelectedModel = NULL;
                m_pSelectedSymbol = NULL;

                if (m_pSelectedPage->GetModel())
                {
                    m_SymbolPath = m_pSelectedPage->GetModel()->GetAbsolutePath();
                    m_SymbolName = m_pSelectedPage->GetModel()->GetModelName();
                }
                else
                {
                    m_SymbolPath = _T("");
                    m_SymbolName = _T("");
                }
            }
            else
            {
                // Not possible, should have been checked before
                ASSERT(FALSE);
            }
        }
    }
    else
    {
        m_pSelectedSymbol = m_SymbolTree.GetSelectedSymbol();

        // If the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (m_pSelectedSymbol && m_pSelectedSymbol->IsKindOf(m_pSelectableClass))
            {
                if (m_pSelectedSymbol && ISA(m_pSelectedSymbol, PSS_Symbol))
                {
                    m_SymbolPath = ((PSS_Symbol*)m_pSelectedSymbol)->GetAbsolutePath();
                    m_SymbolName = ((PSS_Symbol*)m_pSelectedSymbol)->GetSymbolName();
                }
                else if (m_pSelectedSymbol && ISA(m_pSelectedSymbol, PSS_LinkSymbol))
                {
                    m_SymbolPath = ((PSS_LinkSymbol*)m_pSelectedSymbol)->GetAbsolutePath();
                    m_SymbolName = ((PSS_LinkSymbol*)m_pSelectedSymbol)->GetSymbolName();
                }
                else
                {
                    m_SymbolPath = _T("");
                    m_SymbolName = _T("");
                }
            }
            else
            {
                // Not possible, should have been checked before
                ASSERT(FALSE);
            }
        }
        else if (m_pSelectedSymbol && ISA(m_pSelectedSymbol, PSS_Symbol))
        {
            if (m_SelectableItem & Selectable_Symbol)
            {
                m_SymbolPath = ((PSS_Symbol*)m_pSelectedSymbol)->GetAbsolutePath();
                m_SymbolName = ((PSS_Symbol*)m_pSelectedSymbol)->GetSymbolName();
            }
            // And if contains a model
            if (((PSS_Symbol*)m_pSelectedSymbol)->GetChildModel() &&
                ISA(((PSS_Symbol*)m_pSelectedSymbol)->GetChildModel(), PSS_ProcessGraphModelMdl) &&
                !((PSS_Symbol*)m_pSelectedSymbol)->IsChildModelRef())
            {
                if (m_SelectableItem & Selectable_Model)
                {
                    // Assign the model pointer
                    m_pSelectedModel = ((PSS_Symbol*)m_pSelectedSymbol)->GetChildModel();

                    m_SymbolPath =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(((PSS_Symbol*)m_pSelectedSymbol)->GetChildModel())->GetAbsolutePath();

                    m_SymbolName =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(((PSS_Symbol*)m_pSelectedSymbol)->GetChildModel())->GetModelName();
                }
            }
        }
        else if (m_pSelectedSymbol && ISA(m_pSelectedSymbol, PSS_LinkSymbol))
        {
            if (m_SelectableItem & Selectable_LinkSymbol)
            {
                m_SymbolPath = ((PSS_LinkSymbol*)m_pSelectedSymbol)->GetAbsolutePath();
                m_SymbolName = ((PSS_LinkSymbol*)m_pSelectedSymbol)->GetSymbolName();
            }
            else
            {
                // Not possible, should have been checked before
                ASSERT(FALSE);
            }
        }
    }

    UpdateData(FALSE);

    PSS_Dialog::OnOK();
}

void ZVSelectModelSymbolDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    bool                Enable = false;
    CODModel*            pSelectedModel;
    CODSymbolComponent* pSelectedSymbol;
    ZDProcessGraphPage* pSelectedPage;

    if (m_SymbolTree.GetSelectedPage() != NULL)
    {
        pSelectedPage = m_SymbolTree.GetSelectedPage();

        // If the check must be done by runtime class
        if (m_pSelectableClass)
        {
            if (pSelectedPage && pSelectedPage->IsKindOf(m_pSelectableClass))
            {
                Enable = true;
            }
        }
        else if (m_SelectableItem & Selectable_GraphPage)
        {
            Enable = true;
        }

        pSelectedModel = NULL;
        pSelectedSymbol = NULL;

        if (pSelectedPage->GetModel())
        {
            m_SymbolPath = pSelectedPage->GetModel()->GetAbsolutePath();
            m_SymbolName = pSelectedPage->GetModel()->GetModelName();
        }
        else
        {
            m_SymbolPath = _T("");
            m_SymbolName = _T("");
        }
    }
    else
    {
        pSelectedSymbol = m_SymbolTree.GetSelectedSymbol();

        if (pSelectedSymbol && ISA(pSelectedSymbol, PSS_Symbol))
        {
            // If the check must be done by runtime class
            if (m_pSelectableClass)
            {
                if (pSelectedSymbol && pSelectedSymbol->IsKindOf(m_pSelectableClass))
                {
                    Enable = true;
                }
            }
            else if (m_SelectableItem & Selectable_Symbol)
            {
                Enable = true;
            }

            m_SymbolPath = ((PSS_Symbol*)pSelectedSymbol)->GetAbsolutePath();
            m_SymbolName = ((PSS_Symbol*)pSelectedSymbol)->GetSymbolName();

            // And if contains a model
            if (((PSS_Symbol*)pSelectedSymbol)->GetChildModel() &&
                ISA(((PSS_Symbol*)pSelectedSymbol)->GetChildModel(), PSS_ProcessGraphModelMdl) &&
                !((PSS_Symbol*)pSelectedSymbol)->IsChildModelRef())
            {
                if (!m_pSelectableClass && (m_SelectableItem & Selectable_Model))
                {
                    Enable = true;
                }

                // Assign the model pointer
                pSelectedModel = ((PSS_Symbol*)pSelectedSymbol)->GetChildModel();

                m_SymbolPath =
                    dynamic_cast<PSS_ProcessGraphModelMdl*>(((PSS_Symbol*)pSelectedSymbol)->GetChildModel())->GetAbsolutePath();

                m_SymbolName =
                    dynamic_cast<PSS_ProcessGraphModelMdl*>(((PSS_Symbol*)pSelectedSymbol)->GetChildModel())->GetModelName();
            }
        }
        else if (pSelectedSymbol && ISA(pSelectedSymbol, PSS_LinkSymbol))
        {
            // If the check must be done by runtime class
            if (m_pSelectableClass)
            {
                if (pSelectedSymbol && pSelectedSymbol->IsKindOf(m_pSelectableClass))
                {
                    Enable = true;
                }
            }
            else if (m_SelectableItem & Selectable_LinkSymbol)
            {
                Enable = true;
            }

            m_SymbolPath = ((PSS_LinkSymbol*)pSelectedSymbol)->GetAbsolutePath();
            m_SymbolName = ((PSS_LinkSymbol*)pSelectedSymbol)->GetSymbolName();
        }
        else if (!pSelectedSymbol)
        {
            if (!m_pSelectableClass &&
                m_SymbolTree.IsDocumentSelected() &&
                (m_SelectableItem & Selectable_Document))
            {
                Enable = true;
            }

            if (!m_pSelectableClass &&
                m_SymbolTree.IsRootSelected() &&
                (m_SelectableItem & Selectable_RootModel))
            {
                Enable = true;
            }
        }
    }

    UpdateData(FALSE);

    // Enable or not the ok button
    if (GetDlgItem(IDOK))
    {
        GetDlgItem(IDOK)->EnableWindow(Enable);
    }

    *pResult = 0;
}

void ZVSelectModelSymbolDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
    if (m_SymbolTree.HasContextMenu(pWnd, point) != -1)
    {
        m_SymbolTree.DisplayContextMenu(pWnd, point);

        // Done
        return;
    }
}

BOOL ZVSelectModelSymbolDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (m_pModel)
    {
        PSS_ModelSet DocumentModelSet;
        DocumentModelSet.AddModel(m_pModel);
        m_SymbolTree.Initialize(_T("Document"), &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet);
    }

    if (!m_Title.IsEmpty())
    {
        SetWindowText(m_Title);
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}
