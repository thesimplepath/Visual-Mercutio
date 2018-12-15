/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPTaskListProperties
//@module ZBBPTaskListProp.cpp | Implementation of the <c ZBBPTaskListProperties> class.
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


#include "ZBBPTaskListProp.h"

// Resources
#include "zRMdlBP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace sfl;


/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties construction/destruction

IMPLEMENT_SERIAL(ZBBPTaskListProperties, CODIntProperty, def_Version)

//@mfunc | ZBBPTaskListProperties | ZBBPTaskListProperties | Constructor.
//
//@syntax ZBBPTaskListProperties::ZBBPTaskListProperties(int nId);
//@syntax ZBBPTaskListProperties::ZBBPTaskListProperties(const ZBBPTaskListProperties& propProcess);
//
//@parmopt int | nId | OD_PROP_FILL | The identifier of the property.
//@parm ZBBPTaskListProperties& | propProcess | The fill property to copy.
ZBBPTaskListProperties::ZBBPTaskListProperties(int nId) 
    : CODIntProperty(nId)
{
    m_TaskList      = _T("");

    RegisterProperties();
}

ZBBPTaskListProperties::ZBBPTaskListProperties(const ZBBPTaskListProperties& propProcess) 
    : CODIntProperty(propProcess.GetId())
{
    m_TaskList      = propProcess.GetTaskList();

    RegisterProperties();
}

//@mfunc Destructor.
ZBBPTaskListProperties::~ZBBPTaskListProperties()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties attributes
 


//@mfunc Sets the task list.
//@rdesc void
//@parm The new task list.
void ZBBPTaskListProperties::SetTaskList(LPCTSTR lpszValue)
{
    if (lpszValue != NULL)
    {
        m_TaskList = lpszValue;
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
void ZBBPTaskListProperties::SetTaskListEx(const CString value)
{
    SetTaskList(value);
}


/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties operations

//@mfunc Compare the property identifier with another identifier.
//@rdesc BOOL
//@parm Property identifier to compare to.
BOOL ZBBPTaskListProperties::CompareId(const int nId) const
{
    int nIdMin = m_nId;
    int nIdMax = m_nId + Z_TASK_LIST;
    return (nId >= nIdMin && nId <= nIdMax);
}

//@mfunc Sets this property object equal to the one passed in.
//@rdesc A reference to this property after copying the property.
//@parm The property to copy.
ZBBPTaskListProperties& ZBBPTaskListProperties::operator=(const ZBBPTaskListProperties& propProcess)
{
    SetId(propProcess.GetId());
    SetTaskList(propProcess.GetTaskList());

    return *this;
}

//@mfunc Tests if this property is equal to the one passed in.
//@rdesc Non-zero if the two properties are equal.
//@parm The property to test against.
BOOL ZBBPTaskListProperties::operator==(const ZBBPTaskListProperties propProcess) const
{
    return (GetTaskList() == propProcess.GetTaskList());
}


//@mfunc Merges the values of the property passed in with the values in this
// property. Only the properties indicated by dwChangeFlags are changed.
//@rdesc void
//@parm The property object to merge into this one.
//@parmopt DWORD | dwChangeFlags | OD_CHANGE_ALL | Indicates which values 
// to merge into this property object.
void ZBBPTaskListProperties::Merge(CODProperty* pProperty, DWORD dwChangeFlags)
{
    ZBBPTaskListProperties* pProcessProps = (ZBBPTaskListProperties*)pProperty;

    if (pProcessProps)
    {
        if (dwChangeFlags & Z_CHANGE_TASK_LIST)
            m_TaskList = pProcessProps->GetTaskList();
    }
}

//@mfunc Tests if this property is equal to the one passed in. This method
// takes a pointer to a property unlike <mf ZBBPTaskListProperties::operator==>.
//@rdesc Non-zero if the two properties are equal.
//@parm A pointer to the property to test against.
BOOL ZBBPTaskListProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        ZBBPTaskListProperties* pProcessProp = (ZBBPTaskListProperties*)pProp;

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IODPropertyContainer interface

//@mfunc | ZBBPTaskListProperties | GetValue | Gets the value of the given property.
//
//@syntax BOOL ZBBPTaskListProperties::GetValue(const int nPropId, CString& strValue) const
//@syntax BOOL ZBBPTaskListProperties::GetValue(const int nPropId, int& nValue) const
//@syntax BOOL ZBBPTaskListProperties::GetValue(const int nPropId, UINT& nValue) const
//@syntax BOOL ZBBPTaskListProperties::GetValue(const int nPropId, DWORD& dwValue) const
//@syntax BOOL ZBBPTaskListProperties::GetValue(const int nPropId, float& fValue) const
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

BOOL ZBBPTaskListProperties::GetValue(const int nPropId, CString& strValue) const
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        strValue = m_TaskList;
        break;
/*
    case OD_FONT_HEIGHT:
        throw new CODPropertyConversionException();
        break;
*/
    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::GetValue(const int nPropId, int& nValue) const
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::GetValue(const int nPropId, UINT& nValue) const
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::GetValue(const int nPropId, DWORD& dwValue) const
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::GetValue(const int nPropId, float& fValue) const
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

//@mfunc | ZBBPTaskListProperties | SetValue | Sets the value of the given property.
//
//@syntax BOOL ZBBPTaskListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
//@syntax BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const int nValue)
//@syntax BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const UINT nValue)
//@syntax BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const DWORD dwValue)
//@syntax BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const float fValue)
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

BOOL ZBBPTaskListProperties::SetValue(const int nPropId, LPCTSTR lpszValue)
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        m_TaskList = lpszValue;
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const int nValue)
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const UINT nValue)
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const DWORD dwValue)
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

BOOL ZBBPTaskListProperties::SetValue(const int nPropId, const float fValue)
{
    switch (nPropId)
    {
    case Z_TASK_LIST:
        throw new CODPropertyConversionException();
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties serialization

//@mfunc Serializes the line properties.
//@rdesc void
//@parm The archive to use for serialization.
void ZBBPTaskListProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE( "ZBBPTaskListProperties::Serialize : Start Save\n" );

        PUT_SCHEMA(ar, ZBBPTaskListProperties);
        ar << m_TaskList;

        TRACE( "ZBBPTaskListProperties::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBBPTaskListProperties::Serialize : Start Read\n" );

        UINT nSchema;
        GET_SCHEMA(ar, nSchema);
        ar >> m_TaskList;

        TRACE( "ZBBPTaskListProperties::Serialize : End Read\n" );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties Property meta-data 

bool ZBBPTaskListProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {    
        bool success = true;

        if (success)
        {
            success = RegisterProperty(Z_TASK_LIST,
                        IDS_Z_TASK_LIST_NAME, 
                        IDS_Z_TASK_LIST_DESC,
                        _PropertyAccessor(&ZBBPTaskListProperties::GetTaskList,
                        &ZBBPTaskListProperties::SetTaskListEx),
                        VT_BSTR,
                        PROP_DIRECT
                        );
        }

        if (!success)
        {
            ZBBPTaskListProperties::GetPropertyMap().DeleteAll();
        }

        propsRegistered = success;
    }

    return propsRegistered;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTaskListProperties diagnostics

#ifdef _DEBUG
void ZBBPTaskListProperties::AssertValid() const
{
    CODIntProperty::AssertValid();

//    ASSERT(m_ManagementCase.GetLength() > 0);
}

void ZBBPTaskListProperties::Dump(CDumpContext& dc) const
{
    CODIntProperty::Dump(dc);

    dc << "Task list = " << m_TaskList << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
