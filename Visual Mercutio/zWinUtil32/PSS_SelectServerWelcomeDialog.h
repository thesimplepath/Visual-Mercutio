/****************************************************************************
 * ==> PSS_SelectServerWelcomeDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server welcome dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectServerWelcomeDialogH
#define PSS_SelectServerWelcomeDialogH

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
#include "PSS_DirTreeCtrl.h"

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
* Select a server welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectServerWelcomeDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCHOOSESRV_WELCOME
        };

        /**
        * Constructor
        *@param local - if TRUE, server is local
        *@param pPArent - parent window, can be NULL
        */
        PSS_SelectServerWelcomeDialog(BOOL local = TRUE, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectServerWelcomeDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectServerWelcomeDialog)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        BOOL m_Local;
};

#endif
