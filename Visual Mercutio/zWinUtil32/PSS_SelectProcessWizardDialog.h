/****************************************************************************
 * ==> PSS_SelectProcessWizardDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectProcessWizardDialogH
#define PSS_SelectProcessWizardDialogH

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
#include "zEvent\ZProcess.h"
#include "PSS_SearchEdit.h"
#include "PSS_ActivityListCtrl.h"

// resources
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
* Select process Wizard dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectProcessWizardDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param process - process
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectProcessWizardDialog(PSS_Process& process, CWnd* pParent = NULL);

        /**
        * Gets the base activity name
        *@return the base activity name
        */
        virtual inline CString GetBaseActivityName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectProcessWizardDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_SelectProcessWizardDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnClickActivityProcList(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCHOOSEPROC_SEL
        };

        PSS_ActivityListCtrl m_ActivityProcList;
        PSS_Process&         m_Process;
        CString              m_ProcessName;
        CString              m_BaseActivityName;

        /**
        * Checks the control states
        */
        void CheckControlStates();
};

//---------------------------------------------------------------------------
// PSS_SelectProcessWizardDialog
//---------------------------------------------------------------------------
CString PSS_SelectProcessWizardDialog::GetBaseActivityName() const
{
    return m_BaseActivityName;
}
//---------------------------------------------------------------------------

#endif
