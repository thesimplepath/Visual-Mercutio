// ZUODSymbolManipulator.h: interface for the ZUODSymbolManipulator class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUODSYMBOLMANIPULATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)
#define AFX_ZUODSYMBOLMANIPULATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_

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

// Forward declaration
class ZBSymbolEdit;
class ZBSymbolLabel;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 4 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUODSymbolManipulator
{
public:

	ZUODSymbolManipulator();
	virtual ~ZUODSymbolManipulator();

// Manipulation functions
public:

	static ZBSymbolEdit* CreateEditText( CODComponent*	pSymbol,
										 const CString	AreaName,
										 const CString	EditName,
										 CODComponent*	pParent		= NULL );

	static ZBSymbolEdit* CreateAndReplaceEditText( CODComponent*	pSymbol,
												   const CString	EditName,
												   CODComponent*	pParent		= NULL );

	static ZBSymbolLabel* CreateAndReplaceLabelText( CODComponent*	pSymbol,
													 const CString	EditName,
													 bool			NotifyParent,
													 CODComponent*	pParent			= NULL );

	static BOOL RemoveSymbol( CODComponent* pSymbol, const CString SymbolName );
	static BOOL RemoveSymbol( CODComponent* pSymbol, CODComponent* pComponent );

	static CODComponent* FindSymbol( CODComponent* pSymbol, const CString SymbolName );
	static CODComponent* FindSymbolInChild( CODComponent* pSymbol, const CString SymbolName );
	static CODComponent* FindLabel( CODSymbolComponent* pSymbol, const CString SymbolName );

	static void MatchSymbolAreaName( CODComponent* pSymbol, CODComponent* pSrcSymbol );
	static void MatchSymbolAreaNameInChild( CODComponent* pSymbol, CODComponent* pSrcSymbol );

	static BOOL IsSymbolVisible( CODComponent* pSymbol, const CString SymbolName );
	static BOOL SetSymbolVisible( CODComponent* pSymbol, const CString SymbolName, BOOL bVisible );

	/////////////////////////////////////////////////////////////////////////////
	// Line and color manipulation
	static BOOL ChangeComponentLineColor( CODComponent* pSymbol, COLORREF col );
	static BOOL ChangeComponentLineWidth( CODComponent* pSymbol, int width );
	static BOOL ChangeComponentLineColorWidth( CODComponent* pSymbol, COLORREF col, int width );
	static BOOL ChangeLineColor( CODComponent* pSymbol, COLORREF col, const CString SymbolName = _T( "" ) );
	static BOOL ChangeLineWidth( CODComponent* pSymbol, int width, const CString SymbolName = _T( "" ) );
	static BOOL ChangeLabelLineWidth( CODSymbolComponent* pSymbol, int width, const CString LabelName = _T( "" ) );
	static BOOL ChangeLineStyle( CODComponent* pSymbol, int style, const CString SymbolName = _T( "" ) );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction SetLabelItalic.
	static BOOL SetLabelItalic( CODSymbolComponent*	pSymbol,
								BOOL				DoSetTextItalic,
								const CString		LabelName = _T( "" ) );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction ChangeLabelTextColor.
	static BOOL ChangeLabelTextColor( CODSymbolComponent*	pSymbol,
									  COLORREF				col,
									  const CString			LabelName = _T( "" ) );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction SetTextItalic.
	static BOOL SetTextItalic( CODComponent*	pSymbol,
							   BOOL				DoSetTextItalic,
							   const CString	SymbolName			= _T( "" ) );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction ChangeTextColor.
	static BOOL ChangeTextColor( CODComponent*	pSymbol,
								 COLORREF		col,
								 const CString	SymbolName	= _T( "" ) );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction GetTextColor.
	static COLORREF GetTextColor( CODComponent*	pSymbol,
								  const CString	SymbolName = _T( "" ) );

	static BOOL ChangeLabelLineColor( CODSymbolComponent*	pSymbol,
									  COLORREF				col,
									  const CString			LabelName = _T( "" ) );

	static BOOL ChangeLineColorWidth( CODComponent*	pSymbol,
									  COLORREF		col,
									  int			width,
									  const CString	SymbolName = _T( "" ) );

	static BOOL ChangeLabelLineColorWidth( CODSymbolComponent*	pSymbol,
										   COLORREF				col,
										   int					width,
										   const CString		LabelName = _T( "" ) );

	static void ApplyFormatFromObject( CODComponent*	pSymbol,
									   CODComponent&	Object,
									   bool				Font	= true,
									   bool				Fill	= true,
									   bool				Line	= true );

	static BOOL CopySymbolStyle( CODComponent* pSrcSymbol, CODComponent* pTrgSymbol );

	/////////////////////////////////////////////////////////////////////////////
	// Node and Edge Array manipulation
	static size_t KeepOnlySymbolsISA( CODNodeArray& Nodes, const CRuntimeClass* pClass );
	static size_t KeepOnlyLinksISA( CODEdgeArray& Edges, const CRuntimeClass* pClass );
	static bool HasSymbolsISA( CODNodeArray& Nodes, const CRuntimeClass* pClass );
	static bool HasLinksISA( CODEdgeArray& Edges, const CRuntimeClass* pClass );

	static size_t KeepFollowingSymbolsByPortName( const CString PortName, CODNodeArray& Nodes );
	static bool IsSymbolFollowingByPortName( CODSymbolComponent* pSymbol, const CString PortName );

	static size_t GetPortName( CODSymbolComponent* pSymbol, const CString PortName, CODPortSet& Ports );
	static size_t GetPortFollowingSymbols( CODPortComponent& Port, CODComponentSet& Set );
};

#endif // !defined(AFX_ZUODSYMBOLMANIPULATOR_H__C1668594_D42A_4E45_B15E_918C63D31752__INCLUDED_)