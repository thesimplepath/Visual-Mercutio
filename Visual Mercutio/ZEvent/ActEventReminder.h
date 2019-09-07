// ActEventReminder.h: interface for the ZBEventActivityReminder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBActEventReminder_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBActEventReminder_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

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


class AFX_EXT_CLASS ZBEventActivityReminder : public ZBEvent  
{
public:
    ZBEventActivityReminder();
    ZBEventActivityReminder(COleDateTime Time,
                            CString    Priority,
                            CString FolderName,
                            CString ProcessName,
                            CString ActivityName,
                            int     RemainingDays,
                            COleDateTime ActivityDueDate,
                            CString ProcessFilename,
                            CString ActivityStatus,
                            CString Message);
    virtual ~ZBEventActivityReminder();
    ZBEventActivityReminder(const ZBEventActivityReminder &right);
    const ZBEventActivityReminder & operator=(const ZBEventActivityReminder &right);

    
    // The priority
    CString            GetPriority() const { return m_Priority; };
    void            SetPriority(const CString value) { m_Priority = value; };

    // Folder Name
    CString            GetFolderName() const { return m_FolderName; };
    void            SetFolderName(const CString value) { m_FolderName = value; };

    // Process Name
    CString            GetProcessName() const { return m_ProcessName; };
    void            SetProcessName(const CString value) { m_ProcessName = value; };

    // Activity Name
    CString            GetActivityName() const { return m_ActivityName; };
    void            SetActivityName(const CString value) { m_ActivityName = value; };

    int                GetRemainingDays() const { return m_RemainingDays; };
    CString            GetRemainingDaysString() const;
    void            SetRemainingDays( int value ) { m_RemainingDays = value; };

    // Activity Due Date
    COleDateTime    GetActivityDueDate() const { return m_ActivityDueDate; };
    void            SetActivityDueDate(const COleDateTime time) { m_ActivityDueDate = time; };
    int                SetActivityDueDate(int Y, int Mt, int D, int H, int Mn, int S) { return m_ActivityDueDate.SetDateTime(Y, Mt, D, H, Mn, S); };
    BOOL            SetActivityDueDate(CString value) { return ParseDateTime(m_ActivityDueDate, value); };
    CString            GetFormattedActivityDueDate() { return m_ActivityDueDate.Format( EventDateFormatString ); };
    CString            GetFormattedActivityDueDateTime() { return m_ActivityDueDate.Format( EventDateTimeFormatString ); };

    // The Process Filename
    CString            GetProcessFilename() const { return m_ProcessFilename; };
    void            SetProcessFilename(const CString value) { m_ProcessFilename = value; };

    // The Activity Status
    CString            GetActivityStatus() const { return m_ActivityStatus; };
    void            SetActivityStatus(const CString value) { m_ActivityStatus = value; };

    // The Message
    CString            GetMessage() const { return m_Message; };
    void            SetMessage(const CString value) { m_Message = value; };

protected:
    CString            m_ProcessName;
    CString            m_FolderName;
    CString            m_Priority;
    CString            m_ActivityName;
    COleDateTime    m_ActivityDueDate;
    CString            m_ProcessFilename;
    CString            m_ActivityStatus;
    CString            m_Message;
    int                m_RemainingDays;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif // !defined(AFX_ZBActEventReminder_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
