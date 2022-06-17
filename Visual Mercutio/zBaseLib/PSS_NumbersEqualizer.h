/****************************************************************************
 * ==> PSS_NumbersEqualizer -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a numbers equalizer                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NumbersEqualizerH
#define PSS_NumbersEqualizerH

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

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Number equalizer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_NumberEqualizer
{
    public:
        /**
        * Constructor
        *@param number - number
        *@param locked - if true, the number is locked
        */
        inline PSS_NumberEqualizer(double number = 0, bool locked = false);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_NumberEqualizer(const PSS_NumberEqualizer& other);

        virtual inline ~PSS_NumberEqualizer();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        inline PSS_NumberEqualizer& operator = (const PSS_NumberEqualizer& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual inline PSS_NumberEqualizer* Clone() const;

    public:
        double m_Number;
        double m_Percent;
        bool   m_Locked;
};

//---------------------------------------------------------------------------
// PSS_NumberEqualizer
//---------------------------------------------------------------------------
PSS_NumberEqualizer::PSS_NumberEqualizer(double number, bool locked) :
    m_Number(number),
    m_Percent(0.0),
    m_Locked(locked)
{}
//---------------------------------------------------------------------------
PSS_NumberEqualizer::PSS_NumberEqualizer(const PSS_NumberEqualizer& other) :
    m_Number(0.0),
    m_Percent(0.0),
    m_Locked(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_NumberEqualizer::~PSS_NumberEqualizer()
{}
//---------------------------------------------------------------------------
PSS_NumberEqualizer& PSS_NumberEqualizer::operator = (const PSS_NumberEqualizer& other)
{
    m_Number  = other.m_Number;
    m_Locked  = other.m_Locked;
    m_Percent = other.m_Percent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_NumberEqualizer* PSS_NumberEqualizer::Clone() const
{
    return new PSS_NumberEqualizer(*this);
}
//---------------------------------------------------------------------------

/**
* Array of number equalizer
*/
typedef CCArray_T<PSS_NumberEqualizer*, PSS_NumberEqualizer*> PSS_EqNumberSet;

/**
* An iterator for number equalizer collections
*/
typedef Iterator_T<PSS_NumberEqualizer*> PSS_EqNumberIterator;

/**
* Array of double
*/
typedef CCArray_T<double, double> PSS_DoubleSet;

/**
* An iterator for double set collections
*/
typedef Iterator_T<double> PSS_DoubleIterator;

/**
* Numbers equalizer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NumbersEqualizer
{
    public:
        /**
        * Constructor
        *@param minValue - minimum value
        */
        inline PSS_NumbersEqualizer(const double minValue = 0);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        inline PSS_NumbersEqualizer(const PSS_NumbersEqualizer& other);

        virtual inline ~PSS_NumbersEqualizer();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_NumbersEqualizer& operator = (const PSS_NumbersEqualizer& right);

        /**
        * Gets the total
        *@return the total
        */
        virtual inline double GetTotal() const;

        /**
        * Sets the total
        *@param total - total
        */
        virtual inline void SetTotal(double Total);

        /**
        * Sets the total with equalization
        *@param total - total
        */
        virtual void SetTotalEqualizeNumbers(double total);

        /**
        * Sets the total and re-equalize the remaining number with the difference
        *@param total - total
        */
        virtual void SetTotalReEqualizeNumbers(double total);

        /**
        * Gets if the total is locked
        *@return true if the total is locked, otherwise false
        */
        virtual inline bool GetLockedTotal() const;

        /**
        * Sets if the total is locked
        *@param value - if true, the total is locked
        */
        virtual inline void SetLockedTotal(bool value);

        /**
        * Fills the number equalizer set
        *@param[out] set - set to fill
        */
        virtual void FillSet(PSS_EqNumberSet& set);

        /**
        * Fills the double set
        *@param[out] set - set to fill
        *@param locked - if true, the total will be locked
        */
        virtual void FillSet(PSS_DoubleSet& set, bool locked = false);

        /**
        * Adds a number to equalize
        *@param number - number
        *@param locked - if true, the number will be locked
        */
        virtual inline void AddNumber(double number, bool locked = false);

        /**
        * Sets a number at index
        *@param index - index
        *@param number - number
        *@param locked - if true, the number will be locked
        */
        virtual inline void SetNumberAt(std::size_t index, double number, bool locked);

        /**
        * Sets a number at index
        *@param index - index
        *@param number - number
        */
        virtual inline void SetNumberAt(std::size_t index, double number);

        /**
        * Sets a specific number at index and equalize all other numbers
        *@param index - index
        *@param number - number
        */
        virtual void SetNumberAtEqualize(std::size_t index, double number);

        /**
        * Sets a specific percent at index and equalize all other numbers
        *@param index - index
        *@param percent - percent
        */
        virtual void SetPercentAtEqualize(std::size_t index, double percent);

        /**
        * Sets the locked flag at index
        *@param index - index
        *@param locked - if true, the number will be locked
        */
        virtual inline void SetLockedFlagAt(std::size_t index, bool locked);

        /**
        * Gets the number at index
        *@param index - index
        *@param[out] error - if true, an error occurred
        *@return the number
        */
        virtual inline double GetNumberAt(std::size_t index, bool& error) const;

        /**
        * Gets the locked flag at index
        *@param index - index
        *@param[out] error - if true, an error occurred
        *@return the locked flag
        */
        virtual inline bool GetLockedFlagAt(std::size_t index, bool& error) const;

        /**
        * Resets the equalizer
        */
        virtual void Reset();

        /**
        * Gets the sum of all numbers
        *@return the sum of all numbers
        */
        virtual double GetSum() const;

        /**
        * Gets the sum of all locked numbers
        *@return the sum of all locked numbers
        */
        virtual double GetSumOfLockedNumbers() const;

        /**
        * Gets the sum of all unlocked numbers
        *@return the sum of all unlocked numbers
        */
        virtual double GetSumOfUnlockedNumbers() const;

        /**
        * Gets the number count
        *@return the number count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Gets the locked number count
        *@return the locked number count
        */
        virtual std::size_t GetLockedCount() const;

        /**
        * Gets the unlocked number count
        *@return the unlocked number count
        */
        virtual std::size_t GetUnlockedCount() const;

        /**
        * Sets the same value to locked numbers
        *@param value - value to set
        *@param indexToIgnore - index to ignore, none if -1
        */
        virtual void SetValueToLockedNumbers(double value, int indexToIgnore = -1);

        /**
        * Sets the same value to unlocked numbers
        *@param value - value to set
        *@param indexToIgnore - index to ignore, none if -1
        */
        virtual void SetValueToUnlockedNumbers(double value, int indexToIgnore = -1);

        /**
        * Adds a delta to locked numbers
        *@param delta - delta
        *@param indexToIgnore - index to ignore, none if -1
        *@return true if all numbers have been updated by the specific delta, false if the system has forced
        *        one number due to the min value
        */
        virtual bool AddDeltaToLockedNumbers(double delta, int indexToIgnore = -1);

        /**
        * Adds a delta to unlocked numbers
        *@param delta - delta
        *@param indexToIgnore - index to ignore, none if -1
        *@return true if all numbers have been updated by the specific delta, false if the system has forced
        *        one number due to the min value
        */
        virtual bool AddDeltaToUnlockedNumbers(double delta, int indexToIgnore = -1);

        /**
        * Subtracts a delta to locked numbers
        *@param delta - delta
        *@param indexToIgnore - index to ignore, none if -1
        *@return true if all numbers have been updated by the specific delta, false if the system has forced
        *        one number due to the min value
        */
        virtual bool SubstDeltaToLockedNumbers(double delta, int indexToIgnore = -1);

        /**
        * Subtracts a delta to unlocked numbers
        *@param delta - delta
        *@param indexToIgnore - index to ignore, none if -1
        *@return true if all numbers have been updated by the specific delta, false if the system has forced
        *        one number due to the min value
        */
        virtual bool SubstDeltaToUnlockedNumbers(double delta, int indexToIgnore = -1);

        /**
        * Calculates the percent of all numbers
        */
        virtual void CalculatePercents();

        /**
        * Calculates the percent of a specific element at index
        *@param index - index
        */
        virtual void CalculatePercent(std::size_t index);

        /**
        * Gets the number set
        *@return the number set
        */
        virtual inline const PSS_EqNumberSet& GetNumberSetConst() const;

    private:
        PSS_EqNumberSet m_Set;
        double          m_Total;
        double          m_MinValue;
        bool            m_LockedTotal;
};

//---------------------------------------------------------------------------
// PSS_NumbersEqualizer
//---------------------------------------------------------------------------
PSS_NumbersEqualizer::PSS_NumbersEqualizer(const double minValue) :
    m_Total(0.0),
    m_MinValue(minValue),
    m_LockedTotal(false)
{}
//---------------------------------------------------------------------------
PSS_NumbersEqualizer::PSS_NumbersEqualizer(const PSS_NumbersEqualizer& other) :
    m_Total(0.0),
    m_MinValue(0.0),
    m_LockedTotal(false)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_NumbersEqualizer::~PSS_NumbersEqualizer()
{
    // NOTE use the fully qualified name to avoid to call pure virtual functions while destruction
    PSS_NumbersEqualizer::Reset();
}
//---------------------------------------------------------------------------
double PSS_NumbersEqualizer::GetTotal() const
{
    return m_Total;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetTotal(double Total)
{
    m_Total = Total;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::GetLockedTotal() const
{
    return m_LockedTotal;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetLockedTotal(bool value)
{
    m_LockedTotal = value;
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::AddNumber(double number, bool locked)
{
    m_Set.Add(new PSS_NumberEqualizer(number, locked));
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetNumberAt(std::size_t index, double number, bool locked)
{
    if (index < GetCount())
    {
        m_Set.GetAt(index)->m_Number = number;
        m_Set.GetAt(index)->m_Locked = locked;
    }
    else
        m_Set.SetAtGrow(index, new PSS_NumberEqualizer(number, locked));
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetNumberAt(std::size_t index, double number)
{
    if (index < GetCount())
        m_Set.GetAt(index)->m_Number = number;
    else
        m_Set.SetAtGrow(index, new PSS_NumberEqualizer(number));
}
//---------------------------------------------------------------------------
void PSS_NumbersEqualizer::SetLockedFlagAt(std::size_t index, bool locked)
{
    if (index < GetCount())
        m_Set.GetAt(index)->m_Locked = locked;
    else
        m_Set.SetAtGrow(index, new PSS_NumberEqualizer(0, locked));
}
//---------------------------------------------------------------------------
double PSS_NumbersEqualizer::GetNumberAt(std::size_t index, bool& error) const
{
    if (index < GetCount())
    {
        error = false;
        return m_Set.GetAt(index)->m_Number;
    }

    error = true;
    return 0;
}
//---------------------------------------------------------------------------
bool PSS_NumbersEqualizer::GetLockedFlagAt(std::size_t index, bool& error) const
{
    if (index < GetCount())
    {
        error = false;
        return m_Set.GetAt(index)->m_Locked;
    }

    error = true;
    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_NumbersEqualizer::GetCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
const PSS_EqNumberSet& PSS_NumbersEqualizer::GetNumberSetConst() const
{
    return m_Set;
}
//---------------------------------------------------------------------------

#endif
