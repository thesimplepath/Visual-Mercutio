//## begin module%334FC46302F3.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302F3.cm

//## begin module%334FC46302F3.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302F3.cp

//## Module: ZAString%334FC46302F3; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAString.cpp

//## begin module%334FC46302F3.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302F3.additionalIncludes

//## begin module%334FC46302F3.includes preserve=yes
//## end module%334FC46302F3.includes

// ZAString
#include "ZAString.h"
//## begin module%334FC46302F3.declarations preserve=no
//## end module%334FC46302F3.declarations

//## begin module%334FC46302F3.additionalDeclarations preserve=yes
#include "ZDDoc.h"
#include "ZIView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNString, PLFNText, def_Version)
//## end module%334FC46302F3.additionalDeclarations


// Class PLFNString 

PLFNString::PLFNString()
  //## begin PLFNString::PLFNString%.hasinit preserve=no
  //## end PLFNString::PLFNString%.hasinit
  //## begin PLFNString::PLFNString%.initialization preserve=yes
  //## end PLFNString::PLFNString%.initialization
{
  //## begin PLFNString::PLFNString%.body preserve=yes
  //## end PLFNString::PLFNString%.body
}

PLFNString::PLFNString(const PLFNString &right)
  //## begin PLFNString::PLFNString%copy.hasinit preserve=no
  //## end PLFNString::PLFNString%copy.hasinit
  //## begin PLFNString::PLFNString%copy.initialization preserve=yes
  //## end PLFNString::PLFNString%copy.initialization
{
  //## begin PLFNString::PLFNString%copy.body preserve=yes
      *this = right;
  //## end PLFNString::PLFNString%copy.body
}


PLFNString::~PLFNString()
{
  //## begin PLFNString::~PLFNString%.body preserve=yes
  //## end PLFNString::~PLFNString%.body
}


const PLFNString & PLFNString::operator=(const PLFNString &right)
{
  //## begin PLFNString::operator=%.body preserve=yes
    this->PLFNText::operator=( (inherited&)right );
    return *this;
  //## end PLFNString::operator=%.body
}



//## Other Operations (implementation)
const PLFNString& PLFNString::operator = (const PLFNString* right)
{
  //## begin PLFNString::operator =%829516133.body preserve=yes
    this->PLFNText::operator=( (inherited*)right );
    return *this;
  //## end PLFNString::operator =%829516133.body
}

void PLFNString::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNString::DrawObject%829516173.body preserve=yes
    DrawFillObject( pDC, pView );
    
    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        CFont    *OldFont;
        
        OldFont = pDC->SelectObject( GetFont(pView) );
        pDC->SetBkMode(TRANSPARENT);
/*        
        if (GetColor() == -1)
            pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
        else
            pDC->SetTextColor( GetColor() );  // text color
*/            
        pDC->SetTextColor( GetColor(pView) );  // text color
        // Before displaying the object
        // format it but for string now in this
        // version it is not necessary
//        FormatObject( m_Str );
//        pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
//        pDC->TextOut( m_rctObject.left, m_rctObject.bottom, m_Str );
        pDC->SetTextAlign( 0 );
        pDC->DrawText( m_Str, -1, &m_rctObject, GetJustify(pView->GetDocument()) );
        pDC->SelectObject( OldFont );
    }
    PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNString::DrawObject%829516173.body
}

void PLFNString::Serialize (CArchive& ar)
{
  //## begin PLFNString::Serialize%829516183.body preserve=yes
    PLFNText::Serialize(ar);
  //## end PLFNString::Serialize%829516183.body
}

PlanFinObject* PLFNString::Clone ()
{
  //## begin PLFNString::Clone%849755977.body preserve=yes
    PLFNString*    pObject = new PLFNString( *this );
    return pObject;
  //## end PLFNString::Clone%849755977.body
}

void PLFNString::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNString::CopyObject%863615083.body preserve=yes
    ((PLFNString*)this)->PLFNString::operator=( (PLFNString*)pSrc );
  //## end PLFNString::CopyObject%863615083.body
}

// Additional Declarations
  //## begin PLFNString%334FC46102D5.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNString diagnostics

#ifdef _DEBUG
void PLFNString::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNString::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNString%334FC46102D5.declarations
//## begin module%334FC46302F3.epilog preserve=yes
//## end module%334FC46302F3.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin PLFNString::EditObject%829516176.body preserve=no
    if( ((ZDDocumentReadWrite*)pDoc)->GetEditControl() != NULL )
        delete ((ZDDocumentReadWrite*)pDoc)->GetEditControl();
        
    // If history must be kept.
    if (GetKeepHistory())
        ((ZDDocumentReadWrite*)pDoc)->AssignEditControl( new StrEditHistoric );
    else
        ((ZDDocumentReadWrite*)pDoc)->AssignEditControl( new StrEdit );
    ((ZDDocumentReadWrite*)pDoc)->GetEditControl()->Create( pParentWnd, pDC, ((ZDDocumentRead*)pDoc), this, 
                                                         ZAApp::ZAGetApp()->GetHistoryFieldValueManager(), ZAApp::ZAGetApp()->GetGlobalFieldManager(), 
                                                         ZAApp::ZAGetApp()->IsAutoCalculate(), ZAApp::ZAGetApp()->GoNextEdit() );

    ((ZDDocumentReadWrite*)pDoc)->SetModifiedFlag( TRUE );
//## end PLFNString::EditObject%829516176.body

#endif
