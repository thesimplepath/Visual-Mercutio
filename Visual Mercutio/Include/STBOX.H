//---------------------------------------------------------------------------
// Author    : Dominique Aigroz            
// HeaderFile: stbox.h
// Created   : 06.05.1994
// Modify    :           
//
//
// Call      : 
//
//---------------------------------------------------------------------------

#if !defined(__STBOX_H)
#define __STBOX_H

#include "zaconst.h"
#include <afxwin.h>				// MFC core and standard components

#define	NUMBER_OF_ICON	7

extern	HINSTANCE		hInstanceOfDLL;

#ifdef __cplusplus
extern "C" {	/* Assume C declarations for C++ */
#endif			/* __cplusplus */

void FAR PASCAL DisplayAnimatedBox	( HINSTANCE hInstance, LPSTR cpCommentary, LPSTR cpVersion );
void FAR PASCAL DisplaySupportBox	( HINSTANCE hInstance, HWND hWndOwner );
void FAR PASCAL ClearAnimatedBox	();
void FAR PASCAL DisplayAboutBox		( HINSTANCE		hInstance,
									  HWND			hWndOwner,
									  const char*	sName,
									  const char*	sSociety,
									  const char*	sSerialNumber,
									  const char*	sVersion );
BOOL CALLBACK EXPORT AboutWndProc	( HWND hwnd, UINT message, WORD wParam, LONG lParam );

#ifdef __cplusplus
}		/* End of extern "C" { */
#endif	/* __cplusplus */

#endif // __STBOX_H