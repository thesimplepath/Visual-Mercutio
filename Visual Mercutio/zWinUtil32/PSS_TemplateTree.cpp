/****************************************************************************
 * ==> PSS_TemplateTree ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template tree                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TemplateTree.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_TemplateTree
//---------------------------------------------------------------------------
PSS_TemplateTree::PSS_TemplateTree(PSS_TreeCtrl* pTreeCtrl, PSS_TemplateManager* pTemplateManager, BOOL includeFiles) :
    m_pTreeCtrl(pTreeCtrl),
    m_pTemplateManager(pTemplateManager),
    m_IncludeFiles(includeFiles),
    m_Invalid(false)
{}
//---------------------------------------------------------------------------
PSS_TemplateTree::PSS_TemplateTree(const PSS_TemplateTree& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TemplateTree::~PSS_TemplateTree()
{}
//---------------------------------------------------------------------------
const PSS_TemplateTree& PSS_TemplateTree::operator = (const PSS_TemplateTree& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_TemplateTree::Initialize(PSS_TreeCtrl* pTreeCtrl, PSS_TemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTreeCtrl        = pTreeCtrl;
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;

    if (m_pTreeCtrl)
    {
        InitializeTree();
        Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_TemplateTree::ReInitialize(PSS_TemplateManager* pTemplateManager, BOOL includeFiles)
{
    m_pTemplateManager = pTemplateManager;
    m_IncludeFiles     = includeFiles;

    if (m_pTreeCtrl)
        Refresh();
}
//---------------------------------------------------------------------------
void PSS_TemplateTree::Refresh()
{
    if (!m_pTreeCtrl)
        return;

    m_Invalid = true;
    m_pTreeCtrl->DeleteAllItems();
    m_Invalid = false;

    const std::size_t templateCount = m_pTemplateManager->GetSize();

    if (templateCount <= 0)
        return;

    // the first template directory is the root
    PSS_TemplateDir* pTemplateDir;
    HTREEITEM        hRootItem;

    // iterate through all template directories
    for (std::size_t i = 0; i < templateCount; ++i)
    {
        // insert all pages from the template manager
        pTemplateDir = m_pTemplateManager->GetTemplateDirAt(i);

        if (pTemplateDir)
        {
            hRootItem = AddRootItem (pTemplateDir, 0);

            if (!i)
            {
                m_pTreeCtrl->SelectItem(hRootItem);
                m_pTreeCtrl->EnsureVisible(hRootItem);
            }

            if (m_IncludeFiles)
                AddFileItems(pTemplateDir, hRootItem, 1);
        }
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TemplateTree::AddRootItem(PSS_TemplateDir* pData, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = NULL;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TemplateTree::AddSubItem(PSS_TemplateDir* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_TemplateTree::AddSubItem(PSS_TemplateFile* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetTitle());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return m_pTreeCtrl->InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
void PSS_TemplateTree::AddFileItems(PSS_TemplateDir* pTemplateDir, HTREEITEM hParentTreeItem, int iconIndex)
{
    PSS_TemplateFile* pTemplateFile;

    const std::size_t templateCount = pTemplateDir->GetSize();

    // iterate through all template directories
    for (std::size_t i = 0; i < templateCount; ++i)
    {
        // insert all files from the template directory
        pTemplateFile = pTemplateDir->GetTemplateFileAt(i);

        if (pTemplateFile)
            AddSubItem (pTemplateFile, hParentTreeItem, iconIndex);
    }
}
//---------------------------------------------------------------------------
CString PSS_TemplateTree::GetSelectedItemName()
{
    if (m_Invalid || !m_pTreeCtrl)
        return "";

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
        return m_pTreeCtrl->GetItemText(hSelected);

    return "";
}
//---------------------------------------------------------------------------
PSS_TemplateDir* PSS_TemplateTree::GetSelectedItemFolder()
{
    if (m_Invalid || !m_pTreeCtrl)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
    {
        if (!m_pTreeCtrl->GetRootItem())
            return NULL;

        return dynamic_cast<PSS_TemplateDir*>((CObject*)m_pTreeCtrl->GetItemData(hSelected));
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateTree::GetSelectedItemFile()
{
    if (m_Invalid || !m_pTreeCtrl)
        return NULL;

    HTREEITEM hSelected = m_pTreeCtrl->GetSelectedItem();

    if (hSelected)
    {
        if (!m_pTreeCtrl->GetRootItem())
            return NULL;

        return DYNAMIC_DOWNCAST(PSS_TemplateFile, (CObject*)m_pTreeCtrl->GetItemData(hSelected));
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateTree::SelectItemName(const CString& name)
{
    if (!m_pTreeCtrl)
        return FALSE;

    HTREEITEM hItemToSelect = m_pTreeCtrl->FindItem(name, NULL);

    if (hItemToSelect)
        return m_pTreeCtrl->SelectItem(hItemToSelect);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_TemplateTree::InitializeTree ()
{
    // set styles
    m_pTreeCtrl->HasButtons();
    m_pTreeCtrl->HasLines();
    m_pTreeCtrl->LinesAtRoot();

    // load images
    m_pTreeCtrl->LoadImageList(IDB_IL_FORMIMAGES, 17, 1, RGB(255, 255, 255));
}
//---------------------------------------------------------------------------
