//## begin module%363DC8690159.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363DC8690159.cm

//## begin module%363DC8690159.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%363DC8690159.cp

//## Module: GFldDoc%363DC8690159; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\GFldDoc.h

#ifndef GFldDoc_h
#define GFldDoc_h 1

//## begin module%363DC8690159.additionalIncludes preserve=no
//## end module%363DC8690159.additionalIncludes

//## begin module%363DC8690159.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363DC8690159.includes

// FldMng
#include "FldMng.h"
// HistFMng
#include "HistFMng.h"
// Stamp
#include "Stamp.h"
// BaseDoc
#include "BaseDoc.h"
//## begin module%363DC8690159.declarations preserve=no
//## end module%363DC8690159.declarations

//## begin module%363DC8690159.additionalDeclarations preserve=yes
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
//## end module%363DC8690159.additionalDeclarations

//## Class: ZDGlobalFieldDocument%363DC8240069
//## Category: ZBaseLib::History Field manager%36347B0E0308
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%363DC8240074;ZDStamp { -> }
//## Uses: <unnamed>%363DC8240075;ZAGlobalFieldManager { -> }
//## Uses: <unnamed>%36C9E66A01C7;ZAHistoryFieldManager { -> }

class AFX_EXT_CLASS ZDGlobalFieldDocument : public ZDBaseDocument  //## Inherits: <unnamed>%363DC8240073
{
protected:

	DECLARE_SERIAL( ZDGlobalFieldDocument )

//## begin ZDGlobalFieldDocument%363DC8240069.initialDeclarations preserve=yes
public:
	
	// Inherited feature
	typedef ZDBaseDocument inherited;
	//## end ZDGlobalFieldDocument%363DC8240069.initialDeclarations

public:

	//## Constructors (generated)
	ZDGlobalFieldDocument();

	//## Destructor (generated)
	~ZDGlobalFieldDocument();

	//## Other Operations (specified)
	//## Operation: Serialize%910019973
	//	Serialize document information.
	virtual void Serialize ( CArchive& ar );

	//## Operation: Initialize%938959794
	void Initialize ( const CString				Filename,
					  ZAGlobalFieldManager*		pGlobalFieldManager,
					  ZAHistoryFieldManager*	pHistoryValueManager );

	//## Operation: Initialize%938372464
	void Initialize ( ZAGlobalFieldManager* pGlobalFieldManager, ZAHistoryFieldManager* pHistoryValueManager );

	//## Operation: ReadDocument%938242443
	//	Read the document.
	BOOL ReadDocument ( const CString			Filename,
						ZAGlobalFieldManager*	pGlobalFieldManager,
						ZAHistoryFieldManager*	pHistoryValueManager);

	//## Operation: ReadDocument%939754014
	//	Read the document.
	virtual BOOL ReadDocument ( const CString Filename );

	// Additional Public Declarations
	//## begin ZDGlobalFieldDocument%363DC8240069.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

	//## end ZDGlobalFieldDocument%363DC8240069.public

protected:

	// Additional Protected Declarations
	//## begin ZDGlobalFieldDocument%363DC8240069.protected preserve=yes
	//{{AFX_MSG(ZDGlobalFieldDocument)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//## end ZDGlobalFieldDocument%363DC8240069.protected

private:

	//## Constructors (generated)
	ZDGlobalFieldDocument( const ZDGlobalFieldDocument &right );

	//## Assignment Operation (generated)
	const ZDGlobalFieldDocument & operator=( const ZDGlobalFieldDocument &right );

private:

	// Data Members for Class Attributes

	//## Attribute: pHistoryValueManager%37EC7B1E0227
	// This is the manager of history field values.
	//## begin ZDGlobalFieldDocument::pHistoryValueManager%37EC7B1E0227.attr preserve=no  public: ZAHistoryFieldManager* {U} NULL
	ZAHistoryFieldManager* m_pHistoryValueManager;
	//## end ZDGlobalFieldDocument::pHistoryValueManager%37EC7B1E0227.attr

	//## Attribute: pGlobalFieldManager%37EC7B240154
	// This is the manager of global field definition.
	//## begin ZDGlobalFieldDocument::pGlobalFieldManager%37EC7B240154.attr preserve=no  public: ZAGlobalFieldManager* {U} NULL
	ZAGlobalFieldManager* m_pGlobalFieldManager;
	//## end ZDGlobalFieldDocument::pGlobalFieldManager%37EC7B240154.attr

	// Additional Private Declarations
	//## begin ZDGlobalFieldDocument%363DC8240069.private preserve=yes
	//## end ZDGlobalFieldDocument%363DC8240069.private

private:  //## implementation

	// Additional Implementation Declarations
	//## begin ZDGlobalFieldDocument%363DC8240069.implementation preserve=yes
	//## end ZDGlobalFieldDocument%363DC8240069.implementation
};

//## begin ZDGlobalFieldDocument%363DC8240069.postscript preserve=yes
//## end ZDGlobalFieldDocument%363DC8240069.postscript

// Class ZDGlobalFieldDocument 

//## begin module%363DC8690159.epilog preserve=yes
//## end module%363DC8690159.epilog

#endif