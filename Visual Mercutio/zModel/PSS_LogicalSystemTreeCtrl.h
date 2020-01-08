/****************************************************************************
 * ==> PSS_LogicalSystemTreeCtrl -------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system tree controller                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalSystemTreeCtrlH
#define PSS_LogicalSystemTreeCtrlH

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
#ifndef PSS_SystemEntity
    #define PSS_SystemEntity ZBSystemEntity
#endif
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// forward class declaration
class PSS_SystemEntity;
class PSS_LogicalSystemEntity;

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
* Logical system tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalSystemTreeCtrl : public PSS_TreeCtrl,
                                                public PSS_Subject,
                                                public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param rootName - the root name
        *@param pLogicalSystemRoot - the logical system root
        */
        PSS_LogicalSystemTreeCtrl(const CString& rootName = _T(""), PSS_LogicalSystemEntity* pLogicalSystemRoot = NULL);

        virtual ~PSS_LogicalSystemTreeCtrl();

        /**
        * Initializes the controller
        *@param rootName - the root name
        *@param pLogicalSystemRoot - the logical system root
        */
        virtual void Initialize(const CString& rootName, PSS_LogicalSystemEntity* pLogicalSystemRoot);

        /**
        * Releases the controller
        */
        virtual void Release();

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Gets the selected system entity
        *@return the selected system entity, NULL if no selection or on error
        */
        virtual PSS_SystemEntity* GetSelectedSystemEntity();

        /**
        * Gets the selected logical system
        *@return the selected logical system, NULL if no selection or on error
        */
        virtual PSS_LogicalSystemEntity* GetSelectedLogicalSystem();

        /**
        * Gets the selected logical system owner
        *@return the selected logical system owner, NULL if no selection or on error
        */
        virtual PSS_LogicalSystemEntity* GetSelectedLogicalSystemOwner();

        /**
        * Checks if the root is selected
        *@return true if the root is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Adds a logical system
        *@param pLogicalSystem - the logical system to add
        *@param pParentLogicalSystem - the parent logical system to add to, if NULL will be added to the root
        */
        virtual void AddLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem, PSS_LogicalSystemEntity* pParentLogicalSystem = NULL);

        /**
        * Removes a logical system
        *@param pLogicalSystem - the logical system to remove
        */
        virtual void RemoveLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem);

        /**
        * Modifies a logical system
        *@param pLogicalSystem - the logical system to modify
        */
        virtual void ModifyLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem);

        /**
        * Called when a logical system is added
        */
        virtual void OnNewLogicalSystem();

        /**
        * Called when a logical system is deleted
        */
        virtual void OnDeleteLogicalSystem();

        /**
        * Called when a logical system is renamed
        */
        virtual void OnRenameLogicalSystem();

        /**
        * Called when a logical system is moved
        */
        virtual void OnMoveLogicalSystem();

        /**
        * Called when the properties of a logical system are shown
        */
        virtual void OnLogicalSystemProperties();

        /**
        * Checks if a logical system may be added
        *@return true if a new logical system may be added, otherwise false
        */
        virtual bool CanNewLogicalSystem();

        /**
        * Checks if a logical system may be deleted
        *@return true if a new logical system may be deleted, otherwise false
        */
        virtual bool CanDeleteLogicalSystem();

        /**
        * Checks if a logical system may be renamed
        *@return true if a new logical system may be renamed, otherwise false
        */
        virtual bool CanRenameLogicalSystem();

        /**
        * Checks if the properties of a logical system may be shown
        *@return true if the properties of a logical system may be shown, otherwise false
        */
        virtual bool CanLogicalSystemProperties();

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
                enum IEDataType
                {
                    IE_DT_LogicalSystem,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                PSS_LogicalSystemEntity* m_pLogicalSystem;
                IEDataType               m_Type;
                CString                  m_Str;

                ITreeData();

                /**
                * Constructor
                *@param pLogicalSystem - the logical system
                */
                ITreeData(PSS_LogicalSystemEntity* pLogicalSystem);

                /**
                * Constructor
                *@param str - the string
                */
                ITreeData(const CString& str);

                virtual ~ITreeData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_LogicalSystemTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_LogicalSystemTreeCtrl)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
        afx_msg void OnCollapseBranch();
        afx_msg void OnExpandBranch();
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
        virtual CObject* GetDragObject(HTREEITEM dragItem);

    private:
        typedef sfl::CCArray_T <ITreeData*, ITreeData*> ITreeDataSet;
        typedef sfl::Iterator_T<ITreeData*>             ITreeDataIterator;

        PSS_LogicalSystemEntity* m_pLogicalSystemRoot;
        HTREEITEM                m_hUserGroupRoot;
        ITreeDataSet             m_DataSet;
        CMenu                    m_SubMenu;
        CString                  m_RootName;
        bool                     m_HasBeenInitialized;

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
        * Processes the logical system group
        *@param pLogicalSystem - the logical system
        *@param hParentTreeItem - the parent tree item handle
        */
        void ProcessLogicalSystemGroup(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem);

        /**
        * Adds the type item
        *@param name - the item name
        *@param iconIndex - the icon index
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds the logical system item
        *@param pLogicalSystem - the logical system to add
        *@param hParentTreeItem - the parent item handle
        *@return the newly added logical system item handle, NULL on error
        */
        HTREEITEM AddLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem);

        /**
        * Modifies the logical system item
        *@param pLogicalSystem - the logical system to modify
        *@param hItem - the item handle
        *@return the newly added logical system item handle, NULL on error
        */
        BOOL ModifyLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hItem);

        /**
        * Gets the system entity
        *@param hIten - the item handle to get
        *@return the system entity, NULL if not found or on error
        */
        PSS_SystemEntity* GetSystemEntity(HTREEITEM hItem);

        /**
        * Gets the logical system entity
        *@param hIten - the item handle to get
        *@return the logical system entity, NULL if not found or on error
        */
        PSS_LogicalSystemEntity* GetLogicalSystem(HTREEITEM hItem);

        /**
        * Gets the system owner entity
        *@param hIten - the item handle to get
        *@return the system owner entity, NULL if not found or on error
        */
        PSS_LogicalSystemEntity* GetOwnerSystem(HTREEITEM hItem);

        /**
        * Finds an element from a dataset
        *@param pLogicalSystem - the logical system to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_LogicalSystemEntity* pLogicalSystem);

        /**
        * Finds an element from a dataset
        *@param str - the string to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(const CString& str);

        /**
        * Adds a data to a dataset
        *@param pLogicalSystem - the logical system to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_LogicalSystemEntity* pLogicalSystem);

        /**
        * Adds a data to a dataset
        *@param str - the string to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(const CString& str);
};

//---------------------------------------------------------------------------
// PSS_LogicalSystemTreeCtrl
//---------------------------------------------------------------------------
int PSS_LogicalSystemTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}
//---------------------------------------------------------------------------

#endif
