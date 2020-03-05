/****************************************************************************
 * ==> PSS_DistributionAttributesSelectionDlg ------------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes selection dialog box    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionAttributesSelectionDlgH
#define PSS_DistributionAttributesSelectionDlgH

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
#include "zModelBP\PSS_DistributionAttributesList.h"

// resources
#include "zModelBP\zModelBPRes.h"

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
* Distribution attributes selection dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionAttributesSelectionDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pDistribManager - the distribution manager
        *@param pPropManager -  the property manager
        *@param pMainUserGroup - the main user group
        *@param pParent - the parent window, can be NULL
        */
        PSS_DistributionAttributesSelectionDlg(PSS_DistributionAttributeManager* pDistribManager,
                                               ZBDynamicPropertiesManager*       pPropManager,
                                               PSS_UserGroupEntity*              pMainUserGroup,
                                               CWnd*                             pParent = NULL);

        virtual ~PSS_DistributionAttributesSelectionDlg();

        /**
        * Gets the selected distribution attribute
        *@return the selected distribution attribute
        */
        virtual inline PSS_DistributionAttribute* GetSelectedDistributionAttribute();

        /**
        * Gets the selected distribution rule
        *@return the selected distribution rule
        */
        virtual inline PSS_DistributionRule* GetSelectedDistributionRule();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DistributionAttributesSelectionDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DistributionAttributesSelectionDlg)
        virtual void OnOK();
        virtual BOOL OnInitDialog();
        afx_msg void OnClickDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnDblclkDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DISTRIBUTIONATTRIBUTES
        };

        PSS_DistributionAttributesList    m_List;
        PSS_DistributionAttributeManager* m_pDistribManager;
        ZBDynamicPropertiesManager*       m_pPropManager;
        PSS_UserGroupEntity*              m_pMainUserGroup;

        /**
        * Checks the control state
        */
        void CheckControlState();
};

//---------------------------------------------------------------------------
// PSS_DistributionAttributesSelectionDlg
//---------------------------------------------------------------------------
PSS_DistributionAttribute* PSS_DistributionAttributesSelectionDlg::GetSelectedDistributionAttribute()
{
    return m_List.GetSelectedDistributionAttribute();
}
//---------------------------------------------------------------------------
PSS_DistributionRule* PSS_DistributionAttributesSelectionDlg::GetSelectedDistributionRule()
{
    return m_List.GetSelectedDistributionRule();
}
//---------------------------------------------------------------------------

#endif
