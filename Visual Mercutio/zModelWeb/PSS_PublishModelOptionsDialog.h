/****************************************************************************
 * ==> PSS_PublishModelOptionsDialog ---------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model options to publish *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_PublishModelOptionsDialogH
#define PSS_PublishModelOptionsDialogH

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
#include "zBaseLib\PSS_WizardDialog.h"
#include "zWinUtil32\PSS_LanguageComboBox.h"

// resources
#include "zModelWebRes.h"

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Dialog box allowing to select the model options to publish
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_PublishModelOptionsDialog : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param visualize - visualize option initial state
        *@param publishConceptorIsChecked - if true, publish conceptor option is checked
        *@param publishConceptorDetailsIsChecked - if true, publish conceptor details option is checked
        *@param publishConceptorDeliverablesIsChecked - if true, publish conceptor deliverables option is checked
        *@param publishProcessIsChecked - if true, publish process option is checked
        *@param publishRuleBookIsChecked - if true, publish rule book option is checked
        *@param initialLanguage - initial language
        *@param pParent - parent window, can be NULL
        */
        PSS_PublishModelOptionsDialog(BOOL      visualize                             = TRUE,
                                      BOOL      publishConceptorIsChecked             = TRUE,
                                      BOOL      publishConceptorDetailsIsChecked      = FALSE,
                                      BOOL      publishConceptorDeliverablesIsChecked = FALSE,
                                      BOOL      publishProcessIsChecked               = TRUE,
                                      BOOL      publishRuleBookIsChecked              = FALSE,
                                      ELanguage initialLanguage                       = ELanguage::E_LN_Unknown,
                                      CWnd*     pParent                               = NULL);

        /**
        * Gets the visualize option state
        *@return the visualize option state
        */
        virtual inline BOOL GetVisualize() const;

        /**
        * Gets the publish to conceptor option state
        *@return the publish to conceptor option state
        */
        virtual inline BOOL GetPublishConceptor() const;

        /**
        * Gets the publish details to conceptor option state
        *@return the publish details to conceptor option state
        */
        virtual inline BOOL GetPublishConceptorDetails() const;

        /**
        * Gets the publish deliverables to conceptor option state
        *@return the publish deliverables to conceptor option state
        */
        virtual inline BOOL GetPublishConceptorDeliverables() const;

        /**
        * Gets the publish process option state
        *@return the publish process option state
        */
        virtual inline BOOL GetPublishProcess() const;

        /**
        * Gets the publish rule book option state
        *@return the publish rule book option state
        */
        virtual inline BOOL GetPublishRuleBook() const;

        /**
        * Gets the language
        *@return the language
        */
        virtual inline ELanguage GetLanguage() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PublishModelOptionsDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_PublishModelOptionsDialog)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        afx_msg void OnBnClickedPublishConceptor();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_WZPUBMODEL_OPTIONS
        };

        PSS_LanguageComboBox m_CbLanguage;
        ELanguage            m_Language;
        BOOL                 m_Visualize;
        BOOL                 m_PublishConceptorIsChecked;
        BOOL                 m_PublishConceptorDetailsIsChecked;
        BOOL                 m_PublishConceptorDeliverablesIsChecked;
        BOOL                 m_PublishProcessIsChecked;
        BOOL                 m_PublishRuleBookIsChecked;
};

//---------------------------------------------------------------------------
// PSS_PublishModelOptionsDialog
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetVisualize() const
{
    return m_Visualize;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetPublishConceptor() const
{
    return m_PublishConceptorIsChecked;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetPublishConceptorDetails() const
{
    return m_PublishConceptorDetailsIsChecked;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetPublishConceptorDeliverables() const
{
    return m_PublishConceptorDeliverablesIsChecked;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetPublishProcess() const
{
    return m_PublishProcessIsChecked;
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::GetPublishRuleBook() const
{
    return m_PublishRuleBookIsChecked;
}
//---------------------------------------------------------------------------
ELanguage PSS_PublishModelOptionsDialog::GetLanguage() const
{
    return m_Language;
}
//---------------------------------------------------------------------------

#endif
