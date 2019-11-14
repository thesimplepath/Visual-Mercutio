
#ifndef ProcHistoDAO_h
#define ProcHistoDAO_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ActivityEvent.h"
#include "HistoryProcessRecordSet.h"
#include "PSS_HistoryActivityRecordSet.h"
#include "HistoryActivityStatusRecordSet.h"
#include "HistoryProcessStatusRecordSet.h"
#include "HistoryFolderStatusRecordSet.h"

#ifdef _ZEVENTEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZDProcessHistoryDAO
{

public:
    ZDProcessHistoryDAO(CString DatabaseFileName = "");

    ~ZDProcessHistoryDAO();

    void Create(CString DatabaseFileName);

    BOOL AppendEventToHistoric(PSS_ActivityEvent& EventActivity);
    BOOL Close();

    CString GetDatabaseFileName() const;

private:
    CDaoDatabase                      m_ProcessHistoryDatabase;
    PSS_HistoryActivityRecordset*     m_pHistoryActivityRecordset;
    ZDHistoryActivityStatusRecordset* m_pHistoryActivityStatusRecordset;
    ZDHistoryProcessRecordset*        m_pHistoryProcessRecordset;
    ZDHistoryProcessStatusRecordset*  m_pHistoryProcessStatusRecordset;
    ZDHistoryFolderStatusRecordset*   m_pHistoryFolderStatusRecordset;
    CString                           m_DatabaseFileName;

private:
    ZDProcessHistoryDAO(const ZDProcessHistoryDAO &right);
    const ZDProcessHistoryDAO & operator=(const ZDProcessHistoryDAO &right);

    long    FindProcess(PSS_ActivityEvent& EventActivity);
    long    FindActivity(long ProcessID, PSS_Date& CurrentDate, PSS_ActivityEvent& EventActivity);
    bool    AddNewProcessRecord(PSS_ActivityEvent& EventActivity);
    bool    ModifyProcessStatusRecord(long ProcessID, PSS_ActivityEvent& EventActivity);
    bool    AddProcessStatusRecord(long ProcessID, PSS_ActivityEvent& EventActivity);
    bool    ModifyActivityStatusRecord(long ProcessID, long ActivityID, PSS_ActivityEvent& EventActivity);
    bool    AddActivityStatusRecord(long ProcessID, long ActivityID, PSS_ActivityEvent& EventActivity);
    bool    ModifyFolderStatusRecord(long ProcessID, long ActivityID, PSS_ActivityEvent& EventActivity);
    bool    AddFolderStatusRecord(long ProcessID, long ActivityID, PSS_ActivityEvent& EventActivity);


    BOOL OpenRead();
    BOOL OpenWrite();

};

#endif
