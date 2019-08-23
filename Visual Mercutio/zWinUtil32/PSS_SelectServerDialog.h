/****************************************************************************
 * ==> PSS_SelectServerDialog ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectServerDialogH
#define PSS_SelectServerDialogH

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
#include "PSS_DirTreeCtrl.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* Select a server dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectServerDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param local - if TRUE, server is local
        *@param pPArent - parent window, can be NULL
        */
        PSS_SelectServerDialog(BOOL local = TRUE, CWnd* pParent = NULL);

        /**
        * Gets the server directory
        *@return the server directory, empty string if no selection or on error
        */
        virtual inline CString GetDirectory() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectServerDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectServerDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnServerSelected();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZCHOOSESRV_SEL
        };

        PSS_DirTreeCtrl m_DirTreeCtrl;
        CString         m_Directory;
        BOOL            m_Local;

        /**
        * Checks the control states
        */
        void CheckControlStates();

        /**
        * Reflects the changed directory
        */
        void ReflectChangedDirectory();
};

//---------------------------------------------------------------------------
// PSS_SelectServerDialog
//---------------------------------------------------------------------------
CString PSS_SelectServerDialog::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------

#endif
