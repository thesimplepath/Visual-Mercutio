// ZUGUID.cpp: implementation of the ZUGUID class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUGUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 11 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Constant definition
const char gGUIDcheck[] = _T( "_:[v0]" );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUGUID::ZUGUID()
{
}

ZUGUID::~ZUGUID()
{
}

CString ZUGUID::CreateNewGUID()
{
	GUID	guid;
	CString	sGUID;

	HRESULT Result = CoCreateGuid( &guid );

	if ( Result == S_OK )
	{
		sGUID.Format( _T( "%s%d-%d" ), gGUIDcheck, guid.Data1, guid.Data2 );
	}
	else
	{
		sGUID.Empty();
	}

	return sGUID;
}

bool ZUGUID::GUIDIsValid( const CString s )
{
	return ( s.Left( strlen( gGUIDcheck ) ) == gGUIDcheck ) ? true : false;
}
