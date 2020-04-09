/****************************************************************************
 * ==> PSS_WelcomeProcessDlg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the welcome process dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WelcomeProcessDlgH
#define PSS_WelcomeProcessDlgH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zWinUtil32\PSS_WelcomeDialog.h"

// resources
#include "Resources.h"

/**
* Welcome process dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_WelcomeProcessDlg : public PSS_WelcomeDialog
{
    public:
        /**
        * Constructor
        *@param pApplicationOptions - the application options
        *@param enableMoveToGeneral - if TRUE, the enable move to general option will be enabled
        *@param pParent - the parent window, can be NULL
        */
        PSS_WelcomeProcessDlg(PSS_ApplicationOption* pApplicationOptions,
                              BOOL                   enableMoveToGeneral = FALSE,
                              CWnd*                  pParent             = NULL);

        virtual ~PSS_WelcomeProcessDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WelcomeProcessDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WelcomeProcessDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnWelcomeCreateNewModel();
        afx_msg void OnWelcomeCreateNewProject();
        afx_msg void OnWelcomeOpenModel();
        afx_msg void OnWelcomeOpenProject();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        #ifndef _WIN32
            /**
            * Dialog Data
            */
            enum
            {
                IDD = IDD_WELCOME_PROCESS
            };

            CButton m_OpenModel;
            CButton m_OpenProject;
            CButton m_CreateNewModel;
            CButton m_CreateNewProject;
        #endif

        #ifdef _WIN32
            /**
            * Dialog Data
            */
            enum
            {
                IDD = IDD_WELCOME_PROCESS
            };

            PSS_HoverButton m_OpenModel;
            PSS_HoverButton m_OpenProject;
            PSS_HoverButton m_CreateNewModel;
            PSS_HoverButton m_CreateNewProject;
        #endif
};

#endif
