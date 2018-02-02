//---------------------------------------------------------------------------
// Author			: Dominique Aigroz
// HeaderFile		: draw.h
// Created			: 24/1/1995
//
// Description		: Drawing functions.
//
// Modifications	:
//
// -------------------------------------------------------------------------

#if !defined(__DRAW_H)
#define __DRAW_H

// For global APIs
#ifndef AFX_API_EXPORT
	#define AFX_API_EXPORT __declspec(dllexport)
#endif

#ifndef AFX_API_IMPORT
	#define AFX_API_IMPORT __declspec(dllimport)
#endif

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_API
#define AFX_EXT_API AFX_API_IMPORT

/////////////////////////////////////////////////////////////////////////////
// Display apis

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_API
#define AFX_EXT_API AFX_API_EXPORT
#endif

// JMR-MODIF - Le 31 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef __cplusplus
extern "C" {
#endif

AFX_EXT_API void DisplayBitmap			( HBITMAP hBtm, HDC hDC, HINSTANCE hInst, INT iLeft, INT iTop );
AFX_EXT_API void DisplayBitmapFile		( const CHAR *cFile, HDC hDC, HINSTANCE hInst, INT iLeft, INT iTop );

AFX_EXT_API void DisplayBitmapFileExtent( const CHAR	*cFile,
										  HDC			hDC,
										  HINSTANCE		hInst,
										  INT			iLeft,
										  INT			iTop,
										  DWORD			dwType );

AFX_EXT_API void GetSizeOfBitmapFile	( const CHAR *cFile, HINSTANCE hInst, POINT *pt );
AFX_EXT_API void Draw3DLine				( HDC hDC, int iType, int x1, int y1, int x2, int y2 );
AFX_EXT_API void DrawEmbossRect			( HDC hDC, RECT* pRect, COLORREF BackColor );
AFX_EXT_API void DrawEngraveRect		( HDC hDC, RECT* pRect, COLORREF BackColor );

#ifdef __cplusplus
}
#endif

#endif // __DRAW_H