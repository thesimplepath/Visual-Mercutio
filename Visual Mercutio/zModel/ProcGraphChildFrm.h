/****************************************************************************
 * ==> PSS_ProcessGraphChildFrame ------------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process child frame                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphChildFrameH
#define PSS_ProcessGraphChildFrameH

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

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Graphic process child frame
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphChildFrame : public SECMDIChildWnd
{
    DECLARE_DYNCREATE(PSS_ProcessGraphChildFrame)

    public:
        PSS_ProcessGraphChildFrame();
        virtual ~PSS_ProcessGraphChildFrame();

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
        //{{AFX_VIRTUAL(PSS_ProcessGraphChildFrame)
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessGraphChildFrame)
        afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
        afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the frame title should be updated
        *@param addToTitle - if true, the frame name will be added to title
        */
        virtual void OnUpdateFrameTitle(BOOL addToTitle);

    private:
        static CDocument* m_pLastActivatedDocument;
};

#endif
