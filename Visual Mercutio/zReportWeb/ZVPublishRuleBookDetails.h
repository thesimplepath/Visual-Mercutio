// ******************************************************************************************************
// *                                  Classe ZVPublishRuleBookDetails                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 24 avril 2007 - Création de la nouvelle classe ZVPublishRuleBookDetails.            *
// ******************************************************************************************************
// * Cette classe effectue la publication des détails du livre des règles en tant que pages Internet.    *
// ******************************************************************************************************

#if !defined(AFX_ZVPUBLISHRULEBOOKDETAILS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHRULEBOOKDETAILS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ProcGraphModelMdlBP.h"

#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModelWeb\PSS_PublishModelGenerateDialog.h"

#include "zWeb\PSS_HtmlFile.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZVPublishRuleBookDetails
{
public:

    ZVPublishRuleBookDetails            ( ZDProcessGraphModelMdlBP* pModel = NULL );
    virtual ~ZVPublishRuleBookDetails    ();

    bool Publish                        ( CString Directory );

private:

    bool CreateFileSystem                ( ZBLogicalRulesEntity* pRules, CString Directory );

    CString GenerateFileName            ( CString Directory );

    void CreateReport                    ( ZBLogicalRulesEntity* pRules );
    void GenerateHTMLPageHead            ( CString Title );
    void GenerateHTMLPageFoot            ();
    void GenerateHTMLDocumentHeader        ();
    void WriteLine                        ( CString Text );
    void WriteLine                        ( int nID );

    void GenerateSection                ( CString RuleNumber,
                                          CString RuleName,
                                          CString ObjType,
                                          CString ObjName,
                                          CString UnitName );

    void ExploreProcessHierarchy        ( CString                    RuleNumber,
                                          CString                    RuleName,
                                          ZDProcessGraphModelMdlBP*    m_StartRootModel = NULL );

private:

    PSS_ProcessGraphModelMdl*                m_pRootModel;

    PSS_HtmlFile                          HtmlFile;

    PSS_PublishModelGenerateDialog        m_FileGenerateWindow;

    int                                    Level;
    int                                    Lvl1Counter;
    int                                    Lvl2Counter;
    int                                    Lvl3Counter;
};

#endif // !defined(AFX_ZVPUBLISHRULEBOOKDETAILS_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)