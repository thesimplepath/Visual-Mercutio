// -------------------------------------------------------------------------
// Author            : Aigroz Dominique
// Filename            : draw.c
// Created            : 24/1/1995
// Description        : Drawing functions.
//
// Modifications    :
//
// -------------------------------------------------------------------------

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "ZAConst.h"
#include "draw.h"

// JMR-MODIF - Le 31 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// static variable ------------------------------------------------------------
static char        szOldFileName[_MAX_FNAME];
static HBITMAP    mhOldBtm;
static BITMAP    mOldbm;

VOID DisplayBitmap( HBITMAP hBtm, HDC hDC, HINSTANCE hInst, INT iLeft, INT iTop )
{
    HDC        hDCMem;
    HBITMAP    hOldBitmap;
    BITMAP    bm;
    POINT    ptSize, ptOrigin;

    hDCMem        = CreateCompatibleDC ( hDC );

    SetMapMode( hDCMem, GetMapMode ( hDC ) );
    GetObject( hBtm, sizeof (BITMAP), &bm );

    ptSize.x    = bm.bmWidth;
    ptSize.y    = bm.bmHeight;
    ptOrigin.x    = 0;
    ptOrigin.y    = 0;

    DPtoLP( hDCMem, &ptOrigin, 1 );

    hOldBitmap    = SelectObject ( hDCMem, hBtm );

    BitBlt( hDC, iLeft, iTop, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, SRCCOPY );
    SelectObject( hDCMem, hOldBitmap );

    DeleteObject( hOldBitmap );
    DeleteDC( hDCMem );
}

// DisplayBitmapFileExtent ---------------------------------------------------
//
//  Programmer:        Aigroz Dominique, DOA
//  
//  Description:    Display a Bitmap file.
//  
//  Parameters:        cFile    The bitmap file
//                    hDC        The handle of the DC
//                    hInst    The instance of the application
//                    iLeft    The left side from where the bitmap is painted
//                    iTop    The top  side from where the bitmap is painted
//                    dwType    Specifies the raster operation to be performed
//  
//  Returns:        Nothing.
//  
//  Revisions:
//  
VOID DisplayBitmapFileExtent( const CHAR *cFile, HDC hDC, HINSTANCE hInst, INT iLeft, INT iTop, DWORD dwType )
{

    HDC        hDCMem;
    HBITMAP    hBtm, hOldBitmap;
    BITMAP    bm;
    POINT    ptSize, ptOrigin;

    assert( cFile );

    hDCMem        = CreateCompatibleDC ( hDC );
    SetMapMode( hDCMem, GetMapMode ( hDC ) );

    hBtm        = LoadBitmap ( hInst, cFile );
    GetObject( hBtm, sizeof (BITMAP), &bm );

    ptSize.x    = bm.bmWidth;
    ptSize.y    = bm.bmHeight;
    ptOrigin.x    = 0;
    ptOrigin.y    = 0;

    DPtoLP ( hDCMem, &ptOrigin, 1 );

    hOldBitmap    = SelectObject ( hDCMem, hBtm );

    BitBlt( hDC, iLeft, iTop, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, dwType );
    SelectObject( hDCMem, hOldBitmap );

    DeleteObject( hBtm );
    DeleteObject( hOldBitmap );
    DeleteDC( hDCMem );
}

// DisplayBitmapFile ---------------------------------------------------------
//
//  Programmer:        Aigroz Dominique, DOA
//  
//  Description:    Display a Bitmap file.
//  
//  Parameters:        cFile    The bitmap file
//                    hDC        The handle of the DC
//                    hInst    The instance of the application
//                    iLeft    The left side from where the bitmap is painted
//                    iTop    The top  side from where the bitmap is painted
//  
//  Returns:        Nothing.
//  
//  Revisions:
//  
VOID DisplayBitmapFile( const CHAR *cFile, HDC hDC, HINSTANCE hInst, INT iLeft, INT iTop )
{
    HDC        hDCMem;
    HBITMAP    hBtm, hOldBitmap;
    BITMAP    bm;
    POINT    ptSize, ptOrigin;

    assert( cFile );

    hDCMem        = CreateCompatibleDC ( hDC );
    SetMapMode( hDCMem, GetMapMode ( hDC ) );

    hBtm        = LoadBitmap ( hInst, cFile );
    GetObject( hBtm, sizeof (BITMAP), &bm );

    ptSize.x    = bm.bmWidth;
    ptSize.y    = bm.bmHeight;
    ptOrigin.x    = 0;
    ptOrigin.y    = 0;

    DPtoLP( hDCMem, &ptOrigin, 1 );

    hOldBitmap    = SelectObject ( hDCMem, hBtm );
    BitBlt( hDC, iLeft, iTop, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, SRCCOPY );
    SelectObject( hDCMem, hOldBitmap );

    DeleteObject( hBtm );
    DeleteObject( hOldBitmap );
    DeleteDC( hDCMem );
}

// GetSizeOfBitmapFile -------------------------------------------------------
//
//  Programmer:        Aigroz Dominique, DOA
//  
//  Description:    Retrieve the size of a Bitmap file.
//  
//  Parameters:        cFile    The bitmap file
//                    hInst    The instance of the application
//                    *pt        The pointer of the size of the bitmap file
//  
//  Returns:        Nothing.
//  
//  Revisions:
//  
VOID GetSizeOfBitmapFile( const CHAR *cFile, HINSTANCE hInst, POINT *pt )
{
    assert( cFile );

    mhOldBtm    = LoadBitmap ( hInst, cFile );
    GetObject( mhOldBtm, sizeof (BITMAP), &mOldbm );

    pt->x        = mOldbm.bmWidth;
    pt->y        = mOldbm.bmHeight;

    DeleteObject( mhOldBtm );
}

// Draw3DLine ----------------------------------------------------------------
//
//  Programmer:        Aigroz Dominique, DOA
//  
//  Description:    Retrieve the size of a Bitmap file.
//  
//  Parameters:        cFile    The bitmap file
//                    hInst    The instance of the application
//                    *pt        The pointer of the size of the bitmap file
//  
//  Returns:        Nothing.
//  
//  Revisions:
//  
void Draw3DLine( HDC hDC, int iType, int x1, int y1, int x2, int y2 )
{
    HPEN    Pen1    = CreatePen( PS_SOLID, 1, defCOLOR_GRAY );
    HPEN    Pen2    = CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
    HPEN    OldPen    = SelectObject( hDC, Pen1 );

#ifndef _WIN32
    MoveTo( hDC, x1, y1 );
#else
    MoveToEx( hDC, x1, y1, NULL );
#endif // _WIN32

    LineTo( hDC, x2, y2 );
    SelectObject( hDC, Pen2 );

#ifndef _WIN32
    MoveTo( hDC, x1, y1 + 1 );
#else
    MoveToEx( hDC, x1, y1 + 1, NULL );
#endif // _WIN32

    LineTo( hDC, x2, y2 + 1 );
    SelectObject( hDC, OldPen );
    DeleteObject( Pen1 );
    DeleteObject( Pen2 );
}

void DrawEmbossRect( HDC hDC, RECT* pRect, COLORREF BackColor )
{
    HPEN    GrayPen        = CreatePen( PS_SOLID, 1, defCOLOR_GRAY );
    HPEN    WhitePen    = CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
    HPEN    BlackPen    = CreatePen( PS_SOLID, 1, defCOLOR_BLACK );
    HBRUSH    Brush        = CreateSolidBrush( BackColor );
    HPEN    OldPen        = SelectObject( hDC, WhitePen );

    // Fill the area with the back color
    FillRect( hDC, pRect, Brush );

#ifndef _WIN32
    MoveTo( hDC, pRect->right, pRect->top );
    LineTo( hDC, pRect->left,  pRect->top );
    LineTo( hDC, pRect->left,  pRect->bottom );
#else
    MoveToEx( hDC, pRect->right, pRect->top, NULL );
    LineTo( hDC, pRect->left, pRect->top );
    LineTo( hDC, pRect->left, pRect->bottom );
#endif // _WIN32

    SelectObject( hDC, BlackPen );

#ifndef _WIN32
    MoveTo( hDC, pRect->right, pRect->top );
    LineTo( hDC, pRect->right, pRect->bottom );
    LineTo( hDC, pRect->left,  pRect->bottom );
#else
    MoveToEx( hDC, pRect->right, pRect->top, NULL );
    LineTo( hDC, pRect->right, pRect->bottom );
    LineTo( hDC, pRect->left, pRect->bottom );
#endif // _WIN32

    SelectObject( hDC, OldPen );
    DeleteObject( GrayPen );
    DeleteObject( WhitePen );
    DeleteObject( BlackPen );
    DeleteObject( Brush );
}

void DrawEngraveRect( HDC hDC, RECT* pRect, COLORREF BackColor )
{
    HPEN    GrayPen        = CreatePen( PS_SOLID, 1, defCOLOR_GRAY );
    HPEN    WhitePen    = CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
    HPEN    BlackPen    = CreatePen( PS_SOLID, 1, defCOLOR_BLACK );
    HBRUSH    Brush        = CreateSolidBrush( BackColor );
    HPEN    OldPen        = SelectObject( hDC, BlackPen );

    // Fill the area with the back color
    FillRect( hDC, pRect, Brush );

#ifndef _WIN32
    MoveTo( hDC, pRect->right, pRect->top );
    LineTo( hDC, pRect->left,  pRect->top );
    LineTo( hDC, pRect->left,  pRect->bottom );
#else
    MoveToEx( hDC, pRect->right, pRect->top, NULL );
    LineTo( hDC, pRect->left, pRect->top );
    LineTo( hDC, pRect->left, pRect->bottom );
#endif // _WIN32

    SelectObject( hDC, WhitePen );

#ifndef _WIN32
    MoveTo( hDC, pRect->right, pRect->top );
    LineTo( hDC, pRect->right, pRect->bottom );
    LineTo( hDC, pRect->left,  pRect->bottom );
#else
    MoveToEx( hDC, pRect->right, pRect->top, NULL );
    LineTo( hDC, pRect->right, pRect->bottom );
    LineTo( hDC, pRect->left, pRect->bottom );
#endif // _WIN32

    SelectObject( hDC, OldPen );
    DeleteObject( GrayPen );
    DeleteObject( WhitePen );
    DeleteObject( BlackPen );
    DeleteObject( Brush );
}
