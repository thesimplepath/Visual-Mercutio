/****************************************************************************
 * ==> PSS_AddRemoveCombinationDeliverableDlg ------------------------------*
 ****************************************************************************
 * Description : Provides an add/remove deliverable combinations dialog box *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AddRemoveCombinationDeliverableDlgH
#define PSS_AddRemoveCombinationDeliverableDlgH

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
* Add/remove deliverable combinations dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_AddRemoveCombinationDeliverableDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@remainingDeliverables - the remaining deliverables
        *@param deliverables - the deliverables
        *@param pParent - the parent window, can be NULL
        */
        PSS_AddRemoveCombinationDeliverableDlg(const CString& remainingDeliverables = _T(""),
                                               const CString& deliverables          = _T(""),
                                               CWnd*          pParent               = NULL);

        virtual ~PSS_AddRemoveCombinationDeliverableDlg();

        /**
        * Gets the deliverables
        *@return the deliverables
        */
        virtual inline CString GetDeliverables() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_AddRemoveCombinationDeliverableDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_AddRemoveCombinationDeliverableDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddDeliv();
        afx_msg void OnDelDeliv();
        afx_msg void OnSelchangeCombDeliv();
        afx_msg void OnSelchangeRemainDeliv();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_ADD_DELIV_COMBINATION
        };

        CListBox m_CombinationDeliverablesLB;
        CListBox m_RemainingDeliverablesLB;
        CString  m_Deliverables;
        CString  m_RemainingDeliverables;

        /**
        * Adds a deliverable to a listbox
        *@param deliv - the deliverable to add
        *@param lb - the listbox to add to
        */
        void DelivToListBox(const CString& deliv, CListBox& lb);

        /**
        * Gets a deliverable string from a listbox
        *@param lb - the listbox to get from
        *@param[out] str - the string
        */
        void ListBoxToString(CListBox& lb, CString& str);

        /**
        * Adds a string to a listbox
        *@param str - the string to add
        *@param lb - the listbox to add to
        */
        void AddStringToListBox(const CString& str, CListBox& lb);

        /**
        * Removes a string from a listbox
        *@param str - the string to remove
        *@param lb - the listbox to remove from
        */
        void RemoveStringFromListBox(const CString& str, CListBox& lb);

        /**
        * Checks the state
        */
        void CheckState();
};

//---------------------------------------------------------------------------
// PSS_AddRemoveCombinationDeliverableDlg
//---------------------------------------------------------------------------
CString PSS_AddRemoveCombinationDeliverableDlg::GetDeliverables() const
{
    return m_Deliverables;
}
//---------------------------------------------------------------------------

#endif
