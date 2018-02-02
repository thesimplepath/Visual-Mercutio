// **********************************************************************************************************
// *										 Classe ZBBPTextZone											*
// **********************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Ajout de la classe ZBBPTextZone.											*
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage d'une zone de texte personnalisée.						*
// **********************************************************************************************************

#if !defined(AFX_ZBBPTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_)
#define AFX_ZBBPTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_

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

#include "zModel\ZBTextZone.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBBPTextZone : public ZBTextZone
{
	DECLARE_SERIAL( ZBBPTextZone )

public:

	ZBBPTextZone();
	~ZBBPTextZone();

	void Create( CPoint ptLog, CClientDC* dc );

	virtual BOOL InitializeStyle();

	virtual void Serialize( CArchive& ar );
};

#endif // AFX_ZBBPTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_