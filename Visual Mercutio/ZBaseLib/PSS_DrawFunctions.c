/****************************************************************************
 * ==> PSS_DrawFunctions ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides several drawing functions                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "PSS_DrawFunctions.h"

// std
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// windows
#include <assert.h>

// processsoft
#include "ZAConst.h"

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static char    g_OldFileName[_MAX_FNAME];
static HBITMAP g_hOldBm;
static BITMAP  g_OldBm;
//---------------------------------------------------------------------------
// Draw functions
//---------------------------------------------------------------------------
void ShowBitmap(HBITMAP hBitmap, HDC hDC, HINSTANCE hInst, INT left, INT top)
{
    HDC     hDCMem;
    HBITMAP hOldBitmap;
    BITMAP  bm;
    POINT   ptSize, ptOrigin;

    hDCMem = CreateCompatibleDC(hDC);

    SetMapMode(hDCMem, GetMapMode(hDC));
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    ptSize.x   = bm.bmWidth;
    ptSize.y   = bm.bmHeight;
    ptOrigin.x = 0;
    ptOrigin.y = 0;

    DPtoLP(hDCMem, &ptOrigin, 1);

    hOldBitmap = SelectObject(hDCMem, hBitmap);

    BitBlt(hDC, left, top, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, SRCCOPY);
    SelectObject(hDCMem, hOldBitmap);

    DeleteObject(hOldBitmap);
    DeleteDC(hDCMem);
}
//---------------------------------------------------------------------------
void ShowBitmapFile(const CHAR* pFileName, HDC hDC, HINSTANCE hInst, INT left, INT top)
{
    HDC     hDCMem;
    HBITMAP hBtm, hOldBitmap;
    BITMAP  bm;
    POINT   ptSize, ptOrigin;

    assert(pFileName);

    hDCMem = CreateCompatibleDC(hDC);
    SetMapMode(hDCMem, GetMapMode(hDC));

    hBtm = LoadBitmap(hInst, pFileName);
    GetObject(hBtm, sizeof(BITMAP), &bm);

    ptSize.x   = bm.bmWidth;
    ptSize.y   = bm.bmHeight;
    ptOrigin.x = 0;
    ptOrigin.y = 0;

    DPtoLP(hDCMem, &ptOrigin, 1);

    hOldBitmap = SelectObject(hDCMem, hBtm);
    BitBlt(hDC, left, top, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, SRCCOPY);
    SelectObject(hDCMem, hOldBitmap);

    DeleteObject(hBtm);
    DeleteObject(hOldBitmap);
    DeleteDC(hDCMem);
}
//---------------------------------------------------------------------------
void ShowBitmapFileExtent(const CHAR* pFileName,
                          HDC         hDC,
                          HINSTANCE   hInst,
                          INT         left,
                          INT         top,
                          DWORD       type)
{
    HDC     hDCMem;
    HBITMAP hBtm, hOldBitmap;
    BITMAP  bm;
    POINT   ptSize, ptOrigin;

    assert(pFileName);

    hDCMem = CreateCompatibleDC(hDC);
    SetMapMode(hDCMem, GetMapMode(hDC));

    hBtm = LoadBitmap(hInst, pFileName);
    GetObject(hBtm, sizeof(BITMAP), &bm);

    ptSize.x   = bm.bmWidth;
    ptSize.y   = bm.bmHeight;
    ptOrigin.x = 0;
    ptOrigin.y = 0;

    DPtoLP(hDCMem, &ptOrigin, 1);

    hOldBitmap = SelectObject(hDCMem, hBtm);

    BitBlt(hDC, left, top, ptSize.x, ptSize.y, hDCMem, ptOrigin.x, ptOrigin.y, type);
    SelectObject(hDCMem, hOldBitmap);

    DeleteObject(hBtm);
    DeleteObject(hOldBitmap);
    DeleteDC(hDCMem);
}
//---------------------------------------------------------------------------
void GetSizeOfBitmapFile(const CHAR* pFileName, HINSTANCE hInst, SIZE* pSize)
{
    assert(pFileName);

    g_hOldBm = LoadBitmap(hInst, pFileName);
    GetObject(g_hOldBm, sizeof(BITMAP), &g_OldBm);

    pSize->cx = g_OldBm.bmWidth;
    pSize->cy = g_OldBm.bmHeight;

    DeleteObject(g_hOldBm);
}
//---------------------------------------------------------------------------
void Draw3DLine(HDC hDC, int type, int x1, int y1, int x2, int y2)
{
    HPEN hPen1   = CreatePen(PS_SOLID, 1, defCOLOR_GRAY);
    HPEN hPen2   = CreatePen(PS_SOLID, 1, defCOLOR_WHITE);
    HPEN hOldPen = SelectObject(hDC, hPen1);

    #ifndef _WIN32
        MoveTo(hDC, x1, y1);
    #else
        MoveToEx(hDC, x1, y1, NULL);
    #endif

    LineTo(hDC, x2, y2);
    SelectObject(hDC, hPen2);

    #ifndef _WIN32
        MoveTo(hDC, x1, y1 + 1);
    #else
        MoveToEx(hDC, x1, y1 + 1, NULL);
    #endif

    LineTo(hDC, x2, y2 + 1);
    SelectObject(hDC, hOldPen);
    DeleteObject(hPen1);
    DeleteObject(hPen2);
}
//---------------------------------------------------------------------------
void DrawEmbossRect(HDC hDC, RECT* pRect, COLORREF backColor)
{
    HPEN   hWhitePen = CreatePen(PS_SOLID, 1, defCOLOR_WHITE);
    HPEN   hBlackPen = CreatePen(PS_SOLID, 1, defCOLOR_BLACK);
    HBRUSH hBrush    = CreateSolidBrush(backColor);
    HPEN   hOldPen   = SelectObject(hDC, hWhitePen);

    // fill the area with the back color
    FillRect(hDC, pRect, hBrush);

    #ifndef _WIN32
        MoveTo(hDC, pRect->right, pRect->top);
        LineTo(hDC, pRect->left,  pRect->top);
        LineTo(hDC, pRect->left,  pRect->bottom);
    #else
        MoveToEx(hDC, pRect->right, pRect->top, NULL);
        LineTo  (hDC, pRect->left,  pRect->top);
        LineTo  (hDC, pRect->left,  pRect->bottom);
    #endif

    SelectObject(hDC, hBlackPen);

    #ifndef _WIN32
        MoveTo(hDC, pRect->right, pRect->top);
        LineTo(hDC, pRect->right, pRect->bottom);
        LineTo(hDC, pRect->left,  pRect->bottom);
    #else
        MoveToEx(hDC, pRect->right, pRect->top, NULL);
        LineTo  (hDC, pRect->right, pRect->bottom);
        LineTo  (hDC, pRect->left,  pRect->bottom);
    #endif

    SelectObject(hDC, hOldPen);
    DeleteObject(hWhitePen);
    DeleteObject(hBlackPen);
    DeleteObject(hBrush);
}
//---------------------------------------------------------------------------
void DrawEngraveRect(HDC hDC, RECT* pRect, COLORREF backColor)
{
    HPEN   hWhitePen = CreatePen(PS_SOLID, 1, defCOLOR_WHITE);
    HPEN   hBlackPen = CreatePen(PS_SOLID, 1, defCOLOR_BLACK);
    HBRUSH hBrush    = CreateSolidBrush(backColor);
    HPEN   hOldPen   = SelectObject(hDC, hBlackPen);

    // fill the area with the back color
    FillRect(hDC, pRect, hBrush);

    #ifndef _WIN32
        MoveTo(hDC, pRect->right, pRect->top);
        LineTo(hDC, pRect->left,  pRect->top);
        LineTo(hDC, pRect->left,  pRect->bottom);
    #else
        MoveToEx(hDC, pRect->right, pRect->top, NULL);
        LineTo  (hDC, pRect->left,  pRect->top);
        LineTo  (hDC, pRect->left,  pRect->bottom);
    #endif

    SelectObject(hDC, hWhitePen);

    #ifndef _WIN32
        MoveTo(hDC, pRect->right, pRect->top);
        LineTo(hDC, pRect->right, pRect->bottom);
        LineTo(hDC, pRect->left,  pRect->bottom);
    #else
        MoveToEx(hDC, pRect->right, pRect->top, NULL);
        LineTo  (hDC, pRect->right, pRect->bottom);
        LineTo  (hDC, pRect->left,  pRect->bottom);
    #endif

    SelectObject(hDC, hOldPen);
    DeleteObject(hWhitePen);
    DeleteObject(hBlackPen);
    DeleteObject(hBrush);
}
//---------------------------------------------------------------------------
