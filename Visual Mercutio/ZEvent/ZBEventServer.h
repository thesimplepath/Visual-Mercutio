// ZBEventServer.h: interface for the ZBEventServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEventServer_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBEventServer_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

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


#include "ZBEvent.h"

enum EventResult { EventNF, EventImported, EventRejected, EventLogAdded, EventLogProblem  };


#ifdef _ZEVENTEXPORT
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


class AFX_EXT_CLASS ZBEventServer : public ZBEvent  
{
public:
    ZBEventServer();
    ZBEventServer( COleDateTime Time, CString Filename, EventResult EventResultValue );
    virtual ~ZBEventServer();
    ZBEventServer(const ZBEventServer &right);
    const ZBEventServer & operator=(const ZBEventServer &right);
    CString        GetFilename() const { return m_Filename; };
    EventResult    GetEventResult() const { return m_EventResult; };
    CString        GetEventResultStr() const;

protected:
    CString            m_Filename;
    EventResult        m_EventResult;
};


//#undef  AFX_DATA
//#define AFX_DATA


#endif // !defined(AFX_ZBEventServer_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
