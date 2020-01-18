/****************************************************************************
 * ==> PSS_OutputWorkflowLogView -------------------------------------------*
 ****************************************************************************
 * Description : Provides an output workflow log view                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OutputWorkflowLogViewH
#define PSS_OutputWorkflowLogViewH

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

// processsoft
#include "zBaseLib\PSS_OutputView.h"

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
* Output workflow log view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OutputWorkflowLogView : public PSS_OutputView
{
    DECLARE_DYNAMIC(PSS_OutputWorkflowLogView)

    public:
        PSS_OutputWorkflowLogView();
        virtual ~PSS_OutputWorkflowLogView();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_OutputWorkflowLogView)
        virtual void OnSelChanged();
        virtual void OnDoubleClick();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
