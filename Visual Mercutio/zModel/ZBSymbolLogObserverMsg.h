// ZBSymbolLogObserverMsg.h: interface for the ZBSymbolLogObserverMsg class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSymbolLogObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBSymbolLogObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ObserverMsg.h"
#include "PSS_GenericSymbolErrorLine.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 août 2007 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBSymbolLogObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBSymbolLogObserverMsg)

public:
    ZBSymbolLogObserverMsg();

    ZBSymbolLogObserverMsg(PSS_GenericSymbolErrorLine ErrorLine);

    virtual ~ZBSymbolLogObserverMsg();

    PSS_GenericSymbolErrorLine& GetErrorLine();

    void SetErrorLine(PSS_GenericSymbolErrorLine value);

private:
    PSS_GenericSymbolErrorLine m_ErrorLine;
};

inline PSS_GenericSymbolErrorLine& ZBSymbolLogObserverMsg::GetErrorLine()
{
    return m_ErrorLine;
}

inline void ZBSymbolLogObserverMsg::SetErrorLine(PSS_GenericSymbolErrorLine value)
{
    m_ErrorLine = value;
}

#endif
