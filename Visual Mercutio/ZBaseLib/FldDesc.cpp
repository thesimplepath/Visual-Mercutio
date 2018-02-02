//## begin module%363DC9BE02EA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363DC9BE02EA.cm

//## begin module%363DC9BE02EA.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%363DC9BE02EA.cp

//## Module: FldDesc%363DC9BE02EA; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldDesc.cpp

//## begin module%363DC9BE02EA.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%363DC9BE02EA.additionalIncludes

//## begin module%363DC9BE02EA.includes preserve=yes
//## end module%363DC9BE02EA.includes

// FldDesc
#include "FldDesc.h"
//## begin module%363DC9BE02EA.declarations preserve=no
//## end module%363DC9BE02EA.declarations

//## begin module%363DC9BE02EA.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAObjectDefinition, CObject, def_Version)
//## end module%363DC9BE02EA.additionalDeclarations


// Class ZAObjectDefinition 






ZAObjectDefinition::ZAObjectDefinition()
  //## begin ZAObjectDefinition::ZAObjectDefinition%.hasinit preserve=no
      : m_pObject(NULL)
  //## end ZAObjectDefinition::ZAObjectDefinition%.hasinit
  //## begin ZAObjectDefinition::ZAObjectDefinition%.initialization preserve=yes
  , m_Sorted(FALSE) 
  //## end ZAObjectDefinition::ZAObjectDefinition%.initialization
{
  //## begin ZAObjectDefinition::ZAObjectDefinition%.body preserve=yes
  //## end ZAObjectDefinition::ZAObjectDefinition%.body
}

ZAObjectDefinition::ZAObjectDefinition(const ZAObjectDefinition &right)
  //## begin ZAObjectDefinition::ZAObjectDefinition%copy.hasinit preserve=no
      : m_pObject(NULL)
  //## end ZAObjectDefinition::ZAObjectDefinition%copy.hasinit
  //## begin ZAObjectDefinition::ZAObjectDefinition%copy.initialization preserve=yes
  //## end ZAObjectDefinition::ZAObjectDefinition%copy.initialization
{
  //## begin ZAObjectDefinition::ZAObjectDefinition%copy.body preserve=yes
	*this = right;
  //## end ZAObjectDefinition::ZAObjectDefinition%copy.body
}


ZAObjectDefinition::~ZAObjectDefinition()
{
  //## begin ZAObjectDefinition::~ZAObjectDefinition%.body preserve=yes
  	if (m_pObject)
  		delete m_pObject;
  //## end ZAObjectDefinition::~ZAObjectDefinition%.body
}


const ZAObjectDefinition & ZAObjectDefinition::operator=(const ZAObjectDefinition &right)
{
  //## begin ZAObjectDefinition::operator=%.body preserve=yes
	m_FieldName = right.m_FieldName;
	m_Description = right.m_Description;
	m_ClassName = right.m_ClassName;
	m_HelpUserDescription = right.m_HelpUserDescription;
	m_Sorted = right.m_Sorted;
	if (right.m_pObject)
		m_pObject = right.m_pObject->Clone();
	else
		m_pObject = NULL;
	return *this;
  //## end ZAObjectDefinition::operator=%.body
}



//## Other Operations (implementation)
void ZAObjectDefinition::Serialize (CArchive& ar)
{
  //## begin ZAObjectDefinition::Serialize%910019970.body preserve=yes
	if (ar.IsStoring())
	{	// Write the elements
		ar << m_FieldName;
      	ar << m_Description;
      	ar << m_ClassName;
      	ar << m_HelpUserDescription;
		ar << (WORD)m_Sorted;
      	ar << m_pObject;
	}
	else
	{	// Read the elements
		ar >> m_FieldName;
		ar >> m_Description;
      	ar >> m_ClassName;
      	ar >> m_HelpUserDescription;
		WORD	wValue;
		ar >> wValue;
		m_Sorted = (BOOL)wValue;
      	ar >> (CObject*&)m_pObject;
	}
  //## end ZAObjectDefinition::Serialize%910019970.body
}

ZAObjectDefinition* ZAObjectDefinition::Clone ()
{
  //## begin ZAObjectDefinition::Clone%939069933.body preserve=yes
	ZAObjectDefinition*	pObject = new ZAObjectDefinition( *this );
	return pObject;
  //## end ZAObjectDefinition::Clone%939069933.body
}

// Additional Declarations
  //## begin ZAObjectDefinition%363DC8FB02A3.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAObjectDefinition diagnostics

#ifdef _DEBUG
void ZAObjectDefinition::AssertValid() const
{
	CObject::AssertValid();
}

void ZAObjectDefinition::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAObjectDefinition%363DC8FB02A3.declarations
//## begin module%363DC9BE02EA.epilog preserve=yes
//## end module%363DC9BE02EA.epilog
