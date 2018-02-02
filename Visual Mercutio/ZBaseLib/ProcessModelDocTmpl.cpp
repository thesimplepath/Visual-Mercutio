// ProcessModelDocTmpl.cpp: implementation of the ZDProcessModelDocTmpl class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessModelDocTmpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR - MODIF - Le 16 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

IMPLEMENT_DYNAMIC( ZDProcessModelDocTmpl, ZDDocTemplateEx )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZDProcessModelDocTmpl::ZDProcessModelDocTmpl( UINT				nIDResource,
											  CRuntimeClass*	pDocClass,
											  CRuntimeClass*	pFrameClass,
											  CRuntimeClass*	pViewClass,
											  WORD				nMenuId			/*= 0*/,
											  UINT				nMaxMRU			/*= _AFX_MRU_COUNT*/ )
 : ZDDocTemplateEx( nIDResource, pDocClass, pFrameClass, pViewClass, nMenuId, nMaxMRU )
{
}

ZDProcessModelDocTmpl::~ZDProcessModelDocTmpl()
{
}
