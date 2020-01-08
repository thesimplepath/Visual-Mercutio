/****************************************************************************
 * ==> PSS_RulesTreeCtrl ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules tree controller                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RulesTreeCtrlH
#define PSS_RulesTreeCtrlH

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
#ifndef PSS_RulesEntity
    #define PSS_RulesEntity ZBRulesEntity
#endif
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class PSS_RulesEntity;
class PSS_LogicalRulesEntity;

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
* Rules tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RulesTreeCtrl : public PSS_TreeCtrl,
                                        public PSS_Subject,
                                        public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param rootName - the root name
        *@param pLogicalRuleRoot - the logical rule root
        */
        PSS_RulesTreeCtrl(const CString& rootName = _T(""), PSS_LogicalRulesEntity* pLogicalRuleRoot = NULL);

        virtual ~PSS_RulesTreeCtrl();

        /**
        * Initializes the controller
        *@param rootName - the root name
        *@param pLogicalRuleRoot - the logical rule root
        */
        virtual void Initialize(const CString& rootName, PSS_LogicalRulesEntity* pLogicalRuleRoot);

        /**
        * Releases the controller
        */
        virtual void Release();

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Gets the selected rule entity
        *@return the selected rule entity, NULL if no selection or on error
        */
        virtual PSS_RulesEntity* GetSelectedRuleEntity();

        /**
        * Gets the selected logical rule
        *@return the selected logical rule, NULL if no selection or on error
        */
        virtual PSS_LogicalRulesEntity* GetSelectedLogicalRule();

        /**
        * Gets the selected logical rule owner
        *@return the selected logical rule owner, NULL if no selection or on error
        */
        virtual PSS_LogicalRulesEntity* GetSelectedLogicalRuleOwner();

        /**
        * Checks if the root is selected
        *@return true if the root is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Adds a logical rule
        *@param pLogicalRule - the logical rule to add
        *@param pParentLogicalRule - the parent logical rule to add to, if NULL will be added to the root
        */
        virtual void AddRule(PSS_LogicalRulesEntity* pLogicalRule, PSS_LogicalRulesEntity* pParentLogicalRule = NULL);

        /**
        * Removes a logical rule
        *@param pLogicalRule - the logical rule to remove
        */
        virtual void RemoveRule(PSS_LogicalRulesEntity* pLogicalRule);

        /**
        * Modifies a logical rule
        *@param pLogicalRule - the logical rule to modify
        */
        virtual void ModifyRule(PSS_LogicalRulesEntity* pLogicalRule);

        /**
        * Called when a logical rule is added
        */
        virtual void OnNewRule();

        /**
        * Called when a logical rule is deleted
        */
        virtual void OnDeleteRule();

        /**
        * Called when a logical rule is renamed
        */
        virtual void OnRenameRule();

        /**
        * Called when a logical rule is moved
        */
        virtual void OnMoveRule();

        /**
        * Called when the properties of a logical rule are shown
        */
        virtual void OnRuleProperties();

        /**
        * Checks if a logical rule may be added
        *@return true if a new logical rule may be added, otherwise false
        */
        virtual bool CanNewRule();

        /**
        * Checks if a logical rule may be deleted
        *@return true if a new logical rule may be deleted, otherwise false
        */
        virtual bool CanDeleteRule();

        /**
        * Checks if a logical rule may be renamed
        *@return true if a new logical rule may be renamed, otherwise false
        */
        virtual bool CanRenameRule();

        /**
        * Checks if the properties of a logical rule may be shown
        *@return true if the properties of a logical rule may be shown, otherwise false
        */
        virtual bool CanRuleProperties();

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
                    IE_DT_Rule,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                PSS_LogicalRulesEntity* m_pRule;
                IEDataType              m_Type;
                CString                 m_Str;

                ITreeData();

                /**
                * Constructor
                *@param pRule - the logical rule
                */
                ITreeData(PSS_LogicalRulesEntity* pRule);

                /**
                * Constructor
                *@param str - the string
                */
                ITreeData(const CString& str);

                virtual ~ITreeData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RulesTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RulesTreeCtrl)
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
        virtual CObject* GetDragObject(HTREEITEM DragItem);

    private:
        typedef sfl::CCArray_T <ITreeData*, ITreeData*> ITreeDataSet;
        typedef sfl::Iterator_T<ITreeData*>             ITreeDataIterator;

        PSS_LogicalRulesEntity* m_pLogicalRuleRoot;
        HTREEITEM               m_hUserGroupRoot;
        ITreeDataSet            m_DataSet;
        CString                 m_RootName;
        CMenu                   m_SubMenu;
        bool                    m_HasBeenInitialized;

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
        * Processes the logical rule group
        *@param pLogicalRule - the logical rule
        *@param hParentTreeItem - the parent tree item handle
        */
        void ProcessLogicalRulesGroup(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem);

        /**
        * Adds the type item
        *@param name - the item name
        *@param iconIndex - the icon index
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds the logical rule item
        *@param pLogicalRule - the logical rule to add
        *@param hParentTreeItem - the parent item handle
        *@return the newly added logical rule item handle, NULL on error
        */
        HTREEITEM AddLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem);

        /**
        * Modifies the logical rule item
        *@param pLogicalRule - the logical rule to modify
        *@param hItem - the item handle
        *@return the newly added logical rule item handle, NULL on error
        */
        BOOL ModifyLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hItem);

        /**
        * Gets the rule entity
        *@param hIten - the item handle to get
        *@return the rule entity, NULL if not found or on error
        */
        PSS_RulesEntity* GetRuleEntity(HTREEITEM hItem);

        /**
        * Gets the logical rule entity
        *@param hIten - the item handle to get
        *@return the logical rule entity, NULL if not found or on error
        */
        PSS_LogicalRulesEntity* GetLogicalRule(HTREEITEM hItem);

        /**
        * Gets the rule owner entity
        *@param hIten - the item handle to get
        *@return the rule owner entity, NULL if not found or on error
        */
        PSS_LogicalRulesEntity* GetOwnerRule(HTREEITEM hItem);

        /**
        * Finds an element from a dataset
        *@param pLogicalRule - the logical rule to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_LogicalRulesEntity* pLogicalRule);

        /**
        * Finds an element from a dataset
        *@param str - the string to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(const CString& str);

        /**
        * Adds a data to a dataset
        *@param pLogicalRule - the logical rule to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_LogicalRulesEntity* pLogicalRule);

        /**
        * Adds a data to a dataset
        *@param str - the string to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(const CString& str);
};

//---------------------------------------------------------------------------
// PSS_RulesTreeCtrl
//---------------------------------------------------------------------------
int PSS_RulesTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}
//---------------------------------------------------------------------------

#endif
