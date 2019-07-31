/****************************************************************************
 * ==> PSS_ProcessTemplateView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a process template view                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessTemplateViewH
#define PSS_ProcessTemplateViewH

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
#include "PSS_TemplateView.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process template view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessTemplateView : public PSS_TemplateView
{
    DECLARE_DYNCREATE(PSS_ProcessTemplateView)

protected:
    PSS_ProcessTemplateView();
    virtual ~PSS_ProcessTemplateView();

    /// Generated message map functions
    //{{AFX_MSG(PSS_ProcessTemplateView)
    afx_msg LRESULT OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReloadTemplateManager(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif
