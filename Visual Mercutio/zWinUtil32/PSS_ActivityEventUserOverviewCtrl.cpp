/****************************************************************************
 * ==> PSS_ActivityEventUserOverviewCtrl -----------------------------------*
 ****************************************************************************
 * Description : Provides an event activity user overview control           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventUserOverviewCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#endif
#ifdef _WIN32
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
BEGIN_MESSAGE_MAP(PSS_ActivityEventUserOverviewCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(ZCEventActivityUserOverview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityEventUserOverviewCtrl
//---------------------------------------------------------------------------
PSS_ActivityEventUserOverviewCtrl::PSS_ActivityEventUserOverviewCtrl(ZBEventManager* pEventManager) :
    PSS_TreeCtrl(),
    m_pEventManager(pEventManager)
{}
//---------------------------------------------------------------------------
PSS_ActivityEventUserOverviewCtrl::PSS_ActivityEventUserOverviewCtrl(const PSS_ActivityEventUserOverviewCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEventUserOverviewCtrl::~PSS_ActivityEventUserOverviewCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityEventUserOverviewCtrl& PSS_ActivityEventUserOverviewCtrl::operator = (const PSS_ActivityEventUserOverviewCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ActivityEventUserOverviewCtrl::Initialize()
{
    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();

    // load images
    LoadImageListMasked(IDB_ACTIVITYITEM, IDB_FOLDERITEM);

    // build the process array
    BuildProcessArray();

    const int processCount = m_ProcessArray.GetSize();

    for (int processIndex = 0; processIndex < processCount; ++processIndex)
    {
        HTREEITEM hRootItem = AddProcessItem(m_ProcessArray[processIndex], 0);

        for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
        {
            PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

            if (!pEvent)
                continue;

            // is the same user and folder?
            if (pEvent->GetProcessName() == m_ProcessArray[processIndex])
                AddSubItem(pEvent, hRootItem, 1);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ActivityEventUserOverviewCtrl::Initialize(ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_ActivityEventUserOverviewCtrl::GetSelectedActivityItem()
{
    HTREEITEM hSelected = GetSelectedItem();
 
    if (hSelected)
    {
        CObject* pObj = (CObject*)GetItemData(hSelected);

        if (pObj)
            return reinterpret_cast<PSS_ActivityEvent*>(pObj);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_ActivityEventUserOverviewCtrl::GetSelectedProcess()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
    {
        CObject* pObj = (CObject*)GetItemData(hSelected);

        if (!pObj)
            return GetItemText(hSelected);
    }

    return "";
}
//---------------------------------------------------------------------------
void PSS_ActivityEventUserOverviewCtrl::Refresh ()
{
    DeleteAllItems(TRUE);
    Initialize();
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ActivityEventUserOverviewCtrl::AddProcessItem(const CString& processName, int iconIndex)
{
    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = NULL;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)processName);
    curTreeItem.item.lParam         = (LPARAM)NULL;
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_ActivityEventUserOverviewCtrl::AddSubItem(PSS_ActivityEvent* pData, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pData)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pData->GetFolderName());
    curTreeItem.item.lParam         = (LPARAM)pData;
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventUserOverviewCtrl::ProcessExist(const CString& process)
{
    const int processCount = m_ProcessArray.GetSize();

    for (int i = 0; i < processCount; ++i)
        if (m_ProcessArray[i] == process)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventUserOverviewCtrl::BuildProcessArray()
{
    m_ProcessArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
    {
        PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        const CString processName = pEvent->GetProcessName();

        if (!ProcessExist(processName))
            m_ProcessArray.Add(processName);
    }
}
//---------------------------------------------------------------------------
