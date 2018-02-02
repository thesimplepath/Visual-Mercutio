// ZIBasicSymbol.h: interface for the ZIBasicSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIBASICSYMBOL_H__1BFC6894_4B6B_4051_828A_15AC2BF8CFB8__INCLUDED_)
#define AFX_ZIBASICSYMBOL_H__1BFC6894_4B6B_4051_828A_15AC2BF8CFB8__INCLUDED_

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

//////////////////////////////////////////////////////////////////////
// Forward class definition
class ZBPropertyAttributes;
class ZBSymbolEdit;
class ZDProcessGraphPage;
class ZBUserEntity;
class ZBDynamicProperties;

#ifdef _ZBASESYMEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 17 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Global definitions

#define SplitterComponentLine1				_T( "ZC_SplitterLine1" )
#define SplitterComponentLine2				_T( "ZC_SplitterLine2" )
#define AttributeAreaComponentLabel			_T( "ZC_AttributeArea" )
#define CommentComponentControlLabel		_T( "ZC_CommentText" )
#define SymbolNameComponentControlLabel		_T( "ZC_SymbolName" )
#define EditAreaComponentControlLabel		_T( "ZC_EditArea" )

#define PortComponentLabel					_T( "ZC_Port" )
#define PortUPComponentLabel				_T( "ZC_PortUP" )
#define PortDOWNComponentLabel				_T( "ZC_PortDOWN" )
#define PortLEFTComponentLabel				_T( "ZC_PortLEFT" )
#define PortRIGHTComponentLabel				_T( "ZC_PortRIGHT" )

class AFX_EXT_CLASS ZIBasicSymbol
{
public:

	ZIBasicSymbol();
	virtual ~ZIBasicSymbol();

	// Return the unique object type ID
	virtual int GetObjectTypeID() const = 0;

	virtual CString GetSymbolComment() = 0;
	virtual BOOL SetSymbolComment( const CString value ) = 0;

	virtual CString GetSymbolName() = 0;
	virtual BOOL SetSymbolName( const CString value ) = 0;

	virtual int GetSymbolReferenceNumber() = 0;
	virtual CString GetSymbolReferenceNumberStr() = 0;
	virtual BOOL SetSymbolReferenceNumber( int value ) = 0;
	virtual BOOL SetSymbolReferenceNumberStr( const CString value ) = 0;

	virtual void EditSymbolName() = 0;

	virtual ZBSymbolEdit* CreateEditText( const CString AreaName,
										  const CString EditName,
										  CODComponent* pParent		= NULL ) = 0;

	virtual ZBSymbolEdit* CreateAndReplaceEditText( const CString EditName, CODComponent* pParent = NULL ) = 0;

	//////////////////////////////////////////////////////////////////////
	// Attributes management methods
	virtual bool AcceptDynamicAttributes() const = 0;
	virtual bool OnFillDefaultAttributes( ZBPropertyAttributes* pAttributes ) = 0;
	virtual bool OnChangeAttributes( ZBPropertyAttributes* pAttributes ) = 0;
	virtual CString GetAttributeString( ZBPropertyAttributes* pAttributes ) const = 0;
	virtual void RefreshAttributeAreaText(bool Redraw = false) = 0;

	virtual ZBDynamicProperties* GetDynamicPropertiesManager() = 0;

	// Return the Edit Box area
	virtual CODComponent* GetEditBoxArea() = 0;

	// Return the comment Edit
	virtual CODTextComponent* GetCommentTextEdit() = 0;

	// The comment can be edited
	virtual bool CommentTextEditReadOnly() const = 0;

	// Return the symbol name Edit
	virtual CODTextComponent* GetSymbolNameTextEdit() = 0;

	// The symbol name can be edited
	virtual bool SymbolNameTextEditReadOnly() const = 0;

	// Return the attribute Edit
	virtual CODTextComponent* GetAttributeTextEdit() = 0;
	virtual CODLineComponent* GetSplitter1() = 0;
	virtual CODLineComponent* GetSplitter2() = 0;

	// Copy the definition only
	virtual void CopySymbolDefinitionFrom( CODSymbolComponent& src ) = 0;

	virtual CString	GetNameOfReference() const = 0;
	virtual void SetNameOfReference( CString value ) = 0;

	// Return true if the symbol is local
	virtual bool IsLocal() const = 0;
	virtual void SetIsLocal( bool value = true ) = 0;

	//////////////////////////////////////////////////////////////////////
	// Area state methods
	virtual bool IncludeNameArea() const = 0;
	virtual bool IncludeDescriptionArea() const = 0;
	virtual bool IncludeAttributeArea() const = 0;

	virtual void DisplayNameArea( bool value = true ) = 0;
	virtual bool IsNameAreaVisible() const = 0;

	virtual void DisplayDescriptionArea( bool value = true ) = 0;
	virtual bool IsDescriptionsAreaVisible() const = 0;

	virtual void DisplayAttributeArea( bool value = true ) = 0;
	virtual bool IsAttributeAreaVisible() const = 0;

	//////////////////////////////////////////////////////////////////////
	// Symbol mouse methods
	virtual bool AcceptMouseInteraction() const = 0;
	virtual bool OnMouseMove	( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;
	virtual bool OnLButtonDblClk( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;
	virtual bool OnLButtonDown	( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;
	virtual bool OnLButtonUp	( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;
	virtual bool OnRButtonDown	( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;
	virtual bool OnRButtonUp	( UINT nFlags, CPoint point, CODController& Ctrl ) = 0;

	// Show the symbol in error
	virtual void ShowInError( bool value = true ) = 0;

	// Apply the format coming from another object
	virtual void ApplyFormatFromObject( CODSymbolComponent& Object,
										bool				Font	= true,
										bool				Fill	= true,
										bool				Line	= true ) = 0;

	// Get and Set the current line color
	virtual void SetCurrentLineColor( COLORREF value ) = 0;
	virtual COLORREF GetCurrentLineColor() const = 0;

	// Get and Set the current label color
	virtual void SetCurrentLabelColor( COLORREF value ) = 0;
	virtual COLORREF GetCurrentLabelColor() const = 0;

	// Used to find the local symbol of this reference
	virtual CODComponent* GetLocalSymbol() = 0;

	// Used to find the referenced symbol of this master symbol
	virtual CODComponentSet* GetReferenceSymbols() = 0;

	virtual bool IsReferenced() const = 0;
	virtual bool IsReferenceValid() const = 0;
	virtual void AssignReferenceSymbol( CODSymbolComponent* pReference ) = 0;
	virtual void RemoveReferenceSymbol() = 0;
	virtual CODSymbolComponent* GetSymbolReference() const = 0;

	// Retreive the owner symbol model
	virtual CODModel* GetOwnerModel() = 0;

	// Retreive the root symbol model
	virtual CODModel* GetRootModel() = 0;

	// Set the model modified flag to the specified value
	virtual void SetModifiedFlag( BOOL Value = TRUE ) = 0;

	/* Called after the object is created and on the desk 
	   return true if the object can be created or false if the
	   object must be destroyed immediatly */
	virtual bool OnPostCreation( CODModel* pModel = NULL, CODController* pCtrl = NULL ) = 0;

	/* Called before the object is deleted
	   return true if the object can be deleted */
	virtual bool OnPreDelete( CODModel* pModel = NULL, CODController* pCtrl = NULL ) = 0;

	/* Called after the double click occured on the object */
	virtual void OnPostDoubleClick( CODModel* pModel = NULL, CODController* pCtrl = NULL ) = 0;

	// Return true if the symbol can contain a child model
	virtual bool CanContainChildModel() const = 0;

	// Return true if the child model is a reference
	virtual bool IsChildModelRef() const = 0;

	// Return the right sub menu number
	virtual int GetRightSubMenu() const = 0;

	// Return the symbol index image
	virtual int GetIconIndex() const = 0;

	// Redraw the symbol
	virtual void RedrawSymbol() = 0;

	//////////////////////////////////////////////////////////////////////
	// External file and external application methods
	virtual bool AcceptExtApp() const = 0;
	virtual bool DoInsertExtApp( bool DisplayDialog = true ) = 0;

	virtual bool AcceptExtFile() const = 0;
	virtual bool DoInsertExtFile( bool DisplayDialog = true ) = 0;

	//////////////////////////////////////////////////////////////////////
	// Unit methods
	virtual bool HasUnit() const = 0;
	virtual CString GetUnitName() const = 0;
	virtual CString GetUnitGUID() const = 0;

	//////////////////////////////////////////////////////////////////////
	// Call-back on symbols
	virtual void OnSymbolNameChanged( CODComponent& Comp, const CString OldName ) = 0;
	virtual void OnPageNameChanged( ZDProcessGraphPage* pPage, const CString OldName ) = 0;
	virtual void OnUserEntityChanged( ZBUserEntity* pUserEntity, const CString OldName ) = 0;

protected:

	virtual CODLabelComponent*	CreateSymbolLabel() = 0;
	virtual CODTextComponent*	GetpNameEditText() = 0;
	virtual void				SetpNameEditText( CODTextComponent* value) = 0;
	virtual CODTextComponent*	GetpCommentEditText() = 0;
	virtual void				SetpCommentEditText(CODTextComponent* value) = 0;
};

#endif // !defined(AFX_ZIBASICSYMBOL_H__1BFC6894_4B6B_4051_828A_15AC2BF8CFB8__INCLUDED_)