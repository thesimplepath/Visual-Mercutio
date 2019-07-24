/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProp.h : Declaration of ZBBPAnnualNumberProperties
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// Created:         03/2001
// Description:  ZBBPAnnualNumberProperties quantity properties
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPZBBPAnnualNumberProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPAnnualNumberProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zPropertyIds.h"
#include "zBaseLib\ZBEqualizeNumbers.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_NUMBER_YEAR | Change the total quantity for the year.
#define Z_CHANGE_NUMBER_YEAR                    0x0001
//@flag Z_CHANGE_NUMBER_JANUARY | Change the quantity for january.
#define Z_CHANGE_NUMBER_JANUARY                    0x0002
//@flag Z_CHANGE_NUMBER_FEBRUARY | Change the quantity for february.
#define Z_CHANGE_NUMBER_FEBRUARY                0x0004
//@flag Z_CHANGE_NUMBER_MARCH | Change the quantity for march.
#define Z_CHANGE_NUMBER_MARCH                    0x0008
//@flag Z_CHANGE_NUMBER_APRIL | Change the quantity for april.
#define Z_CHANGE_NUMBER_APRIL                    0x0010
//@flag Z_CHANGE_NUMBER_MAY | Change the quantity for may.
#define Z_CHANGE_NUMBER_MAY                        0x0020
//@flag Z_CHANGE_NUMBER_JUNE | Change the quantity for june.
#define Z_CHANGE_NUMBER_JUNE                    0x0040
//@flag Z_CHANGE_NUMBER_JULY | Change the quantity for july.
#define Z_CHANGE_NUMBER_JULY                    0x0080
//@flag Z_CHANGE_NUMBER_AUGUST | Change the quantity for august.
#define Z_CHANGE_NUMBER_AUGUST                    0x0100
//@flag Z_CHANGE_NUMBER_SEPTEMBER | Change the quantity for september.
#define Z_CHANGE_NUMBER_SEPTEMBER                0x0200
//@flag Z_CHANGE_NUMBER_OCTOBER | Change the quantity for october.
#define Z_CHANGE_NUMBER_OCTOBER                    0x0400
//@flag Z_CHANGE_NUMBER_NOVEMBER | Change the quantity for november.
#define Z_CHANGE_NUMBER_NOVEMBER                0x0800
//@flag Z_CHANGE_NUMBER_DECEMBER | Change the quantity for december.
#define Z_CHANGE_NUMBER_DECEMBER                0x1000
//@flag Z_CHANGE_FORCE_EQUALIZER | Change the flag for displaying month details or not.
#define Z_CHANGE_FORCE_EQUALIZER                0x2000
//@flag Z_CHANGE_LOCKED_MONTH | Change the locked flag for a specific month.
#define Z_CHANGE_LOCKED_MONTH                    0x8000    // Used in conjonction with the month

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPAnnualNumberProperties> objects. The ZBBPAnnualNumberProperties
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_NUMBER_YEAR | Identifier for the total quantity for the year.
#define Z_NUMBER_YEAR                            1
//@flag Z_NUMBER_JANUARY | Identifier for the quantity for january.
#define Z_NUMBER_JANUARY                        2
//@flag Z_NUMBER_FEBRUARY | Identifier for the quantity for february.
#define Z_NUMBER_FEBRUARY                        3
//@flag Z_NUMBER_MARCH | Identifier for the quantity for march.
#define Z_NUMBER_MARCH                            4
//@flag Z_NUMBER_APRIL | Identifier for the quantity for april.
#define Z_NUMBER_APRIL                            5
//@flag Z_NUMBER_MAY | Identifier for the quantity for may.
#define Z_NUMBER_MAY                            6
//@flag Z_NUMBER_JUNE | Identifier for the quantity for june.
#define Z_NUMBER_JUNE                            7
//@flag Z_NUMBER_JULY | Identifier for the quantity for july.
#define Z_NUMBER_JULY                            8
//@flag Z_NUMBER_AUGUST | Identifier for the quantity for august.
#define Z_NUMBER_AUGUST                            9
//@flag Z_NUMBER_SEPTEMBER | Identifier for the quantity for september.
#define Z_NUMBER_SEPTEMBER                        10
//@flag Z_NUMBER_OCTOBER | Identifier for the quantity for october.
#define Z_NUMBER_OCTOBER                        11
//@flag Z_NUMBER_NOVEMBER | Identifier for the quantity for november.
#define Z_NUMBER_NOVEMBER                        12
//@flag Z_NUMBER_DECEMBER | Identifier for the quantity for december.
#define Z_NUMBER_DECEMBER                        13
//@flag Z_LOCKED_YEAR | Change the locked flag for the year.
#define Z_LOCKED_YEAR                            14
//@flag Z_LOCKED_JANUARY | Change the locked flag for the year.
#define Z_LOCKED_JANUARY                        15
//@flag Z_LOCKED_FEBRUARY | Change the locked flag for the year.
#define Z_LOCKED_FEBRUARY                        16
//@flag Z_LOCKED_MARCH | Change the locked flag for the year.
#define Z_LOCKED_MARCH                            17
//@flag Z_LOCKED_APRIL | Change the locked flag for the year.
#define Z_LOCKED_APRIL                            18
//@flag Z_LOCKED_MAY | Change the locked flag for the year.
#define Z_LOCKED_MAY                            19
//@flag Z_LOCKED_JUNE | Change the locked flag for the year.
#define Z_LOCKED_JUNE                            20
//@flag Z_LOCKED_JULY | Change the locked flag for the year.
#define Z_LOCKED_JULY                            21
//@flag Z_LOCKED_AUGUST | Change the locked flag for the year.
#define Z_LOCKED_AUGUST                            22
//@flag Z_LOCKED_SEPTEMBER | Change the locked flag for the year.
#define Z_LOCKED_SEPTEMBER                        23
//@flag Z_LOCKED_OCTOBER | Change the locked flag for the year.
#define Z_LOCKED_OCTOBER                        24
//@flag Z_LOCKED_NOVEMBER | Change the locked flag for the year.
#define Z_LOCKED_NOVEMBER                        25
//@flag Z_LOCKED_DECEMBER | Change the locked flag for the year.
#define Z_LOCKED_DECEMBER                        26
//@flag Z_FORCE_EQUALIZER | Change the flag for displaying month details or not.
#define Z_FORCE_EQUALIZER                        27

/////////////////////////////////////////////////////////////////////////////
// Constant definition
const double _NumberOfMonthPerYear = 12;

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties
//
//@class Determines the orientation of a label or component in relation to
// its container. The orientation is defined by an OD_CONTROL_POINT value
// that indicates a location in the container object. Horizontal and vertical
// offset values can also be specified.
//
// This class is both a property and a container for properties. It implements
// the <c IODPropertyContainer> interface for getting and setting values that
// it contains. Each sub-property contained by orientation property objects
// has a unique identifier (see <t Orientation Property Identifiers>) for
// getting and setting each value. There are also methods to directly set
// each property.
//
//@base public | CObject

class AFX_EXT_CLASS ZBBPAnnualNumberProperties : public CObject
{
    DECLARE_SERIAL( ZBBPAnnualNumberProperties )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPAnnualNumberProperties( double TotalNumber = 1 );

    //@cmember
    /* Copy constructor. */
    ZBBPAnnualNumberProperties( const ZBBPAnnualNumberProperties& right );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPAnnualNumberProperties();

public:

    void CalculatePercents()
    {
        m_Equalizer.CalculatePercents();
    };

    void CalculateNumberYear()
    {
        m_Equalizer.SetTotal( m_Equalizer.GetSum() );
    };

    double GetSumOfLockedNumbers() const
    {
        return m_Equalizer.GetSumOfLockedNumbers();
    };

    double GetSumOfUnlockedNumbers() const
    {
        return m_Equalizer.GetSumOfUnlockedNumbers();
    };

    //@cmember
    /* Gets the cost multiplier factor. */
    double GetNumberYear() const;
    void SetNumberYear( const double value );

    //@cmember
    /* Gets and Sets a value at the specific position. */
    double GetNumberAt( size_t Index ) const;
    void SetNumberAt( size_t Index, const double value );

    //@cmember
    /* Gets the processing time. */
    double GetNumberJanuary() const;
    void SetNumberJanuary( const double value );

    //@cmember
    /* Gets the input workload percent. */
    double GetNumberFebruary() const;
    void SetNumberFebruary( const double value );

    //@cmember
    /* Gets the output workload percent. */
    double GetNumberMarch() const;
    void SetNumberMarch( const double value );

    //@cmember
    /* Gets the fix price. */
    double GetNumberApril() const;
    void SetNumberApril( const double value );

    //@cmember
    /* the may quantity. */
    double GetNumberMay() const;
    void SetNumberMay( const double value );

    //@cmember
    /* Get and Set the june quantity. */
    double GetNumberJune() const;
    void SetNumberJune( const double value );

    //@cmember
    /* Get and Set the july quantity. */
    double GetNumberJuly() const;
    void SetNumberJuly( const double value );

    //@cmember
    /* Get and Set the august quantity. */
    double GetNumberAugust() const;
    void SetNumberAugust( const double value );

    //@cmember
    /* Get and Set the september quantity. */
    double GetNumberSeptember() const;
    void SetNumberSeptember( const double value );

    //@cmember
    /* Get and Set the october quantity. */
    double GetNumberOctober() const;
    void SetNumberOctober( const double value );

    //@cmember
    /* Get and Set the november quantity. */
    double GetNumberNovember() const;
    void SetNumberNovember( const double value );

    //@cmember
    /* Get and Set the december quantity. */
    double GetNumberDecember() const;
    void SetNumberDecember( const double value );

    //@cmember
    /* flag to lock the year quantity. */
    bool GetLockNumberYear() const;
    void SetLockNumberYear( const bool value );
    UINT GetLockNumberYearEx() const;
    void SetLockNumberYearEx( const UINT value );

    //@cmember
    /* flag to lock the january quantity. */
    bool GetLockNumberJanuary() const;
    void SetLockNumberJanuary( const bool value );
    UINT GetLockNumberJanuaryEx() const;
    void SetLockNumberJanuaryEx( const UINT value );

    //@cmember
    /* flag to lock the february quantity. */
    bool GetLockNumberFebruary() const;
    void SetLockNumberFebruary(const bool value );
    UINT GetLockNumberFebruaryEx() const;
    void SetLockNumberFebruaryEx(const UINT value );

    //@cmember
    /* flag to lock the march quantity. */
    bool GetLockNumberMarch() const;
    void SetLockNumberMarch( const bool value );
    UINT GetLockNumberMarchEx() const;
    void SetLockNumberMarchEx( const UINT value );

    //@cmember
    /* flag to lock the april quantity. */
    bool GetLockNumberApril() const;
    void SetLockNumberApril( const bool value );
    UINT GetLockNumberAprilEx() const;
    void SetLockNumberAprilEx( const UINT value );

    //@cmember
    /* flag to lock the may quantity. */
    bool GetLockNumberMay() const;
    void SetLockNumberMay( const bool value );
    UINT GetLockNumberMayEx() const;
    void SetLockNumberMayEx( const UINT value );

    //@cmember
    /* flag to lock the june quantity. */
    bool GetLockNumberJune() const;
    void SetLockNumberJune( const bool value );
    UINT GetLockNumberJuneEx() const;
    void SetLockNumberJuneEx( const UINT value );

    //@cmember
    /* flag to lock the july quantity. */
    bool GetLockNumberJuly() const;
    void SetLockNumberJuly( const bool value );
    UINT GetLockNumberJulyEx() const;
    void SetLockNumberJulyEx( const UINT value );

    //@cmember
    /* flag to lock the august quantity. */
    bool GetLockNumberAugust() const;
    void SetLockNumberAugust( const bool value );
    UINT GetLockNumberAugustEx() const;
    void SetLockNumberAugustEx( const UINT value );

    //@cmember
    /* flag to lock the september quantity. */
    bool GetLockNumberSeptember() const;
    void SetLockNumberSeptember( const bool value );
    UINT GetLockNumberSeptemberEx() const;
    void SetLockNumberSeptemberEx( const UINT value );

    //@cmember
    /* flag to lock the october quantity. */
    bool GetLockNumberOctober() const;
    void SetLockNumberOctober( const bool value );
    UINT GetLockNumberOctoberEx() const;
    void SetLockNumberOctoberEx( const UINT value );

    //@cmember
    /* flag to lock the november quantity. */
    bool GetLockNumberNovember() const;
    void SetLockNumberNovember( const bool value );
    UINT GetLockNumberNovemberEx() const;
    void SetLockNumberNovemberEx( const UINT value );

    //@cmember
    /* flag to lock the december quantity. */
    bool GetLockNumberDecember() const;
    void SetLockNumberDecember( const bool value );
    UINT GetLockNumberDecemberEx() const;
    void SetLockNumberDecemberEx( const UINT value );

    //@cmember
    /* flag to show or not month details. */
    bool GetForceEqualizer() const;
    void SetForceEqualizer( bool value );
    UINT GetForceEqualizerEx() const;
    void SetForceEqualizerEx( const UINT value );

    //@cmember
    /* Sets the cost multiplier factor. */
    void SetAndCalculateQuantitiesBasedOnYear( const double value );

    //@cmember
    /* Sets the processing time. */
    void SetAndCalculateQuantitiesBasedOnJanuary( const double value );

    //@cmember
    /* Sets the input workload percent. */
    void SetAndCalculateQuantitiesBasedOnFebruary( const double value );

    //@cmember
    /* Sets the output workload percent. */
    void SetAndCalculateQuantitiesBasedOnMarch( const double value );

    //@cmember
    /* Sets the fix price. */
    void SetAndCalculateQuantitiesBasedOnApril( const double value );

    //@cmember
    /* the may quantity. */
    void SetAndCalculateQuantitiesBasedOnMay( const double value );

    //@cmember
    /* Get and Set the june quantity. */
    void SetAndCalculateQuantitiesBasedOnJune( const double value );

    //@cmember
    /* Get and Set the july quantity. */
    void SetAndCalculateQuantitiesBasedOnJuly( const double value );

    //@cmember
    /* Get and Set the august quantity. */
    void SetAndCalculateQuantitiesBasedOnAugust( const double value );

    //@cmember
    /* Get and Set the september quantity. */
    void SetAndCalculateQuantitiesBasedOnSeptember( const double value );

    //@cmember
    /* Get and Set the october quantity. */
    void SetAndCalculateQuantitiesBasedOnOctober( const double value );

    //@cmember
    /* Get and Set the november quantity. */
    void SetAndCalculateQuantitiesBasedOnNovember( const double value );

    //@cmember
    /* Get and Set the december quantity. */
    void SetAndCalculateQuantitiesBasedOnDecember( const double value );

// Operations
public:

    // Caculate the maximum of two annual numbers
    ZBBPAnnualNumberProperties Max( const ZBBPAnnualNumberProperties& Left,
                                    const ZBBPAnnualNumberProperties& Right );

    ZBBPAnnualNumberProperties Max( const ZBBPAnnualNumberProperties& Right )
    {
        return Max( *this, Right );
    };

    // Caculate the minimum of two annual numbers
    ZBBPAnnualNumberProperties Min( const ZBBPAnnualNumberProperties& Left,
                                    const ZBBPAnnualNumberProperties& Right );

    ZBBPAnnualNumberProperties Min( const ZBBPAnnualNumberProperties& Right )
    {
        return Min( *this, Right );
    };

    //@cmember
    /* Assigns another property to this property. */
    ZBBPAnnualNumberProperties& operator=( const ZBBPAnnualNumberProperties& right );

    //@cmember
    /* Assigns a double value. */
    ZBBPAnnualNumberProperties& operator=( double value );

    //@cmember
    /* Divide by a double value. */
    ZBBPAnnualNumberProperties operator/( double value );

    //@cmember
    /* Multiply by a double value. */
    ZBBPAnnualNumberProperties operator*( double value );

    //@cmember
    /* Add by a double value. */
    ZBBPAnnualNumberProperties operator+( double value );

    //@cmember
    /* Add by another object. */
    ZBBPAnnualNumberProperties operator+( const ZBBPAnnualNumberProperties& Right );

    //@cmember
    /* Sub by a double value. */
    ZBBPAnnualNumberProperties operator-( double value );

    //@cmember
    /* Sub by another object. */
    ZBBPAnnualNumberProperties operator-( const ZBBPAnnualNumberProperties& Right );
    
    //@cmember
    /* Multiply a double */
    ZBBPAnnualNumberProperties& operator*=( double value );
    //@cmember
    /* Divide a double */
    ZBBPAnnualNumberProperties& operator/=( double value );
    //@cmember
    /* Add a double */
    ZBBPAnnualNumberProperties& operator+=( double value );
    //@cmember
    /* Add another object */
    ZBBPAnnualNumberProperties& operator+=( const ZBBPAnnualNumberProperties& Right );
    //@cmember
    /* Substract a double */
    ZBBPAnnualNumberProperties& operator-=( double value );
    //@cmember
    /* Sub another object */
    ZBBPAnnualNumberProperties& operator-=( const ZBBPAnnualNumberProperties& Right );

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==( const ZBBPAnnualNumberProperties propBasic ) const;

    //@cmember
    /* return the total. */
    operator double() const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBBPAnnualNumberProperties* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( ZBBPAnnualNumberProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( ZBBPAnnualNumberProperties* pProp );

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue interface

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;
    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;
    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;
    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;
    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;
    //@cmember
    /* Gets the value of the given double property. */
    virtual BOOL GetValue( const int nPropId, double& dValue ) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );
    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue( const int nPropId, const int nValue );
    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue( const int nPropId, const UINT nValue );
    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );
    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue( const int nPropId, const float fValue );
    //@cmember
    /* Sets the value of the given double property. */
    virtual BOOL SetValue( const int nPropId, const double dValue );

    //@cmember
    /* Serializes the orientation properties. */
    virtual void Serialize( CArchive& ar );

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    /* Equalizer member that keeps all values. */
    ZBEqualizeNumbers    m_Equalizer;
    
    //@cmember
    /* flag for showing or not month details. */
    UINT                m_ForceEqualizer;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPAnnualNumberProperties inline methods

inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator*=( double value )
{
    *this = *this * value;
    return *this; 
}

inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator/=( double value )
{
    *this = *this / value;
    return *this; 
}

inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator+=( double value )
{
    *this = *this + value;
    return *this; 
}

inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator+=( const ZBBPAnnualNumberProperties& Right )
{
    *this = *this + Right;
    return *this; 
}


inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator-=( double value )
{
    *this = *this - value;
    return *this; 
}

inline ZBBPAnnualNumberProperties& ZBBPAnnualNumberProperties::operator-=( const ZBBPAnnualNumberProperties& Right )
{
    *this = *this - Right;
    return *this; 
}

inline double ZBBPAnnualNumberProperties::GetNumberYear() const
{
    return m_Equalizer.GetTotal();
}

inline void ZBBPAnnualNumberProperties::SetNumberYear( const double value )
{
    m_Equalizer.SetTotal( value );
}

inline double ZBBPAnnualNumberProperties::GetNumberAt( size_t Index ) const
{
    bool bError;
    return m_Equalizer.GetNumberAt( Index, bError );
}

inline void ZBBPAnnualNumberProperties::SetNumberAt( size_t Index, const double value )
{
    m_Equalizer.SetNumberAt( Index, value );
}

inline double ZBBPAnnualNumberProperties::GetNumberJanuary() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexJanuary, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberJanuary( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexJanuary, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberFebruary() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexFebruary, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberFebruary( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexFebruary, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberMarch() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexMarch, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberMarch( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexMarch, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberApril() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexApril, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberApril( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexApril, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberMay() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexMay, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberMay( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexMay, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberJune() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexJune, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberJune( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexJune, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberJuly() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexJuly, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberJuly( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexJuly, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberAugust() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexAugust, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberAugust( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexAugust, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberSeptember() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexSeptember, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberSeptember( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexSeptember, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberOctober() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexOctober, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberOctober( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexOctober, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberNovember() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexNovember, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberNovember( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexNovember, value);
}

inline double ZBBPAnnualNumberProperties::GetNumberDecember() const
{
    bool bError;
    return m_Equalizer.GetNumberAt(g_IndexDecember, bError);
}

inline void ZBBPAnnualNumberProperties::SetNumberDecember( const double value )
{
    m_Equalizer.SetNumberAt(g_IndexDecember, value);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberYear() const
{
    return m_Equalizer.GetLockedTotal();
}

inline void ZBBPAnnualNumberProperties::SetLockNumberYear( const bool value )
{
    m_Equalizer.SetLockedTotal( value );
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberYearEx() const
{
    return (UINT)m_Equalizer.GetLockedTotal();
}

inline void ZBBPAnnualNumberProperties::SetLockNumberYearEx( const UINT value )
{
    m_Equalizer.SetLockedTotal( ( value == 1 ) ? true : false );
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberJanuary() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexJanuary, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJanuary( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberJanuaryEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexJanuary, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJanuaryEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJanuary, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberFebruary() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexFebruary, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberFebruary( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberFebruaryEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexFebruary, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberFebruaryEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexFebruary, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberMarch() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexMarch, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberMarch( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberMarchEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexMarch, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberMarchEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexMarch, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberApril() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexApril, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberApril( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexApril, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberAprilEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexApril, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberAprilEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexApril, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberMay() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexMay, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberMay( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexMay, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberMayEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexMay, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberMayEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexMay, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberJune() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexJune, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJune( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJune, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberJuneEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexJune, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJuneEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJune, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberJuly() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexJuly, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJuly( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberJulyEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexJuly, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberJulyEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexJuly, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberAugust() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexAugust, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberAugust( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberAugustEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexAugust, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberAugustEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexAugust, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberSeptember() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexSeptember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberSeptember( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberSeptemberEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexSeptember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberSeptemberEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexSeptember, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberOctober() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexOctober, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberOctober( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberOctoberEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexOctober, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberOctoberEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexOctober, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberNovember() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexNovember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberNovember( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberNovemberEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexNovember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberNovemberEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexNovember, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetLockNumberDecember() const
{
    bool bError;
    return m_Equalizer.GetLockedFlagAt(g_IndexDecember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberDecember( const bool value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, value);
}

inline UINT ZBBPAnnualNumberProperties::GetLockNumberDecemberEx() const
{
    bool bError;
    return (UINT)m_Equalizer.GetLockedFlagAt(g_IndexDecember, bError);
}

inline void ZBBPAnnualNumberProperties::SetLockNumberDecemberEx( const UINT value )
{
    m_Equalizer.SetLockedFlagAt(g_IndexDecember, (value == 1) ? true : false);
}

inline bool ZBBPAnnualNumberProperties::GetForceEqualizer() const
{
    return ( m_ForceEqualizer == 0 ) ? false : true;
}

inline void ZBBPAnnualNumberProperties::SetForceEqualizer( bool value )
{
    m_ForceEqualizer = value;
}

inline UINT ZBBPAnnualNumberProperties::GetForceEqualizerEx() const
{
    return m_ForceEqualizer;
}

inline void ZBBPAnnualNumberProperties::SetForceEqualizerEx( const UINT value )
{
    m_ForceEqualizer = value;
}

inline ZBBPAnnualNumberProperties::operator double() const
{
    return m_Equalizer.GetTotal(); 
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPAnnualNumberProperties* ZBBPAnnualNumberProperties::Dup()
{
    return new ZBBPAnnualNumberProperties( *this );
}

#endif // !defined(AFX_ZBBPZBBPAnnualNumberProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)