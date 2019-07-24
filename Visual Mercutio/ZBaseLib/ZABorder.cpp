//## begin module%33EC6F1A0316.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33EC6F1A0316.cm

//## begin module%33EC6F1A0316.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%33EC6F1A0316.cp

//## Module: ZABorder%33EC6F1A0316; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZABorder.cpp

//## begin module%33EC6F1A0316.additionalIncludes preserve=no
//## end module%33EC6F1A0316.additionalIncludes

//## begin module%33EC6F1A0316.includes preserve=yes
#include <StdAfx.h>
//## end module%33EC6F1A0316.includes

// ZABorder
#include "ZABorder.h"
//## begin module%33EC6F1A0316.declarations preserve=no
//## end module%33EC6F1A0316.declarations

//## begin module%33EC6F1A0316.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZABorder, CObject, g_DefVersion)
//## end module%33EC6F1A0316.additionalDeclarations


// Class ZABorder 














ZABorder::ZABorder()
  //## begin ZABorder::ZABorder%.hasinit preserve=no
      : m_wLeftWidth(1), m_wTopWidth(1), m_wRightWidth(1), m_wBottomWidth(1), m_LeftType(E_LT_No), m_RightType(E_LT_No), m_TopType(E_LT_No), m_BottomType(E_LT_No), m_bShadow(FALSE)
  //## end ZABorder::ZABorder%.hasinit
  //## begin ZABorder::ZABorder%.initialization preserve=yes
  //## end ZABorder::ZABorder%.initialization
{
  //## begin ZABorder::ZABorder%.body preserve=yes
  //## end ZABorder::ZABorder%.body
}

ZABorder::ZABorder(const ZABorder &right)
  //## begin ZABorder::ZABorder%copy.hasinit preserve=no
      : m_wLeftWidth(1), m_wTopWidth(1), m_wRightWidth(1), m_wBottomWidth(1), m_LeftType(E_LT_No), m_RightType(E_LT_No), m_TopType(E_LT_No), m_BottomType(E_LT_No), m_bShadow(FALSE)
  //## end ZABorder::ZABorder%copy.hasinit
  //## begin ZABorder::ZABorder%copy.initialization preserve=yes
  , m_TopColor(defCOLOR_BLACK), m_BottomColor(defCOLOR_BLACK), m_LeftColor(defCOLOR_BLACK), m_RightColor(defCOLOR_BLACK)
  //## end ZABorder::ZABorder%copy.initialization
{
  //## begin ZABorder::ZABorder%copy.body preserve=yes
  *this = right;
  //## end ZABorder::ZABorder%copy.body
}


ZABorder::~ZABorder()
{
  //## begin ZABorder::~ZABorder%.body preserve=yes
  //## end ZABorder::~ZABorder%.body
}


const ZABorder & ZABorder::operator=(const ZABorder &right)
{
  //## begin ZABorder::operator=%.body preserve=yes
    m_wLeftWidth = right.m_wLeftWidth;
    m_wTopWidth = right.m_wTopWidth;
    m_wRightWidth = right.m_wRightWidth;
    m_wBottomWidth = right.m_wBottomWidth;
    m_LeftType = right.m_LeftType;
    m_RightType = right.m_RightType;
    m_TopType = right.m_TopType;
    m_BottomType = right.m_BottomType;
    m_bShadow = right.m_bShadow;
    m_TopColor = right.m_TopColor;
    m_BottomColor = right.m_BottomColor;
    m_LeftColor = right.m_LeftColor;
    m_RightColor = right.m_RightColor;
    return *this;
  //## end ZABorder::operator=%.body
}



//## Other Operations (implementation)
void ZABorder::Serialize (CArchive& ar)
{
  //## begin ZABorder::Serialize%871131125.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_wLeftWidth;
        ar << m_wTopWidth;
        ar << m_wRightWidth;
        ar << m_wBottomWidth;
        ar << (WORD)m_LeftType;
        ar << (WORD)m_RightType;
        ar << (WORD)m_TopType;
        ar << (WORD)m_BottomType;
        ar << (WORD)m_bShadow;
        ar << m_TopColor;
        ar << m_BottomColor;
        ar << m_LeftColor;
        ar << m_RightColor;    
    }
    else
    {
        ar >> m_wLeftWidth;
        ar >> m_wTopWidth;
        ar >> m_wRightWidth;
        ar >> m_wBottomWidth;
        WORD    wTemp;
        ar >> wTemp;
        m_LeftType = ELineType(wTemp);
        ar >> wTemp;
        m_RightType = ELineType(wTemp);
        ar >> wTemp;
        m_TopType = ELineType(wTemp);
        ar >> wTemp;
        m_BottomType = ELineType(wTemp);
        ar >> wTemp;
        m_bShadow = ELineType(wTemp);
        ar >> m_TopColor;
        ar >> m_BottomColor;
        ar >> m_LeftColor;
        ar >> m_RightColor;    
    }
  //## end ZABorder::Serialize%871131125.body
}

ZABorder* ZABorder::Clone ()
{
  //## begin ZABorder::Clone%871131126.body preserve=yes
    ZABorder*    pObject = new ZABorder( *this );
    return pObject;
  //## end ZABorder::Clone%871131126.body
}

void ZABorder::DrawBorderRect (CDC* pDC, const CRect& rect)
{
  //## begin ZABorder::DrawBorderRect%908878453.body preserve=yes
      DrawBorderTopLine( pDC, CPoint( rect.left, rect.top ), CPoint( rect.right, rect.top ) );
      DrawBorderBottomLine( pDC, CPoint( rect.left, rect.bottom ), CPoint( rect.right, rect.bottom ) );
      DrawBorderLeftLine( pDC, CPoint( rect.left, rect.top ), CPoint( rect.left, rect.bottom ) );
      DrawBorderRightLine( pDC, CPoint( rect.right, rect.top ), CPoint( rect.right, rect.bottom ) );
  //## end ZABorder::DrawBorderRect%908878453.body
}

void ZABorder::DrawBorderTopLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint)
{
  //## begin ZABorder::DrawBorderTopLine%908878454.body preserve=yes
    CPen    pen( PS_SOLID, GetwTopWidth(), GetTopColor() );
    CPen   *OldPen;
        
    OldPen = pDC->SelectObject( &pen );
    DrawBorderHorizontalLine( pDC, StartPoint, EndPoint, GetTopType() );
    pDC->SelectObject( OldPen );
  //## end ZABorder::DrawBorderTopLine%908878454.body
}

void ZABorder::DrawBorderBottomLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint)
{
  //## begin ZABorder::DrawBorderBottomLine%908878455.body preserve=yes
    CPen    pen( PS_SOLID, GetwBottomWidth(), GetBottomColor() );
    CPen   *OldPen;
        
    OldPen = pDC->SelectObject( &pen );
    DrawBorderHorizontalLine( pDC, StartPoint, EndPoint, GetBottomType() );
    pDC->SelectObject( OldPen );
  //## end ZABorder::DrawBorderBottomLine%908878455.body
}

void ZABorder::DrawBorderLeftLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint)
{
  //## begin ZABorder::DrawBorderLeftLine%908878456.body preserve=yes
    CPen    pen( PS_SOLID, GetwLeftWidth(), GetLeftColor() );
    CPen   *OldPen;
        
    OldPen = pDC->SelectObject( &pen );
    DrawBorderVerticalLine( pDC, StartPoint, EndPoint, GetLeftType() );
    pDC->SelectObject( OldPen );
  //## end ZABorder::DrawBorderLeftLine%908878456.body
}

void ZABorder::DrawBorderRightLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint)
{
  //## begin ZABorder::DrawBorderRightLine%908878457.body preserve=yes
    CPen    pen( PS_SOLID, GetwRightWidth(), GetRightColor() );
    CPen   *OldPen;
        
    OldPen = pDC->SelectObject( &pen );
    DrawBorderVerticalLine( pDC, StartPoint, EndPoint, GetRightType() );
    pDC->SelectObject( OldPen );
  //## end ZABorder::DrawBorderRightLine%908878457.body
}

void ZABorder::DrawBorderHorizontalLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint, ELineType Type)
{
  //## begin ZABorder::DrawBorderHorizontalLine%908904114.body preserve=yes
    switch (Type)
    {
        case E_LT_Dotted:
        {
            for (int i = StartPoint.x; i < EndPoint.x; i += 2)
            {
                pDC->MoveTo( i, StartPoint.y );
                pDC->LineTo( i + 1, StartPoint.y );
            }
            break;
        }
        case E_LT_Small:
        {
            for (int i = StartPoint.x; i < EndPoint.x; i += 8)
            {
                pDC->MoveTo( i, StartPoint.y );
                pDC->LineTo( i + 4, StartPoint.y );
            }
            break;
        }
        case E_LT_Solid:
        {
            pDC->MoveTo( StartPoint.x, StartPoint.y );
            pDC->LineTo( EndPoint.x, EndPoint.y );
            break;
        }
        case E_LT_Dash:
        {
            for (int i = StartPoint.x; i < EndPoint.x; i += 4)
            {
                pDC->MoveTo( i, StartPoint.y );
                pDC->LineTo( i + 2, StartPoint.y );
            }
            break;
        }
        default: break;
    }
  //## end ZABorder::DrawBorderHorizontalLine%908904114.body
}

void ZABorder::DrawBorderVerticalLine (CDC* pDC, const CPoint& StartPoint, const CPoint& EndPoint, ELineType Type)
{
  //## begin ZABorder::DrawBorderVerticalLine%908904115.body preserve=yes
    switch (Type)
    {
        case E_LT_Dotted:
        {
            for (int i = StartPoint.y; i < EndPoint.y; i += 2)
            {
                pDC->MoveTo( StartPoint.x, i );
                pDC->LineTo( StartPoint.x, i + 1 );
            }
            break;
        }
        case E_LT_Small:
        {
            for (int i = StartPoint.y; i < EndPoint.y; i += 8)
            {
                pDC->MoveTo( StartPoint.x, i );
                pDC->LineTo( StartPoint.x, i + 4 );
            }
            break;
        }
        case E_LT_Solid:
        {
            pDC->MoveTo( StartPoint.x, StartPoint.y );
            pDC->LineTo( EndPoint.x, EndPoint.y );
            break;
        }
        case E_LT_Dash:
        {
            for (int i = StartPoint.y; i < EndPoint.y; i += 4)
            {
                pDC->MoveTo( StartPoint.x, i );
                pDC->LineTo( StartPoint.x, i + 2 );
            }
            break;
        }
        default: break;
    }
  //## end ZABorder::DrawBorderVerticalLine%908904115.body
}

// Additional Declarations
  //## begin ZABorder%33EC676303DE.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZABorder diagnostics

#ifdef _DEBUG
void ZABorder::AssertValid() const
{
    CObject::AssertValid();
}

void ZABorder::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZABorder%33EC676303DE.declarations
//## begin module%33EC6F1A0316.epilog preserve=yes
//## end module%33EC6F1A0316.epilog
