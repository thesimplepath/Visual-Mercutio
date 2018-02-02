// SingleInstanceApp.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "SingleInstanceApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIf - Le 31 décembre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// The pointer to the ZASingleInstanceApplication object

ZASingleInstanceApplication* p_OneApp;

/////////////////////////////////////////////////////////////////////////////
// ZASingleInstanceApplication

BEGIN_MESSAGE_MAP( ZASingleInstanceApplication, zMediatorZAApp )
	//{{AFX_MSG_MAP(ZASingleInstanceApplication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZASingleInstanceApplication construction

ZASingleInstanceApplication::ZASingleInstanceApplication()
{
	// Used for DDE
	p_OneApp	= this;
	isRun		= false;
}

/////////////////////////////////////////////////////////////////////////////
// ZASingleInstanceApplication initialization

BOOL ZASingleInstanceApplication::InitInstance()
{
	// Used for DDE single instance must be defined
	ASSERT( !m_CppServerName.IsEmpty() );
	ASSERT( !m_CppTopicName.IsEmpty() );

	// Check DDE
	if ( DdeInitialize( &idInst, (PFNCALLBACK)DdeCallback, 0, 0 ) )
	{
		return false;
	}

	hszCppServer	= DdeCreateStringHandle( idInst, m_CppServerName, CP_WINANSI );
	hszCppTopic		= DdeCreateStringHandle( idInst, m_CppTopicName, CP_WINANSI );

	// Try to find the first instance
	hconvCppServer	= DdeConnect( idInst, hszCppServer, hszCppTopic, NULL );

	if ( hconvCppServer )
	{
		isRun = true;
		return false;
	}

	DdeNameService( idInst, hszCppServer, 0, DNS_REGISTER );

	return true;
}

int ZASingleInstanceApplication::ExitInstance() 
{
	// DDE close
	DdeFreeStringHandle( idInst, hszCppServer );
	DdeFreeStringHandle( idInst, hszCppTopic );

	// only unregister the DDE server for first instance
	if ( !isRun )
	{
		if ( !DdeNameService ( idInst, hszCppServer, 0, DNS_UNREGISTER ) )
		{
			::MessageBox ( 0, "Error", "in ServiceUnRegister", MB_OK );
		}
	}

	DdeUninitialize( idInst );

	return true;
}

HDDEDATA CALLBACK DdeCallback( WORD		wType,
							   WORD		wFmt,
							   HCONV	hConv,
							   HSZ		hszTopic,
							   HSZ		hszItem,
							   HDDEDATA	hData,
							   DWORD	lData1,
							   DWORD	lData2 )
{
	return p_OneApp->AppDdeCallback( wType,
									 wFmt,
									 hConv,
									 hszTopic,
									 hszItem,
									 hData,
									 lData1,
									 lData2 );
}

HDDEDATA ZASingleInstanceApplication::AppDdeCallback( WORD wType,
													  WORD wFmt,
													  HCONV hConv,
													  HSZ hszTopic,
													  HSZ hszItem,
													  HDDEDATA hData,
													  DWORD lData1,
													  DWORD lData2 )
{
	int icount;
	char* buffers;
	HDDEDATA ret = (HDDEDATA) NULL;
	CWnd* p_Wnd;

	switch ( wType )
	{
		case XTYP_CONNECT:
		{
			icount	= DdeQueryString( idInst, hszTopic, NULL, 0, CP_WINANSI );
			buffers	= (char*)malloc( icount + 1 );
			DdeQueryString( idInst, hszTopic, buffers, icount + 1, CP_WINANSI );

			if ( !strcmp ( buffers, m_CppTopicName ) )
			{
				p_Wnd = AfxGetMainWnd();

				p_Wnd -> ShowWindow( SW_RESTORE );
				p_Wnd -> BringWindowToTop();
				p_Wnd -> SetForegroundWindow();

				// add any code for the first instance have found the second one is launch
				ret = (HDDEDATA) DDE_FACK;
			}

			free ( buffers );

			return ret;
		}

		case XTYP_EXECUTE:
		{
			return ret;
		}

		default:
		{
			return ret;
		}
	}
}
