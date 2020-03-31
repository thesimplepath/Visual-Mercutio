/****************************************************************************
 * ==> PSS_FieldDefinitionDataFeed -----------------------------------------*
 ****************************************************************************
 * Description : Provides a data feed for field definition                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldDefinitionDataFeedH
#define PSS_FieldDefinitionDataFeedH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Export.h"
#include "PSS_FieldRepository.h"

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
* Data feed for field definition
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldDefinitionDataFeed : public PSS_Export
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        *@param pFieldRepository - field repository
        *@param pObjectDefinition - object definition
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        PSS_FieldDefinitionDataFeed(const CString&                fileName          = "",
                                    PSS_FieldRepository*          pFieldRepository  = NULL,
                                    PSS_FieldObjectDefinition*    pObjectDefinition = NULL,
                                    BOOL                          generateHeader    = FALSE,
                                    ESynchronizationSeparatorType separatorType     = E_SS_Automatic,
                                    const CString&                schema            = g_OriginalSchema,
                                    int                           propagationMode   = g_LocatePageOnly,
                                    BOOL                          emptyWhenZero     = FALSE,
                                    PSS_StatusBar*                pStatusBar        = NULL);

        /**
        * Constructor
        *@param fileName - file name
        *@param pFieldRepository - field repository
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        PSS_FieldDefinitionDataFeed(const CString&                fileName,
                                    PSS_FieldRepository*          pFieldRepository,
                                    BOOL                          generateHeader  = FALSE,
                                    ESynchronizationSeparatorType separatorType   = E_SS_Automatic,
                                    const CString&                schema          = g_OriginalSchema,
                                    int                           propagationMode = g_LocatePageOnly,
                                    BOOL                          emptyWhenZero   = FALSE,
                                    PSS_StatusBar*                pStatusBar      = NULL);

        virtual ~PSS_FieldDefinitionDataFeed();

        /**
        * Creates the class content
        *@param fileName - file name
        *@param pFieldRepository - field repository
        *@param pObjectDefinition - object definition
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        virtual inline void Create(const CString&                fileName,
                                   PSS_FieldRepository*          pFieldRepository = NULL,
                                   PSS_FieldObjectDefinition*    pObjectDefinition = NULL,
                                   BOOL                          generateHeader = FALSE,
                                   ESynchronizationSeparatorType separatorType = E_SS_Automatic,
                                   const CString&                schema = g_OriginalSchema,
                                   int                           propagationMode = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero = FALSE,
                                   PSS_StatusBar*                pStatusBar = NULL);

        /**
        * Creates the class content
        *@param fileName - file name
        *@param pFieldRepository - field repository
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        virtual inline void Create(const CString&                fileName,
                                   PSS_FieldRepository*          pFieldRepository = NULL,
                                   BOOL                          generateHeader   = FALSE,
                                   ESynchronizationSeparatorType separatorType    = E_SS_Automatic,
                                   const CString&                schema           = g_OriginalSchema,
                                   int                           propagationMode  = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero    = FALSE,
                                   PSS_StatusBar*                pStatusBar       = NULL);

        /**
        * Processes the line and updates the document
        *@param line - line to process
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ProcessLine(const CString& line);

        /**
        * Builds and gets the export line
        *@param pObj - object
        *@return the export line
        */
        virtual CString GetExportedLine(CObject* pObj) const;

        /**
        * Builds and gets the header line
        *@return the header line
        */
        virtual CString GetHeaderLine() const;

        /**
        * Gets the forecasted total object
        *@return the forecasted total object
        */
        virtual double GetForecastedTotalObject() const;

        /**
        * Does the loop for export
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DoExportLoop();

        /**
        * Pre-imports the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreImport();

        /**
        * Post-imports the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PostImport();

    private:
        /**
        * Field export
        */
        class IFieldExport : public CObject
        {
            public:
                CString m_Key;
                CString m_Value;

                /**
                * Constructor
                *@param key - key
                *@param value - value
                */
                IFieldExport(const CString& key = "", const CString& value = "");

                virtual ~IFieldExport();
        };

        CObArray                   m_LineArray;
        PSS_FieldObjectDefinition* m_pObjectDefinition;
        PSS_FieldRepository*       m_pSourceFieldRepository;
        PSS_FieldRepository*       m_pImportedFieldRepository;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldDefinitionDataFeed(const PSS_FieldDefinitionDataFeed& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldDefinitionDataFeed& operator = (const PSS_FieldDefinitionDataFeed& other);

        /**
        * Deletes the line array
        */
        void DeleteLineArray();

        /**
        * Gets the source field repository
        *@return the source field repository
        */
        inline const PSS_FieldRepository* GetSourceFieldRepository() const;

        /**
        * Sets the source field repository
        *@param pRepository - the source field repository
        */
        inline void SetSourceFieldRepository(PSS_FieldRepository* pRepository);

        /**
        * Gets the imported field repository
        *@return the imported field repository
        */
        inline const PSS_FieldRepository* GetImportedFieldRepository() const;

        /**
        * Sets the imported field repository
        *@param pRepository - the imported field repository
        */
        inline void SetImportedFieldRepository(PSS_FieldRepository* pRepository);
};

//---------------------------------------------------------------------------
// PSS_FieldDefinitionDataFeed
//---------------------------------------------------------------------------
void PSS_FieldDefinitionDataFeed::Create(const CString&                fileName,
                                         PSS_FieldRepository*          pFieldRepository,
                                         PSS_FieldObjectDefinition*    pObjectDefinition,
                                         BOOL                          generateHeader,
                                         ESynchronizationSeparatorType separatorType,
                                         const CString&                schema,
                                         int                           propagationMode,
                                         BOOL                          emptyWhenZero,
                                         PSS_StatusBar*                pStatusBar)
{
    m_pSourceFieldRepository = pFieldRepository;
    m_pObjectDefinition      = pObjectDefinition;

    PSS_Export::Create(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar);
}
//---------------------------------------------------------------------------
void PSS_FieldDefinitionDataFeed::Create(const CString&                fileName,
                                         PSS_FieldRepository*          pFieldRepository,
                                         BOOL                          generateHeader,
                                         ESynchronizationSeparatorType separatorType,
                                         const CString&                schema,
                                         int                           propagationMode,
                                         BOOL                          emptyWhenZero,
                                         PSS_StatusBar*                pStatusBar)
{
    m_pSourceFieldRepository = pFieldRepository;
    m_pObjectDefinition      = NULL;

    PSS_Export::Create(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar);
}
//---------------------------------------------------------------------------
const PSS_FieldRepository* PSS_FieldDefinitionDataFeed::GetSourceFieldRepository() const
{
    return m_pSourceFieldRepository;
}
//---------------------------------------------------------------------------
void PSS_FieldDefinitionDataFeed::SetSourceFieldRepository(PSS_FieldRepository* pRepository)
{
    m_pSourceFieldRepository = pRepository;
}
//---------------------------------------------------------------------------
const PSS_FieldRepository* PSS_FieldDefinitionDataFeed::GetImportedFieldRepository() const
{
    return m_pImportedFieldRepository;
}
//---------------------------------------------------------------------------
void PSS_FieldDefinitionDataFeed::SetImportedFieldRepository(PSS_FieldRepository* pRepository)
{
    m_pImportedFieldRepository = pRepository;
}
//---------------------------------------------------------------------------

#endif
