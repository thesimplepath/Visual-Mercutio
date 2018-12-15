/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPTextItemListProperties
//@module ZBBPTextItemListProp.cpp | Implementation of the <c ZBBPTextItemListProperties> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "ZBBPTextItemListProp.h"

// Resources
#include "zRMdlBP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace sfl;


/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPTextItemListProperties, CODIntProperty, def_Version)

//@mfunc | ZBBPTextItemListProperties | ZBBPTextItemListProperties | Constructor.
//
//@syntax ZBBPTextItemListProperties::ZBBPTextItemListProperties(int nId);
//@syntax ZBBPTextItemListProperties::ZBBPTextItemListProperties(const ZBBPTextItemListProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPTextItemListProperties& | propProcess | The fill property to copy.
ZBBPTextItemListProperties::ZBBPTextItemListProperties(int nId) 
    : CODIntProperty(nId)
{
    m_TextItemList  = _T("");

    RegisterProperties();
}

ZBBPTextItemListProperties::ZBBPTextItemListProperties(const ZBBPTextItemListProperties& propProcess) 
    : CODIntProperty(propProcess.GetId())
{
    m_TextItemList  = propProcess.GetTextItemList();

    RegisterProperties();
}

//@mfunc Destructor.
ZBBPTextItemListProperties::~ZBBPTextItemListProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties attributes
 




//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBBPTextItemListProperties::SetTextItemList(LPCTSTR lpszValue)
{
    if (lpszValue != NULL)
    {
        m_TextItemList = lpszValue;
    }
    else
    {
        TRACE0("Z -> Invalid Decision List pointer!\n");
        ASSERT(FALSE);
    }
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
void ZBBPTextItemListProperties::SetTextItemListEx(const CString value)
{
    SetTextItemList(value);
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPTextItemListProperties::CompareId(const int nId) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_TEXTITEM_LIST;
    return (nId >= nIdMin && nId <= nIdMax);
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPTextItemListProperties& ZBBPTextItemListProperties::operator=(const ZBBPTextItemListProperties& propProcess)
{
    SetId(propProcess.GetId());
    SetTextItemList(propProcess.GetTextItemList());

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPTextItemListProperties::operator==(const ZBBPTextItemListProperties propProcess) const
{
    return (GetTextItemList() == propProcess.GetTextItemList());
}


//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPTextItemListProperties::Merge(CODProperty* pProperty, DWORD dwChangeFlags)
{
    ZBBPTextItemListProperties* pProcessProps = (ZBBPTextItemListProperties*)pProperty;

    if (pProcessProps)
    {
        if (dwChangeFlags & Z_CHANGE_TEXTITEM_LIST)
            m_TextItemList = pProcessProps->GetTextItemList();
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPTextItemListProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPTextItemListProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        ZBBPTextItemListProperties* pProcessProp = (ZBBPTextItemListProperties*)pProp;

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPTextItemListProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, CString& strValue) const
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        strValue = m_TextItemList;
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, int& nValue) const
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, UINT& nValue) const
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, DWORD& dwValue) const
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::GetValue(const int nPropId, float& fValue) const
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

//@mfunc | ZBBPTextItemListProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        m_TextItemList = lpszValue;
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const int nValue)
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const UINT nValue)
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const DWORD dwValue)
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTextItemListProperties::SetValue(const int nPropId, const float fValue)
{
    switch (nPropId)
    {
    case Z_TEXTITEM_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPTextItemListProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE( "ZBBPTextItemListProperties::Serialize : Start Save\n" );

        PUT_SCHEMA(ar, ZBBPTextItemListProperties);
        ar << m_TextItemList;

        TRACE( "ZBBPTextItemListProperties::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBBPTextItemListProperties::Serialize : Start Read\n" );

        UINT nSchema;
        GET_SCHEMA(ar, nSchema);
        ar >> m_TextItemList;

        TRACE( "ZBBPTextItemListProperties::Serialize : End Read\n" );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties Property meta-data 

bool ZBBPTextItemListProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {    
        bool success = true;

        if (success)
        {
            success = RegisterProperty(Z_TEXTITEM_LIST,
                        IDS_Z_TEXTITEM_LIST_NAME, 
                        IDS_Z_TEXTITEM_LIST_DESC,
                        _PropertyAccessor(&ZBBPTextItemListProperties::GetTextItemList,
                        &ZBBPTextItemListProperties::SetTextItemListEx),
                        VT_BSTR,
                        PROP_DIRECT
                        );
        }
        if (!success)
        {
            ZBBPTextItemListProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties diagnostics

#ifdef _DEBUG
void ZBBPTextItemListProperties::AssertValid() const
{
    CODIntProperty::AssertValid();

}

void ZBBPTextItemListProperties::Dump(CDumpContext& dc) const
{
    CODIntProperty::Dump(dc);

    dc << "Text Item list = " << m_TextItemList << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
