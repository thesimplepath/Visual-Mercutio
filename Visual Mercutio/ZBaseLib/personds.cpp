//## begin module%36722E6A030B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36722E6A030B.cm

//## begin module%36722E6A030B.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%36722E6A030B.cp

//## Module: PersonDs%36722E6A030B; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PersonDs.cpp

//## begin module%36722E6A030B.additionalIncludes preserve=no
//## end module%36722E6A030B.additionalIncludes

//## begin module%36722E6A030B.includes preserve=yes
#include <StdAfx.h>
//## end module%36722E6A030B.includes

// PersonDs
#include "PersonDs.h"
//## begin module%36722E6A030B.declarations preserve=no
//## end module%36722E6A030B.declarations

//## begin module%36722E6A030B.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_SERIAL(ZBMailUser, CObject, def_Version)
//## end module%36722E6A030B.additionalDeclarations


// Class ZBMailUser 



ZBMailUser::ZBMailUser(const ZBMailUser &right)
  //## begin ZBMailUser::ZBMailUser%copy.hasinit preserve=no
  //## end ZBMailUser::ZBMailUser%copy.hasinit
  //## begin ZBMailUser::ZBMailUser%copy.initialization preserve=yes
  //## end ZBMailUser::ZBMailUser%copy.initialization
{
  //## begin ZBMailUser::ZBMailUser%copy.body preserve=yes
  	*this = right;
  //## end ZBMailUser::ZBMailUser%copy.body
}

ZBMailUser::ZBMailUser (CString PersonName, ULONG RecipClass)
  //## begin ZBMailUser::ZBMailUser%913452742.hasinit preserve=no
  //## end ZBMailUser::ZBMailUser%913452742.hasinit
  //## begin ZBMailUser::ZBMailUser%913452742.initialization preserve=yes
    : m_PersonName( PersonName ), m_RecipClass( RecipClass )
  //## end ZBMailUser::ZBMailUser%913452742.initialization
{
  //## begin ZBMailUser::ZBMailUser%913452742.body preserve=yes
  //## end ZBMailUser::ZBMailUser%913452742.body
}

ZBMailUser::ZBMailUser (ZUser& PersonName, ULONG RecipClass)
  //## begin ZBMailUser::ZBMailUser%913659111.hasinit preserve=no
  //## end ZBMailUser::ZBMailUser%913659111.hasinit
  //## begin ZBMailUser::ZBMailUser%913659111.initialization preserve=yes
    : m_PersonName( PersonName.GetMailAddress() ), m_RecipClass( RecipClass )
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
ZBMailUser* ZBMailUser::Clone ()
{
  //## begin ZBMailUser::Clone%913452743.body preserve=yes
  	ZBMailUser*	pNewPerson = new ZBMailUser(*this);
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

void ZBMailUser::Serialize (CArchive& ar)
{
  //## begin ZBMailUser::Serialize%928263998.body preserve=yes
	if (ar.IsStoring())
	{	// Write the elements
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
  //## end ZBMailUser::Serialize%928263998.body
}

// Additional Declarations
  //## begin ZBMailUser%36722CE80067.declarations preserve=yes
  //## end ZBMailUser%36722CE80067.declarations

//## begin module%36722E6A030B.epilog preserve=yes
//## end module%36722E6A030B.epilog
