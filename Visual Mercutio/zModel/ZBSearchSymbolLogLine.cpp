// ZBSearchSymbolLogLine.cpp: implementation of the ZBSearchSymbolLogLine class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSearchSymbolLogLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSearchSymbolLogLine::ZBSearchSymbolLogLine()
{
}

ZBSearchSymbolLogLine::ZBSearchSymbolLogLine( const CString symbolname,
											  const CString symbolpath,
											  const CString message		/*= ""*/ )
	: ZBGenericSymbolErrorLine( message, symbolname, symbolpath, -1, 2 )
{
}

ZBSearchSymbolLogLine::ZBSearchSymbolLogLine( const CString	symbolname,
											  const CString	symbolpath,
											  UINT			nIDSmessage )
	: ZBGenericSymbolErrorLine( nIDSmessage, symbolname, symbolpath, -1, 2 )
{
}

ZBSearchSymbolLogLine::~ZBSearchSymbolLogLine()
{
}
