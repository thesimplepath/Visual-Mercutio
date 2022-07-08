/****************************************************************************
 * ==> PSS_ConceptorReportOptionsDlg ---------------------------------------*
 ****************************************************************************
 * Description : Provides a Conceptor report option dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ConceptorReportOptionsDlgH
#define PSS_ConceptorReportOptionsDlgH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_WizardDialog.h"

// resources
#include "resource.h"

/**
* Conceptor report option dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ConceptorReportOptionsDlg : public PSS_WizardDialog
{
    public:
        /**
        * Constructor
        *@param pParent - the parent window, can be NULL
        */
        PSS_ConceptorReportOptionsDlg(CWnd* pParent = NULL);

        virtual ~PSS_ConceptorReportOptionsDlg();

        /**
        * Gets the deliverables option state
        *@return the deliverables option state
        */
        virtual inline BOOL GetDeliverables() const;

        /**
        * Gets the details option state
        *@return the details option state
        */
        virtual inline BOOL GetDetails() const;

    protected:
        /**
        * Dialog Data
        */
        enum
        {
            IDD = IDD_CONCEPTOR_REPORT
        };

        BOOL m_Deliverables;
        BOOL m_Details;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ConceptorReportOptionsDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ConceptorReportOptionsDlg)
        virtual void OnOK();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_ConceptorReportOptionsDlg
//---------------------------------------------------------------------------
BOOL PSS_ConceptorReportOptionsDlg::GetDeliverables() const
{
    return m_Deliverables;
}
//---------------------------------------------------------------------------
BOOL PSS_ConceptorReportOptionsDlg::GetDetails() const
{
    return m_Details;
}
//---------------------------------------------------------------------------

#endif
