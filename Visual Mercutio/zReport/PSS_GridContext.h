/****************************************************************************
 * ==> PSS_GridContext -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid context                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridContextH
#define PSS_GridContextH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Grid context
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_GridContext
{
    public:
        CPoint m_CurSelStart;
        CPoint m_CurSelEnd;

        PSS_GridContext();
        virtual ~PSS_GridContext();

        /**
        * Checks if the selection covers mutiple cells
        *@return true if the selection covers mutiple cells, otherwise false
        */
        virtual inline bool SelectionCoverMultipleCells() const;

        /**
        * Converts the current x and y position to CGX range
        *@return the CGX range
        */
        virtual inline CGXRange ConvertToCGXRange() const;

        /**
        * Converts the current x and y position to CGX range
        *@param[out] range - the CGX range which will contain the result
        */
        virtual inline void ConvertToCGXRange(CGXRange& range) const;

        /**
        * Gets the current selection
        *@param[out] point - the point to fill with the current selection
        */
        virtual inline void GetCurSel(CPoint& point) const;

        /**
        * Gets the current selection
        *@param[out] x - the selection x position
        *@param[out] y - the selection y position
        */
        virtual inline void GetCurSel(int& x, int& y) const;

        /**
        * Gets the current selection
        *@param[out] rect - the rectangle surrounding the selection
        */
        virtual inline void GetCurSel(CRect& rect) const;

        /**
        * Gets the current selection
        *@param[out] left - the rectangle left position surrounding the selection
        *@param[out] top - the rectangle top position surrounding the selection
        *@param[out] right - the rectangle right position surrounding the selection
        *@param[out] bottom - the rectangle bottom position surrounding the selection
        */
        virtual inline void GetCurSel(int& left, int& top, int& right, int& bottom) const;

        /**
        * Sets the current selection
        *@param point - the current selection point
        */
        virtual inline void SetCurSel(const CPoint& point);

        /**
        * Sets the current selection
        *@param x - the current selection x position
        *@param y - the current selection y position
        */
        virtual inline void SetCurSel(int x, int y);

        /**
        * Sets the current selection
        *@param rect - the selection rectangle
        */
        virtual inline void SetCurSel(const CRect& rect);

        /**
        * Sets the current selection
        *@param left - the rectangle left position surrounding the selection
        *@param top - the rectangle top position surrounding the selection
        *@param right - the rectangle right position surrounding the selection
        *@param bottom - the rectangle bottom position surrounding the selection
        */
        virtual inline void SetCurSel(int left, int top, int right, int bottom);

        /**
        * Gets the current selection size
        *@param[out] size - the current selection size
        */
        virtual inline void GetCurSelSize(CSize& size) const;

        /**
        * Gets the current selection size
        *@param[out] width - the current selection width
        *@param[out] height - the current selection height
        */
        virtual inline void GetCurSelSize(int& width, int& height) const;

        /**
        * Sets the current selection size
        *@param size - the current selection size
        */
        virtual inline void SetCurSelSize(const CSize& size);

        /**
        * Sets the current selection size
        *@param width - the current selection width
        *@param height - the current selection height
        */
        virtual inline void SetCurSelSize(int width, int height);

        /**
        * Offsets the selection
        *@param point - the point containing the x and y offsets
        */
        virtual inline void Offset(const CPoint& point);

        /**
        * Offsets the selection
        *@param x - the x offset
        *@param y - the y offset
        */
        virtual inline void Offset(int x, int y);

        /**
        * Moves the selection to the left
        *@param inc - the move increment value
        */
        virtual inline void Left(std::size_t inc = 1);

        /**
        * Moves the selection to the right
        *@param inc - the move increment value
        */
        virtual inline void Right(std::size_t inc = 1);

        /**
        * Moves the selection to the up
        *@param inc - the move increment value
        */
        virtual inline void Up(std::size_t inc = 1);

        /**
        * Moves the selection to the down
        *@param inc - the move increment value
        */
        virtual inline void Down(std::size_t inc = 1);

        /**
        * Moves the selection to the top and left
        */
        virtual inline void TopLeft();

        /**
        * Moves the selection to the top and left
        *@param size - the selection size
        */
        virtual inline void TopLeft(const CSize& size);

        /**
        * Moves the selection to the top and left
        *@param width - the selection width
        *@param height - the selection height
        */
        virtual inline void TopLeft(int width, int height);

        /**
        * Moves the selection to the first left position
        */
        virtual inline void HomeLeft();

        /**
        * Moves the selection to the first top position
        */
        virtual inline void HomeTop();

    private:
        /**
        * Normalizes the start point
        */
        inline void NormalizeStartPoint();

        /**
        * Normalizes the end point
        */
        inline void NormalizeEndPoint();
};

//---------------------------------------------------------------------------
// PSS_GridContext
//---------------------------------------------------------------------------
bool PSS_GridContext::SelectionCoverMultipleCells() const
{
    return (m_CurSelStart != m_CurSelEnd);
}
//---------------------------------------------------------------------------
CGXRange PSS_GridContext::ConvertToCGXRange() const
{
    return (SelectionCoverMultipleCells()                                            ?
            CGXRange(m_CurSelStart.y, m_CurSelStart.x, m_CurSelEnd.y, m_CurSelEnd.x) :
            CGXRange(m_CurSelStart.y, m_CurSelStart.x));
}
//---------------------------------------------------------------------------
void PSS_GridContext::ConvertToCGXRange(CGXRange& range) const
{
    if (SelectionCoverMultipleCells())
        range.SetCells(m_CurSelStart.y, m_CurSelStart.x, m_CurSelEnd.y, m_CurSelEnd.x);
    else
        range.SetCells(m_CurSelStart.y, m_CurSelStart.x);
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSel(CPoint& point) const
{
    point = m_CurSelStart;
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSel(int& x, int& y) const
{
    x = m_CurSelStart.x;
    y = m_CurSelStart.y;
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSel(CRect& rect) const
{
    rect.left   = m_CurSelStart.x;
    rect.top    = m_CurSelStart.y;
    rect.right  = m_CurSelEnd.x;
    rect.bottom = m_CurSelEnd.y;
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSel(int& left, int& top, int& right, int& bottom) const
{
    left   = m_CurSelStart.x;
    top    = m_CurSelStart.y;
    right  = m_CurSelEnd.x;
    bottom = m_CurSelEnd.y;
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSel(const CPoint& point)
{
    m_CurSelStart = point;
    NormalizeStartPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSel(int x, int y)
{
    m_CurSelStart.x = x;
    m_CurSelStart.y = y;
    NormalizeStartPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSel(const CRect& rect)
{
    m_CurSelStart.x = rect.left;
    m_CurSelStart.y = rect.top;

    NormalizeStartPoint();

    m_CurSelEnd.x = rect.right;
    m_CurSelEnd.y = rect.bottom;

    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSel(int left, int top, int right, int bottom)
{
    m_CurSelStart.x = left;
    m_CurSelStart.y = top;

    NormalizeStartPoint();

    m_CurSelEnd.x = right;
    m_CurSelEnd.y = bottom;

    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSelSize(CSize& size) const
{
    size.cx = m_CurSelEnd.x - m_CurSelStart.x;
    size.cy = m_CurSelEnd.y - m_CurSelStart.y;
}
//---------------------------------------------------------------------------
void PSS_GridContext::GetCurSelSize(int& width, int& height) const
{
    width  = m_CurSelEnd.x - m_CurSelStart.x;
    height = m_CurSelEnd.y - m_CurSelStart.y;
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSelSize(const CSize& size)
{
    m_CurSelEnd.x = m_CurSelStart.x + size.cx;
    m_CurSelEnd.y = m_CurSelStart.y + size.cy;
    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::SetCurSelSize(int width, int height)
{
    m_CurSelEnd.x = m_CurSelStart.x + width;
    m_CurSelEnd.y = m_CurSelStart.y + height;
    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::Offset(const CPoint& point)
{
    m_CurSelStart.Offset(point);
    NormalizeStartPoint();

    m_CurSelEnd.Offset(point);
    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::Offset(int x, int y)
{
    m_CurSelStart.Offset(x, y);
    NormalizeStartPoint();

    m_CurSelEnd.Offset(x, y);
    NormalizeEndPoint();
}
//---------------------------------------------------------------------------
void PSS_GridContext::Left(std::size_t inc)
{
    Offset(0 - inc, 0);
}
//---------------------------------------------------------------------------
void PSS_GridContext::Right(std::size_t inc)
{
    Offset(inc, 0);
}
//---------------------------------------------------------------------------
void PSS_GridContext::Up(std::size_t inc)
{
    Offset(0, 0 - inc);
}
//---------------------------------------------------------------------------
void PSS_GridContext::Down(std::size_t inc)
{
    Offset(0, inc);
}
//---------------------------------------------------------------------------
void PSS_GridContext::TopLeft()
{
    SetCurSel(1, 1, 1, 1);
}
//---------------------------------------------------------------------------
void PSS_GridContext::TopLeft(const CSize& size)
{
    SetCurSel(1, 1, 1 + size.cx, 1 + size.cy);
}
//---------------------------------------------------------------------------
void PSS_GridContext::TopLeft(int width, int height)
{
    SetCurSel(1, 1, 1 + width, 1 + height);
}
//---------------------------------------------------------------------------
void PSS_GridContext::HomeLeft()
{
    m_CurSelStart.x = m_CurSelEnd.x = 1;
}
//---------------------------------------------------------------------------
void PSS_GridContext::HomeTop()
{
    m_CurSelStart.y = m_CurSelEnd.y = 1;
}
//---------------------------------------------------------------------------
void PSS_GridContext::NormalizeStartPoint()
{
    m_CurSelStart.x = __max(1, m_CurSelStart.x);
    m_CurSelStart.y = __max(1, m_CurSelStart.y);
}
//---------------------------------------------------------------------------
void PSS_GridContext::NormalizeEndPoint()
{
    m_CurSelEnd.x = __max(1, m_CurSelEnd.x);
    m_CurSelEnd.y = __max(1, m_CurSelEnd.y);
}
//---------------------------------------------------------------------------

#endif
