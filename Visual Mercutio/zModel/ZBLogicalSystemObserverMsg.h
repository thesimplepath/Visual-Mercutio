// ZBLogicalSystemObserverMsg.h: interface for the ZBLogicalSystemObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBLogicalSystemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBLogicalSystemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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
class ZBSystemEntity;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), netttoyage du code inutile. (En commentaires)

const int UM_INITLOGICALSYSTEM        = 200;
const int UM_REFRESHLOGICALSYSTEM    = 201;
const int UM_CLEARLOGICALSYSTEM        = 202;
const int UM_CLOSELOGICALSYSTEM        = 203;

class AFX_EXT_CLASS ZBLogicalSystemObserverMsg : public ZIObserverMsg  
{
    DECLARE_DYNAMIC( ZBLogicalSystemObserverMsg )

public:

    ZBLogicalSystemObserverMsg( UINT MessageID = 0, ZBSystemEntity* pEntity = NULL, const CString RootName = _T( "" ) );
    virtual ~ZBLogicalSystemObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID( UINT value )
    {
        m_MessageID = value;
    };

    ZBSystemEntity* GetpEntity() const
    {
        return m_pEntity;
    };

    void SetpEntity( ZBSystemEntity* value )
    {
        m_pEntity = value;
    };

    CString GetRootName() const
    {
        return m_RootName;
    };

    void SetRootName( const CString value )
    {
        m_RootName = value;
    };

private:

    UINT            m_MessageID;
    ZBSystemEntity*    m_pEntity;
    CString            m_RootName;
};

#endif // !defined(AFX_ZBLogicalSystemObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)