/****************************************************************************
 * ==> PSS_RiskNewFileDlg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a create a new risk file dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskNewFileDlgH
#define PSS_RiskNewFileDlgH

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

// mfc
#include "afxwin.h"

// resources
#include "zModelBPRes.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Create a new risk file dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskNewFileDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param extension - the file extension
        *@param pParent - the parent window, can be NULL
        */
        PSS_RiskNewFileDlg(const CString& extension, CWnd* pParent = NULL);

        virtual ~PSS_RiskNewFileDlg();

        /**
        * Gets the directory
        *@return the directory
        */
        virtual CString GetDirectory();

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RiskNewFileDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RiskNewFileDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnBnClickedDirectorySelect();
        afx_msg void OnEnChangeFileName();
        afx_msg void OnEnChangeDirectory();
        afx_msg void OnBnClickedOk();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_NEW_RISK_FILE
        };

        CEdit   m_FileName_Ctrl;
        CEdit   m_Directory_Ctrl;
        CButton m_OK_Ctrl;
        CString m_Directory;
        CString m_FileName;
        CString m_Extension;

        /**
        * Checks the user entry
        */
        void CheckUserEntry();
};

#endif
