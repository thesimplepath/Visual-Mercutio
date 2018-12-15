// ZBPropertyItemObserverMsg.h: interface for the ZBPropertyItemObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBPropertyItemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBPropertyItemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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
class ZBProperty;


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


class AFX_EXT_CLASS ZBPropertyItemObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC(ZBPropertyItemObserverMsg)
public:

public:
    ZBPropertyItemObserverMsg( ZBProperty* pProperty = NULL );
    virtual ~ZBPropertyItemObserverMsg();

    ZBProperty* GetpProperty() const { return m_pProperty; };
    void SetpProperty( ZBProperty* value ) { m_pProperty = value; };

private:
    ZBProperty*        m_pProperty;
};

#endif // !defined(AFX_ZBPropertyItemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
