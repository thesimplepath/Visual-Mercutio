/****************************************************************************
 * ==> PSS_NumbersEqualizer -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a numbers equalizer                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_NumbersEqualizer.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_NumbersEqualizer
//---------------------------------------------------------------------------
PSS_NumbersEqualizer& PSS_NumbersEqualizer::operator = (const PSS_NumbersEqualizer& other)
{
    // reset the array
    Reset();

    // copy objects
    PSS_EqNumberIterator it(&other.GetNumberSetConst());

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        m_Set.Add(pNumber->Clone());

    // copy member variables
    m_Total       = other.m_Total;
    m_MinValue    = other.m_MinValue;
    m_LockedTotal = other.m_LockedTotal;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetTotalEqualizeNumbers(double total)
{
    // set the new total
    SetTotal(total);

    // equalize all unlocked numbers function of percent
    PSS_EqNumberIterator it(&m_Set);

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (!pNumber->m_Locked)
            pNumber->m_Number = pNumber->m_Percent * total;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetTotalReEqualizeNumbers(double total)
{
    // calculate the amount to distribute, its the total less the sum of locked numbers which will not change
    const double remainingTotal = total - GetSumOfLockedNumbers();

    // set the new total
    SetTotal(total);

    // equalize all unlocked numbers function of percent
    PSS_EqNumberIterator it(&m_Set);

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (!pNumber->m_Locked)
            pNumber->m_Number = pNumber->m_Percent * remainingTotal;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::FillSet(PSS_EqNumberSet& set)
{
    Reset();

    PSS_EqNumberIterator it(&set);

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        m_Set.Add(pNumber);
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::FillSet(PSS_DoubleSet& set, bool locked)
{
    Reset();

    const int count = set.GetSize();

    for (int i = 0; i < count; ++i)
        m_Set.Add(new PSS_NumberEqualizer(set.GetAt(i), locked));
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetNumberAtEqualize(std::size_t index, double number)
{
    const double countLocked   = static_cast<double>(GetLockedCount());
    const double countUnlocked = static_cast<double>(GetUnlockedCount());
          double totalLocked   = GetSumOfLockedNumbers();
          double totalUnlocked = GetSumOfUnlockedNumbers();

    bool         error;
    const double previousNumber = GetNumberAt(index, error);

    if (error)
        return;

    // check that the minimum value is respected. If not, set the min value
    if (number < m_MinValue)
        number = m_MinValue;

    // this is what can be removed from elements
    const double maximumValue = totalUnlocked - previousNumber;

    // if the initial number is higher than the maximum value, set all elements to zero
    // and set the number to the maximum value
    if (number > totalUnlocked)
    {
        // set the new number
        SetNumberAt(index, totalUnlocked);

        // set all other unlocked value to zero
        SetValueToUnlockedNumbers(0, index);
    }
    else
    {
        // calculate the difference
        double diff = previousNumber - number;

        // set the new number
        SetNumberAt(index, number);

        do
        {
            const double valuePerElement = diff / (countUnlocked - 1);

            // add the difference per element, except for the current element
            AddDeltaToUnlockedNumbers(valuePerElement, index);

            // calculate the difference against the real sum
            diff = GetTotal() - GetSum();
        }
        while (diff > 0.01 || diff < -0.01);
    }

    // recalculate all percentages
    CalculatePercents();
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetPercentAtEqualize(std::size_t index, double percent)
{
    // calculate the new number
    const double newNumber = percent * GetTotal();

    // once calculated, call the SetNumberAtEqualize() function to assign its new value
    SetNumberAtEqualize(index, newNumber);
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::Reset()
{
    const int count = m_Set.GetSize();

    for (int i = 0; i < count; ++i)
        if (m_Set.GetAt(i))
            delete m_Set.GetAt(i);

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
double PSS_NumbersEqualizer::GetSum() const
{
    PSS_EqNumberIterator it(&m_Set);
    double               sum = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        sum += pNumber->m_Number;

    return sum;
}
//---------------------------------------------------------------------------
double PSS_NumbersEqualizer::GetSumOfLockedNumbers() const
{
    PSS_EqNumberIterator it(&m_Set);
    double               sum = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (pNumber->m_Locked)
            sum += pNumber->m_Number;

    return sum;
}
//---------------------------------------------------------------------------
double PSS_NumbersEqualizer::GetSumOfUnlockedNumbers() const
{
    PSS_EqNumberIterator it(&m_Set);
    double               sum = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (!pNumber->m_Locked)
            sum += pNumber->m_Number;

    return sum;
}
//---------------------------------------------------------------------------
std::size_t PSS_NumbersEqualizer::GetLockedCount() const
{
    PSS_EqNumberIterator it(&m_Set);
    std::size_t          counter = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (pNumber->m_Locked)
            ++counter;

    return counter;
}
//---------------------------------------------------------------------------
std::size_t PSS_NumbersEqualizer::GetUnlockedCount() const
{
    PSS_EqNumberIterator it(&m_Set);
    std::size_t          counter = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (!pNumber->m_Locked)
            ++counter;

    return counter;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetValueToLockedNumbers(double value, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (pNumber->m_Locked && n != indexToIgnore)
            pNumber->m_Number = value;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetValueToUnlockedNumbers(double value, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n = 0;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (!pNumber->m_Locked && n != indexToIgnore)
            pNumber->m_Number = value;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::AddDeltaToLockedNumbers(double delta, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n              = 0;
    bool                 deltaRespected = true;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (pNumber->m_Locked && n != indexToIgnore)
            if ((pNumber->m_Number + delta) < m_MinValue)
            {
                pNumber->m_Number = m_MinValue;
                deltaRespected = false;
            }
            else
                pNumber->m_Number += delta;

    return deltaRespected;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::AddDeltaToUnlockedNumbers(double delta, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n              = 0;
    bool                 deltaRespected = true;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (!pNumber->m_Locked && n != indexToIgnore)
            if ((pNumber->m_Number + delta) < m_MinValue)
            {
                pNumber->m_Number = m_MinValue;
                deltaRespected = false;
            }
            else
                pNumber->m_Number += delta;

    return deltaRespected;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::SubstDeltaToLockedNumbers(double delta, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n              = 0;
    bool                 deltaRespected = true;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (pNumber->m_Locked && n != indexToIgnore)
            if ((pNumber->m_Number - delta) < m_MinValue)
            {
                pNumber->m_Number = m_MinValue;
                deltaRespected = false;
            }
            else
                pNumber->m_Number -= delta;

    return deltaRespected;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::SubstDeltaToUnlockedNumbers(double delta, int indexToIgnore)
{
    PSS_EqNumberIterator it(&m_Set);
    int                  n              = 0;
    bool                 deltaRespected = true;

    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; ++n, pNumber = it.GetNext())
        if (!pNumber->m_Locked && n != indexToIgnore)
            if ((pNumber->m_Number - delta) < m_MinValue)
            {
                pNumber->m_Number = m_MinValue;
                deltaRespected = false;
            }
            else
                pNumber->m_Number -= delta;

    return deltaRespected;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::CalculatePercents()
{
    const double totalSum = GetTotal();

    PSS_EqNumberIterator it(&m_Set);

    // iterate through the list of elements and calculate the percentage
    for (PSS_NumberEqualizer* pNumber = it.GetFirst(); pNumber; pNumber = it.GetNext())
        if (totalSum > 0)
            pNumber->m_Percent = pNumber->m_Number / totalSum;
        else
            pNumber->m_Percent = 0;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::CalculatePercent(std::size_t index)
{
    if (index < GetCount())
    {
        PSS_NumberEqualizer* pNumber = m_Set.GetAt(index);
        pNumber->m_Percent = pNumber->m_Number / GetTotal();
    }
}
//---------------------------------------------------------------------------
