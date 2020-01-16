/////////////////////////////////////////////////////////////////////////////
//@doc ZUSynthesisNavigation
//@module ZUSynthesisNavigation.h | Interface of the <c ZUSynthesisNavigation> class.
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
// <nl>Description:  ZUSynthesisNavigation navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSynthesisNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUSynthesisNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUSynthesisNavigation : public ZUProcessNavigation
{
public:
    //*@param pClass - the custom data class, can be NULL
    ZUSynthesisNavigation(PSS_ProcessGraphModelMdl*    pModel = NULL,
                          void*                    pClass = NULL,
                          PSS_ProcessGraphModelMdl*    pRootModel = NULL,
                          const CString            domainName = _T(""),
                          const CString            unitName = _T(""));

    virtual ~ZUSynthesisNavigation();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(ZBBPProcedureSymbol*    pSymbol);
    virtual bool OnProcessSymbol(ZBBPProcessSymbol*    pSymbol);
    virtual bool OnSymbol(PSS_Symbol*                pSymbol);
    virtual bool OnLink(PSS_LinkSymbol*            pLink);

private:

    ZBOStreamGrid*            m_postream;
    CGXStyle                m_BlueStyle;

    PSS_ProcessGraphModelMdl*    m_pRootModel;

    CString                    m_DomainName;
    CString                    m_UnitName;
    CString                    m_CurrentProcessName;
};

#endif
