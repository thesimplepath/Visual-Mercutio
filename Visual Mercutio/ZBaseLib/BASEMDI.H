// BaseMDI.h : header file
//

#ifndef BaseMDI_h
#define BaseMDI_h 1


#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "Splitter.h"

#include "BaseTMDI.h"

#include "ZIHtmlView.h"

const    int    iSizeZoomCombo = 70;
const    int    iSizeFileListCombo = 170;
const    int    iSizeSchemaCombo = 120;
const    int    iSizeStyleCombo = 120;

const    UINT    MAIN_ROW = 0;

const    int    PROC_CONTEXT = 0;
const    int    HTML_CONTEXT = 1;
const    int    FORM_CONTEXT = 2;


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZIBaseMDIPage frame

class AFX_EXT_CLASS ZIBaseMDIPage : public ZIBaseTitleMDIPage
{
    DECLARE_DYNCREATE(ZIBaseMDIPage)
protected:
    ZIBaseMDIPage();            // protected constructor used by dynamic creation

    int CreateZoom();
    int CreateSchema();
    int    CreateFileList();

// Operations
public:
    void    AddSchema( const CString& sValue );
    void    RemoveAllSchema();

    BOOL    IsHtmlViewVisible() const { return m_bIsHtmlViewVisible; };
    void    SetHtmlViewVisible( BOOL bValue = TRUE ) { m_bIsHtmlViewVisible = bValue; };
    virtual void    ViewHtmlView( BOOL bShow = TRUE ){};

    BOOL    MustShowOnlyHtmlView() const { return m_ShowOnlyHtmlView; };
    void    SetShowOnlyHtmlView( BOOL value ) { m_ShowOnlyHtmlView = value; };

protected:
    virtual BOOL    ChangeContext( size_t Context ) { return FALSE; };

    virtual CView*    SwitchBottomView( CView* pView );
    virtual CView*    SwitchTopView( CView* pView );
    virtual CView*    GetBottomView();
    virtual CView*    GetTopView();

protected:  // control bar embedded members
    size_t    m_CurrentContext;

    ZIHtmlView*        m_pHtmlView;

    int                INDEX_DROPLIST;
    int             INDEX_DROPLIST_STYLE;
    int                INDEX_DROPLIST_SCHEMA;
    int             INDEX_DROPLIST_FILE;
    int                m_BaseOffset;

    CCJToolBar        m_wndToolBar;

    CCJFlatComboBox    m_cbxPercentage;
    CCJFlatComboBox    m_cbxFileList;
    CCJFlatComboBox    m_cbxSchema;

    ZISplitter        m_wndSplitter;

    // Used to save the window state before a full screen operation
    BOOL m_IsZoomed;
    BOOL m_IsIconic;

// Operations
private:    

private:
    BOOL    m_HasBeenMaximized;
       BOOL    m_bIsHtmlViewVisible;
    BOOL    m_ShowOnlyHtmlView;
    
// Implementation
protected:
    virtual ~ZIBaseMDIPage();

    // Generated message map functions
    //{{AFX_MSG(ZIBaseMDIPage)
    afx_msg void OnViewFullScreen();
    afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
    afx_msg void OnZoomChange();
    afx_msg void OnSchemaChange();
    afx_msg void OnFileChange();
    afx_msg LONG OnFileListChanged(UINT message, LONG lParam);
    afx_msg LONG OnSetDefaultFile(UINT message, LONG wParam);
    afx_msg LONG OnSetDefaultFileOpen(WPARAM wParam, LPARAM lParam);
    afx_msg LONG OnSetDefaultSchema(UINT message, LONG wParam);
    afx_msg LONG OnSchemaHasChanged(UINT message, LONG wParam);
    afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
    afx_msg void OnClose();
    afx_msg LONG OnNavigateURL(WPARAM wParam, LPARAM lParam);
    afx_msg LONG OnHideHtmlView(WPARAM wParam, LPARAM lParam);
    afx_msg LONG OnShowHtmlView(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // BaseMDI_h
