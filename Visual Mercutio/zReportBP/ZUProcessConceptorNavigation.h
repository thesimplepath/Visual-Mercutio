/////////////////////////////////////////////////////////////////////////////
//@doc ZUProcessConceptorNavigation
//@module ZUProcessConceptorNavigation.h | Interface of the <c ZUProcessConceptorNavigation> class.
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
// <nl>Created:         07/2001
// <nl>Description:  ZUProcessConceptorNavigation navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUProcessConceptorNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUProcessConceptorNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUProcessConceptorNavigation : public ZUProcessNavigation
{
public:
    //*@param pClass - the custom data class, can be NULL
    ZUProcessConceptorNavigation(PSS_ProcessGraphModelMdl*    pModel = NULL,
                                 void*                        pClass = NULL,
                                 PSS_ProcessGraphModelMdl*    pRootModel = NULL,
                                 const CString                domainName = _T(""),
                                 const CString                unitName = _T(""),
                                 BOOL                        bIncludeSynthesis = TRUE,
                                 BOOL                        bIncludeDetail = TRUE,
                                 BOOL                        bIncludeDeliverables = TRUE);

    virtual ~ZUProcessConceptorNavigation();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP*    pProcedure);
    virtual bool OnProcessSymbol(PSS_ProcessSymbolBP*    pSymbol);
    virtual bool OnSymbol(PSS_Symbol*               pSymbol);
    virtual bool OnLink(PSS_LinkSymbol*            pLink);

private:

    bool DisplayProcess();
    bool StartSection(CODNodeArray& Nodes);

private:

    ZBOStreamGrid*            m_postream;

    PSS_ProcessSymbolBP*        m_pPreviousProcess;
    PSS_ProcessGraphModelMdl*    m_pRootModel;

    CGXStyle                m_BlueStyle;
    CGXStyle                m_OrangeStyle;
    CGXStyle                m_GrayStyle;

    CGXStyle                m_BlackBorderStyle;
    CGXStyle                m_LeftOnlyBlackBorderStyle;
    CGXStyle                m_RightOnlyBlackBorderStyle;
    CGXStyle                m_TopOnlyBlackBorderStyle;
    CGXStyle                m_BottomOnlyBlackBorderStyle;

    CString                    m_DomainName;
    CString                    m_UnitName;

    BOOL                    m_IncludeSynthesis;
    BOOL                    m_IncludeDetail;
    BOOL                    m_IncludeDeliverables;

    CString                    m_CurrentProcessName;

    bool                    m_First;
};

#endif
