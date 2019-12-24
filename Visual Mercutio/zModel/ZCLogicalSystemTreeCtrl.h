#if !defined(AFX_ZCLogicalSystemTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCLogicalSystemTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

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

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeCtrl.h"

// old class name mapping
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// Forward class declaration
class PSS_LogicalSystemEntity;
class ZBSystemEntity;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Encapsulate information for the modeltree
class _ZInternalLogicalSystemTreeData : public CObject
{
public:

    enum LogicalSystemTreeDataType
    {
        lstp_LogicalSystem,
        lstp_String,
        lstp_Unknown
    };

    _ZInternalLogicalSystemTreeData();
    _ZInternalLogicalSystemTreeData(PSS_LogicalSystemEntity* pLogicalSystem);
    _ZInternalLogicalSystemTreeData(CString Str);
    ~_ZInternalLogicalSystemTreeData();

    // Data member
    LogicalSystemTreeDataType    m_dtp;
    PSS_LogicalSystemEntity*     m_pLogicalSystem;
    CString                        m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCLogicalSystemTreeCtrl window

class AFX_EXT_CLASS ZCLogicalSystemTreeCtrl : public PSS_TreeCtrl,
                                              public PSS_Subject,
                                              public PSS_Observer
{
    // Construction / Destruction
public:

    ZCLogicalSystemTreeCtrl(const CString RootName = _T(""), PSS_LogicalSystemEntity* pLogicalSystemRoot = NULL);
    virtual ~ZCLogicalSystemTreeCtrl();

    //////////////////////////////////////////////////////////////////
    // Operations

    void Initialize(const CString RootName, PSS_LogicalSystemEntity* pLogicalSystemRoot);

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    void Refresh();

    ZBSystemEntity* GetSelectedSystemEntity();
    PSS_LogicalSystemEntity* GetSelectedLogicalSystem();
    PSS_LogicalSystemEntity* GetSelectedLogicalSystemOwner();
    bool IsRootSelected() const;

    void AddLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem, PSS_LogicalSystemEntity* pParentLogicalSystem = NULL);
    void RemoveLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem);
    void ModifyLogicalSystem(PSS_LogicalSystemEntity* pLogicalSystem);

    virtual void OnNewLogicalSystem();
    virtual void OnDeleteLogicalSystem();
    virtual void OnRenameLogicalSystem();
    // JMR-MODIF - Le 27 février 2006 - Ajout de la fonction OnMoveLogicalSystem.
    virtual void OnMoveLogicalSystem();
    virtual void OnLogicalSystemProperties();

    virtual bool CanNewLogicalSystem();
    virtual bool CanDeleteLogicalSystem();
    virtual bool CanRenameLogicalSystem();
    virtual bool CanLogicalSystemProperties();

    ////////////////////////////////////////////////////////////////////
    // ZIObserver call back
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int HasContextMenu(CWnd* pWnd, CPoint point);
    virtual void DisplayContextMenu(CWnd* pWnd, CPoint point);

    // Overrides
protected:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCLogicalSystemTreeCtrl)
    virtual BOOL DestroyWindow();
    //    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(ZCLogicalSystemTreeCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
    afx_msg void OnCollapseBranch();
    afx_msg void OnExpandBranch();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual int GetIndexOfNoDropImage() const;
    virtual CObject* GetDragObject(HTREEITEM DragItem);

private:

    void CreateTree();
    void LoadTree();
    void DestroyTree();
    void EmptyDataSet();

    void ProcessLogicalSystemGroup(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem);

    HTREEITEM AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM AddLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hParentTreeItem);
    BOOL ModifyLogicalSystemItem(PSS_LogicalSystemEntity* pLogicalSystem, HTREEITEM hItem);

    ZBSystemEntity*            _GetSystemEntity(HTREEITEM hItem);
    PSS_LogicalSystemEntity*    _GetLogicalSystem(HTREEITEM hItem);
    PSS_LogicalSystemEntity*    _GetOwnerSystem(HTREEITEM hItem);

    _ZInternalLogicalSystemTreeData* FindElementFromDataSet(ZBSystemEntity* pEntity);
    _ZInternalLogicalSystemTreeData* FindElementFromDataSet(PSS_LogicalSystemEntity* pLogicalSystem);
    _ZInternalLogicalSystemTreeData* FindElementFromDataSet(CString Str);

    _ZInternalLogicalSystemTreeData* AddDataToSet(PSS_LogicalSystemEntity* pLogicalSystem);
    _ZInternalLogicalSystemTreeData* AddDataToSet(CString Str);

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalLogicalSystemTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalLogicalSystemTreeData*,_ZInternalLogicalSystemTreeData*> _ZInternalLogicalSystemTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalLogicalSystemTreeData*, _ZInternalLogicalSystemTreeData*> _ZInternalLogicalSystemTreeDataSet;

    //@type _ZInternalLogicalSystemTreeDataIterator | An iterator for _ZInternalLogicalSystemTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalLogicalSystemTreeData*> _ZInternalLogicalSystemTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalLogicalSystemTreeData*> _ZInternalLogicalSystemTreeDataIterator;

    _ZInternalLogicalSystemTreeDataSet    m_DataSet;
    HTREEITEM                            m_hUserGroupRoot;
    CString                                m_RootName;
    PSS_LogicalSystemEntity*                m_pLogicalSystemRoot;
    CMenu                                m_SubMenu;

    bool                                 m_HasBeenInitialized;
};

inline int ZCLogicalSystemTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}

#endif
