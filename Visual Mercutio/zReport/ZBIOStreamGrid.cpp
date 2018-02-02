// ZBIOStreamGrid.cpp: implementation of the ZBIOStreamGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBIOStreamGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBIOStreamGrid::ZBIOStreamGrid( CGXGridCore* pGridCore /*= NULL*/ )
	: ZBIStreamGrid( pGridCore ),
	  ZBOStreamGrid( pGridCore )
{
}

ZBIOStreamGrid::~ZBIOStreamGrid()
{
}
