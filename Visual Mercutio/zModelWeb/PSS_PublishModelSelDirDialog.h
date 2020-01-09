/****************************************************************************
 * ==> PSS_PublishModelSelDirDialog ----------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model publication dir    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelSelDirDialogH
#define PSS_PublishModelSelDirDialogH

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
#include "zBaseLib\PSS_IntelliEdit.h"
#include "zWinUtil32\PSS_DirTreeCtrl.h"

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
* Dialog box allowing to select the model publication dir
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishModelSelDirDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param lastPathName - last known path name
        *@param pArrayOfAddress - array of address
        *@param pParent - parent window, can be NULL
        */
        PSS_PublishModelSelDirDialog(const CString& lastPathName    = _T(""),
                                     CStringArray*  pArrayOfAddress = NULL,
                                     CWnd*          pParent         = NULL);
    
        /**
        * Gets the directory
        *@return directory
        */
        virtual inline CString GetDirectory() const;

    protected:
        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelSelDirDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        afx_msg void OnChangeServerChoosed();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_SEL
        };

        PSS_DirTreeCtrl m_DirTreeCtrl;
        PSS_IntelliEdit m_CbDirectory;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelSelDirDialog)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        CString       m_Directory;
        CStringArray* m_pArrayOfAddress;

        /**
        * Checks the control state
        */
        void CheckControlStates();

        /**
        * Reflects the changed directory
        */
        void ReflectChangedDirectory();
};

//---------------------------------------------------------------------------
// PSS_PublishModelSelDirDialog
//---------------------------------------------------------------------------
CString PSS_PublishModelSelDirDialog::GetDirectory() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------

#endif
