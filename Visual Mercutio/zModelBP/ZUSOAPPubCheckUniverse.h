// **************************************************************************************************************
// *								   Classe ZUSOAPPubCheckUniverse											*
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe ZUSOAPPubCheckUniverse.								*
// **************************************************************************************************************
// * Cette classe prend en charge le test des référentiels, et permet de déterminer si la publication est		*
// * valide.																									*
// **************************************************************************************************************

#if !defined(AFX_ZUSOAPPUBCHECKUNIVERSE_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)
#define AFX_ZUSOAPPUBCHECKUNIVERSE_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_

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

#include "zSOAP\pCheckUniverse.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
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

class AFX_EXT_CLASS ZUSOAPPubCheckUniverse
{
public:

	ZUSOAPPubCheckUniverse( ZBPublishMessengerModelInformation* pInfo, ZILog* pLog = NULL );
	virtual ~ZUSOAPPubCheckUniverse();

	bool IsValid();

private:

	ZBPublishMessengerModelInformation*	m_pInfo;
	pCheckUniverse						m_cu;
	ZILog*								m_pLog;
};

#endif // !defined(AFX_ZUSOAPPUBCHECKUNIVERSE_H__D709CBA3_F30E_4D59_80D9_F6AADB7A8749__INCLUDED_)