// ******************************************************************************************************************
// *                           Classes _ZInternalRulesTreeData et ZCRulesTreeCtrl                                    *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout des classes _ZInternalRulesTreeData et ZCRulesTreeCtrl.                *
// ******************************************************************************************************************
// * Ces classes contiennent les données élémentaires de type règles, ainsi que le gestionnaire pour ces données.    *
// ******************************************************************************************************************

#if !defined(AFX_ZCRulesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCRulesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

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

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\ZITreeCtl.h"

// Forward class declaration
class ZBLogicalRulesEntity;
class ZBRulesEntity;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// Encapsulate information for the modeltree
class _ZInternalRulesTreeData : public CObject
{
public:

    enum RulesTreeDataType
    {
        ptp_Rule,
        ptp_String,
        ptp_Unknown
    };

    _ZInternalRulesTreeData();
    _ZInternalRulesTreeData( ZBLogicalRulesEntity* pRule );
    _ZInternalRulesTreeData( CString Str );
    ~_ZInternalRulesTreeData();

    // Data member
    RulesTreeDataType        m_dtp;
    ZBLogicalRulesEntity*    m_pRule;
    CString                    m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCRulesTreeCtrl window

class AFX_EXT_CLASS ZCRulesTreeCtrl : public ZITreeCtrl,
                                      public ZISubject,
                                      public ZIObserver
{
// Construction / Destruction
public:

    ZCRulesTreeCtrl( const CString            RootName            = _T( "" ),
                     ZBLogicalRulesEntity*    pLogicalRuleRoot    = NULL );

    virtual ~ZCRulesTreeCtrl();

    //////////////////////////////////////////////////////////////////
    // Operations

    void Initialize( const CString RootName, ZBLogicalRulesEntity* pLogicalRulesRoot );

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    void Refresh();

    ZBRulesEntity* GetSelectedRuleEntity();
    ZBLogicalRulesEntity* GetSelectedLogicalRule();
    ZBLogicalRulesEntity* GetSelectedLogicalRuleOwner();
    bool IsRootSelected() const;

    void AddRule( ZBLogicalRulesEntity* pLogicalRule,
                  ZBLogicalRulesEntity* pParentLogicalRule = NULL );

    void RemoveRule( ZBLogicalRulesEntity* pLogicalRule );
    void ModifyRule( ZBLogicalRulesEntity* pLogicalRule );

    virtual void OnNewRule();
    virtual void OnDeleteRule();
    virtual void OnRenameRule();
    virtual void OnMoveRule();
    virtual void OnRuleProperties();

    virtual bool CanNewRule();
    virtual bool CanDeleteRule();
    virtual bool CanRenameRule();
    virtual bool CanRuleProperties();

    ////////////////////////////////////////////////////////////////////
    // ZIObserver call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int HasContextMenu( CWnd* pWnd, CPoint point );
    virtual void DisplayContextMenu( CWnd* pWnd, CPoint point );

// Overrides
protected:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCRulesTreeCtrl)
    virtual BOOL DestroyWindow();
//    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    //}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(ZCRulesTreeCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
    afx_msg void OnCollapseBranch();
    afx_msg void OnExpandBranch();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual int GetIndexOfNoDropImage() const;
    virtual CObject* GetDragObject( HTREEITEM DragItem );

private:

    void CreateTree();
    void LoadTree();
    void DestroyTree();
    void EmptyDataSet();

    void ProcessLogicalRulesGroup( ZBLogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem );

    HTREEITEM AddTypeItem( const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL );
    HTREEITEM AddLogicalRuleItem( ZBLogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem );
    BOOL ModifyLogicalRuleItem( ZBLogicalRulesEntity* pLogicalRule, HTREEITEM hItem );

    ZBRulesEntity*            _GetRuleEntity( HTREEITEM hItem );
    ZBLogicalRulesEntity*    _GetLogicalRule( HTREEITEM hItem );
    ZBLogicalRulesEntity*    _GetOwnerRule( HTREEITEM hItem );

    _ZInternalRulesTreeData* FindElementFromDataSet( ZBRulesEntity* pEntity );
    _ZInternalRulesTreeData* FindElementFromDataSet( ZBLogicalRulesEntity* pLogicalRule );
    _ZInternalRulesTreeData* FindElementFromDataSet( CString Str );

    _ZInternalRulesTreeData* AddDataToSet( ZBLogicalRulesEntity* pLogicalRule );
    _ZInternalRulesTreeData* AddDataToSet( CString Str );

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalRulesTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalRulesTreeData*,_ZInternalRulesTreeData*> _ZInternalRulesTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalRulesTreeData*, _ZInternalRulesTreeData*> _ZInternalRulesTreeDataSet;

    //@type _ZInternalRulesTreeDataIterator | An iterator for _ZInternalRulesTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalRulesTreeData*> _ZInternalRulesTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalRulesTreeData*> _ZInternalRulesTreeDataIterator;

    _ZInternalRulesTreeDataSet    m_DataSet;
    HTREEITEM                    m_hUserGroupRoot;
    CString                        m_RootName;
    ZBLogicalRulesEntity*        m_pLogicalRuleRoot;
    CMenu                        m_SubMenu;

    bool                        m_HasBeenInitialized;
};

inline int ZCRulesTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCRulesTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)