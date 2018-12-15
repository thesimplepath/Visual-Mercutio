// ZBFieldObserverMsg.h: interface for the ZBFieldObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBFieldObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBFieldObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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

#include "ZIObserverMsg.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class PlanFinObject;

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBFieldObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBFieldObserverMsg )

public:
    ZBFieldObserverMsg( UINT MessageID = 0, PlanFinObject* pObject = NULL );
    virtual ~ZBFieldObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID( UINT value )
    {
        m_MessageID = value;
    };

    PlanFinObject* GetpObject() const
    {
        return m_pObject;
    };

    void SetpObject( PlanFinObject* value )
    {
        m_pObject = value;
    };

private:

    UINT            m_MessageID;
    PlanFinObject*    m_pObject;
    CView*            m_pView;
};

#endif // !defined(AFX_ZBFieldObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)