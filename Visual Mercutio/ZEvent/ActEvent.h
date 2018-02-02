// ActEvent.h: interface for the ZBEventActivity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEventActivity_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBEventActivity_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

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


#include "ZBEvent.h"

enum	ActivityEventType { InvalidActivityEvent, 
							ToDoActivity, 
							MessageActivity,
							DeleteToDoEvent,
							LogActivityEvent,
							DeleteFileEvent,
							FindProcessStateEvent,
							FindProcessesInitiatedEvent };
// Priorities flags
const	char	EventPriorityHigh[] = "HG";
const	char	EventPriorityMedium[] = "MD";
const	char	EventPriorityLow[] = "LW";

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


class AFX_EXT_CLASS ZBEventActivity : public ZBEvent  
{
public:
// Inherited feature
	typedef ZBEvent inherited;
	DECLARE_DYNAMIC(ZBEventActivity)
public:
	ZBEventActivity();
	ZBEventActivity( ActivityEventType EventType,
					 CString Filename,
					 COleDateTime Time, 
					 CString FolderName,
					 CString ProcessName,
					 COleDateTime ProcessCreationDate,
					 COleDateTime ProcessDueDate,
					 CString ActivityType,
					 CString ActivityName,
					 COleDateTime ActivityCreationDate,
					 COleDateTime ActivityDueDate,
					 CString Sender,
					 CString Receiver,
					 CString ProcessFilename,
					 CString ExchangeDataFilename,
					 CString ProcessExchangeDataFilename,
					 CString ActivityStatus,
					 CString Comments,
					 BOOL	 IsInBackup = FALSE);
	ZBEventActivity* Clone();
	virtual ~ZBEventActivity();
	// Event Type
	ActivityEventType	GetActivityEventType() const { return m_ActivityEventType; };
	CString				GetActivityEventTypeString() const;
	void				SetActivityEventType(ActivityEventType value) { m_ActivityEventType = value; };
	void				SetActivityEventType(const CString value);

	// The extension type
	CString			GetFileExtension( int EventType = -1 ) const;

	// Process Name
	CString			GetFolderName() const { return m_FolderName; };
	void			SetFolderName(const CString value) { m_FolderName = value; };

	// Process Name
	CString			GetFilename() const { return m_Filename; };
	void			SetFilename(const CString value) { m_Filename = value; };

	// Process Name
	CString			GetProcessName() const { return m_ProcessName; };
	void			SetProcessName(const CString value) { m_ProcessName = value; };

	// Activity Name
	CString			GetActivityName() const { return m_ActivityName; };
	void			SetActivityName(const CString value) { m_ActivityName = value; };

	// Process Creation Date
	ZBDate			GetProcessCreationDate() const { return m_ProcessCreationDate; };
	void			SetProcessCreationDate(const COleDateTime time) { m_ProcessCreationDate = time; };
	int				SetProcessCreationDate(int Y, int Mt, int D, int H, int Mn, int S) { return m_ProcessCreationDate.SetDateTime(Y, Mt, D, H, Mn, S); };
	BOOL			SetProcessCreationDate(CString value) { return ParseDateTime(m_ProcessCreationDate, value); };
	CString			GetFormatedProcessCreationDate() { return m_ProcessCreationDate.Format( EventDateFormatString ); };
	CString			GetFormatedProcessCreationDateTime() { return m_ProcessCreationDate.Format( EventDateTimeFormatString ); };

	// Process Due Date
	ZBDate			GetProcessDueDate() const  { return m_ProcessDueDate; };
	void			SetProcessDueDate(const COleDateTime time) { m_ProcessDueDate = time; };
	int				SetProcessDueDate(int Y, int Mt, int D, int H, int Mn, int S) { return m_ProcessDueDate.SetDateTime(Y, Mt, D, H, Mn, S); };
	BOOL			SetProcessDueDate(CString value) { return ParseDateTime(m_ProcessDueDate, value); };
	CString			GetFormatedProcessDueDate() { return m_ProcessDueDate.Format( EventDateFormatString ); };
	CString			GetFormatedProcessDueDateTime() { return m_ProcessDueDate.Format( EventDateTimeFormatString ); };

	// Activity Creation Date
	ZBDate			GetActivityCreationDate() const { return m_ActivityCreationDate; };
	void			SetActivityCreationDate(const COleDateTime time) { m_ActivityCreationDate = time; };
	int				SetActivityCreationDate(int Y, int Mt, int D, int H, int Mn, int S) { return m_ActivityCreationDate.SetDateTime(Y, Mt, D, H, Mn, S); };
	BOOL			SetActivityCreationDate(CString value) { return ParseDateTime(m_ActivityCreationDate, value); };
	CString			GetFormatedActivityCreationDate() { return m_ActivityCreationDate.Format( EventDateFormatString ); };
	CString			GetFormatedActivityCreationDateTime() { return m_ActivityCreationDate.Format( EventDateTimeFormatString ); };

	// Activity Due Date
	ZBDate			GetActivityDueDate() const { return m_ActivityDueDate; };
	void			SetActivityDueDate(const COleDateTime time) { m_ActivityDueDate = time; };
	int				SetActivityDueDate(int Y, int Mt, int D, int H, int Mn, int S) { return m_ActivityDueDate.SetDateTime(Y, Mt, D, H, Mn, S); };
	BOOL			SetActivityDueDate(CString value) { return ParseDateTime(m_ActivityDueDate, value); };
	CString			GetFormatedActivityDueDate() { return m_ActivityDueDate.Format( EventDateFormatString ); };
	CString			GetFormatedActivityDueDateTime() { return m_ActivityDueDate.Format( EventDateTimeFormatString ); };

	// The Activity Type 
	CString			GetActivityType() const { return m_ActivityType; };
	void			SetActivityType(const CString value) { m_ActivityType = value; };

	// The Sender
	CString			GetSender() const { return m_Sender; };
	void			SetSender(const CString value) { m_Sender = value; };

	// The Receiver
	CString			GetReceiver() const { return m_Receiver; };
	void			SetReceiver(const CString value) { m_Receiver = value; };

	// The Process Filename
	CString			GetProcessFilename() const { return m_ProcessFilename; };
	void			SetProcessFilename(const CString value) { m_ProcessFilename = value; };

	// The Form Exchange Filename
	CString			GetExchangeDataFilename() const { return m_ExchangeDataFilename; };
	void			SetExchangeDataFilename(const CString value) { m_ExchangeDataFilename = value; };

	// The Process Exchange Filename
	CString			GetProcessExchangeDataFilename() const { return m_ProcessExchangeDataFilename; };
	void			SetProcessExchangeDataFilename(const CString value) { m_ProcessExchangeDataFilename = value; };
	

	// The Activity Status
	CString			GetActivityStatus() const { return m_ActivityStatus; };
	CString			GetActivityStatusString() const;
	void			SetActivityStatus(const CString value) { m_ActivityStatus = value; };

	// The Comment
	CString			GetComments() const { return m_Comments; };
	void			SetComments(const CString value) { m_Comments = value; };

	// The Backup Flag
	BOOL			GetIsInBackup() const { return m_IsInBackup; };
	void			SetIsInBackup(BOOL value = TRUE) { m_IsInBackup = value; };
	void			SetIsInBackup(const CString value) { m_IsInBackup = atoi( (const char*)value ); };

    ZBEventActivity(const ZBEventActivity &right);
    const ZBEventActivity & operator=(const ZBEventActivity &right);

protected:
	ActivityEventType	m_ActivityEventType;
	CString				m_FolderName;
	CString				m_Filename;
	CString				m_ProcessName;
	ZBDate				m_ProcessCreationDate;
	ZBDate				m_ProcessDueDate;
	CString				m_ActivityName;
	ZBDate				m_ActivityCreationDate;
	ZBDate				m_ActivityDueDate;
	CString				m_ActivityType;
	CString				m_Sender;
	CString				m_Receiver;
	CString				m_ProcessFilename;
	CString				m_ExchangeDataFilename;
	CString				m_ProcessExchangeDataFilename;
	CString				m_ActivityStatus;
	CString				m_Comments;
	BOOL				m_IsInBackup;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif // !defined(AFX_ZBEventActivity_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
