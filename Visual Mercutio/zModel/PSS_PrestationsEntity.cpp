/****************************************************************************
 * ==> PSS_PrestationsEntity -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a prestations entity                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PrestationsEntity.h"

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
IMPLEMENT_SERIAL(PSS_PrestationsEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_RulesEntity
//---------------------------------------------------------------------------
PSS_PrestationsEntity::PSS_PrestationsEntity(const CString&         name,
                                             const CString&         description,
                                             PSS_PrestationsEntity* pParent) :
    CObject(),
    m_pParent(pParent),
    m_EntityName(name),
    m_EntityDescription(description)
{
    CreateGUID();
}
//---------------------------------------------------------------------------
PSS_PrestationsEntity::~PSS_PrestationsEntity()
{}
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::Serialize(CArchive& ar)
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
    void PSS_PrestationsEntity::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PrestationsEntity::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PrestationsEntity::CreateGUID()
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
