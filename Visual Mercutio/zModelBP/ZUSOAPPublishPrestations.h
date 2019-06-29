// **************************************************************************************************************
// *                                    Classe ZUSOAPPublishPrestations                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Création de la classe ZUSOAPPublishPrestations.                                *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des prestations vers Messenger.                                *
// **************************************************************************************************************

#if !defined(AFX_ZUSOAPPUBLISHPRESTATIONS_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)
#define AFX_ZUSOAPPUBLISHPRESTATIONS_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_

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

#include "zModel\ZBLogicalPrestationsEntity.h"
#include "ZBPublishMessengerModelInformation.h"

#include "zModel\ProcGraphModelDoc.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zSOAP\PSS_SoapPublisher_Prestations.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBLogicalPrestationsEntity;
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

class AFX_EXT_CLASS ZUSOAPPublishPrestations
{
public:

    ZUSOAPPublishPrestations( ZBPublishMessengerModelInformation* pInfo, ZILog* pLog = NULL );
    virtual ~ZUSOAPPublishPrestations();

    bool Publish();

private:

    void _PublishPrestations( ZBLogicalPrestationsEntity* p_Prestations  );

private:

    ZBPublishMessengerModelInformation*    m_pInfo;
    pPublishPrestations                    m_pp;
    ZILog*                                m_pLog;
};

#endif // !defined(AFX_ZUSOAPPUBLISHPRESTATIONS_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)