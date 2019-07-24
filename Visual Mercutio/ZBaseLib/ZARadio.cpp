//## begin module%336D05DA006E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%336D05DA006E.cm

//## begin module%336D05DA006E.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%336D05DA006E.cp

//## Module: ZARadio%336D05DA006E; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZARadio.cpp

//## begin module%336D05DA006E.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%336D05DA006E.additionalIncludes

//## begin module%336D05DA006E.includes preserve=yes
//## end module%336D05DA006E.includes

// ZARadio
#include "ZARadio.h"
//## begin module%336D05DA006E.declarations preserve=no
//## end module%336D05DA006E.declarations

//## begin module%336D05DA006E.additionalDeclarations preserve=yes
#include "ZDDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNRadio, PLFNTwoStates, g_DefVersion)
//## end module%336D05DA006E.additionalDeclarations


// Class PLFNRadio 

PLFNRadio::PLFNRadio()
  //## begin PLFNRadio::PLFNRadio%.hasinit preserve=no
  //## end PLFNRadio::PLFNRadio%.hasinit
  //## begin PLFNRadio::PLFNRadio%.initialization preserve=yes
  //## end PLFNRadio::PLFNRadio%.initialization
{
  //## begin PLFNRadio::PLFNRadio%.body preserve=yes
  //## end PLFNRadio::PLFNRadio%.body
}

PLFNRadio::PLFNRadio(const PLFNRadio &right)
  //## begin PLFNRadio::PLFNRadio%copy.hasinit preserve=no
  //## end PLFNRadio::PLFNRadio%copy.hasinit
  //## begin PLFNRadio::PLFNRadio%copy.initialization preserve=yes
  //## end PLFNRadio::PLFNRadio%copy.initialization
{
  //## begin PLFNRadio::PLFNRadio%copy.body preserve=yes
  *this = right;
  //## end PLFNRadio::PLFNRadio%copy.body
}


PLFNRadio::~PLFNRadio()
{
  //## begin PLFNRadio::~PLFNRadio%.body preserve=yes
  //## end PLFNRadio::~PLFNRadio%.body
}


const PLFNRadio & PLFNRadio::operator=(const PLFNRadio &right)
{
  //## begin PLFNRadio::operator=%.body preserve=yes
    this->PLFNTwoStates::operator=( (inherited&)right );
    return *this;
  //## end PLFNRadio::operator=%.body
}



//## Other Operations (implementation)
const PLFNRadio& PLFNRadio::operator = (const PLFNRadio* right)
{
  //## begin PLFNRadio::operator =%862783357.body preserve=yes
    this->PLFNTwoStates::operator=( (inherited*)right );
    return *this;
  //## end PLFNRadio::operator =%862783357.body
}

PlanFinObject* PLFNRadio::Clone ()
{
  //## begin PLFNRadio::Clone%862783361.body preserve=yes
    PLFNRadio*    pObject = new PLFNRadio( *this );
    return pObject;
  //## end PLFNRadio::Clone%862783361.body
}

void PLFNRadio::Serialize (CArchive& ar)
{
  //## begin PLFNRadio::Serialize%862783362.body preserve=yes
    PLFNTwoStates::Serialize(ar);
  //## end PLFNRadio::Serialize%862783362.body
}

void PLFNRadio::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNRadio::DrawObject%862783363.body preserve=yes
    DrawFillObject( pDC, pView );
    CPen    pen;
      CPen*    pOldPen = pDC->SelectObject( &GetGraphicPen( pen ) );
      if (!GetbTextIsCtrl())
      {
          CRect    RectControl(m_rctObject);
        // Test if the control is on the right
        if (GetbLeftText())
              RectControl.left = RectControl.right - GetuSize();
          switch (GetCheckType())
          {
              case E_CB_Rounded:
              {
              
                  pDC->Ellipse( RectControl.left, RectControl.top, RectControl.left+GetuSize(), RectControl.top+GetuSize() );
                  // Display a point
                  if (GetbCheckState())
                  {
                      CBrush    Brush( defCOLOR_GRAY );
                      CBrush*    pOldBrush = pDC->SelectObject( &Brush );
                      CRect    PointRect( RectControl.left, RectControl.top, RectControl.left+GetuSize(), RectControl.top+GetuSize() );
                      int        iSize = PointRect.Width();
                      PointRect.InflateRect( -iSize / 4, -iSize / 4 );
                      pDC->Ellipse( &PointRect );
                      pDC->SelectObject( pOldBrush );
                  }
                  
                  break;
              }
              case E_CB_Squared:
              {
                // Draw the square
                pDC->MoveTo( RectControl.left, RectControl.top );
                pDC->LineTo( RectControl.left, RectControl.top+GetuSize() );
                pDC->LineTo( RectControl.left+GetuSize(), RectControl.top+GetuSize() );
                pDC->LineTo( RectControl.left+GetuSize(), RectControl.top );
                pDC->LineTo( RectControl.left, RectControl.top );
                // Display a cross
                  if (GetbCheckState())
                  {
                    pDC->MoveTo( RectControl.left+1, RectControl.top+1 );
                    pDC->LineTo( RectControl.left+GetuSize()-1, RectControl.top+GetuSize()-1 );
                    pDC->MoveTo( RectControl.left+GetuSize()-1, RectControl.top+1 );
                    pDC->LineTo( RectControl.left+1, RectControl.top+GetuSize()-1 );
                  }
                  break;
              }
          }
    }
      // Draw Text
      if (GetbShowText())
      {
        CFont    *OldFont;
        
        OldFont = pDC->SelectObject( GetFont(pView) );
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor( GetColor(pView) );  // text color
        pDC->SetTextAlign( TA_LEFT | TA_BASELINE );
        // If the text does not act as a control 
          if (!GetbTextIsCtrl() && !GetbLeftText())
            pDC->TextOut( m_rctObject.left+GetuSize() + GetOffsetText(), m_rctObject.top+GetuSize(), GetsText() );
        else
        {
            pDC->TextOut( m_rctObject.left, m_rctObject.top+GetuSize(), GetsText() );
              if (GetbCheckState() && GetbTextIsCtrl())
              {
                pDC->MoveTo( m_rctObject.left+1, m_rctObject.top + (m_rctObject.Height()/2) );
                pDC->LineTo( m_rctObject.right, m_rctObject.top + (m_rctObject.Height()/2) );
              }
        }
        pDC->SelectObject( OldFont );
      }
    pDC->SelectObject( pOldPen );
    PlanFinObject::DrawObject( pDC, pView );    
  //## end PLFNRadio::DrawObject%862783363.body
}

void PLFNRadio::EditObject (CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc)
{
  //## begin PLFNRadio::EditObject%862847762.body preserve=yes
      // Get the group number
      // if greather than zero,
      // run through all elments and reset
      // all values of the same group.
    if (GetuGroupNumber() > 0)
    {
        PlanFinObject  *obj;
        // Search wich element is selected
        if ((obj=((ZDDocument*)pDoc)->GetHead()) != NULL)
        {
            do
            {
                // If in the same group
                if (obj->GetuGroupNumber() == GetuGroupNumber() &&
                    obj->IsKindOf(RUNTIME_CLASS(PLFNRadio)))
                {
                    ((PLFNRadio*)obj)->SetbCheckState( FALSE );
                    if (pParentWnd->IsWindowVisible())
                        obj->InvalidateObjectRect( pDC, pParentWnd );
                }
            }
            while ((obj=((ZDDocument*)pDoc)->GetNext( )) != NULL);
        }
    }
      SetbCheckState( !GetbCheckState() );
    if (pParentWnd->IsWindowVisible())
        InvalidateObjectRect( pDC, pParentWnd );
//    ((ZDDocument*)pDoc)->SetModifiedFlag( TRUE );
//    AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)this );
//    CWnd::GetDesktopWindow()->SendMessageToDescendants( ID_NOTIFY_OBJECTSELECTED, ID_NOTIFY_OBJECTSELECTED, (LPARAM)this );
  //## end PLFNRadio::EditObject%862847762.body
}

void PLFNRadio::CopyObject (PlanFinObject* pSrc)
{
  //## begin PLFNRadio::CopyObject%863615078.body preserve=yes
    ((PLFNRadio*)this)->PLFNRadio::operator=( (PLFNRadio*)pSrc );
  //## end PLFNRadio::CopyObject%863615078.body
}

// Additional Declarations
  //## begin PLFNRadio%336D05C30096.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNRadio diagnostics

#ifdef _DEBUG
void PLFNRadio::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNRadio::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNRadio%336D05C30096.declarations
//## begin module%336D05DA006E.epilog preserve=yes
//## end module%336D05DA006E.epilog
