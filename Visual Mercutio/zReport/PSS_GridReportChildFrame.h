/****************************************************************************
 * ==> PSS_GridReportChildFrame --------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report child frame                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_ZVGridReportChildFrm_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ZVGridReportChildFrm_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

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
#include "PSS_GridChildFrame.h"

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
* Grid report child frame
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridReportChildFrame : public PSS_GridChildFrame
{
    DECLARE_DYNCREATE(PSS_GridReportChildFrame)

    public:
        PSS_GridReportChildFrame();
        virtual ~PSS_GridReportChildFrame();

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
        //{{AFX_VIRTUAL(PSS_GridReportChildFrame)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridReportChildFrame)
        afx_msg LRESULT OnInitNew(WPARAM, LPARAM);
        afx_msg LRESULT OnInitFromFile(WPARAM, LPARAM);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the frame title is updated
        *@param addToTitle - if TRUE, the frame title is added to the existing one
        */
        virtual void OnUpdateFrameTitle(BOOL addToTitle);
};

#endif
