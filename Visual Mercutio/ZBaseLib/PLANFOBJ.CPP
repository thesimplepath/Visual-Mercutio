// planfobj.cpp : implementation of the ZDDocumentReadWrite class
//

#include "stdafx.h"

#include "ZIView.h"
#include "planfobj.h"
#include "zamath.h"
#include "draw.h"

#include "ZDDoc.h"

#include <FLOAT.H>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(PLFNStatic, PLFNText, g_DefVersion)
IMPLEMENT_SERIAL(PLFNTime, PLFNAscii, g_DefVersion)
IMPLEMENT_SERIAL(PLFNLong, PLFNAscii, g_DefVersion)
IMPLEMENT_SERIAL(PLFNRect, PLFNGraphic, g_DefVersion)
IMPLEMENT_SERIAL(PLFNLine, PLFNGraphic, g_DefVersion)
               
/////////////////////////////////////////////////////////////////////////////
// PLFNLine construction/destruction

PLFNLine::PLFNLine()
: m_StartPoint(0,0), m_EndPoint(0,0)
{
}

PLFNLine::PLFNLine(const PLFNLine &right)
{
      *this = right;
}

const PLFNLine & PLFNLine::operator=(const PLFNLine *right)
{
    this->PLFNGraphic::operator=( (inherited*)right );
    m_StartPoint = right->m_StartPoint;
    m_EndPoint = right->m_EndPoint;
    return *this;
}

const PLFNLine & PLFNLine::operator=(const PLFNLine &right)
{
    this->PLFNGraphic::operator=( (inherited&)right );
    m_StartPoint = right.m_StartPoint;
    m_EndPoint = right.m_EndPoint;
    return *this;
}


PlanFinObject* PLFNLine::Clone()
{
    PLFNLine*    pObject = new PLFNLine( *this );
    return pObject;
}

void PLFNLine::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNLine*)this)->PLFNLine::operator=( (PLFNLine*)pSrc );
}

PLFNLine::~PLFNLine()
{
}


void PLFNLine::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
/*    
    COLORREF    col;
    if (GetColor() == -1)
        col = GetFont()->GetFontColor();  // text color
    else
        col = GetColor();  // text color
        pen( PS_SOLID, 1, GetColor(pView) )
*/
    CPen    pen, *OldPen;
    CPen    pen2( PS_SOLID, 1, defCOLOR_LTLTGRAY );

    OldPen = pDC->SelectObject( &GetGraphicPen( pen ) );

    // PROBLEM
//    pDC->MoveTo( m_StartPoint.x, m_StartPoint.y );
//    pDC->LineTo( m_EndPoint.x, m_EndPoint.y );
    pDC->MoveTo( m_rctObject.left, m_rctObject.top );
    pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
    // Display the shadow only on the screen
    if( pDC->IsPrinting() == FALSE )
    {
        pDC->SelectObject( &pen2 );
//        pDC->MoveTo( m_StartPoint.x+1, m_StartPoint.y+1 );
//        pDC->LineTo( m_EndPoint.x+1, m_EndPoint.y+1 );
        pDC->MoveTo( m_rctObject.left+1, m_rctObject.top+1 );
        pDC->LineTo( m_rctObject.right+1, m_rctObject.bottom+1 );
    }
    pDC->SelectObject( OldPen );
    PlanFinObject::DrawObject( pDC, pView );
}

void PLFNLine::SizePositionHasChanged()
{
      // Call the basic fonction
    PlanFinObject::SizePositionHasChanged();
      // Recalculate all element positions.
    m_StartPoint.x = m_rctObject.left;
    m_StartPoint.y = m_rctObject.top;
    m_EndPoint.x = m_rctObject.right;
    m_EndPoint.y = m_rctObject.bottom;
  //## end PLFNAutoNumbered::SizePositionHasChanged%863883949.body
}

/////////////////////////////////////////////////////////////////////////////
// PLFNLine serialization

void PLFNLine::Serialize(CArchive& ar)
{
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        PLFNGraphic::Serialize(ar);
    else
        PlanFinObject::Serialize(ar);
        
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_StartPoint;
        ar << m_EndPoint;      
    }
    else
    // If is reading from file
    {    // If the version is before the version 0
        // Then the rectangle for line must be modified
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 0)
            m_rctObject.bottom = m_rctObject.top;
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_StartPoint;
            ar >> m_EndPoint;
        }
        else
        {
            m_StartPoint.x = m_rctObject.left;
            m_StartPoint.y = m_rctObject.top;
            m_EndPoint.x = m_rctObject.right;
            m_EndPoint.y = m_rctObject.bottom;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// PLFNLine diagnostics

#ifdef _DEBUG
void PLFNLine::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNLine::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNRect construction/destruction

PLFNRect::PLFNRect( BOOL bRound )
 : m_bRound(bRound), m_ArcOffset( 5 )    // Offset's arc by default takes 5
{
}

PLFNRect::PLFNRect(const PLFNRect &right)
{
      *this = right;
}

const PLFNRect & PLFNRect::operator=(const PLFNRect *right)
{
    this->PLFNGraphic::operator=( (inherited*)right );
    m_bRound = right->m_bRound;
    m_ArcOffset = right->m_ArcOffset;
    return *this;
}

const PLFNRect & PLFNRect::operator=(const PLFNRect &right)
{
    this->PLFNGraphic::operator=( (inherited&)right );
    m_bRound = right.m_bRound;
    m_ArcOffset = right.m_ArcOffset;
    return *this;
}



PlanFinObject* PLFNRect::Clone()
{
    PLFNRect*    pObject = new PLFNRect( *this );
    return pObject;
}

void PLFNRect::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNRect*)this)->PLFNRect::operator=( (PLFNRect*)pSrc );
}

PLFNRect::~PLFNRect()
{
}


void PLFNRect::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );

/*    
    COLORREF    col;
    if (GetColor() == -1)
        col = GetFont()->GetFontColor();  // text color
    else
        col = GetColor();  // text color
        
        pen( PS_SOLID, 1, GetColor(pView) ), 
*/
    CPen    pen, *OldPen;
    CPen    pen2( PS_SOLID, 1, defCOLOR_LTLTGRAY );

    OldPen = pDC->SelectObject( &GetGraphicPen( pen ) );
    
    if (m_bRound)
    {

        // Display the square
        pDC->MoveTo( m_rctObject.left + GetArcOffset(), m_rctObject.top );
        pDC->LineTo( m_rctObject.right - GetArcOffset() + 1, m_rctObject.top );

        pDC->Arc( m_rctObject.left, m_rctObject.top,    // upper-left corner
                  m_rctObject.left + (GetArcOffset()*2), m_rctObject.top + (GetArcOffset()*2), // lower-right corner
                  m_rctObject.left + GetArcOffset(), m_rctObject.top,    // Starting point
                  m_rctObject.left, m_rctObject.top + GetArcOffset() + 1);    // Ending point
                  
        pDC->MoveTo( m_rctObject.right, m_rctObject.top + GetArcOffset() );
        pDC->LineTo( m_rctObject.right, m_rctObject.bottom - GetArcOffset() + 1 );

        pDC->Arc( m_rctObject.right - (GetArcOffset()*2), m_rctObject.top,    // upper-right corner
                  m_rctObject.right, m_rctObject.top + (GetArcOffset()*2), 
                  m_rctObject.right, m_rctObject.top + GetArcOffset(),    // Starting point
                  m_rctObject.right - GetArcOffset(), m_rctObject.top);    // Ending point

        pDC->MoveTo( m_rctObject.right - GetArcOffset(), m_rctObject.bottom );
        pDC->LineTo( m_rctObject.left + GetArcOffset() - 1, m_rctObject.bottom );

        pDC->Arc( m_rctObject.right - (GetArcOffset()*2), m_rctObject.bottom - (GetArcOffset()*2),// lower-right corner
                  m_rctObject.right, m_rctObject.bottom, 
                  m_rctObject.right - GetArcOffset() - 1, m_rctObject.bottom,    // Starting point
                  m_rctObject.right, m_rctObject.bottom - GetArcOffset());    // Ending point

        pDC->MoveTo( m_rctObject.left, m_rctObject.bottom - GetArcOffset() );
        pDC->LineTo( m_rctObject.left, m_rctObject.top + GetArcOffset() - 1 );

        pDC->Arc( m_rctObject.left, m_rctObject.bottom - (GetArcOffset()*2),    // lower-left corner
                  m_rctObject.left + (GetArcOffset()*2), m_rctObject.bottom, 
                  m_rctObject.left, m_rctObject.bottom - GetArcOffset(),    // Starting point
                  m_rctObject.left + GetArcOffset() + 1, m_rctObject.bottom);    // Ending point

/* Doesn't work, find a solution to not fill the 
#ifdef _WIN32
        pDC->SetBkMode( TRANSPARENT );
        pDC->RoundRect( m_rctObject.left, m_rctObject.top, 
                        m_rctObject.right, m_rctObject.bottom,
                        GetArcOffset(), GetArcOffset() );

#endif
*/
    }

    else
    {
        // Display the square
        pDC->MoveTo( m_rctObject.left, m_rctObject.top );
        pDC->LineTo( m_rctObject.right, m_rctObject.top );
        pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
        pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
        pDC->LineTo( m_rctObject.left, m_rctObject.top );
    }
    // Display the shadow only on the screen
    if( pDC->IsPrinting() == FALSE )
    {
        pDC->SelectObject( &pen2 );
        if (m_bRound)
        {
        }
        else
        {
            pDC->MoveTo( m_rctObject.right+1, m_rctObject.top+1 );
            pDC->LineTo( m_rctObject.right+1, m_rctObject.bottom+1 );
            pDC->LineTo( m_rctObject.left-1, m_rctObject.bottom+1 );
        }
    }
    pDC->SelectObject( OldPen );
    PlanFinObject::DrawObject( pDC, pView );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNRect serialization

void PLFNRect::Serialize(CArchive& ar)
{
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        PLFNGraphic::Serialize(ar);
    else
        PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {    // Write the elements
        ar << m_ArcOffset;
        ar << (WORD)m_bRound;
    }
    else
    {    // Read the elements
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> m_ArcOffset;
            WORD    wTemp;
            ar >> wTemp;
            m_bRound = (BOOL)wTemp;
        }
        else
            m_bRound = FALSE;
    }

    
}

/////////////////////////////////////////////////////////////////////////////
// PLFNRect diagnostics

#ifdef _DEBUG
void PLFNRect::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNRect::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// PLFNStatic construction/destruction

PLFNStatic::PLFNStatic()
{
      SetIsStatic( TRUE );    // Defines as static
}
PLFNStatic::PLFNStatic(const PLFNStatic &right)
{
      *this = right;
}

const PLFNStatic & PLFNStatic::operator=(const PLFNStatic *right)
{
    this->PLFNText::operator=( (inherited*)right );
//    m_Str = right->m_Str;
    return *this;
}

const PLFNStatic & PLFNStatic::operator=(const PLFNStatic &right)
{
    this->PLFNText::operator=( (inherited&)right );
//    m_Str = right.m_Str;
    return *this;
}

PlanFinObject* PLFNStatic::Clone()
{
    PLFNStatic*    pObject = new PLFNStatic( *this );
    return pObject;
}

void PLFNStatic::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNStatic*)this)->PLFNStatic::operator=( (PLFNStatic*)pSrc );
}

PLFNStatic::~PLFNStatic()
{
}

//BOOL     PLFNStatic::IsSelected( const CPoint& point ) const
//{
//    return( m_rctObject.PtInRect( point ) );
//}


void PLFNStatic::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont*    OldFont;
    CSize    sizeText;
    CPoint    orgText;
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    pDC->SetBkMode(TRANSPARENT);

    pDC->SetTextColor( GetColor(pView) );  // text color
    GetTextExtentOrg( pDC, m_Str, sizeText, orgText, GetiAngle() );
    m_rctObject.right = m_rctObject.left + sizeText.cx;
    // I change the alignement to bottom to remove the
    // alignement problem with different fonts
    // then I should change the calculation of the text area
    m_rctObject.top = m_rctObject.bottom - sizeText.cy;
    pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
    pDC->TextOut( m_rctObject.left + orgText.x, m_rctObject.bottom - orgText.y, m_Str );
    pDC->SelectObject( OldFont );

    PlanFinObject::DrawObject( pDC, pView );
}


void PLFNStatic::OnAngleChanged(ZDDocument* pDoc)
{
    // First, rotate the font.
    RotateFont(pDoc);
}


/////////////////////////////////////////////////////////////////////////////
// PLFNStatic serialization





/////////////////////////////////////////////////////////////////////////////
// PLFNTime construction/destruction
// The default is the zero time.
PLFNTime::PLFNTime()
{
    m_Time = g_ZeroTime;
}
PLFNTime::PLFNTime(const PLFNTime &right)
{
      *this = right;
}

const PLFNTime & PLFNTime::operator=(const PLFNTime *right)
{
    this->PLFNAscii::operator=( (inherited*)right );
    m_Time = right->m_Time;
    return *this;
}

const PLFNTime & PLFNTime::operator=(const PLFNTime &right)
{
    this->PLFNAscii::operator=( (inherited&)right );
    m_Time = right.m_Time;
    return *this;
}

PlanFinObject* PLFNTime::Clone()
{
    PLFNTime*    pObject = new PLFNTime( *this );
    return pObject;
}

void PLFNTime::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNTime*)this)->PLFNTime::operator=( (PLFNTime*)pSrc );
}

PLFNTime::~PLFNTime()
{
}

BOOL     PLFNTime::IsSelected( const CPoint& point ) const
{
    return( m_rctObject.PtInRect( point ) );
}

// This function return the string
// represented the object formated 
// with the current format type
// Format with the time value
CString     PLFNTime::GetFormatedObject( )
{
    FormatObject( &m_Time );
    CString        sValue( GetFormatedBuffer() );

    return sValue;
}

CString PLFNTime::GetUnformatedObject()
{
    if (IsEmpty())
        m_szFormatBuffer[0] = 0x00;    // Empty the string
    else
        sprintf( m_szFormatBuffer, "%d.%d.%04d", m_Time.GetDay(), 
                                                 m_Time.GetMonth(),
                                                 m_Time.GetYear() );
    return GetFormatedBuffer();
}

// This function convert the string
// and set the object with the right value
// For this function convert the time
// string to a m_Time.
BOOL    PLFNTime::ConvertFormatedObject( const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero )
{
    // Sets the flag for empty or not
    (sValue.IsEmpty() == TRUE) ? EmptyObject() : ClearEmptyObjectFlag();
    
    int        iMonth;
    int        iDay;
/*
    // Copy the original string
    // and makes it lower for comparison
    CString     sCopy = sValue;
    sCopy.MakeLower();

    CTime    tmNow = CTime::GetCurrentTime();
    CTime    tmTemp( tmNow.GetYear(), 1, 1, 0, 0, 0 );
    int        i;
    // Do the loop with days and
    // store all days in a array
    CStringArray    Days;
    for ( i = 0; i < 7; ++i)
    {
        // Add one day
        tmTemp += 1;
        // Then add the new day in the array
        CString        sTemp = tmTemp.Format("%A");
        sTemp.MakeLower();
        Days.Add( sTemp );
    }

    // Do the loop with months and
    // store all months in a array
    char*    cpPos;
    CStringArray    Months;
    for (int iM = 1; iM < 13; ++iM)
    {
        CTime    tmForMonth( tmNow.GetYear(), iM, 1, 0, 0, 0 );
        CString        sTemp = tmForMonth.Format("%B");
        sTemp.MakeLower();
        // Then add the new month in the array
        Days.Add( sTemp );
    }

    // Search in the list if a months is defined
    for( i = 0; i < Months.GetSize( ); ++i )
        if ( (cpPos=strstr( (const char*)sCopy, (const char*)Months[i] )) != (char*)NULL)
        {
            iMonth = i;
            break;
        }

    // Search in the list if a days is defined
    for( i = 0; i < Days.GetSize( ); ++i )
        if ( (cpPos=strstr( (const char*)sCopy, (const char*)Days[i] )) != (char*)NULL)
        {
            iDay = i;
            break;
        }
*/    
    // Saves the old value to know if the value has changed
#ifndef _WIN32
    CTime            OldTime = m_Time;
#endif
#ifdef _WIN32
    COleDateTime    OldTime = m_Time;
#endif

    CString        strTemp = sValue;

    CString        strParam;
    int            iIndex;
    // Retrieve the day
    if( (iIndex=strTemp.FindOneOf("./")) == -1 )
    {
#ifndef _WIN32
        EmptyObject();
#endif
#ifdef _WIN32
        EmptyObject();
#endif
        // Has changed ???
        return (OldTime != m_Time) ? TRUE : FALSE;
    }
    strParam = strTemp.Left( iIndex );
    iDay = atoi( (const char *)strParam );
    if (iDay <= 0)
        return FALSE;
    // Retrieve the month
    strTemp = strTemp.Right( strTemp.GetLength()-iIndex-1 );
    if( (iIndex=strTemp.FindOneOf("./")) == -1 )
    {
#ifndef _WIN32
        EmptyObject();;
#endif
#ifdef _WIN32
        EmptyObject();;
#endif
        // Has changed ???
        return (OldTime != m_Time) ? TRUE : FALSE;
    }
    strParam = strTemp.Left( iIndex );
    iMonth = atoi( (const char *)strParam );
    if (iMonth <= 0)
        return FALSE;
    // Retrieve the year
    strParam = strTemp.Right( strTemp.GetLength()-iIndex-1 );
    int iYear = atoi( (const char *)strParam );
    if( iYear < 1900 )        // 1900 Based date
        iYear += 1900;
#ifndef _WIN32
    CTime    tm(iYear, iMonth, iDay, 12, 00, 00);
#endif
#ifdef _WIN32
    COleDateTime    tm(iYear, iMonth, iDay, 12, 00, 00);
#endif
    m_Time = tm;
    // Has changed ???
    return (OldTime != m_Time) ? TRUE : FALSE;
}

/*
CStringArray&    PLFNTime::GetInitialChoice()
{
    m_InitialChoice.RemoveAll();
    // Add the today value
    CTime    tmNow = CTime::GetCurrentTime();
    FormatObject( &tmNow );
    CString        sValue( GetFormatedBuffer() );
    m_InitialChoice.Add( sValue );
    return m_InitialChoice;
}
*/

CStringArray&    PLFNTime::GetFormatChoice()
{
    m_FormatChoice.RemoveAll();
    // Read the number and format it
    // Create a copy of the current object
    // and modify the format.
    PLFNTime    TmpTime;
    TmpTime = (PLFNTime*)this;

    TmpTime.SetFormatType(E_FT_Standard);
    TmpTime.FormatObject( &TmpTime.m_Time );
    m_FormatChoice.Add( CString( TmpTime.GetFormatedBuffer() ) );

    TmpTime.SetFormatType(E_FT_Date);
    TmpTime.FormatObject( &TmpTime.m_Time );
    m_FormatChoice.Add( CString( TmpTime.GetFormatedBuffer() ) );

    TmpTime.SetFormatType(E_FT_Date1);
    TmpTime.FormatObject( &TmpTime.m_Time );
    m_FormatChoice.Add( CString( TmpTime.GetFormatedBuffer() ) );

    TmpTime.SetFormatType(E_FT_Date2);
    TmpTime.FormatObject( &TmpTime.m_Time );
    m_FormatChoice.Add( CString( TmpTime.GetFormatedBuffer() ) );

    return m_FormatChoice;
}
//---------------------------------------------------------------------------
void PLFNTime::SetFormatWithChoice( const CString& sValue )
{
    const INT_PTR formatChoiceCount = m_FormatChoice.GetSize();
          INT_PTR index             = 0;

    // run through the array and compare which one is the same
    for (INT_PTR i = 0; i < formatChoiceCount; ++i)
        if (m_FormatChoice[i] == sValue)
        {
            index = i;
            break;
        }

    // one format has been found
    if (index < formatChoiceCount)
        switch (index)
        {
            case 0: m_FormatType = E_FT_Standard; break;
            case 1: m_FormatType = E_FT_Date;     break;
            case 2: m_FormatType = E_FT_Date1;    break;
            case 3: m_FormatType = E_FT_Date2;    break;
        }
}

void PLFNTime::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        pDC->SetBkMode(TRANSPARENT);
/*        
        if (GetColor() == -1)
            pDC->SetTextColor( GetFont()->GetFontColor() );  // text color
        else
            pDC->SetTextColor( GetColor() );  // text color
*/            
        pDC->SetTextColor( GetColor(pView) );  // text color
        // Before displaying the object
        // format it
        FormatObject( &m_Time );
        pDC->SetTextAlign( 0 );
        pDC->DrawText( GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
//        pDC->SetTextAlign( GetJustify() /*TA_LEFT | TA_BOTTOM*/ );
//        pDC->TextOut( m_rctObject.left, m_rctObject.bottom, GetFormatedBuffer() );
//        pDC->DrawText( strFormated, -1, &m_rctObject, DT_LEFT | DT_BOTTOM | DT_SINGLELINE );
    }
    pDC->SelectObject( OldFont );
    PlanFinObject::DrawObject( pDC, pView );
}


/////////////////////////////////////////////////////////////////////////////
// PLFNTime serialization

void PLFNTime::Serialize(CArchive& ar)
{
    PlanFinObject::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_Time;

    }
    else
    {    // Read the elements
        // Before version 12
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 13)
        {
            CTime    Time;
            ar >> Time;
            if (Time.GetTime() >= 0)
                m_Time.SetDateTime( Time.GetYear(), Time.GetMonth(), Time.GetDay(), Time.GetHour(), Time.GetMinute(), Time.GetSecond() );
            // Before version 12
            if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 12)
            {
#ifdef _WIN32
                // Construct a CTime for making comparison
                CTime    ZeroTime( g_ZeroTime.GetYear(), g_ZeroTime.GetMonth(), g_ZeroTime.GetDay(), g_ZeroTime.GetHour(), g_ZeroTime.GetMinute(), g_ZeroTime.GetSecond() );
                m_IsEmpty = (Time == ZeroTime);
#endif
#ifndef _WIN32
                m_IsEmpty = (Time == g_ZeroTime);
#endif
            }
        }
        else
        {
            ar >> m_Time;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// PLFNTime diagnostics

#ifdef _DEBUG
void PLFNTime::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNTime::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG






/////////////////////////////////////////////////////////////////////////////
// PLFNLong construction/destruction

PLFNLong::PLFNLong()
 : m_bKeepTheValue( FALSE ), m_bIsCalculatedField( FALSE ), m_dRounded(0), m_IsRounded(FALSE), m_IconDisplayType( NoIcon )
{
    m_Long = 0;
}
PLFNLong::PLFNLong(const PLFNLong &right)
{
      *this = right;
}

const PLFNLong & PLFNLong::operator=(const PLFNLong *right)
{
    this->PLFNAscii::operator=( (inherited*)right );
    m_Long = right->m_Long;
    m_bIsCalculatedField = right->m_bIsCalculatedField;
    m_bKeepTheValue = right->m_bKeepTheValue;
    m_IsRounded = right->m_IsRounded;
    m_dRounded = right->m_dRounded;
    m_Associations.AssignContents( right->m_Associations );
    m_IconDisplayType = right->m_IconDisplayType;
    return *this;
}

const PLFNLong & PLFNLong::operator=(const PLFNLong &right)
{
    this->PLFNAscii::operator=( (inherited&)right );
    m_Long = right.m_Long;
    m_bIsCalculatedField = right.m_bIsCalculatedField;
    m_bKeepTheValue = right.m_bKeepTheValue;
    m_IsRounded = right.m_IsRounded;
    m_dRounded = right.m_dRounded;
    m_Associations.AssignContents( right.m_Associations );
    m_IconDisplayType = right.m_IconDisplayType;
    return *this;
}

PlanFinObject* PLFNLong::Clone()
{
    PLFNLong*    pObject = new PLFNLong( *this );
    return pObject;
}

void PLFNLong::CopyObject(PlanFinObject* pSrc)
{
    ((PLFNLong*)this)->PLFNLong::operator=( (PLFNLong*)pSrc );
}


PLFNLong::~PLFNLong()
{
}

// This function return the string
// represented the object formated 
// with the current format type
// Format with the time value
CString     PLFNLong::GetFormatedObject( )
{
    if ( IsEmpty() )
        return "";
//    if (IsCalculatedField())
//            FormatObject( m_Long );
//    else
    FormatObject( m_Long );

//    CString        sValue( GetFormatedBuffer() );

    return GetFormatedBuffer();
}

CString PLFNLong::GetUnformatedObject ()
{
    if ( IsEmpty() )
        return "";
    sprintf( m_szFormatBuffer, "%lf", m_Long );
    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
// This function convert the string
// and set the object with the right value
// For this function convert the
// string to a long.
BOOL PLFNLong::ConvertFormatedObject(const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero)
{
    if (sValue.IsEmpty())
    {
        EmptyObject();
        return TRUE;
    }

    // save the oldvalue to make comparison
    double OldValue = m_Long;

    // Convert the string to a double
    // assign the result to the value
    // Test if the char % is present
    // If it is the case remove it and
    // divide the number by 100
    // If the char % is present the char '
    // can't be present at the same time
    char* pCpPos = const_cast<char*>(std::strchr((const char*)sValue, '%'));

    if (pCpPos)
    {
        // test if at the same time char '
        if (std::strchr((const char*)sValue, '\''))
        {
            AfxMessageBox( IDS_WZFORMATNUMBERERROR );
            return FALSE;
        }

        // replace the percentage sign
        *pCpPos = 0x00;
         m_Long = std::atof((const char*)sValue) / 100;

        if (bLocateFormat)
            SetFormatType(E_FT_Percentage);

        // test if it is necessary to empty the object on zeros
        if (EmptyWhenZero && !m_Long)
            EmptyObject();

        // has changed?
        return (OldValue != m_Long) ? TRUE : FALSE;
    }

    // Detect dash or double-dash
    bool b2Dash = false;
    bool b1Dash = false;

    if (std::strstr((const char*)sValue, ".--"))
        b2Dash = true;
    else 
    if (std::strstr((const char*)sValue, ".-"))
        b1Dash = true;

    // test if char ' for amounts
    if (std::strchr((const char*)sValue, '\''))
    {

        // remove the ' char
        const char* pBuffer = (const char*)sValue;
        char        szTemp[100];
        std::size_t index = 0;

        for (int i = 0; *pBuffer; ++pBuffer)
            if (*pBuffer != '\'')
            {
                szTemp[i] = *pBuffer;
                ++i;
                index = i;
            }

        szTemp[index] = 0x00;

        // if dahs or double-dash, remove it before converting to number
        if (b2Dash)
            // set artificial end of buffer
            szTemp[index - 2] = 0x00;
        else
        if (b1Dash)
            // set artificial end of buffer
            szTemp[index - 1] = 0x00;

        m_Long = std::atof(szTemp);

        if (bLocateFormat)
            if (std::strchr((const char*)sValue, ',') || std::strchr((const char*)sValue, '.'))
            {
                if (b2Dash)
                    SetFormatType(E_FT_Amount2DashTrail);
                else
                if (b1Dash)
                    SetFormatType(E_FT_Amount1DashTrail);
                else
                    SetFormatType(E_FT_Amount2);
            }
            else
                SetFormatType(E_FT_Amount);
    }
    else
    {
        char szTemp[100];
        int  i = sValue.GetLength() - 1;

        std::strcpy(szTemp, (const char*)sValue);

        // if dahs or double-dash, remove it before converting to number
        if (b2Dash)
            // set artificial end of buffer
            szTemp[i - 2] = 0x00;
        else
        if (b1Dash)
            // Set artificial end of buffer
            szTemp[i - 1] = 0x00;

        m_Long = std::atof(szTemp);

        if (bLocateFormat && (std::strchr((const char*)sValue, ',') || std::strchr((const char*)sValue, '.')))
        {
            if (b2Dash)
                SetFormatType(E_FT_Amount2Dash);
            else
            if (b1Dash)
                SetFormatType(E_FT_Amount1Dash);
            else
                SetFormatType(E_FT_Amount1);
        }
    }

    // test if it is necessary to empty the object on zeros
    if (EmptyWhenZero && !m_Long)
        EmptyObject();
    else
        ClearEmptyObjectFlag();

    // has changed?
    return (OldValue != m_Long) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
CStringArray& PLFNLong::GetFormatChoice()
{
    m_FormatChoice.RemoveAll();
    // Read the number and format it
    // Create a copy of the current object
    // and modify the format.
    bool        bWasEmpty = false;
    PLFNLong    TmpLong;
    TmpLong = (PLFNLong*)this;
    // Bug for empty number
    // Set 0 if empty
    if (TmpLong.IsEmpty())
    {
        bWasEmpty = true;
        TmpLong.SetValue( 1035.25 );
    }
    TmpLong.SetFormatType(E_FT_Standard);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    TmpLong.SetFormatType(E_FT_Amount);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );


    TmpLong.SetFormatType(E_FT_Amount1);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    TmpLong.SetFormatType(E_FT_Amount2);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );


    TmpLong.SetFormatType(E_FT_Amount1Dash);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );


    TmpLong.SetFormatType(E_FT_Amount2Dash);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    TmpLong.SetFormatType(E_FT_Amount1DashTrail);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    TmpLong.SetFormatType(E_FT_Amount2DashTrail);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    if (bWasEmpty)
        TmpLong.SetValue( 0.5845 );

    TmpLong.SetFormatType(E_FT_Percentage);
    TmpLong.FormatObject( TmpLong.m_Long );
    m_FormatChoice.Add( CString( TmpLong.GetFormatedBuffer() ) );

    return m_FormatChoice;
}

void PLFNLong::SetFormatWithChoice(const CString& sValue)
{
    const INT_PTR formatChoiceCount = m_FormatChoice.GetSize();
          INT_PTR index             = 0;

    // run through the array and compare which one is the same
    for (INT_PTR i = 0; i < formatChoiceCount; ++i)
        if (m_FormatChoice[i] == sValue)
        {
            index = i;
            break;
        }

    // one format has been found
    if (index <  m_FormatChoice.GetSize( ))
        switch (index)
        {
            case 0: m_FormatType = E_FT_Standard;         break;
            case 1: m_FormatType = E_FT_Amount;           break;
            case 2: m_FormatType = E_FT_Amount1;          break;
            case 3: m_FormatType = E_FT_Amount2;          break;
            case 4: m_FormatType = E_FT_Amount1Dash;      break;
            case 5: m_FormatType = E_FT_Amount2Dash;      break;
            case 6: m_FormatType = E_FT_Amount1DashTrail; break;
            case 7: m_FormatType = E_FT_Amount2DashTrail; break;
            case 8: m_FormatType = E_FT_Percentage;       break;
        }
}

void PLFNLong::DrawObject( CDC* pDC, ZIView* pView )
{
    DrawFillObject( pDC, pView );
    
    CFont    *OldFont;
    
    OldFont = pDC->SelectObject( GetFont(pView) );
    if (IsEmpty())
        DrawEmpty( pDC, pView );
    else
    {
        pDC->SetBkMode(TRANSPARENT);
        COLORREF    col = GetColor(pView);
        pDC->SetTextColor( col );  
        // Before displaying the object
        // format it
        FormatObject( m_Long );
        pDC->SetTextAlign( 0 );
        pDC->DrawText( GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()) );
    }
    pDC->SelectObject( OldFont );
    
    PlanFinObject::DrawObject( pDC, pView );
}


void PLFNLong::DrawCalculatedSymbol (CDC* pDC)
{
    if (!pDC->IsPrinting())
    {
        HINSTANCE hInst = AfxFindResourceHandle( MAKEINTRESOURCE(IDB_CALCBACKASSC), RT_BITMAP );

        if (GetCurrentAssociation())
        {
            if (IsCalculatedField())
            {
                PlanFinObject::DrawBoundRect( pDC );
                // Show calculator icon in association mode
                DisplayBitmapFile(     MAKEINTRESOURCE (IDB_CALCBACKASSC), pDC->m_hDC, hInst, 
                                      m_rctObject.right, m_rctObject.bottom );
            }
            else
            {
                // Show icon in association mode
                DisplayBitmapFile(     MAKEINTRESOURCE (IDB_BACKASSC), pDC->m_hDC, hInst, 
                                      m_rctObject.right, m_rctObject.bottom );
                PlanFinObject::DrawRightCorner( pDC );
            }
        }
        else
        {
            if (m_IconDisplayType == AssociationIcon)
            {
                PlanFinObject::DrawBoundRect( pDC );
                // Display the field as calculate with association
                DisplayBitmapFile(     MAKEINTRESOURCE (IDB_CALCWITHASSC), pDC->m_hDC, hInst, 
                                      m_rctObject.right, m_rctObject.bottom );
            }
            else
                if (IsCalculatedField())
                {
                    PlanFinObject::DrawBoundRect( pDC );
                    // Display the field as protected
                    if (KeepTheValue())
                        DisplayBitmapFileExtent( MAKEINTRESOURCE (IDB_LOCKED), pDC->m_hDC, hInst, 
                                                   m_rctObject.right, m_rctObject.bottom,
                                                   SRCAND );
                    else
                    {
                        if (GetAssociations().GetCount())
                            // Show calculator icon for association mode
                            DisplayBitmapFile(     MAKEINTRESOURCE (IDB_CALCSHOWASSC), pDC->m_hDC, hInst, 
                                                  m_rctObject.right, m_rctObject.bottom );                
                        else
                            // Display the field as calculate
                            DisplayBitmapFile(     MAKEINTRESOURCE (IDB_CALCULATOR), pDC->m_hDC, hInst, 
                                                  m_rctObject.right, m_rctObject.bottom );
                    }
                }
        }
    }
}

// This function recalculate is own
// value
void     PLFNLong::Recalculate(ZDDocument*    pDoc)
{
    if (pDoc)
    {
        ZAFormula*    Formula = pDoc->GetFormula( GetObjectName() );
        if (Formula)
        {    
            Parser            prs;
            m_Long = prs.StringParser( (const char *)Formula->m_sExtractedFormula, &(pDoc->GetObjectList()) );
            if( GetRoundedValue() && IsRounded() )
            // Function floor first integer less than
            // Function ceil first integer greater than
                m_Long = /*floor*/ ceil( m_Long / GetRoundedValue() ) * GetRoundedValue();
        }
    }
}

// GetContains --------------------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    19/12/1994
// Description    :    This function scan the line and retreive the object
//                    contains.
// Parameters    :    strLine            the string that contains the line.
//
// Return        :    Nothing.
//
//----------------------------------------------------------------------------
void    PLFNLong::GetContains( CString& strLine )
{
    int            iIndex;
    
    // Extract object Name    
    if( (iIndex=strLine.ReverseFind(',')) == -1 )
        return;

    // Extract the string of the value
    CString        str;
    int        iPos = strLine.GetLength()-iIndex-2;
    if( iPos > 0 )
        str = strLine.Right( iPos );
    m_Long = atof( str );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNLong serialization

void PLFNLong::Serialize(CArchive& ar)
{
    PLFNAscii::Serialize(ar);
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_Long;
        ar << (WORD)m_bIsCalculatedField;
        ar << (WORD)m_bKeepTheValue;
// Since version 5, removed
//        m_SchemaArray.Serialize( ar );
        ar << (WORD)m_IsRounded;
        ar << m_dRounded;
        ar << (WORD)m_IconDisplayType;    
    }
    else
    {    // Read the elements
        WORD    wValue;
        ar >> m_Long;
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 1)
        {
            m_bIsCalculatedField = FALSE;
            m_bKeepTheValue = FALSE;
        }
        else
        {
            ar >> wValue;
            m_bIsCalculatedField = wValue;
            ar >> wValue;
            m_bKeepTheValue = wValue;
        }
        // Between version 2 and 4
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2 && ((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() <= 5)
        {
            CStringArray    m_SchemaArray;        // Contains the schema array
            m_SchemaArray.Serialize( ar );
        }
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> wValue;
            m_IsRounded = (BOOL)wValue;
            ar >> m_dRounded;
        }
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 6)
        {
            ar >> wValue;
            m_IconDisplayType = (IconDisplayType)wValue;
        }
        // Before version 12
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 12)
        {
            m_IsEmpty = (m_Long == FLT_MAX);
            if (m_Long == FLT_MAX)
                m_Long = 0;
        }
    }
    // Serialize Associations
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 6)
        m_Associations.Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// PLFNLong diagnostics

#ifdef _DEBUG
void PLFNLong::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNLong::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG








