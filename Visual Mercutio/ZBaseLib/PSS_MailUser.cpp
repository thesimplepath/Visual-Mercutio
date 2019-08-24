/****************************************************************************
 * ==> PSS_MailUser --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a mail user                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_MailUser.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_MailUser, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_MailUser
//---------------------------------------------------------------------------
PSS_MailUser::PSS_MailUser(const CString& personName, ULONG recipClass) :
    m_PersonName(personName),
    m_RecipClass(recipClass)
{}
//---------------------------------------------------------------------------
PSS_MailUser::PSS_MailUser(ZUser& personName, ULONG recipClass) :
    m_PersonName(personName.GetMailAddress()),
    m_RecipClass(recipClass)
{}
//---------------------------------------------------------------------------
PSS_MailUser::PSS_MailUser(const PSS_MailUser& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_MailUser::~PSS_MailUser()
{}
//---------------------------------------------------------------------------
const PSS_MailUser& PSS_MailUser::operator = (const PSS_MailUser& other)
{
    m_PersonName = other.m_PersonName;
    m_RecipClass = other.m_RecipClass;
    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_MailUser& user)
{
    ar >> user.m_PersonName;
    ar >> user.m_RecipClass;
    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, PSS_MailUser& user)
{
    ar << user.m_PersonName;
    ar << user.m_RecipClass;
    return ar;
}
//---------------------------------------------------------------------------
PSS_MailUser* PSS_MailUser::Clone() const
{
    std::unique_ptr<PSS_MailUser> pNewPerson(new PSS_MailUser(*this));
    return pNewPerson.release();
}
//---------------------------------------------------------------------------
void PSS_MailUser::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        // write the elements
        ar << *this;
    else
        // read the elements
        ar >> *this;
}
//---------------------------------------------------------------------------
