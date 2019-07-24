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

IMPLEMENT_SERIAL(ZBUserRoleEntity, ZBUserEntity, g_DefVersion)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserRoleEntity::ZBUserRoleEntity( const CString Name /*= ""*/, const CString Description /*= ""*/, ZBUserEntity* pParent /*= NULL*/ )
: ZBUserEntity(Name, Description, 0, pParent)
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
    ZBUserEntity::operator=( (const ZBUserEntity&)src);

    return *this;
}

ZBUserEntity* ZBUserRoleEntity::Clone() const
{
    return (new ZBUserRoleEntity(*this));
}

bool ZBUserRoleEntity::DisplayProperties()
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////
// ZBUserRoleEntity serialization

void ZBUserRoleEntity::Serialize (CArchive& ar)
{
    ZBUserEntity::Serialize(ar);
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
    ZBUserEntity::AssertValid();
}

void ZBUserRoleEntity::Dump(CDumpContext& dc) const
{
    ZBUserEntity::Dump(dc);
}
#endif //_DEBUG
