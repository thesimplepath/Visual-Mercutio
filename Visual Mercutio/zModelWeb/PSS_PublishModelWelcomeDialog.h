/****************************************************************************
 * ==> PSS_PublishModelWelcomeDialog ---------------------------------------*
 ****************************************************************************
 * Description : Dialog box showing the publication process welcome page    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelWelcomeDialogH
#define PSS_PublishModelWelcomeDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\ZWizard.h"

// resources
#include "zModelWebRes.h"

 /**
 * Dialog box showing the publication process welcome page
 *@author Dominique Aigroz, Jean-Milost Reymond
 */
class PSS_PublishModelWelcomeDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_WELCOME
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_PublishModelWelcomeDialog(CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelWelcomeDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelWelcomeDialog)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
