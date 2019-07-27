/****************************************************************************
 * ==> PSS_FormTemplateTreeCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides a form template tree control                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FormTemplateTreeCtrlH
#define PSS_FormTemplateTreeCtrlH

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
#include "PSS_TemplateTreeCtrl.h"

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
* Template tree control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FormTemplateTreeCtrl : public PSS_TemplateTreeCtrl
{
    DECLARE_DYNCREATE(PSS_FormTemplateTreeCtrl)

    public:
        PSS_FormTemplateTreeCtrl();
        virtual ~PSS_FormTemplateTreeCtrl();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FormTemplateTreeCtrl)
        //}}AFX_VIRTUAL

        //{{AFX_MSG(PSS_FormTemplateTreeCtrl)
        afx_msg LRESULT OnInitializeTemplateManager(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnReloadTemplateManager(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
