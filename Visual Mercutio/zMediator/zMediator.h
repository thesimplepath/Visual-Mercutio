// zMediator.h : fichier d'en-tête principal pour la DLL zMediator

#ifndef __ZMEDIATOR_H__
#define __ZMEDIATOR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error incluez 'stdafx.h' avant d'inclure ce fichier pour PCH
#endif

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment(lib,"zMediatorD.lib") 
#pragma message("Automatically linking with zMediatorD.dll")
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment(lib,"zMediator.lib") 
#pragma message("Automatically linking with zMediator.dll") 
#endif // NDEBUG
#endif // _AFXDLL

// ***********************************************************
// *
// *  zForms Resources
// *
// ***********************************************************

#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

// ***********************************************************
// *
// *  zMediator Resources
// *
// ***********************************************************

#include "zMediatorRes.h"

#endif // __ZMEDIATOR_H__