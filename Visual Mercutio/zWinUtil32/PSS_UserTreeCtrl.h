/****************************************************************************
 * ==> PSS_UserTreeCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user tree control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserTreeCtrlH
#define PSS_UserTreeCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_TreeCtrl.h"
#include "PSS_UserTree.h"

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
* User tree control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserTreeCtrl : public PSS_TreeCtrl
{
    public:
        /**
        * Constructor
        *@param pUserManager - user manager, can be NULL
        */
        PSS_UserTreeCtrl(PSS_UserManager* pUserManager = NULL);

        virtual ~PSS_UserTreeCtrl();

        /**
        * Initializes the user tree control
        *@param pUserManager - user manager
        */
        void Initialize(PSS_UserManager* pUserManager);

        /**
        * Re-initializes the user tree control
        *@param pUserManager - user manager
        */
        void ReInitialize(PSS_UserManager* pUserManager);

        /**
        * Refreshes the user tree control
        */
        void Refresh();

        /**
        * Gets the selected user
        *@return the selected user, NULL if no selectoin or on error
        */
        ZUser* GetSelectedUser();

        /**
        * Gets the selected department
        *@return the selected department, empty string if no selectoin or on error
        */
        CString GetSelectedDepartement();

        /// ClassWizard generated message map functions
        //{{AFX_MSG(PSS_UserTreeCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_UserManager* m_pUserManager;
        PSS_UserTree     m_UserTree;
        bool             m_Invalid;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserTreeCtrl(const PSS_UserTreeCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserTreeCtrl& operator = (const PSS_UserTreeCtrl& other);
};

#endif
