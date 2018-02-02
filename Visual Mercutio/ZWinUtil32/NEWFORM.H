// newform.h : header file

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"
#include "zBaseLib\TmplMng.h"
#include "BPropSht.h"
#include "GFormP.h"

#include "zWinUtil32\ZWinUtil32.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 13 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Define different type of dialog
enum DialogFormType
{
	StartForm,
	AttachForm,
	OpenForm,
	SelectForm
};

enum DialogFormExtensionType
{
	FormType,
	ProcessFormType,
	ModelFormType
};

/////////////////////////////////////////////////////////////////////////////
// ZINewFormPropertySheet property sheet

class AFX_EXT_CLASS ZINewFormPropertySheet : public ZIBasePropSheet	//## Inherits: <unnamed>
{
	DECLARE_DYNAMIC( ZINewFormPropertySheet )

public:

	ZINewFormPropertySheet( ZDTemplateManager* pTemplateManager );
	~ZINewFormPropertySheet();

	const CString GetRootCaption() const
	{
		return m_RootCaption;
	}

	void Initialize();
	void ClearContents();

protected:

	// Generated message map functions
	//{{AFX_MSG(ZINewFormPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ZINewFormPropertySheet( const ZINewFormPropertySheet &right );

	const ZINewFormPropertySheet & operator=( const ZINewFormPropertySheet &right );

private:

	CString				m_RootCaption;
	BOOL				m_FirstInitialization;
	ZDTemplateManager*	m_pTemplateManager;
};

/////////////////////////////////////////////////////////////////////////////
// ZINewForm dialog

class AFX_EXT_CLASS ZINewForm : public ZIWizardDialog
{
// Construction / Destruction
public:

	// Standard constructor
	ZINewForm( ZDTemplateManager*		pTemplateManager,
			   DialogFormType			Type,
			   DialogFormExtensionType	ExtensionType );

	~ZINewForm();

public:

	CString GetFileName();
	CString GetFormName();

	ZDTemplateFile* GetTemplateFilePtr();

	BOOL MustCopyFormat() const
	{
		return m_bCopyFormat;
	}

	// Dialog Data
	//{{AFX_DATA(ZINewForm)
	enum { IDD = IDD_NEWFORM };
	CStatic			m_Text;
	CButton			m_CopyFormatWnd;
	CButton			m_Button;
	CString			m_sComment;
	BOOL			m_bCopyFormat;
	CBitmapButton	m_MoveToGeneralTabBtn;
	//}}AFX_DATA

// Implementation
protected:

	// DDX/DDV support
	virtual void DoDataExchange( CDataExchange* pDX );

	// Generated message map functions
	//{{AFX_MSG(ZINewForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnMoveToGeneralTab();
	virtual void OnOK();
	afx_msg LONG OnCommentChange(UINT message, LONG lParam);
	afx_msg LONG OnFormsSelected(UINT message, LONG lParam);
	afx_msg LONG OnFormActivate(UINT message, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Implementation
private:

	DialogFormType 				m_Type;
	DialogFormExtensionType		m_ExtensionType;
	CString						m_SelectedFilename;
	CString						m_SelectedFormName;
	ZDTemplateFile*				m_pCurrentTemplateFile;
	ZDTemplateDir*				m_pCurrentTemplateDir;
	ZDTemplateManager*			m_pTemplateManager;
	ZINewFormPropertySheet* 	m_pSystemPropertySheet;
};

inline CString ZINewForm::GetFileName()
{
	return m_SelectedFilename;
}

inline CString ZINewForm::GetFormName()
{
	return m_SelectedFormName;
}

inline ZDTemplateFile* ZINewForm::GetTemplateFilePtr()
{
	return m_pCurrentTemplateFile;
}
