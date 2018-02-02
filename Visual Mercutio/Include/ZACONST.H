//---------------------------------------------------------------------------
// Author    : Dominique Aigroz
// Filename  : zaconst.h
// Created   : 01.03.1993
//    
//      Zorgia Library        version 1.0                       
//    
//    Defines constants used in Zorgia Library modules
//
// Modifications : 18/10/1994   Aigroz D.
//                      Include portability for _WIN32 platform
//
//
// -------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  Hungarian Notation
//  ~~~~~~~~~~~~~~~~~~
//
//  This convention known as Hungarian notation is used to denote the
//  data type of the variable. The variable name begins with a lowercase
//  letter, for example lpsz is for "long pointer to a string terminated
//  by zero".
//  Hungarian notation helps you to avoid errors in your code before they
//  turn into bugs. Because the name of a variable describes both the use
//  of a variable and its data type, you are much less inclined to make
//  coding errors involving mismatched data types.
//
//  The variable name prefixes are shown in the following table:
//
//-------------------------------------------------------------------------------|
//   Prefix              Data Type                                               |
//-------------------------------------------------------------------------------|
//                                                                               |
//   c                   char                                                    |
//   by                  BYTE (unsigned char)                                    |
//   n                   number (short or int)                                   |
//   i                   int                                                     |
//   v                   void                                                    |
//   x, y                short (used as x-coordinate or y-coordinate)            |
//   cx, cy              short (used as x or y length; the c stands for "count") |
//   b                   Boolean (int)                                           |
//   w                   WORD (unsigned int)                                     |
//   l                   LONG (long)                                             |
//   dw                  DWORD (unsigned long)                                   |
//   f                   FLOAT (float)                                           |
//   fn                  function                                                |
//   s                   string                                                  |
//   sz                  string terminated by 0 byte                             |
//   h                   handle (int)                                            |
//                                                                               |
//-------------------------------------------------------------------------------|

#if !defined(__ZACONST_H)
#define __ZACONST_H

// definition of any constantes //
#define	Off	0
#define	On	1

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////
// ToBool

template<class T>
inline bool ToBool(T boolValue)
{
	return boolValue != 0;
}
#endif

// JMR-MODIF - Le 18 mai 2005 - Suppression de cet énumérateur. Il est déjà défini dans le Platform SDK.
//typedef  enum { False , True } Boolean;

// Because in 16bit, bool does not exist
#ifndef _WIN32
	#define	bool		BOOL
	#define true		TRUE
	#define false		FALSE
#endif

typedef unsigned char	BYTE;
typedef unsigned short	USHORT;
typedef short			SHORT;
typedef char			CHAR;
typedef int				INT;

//typedef unsigned int	WORD;	// already defined in Windows.h
typedef unsigned long	DWORD;

//typedef long			LONG;	// already defined in Windows.h
typedef double			DOUBLE;
typedef float			FLOAT;

// If void isn't supported, replace it by INT
#define VOID			void

// If Rogue Wave classes are not used
#if !defined(_RWTOOLSDLL) && !defined(_RTLDLL) && !defined(_RWDBDLL)
	#define LOCAL static
#endif

// If symbol for global replace it
#define GLOBAL

#undef __INCLUDE_WINDOWS_
#if defined(_WINDOWS_)
	#define __INCLUDE_WINDOWS_
#endif // _WINDOWS_
#if defined(_INC_WINDOWS)
	#define __INCLUDE_WINDOWS_
#endif // _INC_WINDOWS_

#if defined(__INCLUDE_WINDOWS_)
	#define defCOLOR_WHITE					RGB			( 255,255,255 )
	#define defCOLOR_GRAY					RGB			( 128, 128, 128 )
	#define defCOLOR_LTGRAY					RGB			( 192, 192, 192 )
	#define defCOLOR_LTLTGRAY				RGB			( 222, 222, 222 )
	#define defCOLOR_BLACK					RGB			( 0, 0, 0 )
	#define defCOLOR_RED					RGB			( 255,0,0 )
	#define defCOLOR_GREEN 					RGB			( 0,255,0 )
	#define defCOLOR_BLUE					RGB			( 0,0,255 )
	#define defCOLOR_YELLOW					RGB			( 255,255,0 )
	#define defCOLOR_LTBLUE					RGB			( 0,255,255 )
	#define defCOLOR_DEFAULT_TEXT			GetSysColor	( COLOR_WINDOWTEXT )
	#define defCOLOR_DEFAULT_BKGRND			GetSysColor	( COLOR_WINDOW )
	#define defCOLOR_DEFAULT_SELECT_TEXT	GetSysColor	( COLOR_HIGHLIGHTTEXT )
	#define defCOLOR_DEFAULT_SELECT			GetSysColor	( COLOR_HIGHLIGHT )
#endif // __INCLUDE_WINDOWS_

#define defLOGICAL_TWIPS		1440
#define defLOGICAL_TWIPSFONT	20

// Platform test Windows 32 bit applications
#if defined(_WIN32)
	#define	_fstrcpy	strcpy
	#define	_fstrcat	strcat
	#define	_fmemmove	memmove
	#define	_fmemset	memset
#else // Windows 16 bit applications
	#define	strcpy		_fstrcpy
	#define	strcat		_fstrcat
	#define	memmove		_fmemmove
	#define	memset		_fmemset
#endif // Platform test

#endif // __ZACONST_H