// ZBPropertyObserverMsg.h: interface for the ZBPropertyObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBPropertyObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBPropertyObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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


#include "zBaseLib\PSS_ObserverMsg.h"

// forward declarations
class ZIProperties;


#ifdef _ZPROPERTYEXPORT
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


class AFX_EXT_CLASS ZBPropertyObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBPropertyObserverMsg)
public:

public:
    ZBPropertyObserverMsg(ZIProperties* pProperties = NULL);
    virtual ~ZBPropertyObserverMsg();

    ZIProperties* GetProperties() const
    {
        return m_pProperties;
    };
    void SetProperties(ZIProperties* value)
    {
        m_pProperties = value;
    };

private:
    ZIProperties* m_pProperties;
};

#endif
