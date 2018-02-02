//## begin module%33D8FD560348.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33D8FD560348.cm

//## begin module%33D8FD560348.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%33D8FD560348.cp

//## Module: ZAStylMg%33D8FD560348; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAStylMg.cpp

//## begin module%33D8FD560348.additionalIncludes preserve=no
//## end module%33D8FD560348.additionalIncludes

//## begin module%33D8FD560348.includes preserve=yes
#include <StdAfx.h>
//## end module%33D8FD560348.includes

// ZAStylMg
#include "ZAStylMg.h"
//## begin module%33D8FD560348.declarations preserve=no
//## end module%33D8FD560348.declarations

//## begin module%33D8FD560348.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAStyleManager, CObject, def_Version)
//## end module%33D8FD560348.additionalDeclarations


// Class ZAStyleManager 


ZAStyleManager::ZAStyleManager()
  //## begin ZAStyleManager::ZAStyleManager%.hasinit preserve=no
  //## end ZAStyleManager::ZAStyleManager%.hasinit
  //## begin ZAStyleManager::ZAStyleManager%.initialization preserve=yes
  //## end ZAStyleManager::ZAStyleManager%.initialization
{
  //## begin ZAStyleManager::ZAStyleManager%.body preserve=yes
  //## end ZAStyleManager::ZAStyleManager%.body
}

ZAStyleManager::ZAStyleManager(const ZAStyleManager &right)
  //## begin ZAStyleManager::ZAStyleManager%copy.hasinit preserve=no
  //## end ZAStyleManager::ZAStyleManager%copy.hasinit
  //## begin ZAStyleManager::ZAStyleManager%copy.initialization preserve=yes
  //## end ZAStyleManager::ZAStyleManager%copy.initialization
{
  //## begin ZAStyleManager::ZAStyleManager%copy.body preserve=yes
  	*this = right;
  //## end ZAStyleManager::ZAStyleManager%copy.body
}


ZAStyleManager::~ZAStyleManager()
{
	//## begin ZAStyleManager::~ZAStyleManager%.body preserve=yes
	for ( int i = 0; i < m_StyleArray.GetSize(); ++i )
	{
		// Delete valid styles
		if ( m_StyleArray[i] )
		{
			delete ( (ZAStyle*)( m_StyleArray[i] ) );
		}
	}

	m_StyleArray.RemoveAll();
	//## end ZAStyleManager::~ZAStyleManager%.body
}


const ZAStyleManager & ZAStyleManager::operator=(const ZAStyleManager &right)
{
  //## begin ZAStyleManager::operator=%.body preserve=yes
  	if (right.m_StyleArray.GetSize() > 0)
  	{
	  	m_StyleArray.SetSize( right.m_StyleArray.GetSize() );
	  	for (int i = 0; i < right.m_StyleArray.GetSize(); ++i)
	  		if (right.m_StyleArray[i])
		  		m_StyleArray.InsertAt(i, ((ZAStyle*)right.m_StyleArray[i])->Clone());
	}
  	return *this;
  //## end ZAStyleManager::operator=%.body
}



//## Other Operations (implementation)
BOOL ZAStyleManager::RemoveStyle (HandleStyle hStyle)
{
  //## begin ZAStyleManager::RemoveStyle%869857715.body preserve=yes
  	for (int i = 0; i < m_StyleArray.GetSize(); ++i)
  		if ( m_StyleArray[i] && ((ZAStyle*)(m_StyleArray[i]))->GethStyleNumber() == hStyle)
  		{
  			// First free memory pointed at location
	  		delete ((ZAStyle*)(m_StyleArray[i]));
	  		// Second sets the element to NULL from the array
	  		// Do not remove.
  			m_StyleArray.SetAt( i, NULL );	
  			return TRUE;
  		}
  	return FALSE;
  //## end ZAStyleManager::RemoveStyle%869857715.body
}

HandleStyle ZAStyleManager::FindStyle (CString Name)
{
  //## begin ZAStyleManager::FindStyle%869857716.body preserve=yes
  	for (int i = 0; i < m_StyleArray.GetSize(); ++i)
  	{
  		// Check valid styles only and check the name
  		if (m_StyleArray[i] && ((ZAStyle*)(m_StyleArray[i]))->GetStyleName() == Name)
	  		return ((ZAStyle*)(m_StyleArray[i]))->GethStyleNumber();
  	}
  	return NoStyleDefined;
  //## end ZAStyleManager::FindStyle%869857716.body
}

void ZAStyleManager::Serialize (CArchive& ar)
{
  //## begin ZAStyleManager::Serialize%869857718.body preserve=yes
  	m_StyleArray.Serialize( ar );
  //## end ZAStyleManager::Serialize%869857718.body
}

// Additional Declarations
  //## begin ZAStyleManager%33D8FD2D021C.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAStyleManager diagnostics

#ifdef _DEBUG
void ZAStyleManager::AssertValid() const
{
	CObject::AssertValid();
}

void ZAStyleManager::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAStyleManager%33D8FD2D021C.declarations
//## begin module%33D8FD560348.epilog preserve=yes
//## end module%33D8FD560348.epilog
