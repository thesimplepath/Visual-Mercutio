/****************************************************************************
 * ==> PSS_SelectRuleDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a rule dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SelectRuleDlgH
#define PSS_SelectRuleDlgH

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
#include "PSS_RulesTreeCtrl.h"

// resources
#include "zModelRes.h"

// class name mapping
#ifndef PSS_RulesEntity
    #define PSS_RulesEntity ZBRulesEntity
#endif
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class PSS_RulesEntity;
class PSS_LogicalRulesEntity;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Select rule dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SelectRuleDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param title - the title
        *@param pMainRule - the main rule
        *@param pPageToRename - the page to rename
        *@param allowRuleSelection - if true, the rule selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectRuleDlg(const CString&          title              = _T(""),
                          PSS_LogicalRulesEntity* pMainRule          = NULL,
                          bool                    allowRuleSelection = true,
                          CWnd*                   pParent            = NULL);

        /**
        * Constructor
        *@param title - the title resource identifier
        *@param pMainRule - the main rule
        *@param pPageToRename - the page to rename
        *@param allowRuleSelection - if true, the rule selection is allowed
        *@param pParent - parent window, can be NULL
        */
        PSS_SelectRuleDlg(UINT                    titleID,
                          PSS_LogicalRulesEntity* pMainRule,
                          bool                    allowRuleSelection = true,
                          CWnd*                   pParent            = NULL);

        virtual ~PSS_SelectRuleDlg();

        /**
        * Release the dialog box content
        */
        virtual void Release();

        /**
        * Gets the selected rule entity
        *@return the selected rule entity
        */
        virtual inline PSS_RulesEntity* GetSelectedRuleEntity() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SelectRuleDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SelectRuleDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSelchangedRulesTree(NMHDR* pNMHDR, LRESULT* pResult);
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_RULE_SELECTION
        };

        PSS_RulesEntity*        m_pRuleEntity;
        PSS_LogicalRulesEntity* m_pMainRule;
        PSS_RulesTreeCtrl       m_Ctrl;
        CString                 m_Title;
        bool                    m_AllowRuleSelection;
};

//---------------------------------------------------------------------------
// PSS_SelectRuleDlg
//---------------------------------------------------------------------------
PSS_RulesEntity* PSS_SelectRuleDlg::GetSelectedRuleEntity() const
{
    return m_pRuleEntity;
}
//---------------------------------------------------------------------------

#endif
