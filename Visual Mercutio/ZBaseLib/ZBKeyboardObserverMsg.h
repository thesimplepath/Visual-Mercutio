// ZBKeyboardObserverMsg.h: interface for the ZBKeyboardObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBKeyboardObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBKeyboardObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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

class AFX_EXT_CLASS ZBKeyboardObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBKeyboardObserverMsg )

public:

    ZBKeyboardObserverMsg( UINT MessageID = 0, UINT Key = 0 );
    virtual ~ZBKeyboardObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID( UINT value )
    {
        m_MessageID = value;
    };

    UINT GetKey() const
    {
        return m_Key;
    };

    void SetKey( UINT value )
    {
        m_Key = value;
    };

private:

    UINT m_MessageID;
    UINT m_Key;
};

#endif // !defined(AFX_ZBKeyboardObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)