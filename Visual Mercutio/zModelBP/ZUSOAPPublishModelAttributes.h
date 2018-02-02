/////////////////////////////////////////////////////////////////////////////
//@doc ZUSOAPPublishModelAttributes
//@module ZUSOAPPublishModelAttributes.h | Interface of the <c ZUSOAPPublishModelAttributes> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 07/2001
// <nl>Description:  ZUSOAPPublishModelAttributes navigates through the process and
//					 publish the symbol attributes to the SOAP Server
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSOAPPublishModelAttributes_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUSOAPPublishModelAttributes_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zModel\ZUModelNavigation.h"

#include "zSOAP\pPublishAttribDef.h"

#include "zProperty\ZBProperty.h"

// JMR-MODIF - Le 21 juin 2006 - Ajout de l'en-tête ZBPublishMessengerModelInformation.h
#include "ZBPublishMessengerModelInformation.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBPublishMessengerModelInformation;

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

/////////////////////////////////////////////////////////////////////////////
// ZUSOAPPublishModelAttributes

class AFX_EXT_CLASS ZUSOAPPublishModelAttributes : public ZUModelNavigation
{
public:

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_pInfo dans le constructeur.
	ZUSOAPPublishModelAttributes( ZBPublishMessengerModelInformation*	m_pInfo,
								  ZDProcessGraphModelMdl*				pModel		= NULL,
								  void*									pClass		= NULL );

	virtual ~ZUSOAPPublishModelAttributes();

	// Call-back methods
	virtual bool OnStart	();
	virtual bool OnFinish	();
	virtual bool OnSymbol	( ZBSymbol* pSymbol );
	virtual bool OnLink		( ZBLinkSymbol* pLink );

private:

	void PublishAttribDef	( ZBPropertySet& PropSet );
	bool KeyExist			( int key );

private:

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_pInfo.
	ZBPublishMessengerModelInformation*	m_pInfo;

	pPublishAttribDef					m_pa;

	int									m_IDArray[500];

	CString								m_MessengerAddress;
};

#endif // !defined(AFX_ZUSOAPPublishModelAttributes_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)