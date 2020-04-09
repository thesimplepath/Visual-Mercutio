/****************************************************************************
 * ==> PSS_ModelWorkflowOptionsWizard --------------------------------------*
 ****************************************************************************
 * Description : Provides a model workflow options wizard and its related   *
 *               dialog boxes                                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelWorkflowOptionsWizardH
#define PSS_ModelWorkflowOptionsWizardH

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"
#include "zWinUtil32\PSS_LanguageComboBox.h"

// resources
#include "Resources.h"

 // class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;

/**
* Model workflow options wizard
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowOptionsWizard
{
    public:
        /**
        * Dialogs data
        */
        typedef struct _IData
        {
            ELanguage m_Language;
            CString   m_CurrencySymbol;
            int       m_Notation;
            int       m_HourPerDay;
            int       m_DayPerWeek;
            int       m_DayPerMonth;
            int       m_DayPerYear;
            BOOL      m_Modify;
            BOOL      m_CheckConsistency;
            BOOL      m_IntegrateCostSimulation;
            BOOL      m_UseModelAsWorkflow;
            BOOL      m_BrowseInSameModel;
        } IData;

        /**
        * Constructor
        *@param modify - if TRUE, existing values will be get and shown for modification, otherwise default values will be shown
        *@param pDoc - the document for which options should be shown
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowOptionsWizard(BOOL modify, PSS_ProcessGraphModelDoc* pDoc, CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowOptionsWizard();

        /**
        * Gets the language
        *@return the language
        */
        virtual inline ELanguage GetLanguage() const;

        /**
        * Shows the wizard in modal mode
        *@return the modal result
        */
        virtual int DoModal();

    private:
        PSS_ProcessGraphModelDoc* m_pDoc;
        IData                     m_Data;
        BOOL                      m_Modify;
};

//---------------------------------------------------------------------------
// PSS_ModelWorkflowOptionsWizard
//---------------------------------------------------------------------------
ELanguage PSS_ModelWorkflowOptionsWizard::GetLanguage() const
{
    return m_Data.m_Language;
}
//---------------------------------------------------------------------------

/**
* Model workflow notation options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowNotationOptionsDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param[in, out] data - the document data to show, modified data on dialog ends
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowNotationOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& data, CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowNotationOptionsDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowNotationOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ModelWorkflowNotationOptionsDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_WZ_MODELTYPE_NOTATION
        };

        PSS_ModelWorkflowOptionsWizard::IData& m_Data;
        int                                    m_Notation;

        /**
        * Saves the dialog content to the data
        */
        void SaveToData();
};

/**
* Model workflow options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowOptionsDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param[in, out] data - the document data to show, modified data on dialog ends
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& data, CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowOptionsDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_ModelWorkflowOptionsDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnIntegrateCostsimulation();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_WZ_MODELTYPE_OPTIONS
        };

        PSS_ModelWorkflowOptionsWizard::IData& m_Data;
        PSS_LanguageComboBox                   m_LanguageCombo;
        BOOL                                   m_CheckConsistency;
        BOOL                                   m_IntegrateCostSimulation;
        BOOL                                   m_UseModelAsWorkflow;
        BOOL                                   m_BrowseInSameModel;

        /**
        * Saves the dialog content to the data
        */
        void SaveToData();

        /**
        * Checks the dialog states
        */
        void CheckStates();
};

/**
* Model workflow costs options dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ModelWorkflowCostsOptionsDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param[in, out] data - the document data to show, modified data on dialog ends
        *@param pParent - the parent window, can be NULL
        */
        PSS_ModelWorkflowCostsOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& Data, CWnd* pParent = NULL);

        virtual ~PSS_ModelWorkflowCostsOptionsDlg();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ModelWorkflowCostsOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ModelWorkflowCostsOptionsDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnNext();
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_WZ_MODELTYPE_COSTOPT
        };

        PSS_ModelWorkflowOptionsWizard::IData& m_Data;
        CComboBox                              m_CurrencySymbolCombo;
        CString                                m_DayPerMonth;
        CString                                m_DayPerWeek;
        CString                                m_DayPerYear;
        CString                                m_HourPerDay;

        /**
        * Saves the dialog content to the data
        */
        void SaveToData();

        /**
        * Checks the dialog states
        */
        bool CheckData();
};

#endif
