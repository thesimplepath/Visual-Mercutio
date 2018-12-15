// ZBCommandObserverMsg.h: interface for the ZBCommandObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ZBCommandObserverMsg_H__)
#define __ZBCommandObserverMsg_H__

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

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBCommandObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBCommandObserverMsg )

public:

    ZBCommandObserverMsg( int CommandID = 0 );
    virtual ~ZBCommandObserverMsg();

    int GetCommandID() const
    {
        return m_CommandID;
    };

    void SetCommandID( int value )
    {
        m_CommandID = value;
    };

private:

    int m_CommandID;
};

#endif // !defined(__ZBCommandObserverMsg_H__)