/****************************************************************************
 * ==> PSS_ProcessNameDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a process name dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessNameDialogH
#define PSS_ProcessNameDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// resources
#include "Resources.h"

/**
* Process name dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ProcessNameDialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - the parent window, can be NULL
        */
        PSS_ProcessNameDialog(CWnd* pParent = NULL);

        virtual ~PSS_ProcessNameDialog();

        /**
        * Gets the process name
        *@return the process name
        */
        virtual inline const CString ProcessName() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessNameDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessNameDialog)
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_PROCESSNAME
        };

        CString m_ProcessName;
};

//---------------------------------------------------------------------------
// PSS_ProcessNameDialog
//---------------------------------------------------------------------------
const CString PSS_ProcessNameDialog::ProcessName() const
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------

#endif
