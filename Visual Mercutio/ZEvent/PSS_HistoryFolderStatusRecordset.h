/****************************************************************************
 * ==> PSS_HistoryFolderStatusRecordset ------------------------------------*
 ****************************************************************************
 * Description : Provides an historic folder status recordset               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryFolderStatusRecordsetH
#define PSS_HistoryFolderStatusRecordsetH

#if _MSC_VER > 1000
#pragma once
#endif

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* History folder status recordset
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoryFolderStatusRecordset : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_HistoryFolderStatusRecordset)

    public:
        /**
        * Constructor
        *@param pDatabase - database
        *@param fileName - database file name
        */
        PSS_HistoryFolderStatusRecordset(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

        /**
        * Gets the activity status identifier field name
        *@return the activity status identifier field name
        */
        virtual inline const CString GetActivityStatusIDFieldName() const;

        /**
        * Gets the activity identifier field name
        *@return the activity identifier field name
        */
        virtual inline const CString GetActivityIDFieldName() const;

        /**
        * Gets the process identifier field name
        *@return the process identifier field name
        */
        virtual inline const CString GetProcessIDFieldName() const;

        /**
        * Gets the folder name field name
        *@return the folder name field name
        */
        virtual inline const CString GetFolderNameFieldName() const;

        /**
        * Gets the name field name
        *@return the name field name
        */
        virtual inline const CString GetNameFieldName() const;

        /**
        * Gets the date field name
        *@return the date field name
        */
        virtual inline const CString GetDateFieldName() const;

        /**
        * Gets the start date field name
        *@return the start date field name
        */
        virtual inline const CString GetStartDateFieldName() const;

        /**
        * Gets the end date field name
        *@return the end date field name
        */
        virtual inline const CString GetEndDateFieldName() const;

        /**
        * Gets the status field name
        *@return the status field name
        */
        virtual inline const CString GetStatusFieldName() const;

        /**
        * Gets the activity status identifier
        *@return the activity status identifier
        */
        virtual inline long GetActivityStatusID() const;

        /**
        * Sets the activity status identifier
        *@param value - the activity status identifier
        */
        virtual inline void SetActivityStatusID(long value);

        /**
        * Gets the activity identifier
        *@return the activity identifier
        */
        virtual inline long GetActivityID() const;

        /**
        * Sets the activity identifier
        *@param value - the activity identifier
        */
        virtual inline void SetActivityID(long value);

        /**
        * Gets the process identifier
        *@return the process identifier
        */
        virtual inline long GetProcessID() const;

        /**
        * Sets the process identifier
        *@param value - the process identifier
        */
        virtual inline void SetProcessID(long value);

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline CString GetFolderName() const;

        /**
        * Sets the folder name
        *@param value - the folder name
        */
        virtual inline void SetFolderName(const CString& value);

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Sets the name
        *@param value - the name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Gets the date
        *@return the date
        */
        virtual inline COleDateTime GetDate() const;

        /**
        * Sets the date
        *@param value - the date
        */
        virtual inline void SetDate(const COleDateTime& value);

        /**
        * Gets the start date
        *@return the start date
        */
        virtual inline COleDateTime GetStartDate() const;

        /**
        * Sets the start date
        *@param value - the start date
        */
        virtual inline void SetStartDate(const COleDateTime& value);

        /**
        * Gets the end date
        *@return the end date
        */
        virtual inline COleDateTime GetEndDate() const;

        /**
        * Sets the end date
        *@param value - the end date
        */
        virtual inline void SetEndDate(const COleDateTime& value);

        /**
        * Gets the status
        *@return the status
        */
        virtual inline CString GetStatus() const;

        /**
        * Sets the status
        *@return the status
        */
        virtual inline void SetStatus(const CString& value);

        /**
        * Gets the default database name
        *@return the default database name
        */
        virtual CString GetDefaultDBName();

        /**
        * Gets the default SQL for recordset
        *@return the default SQL for recordset
        */
        virtual CString GetDefaultSQL();

        /**
        * DDX/DDV data exchange
        *@param pFX - DDX/DDV data
        */
        virtual void DoFieldExchange(CDaoFieldExchange* pFX);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        COleDateTime m_Date;
        COleDateTime m_StartDate;
        COleDateTime m_EndDate;
        CString      m_FolderName;
        CString      m_Name;
        CString      m_Status;
        CString      m_DatabaseFileName;
        long         m_ActivityStatusID;
        long         m_ActivityID;
        long         m_ProcessID;
};

//---------------------------------------------------------------------------
// PSS_HistoryFolderStatusRecordset
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetActivityStatusIDFieldName() const
{
    return _T("[ActivityStatusID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetActivityIDFieldName() const
{
    return _T("[ActivityID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetProcessIDFieldName() const
{
    return _T("[ProcessID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetFolderNameFieldName() const
{
    return _T("[FolderName]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetNameFieldName() const
{
    return _T("[Name]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetDateFieldName() const
{
    return _T("[Date]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetStartDateFieldName() const
{
    return _T("[StartDate]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetEndDateFieldName() const
{
    return _T("[EndDate]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryFolderStatusRecordset::GetStatusFieldName() const
{
    return _T("[Status]");
}
//---------------------------------------------------------------------------
long PSS_HistoryFolderStatusRecordset::GetActivityStatusID() const
{
    return m_ActivityStatusID;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetActivityStatusID(long value)
{
    m_ActivityStatusID = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryFolderStatusRecordset::GetActivityID() const
{
    return m_ActivityID;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetActivityID(long value)
{
    m_ActivityID = value;
}
//---------------------------------------------------------------------------
long PSS_HistoryFolderStatusRecordset::GetProcessID() const
{
    return m_ProcessID;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetProcessID(long value)
{
    m_ProcessID = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryFolderStatusRecordset::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetFolderName(const CString& value)
{
    m_FolderName = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryFolderStatusRecordset::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryFolderStatusRecordset::GetDate() const
{
    return m_Date;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetDate(const COleDateTime& value)
{
    m_Date = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryFolderStatusRecordset::GetStartDate() const
{
    return m_StartDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetStartDate(const COleDateTime& value)
{
    m_StartDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryFolderStatusRecordset::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetEndDate(const COleDateTime& value)
{
    m_EndDate = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryFolderStatusRecordset::GetStatus() const
{
    return m_Status;
}
//---------------------------------------------------------------------------
void PSS_HistoryFolderStatusRecordset::SetStatus(const CString& value)
{
    m_Status = value;
}
//---------------------------------------------------------------------------

#endif
