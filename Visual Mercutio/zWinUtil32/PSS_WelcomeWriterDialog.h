/****************************************************************************
 * ==> PSS_WelcomeWriterDialog ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a welcome writer dialog box                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WelcomeWriterDialogH
#define PSS_WelcomeWriterDialogH

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

#include "PSS_WelcomeDialog.h"

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
* Welcome writer dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WelcomeWriterDialog : public PSS_WelcomeDialog
{
    public:
        #ifdef _WIN32
            /**
            * Dialog resources
            */
            enum
            {
                IDD = IDD_WELCOME_WRITER
            };

            PSS_HoverButton m_FileOpenProcess;
            PSS_HoverButton m_StartProcess;
            PSS_HoverButton m_StartForm;
            PSS_HoverButton m_FileOpen;
        #else
            /**
            * Dialog resources
            */
            enum
            {
                IDD = IDD_WELCOME_PROCESS
            };

            CButton m_FileOpenProcess;
            CButton m_StartProcess;
            CButton m_StartForm;
            CButton m_FileOpen;
        #endif

        /**
        * Constructor
        *@param pApplicationOptions - application options
        *@param enableMoveToGeneral - if TRUE, move to general option will be enabled
        *@param pPArent - parent window, can be NULL
        */
        PSS_WelcomeWriterDialog(PSS_ApplicationOption* pApplicationOptions,
                                BOOL                   enableMoveToGeneral = FALSE,
                                CWnd*                  pParent             = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_WelcomeWriterDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WelcomeWriterDialog)
        afx_msg void OnWelcomeFileOpen();
        afx_msg void OnWelcomeProcessFileOpen();
        afx_msg void OnWelcomeSartForm();
        afx_msg void OnWelcomeStartProcess();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
