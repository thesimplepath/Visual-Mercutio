/****************************************************************************
 * ==> PSS_ProcessTreeCtrl -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process tree control                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ProcessTreeCtrl.h"

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
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_ProcessTreeCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessTreeCtrl
//---------------------------------------------------------------------------
PSS_ProcessTreeCtrl::PSS_ProcessTreeCtrl(PSS_Process* pProcess) :
    PSS_TreeCtrl(),
    m_pProcess(pProcess)
{}
//---------------------------------------------------------------------------
PSS_ProcessTreeCtrl::PSS_ProcessTreeCtrl(const PSS_ProcessTreeCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ProcessTreeCtrl::~PSS_ProcessTreeCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ProcessTreeCtrl& PSS_ProcessTreeCtrl::operator = (const PSS_ProcessTreeCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::Initialize (PSS_Process* pProcess)
{
    m_pProcess = pProcess;
    FillControl();
}
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessTreeCtrl::GetSelectedProcessItem()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
        return dynamic_cast<PSS_Process*>((CObject*)GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Process* PSS_ProcessTreeCtrl::GetRootProcessItem()
{
    HTREEITEM hRoot = GetRootItem();

    if (hRoot)
        return dynamic_cast<PSS_Process*>((CObject*)GetItemData(hRoot));

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Activity* PSS_ProcessTreeCtrl::GetSelectedActivityItem()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
        return dynamic_cast<PSS_Activity*>((CObject*)GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::Refresh()
{
    DeleteAllItems();
    FillControl();
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::FillControl()
{
    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();

    // load images
    LoadImageList(IDB_IL_PROCESSITEM, 17, 1, RGB(255, 255, 255));
    AddProcess(m_pProcess, NULL, 0);

    // expand the root
    ExpandRoot();
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::AddProcess(PSS_BaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex)
{
    hParentTreeItem = AddProcessItem(pBaseActivity, hParentTreeItem, iconIndex);

    const std::size_t activityCount = pBaseActivity->GetActivityCount();

    // iterate through all activities
    for (std::size_t i = 0; i < activityCount; ++i)
    {
        // insert all pages from the template manager
        PSS_BaseActivity* pActivity = pBaseActivity->GetActivityAt(i);

        if (!pActivity)
            continue;

        if (pActivity->HasActivities())
        {
            if (pActivity->GetRunMode() == PSS_BaseActivity::IE_RM_Sequence)
                AddProcess(pActivity, hParentTreeItem, 0);
            else
                AddProcess(pActivity, hParentTreeItem, 2);
        }
        else
            AddSubItem((PSS_Activity*)pActivity, hParentTreeItem, 1);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::AddActivityItems(PSS_BaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex)
{
    const std::size_t activityCount = pBaseActivity->GetActivityCount();

    // iterate through all activities
    for (std::size_t i = 0; i < activityCount; ++i)
    {
        // insert all pages from the template manager
        PSS_Activity* pActivity = dynamic_cast<PSS_Activity*>(pBaseActivity->GetActivityAt(i));

        if (pActivity)
            AddSubItem(pActivity, hParentTreeItem, iconIndex);
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ProcessTreeCtrl::AddProcessItem(PSS_BaseActivity* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST ;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetName());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ProcessTreeCtrl::AddSubItem(PSS_Activity* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem; 
    curTreeItem.hInsertAfter        = TVI_LAST ;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetName());
    curTreeItem.item.lParam         = LPARAM(pData);
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
