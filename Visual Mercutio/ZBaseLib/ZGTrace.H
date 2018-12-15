//---------------------------------------------------------------------------
// Author    : Dominique Aigroz
// Filename  : ZGTrace.h
// Created   : october 2002
// -------------------------------------------------------------------------

#if !defined(__ZGTRACE_H)
#define __ZGTRACE_H

// If enable trace is defined
#ifdef _ENABLETRACE

#ifndef _DEBUG

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

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_API
#define AFX_EXT_API AFX_API_EXPORT
#endif

// JMR-MODIF - Le 27 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifdef __cplusplus
extern "C" {
#endif

AFX_EXT_API void ZGTrace( const PSTR ref, ... );
AFX_EXT_API void ZGTraceT( const PSTR ref, ... );

#ifdef __cplusplus
}
#endif

#ifdef TRACE
#undef TRACE
#endif

#define TRACE( xxx ) ZGTrace( xxx )

#ifdef TRACET
#undef TRACET
#endif

#define TRACET( xxx ) ZGTraceT( xxx )

#endif // Not in _DEBUG

#endif // _ENABLETRACE

#endif  // __ZGTRACE_H