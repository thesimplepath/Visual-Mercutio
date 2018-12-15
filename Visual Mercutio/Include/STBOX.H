/****************************************************************************
 * ==> Stbox ---------------------------------------------------------------*
 ****************************************************************************
 * Description : stBox DLL functions                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef StdboxH
#define StdboxH

// visual mercutio
#include "zaconst.h"

// mfc
#include <afxwin.h>

#define NUMBER_OF_ICON 7

extern HINSTANCE hInstanceOfDLL;

#ifdef __cplusplus
    extern "C"
    {
#endif
    void FAR PASCAL DisplayAnimatedBox(HINSTANCE hInstance, LPSTR cpCommentary, LPSTR cpVersion);
    void FAR PASCAL DisplaySupportBox (HINSTANCE hInstance, HWND  hWndOwner);
    void FAR PASCAL ClearAnimatedBox  ();
    void FAR PASCAL DisplayAboutBox   (HINSTANCE   hInstance,
                                       HWND        hWndOwner,
                                       const char* sName,
                                       const char* sSociety,
                                       const char* sSerialNumber,
                                       const char* sVersion );
    BOOL CALLBACK EXPORT AboutWndProc (HWND hwnd, UINT message, WORD wParam, LONG lParam);
#ifdef __cplusplus
    }
#endif

#endif