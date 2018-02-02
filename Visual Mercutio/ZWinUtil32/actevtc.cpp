// Source file: ActEvtC.cpp

#include <StdAfx.h>

// ActEvtC
#include "ActEvtC.h"
#include "zEvent\BActVt.h"
#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#include "zEvent\ZProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int _gEventActivityColText[] = { IDS_NOCOLUMNHEADER, IDS_COLUMN12_EVENTACTIVITY, IDS_COLUMN15_EVENTACTIVITY,
										IDS_COLUMN0_EVENTACTIVITY, IDS_COLUMN1_EVENTACTIVITY, IDS_COLUMN2_EVENTACTIVITY, IDS_COLUMN3_EVENTACTIVITY, IDS_COLUMN4_EVENTACTIVITY, 
										IDS_COLUMN5_EVENTACTIVITY, IDS_COLUMN6_EVENTACTIVITY, IDS_COLUMN7_EVENTACTIVITY, IDS_COLUMN8_EVENTACTIVITY, 
										IDS_COLUMN9_EVENTACTIVITY, IDS_COLUMN10_EVENTACTIVITY, IDS_COLUMN11_EVENTACTIVITY, IDS_COLUMN14_EVENTACTIVITY,
										IDS_COLUMN13_EVENTACTIVITY };
static int _gEventActivityColSize[] = { 20,		// The action icon
										130,	// The action text
										100,	// The activity type
										150,	// Time
										100,	// FolderName
										100, 	// ProcessName
										100, 	// ProcessCreationDate
										100, 	// ProcessDueDate
										100, 	// ActivityName
										100, 	// ActivityCreationDate
										100, 	// ActivityDueDate
										100, 	// Sender    
										100, 	// Receiver
										200, 	// ProcessFilename
										200, 	// ExchangeDataFilename
										200, 	// Process ExchangeDataFilename
										1000 };	// Comments


BEGIN_MESSAGE_MAP(ZCEventActivityLog, ZIListCtrl)
	//{{AFX_MSG_MAP(ZCEventActivityLog)
	ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCEventActivityLog 


ZCEventActivityLog::ZCEventActivityLog (ZBEventManager* pEventManager)
      : m_pEventManager(pEventManager), m_ColumnsHasBeenBuilt(FALSE)
{
}


ZCEventActivityLog::~ZCEventActivityLog()
{
}



void ZCEventActivityLog::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
	ZCEventActivityLog::Refresh();
}

void ZCEventActivityLog::Refresh ()
{
	DeleteAllItems();
	// If the columns were never built
	if (!ColumnsHasBeenBuilt())
		BuildColumns();
	if (m_pEventManager)
	{
		for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
			((ZBEventActivity&)*(m_pEventManager->GetEventAt(i))) >> *this;
	}
}

ZBEventActivity*	ZCEventActivityLog::GetSelectedItem() const
{
	int	Index;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)     
	{
		Index = GetNextSelectedItem( pos );
		return (ZBEventActivity*)GetItemData( Index );
	}
	return NULL;
}

BOOL	ZCEventActivityLog::BuildColumns()
{
	// Load images
	LoadImageListMasked( IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT );
	ZIListCtrl::SetEnableOver( TRUE );
	ZIListCtrl::SetFullRowSelect( TRUE );
	ZIListCtrl::EnableSort( TRUE );

	ZIListCtrl::BuildColumns(17, _gEventActivityColSize, _gEventActivityColText);
	m_ColumnsHasBeenBuilt = TRUE;
	return TRUE;
}

ZBEventActivity&	operator>>( ZBEventActivity& left, ZCEventActivityLog& listCtrl )
{
	int	Index = listCtrl.GetItemCount();
	int	ImageIndex = 13;
	if (left.GetActivityEventType() != MessageActivity)
	{
		if (left.GetActivityStatus() == ActivityStatusProcessPaused)
			ImageIndex = 12;
		else
		if (left.GetActivityStatus() == ActivityStatusProcessAborted)
			ImageIndex = 4;
		else
		if (left.GetActivityStatus() == ActivityStatusProcessCompleted)
			ImageIndex = 5;
		else
		if (left.GetActivityStatus() == ActivityStatusRequestAcceptation)
			ImageIndex = 8;
		else
		if (left.GetActivityStatus() == ActivityStatusAccepted)
			ImageIndex = 7;
		else
		if (left.GetActivityStatus() == ActivityStatusRejected)
			ImageIndex = 6;
		else
		if (left.GetActivityStatus() == ActivityStatusAttribution)
			ImageIndex = 3;
		else
		if (left.GetActivityStatus() == ActivityStatusSent)
			ImageIndex = 0;
		else
		if (left.GetActivityStatus() == ActivityStatusAttribution)
			ImageIndex = 7;
		else
			ImageIndex = 11;
	}
	// Add the action icon
	listCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
						 NULL,
						 0, 0, 
						 ImageIndex, 
						 (LPARAM)&left);
	// Add the action text
	listCtrl.SetItem( Index, 1, LVIF_TEXT,
					  ZProcess::GetStatusString( left.GetActivityStatus() ),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the Activity Type
	listCtrl.SetItem( Index, 2, LVIF_TEXT,
					  left.GetActivityType(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the event Date
	listCtrl.SetItem( Index, 3, LVIF_TEXT,
					  left.GetFormatedTimeStamp(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the folder name
	listCtrl.SetItem( Index, 4, LVIF_TEXT,
					  left.GetFolderName(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the process name
	listCtrl.SetItem( Index, 5, LVIF_TEXT,
					  left.GetProcessName(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the process creation date
	listCtrl.SetItem( Index, 6, LVIF_TEXT,
					  left.GetFormatedProcessCreationDate(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the process due date
	listCtrl.SetItem( Index, 7, LVIF_TEXT,
					  left.GetFormatedProcessDueDate(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the activity name
	listCtrl.SetItem( Index, 8, LVIF_TEXT,
					  left.GetActivityName(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the activity creation date
	listCtrl.SetItem( Index, 9, LVIF_TEXT,
					  left.GetFormatedActivityCreationDate(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the activity due date
	listCtrl.SetItem( Index, 10, LVIF_TEXT,
					  left.GetFormatedActivityDueDate(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the sender name
	listCtrl.SetItem( Index, 11, LVIF_TEXT,
					  left.GetSender(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the receiver name
	listCtrl.SetItem( Index, 12, LVIF_TEXT,
					  left.GetReceiver(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the process filename
	listCtrl.SetItem( Index, 13, LVIF_TEXT,
					  left.GetProcessFilename(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the exchange date filename
	listCtrl.SetItem( Index, 14, LVIF_TEXT,
					  left.GetExchangeDataFilename(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the process exchange date filename
	listCtrl.SetItem( Index, 15, LVIF_TEXT,
					  left.GetProcessExchangeDataFilename(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	// Add the comments
	listCtrl.SetItem( Index, 16, LVIF_TEXT,
					  left.GetComments(),
					  0, LVIF_TEXT, LVIF_TEXT, 0 );
	return left;
}

LRESULT ZCEventActivityLog::OnNewActivityEvent( WPARAM wParam, LPARAM lParam ) 
{
	ZBEventActivity*	pEvent = (ZBEventActivity*)lParam;

	// If the columns were never built
	if (!ColumnsHasBeenBuilt())
		BuildColumns();
	*pEvent >> *this;
	return 0;
}
