/****************************************************************************
 * ==> PSS_UserListCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user list control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserListCtrlH
#define PSS_UserListCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_UserManager.h"
#include "zBaseLib\PSS_ListCtrl.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* User list control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef _WIN32
    // 32 bit version
    class AFX_EXT_CLASS PSS_UserListCtrl : public PSS_ListCtrl
#else
    // 16 bit version
    class AFX_EXT_CLASS PSS_UserListCtrl : public CListBox
#endif
{
    public:
        /**
        * Constructor
        *@param pUserManager - user manager
        *@param department - department
        */
        PSS_UserListCtrl(PSS_UserManager* pUserManager = NULL, const CString& departement = "");

        virtual ~PSS_UserListCtrl();

        /**
        * Initializes the user list control
        *@param pUserManager - user manager
        *@param department - department
        *@return user count
        */
        virtual int Initialize(PSS_UserManager* pUserManager, const CString& departement = "");

        /**
        * Gets the selected user name
        *@return the selected user name, empty string if no selection or on error
        */
        virtual CString GetSelectedUserName() const;

        /**
        * Gets the selected user names
        *@param[in, out] userNameArray - array to populate with the user names
        *@return the selected user name count
        */
        virtual int GetSelectedUserNames(CStringArray& userNameArray) const;

        /**
        * Sets the department
        *@param department - department
        */
        virtual inline void SetDepartement(const CString& departement);

        /**
        * Refreshes the control
        *@return user count
        */
        virtual int Refresh();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UserListCtrl)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_UserListCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_UserManager* m_pUserManager;
        CString          m_Departement;
        BOOL             m_AdminOnly;
        BOOL             m_NonAdminOnly;
        BOOL             m_ColumnsBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserListCtrl(const PSS_UserListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserListCtrl& operator = (const PSS_UserListCtrl& other);

        /**
        * Builds the columns
        */
        void BuildColumns();
};

//---------------------------------------------------------------------------
// PSS_UserListCtrl
//---------------------------------------------------------------------------
void PSS_UserListCtrl::SetDepartement(const CString& departement)
{
    m_Departement = departement;
}
//---------------------------------------------------------------------------

#endif
