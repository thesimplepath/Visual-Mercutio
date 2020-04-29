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

// processsoft
#include "PSS_GridDocument.h"

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
class AFX_EXT_CLASS PSS_GridView : public CGXGridView
{
    GXDECLARE_DYNCREATE(PSS_GridView)

    public:
        #if _MFC_VER >= 0x0400
            CGXGridDropTarget m_objDndDropTarget;
        #endif

        virtual ~PSS_GridView();

        /**
        * Iinitializes the user attributes
        */
        virtual void SetupUserAttributes();

        /**
        * Sets up the special controls
        */
        virtual void SetupControls();

        /**
        * Gets the document
        *@return the document
        */
        virtual inline PSS_GridDocument* GetDocument();

        /**
        * Gets the master document
        *@return the master document
        */
        virtual inline PSS_GridDocument* GetMasterDocument();

        /**
        * Inserts a group control
        *@param row - the row
        *@param col - the column
        *@param coveringCells - the covering cell count
        *@param horizontal - if true, the layer will be horizontal instead of vertical
        *@param collapsed - if true, the group is collapsed
        *@param label - the label
        *@param tooltipText - the tooltip text
        */
        virtual void InsertGroupCtrl(ROWCOL         row,
                                     ROWCOL         col,
                                     int            coveringCells,
                                     bool           horizontal,
                                     bool           collapsed,
                                     const CString& label       = _T(""),
                                     const CString& tooltipText = _T(""));

        /**
        * Searches for a group control
        *@param row - the row
        *@param col - the column
        *@return the group control, NULL if not found or on error
        */
        virtual PSS_GridGroup* SearchGroupCtrl(ROWCOL row, ROWCOL col);

        /**
        * Sets the popup menu
        *@param resID - the popup menu resource identifier
        */
        virtual void SetPopupMenu(UINT resID);

        /**
        * Exports the grid report to a text file
        */
        virtual void ExportToTextFile();

        /**
        * Exports the grid report to a text file
        *@param fileName - the file name to export to
        *@return true on success, otherwise false
        */
        virtual bool ExportToTextFile(const CString& fileName);

        /**
        * Imports the grid report from a text file
        */
        virtual void ImportTextFile();

        /**
        * Imports the grid report from a text file
        *@param fileName - the file name to import from
        *@return true on success, otherwise false
        */
        virtual bool ImportTextFile(const CString& fileName);

        /**
        * Freezes the report splitter
        */
        virtual void FreezeSplitter();

        /**
        * Unfreezes the report splitter
        */
        virtual void UnfreezeSplitter();

        /**
        * Unhides all the cells
        */
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
        afx_msg void OnViewZoomOut();
        afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
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

        PSS_GridView();

        /**
        * Called when the right button is clicked on a cell
        *@param row - the clicked cell row
        *@param col - the clicked cell column
        *@param flags - the special button flags
        *@param point - the clicked point in pixels
        *@return TRUE if the message was processed, otherwise FALSE
        *@note The default behavior will be to show the popup menu
        */
        virtual BOOL OnRButtonClickedRowCol(ROWCOL row, ROWCOL col, UINT flags, CPoint point);

    private:
        static CMenu m_PopupMenu;
};

//---------------------------------------------------------------------------
// PSS_GridView
//---------------------------------------------------------------------------
PSS_GridDocument* PSS_GridView::GetDocument()
{
    return dynamic_cast<PSS_GridDocument*>(m_pDocument);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    PSS_GridDocument* PSS_GridView::GetMasterDocument()
    {
        PSS_GridDocument* pDoc = dynamic_cast<PSS_GridDocument*>(m_pDocument);

        if (pDoc)
        {
            PSS_GridDocument* pPrimaryDoc = dynamic_cast<PSS_GridDocument*>(pDoc->GetPrimaryDocument());

            if (pPrimaryDoc)
                return pPrimaryDoc;
        }

        return NULL;
    }
#else
    PSS_GridDocument* PSS_GridView::GetMasterDocument()
    {
        PSS_GridDocument* pDoc = GetDocument();
        return (pDoc ? dynamic_cast<PSS_GridDocument*>(pDoc->GetPrimaryDocument()) : NULL);
    }
#endif
//---------------------------------------------------------------------------

#endif
