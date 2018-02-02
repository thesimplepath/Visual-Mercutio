// **********************************************************************************************************
// *										Classe ZVDocumentPageSetupDlg									*
// **********************************************************************************************************
// * Cette classe mets à disposition la boîte de dialogue pour la sélection du format de page.				*
// **********************************************************************************************************

#if !defined(AFX_ZVDOCUMENTPAGESETUPDLG_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)
#define AFX_ZVDOCUMENTPAGESETUPDLG_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_

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

#include "Define.h"
#include "zBaseLibRes.h"
#include "ZWizard.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZVDocumentPageSetupDlg : public ZIWizardDialog
{
	DECLARE_DYNAMIC( ZVDocumentPageSetupDlg )

private:

	CSize								m_PaperSize;

	short								m_StandardSize;
	short								m_Orientation;

	CString								sBkGndName;

	void		UpdateDatas				();

public:

	ZVDocumentPageSetupDlg( CWnd* pParent = NULL );
	~ZVDocumentPageSetupDlg();

	CString		GetBackGroundFilename	();

	CSize		GetPaperSize			();

	short		GetStandardSize			();
	short		GetOrientation			();

	void		SetPaperSize			( CSize PaperSize );
	void		SetStandardSize			( short StandardSize );
	void		SetOrientation			( short Orientation );

	// Données de boîte de dialogue
	enum { IDD = IDD_WZ_DOCUMENT_PAGESETUP };

protected:

	virtual void DoDataExchange( CDataExchange* pDX );    // Prise en charge DDX/DDV

	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedPortrait();
	afx_msg void OnBnClickedLandscape();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtOpenfile();
	afx_msg void OnEnChangeEditFilename();
};

#endif // !defined(AFX_ZVDOCUMENTPAGESETUPDLG_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)