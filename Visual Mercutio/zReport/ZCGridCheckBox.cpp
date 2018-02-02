// ZCGridCheckBox.cpp: implementation of the ZCGridCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZCGridCheckBox.h"

#include "zReportRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZCGridCheckBox::ZCGridCheckBox( CGXGridCore* pGrid )
	: CGXCheckBox( pGrid, TRUE, IDB_CHECK_GRID, IDB_CHECK_GRID )
{
	// size of a checkbox
	m_nCheckBoxSize = 16;
}

ZCGridCheckBox::~ZCGridCheckBox()
{
}

// Override GetColorValue to ajust colors in the bitmap with system colors
COLORREF ZCGridCheckBox::GetColorValue( COLORREF rgb, BOOL bPrint )
{
	switch ( rgb )
	{
		case RGB( 255, 255, 255 ):
		{
			// Replace the white color in the bitmap with the background color of the window
			return bPrint ? RGB( 255, 255, 255 ) : GetSysColor( COLOR_WINDOW );
		}

		default:
		{
			return rgb;
		}
	}
}
