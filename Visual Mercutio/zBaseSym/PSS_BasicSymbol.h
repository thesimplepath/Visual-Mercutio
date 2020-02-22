/****************************************************************************
 * ==> PSS_BasicSymbol -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic symbol interface                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicSymbolH
#define PSS_BasicSymbolH

#if _MSC_VER > 1000
#pragma once
#endif

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// class name mapping
#ifndef PSS_SymbolEdit
    #define PSS_SymbolEdit ZBSymbolEdit
#endif
#ifndef PSS_ProcessGraphPage
    #define PSS_ProcessGraphPage ZDProcessGraphPage
#endif
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif

// forward class definition
class ZBPropertyAttributes;
class PSS_SymbolEdit;
class PSS_ProcessGraphPage;
class PSS_UserEntity;
class ZBDynamicProperties;

#ifdef _ZBASESYMEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_SplitterComponentLine1          _T("ZC_SplitterLine1")
#define M_SplitterComponentLine2          _T("ZC_SplitterLine2")
#define M_AttributeAreaComponentLabel     _T("ZC_AttributeArea")
#define M_CommentComponentControlLabel    _T("ZC_CommentText")
#define M_SymbolNameComponentControlLabel _T("ZC_SymbolName")
#define M_EditAreaComponentControlLabel   _T("ZC_EditArea")
#define M_PortComponentLabel              _T("ZC_Port")
#define M_PortUPComponentLabel            _T("ZC_PortUP")
#define M_PortDOWNComponentLabel          _T("ZC_PortDOWN")
#define M_PortLEFTComponentLabel          _T("ZC_PortLEFT")
#define M_PortRIGHTComponentLabel         _T("ZC_PortRIGHT")
//---------------------------------------------------------------------------

/**
* Basic symbol interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicSymbol
{
    public:
        PSS_BasicSymbol();
        virtual ~PSS_BasicSymbol();

        /**
        * Gets the object type unique identifier
        *@return the object type unique identifier
        */
        virtual int GetObjectTypeID() const = 0;

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual CString GetSymbolName() const = 0;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        */
        virtual BOOL SetSymbolName(const CString& value) = 0;

        /**
        * Gets the symbol comment
        *@return the symbol comment
        */
        virtual CString GetSymbolComment() const = 0;

        /**
        * Sets the symbol comment
        *@param value - the symbol comment
        */
        virtual BOOL SetSymbolComment(const CString& value) = 0;

        /**
        * Gets the symbol reference number
        *@return the symbol reference number
        */
        virtual int GetSymbolReferenceNumber() const = 0;

        /**
        * Sets the symbol reference number
        *@param value - the symbol reference number
        */
        virtual BOOL SetSymbolReferenceNumber(int value) = 0;

        /**
        * Gets the symbol reference number as string
        *@return the symbol reference number as string
        */
        virtual CString GetSymbolReferenceNumberStr() const = 0;

        /**
        * Sets the symbol reference number as string
        *@param value - the symbol reference number as string
        */
        virtual BOOL SetSymbolReferenceNumberStr(const CString& value) = 0;

        /**
        * Edits the symbol name
        */
        virtual void EditSymbolName() = 0;

        /**
        * Creates the text editor
        *@param areaName - area name
        *@param editName - edit name
        *@param pParent - parent window, can be NULL
        *@return the text editor, NULL on error
        */
        virtual PSS_SymbolEdit* CreateEditText(const CString& areaName,
                                               const CString& editName,
                                               CODComponent*  pParent = NULL) = 0;

        /**
        * Creates a new text editor and replaces the existing one
        *@param editName - edit name
        *@param pParent - parent window, can be NULL
        *@return the text editor, NULL on error
        */
        virtual PSS_SymbolEdit* CreateAndReplaceEditText(const CString& editName, CODComponent* pParent = NULL) = 0;

        /**
        * Checks if the symbol accepts the dynamic attributes
        *@return true if the symbol accepts the dynamic attributes, otherwise false
        */
        virtual bool AcceptDynamicAttributes() const = 0;

        /**
        * Called when the default attributes are filled
        *@param pAttributes - attributes
        *@return true if the attributes are autorized to be filled, otherwise false
        */
        virtual bool OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes) = 0;

        /**
        * Called when the attributes are changed
        *@param pAttributes - attributes
        *@return true if the attributes are autorized to change, otherwise false
        */
        virtual bool OnChangeAttributes(ZBPropertyAttributes* pAttributes) = 0;

        /**
        * Gets the attributes as string
        *@param pAttributes - attributes
        *@return the attributes as string
        */
        virtual CString GetAttributeString(ZBPropertyAttributes* pAttributes) const = 0;

        /**
        * Refreshes the attributes text area
        *@param redraw - if true, the attribute text area will also be redrawn
        */
        virtual void RefreshAttributeTextArea(bool redraw = false) = 0;

        /**
        * Gets the dynamic properties manager
        *@return the dynamic properties manager
        */
        virtual ZBDynamicProperties* GetDynamicPropertiesManager() = 0;

        /**
        * Gets the edit box area
        *@return the edit box area
        */
        virtual CODComponent* GetEditBoxArea() = 0;

        /**
        * Gets the comment text edit box
        *@return the comment text edit box
        */
        virtual CODTextComponent* GetCommentTextEdit() = 0;

        /**
        * Checks if the comment text edit box is read-only
        *@return true if the comment text edit box is read-only, otherwise flase
        */
        virtual bool CommentTextEditReadOnly() const = 0;

        /**
        * Gets the symbol name text edit box
        *@return the symbol name text edit box
        */
        virtual CODTextComponent* GetSymbolNameTextEdit() = 0;

        /**
        * Checks if th symbol name edit box is read-only
        *@return true if th symbol name edit box is read-only, otherwise false
        */
        virtual bool SymbolNameTextEditReadOnly() const = 0;

        /**
        * Gets the attribute text edit box
        *@return the attribute text edit box
        */
        virtual CODTextComponent* GetAttributeTextEdit() = 0;

        /**
        * Gets the first splitter
        *@return the first splitter
        */
        virtual CODLineComponent* GetSplitter1() = 0;

        /**
        * Gets the second splitter
        *@return the second splitter
        */
        virtual CODLineComponent* GetSplitter2() = 0;

        /**
        * Copies the symbol definition from another component
        *@param src - source symbol to copy from
        */
        virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src) = 0;

        /**
        * Gets the reference name
        *@return the reference name
        */
        virtual CString GetReferenceName() const = 0;

        /**
        * Sets the reference name
        *@param value - the reference name
        */
        virtual void SetReferenceName(const CString& value) = 0;

        /**
        * Checks if the symbol is local
        *@return true if the symbol is local, otherwise false
        */
        virtual bool IsLocal() const = 0;

        /**
        * Sets the symbol as local
        *@param value - if true, the symbol is local
        */
        virtual void SetIsLocal(bool value = true) = 0;

        /**
        * Checks if the name area should be included
        *@return true if the name area should be included, otherwise false
        */
        virtual bool IncludeNameArea() const = 0;

        /**
        * Checks if the description area should be included
        *@return true if the description area should be included, otherwise false
        */
        virtual bool IncludeDescriptionArea() const = 0;

        /**
        * Checks if the attribute area should be included
        *@return true if the attribute area should be included, otherwise false
        */
        virtual bool IncludeAttributeArea() const = 0;

        /**
        * Shows or hides the name area
        *@param value - if true, the name area will be shown
        */
        virtual void ShowNameArea(bool value = true) = 0;

        /**
        * Checks if the name area is visible
        *@return true if the name area is visible, otherwise false
        */
        virtual bool IsNameAreaVisible() const = 0;

        /**
        * Shows or hides the description area
        *@param value - if true, the description area will be shown
        */
        virtual void ShowDescriptionArea(bool value = true) = 0;

        /**
        * Checks if the description area is visible
        *@return true if the description area is visible, otherwise false
        */
        virtual bool IsDescriptionsAreaVisible() const = 0;

        /**
        * Shows or hides the attributes area
        *@param value - if true, the attributes area will be shown
        */
        virtual void ShowAttributeArea(bool value = true) = 0;

        /**
        * Checks if the attributes area is visible
        *@return true if the attributes area is visible, otherwise false
        */
        virtual bool IsAttributeAreaVisible() const = 0;

        /**
        * Checks if the mouse interactions are accepted by the symbol
        *@return true if the mouse interactions are accepted by the symbol, otherwise false
        */
        virtual bool AcceptMouseInteraction() const = 0;

        /**
        * Called when the mouse moves above the symbol
        *@param flags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Called when the symbol is double clicked with left mouse button
        *@param flags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDblClk(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Called when the left mouse button is down on the symbol
        *@param flags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Called when the left mouse button is up on the symbol
        *@param flags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Called when the right mouse button is down on the symbol
        *@param flags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnRButtonDown(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Called when the right mouse button is up on the symbol
        *@param nFlags - mouse state flags
        *@param point - mouse position in pixels
        *@param ctrl - controller
        *@return true on success, otherwise false
        */
        virtual bool OnRButtonUp(UINT flags, const CPoint& point, CODController& ctrl) = 0;

        /**
        * Shows the symbol in error state
        *@param value - if true, the symbol will be shown in error state, otherwise in normal state
        */
        virtual void ShowInError(bool value = true) = 0;

        /**
        * Applies the format from another object
        *@param object - source object
        *@param font - if true, the font properties will be copied
        *@param fill - if true, the fill properties will be copied
        *@param line - if true, the line properties will be copied
        */
        virtual void ApplyFormatFromObject(CODSymbolComponent& object, bool font = true, bool fill = true, bool line = true) = 0;

        /**
        * Gets the line color
        *@return the line color
        */
        virtual COLORREF GetCurrentLineColor() const = 0;

        /**
        * Sets the line color
        *@param value - the line color
        */
        virtual void SetCurrentLineColor(COLORREF value) = 0;

        /**
        * Gets the label color
        *@return the label color
        */
        virtual COLORREF GetCurrentLabelColor() const = 0;

        /**
        * Sets the label color
        *@param value - the label color
        */
        virtual void SetCurrentLabelColor(COLORREF value) = 0;

        /**
        * Gets the local symbol
        *@return the local symbol
        */
        virtual CODComponent* GetLocalSymbol() = 0;

        /**
        * Gets the referenced symbols
        *@return the referenced symbols
        */
        virtual CODComponentSet* GetReferenceSymbols() = 0;

        /**
        * Checks if the symbol is referenced
        *@return true if the symbol is referenced, otherwise false
        */
        virtual bool IsReferenced() const = 0;

        /**
        * Checks if the reference is valid
        *@return true if the reference is valid, otherwise false
        */
        virtual bool IsReferenceValid() const = 0;

        /**
        * Assigns a reference symbol
        *@param pReference - the reference symbol to assign
        */
        virtual void AssignReferenceSymbol(CODSymbolComponent* pReference) = 0;

        /**
        * Removes the reference symbol
        */
        virtual void RemoveReferenceSymbol() = 0;

        /**
        * Gets the reference symbol
        *@return the reference symbol, NULL if no reference symbol or on error
        */
        virtual CODSymbolComponent* GetSymbolReference() const = 0;

        /**
        * Gets the root model
        *@return the root model, NULL if not found or on error
        */
        virtual CODModel* GetRootModel() = 0;

        /**
        * Gets the owner model
        *@return the owner model, NULL if not found or on error
        */
        virtual CODModel* GetOwnerModel() = 0;

        /**
        * Sets the model modified flag
        *@param value - if TRUE, the symbol is modified
        */
        virtual void SetModifiedFlag(BOOL Value = TRUE) = 0;

        /**
        * Called after the symbol is created and on the desk
        *@param pModel - newly created symbol model
        *@param pCtrl - model controller
        *@return true if the object can be created, false if the object must be destroyed immediatly
        */
        virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL) = 0;

        /**
        * Called before the symbol is deleted
        *@param pModel - currently deleting symbol model
        *@param pCtrl - model controller
        *@return true if the object can be deleted, otherwise false
        */
        virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL) = 0;

        /**
        * Called after the double click occurred on the symbol
        *@param pModel - double-clicked symbol model
        *@param pCtrl - model controller
        */
        virtual void OnPostDoubleClick(CODModel* pModel = NULL, CODController* pCtrl = NULL) = 0;

        /**
        * Checks if the symbol can contain a child model
        *@return true if the symbol can contain a child model, otherwise false
        */
        virtual bool CanContainChildModel() const = 0;

        /**
        * Gets if the child model is a reference
        *@return true if the child model is a reference, otherwise false
        */
        virtual bool IsChildModelRef() const = 0;

        /**
        * Gets the right sub menu number
        *@return the right sub menu number
        */
        virtual int GetRightSubMenu() const = 0;

        /**
        * Gets the symbol image index
        *@return the symbol image index
        */
        virtual int GetIconIndex() const = 0;

        /**
        * Redraws the symbol
        */
        virtual void RedrawSymbol() = 0;

        /**
        * Checks if external applications can be accepted
        *@return true if external applications can be accepted, otherwise false
        */
        virtual bool AcceptExtApp() const = 0;

        /**
        * Checks if an external application should be inserted
        *@param showDialog - if true, the application dialog will be shown
        *@return true if the external application can be inserted, otherwise false
        */
        virtual bool DoInsertExtApp(bool showDialog = true) = 0;

        /**
        * Checks if the external files can be accepted
        *@return true if the external files can be accepted, otherwise false
        */
        virtual bool AcceptExtFile() const = 0;

        /**
        * Checks if an external file should be inserted
        *@param showDialog - if true, the file dialog will be shown
        *@return true if the external file can be inserted, otherwise false
        */
        virtual bool DoInsertExtFile(bool showDialog = true) = 0;

        /**
        * Checks if the symbol has units
        *@return true if the symbol has units, otherwise false
        */
        virtual bool HasUnit() const = 0;

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual CString GetUnitName() const = 0;

        /**
        * Gets the unit GUID
        *@return the unit GUID
        */
        virtual CString GetUnitGUID() const = 0;

        /**
        * Called when the symbol name has changed
        *@param[in, out] comp - the symbol component
        *@param oldName - the old name
        */
        virtual void OnSymbolNameChanged(CODComponent& comp, const CString& oldName) = 0;

        /**
        * Called when the page name has changed
        *@param pPage - the page
        *@param oldName - the old name
        */
        virtual void OnPageNameChanged(PSS_ProcessGraphPage* pPage, const CString& oldName) = 0;

        /**
        * Called when the user entity changed
        *@param comp - the user entity
        *@param oldName - the old name
        */
        virtual void OnUserEntityChanged(PSS_UserEntity* pUserEntity, const CString& oldName) = 0;

    protected:
        /**
        * Creates the symbol label
        *@return the symbol label, NULL on error
        */
        virtual CODLabelComponent* CreateSymbolLabel() = 0;

        /**
        * Gets the name edit text
        *@return the name edit text
        */
        virtual CODTextComponent* GetNameEditTextComponent() = 0;

        /**
        * Sets the name edit text
        *@param pValue - the name edit text
        */
        virtual void SetNameEditTextComponent(CODTextComponent* pValue) = 0;

        /**
        * Gets the comment edit text
        *@return the comment edit text
        */
        virtual CODTextComponent* GetCommentEditTextComponent() = 0;

        /**
        * Sets the comment edit text
        *@param pValue - the comment edit text
        */
        virtual void SetCommentEditTextComponent(CODTextComponent* pValue) = 0;
};

#endif
