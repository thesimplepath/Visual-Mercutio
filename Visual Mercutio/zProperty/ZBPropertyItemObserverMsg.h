// ZBPropertyItemObserverMsg.h: interface for the ZBPropertyItemObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBPropertyItemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBPropertyItemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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

// old class name mapping
#ifndef PSS_Property
    #define PSS_Property ZBProperty
#endif

// forward class declarations
class PSS_Property;

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZBPropertyItemObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBPropertyItemObserverMsg)
public:

public:
    ZBPropertyItemObserverMsg(PSS_Property* pProperty = NULL);
    virtual ~ZBPropertyItemObserverMsg();

    PSS_Property* GetProperty() const
    {
        return m_pProperty;
    };
    void SetProperty(PSS_Property* value)
    {
        m_pProperty = value;
    };

private:
    PSS_Property* m_pProperty;
};

#endif
