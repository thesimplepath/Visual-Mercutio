// **********************************************************************************************************
// *										  Classe ZBTextZone												*
// **********************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Ajout de la classe ZBTextZone.											*
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage d'une zone de texte personnalisée.						*
// **********************************************************************************************************

#if !defined(AFX_ZBTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_)
#define AFX_ZBTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_

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

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

#define TEXTZONE_COLOR RGB( 255, 222, 159 )

class AFX_EXT_CLASS ZBTextZone : public CODTextComponent
{
	DECLARE_SERIAL( ZBTextZone )

public:

	ZBTextZone();
	~ZBTextZone();

	BOOL SetLineColor			( COLORREF Value	= RGB( 0, 0, 0) );
	BOOL SetLineTransparent		( BOOL Value		= FALSE );
	BOOL SetLineWidth			( int Value			= 1 );
	BOOL SetLineStyle			( int Value			= PS_SOLID );

	BOOL SetFillColor			( COLORREF Value	= RGB( 255, 255, 255 ) );
	BOOL SetFillTransparent		( BOOL Value		= FALSE );
	BOOL SetFillStyle			( int Value			= BS_SOLID );
	BOOL SetFillHatch			( int Value			= HS_BDIAGONAL );
	BOOL SetFillBackgroundMode	( int Value			= TRANSPARENT );
	BOOL SetFillBackgroundColor	( COLORREF Value	= RGB( 255, 255, 255 ) );

	BOOL SetFont				( CString Value		= _T( "Arial" ) );
	BOOL SetFontColor			( COLORREF Value	= RGB( 0, 0, 0 ) );
	BOOL SetFontSize			( int Value			= 10 );
	BOOL SetFontHeight			( int Value			= 10 );
	BOOL SetFontWeight			( int Value			= FW_NORMAL );
	BOOL SetItalic				( BOOL Value		= FALSE );
	BOOL SetUnderline			( BOOL Value		= FALSE );
	BOOL SetStrikeout			( BOOL Value		= FALSE );

	BOOL SetMultiline			( BOOL Value		= FALSE );
	BOOL SetUseWordbreak		( BOOL Value		= FALSE );
	BOOL SetVerticalAlignement	( int Value			= DT_VCENTER );
	BOOL SetHorizontalAlignement( int Value			= DT_CENTER );

	virtual BOOL InitializeStyle()
	{
		return TRUE;
	}

	virtual void Serialize( CArchive& ar );
};

#endif // AFX_ZBTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_