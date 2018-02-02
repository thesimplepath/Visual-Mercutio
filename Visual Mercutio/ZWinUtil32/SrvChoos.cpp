//## begin module%36FFBCCB01C3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36FFBCCB01C3.cm

//## begin module%36FFBCCB01C3.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%36FFBCCB01C3.cp

//## Module: SrvChoos%36FFBCCB01C3; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\SrvChoos.cpp

//## begin module%36FFBCCB01C3.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%36FFBCCB01C3.additionalIncludes

//## begin module%36FFBCCB01C3.includes preserve=yes
//## end module%36FFBCCB01C3.includes

// SrvChoos
#include "SrvChoos.h"
//## begin module%36FFBCCB01C3.declarations preserve=no
//## end module%36FFBCCB01C3.declarations

//## begin module%36FFBCCB01C3.additionalDeclarations preserve=yes
#include "zRes32\ZRes.h"
#include "zBaseLib\ZMessage.h"
#include "ZIChooseServerWelcome.h"
#include "ZIChooseServerSel.h"
//## end module%36FFBCCB01C3.additionalDeclarations

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZAChooseServer

//## begin ZAChooseServer::File%36FFBD6403A3.attr preserve=no  private: static CString {U} 
CString ZAChooseServer::m_File;
//## end ZAChooseServer::File%36FFBD6403A3.attr

//## begin ZAChooseServer::CompleteFile%36FFBDE603C8.attr preserve=no  private: static CString {U} 
CString ZAChooseServer::m_CompleteFile;
//## end ZAChooseServer::CompleteFile%36FFBDE603C8.attr

//## begin ZAChooseServer::ServerDirectory%36FFC14E0390.attr preserve=no  public: static CString {U} 
CString ZAChooseServer::m_ServerDirectory;
//## end ZAChooseServer::ServerDirectory%36FFC14E0390.attr

//## begin ZAChooseServer::Local%37BE6CD400EA.attr preserve=no  private: static BOOL {U} 
BOOL ZAChooseServer::m_Local;
//## end ZAChooseServer::Local%37BE6CD400EA.attr

ZAChooseServer::ZAChooseServer()
	//## begin ZAChooseServer::ZAChooseServer%.hasinit preserve=no
	//## end ZAChooseServer::ZAChooseServer%.hasinit
	//## begin ZAChooseServer::ZAChooseServer%.initialization preserve=yes
	//## end ZAChooseServer::ZAChooseServer%.initialization
{
	//## begin ZAChooseServer::ZAChooseServer%.body preserve=yes
	m_Local = FALSE;
	//## end ZAChooseServer::ZAChooseServer%.body
}

ZAChooseServer::ZAChooseServer( const CString File, BOOL Local )
	//## begin ZAChooseServer::ZAChooseServer%922729730.hasinit preserve=no
	//## end ZAChooseServer::ZAChooseServer%922729730.hasinit
	//## begin ZAChooseServer::ZAChooseServer%922729730.initialization preserve=yes
	//## end ZAChooseServer::ZAChooseServer%922729730.initialization
{
	//## begin ZAChooseServer::ZAChooseServer%922729730.body preserve=yes
	m_File = File;
	m_Local = Local;
	//## end ZAChooseServer::ZAChooseServer%922729730.body
}

ZAChooseServer::~ZAChooseServer()
{
	//## begin ZAChooseServer::~ZAChooseServer%.body preserve=yes
	//## end ZAChooseServer::~ZAChooseServer%.body
}

//## Other Operations (implementation)
BOOL ZAChooseServer::ChooseServer()
{
	//## begin ZAChooseServer::ChooseServer%922729731.body preserve=yes
	return ProcessChoose();
	//## end ZAChooseServer::ChooseServer%922729731.body
}

CString ZAChooseServer::ChooseServer( const CString File, BOOL Local )
{
	//## begin ZAChooseServer::ChooseServer%922729732.body preserve=yes
	m_File = File;
	m_Local = Local;

	if ( ProcessChoose() )
	{
		return m_CompleteFile;
	}

	return _T( "" );
	//## end ZAChooseServer::ChooseServer%922729732.body
}

BOOL ZAChooseServer::ProcessChoose()
{
	//## begin ZAChooseServer::ProcessChoose%922729734.body preserve=yes
	if ( m_File.IsEmpty() )
	{
		return FALSE;
	}

	ZIChooseServerWelcome ChooseServerWelcome( m_Local );

	if ( ChooseServerWelcome.DoModal() == IDCANCEL )
	{
		return FALSE;
	}

	ZIChooseServerSelect ChooseServerSelect( m_Local );

	if ( ChooseServerSelect.DoModal() == IDCANCEL )
	{
		return FALSE;
	}

	// No directory selected
	if ( ChooseServerSelect.GetDirectory().IsEmpty() )
	{
		return FALSE;
	}

	CString CompleteFile = ChooseServerSelect.GetDirectory() + _T( "\\" ) + m_File;

	CFileStatus status;

	if ( !CFile::GetStatus( CompleteFile, status ) )
	{
		ZIMessage Message;
		Message.DisplayMessage( IDS_NF_SELECTSERVER, IDS_NF_SELECTSERVER_TITLE );

		return FALSE;
	}

	m_CompleteFile		= CompleteFile;
	m_ServerDirectory	= ChooseServerSelect.GetDirectory();

	return TRUE;
	//## end ZAChooseServer::ProcessChoose%922729734.body
}

//## begin module%36FFBCCB01C3.epilog preserve=yes
//## end module%36FFBCCB01C3.epilog
