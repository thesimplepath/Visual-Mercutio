// ******************************************************************************************************************
// *                                      Classe ZBLogicalPrestationsObserverMsg                                    *
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZBLogicalPrestationsObserverMsg.                            *
// ******************************************************************************************************************
// * Cette classe est un observateur d'événements pour les classes de gestion des prestations.                        *
// ******************************************************************************************************************

#if !defined(AFX_ZBLogicalPrestationsObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_)
#define AFX_ZBLogicalPrestationsObserverMsg_H__31A212D8_7CA2_4BEB_9709_8C785F4909B3__INCLUDED_

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
class ZBPrestationsEntity;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

const int UM_INITPRESTATIONS = 400;
const int UM_REFRESHPRESTATIONS = 401;
const int UM_CLEARPRESTATIONS = 402;
const int UM_CLOSEPRESTATIONS = 403;

class AFX_EXT_CLASS ZBLogicalPrestationsObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(ZBLogicalPrestationsObserverMsg)

public:

    ZBLogicalPrestationsObserverMsg(UINT                    MessageID = 0,
                                    ZBPrestationsEntity*    pEntity = NULL,
                                    const CString            RootName = _T(""));

    virtual ~ZBLogicalPrestationsObserverMsg();

    UINT GetMessageID() const
    {
        return m_MessageID;
    };

    void SetMessageID(UINT value)
    {
        m_MessageID = value;
    };

    ZBPrestationsEntity* GetEntity() const
    {
        return m_pEntity;
    };

    void SetEntity(ZBPrestationsEntity* value)
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
    ZBPrestationsEntity* m_pEntity;
    CString              m_RootName;
    UINT                 m_MessageID;
};

#endif
