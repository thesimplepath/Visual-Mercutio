// ZBIOSGrid.h: interface for the ZBIOSGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBIOSGRID_H__26B4C7B9_EEFF_4CD5_B050_64634845020F__INCLUDED_)
#define AFX_ZBIOSGRID_H__26B4C7B9_EEFF_4CD5_B050_64634845020F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZBGridContext.h"

#ifdef _ZREPORTEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBIOSGrid
{
public:

    ZBIOSGrid( CGXGridCore* pGridCore = NULL );
    virtual ~ZBIOSGrid();

    CGXGridCore* GetGridCore() const
    {
        return m_pGridCore;
    };

    bool SelectionCoverMultipleCells() const
    {
        return m_GridContext.SelectionCoverMultipleCells();
    };

    CGXRange ConvertToCGXRange()
    {
        return m_GridContext.ConvertToCGXRange();
    };

    void ConvertToCGXRange( CGXRange& range )
    {
        m_GridContext.ConvertToCGXRange( range );
    };

    //////////////////////////////////////////////////////////////////////
    // Get current selection methods
    void GetCurSel( CPoint& pt )
    {
        m_GridContext.GetCurSel( pt );
    };

    void GetCurSel( int& x, int& y )
    {
        m_GridContext.GetCurSel( x, y );
    };

    void GetCurSel( CRect& rc )
    {
        m_GridContext.GetCurSel( rc );
    };

    void GetCurSel( int& left, int& top, int& right, int& bottom )
    {
        m_GridContext.GetCurSel( left, top, right, bottom );
    };

    //////////////////////////////////////////////////////////////////////
    // Set current selection methods
    void SetCurSel( CPoint& pt )
    {
        m_GridContext.SetCurSel( pt );
    };

    void SetCurSel( int x, int y )
    {
        m_GridContext.SetCurSel( x, y );
    };

    void SetCurSel( CRect& rc )
    {
        m_GridContext.SetCurSel( rc );
    };

    void SetCurSel( int left, int top, int right, int bottom )
    {
        m_GridContext.SetCurSel( left, top, right, bottom );
    };

    //////////////////////////////////////////////////////////////////////
    // Get current selection size methods
    void GetCurSelSize( CSize& sz )
    {
        m_GridContext.GetCurSelSize( sz );
    };

    void GetCurSelSize( int& width, int& height )
    {
        m_GridContext.GetCurSelSize( width, height );
    };

    //////////////////////////////////////////////////////////////////////
    // Set current selection size methods
    void SetCurSelSize( CSize& sz )
    {
        m_GridContext.SetCurSelSize( sz );
    };

    void SetCurSelSize( int width, int height )
    {
        m_GridContext.SetCurSelSize( width, height );
    };

    //////////////////////////////////////////////////////////////////////
    // Move selection methods
    void Offset( CPoint& pt )
    {
        m_GridContext.Offset( pt );
    };

    void Offset( int x, int y )
    {
        m_GridContext.Offset( x, y );
    };

    void Right( size_t Inc = 1 )
    {
        m_GridContext.Right( Inc );
    };

    void Left( size_t Inc = 1 )
    {
        m_GridContext.Left( Inc );
    };

    void Down( size_t Inc = 1 )
    {
        m_GridContext.Down( Inc );
    };

    void Up( size_t Inc = 1 )
    {
        m_GridContext.Up( Inc );
    };

    void TopLeft() 
    {
        m_GridContext.TopLeft();
    };

    void TopLeft( CSize& sz )
    {
        m_GridContext.TopLeft( sz );
    };

    void TopLeft( int width, int height )
    {
        m_GridContext.TopLeft( width, height );
    };

    void HomeLeft()
    {
        m_GridContext.HomeLeft();
    };

    void HomeTop()
    {
        m_GridContext.HomeTop();
    };

protected:

    ZBGridContext    m_GridContext;
    CGXGridCore*    m_pGridCore;
};

#endif // !defined(AFX_ZBIOSGRID_H__26B4C7B9_EEFF_4CD5_B050_64634845020F__INCLUDED_)