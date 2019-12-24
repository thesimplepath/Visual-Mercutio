/****************************************************************************
 * ==> PSS_ModelTree -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic model tree interface                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ModelTree.h"

// processsoft
#include "zBaseLib\PSS_TreeCtrl.h"
#include "ZBModelSet.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "PSS_ModelObserverMsg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_ModelDocumentTreeItem = 0;
const int g_ModelPageTreeItem     = 2;
//---------------------------------------------------------------------------
// PSS_ModelTree::IData
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData() :
    m_Type(IE_DT_Unknown),
    m_pSymbol(NULL),
    m_pLinkSymbol(NULL),
    m_pGraphPage(NULL),
    m_pModel(NULL),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData(PSS_Symbol* pSymbol) :
    m_Type(IE_DT_Symbol),
    m_pSymbol(pSymbol),
    m_pLinkSymbol(NULL),
    m_pGraphPage(NULL),
    m_pModel(NULL),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData(PSS_LinkSymbol* pLinkSymbol) :
    m_Type(IE_DT_LinkSymbol),
    m_pSymbol(NULL),
    m_pLinkSymbol(pLinkSymbol),
    m_pGraphPage(NULL),
    m_pModel(NULL),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData(ZDProcessGraphPage* pGraphPage) :
    m_Type(IE_DT_GraphPage),
    m_pSymbol(NULL),
    m_pLinkSymbol(NULL),
    m_pGraphPage(pGraphPage),
    m_pModel(NULL),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData(PSS_ProcessGraphModelMdl* pModel) :
    m_Type(IE_DT_Model),
    m_pSymbol(NULL),
    m_pLinkSymbol(NULL),
    m_pGraphPage(NULL),
    m_pModel(pModel),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::IData(const CString& str) :
    m_Type(IE_DT_String),
    m_pSymbol(NULL),
    m_pLinkSymbol(NULL),
    m_pGraphPage(NULL),
    m_pModel(NULL),
    m_Str(str),
    m_Collapsed(false)
{}
//---------------------------------------------------------------------------
PSS_ModelTree::IData::~IData()
{}
//---------------------------------------------------------------------------
// PSS_ModelTree
//---------------------------------------------------------------------------
PSS_ModelTree::PSS_ModelTree(PSS_TreeCtrl*        pTreeCtrl,
                             const CString&       rootName,
                             ZBModelSet*          pModelSet,
                             UINT                 imageResID,
                             PSS_RuntimeClassSet* pSet) :
    m_hRootDocument(NULL),
    m_pModelSet(NULL),
    m_pTreeCtrl(pTreeCtrl),
    m_RootName(rootName),
    m_ImageResID(imageResID),
    m_HasBeenInitialized(FALSE),
    m_pSet(pSet)
{
    if (pModelSet)
        m_pModelSet = pModelSet->Clone();
}
//---------------------------------------------------------------------------
PSS_ModelTree::PSS_ModelTree(const PSS_ModelTree& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ModelTree::~PSS_ModelTree()
{
    // NOTE use the fully qualified name to avoid to call a pure virtual function during destruction
    PSS_ModelTree::Empty();
}
//---------------------------------------------------------------------------
const PSS_ModelTree& PSS_ModelTree::operator = (const PSS_ModelTree& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ModelTree::Initialize(PSS_TreeCtrl*        pTreeCtrl,
                               const CString&       rootName,
                               ZBModelSet*          pModelSet,
                               UINT                 imageResID,
                               PSS_RuntimeClassSet* pSet)
{
    m_pTreeCtrl  = pTreeCtrl;
    m_RootName   = rootName;
    m_ImageResID = imageResID;
    m_pSet       = pSet;

    if (pModelSet)
    {
        FreeModelSet();
        m_pModelSet = pModelSet->Clone();
    }

    // if no model set, create an empty one
    if (!ModelSetExist())
        CreateEmptyModelSet();

    InitializeTree();
    Refresh();

    pTreeCtrl->EnsureVisible(pTreeCtrl->GetRootItem());
    pTreeCtrl->SelectItem(pTreeCtrl->GetRootItem());
}
//---------------------------------------------------------------------------
void PSS_ModelTree::SetRootName(const CString& rootName)
{
    m_RootName = rootName;
}
//---------------------------------------------------------------------------
void PSS_ModelTree::Empty()
{
    FreeModelSet();

    if (m_pTreeCtrl && ::IsWindow(m_pTreeCtrl->GetSafeHwnd()))
        m_pTreeCtrl->DeleteAllItems();

    m_pTreeCtrl     = NULL;
    m_hRootDocument = NULL;

    // empty the data set
    EmptyDataSet();
}
//---------------------------------------------------------------------------
void PSS_ModelTree::Refresh()
{
    // empty the data set
    EmptyDataSet();

    if (m_pTreeCtrl)
    {
        // don't forget to save the tree state
        m_pTreeCtrl->SaveCollapsedState();
        m_pTreeCtrl->DeleteAllItems();

        m_hRootDocument = NULL;
        CreateTree();

        // on recreated, restore the initial state
        m_pTreeCtrl->RestoreCollapsedStateToTreeCtrl();

        // immediate update
        m_pTreeCtrl->RedrawWindow();
    }
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_ModelTree::GetSymbol(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = reinterpret_cast<IData*>(m_pTreeCtrl->GetItemData(hItem));

        if (!pObj)
            return NULL;

        switch (pObj->m_Type)
        {
            case IData::IE_DT_Symbol:     return pObj->m_pSymbol;
            case IData::IE_DT_LinkSymbol: return pObj->m_pLinkSymbol;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelTree::GetModel(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = reinterpret_cast<IData*>(m_pTreeCtrl->GetItemData(hItem));

        if (!pObj)
            return NULL;

        if (pObj->m_Type == IData::IE_DT_Model)
            return pObj->m_pModel;
    }

    return NULL;
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ModelTree::GetPage(HTREEITEM hItem)
{
    if (hItem)
    {
        IData* pObj = reinterpret_cast<IData*>(m_pTreeCtrl->GetItemData(hItem));

        if (!pObj)
            return NULL;

        if (pObj->m_Type == IData::IE_DT_GraphPage)
            return pObj->m_pGraphPage;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelTree::GetOwnerModel(HTREEITEM hItem)
{
    if (hItem)
    {
        PSS_ProcessGraphModelMdl* pModel = GetModel(hItem);

        if (pModel)
            return pModel;

        // check if a page is selected
        ZDProcessGraphPage* pPage = GetPage(hItem);

        // if yes, return the model
        if (pPage)
            return pPage->GetModel();

        // check if a symbol is selected
        CODSymbolComponent* pSymbol = GetSymbol(hItem);

        if (pSymbol)
        {
            PSS_Symbol*               pSym        = dynamic_cast<PSS_Symbol*>(pSymbol);
            PSS_ProcessGraphModelMdl* pGraphModel = NULL;

            if (pSym)
                pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSym->GetChildModel());

            if (pGraphModel)
                return pGraphModel;

            return GetOwnerModel(m_pTreeCtrl->GetParentItem(hItem));
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelTree::GetSelectedModel()
{
    if (m_pTreeCtrl)
        return GetModel(m_pTreeCtrl->GetSelectedItem());

    return NULL;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_ModelTree::GetSelectedSymbol()
{
    if (m_pTreeCtrl)
        return GetSymbol(m_pTreeCtrl->GetSelectedItem());

    return NULL;
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ModelTree::GetSelectedPage()
{
    if (m_pTreeCtrl)
        return GetPage(m_pTreeCtrl->GetSelectedItem());

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ModelTree::GetSelectedOwnerModel()
{
    if (m_pTreeCtrl)
        return GetOwnerModel(m_pTreeCtrl->GetSelectedItem());

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::IsRootSelected() const
{
    return (m_pTreeCtrl && m_pTreeCtrl->GetSelectedItem() == m_pTreeCtrl->GetRootItem());
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::IsDocumentSelected() const
{
    return (m_pTreeCtrl && m_pTreeCtrl->GetSelectedItem() == m_hRootDocument);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::AddModel(PSS_ProcessGraphModelMdl* pModel)
{
    // if no model set, create an empty one
    if (!ModelSetExist())
        CreateEmptyModelSet();

    if (!m_hRootDocument)
        return;

    if (m_pModelSet->FindModelIndex(pModel) != -1)
        return;

    // add the model
    m_pModelSet->AddModel(pModel);

    // insert the model in the tree
    ProcessRootModel(pModel, m_hRootDocument);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::RemoveModel(PSS_ProcessGraphModelMdl* pModel)
{
    // if no model set, nothing to remove
    if (!ModelSetExist())
        return;

    if (!m_hRootDocument)
        return;

    const int modelIndex = m_pModelSet->FindModelIndex(pModel);

    if (modelIndex == -1)
        return;

    IData* pData = FindElementFromDataSet(pModel->GetModelName());

    if (pData)
    {
        HTREEITEM hItem = m_pTreeCtrl->FindItemData(pData, NULL);

        if (hItem)
        {
            m_pTreeCtrl->DeleteItem(hItem);
            DeleteElementFromDataSet(pModel);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::AddModelSet(ZBModelSet* pModelSet)
{
    // if no model set, create an empty one
    if (!ModelSetExist())
        CreateEmptyModelSet();

    if (!m_hRootDocument)
        return;

    ProcessModelSet(pModelSet, m_hRootDocument);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::RemoveModelSet(ZBModelSet* pModelSet)
{
    // if no model set, nothing to remove
    if (!ModelSetExist())
        return;

    // todo -cFeature -oJean: Implement code here if needed
}
//---------------------------------------------------------------------------
void PSS_ModelTree::AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel, bool checkUnique)
{
    // if no model set, nothing to remove
    if (!ModelSetExist())
        return;

    if (!m_hRootDocument)
        return;

    PSS_Symbol*     pSym     = dynamic_cast<PSS_Symbol*>(pSymbol);
    PSS_LinkSymbol* pLinkSym = dynamic_cast<PSS_LinkSymbol*>(pSymbol);

    // symbol component must exist and must be a kind of symbol or link symbol
    if (!pSym && !pLinkSym)
        return;

    if (m_pSet && !SymbolIsPartOfSet(pSymbol))
        return;

    HTREEITEM hParentItem = m_hRootDocument;

    if (pModel)
    {
        IData* pData;

        if (checkUnique)
        {
            // check if already exist
            pData = FindElementFromDataSet(pSymbol);

            // if exists, do nothing
            if (pData)
                return;
        }

        ZDProcessGraphPage* pPage = NULL;

        if (pModel->GetRoot())
            pPage = pModel->GetRoot()->FindModelPage(pModel);

        // find the model
        if (pPage)
            pData = FindElementFromDataSet(pPage);
        else
            pData = FindElementFromDataSet(pModel->GetModelName());

        if (pData)
            hParentItem = m_pTreeCtrl->FindItemData(pData, HTREEITEM(NULL));

        // if not found, set the root as parent
        if (!hParentItem)
            hParentItem = m_hRootDocument;
    }

    if (!hParentItem)
        return;

    if (pSym)
    {
        // if it has a child model, but not a child model reference, iterate through the model
        if (pSym->GetChildModel() && !pSym->IsChildModelRef())
        {
            // create a root item
            HTREEITEM hRootProcess = AddSymbolItem(pSym, hParentItem);

            // run the model
            ProcessModelByPageSet(dynamic_cast<PSS_ProcessGraphModelMdl*>(pSym->GetChildModel()), hRootProcess);

            // ensure visible, and expand the new branch to make elements visible
            if (hRootProcess)
            {
                m_pTreeCtrl->EnsureVisible(hRootProcess);
                m_pTreeCtrl->ExpandBranch(hRootProcess);
            }
        }
        else
            ProcessSymbol(pSym, hParentItem);

        return;
    }

    ProcessLinkSymbol(pLinkSym, hParentItem);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    // if no model set, nothing to remove
    if (!ModelSetExist())
        return;

    if (!m_hRootDocument)
        return;

    // symbol component must exist and must be a kind of symbol or link symbol
    if (!pSymbol || (!ISA(pSymbol, PSS_Symbol) && !ISA(pSymbol, PSS_LinkSymbol)))
        return;

    IData* pData = FindElementFromDataSet(pSymbol);

    if (!pData)
        return;

    HTREEITEM hItem = m_pTreeCtrl->FindItemData(pData, HTREEITEM(NULL));

    if (hItem)
    {
        m_pTreeCtrl->DeleteItem(hItem);
        DeleteElementFromDataSet(pSymbol);
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel)
{
    // if no model set, nothing to remove
    if (!ModelSetExist())
        return;

    if (!m_hRootDocument)
        return;

    PSS_Symbol*     pSym     = dynamic_cast<PSS_Symbol*>(pSymbol);
    PSS_LinkSymbol* pLinkSym = dynamic_cast<PSS_LinkSymbol*>(pSymbol);

    // symbol component must exist and must be a kind of symbol or link symbol
    if (!pSym && !pLinkSym)
        return;

    if (m_pSet && !SymbolIsPartOfSet(pSymbol))
        return;

    HTREEITEM hParentItem = m_hRootDocument;
    IData*    pData       = FindElementFromDataSet(pSymbol);

    if (!pData)
        return;

    HTREEITEM hItem = m_pTreeCtrl->FindItemData(pData, HTREEITEM(NULL));

    if (!hItem)
        return;

    if (pSym)
        ModifySymbolItem(pSym, hItem);
    else
        ModifyLinkSymbolItem(pLinkSym, hItem);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::DoSelectSymbol()
{
    CODSymbolComponent* pComp = GetSelectedSymbol();

    if (pComp && ISA(pComp, PSS_Symbol))
    {
        // send the message
        PSS_ModelObserverMsg mdlMsg(PSS_ModelObserverMsg::IE_AT_SelectElement, NULL, NULL, pComp);
        AfxGetMainWnd()->SendMessageToDescendants(UM_ENSUREVISIBLE_SYMBOL, 0, LPARAM(&mdlMsg));
        return;
    }

    ZDProcessGraphPage* pPage = GetSelectedPage();

    if (pPage)
    {
        // send the message
        PSS_ModelObserverMsg mdlMsg(PSS_ModelObserverMsg::IE_AT_BrowseElement, NULL, NULL, pPage);
        AfxGetMainWnd()->SendMessageToDescendants(UM_OPEN_MODELPAGE, 0, LPARAM(&mdlMsg));
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::OnModelChange()
{
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_ModelTree::OnDoubleClick()
{
    PSS_ModelObserverMsg::IEActionType actionType = PSS_ModelObserverMsg::IE_AT_None;
    UINT                               message    = 0;

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(GetSelectedSymbol());

    if (pSymbol)
    {
        if (pSymbol->GetChildModel())
        {
            actionType = PSS_ModelObserverMsg::IE_AT_BrowseElement;
            message    = UM_BROWSE_SYMBOL;
        }
        else
        {
            actionType = PSS_ModelObserverMsg::IE_AT_EnsureElementVisible;
            message    = UM_ENSUREVISIBLE_SYMBOL;
        }

        // send the message
        PSS_ModelObserverMsg mdlMsg(actionType, NULL, NULL, pSymbol);
        AfxGetMainWnd()->SendMessageToDescendants(message, 0, LPARAM(&mdlMsg));
        return;
    }

    ZDProcessGraphPage* pPage = GetSelectedPage();

    if (pPage)
    {
        // send the message
        PSS_ModelObserverMsg mdlMsg(PSS_ModelObserverMsg::IE_AT_BrowseElement, NULL, NULL, pPage);
        AfxGetMainWnd()->SendMessageToDescendants(UM_OPEN_MODELPAGE, 0, LPARAM(&mdlMsg));
        return;
    }

    if (IsRootSelected() && m_pModelSet && m_pModelSet->GetModelAt(0))
    {
        // send the message
        PSS_ModelObserverMsg mdlMsg(PSS_ModelObserverMsg::IE_AT_BrowseElement, NULL, m_pModelSet->GetModelAt(0));
        AfxGetMainWnd()->SendMessageToDescendants(UM_OPEN_MODELPAGE, 0, LPARAM(&mdlMsg));
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessModelSet(ZBModelSet* pModelSet, HTREEITEM hParentTreeItem)
{
    if (!pModelSet)
        return;

    for (std::size_t i = 0; i < pModelSet->GetModelCount(); ++i)
    {
        PSS_ProcessGraphModelMdl* pModel = pModelSet->GetModelAt(i);

        if (pModel)
            ProcessRootModel(pModel, hParentTreeItem);
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessRootModel(PSS_ProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem)
{
    if (!pModel)
        return;

    HTREEITEM hRootModel = AddModelItem(pModel, hParentTreeItem);

    // if no parent, this model is the root
    if (!hParentTreeItem)
        m_hRootDocument = hRootModel;

    ProcessModelByPageSet(pModel, hRootModel);

    m_pTreeCtrl->ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessModelByPageSet(PSS_ProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem)
{
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pModel->GetPageSet();

    if (pSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            // create a root item and get the graphic model
            HTREEITEM                 hRootPage   = AddPageItem(pPage, hParentTreeItem);
            PSS_ProcessGraphModelMdl* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pPage->GetModel());

            // run the model
            if (pGraphModel)
                ProcessModel(pGraphModel, hRootPage);
        }

        return;
    }

    ProcessModel(pModel, hParentTreeItem);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessModel(PSS_ProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem)
{
    // no model, return
    if (!pModel)
        return;

    CODComponentSet* pSet           = pModel->GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent*   pComp    = pSet->GetAt(i);
        PSS_Symbol*     pSym     = dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSym = dynamic_cast<PSS_LinkSymbol*>(pComp);

        // is a kind of symbol?
        if (!pSym && !pLinkSym)
            continue;

        if (pSym)
        {
            // if contains a child model, but not a child model reference, run through the model
            if (pSym->GetChildModel() && !pSym->IsChildModelRef())
            {
                if (m_pSet && !SymbolIsPartOfSet(pComp))
                    continue;

                // create a root item
                HTREEITEM hRootProcess = AddSymbolItem(pSym, hParentTreeItem);

                // run the model
                ProcessModelByPageSet(dynamic_cast<PSS_ProcessGraphModelMdl*>(pSym->GetChildModel()), hRootProcess);
                continue;
            }

            if (m_pSet && !SymbolIsPartOfSet(pComp))
                continue;

            ProcessSymbol(pSym, hParentTreeItem);
            continue;
        }

        if (m_pSet && !SymbolIsPartOfSet(pComp))
            continue;

        ProcessLinkSymbol(pLinkSym, hParentTreeItem);
    }
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessSymbol(PSS_Symbol* pSymbol, HTREEITEM hParentTreeItem)
{
    if (!pSymbol)
        return;

    if (pSymbol->GetIconIndex() == -1)
        return;

    if (m_pSet && !SymbolIsPartOfSet(pSymbol))
        return;

    HTREEITEM hItem = AddSymbolItem(pSymbol, hParentTreeItem);

    if (hItem)
        m_pTreeCtrl->EnsureVisible(hItem);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::ProcessLinkSymbol(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem)
{
    if (!pSymbol)
        return;

    if (pSymbol->GetIconIndex() == -1)
        return;

    if (m_pSet && !SymbolIsPartOfSet(pSymbol))
        return;

    HTREEITEM hItem = AddLinkSymbolItem(pSymbol, hParentTreeItem);

    if (hItem)
        m_pTreeCtrl->EnsureVisible(hItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ModelTree::AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)name);
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(name));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ModelTree::AddModelItem(PSS_ProcessGraphModelMdl* pModel, HTREEITEM hParentTreeItem)
{
    if (!pModel)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_ModelDocumentTreeItem;
    curTreeItem.item.iSelectedImage = g_ModelDocumentTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pModel->GetModelName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pModel));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ModelTree::AddSymbolItem(PSS_Symbol* pSymbol, HTREEITEM hParentTreeItem)
{
    if (!pSymbol)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = pSymbol->GetIconIndex();
    curTreeItem.item.iSelectedImage = pSymbol->GetIconIndex();
    curTreeItem.item.pszText        = (char*)((const char*)pSymbol->GetSymbolName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pSymbol));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ModelTree::AddLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hParentTreeItem)
{
    if (!pSymbol)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = pSymbol->GetIconIndex();
    curTreeItem.item.iSelectedImage = pSymbol->GetIconIndex();
    curTreeItem.item.pszText        = (char*)((const char*)pSymbol->GetSymbolName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pSymbol));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ModelTree::AddPageItem(ZDProcessGraphPage* pPage, HTREEITEM hParentTreeItem)
{
    if (!pPage)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = g_ModelPageTreeItem;
    curTreeItem.item.iSelectedImage = g_ModelPageTreeItem;
    curTreeItem.item.pszText        = (char*)((const char*)pPage->GetPageName());
    curTreeItem.item.lParam         = LPARAM(AddDataToSet(pPage));
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_ModelTree::ModifyModelItem(PSS_ProcessGraphModelMdl* pModel, HTREEITEM hItem)
{
    if (!pModel)
        return FALSE;

    return m_pTreeCtrl->SetItemText(hItem, (char*)((const char*)pModel->GetModelName()));
}
//---------------------------------------------------------------------------
BOOL PSS_ModelTree::ModifySymbolItem(PSS_Symbol* pSymbol, HTREEITEM hItem)
{
    if (!pSymbol)
        return FALSE;

    return m_pTreeCtrl->SetItemText(hItem, (char*)((const char*)pSymbol->GetSymbolName()));
}
//---------------------------------------------------------------------------
BOOL PSS_ModelTree::ModifyLinkSymbolItem(PSS_LinkSymbol* pSymbol, HTREEITEM hItem)
{
    if (!pSymbol)
        return FALSE;

    return m_pTreeCtrl->SetItemText(hItem, (char*)((const char*)pSymbol->GetSymbolName()));
}
//---------------------------------------------------------------------------
BOOL PSS_ModelTree::ModifyPageItem(ZDProcessGraphPage* pPage, HTREEITEM hItem)
{
    if (!pPage)
        return FALSE;

    return m_pTreeCtrl->SetItemText(hItem, (char*)((const char*)pPage->GetPageName()));
}
//---------------------------------------------------------------------------
void PSS_ModelTree::CreateTree()
{
    if (!m_pModelSet)
        return;

    if (m_pModelSet && m_pModelSet->GetModelCount() > 1)
        m_hRootDocument = AddTypeItem(m_RootName, g_ModelDocumentTreeItem);
    else
        m_hRootDocument = NULL;

    ProcessModelSet(m_pModelSet, m_hRootDocument);

    // expand the root
    m_pTreeCtrl->ExpandRoot(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ModelTree::InitializeTree()
{
    if (m_HasBeenInitialized || !m_pTreeCtrl)
        return;

    // set styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();
    m_pTreeCtrl->ShowSelectionAlways();

    // load images
    m_pTreeCtrl->LoadImageList(m_ImageResID, 17, 1, RGB(255, 255, 255));
    m_HasBeenInitialized = TRUE;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::CreateEmptyModelSet()
{
    FreeModelSet();

    m_pModelSet = new ZBModelSet;

    return m_pModelSet;
}
//---------------------------------------------------------------------------
void PSS_ModelTree::FreeModelSet()
{
    if (m_pModelSet)
    {
        delete m_pModelSet;
        m_pModelSet = NULL;
    }
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::SymbolIsPartOfSet(CODComponent* pSymbol) const
{
    PSS_RuntimeClassIterator it(m_pSet);

    // iterate through the runtime class set and check if the symbol is part of it
    for (const CRuntimeClass* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        if (pSymbol->IsKindOf(pElement))
            return true;

    return false;
}
//---------------------------------------------------------------------------
void PSS_ModelTree::EmptyDataSet()
{
    IDataIterator it(&m_DataSet);

    for (IData* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
        delete pElement;

    m_DataSet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::AddDataToSet(PSS_Symbol* pElement)
{
    std::unique_ptr<IData> pData(new IData(pElement));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::AddDataToSet(PSS_LinkSymbol* pElement)
{
    std::unique_ptr<IData> pData(new IData(pElement));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::AddDataToSet(ZDProcessGraphPage* pElement)
{
    std::unique_ptr<IData> pData(new IData(pElement));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::AddDataToSet(PSS_ProcessGraphModelMdl* pElement)
{
    std::unique_ptr<IData> pData(new IData(pElement));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::AddDataToSet(const CString& element)
{
    std::unique_ptr<IData> pData(new IData(element));
    m_DataSet.Add(pData.get());
    return pData.release();
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(CODSymbolComponent* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        switch (pData->m_Type)
        {
            case IData::IE_DT_Symbol:
                if (pData->m_pSymbol == pElement)
                {
                    delete pData;
                    it.Remove();
                    return true;
                }

                continue;

            case IData::IE_DT_LinkSymbol:
                if (pData->m_pLinkSymbol == pElement)
                {
                    delete pData;
                    it.Remove();
                    return true;
                }

                continue;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(PSS_Symbol* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_Symbol && pData->m_pSymbol == pElement)
        {
            delete pData;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(PSS_LinkSymbol* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_LinkSymbol && pData->m_pLinkSymbol == pElement)
        {
            delete pData;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(ZDProcessGraphPage* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_GraphPage && pData->m_pGraphPage == pElement)
        {
            delete pData;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(PSS_ProcessGraphModelMdl* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_Model && pData->m_pModel == pElement)
        {
            delete pData;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelTree::DeleteElementFromDataSet(const CString& element)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_String && pData->m_Str == element)
        {
            delete pData;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(CODSymbolComponent* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        switch (pData->m_Type)
        {
            case IData::IE_DT_Symbol:
                if (pData->m_pSymbol == pElement)
                    return pData;

                continue;

            case IData::IE_DT_LinkSymbol:
                if (pData->m_pLinkSymbol == pElement)
                    return pData;

                continue;
        }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(PSS_Symbol* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_Symbol && pData->m_pSymbol == pElement)
            return pData;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(PSS_LinkSymbol* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_LinkSymbol && pData->m_pLinkSymbol == pElement)
            return pData;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(ZDProcessGraphPage* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_GraphPage && pData->m_pGraphPage == pElement)
            return pData;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(PSS_ProcessGraphModelMdl* pElement)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_Model && pData->m_pModel == pElement)
            return pData;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ModelTree::IData* PSS_ModelTree::FindElementFromDataSet(const CString& element)
{
    IDataIterator it(&m_DataSet);

    for (IData* pData = it.GetFirst(); pData; pData = it.GetNext())
        if (pData->m_Type == IData::IE_DT_String && pData->m_Str == element)
            return pData;

    return NULL;
}
//---------------------------------------------------------------------------
