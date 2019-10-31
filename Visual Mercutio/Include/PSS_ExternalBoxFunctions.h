/****************************************************************************
 * ==> PSS_ExternalBoxFunctions --------------------------------------------*
 ****************************************************************************
 * Description : External box functions                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExternalBoxFunctionsH
#define PSS_ExternalBoxFunctionsH

 // mfc
#include <afxwin.h>

// processsoft
#include "PSS_Constants.h"

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