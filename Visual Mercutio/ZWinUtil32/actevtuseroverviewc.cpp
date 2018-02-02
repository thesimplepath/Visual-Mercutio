// Source file: ActEvtUserOverviewC.cpp

#include <StdAfx.h>

// ActEvtC
#include "ActEvtUserOverviewC.h"
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

BEGIN_MESSAGE_MAP(ZCEventActivityUserOverview, ZITreeCtrl)
	//{{AFX_MSG_MAP(ZCEventActivityUserOverview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCEventActivityUserOverview 


ZCEventActivityUserOverview::ZCEventActivityUserOverview (ZBEventManager* pEventManager)
      : m_pEventManager(pEventManager)
{
}


ZCEventActivityUserOverview::~ZCEventActivityUserOverview()
{
}



void ZCEventActivityUserOverview::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
	ZCEventActivityUserOverview::Refresh();
}

void ZCEventActivityUserOverview::Refresh ()
{
	DeleteAllItems( TRUE );
	ZCEventActivityUserOverview::Initialize();
}

void ZCEventActivityUserOverview::Initialize ()
{
	// Sets styles
	HasButtons();
	HasLines();
	LinesAtRoot();
	// Load images
	LoadImageListMasked( IDB_ACTIVITYITEM, IDB_FOLDERITEM );

	// Build Process Array
	BuildProcessArray();
	HTREEITEM hRootItem;
	for (int ProcessIndex = 0; ProcessIndex < m_ProcessArray.GetSize(); ++ProcessIndex)
	{
		hRootItem = AddProcessItem (m_ProcessArray[ProcessIndex], 0);
		for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
		{
			// If the same user and the same folder
			if (((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() == m_ProcessArray[ProcessIndex])
			{
				AddSubItem( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i))), hRootItem, 1 );
			}
		}
	}
}

void ZCEventActivityUserOverview::BuildProcessArray()
{
	m_ProcessArray.RemoveAll();
	for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
	{
		if (!ProcessExist( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() ))
			m_ProcessArray.Add( ((ZBEventActivity*)(m_pEventManager->GetEventAt(i)))->GetProcessName() );
	}

}

BOOL ZCEventActivityUserOverview::ProcessExist( const CString Process )
{
	for (int i = 0; i < m_ProcessArray.GetSize(); ++i)
		if (m_ProcessArray[i] == Process)
			return TRUE;
	return FALSE;
}

HTREEITEM ZCEventActivityUserOverview::AddProcessItem (const CString ProcessName, int IconIndex)
{
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = NULL; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)ProcessName);
	curTreeItem.item.lParam = (LPARAM)NULL;	// Does not represent a selectable item
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return this->InsertItem( &curTreeItem );
}

HTREEITEM ZCEventActivityUserOverview::AddSubItem (ZBEventActivity* pData, HTREEITEM hParentTreeItem, int IconIndex)
{
	if (!pData)
		return NULL;
	TV_INSERTSTRUCT     curTreeItem;

	curTreeItem.hParent = hParentTreeItem; 
	curTreeItem.hInsertAfter = TVI_LAST ;
	curTreeItem.item.iImage = IconIndex;
	curTreeItem.item.iSelectedImage = IconIndex;
	curTreeItem.item.pszText = (char*)((const char*)pData->GetFolderName());
	curTreeItem.item.lParam = (LPARAM)pData;
	curTreeItem.item.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	return this->InsertItem(&curTreeItem);
}



ZBEventActivity* ZCEventActivityUserOverview::GetSelectedActivityItem ()
{
	HTREEITEM hSelected = GetSelectedItem();
	if (hSelected)
	{
		CObject*	pObj = (CObject*)GetItemData( hSelected );
		if (pObj != NULL)
			return reinterpret_cast<ZBEventActivity*>( pObj );
	}
	return NULL;
}

CString	ZCEventActivityUserOverview::GetSelectedProcess()
{
	HTREEITEM hSelected = GetSelectedItem();
	if (hSelected)
	{
		CObject*	pObj = (CObject*)GetItemData( hSelected );
		if (pObj == NULL)
			return GetItemText( hSelected );
	}
	return "";
}
