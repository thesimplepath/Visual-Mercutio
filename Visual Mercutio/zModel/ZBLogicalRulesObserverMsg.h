// ******************************************************************************************************************
// *                                      Classe ZBLogicalRulesObserverMsg                                            *
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZBLogicalRulesObserverMsg.                                *
// ******************************************************************************************************************
// * Cette classe est un observateur d'événements pour les classes de gestion des règles.                            *
// ******************************************************************************************************************

#if !defined(AFX_ZBLogicalRulesObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBLogicalRulesObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\PSS_ObserverMsg.h"

// Forward declarations
class ZBRulesEntity;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

const int UM_INITRULES = 450;
const int UM_REFRESHRULES = 451;
const int UM_CLEARRULES = 452;
const int UM_CLOSERULES = 453;

class AFX_EXT_CLASS ZBLogicalRulesObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBLogicalRulesObserverMsg)

public:

    ZBLogicalRulesObserverMsg(UINT                MessageID = 0,
                              ZBRulesEntity*    pEntity = NULL,
                              const CString    RootName = _T(""));

    virtual ~ZBLogicalRulesObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID(UINT value)
    {
        m_MessageID = value;
    };

    ZBRulesEntity* GetEntity() const
    {
        return m_pEntity;
    };

    void SetEntity(ZBRulesEntity* value)
    {
        m_pEntity = value;
    };

    CString GetRootName() const
    {
        return m_RootName;
    };

    void SetRootName(const CString value)
    {
        m_RootName = value;
    };

private:
    ZBRulesEntity* m_pEntity;
    CString        m_RootName;
    UINT           m_MessageID;
};

#endif
