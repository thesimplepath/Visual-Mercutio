/****************************************************************************
 * ==> PSS_OutlookSplitterWnd ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an Outlook splitter window                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OutlookSplitterWndH
#define PSS_OutlookSplitterWndH

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
* Outlook splitter window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OutlookSplitterWnd : public CSplitterWnd
{
    DECLARE_DYNAMIC(PSS_OutlookSplitterWnd)

    public:
        COLORREF m_ClrBtnHLit;
        COLORREF m_ClrBtnShad;
        COLORREF m_ClrBtnFace;

        PSS_OutlookSplitterWnd();
        virtual ~PSS_OutlookSplitterWnd();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_OutlookSplitterWnd)
        virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
        //}}AFX_VIRTUAL

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_OutlookSplitterWnd)
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
