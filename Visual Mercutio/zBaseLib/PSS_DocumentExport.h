/****************************************************************************
 * ==> PSS_DocumentExport --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an interface to import and export document info   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentExportH
#define PSS_DocumentExportH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Export.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

// forward class declarations
class PSS_Document;

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
* Document info import and export interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocumentExport : public PSS_Export
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        *@param pDoc - document
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        PSS_DocumentExport(const CString&                fileName        = "",
                           PSS_Document*                 pDoc            = NULL,
                           BOOL                          generateHeader  = FALSE,
                           ESynchronizationSeparatorType separatorType   = ESynchronizationSeparatorType::E_SS_Automatic,
                           const CString&                schema          = g_OriginalSchema,
                           int                           propagationMode = g_LocatePageOnly,
                           BOOL                          emptyWhenZero   = FALSE,
                           PSS_StatusBar*                pStatusBar      = NULL);

        virtual ~PSS_DocumentExport();

        /**
        * Creates the export class
        *@param fileName - file name
        *@param pDoc - document
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        virtual inline void Create(const CString&                fileName,
                                   PSS_Document*                 pDoc,
                                   BOOL                          generateHeader  = FALSE,
                                   ESynchronizationSeparatorType separatorType   = ESynchronizationSeparatorType::E_SS_Automatic,
                                   const CString&                schema          = g_OriginalSchema,
                                   int                           propagationMode = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero   = FALSE,
                                   PSS_StatusBar*                pStatusBar      = NULL);

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

    protected:
        PSS_Document* m_pDoc;
        int           m_ObjectCounter;

        /**
        * Gets the object counter
        *@return the object counter
        *@note This object counter is automatically incremented by the export function for each object
        */
        const inline int GetObjectCounter() const;

    private:
        CString m_PreviousSchema;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DocumentExport(const PSS_DocumentExport& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DocumentExport & operator = (const PSS_DocumentExport& other);
};

//---------------------------------------------------------------------------
// PSS_DocumentExport
//---------------------------------------------------------------------------
void PSS_DocumentExport::Create(const CString&                fileName,
                                PSS_Document*                 pDoc,
                                BOOL                          generateHeader,
                                ESynchronizationSeparatorType separatorType,
                                const CString&                schema,
                                int                           propagationMode,
                                BOOL                          emptyWhenZero,
                                PSS_StatusBar*                pStatusBar)
{
    m_pDoc = pDoc;
    PSS_Export::Create(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar);
}
//---------------------------------------------------------------------------
const int PSS_DocumentExport::GetObjectCounter() const
{
    return m_ObjectCounter;
}
//---------------------------------------------------------------------------

#endif
