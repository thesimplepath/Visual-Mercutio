/****************************************************************************
 * ==> PSS_PreConditionFormProcWelcomeDialog -------------------------------*
 ****************************************************************************
 * Description : Provides a pre-condition form process welcome dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PreConditionFormProcWelcomeDialogH
#define PSS_PreConditionFormProcWelcomeDialogH

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
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
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
* Pre-condition form process welcome dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PreConditionFormProcWelcomeDialog : public PSS_WizardDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPREACTST_FORMPROC
        };

        CString m_ActivityName;

        /**
        * Constructor
        *@param activityName - activity name
        *@param pParent - parent window, can be NULL
        */
        PSS_PreConditionFormProcWelcomeDialog(const CString& activityName = "", CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PreConditionFormProcWelcomeDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PreConditionFormProcWelcomeDialog)
        afx_msg void OnNext();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
