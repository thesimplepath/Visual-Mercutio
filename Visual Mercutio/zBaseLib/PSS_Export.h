/****************************************************************************
 * ==> PSS_Export ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export interface                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExportH
#define PSS_ExportH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "mfc.h"

// processsoft
#include "PSS_StatusBar.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Export interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Export : public CWnd
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        PSS_Export(const CString&                fileName        = "",
                   BOOL                          generateHeader  = FALSE,
                   ESynchronizationSeparatorType separatorType   = ESynchronizationSeparatorType::E_SS_Automatic,
                   const CString&                schema          = g_OriginalSchema,
                   int                           propagationMode = g_LocatePageOnly,
                   BOOL                          emptyWhenZero   = FALSE,
                   PSS_StatusBar*                pStatusBar      = NULL);

        virtual ~PSS_Export();

        /**
        * Creates the export class
        *@param fileName - file name
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        virtual inline void Create(const CString&                fileName,
                                   BOOL                          generateHeader  = FALSE,
                                   ESynchronizationSeparatorType separatorType   = ESynchronizationSeparatorType::E_SS_Automatic,
                                   const CString&                schema          = g_OriginalSchema,
                                   int                           propagationMode = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero   = FALSE,
                                   PSS_StatusBar*                pStatusBar      = NULL);

        /**
        * Exports the records to a file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Export();

        /**
        * Imports the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Import();

        /**
        * Synchronizes the document records and the file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Synchronize();

        /**
        * Builds and gets the exported line
        *@param pObj - object containing the field from which exported line should be built
        *@return the exported line
        */
        virtual CString GetExportedLine(CObject* pObj);

        /**
        * Checks if the field should be exported
        *@param pObj - object containing the field
        *@return TRUE if the field should be exported, otherwise FALSE
        */
        virtual BOOL IsExportedField(CObject* pObj) const;

        /**
        * Processes the line and updates the document
        *@param line - line to process
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ProcessLine(const CString& line);

        /**
        * Builds and gets the header line
        *@return the header line
        */
        virtual CString GetHeaderLine();

        /**
        * Starts the real time synchronization
        *@param timeValue - synchronization time value in milliseconds
        */
        virtual BOOL StartSynchronization(int timeValue = 5);

        /**
        * Ends the synchronization process
        */
        virtual void EndSynchronization();

        /**
        * Called when the document has just been modified
        */
        virtual void SourceHasBeenModified();

        /**
        * Exports the additional info
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ExportAdditionalInfo();

        /**
        * Imports the additional info
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ImportAdditionalInfo();

        /**
        * Called before importing the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreImport();

        /**
        * Called after importing the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PostImport();

        /**
        * Gets the forecasted total object
        *@return the forecasted total object
        */
        virtual double GetForecastedTotalObject() const;

        /**
        * Processes the export loop
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DoExportLoop();

        /**
        * Called before exporting data
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreExport();

        /**
        * Called after the export finished and before closing the file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PostExport();

        /**
        * Gets if the header should be generated
        *@return TRUE if the header should be generated, otherwise FALSE
        */
        virtual inline const BOOL GetGenerateHeader() const;

        /**
        * Gets the separator type
        *@return the separator type
        */
        virtual inline const ESynchronizationSeparatorType GetSeparatorType() const;

        /**
        * Gets the schema name used for exportation
        *@return the schema name used for exportation
        */
        virtual inline const CString GetSchemaName() const;

        /**
        * Gets the propagation mode for imports
        *@return the propagation mode for imports
        */
        virtual inline const int GetPropagationMode() const;

        /**
        * Gets if during the import, the numbers should be emptied if zero
        *@return TRUE if numbers should be emptied if zero, otherwise FALSE
        */
        virtual inline const BOOL GetEmptyWhenZero() const;

        /**
        * Gets the last file date for the synchronization process
        *@return the last file date for the synchronization process
        */
        virtual inline const CTime GetLastFileDate() const;

        /**
        * Sets the last file date for the synchronization process
        *@param value - the last file date for the synchronization process
        */
        virtual inline void SetLastFileDate(CTime value);

        /**
        * Gets the time sequence for synchronization
        *@return the time sequence for synchronization
        */
        virtual inline const int GetTimeSynchronizationValue() const;

        /**
        * Sets the time sequence for synchronization
        *@param value - the time sequence for synchronization
        */
        virtual inline void SetTimeSynchronizationValue(int value);

    protected:
        PSS_StatusBar* m_pStatusBar;
        CString        m_FileName;
        BOOL           m_SourceIsModified;

        /**
        * Reads the line
        *@param[out] line - one line read from the file buffer on function ends
        *@return the line length in chars, 0 if the file was completely processed, -1 on error
        */
        virtual int ReadLine(CString& line);

        /**
        * Writes one line to the file buffer
        *@param line - line to write
        */
        virtual void WriteLine(const CString& line);

        /**
        * Opens the file in write mode with creation
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenFileCreate();

        /**
        * Opens the file in read mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenFileRead();

        /**
        * Closes the file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CloseFile();

        /**
        * Checks if the synchronization file is more recent
        *@return TRUE if the synchronization file is more recent, otherwise FALSE
        */
        virtual BOOL SynchronizationFileUpdated();

        /**
        * Assigns the synchronization file date
        */
        virtual void AssignSynchronizationFileDate();

        /**
        * Builds a line
        *@param key - key
        *@param value - value
        *@return the built line
        */
        virtual CString BuildLine(const CString& key, const CString& value);

        /// Generated message map
        //{{AFX_MSG(PSS_Export)
        afx_msg void OnTimer(UINT nIDEvent);
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CFile                         m_File;
        ESynchronizationSeparatorType m_SeparatorType;
        CString                       m_SchemaName;
        char                          m_FileBuffer[300];
        char*                         m_pCurrent;
        char*                         m_pNext;
        int                           m_PropagationMode;
        int                           m_TimeSynchronizationValue;
        BOOL                          m_GenerateHeader;
        BOOL                          m_EmptyWhenZero;
        CTime                         m_LastFileDate;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Export(const PSS_Export& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Export& operator = (const PSS_Export& other);


        /**
        * Reads a char buffer from the file.
        *@return 0 if the file was completely processed, -1 on error
        */
        int ReadFileBuffer();
};

//---------------------------------------------------------------------------
// PSS_Export
//---------------------------------------------------------------------------
void PSS_Export::Create(const CString&                fileName,
                        BOOL                          generateHeader,
                        ESynchronizationSeparatorType separatorType,
                        const CString&                schema,
                        int                           propagationMode,
                        BOOL                          emptyWhenZero,
                        PSS_StatusBar*                pStatusBar)
{
    m_pStatusBar      = pStatusBar;
    m_FileName        = fileName;
    m_SeparatorType   = separatorType;
    m_SchemaName      = schema;
    m_PropagationMode = propagationMode;
    m_GenerateHeader  = generateHeader;
    m_EmptyWhenZero   = emptyWhenZero;
}
//---------------------------------------------------------------------------
const BOOL PSS_Export::GetGenerateHeader() const
{
    return m_GenerateHeader;
}
//---------------------------------------------------------------------------
const ESynchronizationSeparatorType PSS_Export::GetSeparatorType() const
{
    return m_SeparatorType;
}
//---------------------------------------------------------------------------
const CString PSS_Export::GetSchemaName() const
{
    return m_SchemaName;
}
//---------------------------------------------------------------------------
const int PSS_Export::GetPropagationMode() const
{
    return m_PropagationMode;
}
//---------------------------------------------------------------------------
const BOOL PSS_Export::GetEmptyWhenZero() const
{
    return m_EmptyWhenZero;
}
//---------------------------------------------------------------------------
const CTime PSS_Export::GetLastFileDate() const
{
    return m_LastFileDate;
}
//---------------------------------------------------------------------------
void PSS_Export::SetLastFileDate(CTime value)
{
    m_LastFileDate = value;
}
//---------------------------------------------------------------------------
const int PSS_Export::GetTimeSynchronizationValue() const
{
    return m_TimeSynchronizationValue;
}
//---------------------------------------------------------------------------
void PSS_Export::SetTimeSynchronizationValue(int value)
{
    m_TimeSynchronizationValue = value;
}
//---------------------------------------------------------------------------

#endif
