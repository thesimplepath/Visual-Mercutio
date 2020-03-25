// ZVGridView.h : interface of the ZVGridView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVGridView_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZVGridView_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

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

// old class name mapping
#ifndef PSS_GridGroup
#define PSS_GridGroup ZCGridGroup
#endif

// forward class declaration
class PSS_GridDocument;
class PSS_GridGroup;

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZVGridView : public CGXGridView
{
protected:

    GXDECLARE_DYNCREATE(ZVGridView)

        // Create from serialization only
        ZVGridView();

public:

    virtual ~ZVGridView();

    // Attributes
public:

    PSS_GridDocument* GetDocument();
    PSS_GridDocument* GetMasterDocument();

    // Operations
public:

    // User attributes initialization 
    virtual void SetupUserAttributes();

    // Setup special controls
    virtual void SetupControls();

    void InsertGroupCtrl(ROWCOL        Row,
                         ROWCOL        Col,
                         int            CoveringCells,
                         bool            Horizontal,
                         bool            Collapsed,
                         const CString    Label = _T(""),
                         const CString    ToolTipText = _T(""));

    PSS_GridGroup* FindGroupCtrl(ROWCOL Row, ROWCOL Col);

    void SetPopupMenu(UINT nIDRes);
    void ExportToTextFile();
    bool ExportToTextFile(const CString fileName);

    void ImportTextFile();
    bool ImportTextFile(const CString fileName);

    virtual void FreezeSplitter();
    virtual void UnfreezeSplitter();

    virtual void UnhideAll();

#if _MFC_VER >= 0x0400
    CGXGridDropTarget m_objDndDropTarget;
#endif

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVGridView)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol);
    afx_msg void OnViewZoomIn();
    afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
    afx_msg void OnViewZoomOut();
    afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
    afx_msg void OnFreezeSplitter();
    afx_msg void OnUpdateFreezeSplitter(CCmdUI* pCmdUI);
    afx_msg void OnUnfreezeSplitter();
    afx_msg void OnUpdateUnfreezeSplitter(CCmdUI* pCmdUI);
    afx_msg void OnUnhideAll();
    afx_msg void OnUpdateUnhideAll(CCmdUI* pCmdUI);
    //}}AFX_VIRTUAL

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
    //{{AFX_MSG(ZVGridView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnExportToTextFile();
    afx_msg void OnUpdateExportToTextFile(CCmdUI* pCmdUI);
    afx_msg void OnImportFromTextFile();
    afx_msg void OnUpdateImportFromTextFile(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Called by the framework when the right button is clicked,
    // The default behaviour will display the popup-menu
    virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);

private:

    static CMenu m_PopupMenu;
};

#ifndef _DEBUG
// Debug version in og70View.cpp
inline PSS_GridDocument* ZVGridView::GetDocument()
{
    return (PSS_GridDocument*)m_pDocument;
}
#endif

#endif
