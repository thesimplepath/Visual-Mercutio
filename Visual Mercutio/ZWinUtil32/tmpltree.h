//## begin module%3735CA150221.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3735CA150221.cm

//## begin module%3735CA150221.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%3735CA150221.cp

//## Module: TmplTree%3735CA150221; Package specification
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\TmplTree.h

#ifndef TmplTree_h
#define TmplTree_h 1

//## begin module%3735CA150221.additionalIncludes preserve=no
//## end module%3735CA150221.additionalIncludes

//## begin module%3735CA150221.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZITreeCtl.h"
//## end module%3735CA150221.includes

// TmplMng
#include "zBaseLib\TmplMng.h"

// Mfc
#include "Mfc.h"

// ZITmplTr
#include "ZITmplTr.h"

//## begin module%3735CA150221.declarations preserve=no
//## end module%3735CA150221.declarations

//## begin module%3735CA150221.additionalDeclarations preserve=yes
#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%3735CA150221.additionalDeclarations

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZCTemplateTreeCtrl%3735C8F3030B
//	This control is automatically filled with a Template
//	manager object.
//## Category: ZWinUtil library::Controls%3747C0280312
//## Subsystem: ZWinUtil%36DEE1730346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3735CA84018B;ZDTemplateManager { -> }
//## Uses: <unnamed>%38B97A5202BE;ZITemplateTree { -> }

class AFX_EXT_CLASS ZCTemplateTreeCtrl : public ZITreeCtrl	//## Inherits: <unnamed>%3735C92C0032
{
	DECLARE_DYNCREATE( ZCTemplateTreeCtrl )

public:

	ZCTemplateTreeCtrl( ZDTemplateManager* pTemplateManager = NULL, BOOL IncludeFiles = FALSE );
	~ZCTemplateTreeCtrl();

	void Initialize( ZDTemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE );

	// Re initialize the tree. It does not work if the tree has
	// never been initialized.
	void ReInitialize( ZDTemplateManager* pTemplateManager, BOOL IncludeFiles = FALSE );

	// Refresh the current tree.
	void Refresh();

	// Returns the selected item name.
	CString GetNameSelectedItem();

	// Returns a pointer to the selected template directory.
	// If no template directory selected, returns NULL.
	ZDTemplateDir* GetSelectedFolderItem();

	// Returns a pointer to the selected template file. If no
	// template file selected, returns NULL.
	ZDTemplateFile* GetSelectedFileItem();

	// Select an item. If selected and found, returns true.
	// Otherwise, returns false.
	BOOL SelectItemName( const CString Name );

	virtual void OnSelChangedEvent()
	{
	};

	virtual void OnClickEvent()
	{
	};

	virtual void OnDblClickEvent()
	{
	};

	virtual void OnRightClickEvent()
	{
	};

	virtual void OnRightDblClickEvent()
	{
	};

protected:

	virtual int GetIndexOfNoDropImage() const;

protected:

	// Additional Protected Declarations
	//## begin ZCTemplateTreeCtrl%3735C8F3030B.protected preserve=yes
	//{{AFX_MSG(ZCTemplateTreeCtrl)
	afx_msg LRESULT OnReloadTemplateManager( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam );
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//## end ZCTemplateTreeCtrl%3735C8F3030B.protected

private:

	//## Constructors (generated)
	ZCTemplateTreeCtrl( const ZCTemplateTreeCtrl &right );

	//## Assignment Operation (generated)
	const ZCTemplateTreeCtrl & operator=( const ZCTemplateTreeCtrl &right );

protected:

	// Data Members for Class Attributes

	ZDTemplateManager*	m_pTemplateManager;
	BOOL				m_IncludeFiles;
	ZITemplateTree		m_TemplateTree;

};

inline int ZCTemplateTreeCtrl::GetIndexOfNoDropImage() const
{
	return 2;
}

#endif