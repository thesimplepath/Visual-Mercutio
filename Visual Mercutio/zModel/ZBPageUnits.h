// ZBPageUnits.h: interface for the ZBPageUnits class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBPAGEUNITS_H__F2584E08_0478_11D4_96F4_0000B45D7C6F__INCLUDED_)
#define AFX_ZBPAGEUNITS_H__F2584E08_0478_11D4_96F4_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBPageUnits : public CObject  
{
public:
	// Inherited feature
	typedef CObject inherited;

protected: // create from serialization only
	DECLARE_SERIAL(ZBPageUnits)

public:
	ZBPageUnits();
	ZBPageUnits(const ZBPageUnits &right);
	ZBPageUnits(const CODRuler &right);

	const ZBPageUnits& operator=(const ZBPageUnits &right);
	const ZBPageUnits& operator=(const CODRuler &right);


	virtual ~ZBPageUnits();

	/* Gets the current unit of measure. */
	OD_UNIT_OF_MEASURE GetUnitOfMeasure() const;
	/* Sets the current unit of measure. */
	void SetUnitOfMeasure(const OD_UNIT_OF_MEASURE units);
	/* Gets the size of one logical unit on the output device. */
	void GetLogicalUnitMeasure(CODMeasure& logXUnit, CODMeasure& logYUnit);
	/* Sets the size of one logical unit on the output device. */
	void SetLogicalUnitMeasure(const CODMeasure& logXUnit, const CODMeasure& logYUnit);
	/* Gets scaling factor for measurements. */
	void GetMeasurementScale(CODMeasure& scaleFrom, CODMeasure& scaleTo);
	/* Sets a scaling factor for measurements. */
	void SetMeasurementScale(const CODMeasure& scaleFrom, const CODMeasure& scaleTo);

	virtual void Serialize( CArchive& ar );


protected:
	OD_UNIT_OF_MEASURE	m_units;
	CODMeasure			m_ScaleFrom;
	CODMeasure			m_ScaleTo;
	CODMeasure			m_logXUnit;
	CODMeasure			m_logYUnit;

};



inline OD_UNIT_OF_MEASURE ZBPageUnits::GetUnitOfMeasure() const
{
	return m_units;
}

inline void ZBPageUnits::SetUnitOfMeasure(const OD_UNIT_OF_MEASURE units)
{
	m_units = units;
}

inline void ZBPageUnits::GetLogicalUnitMeasure(CODMeasure& logXUnit, CODMeasure& logYUnit)
{
	logXUnit = m_logXUnit;
	logYUnit = m_logYUnit;
}

inline void ZBPageUnits::SetLogicalUnitMeasure(const CODMeasure& logXUnit, const CODMeasure& logYUnit)
{
	m_logXUnit = logXUnit;
	m_logYUnit = logYUnit;
}

inline void ZBPageUnits::GetMeasurementScale(CODMeasure& scaleFrom, CODMeasure& scaleTo)
{
	scaleFrom = m_ScaleFrom;
	scaleTo = m_ScaleTo;
}

inline void ZBPageUnits::SetMeasurementScale(const CODMeasure& scaleFrom, const CODMeasure& scaleTo)
{
	m_ScaleFrom = scaleFrom;
	m_ScaleTo = scaleTo;
}

#endif // !defined(AFX_ZBPAGEUNITS_H__F2584E08_0478_11D4_96F4_0000B45D7C6F__INCLUDED_)
