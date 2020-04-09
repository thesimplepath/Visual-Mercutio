/****************************************************************************
 * ==> PSS_ImportProcessDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an import process dialog                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ImportProcessDlgH
#define PSS_ImportProcessDlgH

// processsoft
#include "zBaseLib\PSS_Dialog.h"

// resources
#include "resources.h"

/**
* Import process dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ImportProcessDlg : public PSS_Dialog
{
    public:
        /**
        * Constructor
        *@param fileName - the file name to import
        *@param doImport - if TRUE, the file will be imported, exported otherwise
        *@param pParent - the parent window, can be NULL
        */
        PSS_ImportProcessDlg(const CString& fileName = "", BOOL doImport = TRUE, CWnd* pParent = NULL);

        virtual ~PSS_ImportProcessDlg();

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ImportProcessDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_ImportProcessDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelect();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_IMPORTPROCESS_DEFINITION
        };

        CString m_FileName;
        CString m_InitialFileName;
        BOOL    m_Import;
};

//---------------------------------------------------------------------------
// PSS_ImportProcessDlg
//---------------------------------------------------------------------------
CString PSS_ImportProcessDlg::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------

#endif
