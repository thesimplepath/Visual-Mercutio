// ZBInfoModelGraphicGeneration.cpp: implementation of the ZBInfoModelGraphicGeneration class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBInfoModelGraphicGeneration.h"

#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphModelController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBInfoModelGraphicGeneration::ZBInfoModelGraphicGeneration(PSS_ProcessGraphModelMdl* pModel            /*= NULL*/,
                                                           PSS_ProcessGraphModelController* pCtlr    /*= NULL*/,
                                                           const CString URLName                    /*= ""*/,
                                                           bool AbsolutePath                        /*= true*/,
                                                           bool IncludeConceptor                    /*= true*/,
                                                           bool IncludeProcessReport                /*= true*/,
                                                           bool IncludeRuleBook                    /*= true*/,
                                                           const CString imageFileName                /*= ""*/,
                                                           const CString HyperLink                    /*= ""*/,
                                                           CDC* pDC                                /*= NULL*/,
                                                           PSS_Server* pServer                        /*= NULL*/)
    : m_pModel(pModel),
    m_pCtlr(pCtlr),
    m_URLName(URLName),
    m_AbsolutePath(AbsolutePath),
    m_IncludeConceptor(IncludeConceptor),
    m_IncludeProcessReport(IncludeProcessReport),
    m_IncludeRuleBook(IncludeRuleBook),
    m_ImageFileName(imageFileName),
    m_HyperLink(HyperLink),
    m_pDC(pDC),
    m_pServer(pServer)
{}

ZBInfoModelGraphicGeneration::~ZBInfoModelGraphicGeneration()
{}
