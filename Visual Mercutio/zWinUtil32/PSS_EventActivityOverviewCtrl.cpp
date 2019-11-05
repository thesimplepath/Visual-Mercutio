/****************************************************************************
 * ==> PSS_EventActivityOverviewCtrl ---------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity overview control                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventActivityOverviewCtrl.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"

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
BEGIN_MESSAGE_MAP(PSS_EventActivityOverviewCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_EventActivityOverviewCtrl)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventActivityOverviewCtrl::IElementType
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::IElementType::IElementType(PSS_ActivityEvent* pData, IEActivityType type) :
    m_pData(pData),
    m_Type(type)
{}
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::IElementType::IElementType(const CString& name, IEActivityType type) :
    m_pData(NULL),
    m_Name(name),
    m_Type(type)
{}
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::IElementType::~IElementType()
{
    m_pData = NULL;
}
//---------------------------------------------------------------------------
// PSS_EventActivityOverviewCtrl
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::PSS_EventActivityOverviewCtrl(ZBEventManager* pEventManager) :
    PSS_TreeCtrl(),
    m_pEventManager(pEventManager)
{}
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::PSS_EventActivityOverviewCtrl(const PSS_EventActivityOverviewCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_EventActivityOverviewCtrl::~PSS_EventActivityOverviewCtrl()
{
    m_UserArray.RemoveAll();
    m_ProcessArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_EventActivityOverviewCtrl& PSS_EventActivityOverviewCtrl::operator = (const PSS_EventActivityOverviewCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::Initialize()
{
    // set styles
    HasButtons();
    HasLines();
    LinesAtRoot();

    // load images
    LoadImageListMasked(IDB_USERITEM, IDB_FOLDERITEM);

    // build arrays
    BuildUserArray();
    BuildProcessArray();

    HTREEITEM hRootItem;
    HTREEITEM hRootProcessItem;

    const int userArraySize = m_UserArray.GetSize();

    for (int mainIndex = 0; mainIndex < userArraySize; ++mainIndex)
    {
        std::unique_ptr<IElementType> pElement(new IElementType(m_UserArray[mainIndex], IElementType::IE_AT_User));
        hRootItem = AddUserItem(pElement.get(), 0);
        pElement.release();

        const int processArraySize = m_ProcessArray.GetSize();

        for (int processIndex = 0; processIndex < processArraySize; ++processIndex)
        {
            hRootProcessItem = NULL;

            const int eventCount = m_pEventManager->GetEventCount();

            for (int i = 0; i < eventCount; ++i)
            {
                PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

                if (!pEvent)
                    continue;

                // is the same process?
                if (pEvent->GetActivityEventType() == PSS_ActivityEvent::IE_AT_ToDo &&
                        !pEvent->GetProcessName().CompareNoCase(m_ProcessArray[processIndex]))
                    // is the same user and folder?
                    if (pEvent->IsInUserQueue() && !pEvent->GetUserQueue().CompareNoCase(m_UserArray[mainIndex]))
                    {
                        if (!hRootProcessItem)
                        {
                            std::unique_ptr<IElementType> pElement
                                    (new IElementType(m_ProcessArray[processIndex], IElementType::IE_AT_Process));
                            hRootProcessItem = AddProcessItem(pElement.get(), hRootItem, 1);
                            pElement.release();
                        }

                        // is the folder not already in?
                        if (!FindItem(pEvent->GetFolderName(), hRootProcessItem))
                        {
                            std::unique_ptr<IElementType> pElement(new IElementType(pEvent, IElementType::IE_AT_Activity));
                            AddSubItem(pElement.get(), hRootProcessItem, 2);
                            pElement.release();
                        }
                    }
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::Initialize(ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
    Refresh();
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_EventActivityOverviewCtrl::GetSelectedActivityItem()
{
    HTREEITEM hSelected = GetSelectedItem();

    if (hSelected)
    {
        IElementType* pObj = (IElementType*)GetItemData(hSelected);

        if (pObj && pObj->m_Type == IElementType::IE_AT_Activity)
            return pObj->m_pData;
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_EventActivityOverviewCtrl::GetSelectedUser()
{
    HTREEITEM hSelected = GetSelectedItem();

    while (hSelected)
    {
        IElementType* pObj = (IElementType*)GetItemData(hSelected);

        if (pObj && pObj->m_Type == IElementType::IE_AT_User)
            return GetItemText(hSelected);

        hSelected = GetParentItem(hSelected);
    }

    return "";
}
//---------------------------------------------------------------------------
CString PSS_EventActivityOverviewCtrl::GetSelectedProcess()
{
    HTREEITEM hSelected = GetSelectedItem();

    while (hSelected)
    {
        IElementType* pObj = (IElementType*)GetItemData(hSelected);

        if (pObj && pObj->m_Type == IElementType::IE_AT_Process)
            return GetItemText(hSelected);

        hSelected = GetParentItem(hSelected);
    }

    return "";
}
//---------------------------------------------------------------------------
CObArray& PSS_EventActivityOverviewCtrl::GetUserActivities(const CString& user)
{
    m_ActPtrArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    // iterate through events
    for (int i = 0; i < eventCount; ++i)
    {
        PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        // is the same user and not already in the array?
        if (pEvent->IsInUserQueue() && !pEvent->GetUserQueue().CompareNoCase(user))
            if (!EventExist(pEvent))
                m_ActPtrArray.Add(m_pEventManager->GetEventAt(i));
    }

    return m_ActPtrArray;
}
//---------------------------------------------------------------------------
CObArray& PSS_EventActivityOverviewCtrl::GetProcessActivities(const CString& process, const CString& user)
{
    m_ActPtrArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    // iterate through events
    for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
    {
        PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        // is same user and same process?
        if (pEvent->IsInUserQueue() && !pEvent->GetUserQueue().CompareNoCase(user) && pEvent->GetProcessName() == process)
        {
            // not already in the array?
            if (!EventExist(pEvent))
                m_ActPtrArray.Add(pEvent);
        }
    }

    return m_ActPtrArray;
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::Refresh()
{
    DeleteAllItems();

    PSS_TreeCtrl::DeleteAllItems(TRUE);

    Initialize();
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::OnDestroy()
{
    DeleteAllItems();

    PSS_TreeCtrl::OnDestroy();
}
//---------------------------------------------------------------------------
HTREEITEM PSS_EventActivityOverviewCtrl::AddUserItem(IElementType* pElement, int iconIndex)
{
    if (!pElement || pElement->m_Type != IElementType::IE_AT_User)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = NULL;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pElement->m_Name);
    curTreeItem.item.lParam         = (LPARAM)pElement;
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_EventActivityOverviewCtrl::AddProcessItem(IElementType* pElement, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pElement || pElement->m_Type != IElementType::IE_AT_Process)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pElement->m_Name);
    curTreeItem.item.lParam         = (LPARAM)pElement;    // The pointer to the element
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_EventActivityOverviewCtrl::AddSubItem(IElementType* pElement, HTREEITEM hParentTreeItem, int iconIndex)
{
    if (!pElement || pElement->m_Type != IElementType::IE_AT_Activity)
        return NULL;

    if (!pElement->m_pData)
        return NULL;

    TV_INSERTSTRUCT curTreeItem;
    curTreeItem.hParent             = hParentTreeItem;
    curTreeItem.hInsertAfter        = TVI_LAST;
    curTreeItem.item.iImage         = iconIndex;
    curTreeItem.item.iSelectedImage = iconIndex;
    curTreeItem.item.pszText        = (char*)((const char*)pElement->m_pData->GetFolderName());
    curTreeItem.item.lParam         = (LPARAM)pElement;
    curTreeItem.item.mask           = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    return InsertItem(&curTreeItem);
}
//---------------------------------------------------------------------------
CString PSS_EventActivityOverviewCtrl::FormatActivityText(PSS_ActivityEvent* pData)
{
    CString processNameLabel;
    processNameLabel.LoadString(IDS_COLUMN2_EVENTREMINDER);

    CString activityNameLabel;
    activityNameLabel.LoadString(IDS_COLUMN3_EVENTREMINDER);

    char buffer[100];
    sprintf_s(buffer,
              _tcslen(buffer),
              "%s: %s - %s: %s",
              (const char*)processNameLabel,
              (const char*)pData->GetProcessName(),
              (const char*)activityNameLabel,
              (const char*)pData->GetActivityName());

    return buffer;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityOverviewCtrl::UserExist(const CString& user)
{
    const int count = m_UserArray.GetSize();

    for (int i = 0; i < count; ++i)
        if (!m_UserArray[i].CompareNoCase(user))
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityOverviewCtrl::ProcessExist(const CString& process)
{
    const int count = m_ProcessArray.GetSize();

    for (int i = 0; i < count; ++i)
        if (!m_ProcessArray[i].CompareNoCase(process))
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityOverviewCtrl::EventExist(PSS_ActivityEvent* pActEvent)
{
    const int count = m_ActPtrArray.GetSize();

    for (int i = 0; i < count; ++i)
        if (m_ActPtrArray[i] == pActEvent)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::BuildUserArray()
{
    m_UserArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
    {
        PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        // is a todo activity?
        if (pEvent->GetActivityEventType() != PSS_ActivityEvent::IE_AT_ToDo)
            continue;

        if (!pEvent->IsInUserQueue())
            continue;

        const CString user = pEvent->GetUserQueue();

        if (!UserExist(user))
            m_UserArray.Add(user);
    }
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::BuildProcessArray()
{
    m_ProcessArray.RemoveAll();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
    {
        PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)m_pEventManager->GetEventAt(i);

        if (!pEvent)
            continue;

        // is a todo activity?
        if (pEvent->GetActivityEventType() != PSS_ActivityEvent::IE_AT_ToDo)
            continue;

        const CString processName = pEvent->GetProcessName();

        if (!ProcessExist(processName))
            m_ProcessArray.Add(processName);
    }
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::DeleteAllItems()
{
    DeleteAllItems(GetRootItem());
}
//---------------------------------------------------------------------------
void PSS_EventActivityOverviewCtrl::DeleteAllItems(HTREEITEM hTreeItem)
{
    if (!hTreeItem)
        return;

    // delete all element type
    do
    {
        IElementType* pObj = (IElementType*)GetItemData(hTreeItem);

        if (pObj)
            delete pObj;

        if (ItemHasChildren(hTreeItem))
            DeleteAllItems(GetChildItem(hTreeItem));
    }
    while (hTreeItem = GetNextSiblingItem(hTreeItem));
}
//---------------------------------------------------------------------------
