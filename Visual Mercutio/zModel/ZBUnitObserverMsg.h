// ZBUnitObserverMsg.h: interface for the ZBUnitObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUnitObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBUnitObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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


#include "zBaseLib\ZIObserverMsg.h"

// forward declarations
class ZBSymbol;
class ZBUnit;
class ZBUnitManager;

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


class AFX_EXT_CLASS ZBUnitObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC(ZBUnitObserverMsg)
public:
    enum MessageActionType { NoAction, OpenUnit, CloseUnit, ActivateUnit, AddElement, RemoveElement, ChangedElement };

public:
    ZBUnitObserverMsg( MessageActionType ActionType = NoAction, ZBUnitManager* pUnitManager = NULL, ZBUnit* pUnit = NULL, ZBSymbol* pElement = NULL );
    virtual ~ZBUnitObserverMsg();

    MessageActionType GetActionType() const { return m_ActionType; };
    void SetActionType( MessageActionType value ) { m_ActionType = value; };

    ZBUnitManager*    GetpUnitManager() const { return m_pUnitManager; };
    void SetpUnitManager( ZBUnitManager* value ) { m_pUnitManager = value; };

    ZBUnit*    GetpUnit() const { return m_pUnit; };
    void SetpUnit( ZBUnit* value ) { m_pUnit = value; };

    ZBSymbol*    GetpElement() const { return m_pElement; };
    void SetpElement( ZBSymbol* value ) { m_pElement = value; };
        
private:
    MessageActionType            m_ActionType;
    ZBUnitManager*                m_pUnitManager;
    ZBUnit*                        m_pUnit;
    ZBSymbol*                    m_pElement;
};

#endif // !defined(AFX_ZBUnitObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
