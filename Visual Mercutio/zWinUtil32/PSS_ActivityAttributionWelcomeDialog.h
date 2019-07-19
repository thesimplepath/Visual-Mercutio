/****************************************************************************
 * ==> PSS_ActivityAttributionWelcomeDialog --------------------------------*
 ****************************************************************************
 * Description : Provides the activity attribution welcome dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityAttributionWelcomeDialogH
#define PSS_ActivityAttributionWelcomeDialogH

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
#include "zEvent\Activity.h"

#ifndef _WIN32
    #include "ZWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
#endif

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
* Activity attribution welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityAttributionWelcomeDialog : public ZIWizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZTIMERESOURCE_ATTRST
        };

        /**
        * Constructor
        *@param pActivity - activity
        *@param pParent - parent window, can be NULL
        */
        PSS_ActivityAttributionWelcomeDialog(ZActivity* pActivity, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ActivityAttributionWelcomeDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ActivityAttributionWelcomeDialog)
        virtual BOOL OnInitDialog();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ZActivity* m_pActivity;
};

#endif
