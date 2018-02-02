//## begin module%351BDFFD00FA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%351BDFFD00FA.cm

//## begin module%351BDFFD00FA.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%351BDFFD00FA.cp

//## Module: ZIDialog%351BDFFD00FA; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZIDialog.cpp

//## begin module%351BDFFD00FA.additionalIncludes preserve=no
//## end module%351BDFFD00FA.additionalIncludes

//## begin module%351BDFFD00FA.includes preserve=yes
#include <StdAfx.h>
//## end module%351BDFFD00FA.includes

// ZIDialog
#include "ZIDialog.h"
//## begin module%351BDFFD00FA.declarations preserve=no
//## end module%351BDFFD00FA.declarations

//## begin module%351BDFFD00FA.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## end module%351BDFFD00FA.additionalDeclarations

// Class ZIDialog 

BEGIN_MESSAGE_MAP( ZIDialog, CDialog )
	//{{AFX_MSG_MAP(ZIDialog)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIDialog::ZIDialog ( UINT nIDTemplate, BOOL AutoCenter, CWnd* pParentWnd )
	: CDialog					( nIDTemplate, pParentWnd ),
	  m_bAutoCenter				( AutoCenter ),
	  m_ColorHasBeenSuperseed	( false ),
	  m_BackCol					( defCOLOR_WHITE ),
	  m_StaticCol				( defCOLOR_BLACK ),
	  m_EditCol					( defCOLOR_BLACK )
{
	// JMR-MODIF - Le 20 octobre 2005 - Initialisation des nouvelles variables.
	m_HbrClrCtlBk	= NULL;
	m_ClrCtlText	= defCOLOR_WHITE;
	m_ClrCtlBk		= defCOLOR_BLACK;
}

ZIDialog::ZIDialog ( LPCSTR lpszTemplateName, BOOL AutoCenter, CWnd* pParentWnd )
	: CDialog					( lpszTemplateName, pParentWnd ),
	  m_bAutoCenter				( AutoCenter ),
	  m_ColorHasBeenSuperseed	( false ),
	  m_BackCol					( defCOLOR_WHITE ),
	  m_StaticCol				( defCOLOR_BLACK ),
	  m_EditCol					( defCOLOR_BLACK )
{
	// JMR-MODIF - Le 20 octobre 2005 - Initialisation des nouvelles variables.
	m_HbrClrCtlBk	= NULL;
	m_ClrCtlText	= defCOLOR_WHITE;
	m_ClrCtlBk		= defCOLOR_BLACK;
}

ZIDialog::ZIDialog ( UINT		nIDTemplate,
					 BOOL		AutoCenter,
					 COLORREF	BackCol,
					 COLORREF	StaticCol,
					 COLORREF	EditCol,
					 CWnd*		pParentWnd )
	: CDialog					( nIDTemplate, pParentWnd ),
	  m_bAutoCenter				( AutoCenter ),
	  m_ColorHasBeenSuperseed	( true ),
	  m_BackCol					( BackCol ),
	  m_StaticCol				( StaticCol ),
	  m_EditCol					( EditCol )
{
	// JMR-MODIF - Le 20 octobre 2005 - Initialisation des nouvelles variables.
	m_HbrClrCtlBk	= NULL;
	m_ClrCtlText	= defCOLOR_WHITE;
	m_ClrCtlBk		= defCOLOR_BLACK;

	if ( m_BackCol == -1 && m_StaticCol == -1 && m_EditCol == -1 )
	{
		m_ColorHasBeenSuperseed = false;
	}
}

ZIDialog::ZIDialog ( LPCSTR		lpszTemplateName,
					 BOOL		AutoCenter,
					 COLORREF	BackCol,
					 COLORREF	StaticCol,
					 COLORREF	EditCol,
					 CWnd*		pParentWnd )
	: CDialog					( lpszTemplateName, pParentWnd ),
	  m_bAutoCenter				( AutoCenter ),
	  m_ColorHasBeenSuperseed	( true ),
	  m_BackCol					( BackCol ),
	  m_StaticCol				( StaticCol ),
	  m_EditCol					( EditCol )
{
	// JMR-MODIF - Le 20 octobre 2005 - Initialisation des nouvelles variables.
	m_HbrClrCtlBk	= NULL;
	m_ClrCtlText	= defCOLOR_WHITE;
	m_ClrCtlBk		= defCOLOR_BLACK;

	if ( m_BackCol == -1 && m_StaticCol == -1 && m_EditCol == -1 )
	{
		m_ColorHasBeenSuperseed = false;
	}
}

ZIDialog::~ZIDialog()
{
	// JMR-MODIF - Le 20 octobre 2005 - Ajout du code de nettoyage de la brosse.
	if( m_HbrClrCtlBk )
	{
		::DeleteObject( m_HbrClrCtlBk );
	}
}

void ZIDialog::SetBackGroundColor( COLORREF col )
{
	m_ColorHasBeenSuperseed = true;
	m_BackCol = col;
}

void ZIDialog::SetEditControlColor( COLORREF col )
{
	m_ColorHasBeenSuperseed = true;
	m_EditCol = col;
}

void ZIDialog::SetStaticControlColor( COLORREF col )
{
	m_ColorHasBeenSuperseed = true;
	m_StaticCol = col;
}

//## Other Operations (implementation)
void ZIDialog::Create ( UINT nIDTemplate, BOOL AutoCenter, CWnd* pParentWnd )
{
	//## begin ZIDialog::Create%919330579.body preserve=yes
	m_bAutoCenter = AutoCenter;
	CDialog::Create( nIDTemplate, pParentWnd );
	//## end ZIDialog::Create%919330579.body
}

void ZIDialog::Create ( LPCSTR lpszTemplateName, BOOL AutoCenter, CWnd* pParentWnd )
{
	//## begin ZIDialog::Create%919330580.body preserve=yes
	m_bAutoCenter = AutoCenter;  
	CDialog::Create( lpszTemplateName, pParentWnd );
	//## end ZIDialog::Create%919330580.body
}

void ZIDialog::Create ( UINT		nIDTemplate,
						BOOL		AutoCenter,
						COLORREF	BackCol,
						COLORREF	StaticCol,
						COLORREF	EditCol,
						CWnd*		pParentWnd )
{
	m_bAutoCenter			= AutoCenter;
	m_ColorHasBeenSuperseed	= true;
	m_BackCol				= BackCol;
	m_StaticCol				= StaticCol;
	m_EditCol				= EditCol;
	CDialog::Create( nIDTemplate, pParentWnd );
}

void ZIDialog::Create ( LPCSTR		lpszTemplateName,
						BOOL		AutoCenter,
						COLORREF	BackCol,
						COLORREF	StaticCol,
						COLORREF	EditCol,
						CWnd*		pParentWnd)
{
	m_bAutoCenter			= AutoCenter;  
	m_ColorHasBeenSuperseed	= true;
	m_BackCol				= BackCol;
	m_StaticCol				= StaticCol;
	m_EditCol				= EditCol;
	CDialog::Create( lpszTemplateName, pParentWnd );
}

// Additional Declarations
//## begin ZIDialog%351BDE69006E.declarations preserve=yes

/////////////////////////////////////////////////////////////////////////////
// ZIDialog message handlers

BOOL ZIDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if ( GetbAutoCenter() )
#ifndef _WIN32
	{
		// Put the window in the center of the screen	
		CRect	rect;
		GetClientRect( &rect );
		CRect	ClientRect;
		UINT	uiX, uiY;
		uiX = GetSystemMetrics( SM_CXFULLSCREEN );
		uiY = GetSystemMetrics( SM_CYFULLSCREEN );

		SetWindowPos( NULL,
					  ( uiX - rect.right )  / 2,
					  ( uiY - rect.bottom ) / 2,
					  0,
					  0,
					  SWP_NOZORDER | SWP_NOSIZE );
	}
#else
	{
		CenterWindow();
	}
#endif

	// Color white brush
	m_Brush.CreateSolidBrush( m_BackCol );

	// JMR-MODIF - Le 20 octobre 2005 - Gestion de la couleur de fond, remplace CWinApp::SetDialogBkColor obsolète.
	SetDialogBkColor();

	// return TRUE  unless you set the focus to a control
	return TRUE;
}

// JMR-MODIF - Le 20 octobre 2005 - Cette fonction permet de changer la couleur de fond du formulaire.
void ZIDialog::SetDialogBkColor( COLORREF clrCtlBk		/*= RGB(192, 192, 192)*/,
								 COLORREF clrCtlText	/*= RGB(0, 0, 0) */)
{
	// m_HbrClrCtlBk est à null dans le constructeur
	if( m_HbrClrCtlBk )
	{
		::DeleteObject( m_HbrClrCtlBk );
	}

	m_HbrClrCtlBk	= ::CreateSolidBrush( clrCtlBk );
	m_ClrCtlText	= clrCtlText;
	m_ClrCtlBk		= clrCtlBk;
}

//## end ZIDialog%351BDE69006E.declarations
//## begin module%351BDFFD00FA.epilog preserve=yes
//## end module%351BDFFD00FA.epilog

HBRUSH ZIDialog::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CDialog::OnCtlColor( pDC, pWnd, nCtlColor );

	if ( m_ColorHasBeenSuperseed )
	{
		switch ( nCtlColor )
		{
			//Edit controls need white background and black text
			//Note the 'return hbr' which is needed to draw the Edit
			//control's internal background (as opposed to text background)
			case CTLCOLOR_EDIT:
			{
				pDC->SetTextColor( m_EditCol );
				pDC->SetBkColor( RGB( 255, 255, 255 ) );
				return hbr;
			}

			//Static controls need black text and same background as m_brush
			case CTLCOLOR_STATIC:
			{
				LOGBRUSH logbrush;
				m_Brush.GetLogBrush	( &logbrush );
				pDC->SetTextColor	( m_StaticCol );
				pDC->SetBkColor		( logbrush.lbColor );
				return m_Brush;
			}

			//For listboxes, scrollbars, buttons, messageboxes and dialogs,
			//use the new brush (m_brush)
			case CTLCOLOR_LISTBOX:
			case CTLCOLOR_SCROLLBAR:
			case CTLCOLOR_BTN:
			case CTLCOLOR_MSGBOX:
			case CTLCOLOR_DLG:
			{
				return m_Brush;
			}

			//This shouldn't occurr since we took all the cases, but
			//JUST IN CASE, return the new brush
			default:
			{
				return m_Brush;
			}
		} 
	}
	// JMR-MODIF - Le 20 octobre 2005 - Gestion de l'affichage des couleurs en mode normal.
	else
	{
		switch ( nCtlColor )
		{
			// En mode normal, les boîtes d'édition sont écrites en noir sur fond blanc.
			case CTLCOLOR_EDIT:
			{
				pDC->SetTextColor( m_EditCol );
				pDC->SetBkColor( RGB( 255, 255, 255 ) );

				break;
			}

			// Tout le reste requert un affichage écrit en noir sur fond gris, avec transparence pour les textes.
			default:
			{
				if( m_HbrClrCtlBk )
				{
					pDC->SetTextColor( m_ClrCtlText );
					pDC->SetBkMode( TRANSPARENT );
					hbr = m_HbrClrCtlBk;
				}

				break;
			}
		}
	}

	return hbr;
}
