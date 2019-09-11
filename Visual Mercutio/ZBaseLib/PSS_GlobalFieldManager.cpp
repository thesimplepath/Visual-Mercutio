/****************************************************************************
 * ==> PSS_GlobalFieldManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a global field container for the document         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_GlobalFieldManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_GlobalFieldManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_GlobalFieldManager
//---------------------------------------------------------------------------
PSS_GlobalFieldManager::PSS_GlobalFieldManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_GlobalFieldManager::PSS_GlobalFieldManager(const PSS_GlobalFieldManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_GlobalFieldManager::~PSS_GlobalFieldManager()
{
    FreeList();
}
//---------------------------------------------------------------------------
const PSS_GlobalFieldManager& PSS_GlobalFieldManager::operator = (const PSS_GlobalFieldManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_GlobalFieldManager::AddField(PSS_FieldObjectDefinition* pField)
{
    return m_GlobalFieldArray.Add(pField);
}
//---------------------------------------------------------------------------
BOOL PSS_GlobalFieldManager::DeleteField(const CString& name)
{
    const int arrayCount = m_GlobalFieldArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
        if (((PSS_FieldObjectDefinition*)m_GlobalFieldArray[i])->GetFieldName() == name)
        {
            // free memory pointed at location
            delete ((PSS_FieldObjectDefinition*)(m_GlobalFieldArray[i]));

            // remove the element from the array
            m_GlobalFieldArray.RemoveAt(i);

            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_GlobalFieldManager::DeleteAllField()
{
    m_GlobalFieldArray.RemoveAll();

    return !m_GlobalFieldArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_GlobalFieldManager::FindField(const CString& name)
{
    const int arrayCount = m_GlobalFieldArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
        if (((PSS_FieldObjectDefinition*)m_GlobalFieldArray[i])->GetFieldName() == name)
            return (PSS_FieldObjectDefinition*)m_GlobalFieldArray[i];

    return NULL;
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_GlobalFieldManager::GetAt(int index)
{
    if (index < m_GlobalFieldArray.GetSize())
        return (PSS_FieldObjectDefinition*)m_GlobalFieldArray[index];

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_GlobalFieldManager::GetDescription(const CString& name)
{
    PSS_FieldObjectDefinition* pObject;

    if (pObject = FindField(name))
        return pObject->GetDescription();

    return "";
}
//---------------------------------------------------------------------------
CString PSS_GlobalFieldManager::GetClassName(const CString& name)
{
    PSS_FieldObjectDefinition* pObject;

    if (pObject = FindField(name))
        return pObject->GetClassName();

    return "";
}
//---------------------------------------------------------------------------
const CStringArray& PSS_GlobalFieldManager::GetFieldNameArray()
{
    m_FieldNameArray.RemoveAll();

    const int arrayCount = m_GlobalFieldArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
        m_FieldNameArray.Add(((PSS_FieldObjectDefinition*)m_GlobalFieldArray[i])->GetFieldName());

    return m_FieldNameArray;
}
//---------------------------------------------------------------------------
void PSS_GlobalFieldManager::CopyFieldDefinition(const CString& name, PSS_PlanFinObject* pObj, ZDDocument* pDoc)
{
    PSS_FieldObjectDefinition* pObjectDef = FindField(name);

    if (pObjectDef)
    {
        pObj->SetFormatType   (pObjectDef->GetObject()->GetFormatType());
        pObj->SetJustify      (pObjectDef->GetObject()->GetJustify(NULL));
        pObj->SetStyle        (pObjectDef->GetObject()->GetStyle());
        pObj->SetAngle        (pObjectDef->GetObject()->GetAngle(), pDoc);
        pObj->SetIsVisible    (pObjectDef->GetObject()->GetIsVisible());
        pObj->SetMustBePrinted(pObjectDef->GetObject()->GetMustBePrinted());
        pObj->SetColor        (pObjectDef->GetObject()->GetColor());
        pObj->SetFillColor    (pObjectDef->GetObject()->GetFillColor());
        pObj->SetFont         (pObjectDef->GetObject()->GetFont());
        pObj->SetStyle        (pObjectDef->GetObject()->GetStyle());
        pObj->SetEmptyStyle   (pObjectDef->GetObject()->GetEmptyStyle());
        pObj->SetDefaultValue (pObjectDef->GetObject()->GetDefaultValue());
        pObj->ConvertFormattedObject(((PSS_PlanFinObject*)pObjectDef->GetObject())->GetUnformattedObject());
    }
}
//---------------------------------------------------------------------------
void PSS_GlobalFieldManager::Serialize(CArchive& ar)
{
    m_GlobalFieldArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GlobalFieldManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GlobalFieldManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_GlobalFieldManager::FreeList()
{
    const int arrayCount = m_GlobalFieldArray.GetSize();

    // delete all allocated file objects
    for (int i = 0; i < arrayCount; ++i)
        delete m_GlobalFieldArray[i];

    m_GlobalFieldArray.RemoveAll();
}
//---------------------------------------------------------------------------
