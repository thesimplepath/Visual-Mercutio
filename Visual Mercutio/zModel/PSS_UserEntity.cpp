/****************************************************************************
 * ==> PSS_UserEntity ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user entity                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserEntity.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_UserEntity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UserEntity
//---------------------------------------------------------------------------
PSS_UserEntity::PSS_UserEntity(const CString&  name,
                               const CString&  description,
                               const float     cost,
                               PSS_UserEntity* pParent) :
    CObject(),
    m_pParent(pParent),
    m_EntityName(name),
    m_EntityDescription(description),
    m_EntityCost(cost)
{
    CreateGUID();
}
//---------------------------------------------------------------------------
PSS_UserEntity::PSS_UserEntity(const PSS_UserEntity& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_UserEntity::~PSS_UserEntity()
{}
//---------------------------------------------------------------------------
PSS_UserEntity& PSS_UserEntity::operator = (const PSS_UserEntity& other)
{
    m_GUID              = other.m_GUID;
    m_EntityName        = other.m_EntityName;
    m_EntityDescription = other.m_EntityDescription;
    m_EntityCost        = other.m_EntityCost;

    return *this;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserEntity::Clone() const
{
    return new PSS_UserEntity(*this);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserEntity::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserEntity::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_UserEntity::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_GUID;
        ar << m_EntityName;
        ar << m_EntityDescription;
        ar << m_EntityCost;
    }
    else
    {
        // read the elements
        CString s;
        ar >> s;

        PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 19)
        {
            m_GUID = s;
            ar >> m_EntityName;
        }
        else
        {
            CreateGUID();
            m_EntityName = s;
        }

        ar >> m_EntityDescription;
        ar >> m_EntityCost;
    }
}
//---------------------------------------------------------------------------
void PSS_UserEntity::CreateGUID()
{
    m_GUID = PSS_GUID::CreateNewGUID();
}
//---------------------------------------------------------------------------
