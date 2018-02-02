// ZCProcessModelDocument.cpp : implementation file

#include "stdafx.h"
#include "ZCProcessModelDocument.h"

#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelDocument

IMPLEMENT_DYNCREATE( ZCProcessModelDocument, ZCProcessModelTree )

BEGIN_MESSAGE_MAP( ZCProcessModelDocument, ZCProcessModelTree )
	//{{AFX_MSG_MAP(ZCProcessModelDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCProcessModelDocument::ZCProcessModelDocument()
{
	if ( m_SymbolPopupMainMenu.GetSafeHmenu() != NULL )
	{
		m_SymbolPopupMainMenu.DestroyMenu();
	}

	if ( m_SymbolRefPopupMainMenu.GetSafeHmenu() != NULL )
	{
		m_SymbolRefPopupMainMenu.DestroyMenu();
	}

	// Load the right main menu for components
	m_SymbolPopupMainMenu.LoadMenu( IDR_NAVSYMBOL_POPUP );
	m_SymbolRefPopupMainMenu.LoadMenu( IDR_NAVSYMBOL_REF_POPUP );
}

ZCProcessModelDocument::~ZCProcessModelDocument()
{
}

void ZCProcessModelDocument::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
}
