// ******************************************************************************************************************
// *                       Classes _ZInternalPrestationsTreeData et ZCPrestationsTreeCtrl                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 11 octobre 2005 - Ajout des classes _ZInternalPrestationsTreeData et ZCPrestationsTreeCtrl.        *
// ******************************************************************************************************************
// * Ces classes contiennent les données élémentaires de type prestation, ainsi que le gestionnaire pour ces        *
// * données.                                                                                                        *
// ******************************************************************************************************************

#if !defined(AFX_ZCPrestationsTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)
#define AFX_ZCPrestationsTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_

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
class ZBLogicalPrestationsEntity;
class ZBPrestationsEntity;

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
class _ZInternalPrestationsTreeData : public CObject
{
public:

    enum PrestationsTreeDataType
    {
        ptp_Prestation,
        ptp_String,
        ptp_Unknown
    };

    _ZInternalPrestationsTreeData();
    _ZInternalPrestationsTreeData( ZBLogicalPrestationsEntity* pPrestation );
    _ZInternalPrestationsTreeData( CString Str );
    ~_ZInternalPrestationsTreeData();

    // Data member
    PrestationsTreeDataType        m_dtp;
    ZBLogicalPrestationsEntity*    m_pPrestation;
    CString                        m_Str;
};

/////////////////////////////////////////////////////////////////////////////
// ZCPrestationsTreeCtrl window

class AFX_EXT_CLASS ZCPrestationsTreeCtrl : public ZITreeCtrl,
                                            public ZISubject,
                                            public ZIObserver
{
// Construction / Destruction
public:

    ZCPrestationsTreeCtrl( const CString                RootName                = _T( "" ),
                           ZBLogicalPrestationsEntity*    pLogicalPrestationRoot    = NULL );

    virtual ~ZCPrestationsTreeCtrl();

    //////////////////////////////////////////////////////////////////
    // Operations

    void Initialize( const CString RootName, ZBLogicalPrestationsEntity* pLogicalPrestationsRoot );

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    void Refresh();

    ZBPrestationsEntity* GetSelectedPrestationEntity();
    ZBLogicalPrestationsEntity* GetSelectedLogicalPrestation();
    ZBLogicalPrestationsEntity* GetSelectedLogicalPrestationOwner();
    bool IsRootSelected() const;

    void AddPrestation( ZBLogicalPrestationsEntity* pLogicalPrestation,
                        ZBLogicalPrestationsEntity* pParentLogicalPrestation = NULL );

    void RemovePrestation( ZBLogicalPrestationsEntity* pLogicalPrestation );
    void ModifyPrestation( ZBLogicalPrestationsEntity* pLogicalPrestation );

    virtual void OnNewPrestation();
    virtual void OnDeletePrestation();
    virtual void OnRenamePrestation();
    virtual void OnMovePrestation();
    virtual void OnPrestationProperties();

    virtual bool CanNewPrestation();
    virtual bool CanDeletePrestation();
    virtual bool CanRenamePrestation();
    virtual bool CanPrestationProperties();

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
    //{{AFX_VIRTUAL(ZCPrestationsTreeCtrl)
    virtual BOOL DestroyWindow();
//    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    //}}AFX_VIRTUAL

    // Generated message map functions
    //{{AFX_MSG(ZCPrestationsTreeCtrl)
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

    void ProcessLogicalPrestationsGroup( ZBLogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hParentTreeItem );

    HTREEITEM AddTypeItem( const CString Name, int IconIndex, HTREEITEM hParentTreeItem = NULL );
    HTREEITEM AddLogicalPrestationItem( ZBLogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hParentTreeItem );
    BOOL ModifyLogicalPrestationItem( ZBLogicalPrestationsEntity* pLogicalPrestation, HTREEITEM hItem );

    ZBPrestationsEntity*        _GetPrestationEntity( HTREEITEM hItem );
    ZBLogicalPrestationsEntity*    _GetLogicalPrestation( HTREEITEM hItem );
    ZBLogicalPrestationsEntity*    _GetOwnerPrestation( HTREEITEM hItem );

    _ZInternalPrestationsTreeData* FindElementFromDataSet( ZBPrestationsEntity* pEntity );
    _ZInternalPrestationsTreeData* FindElementFromDataSet( ZBLogicalPrestationsEntity* pLogicalPrestation );
    _ZInternalPrestationsTreeData* FindElementFromDataSet( CString Str );

    _ZInternalPrestationsTreeData* AddDataToSet( ZBLogicalPrestationsEntity* pLogicalPrestation );
    _ZInternalPrestationsTreeData* AddDataToSet( CString Str );

private:

    //@type ZBProcessGraphPageSet | An array of _ZInternalPrestationsTreeData pointers.
    //@iex typedef CCArray_T<_ZInternalPrestationsTreeData*,_ZInternalPrestationsTreeData*> _ZInternalPrestationsTreeDataSet;
    typedef sfl::CCArray_T<_ZInternalPrestationsTreeData*, _ZInternalPrestationsTreeData*> _ZInternalPrestationsTreeDataSet;

    //@type _ZInternalPrestationsTreeDataIterator | An iterator for _ZInternalPrestationsTreeDataSet collections.
    //@iex typedef Iterator_T<_ZInternalPrestationsTreeData*> _ZInternalPrestationsTreeDataIterator;
    typedef sfl::Iterator_T<_ZInternalPrestationsTreeData*> _ZInternalPrestationsTreeDataIterator;

    _ZInternalPrestationsTreeDataSet    m_DataSet;
    HTREEITEM                            m_hUserGroupRoot;
    CString                                m_RootName;
    ZBLogicalPrestationsEntity*            m_pLogicalPrestationRoot;
    CMenu                                m_SubMenu;

    bool                                m_HasBeenInitialized;
};

inline int ZCPrestationsTreeCtrl::GetIndexOfNoDropImage() const
{
    return 2;
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCPrestationsTreeCtrl_H__2F41F061_F558_4A24_BDE9_D472E36F653E__INCLUDED_)