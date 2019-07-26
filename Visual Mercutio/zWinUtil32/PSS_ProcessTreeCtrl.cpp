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
BEGIN_MESSAGE_MAP(PSS_ProcessTreeCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(PSS_ProcessTreeCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessTreeCtrl
//---------------------------------------------------------------------------
PSS_ProcessTreeCtrl::PSS_ProcessTreeCtrl(ZProcess* pProcess) :
    ZITreeCtrl(),
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
void PSS_ProcessTreeCtrl::Initialize (ZProcess* pProcess)
{
    m_pProcess = pProcess;
    FillControl();
}
//---------------------------------------------------------------------------
ZProcess* PSS_ProcessTreeCtrl::GetSelectedProcessItem()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
        return dynamic_cast<ZProcess*>((CObject*)GetItemData(hSelected));

    return NULL;
}
//---------------------------------------------------------------------------
ZProcess* PSS_ProcessTreeCtrl::GetRootProcessItem()
{
    HTREEITEM hRoot = GetRootItem();

    if (hRoot)
        return dynamic_cast<ZProcess*>((CObject*)GetItemData(hRoot));

    return NULL;
}
//---------------------------------------------------------------------------
ZActivity* PSS_ProcessTreeCtrl::GetSelectedActivityItem()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
        return dynamic_cast<ZActivity*>((CObject*)GetItemData(hSelected));

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
void PSS_ProcessTreeCtrl::AddProcess(ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex)
{
    hParentTreeItem = AddProcessItem(pBaseActivity, hParentTreeItem, iconIndex);

    const std::size_t activityCount = pBaseActivity->GetActivityCount();

    // iterate through all activities
    for (std::size_t i = 0; i < activityCount; ++i)
    {
        // insert all pages from the template manager
        ZBaseActivity* pActivity = pBaseActivity->GetActivityAt(i);

        if (!pActivity)
            continue;

        if (pActivity->HasActivities())
        {
            if (pActivity->GetRunMode() == SequenceRun)
                AddProcess(pActivity, hParentTreeItem, 0);
            else
                AddProcess(pActivity, hParentTreeItem, 2);
        }
        else
            AddSubItem((ZActivity*)pActivity, hParentTreeItem, 1);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessTreeCtrl::AddActivityItems(ZBaseActivity* pBaseActivity, HTREEITEM hParentTreeItem, int iconIndex)
{
    const std::size_t activityCount = pBaseActivity->GetActivityCount();

    // iterate through all activities
    for (std::size_t i = 0; i < activityCount; ++i)
    {
        // insert all pages from the template manager
        ZActivity* pActivity = dynamic_cast<ZActivity*>(pBaseActivity->GetActivityAt(i));

        if (pActivity)
            AddSubItem(pActivity, hParentTreeItem, iconIndex);
    }
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ProcessTreeCtrl::AddProcessItem(ZBaseActivity* pData, HTREEITEM hParentTreeItem, int iconIndex)
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
HTREEITEM PSS_ProcessTreeCtrl::AddSubItem(ZActivity* pData, HTREEITEM hParentTreeItem, int iconIndex)
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
