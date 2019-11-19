/****************************************************************************
 * ==> PSS_UserDirectoryManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an user directory manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserDirectoryManagerH
#define PSS_UserDirectoryManagerH

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
* User directory manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserDirectoryManager
{
    public:
        /**
        * Constructor
        *@param directory - directory
        */
        PSS_UserDirectoryManager(const CString& directory = "");

        virtual ~PSS_UserDirectoryManager();

        /**
        * Gets the directory
        *@return the directory
        */
        virtual inline CString GetDirectory() const;

        /**
        * Sets the directory
        *@param value - the directory
        */
        virtual BOOL SetDirectory(const CString& value);

        /**
        * Creates an user
        *@param userName - the user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateUser(const CString& userName);

        /**
        * Checks if the user exists
        *@param userName - the user name
        *@return TRUE if the user exists, otherwise FALSE
        */
        virtual BOOL UserExist(const CString& userName);

        /**
        * Builds the user directory
        *@param userName - the user name
        *@return the user directory
        */
        virtual inline CString BuildUserDirectory(const CString& userName);

    private:
        CString m_Directory;
        DWORD   m_BufferLength;
        char    m_CurrentDir[MAX_PATH];

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserDirectoryManager(const PSS_UserDirectoryManager& other);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        const PSS_UserDirectoryManager& operator = (const PSS_UserDirectoryManager& other);

        /**
        * Saves the current directory
        */
        inline void SaveCurrentDirectory();

        /**
        * Sets the last current directory
        */
        inline void SetLastCurrentDirectory();
};

//---------------------------------------------------------------------------
// PSS_UserDirectoryManager
//---------------------------------------------------------------------------
CString PSS_UserDirectoryManager::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
CString PSS_UserDirectoryManager::BuildUserDirectory(const CString& userName)
{
    return m_Directory + "\\" + userName;
}
//---------------------------------------------------------------------------
void PSS_UserDirectoryManager::SaveCurrentDirectory()
{
    // keep the old directory
    ::GetCurrentDirectory(m_BufferLength, m_CurrentDir);
}
//---------------------------------------------------------------------------
void PSS_UserDirectoryManager::SetLastCurrentDirectory()
{
    // set back the directory
    ::SetCurrentDirectory(m_CurrentDir);
}
//---------------------------------------------------------------------------

#endif
