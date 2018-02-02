//## begin module%36FFBCE7015F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36FFBCE7015F.cm

//## begin module%36FFBCE7015F.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36FFBCE7015F.cp

//## Module: SrvChoos%36FFBCE7015F; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\SrvChoos.h

#ifndef SrvChoos_h
#define SrvChoos_h 1

//## begin module%36FFBCE7015F.additionalIncludes preserve=no
//## end module%36FFBCE7015F.additionalIncludes

//## begin module%36FFBCE7015F.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36FFBCE7015F.includes

//## begin module%36FFBCE7015F.declarations preserve=no
//## end module%36FFBCE7015F.declarations

//## begin module%36FFBCE7015F.additionalDeclarations preserve=yes
#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%36FFBCE7015F.additionalDeclarations

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZAChooseServer

//## Class: ZAChooseServer%36FFBBD60351
//	This class allows the user to choose a server
//## Category: ZWinUtil library::Server%370BC26B021E
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZAChooseServer
{
	//## begin ZAChooseServer%36FFBBD60351.initialDeclarations preserve=yes
	//## end ZAChooseServer%36FFBBD60351.initialDeclarations

public:

	//## Constructors (generated)
	ZAChooseServer();

	//## Constructors (specified)
	//## Operation: ZAChooseServer%922729730
	//	A constructor with the file necessary to search.
	ZAChooseServer( const CString File, BOOL Local );

	//## Destructor (generated)
	~ZAChooseServer();


	//## Other Operations (specified)
	//## Operation: ChooseServer%922729731
	//	This function starts the process of choosing a server.
	BOOL ChooseServer();

	//## Operation: ChooseServer%922729732
	//	This function starts the process of choosing a server.
	//	Returns the server's directory. Empty if not ok.
	static CString ChooseServer( const CString File, BOOL Local );

	//## Operation: GetIniFile%922729733
	//	If successfull, this function returns the complete ini
	//	file with its path.
	CString GetIniFile() const;

	//## Get and Set Operations for Class Attributes (generated)

	//## Attribute: ServerDirectory%36FFC14E0390
	static const CString GetServerDirectory();

private:

	//## Constructors (generated)
	ZAChooseServer( const ZAChooseServer &right );

	//## Assignment Operation (generated)
	const ZAChooseServer & operator=( const ZAChooseServer &right );


	//## Other Operations (specified)
	//## Operation: ProcessChoose%922729734
	static BOOL ProcessChoose();

private:

	// Data Members for Class Attributes

	//## Attribute: File%36FFBD6403A3
	//	The file that should be located in the root directory.
	//## begin ZAChooseServer::File%36FFBD6403A3.attr preserve=no  private: static CString {U} 
	static CString m_File;
	//## end ZAChooseServer::File%36FFBD6403A3.attr

	//## Attribute: CompleteFile%36FFBDE603C8
	//	The complete file.
	//## begin ZAChooseServer::CompleteFile%36FFBDE603C8.attr preserve=no  private: static CString {U} 
	static CString m_CompleteFile;
	//## end ZAChooseServer::CompleteFile%36FFBDE603C8.attr

	//## begin ZAChooseServer::ServerDirectory%36FFC14E0390.attr preserve=no  public: static CString {U} 
	static CString m_ServerDirectory;
	//## end ZAChooseServer::ServerDirectory%36FFC14E0390.attr

	//## Attribute: Local%37BE6CD400EA
	//## begin ZAChooseServer::Local%37BE6CD400EA.attr preserve=no  private: static BOOL {U} 
	static BOOL m_Local;
	//## end ZAChooseServer::Local%37BE6CD400EA.attr
};

//## begin ZAChooseServer%36FFBBD60351.postscript preserve=yes
//## end ZAChooseServer%36FFBBD60351.postscript

//## Other Operations (inline)
inline CString ZAChooseServer::GetIniFile() const
{
	//## begin ZAChooseServer::GetIniFile%922729733.body preserve=yes
	return m_CompleteFile;
	//## end ZAChooseServer::GetIniFile%922729733.body
}

//## Get and Set Operations for Class Attributes (inline)
inline const CString ZAChooseServer::GetServerDirectory()
{
	//## begin ZAChooseServer::GetServerDirectory%36FFC14E0390.get preserve=no
	return m_ServerDirectory;
	//## end ZAChooseServer::GetServerDirectory%36FFC14E0390.get
}

//## begin module%36FFBCE7015F.epilog preserve=yes
//## end module%36FFBCE7015F.epilog

#endif