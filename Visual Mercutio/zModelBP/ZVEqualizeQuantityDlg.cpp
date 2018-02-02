// ZVEqualizeQuantityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVEqualizeQuantityDlg.h"

#include "ZBBPAnnualNumberProp.h"
// Global resources
#include "zBaseLib\ZAGlobal.h"

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
			case Z_NUMBER_YEAR:
			{
				m_Equalizer.SetTotal( pProp->GetValueDouble() );
				m_QuantityYear.Format(szFormatNumbers, m_Equalizer.GetTotal() );
				break;
			}
			case Z_NUMBER_JANUARY:
			{
				m_Equalizer.SetNumberAt( IndexJanuary, pProp->GetValueDouble() );
				m_QuantityJanuary.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_FEBRUARY:
			{
				m_Equalizer.SetNumberAt( IndexFebruary, pProp->GetValueDouble() );
				m_QuantityFebruary.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_MARCH:
			{
				m_Equalizer.SetNumberAt( IndexMarch, pProp->GetValueDouble() );
				m_QuantityMarch.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_APRIL:
			{
				m_Equalizer.SetNumberAt( IndexApril, pProp->GetValueDouble() );
				m_QuantityApril.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_MAY	:
			{
				m_Equalizer.SetNumberAt( IndexMay, pProp->GetValueDouble() );
				m_QuantityMay.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_JUNE	:
			{
				m_Equalizer.SetNumberAt( IndexJune, pProp->GetValueDouble() );
				m_QuantityJune.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_JULY	:
			{
				m_Equalizer.SetNumberAt( IndexJuly, pProp->GetValueDouble() );
				m_QuantityJuly.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_AUGUST:
			{
				m_Equalizer.SetNumberAt( IndexAugust, pProp->GetValueDouble() );
				m_QuantityAugust.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_SEPTEMBER:
			{
				m_Equalizer.SetNumberAt( IndexSeptember, pProp->GetValueDouble() );
				m_QuantitySeptember.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_OCTOBER:
			{
				m_Equalizer.SetNumberAt( IndexOctober, pProp->GetValueDouble() );
				m_QuantityOctober.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_NOVEMBER:
			{
				m_Equalizer.SetNumberAt( IndexNovember, pProp->GetValueDouble() );
				m_QuantityNovember.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_NUMBER_DECEMBER:
			{
				m_Equalizer.SetNumberAt( IndexDecember, pProp->GetValueDouble() );
				m_QuantityDecember.Format(szFormatNumbers, pProp->GetValueDouble());
				break;
			}
			case Z_LOCKED_YEAR:
			{
				m_LockYear = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedTotal( (m_LockYear == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_JANUARY:
			{
				m_LockJanuary = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexJanuary, (m_LockJanuary == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_FEBRUARY:
			{
				m_LockFebruary = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexFebruary, (m_LockFebruary == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_MARCH:
			{
				m_LockMarch = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexMarch, (m_LockMarch == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_APRIL:
			{
				m_LockApril = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexApril, (m_LockApril == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_MAY:
			{
				m_LockMay = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexMay, (m_LockMay == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_JUNE:
			{
				m_LockJune = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexJune, (m_LockJune == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_JULY:
			{
				m_LockJuly = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexJuly, (m_LockJuly == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_AUGUST:
			{
				m_LockAugust = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexAugust, (m_LockAugust == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_SEPTEMBER:
			{
				m_LockSeptember = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexSeptember, (m_LockSeptember == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_OCTOBER:
			{
				m_LockOctober = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexOctober, (m_LockOctober == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_NOVEMBER:
			{
				m_LockNovember = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexNovember, (m_LockNovember == TRUE) ? true : false );
				break;
			}
			case Z_LOCKED_DECEMBER:
			{
				m_LockDecember = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				m_Equalizer.SetLockedFlagAt( IndexDecember, (m_LockDecember == TRUE) ? true : false );
				break;
			}
			case Z_FORCE_EQUALIZER:
			{
				m_ForceEqualizer = (pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo()) ? TRUE : FALSE;
				break;
			}
		}
	}
	UpdateData( FALSE );
	bool bError;

	m_SliderSeptember.SetRange( 0, 100 );
	m_SliderSeptember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexSeptember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderSeptember.SetTicFreq( 10 );

	m_SliderOctober.SetRange( 0, 100 );
	m_SliderOctober.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexOctober, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderOctober.SetTicFreq( 10 );

	m_SliderNovember.SetRange( 0, 100 );
	m_SliderNovember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexNovember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderNovember.SetTicFreq( 10 );

	m_SliderMay.SetRange( 0, 100 );
	m_SliderMay.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexMay, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderMay.SetTicFreq( 10 );

	m_SliderMarch.SetRange( 0, 100 );
	m_SliderMarch.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexMarch, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderMarch.SetTicFreq( 10 );

	m_SliderJune.SetRange( 0, 100 );
	m_SliderJune.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJune, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJune.SetTicFreq( 10 );

	m_SliderJuly.SetRange( 0, 100 );
	m_SliderJuly.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJuly, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJuly.SetTicFreq( 10 );

	m_SliderJanuary.SetRange( 0, 100 );
	m_SliderJanuary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJanuary, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJanuary.SetTicFreq( 10 );

	m_SliderFebruary.SetRange( 0, 100 );
	m_SliderFebruary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexFebruary, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderFebruary.SetTicFreq( 10 );

	m_SliderDecember.SetRange( 0, 100 );
	m_SliderDecember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexDecember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderDecember.SetTicFreq( 10 );

	m_SliderAugust.SetRange( 0, 100 );
	m_SliderAugust.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexAugust, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderAugust.SetTicFreq( 10 );

	m_SliderApril.SetRange( 0, 100 );
	m_SliderApril.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexApril, bError) / m_Equalizer.GetTotal()) * 100) );
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
			case Z_NUMBER_YEAR:
			{
				pProp->SetValueDouble( m_Equalizer.GetTotal() );
				break;
			}
			case Z_NUMBER_JANUARY:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexJanuary, bError ) );
				break;
			}
			case Z_NUMBER_FEBRUARY:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexFebruary, bError ) );
				break;
			}
			case Z_NUMBER_MARCH:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexMarch, bError ) );
				break;
			}
			case Z_NUMBER_APRIL:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexApril, bError ) );
				break;
			}
			case Z_NUMBER_MAY	:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexMay, bError ) );
				break;
			}
			case Z_NUMBER_JUNE	:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexJune, bError ) );
				break;
			}
			case Z_NUMBER_JULY	:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexJuly, bError ) );
				break;
			}
			case Z_NUMBER_AUGUST:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexAugust, bError ) );
				break;
			}
			case Z_NUMBER_SEPTEMBER:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexSeptember, bError ) );
				break;
			}
			case Z_NUMBER_OCTOBER:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexOctober, bError ) );
				break;
			}
			case Z_NUMBER_NOVEMBER:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexNovember, bError ) );
				break;
			}
			case Z_NUMBER_DECEMBER:
			{
				pProp->SetValueDouble( m_Equalizer.GetNumberAt(IndexDecember, bError ) );
				break;
			}
			case Z_LOCKED_YEAR:
			{
				pProp->SetValueString( (m_LockYear == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_JANUARY:
			{
				pProp->SetValueString( (m_LockJanuary == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_FEBRUARY:
			{
				pProp->SetValueString( (m_LockFebruary == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_MARCH:
			{
				pProp->SetValueString( (m_LockMarch == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_APRIL:
			{
				pProp->SetValueString( (m_LockApril == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_MAY:
			{
				pProp->SetValueString( (m_LockMay == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_JUNE:
			{
				pProp->SetValueString( (m_LockJune == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_JULY:
			{
				pProp->SetValueString( (m_LockJuly == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_AUGUST:
			{
				pProp->SetValueString( (m_LockAugust == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_SEPTEMBER:
			{
				pProp->SetValueString( (m_LockSeptember == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_OCTOBER:
			{
				pProp->SetValueString( (m_LockOctober == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_NOVEMBER:
			{
				pProp->SetValueString( (m_LockNovember == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_LOCKED_DECEMBER:
			{
				pProp->SetValueString( (m_LockDecember == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
			case Z_FORCE_EQUALIZER:
			{
				pProp->SetValueString( (m_ForceEqualizer == TRUE) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo() );
				break;
			}
		}
	}
}

void ZVEqualizeQuantityDlg::ApplyEqualizerToControls()
{
	bool bError;
	// Assigns quantities to strings
	m_QuantityYear.Format(szFormatNumbers, m_Equalizer.GetTotal() );
	m_QuantityJanuary.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexJanuary, bError));
	m_QuantityFebruary.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexFebruary, bError));
	m_QuantityMarch.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexMarch, bError));
	m_QuantityApril.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexApril, bError));
	m_QuantityMay.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexMay, bError));
	m_QuantityJune.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexJune, bError));
	m_QuantityJuly.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexJuly, bError));
	m_QuantityAugust.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexAugust, bError));
	m_QuantitySeptember.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexSeptember, bError));
	m_QuantityOctober.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexOctober, bError));
	m_QuantityNovember.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexNovember, bError));
	m_QuantityDecember.Format(szFormatNumbers, m_Equalizer.GetNumberAt( IndexDecember, bError));

	// Assigns slider values
	m_SliderSeptember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexSeptember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderOctober.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexOctober, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderNovember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexNovember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderMay.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexMay, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderMarch.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexMarch, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJune.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJune, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJuly.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJuly, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderJanuary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexJanuary, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderFebruary.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexFebruary, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderDecember.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexDecember, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderAugust.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexAugust, bError) / m_Equalizer.GetTotal()) * 100) );
	m_SliderApril.SetPos( static_cast<int>(static_cast<double>(m_Equalizer.GetNumberAt(IndexApril, bError) / m_Equalizer.GetTotal()) * 100) );

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
	
	m_Equalizer.SetLockedFlagAt( IndexApril, (m_LockApril == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureAprActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderApril.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexApril, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();

	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeAprActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityApril);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexApril, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnAugActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexAugust, (m_LockAugust == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureAugActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderAugust.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexAugust, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeAugActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityAugust);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexAugust, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnDecActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexDecember, (m_LockDecember == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureDecActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderDecember.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexDecember, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeDecActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityDecember);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexDecember, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnFebActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexFebruary, (m_LockFebruary == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureFebActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderFebruary.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexFebruary, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeFebActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityFebruary);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexFebruary, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJanActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexJanuary, (m_LockJanuary == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJanActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderJanuary.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexJanuary, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJanActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityJanuary);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexJanuary, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJulActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexJuly, (m_LockJuly == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJulActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderJuly.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexJuly, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJulActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityJuly);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexJuly, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnJunActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexJune, (m_LockJune == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureJunActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderJune.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexJune, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeJunActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityJune);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexJune, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnMarActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexMarch, (m_LockMarch == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureMarActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderMarch.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexMarch, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeMarActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityMarch);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexMarch, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnMayActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexMay, (m_LockMay == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureMayActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderMay.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexMay, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeMayActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityMay);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexMay, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnNovActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexNovember, (m_LockNovember == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureNovActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderNovember.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexNovember, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeNovActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityNovember);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexNovember, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnOctActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexOctober, (m_LockOctober == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureOctActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderOctober.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexOctober, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeOctActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantityOctober);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexOctober, Number );

	ApplyEqualizerToControls();
}

void ZVEqualizeQuantityDlg::OnSepActLock() 
{
	CheckControlState();

	m_Equalizer.SetLockedFlagAt( IndexSeptember, (m_LockSeptember == TRUE) ? true : false );
}

void ZVEqualizeQuantityDlg::OnReleasedcaptureSepActSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentPos = m_SliderSeptember.GetPos();
	m_Equalizer.SetPercentAtEqualize( IndexSeptember, static_cast<double>(currentPos) / static_cast<double>(100) );

	ApplyEqualizerToControls();
	
	*pResult = 0;
}

void ZVEqualizeQuantityDlg::OnChangeSepActivation() 
{
	UpdateData( TRUE );
	
	double Number = atof(m_QuantitySeptember);
	if (Number < 0)
		Number = 0;
	m_Equalizer.SetNumberAtEqualize( IndexSeptember, Number );

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

	m_Equalizer.SetLockedTotal( (m_LockYear == TRUE) ? true : false );
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
	// Check the control state for the dialog
	CheckControlState();

}
