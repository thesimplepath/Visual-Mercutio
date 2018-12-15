// ZBGridContext.cpp: implementation of the ZBGridContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBGridContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBGridContext::ZBGridContext()
    : m_CurSelStart    ( 1, 1 ),
      m_CurSelEnd    ( 1, 1 )
{
}

ZBGridContext::~ZBGridContext()
{
}
