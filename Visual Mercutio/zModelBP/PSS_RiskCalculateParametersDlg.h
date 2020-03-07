/****************************************************************************
 * ==> PSS_RiskCalculateParametersDlg --------------------------------------*
 ****************************************************************************
 * Description : Provides a calculate risk parameters dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskCalculateParametersDlgH
#define PSS_RiskCalculateParametersDlgH

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
#include "afxcmn.h"

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
* Calculate risk parameters dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskCalculateParametersDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param iniFileName - the ini file name
        *@param currencySymbol - the currency symbol
        *@param pParent - the parent window, can be NULL
        */
        PSS_RiskCalculateParametersDlg(const CString& iniFileName,
                                       const CString& currencySymbol,
                                       CWnd*          pParent = NULL);

        /**
        * Gets the orange severity level
        *@return the orange severity level
        */
        virtual int GetOrangeSeverityLevel();

        /**
        * Gets the red severity level
        *@return the red severity level
        */
        virtual int GetRedSeverityLevel();

        /**
        * Gets the orange unitary estimation
        *@return the orange unitary estimation
        */
        virtual float GetOrangeUE();

        /**
        * Gets the red unitary estimation
        *@return the red unitary estimation
        */
        virtual float GetRedUE();

        /**
        * Gets the orange the orange annual operating loss (perte operationnelle annuelle in French)
        *@return the orange the orange annual operating loss (perte operationnelle annuelle in French)
        */
        virtual float GetOrangePOA();

        /**
        * Gets the red the orange annual operating loss (perte operationnelle annuelle in French)
        *@return the red the orange annual operating loss (perte operationnelle annuelle in French)
        */
        virtual float GetRedPOA();

        /**
        * Checks if the orange action is enabled
        *@return TRUE if the orange action is enabled, otherwise FALSE
        */
        virtual BOOL IsOrangeActionEnabled();

        /**
        * Checks if the orange no action is enabled
        *@return TRUE if the orange no action is enabled, otherwise FALSE
        */
        virtual BOOL IsOrangeNoActionEnabled();

        /**
        * Checks if the red action is enabled
        *@return TRUE if the red action is enabled, otherwise FALSE
        */
        virtual BOOL IsRedActionEnabled();

        /**
        * Checks if the rd no action is enabled
        *@return TRUE if the red no action is enabled, otherwise FALSE
        */
        virtual BOOL IsRedNoActionEnabled();

        /**
        * Checks if the default colors are enabled
        *@return TRUE if the default colors are enabled, otherwise FALSE
        */
        virtual BOOL IsDefaultColorsEnabled();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_RiskCalculateParametersDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_RiskCalculateParametersDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNMReleasedcaptureOrangeSeverity(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg void OnNMReleasedcaptureRedSeverity(NMHDR *pNMHDR, LRESULT *pResult);
        afx_msg void OnBnClickedOrangeAction();
        afx_msg void OnBnClickedOrangeNoAction();
        afx_msg void OnBnClickedRedAction();
        afx_msg void OnBnClickedRedNoAction();
        afx_msg void OnBnClickedOk();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_RISK_CALCULATE_PARAMETERS
        };

        CSliderCtrl m_OrangeSeverityCtrl;
        CSliderCtrl m_RedSeverityCtrl;
        CStatic     m_OrangeLevelCtrl;
        CStatic     m_RedLevelCtrl;
        CStatic     m_OrangeUEFrsLabelCtrl;
        CStatic     m_OrangePOAFrsLabelCtrl;
        CStatic     m_RedUEFrsLabelCtrl;
        CStatic     m_RedPOAFrsLabelCtrl;
        CButton     m_OrangeActionCtrl;
        CButton     m_RedActionCtrl;
        CButton     m_OrangeNoActionCtrl;
        CButton     m_RedNoActionCtrl;
        CButton     m_OKCtrl;
        CString     m_IniFileName;
        CString     m_CurrencySymbol;
        float       m_OrangeUE;
        float       m_OrangePOA;
        float       m_RedUE;
        float       m_RedPOA;
        int         m_OrangeSeverity;
        int         m_RedSeverity;
        BOOL        m_OrangeAction;
        BOOL        m_OrangeNoAction;
        BOOL        m_RedAction;
        BOOL        m_RedNoAction;
        BOOL        m_DefaultColors;
        BOOL        m_OrangeActionChecked;
        BOOL        m_OrangeNoActionChecked;

        /**
        * Updates the orange level
        */
        void UpdateOrangeLevel();

        /**
        * Updates the red level
        */
        void UpdateRedLevel();

        /**
        * Updates the Ok button
        */
        void UpdateOKButton();

        /**
        * Loads the states from the ini file
        *@return true on success, otherwise false
        */
        bool LoadStateFromIniFile();

        /**
        * Saves the states to the ini file
        *@return true on success, otherwise false
        */
        bool SaveStateToIniFile();
};

#endif
