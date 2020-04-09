// ZVConceptorReportOptions.h : header file

#if !defined(AFX_ZVCONCEPTORREPORTOPTIONS_H__4ADDB473_588E_4D04_AD86_146AE0FB649B__INCLUDED_)
#define AFX_ZVCONCEPTORREPORTOPTIONS_H__4ADDB473_588E_4D04_AD86_146AE0FB649B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JMR-MODIF - Le 6 mars 2006 - Ajout de l'en-tête ZWizard.h.
#include "zBaseLib\PSS_WizardDialog.h"

#include "Resources.h"

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// JMR-MODIF - Le 6 mars 2006 - Utilisation de ZIWizardDialog comme héritage plutôt que CDialog, et
// mise à jour de l'interface de la fenêtre de sélection pour correspondance avec le look général de Mercutio.

/////////////////////////////////////////////////////////////////////////////
// ZVConceptorReportOptions dialog

class ZVConceptorReportOptions : public PSS_WizardDialog
{
// Construction
public:

    // Standard constructor
    ZVConceptorReportOptions( CWnd* pParent = NULL );

    // Dialog Data
    //{{AFX_DATA(ZVConceptorReportOptions)
    enum { IDD = IDD_CONCEPTOR_REPORT };
    BOOL    m_Deliverables;
    BOOL    m_Detail;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVConceptorReportOptions)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Implementation
    // Generated message map functions
    //{{AFX_MSG(ZVConceptorReportOptions)
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif
