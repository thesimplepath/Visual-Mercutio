/****************************************************************************
 * ==> PSS_ProjectTree -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project tree                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProjectTree.h"

// processsoft
#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\ZDDoc.h"
#include "zBaseLib\DocData.h"
#include "zBaseLib\File.h"
#include "zRes32\ZRes.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ProjectTree
//---------------------------------------------------------------------------
PSS_ProjectTree::PSS_ProjectTree(ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL visibleOnly) :
    m_pDoc(pDoc),
    m_pTreeCtrl(pTreeCtrl),
    m_VisibleOnly(visibleOnly),
    m_HasBeenInitialized(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ProjectTree::PSS_ProjectTree(const PSS_ProjectTree& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProjectTree::~PSS_ProjectTree()
{}
//---------------------------------------------------------------------------
const PSS_ProjectTree& PSS_ProjectTree::operator = (const PSS_ProjectTree& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::Initialize (ZITreeCtrl* pTreeCtrl, ZDDocument* pDoc, BOOL OnlyVisible)
{
    m_pDoc        = pDoc;
    m_pTreeCtrl   = pTreeCtrl;
    m_VisibleOnly = OnlyVisible;

    InitializeTree();
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::Empty()
{
    m_pDoc = NULL;

    if (m_pTreeCtrl)
        m_pTreeCtrl->DeleteAllItems();
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::Refresh ()
{
    if (m_pTreeCtrl)
    {
        m_pTreeCtrl->DeleteAllItems();
        CreateTree();
    }
}
//---------------------------------------------------------------------------
ZDDocumentData* PSS_ProjectTree::GetSelectedDocument()
{
    if (m_pTreeCtrl)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
        return dynamic_cast<ZDDocumentData*>((CObject*)m_pTreeCtrl->GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_ProjectTree::GetSelectedDocumentTitle()
{
    if (m_pTreeCtrl)
        return "";

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
    {
        CObject* pObj = (CObject*)m_pTreeCtrl->GetItemData(hSelected);

        if (pObj)
            return m_pTreeCtrl->GetItemText(hSelected);
    }

    return "";
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::OnFileListChanged()
{
    Refresh();
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ProjectTree::AddDocumentTypeItem(const CString& documentType, int iconIndex, HTREEITEM hParent)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParent;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)documentType);
    curTreeItem.item.lParam         = LPARAM(NULL);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ProjectTree::AddDocumentItem(ZDDocumentData* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pData)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    if (pData->IsBinaryDataValid())
        curTreeItem.item.pszText = (char*)((const char*)pData->GetStamp().GetTemplate());
    else
        curTreeItem.item.pszText = (char*)((const char*)pData->GetStamp().GetTitle());

    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::CreateTree()
{
    if (!m_pDoc || !m_pDoc->GetActiveDocumentData())
        return;

    HTREEITEM hRoot = NULL;

    if (m_pDoc->DocumentIsTemplate())
        hRoot = AddDocumentTypeItem(m_pDoc->GetStamp().GetTitle(), 0);
    else
    {
        // extract the file name
        ZFile file(m_pDoc->GetPathName());
        hRoot = AddDocumentTypeItem(file.GetFileTitle(), 0);
    }

    HTREEITEM hRootInternal = AddDocumentTypeItem(m_InternalDocumentType, 1, hRoot);
    HTREEITEM hRootExternal = AddDocumentTypeItem(m_ExternalDocumentType, 2, hRoot);

    for (std::size_t i = 0; m_pDoc && i < m_pDoc->GetDocumentDataCount(); ++i)
        if (!m_VisibleOnly || (m_VisibleOnly && m_pDoc->GetDocumentDataAt(i) && m_pDoc->GetDocumentDataAt(i)->DocumentDataIsVisible()))
            if (m_pDoc->GetDocumentDataAt(i)->IsBinaryDataValid())
                AddDocumentItem(m_pDoc->GetDocumentDataAt(i), hRootExternal, 4);
            else
            if (m_pDoc->GetDocumentDataAt(i)->IsURLData())
                AddDocumentItem(m_pDoc->GetDocumentDataAt(i), hRootExternal, 5);
            else
                AddDocumentItem(m_pDoc->GetDocumentDataAt(i), hRootInternal, 3);

    m_pTreeCtrl->ExpandBranch(hRoot, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProjectTree::InitializeTree()
{
    if (m_HasBeenInitialized || !m_pTreeCtrl)
        return;

    // set styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();

    // load images
    m_pTreeCtrl->LoadImageList(IDB_DOCUMENT_TYPES, 17, 1, RGB(255, 255, 255));
    m_InternalDocumentType.LoadString(IDS_INTERNALDOCUMENTTYPE);
    m_ExternalDocumentType.LoadString(IDS_EXTERNALDOCUMENTTYPE);
    m_HasBeenInitialized = TRUE;
}
//---------------------------------------------------------------------------
