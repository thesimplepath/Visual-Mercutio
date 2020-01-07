/****************************************************************************
 * ==> PSS_RulesInfoDlg ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules information dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RulesInfoDlgH
#define PSS_RulesInfoDlgH

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
#include "zModelRes.h"

// class name mapping
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
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
* Rules information dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_RulesInfoDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param titleID - the title identifier
        *@param pLogicalRule - the logical rule
        *@param name - the name
        *@param description - the description
        *@param modifyMode - if true, the dialog will be shown in modification mode
        *@param pParent - the parent window, can be NULL
        */
        PSS_RulesInfoDlg(UINT                    titleID      = -1,
                         PSS_LogicalRulesEntity* pLogicalRule = NULL,
                         const CString&          name         = _T(""),
                         const CString&          description  = _T(""),
                         bool                    modifyMode   = false,
                         CWnd*                   pParent      = NULL);

        virtual ~PSS_RulesInfoDlg();

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Gets the description
        *@return the description
        */
        virtual inline CString GetDescription() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RulesInfoDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RulesInfoDlg)
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
            IDD = IDD_RULES_INFO
        };

        PSS_LogicalRulesEntity* m_pRule;
        CString                 m_Title;
        CString                 m_Name;
        CString                 m_Description;
        bool                    m_ModifyMode;
};

//---------------------------------------------------------------------------
// PSS_RulesInfoDlg
//---------------------------------------------------------------------------
CString PSS_RulesInfoDlg::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
CString PSS_RulesInfoDlg::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------

#endif
