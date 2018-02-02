// **********************************************************************************************************
// *										  Classe ZVDocumentPageSetup									*
// **********************************************************************************************************
// * Cette classe permet la gestion du format de page du document. Elle permet de paramétrer une page,		*
// * et elle prend également en charge le contrôle de la validité de cette page par rapport au device		*
// * d'impression.																							*
// **********************************************************************************************************

#if !defined(AFX_ZVDOCUMENTPAGESETUP_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)
#define AFX_ZVDOCUMENTPAGESETUP_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_

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

#include "Define.h"
#include "ZVDocumentPageSetupDlg.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZVDocumentPageSetup
{
private:

	CString								sBkGndName;

	BOOL								bIsFormatDefined;
	BOOL								bIsCancelled;
	BOOL								bCanPrint;
	BOOL								bIsChecked;

	CSize								m_PaperSize;

	short								m_StandardSize;
	short								m_Orientation;

	ZVDocumentPageSetupDlg				m_PageSetupDlg;

	BOOL		GetPrinterSettings		( CSize& PaperSize, short& StandardSize, short& Orientation );

	void		ChangePrinterSettings	( short StandardSize, short Orientation );

public:

	ZVDocumentPageSetup();
	~ZVDocumentPageSetup();

	CString		GetBackGroundFilename	();

	CSize		GetDefaultPageDim		( CRect Margins );
	CSize		GetPaperSize			();

	short		GetStandardSize			();
	short		GetOrientation			();

	void		SetPaperSize			( CSize PaperSize );
	void		SetStandardSize			( short StandardSize );
	void		SetOrientation			( short Orientation );
	void		OnUserDefinePageFormat	();
	void		OnUpdatePrinterSettings	();

	BOOL		IsSupported				( short StandardSize );
	BOOL		IsFormatDefined			();
	BOOL		IsCancelled				();
	BOOL		CanPrint				();
};

#endif // !defined(AFX_ZVDOCUMENTPAGESETUP_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)