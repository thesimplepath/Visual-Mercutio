/****************************************************************************
 * ==> PSS_ScanWelcomeDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan welcome dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ScanWelcomeDialogH
#define PSS_ScanWelcomeDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\ZWizard.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

/**
* Scan welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ScanWelcomeDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZSCANNING_WELCOME
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_ScanWelcomeDialog(CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ScanWelcomeDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ScanWelcomeDialog)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
