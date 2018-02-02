//## begin module%363DC8590160.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363DC8590160.cm

//## begin module%363DC8590160.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%363DC8590160.cp

//## Module: GFldDoc%363DC8590160; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\GFldDoc.cpp

//## begin module%363DC8590160.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%363DC8590160.additionalIncludes

//## begin module%363DC8590160.includes preserve=yes
//## end module%363DC8590160.includes

// GFldDoc
#include "GFldDoc.h"
//## begin module%363DC8590160.declarations preserve=no
//## end module%363DC8590160.declarations

//## begin module%363DC8590160.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZDGlobalFieldDocument, ZDBaseDocument, def_Version)

BEGIN_MESSAGE_MAP(ZDGlobalFieldDocument, ZDBaseDocument)
	//{{AFX_MSG_MAP(ZDGlobalFieldDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//## end module%363DC8590160.additionalDeclarations

// Class ZDGlobalFieldDocument 

ZDGlobalFieldDocument::ZDGlobalFieldDocument()
	//## begin ZDGlobalFieldDocument::ZDGlobalFieldDocument%.hasinit preserve=no
	: m_pHistoryValueManager( NULL ),
	  m_pGlobalFieldManager	( NULL )
	//## end ZDGlobalFieldDocument::ZDGlobalFieldDocument%.hasinit
	//## begin ZDGlobalFieldDocument::ZDGlobalFieldDocument%.initialization preserve=yes
	//## end ZDGlobalFieldDocument::ZDGlobalFieldDocument%.initialization
{
	//## begin ZDGlobalFieldDocument::ZDGlobalFieldDocument%.body preserve=yes
	//## end ZDGlobalFieldDocument::ZDGlobalFieldDocument%.body
}

// ATTENTION : Surtout ne pas détruire m_pHistoryValueManager et m_pGlobalFieldManager dans cette classe.
// Ce sont des copies de pointeurs, et les objets pointés sont détruits ailleurs dans le code.
ZDGlobalFieldDocument::~ZDGlobalFieldDocument()
{
	//## begin ZDGlobalFieldDocument::~ZDGlobalFieldDocument%.body preserve=yes
	//## end ZDGlobalFieldDocument::~ZDGlobalFieldDocument%.body
}

void ZDGlobalFieldDocument::Initialize ( const CString			Filename,
										 ZAGlobalFieldManager*	pGlobalFieldManager,
										 ZAHistoryFieldManager*	pHistoryValueManager )
{
	//## begin ZDGlobalFieldDocument::Initialize%938959794.body preserve=yes
	SetPathName( Filename, FALSE );

	// Assigns manager pointers
	m_pHistoryValueManager	= pHistoryValueManager;
	m_pGlobalFieldManager	= pGlobalFieldManager;
	//## end ZDGlobalFieldDocument::Initialize%938959794.body
}

void ZDGlobalFieldDocument::Initialize ( ZAGlobalFieldManager*	pGlobalFieldManager,
										 ZAHistoryFieldManager*	pHistoryValueManager )
{
	//## begin ZDGlobalFieldDocument::Initialize%938372464.body preserve=yes
	// Assigns manager pointers
	m_pHistoryValueManager	= pHistoryValueManager;
	m_pGlobalFieldManager	= pGlobalFieldManager;
	//## end ZDGlobalFieldDocument::Initialize%938372464.body
}

BOOL ZDGlobalFieldDocument::ReadDocument ( const CString			Filename,
										   ZAGlobalFieldManager*	pGlobalFieldManager,
										   ZAHistoryFieldManager*	pHistoryValueManager)
{
	//## begin ZDGlobalFieldDocument::ReadDocument%938242443.body preserve=yes
	if ( pGlobalFieldManager == NULL || pHistoryValueManager == NULL )
		return FALSE;

	// Assigns manager pointers
	Initialize( pGlobalFieldManager, pHistoryValueManager );

	return ReadDocument( Filename );
	//## end ZDGlobalFieldDocument::ReadDocument%938242443.body
}

BOOL ZDGlobalFieldDocument::ReadDocument ( const CString Filename )
{
	//## begin ZDGlobalFieldDocument::ReadDocument%939754014.body preserve=yes
	for ( int i = 0; i < 5; ++i )
	{
		if ( ZDBaseDocument::ReadDocument( Filename ) )
			return TRUE;
	}

	return FALSE;
	//## end ZDGlobalFieldDocument::ReadDocument%939754014.body
}

// Additional Declarations
//## begin ZDGlobalFieldDocument%363DC8240069.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZDGlobalFieldDocument diagnostics

#ifdef _DEBUG
void ZDGlobalFieldDocument::AssertValid() const
{
	CObject::AssertValid();
}

void ZDGlobalFieldDocument::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG
//## end ZDGlobalFieldDocument%363DC8240069.declarations

//## Other Operations (implementation)
void ZDGlobalFieldDocument::Serialize ( CArchive& ar )
{
	//## begin ZDGlobalFieldDocument::Serialize%910019973.body preserve=yes
	if ( ar.IsStoring() )
	{
		SerializeStampWrite( ar, GetDocumentStamp() );
	}
	else
	{
		SerializeStampRead( ar, GetDocumentStamp() );
	}

	if ( m_pGlobalFieldManager && m_pHistoryValueManager )
	{
		m_pGlobalFieldManager->Serialize( ar );
		m_pHistoryValueManager->Serialize( ar );
	}

	//## end ZDGlobalFieldDocument::Serialize%910019973.body
}

//## begin module%363DC8590160.epilog preserve=yes
//## end module%363DC8590160.epilog