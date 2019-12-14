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

// processsoft
#include "zBaseSym\PSS_BasicSymbolVisitor.h"

// class name mapping
#ifndef PSS_Symbol
    //#define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Log;
class PSS_Symbol;
class PSS_LinkSymbol;
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_Log;

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

class AFX_EXT_CLASS ZUProcessNavigation : public PSS_BasicSymbolVisitor
{
public:

    ZUProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUProcessNavigation();

    bool Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass);
    bool Navigate(PSS_ProcessGraphModelMdl* pModel);
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

    virtual bool OnDoorSymbol(ZBBPDoorSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnPageSymbol(ZBBPPageSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnProcessSymbol(ZBBPProcessSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnStartSymbol(ZBBPStartSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnStopSymbol(ZBBPStopSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
    {
        return true;
    };

    virtual bool OnSymbol(PSS_Symbol* pSymbol)
    {
        return true;
    };

    virtual bool OnLink(PSS_LinkSymbol* pLink)
    {
        return true;
    };

    void SetLog(PSS_Log* pLog)
    {
        m_pLog = pLog;
    };

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate
       algorithm
       In this concrete class the Visit will On the
       BasicSymbol passes as an argument */
    virtual bool Visit(CODComponent& Symbol);

    size_t GetErrorCounter() const
    {
        return m_ErrorCounter;
    };

    size_t GetWarningCounter() const
    {
        return m_WarningCounter;
    };

protected:

    PSS_ProcessGraphModelMdl* m_pModel;
    void*                     m_pClass;
    PSS_Log*                  m_pLog;

    size_t                    m_ErrorCounter;
    size_t                    m_WarningCounter;
};

#endif
