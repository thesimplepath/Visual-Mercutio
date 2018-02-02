// ******************************************************************************************************
// *										   Classe ZUReportNavigation								*
// ******************************************************************************************************
// * JMR-MODIF - Le 29 juin 2005 - Création de la nouvelle classe ZVPublishReport.						*
// * Cette classe gère la navigation dans les symboles du document.										*
// ******************************************************************************************************

#if !defined(AFX_ZUREPORTNAVIGATION_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUREPORTNAVIGATION_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZAConst.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zBaseSym\ZIBasicSymbolVisitor.h"

#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zWeb\ZDHtmlFile.h"

#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// ******************************************************************************************************
// *												 Enumérateurs										*
// ******************************************************************************************************

// Enumérateur représentant l'opération d'exportation en cours.
enum AFX_EXT_CLASS ZVPublishProc
{
	PUBLISH_HEADERS,
	PUBLISH_DETAILS,
};

// ******************************************************************************************************
// *										  Classe ZUReportNavigation									*
// ******************************************************************************************************

class AFX_EXT_CLASS ZUReportNavigation : public ZIBasicSymbolVisitor
{
protected:

	ZDProcessGraphModelMdl*		m_pRootModel;

	ZDProcessGraphModelMdlBP*	m_pModel;

	ZBBPProcessSymbol*			m_pPreviousProcess;

	ZDHtmlFile					HtmlFile;

	CString						m_DomainName;
	CString						m_UnitName;
	CString						m_CurrentProcessName;

	BOOL						m_ShowDetails;
	BOOL						m_IncludeDeliverables;

	bool						m_First;

	ZVPublishProc				PublishProc;

	void GeneratePageFile(CString Name, CString Description);

	bool CreateProcess();
	bool StartSection( CODNodeArray& Nodes );
	bool OnDoorSymbol( ZBBPDoorSymbol* pSymbol );
	bool OnPageSymbol( ZBBPPageSymbol* pSymbol );
	bool OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol );
	bool OnProcessSymbol( ZBBPProcessSymbol* pSymbol );
	bool OnStartSymbol( ZBBPStartSymbol* pSymbol );
	bool OnStopSymbol( ZBBPStopSymbol* pSymbol );
	bool OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol );
	bool OnSymbol( ZBSymbol* pSymbol );
	bool OnLink( ZBLinkSymbol* pLink );

	virtual bool Visit( CODComponent& Symbol );

public:

	ZUReportNavigation();
	~ZUReportNavigation();
};

#endif // !defined(AFX_ZUREPORTNAVIGATION_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)