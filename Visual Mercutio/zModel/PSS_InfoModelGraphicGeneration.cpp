/****************************************************************************
 * ==> PSS_InfoModelGraphicGeneration --------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic model info generator                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InfoModelGraphicGeneration.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphModelController.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_InfoModelGraphicGeneration
//---------------------------------------------------------------------------
PSS_InfoModelGraphicGeneration::PSS_InfoModelGraphicGeneration(PSS_ProcessGraphModelMdl*        pModel,
                                                               PSS_ProcessGraphModelController* pCtlr,
                                                               const CString&                   urlName,
                                                               bool                             absolutePath,
                                                               bool                             includeConceptor,
                                                               bool                             includeProcessReport,
                                                               bool                             includeRuleBook,
                                                               const CString&                   imageFileName,
                                                               const CString&                   hyperlink,
                                                               CDC*                             pDC,
                                                               PSS_Server*                      pServer) :
    m_pModel(pModel),
    m_pCtlr(pCtlr),
    m_pServer(pServer),
    m_pDC(pDC),
    m_URLName(urlName),
    m_ImageFileName(imageFileName),
    m_HyperLink(hyperlink),
    m_AbsolutePath(absolutePath),
    m_IncludeConceptor(includeConceptor),
    m_IncludeProcessReport(includeProcessReport),
    m_IncludeRuleBook(includeRuleBook)
{}
//---------------------------------------------------------------------------
PSS_InfoModelGraphicGeneration::~PSS_InfoModelGraphicGeneration()
{}
//---------------------------------------------------------------------------
