//## begin module%334FC46302E7.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302E7.cm

//## begin module%334FC46302E7.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302E7.cp

//## Module: ZAObject%334FC46302E7; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAObject.cpp

//## begin module%334FC46302E7.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302E7.additionalIncludes

//## begin module%334FC46302E7.includes preserve=yes
#include "ZIView.h"
#include "ZDDoc.h"
#include "PSS_DrawFunctions.h"

// PaintRes
#include "PaintRes.h"
//## end module%334FC46302E7.includes

// ZAObject
#include "ZAObject.h"

//## begin module%334FC46302E7.declarations preserve=no
//## end module%334FC46302E7.declarations

//## begin module%334FC46302E7.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 20 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(PlanFinObject, CObject, g_DefVersion)

// Add this one because Microsoft is unable
// to support the local
static char *months[] =
{
    _T( "janvier" ),
    _T( "février" ),
    _T( "mars" ),
    _T( "avril" ),
    _T( "mai" ),
    _T( "juin" ),
    _T( "juillet" ),
    _T( "août" ),
    _T( "septembre" ),
    _T( "octobre" ),
    _T( "novembre" ),
    _T( "décembre" )
};

static char *days[] =
{
    _T( "dimanche" ),
    _T( "lundi" ),
    _T( "mardi" ),
    _T( "mercredi" ),
    _T( "jeudi" ),
    _T( "vendredi" ),
    _T( "samedi" )
};

//## end module%334FC46302E7.additionalDeclarations

// Class PlanFinObject

//## begin PlanFinObject::FormatChoice%334FC461029D.attr preserve=no  public: static CStringArray {V} 
CStringArray PlanFinObject::m_FormatChoice;
//## end PlanFinObject::FormatChoice%334FC461029D.attr

//## begin PlanFinObject::szFormatBuffer%334FC461029E.attr preserve=no  implementation: static char[300] {V} ""
char PlanFinObject::m_szFormatBuffer[300] = _T( "" );
//## end PlanFinObject::szFormatBuffer%334FC461029E.attr

PlanFinObject::PlanFinObject()
    //## begin PlanFinObject::PlanFinObject%.hasinit preserve=no
    : m_bSelected            ( FALSE ),
      m_bIsVisible            ( TRUE ),
      m_bMustBePrinted        ( TRUE ),
      m_pRectTracker        ( NULL ),
      m_uGroupNumber        ( 0 ),
      m_hFont                ( -1 ),
      m_iAngle                ( 0 ),
      m_EmptyStyle            (E_LT_Automatic),
      m_TabOrder            ( 0 ),
      m_pBorder                ( NULL ),
      m_DefaultValue        ( FALSE ),
      m_IsEmpty                ( TRUE ),
    //## end PlanFinObject::PlanFinObject%.hasinit
    //## begin PlanFinObject::PlanFinObject%.initialization preserve=yes
      m_rctObject            ( 0, 0, 0, 0 ),
      m_iPage                ( 0 ),
      m_FormatType            (E_FT_Standard),
      m_hStyle                (NormalStyle),
      m_HasBeenChanged        ( FALSE ),
      m_ReadOnly            ( FALSE ),
      m_ReadOnlyAtRuntime    ( FALSE ),
      m_pNotes                ( NULL ),
      m_pColumn                ( NULL )
    //## end PlanFinObject::PlanFinObject%.initialization
{
    //## begin PlanFinObject::PlanFinObject%.body preserve=yes
    m_Color        = -1;
    m_FillColor    = -1;
    //## end PlanFinObject::PlanFinObject%.body
}

PlanFinObject::PlanFinObject( const PlanFinObject &right )
    //## begin PlanFinObject::PlanFinObject%copy.hasinit preserve=no
    : m_bSelected        ( FALSE ),
      m_bIsVisible        ( TRUE ),
      m_bMustBePrinted    ( TRUE ),
      m_pRectTracker    ( NULL ),
      m_uGroupNumber    ( 0 ),
      m_hFont            ( -1 ),
      m_iAngle            ( 0 ),
      m_EmptyStyle        (E_LT_Automatic),
      m_TabOrder        ( 0 ),
      m_pBorder            ( NULL ),
      m_DefaultValue    ( FALSE ),
      m_IsEmpty            ( TRUE )
    //## end PlanFinObject::PlanFinObject%copy.hasinit
    //## begin PlanFinObject::PlanFinObject%copy.initialization preserve=yes
    //## end PlanFinObject::PlanFinObject%copy.initialization
{
    //## begin PlanFinObject::PlanFinObject%copy.body preserve=yes
    *this = right;
    //## end PlanFinObject::PlanFinObject%copy.body
}

PlanFinObject::~PlanFinObject()
{
    //## begin PlanFinObject::~PlanFinObject%.body preserve=yes
    if ( m_pRectTracker )
    {
        delete m_pRectTracker;
        m_pRectTracker = NULL;
    }

    if ( m_pBorder )
    {
        delete m_pBorder;
        m_pBorder = NULL;
    }

    if ( m_pNotes )
    {
        delete m_pNotes;
        m_pNotes = NULL;
    }
    //## end PlanFinObject::~PlanFinObject%.body
}

const PlanFinObject & PlanFinObject::operator=( const PlanFinObject &right )
{
    //## begin PlanFinObject::operator=%.body preserve=yes
    this->ObjectParser::operator=( (inherited&)right );
    m_rctObject = right.m_rctObject;

    m_iPage                = right.m_iPage;
    m_bSelected            = right.m_bSelected;
    m_FormatType        = right.m_FormatType;
    m_bIsVisible        = right.m_bIsVisible;
    m_bMustBePrinted    = right.m_bMustBePrinted;
    m_Color                = right.m_Color;
    m_FillColor            = right.m_FillColor;
    m_uGroupNumber        = right.m_uGroupNumber;
    m_hFont                = right.m_hFont;
    m_hStyle            = right.m_hStyle;
    m_iAngle            = right.m_iAngle;
    m_EmptyStyle        = right.m_EmptyStyle;
    m_TabOrder            = right.m_TabOrder;
    m_LineNumber        = right.m_LineNumber;
    m_DefaultValue        = right.m_DefaultValue;
    m_HasBeenChanged    = right.m_HasBeenChanged;
    m_IsEmpty            = right.m_IsEmpty;
    m_ReadOnly            = right.m_ReadOnly;

    if ( right.m_pNotes )
    {
        m_pNotes = right.m_pNotes->Clone();
    }
    else
    {
        m_pNotes = NULL;
    }

    if ( right.m_pRectTracker )
    {
        m_pRectTracker = new CRectTracker( right.m_pRectTracker->m_rect,
                                           CRectTracker::dottedLine | CRectTracker::resizeInside );
    }
    else
    {
        m_pRectTracker = NULL;
    }

    if ( right.m_pBorder )
    {
        m_pBorder = new ZABorder( *right.m_pBorder );
    }
    else
    {
        m_pBorder = NULL;
    }

    // Copy the pointer of the multi-column
    m_pColumn = right.m_pColumn;

    // Version 17
    m_UserHelp = right.m_UserHelp;
    return *this;
    //## end PlanFinObject::operator=%.body
}

//## Other Operations (implementation)
const PlanFinObject& PlanFinObject::operator = ( const PlanFinObject* right )
{
    //## begin PlanFinObject::operator =%829516133.body preserve=yes
    this->PlanFinObject::operator=( (PlanFinObject&)*right );
    return *this;
    //## end PlanFinObject::operator =%829516133.body
}

void PlanFinObject::SetOrigin( CPoint& pt )
{
    int width                = GetClientRect().Width();
    int height                = GetClientRect().Height();
    GetClientRect().top        = pt.y;
    GetClientRect().left    = pt.x;
    GetClientRect().bottom    = GetClientRect().top + height;
    GetClientRect().right    = GetClientRect().left + width;
}

void PlanFinObject::SelectObject( CWnd* wnd, CDC* pDC, BOOL bState, BOOL bErase )
{
    //## begin PlanFinObject::SelectObject%829516138.body preserve=yes
    if ( m_bSelected == bState )
    {
        return;
    }

    m_bSelected    = bState;
    CRect rect    = m_rctObject;

    pDC->LPtoDP( &rect );

    // Creation of a RectTracker object
    if ( m_bSelected && !m_pRectTracker )
    {
        m_pRectTracker = new CRectTracker( &rect, CRectTracker::dottedLine | CRectTracker::resizeInside );
        ASSERT( m_pRectTracker );
    }
    // Deletion of the RectTracker object
    else
    {
        if ( m_pRectTracker )
        {
            delete m_pRectTracker;
            m_pRectTracker = NULL;
        }
    }

    // Refresh the modified area
    rect.InflateRect( 10, 10 );
    wnd->InvalidateRect( &rect, bErase );
    //## end PlanFinObject::SelectObject%829516138.body
}

void PlanFinObject::CopyObject( PlanFinObject* pSrc )
{
    //## begin PlanFinObject::CopyObject%863615075.body preserve=yes
    ( (PlanFinObject*)this )->PlanFinObject::operator=( (PlanFinObject*)pSrc );
    //## end PlanFinObject::CopyObject%863615075.body
}

void PlanFinObject::FormatObject( const char* szBuf )
{
    //## begin PlanFinObject::FormatObject%829516140.body preserve=yes
    strcpy( m_szFormatBuffer, szBuf );
    //## end PlanFinObject::FormatObject%829516140.body
}

void PlanFinObject::FormatObject( CTime* time )
{
    //## begin PlanFinObject::FormatObject%829516141.body preserve=yes
    switch( GetFormatType() )
    {
        case E_FT_Date:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d %s, %04d" ),
                     time->GetDay(),
                     months[time->GetMonth() - 1],
                     time->GetYear() );

            break;
        }

        case E_FT_Date1:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%s, %d %s %04d" ),
                     days[time->GetDayOfWeek() - 1],
                     time->GetDay(),
                     months[time->GetMonth() - 1],
                     time->GetYear() );

            break;
        }

        case E_FT_Date2:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d.%d.%04d %dh%d" ),
                     time->GetDay(),
                     time->GetMonth(),
                     time->GetYear(),
                     time->GetHour(),
                     time->GetSecond() );

            break;
        }

        default:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d.%d.%04d" ),
                     time->GetDay(),
                     time->GetMonth(),
                     time->GetYear() );
        }
    }
    //## end PlanFinObject::FormatObject%829516141.body
}

void PlanFinObject::FormatObject( DOUBLE dValue )
{
    //## begin PlanFinObject::FormatObject%829516142.body preserve=yes
    switch( GetFormatType() )
    {
        case E_FT_Percentage:
        {
            sprintf( m_szFormatBuffer, _T( "%3.3lg%c" ), dValue*100, _T( '%' ) );
            break;
        }

        case E_FT_Amount:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals
            char szTemp[100];
            char *p = szTemp;
            sprintf( p, _T( "%.0lf" ), dValue );

            // Introduce the symbol '
            int iLen    = strlen( p );
            int i        = 0;
            int iCount    = 0;

            //Test if negative, go to next char
            if ( dValue < 0 )
            {
                --iLen; ++p;
                m_szFormatBuffer[i++] = _T( '-' );
            }

            for( ; *p ; ++i, ++iCount, ++p )
            {
                // Add the char ' every 3 digits
                // calculate if we are on a third
                // digit by substracting the i from
                // the length
                if( iCount && ( ( iLen - iCount ) % 3) == 0 )
                {
                    m_szFormatBuffer[i++] = _T( '\'' );
                }

                m_szFormatBuffer[i] = *p;
            }

            m_szFormatBuffer[i] = 0x00;
            break;
        }

        case E_FT_Amount2:
        {
            // Use lf to remove the exponent notation
            char szTemp[100];
            char *p = szTemp;
            sprintf( p, _T( "%.2lf" ), dValue );

            // Introduce the symbol '
            int iLen    = strlen( p );
            int i        = 0;
            int iCount    = 0;

            //Test if negative, go to next char
            if ( dValue < 0 )
            {
                --iLen; ++p;
                m_szFormatBuffer[i++] = _T( '-' );
            }

            // Until the end of the string or
            // when encounter the decimal point
            for( ; *p && (*p != _T( '.' ) ) ; ++i, ++iCount, ++p )
            {
                // Add the char ' every 3 digits
                // calculate if we are on a third
                // digit by substracting the i from
                // the length
                if( iCount && ( ( iLen - iCount ) % 3 ) == 0 )
                {
                    m_szFormatBuffer[i++] = _T( '\'' );
                }

                m_szFormatBuffer[i] = *p;
            }

            while( *p )
            {
                m_szFormatBuffer[i++] = *p++;
            }

            m_szFormatBuffer[i] = 0x00;
            break;
        }

        // In the default case
        // just copy the source
        case E_FT_Standard:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals
            sprintf( m_szFormatBuffer, _T( "%.0lf" ), dValue );
            break;
        }

        case E_FT_Amount1:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals
            sprintf( m_szFormatBuffer, _T( "%.2lf" ), dValue );
            break;
        }

        case E_FT_Amount1Dash:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals + add .-
            sprintf( m_szFormatBuffer, _T( "%.0lf.-" ), dValue );
            break;
        }

        case E_FT_Amount2Dash:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals + add .--
            sprintf( m_szFormatBuffer, _T( "%.0lf.--" ), dValue );
            break;
        }

        case E_FT_Amount1DashTrail:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals
            char szTemp[100];
            char *p = szTemp;
            sprintf( p, _T( "%.0lf" ), dValue );

            // Introduce the symbol '
            int iLen    = strlen( p );
            int i        = 0;
            int iCount    = 0;

            //Test if negative, go to next char
            if ( dValue < 0 )
            {
                --iLen; ++p;
                m_szFormatBuffer[i++] = _T( '-' );
            }

            for( ; *p ; ++i, ++iCount, ++p )
            {
                // Add the char ' every 3 digits
                // calculate if we are on a third
                // digit by substracting the i from
                // the length
                if( iCount && ( ( iLen - iCount ) % 3) == 0 )
                {
                    m_szFormatBuffer[i++] = _T( '\'' );
                }

                m_szFormatBuffer[i] = *p;
            }

            m_szFormatBuffer[i++]    = _T( '.' );
            m_szFormatBuffer[i++]    = _T( '-' );
            m_szFormatBuffer[i]        = 0x00;

            break;
        }

        case E_FT_Amount2DashTrail:
        {
            // Use lf to remove the exponent notation
            // and .0 to remove the decimals
            char szTemp[100];
            char *p = szTemp;
            sprintf( p, _T( "%.0lf" ), dValue );

            // Introduce the symbol '
            int iLen    = strlen( p );
            int i        = 0;
            int iCount    = 0;

            //Test if negative, go to next char
            if ( dValue < 0 )
            {
                --iLen; ++p;
                m_szFormatBuffer[i++] = _T( '-' );
            }

            for( ; *p ; ++i, ++iCount, ++p )
            {
                // Add the char ' every 3 digits
                // calculate if we are on a third
                // digit by substracting the i from
                // the length
                if( iCount && ( ( iLen - iCount ) % 3) == 0 )
                {
                    m_szFormatBuffer[i++] = _T( '\'' );
                }

                m_szFormatBuffer[i] = *p;
            }

            m_szFormatBuffer[i++]    = _T( '.' );
            m_szFormatBuffer[i++]    = _T( '-' );
            m_szFormatBuffer[i++]    = _T( '-' );
            m_szFormatBuffer[i]        = 0x00;

            break;
        }

        default:
        {
            m_szFormatBuffer[0] = 0x00;
        }
    }
    //## end PlanFinObject::FormatObject%829516142.body
}

CString PlanFinObject::GetFormatedObject()
{
    //## begin PlanFinObject::GetFormatedObject%829516158.body preserve=yes
    return _T( "" );
    //## end PlanFinObject::GetFormatedObject%829516158.body
}

CString PlanFinObject::GetUnformatedObject()
{
    //## begin PlanFinObject::GetUnformatedObject%901298461.body preserve=yes
    return _T( "" );
    //## end PlanFinObject::GetUnformatedObject%901298461.body
}

BOOL PlanFinObject::ConvertFormatedObject( const CString& sValue, BOOL bLocateFormat, BOOL EmptyWhenZero )
{
    //## begin PlanFinObject::ConvertFormatedObject%829516157.body preserve=yes
    // Hasn't changed
    return FALSE;
    //## end PlanFinObject::ConvertFormatedObject%829516157.body
}

void PlanFinObject::DrawObject( CDC* pDC, ZIView* pView )
{
    //## begin PlanFinObject::DrawObject%829516173.body preserve=yes
    if ( IsSelectObject() )
    {
        if ( m_pRectTracker )
        {
            CRect rect = GetClientRect();
            pDC->LPtoDP( &rect );
            GetpRectTracker()->m_rect = rect;
            m_pRectTracker->Draw( pDC );
        }
    }

    // Draw the border if exists
    ZABorder* pBorder = (ZABorder*)GetBorder( pView );

    if ( pBorder )
    {
        pBorder->DrawBorderRect( pDC, m_rctObject );
    }
    //## end PlanFinObject::DrawObject%829516173.body
}

void PlanFinObject::DrawEmpty( CDC* pDC, ZIView* pView )
{
    //## begin PlanFinObject::DrawEmpty%829516174.body preserve=yes
    // If we are printing and it is not necessary to print the empty style,
    // just return
    if ( pDC->IsPrinting() && pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty() == FALSE )
    {
        return;
    }

    // Draw the doted line without the dotted line style
    // it is bugged when it print
    CPen pen( PS_SOLID, 1, GetColor( pView ) );
    CPen *OldPen;
    OldPen = pDC->SelectObject( &pen );

    switch ( pView->GetDocument()->GetDocOptions().GetEmptyStyle() )
    {
        case E_LT_Dotted:
        {
            for ( int i = m_rctObject.left; i < m_rctObject.right; i += 2 )
            {
                pDC->MoveTo( i, m_rctObject.bottom - 2 );
                pDC->LineTo( i + 1, m_rctObject.bottom - 2 );
            }

            break;
        }

        case E_LT_Small:
        {
            for ( int i = m_rctObject.left; i < m_rctObject.right; i += 8 )
            {
                pDC->MoveTo( i, m_rctObject.bottom - 2 );
                pDC->LineTo( i + 4, m_rctObject.bottom - 2 );
            }

            break;
        }

        case E_LT_Solid:
        {
            pDC->MoveTo( m_rctObject.left, m_rctObject.bottom - 2 );
            pDC->LineTo( m_rctObject.right, m_rctObject.bottom - 2 );

            break;
        }

        case E_LT_Dash:
        {
            for ( int i = m_rctObject.left; i < m_rctObject.right; i += 4 )
            {
                pDC->MoveTo( i, m_rctObject.bottom - 2 );
                pDC->LineTo( i + 2, m_rctObject.bottom - 2 );
            }

            break;
        }

        default:
        {
            break;
        }
    }

    pDC->SelectObject( OldPen );
    //## end PlanFinObject::DrawEmpty%829516174.body
}

void PlanFinObject::DrawHiddenSymbol(CDC* pDC)
{
    // draw the object rectangle
    PlanFinObject::DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_HIDDEN),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_HIDDEN), RT_BITMAP),
                         m_rctObject.right,
                         m_rctObject.bottom,
                         SRCAND);
}

void PlanFinObject::DrawHiddenOnPrintSymbol( CDC* pDC )
{
    // draw the object rectangle
    PlanFinObject::DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_PRINTER),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PRINTER), RT_BITMAP),
                         m_rctObject.right,
                         m_rctObject.bottom,
                         SRCAND);
}

void PlanFinObject::DrawCalculatedSymbol(CDC* pDC)
{}

void PlanFinObject::DrawNoteSymbol(CDC* pDC)
{
    // draw the object rectangle
    PlanFinObject::DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_NOTES),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_NOTES), RT_BITMAP),
                         m_rctObject.right,
                         m_rctObject.bottom,
                         SRCAND);
}

void PlanFinObject::DrawObjectRectangle( CDC* pDC )
{
    //## begin PlanFinObject::DrawObjectRectangle%944215349.body preserve=yes
    CPen*    pOldPen = NULL;
    CPen    Pen( PS_DOT, 1, defCOLOR_BLACK );

    pOldPen = pDC->SelectObject( &Pen );
    pDC->MoveTo( m_rctObject.left, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.top );

    pDC->SelectObject( pOldPen );
    //## end PlanFinObject::DrawObjectRectangle%944215349.body
}

void PlanFinObject::DrawTabOrder( CDC* pDC )
{
    //## begin PlanFinObject::DrawTabOrder%947360848.body preserve=yes
    // First display the object
    CFont *OldFont;
    OldFont = pDC->SelectObject( &ZBPaintResources::GetSmallSystemFont() );

    CString Buffer;
    sprintf( Buffer.GetBufferSetLength( 7 ), _T( "%g" ), GetTabOrder() );
    Buffer.ReleaseBuffer();

    CSize sizeText;
    sizeText = pDC->GetTextExtent( Buffer, Buffer.GetLength() );
    sizeText.cx += 10;
    sizeText.cy += 5;

    // Calculate the position of the main bubble
    int iMiddleX = m_rctObject.left + ( m_rctObject.Width() / 2 );
    int iBottomY = __max( m_rctObject.bottom, sizeText.cy + m_rctObject.top );

    CRect rect( iMiddleX - (sizeText.cx / 2),
                m_rctObject.top,
                iMiddleX + (sizeText.cx / 2),
                iBottomY );

    // Draw the object rectangle in blue
    CPen* pOldPen;
    pOldPen = pDC->SelectObject( &ZBPaintResources::GetGrayPen() );

    pDC->MoveTo( m_rctObject.left, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.top );

    // After display the bubble with the name
    CBrush* pOldBrush;
    pOldBrush = pDC->SelectObject( &ZBPaintResources::GetGrayBrush() );

    pDC->SetBkMode( TRANSPARENT );
    pDC->SetTextColor( defCOLOR_BLACK );
    pDC->SetTextAlign( 0 );
    pDC->Rectangle( &rect );
    pDC->DrawText( Buffer, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

    // Draw Shadow
    pDC->SelectObject( &ZBPaintResources::GetBlackPen() );
    pDC->MoveTo( m_rctObject.right + 1, m_rctObject.top + 1 );
    pDC->LineTo( m_rctObject.right + 1, m_rctObject.bottom + 1 );
    pDC->LineTo( m_rctObject.left + 1, m_rctObject.bottom + 1 );
    pDC->MoveTo( rect.right, rect.top + 1 );
    pDC->LineTo( rect.right, rect.bottom );
    pDC->LineTo( rect.left + 1, rect.bottom );

    pDC->SelectObject( pOldPen );
    pDC->SelectObject( pOldBrush );
    pDC->SelectObject( OldFont );
    //## end PlanFinObject::DrawTabOrder%947360848.body
}

void PlanFinObject::DisplayCodeName( CDC* pDC, ZIView* pView, BOOL bDisplay, CWnd* pWnd )
{
    //## begin PlanFinObject::DisplayCodeName%829516178.body preserve=yes
    // First display the object
    CFont *OldFont;
    OldFont = pDC->SelectObject( &ZBPaintResources::GetSmallSystemFont() );

    CSize sizeText;
    sizeText = pDC->GetTextExtent( GetObjectName(), GetObjectName().GetLength() );
    sizeText.cx += 10;
    sizeText.cy += 5;

    // Calculate the position of the main bubble
    int iMiddleX    = m_rctObject.left + ( m_rctObject.Width() / 2 );
    int iTopY        = m_rctObject.top - 15;

    CRect rect( iMiddleX - (sizeText.cx / 2),
                iTopY - sizeText.cy,
                iMiddleX + (sizeText.cx / 2),
                iTopY );

    // Draw the bubble
    if ( bDisplay )
    {
        DrawObject( pDC, pView );

        // Draw the object rectangle in blue
        CPen* pOldPen;
        pOldPen = pDC->SelectObject( &ZBPaintResources::GetBluePen() );

        pDC->MoveTo( m_rctObject.left, m_rctObject.top );
        pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
        pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
        pDC->LineTo( m_rctObject.right, m_rctObject.top );
        pDC->LineTo( m_rctObject.left, m_rctObject.top );

        // After display the bubble with the name
        CBrush* pOldBrush;
        pOldBrush = pDC->SelectObject( &ZBPaintResources::GetLtBlueBrush() );

        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor( GetFont( pView )->GetFontColor() );
        pDC->SetTextAlign( 0 );
        pDC->Rectangle( &rect );
        pDC->DrawText( GetObjectName(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

        // Draw small bubble
        CRect BigElipseRect( 0, 0, 12, 6 );
        CRect SmallElipseRect( 0, 0, 8, 4 );

        BigElipseRect.OffsetRect( iMiddleX - 6, iTopY + 2 );
        pDC->Ellipse( &BigElipseRect );

        SmallElipseRect.OffsetRect( iMiddleX - 4, iTopY + 10 );
        pDC->Ellipse( &SmallElipseRect );

        // Draw Shadow
        pDC->SelectObject( &ZBPaintResources::GetBlackPen() );
        pDC->MoveTo( m_rctObject.right + 1, m_rctObject.top + 1 );
        pDC->LineTo( m_rctObject.right + 1, m_rctObject.bottom + 1 );
        pDC->LineTo( m_rctObject.left + 1, m_rctObject.bottom + 1 );
        pDC->MoveTo( rect.right, rect.top + 1 );
        pDC->LineTo( rect.right, rect.bottom );
        pDC->LineTo( rect.left + 1, rect.bottom );

        pDC->SelectObject( pOldPen );
        pDC->SelectObject( pOldBrush );
    }
    else
    {
        CRect RegionRect;

        // Bug with a line
//        RegionRect.UnionRect( &rect, &m_rctObject );
//        RegionRect.InflateRect( 5, 10 );

        // Thus, do itself
        RegionRect.left        = __min( rect.left, m_rctObject.left ) - 5;
        RegionRect.right    = __max( rect.right, m_rctObject.right ) + 5;
        RegionRect.top        = __min( rect.top, m_rctObject.top ) - 5;
        RegionRect.bottom    = __max( rect.bottom, m_rctObject.bottom ) + 5;
        pDC->LPtoDP( &RegionRect );

        pWnd->InvalidateRect( &RegionRect );
        pWnd->UpdateWindow();
    }

    pDC->SelectObject( OldFont );
    //## end PlanFinObject::DisplayCodeName%829516178.body
}

void PlanFinObject::AssignFont()
{
    //## begin PlanFinObject::AssignFont%829516181.body preserve=yes
    //## end PlanFinObject::AssignFont%829516181.body
}

void PlanFinObject::DCDrawMoveObject( CDC* pDC )
{
    //## begin PlanFinObject::DCDrawMoveObject%829516182.body preserve=yes
    TRACE( _T( "DRAW DC" ) );

    CRect    rect;
    CBrush    brush, *OldBrush;
    CPen    pen, *OldPen;

    brush.CreateHatchBrush( HS_BDIAGONAL, defCOLOR_BLACK );
    pen.CreatePen( PS_SOLID, 1, defCOLOR_BLACK );

    OldBrush    = pDC->SelectObject( &brush );
    OldPen        = pDC->SelectObject( &pen );

    GetRectTop( &rect );
    pDC->Rectangle( &rect );

    GetRectBottom( &rect );
    pDC->Rectangle( &rect );

    GetRectLeft( &rect );
    pDC->Rectangle( &rect );

    GetRectRight( &rect );
    pDC->Rectangle( &rect );

    pDC->FrameRect( m_rctObject, &brush );
    pDC->SelectObject( OldBrush );
    pDC->SelectObject( OldPen );
    //## end PlanFinObject::DCDrawMoveObject%829516182.body
}

void PlanFinObject::InvalidateObjectRect( CDC* pDC, CWnd* pWnd, CRect* pRect )
{
    //## begin PlanFinObject::InvalidateObjectRect%831175686.body preserve=yes
    if ( pRect == NULL )
    {
        CRect ObjRect( GetClientRect() );
        pDC->LPtoDP( &ObjRect );
        pWnd->InvalidateRect( &ObjRect );
    }
    else
    {
        pDC->LPtoDP( pRect );
        pWnd->InvalidateRect( pRect );
    }
    //## end PlanFinObject::InvalidateObjectRect%831175686.body
}

void PlanFinObject::DisplayColorForNumber( CDC* pDC, ZIView* pView )
{
    //## begin PlanFinObject::DisplayColorForNumber%840085276.body preserve=yes
    // First display the object
    DrawObject( pDC, pView );

    // Draw the object rectangle in blue
    CPen* pOldPen;
    pOldPen = pDC->SelectObject( &ZBPaintResources::GetRedPen() );

    pDC->MoveTo( m_rctObject.left, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.top );

    // Draw Shadow
    pDC->SelectObject( &ZBPaintResources::GetBlackPen() );
    pDC->MoveTo( m_rctObject.right + 1, m_rctObject.top + 1 );
    pDC->LineTo( m_rctObject.right + 1, m_rctObject.bottom + 1 );
    pDC->LineTo( m_rctObject.left + 1, m_rctObject.bottom + 1 );

    pDC->SelectObject( pOldPen );
    //## end PlanFinObject::DisplayColorForNumber%840085276.body
}

void PlanFinObject::DrawBoundRect( CDC* pDC )
{
    //## begin PlanFinObject::DrawBoundRect%846024741.body preserve=yes
    CPen*    pOldPen = NULL;
    CPen    Pen( PS_DOT, 1, defCOLOR_GRAY );

    pOldPen = pDC->SelectObject( &Pen );
    pDC->MoveTo( m_rctObject.left, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.bottom );
    pDC->LineTo( m_rctObject.right, m_rctObject.top );
    pDC->LineTo( m_rctObject.left, m_rctObject.top );
    pDC->SelectObject( pOldPen );

    DrawRightCorner( pDC );
    //## end PlanFinObject::DrawBoundRect%846024741.body
}

PlanFinObject* PlanFinObject::Clone()
{
    //## begin PlanFinObject::Clone%849755977.body preserve=yes
    PlanFinObject* pObject = new PlanFinObject( *this );
    return pObject;
    //## end PlanFinObject::Clone%849755977.body
}

void PlanFinObject::DrawFillObject( CDC* pDC, ZIView* pView )
{
    //## begin PlanFinObject::DrawFillObject%850768723.body preserve=yes
    COLORREF col = GetFillColor( pView );

    if ( col != -1 )
    {
        CPen    Pen( PS_SOLID, 1, col );
        CPen*    pOldPen = pDC->SelectObject( &Pen );
        CBrush  Brush( col );
        CBrush*    pOldBrush = pDC->SelectObject( &Brush );

        pDC->Rectangle( &GetClientRect() );
        pDC->SelectObject( pOldPen );
        pDC->SelectObject( pOldBrush );
    }
    //## end PlanFinObject::DrawFillObject%850768723.body
}

void PlanFinObject::DisplayObjectName( CDC* pDC )
{
    //## begin PlanFinObject::DisplayObjectName%862512873.body preserve=yes
    CFont *OldFont = pDC->SelectObject( &ZBPaintResources::GetSmallSystemFont() );

    pDC->SetBkMode( TRANSPARENT );
    pDC->SetTextColor( defCOLOR_BLACK );
    pDC->SetTextAlign( TA_LEFT | TA_BOTTOM );
    pDC->TextOut( m_rctObject.left, m_rctObject.bottom, GetObjectName() );
    pDC->SelectObject( OldFont );
    //## end PlanFinObject::DisplayObjectName%862512873.body
}

void PlanFinObject::SizePositionHasChanged()
{
    //## begin PlanFinObject::SizePositionHasChanged%863883948.body preserve=yes
    AfxGetMainWnd()->SendMessageToDescendants( UM_MOVEOBJECTINORDER, 0, (LPARAM)this );
    //## end PlanFinObject::SizePositionHasChanged%863883948.body
}

ZAFont* PlanFinObject::GetFont( ZIView* pView )
{
    //## begin PlanFinObject::GetFont%870032842.body preserve=yes
    ZDDocument* pDoc = pView->GetDocument();

    if ( pDoc )
    {
        // Return the specific Font assigned directly

        if ( m_hFont != NoFontDefined )
        {
            return pDoc->GetFontManager().GetFont( m_hFont );
        }

        if ( !pDoc->GetStyleManager().GetStyle( m_hStyle ) )
        {
            return NULL;
        }

        // Return the Font of the style
        return pDoc->GetFontManager().GetFont( pDoc->GetStyleManager().GetStyle( m_hStyle )->GethFont() );
    }

    return NULL;
    //## end PlanFinObject::GetFont%870032842.body
}

COLORREF PlanFinObject::GetColor( ZIView* pView )
{
    //## begin PlanFinObject::GetColor%873634803.body preserve=yes
    ZDDocument* pDoc = pView->GetDocument();

    if ( pDoc )
    {
        // If the object has changed.
        if ( HasBeenChanged() )
        {
            // if the color is already red change and 
            // draw with blue color
            return ( m_Color == defCOLOR_RED ) ? defCOLOR_BLUE : defCOLOR_RED;
        }

        // Return the assigned color if there is one defined
        if ( m_Color != -1 )
        {
            return m_Color;
        }

        // Otherwise return the font color defined in the font or in the style
        return ( GetFont( pView ) ) ? GetFont( pView )->GetFontColor() : defCOLOR_BLACK;
    }

    return -1;
    //## end PlanFinObject::GetColor%873634803.body
}

void PlanFinObject::SethStyle( HandleStyle value )
{
    //## begin PlanFinObject::SethStyle%873638112.body preserve=yes
    m_hStyle = value;

    // Remove the object format attributes
    // No Font
    SethFont( NoFontDefined );

    // No Color
    SetColor( -1 );

    // No Fill Color
    SetFillColor( -1 );

    // No Justification
    SetJustify(g_NoAlignement);

    // No Border
    SetpBorder( NULL );
    //## end PlanFinObject::SethStyle%873638112.body
}

void PlanFinObject::OnAngleChanged( ZDDocument* pDoc )
{
    //## begin PlanFinObject::OnAngleChanged%880663112.body preserve=yes
    // Does nothing. Each object must implement themselve this method
    //## end PlanFinObject::OnAngleChanged%880663112.body
}

void PlanFinObject::RotateFont( ZDDocument* pDoc )
{
    //## begin PlanFinObject::RotateFont%880893868.body preserve=yes
    if ( pDoc )
    {
        HandleFont hFont;

        if ( GethFont() != NoFontDefined )
        {
            hFont = GethFont();
        }
        else
        {
            hFont =
                ( pDoc->GetStyleManager().GetStyle( m_hStyle ) != NULL ) ? pDoc->GetStyleManager().GetStyle( m_hStyle )->GethFont() : NULL;
        }

        if ( hFont )
        {
            SethFont( pDoc->GetFontManager().RotateFont( hFont, m_iAngle ) );
        }
    }
    //## end PlanFinObject::RotateFont%880893868.body
}

CSize PlanFinObject::GetTextExtent( CDC* pDC, const CString& Str, int Angle )
{
    //## begin PlanFinObject::GetTextExtent%881694196.body preserve=yes
    CSize TextSize;
    TextSize = pDC->GetTextExtent( Str, Str.GetLength() );

    if ( Angle == 0 )
    {
        return TextSize;
    }

    // Angle must be positive
    while ( Angle < 0 )
    {
        Angle += 3600;
    }

    // Convert in radian
    double dRadianAngle;
    dRadianAngle = ( (double)Angle * atan( 1.0 ) * 4 ) / 1800;

    CSize    ModifiedTextSize;
    ModifiedTextSize.cx = abs( (int)( (double)TextSize.cx * cos( dRadianAngle ) ) ) + abs( (int)( (double)TextSize.cy * sin( dRadianAngle ) ) );
    ModifiedTextSize.cy = abs( (int)( (double)TextSize.cx * sin( dRadianAngle ) ) ) + abs( (int)( (double)TextSize.cy * cos( dRadianAngle ) ) );

    return ModifiedTextSize;
    //## end PlanFinObject::GetTextExtent%881694196.body
}

void PlanFinObject::GetTextExtentOrg( CDC* pDC, const CString& Str, CSize& Size, CPoint& Org, int Angle )
{
    //## begin PlanFinObject::GetTextExtentOrg%881701325.body preserve=yes

    // Angle must be positive
    ASSERT( Angle >= 0 );

    CSize TextSize;
    TextSize = pDC->GetTextExtent( Str, Str.GetLength() );

    if ( Angle == 0 )
    {
        Size    = TextSize;
        Org.x    = Org.y = 0;

        return;
    }

    // Convert in radian
    double dRadianAngle;
    dRadianAngle = ( (double)Angle * atan( 1.0 ) * 4 ) / 1800;

    // Calculate the text size
    Size.cx = abs( (int)( (double)TextSize.cx * cos( dRadianAngle ) ) ) + abs( (int)( (double)TextSize.cy * sin( dRadianAngle ) ) );
    Size.cy = abs( (int)( (double)TextSize.cx * sin( dRadianAngle ) ) ) + abs( (int)( (double)TextSize.cy * cos( dRadianAngle ) ) );

    // Calculate the text origin
    if ( Angle < 900 )
    {
        Org.y = 0;
        Org.x = abs( (int)( (double)TextSize.cy * sin( dRadianAngle ) ) );
    }
    else if ( Angle < 1800 )
    {
        Org.y = abs( (int)( (double)TextSize.cy * cos( dRadianAngle ) ) );
        Org.x = Size.cx;
    }
    else if ( Angle < 2700 )
    {
        Org.y = Size.cy;
        Org.x = abs( (int)( (double)TextSize.cx * sin( dRadianAngle - 900 ) ) );
    }
    else
    {
        Org.y = abs( (int)( (double)TextSize.cx * cos( dRadianAngle - 900 ) ) );
        Org.x = 0;
    }
    //## end PlanFinObject::GetTextExtentOrg%881701325.body
}

COLORREF PlanFinObject::GetFillColor( ZIView* pView ) const
{
    //## begin PlanFinObject::GetFillColor%892746528.body preserve=yes
    if ( m_FillColor != -1 )
    {
        return m_FillColor;
    }

    // Retreive the style back color
    return ( pView->GetDocument()->GetStyleManager().GetStyle( m_hStyle ) != NULL ) ?
                pView->GetDocument()->GetStyleManager().GetStyle( m_hStyle )->GetBackColor() :
                defCOLOR_WHITE;
    //## end PlanFinObject::GetFillColor%892746528.body
}

void PlanFinObject::MoveObject( CPoint& MovePt, BOOL RelativeMove )
{
    //## begin PlanFinObject::MoveObject%901975364.body preserve=yes
    if ( RelativeMove )
    {
        m_rctObject.OffsetRect( MovePt );
    }
    else
    {
        // Saves the height and the width of the object
        int iWidth    = GetClientRect().Width();
        int iHeight    = GetClientRect().Height();

        // Assigns new starting point
        GetClientRect().top        = MovePt.y;
        GetClientRect().left    = MovePt.x;

        // Assigns the size
        GetClientRect().bottom    = GetClientRect().top + iHeight;
        GetClientRect().right    = GetClientRect().left + iWidth;
    }
    //## end PlanFinObject::MoveObject%901975364.body
}

const ZABorder* PlanFinObject::GetBorder( ZIView* pView ) const
{
    //## begin PlanFinObject::GetBorder%908815225.body preserve=yes
    if ( m_pBorder )
    {
        return m_pBorder;
    }

    // Retreive the style back color
    return ( pView->GetDocument()->GetStyleManager().GetStyle( m_hStyle ) != NULL) ?
                pView->GetDocument()->GetStyleManager().GetStyle( m_hStyle )->GetpBorder() :
                NULL;
    //## end PlanFinObject::GetBorder%908815225.body
}

BOOL PlanFinObject::AddNotes( const CString Comment, const CString Username )
{
    //## begin PlanFinObject::AddNotes%937741726.body preserve=yes
    if ( !m_pNotes )
    {
        m_pNotes = new ZBNotes;
    }

    m_pNotes->SetComment( Comment );
    m_pNotes->SetUsername( Username );

    return TRUE;
    //## end PlanFinObject::AddNotes%937741726.body
}

void PlanFinObject::DeleteNotes()
{
    //## begin PlanFinObject::DeleteNotes%937741727.body preserve=yes
    if ( m_pNotes )
    {
        delete m_pNotes;
    }

    m_pNotes = NULL;
    //## end PlanFinObject::DeleteNotes%937741727.body
}

// Additional Declarations
//## begin PlanFinObject%334FC4610180.declarations preserve=yes
void PlanFinObject::DrawRightCorner( CDC* pDC )
{
    CPen* pOldPen = NULL;
    pOldPen = pDC->SelectObject( &ZBPaintResources::GetBlackPen() );

    // Draw Small Shadow
    pDC->MoveTo( m_rctObject.right + 1, m_rctObject.bottom - 4 );
    pDC->LineTo( m_rctObject.right + 1, m_rctObject.bottom + 1 );
    pDC->LineTo( m_rctObject.right - 4, m_rctObject.bottom + 1 );
    pDC->MoveTo( m_rctObject.right + 2, m_rctObject.bottom - 3 );
    pDC->LineTo( m_rctObject.right + 2, m_rctObject.bottom + 2 );
    pDC->LineTo( m_rctObject.right - 3, m_rctObject.bottom + 2 );
    pDC->MoveTo( m_rctObject.right + 1, m_rctObject.bottom - 4 );
    pDC->LineTo( m_rctObject.right - 4, m_rctObject.bottom + 1 );

    pDC->SelectObject( pOldPen );
}
//## end PlanFinObject%334FC4610180.declarations

//## begin module%334FC46302E7.epilog preserve=yes
void PlanFinObject::FormatObject( COleDateTime* time )
{
    switch( GetFormatType() )
    {
        case E_FT_Date:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d %s, %04d" ),
                     time->GetDay(),
                     months[time->GetMonth() - 1],
                     time->GetYear() );

            break;
        }

        case E_FT_Date1:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%s, %d %s %04d" ),
                     days[time->GetDayOfWeek() - 1],
                     time->GetDay(),
                     months[time->GetMonth() - 1],
                     time->GetYear() );

            break;
        }

        case E_FT_Date2:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d.%d.%04d %dh%d" ),
                     time->GetDay(),
                     time->GetMonth(),
                     time->GetYear(),
                     time->GetHour(),
                     time->GetSecond() );

            break;
        }

        default:
        {
            sprintf( m_szFormatBuffer,
                     _T( "%d.%d.%04d" ),
                     time->GetDay(),
                     time->GetMonth(),
                     time->GetYear() );
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// PlanFinObject diagnostics

#ifdef _DEBUG
void PlanFinObject::AssertValid() const
{
    CObject::AssertValid();
}

void PlanFinObject::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

void PlanFinObject::Serialize (CArchive& ar)
{
    //## begin PlanFinObject::Serialize%829516183.body preserve=yes
    // Increment the element counter.
    if ( ar.m_pDocument->IsKindOf( RUNTIME_CLASS( ZDDocument ) ) )
    {
        ( (ZDDocument*)ar.m_pDocument )->SetCurrentElement( ( (ZDDocument*)ar.m_pDocument )->GetCurrentElement() + 1 );
    }

    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_rctObject;
        ar << m_strObjName;

        // In version 4 do not write the FontType
//        ar << (WORD)m_fntType;        

        ar << (WORD)m_iPage;

        // To keep the serialization as before
        // do the following
        ar << (WORD)m_FormatType;
        ar << (WORD)m_bIsVisible;
        ar << (WORD)m_bMustBePrinted;

        // Version 2
        ar << m_Color;
        ar << m_FillColor;

        // Version 3
        ar << m_uGroupNumber;

        // Version 4
        ar << m_hFont;
        ar << (WORD)m_hStyle;
        ar << (WORD)m_iAngle;
        ar << (WORD)m_EmptyStyle;
        ar << m_TabOrder;

        // Serialize the font pointer
        ar << m_pBorder;

        // Serialize the default value
        ar << (WORD)m_DefaultValue;

        // Test if template
        if (((ZDDocument*)ar.m_pDocument )->GetDocumentStamp().GetFileType() == E_FD_TemplateType &&
            !GetDefaultValue()                                                                    &&
            !GetIsStatic() )
        {
            m_IsEmpty = TRUE;
        }

        ar << (WORD)m_IsEmpty;
        ar << (WORD)m_ReadOnly; // Version 14
        ar << m_pNotes;            // Version 14
        ar << m_UserHelp;        // Version 17
    }
    else
    {
        // Read the elements
        ar >> m_rctObject;
        ar >> m_strObjName;
        ASSERT( !m_strObjName.IsEmpty() );

        WORD wTemp;
        // If before Version 4 read the FontType
        // And assign the font
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() < 4 )
        {
            ar >> wTemp;
        }

        ar >> wTemp;
        m_iPage = (int)wTemp;
        ASSERT( m_iPage >= 0 );
        
        ar >> wTemp;

        // To keep the serialization as before
        // do the following
        m_FormatType = EFormatType(wTemp);

        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 1 )
        {
            ar >> wTemp;
            m_bIsVisible = (int)wTemp;

            ar >> wTemp;
            m_bMustBePrinted = (int)wTemp;
        }

        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 2 )
        {
            ar >> m_Color;
            ar >> m_FillColor;
        }

        if ( ( (PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 3 )
        {
            ar >> m_uGroupNumber;
        }

        // Version 4
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 4 )
        {
            ar >> m_hFont;

            ar >> wTemp;
            m_hStyle = (int)wTemp;

            ar >> wTemp;
            m_iAngle = (int)wTemp;
        }

        // Version 5
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 5 )
        {
            ar >> wTemp;
            m_EmptyStyle = ELineType(wTemp);
            ar >> m_TabOrder;
        }

        // Version 7
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 7 )
        {
            // Deserialize the font pointer
            ar >> m_pBorder;
        }

        // Version 8
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 8 )
        {
            // Deserialize the default value
            ar >> wTemp;
            m_DefaultValue = (BOOL)wTemp;
        }

        // Version 12
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 12 )
        {
            // Deserialize the empty value
            ar >> wTemp;
            m_IsEmpty = (BOOL)wTemp;
        }

        // Version 14
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 14 )
        {
            // Deserialize the read-only value
            ar >> wTemp;
            m_ReadOnly = (BOOL)wTemp;
            ar >> (CObject*&)m_pNotes;
        }

        // Version 17
        if ( ( (PSS_BaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 17 )
        {
            ar >> m_UserHelp;
        }
    }
    //## end PlanFinObject::Serialize%829516183.body
}
//## end module%334FC46302E7.epilog
