//## begin module%3705B620027B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3705B620027B.cm

//## begin module%3705B620027B.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%3705B620027B.cp

//## Module: BPropSht%3705B620027B; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\BPropSht.cpp

//## begin module%3705B620027B.additionalIncludes preserve=no
//## end module%3705B620027B.additionalIncludes

//## begin module%3705B620027B.includes preserve=yes
#include <StdAfx.h>
//## end module%3705B620027B.includes

// BPropSht
#include "BPropSht.h"
//## begin module%3705B620027B.declarations preserve=no
//## end module%3705B620027B.declarations

//## begin module%3705B620027B.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZIBasePropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(ZIBasePropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(ZIBasePropSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%3705B620027B.additionalDeclarations


// Class ZIBasePropSheet 


ZIBasePropSheet::ZIBasePropSheet (int DefaultTab)
  //## begin ZIBasePropSheet::ZIBasePropSheet%923121219.hasinit preserve=no
  //## end ZIBasePropSheet::ZIBasePropSheet%923121219.hasinit
  //## begin ZIBasePropSheet::ZIBasePropSheet%923121219.initialization preserve=yes
  : CPropertySheet("", NULL, DefaultTab)
  //## end ZIBasePropSheet::ZIBasePropSheet%923121219.initialization
{
  //## begin ZIBasePropSheet::ZIBasePropSheet%923121219.body preserve=yes
  //## end ZIBasePropSheet::ZIBasePropSheet%923121219.body
}

ZIBasePropSheet::ZIBasePropSheet (UINT nIDCaption, int DefaultTab)
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598941.hasinit preserve=no
  //## end ZIBasePropSheet::ZIBasePropSheet%923598941.hasinit
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598941.initialization preserve=yes
  : CPropertySheet(nIDCaption, NULL, DefaultTab)
  //## end ZIBasePropSheet::ZIBasePropSheet%923598941.initialization
{
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598941.body preserve=yes
  //## end ZIBasePropSheet::ZIBasePropSheet%923598941.body
}

ZIBasePropSheet::ZIBasePropSheet (LPCTSTR pszCaption, int DefaultTab)
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598942.hasinit preserve=no
  //## end ZIBasePropSheet::ZIBasePropSheet%923598942.hasinit
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598942.initialization preserve=yes
  : CPropertySheet(pszCaption, NULL, DefaultTab)
  //## end ZIBasePropSheet::ZIBasePropSheet%923598942.initialization
{
  //## begin ZIBasePropSheet::ZIBasePropSheet%923598942.body preserve=yes
  //## end ZIBasePropSheet::ZIBasePropSheet%923598942.body
}


ZIBasePropSheet::~ZIBasePropSheet()
{
  //## begin ZIBasePropSheet::~ZIBasePropSheet%.body preserve=yes
	DeleteAllPropertyPages();
  //## end ZIBasePropSheet::~ZIBasePropSheet%.body
}



//## Other Operations (implementation)
int ZIBasePropSheet::GetCurPage () const
{
  //## begin ZIBasePropSheet::GetCurPage%923121220.body preserve=yes
#ifndef _WIN32
	return m_nCurPage;
#else
	return GetActiveIndex();
#endif
  //## end ZIBasePropSheet::GetCurPage%923121220.body
}

// Additional Declarations
  //## begin ZIBasePropSheet%3705B57B035A.declarations preserve=yes
  //## end ZIBasePropSheet%3705B57B035A.declarations

//## begin module%3705B620027B.epilog preserve=yes
int  ZIBasePropSheet::FindPropertyPage( CPropertyPage* pPage )
{
  	for (int i = 0; i < m_PageArray.GetSize(); ++i)
	{
		if ( pPage == m_PageArray[i])
			return i;
	}
	return -1;
}

bool ZIBasePropSheet::DeletePropertyPage( CPropertyPage* pPage )
{
	int  Index = FindPropertyPage( pPage );
	if (Index != -1)
		return DeletePropertyPageAt( Index );
	return false;
}

bool ZIBasePropSheet::DeletePropertyPageAt( size_t Index )
{
  	if (Index < (size_t)m_PageArray.GetSize())
	{
  		delete ((ZIGenericPropPage*)(m_PageArray[Index]));
		m_PageArray.RemoveAt( Index );
		RemovePage( Index );
		return true;
	}
	return false;
}


void ZIBasePropSheet::DeleteAllPropertyPages()
{
	// Free the pages allocated on the fly by the ZINewForm class
  	for (int i = 0; i < m_PageArray.GetSize(); ++i)
	{
  		delete ((ZIGenericPropPage*)(m_PageArray[i]));
		RemovePage( 0 );
	}
	m_PageArray.RemoveAll();
}

//## end module%3705B620027B.epilog
