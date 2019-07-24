// **********************************************************************************************************************
// * ZBBPCostPropDeliverable.cpp : Implementation of ZBBPCostPropertiesDeliverable                                        *
// *                                                                                                                    *
// * ProcessSoft Classes                                                                                                *
// * <nl>Copyright <cp> 2001 - ProcessSoft SA,                                                                            *
// * All rights reserved.                                                                                                *
// *                                                                                                                    *
// * This source code is only intended as a supplement to                                                                *
// * the ProcessSoft Class Reference and related                                                                        *
// * electronic documentation provided with the library.                                                                *
// * See these sources for detailed information regarding                                                                *
// * ProcessSoft products.                                                                                                *
// *                                                                                                                    *
// * Author:        Dom                                                                                                    *
// * Created:        05/2001                                                                                                *
// * Description:    ZBBPCostPropertiesDeliverable cost properties for deliverables                                        *
// *                                                                                                                    *
// **********************************************************************************************************************

#include "stdafx.h"
#include "ZBBPCostPropDeliverable.h"

#include "zRMdlBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// **********************************************************************************************************************
// *                                ZBBPCostPropertiesDeliverable construction/destruction                                *
// **********************************************************************************************************************

IMPLEMENT_SERIAL(ZBBPCostPropertiesDeliverable, CODIntProperty, g_DefVersion)

using namespace sfl;

//@mfunc | ZBBPCostPropertiesDeliverable | ZBBPCostPropertiesDeliverable | Constructor.
//
//@syntax ZBBPCostPropertiesDeliverable::ZBBPCostPropertiesDeliverable(int nId);
//@syntax ZBBPCostPropertiesDeliverable::ZBBPCostPropertiesDeliverable(const ZBBPCostPropertiesDeliverable& propBasic);
//
//@parmopt int | nId | OD_PROP_ORIENTATION | The identifier of the property.
//@parm ZBBPCostPropertiesDeliverable& | propBasic | The orientation property to copy.
ZBBPCostPropertiesDeliverable::ZBBPCostPropertiesDeliverable(int nId)
    : CODIntProperty(nId)
{
    m_ProcessingTime = 0;
    m_InWorkloadPercent = 1;
    m_OutWorkloadPercent = 1;
    m_UnitaryCost = 0;

    VERIFY(RegisterProperties());
}

ZBBPCostPropertiesDeliverable::ZBBPCostPropertiesDeliverable(const ZBBPCostPropertiesDeliverable& propBasic) 
    : CODIntProperty(propBasic.GetId())
{
    *this = propBasic;

    VERIFY(RegisterProperties());
}

//@mfunc Destructor.
ZBBPCostPropertiesDeliverable::~ZBBPCostPropertiesDeliverable()
{
}

// **********************************************************************************************************************
// *                                    ZBBPCostPropertiesDeliverable operations                                        *
// **********************************************************************************************************************

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPCostPropertiesDeliverable::CompareId(const int nId) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_COST_UNITARY_COST;
    return (nId >= nIdMin && nId <= nIdMax);
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPCostPropertiesDeliverable& ZBBPCostPropertiesDeliverable::operator=(const ZBBPCostPropertiesDeliverable& propBasic)
{
    SetProcessingTime(propBasic.GetProcessingTime());
    SetInWorkloadPercent(propBasic.GetInWorkloadPercent());
    SetOutWorkloadPercent(propBasic.GetOutWorkloadPercent());
    SetUnitaryCost(propBasic.GetUnitaryCost());
    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPCostPropertiesDeliverable::operator==(const ZBBPCostPropertiesDeliverable propBasic) const
{
    return (GetProcessingTime() == propBasic.GetProcessingTime() &&
            GetInWorkloadPercent() == propBasic.GetInWorkloadPercent() &&
            GetOutWorkloadPercent() == propBasic.GetOutWorkloadPercent() &&
            GetUnitaryCost() == propBasic.GetUnitaryCost());
}

//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPCostPropertiesDeliverable::Merge(CODProperty* pProperty, DWORD dwChangeFlags)
{
    ZBBPCostPropertiesDeliverable* pOrientationProp = (ZBBPCostPropertiesDeliverable*)pProperty;

    if (pOrientationProp)
    {
        if (dwChangeFlags & Z_CHANGE_COST_PROCESSING_TIME)
            m_ProcessingTime = pOrientationProp->GetProcessingTime();

        if (dwChangeFlags & Z_CHANGE_COST_IN_WORKLOAD_PERCENT)
            m_InWorkloadPercent = pOrientationProp->GetInWorkloadPercent();

        if (dwChangeFlags & Z_CHANGE_COST_OUT_WORKLOAD_PERCENT)
            m_OutWorkloadPercent = pOrientationProp->GetOutWorkloadPercent();

        if (dwChangeFlags & Z_CHANGE_COST_UNITARY_COST)
            m_UnitaryCost = pOrientationProp->GetUnitaryCost();



    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf CODFillProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPCostPropertiesDeliverable::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        ZBBPCostPropertiesDeliverable* pOrientationProp = (ZBBPCostPropertiesDeliverable*)pProp;

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}

// **********************************************************************************************************************
// *                                            IODPropertyContainer interface                                            *
// **********************************************************************************************************************

//@mfunc | ZBBPCostPropertiesDeliverable | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, float& fValue) const
//@syntax BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, double& dValue) const
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

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, CString& strValue) const
{
    switch (nPropId)
    {
    case Z_COST_PROCESSING_TIME:
        strValue.Format("%.0f", m_ProcessingTime);
        break;
    case Z_COST_IN_WORKLOAD_PERCENT:
        strValue.Format("%.0f", m_InWorkloadPercent * (float)100);
        break;
    case Z_COST_OUT_WORKLOAD_PERCENT:
        strValue.Format("%.0f", m_OutWorkloadPercent * (float)100);
        break;
    case Z_COST_UNITARY_COST:
        strValue.Format("%.0f", m_UnitaryCost);
        break;
//        throw new CODPropertyConversionException();

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, int& nValue) const
{
    nValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, UINT& nValue) const
{
    nValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, DWORD& dwValue) const
{
    dwValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, float& fValue) const
{
    switch (nPropId)
    {
    case Z_COST_IN_WORKLOAD_PERCENT:
        fValue = m_InWorkloadPercent;
        break;
    case Z_COST_OUT_WORKLOAD_PERCENT:
        fValue = m_OutWorkloadPercent;
        break;
    case Z_COST_UNITARY_COST:
        fValue = m_UnitaryCost;
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable::GetValue(const int nPropId, double& dValue) const
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

//@mfunc | ZBBPCostPropertiesDeliverable | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const float fValue)
//@syntax BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const double dValue)
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

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, LPCTSTR lpszValue)
{
    switch (nPropId)
    {
    case Z_COST_PROCESSING_TIME:
        m_ProcessingTime = atof(lpszValue);
        break;
    case Z_COST_IN_WORKLOAD_PERCENT:
        m_InWorkloadPercent = static_cast<float>(atof(lpszValue) / (float)100);
        break;
    case Z_COST_OUT_WORKLOAD_PERCENT:
        m_OutWorkloadPercent = static_cast<float>(atof(lpszValue) / (float)100);
        break;
    case Z_COST_UNITARY_COST:
        m_UnitaryCost = static_cast<float>(atof(lpszValue));
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const int nValue)
{
    nValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const UINT nValue)
{
    nValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const DWORD dwValue)
{
    dwValue; // unused
    if (nPropId >= Z_COST_PROCESSING_TIME && nPropId <= Z_COST_UNITARY_COST)
    {
        throw new CODPropertyConversionException();
    }
    return FALSE;
}

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const float fValue)
{
    switch (nPropId)
    {
    case Z_COST_IN_WORKLOAD_PERCENT:
        m_InWorkloadPercent = fValue;
        break;
    case Z_COST_OUT_WORKLOAD_PERCENT:
        m_OutWorkloadPercent = fValue;
        break;
    case Z_COST_UNITARY_COST:
        m_UnitaryCost = fValue;
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPCostPropertiesDeliverable::SetValue(const int nPropId, const double dValue)
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
// *                                    ZBBPCostPropertiesDeliverable serialization                                        *
// **********************************************************************************************************************

//@mfunc Serializes the orientation properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPCostPropertiesDeliverable::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE( "ZBBPCostPropertiesDeliverable::Serialize : Start Save\n" );

        PUT_SCHEMA(ar, ZBBPCostPropertiesDeliverable);
        ar << m_ProcessingTime;
        ar << m_InWorkloadPercent;
        ar << m_OutWorkloadPercent;
        ar << m_UnitaryCost;

        TRACE( "ZBBPCostPropertiesDeliverable::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBBPCostPropertiesDeliverable::Serialize : Start Read\n" );

        UINT nSchema;
        GET_SCHEMA(ar, nSchema);
        ar >> m_ProcessingTime;
        ar >> m_InWorkloadPercent;
        ar >> m_OutWorkloadPercent;
        ar >> m_UnitaryCost;

        TRACE( "ZBBPCostPropertiesDeliverable::Serialize : End Read\n" );
    }
}

// **********************************************************************************************************************
// *                                ZBBPCostPropertiesDeliverable Property meta-data                                    *
// **********************************************************************************************************************

bool ZBBPCostPropertiesDeliverable::RegisterProperties()
{
    static bool propsRegistered = false;
    
    if (!propsRegistered)
    {
        bool success = true;

        if (success)
        {
            success = RegisterProperty(Z_COST_PROCESSING_TIME,
                                       IDS_Z_COST_PROCESSING_TIME_NAME, 
                                       IDS_Z_COST_PROCESSING_TIME_DESC,
                                       _PropertyAccessor(&ZBBPCostPropertiesDeliverable::GetProcessingTime,
                                       &ZBBPCostPropertiesDeliverable::SetProcessingTime),
                                       VT_R4,
                                       PROP_DIRECT
                                       );
        }

        if (success)
        {
            success = RegisterProperty(Z_COST_IN_WORKLOAD_PERCENT,
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_NAME, 
                                       IDS_Z_COST_IN_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&ZBBPCostPropertiesDeliverable::GetInWorkloadPercent,
                                       &ZBBPCostPropertiesDeliverable::SetInWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT
                                       );
        }

        if (success)
        {
            success = RegisterProperty(Z_COST_OUT_WORKLOAD_PERCENT,
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_NAME, 
                                       IDS_Z_COST_OUT_WORKLOAD_PERCENT_DESC,
                                       _PropertyAccessor(&ZBBPCostPropertiesDeliverable::GetOutWorkloadPercent,
                                       &ZBBPCostPropertiesDeliverable::SetOutWorkloadPercent),
                                       VT_R4,
                                       PROP_DIRECT
                                       );
        }

        if (success)
        {
            success = RegisterProperty(Z_COST_UNITARY_COST,
                                       IDS_Z_COST_UNITARY_COST_NAME, 
                                       IDS_Z_COST_UNITARY_COST_DESC,
                                       _PropertyAccessor(&ZBBPCostPropertiesDeliverable::GetUnitaryCost,
                                       &ZBBPCostPropertiesDeliverable::SetUnitaryCost),
                                       VT_R4,
                                       PROP_DIRECT
                                       );
        }

        if (!success)
        {
            ZBBPCostPropertiesDeliverable::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

// **********************************************************************************************************************
// *                                      ZBBPCostPropertiesDeliverable diagnostics                                        *
// **********************************************************************************************************************

#ifdef _DEBUG

void ZBBPCostPropertiesDeliverable::AssertValid() const
{
    CODIntProperty::AssertValid();
}

void ZBBPCostPropertiesDeliverable::Dump(CDumpContext& dc) const
{
    CODIntProperty::Dump(dc);
}

#endif //_DEBUG