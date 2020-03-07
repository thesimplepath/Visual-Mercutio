/****************************************************************************
 * ==> PSS_RiskOptionsDlg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk options dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskOptionsDlgH
#define PSS_RiskOptionsDlgH

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

// mfc
#include "afxwin.h"

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
* Risk options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskOptionsDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param riskName - the risk name
        *@param riskDesc - the risk description
        *@param riskType - the risk type
        *@param riskImpact - the risk impact
        *@param riskProbability - the risk probability
        *@param riskUE - the risk unitary estimation
        *@param riskPOA - the risk annual operating loss (perte operationnelle annuelle in French)
        *@param riskAction - the risk action
        *@param currencySymbol - the currency symbol
        *@param pParent - the parent window, can be NULL
        */
        PSS_RiskOptionsDlg(const CString& riskName,
                           const CString& riskDesc,
                           const CString& riskType,
                           int            riskImpact,
                           int            riskProbability,
                           float          riskUE,
                           float          riskPOA,
                           bool           riskAction,
                           const CString& currencySymbol,
                           CWnd*          pParent = NULL);

        virtual ~PSS_RiskOptionsDlg();

        /**
        * Gets the risk title
        *@return the risk title
        */
        virtual CString GetRiskTitle() const;

        /**
        * Gets the risk description
        *@return the risk description
        */
        virtual CString GetRiskDescription() const;

        /**
        * Gets the risk type
        *@return the risk type
        */
        virtual CString GetRiskType() const;

        /**
        * Gets the risk impact
        *@return the risk impact
        */
        virtual int GetRiskImpact() const;

        /**
        * Gets the risk probability
        *@return the risk probability
        */
        virtual int GetRiskProbability() const;

        /**
        * Gets the risk severity
        *@return the risk severity
        */
        virtual int GetRiskSeverity() const;

        /**
        * Gets the risk unitary estimation
        *@return the risk unitary estimation
        */
        virtual float GetRiskUE() const;

        /**
        * Gets the risk annual operating loss (perte operationnelle annuelle in French)
        *@return the risk annual operating loss (perte operationnelle annuelle in French)
        */
        virtual float GetRiskPOA() const;

        /**
        * Gets the risk action
        *@return the risk action
        */
        virtual bool GetRiskAction() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RiskOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RiskOptionsDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnCbnSelchangeRiskImpact();
        afx_msg void OnCbnSelchangeRiskProbability();
        afx_msg void OnBnClickedModifyRiskType();
        afx_msg void OnBnClickedOpenRiskType();
        afx_msg void OnBnClickedModifyRiskImpact();
        afx_msg void OnBnClickedModifyRiskProbability();
        afx_msg void OnBnClickedOpenRiskImpact();
        afx_msg void OnBnClickedOpenRiskProbability();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_RISK_OPTIONS
        };

        CComboBox m_RiskImpactCtrl;
        CComboBox m_RiskProbabilityCtrl;
        CComboBox m_RiskTypeCtrl;
        CStatic   m_RiskSeverityCtrl;
        CStatic   m_UEFrsLabelCtrl;
        CStatic   m_POAFrsLabelCtrl;
        CString   m_RiskName;
        CString   m_RiskDesc;
        CString   m_RiskType;
        CString   m_CurrencySymbol;
        float     m_RiskUE;
        float     m_RiskPOA;
        int       m_RiskImpact;
        int       m_RiskProbability;
        BOOL      m_RiskAction;

        /**
        * Gets the impact index
        *@return the impact index
        */
        int GetImpactIndex() const;

        /**
        * Gets the probability index
        *@return the probability index
        */
        int GetProbabilityIndex() const;

        /**
        * Loads the type list
        */
        void LoadTypeList();

        /**
        * Loads the impact list
        */
        void LoadImpactList();

        /**
        * Loads the probability list
        */
        void LoadProbabilityList();

        /**
        * Updates the severity
        */
        void UpdateSeverity();

        /**
        * Selects a file to open
        *@param dir - the initial dir
        *@param caption - the search dialog caption
        *@param extension - the extension
        *@param fileName - the file name
        */
        void SelectFileToOpen(const CString& dir, const CString& caption, const CString& extension, CString& fileName);

        /**
        * Reloads the type file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ReloadTypeFile(const CString& fileName);

        /**
        * Reloads the impact file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ReloadImpactFile(const CString& fileName);

        /**
        * Reloads the probability file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ReloadProbabilityFile(const CString& fileName);
};

#endif
