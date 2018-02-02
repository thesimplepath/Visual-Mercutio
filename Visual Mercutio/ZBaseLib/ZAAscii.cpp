//## begin module%334FC4630321.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%334FC4630321.cm

//## begin module%334FC4630321.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%334FC4630321.cp

//## Module: ZAAscii%334FC4630321; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAAscii.cpp

//## begin module%334FC4630321.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC4630321.additionalIncludes

//## begin module%334FC4630321.includes preserve=yes
//## end module%334FC4630321.includes

// ZAAscii
#include "ZAAscii.h"
//## begin module%334FC4630321.declarations preserve=no
//## end module%334FC4630321.declarations

//## begin module%334FC4630321.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNAscii, PlanFinObject, def_Version)
//## end module%334FC4630321.additionalDeclarations


// Class PLFNAscii 





PLFNAscii::PLFNAscii()
  //## begin PLFNAscii::PLFNAscii%.hasinit preserve=no
      : m_iJustify(NoAlignement), m_IsStriked(FALSE), m_StrikeStyle(NormalStrike), m_KeepHistory(FALSE)
  //## end PLFNAscii::PLFNAscii%.hasinit
  //## begin PLFNAscii::PLFNAscii%.initialization preserve=yes
  //## end PLFNAscii::PLFNAscii%.initialization
{
  //## begin PLFNAscii::PLFNAscii%.body preserve=yes
  //## end PLFNAscii::PLFNAscii%.body
}

PLFNAscii::PLFNAscii(const PLFNAscii &right)
  //## begin PLFNAscii::PLFNAscii%copy.hasinit preserve=no
      : m_iJustify(NoAlignement), m_IsStriked(FALSE), m_StrikeStyle(NormalStrike), m_KeepHistory(FALSE)
  //## end PLFNAscii::PLFNAscii%copy.hasinit
  //## begin PLFNAscii::PLFNAscii%copy.initialization preserve=yes
  //## end PLFNAscii::PLFNAscii%copy.initialization
{
  //## begin PLFNAscii::PLFNAscii%copy.body preserve=yes
  *this = right;
  //## end PLFNAscii::PLFNAscii%copy.body
}


PLFNAscii::~PLFNAscii()
{
  //## begin PLFNAscii::~PLFNAscii%.body preserve=yes
  //## end PLFNAscii::~PLFNAscii%.body
}


const PLFNAscii & PLFNAscii::operator=(const PLFNAscii &right)
{
  //## begin PLFNAscii::operator=%.body preserve=yes
	this->PlanFinObject::operator=( (inherited&)right );
	m_iJustify = right.m_iJustify;
  	m_IsStriked = right.m_IsStriked;
  	m_StrikeStyle = right.m_StrikeStyle;
  	m_KeepHistory = right.m_KeepHistory;
	return *this;
  //## end PLFNAscii::operator=%.body
}



//## Other Operations (implementation)
const PLFNAscii& PLFNAscii::operator = (const PLFNAscii* right)
{
  //## begin PLFNAscii::operator =%829516133.body preserve=yes
	this->PlanFinObject::operator=( (inherited*)right );
	m_iJustify = right->m_iJustify;
  	m_IsStriked = right->m_IsStriked;
  	m_StrikeStyle = right->m_StrikeStyle;
  	m_KeepHistory = right->m_KeepHistory;
	return *this;
  //## end PLFNAscii::operator =%829516133.body
}

void PLFNAscii::Serialize (CArchive& ar)
{
  //## begin PLFNAscii::Serialize%829516183.body preserve=yes
	PlanFinObject::Serialize(ar);
	if (ar.IsStoring())
	{	// Write the elements
		ar << (WORD)m_iJustify;
      	ar << (WORD)m_IsStriked;
      	ar << (WORD)m_StrikeStyle;
      	ar << (WORD)m_KeepHistory;
	}
	else
	{	// Read the elements
		WORD	wTemp;
		if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 0)
		{
			ar >> wTemp;
			m_iJustify = wTemp;
		}
		if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
		{
	      	ar >> wTemp;
	      	m_IsStriked = (BOOL)wTemp;
	      	
	      	ar >> wTemp;
	      	m_StrikeStyle = (StrikeStyles)wTemp;
	    }
	    if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 7)
	    {
	    	ar >> wTemp;
	    	m_KeepHistory = (BOOL)wTemp;
	    }
	}
  //## end PLFNAscii::Serialize%829516183.body
}

UINT PLFNAscii::GetJustify (ZDDocument* pDoc) const
{
  //## begin PLFNAscii::GetJustify%833261594.body preserve=yes
  	if (m_iJustify != NoAlignement)
	  	return m_iJustify;
  	if (pDoc && pDoc->GetStyleManager().GetStyle( GethStyle() ))
  		return pDoc->GetStyleManager().GetStyle( GethStyle() )->GetJustify();
  	return 0;
  //## end PLFNAscii::GetJustify%833261594.body
}

PlanFinObject* PLFNAscii::Clone ()
{
  //## begin PLFNAscii::Clone%849755977.body preserve=yes
	PLFNAscii*	pObject = new PLFNAscii( *this );
	return pObject;
  //## end PLFNAscii::Clone%849755977.body
}

// Additional Declarations
  //## begin PLFNAscii%334FC4610319.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNAscii diagnostics

#ifdef _DEBUG
void PLFNAscii::AssertValid() const
{
	CObject::AssertValid();
}

void PLFNAscii::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNAscii%334FC4610319.declarations
//## begin module%334FC4630321.epilog preserve=yes
//## end module%334FC4630321.epilog
