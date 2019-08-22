/****************************************************************************
 * ==> PSS_FieldValueDataFeed ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a data feed for field values only                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldValueDataFeedH
#define PSS_FieldValueDataFeedH

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
* Data feed for field values only
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldValueDataFeed : public PSS_Export
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
        PSS_FieldValueDataFeed(const CString&                fileName          = "",
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
        *@param pValueArray - value array
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        PSS_FieldValueDataFeed(const CString&                fileName,
                               CStringArray*                 pValueArray,
                               BOOL                          generateHeader  = FALSE,
                               ESynchronizationSeparatorType separatorType   = E_SS_Automatic,
                               const CString&                schema          = g_OriginalSchema,
                               int                           propagationMode = g_LocatePageOnly,
                               BOOL                          emptyWhenZero   = FALSE,
                               PSS_StatusBar*                pStatusBar      = NULL);

        virtual ~PSS_FieldValueDataFeed();

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
                                   PSS_FieldRepository*          pFieldRepository  = NULL,
                                   PSS_FieldObjectDefinition*    pObjectDefinition = NULL,
                                   BOOL                          generateHeader    = FALSE,
                                   ESynchronizationSeparatorType separatorType     = E_SS_Automatic,
                                   const CString&                schema            = g_OriginalSchema,
                                   int                           propagationMode   = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero     = FALSE,
                                   PSS_StatusBar*                pStatusBar        = NULL);

        /**
        * Creates the class content
        *@param fileName - file name
        *@param pValueArray - value array
        *@param generateHeader - if TRUE, a header will be generated
        *@param separatorType - separator type
        *@param schema - schema
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, fields will be emptied when set to zero
        *@param pStatusBar - status bar
        */
        virtual inline void Create(const CString&                filename,
                                   CStringArray*                 pValueArray     = NULL,
                                   BOOL                          generateHeader  = FALSE,
                                   ESynchronizationSeparatorType separatorType   = E_SS_Automatic,
                                   const CString&                schema          = g_OriginalSchema,
                                   int                           propagationMode = g_LocatePageOnly,
                                   BOOL                          emptyWhenZero   = FALSE,
                                   PSS_StatusBar*                pStatusBar      = NULL);

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

    private:
        CStringArray*              m_pValueArray;
        PSS_FieldObjectDefinition* m_pObjectDefinition;
        PSS_FieldRepository*       m_pSourceFieldRepository;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldValueDataFeed(const PSS_FieldValueDataFeed& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldValueDataFeed& operator = (const PSS_FieldValueDataFeed& other);

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
};

//---------------------------------------------------------------------------
// PSS_FieldValueDataFeed
//---------------------------------------------------------------------------
void PSS_FieldValueDataFeed::Create(const CString&                fileName,
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
void PSS_FieldValueDataFeed::Create(const CString&                fileName,
                                    CStringArray*                 pValueArray,
                                    BOOL                          generateHeader,
                                    ESynchronizationSeparatorType separatorType,
                                    const CString&                schema,
                                    int                           propagationMode,
                                    BOOL                          emptyWhenZero,
                                    PSS_StatusBar* pStatusBar)
{
    m_pValueArray = pValueArray;

    PSS_Export::Create(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar);
}
//---------------------------------------------------------------------------
const PSS_FieldRepository* PSS_FieldValueDataFeed::GetSourceFieldRepository() const
{
    return m_pSourceFieldRepository;
}
//---------------------------------------------------------------------------
void PSS_FieldValueDataFeed::SetSourceFieldRepository(PSS_FieldRepository* value)
{
    m_pSourceFieldRepository = value;
}
//---------------------------------------------------------------------------

#endif
