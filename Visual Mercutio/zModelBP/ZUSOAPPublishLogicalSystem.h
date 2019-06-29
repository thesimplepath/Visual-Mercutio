// ZUSOAPPublishLogicalSystem.h: interface for the ZUSOAPPublishLogicalSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSOAPPUBLISHLOGICALSYSTEM_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)
#define AFX_ZUSOAPPUBLISHLOGICALSYSTEM_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_

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

#include "zSOAP\PSS_SoapPublisher_System.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBLogicalSystemEntity;
class ZBPublishMessengerModelInformation;
class ZILog;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUSOAPPublishLogicalSystem
{
public:

    ZUSOAPPublishLogicalSystem( ZBPublishMessengerModelInformation* pInfo, ZILog* pLog = NULL );
    virtual ~ZUSOAPPublishLogicalSystem();

    bool Publish();

private:

    void _PublishLogicalSystem( ZBLogicalSystemEntity* pSystem );

private:

    ZBPublishMessengerModelInformation* m_pInfo;
    PSS_SoapPublisher_System            m_PubSys;
    ZILog*                              m_pLog;
};

#endif // !defined(AFX_ZUSOAPPUBLISHLOGICALSYSTEM_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)