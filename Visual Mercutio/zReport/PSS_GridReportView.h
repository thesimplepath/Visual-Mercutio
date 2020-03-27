/****************************************************************************
 * ==> PSS_GridReportView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridReportViewH
#define PSS_GridReportViewH

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
#include "ZVGridView.h"

// forward class declaration
class PSS_GridReportDocument;

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
* Grid report view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GridReportView : public ZVGridView
{
    GXDECLARE_DYNCREATE(PSS_GridReportView)

    public:
        virtual ~PSS_GridReportView();

        /**
        * Initializes the user attributes
        */
        virtual void SetupUserAttributes();

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
        //{{AFX_VIRTUAL(PSS_GridReportView)
        virtual void OnInitialUpdate();
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_GridReportView)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        PSS_GridReportView();
};

#endif
