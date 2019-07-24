// MdlWkfOpt.cpp : implementation file

#include "stdafx.h"
#include "MdlWkfOpt.h"

// processsoft
#include "zModel\ProcGraphModelDoc.h"
#include "zBaseLib\ZAGlobal.h"
#include "zBaseLib\MsgBox.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 18 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptions class

ZVModelWorkflowOptions::ZVModelWorkflowOptions( BOOL Modify, ZDProcessGraphModelDoc* pDoc, CWnd* pParent /*=NULL*/ )
    : m_Modify    ( Modify ),
      m_pDoc    ( pDoc )
{
}

int ZVModelWorkflowOptions::DoModal()
{
    // Initialize dialog data
    m_Data.m_Modify = m_Modify;

    // If in modification, retrieve values,
    // otherwise sets default values
    if ( m_Modify )
    {
        m_Data.m_UseModelAsWorkflow    = m_pDoc->GetUseWorkflow();
        m_Data.m_CheckConsistency    = m_pDoc->GetCheckConsistency();

        switch ( m_pDoc->GetNotation() )
        {
            case E_MN_Beryl:
            {
                m_Data.m_Notation = 0;
                break;
            }

            case E_MN_ABC:
            {
                m_Data.m_Notation = 1;
                break;
            }

            case E_MN_UML:
            {
                m_Data.m_Notation = 2;
                break;
            }

            case E_MN_Unknown:
            default:
            {
                m_Data.m_Notation = 3;
                break;
            }
        }

        m_Data.m_IntegrateCostSimulation    = m_pDoc->GetIntegrateCostSimulation();
        m_Data.m_BrowseInSameModel            = m_pDoc->BrowseInSameWindow();
        m_Data.m_HourPerDay                    = m_pDoc->GetHourPerDay();
        m_Data.m_DayPerWeek                    = m_pDoc->GetDayPerWeek();
        m_Data.m_DayPerMonth                = m_pDoc->GetDayPerMonth();
        m_Data.m_DayPerYear                    = m_pDoc->GetDayPerYear();
        m_Data.m_CurrencySymbol                = m_pDoc->GetCurrencySymbol();
        m_Data.m_Language                    = m_pDoc->GetLanguage();
    }
    else
    {
        m_Data.m_UseModelAsWorkflow            = TRUE;
        m_Data.m_CheckConsistency            = TRUE;
        m_Data.m_Notation                    = 0;
        m_Data.m_IntegrateCostSimulation    = TRUE;
        m_Data.m_BrowseInSameModel            = TRUE;

        m_Data.m_HourPerDay                    = 8;
        m_Data.m_DayPerWeek                    = 5;
        m_Data.m_DayPerMonth                = 22;
        m_Data.m_DayPerYear                    = 220;
        m_Data.m_CurrencySymbol                = ZAGlobal::GetLocaleCurrency();

        // set the French language as default
        m_Data.m_Language = E_LN_French;
    }

    // The notation can't be modified in modification mode
    if ( !m_Modify )
    {
        ZVModelWorkflowOptionsNotation Notation( m_Data );

        if ( Notation.DoModal() == IDCANCEL )
        {
            return IDCANCEL;
        }
    }

    ZVModelWorkflowOptionsOptions Options( m_Data );

    int Ret;

    if ( ( Ret = Options.DoModal() ) == IDCANCEL )
    {
        return IDCANCEL;
    }

    if ( Ret == IDNEXT )
    {
        ZVModelWorkflowOptionsCosts Costs( m_Data );

        if ( Costs.DoModal() == IDCANCEL )
        {
            return IDCANCEL;
        }
    }

    // Save options
    m_pDoc->SetUseWorkflow( m_Data.m_UseModelAsWorkflow );
    m_pDoc->SetCheckConsistency( m_Data.m_CheckConsistency );

    switch ( m_Data.m_Notation )
    {
        case 0:
        {
            m_pDoc->SetNotation(E_MN_Beryl);
            break;
        }

        case 1:
        {
            m_pDoc->SetNotation(E_MN_ABC);
            break;
        }

        case 2:
        {
            m_pDoc->SetNotation(E_MN_UML);
            break;
        }

        case 3:
        default:
        {
            m_pDoc->SetNotation(E_MN_Unknown);
            break;
        }
    }

    m_pDoc->SetIntegrateCostSimulation( m_Data.m_IntegrateCostSimulation );
    m_pDoc->SetBrowseInSameWindow ( m_Data.m_BrowseInSameModel );

    m_pDoc->SetHourPerDay( m_Data.m_HourPerDay );
    m_pDoc->SetDayPerWeek( m_Data.m_DayPerWeek );
    m_pDoc->SetDayPerMonth( m_Data.m_DayPerMonth );
    m_pDoc->SetDayPerYear( m_Data.m_DayPerYear );
    m_pDoc->SetCurrencySymbol( m_Data.m_CurrencySymbol );

    m_pDoc->SetLanguage( m_Data.m_Language );

    return IDOK;
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsNotation dialog

BEGIN_MESSAGE_MAP( ZVModelWorkflowOptionsNotation, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVModelWorkflowOptionsNotation)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVModelWorkflowOptionsNotation::ZVModelWorkflowOptionsNotation( MODELOPTIONDATA& Data, CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog    ( ZVModelWorkflowOptionsNotation::IDD,
                          IDB_WZBMP1,
                          0,
                          0,
                          IDS_WZ_MODELNOTATION_S,
                          IDS_WZ_MODELNOTATION_T ),
      m_Data            ( Data )
{
    //{{AFX_DATA_INIT(ZVModelWorkflowOptionsNotation)
    m_Notation = m_Data.m_Notation;
    //}}AFX_DATA_INIT
}

void ZVModelWorkflowOptionsNotation::SaveToData()
{
    UpdateData( TRUE );
    m_Data.m_Notation = m_Notation;
}

ZVModelWorkflowOptionsNotation::~ZVModelWorkflowOptionsNotation()
{
}

void ZVModelWorkflowOptionsNotation::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVModelWorkflowOptionsNotation)
    DDX_Radio(pDX, IDC_MODEL_NOTATION, m_Notation);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsNotation message handlers

BOOL ZVModelWorkflowOptionsNotation::OnInitDialog()
{
    BOOL RetValue = ZIWizardDialog::OnInitDialog();

    if ( GetDlgItem( IDOK ) && m_Data.m_Modify == FALSE )
    {
        GetDlgItem( IDOK )->ShowWindow( SW_HIDE );
    }

    return RetValue;
}

void ZVModelWorkflowOptionsNotation::OnOK()
{
    SaveToData();
    ZIWizardDialog::OnOK();
}

void ZVModelWorkflowOptionsNotation::OnNext()
{
    SaveToData();
    EndDialog( IDNEXT );
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsOptions dialog

BEGIN_MESSAGE_MAP( ZVModelWorkflowOptionsOptions, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVModelWorkflowOptionsOptions)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_BN_CLICKED(IDC_INTEGRATE_COSTSIMULATION, OnIntegrateCostsimulation)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVModelWorkflowOptionsOptions::ZVModelWorkflowOptionsOptions( MODELOPTIONDATA& Data, CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog    ( ZVModelWorkflowOptionsOptions::IDD,
                          IDB_WZBMP1,
                          0,
                          0,
                          IDS_WZ_MODELPARAM_S,
                          IDS_WZ_MODELPARAM_T ),
      m_Data            ( Data )
{
    //{{AFX_DATA_INIT(ZVModelWorkflowOptionsOptions)
    m_CheckConsistency = m_Data.m_CheckConsistency;
    m_IntegrateCostSimulation = m_Data.m_IntegrateCostSimulation;
    m_UseModelAsWorkflow = m_Data.m_UseModelAsWorkflow;
    m_BrowseInSameModel = m_Data.m_BrowseInSameModel;
    //}}AFX_DATA_INIT
}

ZVModelWorkflowOptionsOptions::~ZVModelWorkflowOptionsOptions()
{
}

void ZVModelWorkflowOptionsOptions::SaveToData()
{
    UpdateData( TRUE );

    m_Data.m_CheckConsistency            = m_CheckConsistency;
    m_Data.m_IntegrateCostSimulation    = m_IntegrateCostSimulation;
    m_Data.m_UseModelAsWorkflow            = m_UseModelAsWorkflow;
    m_Data.m_BrowseInSameModel            = m_BrowseInSameModel;

    // Saves the language selected
    m_Data.m_Language = m_cbLanguage.GetLanguage();
}

void ZVModelWorkflowOptionsOptions::CheckStates()
{
    // Enable the next button function of the cost simulation states
    if ( GetDlgItem( IDNEXT ) && GetDlgItem( IDOK ) )
    {
        GetDlgItem( IDNEXT )->EnableWindow( m_IntegrateCostSimulation );

        if ( m_IntegrateCostSimulation )
        {
            SetDefID( IDNEXT );
        }
        else
        {
            SetDefID( IDOK );
        }
    }
}

void ZVModelWorkflowOptionsOptions::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVModelWorkflowOptionsOptions)
    DDX_Control(pDX, IDC_MODEL_LANGUAGE, m_cbLanguage);
    DDX_Check(pDX, IDC_CHECKMODEL_CONSISTENCY, m_CheckConsistency);
    DDX_Check(pDX, IDC_INTEGRATE_COSTSIMULATION, m_IntegrateCostSimulation);
    DDX_Check(pDX, IDC_USEMODEL_ASWORKFLOW, m_UseModelAsWorkflow);
    DDX_Check(pDX, IDC_BROWSEMODEL_INSAMEWINDOW, m_BrowseInSameModel);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsOptions message handlers

BOOL ZVModelWorkflowOptionsOptions::OnInitDialog()
{
    BOOL RetValue = ZIWizardDialog::OnInitDialog();

    switch ( m_Data.m_Notation )
    {
        case 0:
        {
            break;
        }

        case 1:
        {
            if ( GetDlgItem( IDC_CHECKMODEL_CONSISTENCY ) )
            {
                GetDlgItem( IDC_CHECKMODEL_CONSISTENCY )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_USEMODEL_ASWORKFLOW ) )
            {
                GetDlgItem( IDC_USEMODEL_ASWORKFLOW )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_INTEGRATE_COSTSIMULATION ) )
            {
                GetDlgItem( IDC_INTEGRATE_COSTSIMULATION )->EnableWindow( FALSE );
            }

            break;
        }

        case 2:
        {
            if ( GetDlgItem( IDC_CHECKMODEL_CONSISTENCY ) )
            {
                GetDlgItem( IDC_CHECKMODEL_CONSISTENCY )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_USEMODEL_ASWORKFLOW ) )
            {
                GetDlgItem( IDC_USEMODEL_ASWORKFLOW )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_INTEGRATE_COSTSIMULATION ) )
            {
                GetDlgItem( IDC_INTEGRATE_COSTSIMULATION )->EnableWindow( FALSE );
            }

            break;
        }

        case 3:
        default:
        {
            if ( GetDlgItem( IDC_CHECKMODEL_CONSISTENCY ) )
            {
                GetDlgItem( IDC_CHECKMODEL_CONSISTENCY )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_USEMODEL_ASWORKFLOW ) )
            {
                GetDlgItem( IDC_USEMODEL_ASWORKFLOW )->EnableWindow( FALSE );
            }

            if ( GetDlgItem( IDC_INTEGRATE_COSTSIMULATION ) )
            {
                GetDlgItem( IDC_INTEGRATE_COSTSIMULATION )->EnableWindow( FALSE );
            }

            break;
        }
    }

    // Initialize the language combo-box
    m_cbLanguage.Initialize( m_Data.m_Language );

    CheckStates();

    return RetValue;
}

void ZVModelWorkflowOptionsOptions::OnIntegrateCostsimulation() 
{
    UpdateData();
    CheckStates();
}

void ZVModelWorkflowOptionsOptions::OnOK()
{
    SaveToData();
    ZIWizardDialog::OnOK();
}

void ZVModelWorkflowOptionsOptions::OnNext()
{
    SaveToData();
    EndDialog( IDNEXT );
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsCosts dialog

BEGIN_MESSAGE_MAP( ZVModelWorkflowOptionsCosts, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVModelWorkflowOptionsCosts)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVModelWorkflowOptionsCosts::ZVModelWorkflowOptionsCosts( MODELOPTIONDATA& Data, CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog    ( ZVModelWorkflowOptionsCosts::IDD,
                          IDB_WZBMP1,
                          0,
                          0,
                          IDS_WZ_MODELCOSTS_S,
                          IDS_WZ_MODELCOSTS_T ),
      m_Data            ( Data )
{
    //{{AFX_DATA_INIT(ZVModelWorkflowOptionsCosts)
    m_DayPerMonth.Format( "%d", m_Data.m_DayPerMonth );
    m_DayPerWeek.Format( "%d", m_Data.m_DayPerWeek );
    m_DayPerYear.Format( "%d", m_Data.m_DayPerYear );
    m_HourPerDay.Format( "%d", m_Data.m_HourPerDay );
    //}}AFX_DATA_INIT
}

void ZVModelWorkflowOptionsCosts::SaveToData()
{
    UpdateData( TRUE );

    m_Data.m_HourPerDay        = atoi( m_HourPerDay );
    m_Data.m_DayPerWeek        = atoi( m_DayPerWeek );
    m_Data.m_DayPerMonth    = atoi( m_DayPerMonth );
    m_Data.m_DayPerYear        = atoi( m_DayPerYear );
    
    // Initialize text with the previous value
    CString Text            = m_Data.m_CurrencySymbol;
    int Index                = m_CurrencySymbol.GetCurSel();

    // If no error, retreive the text
    if ( Index != CB_ERR )
    {
        m_CurrencySymbol.GetLBText( Index, Text );
    }

    m_Data.m_CurrencySymbol = Text;
}

bool ZVModelWorkflowOptionsCosts::CheckData()
{
    UpdateData( TRUE );

    // Check the currency symbol
    CString Text;

    // First, check if the text entered is already in the list
    m_CurrencySymbol.GetWindowText( Text );

    if ( Text.IsEmpty() )
    {
        // Warm the user
    }
    else
    {
        if ( m_CurrencySymbol.FindStringExact( -1, Text ) == CB_ERR )
        {
            m_CurrencySymbol.InsertString( 0, Text );
            m_CurrencySymbol.SelectString( -1, Text );
        }
        else
        {
            int Index = m_CurrencySymbol.GetCurSel();

            // If no error, retreive the text
            if ( Index == CB_ERR )
            {
                // Warm the user
                return false;
            }

            m_CurrencySymbol.GetLBText( Index, Text );

            if ( Text.IsEmpty() )
            {
                // Warm the user
            }
        }
    }

    return true;
}

void ZVModelWorkflowOptionsCosts::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVModelWorkflowOptionsCosts)
    DDX_Control(pDX, IDC_CURRENCY_SYMBOL, m_CurrencySymbol);
    DDX_Text(pDX, IDC_DAY_PERMONTH, m_DayPerMonth);
    DDX_Text(pDX, IDC_DAY_PERWEEK, m_DayPerWeek);
    DDX_Text(pDX, IDC_DAY_PERYEAR, m_DayPerYear);
    DDX_Text(pDX, IDC_HOUR_PERDAY, m_HourPerDay);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowOptionsCosts message handlers

BOOL ZVModelWorkflowOptionsCosts::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();
    
    m_CurrencySymbol.AddString( m_Data.m_CurrencySymbol );

    if ( m_CurrencySymbol.FindStringExact( -1, _T( "$" ) ) == CB_ERR )
    {
        m_CurrencySymbol.AddString( _T( "$" ) );
    }

    if ( m_CurrencySymbol.FindStringExact( -1, _T( "£" ) ) == CB_ERR )
    {
        m_CurrencySymbol.AddString( _T( "£" ) );
    }

    if ( m_CurrencySymbol.FindStringExact( -1, _T( "€" ) ) == CB_ERR )
    {
        m_CurrencySymbol.AddString( _T( "€" ) );
    }

    // Now selects the CurrencySymbol
    if ( m_CurrencySymbol.SelectString( -1, m_Data.m_CurrencySymbol ) == CB_ERR )
    {
        // If error selecting the symbol, selects the first element
        m_CurrencySymbol.SetCurSel( 0 );
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVModelWorkflowOptionsCosts::OnOK()
{
    if ( !CheckData() )
    {
        return;
    }

    SaveToData();
    ZIWizardDialog::OnOK();
}

void ZVModelWorkflowOptionsCosts::OnNext()
{
    if ( !CheckData() )
    {
        return;
    }

    SaveToData();
    EndDialog( IDNEXT );
}
