// ******************************************************************************************************
// *										 Classe ZVPublishRuleBook									*
// ******************************************************************************************************
// * JMR-MODIF - Le 14 janvier 2007 - Création de la nouvelle classe ZVPublishRuleBook.					*
// ******************************************************************************************************
// * Cette classe effectue la publication du livre des règles en tant que pages Internet.				*
// ******************************************************************************************************

#if !defined(AFX_ZVPUBLISHRULEBOOK_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHRULEBOOK_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ProcGraphModelMdlBP.h"

#include "zModelWeb\ZVPublishModelGenerate.h"

#include "zWeb\ZDHtmlFile.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZVPublishRuleBook
{
public:

	ZVPublishRuleBook					( ZDProcessGraphModelMdlBP* pModel = NULL );
	virtual ~ZVPublishRuleBook			();

	bool Publish						( CString Directory );

private:

	bool CreateFileSystem				( ZBLogicalRulesEntity* pRules, CString Directory );

	CString GenerateFilename			( CString Directory );

	void CreateReport					( ZBLogicalRulesEntity* pRules );
	void GenerateHTMLPageHead			( CString Title );
	void GenerateHTMLPageFoot			();
	void GenerateHTMLDocumentHeader		( CString RuleName, CString RuleDesc );
	void GenerateHTMLTable1				( CString RuleName, CString RuleDesc );
	void GenerateHTMLTable2				( CString RuleName, CString RuleDesc );
	void GenerateHTMLTable3				( CString RuleName, CString RuleDesc );
	void WriteLine						( CString Text );
	void WriteLine						( int nID );

private:

	ZDProcessGraphModelMdl*				m_pRootModel;

	ZDHtmlFile							HtmlFile;

	ZVPublishModelGenerate				m_FileGenerateWindow;

	int									Level;
	int									Lvl1Counter;
	int									Lvl2Counter;
	int									Lvl3Counter;
};

#endif // !defined(AFX_ZVPUBLISHRULEBOOK_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)