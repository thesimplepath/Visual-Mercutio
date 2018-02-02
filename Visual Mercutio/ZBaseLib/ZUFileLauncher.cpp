/************************************************************************************************************
 *												Classe ZUFileLauncher										*
 ************************************************************************************************************
 * Cette classe permet d'ouvrir un fichier. Si ce n'est pas un fichier associé à l'application Mercutio,	*
 * la classe prend en charge le démarrage de l'application propriétaire du fichier.							*
 ************************************************************************************************************/

#include "stdafx.h"
#include "ZUFileLauncher.h"
#include <vdmdbg.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Declare Callback Enum Functions.
BOOL CALLBACK ActivateAppEnum	( HWND hwnd, LPARAM lParam );
BOOL CALLBACK Activate16AppEnum	( HWND hwnd, LPARAM lParam );
BOOL CALLBACK TerminateAppEnum	( HWND hwnd, LPARAM lParam );
BOOL CALLBACK Terminate16AppEnum( HWND hwnd, LPARAM lParam );

// **********************************************************************************************************
// *										   Construction/Destruction										*
// **********************************************************************************************************

// Constructeur de la classe ZUFileLauncher.
ZUFileLauncher::ZUFileLauncher( const CString		Filename,
							    FileLauncherMode	Mode,
								const CString		Parameters,
								const CString		Directory )
	:	m_Filename		(Filename),
		m_Mode			(Mode),
		m_Parameters	(Parameters),
		m_Directory		(Directory)
{
	ZeroMemory( &m_sei, sizeof( m_sei ) );
}

// Destructeur de la classe ZUFileLauncher.
ZUFileLauncher::~ZUFileLauncher()
{
}

// **********************************************************************************************************
// *											Fonctions de la classe										*
// **********************************************************************************************************

// Cette fonction permet d'initialiser les données de la classe.
BOOL ZUFileLauncher::Initialize( const CString		Filename,
								 FileLauncherMode	Mode,
								 const CString		Parameters,
								 const CString		Directory )
{
	m_Filename		= Filename;
	m_Mode			= Mode;
	m_Parameters	= Parameters;
	m_Directory		= Directory;

	return TRUE;
}

// Cette fonction permet d'ouvrir un fichier, et de démarrer le programme approprié, si ce n'est pas un modèle Mercutio.
BOOL ZUFileLauncher::Launch( const CString		Filename,
							 FileLauncherMode	Mode,
							 const CString		Parameters,
							 const CString		Directory )
{
	m_Filename		= Filename;
	m_Mode			= Mode;
	m_Parameters	= Parameters;
	m_Directory		= Directory;

	return ZUFileLauncher::Launch();
}

// Cette fonction permet d'ouvrir un fichier, et de démarrer le programme approprié, si ce n'est pas un modèle Mercutio.
BOOL ZUFileLauncher::Launch()
{
	m_ErrorCode = ShellExecute( ::GetDesktopWindow(), 
								(const char*)GetModeVerbString(), 
								(const char*)m_Filename, 
								(const char*)m_Parameters,
								(const char*)m_Directory, 
								SW_SHOWDEFAULT );

	return IsError() == FALSE;
/*
	CString	Verb = GetModeVerbString();
	ZeroMemory(&m_sei,sizeof(m_sei));
	m_sei.cbSize = sizeof(m_sei);
	m_sei.lpFile = (const char*)m_Filename;
	m_sei.lpParameters = (const char*)m_Parameters;
	m_sei.lpDirectory = (const char*)m_Directory;
	m_sei.nShow = SW_SHOWDEFAULT;
	m_sei.lpVerb = (const char*)Verb;
	m_sei.fMask  = SEE_MASK_NOCLOSEPROCESS;
	m_sei.hwnd = ::GetDesktopWindow();
	return ShellExecuteEx(&m_sei);
*/
}

// Cette fonction permet la fermeture du fichier.
BOOL ZUFileLauncher::Close()
{ 
	if ( IsError() || !HasBeenLaunched() )
		return TRUE;

	BOOL Ret;

	// TerminateAppEnum() posts WM_CLOSE to all windows whose PID
	// matches your process's.
	EnumWindows( (WNDENUMPROC)TerminateAppEnum, (LPARAM) m_sei.hProcess );

	// Wait on the handle. If it signals, great. If it times out,
	// then you kill it.
	if ( WaitForSingleObject( m_sei.hProcess, /*Timeout*/1000 )!= WAIT_OBJECT_0 )
		Ret = ( TerminateProcess( m_sei.hProcess, 0 ) ? TRUE : FALSE );
	else
		Ret = TRUE;

	CloseHandle( m_sei.hProcess );

	return Ret;
}

// Cette fonction permet de déterminer si le fichier est déjà ouvert.
BOOL ZUFileLauncher::HasBeenLaunched()
{ 
	if ( m_sei.hProcess == NULL )
		return FALSE;

	// Otherwise, check if the process still exist
	DWORD ExitCode;

	if ( GetExitCodeProcess( m_sei.hProcess, &ExitCode ) )
	{
		if ( ExitCode == STILL_ACTIVE )
			return TRUE;
	}

	// Not running or never launched
	return FALSE;
}

// Cette fonction permet de donner le focus à l'application hôte.
BOOL ZUFileLauncher::ActivateApplication()
{
	if ( IsError() || !HasBeenLaunched() )
		return FALSE;

	// ActivateAppEnum() activates the application
	EnumWindows( (WNDENUMPROC)ActivateAppEnum, (LPARAM)m_sei.hProcess );

	return TRUE;
}

// Cette fonction permet d'obtenir le bon verbe. Le verbe est l'action que ShellExecute doit effectuer sur le fichier.
CString	ZUFileLauncher::GetModeVerbString()
{
	switch ( m_Mode )
	{
		case FLMedit:
		{
			return "edit";
		}

		case FLMexplore:
		{
			return "explore";
		}

		case FLMopen:
		{
			return "open";
		}

		case FLMprint:
		{
			return "print";
		}

		case FLMproperties:
		{
			return "properties";
		}
	}

	return "";
}

// Cette fonction permet d'obtenir l'erreur associée au mode.
CString	ZUFileLauncher::GetErrorString()
{
	switch ( m_Mode )
	{
		case 0:							return "The operating system is out of memory or resources.";
		case ERROR_BAD_FORMAT:			return "The .exe file is invalid (non-Win32® .exe or error in .exe image.";
		case SE_ERR_ACCESSDENIED:		return "The operating system denied access to the specified file.";
		case SE_ERR_ASSOCINCOMPLETE:	return "The file name association is incomplete or invalid.";
		case SE_ERR_DDEBUSY:			return "The DDE transaction could not be completed because other DDE transactions were being processed.";
		case SE_ERR_DDEFAIL:			return "The DDE transaction failed.";
		case SE_ERR_DDETIMEOUT:			return "The DDE transaction could not be completed because the request timed out.";
		case SE_ERR_DLLNOTFOUND:		return "The specified dynamic-link library was not found.";
		case SE_ERR_FNF:				return "The specified file was not found.";
		case SE_ERR_NOASSOC:			return "There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
		case SE_ERR_OOM:				return "There was not enough memory to complete the operation.";
		case SE_ERR_PNF:				return "The specified path was not found.";
		case SE_ERR_SHARE:				return "A sharing violation occurred.";
	}

	return "";
}

BOOL CALLBACK ActivateAppEnum( HWND hwnd, LPARAM lParam )
{
	DWORD dwID;

	GetWindowThreadProcessId( hwnd, &dwID );

	if( dwID == (DWORD)lParam )
	{
		::SetActiveWindow( hwnd );
		::SetForegroundWindow( hwnd );
	}

	return TRUE;
}

BOOL CALLBACK Activate16AppEnum( HWND hwnd, LPARAM lParam )
{
	DWORD      dwID;
	DWORD      dwThread;
//	TERMINFO   *termInfo;

//	termInfo = (TERMINFO *)lParam;

	dwThread = GetWindowThreadProcessId( hwnd, &dwID );

//	if(dwID == termInfo->dwID && termInfo->dwThread == dwThread )
//	{
		::SetActiveWindow( hwnd );
//	}

	return TRUE;
}


BOOL CALLBACK TerminateAppEnum( HWND hwnd, LPARAM lParam )
{
	DWORD dwID ;

	GetWindowThreadProcessId( hwnd, &dwID );

	if( dwID == (DWORD)lParam )
	{
		PostMessage( hwnd, WM_CLOSE, 0, 0 );
	}

	return TRUE;
}

BOOL CALLBACK Terminate16AppEnum( HWND hwnd, LPARAM lParam )
{
	DWORD      dwID;
	DWORD      dwThread;
//	TERMINFO   *termInfo ;

//	termInfo = (TERMINFO *)lParam ;

	dwThread = GetWindowThreadProcessId( hwnd, &dwID );

//	if(dwID == termInfo->dwID && termInfo->dwThread == dwThread )
//	{
		PostMessage( hwnd, WM_CLOSE, 0, 0 );
//	}

	return TRUE;
}
