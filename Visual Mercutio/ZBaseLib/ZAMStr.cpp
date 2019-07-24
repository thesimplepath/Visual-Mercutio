//## begin module%38722BAE018E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38722BAE018E.cm

//## begin module%38722BAE018E.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%38722BAE018E.cp

//## Module: ZAMStr%38722BAE018E; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAMStr.cpp

//## begin module%38722BAE018E.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%38722BAE018E.additionalIncludes

//## begin module%38722BAE018E.includes preserve=yes
//## end module%38722BAE018E.includes

// ZAMStr
#include "ZAMStr.h"
//## begin module%38722BAE018E.declarations preserve=no
//## end module%38722BAE018E.declarations

//## begin module%38722BAE018E.additionalDeclarations preserve=yes
#include "ZDDoc.h"
#include "ZIView.h"
#include "MskEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNMaskString, PLFNString, g_DefVersion)
//## end module%38722BAE018E.additionalDeclarations


// Class PLFNMaskString 


PLFNMaskString::PLFNMaskString()
  //## begin PLFNMaskString::PLFNMaskString%.hasinit preserve=no
  //## end PLFNMaskString::PLFNMaskString%.hasinit
  //## begin PLFNMaskString::PLFNMaskString%.initialization preserve=yes
  //## end PLFNMaskString::PLFNMaskString%.initialization
{
  //## begin PLFNMaskString::PLFNMaskString%.body preserve=yes
  //## end PLFNMaskString::PLFNMaskString%.body
}

PLFNMaskString::PLFNMaskString(const PLFNMaskString &right)
  //## begin PLFNMaskString::PLFNMaskString%copy.hasinit preserve=no
  //## end PLFNMaskString::PLFNMaskString%copy.hasinit
  //## begin PLFNMaskString::PLFNMaskString%copy.initialization preserve=yes
  //## end PLFNMaskString::PLFNMaskString%copy.initialization
{
  //## begin PLFNMaskString::PLFNMaskString%copy.body preserve=yes
      *this = right;
  //## end PLFNMaskString::PLFNMaskString%copy.body
}


PLFNMaskString::~PLFNMaskString()
{
  //## begin PLFNMaskString::~PLFNMaskString%.body preserve=yes
  //## end PLFNMaskString::~PLFNMaskString%.body
}


const PLFNMaskString & PLFNMaskString::operator=(const PLFNMaskString &right)
{
  //## begin PLFNMaskString::operator=%.body preserve=yes
    this->PLFNString::operator=( (inherited&)right );
    m_Mask = right.m_Mask;
    return *this;
  //## end PLFNMaskString::operator=%.body
}



//## Other Operations (implementation)
const PLFNMaskString& PLFNMaskString::operator = (const PLFNMaskString* right)
{
  //## begin PLFNMaskString::operator =%947006438.body preserve=yes
    *this = *right;
    return *this;
  //## end PLFNMaskString::operator =%947006438.body
}

void PLFNMaskString::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNMaskString::DrawObject%947006442.body preserve=yes
    DrawFillObject( pDC, pView );
    
    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        // If we are printing and the content is empty 
        // and it is not necessary to print the empty style,
        // just return
        if ( !(pDC->IsPrinting() && PLFNText::IsEmpty() &&
               pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty() == FALSE))
        {
            CFont    *OldFont;
            
            OldFont = pDC->SelectObject( GetFont(pView) );
            pDC->SetBkMode(TRANSPARENT);
            pDC->SetTextColor( GetColor(pView) );  // text color
            // Before displaying the object
            // format it but for string now in this
            // version it is not necessary
            pDC->SetTextAlign( 0 );
            pDC->DrawText( GetFormatedObject(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
            pDC->SelectObject( OldFont );
        }
    }
    PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNMaskString::DrawObject%947006442.body
}

void PLFNMaskString::Serialize (CArchive& ar)
{
  //## begin PLFNMaskString::Serialize%947006443.body preserve=yes
    PLFNString::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_Mask;
    }
    else
    {    // Read the elements
        ar >> m_Mask;
    }
  //## end PLFNMaskString::Serialize%947006443.body
}

PlanFinObject* PLFNMaskString::Clone ()
{
  //## begin PLFNMaskString::Clone%947006444.body preserve=yes
    PLFNMaskString*    pObject = new PLFNMaskString( *this );
    return pObject;
  //## end PLFNMaskString::Clone%947006444.body
}

void PLFNMaskString::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNMaskString::CopyObject%947006445.body preserve=yes
    ((PLFNMaskString*)this)->PLFNMaskString::operator=( (PLFNMaskString*)pSrc );
  //## end PLFNMaskString::CopyObject%947006445.body
}

CString PLFNMaskString::GetFormatedObject ()
{
  //## begin PLFNMaskString::GetFormatedObject%947341238.body preserve=yes
    ZMaskEdit    MaskEdit;
    return MaskEdit.GetFormatedBuffer( m_Mask, m_Str );
  //## end PLFNMaskString::GetFormatedObject%947341238.body
}

// Additional Declarations
  //## begin PLFNMaskString%38722B7803AE.declarations preserve=yes
  //## end PLFNMaskString%38722B7803AE.declarations

//## begin module%38722BAE018E.epilog preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNMaskString diagnostics

#ifdef _DEBUG
void PLFNMaskString::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNMaskString::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG
//## end module%38722BAE018E.epilog
