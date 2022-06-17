/****************************************************************************
 * ==> PSS_AnnualNumberPropertiesBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the annual number properties for banking process  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_AnnualNumberPropertiesBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_AnnualNumberPropertiesBP, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_AnnualNumberPropertiesBP
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP::PSS_AnnualNumberPropertiesBP(double totalNumber) :
    CObject(),
    m_ForceEqualizer(0)
{
    // set the year quantity to 1
    m_Equalizer.SetTotal(totalNumber);

    // calculates the value for one month
    const double oneMonthQuantity = totalNumber / g_NumberOfMonthPerYear;

    // assigns monthly values
    m_Equalizer.SetNumberAt(g_IndexJanuary,   oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexFebruary,  oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexMarch,     oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexApril,     oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexMay,       oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexJune,      oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexJuly,      oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexAugust,    oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexSeptember, oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexOctober,   oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexNovember,  oneMonthQuantity);
    m_Equalizer.SetNumberAt(g_IndexDecember,  oneMonthQuantity);

    // initialize the lock to false
    m_Equalizer.SetLockedTotal(false);
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary,   false);
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary,  false);
    m_Equalizer.SetLockedFlagAt(g_IndexMarch,     false);
    m_Equalizer.SetLockedFlagAt(g_IndexApril,     false);
    m_Equalizer.SetLockedFlagAt(g_IndexMay,       false);
    m_Equalizer.SetLockedFlagAt(g_IndexJune,      false);
    m_Equalizer.SetLockedFlagAt(g_IndexJuly,      false);
    m_Equalizer.SetLockedFlagAt(g_IndexAugust,    false);
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, false);
    m_Equalizer.SetLockedFlagAt(g_IndexOctober,   false);
    m_Equalizer.SetLockedFlagAt(g_IndexNovember,  false);
    m_Equalizer.SetLockedFlagAt(g_IndexDecember,  false);

    // calculate all percents according to values
    m_Equalizer.CalculatePercents();

    // don't show month details
    SetForceEqualizer(false);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP::PSS_AnnualNumberPropertiesBP(const PSS_AnnualNumberPropertiesBP& other) :
    CObject(),
    m_ForceEqualizer(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP::~PSS_AnnualNumberPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator = (const PSS_AnnualNumberPropertiesBP& other)
{
    m_Equalizer      = other.m_Equalizer;
    m_ForceEqualizer = other.m_ForceEqualizer;

    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator = (double value)
{
    SetAndCalculateQuantitiesBasedOnYear(value);
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator + (const PSS_AnnualNumberPropertiesBP& other)
{
    PSS_AnnualNumberPropertiesBP annualProp;

    for (std::size_t index = g_IndexJanuary; index < g_IndexDecember + 1; ++index)
        annualProp.SetNumberAt(index, GetNumberAt(index) + other.GetNumberAt(index));

    // all values are set, recalculate the total
    annualProp.CalculateNumberYear();
    annualProp.CalculatePercents();

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator + (double value)
{
    // initialize the result
    PSS_AnnualNumberPropertiesBP annualProp = *this;

    // add the total
    const double newValue = GetNumberYear() + value;

    // set the new total and calculate all others
    annualProp.SetAndCalculateQuantitiesBasedOnYear(newValue);

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator - (const PSS_AnnualNumberPropertiesBP& other)
{
    PSS_AnnualNumberPropertiesBP annualProp;

    for (std::size_t index = g_IndexJanuary; index < g_IndexDecember + 1; ++index)
        annualProp.SetNumberAt(index, GetNumberAt(index) - other.GetNumberAt(index));

    // all values are set, recalculate the total
    annualProp.CalculateNumberYear();
    annualProp.CalculatePercents();

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator - (double value)
{
    // initialize the result
    PSS_AnnualNumberPropertiesBP annualProp = *this;

    // subtract the total
    const double newValue = GetNumberYear() - value;

    // set the new total and calculate all others
    annualProp.SetAndCalculateQuantitiesBasedOnYear(newValue);

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator * (double value)
{
    // initialize the reslut
    PSS_AnnualNumberPropertiesBP annualProp = *this;

    // multiply the total
    const double newValue = GetNumberYear() * value;

    // set the new total and calculate all others
    annualProp.SetAndCalculateQuantitiesBasedOnYear(newValue);

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::operator / (double value)
{
    // initialize the reslut
    PSS_AnnualNumberPropertiesBP annualProp = *this;

    // divide the total
    const double newValue = value ? GetNumberYear() / value : 0;

    // set the new total and calculate all others
    annualProp.SetAndCalculateQuantitiesBasedOnYear(newValue);

    return annualProp;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::operator == (const PSS_AnnualNumberPropertiesBP& other) const
{
    return (GetNumberYear()          == other.GetNumberYear()          &&
            GetNumberJanuary()       == other.GetNumberJanuary()       &&
            GetNumberFebruary()      == other.GetNumberFebruary()      &&
            GetNumberMarch()         == other.GetNumberMarch()         &&
            GetNumberApril()         == other.GetNumberApril()         &&
            GetNumberJune()          == other.GetNumberJune()          &&
            GetNumberJuly()          == other.GetNumberJuly()          &&
            GetNumberAugust()        == other.GetNumberAugust()        &&
            GetNumberSeptember()     == other.GetNumberSeptember()     &&
            GetNumberOctober()       == other.GetNumberOctober()       &&
            GetNumberNovember()      == other.GetNumberNovember()      &&
            GetNumberDecember()      == other.GetNumberDecember()      &&
            GetLockNumberYear()      == other.GetLockNumberYear()      &&
            GetLockNumberJanuary()   == other.GetLockNumberJanuary()   &&
            GetLockNumberFebruary()  == other.GetLockNumberFebruary()  &&
            GetLockNumberMarch()     == other.GetLockNumberMarch()     &&
            GetLockNumberApril()     == other.GetLockNumberApril()     &&
            GetLockNumberMay()       == other.GetLockNumberMay()       &&
            GetLockNumberJune()      == other.GetLockNumberJune()      &&
            GetLockNumberJuly()      == other.GetLockNumberJuly()      &&
            GetLockNumberAugust()    == other.GetLockNumberAugust()    &&
            GetLockNumberSeptember() == other.GetLockNumberSeptember() &&
            GetLockNumberOctober()   == other.GetLockNumberOctober()   &&
            GetLockNumberNovember()  == other.GetLockNumberNovember()  &&
            GetLockNumberDecember()  == other.GetLockNumberDecember()  &&
            GetForceEqualizer()      == other.GetForceEqualizer());
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::Merge(PSS_AnnualNumberPropertiesBP* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_Year)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberYear(pProp->GetNumberYear());
                SetLockNumberYear(pProp->GetLockNumberYear());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberYear(pProp->GetLockNumberYear());
            else
                SetNumberYear(pProp->GetNumberYear());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_January)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberJanuary(pProp->GetNumberJanuary());
                SetLockNumberJanuary(pProp->GetLockNumberJanuary());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberJanuary(pProp->GetLockNumberJanuary());
            else
                SetNumberJanuary(pProp->GetNumberJanuary());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_February)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberFebruary(pProp->GetNumberFebruary());
                SetLockNumberFebruary(pProp->GetLockNumberFebruary());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberFebruary(pProp->GetLockNumberFebruary());
            else
                SetNumberFebruary(pProp->GetNumberFebruary());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_March)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberMarch(pProp->GetNumberMarch());
                SetLockNumberMarch(pProp->GetLockNumberMarch());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberMarch(pProp->GetLockNumberMarch());
            else
                SetNumberMarch(pProp->GetNumberMarch());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_April)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberApril(pProp->GetNumberApril());
                SetLockNumberApril(pProp->GetLockNumberApril());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberApril(pProp->GetLockNumberApril());
            else
                SetNumberApril(pProp->GetNumberApril());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_May)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberMay(pProp->GetNumberMay());
                SetLockNumberMay(pProp->GetLockNumberMay());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberMay(pProp->GetLockNumberMay());
            else
                SetNumberMay(pProp->GetNumberMay());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_June)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberJune(pProp->GetNumberJune());
                SetLockNumberJune(pProp->GetLockNumberJune());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberJune(pProp->GetLockNumberJune());
            else
                SetNumberJune(pProp->GetNumberJune());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_July)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberJuly(pProp->GetNumberJuly());
                SetLockNumberJuly(pProp->GetLockNumberJuly());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberJuly(pProp->GetLockNumberJuly());
            else
                SetNumberJuly(pProp->GetNumberJuly());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_August)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberAugust(pProp->GetNumberAugust());
                SetLockNumberAugust(pProp->GetLockNumberAugust());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberAugust(pProp->GetLockNumberAugust());
            else
                SetNumberAugust(pProp->GetNumberAugust());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_September)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberSeptember(pProp->GetNumberSeptember());
                SetLockNumberSeptember(pProp->GetLockNumberSeptember());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberSeptember(pProp->GetLockNumberSeptember());
            else
                SetNumberSeptember(pProp->GetNumberSeptember());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_October)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberOctober(pProp->GetNumberOctober());
                SetLockNumberOctober(pProp->GetLockNumberOctober());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberOctober(pProp->GetLockNumberOctober());
            else
                SetNumberOctober(pProp->GetNumberOctober());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_November)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberNovember(pProp->GetNumberNovember());
                SetLockNumberNovember(pProp->GetLockNumberNovember());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberNovember(pProp->GetLockNumberNovember());
            else
                SetNumberNovember(pProp->GetNumberNovember());

        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Number_December)
            if (changeFlags & (DWORD)IEChangeType::IE_CT_All)
            {
                SetNumberDecember(pProp->GetNumberDecember());
                SetLockNumberDecember(pProp->GetLockNumberDecember());
            }
            else
            if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Locked_Month)
                SetLockNumberDecember(pProp->GetLockNumberDecember());
            else
                SetNumberDecember(pProp->GetNumberDecember());
    }
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::IsEqual(PSS_AnnualNumberPropertiesBP* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnYear(const double value)
{
    m_Equalizer.SetTotalEqualizeNumbers(value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnJanuary(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexJanuary, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnFebruary(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexFebruary, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnMarch(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexMarch, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnApril(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexApril, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnMay(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexMay, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnJune(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexJune, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnJuly(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexJuly, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnAugust(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexAugust, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnSeptember(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexSeptember, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnOctober(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexOctober, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnNovember(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexNovember, value);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetAndCalculateQuantitiesBasedOnDecember(const double value)
{
    m_Equalizer.SetNumberAtEqualize(g_IndexDecember, value);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::Min(const PSS_AnnualNumberPropertiesBP& left,
                                                               const PSS_AnnualNumberPropertiesBP& right)
{
    PSS_AnnualNumberPropertiesBP annualProp;

    for (std::size_t index = g_IndexJanuary; index < g_IndexDecember + 1; ++index)
        annualProp.SetNumberAt(index, __min(left.GetNumberAt(index), right.GetNumberAt(index)));

    // all values are set, recalculate the total
    annualProp.CalculateNumberYear();
    annualProp.CalculatePercents();

    return annualProp;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::Max(const PSS_AnnualNumberPropertiesBP& left,
                                                               const PSS_AnnualNumberPropertiesBP& right)
{
    PSS_AnnualNumberPropertiesBP annualProp;

    for (std::size_t index = g_IndexJanuary; index < g_IndexDecember + 1; ++index)
        annualProp.SetNumberAt(index, __max(left.GetNumberAt(index), right.GetNumberAt(index)));

    // all values are set, recalculate the total
    annualProp.CalculateNumberYear();
    annualProp.CalculatePercents();

    return annualProp;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, int& value) const
{
    // only used to get the lock flag value
    switch (propId)
    {
        case M_Locked_Year_ID:      value = static_cast<int>(GetLockNumberYear());      break;
        case M_Locked_January_ID:   value = static_cast<int>(GetLockNumberJanuary());   break;
        case M_Locked_February_ID:  value = static_cast<int>(GetLockNumberFebruary());  break;
        case M_Locked_March_ID:     value = static_cast<int>(GetLockNumberMarch());     break;
        case M_Locked_April_ID:     value = static_cast<int>(GetLockNumberApril());     break;
        case M_Locked_May_ID:       value = static_cast<int>(GetLockNumberMay());       break;
        case M_Locked_June_ID:      value = static_cast<int>(GetLockNumberJune());      break;
        case M_Locked_July_ID:      value = static_cast<int>(GetLockNumberJuly());      break;
        case M_Locked_August_ID:    value = static_cast<int>(GetLockNumberAugust());    break;
        case M_Locked_September_ID: value = static_cast<int>(GetLockNumberSeptember()); break;
        case M_Locked_October_ID:   value = static_cast<int>(GetLockNumberOctober());   break;
        case M_Locked_November_ID:  value = static_cast<int>(GetLockNumberNovember());  break;
        case M_Locked_December_ID:  value = static_cast<int>(GetLockNumberDecember());  break;
        case M_Force_Equalizer_ID:  value = static_cast<int>(GetForceEqualizer());      break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, UINT& value) const
{
    // only used to get the lock flag value
    switch (propId)
    {
        case M_Locked_Year_ID:      value = GetLockNumberYear();      break;
        case M_Locked_January_ID:   value = GetLockNumberJanuary();   break;
        case M_Locked_February_ID:  value = GetLockNumberFebruary();  break;
        case M_Locked_March_ID:     value = GetLockNumberMarch();     break;
        case M_Locked_April_ID:     value = GetLockNumberApril();     break;
        case M_Locked_May_ID:       value = GetLockNumberMay();       break;
        case M_Locked_June_ID:      value = GetLockNumberJune();      break;
        case M_Locked_July_ID:      value = GetLockNumberJuly();      break;
        case M_Locked_August_ID:    value = GetLockNumberAugust();    break;
        case M_Locked_September_ID: value = GetLockNumberSeptember(); break;
        case M_Locked_October_ID:   value = GetLockNumberOctober();   break;
        case M_Locked_November_ID:  value = GetLockNumberNovember();  break;
        case M_Locked_December_ID:  value = GetLockNumberDecember();  break;
        case M_Force_Equalizer_ID:  value = GetForceEqualizer();      break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    // only used to get the lock flag value
    switch (propId)
    {
        case M_Locked_Year_ID:      value = static_cast<DWORD>(GetLockNumberYear());      break;
        case M_Locked_January_ID:   value = static_cast<DWORD>(GetLockNumberJanuary());   break;
        case M_Locked_February_ID:  value = static_cast<DWORD>(GetLockNumberFebruary());  break;
        case M_Locked_March_ID:     value = static_cast<DWORD>(GetLockNumberMarch());     break;
        case M_Locked_April_ID:     value = static_cast<DWORD>(GetLockNumberApril());     break;
        case M_Locked_May_ID:       value = static_cast<DWORD>(GetLockNumberMay());       break;
        case M_Locked_June_ID:      value = static_cast<DWORD>(GetLockNumberJune());      break;
        case M_Locked_July_ID:      value = static_cast<DWORD>(GetLockNumberJuly());      break;
        case M_Locked_August_ID:    value = static_cast<DWORD>(GetLockNumberAugust());    break;
        case M_Locked_September_ID: value = static_cast<DWORD>(GetLockNumberSeptember()); break;
        case M_Locked_October_ID:   value = static_cast<DWORD>(GetLockNumberOctober());   break;
        case M_Locked_November_ID:  value = static_cast<DWORD>(GetLockNumberNovember());  break;
        case M_Locked_December_ID:  value = static_cast<DWORD>(GetLockNumberDecember());  break;
        case M_Force_Equalizer_ID:  value = static_cast<DWORD>(GetForceEqualizer());      break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, float& value) const
{
    // only used to get quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      value = static_cast<float>(GetNumberYear());      break;
        case M_Number_January_ID:   value = static_cast<float>(GetNumberJanuary());   break;
        case M_Number_February_ID:  value = static_cast<float>(GetNumberFebruary());  break;
        case M_Number_March_ID:     value = static_cast<float>(GetNumberMarch());     break;
        case M_Number_April_ID:     value = static_cast<float>(GetNumberApril());     break;
        case M_Number_May_ID:       value = static_cast<float>(GetNumberMay());       break;
        case M_Number_June_ID:      value = static_cast<float>(GetNumberJune());      break;
        case M_Number_July_ID:      value = static_cast<float>(GetNumberJuly());      break;
        case M_Number_August_ID:    value = static_cast<float>(GetNumberAugust());    break;
        case M_Number_September_ID: value = static_cast<float>(GetNumberSeptember()); break;
        case M_Number_October_ID:   value = static_cast<float>(GetNumberOctober());   break;
        case M_Number_November_ID:  value = static_cast<float>(GetNumberNovember());  break;
        case M_Number_December_ID:  value = static_cast<float>(GetNumberDecember());  break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, double& value) const
{
    // only used to get quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      value = GetNumberYear();      break;
        case M_Number_January_ID:   value = GetNumberJanuary();   break;
        case M_Number_February_ID:  value = GetNumberFebruary();  break;
        case M_Number_March_ID:     value = GetNumberMarch();     break;
        case M_Number_April_ID:     value = GetNumberApril();     break;
        case M_Number_May_ID:       value = GetNumberMay();       break;
        case M_Number_June_ID:      value = GetNumberJune();      break;
        case M_Number_July_ID:      value = GetNumberJuly();      break;
        case M_Number_August_ID:    value = GetNumberAugust();    break;
        case M_Number_September_ID: value = GetNumberSeptember(); break;
        case M_Number_October_ID:   value = GetNumberOctober();   break;
        case M_Number_November_ID:  value = GetNumberNovember();  break;
        case M_Number_December_ID:  value = GetNumberDecember();  break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::GetValue(const int propId, CString& value) const
{
    // only used to get quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      value.Format(_T("%.2f"), GetNumberYear());      break;
        case M_Number_January_ID:   value.Format(_T("%.2f"), GetNumberJanuary());   break;
        case M_Number_February_ID:  value.Format(_T("%.2f"), GetNumberFebruary());  break;
        case M_Number_March_ID:     value.Format(_T("%.2f"), GetNumberMarch());     break;
        case M_Number_April_ID:     value.Format(_T("%.2f"), GetNumberApril());     break;
        case M_Number_May_ID:       value.Format(_T("%.2f"), GetNumberMay());       break;
        case M_Number_June_ID:      value.Format(_T("%.2f"), GetNumberJune());      break;
        case M_Number_July_ID:      value.Format(_T("%.2f"), GetNumberJuly());      break;
        case M_Number_August_ID:    value.Format(_T("%.2f"), GetNumberAugust());    break;
        case M_Number_September_ID: value.Format(_T("%.2f"), GetNumberSeptember()); break;
        case M_Number_October_ID:   value.Format(_T("%.2f"), GetNumberOctober());   break;
        case M_Number_November_ID:  value.Format(_T("%.2f"), GetNumberNovember());  break;
        case M_Number_December_ID:  value.Format(_T("%.2f"), GetNumberDecember());  break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, const int value)
{
    // only used to set locked flags
    switch (propId)
    {
        case M_Locked_Year_ID:      SetLockNumberYearEx     (static_cast<UINT>(value)); break;
        case M_Locked_January_ID:   SetLockNumberJanuaryEx  (static_cast<UINT>(value)); break;
        case M_Locked_February_ID:  SetLockNumberFebruaryEx (static_cast<UINT>(value)); break;
        case M_Locked_March_ID:     SetLockNumberMarchEx    (static_cast<UINT>(value)); break;
        case M_Locked_April_ID:     SetLockNumberAprilEx    (static_cast<UINT>(value)); break;
        case M_Locked_May_ID:       SetLockNumberMayEx      (static_cast<UINT>(value)); break;
        case M_Locked_June_ID:      SetLockNumberJuneEx     (static_cast<UINT>(value)); break;
        case M_Locked_July_ID:      SetLockNumberJulyEx     (static_cast<UINT>(value)); break;
        case M_Locked_August_ID:    SetLockNumberAugustEx   (static_cast<UINT>(value)); break;
        case M_Locked_September_ID: SetLockNumberSeptemberEx(static_cast<UINT>(value)); break;
        case M_Locked_October_ID:   SetLockNumberOctoberEx  (static_cast<UINT>(value)); break;
        case M_Locked_November_ID:  SetLockNumberNovemberEx (static_cast<UINT>(value)); break;
        case M_Locked_December_ID:  SetLockNumberDecemberEx (static_cast<UINT>(value)); break;
        case M_Force_Equalizer_ID:  SetForceEqualizerEx     (static_cast<UINT>(value)); break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, const UINT value)
{
    // only used to set locked flags
    switch (propId)
    {
        case M_Locked_Year_ID:      SetLockNumberYearEx(value);      break;
        case M_Locked_January_ID:   SetLockNumberJanuaryEx(value);   break;
        case M_Locked_February_ID:  SetLockNumberFebruaryEx(value);  break;
        case M_Locked_March_ID:     SetLockNumberMarchEx(value);     break;
        case M_Locked_April_ID:     SetLockNumberAprilEx(value);     break;
        case M_Locked_May_ID:       SetLockNumberMayEx(value);       break;
        case M_Locked_June_ID:      SetLockNumberJuneEx(value);      break;
        case M_Locked_July_ID:      SetLockNumberJulyEx(value);      break;
        case M_Locked_August_ID:    SetLockNumberAugustEx(value);    break;
        case M_Locked_September_ID: SetLockNumberSeptemberEx(value); break;
        case M_Locked_October_ID:   SetLockNumberOctoberEx(value);   break;
        case M_Locked_November_ID:  SetLockNumberNovemberEx(value);  break;
        case M_Locked_December_ID:  SetLockNumberDecemberEx(value);  break;
        case M_Force_Equalizer_ID:  SetForceEqualizerEx(value);      break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, const DWORD value)
{
    // only used to set locked flags
    switch (propId)
    {
        case M_Locked_Year_ID:      SetLockNumberYearEx     (static_cast<UINT>(value)); break;
        case M_Locked_January_ID:   SetLockNumberJanuaryEx  (static_cast<UINT>(value)); break;
        case M_Locked_February_ID:  SetLockNumberFebruaryEx (static_cast<UINT>(value)); break;
        case M_Locked_March_ID:     SetLockNumberMarchEx    (static_cast<UINT>(value)); break;
        case M_Locked_April_ID:     SetLockNumberAprilEx    (static_cast<UINT>(value)); break;
        case M_Locked_May_ID:       SetLockNumberMayEx      (static_cast<UINT>(value)); break;
        case M_Locked_June_ID:      SetLockNumberJuneEx     (static_cast<UINT>(value)); break;
        case M_Locked_July_ID:      SetLockNumberJulyEx     (static_cast<UINT>(value)); break;
        case M_Locked_August_ID:    SetLockNumberAugustEx   (static_cast<UINT>(value)); break;
        case M_Locked_September_ID: SetLockNumberSeptemberEx(static_cast<UINT>(value)); break;
        case M_Locked_October_ID:   SetLockNumberOctoberEx  (static_cast<UINT>(value)); break;
        case M_Locked_November_ID:  SetLockNumberNovemberEx (static_cast<UINT>(value)); break;
        case M_Locked_December_ID:  SetLockNumberDecemberEx (static_cast<UINT>(value)); break;
        case M_Force_Equalizer_ID:  SetForceEqualizerEx     (static_cast<UINT>(value)); break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, const float value)
{
    // only used to set quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      SetNumberYear(value);      break;
        case M_Number_January_ID:   SetNumberJanuary(value);   break;
        case M_Number_February_ID:  SetNumberFebruary(value);  break;
        case M_Number_March_ID:     SetNumberMarch(value);     break;
        case M_Number_April_ID:     SetNumberApril(value);     break;
        case M_Number_May_ID:       SetNumberMay(value);       break;
        case M_Number_June_ID:      SetNumberJune(value);      break;
        case M_Number_July_ID:      SetNumberJuly(value);      break;
        case M_Number_August_ID:    SetNumberAugust(value);    break;
        case M_Number_September_ID: SetNumberSeptember(value); break;
        case M_Number_October_ID:   SetNumberOctober(value);   break;
        case M_Number_November_ID:  SetNumberNovember(value);  break;
        case M_Number_December_ID:  SetNumberDecember(value);  break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, const double value)
{
    // only used to set quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      SetNumberYear(value);      break;
        case M_Number_January_ID:   SetNumberJanuary(value);   break;
        case M_Number_February_ID:  SetNumberFebruary(value);  break;
        case M_Number_March_ID:     SetNumberMarch(value);     break;
        case M_Number_April_ID:     SetNumberApril(value);     break;
        case M_Number_May_ID:       SetNumberMay(value);       break;
        case M_Number_June_ID:      SetNumberJune(value);      break;
        case M_Number_July_ID:      SetNumberJuly(value);      break;
        case M_Number_August_ID:    SetNumberAugust(value);    break;
        case M_Number_September_ID: SetNumberSeptember(value); break;
        case M_Number_October_ID:   SetNumberOctober(value);   break;
        case M_Number_November_ID:  SetNumberNovember(value);  break;
        case M_Number_December_ID:  SetNumberDecember(value);  break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnnualNumberPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    // only used to set quantity values
    switch (propId)
    {
        case M_Number_Year_ID:      SetNumberYear     (static_cast<float>(std::atof(pValue))); break;
        case M_Number_January_ID:   SetNumberJanuary  (static_cast<float>(std::atof(pValue))); break;
        case M_Number_February_ID:  SetNumberFebruary (static_cast<float>(std::atof(pValue))); break;
        case M_Number_March_ID:     SetNumberMarch    (static_cast<float>(std::atof(pValue))); break;
        case M_Number_April_ID:     SetNumberApril    (static_cast<float>(std::atof(pValue))); break;
        case M_Number_May_ID:       SetNumberMay      (static_cast<float>(std::atof(pValue))); break;
        case M_Number_June_ID:      SetNumberJune     (static_cast<float>(std::atof(pValue))); break;
        case M_Number_July_ID:      SetNumberJuly     (static_cast<float>(std::atof(pValue))); break;
        case M_Number_August_ID:    SetNumberAugust   (static_cast<float>(std::atof(pValue))); break;
        case M_Number_September_ID: SetNumberSeptember(static_cast<float>(std::atof(pValue))); break;
        case M_Number_October_ID:   SetNumberOctober  (static_cast<float>(std::atof(pValue))); break;
        case M_Number_November_ID:  SetNumberNovember (static_cast<float>(std::atof(pValue))); break;
        case M_Number_December_ID:  SetNumberDecember (static_cast<float>(std::atof(pValue))); break;
        default:                    throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_AnnualNumberPropertiesBP::Serialize - Start Save\n");

        PUT_SCHEMA(ar, PSS_AnnualNumberPropertiesBP);

        ar << GetNumberYear();
        ar << GetNumberJanuary();
        ar << GetNumberFebruary();
        ar << GetNumberMarch();
        ar << GetNumberApril();
        ar << GetNumberMay();
        ar << GetNumberJune();
        ar << GetNumberJuly();
        ar << GetNumberAugust();
        ar << GetNumberSeptember();
        ar << GetNumberOctober();
        ar << GetNumberNovember();
        ar << GetNumberDecember();

        ar << UINT(GetLockNumberYear());
        ar << UINT(GetLockNumberJanuary());
        ar << UINT(GetLockNumberFebruary());
        ar << UINT(GetLockNumberMarch());
        ar << UINT(GetLockNumberApril());
        ar << UINT(GetLockNumberMay());
        ar << UINT(GetLockNumberJune());
        ar << UINT(GetLockNumberJuly());
        ar << UINT(GetLockNumberAugust());
        ar << UINT(GetLockNumberSeptember());
        ar << UINT(GetLockNumberOctober());
        ar << UINT(GetLockNumberNovember());
        ar << UINT(GetLockNumberDecember());
        ar << UINT(GetForceEqualizer());

        TRACE("PSS_AnnualNumberPropertiesBP::Serialize - End Save\n");
    }
    else
    {
        TRACE("PSS_AnnualNumberPropertiesBP::Serialize - Start Read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        double value;
        ar >> value;
        SetNumberYear(value);
        ar >> value;
        SetNumberJanuary(value);
        ar >> value;
        SetNumberFebruary(value);
        ar >> value;
        SetNumberMarch(value);
        ar >> value;
        SetNumberApril(value);
        ar >> value;
        SetNumberMay(value);
        ar >> value;
        SetNumberJune(value);
        ar >> value;
        SetNumberJuly(value);
        ar >> value;
        SetNumberAugust(value);
        ar >> value;
        SetNumberSeptember(value);
        ar >> value;
        SetNumberOctober(value);
        ar >> value;
        SetNumberNovember(value);
        ar >> value;
        SetNumberDecember(value);

        UINT lock;
        ar >> lock;
        SetLockNumberYearEx(lock);
        ar >> lock;
        SetLockNumberJanuaryEx(lock);
        ar >> lock;
        SetLockNumberFebruaryEx(lock);
        ar >> lock;
        SetLockNumberMarchEx(lock);
        ar >> lock;
        SetLockNumberAprilEx(lock);
        ar >> lock;
        SetLockNumberMayEx(lock);
        ar >> lock;
        SetLockNumberJuneEx(lock);
        ar >> lock;
        SetLockNumberJulyEx(lock);
        ar >> lock;
        SetLockNumberAugustEx(lock);
        ar >> lock;
        SetLockNumberSeptemberEx(lock);
        ar >> lock;
        SetLockNumberOctoberEx(lock);
        ar >> lock;
        SetLockNumberNovemberEx(lock);
        ar >> lock;
        SetLockNumberDecemberEx(lock);
        ar >> lock;
        SetForceEqualizerEx(lock);

        TRACE("PSS_AnnualNumberPropertiesBP::Serialize - End Read\n");

        CalculatePercents();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_AnnualNumberPropertiesBP::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_AnnualNumberPropertiesBP::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
