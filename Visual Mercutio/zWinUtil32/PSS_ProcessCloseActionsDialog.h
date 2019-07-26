/****************************************************************************
 * ==> PSS_ProcessCloseActionsDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a process close actions dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessCloseActionsDialogH
#define PSS_ProcessCloseActionsDialogH

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
#include "zBaseLib\ZIDialog.h"
#include "PSS_HoverButton.h"

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
* Process close actions dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessCloseActionsDialog : public ZIDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_PROCESSCLOSE
        };

        PSS_HoverButton m_AbortCommand;
        PSS_HoverButton m_TrashCommandBtn;
        PSS_HoverButton m_SuspendCommandBtn;
        PSS_HoverButton m_SendCommandBtn;
        PSS_HoverButton m_RejectCommandBtn;
        PSS_HoverButton m_CancelCommandBtn;
        PSS_HoverButton m_AcceptCommandBtn;

        /**
        * Constructor
        *@param sendCommand - if TRUE, send command will be enabled
        *@param acceptRejectCommand - if TRUE, accept/reject command will be enabled
        *@param suspendCommand - if TRUE, suspend command will be enabled
        *@param pParent - parent window, can be NULL
        */
        PSS_ProcessCloseActionsDialog(BOOL  sendCommand         = TRUE,
                                      BOOL  acceptRejectCommand = TRUE,
                                      BOOL  suspendCommand      = TRUE,
                                      CWnd* pParent             = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessCloseActionsDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessCloseActionsDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnAcceptCommand();
        afx_msg void OnRejectCommand();
        afx_msg void OnSendCommand();
        afx_msg void OnSuspendCommand();
        afx_msg void OnTrashCommand();
        afx_msg void OnCancelCommand();
        afx_msg void OnAbortCommand();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        BOOL m_SendCommand;
        BOOL m_AcceptRejectCommand;
        BOOL m_SuspendCommand;
};

#endif
