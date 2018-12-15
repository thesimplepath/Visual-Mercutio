/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckSesterceConsistency
//@module ZUCheckSesterceConsistency.h | Interface of the <c ZUCheckSesterceConsistency> class.
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
// <nl>Description:  ZUCheckSesterceConsistency deep sesterce check
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCheckSesterceConsistency_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCheckSesterceConsistency_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

// JMR-MODIF - Le 17 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUCheckSesterceConsistency : public ZIBasicSymbolVisitor
{
public:

    ZUCheckSesterceConsistency( ZDProcessGraphModelMdl* pModel = NULL, ZILog* pLog = NULL );
    virtual ~ZUCheckSesterceConsistency();

    bool CheckModel();

    size_t GetErrorCounter() const
    {
        return m_ErrorCounter;
    };

    size_t GetWarningCounter() const
    {
        return m_WarningCounter;
    };

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate 
       algorithm 
       In this concrete class the Visit will check the
       BasicSymbol passes as an argument */
    virtual bool Visit( CODComponent& Symbol );

private:

    bool CheckDoorSymbol            ( ZBBPDoorSymbol* pSymbol );
    bool CheckPageSymbol            ( ZBBPPageSymbol* pSymbol );
    bool CheckProcedureSymbol        ( ZBBPProcedureSymbol* pSymbol );
    bool CheckProcessSymbol            ( ZBBPProcessSymbol* pSymbol );
    bool CheckStartSymbol            ( ZBBPStartSymbol* pSymbol );
    bool CheckStopSymbol            ( ZBBPStopSymbol* pSymbol );
    bool CheckDeliverableLinkSymbol    ( ZBDeliverableLinkSymbol* pSymbol );
    bool CheckSymbol                ( ZBSymbol* pSymbol );
    bool CheckLink                    ( ZBLinkSymbol* pLink );

private:

    ZILog*                    m_pLog;
    ZDProcessGraphModelMdl* m_pModel;
    size_t                    m_ErrorCounter;
    size_t                    m_WarningCounter;
};

#endif // !defined(AFX_ZUCheckSesterceConsistency_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)