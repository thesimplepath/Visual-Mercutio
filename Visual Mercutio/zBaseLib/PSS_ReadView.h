/****************************************************************************
 * ==> PSS_ReadView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a read view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ReadViewH
#define PSS_ReadViewH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Document.h"
#include "PSS_View.h"

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
* Read view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ReadView : public PSS_View
{
    DECLARE_DYNCREATE(PSS_ReadView)

    public:
        typedef PSS_View inherited;

        PSS_ReadView();

        /**
        * Gets the document
        *@return the document
        */
        virtual inline PSS_Document* GetDocument();

    protected:
        virtual ~PSS_ReadView();

        /**
        * Called when view is drawn
        *@param pDC - device context
        */
        virtual void OnDraw(CDC* pDC);

        /**
        * Called when view is printed
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

        /**
        * Called when print is prepared
        *@param pInfo - print info
        */
        virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

        /**
        * Called when print begins
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);

        /**
        * Called when print ends
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

        /**
        * Pre translates key message
        *@param pMsg - message
        *@return TRUE if message was processed and should no longer be handled, otherwise FALSE
        */
        virtual BOOL PreTranslateMessage(MSG* pMsg);

        /**
        * Gets the right popup menu identifier
        *@return the popup menu identifier
        */
        virtual inline UINT GetRightPopupMenuID();

        /// Generated message map functions
        //{{AFX_MSG(PSS_ReadView)
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnViewZoomIn();
        afx_msg void OnViewZoomOut();
        afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
        afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        int m_SavePageForPrinting;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ReadView(const PSS_ReadView& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ReadView& operator = (const PSS_ReadView& other);
};

//---------------------------------------------------------------------------
// PSS_ReadView
//---------------------------------------------------------------------------
PSS_Document* PSS_ReadView::GetDocument()
{
    return (PSS_Document*)CView::GetDocument();
}
//---------------------------------------------------------------------------
UINT PSS_ReadView::GetRightPopupMenuID()
{
    return IDR_POPUPMENU_READERVIEW;
}
//---------------------------------------------------------------------------

#endif
