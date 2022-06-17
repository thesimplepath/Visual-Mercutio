/****************************************************************************
 * ==> PSS_UserExport ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an interface to import and export the user table  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserExportH
#define PSS_UserExportH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Export.h"
#include "PSS_UserManager.h"

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
* User table import and export interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserExport : public PSS_Export
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        *@param pUserManager - user manager
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        PSS_UserExport(const CString&                fileName        = "",
                       PSS_UserManager*              pUserManager    = NULL,
                       BOOL                          generateHeader  = FALSE,
                       ESynchronizationSeparatorType separatorType   = ESynchronizationSeparatorType::E_SS_Automatic,
                       const CString&                schema          = g_OriginalSchema,
                       int                           propagationMode = g_LocatePageOnly,
                       BOOL                          emptyWhenZero   = FALSE,
                       PSS_StatusBar*                pStatusBar      = NULL);

        virtual ~PSS_UserExport();

        /**
        * Creates the export class
        *@param fileName - file name
        *@param pUserManager - user manager
        *@param generateHeader - if TRUE, header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, empty fields will be filled with 0
        *@param pStatusBar - status bar, can be NULL
        */
        virtual inline void Create(const CString&                fileName,
                                   PSS_UserManager*              pUserManager    = NULL,
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
        * Called before importing the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreImport();

    private:
        PSS_UserManager* m_pUserManager;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserExport(const PSS_UserExport& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserExport & operator = (const PSS_UserExport& other);
};

//---------------------------------------------------------------------------
// PSS_UserExport
//---------------------------------------------------------------------------
void PSS_UserExport::Create(const CString&                fileName,
                            PSS_UserManager*              pUserManager,
                            BOOL                          generateHeader,
                            ESynchronizationSeparatorType separatorType,
                            const CString&                schema,
                            int                           propagationMode,
                            BOOL                          emptyWhenZero,
                            PSS_StatusBar*                pStatusBar)
{
    m_pUserManager = pUserManager;
    PSS_Export::Create(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar);
}
//---------------------------------------------------------------------------

#endif
