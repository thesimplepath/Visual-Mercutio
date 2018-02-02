/////////////////////////////////////////////////////////////////////////////
//@doc ZAWindowConfiguration
//@module ZConfigW.cpp | Implementation of the <c ZAWindowConfiguration> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com

#include <StdAfx.h>

// ZConfigW
#include "ZConfigW.h"

// JMR-MODIF - le 19 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

static TCHAR szFormat[] = _T( "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d" );

// Class ZAWindowConfiguration 

ZAWindowConfiguration::ZAWindowConfiguration ( CString IniFile )
{
	Create( IniFile );
}

ZAWindowConfiguration::~ZAWindowConfiguration()
{
}

BOOL ZAWindowConfiguration::Create ( CString IniFile )
{
	m_SystemOption.Create( IniFile, WindowsConfigSectionName );
	return TRUE;
}

BOOL ZAWindowConfiguration::ReadWindowPlacement( LPWINDOWPLACEMENT pwp, const CString WndName )
{
	CString strBuffer = m_SystemOption.ReadOption( szIniWindowBufferEntry + WndName, _T( "" ) );

	if ( strBuffer.IsEmpty() )
	{
		return FALSE;
	}

	WINDOWPLACEMENT wp;

	int nRead = _stscanf( strBuffer,
						  szFormat,
						  &wp.flags,
						  &wp.showCmd,
						  &wp.ptMinPosition.x,
						  &wp.ptMinPosition.y,
						  &wp.ptMaxPosition.x,
						  &wp.ptMaxPosition.y,
						  &wp.rcNormalPosition.left,
						  &wp.rcNormalPosition.top,
						  &wp.rcNormalPosition.right,
						  &wp.rcNormalPosition.bottom );

	if ( nRead != 10 )
	{
		return FALSE;
	}

	wp.length = sizeof wp;
	*pwp = wp;

	return TRUE;
}

// write a window placement to settings section of app's ini file
void ZAWindowConfiguration::WriteWindowPlacement( LPWINDOWPLACEMENT pwp, const CString WndName )
{
	TCHAR szBuffer[ sizeof( _T( "-32767" ) ) * 8 + sizeof( _T( "65535" ) ) * 2 ];

	wsprintf( szBuffer,
			  szFormat,
			  pwp->flags,
			  pwp->showCmd,
			  pwp->ptMinPosition.x,
			  pwp->ptMinPosition.y,
			  pwp->ptMaxPosition.x,
			  pwp->ptMaxPosition.y,
			  pwp->rcNormalPosition.left,
			  pwp->rcNormalPosition.top,
			  pwp->rcNormalPosition.right,
			  pwp->rcNormalPosition.bottom );

	m_SystemOption.WriteOption( szIniWindowBufferEntry + WndName, szBuffer );
}

BOOL ZAWindowConfiguration::SaveWindowPosition ( CWnd* pWnd, const CString WndName, BOOL PositionOnly )
{
	if ( pWnd )
	{
		WINDOWPLACEMENT wp;
		wp.length = sizeof wp;

		if ( pWnd->GetWindowPlacement( &wp ) )
		{
			wp.flags = 0;

			if ( pWnd->IsZoomed() )
			{
				wp.flags |= WPF_RESTORETOMAXIMIZED;
			}

			if ( !pWnd->IsWindowVisible() )
			{
				wp.showCmd = SW_HIDE;
			}

			// and write it to the .INI file
			WriteWindowPlacement( &wp, WndName );
		}
	}

	return TRUE;
}

BOOL ZAWindowConfiguration::RestoreWindowPosition ( CWnd* pWnd, const CString WndName, BOOL PositionOnly )
{
	if ( pWnd )
	{
		WINDOWPLACEMENT wp;

		if ( ReadWindowPlacement( &wp, WndName ) )
		{
			pWnd->SetWindowPlacement( &wp );
		}
	}

	return TRUE;
}

BOOL ZAWindowConfiguration::SaveWindowDesktop ( CWnd* pDesktopWnd, const CString WndName, BOOL PositionOnly )
{
	// Not implemented
	return TRUE;
}

BOOL ZAWindowConfiguration::RestoreWindowDesktop ( CWnd* pDesktopWnd, const CString WndName, BOOL PositionOnly )
{
	// Not implemented
	return TRUE;
}
