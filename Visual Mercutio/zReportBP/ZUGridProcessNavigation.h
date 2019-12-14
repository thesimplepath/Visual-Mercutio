/////////////////////////////////////////////////////////////////////////////
//@doc ZUGridProcessNavigation
//@module ZUGridProcessNavigation.h | Interface of the <c ZUGridProcessNavigation> class.
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
// <nl>Description:  ZUGridProcessNavigation navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUGridProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUGridProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelBP\ZUProcessNavigation.h"

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBOStreamGrid;

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUGridProcessNavigation : public ZUProcessNavigation
{
public:

    ZUGridProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUGridProcessNavigation();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnDoorSymbol(ZBBPDoorSymbol*            pSymbol);
    virtual bool OnPageSymbol(ZBBPPageSymbol*            pSymbol);
    virtual bool OnProcedureSymbol(ZBBPProcedureSymbol*        pSymbol);
    virtual bool OnProcessSymbol(ZBBPProcessSymbol*        pSymbol);
    virtual bool OnStartSymbol(ZBBPStartSymbol*            pSymbol);
    virtual bool OnStopSymbol(ZBBPStopSymbol*            pSymbol);
    virtual bool OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol*    pSymbol);
    virtual bool OnSymbol(PSS_Symbol*                    pSymbol);
    virtual bool OnLink(PSS_LinkSymbol*                pLink);

private:

    ZBOStreamGrid* m_postream;
};

#endif // !defined(AFX_ZUGridProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)