//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//  Source file: ZBServerDiskDisk.h

#ifndef ZBServerDisk_h
#define ZBServerDisk_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// ZBServer
#include "ZBServer.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZBServerDisk 
{
  public:
      ZBServerDisk ( ZBServer* pServer = NULL, const CString EmptyImageServerIniFile = "" );
	  void	Initialize( ZBServer* pServer, const CString EmptyImageServerIniFile = "" );
	  bool	DeleteServer(bool CheckStructure = true);
	  bool	CreateServer();
	  bool	CopyServer( ZBServer& SourceServer );
	  CString	GetLog() { return m_Log; };

      ~ZBServerDisk();

  private:
	  bool CopyServerDirectory( ZBServer& SourceServer );
	  bool CreateServerDirectoryStructure();

  private:
      ZBServerDisk(const ZBServerDisk &right);
      const ZBServerDisk & operator=(const ZBServerDisk &right);

	  ZBServer			m_EmptyImageServer;
	  ZBServer*			m_pServer;
	  CString			m_EmptyImageServerIniFile;
	  CString			m_Log;

	  // Predefined messages
	  CString			m_ServerCreationSuccess;
	  CString			m_ServerCreationStart;
	  CString			m_FailedToCreateServer;
	  CString			m_FailedToCreateDir;
	  CString			m_FailedToCopyFile;
	  CString			m_FailedToInitializeParameters;

};


// Class ZBServerDisk 



#endif	// ZBServerDisk_h
