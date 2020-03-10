/****************************************************************************
 * ==> PSS_EqualizeQuantityDlg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an equalize a quantity dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_EqualizeQuantityDlg.h"

// processsoft
#include "PSS_AnnualNumberPropertiesBP.h"

// resources
#include "zBaseLib\PSS_Global.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Constant variables
//---------------------------------------------------------------------------
const char g_FormatNumbers[] = "%.0f";
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_EqualizeQuantityDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_EqualizeQuantityDlg)
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
//---------------------------------------------------------------------------
// PSS_EqualizeQuantityDlg
//---------------------------------------------------------------------------
PSS_EqualizeQuantityDlg::PSS_EqualizeQuantityDlg(ZBPropertySet* pPropertySet, CWnd* pParent) :
    CDialog(PSS_EqualizeQuantityDlg::IDD, pParent),
    m_pPropertySet(pPropertySet),
    m_LockYear(FALSE),
    m_LockJanuary(FALSE),
    m_LockFebruary(FALSE),
    m_LockMarch(FALSE),
    m_LockApril(FALSE),
    m_LockMay(FALSE),
    m_LockJune(FALSE),
    m_LockJuly(FALSE),
    m_LockAugust(FALSE),
    m_LockSeptember(FALSE),
    m_LockOctober(FALSE),
    m_LockNovember(FALSE),
    m_LockDecember(FALSE),
    m_ForceEqualizer(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EqualizeQuantityDlg::~PSS_EqualizeQuantityDlg()
{}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_EqualizeQuantityDlg)
    DDX_Control(pDX, IDC_SEP_ACT_SLIDER,   m_SliderSeptember);
    DDX_Control(pDX, IDC_OCT_ACT_SLIDER,   m_SliderOctober);
    DDX_Control(pDX, IDC_NOV_ACT_SLIDER,   m_SliderNovember);
    DDX_Control(pDX, IDC_MAY_ACT_SLIDER,   m_SliderMay);
    DDX_Control(pDX, IDC_MAR_ACT_SLIDER,   m_SliderMarch);
    DDX_Control(pDX, IDC_JUN_ACT_SLIDER,   m_SliderJune);
    DDX_Control(pDX, IDC_JUL_ACT_SLIDER,   m_SliderJuly);
    DDX_Control(pDX, IDC_JAN_ACT_SLIDER,   m_SliderJanuary);
    DDX_Control(pDX, IDC_FEB_ACT_SLIDER,   m_SliderFebruary);
    DDX_Control(pDX, IDC_DEC_ACT_SLIDER,   m_SliderDecember);
    DDX_Control(pDX, IDC_AUG_ACT_SLIDER,   m_SliderAugust);
    DDX_Control(pDX, IDC_APR_ACT_SLIDER,   m_SliderApril);
    DDX_Check  (pDX, IDC_APR_ACT_LOCK,     m_LockApril);
    DDX_Check  (pDX, IDC_AUG_ACT_LOCK,     m_LockAugust);
    DDX_Check  (pDX, IDC_DEC_ACT_LOCK,     m_LockDecember);
    DDX_Check  (pDX, IDC_FEB_ACT_LOCK,     m_LockFebruary);
    DDX_Check  (pDX, IDC_JAN_ACT_LOCK,     m_LockJanuary);
    DDX_Check  (pDX, IDC_JUL_ACT_LOCK,     m_LockJuly);
    DDX_Check  (pDX, IDC_JUN_ACT_LOCK,     m_LockJune);
    DDX_Check  (pDX, IDC_MAR_ACT_LOCK,     m_LockMarch);
    DDX_Check  (pDX, IDC_MAY_ACT_LOCK,     m_LockMay);
    DDX_Check  (pDX, IDC_NOV_ACT_LOCK,     m_LockNovember);
    DDX_Check  (pDX, IDC_OCT_ACT_LOCK,     m_LockOctober);
    DDX_Check  (pDX, IDC_SEP_ACT_LOCK,     m_LockSeptember);
    DDX_Check  (pDX, IDC_YEAR_ACT_LOCK,    m_LockYear);
    DDX_Text   (pDX, IDC_APR_ACTIVATION,   m_QuantityApril);
    DDX_Text   (pDX, IDC_AUG_ACTIVATION,   m_QuantityAugust);
    DDX_Text   (pDX, IDC_DEC_ACTIVATION,   m_QuantityDecember);
    DDX_Text   (pDX, IDC_FEB_ACTIVATION,   m_QuantityFebruary);
    DDX_Text   (pDX, IDC_JAN_ACTIVATION,   m_QuantityJanuary);
    DDX_Text   (pDX, IDC_JUL_ACTIVATION,   m_QuantityJuly);
    DDX_Text   (pDX, IDC_JUN_ACTIVATION,   m_QuantityJune);
    DDX_Text   (pDX, IDC_MAR_ACTIVATION,   m_QuantityMarch);
    DDX_Text   (pDX, IDC_MAY_ACTIVATION,   m_QuantityMay);
    DDX_Text   (pDX, IDC_NOV_ACTIVATION,   m_QuantityNovember);
    DDX_Text   (pDX, IDC_OCT_ACTIVATION,   m_QuantityOctober);
    DDX_Text   (pDX, IDC_SEP_ACTIVATION,   m_QuantitySeptember);
    DDX_Text   (pDX, IDC_TOTAL_ACTIVATION, m_QuantityYear);
    DDX_Check  (pDX, IDC_FORCE_EQUALIZER,  m_ForceEqualizer);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_EqualizeQuantityDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    InitializeVariables();
    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnAprActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexApril, m_LockApril);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureAprActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexApril, double(m_SliderApril.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeAprActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityApril);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexApril, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnAugActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, m_LockAugust);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureAugActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexAugust, double(m_SliderAugust.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeAugActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityAugust);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexAugust, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnDecActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, m_LockDecember);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureDecActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexDecember, double(m_SliderDecember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeDecActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityDecember);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexDecember, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnFebActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, m_LockFebruary);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureFebActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexFebruary, double(m_SliderFebruary.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeFebActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityFebruary);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexFebruary, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnJanActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, m_LockJanuary);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureJanActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJanuary, double(m_SliderJanuary.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeJanActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityJanuary);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexJanuary, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnJulActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, m_LockJuly);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureJulActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJuly, double(m_SliderJuly.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeJulActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityJuly);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexJuly, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnJunActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexJune, m_LockJune);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureJunActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexJune, double(m_SliderJune.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeJunActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityJune);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexJune, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnMarActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, m_LockMarch);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureMarActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexMarch, double(m_SliderMarch.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeMarActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityMarch);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexMarch, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnMayActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexMay, m_LockMay);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureMayActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexMay, double(m_SliderMay.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeMayActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityMay);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexMay, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnNovActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, m_LockNovember);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureNovActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexNovember, double(m_SliderNovember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeNovActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityNovember);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexNovember, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnOctActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, m_LockOctober);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureOctActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexOctober, double(m_SliderOctober.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeOctActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantityOctober);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexOctober, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnSepActLock()
{
    CheckControlState();
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, m_LockSeptember);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnReleasedcaptureSepActSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    m_Equalizer.SetPercentAtEqualize(g_IndexSeptember, double(m_SliderSeptember.GetPos()) / 100.0);
    ApplyEqualizerToControls();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeSepActivation()
{
    UpdateData(TRUE);

    double number = std::atof(m_QuantitySeptember);

    if (number < 0.0)
        number = 0.0;

    m_Equalizer.SetNumberAtEqualize(g_IndexSeptember, number);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnChangeTotalActivation()
{
    UpdateData(TRUE);

    double total = std::atof(m_QuantityYear);

    if (total < 0.0)
        total = 0.0;

    m_Equalizer.SetTotalReEqualizeNumbers(total);

    ApplyEqualizerToControls();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnYearActLock()
{
    CheckControlState();

    m_Equalizer.SetLockedTotal(m_LockYear);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnDefault()
{
    UpdateData(TRUE);

    const double total         = std::atof(m_QuantityYear);
    const double valuePerMonth = total / 12.0;

    // for each number, sets the new value and unlock all values
    for (int i = 0; i < 12; ++i)
    {
        m_Equalizer.SetNumberAt(i, valuePerMonth);
        m_Equalizer.SetLockedFlagAt(i, false);
    }
    // apply the equalizer value to all controls
    ApplyEqualizerToControls();

    // calculate all the percents
    m_Equalizer.CalculatePercents();

    // reset all lock controls
    m_LockYear      = FALSE;
    m_LockJanuary   = FALSE;
    m_LockFebruary  = FALSE;
    m_LockMarch     = FALSE;
    m_LockApril     = FALSE;
    m_LockMay       = FALSE;
    m_LockJune      = FALSE;
    m_LockJuly      = FALSE;
    m_LockAugust    = FALSE;
    m_LockSeptember = FALSE;
    m_LockOctober   = FALSE;
    m_LockNovember  = FALSE;
    m_LockDecember  = FALSE;

    UpdateData(FALSE);

    // check the control state for the dialog
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::OnOK()
{
    SaveVariables();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::InitializeVariables()
{
    ZBPropertyIterator it(m_pPropertySet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:
                m_Equalizer.SetTotal(pProp->GetValueDouble());
                m_QuantityYear.Format(g_FormatNumbers, m_Equalizer.GetTotal());
                break;

            case M_Number_January_ID:
                m_Equalizer.SetNumberAt(g_IndexJanuary, pProp->GetValueDouble());
                m_QuantityJanuary.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_February_ID:
                m_Equalizer.SetNumberAt(g_IndexFebruary, pProp->GetValueDouble());
                m_QuantityFebruary.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_March_ID:
                m_Equalizer.SetNumberAt(g_IndexMarch, pProp->GetValueDouble());
                m_QuantityMarch.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_April_ID:
                m_Equalizer.SetNumberAt(g_IndexApril, pProp->GetValueDouble());
                m_QuantityApril.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_May_ID:
                m_Equalizer.SetNumberAt(g_IndexMay, pProp->GetValueDouble());
                m_QuantityMay.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_June_ID:
                m_Equalizer.SetNumberAt(g_IndexJune, pProp->GetValueDouble());
                m_QuantityJune.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_July_ID:
                m_Equalizer.SetNumberAt(g_IndexJuly, pProp->GetValueDouble());
                m_QuantityJuly.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_August_ID:
                m_Equalizer.SetNumberAt(g_IndexAugust, pProp->GetValueDouble());
                m_QuantityAugust.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_September_ID:
                m_Equalizer.SetNumberAt(g_IndexSeptember, pProp->GetValueDouble());
                m_QuantitySeptember.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_October_ID:
                m_Equalizer.SetNumberAt(g_IndexOctober, pProp->GetValueDouble());
                m_QuantityOctober.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_November_ID:
                m_Equalizer.SetNumberAt(g_IndexNovember, pProp->GetValueDouble());
                m_QuantityNovember.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Number_December_ID:
                m_Equalizer.SetNumberAt(g_IndexDecember, pProp->GetValueDouble());
                m_QuantityDecember.Format(g_FormatNumbers, pProp->GetValueDouble());
                break;

            case M_Locked_Year_ID:
                m_LockYear = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedTotal(m_LockYear);
                break;

            case M_Locked_January_ID:
                m_LockJanuary = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexJanuary, m_LockJanuary);
                break;

            case M_Locked_February_ID:
                m_LockFebruary = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexFebruary, m_LockFebruary);
                break;

            case M_Locked_March_ID:
                m_LockMarch = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexMarch, m_LockMarch);
                break;

            case M_Locked_April_ID:
                m_LockApril = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexApril, m_LockApril);
                break;

            case M_Locked_May_ID:
                m_LockMay = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexMay, m_LockMay);
                break;

            case M_Locked_June_ID:
                m_LockJune = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexJune, m_LockJune);
                break;

            case M_Locked_July_ID:
                m_LockJuly = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexJuly, m_LockJuly);
                break;

            case M_Locked_August_ID:
                m_LockAugust = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexAugust, m_LockAugust);
                break;

            case M_Locked_September_ID:
                m_LockSeptember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexSeptember, m_LockSeptember);
                break;

            case M_Locked_October_ID:
                m_LockOctober = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexOctober, m_LockOctober);
                break;

            case M_Locked_November_ID:
                m_LockNovember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexNovember, m_LockNovember);
                break;

            case M_Locked_December_ID:
                m_LockDecember = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                m_Equalizer.SetLockedFlagAt(g_IndexDecember, m_LockDecember);
                break;

            case M_Force_Equalizer_ID:
                m_ForceEqualizer = (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo());
                break;
        }
    }

    UpdateData(FALSE);
    bool bError;

    m_SliderSeptember.SetRange(0, 100);
    m_SliderSeptember.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexSeptember, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderSeptember.SetTicFreq(10);

    m_SliderOctober.SetRange(0, 100);
    m_SliderOctober.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexOctober, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderOctober.SetTicFreq(10);

    m_SliderNovember.SetRange(0, 100);
    m_SliderNovember.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexNovember, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderNovember.SetTicFreq(10);

    m_SliderMay.SetRange(0, 100);
    m_SliderMay.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexMay, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderMay.SetTicFreq(10);

    m_SliderMarch.SetRange(0, 100);
    m_SliderMarch.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexMarch, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderMarch.SetTicFreq(10);

    m_SliderJune.SetRange(0, 100);
    m_SliderJune.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexJune, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJune.SetTicFreq(10);

    m_SliderJuly.SetRange(0, 100);
    m_SliderJuly.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexJuly, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJuly.SetTicFreq(10);

    m_SliderJanuary.SetRange(0, 100);
    m_SliderJanuary.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexJanuary, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJanuary.SetTicFreq(10);

    m_SliderFebruary.SetRange(0, 100);
    m_SliderFebruary.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexFebruary, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderFebruary.SetTicFreq(10);

    m_SliderDecember.SetRange(0, 100);
    m_SliderDecember.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexDecember, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderDecember.SetTicFreq(10);

    m_SliderAugust.SetRange(0, 100);
    m_SliderAugust.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexAugust, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderAugust.SetTicFreq(10);

    m_SliderApril.SetRange(0, 100);
    m_SliderApril.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexApril, bError) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderApril.SetTicFreq(10);

    // calculate all the percents
    m_Equalizer.CalculatePercents();
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::SaveVariables()
{
    UpdateData(TRUE);

    ZBPropertyIterator it(m_pPropertySet);
    bool               error;

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:      pProp->SetValueDouble(m_Equalizer.GetTotal());                                                                    break;
            case M_Number_January_ID:   pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexJanuary,   error));                                          break;
            case M_Number_February_ID:  pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexFebruary,  error));                                          break;
            case M_Number_March_ID:     pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexMarch,     error));                                          break;
            case M_Number_April_ID:     pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexApril,     error));                                          break;
            case M_Number_May_ID:       pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexMay,       error));                                          break;
            case M_Number_June_ID:      pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexJune,      error));                                          break;
            case M_Number_July_ID:      pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexJuly,      error));                                          break;
            case M_Number_August_ID:    pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexAugust,    error));                                          break;
            case M_Number_September_ID: pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexSeptember, error));                                          break;
            case M_Number_October_ID:   pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexOctober,   error));                                          break;
            case M_Number_November_ID:  pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexNovember,  error));                                          break;
            case M_Number_December_ID:  pProp->SetValueDouble(m_Equalizer.GetNumberAt(g_IndexDecember,  error));                                          break;
            case M_Locked_Year_ID:      pProp->SetValueString(m_LockYear       ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_January_ID:   pProp->SetValueString(m_LockJanuary    ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_February_ID:  pProp->SetValueString(m_LockFebruary   ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_March_ID:     pProp->SetValueString(m_LockMarch      ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_April_ID:     pProp->SetValueString(m_LockApril      ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_May_ID:       pProp->SetValueString(m_LockMay        ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_June_ID:      pProp->SetValueString(m_LockJune       ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_July_ID:      pProp->SetValueString(m_LockJuly       ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_August_ID:    pProp->SetValueString(m_LockAugust     ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_September_ID: pProp->SetValueString(m_LockSeptember  ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_October_ID:   pProp->SetValueString(m_LockOctober    ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_November_ID:  pProp->SetValueString(m_LockNovember   ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_December_ID:  pProp->SetValueString(m_LockDecember   ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Force_Equalizer_ID:  pProp->SetValueString(m_ForceEqualizer ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::ApplyEqualizerToControls()
{
    bool error;

    // assign quantities to strings
    m_QuantityYear.Format     (g_FormatNumbers, m_Equalizer.GetTotal());
    m_QuantityJanuary.Format  (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexJanuary,   error));
    m_QuantityFebruary.Format (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexFebruary,  error));
    m_QuantityMarch.Format    (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexMarch,     error));
    m_QuantityApril.Format    (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexApril,     error));
    m_QuantityMay.Format      (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexMay,       error));
    m_QuantityJune.Format     (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexJune,      error));
    m_QuantityJuly.Format     (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexJuly,      error));
    m_QuantityAugust.Format   (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexAugust,    error));
    m_QuantitySeptember.Format(g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexSeptember, error));
    m_QuantityOctober.Format  (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexOctober,   error));
    m_QuantityNovember.Format (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexNovember,  error));
    m_QuantityDecember.Format (g_FormatNumbers, m_Equalizer.GetNumberAt(g_IndexDecember,  error));

    // assign slider values
    m_SliderSeptember.SetPos(int(double(m_Equalizer.GetNumberAt(g_IndexSeptember, error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderOctober.SetPos  (int(double(m_Equalizer.GetNumberAt(g_IndexOctober,   error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderNovember.SetPos (int(double(m_Equalizer.GetNumberAt(g_IndexNovember,  error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderMay.SetPos      (int(double(m_Equalizer.GetNumberAt(g_IndexMay,       error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderMarch.SetPos    (int(double(m_Equalizer.GetNumberAt(g_IndexMarch,     error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJune.SetPos     (int(double(m_Equalizer.GetNumberAt(g_IndexJune,      error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJuly.SetPos     (int(double(m_Equalizer.GetNumberAt(g_IndexJuly,      error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderJanuary.SetPos  (int(double(m_Equalizer.GetNumberAt(g_IndexJanuary,   error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderFebruary.SetPos (int(double(m_Equalizer.GetNumberAt(g_IndexFebruary,  error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderDecember.SetPos (int(double(m_Equalizer.GetNumberAt(g_IndexDecember,  error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderAugust.SetPos   (int(double(m_Equalizer.GetNumberAt(g_IndexAugust,    error) / m_Equalizer.GetTotal()) * 100.0));
    m_SliderApril.SetPos    (int(double(m_Equalizer.GetNumberAt(g_IndexApril,     error) / m_Equalizer.GetTotal()) * 100.0));

    UpdateData(FALSE);
}
//---------------------------------------------------------------------------
void PSS_EqualizeQuantityDlg::CheckControlState()
{
    UpdateData(TRUE);

    if (GetDlgItem(IDC_TOTAL_ACTIVATION))
        GetDlgItem(IDC_TOTAL_ACTIVATION)->EnableWindow(!m_LockYear);

    if (GetDlgItem(IDC_SEP_ACT_SLIDER))
        GetDlgItem(IDC_SEP_ACT_SLIDER)->EnableWindow(!m_LockSeptember);

    if (GetDlgItem(IDC_SEP_ACTIVATION))
        GetDlgItem(IDC_SEP_ACTIVATION)->EnableWindow(!m_LockSeptember);

    if (GetDlgItem(IDC_OCT_ACT_SLIDER))
        GetDlgItem(IDC_OCT_ACT_SLIDER)->EnableWindow(!m_LockOctober);

    if (GetDlgItem(IDC_OCT_ACTIVATION))
        GetDlgItem(IDC_OCT_ACTIVATION)->EnableWindow(!m_LockOctober);

    if (GetDlgItem(IDC_NOV_ACT_SLIDER))
        GetDlgItem(IDC_NOV_ACT_SLIDER)->EnableWindow(!m_LockNovember);

    if (GetDlgItem(IDC_NOV_ACTIVATION))
        GetDlgItem(IDC_NOV_ACTIVATION)->EnableWindow(!m_LockNovember);

    if (GetDlgItem(IDC_MAY_ACT_SLIDER))
        GetDlgItem(IDC_MAY_ACT_SLIDER)->EnableWindow(!m_LockMay);

    if (GetDlgItem(IDC_MAY_ACTIVATION))
        GetDlgItem(IDC_MAY_ACTIVATION)->EnableWindow(!m_LockMay);

    if (GetDlgItem(IDC_MAR_ACT_SLIDER))
        GetDlgItem(IDC_MAR_ACT_SLIDER)->EnableWindow(!m_LockMarch);

    if (GetDlgItem(IDC_MAR_ACTIVATION))
        GetDlgItem(IDC_MAR_ACTIVATION)->EnableWindow(!m_LockMarch);

    if (GetDlgItem(IDC_JUN_ACT_SLIDER))
        GetDlgItem(IDC_JUN_ACT_SLIDER)->EnableWindow(!m_LockJune);

    if (GetDlgItem(IDC_JUN_ACTIVATION))
        GetDlgItem(IDC_JUN_ACTIVATION)->EnableWindow(!m_LockJune);

    if (GetDlgItem(IDC_JUL_ACT_SLIDER))
        GetDlgItem(IDC_JUL_ACT_SLIDER)->EnableWindow(!m_LockJuly);

    if (GetDlgItem(IDC_JUL_ACTIVATION))
        GetDlgItem(IDC_JUL_ACTIVATION)->EnableWindow(!m_LockJuly);

    if (GetDlgItem(IDC_JAN_ACT_SLIDER))
        GetDlgItem(IDC_JAN_ACT_SLIDER)->EnableWindow(!m_LockJanuary);

    if (GetDlgItem(IDC_JAN_ACTIVATION))
        GetDlgItem(IDC_JAN_ACTIVATION)->EnableWindow(!m_LockJanuary);

    if (GetDlgItem(IDC_FEB_ACT_SLIDER))
        GetDlgItem(IDC_FEB_ACT_SLIDER)->EnableWindow(!m_LockFebruary);

    if (GetDlgItem(IDC_FEB_ACTIVATION))
        GetDlgItem(IDC_FEB_ACTIVATION)->EnableWindow(!m_LockFebruary);

    if (GetDlgItem(IDC_DEC_ACT_SLIDER))
        GetDlgItem(IDC_DEC_ACT_SLIDER)->EnableWindow(!m_LockDecember);

    if (GetDlgItem(IDC_DEC_ACTIVATION))
        GetDlgItem(IDC_DEC_ACTIVATION)->EnableWindow(!m_LockDecember);

    if (GetDlgItem(IDC_AUG_ACT_SLIDER))
        GetDlgItem(IDC_AUG_ACT_SLIDER)->EnableWindow(!m_LockAugust);

    if (GetDlgItem(IDC_AUG_ACTIVATION))
        GetDlgItem(IDC_AUG_ACTIVATION)->EnableWindow(!m_LockAugust);

    if (GetDlgItem(IDC_APR_ACT_SLIDER))
        GetDlgItem(IDC_APR_ACT_SLIDER)->EnableWindow(!m_LockApril);

    if (GetDlgItem(IDC_APR_ACTIVATION))
        GetDlgItem(IDC_APR_ACTIVATION)->EnableWindow(!m_LockApril);
}
//---------------------------------------------------------------------------
