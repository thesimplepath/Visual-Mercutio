//## begin module%3881855902BB.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3881855902BB.cm

//## begin module%3881855902BB.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3881855902BB.cp

//## Module: ZAMultiC%3881855902BB; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAMultiC.cpp

//## begin module%3881855902BB.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3881855902BB.additionalIncludes

//## begin module%3881855902BB.includes preserve=yes
//## end module%3881855902BB.includes

// ZAMultiC
#include "ZAMultiC.h"
//## begin module%3881855902BB.declarations preserve=no
//## end module%3881855902BB.declarations

//## begin module%3881855902BB.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNMultiColumn, PlanFinObject, g_DefVersion)
//## end module%3881855902BB.additionalDeclarations


// Class PLFNMultiColumn 



PLFNMultiColumn::PLFNMultiColumn()
  //## begin PLFNMultiColumn::PLFNMultiColumn%.hasinit preserve=no
  //## end PLFNMultiColumn::PLFNMultiColumn%.hasinit
  //## begin PLFNMultiColumn::PLFNMultiColumn%.initialization preserve=yes
  : m_ShowHeader(TRUE)
  //## end PLFNMultiColumn::PLFNMultiColumn%.initialization
{
  //## begin PLFNMultiColumn::PLFNMultiColumn%.body preserve=yes
    // By default, the multi-column field is not visible
    SetbIsVisible( FALSE );
  //## end PLFNMultiColumn::PLFNMultiColumn%.body
}

PLFNMultiColumn::PLFNMultiColumn(const PLFNMultiColumn &right)
  //## begin PLFNMultiColumn::PLFNMultiColumn%copy.hasinit preserve=no
  //## end PLFNMultiColumn::PLFNMultiColumn%copy.hasinit
  //## begin PLFNMultiColumn::PLFNMultiColumn%copy.initialization preserve=yes
  //## end PLFNMultiColumn::PLFNMultiColumn%copy.initialization
{
  //## begin PLFNMultiColumn::PLFNMultiColumn%copy.body preserve=yes
  *this = right;
  //## end PLFNMultiColumn::PLFNMultiColumn%copy.body
}


PLFNMultiColumn::~PLFNMultiColumn()
{
  //## begin PLFNMultiColumn::~PLFNMultiColumn%.body preserve=yes
  //## end PLFNMultiColumn::~PLFNMultiColumn%.body
}


const PLFNMultiColumn & PLFNMultiColumn::operator=(const PLFNMultiColumn &right)
{
  //## begin PLFNMultiColumn::operator=%.body preserve=yes
    this->PlanFinObject::operator=( (inherited&)right );
    m_MultiColumnManager = right.m_MultiColumnManager;
    m_ShowHeader = right.m_ShowHeader;
    return *this;
  //## end PLFNMultiColumn::operator=%.body
}



//## Other Operations (implementation)
const PLFNMultiColumn& PLFNMultiColumn::operator = (const PLFNMultiColumn* right)
{
  //## begin PLFNMultiColumn::operator =%948017479.body preserve=yes
    *this = *right;
    return *this;
  //## end PLFNMultiColumn::operator =%948017479.body
}

void PLFNMultiColumn::Serialize (CArchive& ar)
{
  //## begin PLFNMultiColumn::Serialize%948017480.body preserve=yes
    PlanFinObject::Serialize(ar);
    m_MultiColumnManager.Serialize( ar );
    if (ar.IsStoring())
    {    // Write the elements
        ar << (WORD)m_ShowHeader;
    }
    else
    {    // Read the elements
        WORD    wValue;
        ar >> wValue;
        m_ShowHeader = (BOOL)m_ShowHeader;
    }
  //## end PLFNMultiColumn::Serialize%948017480.body
}

PlanFinObject* PLFNMultiColumn::Clone ()
{
  //## begin PLFNMultiColumn::Clone%948017481.body preserve=yes
    PLFNMultiColumn*    pObject = new PLFNMultiColumn( *this );
    return pObject;
  //## end PLFNMultiColumn::Clone%948017481.body
}

void PLFNMultiColumn::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNMultiColumn::CopyObject%948017482.body preserve=yes
    ((PLFNMultiColumn*)this)->PLFNMultiColumn::operator=( (PLFNMultiColumn*)pSrc );
  //## end PLFNMultiColumn::CopyObject%948017482.body
}

void PLFNMultiColumn::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNMultiColumn::DrawObject%948017512.body preserve=yes
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor( GetColor(pView) );  // text color
    // Before displaying the object
    // format it but for string now in this
    // version it is not necessary
    pDC->SetTextAlign( 0 );
//        pDC->DrawText( GetFormatedObject(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
    pDC->SelectObject( OldFont );
    // Base class drawobject
    PlanFinObject::DrawObject( pDC, pView );
    PlanFinObject::DrawObjectRectangle( pDC );
  //## end PLFNMultiColumn::DrawObject%948017512.body
}

// Additional Declarations
  //## begin PLFNMultiColumn%388185310245.declarations preserve=yes
  //## end PLFNMultiColumn%388185310245.declarations

//## begin module%3881855902BB.epilog preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNMultiColumn diagnostics

#ifdef _DEBUG
void PLFNMultiColumn::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNMultiColumn::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

//## end module%3881855902BB.epilog
