/****************************************************************************
 * ==> PSS_DocumentOptions -------------------------------------------------*
 ****************************************************************************
 * Description : Provides document options                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentOptionsH
#define PSS_DocumentOptionsH

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
* Document options
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocumentOptions
{
    public:
        PSS_DocumentOptions();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DocumentOptions(const PSS_DocumentOptions& other);

        virtual ~PSS_DocumentOptions();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DocumentOptions& operator = (const PSS_DocumentOptions& other);

        /**
        * Stores the object document options from the archive
        *@param ar - archive
        *@param docOptions - document options
        *@return provided archive, to allow to chain operators like a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_DocumentOptions& docOptions);

        /**
        * Stores the object document options to the archive
        *@param ar - archive
        *@param docOptions - document options
        *@return provided archive, to allow to chain operators like a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_DocumentOptions& docOptions);

        /**
        * Builds the synchronization file name
        *@param documentFileName - document file name
        *@return built synchronization file name
        */
        virtual CString BuildSynchronizationFileName(const CString& documentFileName);

        /**
        * Gets the empty style to use when the controls are empty
        *@return the empty style to use when the controls are empty
        */
        virtual inline const ELineType GetEmptyStyle() const;

        /**
        * Sets the empty style to use when the controls are empty
        *@param value - the empty style to use when the controls are empty
        */
        virtual inline void SetEmptyStyle(ELineType value);

        /**
        * Gets if it's necessary to synchronize the feed data file
        *@return TRUE if it is necessary to synchronize the feed data file, otherwise FALSE
        */
        virtual inline const BOOL GetIsSynchronizeExchangeFeedFile() const;

        /**
        * Sets if it's necessary to synchronize the feed data file
        *@param value - if TRUE, it's necessary to synchronize the feed data file
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
        * Gets if hidden fields must be shown
        *@return yes, no or application
        */
        virtual inline const EOptionType GetShowHiddenField() const;

        /**
        * Sets if hidden fields must be shown
        *@param value - yes, no or application
        */
        virtual inline void SetShowHiddenField(EOptionType value);

        /**
        * Gets if empty lines must be shown if there are emty
        *@return yes, no or application
        */
        virtual inline const EOptionType GetShowEmptyLine() const;

        /**
        * Sets if empty lines must be shown if there are emty
        *@param value - yes, no or application
        */
        virtual inline void SetShowEmptyLine(EOptionType value);

        /**
        * Gets if the file name is automatically created
        *@return automatic name, file name specified, or folder specified
        */
        virtual inline const ESynchronizationFileType GetAutomaticSynchronizeFileName() const;

        /**
        * Sets if the file name is automatically created
        *@return automatic name, file name specified, or folder specified
        */
        virtual inline void SetAutomaticSynchronizeFileName(ESynchronizationFileType value);

        /**
        * Gets the synchronization file name if not automatic
        *@return the synchronization file name
        */
        virtual inline const CString GetSynchronizeFileName() const;

        /**
        * Sets the synchronization file name if not automatic
        *@param value - the synchronization file name
        */
        virtual inline void SetSynchronizeFileName(const CString& value);

        /**
        * Gets if the header should be synchronized
        *@return TRUE if the header should be synchronized, otherwise FALSE
        */
        virtual inline const BOOL GetSynchronizationHeader() const;

        /**
        * Sets if the header should be synchronized
        *@param value - if TRUE, the header should be synchronized
        */
        virtual inline void SetSynchronizationHeader(BOOL value);

        /**
        * Gets the seperator type
        *@return the separator type
        */
        virtual inline const ESynchronizationSeparatorType GetSynchronizationSeparator() const;

        /**
        * Sets the seperator type
        *@param value - the separator type
        */
        virtual inline void SetSynchronizationSeparator(ESynchronizationSeparatorType value);

        /**
        * Gets if empty style should be printed
        *@return TRUE if empty style should be printed, otherwise FALSE
        */
        virtual inline BOOL GetPrintEmptyStyleWhenEmpty() const;

        /**
        * Sets if empty style should be printed
        *@param value - if TRUE, empty style should be printed
        */
        virtual inline void SetPrintEmptyStyleWhenEmpty(BOOL value);

    private:
        EOptionType                   m_ShowHiddenField;
        EOptionType                   m_ShowEmptyLine;
        ELineType                     m_EmptyStyle;
        ESynchronizationFileType      m_AutomaticSynchronizeFileName;
        ESynchronizationSeparatorType m_SynchronizationSeparator;
        CString                       m_SynchronizeFileName;
        int                           m_SynchronizeTimeSequence;
        BOOL                          m_IsSynchronizeExchangeFeedFile;
        BOOL                          m_SynchronizationHeader;
        BOOL                          m_PrintEmptyStyleWhenEmpty;
};

//---------------------------------------------------------------------------
// PSS_DocumentOptions
//---------------------------------------------------------------------------
const ELineType PSS_DocumentOptions::GetEmptyStyle() const
{
    return m_EmptyStyle;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetEmptyStyle(ELineType value)
{
    m_EmptyStyle = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_DocumentOptions::GetIsSynchronizeExchangeFeedFile() const
{
    return m_IsSynchronizeExchangeFeedFile;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetIsSynchronizeExchangeFeedFile(BOOL value)
{
    m_IsSynchronizeExchangeFeedFile = value;
}
//---------------------------------------------------------------------------
const int PSS_DocumentOptions::GetSynchronizeTimeSequence() const
{
    return m_SynchronizeTimeSequence;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetSynchronizeTimeSequence(int value)
{
    m_SynchronizeTimeSequence = value;
}
//---------------------------------------------------------------------------
const EOptionType PSS_DocumentOptions::GetShowHiddenField() const
{
    return m_ShowHiddenField;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetShowHiddenField(EOptionType value)
{
    m_ShowHiddenField = value;
}
//---------------------------------------------------------------------------
const EOptionType PSS_DocumentOptions::GetShowEmptyLine() const
{
    return m_ShowEmptyLine;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetShowEmptyLine(EOptionType value)
{
    m_ShowEmptyLine = value;
}
//---------------------------------------------------------------------------
const ESynchronizationFileType PSS_DocumentOptions::GetAutomaticSynchronizeFileName() const
{
    return m_AutomaticSynchronizeFileName;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetAutomaticSynchronizeFileName(ESynchronizationFileType value)
{
    m_AutomaticSynchronizeFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_DocumentOptions::GetSynchronizeFileName() const
{
    return m_SynchronizeFileName;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetSynchronizeFileName(const CString& value)
{
    m_SynchronizeFileName = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_DocumentOptions::GetSynchronizationHeader() const
{
    return m_SynchronizationHeader;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetSynchronizationHeader(BOOL value)
{
    m_SynchronizationHeader = value;
}
//---------------------------------------------------------------------------
const ESynchronizationSeparatorType PSS_DocumentOptions::GetSynchronizationSeparator() const
{
    return m_SynchronizationSeparator;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetSynchronizationSeparator(ESynchronizationSeparatorType value)
{
    m_SynchronizationSeparator = value;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentOptions::GetPrintEmptyStyleWhenEmpty() const
{
    return m_PrintEmptyStyleWhenEmpty;
}
//---------------------------------------------------------------------------
void PSS_DocumentOptions::SetPrintEmptyStyleWhenEmpty(BOOL value)
{
    m_PrintEmptyStyleWhenEmpty = value;
}
//---------------------------------------------------------------------------

#endif
