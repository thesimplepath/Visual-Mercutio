/****************************************************************************
 * ==> PSS_ProcessDocumentOptions ------------------------------------------*
 ****************************************************************************
 * Description : Provides the process document options                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessDocumentOptionsH
#define PSS_ProcessDocumentOptionsH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Process document options
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessDocumentOptions
{
    public:
        PSS_ProcessDocumentOptions();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessDocumentOptions(const PSS_ProcessDocumentOptions& other);

        virtual ~PSS_ProcessDocumentOptions();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProcessDocumentOptions& operator = (const PSS_ProcessDocumentOptions& other);

        /**
        * Stores from the archive to the object document options
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_ProcessDocumentOptions& docOptions);

        /**
        * Stores the object document options to the archive
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_ProcessDocumentOptions& docOptions);

        /**
        * Builds the synchronization file name
        *@param documentFileName - document file name
        *@return the built synchronization file name
        */
        virtual CString BuildSynchronizationFileName(const CString& documentFileName);

        /**
        * Gets if it's necessary to synchronize the feed data file
        *@return TRUE if it's necessary to synchronize the feed data file, otherwise FALSE
        */
        virtual inline const BOOL GetIsSynchronizeExchangeFeedFile() const;

        /**
        * Sets if it's necessary to synchronize the feed data file
        *@param value - if TRUE, it will be necessary to synchronize the feed data file
        */
        virtual inline void SetIsSynchronizeExchangeFeedFile(BOOL value);

        /**
        * Gets the synchronization time (in seconds)
        *@return the synchronization time (in seconds)
        */
        virtual inline const int GetSynchronizeTimeSequence() const;

        /**
        * Sets the synchronization time (in seconds)
        *@param value - the synchronization time (in seconds)
        */
        virtual inline void SetSynchronizeTimeSequence(int value);

        /**
        * Gets the file name auto-creation mode
        *@return the file name auto-creation mode
        */
        virtual inline const ESynchronizationFileType GetAutomaticSynchronizeFileName() const;

        /**
        * Sets the file name auto-creation mode
        *@rparam value - the file name auto-creation mode
        */
        virtual inline void SetAutomaticSynchronizeFileName(ESynchronizationFileType value);

        /**
        * Gets the synchronization file name if not automatic
        *@return the synchronization file name if not automatic
        */
        virtual inline const CString GetSynchronizeFileName() const;

        /**
        * Sets the synchronization file name if not automatic
        *@param value - the synchronization file name
        */
        virtual inline void SetSynchronizeFileName(const CString& value);

        /**
        * Gets if a synchronization header should be created
        *@return TRUE if a synchronization header should be created, otherwise FALSE
        */
        virtual inline const BOOL GetSynchronizationHeader() const;

        /**
        * Sets if a synchronization header should be created
        *@param value - if TRUE, a synchronization header should be created
        */
        virtual inline void SetSynchronizationHeader(BOOL value);

        /**
        * Gets the separator type
        *@return the separator type
        */
        virtual inline const ESynchronizationSeparatorType GetSynchronizationSeparator() const;

        /**
        * Sets the separator type
        *@param value - the separator type
        */
        virtual inline void SetSynchronizationSeparator(ESynchronizationSeparatorType value);

    private:
        ESynchronizationFileType      m_AutomaticSynchronizeFileName;
        ESynchronizationSeparatorType m_SynchronizationSeparator;
        CString                       m_SynchronizeFileName;
        int                           m_SynchronizeTimeSequence;
        BOOL                          m_IsSynchronizeExchangeFeedFile;
        BOOL                          m_SynchronizationHeader;
};

//---------------------------------------------------------------------------
// PSS_ProcessDocumentOptions
//---------------------------------------------------------------------------
const BOOL PSS_ProcessDocumentOptions::GetIsSynchronizeExchangeFeedFile() const
{
    return m_IsSynchronizeExchangeFeedFile;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetIsSynchronizeExchangeFeedFile(BOOL value)
{
    m_IsSynchronizeExchangeFeedFile = value;
}
//---------------------------------------------------------------------------
const int PSS_ProcessDocumentOptions::GetSynchronizeTimeSequence() const
{
    return m_SynchronizeTimeSequence;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetSynchronizeTimeSequence(int value)
{
    m_SynchronizeTimeSequence = value;
}
//---------------------------------------------------------------------------
const ESynchronizationFileType PSS_ProcessDocumentOptions::GetAutomaticSynchronizeFileName() const
{
    return m_AutomaticSynchronizeFileName;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetAutomaticSynchronizeFileName(ESynchronizationFileType value)
{
    m_AutomaticSynchronizeFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ProcessDocumentOptions::GetSynchronizeFileName() const
{
    return m_SynchronizeFileName;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetSynchronizeFileName(const CString& value)
{
    m_SynchronizeFileName = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ProcessDocumentOptions::GetSynchronizationHeader() const
{
    return m_SynchronizationHeader;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetSynchronizationHeader(BOOL value)
{
    m_SynchronizationHeader = value;
}
//---------------------------------------------------------------------------
const ESynchronizationSeparatorType PSS_ProcessDocumentOptions::GetSynchronizationSeparator() const
{
    return m_SynchronizationSeparator;
}
//---------------------------------------------------------------------------
void PSS_ProcessDocumentOptions::SetSynchronizationSeparator(ESynchronizationSeparatorType value)
{
    m_SynchronizationSeparator = value;
}
//---------------------------------------------------------------------------

#endif
