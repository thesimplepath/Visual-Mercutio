/****************************************************************************
 * ==> PSS_AnnualNumberPropertiesBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the annual number properties for banking process  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AnnualNumberPropertiesBPH
#define PSS_AnnualNumberPropertiesBPH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_AnnualNumberPropertiesBP
    #define PSS_AnnualNumberPropertiesBP ZBBPAnnualNumberProperties
#endif

// processsoft
#include "zBaseLib\PSS_NumbersEqualizer.h"
#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Number_Year_ID      1
#define M_Number_January_ID   2
#define M_Number_February_ID  3
#define M_Number_March_ID     4
#define M_Number_April_ID     5
#define M_Number_May_ID       6
#define M_Number_June_ID      7
#define M_Number_July_ID      8
#define M_Number_August_ID    9
#define M_Number_September_ID 10
#define M_Number_October_ID   11
#define M_Number_November_ID  12
#define M_Number_December_ID  13
#define M_Locked_Year_ID      14
#define M_Locked_January_ID   15
#define M_Locked_February_ID  16
#define M_Locked_March_ID     17
#define M_Locked_April_ID     18
#define M_Locked_May_ID       19
#define M_Locked_June_ID      20
#define M_Locked_July_ID      21
#define M_Locked_August_ID    22
#define M_Locked_September_ID 23
#define M_Locked_October_ID   24
#define M_Locked_November_ID  25
#define M_Locked_December_ID  26
#define M_Force_Equalizer_ID  27
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const double g_NumberOfMonthPerYear = 12;
//---------------------------------------------------------------------------

/**
* Annual number properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_AnnualNumberPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_AnnualNumberPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Number_Year      = 0x0001,
            IE_CT_Change_Number_January   = 0x0002,
            IE_CT_Change_Number_February  = 0x0004,
            IE_CT_Change_Number_March     = 0x0008,
            IE_CT_Change_Number_April     = 0x0010,
            IE_CT_Change_Number_May       = 0x0020,
            IE_CT_Change_Number_June      = 0x0040,
            IE_CT_Change_Number_July      = 0x0080,
            IE_CT_Change_Number_August    = 0x0100,
            IE_CT_Change_Number_September = 0x0200,
            IE_CT_Change_Number_October   = 0x0400,
            IE_CT_Change_Number_November  = 0x0800,
            IE_CT_Change_Number_December  = 0x1000,
            IE_CT_Change_Force_Equalizer  = 0x2000,
            IE_CT_Change_Locked_Month     = 0x8000,
            IE_CT_All                     = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param totalNumber - the month per year total number for equalization
        */
        PSS_AnnualNumberPropertiesBP(double totalNumber = 1);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_AnnualNumberPropertiesBP(const PSS_AnnualNumberPropertiesBP& other);

        virtual ~PSS_AnnualNumberPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_AnnualNumberPropertiesBP& operator = (const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Copy operator
        *@param value - value to set
        *@return copy of itself
        */
        PSS_AnnualNumberPropertiesBP& operator = (double value);

        /**
        * Adds the properties to another one
        *@param other - the other properties to add to
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator + (const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Adds the properties to a value
        *@param value - the value to add to
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator + (double value);

        /**
        * Subtracts the properties from another one
        *@param other - the other properties to subtract from
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator - (const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Subtracts the properties from a value
        *@param value - the value to subtract from
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator - (double value);

        /**
        * Multiplies the properties by a value
        *@param value - the value to multiply by
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator * (double value);

        /**
        * Divides the properties by a value
        *@param value - the value to divide by
        *@return a copy of the properties containing the result
        */
        PSS_AnnualNumberPropertiesBP operator / (double value);

        /**
        * Adds the properties to another one and assigns the result
        *@param other - the other properties to add to
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator += (const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Adds the properties to a value and assigns the result
        *@param value - the value to add to
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator += (double value);

        /**
        * Subtracts the properties from another one and assigns the result
        *@param other - the other properties to subtract from
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator -= (const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Subtracts the properties from a value and assigns the result
        *@param value - the value to subtract from
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator -= (double value);

        /**
        * Multiplies the properties by a value and assigns the result
        *@param value - the value to multiply by
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator *= (double value);

        /**
        * Divides the properties by a value and assigns the result
        *@param value - the value to divide by
        *@return itself
        */
        inline PSS_AnnualNumberPropertiesBP& operator /= (double value);

        //@cmember
        /* Compares two orientation properties. */
        BOOL operator == (const PSS_AnnualNumberPropertiesBP& other) const;

        /**
        * Gets the total as a double
        *@return the total
        */
        inline operator double() const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_AnnualNumberPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_AnnualNumberPropertiesBP* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_AnnualNumberPropertiesBP* pProp);

        /**
        * Calculates the total as percents
        *@return the total as percents
        */
        virtual inline void CalculatePercents();

        /**
        * Calculates the years number
        *@return the years number
        */
        virtual inline void CalculateNumberYear();

        /**
        * Gets the sum of locked numbers
        *@return the sum of locked numbers
        */
        virtual inline double GetSumOfLockedNumbers() const;

        /**
        * Gets the sum of unlocked numbers
        *@return the sum of unlocked numbers
        */
        virtual inline double GetSumOfUnlockedNumbers() const;

        /**
        * Gets the years number (i.e the cost multiplier factor)
        *@return the years number
        */
        virtual inline double GetNumberYear() const;

        /**
        * Sets the years number (i.e the cost multiplier factor)
        *@param value - the years number
        */
        virtual inline void SetNumberYear(const double value);

        /**
        * Gets a value at index
        *@param index - the index
        *@return the matching number
        */
        virtual inline double GetNumberAt(std::size_t index) const;

        /**
        * Sets a value at index
        *@param index - the index
        *@param value - the number to set
        */
        virtual inline void SetNumberAt(std::size_t index, const double value);

        /**
        * Gets the workload percent for the month of January
        *@return the workload percent for the month of January
        */
        virtual inline double GetNumberJanuary() const;

        /**
        * Sets the workload percent for the month of January
        *@param value - the workload percent for the month of January
        */
        virtual inline void SetNumberJanuary(const double value);

        /**
        * Gets the workload percent for the month of February
        *@return the workload percent for the month of February
        */
        virtual inline double GetNumberFebruary() const;

        /**
        * Sets the workload percent for the month of February
        *@param value - the workload percent for the month of February
        */
        virtual inline void SetNumberFebruary(const double value);

        /**
        * Gets the workload percent for the month of March
        *@return the workload percent for the month of March
        */
        virtual inline double GetNumberMarch() const;

        /**
        * Sets the workload percent for the month of March
        *@param value - the workload percent for the month of March
        */
        virtual inline void SetNumberMarch(const double value);

        /**
        * Gets the workload percent for the month of April
        *@return the workload percent for the month of April
        */
        virtual inline double GetNumberApril() const;

        /**
        * Sets the workload percent for the month of April
        *@param value - the workload percent for the month of April
        */
        virtual inline void SetNumberApril(const double value);

        /**
        * Gets the workload percent for the month of May
        *@return the workload percent for the month of May
        */
        virtual inline double GetNumberMay() const;

        /**
        * Sets the workload percent for the month of May
        *@param value - the workload percent for the month of May
        */
        virtual inline void SetNumberMay(const double value);

        /**
        * Gets the workload percent for the month of June
        *@return the workload percent for the month of June
        */
        virtual inline double GetNumberJune() const;

        /**
        * Sets the workload percent for the month of June
        *@param value - the workload percent for the month of June
        */
        virtual inline void SetNumberJune(const double value);

        /**
        * Gets the workload percent for the month of July
        *@return the workload percent for the month of July
        */
        virtual inline double GetNumberJuly() const;

        /**
        * Sets the workload percent for the month of July
        *@param value - the workload percent for the month of July
        */
        virtual inline void SetNumberJuly(const double value);

        /**
        * Gets the workload percent for the month of August
        *@return the workload percent for the month of August
        */
        virtual inline double GetNumberAugust() const;

        /**
        * Sets the workload percent for the month of August
        *@param value - the workload percent for the month of August
        */
        virtual inline void SetNumberAugust(const double value);

        /**
        * Gets the workload percent for the month of September
        *@return the workload percent for the month of September
        */
        virtual inline double GetNumberSeptember() const;

        /**
        * Sets the workload percent for the month of September
        *@param value - the workload percent for the month of September
        */
        virtual inline void SetNumberSeptember(const double value);

        /**
        * Gets the workload percent for the month of October
        *@return the workload percent for the month of October
        */
        virtual inline double GetNumberOctober() const;

        /**
        * Sets the workload percent for the month of October
        *@param value - the workload percent for the month of October
        */
        virtual inline void SetNumberOctober(const double value);

        /**
        * Gets the workload percent for the month of November
        *@return the workload percent for the month of November
        */
        virtual inline double GetNumberNovember() const;

        /**
        * Sets the workload percent for the month of November
        *@param value - the workload percent for the month of November
        */
        virtual inline void SetNumberNovember(const double value);

        /**
        * Gets the workload percent for the month of December
        *@return the workload percent for the month of December
        */
        virtual inline double GetNumberDecember() const;

        /**
        * Sets the workload percent for the month of December
        *@param value - the workload percent for the month of December
        */
        virtual inline void SetNumberDecember(const double value);

        /**
        * Gets if the year quantity is locked
        *@return true if the year quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberYear() const;

        /**
        * Sets the year quantity as locked
        *@param value - if true, the year quantity will be locked
        */
        virtual inline void SetLockNumberYear(const bool value);

        /**
        * Gets if the year quantity is locked
        *@return 1 if the year quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberYearEx() const;

        /**
        * Sets the year quantity as locked
        *@param value - if 1, the year quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberYearEx(const UINT value);

        /**
        * Gets if the January quantity is locked
        *@return true if the January quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberJanuary() const;

        /**
        * Sets the January quantity as locked
        *@param value - if true, the January quantity will be locked
        */
        virtual inline void SetLockNumberJanuary(const bool value);

        /**
        * Gets if the January quantity is locked
        *@return 1 if the January quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberJanuaryEx() const;

        /**
        * Sets the January quantity as locked
        *@param value - if 1, the January quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberJanuaryEx(const UINT value);

        /**
        * Gets if the February quantity is locked
        *@return true if the February quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberFebruary() const;

        /**
        * Sets the February quantity as locked
        *@param value - if true, the February quantity will be locked
        */
        virtual inline void SetLockNumberFebruary(const bool value);

        /**
        * Gets if the February quantity is locked
        *@return 1 if the February quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberFebruaryEx() const;

        /**
        * Sets the February quantity as locked
        *@param value - if 1, the February quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberFebruaryEx(const UINT value);

        /**
        * Gets if the March quantity is locked
        *@return true if the March quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberMarch() const;

        /**
        * Sets the March quantity as locked
        *@param value - if true, the March quantity will be locked
        */
        virtual inline void SetLockNumberMarch(const bool value);

        /**
        * Gets if the March quantity is locked
        *@return 1 if the March quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberMarchEx() const;

        /**
        * Sets the March quantity as locked
        *@param value - if 1, the March quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberMarchEx(const UINT value);

        /**
        * Gets if the April quantity is locked
        *@return true if the April quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberApril() const;

        /**
        * Sets the Abril quantity as locked
        *@param value - if true, the Abril quantity will be locked
        */
        virtual inline void SetLockNumberApril(const bool value);

        /**
        * Gets if the Abril quantity is locked
        *@return 1 if the Abril quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberAprilEx() const;

        /**
        * Sets the Abril quantity as locked
        *@param value - if 1, the Abril quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberAprilEx(const UINT value);

        /**
        * Gets if the May quantity is locked
        *@return true if the May quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberMay() const;

        /**
        * Sets the May quantity as locked
        *@param value - if true, the May quantity will be locked
        */
        virtual inline void SetLockNumberMay(const bool value);

        /**
        * Gets if the May quantity is locked
        *@return 1 if the May quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberMayEx() const;

        /**
        * Sets the May quantity as locked
        *@param value - if 1, the May quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberMayEx(const UINT value);

        /**
        * Gets if the June quantity is locked
        *@return true if the June quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberJune() const;

        /**
        * Sets the June quantity as locked
        *@param value - if true, the June quantity will be locked
        */
        virtual inline void SetLockNumberJune(const bool value);

        /**
        * Gets if the June quantity is locked
        *@return 1 if the June quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberJuneEx() const;

        /**
        * Sets the June quantity as locked
        *@param value - if 1, the June quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberJuneEx(const UINT value);

        /**
        * Gets if the July quantity is locked
        *@return true if the July quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberJuly() const;

        /**
        * Sets the July quantity as locked
        *@param value - if true, the July quantity will be locked
        */
        virtual inline void SetLockNumberJuly(const bool value);

        /**
        * Gets if the July quantity is locked
        *@return 1 if the July quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberJulyEx() const;

        /**
        * Sets the July quantity as locked
        *@param value - if 1, the July quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberJulyEx(const UINT value);

        /**
        * Gets if the August quantity is locked
        *@return true if the August quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberAugust() const;

        /**
        * Sets the August quantity as locked
        *@param value - if true, the August quantity will be locked
        */
        virtual inline void SetLockNumberAugust(const bool value);

        /**
        * Gets if the August quantity is locked
        *@return 1 if the August quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberAugustEx() const;

        /**
        * Sets the August quantity as locked
        *@param value - if 1, the August quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberAugustEx(const UINT value);

        /**
        * Gets if the September quantity is locked
        *@return true if the September quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberSeptember() const;

        /**
        * Sets the September quantity as locked
        *@param value - if true, the September quantity will be locked
        */
        virtual inline void SetLockNumberSeptember(const bool value);

        /**
        * Gets if the September quantity is locked
        *@return 1 if the September quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberSeptemberEx() const;

        /**
        * Sets the September quantity as locked
        *@param value - if 1, the September quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberSeptemberEx(const UINT value);

        /**
        * Gets if the October quantity is locked
        *@return true if the October quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberOctober() const;

        /**
        * Sets the October quantity as locked
        *@param value - if true, the October quantity will be locked
        */
        virtual inline void SetLockNumberOctober(const bool value);

        /**
        * Gets if the October quantity is locked
        *@return 1 if the October quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberOctoberEx() const;

        /**
        * Sets the October quantity as locked
        *@param value - if 1, the October quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberOctoberEx(const UINT value);

        /**
        * Gets if the November quantity is locked
        *@return true if the November quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberNovember() const;

        /**
        * Sets the November quantity as locked
        *@param value - if true, the November quantity will be locked
        */
        virtual inline void SetLockNumberNovember(const bool value);

        /**
        * Gets if the November quantity is locked
        *@return 1 if the November quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberNovemberEx() const;

        /**
        * Sets the November quantity as locked
        *@param value - if 1, the November quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberNovemberEx(const UINT value);

        /**
        * Gets if the December quantity is locked
        *@return true if the December quantity is locked, otherwise false
        */
        virtual inline bool GetLockNumberDecember() const;

        /**
        * Sets the December quantity as locked
        *@param value - if true, the December quantity will be locked
        */
        virtual inline void SetLockNumberDecember(const bool value);

        /**
        * Gets if the December quantity is locked
        *@return 1 if the December quantity is locked, otherwise 0
        */
        virtual inline UINT GetLockNumberDecemberEx() const;

        /**
        * Sets the December quantity as locked
        *@param value - if 1, the December quantity will be locked, unlocked otherwise
        */
        virtual inline void SetLockNumberDecemberEx(const UINT value);

        /**
        * Gets if the equalizer should be forced
        *@return true if the equalizer should be forced, otherwise false
        */
        virtual inline bool GetForceEqualizer() const;

        /**
        * Sets the equalizer to be forced
        *@param value - if true, the equalizer will be forced
        */
        virtual inline void SetForceEqualizer(bool value);

        /**
        * Gets if the equalizer should be forced
        *@return 1 if the equalizer should be forced, otherwise 0
        */
        virtual inline UINT GetForceEqualizerEx() const;

        /**
        * Sets the equalizer to be forced
        *@param value - if 1, the equalizer will be forced, not forced otherwise
        */
        virtual inline void SetForceEqualizerEx(const UINT value);

        /**
        * Sets and calculates the quantities based on the year
        *@param value - the year value
        */
        virtual void SetAndCalculateQuantitiesBasedOnYear(const double value);

        /**
        * Sets and calculates the quantities based on the month of January
        *@param value - the January value
        */
        virtual void SetAndCalculateQuantitiesBasedOnJanuary(const double value);

        /**
        * Sets and calculates the quantities based on the month of February
        *@param value - the February value
        */
        virtual void SetAndCalculateQuantitiesBasedOnFebruary(const double value);

        /**
        * Sets and calculates the quantities based on the month of March
        *@param value - the March value
        */
        virtual void SetAndCalculateQuantitiesBasedOnMarch(const double value);

        /**
        * Sets and calculates the quantities based on the month of Abril
        *@param value - the Abril value
        */
        virtual void SetAndCalculateQuantitiesBasedOnApril(const double value);

        /**
        * Sets and calculates the quantities based on the month of May
        *@param value - the may value
        */
        virtual void SetAndCalculateQuantitiesBasedOnMay(const double value);

        /**
        * Sets and calculates the quantities based on the month of June
        *@param value - the June value
        */
        virtual void SetAndCalculateQuantitiesBasedOnJune(const double value);

        /**
        * Sets and calculates the quantities based on the month of July
        *@param value - the July value
        */
        virtual void SetAndCalculateQuantitiesBasedOnJuly(const double value);

        /**
        * Sets and calculates the quantities based on the month of August
        *@param value - the August value
        */
        virtual void SetAndCalculateQuantitiesBasedOnAugust(const double value);

        /**
        * Sets and calculates the quantities based on the month of September
        *@param value - the September value
        */
        virtual void SetAndCalculateQuantitiesBasedOnSeptember(const double value);

        /**
        * Sets and calculates the quantities based on the month of October
        *@param value - the October value
        */
        virtual void SetAndCalculateQuantitiesBasedOnOctober(const double value);

        /**
        * Sets and calculates the quantities based on the month of November
        *@param value - the November value
        */
        virtual void SetAndCalculateQuantitiesBasedOnNovember(const double value);

        /**
        * Sets and calculates the quantities based on the month of December
        *@param value - the December value
        */
        virtual void SetAndCalculateQuantitiesBasedOnDecember(const double value);

        /**
        * Calculates the minimum between two annual numbers
        *@param left - the left properties to compare
        *@param right - the right properties to compare with
        *@return the properties containing the minimal numbers
        */
        virtual PSS_AnnualNumberPropertiesBP Min(const PSS_AnnualNumberPropertiesBP& left,
                                                 const PSS_AnnualNumberPropertiesBP& right);

        /**
        * Calculates the minimum between this and another annual numbers
        *@param other - the other properties to compare with
        *@return the properties containing the minimal numbers
        */
        virtual inline PSS_AnnualNumberPropertiesBP Min(const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Calculates the maximum between two annual numbers
        *@param left - the left properties to compare
        *@param right - the right properties to compare with
        *@return the properties containing the maximal numbers
        */
        virtual PSS_AnnualNumberPropertiesBP Max(const PSS_AnnualNumberPropertiesBP& left,
                                                 const PSS_AnnualNumberPropertiesBP& right);

        /**
        * Calculates the maximum between this and another annual numbers
        *@param other - the other properties to compare with
        *@return the properties containing the maximal numbers
        */
        virtual inline PSS_AnnualNumberPropertiesBP Max(const PSS_AnnualNumberPropertiesBP& other);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, double&  value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int    value);
        virtual BOOL SetValue(const int propId, const UINT   value);
        virtual BOOL SetValue(const int propId, const DWORD  value);
        virtual BOOL SetValue(const int propId, const float  value);
        virtual BOOL SetValue(const int propId, const double value);
        virtual BOOL SetValue(const int propId, LPCTSTR      pValue);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_NumbersEqualizer m_Equalizer;
        UINT                 m_ForceEqualizer;
};

//---------------------------------------------------------------------------
// PSS_AnnualNumberPropertiesBP
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator += (const PSS_AnnualNumberPropertiesBP& other)
{
    *this = *this + other;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator += (double value)
{
    *this = *this + value;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator -= (const PSS_AnnualNumberPropertiesBP& other)
{
    *this = *this - other;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator -= (double value)
{
    *this = *this - value;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator *= (double value)
{
    *this = *this * value;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_AnnualNumberPropertiesBP::operator /= (double value)
{
    *this = *this / value;
    return *this;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP::operator double() const
{
    return m_Equalizer.GetTotal();
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP* PSS_AnnualNumberPropertiesBP::Dup() const
{
    return new PSS_AnnualNumberPropertiesBP(*this);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::CalculatePercents()
{
    m_Equalizer.CalculatePercents();
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::CalculateNumberYear()
{
    m_Equalizer.SetTotal(m_Equalizer.GetSum());
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetSumOfLockedNumbers() const
{
    return m_Equalizer.GetSumOfLockedNumbers();
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetSumOfUnlockedNumbers() const
{
    return m_Equalizer.GetSumOfUnlockedNumbers();
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberYear() const
{
    return m_Equalizer.GetTotal();
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberYear(const double value)
{
    m_Equalizer.SetTotal(value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberAt(size_t Index) const
{
    bool bError;
    return m_Equalizer.GetNumberAt(Index, bError);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberAt(size_t Index, const double value)
{
    m_Equalizer.SetNumberAt(Index, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberJanuary() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJanuary, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberJanuary(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexJanuary, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberFebruary() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexFebruary, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberFebruary(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexFebruary, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberMarch() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexMarch, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberMarch(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexMarch, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberApril() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexApril, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberApril(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexApril, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberMay() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexMay, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberMay(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexMay, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberJune() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJune, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberJune(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexJune, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberJuly() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexJuly, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberJuly(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexJuly, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberAugust() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexAugust, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberAugust(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexAugust, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberSeptember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexSeptember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberSeptember(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexSeptember, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberOctober() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexOctober, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberOctober(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexOctober, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberNovember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexNovember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberNovember(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexNovember, value);
}
//---------------------------------------------------------------------------
double PSS_AnnualNumberPropertiesBP::GetNumberDecember() const
{
    bool error;
    return m_Equalizer.GetNumberAt(g_IndexDecember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetNumberDecember(const double value)
{
    m_Equalizer.SetNumberAt(g_IndexDecember, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberYear() const
{
    return m_Equalizer.GetLockedTotal();
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberYear(const bool value)
{
    m_Equalizer.SetLockedTotal(value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberYearEx() const
{
    return UINT(m_Equalizer.GetLockedTotal());
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberYearEx(const UINT value)
{
    m_Equalizer.SetLockedTotal(value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberJanuary() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexJanuary, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJanuary(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberJanuaryEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexJanuary, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJanuaryEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberFebruary() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexFebruary, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberFebruary(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberFebruaryEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexFebruary, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberFebruaryEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberMarch() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexMarch, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberMarch(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberMarchEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexMarch, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberMarchEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberApril() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexApril, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberApril(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexApril, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberAprilEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexApril, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberAprilEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexApril, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberMay() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexMay, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberMay(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexMay, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberMayEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexMay, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberMayEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexMay, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberJune() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexJune, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJune(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJune, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberJuneEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexJune, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJuneEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJune, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberJuly() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexJuly, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJuly(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberJulyEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexJuly, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberJulyEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberAugust() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexAugust, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberAugust(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberAugustEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexAugust, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberAugustEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberSeptember() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexSeptember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberSeptember(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberSeptemberEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexSeptember, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberSeptemberEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberOctober() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexOctober, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberOctober(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberOctoberEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexOctober, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberOctoberEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberNovember() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexNovember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberNovember(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberNovemberEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexNovember, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberNovemberEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetLockNumberDecember() const
{
    bool error;
    return m_Equalizer.GetLockedFlagAt(g_IndexDecember, error);
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberDecember(const bool value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, value);
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetLockNumberDecemberEx() const
{
    bool error;
    return UINT(m_Equalizer.GetLockedFlagAt(g_IndexDecember, error));
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetLockNumberDecemberEx(const UINT value)
{
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, value);
}
//---------------------------------------------------------------------------
bool PSS_AnnualNumberPropertiesBP::GetForceEqualizer() const
{
    return m_ForceEqualizer;
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetForceEqualizer(bool value)
{
    m_ForceEqualizer = value;
}
//---------------------------------------------------------------------------
UINT PSS_AnnualNumberPropertiesBP::GetForceEqualizerEx() const
{
    return m_ForceEqualizer;
}
//---------------------------------------------------------------------------
void PSS_AnnualNumberPropertiesBP::SetForceEqualizerEx(const UINT value)
{
    m_ForceEqualizer = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::Min(const PSS_AnnualNumberPropertiesBP& other)
{
    return Min(*this, other);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_AnnualNumberPropertiesBP::Max(const PSS_AnnualNumberPropertiesBP& other)
{
    return Max(*this, other);
}
//---------------------------------------------------------------------------

#endif
