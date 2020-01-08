/****************************************************************************
 * ==> PSS_UserRoleEntity --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user role entity                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserRoleEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_UserRoleEntity, PSS_UserEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_UserRoleEntity
//---------------------------------------------------------------------------
PSS_UserRoleEntity::PSS_UserRoleEntity(const CString&  name,
                                       const CString&  description,
                                       PSS_UserEntity* pParent) :
    PSS_UserEntity(name, description, 0, pParent)
{}
//---------------------------------------------------------------------------
PSS_UserRoleEntity::PSS_UserRoleEntity(const PSS_UserRoleEntity& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_UserRoleEntity::~PSS_UserRoleEntity()
{}
//---------------------------------------------------------------------------
PSS_UserRoleEntity& PSS_UserRoleEntity::operator = (const PSS_UserRoleEntity& other)
{
    PSS_UserEntity::operator = ((const PSS_UserEntity&)other);

    return *this;
}
//---------------------------------------------------------------------------
PSS_UserEntity* PSS_UserRoleEntity::Clone() const
{
    return new PSS_UserRoleEntity(*this);
}
//---------------------------------------------------------------------------
bool PSS_UserRoleEntity::ShowProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_UserRoleEntity::Serialize(CArchive& ar)
{
    PSS_UserEntity::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserRoleEntity::AssertValid() const
    {
        PSS_UserEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_UserRoleEntity::Dump(CDumpContext& dc) const
    {
        PSS_UserEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
