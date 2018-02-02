#if !defined(AFX_DIRTREECTRL_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_)
#define AFX_DIRTREECTRL_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// DirTreeCtrl.h : header file
#include "zBaseLib\ZITreeCtl.h"
#include "zBaseLib\ZNetResourceWrapper.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZIDirTreeCtrl : public ZITreeCtrl
{
// Construction
public:

	ZIDirTreeCtrl( bool IncludeFile = false );
	virtual ~ZIDirTreeCtrl();

// Operations
public:

	void	Initialize( const CString InitialPath = _T( "" ), bool clear = true, bool IncludeFile = false );
	void	Refresh();
	CString	GetSelectedDirectory();
	void	SetPath( const CString Path );
	bool	IsValid() const;
	
	virtual int GetIndexOfNoDropImage() const;

public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIDirTreeCtrl)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:

	//{{AFX_MSG(ZIDirTreeCtrl)
	afx_msg BOOL OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//Operators
private:

	CString GetItemPath( HTREEITEM hItem );
	bool	PopulateTree( CString sPath, HTREEITEM hParent );
	bool	EnumNetwork( HTREEITEM hParent );

	HTREEITEM InsertPathItem( HTREEITEM		hParent,
							  NETRESOURCE*	pNetResource,
							  CString		sText,
							  CString		FullName,
							  int			iImage,
							  int			iImageSelected	= -1 );

	HTREEITEM InsertFileItem( HTREEITEM		hParent,
							  NETRESOURCE*	pNetResource,
							  CString		sText,
							  CString		FullName,
							  int			iImage,
							  int			iImageSelected	= -1 );

	// JMR-MODIF - Le 31 août 2005 - Ajout de la fonction EmptyNetRessources.
	void EmptyNetRessources();

//Attributes
private:

	CImageList	m_ImageListTree;		//Item in the Tree image list

	HTREEITEM	m_hNetworkRoot;			//Network neighbourhood root

	CString		m_sPath;				//Highlighted path

	bool		m_IsValid;
	bool		m_IncludeFile;
	bool		m_HasBeenInitialized;
};

inline bool ZIDirTreeCtrl::IsValid() const
{
	return m_IsValid;
}

inline int ZIDirTreeCtrl::GetIndexOfNoDropImage() const
{
	return DRIVE_RAMDISK + 3;
}

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRTREECTRL_H__F5512005_305A_11D2_B989_00AA00AC7921__INCLUDED_)
