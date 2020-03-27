/****************************************************************************
 * ==> PSS_GridView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridViewH
#define PSS_GridViewH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Grid view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZVGridView : public CGXGridView
{
    GXDECLARE_DYNCREATE(ZVGridView)

public:
    #if _MFC_VER >= 0x0400
        CGXGridDropTarget m_objDndDropTarget;
    #endif

    virtual ~ZVGridView();

    // User attributes initialization 
    virtual void SetupUserAttributes();

    // Setup special controls
    virtual void SetupControls();

    PSS_GridDocument* GetDocument();
    PSS_GridDocument* GetMasterDocument();

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

    /**
    * Asserts the class validity
    */
    #ifdef _DEBUG
        virtual void AssertValid() const;
    #endif

    /**
    * Dumps the class content
    *@param dc - dump context
    */
    #ifdef _DEBUG
        virtual void Dump(CDumpContext& dc) const;
    #endif

protected:
    /// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(PSS_GridView)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
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
    virtual void OnDraw(CDC* pDC);
    //}}AFX_VIRTUAL

    /// Generated message map functions
    //{{AFX_MSG(PSS_GridView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnExportToTextFile();
    afx_msg void OnUpdateExportToTextFile(CCmdUI* pCmdUI);
    afx_msg void OnImportFromTextFile();
    afx_msg void OnUpdateImportFromTextFile(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    ZVGridView();

    // Called by the framework when the right button is clicked,
    // The default behaviour will display the popup-menu
    virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);

private:
    static CMenu m_PopupMenu;
};

//---------------------------------------------------------------------------
// PSS_GridView
//---------------------------------------------------------------------------
#ifndef _DEBUG
    // Debug version in og70View.cpp
    inline PSS_GridDocument* ZVGridView::GetDocument()
    {
        return (PSS_GridDocument*)m_pDocument;
    }
#endif
//---------------------------------------------------------------------------

#endif
