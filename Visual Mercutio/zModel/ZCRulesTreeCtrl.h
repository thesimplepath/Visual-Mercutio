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

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeCtrl.h"

// class name mapping
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class PSS_LogicalRulesEntity;
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
    _ZInternalRulesTreeData(PSS_LogicalRulesEntity* pRule);
    _ZInternalRulesTreeData(CString Str);
    ~_ZInternalRulesTreeData();

    // Data member
    RulesTreeDataType        m_dtp;
    PSS_LogicalRulesEntity*    m_pRule;
    CString                    m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCRulesTreeCtrl window

class AFX_EXT_CLASS ZCRulesTreeCtrl : public PSS_TreeCtrl,
    public PSS_Subject,
    public PSS_Observer
{
    // Construction / Destruction
public:

    ZCRulesTreeCtrl(const CString            RootName = _T(""),
                    PSS_LogicalRulesEntity*    pLogicalRuleRoot = NULL);

    virtual ~ZCRulesTreeCtrl();

    //////////////////////////////////////////////////////////////////
    // Operations

    void Initialize(const CString RootName, PSS_LogicalRulesEntity* pLogicalRulesRoot);

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    void Refresh();

    ZBRulesEntity* GetSelectedRuleEntity();
    PSS_LogicalRulesEntity* GetSelectedLogicalRule();
    PSS_LogicalRulesEntity* GetSelectedLogicalRuleOwner();
    bool IsRootSelected() const;

    void AddRule(PSS_LogicalRulesEntity* pLogicalRule,
                 PSS_LogicalRulesEntity* pParentLogicalRule = NULL);

    void RemoveRule(PSS_LogicalRulesEntity* pLogicalRule);
    void ModifyRule(PSS_LogicalRulesEntity* pLogicalRule);

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
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int HasContextMenu(CWnd* pWnd, CPoint point);
    virtual void DisplayContextMenu(CWnd* pWnd, CPoint point);

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
    virtual CObject* GetDragObject(HTREEITEM DragItem);

private:

    void CreateTree();
    void LoadTree();
    void DestroyTree();
    void EmptyDataSet();

    void ProcessLogicalRulesGroup(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem);

    HTREEITEM AddTypeItem(const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL);
    HTREEITEM AddLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hParentTreeItem);
    BOOL ModifyLogicalRuleItem(PSS_LogicalRulesEntity* pLogicalRule, HTREEITEM hItem);

    ZBRulesEntity*            _GetRuleEntity(HTREEITEM hItem);
    PSS_LogicalRulesEntity*    _GetLogicalRule(HTREEITEM hItem);
    PSS_LogicalRulesEntity*    _GetOwnerRule(HTREEITEM hItem);

    _ZInternalRulesTreeData* FindElementFromDataSet(ZBRulesEntity* pEntity);
    _ZInternalRulesTreeData* FindElementFromDataSet(PSS_LogicalRulesEntity* pLogicalRule);
    _ZInternalRulesTreeData* FindElementFromDataSet(CString Str);

    _ZInternalRulesTreeData* AddDataToSet(PSS_LogicalRulesEntity* pLogicalRule);
    _ZInternalRulesTreeData* AddDataToSet(CString Str);

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
    PSS_LogicalRulesEntity*        m_pLogicalRuleRoot;
    CMenu                        m_SubMenu;

    bool                        m_HasBeenInitialized;
};

inline int ZCRulesTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}

#endif
