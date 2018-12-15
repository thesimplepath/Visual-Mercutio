// ZDGridDoc.h : interface of the ZDGridDocument class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVGridDoc_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZVGridDoc_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZVGridView;
class ZCGridGroup;

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZCGridGroupSet | An array of ZCGridGroup pointers.
//@iex typedef CCArray_T<ZCGridGroup*,ZCGridGroup*> ZCGridGroupSet;
typedef CCArray_T<ZCGridGroup*, ZCGridGroup*> ZCGridGroupSet;

//@type ZCGridGroupIterator | An iterator for ZCGridGroupSet collections.
//@iex typedef Iterator_T<ZCGridGroup*> ZCGridGroupIterator;
typedef Iterator_T<ZCGridGroup*> ZCGridGroupIterator;

class AFX_EXT_CLASS ZDGridDocument : public CGXDocument
{
protected:

    GXDECLARE_DYNCREATE( ZDGridDocument )

    // Create from serialization only
    ZDGridDocument();

// Operations
public:

    CGXGridParam* GetGridParam()
    {
        return m_pParam;
    };

    bool SetNewGridParamPtr( CGXGridParam* ptr );

    // Create the grid param, the default is creating an empty grid param.
    virtual bool CreateGridParam()
    {
        return SetNewGridParamPtr( new CGXGridParam );
    }

    // Returns the grid param at specific index
    CGXGridParam* GetGridParam( size_t Index );

    // Returns the tab create info at the specific index
    CGXTabCreateInfo* GetTabCreateInfo( size_t Index );

    // Returns the document pointer at the specific index
    ZDGridDocument* GetDocumentAt( size_t Index );

    // Returns the tabwnd pointer at the specific index
    CGXTabWnd* GetTabWnd( size_t Index );

    // Returns the tab view pointer at the specific index
    ZVGridView* GetTabView( size_t Index );

    // Returns the tab grid core pointer at the specific index
    CGXGridCore* GetTabGridCore( size_t Index );

    // Returns the first document view
    ZVGridView* GetFirstView();

    // SetPathName needs to be changed in order to set 
    // the pathname to all documents contained in the workbook
    virtual void SetPathName( LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE );

    // Tab name get and set methods
    const CString GetTabName( size_t Index );
    void SetTabName( const CString Name, size_t Index );

    // Return the actual grid tab count
    size_t GetGridTabCount();

    bool DeleteGridTab( size_t Index = 0 );

    bool InsertNewGridTab()
    {
        return _InsertNewGridTabAt( GetGridTabCount() - 1 );
    };

    bool InsertNewGridTabAfter( size_t Index = 0 )
    {
        return _InsertNewGridTabAt( Index + 1 );
    };

    bool InsertNewGridTabBefore( size_t Index = 0 )
    {
        return _InsertNewGridTabAt( Index );
    };

    void RemoveAllGroupCtrl();

    void InsertGroupCtrl( ROWCOL        Row,
                          ROWCOL        Col,
                          int            CoveringCells,
                          bool            Horizontal,
                          bool            Collapsed,
                          const CString    Label            = _T( "" ),
                          const CString    ToolTipText        = _T( "" ) );

    ZCGridGroup* FindGroupCtrl( ROWCOL Row, ROWCOL Col );
    void InitializeGroupControls( ZVGridView* pView );

    virtual BOOL OnOpenDocument( LPCTSTR pszPathName );
    virtual BOOL OnSaveDocument( LPCTSTR pszPathName );

    virtual void DeleteContents();

    // Return TRUE if ok to continue
    virtual BOOL SaveModified();
    virtual BOOL CanCloseFrame( CFrameWnd* pFrame );

    // Called to update the frame title. Normally called 
    // when the document name has changed
    BOOL UpdateFrameTitle();

    virtual BOOL CanExitGridView( CView* pView );

    ROWCOL GetFrozenRow() const;
    void SetFrozenRow( ROWCOL value );

    ROWCOL GetFrozenCol() const;
    void SetFrozenCol( ROWCOL value );

    ROWCOL GetFrozenHeaderRow() const;
    void SetFrozenHeaderRow( ROWCOL value );

    ROWCOL GetFrozenHeaderCol() const;
    void SetFrozenHeaderCol( ROWCOL value );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDGridDocument)
    public:
    virtual BOOL OnNewDocument();
    virtual void WorkBookSerialize(CArchive& ar);
    //}}AFX_VIRTUAL

    void _BaseClassSetPathName( LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE );
    void _BaseClassSetTitle( LPCTSTR lpszTitle );

// Implementation
public:

    virtual ~ZDGridDocument();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
protected:

    //{{AFX_MSG(ZDGridDocument)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


    bool _InsertNewGridTabAt( size_t Insert = 0 );

private:

    CGXGridParam*    m_pParam;
    ZCGridGroupSet    m_GroupCtrlSet;

    ROWCOL            m_FrozenRow;
    ROWCOL            m_FrozenCol;
    ROWCOL            m_FrozenHeaderRow;
    ROWCOL            m_FrozenHeaderCol;
};

/////////////////////////////////////////////////////////////////////////////

inline ROWCOL ZDGridDocument::GetFrozenRow() const
{
    return m_FrozenRow;
}

inline void ZDGridDocument::SetFrozenRow( ROWCOL value )
{
    m_FrozenRow = value;
}

inline ROWCOL ZDGridDocument::GetFrozenCol() const
{
    return m_FrozenCol;
}

inline void ZDGridDocument::SetFrozenCol( ROWCOL value )
{
    m_FrozenCol = value;
}

inline ROWCOL ZDGridDocument::GetFrozenHeaderRow() const
{
    return m_FrozenHeaderRow;
}

inline void ZDGridDocument::SetFrozenHeaderRow( ROWCOL value )
{
    m_FrozenHeaderRow = value;
}

inline ROWCOL ZDGridDocument::GetFrozenHeaderCol() const
{
    return m_FrozenHeaderCol;
}

inline void ZDGridDocument::SetFrozenHeaderCol( ROWCOL value )
{
    m_FrozenHeaderCol = value;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVGridDoc_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
