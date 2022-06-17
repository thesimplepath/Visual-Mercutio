/****************************************************************************
 * ==> PSS_TaskListPropertiesBP --------------------------------------------*
 ****************************************************************************
 * Description : Provides the task list properties for banking process      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TaskListPropertiesBP.h"

// resources
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_TaskListPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_TaskListPropertiesBP
//---------------------------------------------------------------------------
PSS_TaskListPropertiesBP::PSS_TaskListPropertiesBP(int propID) :
    CODIntProperty(propID)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_TaskListPropertiesBP::PSS_TaskListPropertiesBP(const PSS_TaskListPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_TaskList = other.GetTaskList();
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_TaskListPropertiesBP::~PSS_TaskListPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_TaskListPropertiesBP& PSS_TaskListPropertiesBP::operator = (const PSS_TaskListPropertiesBP& other)
{
    SetId(other.GetId());
    SetTaskList(other.GetTaskList());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::operator == (const PSS_TaskListPropertiesBP& other) const
{
    return (GetTaskList() == other.GetTaskList());
}
//---------------------------------------------------------------------------
void PSS_TaskListPropertiesBP::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_TaskListPropertiesBP* pProcessProps = dynamic_cast<PSS_TaskListPropertiesBP*>(pProp);

    if (pProcessProps)
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Task_List)
            m_TaskList = pProcessProps->GetTaskList();
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Task_List_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_TaskListPropertiesBP* pProcessProp = dynamic_cast<PSS_TaskListPropertiesBP*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_TaskListPropertiesBP::SetTaskList(LPCTSTR pValue)
{
    if (pValue)
        m_TaskList = pValue;
    else
        THROW("PSS_TaskListPropertiesBP - Invalid task list");
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Task_List_ID: value = m_TaskList; break;
        default:                                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Task_List_ID: throw new CODPropertyConversionException();
        default:             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TaskListPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Task_List_ID: m_TaskList = pValue; break;
        default:                                  return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_TaskListPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_TaskListPropertiesBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_TaskListPropertiesBP);
        ar << m_TaskList;

        TRACE("PSS_TaskListPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_TaskListPropertiesBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_TaskList;

        TRACE("PSS_TaskListPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TaskListPropertiesBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TaskListPropertiesBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);

        dc << "Task list = " << m_TaskList << "\n";
    }
#endif
//---------------------------------------------------------------------------
void PSS_TaskListPropertiesBP::SetTaskListEx(const CString value)
{
    SetTaskList(value);
}
//---------------------------------------------------------------------------
bool PSS_TaskListPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        const bool success = RegisterProperty(M_Task_List_ID,
                                              IDS_Z_TASK_LIST_NAME,
                                              IDS_Z_TASK_LIST_DESC,
                                              _PropertyAccessor(&PSS_TaskListPropertiesBP::GetTaskList,
                                                                &PSS_TaskListPropertiesBP::SetTaskListEx),
                                              VT_BSTR,
                                              PROP_DIRECT);

        if (!success)
            GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
