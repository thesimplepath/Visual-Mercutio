/****************************************************************************
 * ==> PSS_MailUser --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PersonDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZBMailUser, CObject, g_DefVersion)

ZBMailUser::ZBMailUser(const ZBMailUser &right)
{
    *this = right;
}

ZBMailUser::ZBMailUser(CString PersonName, ULONG RecipClass) :
    m_PersonName(PersonName), m_RecipClass(RecipClass)
{}

ZBMailUser::ZBMailUser(ZUser& PersonName, ULONG RecipClass)
//## begin ZBMailUser::ZBMailUser%913659111.hasinit preserve=no
//## end ZBMailUser::ZBMailUser%913659111.hasinit
//## begin ZBMailUser::ZBMailUser%913659111.initialization preserve=yes
    : m_PersonName(PersonName.GetMailAddress()), m_RecipClass(RecipClass)
    //## end ZBMailUser::ZBMailUser%913659111.initialization
{
    //## begin ZBMailUser::ZBMailUser%913659111.body preserve=yes
    //## end ZBMailUser::ZBMailUser%913659111.body
}


ZBMailUser::~ZBMailUser()
{
    //## begin ZBMailUser::~ZBMailUser%.body preserve=yes
    //## end ZBMailUser::~ZBMailUser%.body
}


const ZBMailUser & ZBMailUser::operator=(const ZBMailUser &right)
{
    //## begin ZBMailUser::operator=%.body preserve=yes
    m_PersonName = right.m_PersonName;
    m_RecipClass = right.m_RecipClass;
    return *this;
    //## end ZBMailUser::operator=%.body
}



//## Other Operations (implementation)
ZBMailUser* ZBMailUser::Clone()
{
    //## begin ZBMailUser::Clone%913452743.body preserve=yes
    ZBMailUser*    pNewPerson = new ZBMailUser(*this);
    return pNewPerson;
    //## end ZBMailUser::Clone%913452743.body
}

CArchive& operator >> (CArchive& ar, ZBMailUser& User)
{
    //## begin ZBMailUser::operator >>%928176921.body preserve=yes
    ar >> User.m_PersonName;
    ar >> User.m_RecipClass;
    return ar;
    //## end ZBMailUser::operator >>%928176921.body
}

CArchive& operator << (CArchive& ar, ZBMailUser& User)
{
    //## begin ZBMailUser::operator <<%928176922.body preserve=yes
    ar << User.m_PersonName;
    ar << User.m_RecipClass;
    return ar;
    //## end ZBMailUser::operator <<%928176922.body
}

void ZBMailUser::Serialize(CArchive& ar)
{
    //## begin ZBMailUser::Serialize%928263998.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << *this;
    }
    else
    {
        ar >> *this;
    }
    //## end ZBMailUser::Serialize%928263998.body
}
