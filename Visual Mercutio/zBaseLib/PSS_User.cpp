/****************************************************************************
 * ==> PSS_User ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_User.h"

// processsoft
#include "PSS_BaseDocument.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_User, CObject)
//---------------------------------------------------------------------------
// PSS_User
//---------------------------------------------------------------------------
PSS_User::PSS_User(const CString& userName,
                   const CString& mailAddress,
                   const CString& description,
                   const CString& responsible,
                   const CString& departement,
                   BOOL           isAdministrator,
                   const CString& displayName) :
    CObject(),
    m_UserName(userName),
    m_Description(description),
    m_MailAddress(mailAddress),
    m_Responsible(responsible),
    m_Departement(departement),
    m_DisplayName(displayName),
    m_IsAdministrator(isAdministrator)
{}
//---------------------------------------------------------------------------
PSS_User::PSS_User(const PSS_User& other) :
    CObject(),
    m_IsAdministrator(FALSE)
{
      *this = other;
}
//---------------------------------------------------------------------------
PSS_User::~PSS_User()
{}
//---------------------------------------------------------------------------
const PSS_User& PSS_User::operator = (const PSS_User& other)
{
    m_UserName        = other.m_UserName;
    m_Description     = other.m_Description;
    m_MailAddress     = other.m_MailAddress;
    m_Responsible     = other.m_Responsible;
    m_Departement     = other.m_Departement;
    m_DisplayName     = other.m_DisplayName;
    m_IsAdministrator = other.m_IsAdministrator;
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_User::operator == (const PSS_User& other)
{
    return !m_UserName.CompareNoCase(other.m_UserName);
}
//---------------------------------------------------------------------------
BOOL PSS_User::operator == (const CString& other)
{
    return !m_UserName.CompareNoCase(other);
}
//---------------------------------------------------------------------------
BOOL PSS_User::operator == (LPCTSTR pOther)
{
    return !m_UserName.CompareNoCase(pOther);
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_User& user)
{
    ar >> user.m_UserName;
    ar >> user.m_MailAddress;
    ar >> user.m_Description;
    ar >> user.m_Responsible;
    ar >> user.m_Departement;

    WORD wValue;
    ar >> wValue;
    user.m_IsAdministrator = BOOL(wValue);

    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 16)
        ar >> user.m_DisplayName;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_User& user)
{
    ar << user.m_UserName;
    ar << user.m_MailAddress;
    ar << user.m_Description;
    ar << user.m_Responsible;
    ar << user.m_Departement;
    ar << WORD(user.m_IsAdministrator);
    ar << user.m_DisplayName;
    return ar;
}
//---------------------------------------------------------------------------
PSS_User* PSS_User::Clone() const
{
    return new PSS_User(*this);
}
//---------------------------------------------------------------------------
