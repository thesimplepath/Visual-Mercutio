/////////////////////////////////////////////////////////////////////////////
//@doc ZUModelGenerateImageFiles
//@module ZUModelGenerateImageFiles.h | Interface of the <c ZUModelGenerateImageFiles> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 07/2001
// <nl>Description:  ZUModelGenerateImageFiles navigates through the process and
//					 write process information to the grid
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUModelGenerateImageFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUModelGenerateImageFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zModel\ZUModelNavigation.h"
#include "zModelWeb\ZVPublishModelGenerate.h"
#include "zBaseLib\ZBKeepStringUsage.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZIBasicSymbol;
class ZIProperties;
class ZBInfoModelGraphicGeneration;
class ZBUserGroupEntity;
class ZBUserRoleEntity;
class ZBLogicalSystemEntity;
class ZBSystemEntity;
// JMR-MODIF - Le 20 février 2006 - Ajout déclarations de classes ZBLogicalPrestationsEntity et ZBPrestationsEntity.
class ZBLogicalPrestationsEntity;
class ZBPrestationsEntity;
// JMR-MODIF - Le 16 janvier 2007 - Ajout déclarations de classes ZBLogicalRulesEntity et ZBRulesEntity.
class ZBLogicalRulesEntity;
class ZBRulesEntity;
class ZBUserEntity;
class ZDHtmlFile;

#ifdef _ZMODELWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUModelGenerateImageFiles

class AFX_EXT_CLASS ZUModelGenerateImageFiles : public ZUModelNavigation, public ZBKeepStringUsage
{
public:

	ZUModelGenerateImageFiles( ZDProcessGraphModelMdl*	pModel			= NULL,
							   void*					pClass			= NULL,
							   ZBPropertyAttributes*	pPropAttributes	= NULL );

	virtual ~ZUModelGenerateImageFiles();

	CString GetIndexHtmlFilename() const
	{
		return m_IndexHtmlFilename;
	};

	CString GetRootHtmlFilename() const
	{
		return m_RootHtmlFilename;
	};

	// Call-back methods
	virtual bool OnStart();
	virtual bool OnFinish();
	virtual bool OnSymbol( ZBSymbol* pSymbol );
	virtual bool OnLink( ZBLinkSymbol* pLink );

private:

	CString CalculatePath( CString Filename, CString RefFilename );
	CString ReplaceBackSlash( CString CompleteFile );
	CString ReplaceSpecialCharInString( CString s );
	CString BuildModelImageFilename( ZDProcessGraphModelMdl* pModel );
	CString BuildMainFrameModelHTMLFilename( ZDProcessGraphModelMdl* pModel );
	CString BuildModelHTMLFilenameIndex();
	CString BuildModelHTMLFilenameBanner();
	CString BuildModelHTMLFilenameUserMainFrame();
	CString BuildModelHTMLFilenameSystemMainFrame();
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction BuildModelHTMLFilenamePrestationsMainFrame.
	CString BuildModelHTMLFilenamePrestationsMainFrame();
	CString BuildModelHTMLFilenameEmptyUser();
	CString BuildModelHTMLFilenameEmptySystem();
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction BuildModelHTMLFilenameEmptyPrestations.
	CString BuildModelHTMLFilenameEmptyPrestations();
	CString BuildModelHTMLFilenameEmptyPropertyPage();
	// JMR-MODIF - Le 6 mars 2006 - Ajout de la fonction BuildConceptorHTMLFilename.
	CString BuildConceptorHTMLFilename( CString EntityName );
	// JMR-MODIF - Le 6 mars 2006 - Ajout de la fonction BuildProcessReportHTMLFilename.
	CString BuildProcessReportHTMLFilename( CString ProcessName );
	// JMR-MODIF - Le 15 mars 2006 - Ajout de la fonction BuildPrestationsReportHTMLFilename.
	CString BuildPrestationsReportHTMLFilename( CString PrestationName );
	CString BuildModelHTMLFilename( ZDProcessGraphModelMdl* pModel, const CString Prefix = _T( "" ) );
	CString BuildModelHTMLFilenameForPrinter( ZDProcessGraphModelMdl* pModel );

	CString BuildSymbolPropertyHTMLFilename( ZIBasicSymbol*				pBasicSymbol,
											 ZDProcessGraphModelMdl*	pModel,
											 const CString				Prefix			= _T( "" ) );

	CString ParseModelName( CString ModelName );

	bool	GenerateModel( ZDProcessGraphModelMdl* pModel );
	bool	CreateHtmlPage( ZDProcessGraphModelMdl* pModel, const CString ImageFilename );
	bool	GenerateIndexPage( ZDProcessGraphModelMdl* pModel );
	bool	GenerateFrameMainModelPage( ZDProcessGraphModelMdl* pModel, CString ModelHtmlPage );
	bool	GenerateFrameUserPage( ZDProcessGraphModelMdl* pModel );
	bool	GenerateFrameSystemPage( ZDProcessGraphModelMdl* pModel );
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction GenerateFramePrestationsPage.
	bool	GenerateFramePrestationsPage( ZDProcessGraphModelMdl* pModel );
	bool	GenerateFrameEmptyUserPage();
	bool	GenerateFrameEmptySystemPage();
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction GenerateFrameEmptyPrestationsPage.
	bool	GenerateFrameEmptyPrestationsPage();
	bool	GenerateEmptyPropertyPage();
	bool	GenerateBannerPage( ZDProcessGraphModelMdl* pModel );
	bool	GenerateUnitGroupPage( ZDProcessGraphModelMdl* pModel );
	bool	GenerateLogicalSystemPage( ZDProcessGraphModelMdl* pModel );
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction GenerateLogicalPrestationsPage.
	bool	GenerateLogicalPrestationsPage( ZDProcessGraphModelMdl* pModel );

	CString BuildModelHTMLFilenameIndex( ZDProcessGraphModelMdl* pModel )
	{
		return BuildModelHTMLFilename( pModel, _T( "Index_" ) );
	};

	CString BuildModelHTMLFilenameUnit( ZDProcessGraphModelMdl* pModel )
	{
		return BuildModelHTMLFilename( pModel, _T( "Unit_" ) );
	};

	CString BuildModelHTMLFilenameSystem( ZDProcessGraphModelMdl* pModel )
	{
		return BuildModelHTMLFilename( pModel, _T( "System_" ) );
	};

	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction BuildModelHTMLFilenamePrestations.
	CString BuildModelHTMLFilenamePrestations( ZDProcessGraphModelMdl* pModel )
	{
		return BuildModelHTMLFilename( pModel, _T( "Prestations_" ) );
	};

	CString BuildLogicalSystemHTMLFilename( ZBSystemEntity* pSystemEntity );
	CString BuildUserHTMLFilename( ZBUserEntity* pUserEntity );
	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction BuildLogicalPrestationsHTMLFilename.
	CString BuildLogicalPrestationsHTMLFilename( ZBPrestationsEntity* pPrestationsEntity );

	bool GenerateUnitObjects( ZBUserGroupEntity* pGroupEntity, ZDHtmlFile* pHtmlFile );
	bool _GenerateUnitGroupObjects( ZBUserGroupEntity* pGroupEntity, ZDHtmlFile* pHtmlFile, size_t ParentID );
	bool _GenerateUnitRoleObjects( ZBUserRoleEntity* pRoleEntity, ZDHtmlFile* pHtmlFile, size_t ParentID );
	CString GenerateUserGroupList( ZBUserGroupEntity* pGroupEntity );

	bool GenerateLogicalSystemObjects( ZBLogicalSystemEntity* pSystemEntity, ZDHtmlFile* pHtmlFile );

	bool _GenerateLogicalSystemObjects( ZBLogicalSystemEntity*	pSystemEntity,
										ZDHtmlFile*				pHtmlFile,
										size_t					ParentID );

	CString GenerateLogicalSystemList( ZBLogicalSystemEntity* pSystemEntity );

	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction GenerateLogicalPrestationsObjects.
	bool GenerateLogicalPrestationsObjects( ZBLogicalPrestationsEntity*	pPrestationsEntity,
											ZDHtmlFile*					pHtmlFile );

	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction _GenerateLogicalPrestationsObjects.
	bool _GenerateLogicalPrestationsObjects( ZBLogicalPrestationsEntity*	pPrestationsEntity,
											 ZDHtmlFile*					pHtmlFile,
											 size_t							ParentID );

	// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction GenerateLogicalPrestationsList.
	CString GenerateLogicalPrestationsList( ZBLogicalPrestationsEntity* pPrestationsEntity );

	bool GeneratePropertyPage( ZIProperties* pPropertiesObject, CString HtmlFilename );

private:

	ZBInfoModelGraphicGeneration*	m_pInfo;

	ZBPropertyAttributes*			m_pPropAttributes;

	ZVPublishModelGenerate			m_FileGenerateWindow;

	CString							m_RootHtmlFilename;
	CString							m_IndexHtmlFilename;
	CString							m_RootName;
	CString							m_ImageDirectory;
	CString							m_IncludeDirectory;
	CString							m_InternalLogoFilename;

	static size_t					m_IndexItem;
};

#endif // !defined(AFX_ZUModelGenerateImageFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)