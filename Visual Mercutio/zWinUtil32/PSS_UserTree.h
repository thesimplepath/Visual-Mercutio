/****************************************************************************
 * ==> PSS_UserTree --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user tree                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserTreeH
#define PSS_UserTreeH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_UserManager.h"
#include "zBaseLib\PSS_TreeCtrl.h"

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
* User tree
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserTree
{
    public:
        /**
        * Constructor
        *@param pTreeCtrl - tree control, can be NULL
        *@param pUserManager - user manager, can be NULL
        */
        PSS_UserTree(PSS_TreeCtrl* pTreeCtrl = NULL, PSS_UserManager* pUserManager = NULL);

        virtual ~PSS_UserTree();

        /**
        * Initializes the user tree
        *@param pTreeCtrl - tree control
        *@param pUserManager - user manager
        */
        virtual void Initialize(PSS_TreeCtrl* pTreeCtrl, PSS_UserManager* pUserManager);

        /**
        * Re-initializes the user tree
        *@param pUserManager - user manager
        */
        virtual void ReInitialize(PSS_UserManager* pUserManager);

        /**
        * Refreshes the user tree
        */
        virtual void Refresh();

        /**
        * Gets the selected user
        *@return the selected user, NULL if no selection or on error
        */
        virtual ZUser* GetSelectedUser() const;

        /**
        * Gets the selected department
        *@return the selected department, empty string if no selection or on error
        */
        virtual CString GetSelectedDepartement() const;

        /**
        * Called when user list changed
        */
        virtual void OnUserListChanged();

    private:
        PSS_TreeCtrl*    m_pTreeCtrl;
        PSS_UserManager* m_pUserManager;
        CStringArray     m_DepartementArray;
        bool             m_Invalid;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UserTree(const PSS_UserTree& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_UserTree& operator = (const PSS_UserTree& other);

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Initializes the tree
        */
        void InitializeTree();

        /**
        * Adds a department item
        *@param department - department name
        *@param iconIndex - icon index
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddDepartementItem(const CString& departement, int iconIndex);

        /**
        * Adds an user item
        *@param pData - user data
        *@param hParentTreeItem - parent tree item handle to add to, if NULL item will be added to root item
        *@param iconIndex - icon index
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddUserItem(ZUser* pData, HTREEITEM hParentTreeItem, int iconIndex);

        /**
        * Checks if a department exists
        *@param departement - departement name to search
        *@return TRUE if the department exists, otherwise FALSE
        */
        BOOL DepartementExist(const CString& departement);

        /**
        * Builds the department array
        */
        void BuildDepartementArray();
};

#endif
