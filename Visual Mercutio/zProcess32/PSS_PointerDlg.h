/****************************************************************************
 * ==> PSS_PointerDlg ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a pointer dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PointerDlgH
#define PSS_PointerDlgH

// processsoft
#include "zBaseLib\PSS_PlanFinObjects.h"
#include "zWinUtil32\PSS_NewFormDialog.h"
#include "zWinUtil32\PSS_PointerWnd.h"

/**
* Pointer dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PointerDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pParent - the parent window, can be NULL
        */
        PSS_PointerDlg(CWnd* pParent = NULL);

        virtual ~PSS_PointerDlg();

        /**
        * Creates the dialog
        *@param pParent - the parent window, can be NULL
        */
        virtual void Create(CWnd* pParent = NULL);

        /**
        * Closes the dialog box
        */
        virtual void Close();

        /**
        * Gets the selected object
        *@return the selected object
        */
        virtual inline PSS_PlanFinObject* GetSelectedObject();

        /**
        * Shows the wizard in modal mode
        *@return the modal result
        */
        virtual int DoModal();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowNotationOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZDPointerDlg)
        afx_msg LONG OnNotifyPointerObjSelected(UINT message, LONG wParam);
        afx_msg void OnClose();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the dialog is initialized
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OnInitDialog();

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_POINTER
        };

        PSS_PointerWnd     m_PointerWindow;
        PSS_PlanFinObject* m_pObj;
        CString            m_Field;
        int                m_ID;
};

//---------------------------------------------------------------------------
// PSS_PointerDlg
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PointerDlg::GetSelectedObject()
{
    return m_pObj;
}
//---------------------------------------------------------------------------

#endif
