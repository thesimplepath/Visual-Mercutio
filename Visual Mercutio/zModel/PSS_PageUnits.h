/****************************************************************************
 * ==> PSS_PageUnits -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides page units                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PageUnitsH
#define PSS_PageUnitsH

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
#ifndef PSS_PageUnits
    #define PSS_PageUnits ZBPageUnits
#endif

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Page units
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PageUnits : public CObject
{
    DECLARE_SERIAL(PSS_PageUnits)

    public:
        typedef CObject inherited;

        PSS_PageUnits();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PageUnits(const PSS_PageUnits& other);
        PSS_PageUnits(const CODRuler&      other);

        virtual ~PSS_PageUnits();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PageUnits& operator = (const PSS_PageUnits& other);
        const PSS_PageUnits& operator = (const CODRuler&      other);

        /**
        * Gets the measure unit
        *@return the measure unit
        */
        virtual inline OD_UNIT_OF_MEASURE GetUnitOfMeasure() const;

        /**
        * Sets the measure unit
        *@param value - the measure unit
        */
        virtual inline void SetUnitOfMeasure(const OD_UNIT_OF_MEASURE units);

        /**
        * Gets the logical unit size on the output device
        *@param[out] logXUnit - the logical unit size on the x axis
        *@param[out] logYUnit - the logical unit size on the y axis
        */
        virtual inline void GetLogicalUnitMeasure(CODMeasure& logXUnit, CODMeasure& logYUnit);

        /**
        * Sets the logical unit size on the output device
        *@param logXUnit - the logical unit size on the x axis
        *@param logYUnit - the logical unit size on the y axis
        */
        virtual inline void SetLogicalUnitMeasure(const CODMeasure& logXUnit, const CODMeasure& logYUnit);

        /**
        * Gets the scaling factor for measurements
        *@param[out] scaleFrom - the scale from factor
        *@param[out] scaleTo - the scale to factor
        */
        virtual inline void GetMeasurementScale(CODMeasure& scaleFrom, CODMeasure& scaleTo);

        /**
        * Sets the scaling factor for measurements
        *@param scaleFrom - the scale from factor
        *@param scaleTo - the scale to factor
        */
        virtual inline void SetMeasurementScale(const CODMeasure& scaleFrom, const CODMeasure& scaleTo);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    protected:
        OD_UNIT_OF_MEASURE m_Units;
        CODMeasure         m_LogXUnit;
        CODMeasure         m_LogYUnit;
        CODMeasure         m_ScaleFrom;
        CODMeasure         m_ScaleTo;
};

//---------------------------------------------------------------------------
// PSS_PageUnits
//---------------------------------------------------------------------------
OD_UNIT_OF_MEASURE PSS_PageUnits::GetUnitOfMeasure() const
{
    return m_Units;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::SetUnitOfMeasure(const OD_UNIT_OF_MEASURE units)
{
    m_Units = units;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::GetLogicalUnitMeasure(CODMeasure& logXUnit, CODMeasure& logYUnit)
{
    logXUnit = m_LogXUnit;
    logYUnit = m_LogYUnit;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::SetLogicalUnitMeasure(const CODMeasure& logXUnit, const CODMeasure& logYUnit)
{
    m_LogXUnit = logXUnit;
    m_LogYUnit = logYUnit;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::GetMeasurementScale(CODMeasure& scaleFrom, CODMeasure& scaleTo)
{
    scaleFrom = m_ScaleFrom;
    scaleTo   = m_ScaleTo;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::SetMeasurementScale(const CODMeasure& scaleFrom, const CODMeasure& scaleTo)
{
    m_ScaleFrom = scaleFrom;
    m_ScaleTo   = scaleTo;
}
//---------------------------------------------------------------------------

#endif
