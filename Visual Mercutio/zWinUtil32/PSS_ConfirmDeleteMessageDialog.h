/****************************************************************************
 * ==> PSS_ConfirmDeleteMessageDialog --------------------------------------*
 ****************************************************************************
 * Description : Provides a confirm delete message dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ConfirmDeleteMessageDialogH
#define PSS_ConfirmDeleteMessageDialogH

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
#include "zEvent\ActEvent.h"
#include "HoverButton.h"

// resources
#ifdef _WIN32
    #include "zWinUtil32Res.h"
#else
    #include "zWinUtilRes.h"
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
* Confirm delete message dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ConfirmDeleteMessageDialog : public ZIDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_CONFIRM_DELETE_MSGEVT
        };

        ZUHoverButton m_Delete;
        ZUHoverButton m_DoNotDelete;
        CString       m_ActivityName;
        CString       m_Message;
        CString       m_ProcessName;
        CString       m_Status;

        /**
        * Constructor
        *@param eventActivity - event activity
        *@param pParent - parent window - can be NULL
        */
        PSS_ConfirmDeleteMessageDialog(ZBEventActivity& eventActivity, CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ConfirmDeleteMessageDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ConfirmDeleteMessageDialog)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
