// **********************************************************************************************************************
// * ZBBPCostPropProcedure.cpp : Implementation of ZBBPCostPropertiesProcedure											*
// *																													*
// * ProcessSoft Classes																								*
// * <nl>Copyright <cp> 2001 - ProcessSoft SA,																			*
// * All rights reserved.																								*
// *																													*
// * This source code is only intended as a supplement to																*
// * the ProcessSoft Class Reference and related																		*
// * electronic documentation provided with the library.																*
// * See these sources for detailed information regarding																*
// * ProcessSoft products.																								*
// *																													*
// * Author:		Dom																									*
// * Created:		05/2001																								*
// * Description:	ZBBPCostPropertiesProcedure cost properties for procedure											*
// *																													*
// **********************************************************************************************************************

#include "stdafx.h"
#include "ZBBPCostPropProcedure.h"

// Resources
#include "zRMdlBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// **********************************************************************************************************************
// *								ZBBPCostPropertiesProcedure construction/destruction								*
// **********************************************************************************************************************

IMPLEMENT_SERIAL(ZBBPCostPropertiesProcedure, CODIntProperty, def_Version)

using namespace sfl;

//@mfunc | ZBBPCostPropertiesProcedure | ZBBPCostPropertiesProcedure | Constructor.
//
//@syntax ZBBPCostPropertiesProcedure::ZBBPCostPropertiesProcedure(int nId);
//@syntax ZBBPCostPropertiesProcedure::ZBBPCostPropertiesProcedure(const ZBBPCostPropertiesProcedure& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPCostPropertiesProcedure& | propBasic | The orientation property to copy.
ZBBPCostPropertiesProcedure::ZBBPCostPropertiesProcedure(int nId)
	: CODIntProperty(nId)
{
	m_Multiplier = 1;
	m_ProcessingTime = 0;
	m_UnitaryCost = 0;

	VERIFY(RegisterProperties());
}

ZBBPCostPropertiesProcedure::ZBBPCostPropertiesProcedure(const ZBBPCostPropertiesProcedure& propBasic) 
	: CODIntProperty(propBasic.GetId())
{
	*this = propBasic;

	VERIFY(RegisterProperties());
}

//@mfunc Destructor.
ZBBPCostPropertiesProcedure::~ZBBPCostPropertiesProcedure()
{
}

// **********************************************************************************************************************
// *										ZBBPCostPropertiesProcedure operations										*
// **********************************************************************************************************************

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPCostPropertiesProcedure::CompareId(const int nId) const
{
	int nIdMin = m_nId;
	int nIdMax = m_nId + Z_COST_UNITARY_COST;
	return (nId >= nIdMin && nId <= nIdMax);
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPCostPropertiesProcedure& ZBBPCostPropertiesProcedure::operator=(const ZBBPCostPropertiesProcedure& propBasic)
{
	SetMultiplier(propBasic.GetMultiplier());
	SetProcessingTime(propBasic.GetProcessingTime());
	SetUnitaryCost(propBasic.GetUnitaryCost());
	return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPCostPropertiesProcedure::operator==(const ZBBPCostPropertiesProcedure propBasic) const
{
	return (GetMultiplier() == propBasic.GetMultiplier() &&
			GetProcessingTime() == propBasic.GetProcessingTime() &&
			GetUnitaryCost() == propBasic.GetUnitaryCost());
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPCostPropertiesProcedure::Merge(CODProperty* pProperty, DWORD dwChangeFlags)
{
	ZBBPCostPropertiesProcedure* pOrientationProp = (ZBBPCostPropertiesProcedure*)pProperty;

	if (pOrientationProp)
	{
		if (dwChangeFlags & Z_CHANGE_COST_MULTIPLIER)
			m_Multiplier = pOrientationProp->GetMultiplier();

		if (dwChangeFlags & Z_CHANGE_COST_PROCESSING_TIME)
			m_ProcessingTime = pOrientationProp->GetProcessingTime();

		if (dwChangeFlags & Z_CHANGE_COST_UNITARY_COST)
			m_UnitaryCost = pOrientationProp->GetUnitaryCost();



	}
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPCostPropertiesProcedure::IsEqual(CODProperty* pProp)
{
	if (GetId() == pProp->GetId())
	{
		ZBBPCostPropertiesProcedure* pOrientationProp = (ZBBPCostPropertiesProcedure*)pProp;

		if (pOrientationProp)
			return (*this == *pOrientationProp);
	}

	return FALSE;
}

// **********************************************************************************************************************
// *										  IODPropertyContainer interface											*
// **********************************************************************************************************************

//@mfunc | ZBBPCostPropertiesProcedure | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, double& dValue) const
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to retrieve.
//@parm CString& | strValue | Variable to assign return value to.
//@parm int& | nValue | Variable to assign return value to.
//@parm UINT& | nValue | Variable to assign return value to.
//@parm DWORD& | dwValue | Variable to assign return value to.
//@parm float& | fValue | Variable to assign return value to.
//
//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, CString& strValue) const
{
	switch (nPropId)
	{
	case Z_COST_MULTIPLIER:
		strValue.Format("%.0f", m_Multiplier);
		break;
	case Z_COST_PROCESSING_TIME:
		strValue.Format("%.0f", m_ProcessingTime);
		break;
	case Z_COST_UNITARY_COST:
		strValue.Format("%.0f", m_UnitaryCost);
		break;

	default:
		throw new CODPropertyConversionException();
		return FALSE;
	}

	return TRUE;
}

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, int& nValue) const
{
	nValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, UINT& nValue) const
{
	nValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, DWORD& dwValue) const
{
	dwValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, float& fValue) const
{
	switch (nPropId)
	{
	case Z_COST_MULTIPLIER:
		fValue = m_Multiplier;
		break;
	case Z_COST_UNITARY_COST:
		fValue = m_UnitaryCost;
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

BOOL ZBBPCostPropertiesProcedure::GetValue(const int nPropId, double& dValue) const
{
	switch (nPropId)
	{
	case Z_COST_PROCESSING_TIME:
		dValue = m_ProcessingTime;
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

//@mfunc | ZBBPCostPropertiesProcedure | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const double dValue)
//
//@rdesc TRUE if the property identifier is supported by this property
// container. FALSE if the property identifier is invalid.
//@parm const int | nPropId | ID of property to set.
//@parm LPCTSTR | lpszValue | Input value to assign to the specified property.
//@parm const int | nValue | Input value to assign to the specified property.
//@parm const UINT | nValue | Input value to assign to the specified property.
//@parm const DWORD | dwValue | Input value to assign to the specified property.
//@parm const float | fValue | Input value to assign to the specified property.
//
//@comm See <t Orientation Property Identifiers> for a list property IDs
// supported. This function will throw a <c CODPropertyConversionException>
// exception if the data type of the argument passed in is not compatible
// with the given property identifier.

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, LPCTSTR lpszValue)
{
	switch (nPropId)
	{
	case Z_COST_MULTIPLIER:
		m_Multiplier = static_cast<float>(atof(lpszValue));
		break;
	case Z_COST_PROCESSING_TIME:
		m_ProcessingTime = atof(lpszValue);
		break;
	case Z_COST_UNITARY_COST:
		m_UnitaryCost = static_cast<float>(atof(lpszValue));
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const int nValue)
{
	nValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const UINT nValue)
{
	nValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const DWORD dwValue)
{
	dwValue; // unused
	if (nPropId >= Z_COST_MULTIPLIER && nPropId <= Z_COST_UNITARY_COST)
	{
		throw new CODPropertyConversionException();
	}
	return FALSE;
}

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const float fValue)
{
	switch (nPropId)
	{
	case Z_COST_MULTIPLIER:
		m_Multiplier = fValue;
		break;
	case Z_COST_UNITARY_COST:
		m_UnitaryCost = fValue;
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

BOOL ZBBPCostPropertiesProcedure::SetValue(const int nPropId, const double dValue)
{
	switch (nPropId)
	{
	case Z_COST_PROCESSING_TIME:
		m_ProcessingTime = dValue;
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

// **********************************************************************************************************************
// *									   ZBBPCostPropertiesProcedure serialization									*
// **********************************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPCostPropertiesProcedure::Serialize(CArchive& ar)
{
	CODIntProperty::Serialize(ar);

	if (ar.IsStoring())
	{
		TRACE( "ZBBPCostPropertiesProcedure::Serialize : Start Save\n" );

		PUT_SCHEMA(ar, ZBBPCostPropertiesProcedure);
		ar << m_Multiplier;
		ar << m_ProcessingTime;
		ar << m_UnitaryCost;

		TRACE( "ZBBPCostPropertiesProcedure::Serialize : End Save\n" );
	}
	else
	{
		TRACE( "ZBBPCostPropertiesProcedure::Serialize : Start Read\n" );

		UINT nSchema;
		GET_SCHEMA(ar, nSchema);
		ar >> m_Multiplier;
		ar >> m_ProcessingTime;
		ar >> m_UnitaryCost;

		TRACE( "ZBBPCostPropertiesProcedure::Serialize : End Read\n" );
	}
}

// **********************************************************************************************************************
// *								ZBBPCostPropertiesProcedure Property meta-data										*
// **********************************************************************************************************************

bool ZBBPCostPropertiesProcedure::RegisterProperties()
{
	static bool propsRegistered = false;
	
	if (!propsRegistered)
	{
		bool success = true;

		if (success)
		{
			success = RegisterProperty(Z_COST_MULTIPLIER,
									   IDS_Z_COST_MULTIPLIER_NAME, 
									   IDS_Z_COST_MULTIPLIER_DESC,
									   _PropertyAccessor(&ZBBPCostPropertiesProcedure::GetMultiplier,
									   &ZBBPCostPropertiesProcedure::SetMultiplier),
									   VT_R4,
									   PROP_DIRECT
									   );
		}

		if (success)
		{
			success = RegisterProperty(Z_COST_PROCESSING_TIME,
									   IDS_Z_COST_PROCESSING_TIME_NAME, 
									   IDS_Z_COST_PROCESSING_TIME_DESC,
									   _PropertyAccessor(&ZBBPCostPropertiesProcedure::GetProcessingTime,
									   &ZBBPCostPropertiesProcedure::SetProcessingTime),
									   VT_R4,
									   PROP_DIRECT
									   );
		}

		if (success)
		{
			success = RegisterProperty(Z_COST_UNITARY_COST,
									   IDS_Z_COST_UNITARY_COST_NAME, 
									   IDS_Z_COST_UNITARY_COST_DESC,
									   _PropertyAccessor(&ZBBPCostPropertiesProcedure::GetUnitaryCost,
									   &ZBBPCostPropertiesProcedure::SetUnitaryCost),
									   VT_R4,
									   PROP_DIRECT
									   );
		}

		if (!success)
		{
			ZBBPCostPropertiesProcedure::GetPropertyMap().DeleteAll();
		}

		propsRegistered = success;
	}

	return propsRegistered;
}

// **********************************************************************************************************************
// *										ZBBPCostPropertiesProcedure diagnostics										*
// **********************************************************************************************************************

#ifdef _DEBUG

void ZBBPCostPropertiesProcedure::AssertValid() const
{
	CODIntProperty::AssertValid();
}

void ZBBPCostPropertiesProcedure::Dump(CDumpContext& dc) const
{
	CODIntProperty::Dump(dc);
}

#endif //_DEBUG