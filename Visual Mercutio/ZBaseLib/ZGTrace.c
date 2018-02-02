//---------------------------------------------------------------------------
// Author    : Dominique Aigroz
// Filename  : ZGTrace.c
// Created   : october 2002
// -------------------------------------------------------------------------

// JMR-MODIF - Le 25 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// If enable trace is defined
#ifdef _ENABLETRACE

#ifndef _DEBUG

#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winnt.h>
#include <assert.h>
#include <crtdbg.h>

#include "ZAConst.h"
#include "ZGTrace.h"

void ZGTrace( const PSTR ref, ... )
{
}

void ZGTraceT( const PSTR ref, ... )
{
}

#endif

#endif // _ENABLETRACE
