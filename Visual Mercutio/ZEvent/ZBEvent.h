// ZBEvent.h: interface for the ZBEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEVENT_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBEVENT_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zBaseLib\ZIListCtrl.h"
#include "zBaseLib\ZBDate.h"

const	int	EVT_UNDEFINED = 0;
const	int	EVT_SERVER = 1;
const	int	EVT_ACTIVITY = 2;
const	int	EVT_REMINDER = 3;
const	int	EVT_OVERVIEW = 4;

const	char	EventDateTimeFormatString[] = "%d.%m.%Y - %H:%M:%S";
const	char	EventDateFormatString[] = "%d.%m.%Y";


#ifdef _ZEVENTEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBEvent : public CObject  
{
public:
// Inherited feature
	typedef CObject inherited;
	DECLARE_DYNAMIC(ZBEvent)
public:
	ZBEvent();
	ZBEvent( COleDateTime Time, int EventID = EVT_UNDEFINED, CString UserQueue = "" );
	virtual ~ZBEvent();
    ZBEvent(const ZBEvent &right);
    const ZBEvent & operator=(const ZBEvent &right);
	ZBDate			GetTimeStamp() const { return m_TimeStamp; };
	CString			GetFormatedTimeStamp() { return m_TimeStamp.Format( EventDateTimeFormatString ); };
	int				GetEventID() const { return m_EventID; };
	CString			GetEventIDStr() const;

	CString			GetUserQueue() const { return m_UserQueue; };
	void			SetUserQueue(const CString value) { m_UserQueue = value; };
	BOOL			IsInUserQueue() const { return m_UserQueue.IsEmpty() != TRUE; };

	BOOL			ParseDateTime(COleDateTime& Date, CString& value);
#ifdef _WIN32
	AFX_EXT_API	friend	ZBEvent&	operator>>( ZBEvent& left, ZIListCtrl& listCtrl );
#endif

protected:
	ZBDate			m_TimeStamp;
	int				m_EventID;
	CString			m_UserQueue;
};


//#undef  AFX_DATA
//#define AFX_DATA


#endif // !defined(AFX_ZBEVENT_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
