#if !defined(AFX_ZCUserGroupTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCUserGroupTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\ZITreeCtl.h"

// Forward class declaration
class ZBWorkspaceEnv;
class ZBUserRoleEntity;
class ZBUserGroupEntity;
class ZBUserEntity;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

// Encapsulate information for the modeltree
class _ZInternalUserGroupTreeData : public CObject
{
public:

    enum UserGroupTreeDataType { wktp_Group,
                                 wktp_Role,
                                 wktp_String,
                                 wktp_Unknown };

    _ZInternalUserGroupTreeData();
    _ZInternalUserGroupTreeData( ZBUserGroupEntity* pGroup );
    _ZInternalUserGroupTreeData( ZBUserRoleEntity* pRole );
    _ZInternalUserGroupTreeData( CString Str );
    ~_ZInternalUserGroupTreeData();

    // Data member
    UserGroupTreeDataType    m_dtp;
    ZBUserGroupEntity*        m_pGroup;
    ZBUserRoleEntity*        m_pRole;
    CString                    m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCUserGroupTreeCtrl window

class AFX_EXT_CLASS ZCUserGroupTreeCtrl : public ZITreeCtrl,
                                          public PSS_Subject,
                                          public PSS_Observer
{
// Construction
public:

    ZCUserGroupTreeCtrl( const CString RootName = _T( "" ), ZBUserGroupEntity* pUserGroupRoot = NULL );
    virtual ~ZCUserGroupTreeCtrl();

// Operations
public:

    void                Initialize                ( const CString RootName, ZBUserGroupEntity* pUserGroupRoot );
    void                Release                    ();
    void                Refresh                    ();

    ZBUserEntity*        GetSelectedEntity        ();
    ZBUserGroupEntity*    GetSelectedGroup        ();
    ZBUserRoleEntity*    GetSelectedRole            ();
    ZBUserGroupEntity*    GetSelectedOwnerGroup    ();
    bool                IsRootSelected            () const;

    void                AddGroup                ( ZBUserGroupEntity* pGroup, ZBUserGroupEntity* pParentGroup = NULL );
    void                RemoveGroup                ( ZBUserGroupEntity* pGroup );
    void                ModifyGroup                ( ZBUserGroupEntity* pGroup );
    void                AddRole                    ( ZBUserRoleEntity* pRole, ZBUserGroupEntity* pParentGroup );
    void                RemoveRole                ( ZBUserRoleEntity* pRole );
    void                ModifyRole                ( ZBUserRoleEntity* pRole );

    virtual void        OnUgpNewGroup            ();
    virtual void        OnUgpDeleteGroup        ();
    virtual void        OnUgpRenameGroup        ();
    virtual void        OnUgpAddRole            ();
    virtual void        OnUgpDeleteRole            ();
    virtual void        OnUgpRenameRole            ();
    virtual void        OnUgpMove                ();
    virtual void        OnUgpProperties            ();

    virtual bool        CanUgpNewGroup            ();
    virtual bool        CanUgpDeleteGroup        ();
    virtual bool        CanUgpRenameGroup        ();
    virtual bool        CanUgpAddRole            ();
    virtual bool        CanUgpDeleteRole        ();
    virtual bool        CanUgpRenameRole        ();
    virtual bool        CanUgpMove                ();
    virtual bool        CanUgpProperties        ();

    ////////////////////////////////////////////////////////////////////
    // ZIObserver call back
    virtual void        OnUpdate                ( PSS_Subject* pSubject, PSS_ObserverMsg* pMsg );

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int            HasContextMenu            ( CWnd* pWnd, CPoint point );
    virtual void        DisplayContextMenu        ( CWnd* pWnd, CPoint point );

// Overrides
protected:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCUserGroupTreeCtrl)
    virtual BOOL DestroyWindow();
    //}}AFX_VIRTUAL


    // Generated message map functions
    //{{AFX_MSG(ZCUserGroupTreeCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
    afx_msg void OnCollapseBranch();
    afx_msg void OnExpandBranch();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:

    virtual int            GetIndexOfNoDropImage    () const;
    virtual CObject*    GetDragObject            ( HTREEITEM DragItem );

private:

    void                CreateTree                ();
    void                LoadTree                ();
    void                DestroyTree                ();
    void                EmptyDataSet            ();
    void                ProcessGroup            ( ZBUserGroupEntity* pGroup, HTREEITEM hParentTreeItem );
    void                ProcessRole                ( ZBUserRoleEntity* pRole, HTREEITEM hParentTreeItem );

    HTREEITEM            AddTypeItem                ( const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL );
    HTREEITEM            AddGroupItem            ( ZBUserGroupEntity* pGroup, HTREEITEM hParentTreeItem );
    HTREEITEM            AddRoleItem                ( ZBUserRoleEntity* pRole, HTREEITEM hParentTreeItem );

    BOOL                ModifyGroupItem            ( ZBUserGroupEntity* pGroup, HTREEITEM hItem );
    BOOL                ModifyRoleItem            ( ZBUserRoleEntity* pRole, HTREEITEM hItem );

    ZBUserEntity*        _GetEntity                ( HTREEITEM hItem );
    ZBUserGroupEntity*    _GetGroup                ( HTREEITEM hItem );
    ZBUserRoleEntity*    _GetRole                ( HTREEITEM hItem );
    ZBUserGroupEntity*    _GetOwnerGroup            ( HTREEITEM hItem );
      
    _ZInternalUserGroupTreeData* FindElementFromDataSet( ZBUserEntity* pEntity );
    _ZInternalUserGroupTreeData* FindElementFromDataSet( ZBUserGroupEntity* pGroup );
    _ZInternalUserGroupTreeData* FindElementFromDataSet( ZBUserRoleEntity* pRole );
    _ZInternalUserGroupTreeData* FindElementFromDataSet( CString Str );

    _ZInternalUserGroupTreeData* AddDataToSet( ZBUserGroupEntity* pGroup );
    _ZInternalUserGroupTreeData* AddDataToSet( ZBUserRoleEntity* pRole );
    _ZInternalUserGroupTreeData* AddDataToSet( CString Str );

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalUserGroupTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalUserGroupTreeData*,_ZInternalUserGroupTreeData*> _ZInternalUserGroupTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalUserGroupTreeData*, _ZInternalUserGroupTreeData*> _ZInternalUserGroupTreeDataSet;

    //@type _ZInternalUserGroupTreeDataIterator | An iterator for _ZInternalUserGroupTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalUserGroupTreeData*> _ZInternalUserGroupTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalUserGroupTreeData*> _ZInternalUserGroupTreeDataIterator;

private:

    _ZInternalUserGroupTreeDataSet    m_DataSet;

    HTREEITEM                        m_hUserGroupRoot;

    CString                            m_RootName;

    ZBUserGroupEntity*                m_pUserGroupRoot;

    CMenu                            m_SubMenu;

    bool                             m_HasBeenInitialized;
};

inline int ZCUserGroupTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCUserGroupTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)