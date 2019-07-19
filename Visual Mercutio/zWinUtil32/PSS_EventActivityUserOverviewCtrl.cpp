/****************************************************************************
 * ==> PSS_EventActivityUserOverviewCtrl -----------------------------------*
 ****************************************************************************
 * Description : Provides an event activity user overview control           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventActivityUserOverviewCtrl.h"

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
BEGIN_MESSAGE_MAP(PSS_EventActivityUserOverviewCtrl, ZITreeCtrl)
    //{{AFX_MSG_MAP(ZCEventActivityUserOverview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventActivityUserOverviewCtrl
//---------------------------------------------------------------------------
PSS_EventActivityUserOverviewCtrl::PSS_EventActivityUserOverviewCtrl(ZBEventManager* pEventManager) :
    m_pEventManager(pEventManager)
{}
//---------------------------------------------------------------------------
PSS_EventActivityUserOverviewCtrl::PSS_EventActivityUserOverviewCtrl(const PSS_EventActivityUserOverviewCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_EventActivityUserOverviewCtrl::~PSS_EventActivityUserOverviewCtrl()
{}
//---------------------------------------------------------------------------
const PSS_EventActivityUserOverviewCtrl& PSS_EventActivityUserOverviewCtrl::operator = (const PSS_EventActivityUserOverviewCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_EventActivityUserOverviewCtrl::Initialize()
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
            ZBEventActivity* pEvent = (ZBEventActivity*)m_pEventManager->GetEventAt(i);

            if (!pEvent)
                continue;

            // is the same user and folder?
            if (pEvent->GetProcessName() == m_ProcessArray[processIndex])
                AddSubItem(pEvent, hRootItem, 1);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_EventActivityUserOverviewCtrl::Initialize(ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
ZBEventActivity* PSS_EventActivityUserOverviewCtrl::GetSelectedActivityItem()
{
    HTREEITEM hSelected = GetSelectedItem();
 
    if (hSelected)
    {
        CObject* pObj = (CObject*)GetItemData(hSelected);

        if (pObj)
            return reinterpret_cast<ZBEventActivity*>(pObj);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_EventActivityUserOverviewCtrl::GetSelectedProcess()
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
void PSS_EventActivityUserOverviewCtrl::Refresh ()
{
    DeleteAllItems(TRUE);
    Initialize();
}
//---------------------------------------------------------------------------
HTREEITEM PSS_EventActivityUserOverviewCtrl::AddProcessItem(const CString& processName, int iconIndex)
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
HTREEITEM PSS_EventActivityUserOverviewCtrl::AddSubItem(ZBEventActivity* pData, HTREEITEM hParentTreeItem, int iconIndex)
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
BOOL PSS_EventActivityUserOverviewCtrl::ProcessExist(const CString& process)
{
    const int processCount = m_ProcessArray.GetSize();

    for (int i = 0; i < processCount; ++i)
        if (m_ProcessArray[i] == process)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_EventActivityUserOverviewCtrl::BuildProcessArray()
{
    m_ProcessArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
    {
        ZBEventActivity* pEvent = (ZBEventActivity*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        const CString processName = pEvent->GetProcessName();

        if (!ProcessExist(processName))
            m_ProcessArray.Add(processName);
    }
}
//---------------------------------------------------------------------------
