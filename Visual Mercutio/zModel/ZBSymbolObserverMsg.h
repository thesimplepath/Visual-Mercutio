// ZBSymbolObserverMsg.h: interface for the ZBSymbolObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSymbolObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBSymbolObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ObserverMsg.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBSymbolObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBSymbolObserverMsg)
public:
    enum MessageActionType
    {
        NoAction, ElementHasChanged, NameHasChanged, DescriptionHasChanged, ElementSelected
    };

public:
    ZBSymbolObserverMsg(MessageActionType ActionType = NoAction, CODComponent* pElement = NULL);
    ZBSymbolObserverMsg(int SymbolRef, MessageActionType ActionType = NoAction);
    virtual ~ZBSymbolObserverMsg();

    MessageActionType GetActionType() const
    {
        return m_ActionType;
    };
    void SetActionType(MessageActionType value)
    {
        m_ActionType = value;
    };

    CODComponent* GetElement() const
    {
        return m_pElement;
    };
    void SetElement(CODComponent* value)
    {
        m_pElement = value;
    };

    int GetSymbolRef() const
    {
        return m_SymbolRef;
    };
    void SetSymbolRef(int value)
    {
        m_SymbolRef = value;
    };

private:
    MessageActionType            m_ActionType;
    CODComponent*                m_pElement;
    int                            m_SymbolRef;
};

#endif
