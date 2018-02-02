// rsetuser.h : header file
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
// ZDUserRecordSet recordset

class AFX_EXT_CLASS ZDUserRecordSet : public CRecordset
{
public:
	ZDUserRecordSet(CDatabase* pDatabase = NULL);
	CString GetUserDBTableName();

// Field/Param Data
	//{{AFX_FIELD(ZDUserRecordSet, CRecordset)
	CString	m_UserName;
	CString	m_Email;
	CString	m_Responsible;
	CString	m_Description;
	//}}AFX_FIELD


// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	DECLARE_DYNAMIC(ZDUserRecordSet)
};

