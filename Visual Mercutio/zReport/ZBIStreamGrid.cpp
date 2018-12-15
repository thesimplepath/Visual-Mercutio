// ZBIStreamGrid.cpp: implementation of the ZBIStreamGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBIStreamGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBIStreamGrid::ZBIStreamGrid( CGXGridCore* pGridCore /*= NULL*/ )
    : ZBIOSGrid( pGridCore )
{
}

ZBIStreamGrid::~ZBIStreamGrid()
{
}
