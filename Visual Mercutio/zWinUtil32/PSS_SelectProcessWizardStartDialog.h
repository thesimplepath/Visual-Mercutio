/****************************************************************************
 * ==> PSS_SelectProcessWizardStartDialog ----------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard start dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectProcessWizardStartDialogH
#define PSS_SelectProcessWizardStartDialogH

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
#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* Select process Wizard start dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectProcessWizardStartDialog : public ZIWizardDialog
{
    public:
        /**
        * Constructor
        *@param processName - process name
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectProcessWizardStartDialog(const CString& processName, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectProcessWizardStartDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectProcessWizardStartDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCHOOSEPROC_WELCOME
        };

        CString m_ProcessName;
};

#endif
