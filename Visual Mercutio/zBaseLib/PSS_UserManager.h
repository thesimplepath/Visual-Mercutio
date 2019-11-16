/****************************************************************************
 * ==> PSS_UserManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserManagerH
#define PSS_UserManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_User.h"

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
* User manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserManager
{
    public:
        PSS_UserManager();
        virtual ~PSS_UserManager();

        /**
        * Adds a new user
        *@param userName - user name
        *@param mailAddress - mail address
        *@param description - description
        *@param responsible - responsible
        *@param department - department
        *@param isAdministrator - if TRUE, the user is an administrator
        *@param displayName - display name
        */
        virtual void AddUser(const CString& userName,
                             const CString& mailAddress     = "",
                             const CString& description     = "",
                             const CString& responsible     = "",
                             const CString& departement     = "",
                             BOOL           isAdministrator = FALSE,
                             const CString& displayName     = "");

        /**
        * Adds a new user
        *@param user - user to add
        */
        virtual void AddUser(PSS_User& user);

        /**
        * Searches if a specific user exists
        *@param userName - user name
        *@param byDisplayName - if TRUE, the search will be processed by display name
        *@return the user, NULL if not found or on error
        */
        virtual PSS_User* FindUser(const CString& userName, BOOL byDisplayName = FALSE) const;

        /**
        * Removes a specific user
        *@param userName - user name
        *@param byDisplayName - if TRUE, the search will be processed by display name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveUser(const CString& userName, BOOL byDisplayName = FALSE);

        /**
        * Removes all the users
        */
        virtual void RemoveAllUsers();

        /**
        * Gets the user at the index
        *@param index - index
        *@return the user, NULL if not found or on error
        */
        virtual inline PSS_User* GetAt(int index) const;

        /**
        * Gets the user count
        *@return the user count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObArray m_UserArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserManager(const PSS_UserManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserManager& operator = (const PSS_UserManager& other);
};

//---------------------------------------------------------------------------
// PSS_UserManager
//---------------------------------------------------------------------------
PSS_User* PSS_UserManager::GetAt(int index) const
{
    if (index < int(GetCount()))
        return (PSS_User*)m_UserArray.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
std::size_t PSS_UserManager::GetCount() const
{
    return m_UserArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
