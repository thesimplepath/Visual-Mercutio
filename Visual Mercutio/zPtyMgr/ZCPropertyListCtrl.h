// ZCPropertyListCtrl.h : header file

#if !defined(_ZCPropertyListCtrl_H__)
#define _ZCPropertyListCtrl_H__

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

#include "zProperty\ZIInPlaceEdit.h"
#include "zProperty\ZBPropertyItem.h"
#include "ZBPropertyManager.h"

// Forward declaration
class ZIProperties;

#ifdef _ZPTYMGREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCPropertyListCtrl

class AFX_EXT_CLASS ZCPropertyListCtrl : public CDragListBox, public ZISubject, public ZIObserver
{
    friend class ZBPropertyItemManager;

    DECLARE_DYNAMIC( ZCPropertyListCtrl )

    ZCPropertyListCtrl( const ZCPropertyListCtrl& d );
    ZCPropertyListCtrl& operator=( const ZCPropertyListCtrl& d );

public:

    ZCPropertyListCtrl( LPCTSTR pIniFile = NULL );

    // Initialization function
    void Initialize( ZIProperties* pProperties = NULL, LPCTSTR pIniFile = NULL );
    void Initialize( ZBPropertySet& PropSet, LPCTSTR pIniFile = NULL );
    void LoadStateFromIniFile( const CString IniFile );
    void Refresh( bool DeleteEditCtrl = true, bool ReloadControlData = false  );
    void Empty();

    void SetDisplayType( PropertyDisplayType tp )
    {
        if ( m_pPropertyItemManager )
        {
            m_pPropertyItemManager->SetDisplayType( tp );
        }
    };

    bool IsListInReadOnly() const
    {
        return m_ListInReadOnly;
    };

    void SetListInReadOnly( bool value = true )
    {
        m_ListInReadOnly = value;
    };

    // Observer call back
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    // Attributes
    ZBPropertyItemCategory* GetCategoryTab( int nIndex ) const
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->GetCategoryTab( nIndex );
        }

        return NULL;
    };

    // Operations
    ZBPropertyItemCategory* AddNewTab( LPCTSTR pStrTabName )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->AddNewTab( pStrTabName );
        }

        return NULL;
    };

    ZBProperty* GetCorrespondingProperty( ZBPropertyItem* pPropertyItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->GetCorrespondingProperty( pPropertyItem );
        }

        return NULL;
    };

    // Operations
    void CheckState();

    virtual void OnDataChanged( ZBPropertyItem* pPropertyItem, int nIndex, bool& Refresh )
    {
        if ( m_pPropertyItemManager )
        {
            m_pPropertyItemManager->OnDataChanged( pPropertyItem, this, nIndex, Refresh );
        }
    };
    
    virtual bool UpdateControlData( const ZIProperties* pData )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->UpdateControlData( pData );
        }

        return false;
    };

    virtual bool UpdatePropertyData( ZBPropertyItem* pPropertyItem = NULL ) const
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->UpdatePropertyData( pPropertyItem );
        }

        return false;
    };

    virtual bool CheckCurrentPropertyData( ZBPropertyItem* pPropertyItem, CString& ProposedValue )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->CheckCurrentPropertyData( pPropertyItem, ProposedValue );
        }

        // In this case return true, assuming all values entered are correct
        return true;
    };

    virtual bool ProcessExtendedCurrentPropertyData( ZBPropertyItem*    pPropertyItem,
                                                     CString&            ProposedValue,
                                                     bool&                Refresh )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->ProcessExtendedCurrentPropertyData( pPropertyItem,
                                                                               ProposedValue,
                                                                               Refresh );
        }

        // In this case return false, nothing has been processed, therefore nothing has changed
        return false;
    };

    virtual bool ProcessMenuCommandCurrentPropertyData( int                MenuCommand,
                                                        ZBPropertyItem*    pPropertyItem,
                                                        CString&        ProposedValue,
                                                        bool&            Refresh )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->ProcessMenuCommandCurrentPropertyData( MenuCommand,
                                                                                  pPropertyItem,
                                                                                  ProposedValue,
                                                                                  Refresh );
        }

        // In this case return true, assuming all values entered are correct
        return false;
    };

    /////////////////////////////////////////////////////////////////////////////
    // Property state management methods
    bool SavePropertyState( ZBPropertyItem* pPropertyItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->SavePropertyState( pPropertyItem );
        }

        // fail
        return false;
    };

    bool SetPropertyStateToProperty( ZBPropertyItem* pPropertyItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->SetPropertyStateToProperty( pPropertyItem );
        }

        // fail
        return false;
    };

    _ZBPropertyState* GetPropertyState( ZBPropertyItem* pPropertyItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->GetPropertyState( pPropertyItem );
        }

        // fail
        return NULL;
    };

    bool SavePropertyState( ZBPropertyItemCategory* pPropertyCategoryItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->SavePropertyState( pPropertyCategoryItem );
        }

        // fail
        return false;
    };

    bool SetPropertyStateToProperty( ZBPropertyItemCategory* pPropertyCategoryItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->SetPropertyStateToProperty( pPropertyCategoryItem );
        }

        // fail
        return false;
    };

    _ZBPropertyState* GetPropertyCategoryState( ZBPropertyItemCategory* pPropertyCategoryItem )
    {
        if ( m_pPropertyItemManager )
        {
            return m_pPropertyItemManager->GetPropertyCategoryState( pPropertyCategoryItem );
        }

        // fail
        return NULL;
    };

    // Attributes
    void SetPropertyItemManager( ZBPropertyItemManager* pPropertyItemManager );

    // Return the current property item element
    ZBPropertyItem* GetCurrentPropertyItem();
    ZBPropertyItem* GetPropertyItem( int nIndex );

    // Operations
    void InsertPropertyItem( ZBPropertyItem* pPropertyItem, int nIndex = 0 );
    void DeletePropertyItem( ZBPropertyItem* pPropertyItem );
    void DeletePropertyItem( int nIndex );
    void ResetContent( bool DeleteEditCtrl = true );
    void ShowInPlaceControl( bool bShow = true );
    void RedrawAll();

protected:

    // Call-back for drag&drop operation
    virtual BOOL BeginDrag( CPoint pt );
    virtual void Dropped( int nSrcIndex, CPoint pt );

    void DetachObserverForEditCtrl();
    void CreateInPlaceControl( int nItem, int nPreviousItem = -1 );
    void EditNextItem();
    void EditPreviousItem();

    void DoCollapse( ZBPropertyItemCategory* pPropertyItemTab, int nItem );
    void DoExpand( ZBPropertyItemCategory* pPropertyItemTab, int& nItem );

    void DoCollapseExpand( int nItem, ZBPropertyItem* pPropertyItem = NULL );

    void GetItemValueRect( CRect& rect );
    bool SetCurrentData();

    void NoInPlaceControl();

    bool IsListInPhase();
    bool LookupPropertyItem( char nStartChar );
    int FindPropertyItem( char nStartChar, int nFromIndex, int nCount );

    void RedrawItem( int nItem );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCPropertyListCtrl)

public:

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);

protected:

    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual ~ZCPropertyListCtrl();

// Generated message map functions
protected:

    //{{AFX_MSG(ZCPropertyListCtrl)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnSelChange();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg LONG OnKeyPressed(WPARAM wParam, LPARAM lParam);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

// Data
private:

    int                        m_nSelectedItem;
    ZIInPlaceEdit*            m_pWndInPlaceControl;
    CFont                    m_Font;
    CFont                    m_FontBold;

    ZBPropertyItemManager*    m_pPropertyItemManager;
    ZIProperties*            m_pCurrentProperties;

    CString                    m_IniFile;
    bool                    m_IniFileLoaded;

    int                        m_SplitterX;
    HCURSOR                    m_hcurSplitter;

    ZBPropertyItem*            m_pSrcDragPropertyItem;
    int                        m_SrcDragPropertyItemIndex;

    bool                    m_ListInReadOnly;
};

inline void ZCPropertyListCtrl::InsertPropertyItem( ZBPropertyItem* pPropertyItem, int nIndex )
{
    ASSERT( pPropertyItem != NULL );
    InsertString( nIndex, (LPCTSTR)pPropertyItem );
}

inline void ZCPropertyListCtrl::DeletePropertyItem( int nIndex )
{
    ASSERT( nIndex >= 0 );
    DeleteString( nIndex );
}

inline void ZCPropertyListCtrl::MeasureItem( LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/ )
{
}

inline int ZCPropertyListCtrl::CompareItem( LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/ )
{
    return 0;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(_ZCPropertyListCtrl_H__)
