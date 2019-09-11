//## begin module%336D05240276.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%336D05240276.cm

//## begin module%336D05240276.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%336D05240276.cp

//## Module: ZASquare%336D05240276; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZASquare.cpp

//## begin module%336D05240276.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%336D05240276.additionalIncludes

//## begin module%336D05240276.includes preserve=yes
//## end module%336D05240276.includes

// ZASquare
#include "ZASquare.h"
//## begin module%336D05240276.declarations preserve=no
//## end module%336D05240276.declarations

//## begin module%336D05240276.additionalDeclarations preserve=yes
#include "ZDDoc.h"
// PaintRes
#include "PSS_PaintResources.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNSquare, PSS_PlanFinObject, g_DefVersion)
//## end module%336D05240276.additionalDeclarations


// Class PLFNSquare 








PLFNSquare::PLFNSquare()
  //## begin PLFNSquare::PLFNSquare%.hasinit preserve=no
      : PSS_PlanFinObject(), m_nCharPerSquare(1), m_pObject(NULL), m_TypeOfSquare(E_SQ_Normal), m_ParsingMode(E_PM_Normal)
  //## end PLFNSquare::PLFNSquare%.hasinit
  //## begin PLFNSquare::PLFNSquare%.initialization preserve=yes
  , m_SizeSquare( CSize(15, 15) ), m_SquareMaxLength( -1 )
  //## end PLFNSquare::PLFNSquare%.initialization
{
  //## begin PLFNSquare::PLFNSquare%.body preserve=yes
  //## end PLFNSquare::PLFNSquare%.body
}

PLFNSquare::PLFNSquare(const PLFNSquare &right)
  //## begin PLFNSquare::PLFNSquare%copy.hasinit preserve=no
      : PSS_PlanFinObject(), m_nCharPerSquare(1), m_pObject(NULL), m_TypeOfSquare(E_SQ_Normal), m_ParsingMode(E_PM_Normal)
  //## end PLFNSquare::PLFNSquare%copy.hasinit
  //## begin PLFNSquare::PLFNSquare%copy.initialization preserve=yes
  //## end PLFNSquare::PLFNSquare%copy.initialization
{
  //## begin PLFNSquare::PLFNSquare%copy.body preserve=yes
  *this = right;
  //## end PLFNSquare::PLFNSquare%copy.body
}

PLFNSquare::PLFNSquare (CSize SquareSize, int iMaxLength)
  //## begin PLFNSquare::PLFNSquare%863099799.hasinit preserve=no
      : PSS_PlanFinObject(), m_nCharPerSquare(1), m_pObject(NULL), m_TypeOfSquare(E_SQ_Normal), m_ParsingMode(E_PM_Normal)
  //## end PLFNSquare::PLFNSquare%863099799.hasinit
  //## begin PLFNSquare::PLFNSquare%863099799.initialization preserve=yes
  , m_SizeSquare( SquareSize ), m_SquareMaxLength( iMaxLength )
  //## end PLFNSquare::PLFNSquare%863099799.initialization
{
  //## begin PLFNSquare::PLFNSquare%863099799.body preserve=yes
  //## end PLFNSquare::PLFNSquare%863099799.body
}


PLFNSquare::~PLFNSquare()
{
  //## begin PLFNSquare::~PLFNSquare%.body preserve=yes
      if (m_pObject)
          delete m_pObject;
  //## end PLFNSquare::~PLFNSquare%.body
}


const PLFNSquare & PLFNSquare::operator=(const PLFNSquare &right)
{
  //## begin PLFNSquare::operator=%.body preserve=yes
    this->PSS_PlanFinObject::operator=( (inherited&)right );
    m_SizeSquare = right.m_SizeSquare;
    m_SquareMaxLength = right.m_SquareMaxLength;
    m_nCharPerSquare = right.m_nCharPerSquare;
    m_TypeOfSquare = right.m_TypeOfSquare;
    m_ParsingMode = right.m_ParsingMode;
    m_pObject = right.m_pObject->Clone();
    return *this;
  //## end PLFNSquare::operator=%.body
}



//## Other Operations (implementation)
const PLFNSquare& PLFNSquare::operator = (const PLFNSquare* right)
{
  //## begin PLFNSquare::operator =%862783356.body preserve=yes
    this->PSS_PlanFinObject::operator=( (inherited*)right );
    m_SizeSquare = right->m_SizeSquare;
    m_SquareMaxLength = right->m_SquareMaxLength;
    m_nCharPerSquare = right->m_nCharPerSquare;
    m_TypeOfSquare = right->m_TypeOfSquare;
    m_ParsingMode = right->m_ParsingMode;
    m_pObject = right->m_pObject->Clone();
    return *this;
  //## end PLFNSquare::operator =%862783356.body
}

PSS_PlanFinObject* PLFNSquare::Clone ()
{
  //## begin PLFNSquare::Clone%862783358.body preserve=yes
    PLFNSquare*    pObject = new PLFNSquare( *this );
    return pObject;
  //## end PLFNSquare::Clone%862783358.body
}

void PLFNSquare::Serialize (CArchive& ar)
{
  //## begin PLFNSquare::Serialize%862783359.body preserve=yes
    PSS_PlanFinObject::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_SizeSquare;
        ar << (DWORD)m_SquareMaxLength;
        ar << (WORD)m_bAutoAdjustSize;
        ar << (DWORD)m_nCharPerSquare;
        ar << (WORD)m_TypeOfSquare;
        ar << (WORD)m_ParsingMode;
        // Serialize the oject defined
        ar << m_pObject;
    }
    else
    {    // Read the elements
        ar >> m_SizeSquare;
        DWORD dwValue;
        ar >> dwValue;
        m_SquareMaxLength = int(dwValue);
        WORD    wValue;
        ar >> wValue;
        m_bAutoAdjustSize = wValue;
        ar >> dwValue;
        m_nCharPerSquare = unsigned(dwValue);

        ar >> wValue;
        m_TypeOfSquare = ESquareType(wValue);

        ar >> wValue;
        m_ParsingMode = EParsingModeType(wValue);

        // Serialize the oject defined
        ar >> m_pObject;
    }
  //## end PLFNSquare::Serialize%862783359.body
}

void PLFNSquare::DrawObject (CDC* pDC, ZIView* pView)
{
  //## begin PLFNSquare::DrawObject%862783360.body preserve=yes
    DrawFillObject( pDC, pView );
    // If no object defined, nothing to do
      if (!m_pObject)
          return;
      CString    Str = m_pObject->GetFormattedObject();
    CFont*    pOldFont = pDC->SelectObject( GetFont(pView) );

    if (Str.GetLength())
    {
        pDC->SetBkMode(TRANSPARENT);
/*        
        if (GetColor() == -1)
            pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
        else
            pDC->SetTextColor( GetColor() );  // text color
*/            
        pDC->SetTextColor( GetColor(pView) );  // text color
    }

      // Run through each characters
    CSize    SizeText( pDC->GetTextExtent( "A", 1 ) );
     
    // If auto adjust, calculate the square size
    if (GetbAutoAdjustSize())
    {
        SetSizeSquare( CSize( SizeText.cx + 4, SizeText.cy + 4 ) );
        m_ObjectRect.top = m_ObjectRect.bottom - GetSizeSquare().cy;
/*        
        // Invalidate the new rect
        if (::GetActiveWindow())
        {
            CWnd    ActiveWindow;
            ActiveWindow.Attach( ::GetActiveWindow() );
            if (ActiveWindow.IsWindowVisible())
                InvalidateObjectRect( pDC, &ActiveWindow );
            ActiveWindow.Detach();
        }
*/        
        CRect    Rect( m_ObjectRect );
        Rect.InflateRect( 5, 5 );
        ::InvalidateRect( ::GetActiveWindow(), &Rect, TRUE );
        // Generate a WM_PAINT message
//        ::UpdateWindow( ::GetActiveWindow() );
    }
    
    DrawSquares( pDC );    
    int        iBaseText = (m_ObjectRect.Height() - SizeText.cy) / 2;
    pDC->SetTextAlign( TA_CENTER | TA_BOTTOM );
      for (int i=0; i < Str.GetLength(); ++i)
      {
        pDC->TextOut(     m_ObjectRect.left + (GetSizeSquare().cx/2) + (i*GetSizeSquare().cx) + 1, 
                        m_ObjectRect.bottom - iBaseText, 
                        Str[i] );
      }
    pDC->SelectObject( pOldFont );
    PSS_PlanFinObject::DrawObject( pDC, pView );
  //## end PLFNSquare::DrawObject%862783360.body
}

void PLFNSquare::DrawSquares (CDC* pDC)
{
  //## begin PLFNSquare::DrawSquares%863099801.body preserve=yes
    // If no object defined, nothing to do
      if (!m_pObject)
          return;
      CString    Str = m_pObject->GetFormattedObject();

      CPen*    pOldPen = pDC->SelectObject( &PSS_PaintResources::GetBlackPen() );
    // Draw squares only if the length is defined
    int        iNbSquare = GetSquareMaxLength();
    if (GetSquareMaxLength() == -1)
    {
        iNbSquare = __max( 1, Str.GetLength() );
        // Adjust the right side
        m_ObjectRect.right = m_ObjectRect.left + (iNbSquare*GetSizeSquare().cx);
    }
    if (GetbAutoAdjustSize())
        // Adjust the right side
        m_ObjectRect.right = m_ObjectRect.left + (iNbSquare*GetSizeSquare().cx);
    // Draw the outside rect
    pDC->MoveTo( m_ObjectRect.left, m_ObjectRect.top );
    pDC->LineTo( m_ObjectRect.left, m_ObjectRect.bottom );
    pDC->LineTo( m_ObjectRect.right, m_ObjectRect.bottom );
    pDC->LineTo( m_ObjectRect.right, m_ObjectRect.top );
    pDC->LineTo( m_ObjectRect.left, m_ObjectRect.top );
      // Run through each squares and draw the vertical line
      for (int i=m_nCharPerSquare; i < iNbSquare; i += m_nCharPerSquare)
    {
        pDC->MoveTo( m_ObjectRect.left+(i*GetSizeSquare().cx), m_ObjectRect.top );
        pDC->LineTo( m_ObjectRect.left+(i*GetSizeSquare().cx), m_ObjectRect.bottom );
    }
    pDC->SelectObject( pOldPen );
  //## end PLFNSquare::DrawSquares%863099801.body
}

void PLFNSquare::CopyObject (PSS_PlanFinObject* pSrc)
{
  //## begin PLFNSquare::CopyObject%863615081.body preserve=yes
    ((PLFNSquare*)this)->PLFNSquare::operator=( (PLFNSquare*)pSrc );
  //## end PLFNSquare::CopyObject%863615081.body
}

CString PLFNSquare::GetFormattedObject ()
{
  //## begin PLFNSquare::GetFormattedObject%909073221.body preserve=yes
      if (m_pObject)
          return m_pObject->GetFormattedObject();
    return "";
  //## end PLFNSquare::GetFormattedObject%909073221.body
}

BOOL PLFNSquare::ConvertFormattedObject (const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero)
{
  //## begin PLFNSquare::ConvertFormattedObject%909073222.body preserve=yes
      if (m_pObject)
          return m_pObject->ConvertFormattedObject( sValue, bLocateFormat, EmptyWhenZero );
    // Hasn't changed
    return FALSE;
  //## end PLFNSquare::ConvertFormattedObject%909073222.body
}

CString PLFNSquare::GetUnformattedObject ()
{
  //## begin PLFNSquare::GetUnformattedObject%909073225.body preserve=yes
      if (m_pObject)
          return m_pObject->GetUnformattedObject();
    return "";
  //## end PLFNSquare::GetUnformattedObject%909073225.body
}

// Additional Declarations
  //## begin PLFNSquare%336D04BA0208.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNSquare diagnostics

#ifdef _DEBUG
void PLFNSquare::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNSquare::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end PLFNSquare%336D04BA0208.declarations
//## begin module%336D05240276.epilog preserve=yes
//## end module%336D05240276.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin PLFNSquare::EditObject%862847761.body preserve=no
      if (m_pObject)
        m_pObject->EditObject( pParentWnd, pDC, pDoc);
//## end PLFNSquare::EditObject%862847761.body

#endif
