/****************************************************************************
 * ==> PSS_CodeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a code view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CodeViewH
#define PSS_CodeViewH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
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
* Code view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CodeView : public PSS_View
{
    DECLARE_DYNCREATE(PSS_CodeView)

    public:
        typedef PSS_View inherited;

        /**
        * Gets the displayed code
        *@return the displayed code
        */
        virtual inline EClassType GetDisplayCode();

        /**
        * Sets the displayed code
        *@param type - the displayed code
        */
        virtual inline void SetDisplayCode(EClassType type);

    protected:
        PSS_CodeView();
        virtual ~PSS_CodeView();

        /**
        * Called when the view is initialized for the first time
        */
        virtual void OnInitialUpdate();

        /**
        * Called when the view is drawn
        *@param pDC - device context
        */
        virtual void OnDraw(CDC* pDC);

        /**
        * Called when the view is prepared to be printed
        *@param pInfo - print info
        */
        virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

        /**
        * Called when the view printing begins
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);

        /**
        * Called when the view printing ends
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

        /**
        * Called when the view is printed
        *@param pDC - device context
        *@param pInfo - print info
        */
        virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

        /// Generated message map functions
        //{{AFX_MSG(PSS_CodeView)
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnOnlyNumericFields();
        afx_msg void OnUpdateOnlyNumericFields(CCmdUI* pCmdUI);
        afx_msg LONG OnDisplayFieldType(UINT message, LONG lParam);
        afx_msg LONG OnSynchronizeVScroll(UINT message, LONG lParam);
        afx_msg LONG OnSynchronizeHScroll(UINT message, LONG lParam);
        afx_msg void OnDisplayCalculatedCode();
        afx_msg void OnUpdateDisplayCalculatedCode(CCmdUI* pCmdUI);
        afx_msg void OnDisplayallCode();
        afx_msg void OnUpdateDisplayallCode(CCmdUI* pCmdUI);
        afx_msg void OnDisplayStaticCode();
        afx_msg void OnUpdateDisplayStaticCode(CCmdUI* pCmdUI);
        afx_msg void OnDisplayTextCode();
        afx_msg void OnUpdateDisplayTextCode(CCmdUI* pCmdUI);
        afx_msg void OnDisplayGraphicCode();
        afx_msg void OnUpdateDisplayGraphicCode(CCmdUI* pCmdUI);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        EClassType m_CodeType;
        int        m_SavePageForPrinting;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CodeView(const PSS_CodeView& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_CodeView& operator = (const PSS_CodeView& other);
};

//---------------------------------------------------------------------------
// PSS_CodeView
//---------------------------------------------------------------------------
EClassType PSS_CodeView::GetDisplayCode()
{
    return m_CodeType;
}
//---------------------------------------------------------------------------
void PSS_CodeView::SetDisplayCode(EClassType Type)
{
    m_CodeType = Type;
}
//---------------------------------------------------------------------------

#endif
