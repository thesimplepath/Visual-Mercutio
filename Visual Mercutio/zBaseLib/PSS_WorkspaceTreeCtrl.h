/****************************************************************************
 * ==> PSS_WorkspaceTreeCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace tree controller                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceTreeCtrlH
#define PSS_WorkspaceTreeCtrlH

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
#include "PSS_Subject.h"
#include "PSS_Observer.h"
#include "PSS_TreeCtrl.h"

// class name mapping
#ifndef PSS_WorkspaceEnv
    #define PSS_WorkspaceEnv ZBWorkspaceEnv
#endif
#ifndef PSS_WorkspaceEntity
    #define PSS_WorkspaceEntity ZBWorkspaceEntity
#endif
#ifndef PSS_WorkspaceFileEntity
    #define PSS_WorkspaceFileEntity ZBWorkspaceFileEntity
#endif
#ifndef PSS_WorkspaceGroupEntity
    #define PSS_WorkspaceGroupEntity ZBWorkspaceGroupEntity
#endif

// forward class declaration
class PSS_WorkspaceEnv;
class PSS_WorkspaceEntity;
class PSS_WorkspaceFileEntity;
class PSS_WorkspaceGroupEntity;

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
* Workspace tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceTreeCtrl : public PSS_TreeCtrl,
                                            public PSS_Subject,
                                            public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param rootName - root name
        *@param pWorkspaceEnv - workspace environment
        */
        PSS_WorkspaceTreeCtrl(const CString& rootName = _T(""), PSS_WorkspaceEnv* pWorkspaceEnv = NULL);

        virtual ~PSS_WorkspaceTreeCtrl();

        /**
        * Initializes the class
        *@param rootName - root name
        *@param pWorkspaceEnv - workspace environment
        */
        virtual void Initialize(const CString& rootName, PSS_WorkspaceEnv* pWorkspaceEnv);

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Checks if controller has items
        *@return true if controller has items, otherwise false
        */
        virtual inline bool HasItems() const;

        /**
        * Gets the selected entity
        *@return the selected entity
        */
        virtual PSS_WorkspaceEntity* GetSelectedEntity();

        /**
        * Gets the selected group
        *@return the selected group
        */
        virtual PSS_WorkspaceGroupEntity* GetSelectedGroup();

        /**
        * Gets the selected file
        *@return the selected file
        */
        virtual PSS_WorkspaceFileEntity* GetSelectedFile();

        /**
        * Gets the selected owner group
        *@return the selected owner group
        */
        virtual PSS_WorkspaceGroupEntity* GetSelectedOwnerGroup();

        /**
        * Checks if the root object is selected
        *@return true if the root object is selected, otherwise false
        */
        virtual bool IsRootSelected() const;

        /**
        * Adds a group
        *@param pGroup - group to add
        *@param pParentGroup - parent group
        */
        virtual void AddGroup(PSS_WorkspaceGroupEntity* pGroup, PSS_WorkspaceGroupEntity* pParentGroup = NULL);

        /**
        * Removes a group
        *@param pGroup - group to remove
        */
        virtual void RemoveGroup(PSS_WorkspaceGroupEntity* pGroup);

        /**
        * Modifies a group
        *@param pGroup - group to modify
        */
        virtual void ModifyGroup(PSS_WorkspaceGroupEntity* pGroup);

        /**
        * Adds a file
        *@param pFile - file to add
        *@param pParentGroup - parent group
        */
        virtual void AddFile(PSS_WorkspaceFileEntity* pFile, PSS_WorkspaceGroupEntity* pParentGroup);

        /**
        * Removes a file
        *@param pFile - file to remove
        */
        virtual void RemoveFile(PSS_WorkspaceFileEntity* pFile);

        /**
        * Modifies a file
        *@param pFile - file to modify
        */
        virtual void ModifyFile(PSS_WorkspaceFileEntity* pFile);

        /**
        * Called when a new group is added in workspace
        */
        virtual void OnWksNewGroup();

        /**
        * Called when a group is deleted from workspace
        */
        virtual void OnWksDeleteGroup();

        /**
        * Called when a group is renamed in workspace
        */
        virtual void OnWksRenameGroup();

        /**
        * Called when a new file is added in workspace
        */
        virtual void OnWksAddFile();

        /**
        * Called when a file is deleted from workspace
        */
        virtual void OnWksDeleteFile();

        /**
        * Called when a file is opened from workspace
        */
        virtual void OnWksOpenFile();

        /**
        * Called when workspace properties are opened
        */
        virtual void OnWksProperties();

        /**
        * Called when a new file is added to project
        *@param fileName - file name
        */
        virtual void OnAddFileToProject(const CString& fileName);

        /**
        * Checks if a file may be added to project
        *@param fileName - file name
        *@return true if a file may be added to project, otherwise false
        */
        virtual bool CanAddCurrentFileToProject(const CString& fileName);

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Checks if the workspace has a context menu
        *@param pWnd - window
        *@param point - hit point
        *@return the context menu identifier
        */
        virtual int HasContextMenu(CWnd* pWnd, const CPoint& point);

        /**
        * Shows the context menu
        *@param pWnd - window
        *@param point - hit point
        *@return the context menu identifier
        */
        virtual void ShowContextMenu(CWnd* pWnd, const CPoint& point);

    protected:
        /**
        * Workspace tree data
        */
        class IData : public CObject
        {
            public:
                /**
                * Data type
                */
                enum IEType
                {
                    IE_DT_WorkspaceEnv,
                    IE_DT_Group,
                    IE_DT_File,
                    IE_DT_String,
                    IE_DT_Unknown
                };

                IEType                    m_Type;
                PSS_WorkspaceEnv*         m_pWorkspaceEnv;
                PSS_WorkspaceGroupEntity* m_pGroup;
                PSS_WorkspaceFileEntity*  m_pFile;
                CString                   m_Str;

                IData();

                /**
                * Constructor
                *@param pWorkspaceEnv - workspace environment
                */
                IData(PSS_WorkspaceEnv* pWorkspaceEnv);

                /**
                * Constructor
                *@param pGroup - workspace group entity
                */
                IData(PSS_WorkspaceGroupEntity* pGroup);

                /**
                * Constructor
                *@param pFile - workspace file entity
                */
                IData(PSS_WorkspaceFileEntity* pFile);

                /**
                * Constructor
                *@param str - string
                */
                IData(const CString& str);

                virtual ~IData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WorkspaceTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceTreeCtrl)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
        afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the no drop image index
        *@return the no drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

    private:
        typedef sfl::CCArray_T<IData*, IData*> IDataSet;
        typedef sfl::Iterator_T<IData*>        IDataIterator;

        IDataSet          m_DataSet;
        HTREEITEM         m_hRootWorkspaceEnv;
        PSS_WorkspaceEnv* m_pWorkspaceEnv;
        CMenu             m_SubMenu;
        CString           m_RootName;

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
        * Processes the workspace environment
        *@param pWorkspaceEnv - workspace environment
        *@param hParentTreeItem - parent tree item handle
        */
        void ProcessWorkspaceEnv(PSS_WorkspaceEnv* pWorkspaceEnv, HTREEITEM hParentTreeItem);

        /**
        * Processes the group
        *@param pGroup - group
        *@param hParentTreeItem - parent tree item handle
        */
        void ProcessGroup(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);

        /**
        * Processes the file
        *@param pFile - file
        *@param hParentTreeItem - parent tree item handle
        */
        void ProcessFile(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);

        /**
        * Modifies the entity
        *@param pEntity - entity
        */
        void ModifyEntity(PSS_WorkspaceEntity* pEntity);

        /**
        * Adds the type item
        *@param name - name
        *@param iconIndex - icon index
        *@param hParentTreeItem - parent tree item handle
        *@return the item handle
        */
        HTREEITEM AddTypeItem(const CString& name, int IconIndex, HTREEITEM hParentTreeItem = NULL);

        /**
        * Adds the group item
        *@param pGroup - group
        *@param hParentTreeItem - parent tree item handle
        *@return the item handle
        */
        HTREEITEM AddGroupItem(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);

        /**
        * Adds the file item
        *@param pFile - file
        *@param hParentTreeItem - parent tree item handle
        *@return the item handle
        */
        HTREEITEM AddFileItem(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);

        /**
        * Modifies the item
        *@param pEntity - entity
        *@param hItem - item handle
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ModifyItem(PSS_WorkspaceEntity* pEntity, HTREEITEM hItem);

        /**
        * Gets the entity
        *@param hItem - item handle
        *@return the entity, NULL on error
        */
        PSS_WorkspaceEntity* GetEntity(HTREEITEM hItem);

        /**
        * Gets the group
        *@param hItem - item handle
        *@return the group, NULL on error
        */
        PSS_WorkspaceGroupEntity* GetGroup(HTREEITEM hItem);

        /**
        * Gets the file
        *@param hItem - item handle
        *@return the file, NULL on error
        */
        PSS_WorkspaceFileEntity* GetFile(HTREEITEM hItem);

        /**
        * Gets the owner group
        *@param hItem - item handle
        *@return the owner group, NULL on error
        */
        PSS_WorkspaceGroupEntity* GetOwnerGroup(HTREEITEM hItem);

        /**
        * Gets the file best group
        *@param fileName - file name
        *@return the file best group, NULL if not found or on error
        */
        PSS_WorkspaceGroupEntity* GetFileBestGroup(const CString& fileName) const;

        /**
        * Gets the file entity
        *@param fileName - file name
        *@return the file entity, NULL if not found or on error
        */
        PSS_WorkspaceFileEntity* GetFileEntity(const CString& fileName) const;

        /**
        * Checks if file exists
        *@param fileName - file name
        *@return true if file exists, otherwise false
        */
        inline bool FileExist(const CString& fileName) const;

        /**
        * Empties the data set
        */
        void EmptyDataSet();

        /**
        * Finds an element in the data set
        *@param pEntity - entity
        *@return the element, NULL if not found or on error
        */
        IData* FindElementFromDataSet(PSS_WorkspaceEntity*      pEntity);
        IData* FindElementFromDataSet(PSS_WorkspaceEnv*         pEntity);
        IData* FindElementFromDataSet(PSS_WorkspaceGroupEntity* pEntity);
        IData* FindElementFromDataSet(PSS_WorkspaceFileEntity*  pEntity);

        /**
        * Finds an element from the data set
        *@param entity - entity name
        *@return the element, NULL if not found or on error
        */
        IData* FindElementFromDataSet(const CString& entity);

        /**
        * Adds a data to the set
        *@param pEntity - entity
        *@return the newly added data, NULL on error
        */
        IData* AddDataToSet(PSS_WorkspaceEnv*         pEntity);
        IData* AddDataToSet(PSS_WorkspaceGroupEntity* pEntity);
        IData* AddDataToSet(PSS_WorkspaceFileEntity*  pEntity);

        /**
        * Adds a data to the set
        *@param entity - entity name
        *@return the newly added data, NULL on error
        */
        IData* AddDataToSet(const CString& entity);

        /**
        * Deletes an element from the data set
        *@param pEntity - entity
        *@return true on success, otherwise false
        */
        bool DeleteElementFromDataSet(PSS_WorkspaceGroupEntity* pEntity);
        bool DeleteElementFromDataSet(PSS_WorkspaceFileEntity*  pEntity);

        /**
        * Deletes an element from the data set
        *@param entity  - entity name
        *@return true on success, otherwise false
        */
        bool DeleteElementFromDataSet(const CString& entity);
};

//---------------------------------------------------------------------------
// PSS_WorkspaceTreeCtrl
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::HasItems() const
{
    return (m_DataSet.GetSize() > 0);
}
//---------------------------------------------------------------------------
int PSS_WorkspaceTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceTreeCtrl::FileExist(const CString& fileName) const
{
    return GetFileEntity(fileName);
}
//---------------------------------------------------------------------------

#endif
