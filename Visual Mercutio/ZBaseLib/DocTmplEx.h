// DocTmplEx.h : header file

#if !defined(AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_)
#define AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _AFXEXT
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 mai 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#define MRU_RANGE unsigned( ID_FILE_MRU_LAST - ID_FILE_MRU_FIRST )

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx class

class AFX_EXT_CLASS ZDDocTemplateEx : public CMultiDocTemplate
{
	DECLARE_DYNAMIC( ZDDocTemplateEx )

// Constructors / Destructor
public:

	ZDDocTemplateEx( UINT			nIDResource,
					 CRuntimeClass*	pDocClass,
					 CRuntimeClass*	pFrameClass,
					 CRuntimeClass*	pViewClass,
					 UINT			nMenuId		= 0,
					 UINT			nMaxMRU		= _AFX_MRU_COUNT );

	virtual ~ZDDocTemplateEx();

// Attributes
public:

	UINT GetMenuID() const
	{
		return m_nMenuId;
	}

public:

	virtual void AddToRecentFileList( LPCTSTR lpszPathName );

// Implementation
public:

#ifdef _DEBUG
	virtual void Dump( CDumpContext& ) const;
	virtual void AssertValid() const;
#endif //_DEBUG

protected:

	void LoadStdProfileSettings( UINT nMaxMRU );
	void SaveStdProfileSettings();
	void OnUpdateRecentFileMenu( CCmdUI* pCmdUI );
	BOOL OnOpenRecentFile( UINT nID );

// Overridables
protected:

	// Route and dispatch standard command message types
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

protected:

	CRecentFileList*	m_pRecentFileList;
	UINT				m_nMenuId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_)
