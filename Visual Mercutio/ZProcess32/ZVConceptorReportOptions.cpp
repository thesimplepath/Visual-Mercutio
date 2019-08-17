// ZVConceptorReportOptions.cpp : implementation file

#include "stdafx.h"
#include "ZVConceptorReportOptions.h"

#include "zBaseLib\PSS_MsgBox.h"
#include ".\zvconceptorreportoptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// JMR-MODIF - Le 6 mars 2006 - Utilisation de ZIWizardDialog comme héritage plutôt que CDialog, et
// mise à jour de l'interface de la fenêtre de sélection pour correspondance avec le look général de Mercutio.

/////////////////////////////////////////////////////////////////////////////
// ZVConceptorReportOptions dialog

BEGIN_MESSAGE_MAP( ZVConceptorReportOptions, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVConceptorReportOptions)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVConceptorReportOptions::ZVConceptorReportOptions( CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog                ( ZVConceptorReportOptions::IDD,
                                      IDB_WIZ_REPORT,
                                      0,
                                      0,
                                      IDS_WZ_REPORTGENERATION_ST_S,
                                      IDS_WZ_REPORTGENERATION_ST_T )
//    : CDialog( ZVConceptorReportOptions::IDD, pParent )
{
    //{{AFX_DATA_INIT(ZVConceptorReportOptions)
    m_Deliverables = TRUE;
    m_Detail = TRUE;
    //}}AFX_DATA_INIT
}

void ZVConceptorReportOptions::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVConceptorReportOptions)
    DDX_Check(pDX, IDC_DELIVERABLE, m_Deliverables);
    DDX_Check(pDX, IDC_DETAIL, m_Detail);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVConceptorReportOptions message handlers

void ZVConceptorReportOptions::OnOK()
{
    UpdateData();

    if ( m_Deliverables == FALSE && m_Detail == FALSE )
    {
        // Warm the user
        PSS_MsgBox mBox;
        mBox.ShowMsgBox( IDS_ONEOPTIONREQUIRED, MB_OK );
        return;
    }

    ZIWizardDialog::OnOK();
}
