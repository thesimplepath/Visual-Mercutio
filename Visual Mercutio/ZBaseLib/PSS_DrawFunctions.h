/****************************************************************************
 * ==> PSS_DrawFunctions ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides several drawing functions                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DrawFunctionsH
#define PSS_DrawFunctionsH

// for global APIs
#ifndef AFX_API_EXPORT
    #define AFX_API_EXPORT __declspec(dllexport)
#endif

#ifndef AFX_API_IMPORT
    #define AFX_API_IMPORT __declspec(dllimport)
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_API
#define AFX_EXT_API AFX_API_IMPORT

// windows
#include <windows.h>

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_API
    #define AFX_EXT_API AFX_API_EXPORT
#endif

/**
* Drawing functions
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#ifdef __cplusplus
extern "C"
{
#endif
    /**
    * Shows a bitmap
    *@param hBitmap - bitmap handle to show
    *@param hDC - device context to draw to
    *@param hInstance - module instance
    *@param left - left position of the left and top image corner on the canvas, in pixels
    *@param top - top position of the left and top image corner on the canvas, in pixels
    */
    AFX_EXT_API void ShowBitmap(HBITMAP hBitmap, HDC hDC, HINSTANCE hInst, INT left, INT top);

    /**
    * Shows a bitmap from a file
    *@param pFileName - bitmap file name to show
    *@param hDC - device context to draw to
    *@param hInstance - module instance
    *@param left - left position of the left and top image corner on the canvas, in pixels
    *@param top - top position of the left and top image corner on the canvas, in pixels
    */
    AFX_EXT_API void ShowBitmapFile(const CHAR* pFileName, HDC hDC, HINSTANCE hInst, INT left, INT top);

    /**
    * Shows a bitmap file extents
    *@param pFileName - bitmap file name to show
    *@param hDC - device context to draw to
    *@param hInstance - module instance
    *@param left - left position of the left and top image corner on the canvas, in pixels
    *@param top - top position of the left and top image corner on the canvas, in pixels
    *@param type - blitting type
    */
    AFX_EXT_API void ShowBitmapFileExtent(const CHAR* pFileName,
                                          HDC         hDC,
                                          HINSTANCE   hInst,
                                          INT         left,
                                          INT         top,
                                          DWORD       type);

    /**
    * Gets the size of a bitmap contained in a file
    *@param pFileName - bitmap file name to measure
    *@param hDC - device context to draw to
    *@param hInstance - module instance
    *@param pSize - on function ends, will contain the size of the bitmap file in pixels
    */
    AFX_EXT_API void GetSizeOfBitmapFile(const CHAR* pFileName, HINSTANCE hInst, SIZE* pSize);

    /**
    * Draws a 3d line
    *@param hDC - device context to draw to
    *@param type - line type to draw
    *@param x1 - line start x position in pixels
    *@param y1 - line start y position in pixels
    *@param x2 - line end x position in pixels
    *@param y2 - line end y position in pixels
    */
    AFX_EXT_API void Draw3DLine(HDC hDC, int type, int x1, int y1, int x2, int y2);

    /**
    * Draws an embossed rect
    *@param hDC - device context to draw to
    *@param pRect - embossed rect to draw in pixels
    *@param backColor - background color to use
    */
    AFX_EXT_API void DrawEmbossRect(HDC hDC, RECT* pRect, COLORREF backColor);

    /**
    * Draws an engraved rect
    *@param hDC - device context to draw to
    *@param pRect - embossed rect to draw in pixels
    *@param backColor - background color to use
    */
    AFX_EXT_API void DrawEngraveRect(HDC hDC, RECT* pRect, COLORREF backColor);
#ifdef __cplusplus
}
#endif

#endif
