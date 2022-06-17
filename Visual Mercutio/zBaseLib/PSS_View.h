/****************************************************************************
 * ==> PSS_View ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ViewH
#define PSS_ViewH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

// processsoft
#include "PSS_PlanFinObject.h"
#include "PSS_DropScrollView.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

// forward class declarations
class PSS_Document;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Generic view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_View : public PSS_DropScrollView
{
    DECLARE_DYNCREATE(PSS_View)

    public:
        /**
        * View type
        */
        enum class IEType
        {
            IE_VT_Unknown,
            IE_VT_FormRead,
            IE_VT_FormModify,
            IE_VT_FormFieldCode,
            IE_VT_FormDesign,
            IE_VT_ProcessRead,
            IE_VT_ProcessModify,
            IE_VT_ProcessDesign
        };

        typedef PSS_DropScrollView inherited;

        /**
        * Initializes the view
        */
        virtual void Initialize();

        /**
        * Calculates the document size
        */
        virtual void CalculateDocumentSize();

        /**
        * Sets the logical coordinates
        *@param pDC - device context on which coordinates should be measured
        */
        virtual void SetLogicalCoordinates(CDC* pDC);

        /**
        * Gets the document
        *@return the document
        */
        virtual inline PSS_Document* GetDocument();

        /**
        * Called when the device context is prepared
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

        /**
        * Gets the object selected by the righ-click
        *@param point - click point
        *@param autoReset - if TRUE, the selection will be released if it was already selected
        *@return the object selected by the righ-click, NULL if no selection or on error
        */
        virtual PSS_PlanFinObject* ActiveSelectedObject(CPoint& point, BOOL autoReset = FALSE);

        /**
        * Selects the object inside a rect
        *@param rect - rect
        *@param pWnd - parent window
        *@param pDC - device context
        */
        virtual void SelectObjectInRect(const CRect& rect, CWnd* pWnd, CDC* pDC);

        /**
        * Gets the rectangle surrounding all the selected objects
        *@param[out] rect - the rectangle surrounding all the selected objects on function ends
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetRectOfSelectedObject(CRect& rect);

        /**
        * De-selects all the objects
        *@param pWnd - parent window
        *@param pDC - device context
        *@param pDoc - document
        */
        virtual void DeselectAllObject(CWnd* pWnd, CDC* pDC, PSS_Document* pDoc);

        /**
        * Converts the client screen coordinates to document coordinates
        *@param[in, out] point - point to convert, converted point on function ends
        */
        virtual void ClientToDoc(CPoint& point);

        /**
        * Converts the client screen coordinates to document coordinates
        *@param[in, out] rect - rectangle to convert, converted rectangle on function ends
        */
        virtual void ClientToDoc(CRect& rect);

        /**
        * Converts the document coordinates to client screen coordinates
        *@param[in, out] point - point to convert, converted point on function ends
        */
        virtual void DocToClient(CPoint& point);

        /**
        * Converts the document coordinates to client screen coordinates
        *@param[in, out] rect - rectangle to convert, converted rectangle on function ends
        */
        virtual void DocToClient(CRect& rect);

        /**
        * Gets the selected object located at the point
        *@param point - point
        *@return the selected object, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* FindHitObject(CPoint& point);

        /**
        * Selects an object and gets it
        *@return the selected object, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* SelectAndGet();

        /**
        * Gets the selected object array
        *@return the selected object array
        */
        virtual CObArray& GetArrayOfSelectedObject();

        /**
        * Checks if the object is still in the page report. If not, the object will be moved
        *@param pObj - object to check and move
        *@param reportSize - report size
        */
        virtual void KeepObjectInPage(PSS_PlanFinObject* pObj, const CSize& reportSize);

        /**
        * Gets the current zoom percentage
        *@return the current zoom percentage
        */
        virtual inline int GetZoomPercentage();

        /**
        * Sets the new zoom percentage
        *@param value - the new zoom percentage
        */
        virtual void SetZoomPercentage(int value);

        /**
        * Processes the object edition
        *@param pObj - object to process
        */
        virtual void EditObject(PSS_PlanFinObject* pObj = NULL);

        /**
        * Gets the tooltip
        *@return the tooltip
        */
        virtual inline CToolTipCtrl& GetToolTip();

        /**
        * Gets the viewtype
        *@return the view type
        */
        virtual inline const IEType GetViewType() const;

        /**
        * Sets the scroll sizes
        */
        virtual void SetScrollSizes();

    protected:
        static PSS_PlanFinObject* m_pOldPointerSelectedObj;
        CToolTipCtrl              m_ToolTip;
        CObArray                  m_ArrayOfSelectedObject;
        IEType                    m_ViewType;
        CRect                     m_PageRect;
        CSize                     m_TotalSize;
        CSize                     m_PageSize;
        CSize                     m_LineSize;
        HCURSOR                   m_hSelectorCursor;
        CString                   m_StrToolTip;
        BOOL                      m_SelectObjectMode;

        PSS_View();
        virtual ~PSS_View();

        /**
        * Called on initial update
        */
        virtual void OnInitialUpdate();

        /**
        * Gets the report page size in millimeters
        *@return the report page size in millimeters
        */
        virtual CSize GetReportPageSize();

        /**
        * Gets the report page size in pixels
        *@return the report page size in pixels
        */
        virtual CSize GetReportPageSizeInPixels();

        /**
        * Draws the page rect
        *@param pDC - device context to draw to
        */
        virtual void DrawPageRect(CDC* pDC);

        /**
        * Called when the page is drawing
        *@param pDC - device context to draw to
        */
        virtual void OnDraw(CDC* pDC);

        /// Generated message map functions
        //{{AFX_MSG(PSS_View)
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_PlanFinObject* m_pSelectedObject;
        int                m_LogUnitX;
        int                m_LogUnitY;
        int                m_Zoom;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_View(const PSS_View& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_View& operator = (const PSS_View& other);
};

//---------------------------------------------------------------------------
// PSS_View
//---------------------------------------------------------------------------
PSS_Document* PSS_View::GetDocument()
{
    return (PSS_Document*)CView::GetDocument();
}
//---------------------------------------------------------------------------
int PSS_View::GetZoomPercentage()
{
    return m_Zoom;
}
//---------------------------------------------------------------------------
CToolTipCtrl& PSS_View::GetToolTip()
{
    return m_ToolTip;
}
//---------------------------------------------------------------------------
inline const PSS_View::IEType PSS_View::GetViewType() const
{
    return m_ViewType;
}
//---------------------------------------------------------------------------

#endif
