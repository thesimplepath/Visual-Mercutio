// ZUCheckSymbolConsistency.h: interface for the ZUCheckSymbolConsistency class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCHECKSYMBOLCONSISTENCY_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCHECKSYMBOLCONSISTENCY_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseSym\ZIBasicSymbolVisitor.h"

// Forward declaration
class ZILog;
class ZIBasicSymbol;
class ZBSymbol;
class ZBLinkSymbol;
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class ZDProcessGraphModelMdl;
// JMR-MODIF - Le 2 octobre 2006 - Ajout de la classe ZDProcessGraphModelMdlBP dans les déclarations.
class ZDProcessGraphModelMdlBP;
// JMR-MODIF - Le 2 octobre 2006 - Ajout de la classe ZDProcessGraphModelController dans les déclarations.
class ZDProcessGraphModelController;

// JMR-MODIF - Le 2 octobre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUCheckSymbolConsistency : public ZIBasicSymbolVisitor
{
public:

	ZUCheckSymbolConsistency( ZDProcessGraphModelMdl*	pModel	= NULL,
							  ZILog*					pLog	= NULL );

	virtual ~ZUCheckSymbolConsistency();

	// JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
	bool CheckSymbol( CODComponent& Symbol, BOOL ModelIsClean );

	// Logging functions
	void StartLogging()
	{
		m_IsLogging = true;
	};

	void StopLogging()
	{
		m_IsLogging = false;
	};

	bool IsLogging() const
	{
		return m_IsLogging;
	};

	// Returns the ZILog pointer on the log used for checking the symbol
	ZILog* GetLog()
	{
		return m_pLog;
	};

	/* Each concrete derived ZIBasicSymbolVisitor class
	   must implement Visit to implement the appropriate 
	   algorithm 
	   In this concrete class the Visit will check the
	   BasicSymbol passes as an argument */
	virtual bool Visit( CODComponent& Symbol );

private:

	bool CheckDoorSymbol				( ZBBPDoorSymbol* pSymbol );
	bool CheckPageSymbol				( ZBBPPageSymbol* pSymbol );
	bool CheckProcedureSymbol			( ZBBPProcedureSymbol* pSymbol );
	bool CheckProcessSymbol				( ZBBPProcessSymbol* pSymbol );
	bool CheckStartSymbol				( ZBBPStartSymbol* pSymbol );
	bool CheckStopSymbol				( ZBBPStopSymbol* pSymbol );
	bool CheckDeliverableLinkSymbol		( ZBDeliverableLinkSymbol* pSymbol );
	bool CheckSymbol					( ZBSymbol* pSymbol );
	bool CheckLink						( ZBLinkSymbol* pLink );

	bool CheckInvalidCharInSymbolName	( ZIBasicSymbol* pSymbol, CString Path );
	bool CheckUniqueRef					( ZIBasicSymbol* pSymbol );
	bool RefExist						( int ref );

	void DeleteCorruptedSymbol			( ZBSymbol*					m_Symbol,
										  ZDProcessGraphModelMdlBP*	m_StartRootModel	= NULL );

private:

	bool					m_IsLogging;

	ZILog*					m_pLog;

	int*					m_pIDArray;
	int						m_RefIDSize;

	ZDProcessGraphModelMdl*	m_pModel;

	size_t					m_ErrorCounter;
	size_t					m_WarningCounter;
};

#endif // !defined(AFX_ZUCHECKSYMBOLCONSISTENCY_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)