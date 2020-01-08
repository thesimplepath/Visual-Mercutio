/****************************************************************************
 * ==> PSS_PrestationsTreeCtrl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations tree controller                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PrestationsTreeCtrlH
#define PSS_PrestationsTreeCtrlH

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
#ifndef PSS_PrestationsEntity
    #define PSS_PrestationsEntity ZBPrestationsEntity
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif

// forward class declaration
class PSS_PrestationsEntity;
class PSS_LogicalPrestationsEntity;

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
* Prestations tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PrestationsTreeCtrl : public PSS_TreeCtrl,
                                              public PSS_Subject,
                                              public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param rootName - the root name
        *@param pLogicalPrestationRoot - the logical prestation root
        */
        PSS_PrestationsTreeCtrl(const CString& rootName = _T(""), PSS_LogicalPrestationsEntity* pLogicalPrestationRoot = NULL);

        virtual ~PSS_PrestationsTreeCtrl();

        /**
        * Initializes the controller
        *@param rootName - the root name
        *@param pLogicalPrestationRoot - the logical prestation root
        */
        virtual void Initialize(const CString& rootName, PSS_LogicalPrestationsEntity* pLogicalPrestationRoot);

        /**
        * Releases the controller
        */
        virtual void Release();

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Gets the selected prestation entity
        *@return the selected prestation entity, NULL if no selection or on error
        */
        virtual PSS_PrestationsEntity* GetSelectedPrestationEntity();

        /**
        * Gets the selected logical prestation
        *@return the selected logical prestation, NULL if no selection or on error
        */
        virtual PSS_LogicalPrestationsEntity* GetSelectedLogicalPrestation();

        /**
        * Gets the selected logical prestation owner
        *@return the selected logical prestation owner, NULL if no selection or on error
        */
        virtual PSS_LogicalPrestationsEntity* GetSelectedLogicalPrestationOwner();

        /**
        * Checks if the root is selected
        *@return true if the root is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Adds a logical prestation
        *@param pLogicalPrestation - the logical prestation to add
        *@param pParentLogicalPrestation - the parent logical prestation to add to, if NULL will be added to the root
        */
        virtual void AddPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation,
                                   PSS_LogicalPrestationsEntity* pParentLogicalPrestation = NULL);

        /**
        * Removes a logical prestation
        *@param pLogicalPrestation - the logical prestation to remove
        */
        virtual void RemovePrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation);

        /**
        * Modifies a logical prestation
        *@param pLogicalPrestation - the logical prestation to modify
        */
        virtual void ModifyPrestation(PSS_LogicalPrestationsEntity* pLogicalPrestation);

        /**
        * Called when a logical prestation is added
        */
        virtual void OnNewPrestation();

        /**
        * Called when a logical prestation is deleted
        */
        virtual void OnDeletePrestation();

        /**
        * Called when a logical prestation is renamed
        */
        virtual void OnRenamePrestation();

        /**
        * Called when a logical prestation is moved
        */
        virtual void OnMovePrestation();

        /**
        * Called when the properties of a logical prestation are shown
        */
        virtual void OnPrestationProperties();

        /**
        * Checks if a logical prestation may be added
        *@return true if a new logical prestation may be added, otherwise false
        */
        virtual bool CanNewPrestation();

        /**
        * Checks if a logical prestation may be deleted
        *@return true if a new logical prestation may be deleted, otherwise false
        */
        virtual bool CanDeletePrestation();

        /**
        * Checks if a logical prestation may be renamed
        *@return true if a new logical prestation may be renamed, otherwise false
        */
        virtual bool CanRenamePrestation();

        /**
        * Checks if the properties of a logical prestation may be shown
        *@return true if the properties of a logical prestation may be shown, otherwise false
        */
        virtual bool CanPrestationProperties();

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
                    IE_DT_Prestation,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                PSS_LogicalPrestationsEntity* m_pPrestation;
                IEDataType                    m_Type;
                CString                       m_Str;

                ITreeData();

                /**
                * Constructor
                *@param pPrestation - the logical prestation
                */
                ITreeData(PSS_LogicalPrestationsEntity* pPrestation);

                /**
                * Constructor
                *@param str - the string
                */
                ITreeData(const CString& str);

                virtual ~ITreeData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PrestationsTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PrestationsTreeCtrl)
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

        PSS_LogicalPrestationsEntity* m_pLogicalPrestationRoot;
        HTREEITEM                     m_hUserGroupRoot;
        ITreeDataSet                  m_DataSet;
        CMenu                         m_SubMenu;
        CString                       m_RootName;
        bool                          m_HasBeenInitialized;

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
        * Processes the logical prestation group
        *@param pLogicalPrestation - the logical prestation
        *@param hParentTreeItem - the parent tree item handle
        */
        void ProcessLogicalPrestationsGroup(PSS_LogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hParentTreeItem);

        /**
        * Adds the type item
        *@param name - the item name
        *@param iconIndex - the icon index
        *@param hParentTreeItem - the parent item handle
        *@return the newly added item handle, NULL on error
        */
        HTREEITEM AddTypeItem(const CString& name, int iconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds the logical prestation item
        *@param pLogicalPrestation - the logical prestation to add
        *@param hParentTreeItem - the parent item handle
        *@return the newly added logical prestation item handle, NULL on error
        */
        HTREEITEM AddLogicalPrestationItem(PSS_LogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hParentTreeItem);

        /**
        * Modifies the logical prestation item
        *@param pLogicalPrestation - the logical prestation to modify
        *@param hItem - the item handle
        *@return the newly added logical prestation item handle, NULL on error
        */
        BOOL ModifyLogicalPrestationItem(PSS_LogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hItem);

        /**
        * Gets the prestation entity
        *@param hIten - the item handle to get
        *@return the prestation entity, NULL if not found or on error
        */
        PSS_PrestationsEntity* GetPrestationEntity(HTREEITEM hItem);

        /**
        * Gets the logical prestation entity
        *@param hIten - the item handle to get
        *@return the logical prestation entity, NULL if not found or on error
        */
        PSS_LogicalPrestationsEntity* GetLogicalPrestation(HTREEITEM hItem);

        /**
        * Gets the prestation owner entity
        *@param hIten - the item handle to get
        *@return the prestation owner entity, NULL if not found or on error
        */
        PSS_LogicalPrestationsEntity* GetOwnerPrestation(HTREEITEM hItem);

        /**
        * Finds an element from a dataset
        *@param pLogicalPrestation - the logical prestation to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_LogicalPrestationsEntity* pLogicalPrestation);

        /**
        * Finds an element from a dataset
        *@param str - the string to find
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(const CString& str);

        /**
        * Adds a data to a dataset
        *@param pLogicalPrestation - the logical prestation to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_LogicalPrestationsEntity* pLogicalPrestation);

        /**
        * Adds a data to a dataset
        *@param str - the string to add
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(const CString& str);
};

//---------------------------------------------------------------------------
// PSS_PrestationsTreeCtrl
//---------------------------------------------------------------------------
int PSS_PrestationsTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}
//---------------------------------------------------------------------------

#endif
