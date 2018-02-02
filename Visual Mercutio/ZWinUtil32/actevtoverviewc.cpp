// Source file: ActEvtOverviewC.cpp

#include <StdAfx.h>

// ActEvtC
#include "ActEvtOverviewC.h"
// The tokenizer
#include "zBaseLib\ZBTokenizer.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZCEventActivityOverview, ZITreeCtrl)
	//{{AFX_MSG_MAP(ZCEventActivityOverview)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ElementType 


ZCEventActivityOverview::ElementType::ElementType( ZBEventActivity* pData /*= NULL*/, ActivityType Type /*= Activity*/ )
: m_pData(pData), m_Type(Type)
{
}
ZCEventActivityOverview::ElementType::ElementType( const CString Name, ActivityType Type )
: m_pData(NULL), m_Type(Type), m_Name(Name)
{
}

ZCEventActivityOverview::ElementType::~ElementType()
{
	m_pData = NULL;
}

// Class ZCEventActivityOverview 


ZCEventActivityOverview::ZCEventActivityOverview (ZBEventManager* pEventManager)
      : m_pEventManager(pEventManager)
{
}


ZCEventActivityOverview::~ZCEventActivityOverview()
{
	m_UserArray.RemoveAll();
	m_ProcessArray.RemoveAll();
}

void ZCEventActivityOverview::DeleteAllElements()
{
	DeleteAllSubElements( GetRootItem() );
}

void ZCEventActivityOverview::DeleteAllSubElements( HTREEITEM hTreeItem )
{
	// Delete all element type
	if (!hTreeItem)
		return;

	do
	{
		ElementType*	pObj = (ElementType*)GetItemData( hTreeItem );
		if (pObj != NULL)
		{
			delete pObj;
			pObj = NULL;
		}
		if (ItemHasChildren( hTreeItem ))
		{
			DeleteAllSubElements( GetChildItem( hTreeItem ) );
		}
	}
	while( (hTreeItem = GetNextSiblingItem( hTreeItem )) != NULL );
}


void ZCEventActivityOverview::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
	ZCEventActivityOverview::Refresh();
}

void ZCEventActivityOverview::Refresh ()
{
	DeleteAllElements();
	DeleteAllItems( TRUE );
	ZCEventActivityOverview::Initialize();
}

void ZCEventActivityOverview::Initialize ()
{
	// Sets styles
	HasButtons();
	HasLines();
	LinesAtRoot();
	// Load images
	LoadImageListMasked( IDB_USERITEM, IDB_FOLDERITEM );

	// Build User Array
	BuildUserArray();
	// Build Process Array
	BuildProcessArray();
	HTREEITEM hRootItem;
	HTREEITEM hRootProcessItem;
	for (int MainIndex = 0; MainIndex < m_UserArray.GetSize(); ++MainIndex)
	{
		ElementType*	pElement = new ElementType( m_UserArray[MainIndex], ElementType::User );
		hRootItem = AddUserItem (pElement, 0);
		for (int ProcessIndex = 0; ProcessIndex < m_ProcessArray.GetSize(); ++ProcessIndex)
		{
			hRootProcessItem = NULL;
			for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
			{
				// If the same process
				if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetActivityEventType() == ToDoActivity &&
					((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName().CompareNoCase( m_ProcessArray[ProcessIndex] ) == 0)
				{
					// If the same user and the same folder
					if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->IsInUserQueue() && 
					    ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetUserQueue().CompareNoCase( m_UserArray[MainIndex] ) == 0)
					{
						if (hRootProcessItem == NULL)
						{
							ElementType*	pElement = new ElementType( m_ProcessArray[ProcessIndex], ElementType::Process );
							hRootProcessItem = AddProcessItem (pElement, hRootItem, 1);
						}
						// If the folder is not alread in
						if (FindItem( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetFolderName(), hRootProcessItem ) == NULL)
						{
							ElementType*	pElement = new ElementType( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))), ElementType::Activity );
							AddSubItem( pElement, hRootProcessItem, 2 );
						}
					}
/*					
					// For multi-user mode, run through all receiver
					ZBTokenizer	Tokenizer( ';' );
					CString	Token = Tokenizer.GetFirstToken( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetReceiver() );
					while (!Token.IsEmpty())
					{
						if (Token.CompareNoCase( m_UserArray[MainIndex] ) == 0)
						{
							if (hRootProcessItem == NULL)
							{
								ElementType*	pElement = new ElementType( m_ProcessArray[ProcessIndex], ElementType::Process );
								hRootProcessItem = AddProcessItem (pElement, hRootItem, 1);
							}
							// If the folder is not alread in
							if (FindItem( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetFolderName(), hRootProcessItem ) == NULL)
							{
								ElementType*	pElement = new ElementType( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))), ElementType::Activity );
								AddSubItem( pElement, hRootProcessItem, 2 );
							}
						}
						Token = Tokenizer.GetNextToken();
					}
*/
				}
			}
		}
	}
}

void ZCEventActivityOverview::BuildUserArray()
{
	m_UserArray.RemoveAll();
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		// For todo activity only
		if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetActivityEventType() == ToDoActivity)
		{
/*
			// For multi-user mode, run through all senders
			ZBTokenizer	Tokenizer( ';' );
			CString	Token = Tokenizer.GetFirstToken( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetReceiver() );
			while (!Token.IsEmpty())
			{
				// Make the string lower case
				Token.MakeLower();
				// Dispatch to the first
				if (!UserExist( Token ))
					m_UserArray.Add( Token );
				Token = Tokenizer.GetNextToken();
			}
*/
			if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->IsInUserQueue() && 
				!UserExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetUserQueue() ))
				m_UserArray.Add( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetUserQueue() );
		}
	}
}

void ZCEventActivityOverview::BuildProcessArray()
{
	m_ProcessArray.RemoveAll();
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		// For todo activity only
		if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetActivityEventType() == ToDoActivity)
		{
			if (!ProcessExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() ))
				m_ProcessArray.Add( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() );
		}
	}

}

BOOL ZCEventActivityOverview::UserExist( const CString User )
{
	for (int i = 0; i < m_UserArray.GetSize(); ++i)
		if (m_UserArray[i].CompareNoCase( User ) == 0)
			return TRUE;
	return FALSE;
}

BOOL ZCEventActivityOverview::ProcessExist( const CString Process )
{
	for (int i = 0; i < m_ProcessArray.GetSize(); ++i)
		if (m_ProcessArray[i].CompareNoCase( Process ) == 0)
			return TRUE;
	return FALSE;
}


BOOL ZCEventActivityOverview::EventPtrExist( ZBEventActivity* pActEvent )
{
	for (int i = 0; i < m_ActPtrArray.GetSize(); ++i)
		if (m_ActPtrArray[i] == pActEvent)
			return TRUE;
	return FALSE;
}

HTREEITEM ZCEventActivityOverview::AddUserItem (ElementType* pElement, int IconIndex)
{
	if (pElement->m_Type != ElementType::User)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = NULL; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)pElement->m_Name);
	curTreeItem.item.lParam = (LPARAM)pElement;	// The pointer to the element
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return this->InsertItem( &curTreeItem );
}

HTREEITEM	ZCEventActivityOverview::AddProcessItem (ElementType* pElement, HTREEITEM hParentTreeItem, int IconIndex)
{
	if (pElement->m_Type != ElementType::Process)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)pElement->m_Name);
	curTreeItem.item.lParam = (LPARAM)pElement;	// The pointer to the element
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return this->InsertItem(&curTreeItem);
}

HTREEITEM ZCEventActivityOverview::AddSubItem (ElementType* pElement, HTREEITEM hParentTreeItem, int IconIndex)
{
	if (pElement->m_Type != ElementType::Activity)
		return NULL;
	if (!pElement->m_pData)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)pElement->m_pData->GetFolderName());
	curTreeItem.item.lParam = (LPARAM)pElement;
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return this->InsertItem(&curTreeItem);
}



ZBEventActivity* ZCEventActivityOverview::GetSelectedActivityItem ()
{
	HTREEITEM hSelected = GetSelectedItem();
	if (hSelected)
	{
		ElementType*	pObj = (ElementType*)GetItemData( hSelected );
		if (pObj != NULL && pObj->m_Type == ElementType::Activity)
			return pObj->m_pData;
	}
	return NULL;
}

CString	ZCEventActivityOverview::FormatActivityText(ZBEventActivity* pData)
{
	CString	ProcessNameLabel;
	ProcessNameLabel.LoadString( IDS_COLUMN2_EVENTREMINDER );
	CString	ActivityNameLabel;
	ActivityNameLabel.LoadString( IDS_COLUMN3_EVENTREMINDER );
	char	Buffer[100];
	sprintf( Buffer, "%s: %s - %s: %s", (const char*)ProcessNameLabel, (const char*)pData->GetProcessName(),
										(const char*)ActivityNameLabel, (const char*)pData->GetActivityName());
	return Buffer;
}

CString	ZCEventActivityOverview::GetSelectedUser()
{
	HTREEITEM hSelected = GetSelectedItem();
	while (hSelected != NULL)
	{
		ElementType*	pObj = (ElementType*)GetItemData( hSelected );
		if (pObj && pObj->m_Type == ElementType::User)
			return GetItemText( hSelected );
		hSelected = GetParentItem( hSelected );
	}
	return "";
}

CString	ZCEventActivityOverview::GetSelectedProcess()
{
	HTREEITEM hSelected = GetSelectedItem();
	while (hSelected != NULL)
	{
		ElementType*	pObj = (ElementType*)GetItemData( hSelected );
		if (pObj && pObj->m_Type == ElementType::Process)
			return GetItemText( hSelected );
		hSelected = GetParentItem( hSelected );
	}
	return "";
}


CObArray&	ZCEventActivityOverview::GetUserActivities(const CString User)
{
	m_ActPtrArray.RemoveAll();
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		// If same user
		if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->IsInUserQueue() && 
			((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetUserQueue().CompareNoCase( User ) == 0)
		{
			// If not already in the array
			if (!EventPtrExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))) ))
				m_ActPtrArray.Add( m_pEventManager->GetEventAt(i) );
		}

/*
		// For multi-user mode, run through all senders
		ZBTokenizer	Tokenizer( ';' );
		CString	Token = Tokenizer.GetFirstToken( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetReceiver() );
		while (!Token.IsEmpty())
		{
			// if for requested user
			if (Token.CompareNoCase( User ) == 0)
			{
				if (!EventPtrExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))) ))
					m_ActPtrArray.Add( m_pEventManager->GetEventAt(i) );
			}
			// Get next token
			Token = Tokenizer.GetNextToken();
		}
*/
	}
	return m_ActPtrArray;
}

CObArray&	ZCEventActivityOverview::GetProcessActivities(const CString Process, const CString User)
{
	m_ActPtrArray.RemoveAll();
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		// If same user and same process
		if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->IsInUserQueue() && 
			((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetUserQueue().CompareNoCase( User ) == 0 &&
			((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() == Process)
		{
			// If not already in the array
			if (!EventPtrExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))) ))
				m_ActPtrArray.Add( m_pEventManager->GetEventAt(i) );
		}
/*
		// For multi-user mode, run through all senders
		ZBTokenizer	Tokenizer( ';' );
		CString	Token = Tokenizer.GetFirstToken( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetReceiver() );
		while (!Token.IsEmpty())
		{
			// if for requested user and
			// process name
			if (Token.CompareNoCase( User ) == 0 && 
				((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() == Process)
			{
				if (!EventPtrExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))) ))
					m_ActPtrArray.Add( m_pEventManager->GetEventAt(i) );
			}
			// Get next token
			Token = Tokenizer.GetNextToken();
		}
*/
	}
	return m_ActPtrArray;
}

void ZCEventActivityOverview::OnDestroy() 
{
	DeleteAllElements();
	ZITreeCtrl::OnDestroy();
}
