/////////////////////////////////////////////////////////////////////////////
//@doc ZUProcessNavigation
//@module ZUProcessNavigation.h | Interface of the <c ZUProcessNavigation> class.
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
// <nl>Created:         06/2001
// <nl>Description:  ZUProcessNavigation offers the possibility to navigate
//                     through process symbols
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zBaseSym\ZIBasicSymbolVisitor.h"

// Forward declaration
class ZILog;
class ZBSymbol;
class ZBLinkSymbol;
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class ZDProcessGraphModelMdl;
class ZILog;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUProcessNavigation : public ZIBasicSymbolVisitor
{
public:

    ZUProcessNavigation( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
    virtual ~ZUProcessNavigation();

    bool Navigate( ZDProcessGraphModelMdl* pModel, void* pClass );
    bool Navigate( ZDProcessGraphModelMdl* pModel );
    bool Navigate();

    // Call-back methods
    virtual bool OnStart()
    {
        return true;
    };

    virtual bool OnFinish()
    {
        return true;
    };

    virtual bool OnDoorSymbol( ZBBPDoorSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnPageSymbol( ZBBPPageSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnStartSymbol( ZBBPStartSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnStopSymbol( ZBBPStopSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnSymbol( ZBSymbol* pSymbol )
    {
        return true;
    };

    virtual bool OnLink( ZBLinkSymbol* pLink )
    {
        return true;
    };

    void SetLog( ZILog* pLog )
    {
        m_pLog = pLog;
    };

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate 
       algorithm 
       In this concrete class the Visit will On the
       BasicSymbol passes as an argument */
    virtual bool Visit( CODComponent& Symbol );

    size_t GetErrorCounter() const
    {
        return m_ErrorCounter;
    };

    size_t GetWarningCounter() const
    {
        return m_WarningCounter;
    };

protected:

    ZDProcessGraphModelMdl*    m_pModel;
    void*                    m_pClass;
    ZILog*                    m_pLog;

    size_t                    m_ErrorCounter;
    size_t                    m_WarningCounter;
};

#endif // !defined(AFX_ZUProcessNavigation_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)