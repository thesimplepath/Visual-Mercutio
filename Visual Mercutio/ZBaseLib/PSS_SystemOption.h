/****************************************************************************
 * ==> PSS_SystemOption ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system options manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SystemOptionH
#define PSS_SystemOptionH

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
* System options manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SystemOption
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file name
        *@param sectionName - section name containing the options in the ini file
        */
        PSS_SystemOption(const CString& iniFile = _T(""), const CString& sectionName = _T(""));

        virtual ~PSS_SystemOption();

        /**
        * Creates the options
        *@param iniFile - initialization file name
        *@param sectionName - section name containing the options in the ini file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& iniFile = _T(""), const CString& sectionName = _T(""));

        /**
        * Gets the ini file name
        *@return the ini file name
        */
        virtual inline const CString GetIniFile() const;

        /**
        * Sets the ini file name
        *@param value - the ini file name
        */
        virtual inline void SetIniFile(const CString& value);

        /**
        * Gets the section name
        *@return the section name
        */
        virtual inline const CString GetSectionName() const;

        /**
        * Sets the section name
        *@param value - the section name
        */
        virtual inline void SetSectionName(const CString& value);

        /**
        * Reads a system option
        *@param entityKey - entity key
        *@param defaultValue - default value to return in case the key is not found in the file
        *@returns the system option
        */
        virtual CString ReadOption(const CString& entityKey, LPCTSTR        pDefaultValue = NULL);
        virtual CString ReadOption(const CString& entityKey, const CString& defaultValue  = _T(""));
        virtual bool    ReadOption(const CString& entityKey, bool           defaultValue  = false);
        virtual int     ReadOption(const CString& entityKey, int            defaultValue = 0);
        virtual float   ReadOption(const CString& entityKey, float          defaultValue  = 0);
        virtual double  ReadOption(const CString& entityKey, double         defaultValue  = 0);

        /**
        * Writes a system option
        *@param entityKey - entity key
        *@param value - value to write
        *@returns TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteOption(const CString& entityKey, LPCTSTR        pValue);
        virtual BOOL WriteOption(const CString& entityKey, const CString& value);
        virtual BOOL WriteOption(const CString& entityKey, bool           value);
        virtual BOOL WriteOption(const CString& entityKey, int            value);
        virtual BOOL WriteOption(const CString& entityKey, float          value);
        virtual BOOL WriteOption(const CString& entityKey, double         value);

    private:
        CString m_IniFile;
        CString m_SectionName;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SystemOption(const PSS_SystemOption& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SystemOption& operator = (const PSS_SystemOption& other);
};

//---------------------------------------------------------------------------
// PSS_SystemOption
//---------------------------------------------------------------------------
const CString PSS_SystemOption::GetIniFile() const
{
    return m_IniFile;
}
//---------------------------------------------------------------------------
void PSS_SystemOption::SetIniFile(const CString& value)
{
    m_IniFile = value;
}
//---------------------------------------------------------------------------
const CString PSS_SystemOption::GetSectionName() const
{
    return m_SectionName;
}
//---------------------------------------------------------------------------
void PSS_SystemOption::SetSectionName(const CString& value)
{
    m_SectionName = value;
}
//---------------------------------------------------------------------------

#endif
