//## begin module%374DA431001C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%374DA431001C.cm

//## begin module%374DA431001C.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%374DA431001C.cp

//## Module: MailMsg%374DA431001C; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\MailMsg.cpp

//## begin module%374DA431001C.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%374DA431001C.additionalIncludes

// MailMsg
#include "MailMsg.h"
//## begin module%374DA431001C.declarations preserve=no
//## end module%374DA431001C.declarations

//## begin module%374DA431001C.additionalDeclarations preserve=yes

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(ZBMailMessage, CObject, def_Version)
//## end module%374DA431001C.additionalDeclarations


// Class ZBMailMessage 





ZBMailMessage::ZBMailMessage (ZUMailUserList* UserList, const CString Subject, const CString Text)
  //## begin ZBMailMessage::ZBMailMessage%927831775.hasinit preserve=no
  //## end ZBMailMessage::ZBMailMessage%927831775.hasinit
  //## begin ZBMailMessage::ZBMailMessage%927831775.initialization preserve=yes
  : m_pMailUserList(UserList), m_Subject(Subject), m_Text(Text), m_pMailFileList(NULL)
  //## end ZBMailMessage::ZBMailMessage%927831775.initialization
{
  //## begin ZBMailMessage::ZBMailMessage%927831775.body preserve=yes
  //## end ZBMailMessage::ZBMailMessage%927831775.body
}


ZBMailMessage::~ZBMailMessage()
{
  //## begin ZBMailMessage::~ZBMailMessage%.body preserve=yes
	if (m_pMailUserList)
		delete m_pMailUserList;
	m_pMailUserList = NULL;
  //## end ZBMailMessage::~ZBMailMessage%.body
}



//## Other Operations (implementation)
void ZBMailMessage::Serialize (CArchive& ar)
{
  //## begin ZBMailMessage::Serialize%928062191.body preserve=yes
	if (ar.IsStoring())
	{	// Write the elements
		ar << m_Subject;
		ar << m_Text;
		ar << m_pMailUserList;
	}
	else
	{
		ar >> m_Subject;
		ar >> m_Text;
		ar >> m_pMailUserList;
	}
  //## end ZBMailMessage::Serialize%928062191.body
}

void ZBMailMessage::FillPerson (CStringArray& PersonList, ULONG RecipClass)
{
  //## begin ZBMailMessage::FillPerson%927831780.body preserve=yes
	if (!m_pMailUserList)
		m_pMailUserList = new ZUMailUserList;
	m_pMailUserList->Fill( PersonList, RecipClass );
  //## end ZBMailMessage::FillPerson%927831780.body
}

void ZBMailMessage::FillPerson (ZUUserManager& PersonList, ULONG RecipClass)
{
  //## begin ZBMailMessage::FillPerson%927831781.body preserve=yes
	if (!m_pMailUserList)
		m_pMailUserList = new ZUMailUserList;
	m_pMailUserList->Fill( PersonList, RecipClass );
  //## end ZBMailMessage::FillPerson%927831781.body
}

void ZBMailMessage::FillPerson (lpMapiRecipDesc* pMapiDesc, ULONG Count)
{
  //## begin ZBMailMessage::FillPerson%927831782.body preserve=yes
	if (!m_pMailUserList)
		m_pMailUserList = new ZUMailUserList;
	m_pMailUserList->Fill( pMapiDesc, Count );
  //## end ZBMailMessage::FillPerson%927831782.body
}

MapiRecipDesc* ZBMailMessage::GetMapiRecipDescPtr ()
{
  //## begin ZBMailMessage::GetMapiRecipDescPtr%927831785.body preserve=yes
	if (m_pMailUserList)
		return m_pMailUserList->GetMapiRecipDescPtr();
	return NULL;
  //## end ZBMailMessage::GetMapiRecipDescPtr%927831785.body
}

// Additional Declarations
  //## begin ZBMailMessage%374D9FC902EB.declarations preserve=yes
  //## end ZBMailMessage%374D9FC902EB.declarations

//## begin module%374DA431001C.epilog preserve=yes
//## end module%374DA431001C.epilog
