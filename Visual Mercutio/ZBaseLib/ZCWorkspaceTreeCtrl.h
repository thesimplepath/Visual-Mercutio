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

#include "PSS_Subject.h"
#include "PSS_Observer.h"
#include "ZITreeCtl.h"

// class name mapping
#ifndef PSS_WorkspaceEntity
    #define PSS_WorkspaceEntity ZBWorkspaceEntity
#endif

// forward class declaration
class ZBWorkspaceEnv;
class ZBWorkspaceFileEntity;
class ZBWorkspaceGroupEntity;
class PSS_WorkspaceEntity;

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
    _ZInternalWksTreeData(ZBWorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData(ZBWorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData(ZBWorkspaceFileEntity* pFile);
    _ZInternalWksTreeData(CString Str);
    ~_ZInternalWksTreeData();

    // Data member
    WksTreeDataType            m_dtp;
    ZBWorkspaceEnv*            m_pWorkspaceEnv;
    ZBWorkspaceGroupEntity*    m_pGroup;
    ZBWorkspaceFileEntity*    m_pFile;
    CString                    m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCWorkspaceTreeCtrl window

class AFX_EXT_CLASS ZCWorkspaceTreeCtrl : public ZITreeCtrl,
                                          public PSS_Subject,
                                          public PSS_Observer
{
    // Construction / destruction
public:

    ZCWorkspaceTreeCtrl(const CString RootName = _T(""), ZBWorkspaceEnv* pWorkspaceEnv = NULL);
    virtual ~ZCWorkspaceTreeCtrl();

    // Operations
public:

    void Initialize(const CString RootName, ZBWorkspaceEnv* pWorkspaceEnv);
    void Refresh();

    bool HasItems() const
    {
        return (m_DataSet.GetSize() > 0) ? true : false;
    };

    PSS_WorkspaceEntity* GetSelectedEntity();
    ZBWorkspaceGroupEntity* GetSelectedGroup();
    ZBWorkspaceFileEntity* GetSelectedFile();
    ZBWorkspaceGroupEntity* GetSelectedOwnerGroup();
    bool IsRootSelected() const;

    void AddGroup(ZBWorkspaceGroupEntity* pGroup, ZBWorkspaceGroupEntity* pParentGroup = NULL);
    void RemoveGroup(ZBWorkspaceGroupEntity* pGroup);
    void ModifyGroup(ZBWorkspaceGroupEntity* pGroup);
    void AddFile(ZBWorkspaceFileEntity* pFile, ZBWorkspaceGroupEntity* pParentGroup);
    void RemoveFile(ZBWorkspaceFileEntity* pFile);
    void ModifyFile(ZBWorkspaceFileEntity* pFile);

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

    void ProcessWorkspaceEnv(ZBWorkspaceEnv* pWorkspaceEnv, HTREEITEM hParentTreeItem);
    void ProcessGroup(ZBWorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);
    void ProcessFile(ZBWorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);
    void ModifyEntity(PSS_WorkspaceEntity* pEntity);

    HTREEITEM AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM AddGroupItem(ZBWorkspaceGroupEntity* pGroup, HTREEITEM hParentTreeItem);
    HTREEITEM AddFileItem(ZBWorkspaceFileEntity* pFile, HTREEITEM hParentTreeItem);
    BOOL ModifyItem(PSS_WorkspaceEntity* pEntity, HTREEITEM hItem);

    PSS_WorkspaceEntity* _GetEntity(HTREEITEM hItem);
    ZBWorkspaceGroupEntity* _GetGroup(HTREEITEM hItem);
    ZBWorkspaceFileEntity* _GetFile(HTREEITEM hItem);
    ZBWorkspaceGroupEntity* _GetOwnerGroup(HTREEITEM hItem);

    ZBWorkspaceGroupEntity* GetFileBestGroup(const CString Filename) const;
    ZBWorkspaceFileEntity* GetFileEntity(const CString Filename) const;

    bool FileExist(const CString Filename) const
    {
        return (GetFileEntity(Filename)) ? true : false;
    }

    void EmptyDataSet();

    _ZInternalWksTreeData* FindElementFromDataSet(PSS_WorkspaceEntity* pEntity);
    _ZInternalWksTreeData* FindElementFromDataSet(ZBWorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData* FindElementFromDataSet(ZBWorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData* FindElementFromDataSet(ZBWorkspaceFileEntity* pFile);
    _ZInternalWksTreeData* FindElementFromDataSet(CString Str);

    _ZInternalWksTreeData* AddDataToSet(ZBWorkspaceEnv* pWorkspaceEnv);
    _ZInternalWksTreeData* AddDataToSet(ZBWorkspaceGroupEntity* pGroup);
    _ZInternalWksTreeData* AddDataToSet(ZBWorkspaceFileEntity* pFile);
    _ZInternalWksTreeData* AddDataToSet(CString Str);

    bool DeleteElementFromDataSet(ZBWorkspaceGroupEntity* pGroup);
    bool DeleteElementFromDataSet(ZBWorkspaceFileEntity* pFile);
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
    ZBWorkspaceEnv*                m_pWorkspaceEnv;
    CMenu                        m_SubMenu;
};

inline int ZCWorkspaceTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}

#endif
