//## begin module%36725CA70063.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36725CA70063.cm

//## begin module%36725CA70063.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%36725CA70063.cp

//## Module: ZUser%36725CA70063; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZUser.cpp

//## begin module%36725CA70063.additionalIncludes preserve=no
//## end module%36725CA70063.additionalIncludes

//## begin module%36725CA70063.includes preserve=yes
#include <StdAfx.h>
//## end module%36725CA70063.includes

// ZUser
#include "ZUser.h"
//## begin module%36725CA70063.declarations preserve=no
//## end module%36725CA70063.declarations

//## begin module%36725CA70063.additionalDeclarations preserve=yes
#include "BaseDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(ZUser, CObject)

//## end module%36725CA70063.additionalDeclarations


// Class ZUser 








ZUser::ZUser(const ZUser &right)
  //## begin ZUser::ZUser%copy.hasinit preserve=no
  //## end ZUser::ZUser%copy.hasinit
  //## begin ZUser::ZUser%copy.initialization preserve=yes
      : m_IsAdministrator(FALSE)
  //## end ZUser::ZUser%copy.initialization
{
  //## begin ZUser::ZUser%copy.body preserve=yes
  	*this = right;
  //## end ZUser::ZUser%copy.body
}

ZUser::ZUser (CString UserName, CString MailAddress, CString Description, CString Responsible, CString Departement, BOOL IsAdministrator, CString DisplayName)
  //## begin ZUser::ZUser%913459631.hasinit preserve=no
  //## end ZUser::ZUser%913459631.hasinit
  //## begin ZUser::ZUser%913459631.initialization preserve=yes
  : m_UserName(UserName), m_MailAddress(MailAddress), m_Description(Description), m_Responsible(Responsible), 
	m_Departement(Departement),
    m_IsAdministrator(IsAdministrator),
	m_DisplayName(DisplayName)
  //## end ZUser::ZUser%913459631.initialization
{
  //## begin ZUser::ZUser%913459631.body preserve=yes
  //## end ZUser::ZUser%913459631.body
}


ZUser::~ZUser()
{
  //## begin ZUser::~ZUser%.body preserve=yes
  //## end ZUser::~ZUser%.body
}


const ZUser & ZUser::operator=(const ZUser &right)
{
  //## begin ZUser::operator=%.body preserve=yes
  	m_UserName = right.m_UserName;
  	m_MailAddress = right.m_MailAddress;
  	m_Description = right.m_Description;
  	m_Responsible = right.m_Responsible;
	m_Departement = right.m_Departement;
    m_IsAdministrator = right.m_IsAdministrator;
	m_DisplayName = right.m_DisplayName;
  	return *this;
  //## end ZUser::operator=%.body
}



//## Other Operations (implementation)
BOOL ZUser::operator == (const ZUser& User)
{
  //## begin ZUser::operator==%936516041.body preserve=yes
  	return m_UserName.CompareNoCase( User.m_UserName ) == 0;
  //## end ZUser::operator==%936516041.body
}

BOOL ZUser::operator == (const CString str)
{
  //## begin ZUser::operator==%936516039.body preserve=yes
  	return m_UserName.CompareNoCase( str ) == 0;
  //## end ZUser::operator==%936516039.body
}

BOOL ZUser::operator == (LPCTSTR lpsz)
{
  //## begin ZUser::operator==%936516040.body preserve=yes
  	return m_UserName.CompareNoCase( lpsz ) == 0;
  //## end ZUser::operator==%936516040.body
}

ZUser* ZUser::Clone ()
{
  //## begin ZUser::Clone%913459632.body preserve=yes
  	ZUser*	pNewUser = new ZUser(*this);
  	return pNewUser;
  //## end ZUser::Clone%913459632.body
}

CArchive& operator >> (CArchive& ar, ZUser& User)
{
  //## begin ZUser::operator >>%913659096.body preserve=yes
  	ar >> User.m_UserName;
  	ar >> User.m_MailAddress;
  	ar >> User.m_Description;
  	ar >> User.m_Responsible;
	ar >> User.m_Departement;
	WORD	wValue;
    ar >> wValue;
	User.m_IsAdministrator = (BOOL)wValue;

	if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 16)
		ar >> User.m_DisplayName;

  	return ar;
  //## end ZUser::operator >>%913659096.body
}

CArchive& operator << (CArchive& ar, ZUser& User)
{
  //## begin ZUser::operator <<%913659097.body preserve=yes
  	ar << User.m_UserName;
  	ar << User.m_MailAddress;
  	ar << User.m_Description;
  	ar << User.m_Responsible;
	ar << User.m_Departement;
    ar << (WORD)User.m_IsAdministrator;
	ar << User.m_DisplayName;
  	return ar;
  //## end ZUser::operator <<%913659097.body
}

// Additional Declarations
  //## begin ZUser%36725BAA0204.declarations preserve=yes
  //## end ZUser%36725BAA0204.declarations

//## begin module%36725CA70063.epilog preserve=yes
//## end module%36725CA70063.epilog
