/****************************************************************************
 * ==> PSS_GridChildFrame --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid child frame                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridChildFrameH
#define PSS_GridChildFrameH

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
* Grid child frame
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridChildFrame : public CGXWChildFrame
{
    DECLARE_DYNCREATE(PSS_GridChildFrame)

    public:
        PSS_GridChildFrame();
        virtual ~PSS_GridChildFrame();

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
        //{{AFX_VIRTUAL(PSS_GridChildFrame)
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridChildFrame)
        afx_msg void OnInsertsksheet();
        afx_msg void OnDeletewksheet();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
