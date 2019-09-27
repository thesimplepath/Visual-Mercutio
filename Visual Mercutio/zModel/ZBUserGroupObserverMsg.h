// ZBUserGroupObserverMsg.h: interface for the ZBUserGroupObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUserGroupObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBUserGroupObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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
class ZBUserEntity;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

const int UM_INITUSERGROUP            = 100;
const int UM_REFRESHUSERGROUP        = 101;
const int UM_CLEARUSERGROUP            = 102;
const int UM_CLOSEUSERGROUP            = 103;

class AFX_EXT_CLASS ZBUserGroupObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC( ZBUserGroupObserverMsg )

public:

    ZBUserGroupObserverMsg( UINT MessageID = 0, ZBUserEntity* pEntity = NULL, const CString RootName = _T( "" ) );
    virtual ~ZBUserGroupObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID( UINT value )
    {
        m_MessageID = value;
    };

    ZBUserEntity* GetpEntity() const
    {
        return m_pEntity;
    };

    void SetpEntity( ZBUserEntity* value )
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
    ZBUserEntity*    m_pEntity;
    CString            m_RootName;
};

#endif // !defined(AFX_ZBUserGroupObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)