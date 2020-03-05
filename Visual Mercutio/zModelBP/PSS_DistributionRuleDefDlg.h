/****************************************************************************
 * ==> PSS_DistributionRuleDefDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides a distribution rule definition dialog box         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DistributionRuleDefDlgH
#define PSS_DistributionRuleDefDlgH

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
#include "zModelBP\zModelBPRes.h"

// old class name mapping
#ifndef PSS_DistributionRule
    #define PSS_DistributionRule ZBDistributionRule
#endif

// forward class declaration
class PSS_DistributionRule;

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
* Distribution rule definition dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DistributionRuleDefDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param pRule - the distribution rule
        *@param pParent - the parent window, can be NULL
        */
        PSS_DistributionRuleDefDlg(PSS_DistributionRule* pRule = NULL, CWnd* pParent = NULL);

        virtual ~PSS_DistributionRuleDefDlg();

        /**
        * Gets the operator
        *@return the operator
        */
        virtual inline int GetOperator() const;

        /**
        * Gets the logical operator
        *@return the logical operator
        */
        virtual inline int GetLogicalOperator() const;

        /**
        * Gets the value
        *@return the value
        */
        virtual inline CString GetValue() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DistributionRuleDefDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DistributionRuleDefDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_DISTRIBUTIONRULE_DEF
        };

        PSS_DistributionRule* m_pRule;
        CString               m_Value;
        int                   m_Operator;
        int                   m_LogicalOperator;
};

//---------------------------------------------------------------------------
// PSS_DistributionRuleDefDlg
//---------------------------------------------------------------------------
int PSS_DistributionRuleDefDlg::GetOperator() const
{
    return m_Operator;
}
//---------------------------------------------------------------------------
int PSS_DistributionRuleDefDlg::GetLogicalOperator() const
{
    return m_LogicalOperator;
}
//---------------------------------------------------------------------------
CString PSS_DistributionRuleDefDlg::GetValue() const
{
    return m_Value;
}
//---------------------------------------------------------------------------

#endif
