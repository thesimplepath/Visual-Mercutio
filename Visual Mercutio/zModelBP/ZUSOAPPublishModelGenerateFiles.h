/////////////////////////////////////////////////////////////////////////////
//@doc ZUSOAPPublishModelGenerateFiles
//@module ZUSOAPPublishModelGenerateFiles.h | Interface of the <c ZUSOAPPublishModelGenerateFiles> class.
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
// <nl>Description:  ZUSOAPPublishModelGenerateFiles navigates through the process and
//					 write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSOAPPublishModelGenerateFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUSOAPPublishModelGenerateFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zSOAP\pPublishFile.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBPublishMessengerModelInformation;
class ZBInfoModelGraphicGeneration;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUSOAPPublishModelGenerateFiles

class AFX_EXT_CLASS ZUSOAPPublishModelGenerateFiles : public ZUModelNavigation, public ZBKeepStringUsage
{
public:

	ZUSOAPPublishModelGenerateFiles( ZDProcessGraphModelMdl*				pModel	= NULL,
									 void*									pClass	= NULL,
									 ZBPublishMessengerModelInformation*	pInfo	= NULL );

	virtual ~ZUSOAPPublishModelGenerateFiles();

public:

	// Call-back methods
	virtual bool OnStart();
	virtual bool OnFinish();
	virtual bool OnSymbol( ZBSymbol* pSymbol );
	virtual bool OnLink( ZBLinkSymbol* pLink );

private:

	bool	GenerateModel( ZDProcessGraphModelMdl* pModel );
	bool	CreateHtmlPage( ZDProcessGraphModelMdl* pModel, const CString ImageFilename );

	CString BuildModelImageFilename( ZDProcessGraphModelMdl* pModel );
	CString BuildModelHTMLFilename( ZDProcessGraphModelMdl* pModel );
	CString ParseModelName( CString ModelName );

private:

	ZVPublishModelGenerate				m_FileGenerateWindow;

	CString								m_RootHtmlFilename;
	CString								m_RootName;
	CString								m_TargetDirectory;

	ZBPublishMessengerModelInformation*	m_pModelInfo;
	ZBInfoModelGraphicGeneration*		m_pInfo;

	pPublishFile						m_pf;
};

#endif // !defined(AFX_ZUSOAPPublishModelGenerateFiles_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)