/****************************************************************************
 * ==> PSS_IOSGrid ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic input/output stream grid                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IOSGridH
#define PSS_IOSGridH

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

// processsoft
#include "PSS_GridContext.h"

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
* Basic input/output stream grid
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_IOSGrid
{
    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_IOSGrid(CGXGridCore* pGridCore = NULL);

        virtual ~PSS_IOSGrid();

        /**
        * Gets the grid core
        *@return the grid core
        */
        virtual inline CGXGridCore* GetGridCore() const;

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
        virtual inline void GetCurSel(int& left, int& top, int& right, int& bottom);

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
        virtual inline void SetCurSel(CRect& rect);

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
        virtual inline void SetCurSelSize(CSize& size);

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

    protected:
        PSS_GridContext m_GridContext;
        CGXGridCore*    m_pGridCore;
};

//---------------------------------------------------------------------------
// PSS_IOSGrid
//---------------------------------------------------------------------------
CGXGridCore* PSS_IOSGrid::GetGridCore() const
{
    return m_pGridCore;
}
//---------------------------------------------------------------------------
bool PSS_IOSGrid::SelectionCoverMultipleCells() const
{
    return m_GridContext.SelectionCoverMultipleCells();
}
//---------------------------------------------------------------------------
CGXRange PSS_IOSGrid::ConvertToCGXRange() const
{
    return m_GridContext.ConvertToCGXRange();
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::ConvertToCGXRange(CGXRange& range) const
{
    m_GridContext.ConvertToCGXRange(range);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSel(CPoint& point) const
{
    m_GridContext.GetCurSel(point);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSel(int& x, int& y) const
{
    m_GridContext.GetCurSel(x, y);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSel(CRect& rect) const
{
    m_GridContext.GetCurSel(rect);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSel(int& left, int& top, int& right, int& bottom)
{
    m_GridContext.GetCurSel(left, top, right, bottom);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSel(const CPoint& point)
{
    m_GridContext.SetCurSel(point);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSel(int x, int y)
{
    m_GridContext.SetCurSel(x, y);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSel(CRect& rect)
{
    m_GridContext.SetCurSel(rect);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSel(int left, int top, int right, int bottom)
{
    m_GridContext.SetCurSel(left, top, right, bottom);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSelSize(CSize& size) const
{
    m_GridContext.GetCurSelSize(size);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::GetCurSelSize(int& width, int& height) const
{
    m_GridContext.GetCurSelSize(width, height);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSelSize(CSize& size)
{
    m_GridContext.SetCurSelSize(size);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::SetCurSelSize(int width, int height)
{
    m_GridContext.SetCurSelSize(width, height);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Offset(const CPoint& point)
{
    m_GridContext.Offset(point);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Offset(int x, int y)
{
    m_GridContext.Offset(x, y);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Left(std::size_t inc)
{
    m_GridContext.Left(inc);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Right(std::size_t inc)
{
    m_GridContext.Right(inc);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Up(std::size_t inc)
{
    m_GridContext.Up(inc);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::Down(std::size_t inc)
{
    m_GridContext.Down(inc);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::TopLeft()
{
    m_GridContext.TopLeft();
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::TopLeft(const CSize& size)
{
    m_GridContext.TopLeft(size);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::TopLeft(int width, int height)
{
    m_GridContext.TopLeft(width, height);
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::HomeLeft()
{
    m_GridContext.HomeLeft();
}
//---------------------------------------------------------------------------
void PSS_IOSGrid::HomeTop()
{
    m_GridContext.HomeTop();
}
//---------------------------------------------------------------------------

#endif
