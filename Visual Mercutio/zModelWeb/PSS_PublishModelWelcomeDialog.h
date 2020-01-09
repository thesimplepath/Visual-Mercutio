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

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"

// resources
#include "zModelWebRes.h"

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

 /**
 * Dialog box showing the publication process welcome page
 *@author Dominique Aigroz, Jean-Milost Reymond
 */
class PSS_PublishModelWelcomeDialog : public PSS_WizardDialog
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
