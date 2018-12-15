// ZBMenuObserverMsg.h: interface for the ZBMenuObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBMenuObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBMenuObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

class AFX_EXT_CLASS ZBMenuObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBMenuObserverMsg )

public:

    ZBMenuObserverMsg( int CommandID = 0 );
    virtual ~ZBMenuObserverMsg();

    int GetMessageID() const
    {
        return m_CommandID;
    };

    void SetMessageID( int value )
    {
        m_CommandID = value;
    };

private:

    int m_CommandID;
};

#endif // !defined(AFX_ZBMenuObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)