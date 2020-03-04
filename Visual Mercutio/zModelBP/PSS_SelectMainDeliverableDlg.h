/****************************************************************************
 * ==> PSS_SelectMainDeliverableDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a select the main deliverable dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectMainDeliverableDlgH
#define PSS_SelectMainDeliverableDlgH

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
* Select the main deliverable dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SelectMainDeliverableDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@remainingDeliverables - the remaining deliverables
        *@param deliverables - the deliverables
        *@param pParent - the parent window, can be NULL
        */
        PSS_SelectMainDeliverableDlg(const CString& deliverables, const CString& main = _T(""), CWnd* pParent = NULL);

        virtual ~PSS_SelectMainDeliverableDlg();

        /**
        * Gets the main deliverable
        *@return the main deliverable
        */
        virtual inline CString GetMain() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectMainDeliverableDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectMainDeliverableDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangeListOfDeliverable();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_CHOOSE_MAINDELIV
        };

        CListBox m_ListOfDeliverables;
        CString  m_Deliverables;
        CString  m_Main;

        /**
        * Adds a deliverable to a listbox
        *@param deliv - the deliverable to add
        *@param lb - the listbox to add to
        */
        void DelivToListBox(const CString& deliv, CListBox& lb);

        /**
        * Checks the state
        */
        void CheckState();
};

//---------------------------------------------------------------------------
// PSS_SelectMainDeliverableDlg
//---------------------------------------------------------------------------
CString PSS_SelectMainDeliverableDlg::GetMain() const
{
    return m_Main;
}
//---------------------------------------------------------------------------

#endif
