/****************************************************************************
 * ==> PSS_ExtAppProperties ------------------------------------------------*
 ****************************************************************************
 * Description : Provides external application properties                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_ExtAppPropertiesH
#define PSS_ExtAppPropertiesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ExtAppProperties
    #define PSS_ExtAppProperties ZBExtAppProperties
#endif

// processsoft
#include "PSS_PropIDs.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Command_Title_ID      1
#define M_Command_Line_ID       2
#define M_Command_Param_ID      3
#define M_Command_StartupDir_ID 4
#define M_Priority_Level_ID     5
#define M_Window_StartMode_ID   6
//---------------------------------------------------------------------------

/**
* External application properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtAppProperties : public CObject
{
    DECLARE_SERIAL(PSS_ExtAppProperties)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Command_Title      = 0x0001,
            IE_CT_Command_Line       = 0x0002,
            IE_CT_Command_Param      = 0x0004,
            IE_CT_Command_StartupDir = 0x0008,
            IE_CT_Priority_Level     = 0x0010,
            IE_CT_Window_StartMode   = 0x0020,
            IE_CT_All                = OD_CHANGE_ALL
        };

        PSS_ExtAppProperties();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtAppProperties(const PSS_ExtAppProperties& other);

        virtual ~PSS_ExtAppProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtAppProperties& operator = (const PSS_ExtAppProperties& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_ExtAppProperties& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_ExtAppProperties* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_ExtAppProperties* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_ExtAppProperties* pProp);

        /**
        * Checks if the object is empty
        *@return TRUE if the object is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the combination name
        *@return the combination name
        */
        virtual inline CString GetCommandTitle() const;

        /**
        * Sets the combination name
        *@param pValue - the combination name
        */
        virtual void SetCommandTitle(LPCTSTR pValue);

        /**
        * Gets the command line
        *@return the command line
        */
        virtual inline CString GetCommandLine() const;

        /**
        * Sets the command line
        *@param pValue - the command line
        */
        virtual void SetCommandLine(LPCTSTR pValue);

        /**
        * Gets the command parameters
        *@return the command parameters
        */
        virtual inline CString GetCommandParameters() const;

        /**
        * Sets the command parameters
        *@param pValue - the command parameters
        */
        virtual void SetCommandParameters(LPCTSTR pValue);

        /**
        * Gets the command startup parameters
        *@return the command startup parameters
        */
        virtual inline CString GetCommandStartupDirectory() const;

        /**
        * Sets the command startup parameters
        *@param pValue - the command startup parameters
        */
        virtual void SetCommandStartupDirectory(LPCTSTR pValue);

        /**
        * Gets the priority level
        *@return the priority level
        */
        virtual inline int GetPriorityLevel() const;

        /**
        * Sets the priority level
        *@param value - the priority level
        */
        virtual inline void SetPriorityLevel(const int value);

        /**
        * Gets the window start mode
        *@return the window start mode
        */
        virtual inline int GetWindowStartMode() const;

        /**
        * Sets the window start mode
        *@param value - the window start mode
        */
        virtual inline void SetWindowStartMode(const int value);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int   value);
        virtual BOOL SetValue(const int propId, const UINT  value);
        virtual BOOL SetValue(const int propId, const DWORD value);
        virtual BOOL SetValue(const int propId, const float value);
        virtual BOOL SetValue(const int propId, LPCTSTR     pValue);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

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

    protected:
        CString m_CommandTitle;
        CString m_CommandLine;
        CString m_CommandParameters;
        CString m_CommandStartupDirectory;
        int     m_PriorityLevel;
        int     m_WindowStartMode;

    private:
        /**
        * Sets the command title (extended)
        *@param value - the value
        */
        void SetCommandTitleEx(const CString& value);

        /**
        * Sets the command line (extended)
        *@param value - the value
        */
        void SetCommandLineEx(const CString& value);

        /**
        * Sets the command parameters (extended)
        *@param value - the value
        */
        void SetCommandParametersEx(const CString& value);

        /**
        * Sets the command startup directory (extended)
        *@param value - the value
        */
        void SetCommandStartupDirectoryEx(const CString& value);
};

//---------------------------------------------------------------------------
// PSS_ExtAppProperties
//---------------------------------------------------------------------------
PSS_ExtAppProperties* PSS_ExtAppProperties::Dup() const
{
    return new PSS_ExtAppProperties(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::IsEmpty() const
{
    return m_CommandTitle.IsEmpty()      &&
           m_CommandLine.IsEmpty()       &&
           m_CommandParameters.IsEmpty() &&
           m_CommandStartupDirectory.IsEmpty();
};
//---------------------------------------------------------------------------
CString PSS_ExtAppProperties::GetCommandTitle() const
{
    return m_CommandTitle;
}
//---------------------------------------------------------------------------
CString PSS_ExtAppProperties::GetCommandLine() const
{
    return m_CommandLine;
}
//---------------------------------------------------------------------------
CString PSS_ExtAppProperties::GetCommandParameters() const
{
    return m_CommandParameters;
}
//---------------------------------------------------------------------------
CString PSS_ExtAppProperties::GetCommandStartupDirectory() const
{
    return m_CommandStartupDirectory;
}
//---------------------------------------------------------------------------
int PSS_ExtAppProperties::GetPriorityLevel() const
{
    return m_PriorityLevel;
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetPriorityLevel(const int value)
{
    m_PriorityLevel = value;
}
//---------------------------------------------------------------------------
int PSS_ExtAppProperties::GetWindowStartMode() const
{
    return m_WindowStartMode;
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetWindowStartMode(const int value)
{
    m_WindowStartMode = value;
}
//---------------------------------------------------------------------------

#endif
