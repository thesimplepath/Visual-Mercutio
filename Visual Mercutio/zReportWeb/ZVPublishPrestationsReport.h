// ******************************************************************************************************
// *								  Classe ZVPublishPrestationsReport									*
// ******************************************************************************************************
// * JMR-MODIF - Le 9 mars 2006 - Création de la nouvelle classe ZVPublishPrestationsReport.			*
// ******************************************************************************************************
// * Cette classe effectue la publication du rapport prestations en tant que pages Internet.			*
// ******************************************************************************************************

#if !defined(AFX_ZVPUBLISHPRESTATIONSREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHPRESTATIONSREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZAConst.h"

#include "zBaseLib\ZUStringFormater.h"
#include "zBaseLib\ZBTokenizer.h"

#include "zConversion\ZUStringConversion.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"
#include "zModelBP\ZBBPUnitProp2.h"

#include "zModelWeb\ZVPublishModelGenerate.h"

#include "zWeb\ZDHtmlFile.h"

#include "zProperty\ZBPropertyAttributes.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// ******************************************************************************************************
// *								  Classe ZVPublishPrestationsReport									*
// ******************************************************************************************************
class AFX_EXT_CLASS ZVPublishPrestationsReport
{
public:

	ZVPublishPrestationsReport			( ZDProcessGraphModelMdlBP* pModel = NULL );
	virtual ~ZVPublishPrestationsReport	();

	bool Publish						( CString Directory );

private:

	bool CreateFileSystem				( ZBLogicalPrestationsEntity* pPrestations, CString Directory );

	CString GenerateFilename			( CString Directory, CString PrestationName );

	void CreateReport					( CString PrestationName );
	void GenerateHTMLPageHead			( CString Title );
	void GenerateHTMLPageFoot			();
	void GenerateHTMLTableHead			();
	void GenerateHTMLTableFoot			();
	void GenerateHTMLReportTitle		( CString PrestationName, CString Description );
	void GenerateHTMLSectionTitle		();
	void GenerateHTMLSectionLine		( CString Group, CString Processus, CString Procedure );
	void WriteLine						( CString Text );
	void WriteLine						( int nID );
	void FindProcedures					( CString ProcessName, ZDProcessGraphModelMdlBP* m_StartModel );

	void FindUnitGroupChilds			( ZBUserGroupEntity*		pGroup,
										  CString					PropertyName,
										  CString					ProcessName,
										  CString					ProcedureName,
										  BOOL						ChildMode		= FALSE,
										  int						ChildLevel		= 0 );

	void ExploreProcessHierarchy		( CString					PrestationName,
										  ZDProcessGraphModelMdlBP*	m_StartRootModel = NULL );

private:

	ZDProcessGraphModelMdl*				m_pRootModel;

	ZDHtmlFile							HtmlFile;

	ZVPublishModelGenerate				m_FileGenerateWindow;
};

#endif // !defined(AFX_ZVPUBLISHPRESTATIONSREPORT_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)