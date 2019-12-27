/****************************************************************************
 * ==> PSS_RulesEntity -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules entity                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RulesEntity.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_RulesEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_RulesEntity
//---------------------------------------------------------------------------
PSS_RulesEntity::PSS_RulesEntity(const CString&   name,
                                 const CString&   description,
                                 PSS_RulesEntity* pParent) :
    CObject(),
    m_pParent(pParent),
    m_EntityName(name),
    m_EntityDescription(description)
{
    CreateGUID();
}
//---------------------------------------------------------------------------
PSS_RulesEntity::~PSS_RulesEntity()
{}
//---------------------------------------------------------------------------
void PSS_RulesEntity::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_GUID;
        ar << m_EntityName;
        ar << m_EntityDescription;
    }
    else
    {
        // read the elements
        ar >> m_GUID;
        ar >> m_EntityName;
        ar >> m_EntityDescription;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RulesEntity::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_RulesEntity::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_RulesEntity::CreateGUID()
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
