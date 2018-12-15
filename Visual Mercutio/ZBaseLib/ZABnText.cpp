//## begin module%334FC46302F0.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302F0.cm

//## begin module%334FC46302F0.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302F0.cp

//## Module: ZABnText%334FC46302F0; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZABnText.cpp

//## begin module%334FC46302F0.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302F0.additionalIncludes

//## begin module%334FC46302F0.includes preserve=yes
//## end module%334FC46302F0.includes

// ZABnText
#include "ZABnText.h"
//## begin module%334FC46302F0.declarations preserve=no
//## end module%334FC46302F0.declarations

//## begin module%334FC46302F0.additionalDeclarations preserve=yes
#include "ZIView.h"
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNBoundText, PLFNString, def_Version)
//## end module%334FC46302F0.additionalDeclarations


// Class PLFNBoundText 




PLFNBoundText::PLFNBoundText(const PLFNBoundText &right)
  //## begin PLFNBoundText::PLFNBoundText%copy.hasinit preserve=no
      : m_Hanging(0), m_HangingLines(0), m_InterLine(0)
  //## end PLFNBoundText::PLFNBoundText%copy.hasinit
  //## begin PLFNBoundText::PLFNBoundText%copy.initialization preserve=yes
  //## end PLFNBoundText::PLFNBoundText%copy.initialization
{
  //## begin PLFNBoundText::PLFNBoundText%copy.body preserve=yes
  *this = right;
  //## end PLFNBoundText::PLFNBoundText%copy.body
}

PLFNBoundText::PLFNBoundText (BOOL bStatic)
  //## begin PLFNBoundText::PLFNBoundText%829516132.hasinit preserve=no
      : m_Hanging(0), m_HangingLines(0), m_InterLine(0)
  //## end PLFNBoundText::PLFNBoundText%829516132.hasinit
  //## begin PLFNBoundText::PLFNBoundText%829516132.initialization preserve=yes
  //## end PLFNBoundText::PLFNBoundText%829516132.initialization
{
  //## begin PLFNBoundText::PLFNBoundText%829516132.body preserve=yes
      SetJustify( DT_LEFT | DT_BOTTOM | DT_WORDBREAK );
      SetIsStatic( bStatic );
  //## end PLFNBoundText::PLFNBoundText%829516132.body
}


PLFNBoundText::~PLFNBoundText()
{
  //## begin PLFNBoundText::~PLFNBoundText%.body preserve=yes
  //## end PLFNBoundText::~PLFNBoundText%.body
}


const PLFNBoundText & PLFNBoundText::operator=(const PLFNBoundText &right)
{
  //## begin PLFNBoundText::operator=%.body preserve=yes
    this->PLFNString::operator=( (inherited&)right );
      m_Hanging = right.m_Hanging;
      m_HangingLines = right.m_HangingLines;
      m_InterLine = right.m_InterLine;
    return *this;
  //## end PLFNBoundText::operator=%.body
}



//## Other Operations (implementation)
const PLFNBoundText& PLFNBoundText::operator = (const PLFNBoundText* right)
{
  //## begin PLFNBoundText::operator =%829516133.body preserve=yes
    this->PLFNString::operator=( (inherited*)right );
      m_Hanging = right->m_Hanging;
      m_HangingLines = right->m_HangingLines;
      m_InterLine = right->m_InterLine;
    return *this;
  //## end PLFNBoundText::operator =%829516133.body
}

PlanFinObject* PLFNBoundText::Clone ()
{
  //## begin PLFNBoundText::Clone%849755977.body preserve=yes
    PLFNBoundText*    pObject = new PLFNBoundText( *this );
    return pObject;
  //## end PLFNBoundText::Clone%849755977.body
}

void PLFNBoundText::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNBoundText::CopyObject%863615084.body preserve=yes
    ((PLFNBoundText*)this)->PLFNBoundText::operator=( (PLFNBoundText*)pSrc );
  //## end PLFNBoundText::CopyObject%863615084.body
}

void PLFNBoundText::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNBoundText::DrawObject%882107400.body preserve=yes
    DrawFillObject( pDC, pView );
    
    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        CFont    *OldFont;
        
        OldFont = pDC->SelectObject( GetFont(pView) );
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor( GetColor(pView) );  // text color
        // Before displaying the object
        // format it but for string now in this
        // version it is not necessary
        pDC->SetTextAlign( 0 );

        if (GetHanging())
        {
            CSize    TextSize;
            TextSize = pDC->GetTextExtent( m_Str, m_Str.GetLength() );
            UINT    nTabChar = (UINT)(GetHanging() / (double)((double)TextSize.cx / (double)m_Str.GetLength()));
            
            pDC->DrawText( "\t" + m_Str, -1, &m_rctObject, GetJustify(pView->GetDocument())  & ~DT_SINGLELINE | DT_WORDBREAK | DT_EXPANDTABS | DT_TABSTOP | (nTabChar << 8) );
        }
        else
            pDC->DrawText( m_Str, -1, &m_rctObject, (GetJustify(pView->GetDocument()) & ~DT_SINGLELINE) | DT_WORDBREAK);
        pDC->SelectObject( OldFont );
    }
    PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNBoundText::DrawObject%882107400.body
}

void PLFNBoundText::DrawEmpty (CDC* pDC, ZIView* pView)
{
  //## begin PLFNBoundText::DrawEmpty%882107401.body preserve=yes
    // If we are printing and it is not necessary to print the empty style,
    // just return
    if (pDC->IsPrinting() && 
        pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty() == FALSE)
        return;
    CFont    *OldFont;
    OldFont = pDC->SelectObject( GetFont(pView) );
    // Retreive the text size to be able to
    // draw correct number of lines
    CSize    TextSize;
    TextSize = pDC->GetTextExtent( "A", 1 );
    pDC->SelectObject( OldFont );

    // Draw the doted line without the dotted line style
    // it is bugged when it print
    CPen    pen( PS_SOLID, 1, GetColor( pView ) );
    CPen   *OldPen;
        
    OldPen = pDC->SelectObject( &pen );
    int    iLine = __max( 1, m_rctObject.Height() / (TextSize.cy+2) );
    UINT    nLeftHanging = (UINT)GetHanging(); // / (double)TextSize.cx);
    
    switch (pView->GetDocument()->GetDocOptions().GetEmptyStyle())
    {
        case DottedLine:
        {
            // If hanging, the first line is drawn differently
            register y = 0;
            if (GetHanging())
            {
                // Calculate the start point
                for (int i = m_rctObject.left + nLeftHanging; i < m_rctObject.right; i += 2)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 1, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
                y = 1;
            }
            for ( ; y < iLine; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 2)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 1, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
            break;
        }
        case SmallLine:
        {
            // If hanging, the first line is drawn differently
            register y = 0;
            if (GetHanging())
            {
                // Calculate the start point
                for (int i = m_rctObject.left + nLeftHanging; i < m_rctObject.right; i += 8)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 4, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
                y = 1;
            }
            for ( ; y < iLine; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 8)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 4, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
            break;
        }
        case SolidLine:
        {
            // If hanging, the first line is drawn differently
            register y = 0;
            if (GetHanging())
            {
                // Calculate the start point
                pDC->MoveTo( m_rctObject.left + nLeftHanging, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                pDC->LineTo( m_rctObject.right, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                y = 1;
            }
            for ( ; y < iLine; ++y)
            {
                pDC->MoveTo( m_rctObject.left, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                pDC->LineTo( m_rctObject.right, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
            }
            break;
        }
        case DashLine:
        {
            // If hanging, the first line is drawn differently
            register y = 0;
            if (GetHanging())
            {
                // Calculate the start point
                for (int i = m_rctObject.left + nLeftHanging; i < m_rctObject.right; i += 4)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 2, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
                y = 1;
            }
            for ( ; y < iLine; ++y)
                for (int i = m_rctObject.left; i < m_rctObject.right; i += 4)
                {
                    pDC->MoveTo( i, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                    pDC->LineTo( i + 2, (m_rctObject.top + (y*(TextSize.cy+2)) ) + TextSize.cy );
                }
            break;
        }
        default: break;
    }

    pDC->SelectObject( OldPen );
  //## end PLFNBoundText::DrawEmpty%882107401.body
}

void PLFNBoundText::Serialize (CArchive& ar)
{
  //## begin PLFNBoundText::Serialize%882107402.body preserve=yes
    PLFNString::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
          ar << m_Hanging;
          ar << (WORD)m_HangingLines;
          ar << m_InterLine;
    }
    else
    {    // Read the elements
        if (((ZDDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
              ar >> m_Hanging;
              
            WORD    wTemp;
              ar >> wTemp;
              m_HangingLines = (UINT)wTemp;
              
              ar >> m_InterLine;
              
        }
    }
  //## end PLFNBoundText::Serialize%882107402.body
}

// Additional Declarations
  //## begin PLFNBoundText%334FC461030D.declarations preserve=yes
  //## end PLFNBoundText%334FC461030D.declarations

//## begin module%334FC46302F0.epilog preserve=yes
//## end module%334FC46302F0.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin PLFNBoundText::EditObject%829516176.body preserve=no
    if( ((ZDDocumentReadWrite*)pDoc)->GetEditControl() != NULL )
        delete ((ZDDocumentReadWrite*)pDoc)->GetEditControl();
    
    // If the object is static, no edition
    if (GetIsStatic())
        ((ZDDocumentReadWrite*)pDoc)->AssignEditControl( new CalcEdit );
    else    
        ((ZDDocumentReadWrite*)pDoc)->AssignEditControl( new StrEdit( TRUE ) );
    ((ZDDocumentReadWrite*)pDoc)->GetEditControl()->Create( pParentWnd, pDC, ((ZDDocumentRead*)pDoc), this, 
                                                         ZAApp::ZAGetApp()->GetHistoryFieldValueManager(), ZAApp::ZAGetApp()->GetGlobalFieldManager(),
                                                         ZAApp::ZAGetApp()->IsAutoCalculate(), ZAApp::ZAGetApp()->GoNextEdit() );

    ((ZDDocumentReadWrite*)pDoc)->SetModifiedFlag( TRUE );
//## end PLFNBoundText::EditObject%829516176.body

#endif
