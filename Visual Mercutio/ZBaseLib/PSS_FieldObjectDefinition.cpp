/****************************************************************************
 * ==> PSS_FieldObjectDefinition -------------------------------------------*
 ****************************************************************************
 * Description : Provides a field object definition                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldObjectDefinition.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FieldObjectDefinition, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FieldObjectDefinition
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition::PSS_FieldObjectDefinition() :
    CObject(),
    m_pObject(NULL),
    m_Sorted(FALSE)
{}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition::PSS_FieldObjectDefinition(const PSS_FieldObjectDefinition& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition::~PSS_FieldObjectDefinition()
{
    if (m_pObject)
        delete m_pObject;
}
//---------------------------------------------------------------------------
const PSS_FieldObjectDefinition& PSS_FieldObjectDefinition::operator = (const PSS_FieldObjectDefinition& other)
{
    if (other.m_pObject)
        m_pObject = other.m_pObject->Clone();
    else
        m_pObject = NULL;

    m_Description         = other.m_Description;
    m_ClassName           = other.m_ClassName;
    m_FieldName           = other.m_FieldName;
    m_HelpUserDescription = other.m_HelpUserDescription;
    m_Sorted              = other.m_Sorted;

    return *this;
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_FieldObjectDefinition::Clone() const
{
    std::unique_ptr<PSS_FieldObjectDefinition> pObject(new PSS_FieldObjectDefinition(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_FieldName;
        ar << m_Description;
        ar << m_ClassName;
        ar << m_HelpUserDescription;
        ar << WORD(m_Sorted);
        ar << m_pObject;
    }
    else
    {
        // read the elements
        ar >> m_FieldName;
        ar >> m_Description;
        ar >> m_ClassName;
        ar >> m_HelpUserDescription;

        WORD wValue;
        ar >> wValue;
        m_Sorted = BOOL(wValue);

        ar >> (CObject*&)m_pObject;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldObjectDefinition::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldObjectDefinition::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
