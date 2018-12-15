// rsetact.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZBASELIBEXPORT
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

/////////////////////////////////////////////////////////////////////////////
// ZDActivityLogRecordSet recordset

class AFX_EXT_CLASS ZDActivityLogRecordSet : public CRecordset
{
public:
    ZDActivityLogRecordSet(CDatabase* pDatabase = NULL);

// Field/Param Data
    //{{AFX_FIELD(ZDActivityLogRecordSet, CRecordset)
    CTime    m_Date;
    CString    m_FolderName;
    CString    m_File;
    CString    m_DataFile;
    CString    m_Process;
    CString    m_Activity;
    CTime    m_DueDate;
    CString    m_Status;
    CString    m_Sender;
    CString    m_Receiver;
    CString    m_Comments;
    //}}AFX_FIELD


// Implementation
protected:
    virtual CString GetDefaultConnect();    // Default connection string
    virtual CString GetDefaultSQL();     // Default SQL for Recordset
    virtual void DoFieldExchange(CFieldExchange* pFX);    // RFX support
    DECLARE_DYNAMIC(ZDActivityLogRecordSet)
};

