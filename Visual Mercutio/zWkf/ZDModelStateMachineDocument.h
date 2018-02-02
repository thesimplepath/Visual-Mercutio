#if !defined(AFX_ZDModelStateMachineDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDModelStateMachineDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDModelStateMachineDocument.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBStateMachineCollection.h"


#ifdef _ZWKFEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZDModelStateMachineDocument document

class AFX_EXT_CLASS ZDModelStateMachineDocument : public CDocument
{
	DECLARE_DYNCREATE(ZDModelStateMachineDocument)
public:
	ZDModelStateMachineDocument(ZBStateMachineCollection* pModelStateMachine = NULL);           // Public constructor since not used by dynamic creation
	virtual ~ZDModelStateMachineDocument();

// Operations
public:
	bool ReadFromFile( const CString Filename, ZBStateMachineCollection* pModelStateMachine = NULL );
	bool SaveToFile( const CString Filename, ZBStateMachineCollection* pModelStateMachine = NULL );

	bool IsLoaded() const
	{
		return m_IsLoaded;
	};
	void SetLoaded( bool value = true )
	{
		m_IsLoaded = value;
	};
/*
	virtual BOOL IsModified()
	{
		return CDocument::IsModified() || m_UserGroupEnvironment.IsModified();
	};
*/
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZDModelStateMachineDocument)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZDModelStateMachineDocument)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZBStateMachineCollection*	m_pStateMachineCollection;
	bool					m_IsLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDModelStateMachineDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
