/****************************************************************************
 * ==> PSS_FormFilePreviewDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a form file preview dialog                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FormFilePreviewDialogH
#define PSS_FormFilePreviewDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ViewRead.h"
#include "zBaseLib\ZDDoc.h"
#include "zBaseLib\DocTmplEx.h"

// resources
#include "zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIButtonToolBarFormFilePreview window

class ZIButtonToolBarFormFilePreview : public CStatic
{
public:
// Construction
public:
    ZIButtonToolBarFormFilePreview();
    void SetParent(CWnd* pParent);

// Attributes
private:
    CCJFlatButton    m_NextPageButton;
    CCJFlatButton    m_PreviousPageButton;
    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_ZoomOutButton;
    CCJFlatButton    m_ZoomInButton;
    CCJFlatButton    m_NextFileButton;
    CCJFlatButton    m_PreviousFileButton;
    CCJFlatButton    m_CloseFileButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;
    CWnd*            m_pParent;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIButtonToolBarFormFilePreview)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZIButtonToolBarFormFilePreview();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZIButtonToolBarFormFilePreview)
    afx_msg void OnNextPageButton();
    afx_msg void OnPreviousPageButton();
    afx_msg void OnRefreshButton();
    afx_msg void OnZoomOutButton();
    afx_msg void OnZoomInButton();
    afx_msg void OnNextFileButton();
    afx_msg void OnPrevFileButton();
    afx_msg void OnCloseButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

class AFX_EXT_CLASS ZVFormFilePreviewDlg : public CDialog
{
// Construction
public:
    /**
    * Dialog resources
    */
    enum
    {
        IDD = IDD_FORM_FILEPREVIEW
    };

    ZIButtonToolBarFormFilePreview m_FlatToolBar;

    ZVFormFilePreviewDlg(const CString fileName, ZDDocTemplateEx* pDocTemplate, CWnd* pParent = NULL);
    virtual ~ZVFormFilePreviewDlg();

protected:
    /// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVFormFilePreviewDlg)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

    /// Generated message map functions
    //{{AFX_MSG(ZVFormFilePreviewDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void OnOK();
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


private:
    CCreateContext   m_Context; 
    CString          m_Filename;
    ZIViewRead*      m_pView;
    CFrameWnd*       m_pFrameWindow;
    ZDDocument*      m_pDocument;
    ZDDocTemplateEx* m_pDocTemplate;

    void SizeControl();
    void CloseDocument();
};

#endif
