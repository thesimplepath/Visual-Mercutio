// ZVEqualizeQuantityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVEqualizeQuantityDlg.h"

// processsoft
#include "PSS_AnnualNumberPropertiesBP.h"

// resources
#include "zBaseLib\PSS_Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char szFormatNumbers[] = "%.0f";

/////////////////////////////////////////////////////////////////////////////
// ZVEqualizeQuantityDlg dialog


ZVEqualizeQuantityDlg::ZVEqualizeQuantityDlg(ZBPropertySet* pPropertySet /*= NULL*/, CWnd* pParent /*=NULL*/)
    : CDialog(ZVEqualizeQuantityDlg::IDD, pParent),
      m_pPropertySet(pPropertySet)
{
    //{{AFX_DATA_INIT(ZVEqualizeQuantityDlg)
    m_LockApril = FALSE;
    m_LockAugust = FALSE;
    m_LockDecember = FALSE;
    m_LockFebruary = FALSE;
    m_LockJanuary = FALSE;
    m_LockJuly = FALSE;
    m_LockJune = FALSE;
    m_LockMarch = FALSE;
    m_LockMay = FALSE;
    m_LockNovember = FALSE;
    m_LockOctober = FALSE;
    m_LockSeptember = FALSE;
    m_LockYear = FALSE;
    m_QuantityApril = _T("");
    m_QuantityAugust = _T("");
    m_QuantityDecember = _T("");
    m_QuantityFebruary = _T("");
    m_QuantityJanuary = _T("");
    m_QuantityJuly = _T("");
    m_QuantityJune = _T("");
    m_QuantityMarch = _T("");
    m_QuantityMay = _T("");
    m_QuantityNovember = _T("");
    m_QuantityOctober = _T("");
    m_QuantitySeptember = _T("");
    m_QuantityYear = _T("");
    m_ForceEqualizer = FALSE;
    //}}AFX_DATA_INIT
}


void ZVEqualizeQuantityDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVEqualizeQuantityDlg)
    DDX_Control(pDX, IDC_SEP_ACT_SLIDER, m_SliderSeptember);
    DDX_Control(pDX, IDC_OCT_ACT_SLIDER, m_SliderOctober);
    DDX_Control(pDX, IDC_NOV_ACT_SLIDER, m_SliderNovember);
    DDX_Control(pDX, IDC_MAY_ACT_SLIDER, m_SliderMay);
    DDX_Control(pDX, IDC_MAR_ACT_SLIDER, m_SliderMarch);
    DDX_Control(pDX, IDC_JUN_ACT_SLIDER, m_SliderJune);
    DDX_Control(pDX, IDC_JUL_ACT_SLIDER, m_SliderJuly);
    DDX_Control(pDX, IDC_JAN_ACT_SLIDER, m_SliderJanuary);
    DDX_Control(pDX, IDC_FEB_ACT_SLIDER, m_SliderFebruary);
    DDX_Control(pDX, IDC_DEC_ACT_SLIDER, m_SliderDecember);
    DDX_Control(pDX, IDC_AUG_ACT_SLIDER, m_SliderAugust);
    DDX_Control(pDX, IDC_APR_ACT_SLIDER, m_SliderApril);
    DDX_Check(pDX, IDC_APR_ACT_LOCK, m_LockApril);
    DDX_Check(pDX, IDC_AUG_ACT_LOCK, m_LockAugust);
    DDX_Check(pDX, IDC_DEC_ACT_LOCK, m_LockDecember);
    DDX_Check(pDX, IDC_FEB_ACT_LOCK, m_LockFebruary);
    DDX_Check(pDX, IDC_JAN_ACT_LOCK, m_LockJanuary);
    DDX_Check(pDX, IDC_JUL_ACT_LOCK, m_LockJuly);
    DDX_Check(pDX, IDC_JUN_ACT_LOCK, m_LockJune);
    DDX_Check(pDX, IDC_MAR_ACT_LOCK, m_LockMarch);
    DDX_Check(pDX, IDC_MAY_ACT_LOCK, m_LockMay);
    DDX_Check(pDX, IDC_NOV_ACT_LOCK, m_LockNovember);
    DDX_Check(pDX, IDC_OCT_ACT_LOCK, m_LockOctober);
    DDX_Check(pDX, IDC_SEP_ACT_LOCK, m_LockSeptember);
    DDX_Check(pDX, IDC_YEAR_ACT_LOCK, m_LockYear);
    DDX_Text(pDX, IDC_APR_ACTIVATION, m_QuantityApril);
    DDX_Text(pDX, IDC_AUG_ACTIVATION, m_QuantityAugust);
    DDX_Text(pDX, IDC_DEC_ACTIVATION, m_QuantityDecember);
    DDX_Text(pDX, IDC_FEB_ACTIVATION, m_QuantityFebruary);
    DDX_Text(pDX, IDC_JAN_ACTIVATION, m_QuantityJanuary);
    DDX_Text(pDX, IDC_JUL_ACTIVATION, m_QuantityJuly);
    DDX_Text(pDX, IDC_JUN_ACTIVATION, m_QuantityJune);
    DDX_Text(pDX, IDC_MAR_ACTIVATION, m_QuantityMarch);
    DDX_Text(pDX, IDC_MAY_ACTIVATION, m_QuantityMay);
    DDX_Text(pDX, IDC_NOV_ACTIVATION, m_QuantityNovember);
    DDX_Text(pDX, IDC_OCT_ACTIVATION, m_QuantityOctober);
    DDX_Text(pDX, IDC_SEP_ACTIVATION, m_QuantitySeptember);
    DDX_Text(pDX, IDC_TOTAL_ACTIVATION, m_QuantityYear);
    DDX_Check(pDX, IDC_FORCE_EQUALIZER, m_ForceEqualizer);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVEqualizeQuantityDlg, CDialog)
    //{{AFX_MSG_MAP(ZVEqualizeQuantityDlg)
    ON_BN_CLICKED(IDC_APR_ACT_LOCK, OnAprActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_APR_ACT_SLIDER, OnReleasedcaptureAprActSlider)
    ON_EN_CHANGE(IDC_APR_ACTIVATION, OnChangeAprActivation)
    ON_BN_CLICKED(IDC_AUG_ACT_LOCK, OnAugActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_AUG_ACT_SLIDER, OnReleasedcaptureAugActSlider)
    ON_EN_CHANGE(IDC_AUG_ACTIVATION, OnChangeAugActivation)
    ON_BN_CLICKED(IDC_DEC_ACT_LOCK, OnDecActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_DEC_ACT_SLIDER, OnReleasedcaptureDecActSlider)
    ON_EN_CHANGE(IDC_DEC_ACTIVATION, OnChangeDecActivation)
    ON_BN_CLICKED(IDC_FEB_ACT_LOCK, OnFebActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FEB_ACT_SLIDER, OnReleasedcaptureFebActSlider)
    ON_EN_CHANGE(IDC_FEB_ACTIVATION, OnChangeFebActivation)
    ON_BN_CLICKED(IDC_JAN_ACT_LOCK, OnJanActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_JAN_ACT_SLIDER, OnReleasedcaptureJanActSlider)
    ON_EN_CHANGE(IDC_JAN_ACTIVATION, OnChangeJanActivation)
    ON_BN_CLICKED(IDC_JUL_ACT_LOCK, OnJulActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_JUL_ACT_SLIDER, OnReleasedcaptureJulActSlider)
    ON_EN_CHANGE(IDC_JUL_ACTIVATION, OnChangeJulActivation)
    ON_BN_CLICKED(IDC_JUN_ACT_LOCK, OnJunActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_JUN_ACT_SLIDER, OnReleasedcaptureJunActSlider)
    ON_EN_CHANGE(IDC_JUN_ACTIVATION, OnChangeJunActivation)
    ON_BN_CLICKED(IDC_MAR_ACT_LOCK, OnMarActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_MAR_ACT_SLIDER, OnReleasedcaptureMarActSlider)
    ON_EN_CHANGE(IDC_MAR_ACTIVATION, OnChangeMarActivation)
    ON_BN_CLICKED(IDC_MAY_ACT_LOCK, OnMayActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_MAY_ACT_SLIDER, OnReleasedcaptureMayActSlider)
    ON_EN_CHANGE(IDC_MAY_ACTIVATION, OnChangeMayActivation)
    ON_BN_CLICKED(IDC_NOV_ACT_LOCK, OnNovActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_NOV_ACT_SLIDER, OnReleasedcaptureNovActSlider)
    ON_EN_CHANGE(IDC_NOV_ACTIVATION, OnChangeNovActivation)
    ON_BN_CLICKED(IDC_OCT_ACT_LOCK, OnOctActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_OCT_ACT_SLIDER, OnReleasedcaptureOctActSlider)
    ON_EN_CHANGE(IDC_OCT_ACTIVATION, OnChangeOctActivation)
    ON_BN_CLICKED(IDC_SEP_ACT_LOCK, OnSepActLock)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SEP_ACT_SLIDER, OnReleasedcaptureSepActSlider)
    ON_EN_CHANGE(IDC_SEP_ACTIVATION, OnChangeSepActivation)
    ON_EN_CHANGE(IDC_TOTAL_ACTIVATION, OnChangeTotalActivation)
    ON_BN_CLICKED(IDC_YEAR_ACT_LOCK, OnYearActLock)
    ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// ZVEqualizeQuantityDlg message handlers

void ZVEqualizeQuantityDlg::OnOK() 
{
    SaveVariables();
    
    CDialog::OnOK();
}

BOOL ZVEqualizeQuantityDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    InitializeVariables();

    CheckControlState();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVEqualizeQuantityDlg::InitializeVariables()
{
    ZBPropertyIterator i(m_pPropertySet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:
            {
                m_Equalizer.SetTotal( pProp->GetValueDouble() );
                m_QuantityYear.Format(szFormatNumbers, m_Equalizer.GetTotal() );
                break;
            }
            case M_Number_January_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexJanuary, pProp->GetValueDouble());
                m_QuantityJanuary.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_February_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexFebruary, pProp->GetValueDouble());
                m_QuantityFebruary.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_March_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexMarch, pProp->GetValueDouble());
                m_QuantityMarch.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_April_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexApril, pProp->GetValueDouble());
                m_QuantityApril.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_May_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexMay, pProp->GetValueDouble());
                m_QuantityMay.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_June_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexJune, pProp->GetValueDouble());
                m_QuantityJune.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_July_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexJuly, pProp->GetValueDouble());
                m_QuantityJuly.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_August_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexAugust, pProp->GetValueDouble());
                m_QuantityAugust.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_September_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexSeptember, pProp->GetValueDouble());
                m_QuantitySeptember.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_October_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexOctober, pProp->GetValueDouble());
                m_QuantityOctober.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_November_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexNovember, pProp->GetValueDouble());
                m_QuantityNovember.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Number_December_ID:
            {
                m_Equalizer.SetNumberAt(g_IndexDecember, pProp->GetValueDouble());
                m_QuantityDecember.Format(szFormatNumbers, pProp->GetValueDouble());
                break;
            }
            case M_Locked_Year_ID:
            {
                m_LockYear = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedTotal(m_LockYear);
                break;
            }
            case M_Locked_January_ID:
            {
                m_LockJanuary = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexJanuary, m_LockJanuary);
                break;
            }
            case M_Locked_February_ID:
            {
                m_LockFebruary = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexFebruary, m_LockFebruary);
                break;
            }
            case M_Locked_March_ID:
            {
                m_LockMarch = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexMarch, m_LockMarch);
                break;
            }
            case M_Locked_April_ID:
            {
                m_LockApril = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexApril, m_LockApril);
                break;
            }
            case M_Locked_May_ID:
            {
                m_LockMay = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexMay, m_LockMay);
                break;
            }
            case M_Locked_June_ID:
            {
                m_LockJune = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexJune, m_LockJune);
                break;
            }
            case M_Locked_July_ID:
            {
                m_LockJuly = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexJuly, m_LockJuly);
                break;
            }
            case M_Locked_August_ID:
            {
                m_LockAugust = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexAugust, m_LockAugust);
                break;
            }
            case M_Locked_September_ID:
            {
                m_LockSeptember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexSeptember, m_LockSeptember);
                break;
            }
            case M_Locked_October_ID:
            {
                m_LockOctober = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexOctober, m_LockOctober);
                break;
            }
            case M_Locked_November_ID:
            {
                m_LockNovember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexNovember, m_LockNovember);
                break;
            }
            case M_Locked_December_ID:
            {
                m_LockDecember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                m_Equalizer.SetLockedFlagAt(g_IndexDecember, m_LockDecember);
                break;
            }
            case M_Force_Equalizer_ID:
            {
                m_ForceEqualizer = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? TRUE : FALSE;
                break;
            }
        }
    }
    UpdateData( FALSE );
    bool bError;

    m_SliderSeptember.SetRange( 0, 100 );
    m_SliderSeptember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexSeptember, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderSeptember.SetTicFreq( 10 );

    m_SliderOctober.SetRange( 0, 100 );
    m_SliderOctober.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexOctober, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderOctober.SetTicFreq( 10 );

    m_SliderNovember.SetRange( 0, 100 );
    m_SliderNovember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexNovember, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderNovember.SetTicFreq( 10 );

    m_SliderMay.SetRange( 0, 100 );
    m_SliderMay.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexMay, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderMay.SetTicFreq( 10 );

    m_SliderMarch.SetRange( 0, 100 );
    m_SliderMarch.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexMarch, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderMarch.SetTicFreq( 10 );

    m_SliderJune.SetRange( 0, 100 );
    m_SliderJune.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJune, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderJune.SetTicFreq( 10 );

    m_SliderJuly.SetRange( 0, 100 );
    m_SliderJuly.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJuly, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderJuly.SetTicFreq( 10 );

    m_SliderJanuary.SetRange( 0, 100 );
    m_SliderJanuary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJanuary, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderJanuary.SetTicFreq( 10 );

    m_SliderFebruary.SetRange( 0, 100 );
    m_SliderFebruary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexFebruary, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderFebruary.SetTicFreq( 10 );

    m_SliderDecember.SetRange( 0, 100 );
    m_SliderDecember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexDecember, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderDecember.SetTicFreq( 10 );

    m_SliderAugust.SetRange( 0, 100 );
    m_SliderAugust.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexAugust, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderAugust.SetTicFreq( 10 );

    m_SliderApril.SetRange( 0, 100 );
    m_SliderApril.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexApril, bError) / m_Equalizer.GetTotal()) * 100) );
    m_SliderApril.SetTicFreq( 10 );

    // Finally, calculates all the percents
    m_Equalizer.CalculatePercents();

}

void ZVEqualizeQuantityDlg::SaveVariables()
{
    UpdateData( TRUE );

    ZBPropertyIterator i(m_pPropertySet);
    ZBProperty* pProp;
    bool bError;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetTotal() );
                break;
            }
            case M_Number_January_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexJanuary, bError ) );
                break;
            }
            case M_Number_February_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexFebruary, bError ) );
                break;
            }
            case M_Number_March_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexMarch, bError ) );
                break;
            }
            case M_Number_April_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexApril, bError ) );
                break;
            }
            case M_Number_May_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexMay, bError ) );
                break;
            }
            case M_Number_June_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexJune, bError ) );
                break;
            }
            case M_Number_July_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexJuly, bError ) );
                break;
            }
            case M_Number_August_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexAugust, bError ) );
                break;
            }
            case M_Number_September_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexSeptember, bError ) );
                break;
            }
            case M_Number_October_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexOctober, bError ) );
                break;
            }
            case M_Number_November_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexNovember, bError ) );
                break;
            }
            case M_Number_December_ID:
            {
                pProp->SetValueDouble( m_Equalizer.GetNumberAt(g_IndexDecember, bError ) );
                break;
            }
            case M_Locked_Year_ID:
            {
                pProp->SetValueString(m_LockYear ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_January_ID:
            {
                pProp->SetValueString(m_LockJanuary ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_February_ID:
            {
                pProp->SetValueString(m_LockFebruary ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_March_ID:
            {
                pProp->SetValueString(m_LockMarch ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_April_ID:
            {
                pProp->SetValueString(m_LockApril ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_May_ID:
            {
                pProp->SetValueString(m_LockMay ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_June_ID:
            {
                pProp->SetValueString(m_LockJune ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_July_ID:
            {
                pProp->SetValueString(m_LockJuly ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_August_ID:
            {
                pProp->SetValueString(m_LockAugust ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_September_ID:
            {
                pProp->SetValueString(m_LockSeptember ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_October_ID:
            {
                pProp->SetValueString(m_LockOctober ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_November_ID:
            {
                pProp->SetValueString(m_LockNovember ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Locked_December_ID:
            {
                pProp->SetValueString(m_LockDecember ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
            case M_Force_Equalizer_ID:
            {
                pProp->SetValueString(m_ForceEqualizer ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo());
                break;
            }
        }
    }
}

void ZVEqualizeQuantityDlg::ApplyEqualizerToControls()
{
    bool error;

    // assigns quantities to strings
    m_QuantityYear.Format     (szFormatNumbers, m_Equalizer.GetTotal());
    m_QuantityJanuary.Format  (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexJanuary,   error));
    m_QuantityFebruary.Format (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexFebruary,  error));
    m_QuantityMarch.Format    (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexMarch,     error));
    m_QuantityApril.Format    (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexApril,     error));
    m_QuantityMay.Format      (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexMay,       error));
    m_QuantityJune.Format     (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexJune,      error));
    m_QuantityJuly.Format     (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexJuly,      error));
    m_QuantityAugust.Format   (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexAugust,    error));
    m_QuantitySeptember.Format(szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexSeptember, error));
    m_QuantityOctober.Format  (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexOctober,   error));
    m_QuantityNovember.Format (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexNovember,  error));
    m_QuantityDecember.Format (szFormatNumbers, m_Equalizer.GetNumberAt(g_IndexDecember,  error));

    // Assigns slider values
    m_SliderSeptember.SetPos(static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexSeptember, error) / m_Equalizer.GetTotal()) * 100));
    m_SliderOctober.SetPos  (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexOctober,   error) / m_Equalizer.GetTotal()) * 100));
    m_SliderNovember.SetPos (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexNovember,  error) / m_Equalizer.GetTotal()) * 100));
    m_SliderMay.SetPos      (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexMay,       error) / m_Equalizer.GetTotal()) * 100));
    m_SliderMarch.SetPos    (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexMarch,     error) / m_Equalizer.GetTotal()) * 100));
    m_SliderJune.SetPos     (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJune,      error) / m_Equalizer.GetTotal()) * 100));
    m_SliderJuly.SetPos     (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJuly,      error) / m_Equalizer.GetTotal()) * 100));
    m_SliderJanuary.SetPos  (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexJanuary,   error) / m_Equalizer.GetTotal()) * 100));
    m_SliderFebruary.SetPos (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexFebruary,  error) / m_Equalizer.GetTotal()) * 100));
    m_SliderDecember.SetPos (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexDecember,  error) / m_Equalizer.GetTotal()) * 100));
    m_SliderAugust.SetPos   (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexAugust,    error) / m_Equalizer.GetTotal()) * 100));
    m_SliderApril.SetPos    (static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(g_IndexApril,     error) / m_Equalizer.GetTotal()) * 100));

    UpdateData(FALSE);
}

void ZVEqualizeQuantityDlg::CheckControlState()
{
    UpdateData( TRUE );
    if (GetDlgItem(IDC_TOTAL_ACTIVATION))
        GetDlgItem(IDC_TOTAL_ACTIVATION)->EnableWindow( m_LockYear == FALSE );
    if (GetDlgItem(IDC_SEP_ACT_SLIDER))
        GetDlgItem(IDC_SEP_ACT_SLIDER)->EnableWindow( m_LockSeptember == FALSE );
    if (GetDlgItem(IDC_SEP_ACTIVATION))
        GetDlgItem(IDC_SEP_ACTIVATION)->EnableWindow( m_LockSeptember == FALSE );
    if (GetDlgItem(IDC_OCT_ACT_SLIDER))
        GetDlgItem(IDC_OCT_ACT_SLIDER)->EnableWindow( m_LockOctober == FALSE );
    if (GetDlgItem(IDC_OCT_ACTIVATION))
        GetDlgItem(IDC_OCT_ACTIVATION)->EnableWindow( m_LockOctober == FALSE );
    if (GetDlgItem(IDC_NOV_ACT_SLIDER))
        GetDlgItem(IDC_NOV_ACT_SLIDER)->EnableWindow( m_LockNovember == FALSE );
    if (GetDlgItem(IDC_NOV_ACTIVATION))
        GetDlgItem(IDC_NOV_ACTIVATION)->EnableWindow( m_LockNovember == FALSE );
    if (GetDlgItem(IDC_MAY_ACT_SLIDER))
        GetDlgItem(IDC_MAY_ACT_SLIDER)->EnableWindow( m_LockMay == FALSE );
    if (GetDlgItem(IDC_MAY_ACTIVATION))
        GetDlgItem(IDC_MAY_ACTIVATION)->EnableWindow( m_LockMay == FALSE );
    if (GetDlgItem(IDC_MAR_ACT_SLIDER))
        GetDlgItem(IDC_MAR_ACT_SLIDER)->EnableWindow( m_LockMarch == FALSE );
    if (GetDlgItem(IDC_MAR_ACTIVATION))
        GetDlgItem(IDC_MAR_ACTIVATION)->EnableWindow( m_LockMarch == FALSE );
    if (GetDlgItem(IDC_JUN_ACT_SLIDER))
        GetDlgItem(IDC_JUN_ACT_SLIDER)->EnableWindow( m_LockJune == FALSE );
    if (GetDlgItem(IDC_JUN_ACTIVATION))
        GetDlgItem(IDC_JUN_ACTIVATION)->EnableWindow( m_LockJune == FALSE );
    if (GetDlgItem(IDC_JUL_ACT_SLIDER))
        GetDlgItem(IDC_JUL_ACT_SLIDER)->EnableWindow( m_LockJuly == FALSE );
    if (GetDlgItem(IDC_JUL_ACTIVATION))
        GetDlgItem(IDC_JUL_ACTIVATION)->EnableWindow( m_LockJuly == FALSE );
    if (GetDlgItem(IDC_JAN_ACT_SLIDER))
        GetDlgItem(IDC_JAN_ACT_SLIDER)->EnableWindow( m_LockJanuary == FALSE );
    if (GetDlgItem(IDC_JAN_ACTIVATION))
        GetDlgItem(IDC_JAN_ACTIVATION)->EnableWindow( m_LockJanuary == FALSE );
    if (GetDlgItem(IDC_FEB_ACT_SLIDER))
        GetDlgItem(IDC_FEB_ACT_SLIDER)->EnableWindow( m_LockFebruary == FALSE );
    if (GetDlgItem(IDC_FEB_ACTIVATION))
        GetDlgItem(IDC_FEB_ACTIVATION)->EnableWindow( m_LockFebruary == FALSE );
    if (GetDlgItem(IDC_DEC_ACT_SLIDER))
        GetDlgItem(IDC_DEC_ACT_SLIDER)->EnableWindow( m_LockDecember == FALSE );
    if (GetDlgItem(IDC_DEC_ACTIVATION))
        GetDlgItem(IDC_DEC_ACTIVATION)->EnableWindow( m_LockDecember == FALSE );
    if (GetDlgItem(IDC_AUG_ACT_SLIDER))
        GetDlgItem(IDC_AUG_ACT_SLIDER)->EnableWindow( m_LockAugust == FALSE );
    if (GetDlgItem(IDC_AUG_ACTIVATION))
        GetDlgItem(IDC_AUG_ACTIVATION)->EnableWindow( m_LockAugust == FALSE );
    if (GetDlgItem(IDC_APR_ACT_SLIDER))
        GetDlgItem(IDC_APR_ACT_SLIDER)->EnableWindow( m_LockApril == FALSE );
    if (GetDlgItem(IDC_APR_ACTIVATION))
        GetDlgItem(IDC_APR_ACTIVATION)->EnableWindow( m_LockApril == FALSE );
}

void ZVEqualizeQuantityDlg::OnAprActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexApril, m_LockApril);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureAprActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexApril, double(m_SliderApril.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeAprActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityApril);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexApril, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnAugActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, m_LockAugust);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureAugActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexAugust, double(m_SliderAugust.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeAugActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityAugust);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexAugust, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnDecActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, m_LockDecember);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureDecActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexDecember, double(m_SliderDecember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeDecActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityDecember);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexDecember, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnFebActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, m_LockFebruary);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureFebActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexFebruary, double(m_SliderFebruary.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeFebActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityFebruary);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexFebruary, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJanActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, m_LockJanuary);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJanActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJanuary, double(m_SliderJanuary.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJanActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityJanuary);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexJanuary, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJulActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, m_LockJuly);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJulActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJuly, double(m_SliderJuly.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJulActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityJuly);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexJuly, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJunActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJune, m_LockJune);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJunActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJune, double(m_SliderJune.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJunActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityJune);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexJune, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnMarActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, m_LockMarch);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureMarActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexMarch, double(m_SliderMarch.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeMarActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityMarch);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexMarch, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnMayActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexMay, m_LockMay);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureMayActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexMay, double(m_SliderMay.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeMayActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityMay);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexMay, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnNovActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, m_LockNovember);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureNovActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexNovember, double(m_SliderNovember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeNovActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityNovember);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexNovember, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnOctActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, m_LockOctober);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureOctActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexOctober, double(m_SliderOctober.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeOctActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantityOctober);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexOctober, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnSepActLock() 
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, m_LockSeptember);
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureSepActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Equalizer.SetPercentAtEqualize(g_IndexSeptember, double(m_SliderSeptember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeSepActivation() 
{
    UpdateData( TRUE );

    double Number = atof(m_QuantitySeptember);
    if (Number < 0)
        Number = 0;
    m_Equalizer.SetNumberAtEqualize(g_IndexSeptember, Number);

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnChangeTotalActivation() 
{
    UpdateData( TRUE );

    double Total = atof(m_QuantityYear);
    if (Total < 0)
        Total = 0;
    m_Equalizer.SetTotalReEqualizeNumbers( Total );

    ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnYearActLock() 
{
    CheckControlState();

    m_Equalizer.SetLockedTotal(m_LockYear);
}


void ZVEqualizeQuantityDlg::OnDefault() 
{
    UpdateData( TRUE );
    
    double Total = atof(m_QuantityYear);
    double ValuePerMonth = Total / (double)12;
    
    // Now, for each number, sets the new value
    // and unlock all values
    for (int i = 0; i < 12; ++i)
    {
        m_Equalizer.SetNumberAt( i, ValuePerMonth );
        m_Equalizer.SetLockedFlagAt( i, false );
    }
    // Now apply the equalizer value to all controls
    ApplyEqualizerToControls();

    // Calculates all the percents
    m_Equalizer.CalculatePercents();

    // Finally, resets all lock controls
    m_LockYear = FALSE;
    m_LockSeptember = FALSE;
    m_LockOctober = FALSE;
    m_LockNovember = FALSE;
    m_LockMay = FALSE;
    m_LockMarch = FALSE;
    m_LockJune = FALSE;
    m_LockJuly = FALSE;
    m_LockJanuary = FALSE;
    m_LockFebruary = FALSE;
    m_LockDecember = FALSE;
    m_LockAugust = FALSE;
    m_LockApril = FALSE;

    UpdateData( FALSE );

    // check the control state for the dialog
    CheckControlState();
}
