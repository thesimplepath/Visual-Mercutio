// ZBUserRoleEntity.cpp: implementation of the ZBUserRoleEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUserRoleEntity.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBUserRoleEntity, PSS_UserEntity, g_DefVersion)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserRoleEntity::ZBUserRoleEntity( const CString Name /*= ""*/, const CString Description /*= ""*/, PSS_UserEntity* pParent /*= NULL*/ )
: PSS_UserEntity(Name, Description, 0, pParent)
{
}

ZBUserRoleEntity::~ZBUserRoleEntity()
{

}

ZBUserRoleEntity::ZBUserRoleEntity(const ZBUserRoleEntity& src)
{
    *this = src;
}

ZBUserRoleEntity& ZBUserRoleEntity::operator=(const ZBUserRoleEntity& src)
{
    // Call the base class assignement operator
    PSS_UserEntity::operator=( (const PSS_UserEntity&)src);

    return *this;
}

PSS_UserEntity* ZBUserRoleEntity::Clone() const
{
    return new ZBUserRoleEntity(*this);
}

bool ZBUserRoleEntity::DisplayProperties()
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////
// ZBUserRoleEntity serialization

void ZBUserRoleEntity::Serialize (CArchive& ar)
{
    PSS_UserEntity::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
    }
    else
    {    // Read the elements
    }
}


/////////////////////////////////////////////////////////////////////////////
// ZBUserRoleEntity diagnostics

#ifdef _DEBUG
void ZBUserRoleEntity::AssertValid() const
{
    PSS_UserEntity::AssertValid();
}

void ZBUserRoleEntity::Dump(CDumpContext& dc) const
{
    PSS_UserEntity::Dump(dc);
}
#endif //_DEBUG
