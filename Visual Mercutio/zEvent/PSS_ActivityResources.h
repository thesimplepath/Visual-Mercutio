/****************************************************************************
 * ==> PSS_ActivityResources -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the resources for an activity                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityResourcesH
#define PSS_ActivityResourcesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "mfc.h"

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_MailUserList.h"
#include "zBaseLib\PSS_UserManager.h"

// class name mapping
#ifndef PSS_Process
    #define PSS_Process ZProcess
#endif

// forward class declarations
class PSS_Process;

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
* Activity resources
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityResources : public CObject
{
    DECLARE_DYNAMIC(PSS_ActivityResources)

    public:
        /**
        * User type
        */
        enum class IEUserType
        {
            IE_UT_Users,
            IE_UT_ResponsibleOfUser,
            IE_UT_AttributionOfUsers,
            IE_UT_UserFromActivity
        };

        typedef CObject inherited;

    public:
        PSS_ActivityResources();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityResources(const PSS_ActivityResources& other);

        virtual ~PSS_ActivityResources();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityResources& operator = (const PSS_ActivityResources& other);

        /**
        * Stores from the archive to the resource
        *@param ar - archive
        *@param activityResource - activity resource
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        friend CArchive& operator >> (CArchive& ar, PSS_ActivityResources& activityResource);

        /**
        * Stores the resource to the archive
        *@param ar - archive
        *@param activityResource - activity resource
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        friend CArchive& operator << (CArchive& ar, const PSS_ActivityResources& activityResource);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_ActivityResources* Clone();

        /**
        * Adds a new user
        *@param userName - the user name
        */
        virtual void AddUser(const CString& userName);

        /**
        * Adds new users
        *@param userNames - delimited string containing the user names to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddUsers(const CString& userNames);

        /**
        * Removes an user
        *@param userName - the user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveUser(const CString& userName);

        /**
        * Searches if an user exists
        *@param userName - the user name
        *@return TRUE if the user exists, otherwise FALSE
        */
        virtual BOOL UserExist(const CString& userName) const;

        /**
        * Gets the user count
        *@return the user count
        */
        virtual inline std::size_t GetUserCount() const;

        /**
        * Gets the user at index
        *@param index - index
        *@return the user, empty string if not found or on error
        */
        virtual inline CString GetUserAt(int index) const;

        /**
        * Removes all the users
        */
        virtual inline void RemoveAllUsers();

        /**
        * Build a person list for the email
        *@param pMainProcess - main process
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@return the user email list
        */
        virtual PSS_MailUserList* CreatePersonList(PSS_Process*           pMainProcess,
                                                   const PSS_UserManager& userManager,
                                                   const CString&         connectedUser);

        /**
        * Fills a person array
        *@param pMainProcess - main process
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with the result
        *@param connectedUser - connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL FillPersonArray(PSS_Process*           pMainProcess,
                                     const PSS_UserManager& userManager,
                                     CStringArray&          userArray,
                                     const CString&         connectedUser);

        /**
        * Build a delimited string containing the person list
        *@param pMainProcess - main process
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString CreatePersonDelimStr(PSS_Process*           pMainProcess,
                                             const PSS_UserManager& userManager,
                                             const CString&         connectedUser,
                                             const CString&         delimiter = ";");

        /**
        * Gets the activity user type
        *@return the activity user type
        */
        virtual inline const IEUserType GetUserType() const;

        /**
        * Sets the activity user type
        *@param value - the activity user type
        */
        virtual inline void SetUserType(IEUserType value);

    private:
        IEUserType   m_UserType;
        CStringArray m_UserArray;
};

//---------------------------------------------------------------------------
// PSS_ActivityResources
//---------------------------------------------------------------------------
std::size_t PSS_ActivityResources::GetUserCount() const
{
    return m_UserArray.GetSize();
}
//---------------------------------------------------------------------------
CString PSS_ActivityResources::GetUserAt(int index) const
{
    return m_UserArray.GetAt(index);
}
//---------------------------------------------------------------------------
void PSS_ActivityResources::RemoveAllUsers()
{
    m_UserArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_ActivityResources::IEUserType PSS_ActivityResources::GetUserType() const
{
    return m_UserType;
}
//---------------------------------------------------------------------------
void PSS_ActivityResources::SetUserType(IEUserType value)
{
    m_UserType = value;
}
//---------------------------------------------------------------------------

#endif
