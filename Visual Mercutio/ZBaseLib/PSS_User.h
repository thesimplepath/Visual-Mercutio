/****************************************************************************
 * ==> PSS_User ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserH
#define PSS_UserH

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
* User manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_User : public CObject
{
    DECLARE_DYNCREATE(PSS_User)

    public:
        /**
        * Constructor
        *@param userName - the user name
        *@param mailAddress - the mail address
        *@param description - the description
        *@param responsible - the responsible person name
        *@param department - the department
        *@param isAdministrator - if TRUE, the user is an administrator
        *@param displayName - the display name
        */
        PSS_User(const CString& userName        = "",
                 const CString& mailAddress     = "",
                 const CString& description     = "",
                 const CString& responsible     = "",
                 const CString& departement     = "",
                 BOOL           isAdministrator = FALSE,
                 const CString& displayName     = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_User(const PSS_User& other);

        virtual ~PSS_User();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_User& operator = (const PSS_User& other);

        /**
        * Equality operator
        *@param other - other object to compare with
        *@return TRUE if the both objects are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_User& other);

        /**
        * Equality operator with a string
        *@param other - string to compare with
        *@return TRUE if the both objects are equals, otherwise FALSE
        */
        BOOL operator == (const CString& other);

        /**
        * Equality operator with a char array
        *@param pOther - char array to compare with
        *@return TRUE if the both objects are equals, otherwise FALSE
        */
        BOOL operator == (LPCTSTR pOther);

        /**
        * Stores from the archive to the user
        *@param ar - archive
        *@param user - user
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_User& user);

        /**
        * Stores the user to the archive
        *@param ar - archive
        *@param user - user
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_User& user);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_User* Clone() const;

        /**
        * Checks if the user has administrator rights
        *@return TRUE if the user has administrator rights, otherwise FALSE
        */
        virtual inline BOOL IsAdministrator() const;

        /**
        * Sets the user as administrator
        *@param value - if TRUE, the user will have administrator rights
        */
        virtual inline void SetAdministrator(BOOL value = TRUE);

        /**
        * Gets the user name
        *@return the user name
        */
        virtual inline const CString GetUserName() const;

        /**
        * Sets the user name
        *@param value - the user name
        */
        virtual inline void SetUserName(const CString& value);

        /**
        * Gets the mail address
        *@return the mail address
        */
        virtual inline const CString GetMailAddress() const;

        /**
        * Sets the mail address
        *@param value - the mail address
        */
        virtual inline void SetMailAddress(const CString& value);

        /**
        * Gets the description
        *@return the description
        */
        virtual inline const CString GetDescription() const;

        /**
        * Sets the description
        *@param value - the description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the responsible person name
        *@return the responsible person name
        */
        virtual inline const CString& GetResponsible() const;

        /**
        * Sets the responsible person name
        *@param value - the responsible person name
        */
        virtual inline void SetResponsible(const CString& value);

        /**
        * Gets the department name
        *@return the department name
        */
        virtual inline const CString GetDepartement() const;

        /**
        * Sets the department name
        *@param value - the department name
        */
        virtual inline void SetDepartement(const CString& value);

        /**
        * Gets the display name
        *@return the display name
        */
        virtual inline const CString GetDisplayName() const;

        /**
        * Sets the display name
        *@param value - the display name
        */
        virtual inline void SetDisplayName(const CString& value);

    private:
        CString m_UserName;
        CString m_Description;
        CString m_MailAddress;
        CString m_Responsible;
        CString m_Departement;
        CString m_DisplayName;
        BOOL    m_IsAdministrator;
};

//---------------------------------------------------------------------------
// PSS_User
//---------------------------------------------------------------------------
BOOL PSS_User::IsAdministrator() const
{
    return m_IsAdministrator;
}
//---------------------------------------------------------------------------
void PSS_User::SetAdministrator(BOOL value)
{
    m_IsAdministrator = value;
}
//---------------------------------------------------------------------------
const CString PSS_User::GetUserName() const
{
    return m_UserName;
}
//---------------------------------------------------------------------------
void PSS_User::SetUserName(const CString& value)
{
    m_UserName = value;
}
//---------------------------------------------------------------------------
const CString PSS_User::GetMailAddress() const
{
    return m_MailAddress;
}
//---------------------------------------------------------------------------
void PSS_User::SetMailAddress(const CString& value)
{
    m_MailAddress = value;
}
//---------------------------------------------------------------------------
const CString PSS_User::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_User::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
const CString& PSS_User::GetResponsible() const
{
    return m_Responsible;
}
//---------------------------------------------------------------------------
void PSS_User::SetResponsible(const CString& value)
{
    m_Responsible = value;
}
//---------------------------------------------------------------------------
const CString PSS_User::GetDepartement() const
{
    return m_Departement;
}
//---------------------------------------------------------------------------
void PSS_User::SetDepartement(const CString& value)
{
    m_Departement = value;
}
//---------------------------------------------------------------------------
const CString PSS_User::GetDisplayName() const
{
    return m_DisplayName;
}
//---------------------------------------------------------------------------
void PSS_User::SetDisplayName(const CString& value)
{
    m_DisplayName = value;
}
//---------------------------------------------------------------------------

#endif
