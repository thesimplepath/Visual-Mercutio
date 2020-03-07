/****************************************************************************
 * ==> PSS_AddRemoveDeliveryDeliverablesDlg --------------------------------*
 ****************************************************************************
 * Description : Provides an add/remove deliverable delivery dialog box     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AddRemoveDeliveryDeliverablesDlgH
#define PSS_AddRemoveDeliveryDeliverablesDlgH

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
* Add/remove deliverable delivery dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_AddRemoveDeliveryDeliverablesDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param remainingDeliverables - the remaining deliverables
        *@param deliverables - the deliverables
        *@param pParent - the parent window, can be NULL
        */
        PSS_AddRemoveDeliveryDeliverablesDlg(const CString& availableDeliverables = _T(""),
                                             const CString& selectedDeliverables  = _T(""),
                                             CWnd*          pParent               = NULL);

        virtual ~PSS_AddRemoveDeliveryDeliverablesDlg();

        /**
        * Gets the deliverables
        *@return the deliverables
        */
        virtual inline CString GetDeliverables() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_AddRemoveDeliveryDeliverablesDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_AddRemoveDeliveryDeliverablesDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnAddDeliv();
        afx_msg void OnDelDeliv();
        afx_msg void OnSelchangeSelectedDeliv();
        afx_msg void OnSelchangeAvailableDeliv();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_ADD_DELIV_DELIVERY
        };

        CListBox m_SelectedDeliverablesLB;
        CListBox m_AvailableDeliverablesLB;
        CString  m_SelectedDeliverables;
        CString  m_AvailableDeliverables;

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
        void ListBoxToString(CListBox& lb, CString& deliv);

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

        /**
        * Checks if an entry exists
        *@param entryValue - the entry value to search
        *@return TRUE if the entry exists, otherwise FALSE
        */
        BOOL EntryExist(const CString& entryValue);
};

//---------------------------------------------------------------------------
// PSS_AddRemoveDeliveryDeliverablesDlg
//---------------------------------------------------------------------------
CString PSS_AddRemoveDeliveryDeliverablesDlg::GetDeliverables() const
{
    return m_SelectedDeliverables;
}
//---------------------------------------------------------------------------

#endif
