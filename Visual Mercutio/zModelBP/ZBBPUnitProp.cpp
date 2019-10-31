/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPUnitProperties
//@module ZBBPUnitProp.cpp | Implementation of the <c ZBBPUnitProperties> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "ZBBPUnitProp.h"

#include "zBaseLib\PSS_BaseDocument.h"

// Resources
#include "PSS_ModelResIDs.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace sfl;


/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPUnitProperties, CODIntProperty, g_DefVersion)

//@mfunc | ZBBPUnitProperties | ZBBPUnitProperties | Constructor.
//
//@syntax ZBBPUnitProperties::ZBBPUnitProperties(int nId);
//@syntax ZBBPUnitProperties::ZBBPUnitProperties(const ZBBPUnitProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPUnitProperties& | propProcess | The fill property to copy.
ZBBPUnitProperties::ZBBPUnitProperties(int nId) 
    : CODIntProperty(nId)
{
    m_UnitName      = _T("");
    m_UnitCost  = 0;

    RegisterProperties();
}

ZBBPUnitProperties::ZBBPUnitProperties(const ZBBPUnitProperties& propProcess) 
    : CODIntProperty(propProcess.GetId())
{
    m_UnitName      = propProcess.GetUnitName();
    m_UnitCost  = propProcess.GetUnitCost();

    RegisterProperties();
}

//@mfunc Destructor.
ZBBPUnitProperties::~ZBBPUnitProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties attributes
 


//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPUnitProperties::SetUnitName(LPCTSTR lpszValue)
{
    if (lpszValue != NULL)
    {
        m_UnitName = lpszValue;
    }
    else
    {
        TRACE0("Z -> Invalid Task List pointer!\n");
        ASSERT(FALSE);
    }
}

//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPUnitProperties::SetUnitNameEx(const CString value)
{
    SetUnitName(value);
}



/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPUnitProperties::CompareId(const int nId) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_UNIT_COST;
    return (nId >= nIdMin && nId <= nIdMax);
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPUnitProperties& ZBBPUnitProperties::operator=(const ZBBPUnitProperties& propProcess)
{
    SetId(propProcess.GetId());
    SetUnitName(propProcess.GetUnitName());
    SetUnitCost(propProcess.GetUnitCost());

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPUnitProperties::operator==(const ZBBPUnitProperties propProcess) const
{
    return (GetUnitName() == propProcess.GetUnitName() &&
            GetUnitCost() == propProcess.GetUnitCost());
}


//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPUnitProperties::Merge(CODProperty* pProperty, DWORD dwChangeFlags)
{
    ZBBPUnitProperties* pProcessProps = (ZBBPUnitProperties*)pProperty;

    if (pProcessProps)
    {
        if (dwChangeFlags & Z_CHANGE_UNIT_NAME)
            m_UnitName = pProcessProps->GetUnitName();
        if (dwChangeFlags & Z_CHANGE_UNIT_COST)
            m_UnitCost = pProcessProps->GetUnitCost();
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPUnitProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPUnitProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        ZBBPUnitProperties* pProcessProp = (ZBBPUnitProperties*)pProp;

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPUnitProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPUnitProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPUnitProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPUnitProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPUnitProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPUnitProperties::GetValue(const int nPropId, float& fValue) const
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
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPUnitProperties::GetValue(const int nPropId, CString& strValue) const
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
        strValue = m_UnitName;
        break;
    default:
        throw new CODPropertyConversionException();
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::GetValue(const int nPropId, int& nValue) const
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::GetValue(const int nPropId, UINT& nValue) const
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::GetValue(const int nPropId, DWORD& dwValue) const
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::GetValue(const int nPropId, float& fValue) const
{
    switch (nPropId)
    {
    case Z_UNIT_COST:
        fValue = m_UnitCost;
        break;
    case Z_UNIT_NAME:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

//@mfunc | ZBBPUnitProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPUnitProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPUnitProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPUnitProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPUnitProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPUnitProperties::SetValue(const int nPropId, const float fValue)
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
//@comm See <t Fill Property Identifiers> for a list property IDs supported.
// This function will throw a <c CODPropertyConversionException> exception
// if the data type of the argument passed in is not compatible with the
// given property identifier.

BOOL ZBBPUnitProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
        m_UnitName = lpszValue;
        break;

    default:
        throw new CODPropertyConversionException();
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::SetValue(const int nPropId, const int nValue)
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::SetValue(const int nPropId, const UINT nValue)
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::SetValue(const int nPropId, const DWORD dwValue)
{
    switch (nPropId)
    {
    case Z_UNIT_NAME:
    case Z_UNIT_COST:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPUnitProperties::SetValue(const int nPropId, const float fValue)
{
    switch (nPropId)
    {
    case Z_UNIT_COST:
        m_UnitCost = fValue;
        break;
    case Z_UNIT_NAME:
    case Z_UNIT_GUID:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPUnitProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE( "ZBBPUnitProperties::Serialize : Start Save\n" );

        PUT_SCHEMA(ar, ZBBPUnitProperties);
        ar << m_UnitName;
        ar << m_UnitCost;

        TRACE( "ZBBPUnitProperties::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBBPUnitProperties::Serialize : Start Read\n" );

        UINT nSchema;
        GET_SCHEMA(ar, nSchema);
        ar >> m_UnitName;
        ar >> m_UnitCost;

        TRACE( "ZBBPUnitProperties::Serialize : End Read\n" );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties Property meta-data 

bool ZBBPUnitProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {    
        bool success = true;

        if (success)
        {
            success = RegisterProperty(Z_UNIT_NAME,
                        IDS_Z_UNIT_NAME_NAME, 
                        IDS_Z_UNIT_NAME_DESC,
                        _PropertyAccessor(&ZBBPUnitProperties::GetUnitName,
                        &ZBBPUnitProperties::SetUnitNameEx),
                        VT_BSTR,
                        PROP_DIRECT
                        );
        }

        if (success)
        {
            success = RegisterProperty(Z_UNIT_COST,
                        IDS_Z_UNIT_COST_NAME, 
                        IDS_Z_UNIT_COST_DESC,
                        _PropertyAccessor(&ZBBPUnitProperties::GetUnitCost,
                        &ZBBPUnitProperties::SetUnitCost),
                        VT_R4,
                        PROP_DIRECT
                        );
        }

        if (!success)
        {
            ZBBPUnitProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties diagnostics

#ifdef _DEBUG
void ZBBPUnitProperties::AssertValid() const
{
    CODIntProperty::AssertValid();

}

void ZBBPUnitProperties::Dump(CDumpContext& dc) const
{
    CODIntProperty::Dump(dc);

    dc << "Unit name = " << m_UnitName << "\n";
    dc << "Unit Cost = " << m_UnitCost << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
