// ZCWorkspaceTreeCtrl.h : header file

#if !defined(AFX_ZCWORKSPACETREECTRL_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCWORKSPACETREECTRL_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Subject.h"
#include "PSS_Observer.h"
#include "ZITreeCtl.h"

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
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 16 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Encapsulate information for the modeltree
class _ZInternalWksTreeData : public CObject
{
public:

    enum WksTreeDataType
    {
        wktp_WorkspaceEnv,
        wktp_Group,
        wktp_File,
        wktp_String,
        wktp_Unknown
    };

    _ZInternalWksTreeData();
    _ZInternalWksTreeData(PSS_WorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData(PSS_WorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData(PSS_WorkspaceFileEntity* pFile);
    _ZInternalWksTreeData(CString Str);
    ~_ZInternalWksTreeData();

    // Data member
    WksTreeDataType           m_dtp;
    PSS_WorkspaceEnv*         m_pWorkspaceEnv;
    PSS_WorkspaceGroupEntity* m_pGroup;
    PSS_WorkspaceFileEntity*  m_pFile;
    CString                   m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCWorkspaceTreeCtrl window

class AFX_EXT_CLASS ZCWorkspaceTreeCtrl : public ZITreeCtrl,
                                          public PSS_Subject,
                                          public PSS_Observer
{
    // Construction / destruction
public:

    ZCWorkspaceTreeCtrl(const CString RootName = _T(""), PSS_WorkspaceEnv* pWorkspaceEnv = NULL);
    virtual ~ZCWorkspaceTreeCtrl();

    // Operations
public:

    void Initialize(const CString RootName, PSS_WorkspaceEnv* pWorkspaceEnv);
    void Refresh();

    bool HasItems() const
    {
        return (m_DataSet.GetSize() > 0) ? true : false;
    };

    PSS_WorkspaceEntity* GetSelectedEntity();
    PSS_WorkspaceGroupEntity* GetSelectedGroup();
    PSS_WorkspaceFileEntity* GetSelectedFile();
    PSS_WorkspaceGroupEntity* GetSelectedOwnerGroup();
    bool IsRootSelected() const;

    void AddGroup(PSS_WorkspaceGroupEntity* pGroup, PSS_WorkspaceGroupEntity* pParentGroup = NULL);
    void RemoveGroup(PSS_WorkspaceGroupEntity* pGroup);
    void ModifyGroup(PSS_WorkspaceGroupEntity* pGroup);
    void AddFile(PSS_WorkspaceFileEntity* pFile, PSS_WorkspaceGroupEntity* pParentGroup);
    void RemoveFile(PSS_WorkspaceFileEntity* pFile);
    void ModifyFile(PSS_WorkspaceFileEntity* pFile);

    virtual void OnWksNewGroup();
    virtual void OnWksDeleteGroup();
    virtual void OnWksRenameGroup();
    virtual void OnWksAddFile();
    virtual void OnWksDeleteFile();
    virtual void OnWksOpenFile();
    virtual void OnWksProperties();
    virtual void OnAddFileToProject(const CString Filename);
    virtual bool CanAddCurrentFileToProject(const CString Filename);

    ////////////////////////////////////////////////////////////////////
    // ZIObserver call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int HasContextMenu(CWnd* pWnd, CPoint point);
    virtual void DisplayContextMenu(CWnd* pWnd, CPoint point);

protected:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCWorkspaceTreeCtrl)
    virtual BOOL DestroyWindow();
    //    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
        //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ZCWorkspaceTreeCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    //    afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam);
    afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:

    virtual int GetIndexOfNoDropImage() const;

private:

    void CreateTree();
    void LoadTree();
    void DestroyTree();

private:

    void ProcessWorkspaceEnv(PSS_WorkspaceEnv* pWorkspaceEnv, HTREEITEM hParentTreeItem);
    void ProcessGroup(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);
    void ProcessFile(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);
    void ModifyEntity(PSS_WorkspaceEntity* pEntity);

    HTREEITEM AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM AddGroupItem(PSS_WorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);
    HTREEITEM AddFileItem(PSS_WorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);
    BOOL ModifyItem(PSS_WorkspaceEntity* pEntity, HTREEITEM hItem);

    PSS_WorkspaceEntity* _GetEntity(HTREEITEM hItem);
    PSS_WorkspaceGroupEntity* _GetGroup(HTREEITEM hItem);
    PSS_WorkspaceFileEntity* _GetFile(HTREEITEM hItem);
    PSS_WorkspaceGroupEntity* _GetOwnerGroup(HTREEITEM hItem);

    PSS_WorkspaceGroupEntity* GetFileBestGroup(const CString Filename) const;
    PSS_WorkspaceFileEntity* GetFileEntity(const CString Filename) const;

    bool FileExist(const CString Filename) const
    {
        return (GetFileEntity(Filename)) ? true : false;
    }

    void EmptyDataSet();

    _ZInternalWksTreeData* FindElementFromDataSet(PSS_WorkspaceEntity* pEntity);
    _ZInternalWksTreeData* FindElementFromDataSet(PSS_WorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData* FindElementFromDataSet(PSS_WorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData* FindElementFromDataSet(PSS_WorkspaceFileEntity* pFile);
    _ZInternalWksTreeData* FindElementFromDataSet(CString Str);

    _ZInternalWksTreeData* AddDataToSet(PSS_WorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData* AddDataToSet(PSS_WorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData* AddDataToSet(PSS_WorkspaceFileEntity* pFile);
    _ZInternalWksTreeData* AddDataToSet(CString Str);

    bool DeleteElementFromDataSet(PSS_WorkspaceGroupEntity* pGroup);
    bool DeleteElementFromDataSet(PSS_WorkspaceFileEntity* pFile);
    bool DeleteElementFromDataSet(CString Str);

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalWksTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalWksTreeData*,_ZInternalWksTreeData*> _ZInternalWksTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalWksTreeData*, _ZInternalWksTreeData*> _ZInternalWksTreeDataSet;

    //@type _ZInternalWksTreeDataIterator | An iterator for _ZInternalWksTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalWksTreeData*> _ZInternalWksTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalWksTreeData*> _ZInternalWksTreeDataIterator;

    _ZInternalWksTreeDataSet    m_DataSet;

private:

    HTREEITEM                    m_hRootWorkspaceEnv;
    CString                        m_RootName;
    PSS_WorkspaceEnv*                m_pWorkspaceEnv;
    CMenu                        m_SubMenu;
};

inline int ZCWorkspaceTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}

#endif
