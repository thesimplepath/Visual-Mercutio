/****************************************************************************
 * ==> PSS_ProcessTakeOwnershipActionsDialog -------------------------------*
 ****************************************************************************
 * Description : Provides a process take ownership actions dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TakeOwnershipActionsDialogH
#define PSS_TakeOwnershipActionsDialogH

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
* Take ownership actions dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessTakeOwnershipActionsDialog : public ZIDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_PROCESS_TAKEOWNERSHIP
        };

        PSS_HoverButton m_ViewCommandBtn;
        PSS_HoverButton m_CancelCommandBtn;
        PSS_HoverButton m_AcceptCommandBtn;

        /**
        * Constructor
        *@param fileName - file name
        *@param activityName - activity name
        *@param pParent - parent window, can be NULL
        */
        PSS_ProcessTakeOwnershipActionsDialog(const CString& fileName, const CString& activityName, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessTakeOwnershipActionsDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessTakeOwnershipActionsDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnViewCommand();
        afx_msg void OnAcceptCommand();
        afx_msg void OnCancelCommand();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CString m_FileName;
        CString m_ActivityName;
};

#endif
