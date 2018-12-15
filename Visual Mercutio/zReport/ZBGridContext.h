// ZBGridContext.h: interface for the ZBGridContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBGRIDCONTEXT_H__1D494B90_AB73_458B_B112_7207FC9ABC49__INCLUDED_)
#define AFX_ZBGRIDCONTEXT_H__1D494B90_AB73_458B_B112_7207FC9ABC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZBGridContext
{
public:

    ZBGridContext();
    virtual ~ZBGridContext();

    bool SelectionCoverMultipleCells() const
    {
        return ( m_CurSelStart != m_CurSelEnd ) ? true : false;
    };

    CGXRange ConvertToCGXRange()
    {
        return ( SelectionCoverMultipleCells() ) ?
                    CGXRange( m_CurSelStart.y, m_CurSelStart.x, m_CurSelEnd.y, m_CurSelEnd.x ) :
                    CGXRange( m_CurSelStart.y, m_CurSelStart.x );
    }

    void ConvertToCGXRange( CGXRange& range )
    {
        if ( SelectionCoverMultipleCells() )
        {
            range.SetCells( m_CurSelStart.y, m_CurSelStart.x, m_CurSelEnd.y, m_CurSelEnd.x );
        }
        else
        {
            range.SetCells( m_CurSelStart.y, m_CurSelStart.x );
        }
    }

    //////////////////////////////////////////////////////////////////////
    // Get current selection methods
    void GetCurSel( CPoint& pt );
    void GetCurSel( int& x, int& y );
    void GetCurSel( CRect& rc );
    void GetCurSel( int& left, int& top, int& right, int& bottom );

    //////////////////////////////////////////////////////////////////////
    // Set current selection methods
    void SetCurSel( CPoint& pt );
    void SetCurSel( int x, int y );
    void SetCurSel( CRect& rc );
    void SetCurSel( int left, int top, int right, int bottom );

    //////////////////////////////////////////////////////////////////////
    // Get current selection size methods
    void GetCurSelSize( CSize& sz );
    void GetCurSelSize( int& width, int& height );

    //////////////////////////////////////////////////////////////////////
    // Set current selection size methods
    void SetCurSelSize( CSize& sz );
    void SetCurSelSize( int width, int height );

    //////////////////////////////////////////////////////////////////////
    // Move selection methods
    void Offset( CPoint& pt );
    void Offset( int x, int y );
    void Right( size_t Inc = 1 );
    void Left( size_t Inc = 1 );
    void Down( size_t Inc = 1 );
    void Up( size_t Inc = 1 );
    void TopLeft();
    void TopLeft( CSize& sz );
    void TopLeft( int width, int height );
    void HomeLeft();
    void HomeTop();

// Start and End selection CPoint are public.
// It gives an easier and faster access.
public:

    CPoint    m_CurSelStart;
    CPoint    m_CurSelEnd;

private:

    // We provide two different functions for the same usage
    // To be fast we avoid passing reference parameter to the function
    // we directly use the right member
    void NormalizeStartPoint();
    void NormalizeEndPoint();
};

inline void ZBGridContext::GetCurSel( CPoint& pt )
{
    pt = m_CurSelStart;
}

inline void ZBGridContext::GetCurSel( int& x, int& y )
{
    x = m_CurSelStart.x;
    y = m_CurSelStart.y;
}

inline void ZBGridContext::GetCurSel( CRect& rc )
{
    rc.left        = m_CurSelStart.x;
    rc.top        = m_CurSelStart.y;
    rc.right    = m_CurSelEnd.x;
    rc.bottom    = m_CurSelEnd.y;
}

inline void ZBGridContext::GetCurSel( int& left, int& top, int& right, int& bottom )
{
    left    = m_CurSelStart.x;
    top        = m_CurSelStart.y;
    right    = m_CurSelEnd.x;
    bottom    = m_CurSelEnd.y;
}

inline void ZBGridContext::SetCurSel( CPoint& pt )
{
    m_CurSelStart = pt;
    NormalizeStartPoint();
}

inline void ZBGridContext::SetCurSel( int x, int y )
{
    m_CurSelStart.x = x;
    m_CurSelStart.y = y;
    NormalizeStartPoint();
}

inline void ZBGridContext::SetCurSel( CRect& rc )
{
    m_CurSelStart.x    = rc.left;
    m_CurSelStart.y    = rc.top;

    NormalizeStartPoint();

    m_CurSelEnd.x    = rc.right;
    m_CurSelEnd.y    = rc.bottom;

    NormalizeEndPoint();
}

inline void ZBGridContext::SetCurSel( int left, int top, int right, int bottom )
{
    m_CurSelStart.x    = left;
    m_CurSelStart.y    = top;

    NormalizeStartPoint();

    m_CurSelEnd.x    = right;
    m_CurSelEnd.y    = bottom;

    NormalizeEndPoint();
}

inline void ZBGridContext::GetCurSelSize( CSize& sz )
{
    sz.cx = m_CurSelEnd.x - m_CurSelStart.x;
    sz.cy = m_CurSelEnd.y - m_CurSelStart.y;
}

inline void ZBGridContext::GetCurSelSize( int& width, int& height )
{
    width = m_CurSelEnd.x - m_CurSelStart.x;
    height= m_CurSelEnd.y - m_CurSelStart.y;
}

inline void ZBGridContext::SetCurSelSize( CSize& sz )
{
    m_CurSelEnd.x = m_CurSelStart.x + sz.cx;
    m_CurSelEnd.y = m_CurSelStart.y + sz.cy;
    NormalizeEndPoint();
}

inline void ZBGridContext::SetCurSelSize( int width, int height )
{
    m_CurSelEnd.x = m_CurSelStart.x + width;
    m_CurSelEnd.y = m_CurSelStart.y + height;
    NormalizeEndPoint();
}

inline void ZBGridContext::Offset( CPoint& pt )
{
    m_CurSelStart.Offset( pt );
    NormalizeStartPoint();

    m_CurSelEnd.Offset( pt );
    NormalizeEndPoint();
}

inline void ZBGridContext::Offset( int x, int y )
{
    m_CurSelStart.Offset( x, y );
    NormalizeStartPoint();

    m_CurSelEnd.Offset( x, y );
    NormalizeEndPoint();
}

inline void ZBGridContext::Right( size_t Inc /*= 1*/ )
{
    ZBGridContext::Offset( Inc, 0 );
}

inline void ZBGridContext::Left( size_t Inc /*= 1*/ )
{
    ZBGridContext::Offset( 0 - Inc, 0 );
}

inline void ZBGridContext::Down( size_t Inc /*= 1*/ )
{
    ZBGridContext::Offset( 0, Inc );
}

inline void ZBGridContext::Up( size_t Inc /*= 1*/ )
{
    ZBGridContext::Offset( 0, 0 - Inc );
}

inline void ZBGridContext::TopLeft()
{
    ZBGridContext::SetCurSel( 1, 1, 1, 1 );
}

inline void ZBGridContext::TopLeft( CSize& sz )
{
    ZBGridContext::SetCurSel( 1, 1, 1 + sz.cx, 1 + sz.cy );
}

inline void ZBGridContext::TopLeft( int width, int height )
{
    ZBGridContext::SetCurSel( 1, 1, 1 + width, 1 + height );
}

inline void ZBGridContext::HomeLeft()
{
    m_CurSelStart.x = m_CurSelEnd.x = 1;
}

inline void ZBGridContext::HomeTop()
{
    m_CurSelStart.y = m_CurSelEnd.y = 1;
}

inline void ZBGridContext::NormalizeStartPoint()
{
    m_CurSelStart.x = __max( 1, m_CurSelStart.x );
    m_CurSelStart.y = __max( 1, m_CurSelStart.y );
}

inline void ZBGridContext::NormalizeEndPoint()
{
    m_CurSelEnd.x = __max( 1, m_CurSelEnd.x );
    m_CurSelEnd.y = __max( 1, m_CurSelEnd.y );
}

#endif // !defined(AFX_ZBGRIDCONTEXT_H__1D494B90_AB73_458B_B112_7207FC9ABC49__INCLUDED_)