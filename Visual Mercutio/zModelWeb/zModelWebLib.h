// zModelWebLib.h : header file
//
// Copyright © 1993-2000 Aigroz Dominique - ProcessSoft
//		mailto:dominique.aigroz@processsoft.com
//		http://www.processsoft.com
//
//
// ==========================================================================  
// HISTORY:	
// ==========================================================================
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZMODELWEBLIB_H__
#define __ZMODELWEBLIB_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef _AFXDLL
#ifdef _DEBUG
#pragma comment( lib, "zModelWebd.lib" )
#pragma message( "Automatically linking with zModelWebd.dll" )
#endif // _DEBUG
#ifdef NDEBUG
#pragma comment( lib, "zModelWeb.lib" )
#pragma message( "Automatically linking with zModelWeb.dll" )
#endif // NDEBUG
#endif // _AFXDLL

#include "zModelWeb\zModelWebRes.h"

#endif // __ZMODELWEBLIB_H__