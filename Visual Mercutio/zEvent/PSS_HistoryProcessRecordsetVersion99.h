/****************************************************************************
 * ==> PSS_HistoryProcessRecordsetVersion99 --------------------------------*
 ****************************************************************************
 * Description : Provides an historic process recordset (version 99)        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryProcessRecordsetVersion99H
#define PSS_HistoryProcessRecordsetVersion99H

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
* History process recordset (version 99)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoryProcessRecordsetVersion99 : public CDaoRecordset
{
    DECLARE_DYNAMIC(PSS_HistoryProcessRecordsetVersion99)

    public:
        /**
        * Constructor
        *@param pDatabase - database
        *@param fileName - database file name
        */
        PSS_HistoryProcessRecordsetVersion99(CDaoDatabase* pDatabase = NULL, const CString& fileName = "");

        /**
        * Gets the process identifier field name
        *@return the process identifier field name
        */
        virtual inline const CString GetProcessIDFieldName() const;

        /**
        * Gets the name field name
        *@return the name field name
        */
        virtual inline const CString GetNameFieldName() const;

        /**
        * Gets the file name field name
        *@return the file name field name
        */
        virtual inline const CString GetFileNameFieldName() const;

        /**
        * Gets the folder name field name
        *@return the folder name field name
        */
        virtual inline const CString GetFolderNameFieldName() const;

        /**
        * Gets the data feed form field name
        *@return the data feed form field name
        */
        virtual inline const CString GetDataFeedFormFieldName() const;

        /**
        * Gets the data feed process field name
        *@return the data feed process field name
        */
        virtual inline const CString GetDataFeedProcFieldName() const;

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
        * Gets the initiator field name
        *@return the initiator field name
        */
        virtual inline const CString GetInitiatorFieldName() const;

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
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Sets the file name
        *@param value - the file name
        */
        virtual inline void SetFileName(const CString& value);

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
        * Gets the data feed form
        *@return the data feed form
        */
        virtual inline CString GetDataFeedForm() const;

        /**
        * Sets the data feed form
        *@param value - the data feed form
        */
        virtual inline void SetDataFeedForm(const CString& value);

        /**
        * Gets the data feed proces
        *@return the data feed process
        */
        virtual inline CString GetDataFeedProc() const;

        /**
        * Sets the data feed process
        *@param value - the data feed process
        */
        virtual inline void SetDataFeedProc(const CString& value);

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
        * Gets the initiator
        *@return the initiator
        */
        virtual inline CString GetInitiator() const;

        /**
        * Sets the initiator
        *@param value - the initiator
        */
        virtual inline void SetInitiator(const CString& value);

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
        COleDateTime m_StartDate;
        COleDateTime m_EndDate;
        CString      m_Name;
        CString      m_FileName;
        CString      m_FolderName;
        CString      m_DataFeedForm;
        CString      m_DataFeedProc;
        CString      m_Initiator;
        CString      m_DatabaseFileName;
        long         m_ProcessID;
};

//---------------------------------------------------------------------------
// PSS_HistoryProcessRecordsetVersion99
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetProcessIDFieldName() const
{
    return _T("[ProcessID]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetNameFieldName() const
{
    return _T("[Name]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetFileNameFieldName() const
{
    return _T("[Filename]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetFolderNameFieldName() const
{
    return _T("[FolderName]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetDataFeedFormFieldName() const
{
    return _T("[DataFeedForm]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetDataFeedProcFieldName() const
{
    return _T("[DataFeedProc]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetStartDateFieldName() const
{
    return _T("[StartDate]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetEndDateFieldName() const
{
    return _T("[EndDate]");
}
//---------------------------------------------------------------------------
const CString PSS_HistoryProcessRecordsetVersion99::GetInitiatorFieldName() const
{
    return _T("[Initiator]");
}
//---------------------------------------------------------------------------
long PSS_HistoryProcessRecordsetVersion99::GetProcessID() const
{
    return m_ProcessID;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetProcessID(long value)
{
    m_ProcessID = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetFolderName(const CString& value)
{
    m_FolderName = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetDataFeedForm() const
{
    return m_DataFeedForm;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetDataFeedForm(const CString& value)
{
    m_DataFeedForm = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetDataFeedProc() const
{
    return m_DataFeedProc;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetDataFeedProc(const CString& value)
{
    m_DataFeedProc = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryProcessRecordsetVersion99::GetStartDate() const
{
    return m_StartDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetStartDate(const COleDateTime& value)
{
    m_StartDate = value;
}
//---------------------------------------------------------------------------
COleDateTime PSS_HistoryProcessRecordsetVersion99::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetEndDate(const COleDateTime& value)
{
    m_EndDate = value;
}
//---------------------------------------------------------------------------
CString PSS_HistoryProcessRecordsetVersion99::GetInitiator() const
{
    return m_Initiator;
}
//---------------------------------------------------------------------------
void PSS_HistoryProcessRecordsetVersion99::SetInitiator(const CString& value)
{
    m_Initiator = value;
}
//---------------------------------------------------------------------------

#endif
