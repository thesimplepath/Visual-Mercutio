//## begin module%33798B7D02A8.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33798B7D02A8.cm

//## begin module%33798B7D02A8.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%33798B7D02A8.cp

//## Module: ZANumbrd%33798B7D02A8; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZANumbrd.cpp

//## begin module%33798B7D02A8.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%33798B7D02A8.additionalIncludes

//## begin module%33798B7D02A8.includes preserve=yes
//## end module%33798B7D02A8.includes

// ZANumbrd
#include "ZANumbrd.h"
//## begin module%33798B7D02A8.declarations preserve=no
//## end module%33798B7D02A8.declarations

//## begin module%33798B7D02A8.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNAutoNumbered, PlanFinObject, g_DefVersion)




//## end module%33798B7D02A8.additionalDeclarations


// Class PLFNAutoNumbered 







PLFNAutoNumbered::PLFNAutoNumbered()
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%.hasinit preserve=no
      : m_pObject(NULL), m_iTextOffset(20), m_bAutoCalculate(TRUE), m_iLevel(0)
  //## end PLFNAutoNumbered::PLFNAutoNumbered%.hasinit
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%.initialization preserve=yes
  , m_iSectionNumber( 0 )
  //## end PLFNAutoNumbered::PLFNAutoNumbered%.initialization
{
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%.body preserve=yes
  //## end PLFNAutoNumbered::PLFNAutoNumbered%.body
}

PLFNAutoNumbered::PLFNAutoNumbered(const PLFNAutoNumbered &right)
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%copy.hasinit preserve=no
      : m_pObject(NULL), m_iTextOffset(20), m_bAutoCalculate(TRUE), m_iLevel(0)
  //## end PLFNAutoNumbered::PLFNAutoNumbered%copy.hasinit
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%copy.initialization preserve=yes
  //## end PLFNAutoNumbered::PLFNAutoNumbered%copy.initialization
{
  //## begin PLFNAutoNumbered::PLFNAutoNumbered%copy.body preserve=yes
  *this = right;
  //## end PLFNAutoNumbered::PLFNAutoNumbered%copy.body
}


PLFNAutoNumbered::~PLFNAutoNumbered()
{
  //## begin PLFNAutoNumbered::~PLFNAutoNumbered%.body preserve=yes
      if (m_pObject)
          delete m_pObject;
  //## end PLFNAutoNumbered::~PLFNAutoNumbered%.body
}


const PLFNAutoNumbered & PLFNAutoNumbered::operator=(const PLFNAutoNumbered &right)
{
  //## begin PLFNAutoNumbered::operator=%.body preserve=yes
    this->PlanFinObject::operator=( (inherited&)right );
    m_TextLevel = right.m_TextLevel;
    m_pObject = right.m_pObject->Clone();
    m_iTextOffset = right.m_iTextOffset;
    m_bAutoCalculate = right.m_bAutoCalculate;
    m_iSectionNumber = right.m_iSectionNumber;
    m_iLevel = right.m_iLevel;
    return *this;
  //## end PLFNAutoNumbered::operator=%.body
}



//## Other Operations (implementation)
const PLFNAutoNumbered& PLFNAutoNumbered::operator = (const PLFNAutoNumbered* right)
{
  //## begin PLFNAutoNumbered::operator =%863604533.body preserve=yes
    this->PlanFinObject::operator=( (inherited*)right );
    m_TextLevel = right->m_TextLevel;
    m_pObject = right->m_pObject->Clone();
    m_iTextOffset = right->m_iTextOffset;
    m_bAutoCalculate = right->m_bAutoCalculate;
    m_iSectionNumber = right->m_iSectionNumber;
    m_iLevel = right->m_iLevel;
    return *this;
  //## end PLFNAutoNumbered::operator =%863604533.body
}

CString PLFNAutoNumbered::GetFormattedObject ()
{
  //## begin PLFNAutoNumbered::GetFormattedObject%863604535.body preserve=yes
      if (m_pObject)
          return m_pObject->GetFormattedObject();
    return "";
  //## end PLFNAutoNumbered::GetFormattedObject%863604535.body
}

BOOL PLFNAutoNumbered::ConvertFormattedObject (const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero)
{
  //## begin PLFNAutoNumbered::ConvertFormattedObject%863604536.body preserve=yes
      if (m_pObject)
          return m_pObject->ConvertFormattedObject( sValue, bLocateFormat, EmptyWhenZero );
    // Hasn't changed
    return FALSE;
  //## end PLFNAutoNumbered::ConvertFormattedObject%863604536.body
}

void PLFNAutoNumbered::Serialize (CArchive& ar)
{
  //## begin PLFNAutoNumbered::Serialize%863604538.body preserve=yes
    PlanFinObject::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << (WORD)m_iTextOffset;
        ar << (WORD)m_bAutoCalculate;
        ar << (WORD)m_iSectionNumber;
        ar << (WORD)m_iLevel;
        // Serialize the oject defined
        ar << m_pObject;
    }
    else
    {    // Read the elements
        WORD    wTemp;
        ar >> wTemp;
        m_iTextOffset = wTemp;
        ar >> wTemp;
        m_bAutoCalculate = wTemp;
        ar >> wTemp;
        m_iSectionNumber = wTemp;
        ar >> wTemp;
        m_iLevel = wTemp;
        // Serialize the oject defined
        ar >> m_pObject;
    }
    // Must serialize the Static member
    // Serialize the Text Level
    m_TextLevel.Serialize( ar );
  //## end PLFNAutoNumbered::Serialize%863604538.body
}

PlanFinObject* PLFNAutoNumbered::Clone ()
{
  //## begin PLFNAutoNumbered::Clone%863604539.body preserve=yes
    PLFNAutoNumbered*    pObject = new PLFNAutoNumbered( *this );
    return pObject;
  //## end PLFNAutoNumbered::Clone%863604539.body
}

void PLFNAutoNumbered::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNAutoNumbered::CopyObject%863615080.body preserve=yes
    ((PLFNAutoNumbered*)this)->PLFNAutoNumbered::operator=( (PLFNAutoNumbered*)pSrc );
  //## end PLFNAutoNumbered::CopyObject%863615080.body
}

void PLFNAutoNumbered::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNAutoNumbered::DrawObject%863615085.body preserve=yes
    DrawFillObject( pDC, pView );
    m_TextLevel.DrawObject( pDC, pView );
    // Must draw the object
      if (m_pObject)
        m_pObject->DrawObject( pDC, pView );
    PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNAutoNumbered::DrawObject%863615085.body
}

void PLFNAutoNumbered::SizePositionHasChanged ()
{
  //## begin PLFNAutoNumbered::SizePositionHasChanged%863883949.body preserve=yes
    if (!m_pObject)
        return;
      // Call the basic fonction
    PlanFinObject::SizePositionHasChanged();
      // Recalculate all element positions.
      GetTextLevel().SetClientRect( m_rctObject );
      m_pObject->SetClientRect( m_rctObject );
      m_pObject->GetClientRect().left += GetiTextOffset();
      // If automatic recalculation of section
      if (GetbAutoCalculate())
        AfxGetMainWnd( )->SendMessageToDescendants( UM_REBUILDAUTOMATICNUMBER );
  //## end PLFNAutoNumbered::SizePositionHasChanged%863883949.body
}

CString PLFNAutoNumbered::GetUnformattedObject ()
{
  //## begin PLFNAutoNumbered::GetUnformattedObject%901298462.body preserve=yes
      if (m_pObject)
          return m_pObject->GetUnformattedObject();
    return "";
  //## end PLFNAutoNumbered::GetUnformattedObject%901298462.body
}

void PLFNAutoNumbered::SethStyle (HandleStyle value)
{
  //## begin PLFNAutoNumbered::SethStyle%907428568.body preserve=yes
      if (m_pObject)
          m_pObject->SethStyle( value );
  //## end PLFNAutoNumbered::SethStyle%907428568.body
}

// Additional Declarations
  //## begin PLFNAutoNumbered%33798B3703D4.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNAutoNumbered diagnostics

#ifdef _DEBUG
void PLFNAutoNumbered::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNAutoNumbered::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG



const COLORREF PLFNAutoNumbered::GetFillColor () const
{
      if (m_pObject)
          return m_pObject->GetFillColor();
    return 0;
}

void PLFNAutoNumbered::SetFillColor (COLORREF value)
{
      if (m_pObject)
          m_pObject->SetFillColor( value );
}



  //## end PLFNAutoNumbered%33798B3703D4.declarations
//## begin module%33798B7D02A8.epilog preserve=yes
//## end module%33798B7D02A8.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin PLFNAutoNumbered::EditObject%863615086.body preserve=no
      if (m_pObject)
        m_pObject->EditObject( pParentWnd, pDC, pDoc);
//## end PLFNAutoNumbered::EditObject%863615086.body

#endif
