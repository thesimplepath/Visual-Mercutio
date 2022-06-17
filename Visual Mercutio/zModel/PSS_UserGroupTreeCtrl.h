/****************************************************************************
 * ==> PSS_UserGroupTreeCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group tree controller                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupTreeCtrlH
#define PSS_UserGroupTreeCtrlH

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

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeCtrl.h"

// class name mapping
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif

// forward class declaration
class ZBWorkspaceEnv;
class PSS_UserEntity;
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* User group tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserGroupTreeCtrl : public PSS_TreeCtrl,
                                            public PSS_Subject,
                                            public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param rootName - the root name
        *@param pLogicalRuleRoot - the logical rule root
        */
        PSS_UserGroupTreeCtrl(const CString& rootName = _T(""), PSS_UserGroupEntity* pUserGroupRoot = NULL);

        virtual ~PSS_UserGroupTreeCtrl();

        /**
        * Initializes the controller
        *@param rootName - the root name
        *@param pUserGroupRoot - the user group root
        */
        virtual void Initialize(const CString& rootName, PSS_UserGroupEntity* pUserGroupRoot);

        /**
        * Releases the controller
        */
        virtual void Release();

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Gets the selected entity
        *@return the selected entity, NULL if no selection or on error
        */
        virtual PSS_UserEntity* GetSelectedEntity();

        /**
        * Gets the selected group
        *@return the selected group, NULL if no selection or on error
        */
        virtual PSS_UserGroupEntity* GetSelectedGroup();

        /**
        * Gets the selected role
        *@return the selected role, NULL if no selection or on error
        */
        virtual PSS_UserRoleEntity* GetSelectedRole();

        /**
        * Gets the selected owner group
        *@return the selected owner group, NULL if no selection or on error
        */
        virtual PSS_UserGroupEntity* GetSelectedOwnerGroup();

        /**
        * Checks if the root is selected
        *@return true if the root is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Adds a group
        *@param pGroup - the group to add
        *@param pParentGroup - the parent group to add to, if NULL will be added to the root
        */
        virtual void AddGroup(PSS_UserGroupEntity* pGroup, PSS_UserGroupEntity* pParentGroup = NULL);

        /**
        * Removes a group
        *@param pGroup - the group to remove
        */
        virtual void RemoveGroup(PSS_UserGroupEntity* pGroup);

        /**
        * Modifies a group
        *@param pGroup - the group to modify
        */
        virtual void ModifyGroup(PSS_UserGroupEntity* pGroup);

        /**
        * Adds a role
        *@param pGroup - the role to add
        *@param pParentGroup - the parent role to add to, if NULL will be added to the root
        */
        virtual void AddRole(PSS_UserRoleEntity* pRole, PSS_UserGroupEntity* pParentGroup);

        /**
        * Removes a role
        *@param pRole - the role to remove
        */
        virtual void RemoveRole(PSS_UserRoleEntity* pRole);

        /**
        * Modifies a role
        *@param pRole - the role to modify
        */
        virtual void ModifyRole(PSS_UserRoleEntity* pRole);

        /**
        * Called when a group should be added
        */
        virtual void OnUgpNewGroup();

        /**
        * Called when a group should be deleted
        */
        virtual void OnUgpDeleteGroup();

        /**
        * Called when a group should be renamed
        */
        virtual void OnUgpRenameGroup();

        /**
        * Called when a role should be added
        */
        virtual void OnUgpAddRole();

        /**
        * Called when a role should be deleted
        */
        virtual void OnUgpDeleteRole();

        /**
        * Called when a role should be renamed
        */
        virtual void OnUgpRenameRole();

        /**
        * Called when an item should be moved
        */
        virtual void OnUgpMove();

        /**
        * Called when the properties should be shown
        */
        virtual void OnUgpProperties();

        /**
        * Checks if a group may be added
        *@return true if a group may be added, otherwise false
        */
        virtual bool CanUgpNewGroup();

        /**
        * Checks if a group may be deleted
        *@return true if a group may be deleted, otherwise false
        */
        virtual bool CanUgpDeleteGroup();

        /**
        * Checks if a group may be renamed
        *@return true if a group may be renamed, otherwise false
        */
        virtual bool CanUgpRenameGroup();

        /**
        * Checks if a role may be added
        *@return true if a role may be added, otherwise false
        */
        virtual bool CanUgpAddRole();

        /**
        * Checks if a role may be deleted
        *@return true if a role may be deleted, otherwise false
        */
        virtual bool CanUgpDeleteRole();

        /**
        * Checks if a role may be renamed
        *@return true if a role may be renamed, otherwise false
        */
        virtual bool CanUgpRenameRole();

        /**
        * Checks if an item may be moved
        *@return true if an item may be moved, otherwise false
        */
        virtual bool CanUgpMove();

        /**
        * Checks if the properties should be shown
        *@return true if the properties should be shown, otherwise false
        */
        virtual bool CanUgpProperties();

        /**
        * Called when the branch should be expanded
        */
        virtual void OnExpandBranch();

        /**
        * Called when the branch should be collapsed
        */
        virtual void OnCollapseBranch();

        /**
        * Called when the controller receives a message
        *@param pSubject - the subject which sent the message
        *@param pMsg - the received message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Checks if the controller contains a context menu
        *@param pWnd - the owner window to check
        *@param point - the mouse cursor position
        *@return the context menu identifier, -1 if no context menu
        */
        virtual int HasContextMenu(CWnd* pWnd, const CPoint& point);

        /**
        * Shows a context menu
        *@param pWnd - the owner window
        *@param point - the mouse cursor point
        *@return the context menu identifier, -1 if no context menu
        */
        virtual void ShowContextMenu(CWnd* pWnd, const CPoint& point);

    protected:
        /**
        * Tree data
        */
        class ITreeData : public CObject
        {
            public:
                /**
                * Data type
                */
                enum class IEDataType
                {
                    IE_DT_Group,
                    IE_DT_Role,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                PSS_UserGroupEntity* m_pGroup;
                PSS_UserRoleEntity*  m_pRole;
                IEDataType           m_Type;
                CString              m_Str;

                ITreeData();

                /**
                * Constructor
                *@param pGroup - the user group
                */
                ITreeData(PSS_UserGroupEntity* pGroup);

                /**
                * Constructor
                *@param pRole - the user role
                */
                ITreeData(PSS_UserRoleEntity* pRole);

                /**
                * Constructor
                *@param str - the string
                */
                ITreeData(const CString& Str);

                virtual ~ITreeData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_UserGroupTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_UserGroupTreeCtrl)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the no drop image index
        *@return the no drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /**
        * Gets the drag object
        *@param dragItem - the drag item handle
        *@return the drag object, NULL if not found or on error
        */
        virtual CObject* GetDragObject(HTREEITEM DragItem);

    private:
        typedef sfl::CCArray_T <ITreeData*, ITreeData*> ITreeDataSet;
        typedef sfl::Iterator_T<ITreeData*>             ITreeDataIterator;

        PSS_UserGroupEntity* m_pUserGroupRoot;
        HTREEITEM            m_hUserGroupRoot;
        ITreeDataSet         m_DataSet;
        CString              m_RootName;
        CMenu                m_SubMenu;
        bool                 m_HasBeenInitialized;

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Loads the tree
        */
        void LoadTree();

        /**
        * Destroys the tree
        */
        void DestroyTree();

        /**
        * Empties the dataset
        */
        void EmptyDataSet();

        /**
        * Processes the group
        *@param pGroup - the group
        *@param hParentTreeItem - the parent tree item handle
        */
        void ProcessGroup(PSS_UserGroupEntity* pGroup, HTREEITEM hParentTreeItem);

        /**
        * Processes the role
        *@param pRole - the role
        *@param hParentTreeItem - the parent tree item handle
        */
        void ProcessRole(PSS_UserRoleEntity* pRole, HTREEITEM hParentTreeItem);

        /**
        * Adds the type item
        *@param name - the item name
        *@param iconIndex - the icon index
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds the group item
        *@param pGroup - the group item
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddGroupItem(PSS_UserGroupEntity* pGroup, HTREEITEM hParentTreeItem);

        /**
        * Adds the role item
        *@param pRole - the role item
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddRoleItem(PSS_UserRoleEntity* pRole, HTREEITEM hParentTreeItem);

        /**
        * Modifies the group item
        *@param pGroup - the group to modify
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ModifyGroupItem(PSS_UserGroupEntity* pGroup, HTREEITEM hItem);

        /**
        * Modifies the role item
        *@param pRole - the role to modify
        *@param hItem - the item handle
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ModifyRoleItem(PSS_UserRoleEntity* pRole, HTREEITEM hItem);

        /**
        * Gets the entity
        *@param hIten - the item handle to get
        *@return the entity, NULL if not found or on error
        */
        PSS_UserEntity* GetEntity(HTREEITEM hItem);

        /**
        * Gets the group entity
        *@param hIten - the item handle to get
        *@return the group entity, NULL if not found or on error
        */
        PSS_UserGroupEntity* GetGroup(HTREEITEM hItem);

        /**
        * Gets the role entity
        *@param hIten - the item handle to get
        *@return the role entity, NULL if not found or on error
        */
        PSS_UserRoleEntity* GetRole(HTREEITEM hItem);

        /**
        * Gets the owner group entity
        *@param hIten - the item handle to get
        *@return the owner group entity, NULL if not found or on error
        */
        PSS_UserGroupEntity* GetOwnerGroup(HTREEITEM hItem);

        /**
        * Finds an element from a dataset
        *@param pEntity - the entity to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_UserEntity* pEntity);

        /**
        * Finds an element from a dataset
        *@param pGroup - the group entity to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_UserGroupEntity* pGroup);

        /**
        * Finds an element from a dataset
        *@param pRole - the role entity to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_UserRoleEntity* pRole);

        /**
        * Finds an element from a dataset
        *@param str - the string to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(const CString& str);

        /**
        * Adds a data to a dataset
        *@param pGroup - the group to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_UserGroupEntity* pGroup);

        /**
        * Adds a data to a dataset
        *@param pRole - the role to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_UserRoleEntity* pRole);

        /**
        * Adds a data to a dataset
        *@param str - the string to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(const CString& str);
};

//---------------------------------------------------------------------------
// PSS_UserGroupTreeCtrl
//---------------------------------------------------------------------------
int PSS_UserGroupTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}
//---------------------------------------------------------------------------

#endif
