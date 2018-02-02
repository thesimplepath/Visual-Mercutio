//## begin module%33747B820334.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33747B820334.cm

//## begin module%33747B820334.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%33747B820334.cp

//## Module: ZAGraphc%33747B820334; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZAGraphc.cpp

//## begin module%33747B820334.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%33747B820334.additionalIncludes

//## begin module%33747B820334.includes preserve=yes
//## end module%33747B820334.includes

// ZAGraphc
#include "ZAGraphc.h"
//## begin module%33747B820334.declarations preserve=no
//## end module%33747B820334.declarations

//## begin module%33747B820334.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNGraphic, PlanFinObject, def_Version)
//## end module%33747B820334.additionalDeclarations


// Class PLFNGraphic 





PLFNGraphic::PLFNGraphic()
  //## begin PLFNGraphic::PLFNGraphic%.hasinit preserve=no
      : m_GraphicColor(defCOLOR_BLACK), m_GraphicWidth(1), m_bShadow(FALSE), m_GraphicStyle(PS_SOLID)
  //## end PLFNGraphic::PLFNGraphic%.hasinit
  //## begin PLFNGraphic::PLFNGraphic%.initialization preserve=yes
  //## end PLFNGraphic::PLFNGraphic%.initialization
{
  //## begin PLFNGraphic::PLFNGraphic%.body preserve=yes
  //## end PLFNGraphic::PLFNGraphic%.body
}

PLFNGraphic::PLFNGraphic(const PLFNGraphic &right)
  //## begin PLFNGraphic::PLFNGraphic%copy.hasinit preserve=no
      : m_GraphicColor(defCOLOR_BLACK), m_GraphicWidth(1), m_bShadow(FALSE), m_GraphicStyle(PS_SOLID)
  //## end PLFNGraphic::PLFNGraphic%copy.hasinit
  //## begin PLFNGraphic::PLFNGraphic%copy.initialization preserve=yes
  //## end PLFNGraphic::PLFNGraphic%copy.initialization
{
  //## begin PLFNGraphic::PLFNGraphic%copy.body preserve=yes
  *this = right;
  //## end PLFNGraphic::PLFNGraphic%copy.body
}


PLFNGraphic::~PLFNGraphic()
{
  //## begin PLFNGraphic::~PLFNGraphic%.body preserve=yes
  //## end PLFNGraphic::~PLFNGraphic%.body
}


const PLFNGraphic & PLFNGraphic::operator=(const PLFNGraphic &right)
{
  //## begin PLFNGraphic::operator=%.body preserve=yes
	this->PlanFinObject::operator=( (inherited&)right );
	m_GraphicColor = right.m_GraphicColor;
	m_GraphicWidth = right.m_GraphicWidth;
	m_bShadow = right.m_bShadow;
	m_GraphicStyle = right.m_GraphicStyle;
	return *this;
  //## end PLFNGraphic::operator=%.body
}



//## Other Operations (implementation)
const PLFNGraphic& PLFNGraphic::operator = (const PLFNGraphic* right)
{
  //## begin PLFNGraphic::operator =%863265788.body preserve=yes
	this->PlanFinObject::operator=( (inherited*)right );
	m_GraphicColor = right->m_GraphicColor;
	m_GraphicWidth = right->m_GraphicWidth;
	m_bShadow = right->m_bShadow;
	m_GraphicStyle = right->m_GraphicStyle;
	return *this;
  //## end PLFNGraphic::operator =%863265788.body
}

void PLFNGraphic::Serialize (CArchive& ar)
{
  //## begin PLFNGraphic::Serialize%863265789.body preserve=yes
	PlanFinObject::Serialize(ar);
	if (ar.IsStoring())
	{	// Write the elements
	    ar << m_GraphicColor;
	    ar << (WORD)m_GraphicWidth;
		ar << (WORD)m_bShadow;
		ar << (WORD)m_GraphicStyle;
	}
	else
	{	// Read the elements
	    ar >> m_GraphicColor;
		WORD	wValue;
		ar >> wValue;
	    m_GraphicWidth = wValue;
		ar >> wValue;
		m_bShadow = wValue;
		ar >> wValue;
		m_GraphicStyle = wValue;
		// Rebuild graphic tools
	}
  //## end PLFNGraphic::Serialize%863265789.body
}

PlanFinObject* PLFNGraphic::Clone ()
{
  //## begin PLFNGraphic::Clone%863265790.body preserve=yes
	PLFNGraphic*	pObject = new PLFNGraphic( *this );
	return pObject;
  //## end PLFNGraphic::Clone%863265790.body
}

CPen& PLFNGraphic::GetGraphicPen (CPen& pen)
{
  //## begin PLFNGraphic::GetGraphicPen%863265791.body preserve=yes
  	if (pen.GetSafeHandle() != NULL)
		pen.Detach();  	
    pen.CreatePen( m_GraphicStyle, m_GraphicWidth, m_GraphicColor );
    return pen;
  //## end PLFNGraphic::GetGraphicPen%863265791.body
}

CBrush& PLFNGraphic::GetGraphicBrush (CBrush& brush)
{
  //## begin PLFNGraphic::GetGraphicBrush%863265792.body preserve=yes
  	if (brush.GetSafeHandle() != NULL)
		brush.Detach();  	
    brush.CreateSolidBrush( m_GraphicColor );
    return brush;
  //## end PLFNGraphic::GetGraphicBrush%863265792.body
}

void PLFNGraphic::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNGraphic::CopyObject%863615077.body preserve=yes
	((PLFNGraphic*)this)->PLFNGraphic::operator=( (PLFNGraphic*)pSrc );
  //## end PLFNGraphic::CopyObject%863615077.body
}

// Additional Declarations
  //## begin PLFNGraphic%33747B5B0226.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNGraphic diagnostics

#ifdef _DEBUG
void PLFNGraphic::AssertValid() const
{
	CObject::AssertValid();
}

void PLFNGraphic::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNGraphic%33747B5B0226.declarations
//## begin module%33747B820334.epilog preserve=yes
//## end module%33747B820334.epilog
