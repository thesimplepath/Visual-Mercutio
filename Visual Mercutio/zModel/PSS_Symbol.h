/****************************************************************************
 * ==> PSS_Symbol ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolH
#define PSS_SymbolH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_Bitmap.h"
#include "zBaseLib\PSS_ToolTip.h"
#include "zBaseSym\PSS_BasicSymbolAcceptVisitor.h"
#include "zBaseSym\PSS_BasicSymbolVisitor.h"
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zBaseSym\PSS_ObjectPath.h"
#include "zBaseSym\PSS_NavigableSymbol.h"
#include "zProperty\PSS_Properties.h"
#include "zModel\PSS_ExtAppPropertyMgr.h"
#include "zModel\PSS_ExtFilePropertyMgr.h"
#include "zModel\PSS_SymbolAttributes.h"

// class name mapping
#ifndef PSS_SymbolEdit
    #define PSS_SymbolEdit ZBSymbolEdit
#endif

// forward class declaration
class PSS_SymbolEdit;
class PSS_PropertyAttributes;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Symbol : public CODSymbolComponent,
                                 public PSS_BasicSymbol,
                                 public PSS_ObjectPath,
                                 public PSS_NavigableSymbol,
                                 public PSS_Properties,
                                 public PSS_ExtAppPropertyMgr,
                                 public PSS_ExtFilePropertyMgr,
                                 public PSS_SymbolAttributes,
                                 public PSS_BasicSymbolAcceptVisitor,
                                 public PSS_Subject,
                                 public PSS_Observer,
                                 public PSS_ToolTip
{
    DECLARE_SERIAL(PSS_Symbol)

    public:
        PSS_Symbol();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Symbol(const PSS_Symbol& other);

        virtual ~PSS_Symbol();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_Symbol& operator = (const PSS_Symbol& other);

        /**
        * Creates the symbol
        *@param id - the symbol identifier
        *@param hInst - the instance handle
        *@param name - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(UINT id, HINSTANCE hInst, const CString& name = _T(""));

        /**
        * Creates a duplicate copy of this object
        *@return the duplicate copy of this object
        */
        virtual CODComponent* Dup() const;

        /**
        * Gets the unique object type identifier
        *@return the unique object type identifier
        */
        virtual inline int GetObjectTypeID() const;

        /**
        * Allows the symbol to accept dynamic attributes
        *@return true on success, otherwise false
        */
        virtual inline bool AcceptDynamicAttributes() const;

        /**
        * Gets the attributes as a string
        *@param pAttributes - the attributes
        *@return the attributes as a string
        */
        virtual CString GetAttributeString(PSS_PropertyAttributes* pAttributes) const;

        /**
        * Refreshes the attribute text area
        *@param redraw - if true, the area will be redrawn immediately
        */
        virtual void RefreshAttributeTextArea(bool redraw = false);

        /**
        * Gets if the title text is shown
        *@return true if the title text is shown, otherwise false
        */
        virtual bool GetShowTitleText() const;

        /**
        * Sets if the title text is shown
        *@param value - if true, the title text is shown
        */
        virtual void SetShowTitleText(bool value);

        /**
        * Creates a new text editor
        *@param areaName - the area name
        *@param editName - the edit name
        *@param pParent - the parent component
        *@return the newly created text editor, NULL on error
        */
        virtual PSS_SymbolEdit* CreateEditText(const CString& areaName,
                                               const CString& editName,
                                               CODComponent*  pParent = NULL);

        /**
        * Creates a new text editor and replaces the existing one
        *@param editName - the edit name
        *@param pParent - the parent component
        *@return the newly created text editor, NULL on error
        */
        virtual PSS_SymbolEdit* CreateAndReplaceEditText(const CString& editName, CODComponent* pParent = NULL);

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual CString GetSymbolName() const;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        */
        virtual BOOL SetSymbolName(const CString& value);

        /**
        * Gets the symbol comment
        *@return the symbol comment
        */
        virtual CString GetSymbolComment() const;

        /**
        * Sets the symbol comment
        *@param value - the symbol comment
        */
        virtual BOOL SetSymbolComment(const CString& value);

        /**
        * Gets the symbol reference number
        *@return the symbol reference number
        */
        virtual int GetSymbolReferenceNumber() const;

        /**
        * Gets the symbol reference number as a string
        *@return the symbol reference number as a string
        */
        virtual CString GetSymbolReferenceNumberStr() const;

        /**
        * Sets the symbol reference number
        *@param value - the symbol reference number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetSymbolReferenceNumber(int value);

        /**
        * Sets the symbol reference number from a string
        *@param value - the string containing the symbol reference number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetSymbolReferenceNumberStr(const CString& value);

        /**
        * Checks if the argument matches an attribute
        *@param argument - the argument to search
        *@param pPropAttributes - the property attributes to search in
        *@param caseSensitive - if true, the search will be case sensitive
        *@param partialSearch - if true, the search will be partial
        *@return true the argument matches an attribute, otherwise false
        */
        virtual bool Match(const CString&          argument,
                           PSS_PropertyAttributes* pPropAttributes = NULL,
                           bool                    caseSensitive   = false,
                           bool                    partialSearch   = false);

        /**
        * Retrieves the unit GUID from the name
        *@param name - the unit name
        *@param[out] error - if true, an error occurred
        *@return the unit GUID
        */
        virtual CString RetrieveUnitGUID(const CString& name, bool& error) const;

        /**
        * Retrieves the unit name from the GUID
        *@param guid - the unit GUID
        *@param[out] error - if true, an error occurred
        *@return the unit name
        */
        virtual CString RetrieveUnitName(const CString& guid, bool& error) const;

        /**
        * Retrieves the unit description from the GUID
        *@param guid - the unit GUID
        *@param[out] error - if true, an error occurred
        *@return the unit description
        */
        virtual CString RetrieveUnitDescription(const CString& guid, bool& error) const;

        /**
        * Retrieves the unit cost from the GUID
        *@param guid - the unit GUID
        *@param[out] error - if true, an error occurred
        *@return the unit cost
        */
        virtual float RetrieveUnitCost(const CString& guid, bool& error) const;

        /**
        * Retrieves the logical system GUID from the name
        *@param name - the logical system name
        *@param[out] error - if true, an error occurred
        *@return the logical system GUID
        */
        virtual CString RetrieveLogicalSystemGUID(const CString& name, bool& error) const;

        /**
        * Retrieves the logical system name from the GUID
        *@param guid - the logical system GUID
        *@param[out] error - if true, an error occurred
        *@return the logical system name
        */
        virtual CString RetrieveLogicalSystemName(const CString& guid, bool& error) const;

        /**
        * Retrieves the logical system description from the GUID
        *@param guid - the logical system GUID
        *@param[out] error - if true, an error occurred
        *@return the logical system description
        */
        virtual CString RetrieveLogicalSystemDescription(const CString& guid, bool& error) const;

        /**
        * Retrieves the prestation name from the GUID
        *@param guid - the prestation GUID
        *@param[out] error - if true, an error occurred
        *@return the prestation name
        */
        virtual CString RetrievePrestationName(const CString& guid, bool& error) const;

        /**
        * Edits the symbol name
        */
        virtual void EditSymbolName();

        /**
        * Checks if the new name is valid
        *@param value - the name to check
        *@return true if the new name is valid, oitherwise false
        */
        virtual bool IsNewNameValid(const CString& value) const;

        /**
        * Gets the edit box area
        *@return the edit box area
        */
        virtual inline CODComponent* GetEditBoxArea();

        /**
        * Gets the comment text editor
        *@return the comment text editor
        */
        virtual inline CODTextComponent* GetCommentTextEdit();

        /**
        * Checks if the comment is read-only
        *@return true if the comment is read-only, otherwise false
        */
        virtual inline bool CommentTextEditReadOnly() const;

        /**
        * Gets the symbol name text editor
        *@return the symbol name text editor
        */
        virtual inline CODTextComponent* GetSymbolNameTextEdit();

        /**
        * Checks if the symbol name is read-only
        *@return true if the symbol name is read-only, otherwise false
        */
        virtual inline bool SymbolNameTextEditReadOnly() const;

        /**
        * Gets the attribute text editor
        *@return the attribute text editor
        */
        virtual inline CODTextComponent* GetAttributeTextEdit();

        /**
        * Gets the first splitter
        *@return the first splitter
        */
        virtual inline CODLineComponent* GetSplitter1();

        /**
        * Gets the second splitter
        *@return the second splitter
        */
        virtual inline CODLineComponent* GetSplitter2();

        /**
        * Copies the symbol definitions from another component
        *@param src - source component to copy from
        */
        virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src);

        /**
        * Gets the reference name
        *@return the reference name
        */
        virtual inline CString GetReferenceName() const;

        /**
        * Sets the reference name
        *@param value - the reference name
        */
        virtual inline void SetReferenceName(const CString& value);

        /**
        * Checks if the symbol is local
        *@return true if the symbol is local, otherwise false
        */
        virtual inline bool IsLocal() const;

        /**
        * Sets the symbol as local
        *@param value - if true, the symbol will be local
        */
        virtual void SetIsLocal(bool value = true);

        /**
        * Duplicates the style on the twin symbols linked to this symbol
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DuplicateStyleOnTwinSymbol();

        /**
        * Checks if the symbol is generic
        *@return TRUE if the symbol is generic, otherwise FALSE
        */
        virtual inline BOOL IsGeneric() const;

        /**
        * Checks if the symbol is a process
        *@return TRUE if the symbol is a process, otherwise FALSE
        */
        virtual inline BOOL IsProcess() const;

        /**
        * Checks if the symbol is a procedure
        *@return TRUE if the symbol is a procedure, otherwise FALSE
        */
        virtual inline BOOL IsProcedure() const;

        /**
        * Checks if the symbol is a start symbol
        *@return TRUE if the symbol is a start symbol, otherwise FALSE
        */
        virtual inline BOOL IsStart() const;

        /**
        * Checks if the symbol is a stop symbol
        *@return TRUE if the symbol is a stop symbol, otherwise FALSE
        */
        virtual inline BOOL IsStop() const;

        /**
        * Checks if the symbol is a door
        *@return TRUE if the symbol is a door, otherwise FALSE
        */
        virtual inline BOOL IsDoor() const;

        /**
        * Checks if the symbol is a page
        *@return TRUE if the symbol is a page, otherwise FALSE
        */
        virtual inline BOOL IsPage() const;

        /**
        * Checks if the symbol is a package
        *@return TRUE if the symbol is a package, otherwise FALSE
        */
        virtual inline BOOL IsPackage() const;

        /**
        * Gets the risk level
        *@return the risk level
        */
        virtual CString GetRiskLevel() const;

        /**
        * Sets the risk level
        *@param level - the risk level
        */
        virtual void SetRiskLevel(const CString& level);

        /**
        * Checks if the name area is included
        *@return true if the name area is included, otherwise false
        */
        virtual inline bool IncludeNameArea() const;

        /**
        * Checks if the description area is included
        *@return true if the description area is included, otherwise false
        */
        virtual inline bool IncludeDescriptionArea() const;

        /**
        * Checks if the attribute area is included
        *@return true if the attribute area is included, otherwise false
        */
        virtual inline bool IncludeAttributeArea() const;

        /**
        * Shows the name area
        *@param value - if true, the name area will be shown
        */
        virtual inline void ShowNameArea(bool value = true);

        /**
        * Checks if the name area is visible
        *@return true if the name area is visible, otherwise false
        */
        virtual inline bool IsNameAreaVisible() const;

        /**
        * Shows the description area
        *@param value - if true, the description area will be shown
        */
        virtual inline void ShowDescriptionArea(bool value = true);

        /**
        * Checks if the description area is visible
        *@return true if the description area is visible, otherwise false
        */
        virtual inline bool IsDescriptionsAreaVisible() const;

        /**
        * Shows the attribute area
        *@param value - if true, the attribute area will be shown
        */
        virtual inline void ShowAttributeArea(bool value = true);

        /**
        * Checks if the attribute area is visible
        *@return true if the attribute area is visible, otherwise false
        */
        virtual inline bool IsAttributeAreaVisible() const;

        /**
        * Checks if the mouse interactions are accepted
        *@return true if the mouse interactions are accepted, otherwise false
        */
        virtual inline bool AcceptMouseInteraction() const;

        /**
        * Shows the symbol in error
        *@param value - if true, the symbol will be shown in error
        */
        virtual void ShowInError(bool value = true);

        /**
        * Applies the format coming from another object
        *@param[in, out] srcObj - source object
        *@param font - if true, the fonts will be copied
        *@param fill - if true, the fill style will be copied
        *@param line - if true, the line style will be copied
        */
        virtual void ApplyFormatFromObject(CODSymbolComponent& srcObj,
                                           bool                font = true,
                                           bool                fill = true,
                                           bool                line = true);

        /**
        * Gets the local symbol of this reference
        *@return the local symbol of this reference, NULL if not found or on error
        */
        virtual CODComponent* GetLocalSymbol();

        /**
        * Gets the referenced symbol of this master symbol
        *@return the referenced symbol of this master symbol,  NULL if not found or on error
        */
        virtual CODComponentSet* GetReferenceSymbols();

        /**
        * Checks if this symbol is referenced
        *@return true if this symbol is referenced, otherwise false
        */
        virtual inline bool IsReferenced() const;

        /**
        * Checks if the reference is valid
        *@return true if the reference is valid, otherwise false
        */
        virtual inline bool IsReferenceValid() const;

        /**
        * Assigns the reference symbol
        *@param pReference - the reference
        */
        virtual void AssignReferenceSymbol(CODSymbolComponent* pReference);

        /**
        * Removes the reference symbol
        */
        virtual void RemoveReferenceSymbol();

        /**
        * Gets the reference symbol
        *@return the reference symbol, NULL if not found or on error
        */
        virtual inline CODSymbolComponent* GetSymbolReference() const;

        /**
        * Creates an empty child model
        *@param pParent - the parent model
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmptyChildModel(CODModel* pParent);

        /**
        * Gets the child model
        *@return the child model, NULL if no child model
        */
        virtual inline CODModel* GetChildModel();

        /**
        * Sets the child model
        *@param pModel - the child model
        */
        virtual inline void SetChildModel(CODModel* pModel);

        /**
        * Checks if the symbol can contain a child model
        *@return true if the symbol can contain a child model, otherwise false
        */
        virtual inline bool CanContainChildModel() const;

        /**
        * Checks if the symbol is a child model reference of another symbol
        *@return true if the symbol is a child model reference of another symbol, otherwise false
        */
        virtual inline bool IsChildModelRef() const;

        /**
        * Gets the child model path name
        *@return the child model path name
        */
        virtual inline CString GetChildModelPathName() const;

        /**
        * Gets the owner symbol model
        *@return the owner symbol model, NULL if not found or on error
        */
        virtual CODModel* GetOwnerModel();

        /**
        * Gets the root symbol model
        *@return the root symbol model, NULL if not found or on error
        */
        virtual CODModel* GetRootModel();

        /**
        * Gets the model
        *@return the model
        */
        virtual inline CODModel* GetModel();

        /**
        * Sets the model
        *@param pModel - the model
        */
        virtual inline void SetModel(CODModel* pModel);

        /**
        * Gets the right sub-menu identifier
        *@return the right sub-menu identifier, -1 if none
        */
        virtual inline int GetRightSubMenu() const;

        /**
        * Gets the symbol icon identifier
        *@return the symbol icon identifier
        */
        virtual inline int GetIconIndex() const;

        /**
        * Sets the symbol modified flag
        *@param value - if TRUE, the symbol was modified
        */
        virtual void SetModifiedFlag(BOOL value = TRUE);

        /**
        * Calculates the absolute path
        */
        virtual inline void CalculateAbsolutePath();

        /**
        * Redraws the symbol
        */
        virtual void RedrawSymbol();

        /**
        * Checks if a dropped item may be accepted by the symbol
        *@param pObj - item to check and accept
        *@param point - drop point in pixels
        *@return true if the dropped item is accepted by the symbol, otherwise false
        */
        virtual inline bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item in the symbol
        *@param pObj - dropped item
        *@param point - drop point in pixels
        *@return true on success, otherwise false
        */
        virtual inline bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Checks if external applications are accepted by the symbol
        *@return true if external applications are accepted by the symbol, otherwise false
        */
        virtual inline bool AcceptExtApp() const;

        /**
        * Inserts an external application in the symbol
        *@param showDialog - if true, the insert dialog will be shown
        *@return true on success, otherwise false
        */
        virtual inline bool DoInsertExtApp(bool showDialog = true);

        /**
        * Checks if external files are accepted by the symbol
        *@return true if external files are accepted by the symbol, otherwise false
        */
        virtual inline bool AcceptExtFile() const;

        /**
        * Inserts an external file in the symbol
        *@param showDialog - if true, the insert dialog will be shown
        *@return true on success, otherwise false
        */
        virtual inline bool DoInsertExtFile(bool showDialog = true);

        /**
        * Checks if symbol has units
        *@return true if symbol has units, otherwise false
        */
        virtual inline bool HasUnit() const;

        /**
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Gets the unit GUID
        *@return the unit GUID
        */
        virtual inline CString GetUnitGUID() const;

        /**
        * Checks if symbol has prestations
        *@return true if symbol has prestations, otherwise false
        */
        virtual inline bool HasPrestations() const;

        /**
        * Gets the prestation list
        *@return the prestation list, empty list if no prestations
        */
        virtual inline PSS_Tokenizer GetPrestationsList() const;

        /**
        * Checks if the symbol contains properties
        *@return true if the symbol contains properties, otherwise false
        */
        virtual inline bool HasProperties() const;

        /**
        * Fills an array with the symbol properties
        *@param[in, out] propSet - property set to fill with the symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValue = false, bool groupValue = false);

        /**
        * Saves the changes to object properties
        *@param[in, out] propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(PSS_Properties::IPropertySet& propSet);

        /**
        * Fills a symbol property
        *@param[in, out] prop - property to fill, filled property on function ends
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(PSS_Property& prop);

        /**
        * Saves a symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(PSS_Property& prop);

        /**
        * Checks the property value
        *@param[in, out] prop - property to check
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int                           menuCmdID,
                                        PSS_Property&                 prop,
                                        CString&                      value,
                                        PSS_Properties::IPropertySet& props,
                                        bool&                         refresh);

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Checks if the properties are read-only
        *@return true if the properties are read-only, otherwise false
        */
        virtual inline bool IsPropertiesReadOnly() const;

        /**
        * Gets the dynamic properties manager
        *@return the dynamic properties manager
        */
        virtual inline PSS_DynamicProperties* GetDynamicPropertiesManager();

        /**
        * Checks if the object can be visited
        *@param[in, out] visitor - the visitor
        *@return true if the object can be visited, otherwise false
        */
        virtual inline bool AcceptVisitor(PSS_BasicSymbolVisitor& visitor);

        /**
        * Updates the graphic from the Risk engine
        *@param color - color
        *@param italic - if true, the text will be shown in italic
        */
        virtual void UpdateGraphicFromRisk(COLORREF color, BOOL italic);

        /**
        * Gets the current line color
        *@return the current line color
        */
        virtual inline COLORREF GetCurrentLineColor() const;

        /**
        * Sets the current line color
        *@param value - the current line color
        */
        virtual void SetCurrentLineColor(COLORREF value);

        /**
        * Gets the current label color
        *@return the current label color
        */
        virtual inline COLORREF GetCurrentLabelColor() const;

        /**
        * Sets the current label color
        *@param value - the current label color
        */
        virtual void SetCurrentLabelColor(COLORREF value);

        /**
        * Gets the initial line color
        *@return the initial line color
        */
        virtual inline COLORREF GetInitialLineColor() const;

        /**
        * Sets the initial line color
        *@param value - the initial line color
        */
        virtual void SetInitialLineColor(COLORREF value);

        /**
        * Gets the initial line width
        *@return the initial line width
        */
        virtual inline int GetInitialLineWidth() const;

        /**
        * Sets the initial line width
        *@param value - the initial line width
        */
        virtual void SetInitialLineWidth(int value);

        /**
        * Gets the initial label line color
        *@return the initial label line color
        */
        virtual inline COLORREF GetInitialLabelLineColor() const;

        /**
        * Sets the initial label line color
        *@param value - the initial label line color
        */
        virtual void SetInitialLabelLineColor(COLORREF value);

        /**
        * Gets the initial label line width
        *@return the initial label line width
        */
        virtual inline int GetInitialLabelLineWidth() const;

        /**
        * Sets the initial label line width
        *@param value - the initial label line width
        */
        virtual void SetInitialLabelLineWidth(int value);

        /**
        * Checks if the symbol is a memory copy of another
        *@return true if the symbol is a memory copy of another, otherwise false
        *@note The memory copy value will be reseted every time the application is closed and reopened. For that reason,
        *      this function should only be used for memory cleanup processes, in order to know if a symbol was copied
        *      during the current session and thus should be cleaned up on closure. The function shouldn't be used to know
        *      if the symbol is a duplicate of another, the IsLocal() function should be used for this purpose instead
        */
        virtual inline BOOL IsCopy();

        /**
        * Sets the symbol as a memory copy of another
        *@param value - if true, the symbol is a memory copy of another
        *@note The memory copy value will be reseted every time the application is closed and reopened. For that reason,
        *      this function should only be used for memory cleanup processes, in order to know if a symbol was copied
        *      during the current session and thus should be cleaned up on closure. The function shouldn't be used to set
        *      if the symbol is a duplicate of another, the SetIsLocal() function should be used for this purpose instead
        */
        virtual inline void SetIsCopy(BOOL value = TRUE);

        /**
        * Finds a symbol
        *@param symbolName - the symbol name to find
        *@return the component, NULL if not found or on error
        */
        virtual inline CODComponent* FindSymbol(const CString& symbolName);

        /**
        * Finds a symbol
        *@param pMainComponent - the main component to search from
        *@param symbolName - the symbol name to find
        *@return the component, NULL if not found or on error
        */
        virtual CODComponent* FindSymbol(CODComponent* pMainComponent, const CString& symbolName);

        /**
        * Finds a symbol in the child
        *@param pMainComponent - the main component to search from
        *@param symbolName - the symbol name to find
        *@return the component, NULL if not found or on error
        */
        virtual CODComponent* FindSymbolInChild(CODComponent* pMainComponent, const CString& symbolName);

        /**
        * Removes a symbol
        *@param symbolName - the symbol name to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveSymbol(const CString& symbolName);

        /**
        * Removes a symbol
        *@param pComponent - the symbol to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveSymbol(CODComponent* pComponent);

        /**
        * Removes a symbol
        *@param pMainComponent - the main component to search from
        *@param pComponent - the symbol to remove
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveSymbol(CODComponent* pMainComponent, CODComponent* pComponent);

        /**
        * Gets all the entering symbols
        *@param[out] nodes - node array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEnteringSymbols(CODNodeArray& nodes);

        /**
        * Gets all the entering symbols on the left
        *@param[out] nodes - node array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEnteringSymbols_Left(CODNodeArray& nodes);

        /**
        * Gets all the entering symbols on the right
        *@param[out] nodes - node array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEnteringSymbols_Right(CODNodeArray& nodes);

        /**
        * Gets all the entering symbols on the top
        *@param[out] nodes - node array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEnteringSymbols_Up(CODNodeArray& nodes);

        /**
        * Gets all the entering symbols on the bottom
        *@param[out] nodes - node array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEnteringSymbols_Down(CODNodeArray& nodes);

        /**
        * Gets all the following symbols
        *@param[out] nodes - node array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetFollowingSymbols(CODNodeArray& nodes);

        /**
        * Gets all the following symbols on the left
        *@param[out] nodes - node array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetFollowingSymbols_Left(CODNodeArray& nodes);

        /**
        * Gets all the following symbols on the right
        *@param[out] nodes - node array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetFollowingSymbols_Right(CODNodeArray& nodes);

        /**
        * Gets all the following symbols on the top
        *@param[out] nodes - node array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetFollowingSymbols_Up(CODNodeArray& nodes);

        /**
        * Gets all the following symbols on the bottom
        *@param[out] nodes - node array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetFollowingSymbols_Down(CODNodeArray& nodes);

        /**
        * Gets all the entering symbols on the edges
        *@param[out] edges - edge array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesEntering(CODEdgeArray& edges);

        /**
        * Gets all the entering symbols on the edges on the left
        *@param[out] edges - edge array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesEntering_Left(CODEdgeArray& edges);

        /**
        * Gets all the entering symbols on the edges on the right
        *@param[out] edges - edge array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesEntering_Right(CODEdgeArray& edges);

        /**
        * Gets all the entering symbols on the edges on the top
        *@param[out] edges - edge array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesEntering_Up(CODEdgeArray& edges);

        /**
        * Gets all the entering symbols on the edges on the bottom
        *@param[out] edges - edge array containing the entering symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesEntering_Down(CODEdgeArray& edges);

        /**
        * Gets all the following symbols on the edges
        *@param[out] edges - edge array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesLeaving(CODEdgeArray& edges);

        /**
        * Gets all the following symbols on the edges on the left
        *@param[out] edges - edge array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesLeaving_Left(CODEdgeArray& edges);

        /**
        * Gets all the following symbols on the edges on the right
        *@param[out] edges - edge array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesLeaving_Right(CODEdgeArray& edges);

        /**
        * Gets all the following symbols on the edges on the top
        *@param[out] edges - edge array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesLeaving_Up(CODEdgeArray& edges);

        /**
        * Gets all the following symbols on the edges on the bottom
        *@param[out] edges - edge array containing the following symbols
        *@return the entering symbol count
        */
        virtual std::size_t GetEdgesLeaving_Down(CODEdgeArray& edges);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called after the object is created
        *@param pModel - the parent model
        *@param pCtrl - the parent model controller
        *@return true if the object can be created, false if the object must be destroyed immediately
        */
        virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called before the object is deleted
        *@param pModel - the parent model
        *@param pCtrl - the parent model controller
        *@return true if the object can be deleted, otherwise false
        */
        virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called when the symbol is updated
        *@param pSubject - the subject
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Called when the link moves
        */
        virtual void OnMove();

        /**
        * Called when the mouse moves above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is down above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is up above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is double clicked above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDblClk(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the right mouse button is down above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnRButtonDown(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the right mouse button is up above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param[in, out] ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnRButtonUp(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called after a double click occurred above the symbol
        *@param pModel - the model
        *@param pCtrl - the controller
        */
        virtual void OnPostDoubleClick(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called when a link is connected to the symbol
        *@param pLink - the connected link
        */
        virtual void OnLinkConnect(CODLinkComponent* pLink);

        /**
        * Called when a link is disconnected to the symbol
        *@param pLink - the disconnected link
        */
        virtual void OnLinkDisconnect(CODLinkComponent* pLink);

        /**
        * Called when the default attributes are filled
        *@param pAttributes - the attributes
        *@return true if the attributes were filled, otherwise false
        */
        virtual bool OnFillDefaultAttributes(PSS_PropertyAttributes* pAttributes);

        /**
        * Called when the attributes change
        *@param pAttributes - the attributes
        *@return true if the attributes changed, otherwise false
        */
        virtual bool OnChangeAttributes(PSS_PropertyAttributes* pAttributes);

        /**
        * Called before the property changes
        *@param newValue - the new value
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, PSS_Properties::IPropertySet& props);

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh);

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param[in, out] srcProperty - the source property
        *@param[in, out] dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param[in, out] props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                PSS_Property&                 dstProperty,
                                                bool                          top2Down,
                                                PSS_Properties::IPropertySet& props);

        /**
        * Called when the symbol name has changed
        *@param[in, out] comp - the symbol component for which the name has changed
        *@param oldName - the old name
        */
        virtual void OnSymbolNameChanged(CODComponent& comp, const CString& oldName);

        /**
        * Called when the page name has changed
        *@param comp - the page component for which the name has changed
        *@param oldName - the old name
        */
        virtual void OnPageNameChanged(PSS_ProcessGraphPage* pPage, const CString& oldName);

        /**
        * Called when the user entity name changed
        *@param pUserEntity - the user entity on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnUserEntityChanged(PSS_UserEntity* pUserEntity, const CString& oldName);

        /**
        * Called when the symbol is deleted
        */
        virtual void OnDeleteSymbol();

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString&                   toolTipText,
                               const CPoint&              point,
                               PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IEToolTipMode::IE_TT_Normal);

    protected:
        CODModel*              m_pModel;
        CODSymbolComponent*    m_pReference;
        PSS_DynamicProperties* m_pDynamicPropManager;
        CString                m_ReferenceName;
        CPoint                 m_AllSymbolPosition;
        bool                   m_IsInCreationProcess;
        bool                   m_IsLocal;

        /**
        * Creates the symbol label
        *@return the newly created symbol label
        */
        virtual CODLabelComponent* CreateSymbolLabel();

        /**
        * Gets the edit box area component
        *@return the edit box area
        */
        virtual inline CODComponent* GetEditBoxAreaComponent();

        /**
        * Sets the edit box area component
        *@param pEdit - the edit box area to set
        */
        virtual inline void SetEditBoxAreaComponent(CODComponent* pEdit);

        /**
        * Gets the name edit text box
        *@return the name edit text box
        */
        virtual inline CODTextComponent* GetNameEditTextComponent();

        /**
        * Sets the name edit text box
        *@param pEdit - the name edit text box
        */
        virtual inline void SetNameEditTextComponent(CODTextComponent* pEdit);

        /**
        * Gets the comment edit text box
        *@return the comment edit text box
        */
        virtual inline CODTextComponent* GetCommentEditTextComponent();

        /**
        * Sets the comment edit text box
        *@param pEdit - the comment edit text box
        */
        virtual inline void SetCommentEditTextComponent(CODTextComponent* pEdit);

        /**
        * Gets the first splitter component
        *@return the splitter
        */
        virtual inline CODLineComponent* GetSplitter1Component();

        /**
        * Sets the first splitter component
        *@param pSplitter - the splitter
        */
        virtual inline void SetSplitter1Component(CODLineComponent* pSplitter);

        /**
        * Gets the second splitter component
        *@return the splitter
        */
        virtual inline CODLineComponent* GetSplitter2Component();

        /**
        * Sets the second splitter component
        *@param pSplitter - the splitter
        */
        virtual inline void SetSplitter2Component(CODLineComponent* pSplitter);

        /**
        * Gets the entering links matching with the name
        *@param name - the name to search
        *@param[out] edges - the edge array containing the matching links
        *@return the found link count
        */
        virtual std::size_t GetEdgesEntering_Name(const CString& name, CODEdgeArray& edges);

        /**
        * Gets the leaving links matching with the name
        *@param name - the name to search
        *@param[out] edges - the edge array containing the matching links
        *@return the found link count
        */
        virtual std::size_t GetEdgesLeaving_Name(const CString& name, CODEdgeArray& edges);

    private:
        static PSS_Bitmap m_ShortcutBitmap;
        CString           m_Name;
        CString           m_Comment;
        CString           m_ChildModelPathName;
        CPoint            m_ShortcutBitmapPosition;
        COLORREF          m_CurrentLineColor;
        COLORREF          m_CurrentLabelLineColor;
        COLORREF          m_InitialLineColor;
        COLORREF          m_InitialLabelLineColor;
        int               m_InitialLineWidth;
        int               m_InitialLabelLineWidth;
        BOOL              m_IsCopy;
};

//---------------------------------------------------------------------------
// PSS_Symbol
//---------------------------------------------------------------------------
int PSS_Symbol::GetObjectTypeID() const
{
    return -1;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptDynamicAttributes() const
{
    return true;
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_Symbol::GetSymbolReference() const
{
    return m_pReference;
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::GetEditBoxArea()
{
    return PSS_SymbolAttributes::GetEditBoxArea();
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_Symbol::GetCommentTextEdit()
{
    return PSS_SymbolAttributes::GetCommentTextEdit();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::CommentTextEditReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_Symbol::GetSymbolNameTextEdit()
{
    return PSS_SymbolAttributes::GetSymbolNameTextEdit();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::SymbolNameTextEditReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_Symbol::GetAttributeTextEdit()
{
    return PSS_SymbolAttributes::GetAttributeTextEdit();
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_Symbol::GetSplitter1()
{
    return PSS_SymbolAttributes::GetSplitter1();
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_Symbol::GetSplitter2()
{
    return PSS_SymbolAttributes::GetSplitter2();
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetReferenceName() const
{
    return m_ReferenceName;
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetReferenceName(const CString& value)
{
    m_ReferenceName = value;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsLocal() const
{
    return m_IsLocal;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsGeneric() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsProcess() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsProcedure() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsStart() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsStop() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsDoor() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsPage() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsPackage() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IncludeNameArea() const
{
    // the default is true to have a name area
    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IncludeDescriptionArea() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IncludeAttributeArea() const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_Symbol::ShowNameArea(bool value)
{
    PSS_SymbolAttributes::ShowNameArea(value);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsNameAreaVisible() const
{
    return PSS_SymbolAttributes::IsNameAreaVisible();
}
//---------------------------------------------------------------------------
void PSS_Symbol::ShowDescriptionArea(bool value)
{
    PSS_SymbolAttributes::ShowDescriptionArea(value);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsDescriptionsAreaVisible() const
{
    return PSS_SymbolAttributes::IsDescriptionsAreaVisible();
}
//---------------------------------------------------------------------------
void PSS_Symbol::ShowAttributeArea(bool value)
{
    PSS_SymbolAttributes::ShowAttributeArea(value);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsAttributeAreaVisible() const
{
    return PSS_SymbolAttributes::IsAttributeAreaVisible();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptMouseInteraction() const
{
    // yes, in order to manage the attributes splitters
    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsReferenced() const
{
    return !m_ReferenceName.IsEmpty();
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsReferenceValid() const
{
    return (!m_ReferenceName.IsEmpty() && m_pReference);
}
//---------------------------------------------------------------------------
CODModel* PSS_Symbol::GetChildModel()
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetChildModel(CODModel* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::CanContainChildModel() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsChildModelRef() const
{
    return false;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetChildModelPathName() const
{
    return m_ChildModelPathName;
}
//---------------------------------------------------------------------------
CODModel* PSS_Symbol::GetModel()
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetModel(CODModel* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
int PSS_Symbol::GetRightSubMenu() const
{
    return -1;
}
//---------------------------------------------------------------------------
int PSS_Symbol::GetIconIndex() const
{
    return -1;
}
//---------------------------------------------------------------------------
void PSS_Symbol::CalculateAbsolutePath()
{
    // if no path defined
    if (GetAbsolutePath().IsEmpty())
        AddMemberToPath(GetSymbolName());
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    return (AcceptExtApp()  && PSS_ExtAppPropertyMgr::AcceptDropItem (pObj, point)) ||
           (AcceptExtFile() && PSS_ExtFilePropertyMgr::AcceptDropItem(pObj, point));
}
//---------------------------------------------------------------------------
bool PSS_Symbol::DropItem(CObject* pObj, const CPoint& point)
{
    return ((AcceptExtApp()  && PSS_ExtAppPropertyMgr::AcceptDropItem (pObj, point)) ? PSS_ExtAppPropertyMgr::DropItem (pObj, point) : false) ||
           ((AcceptExtFile() && PSS_ExtFilePropertyMgr::AcceptDropItem(pObj, point)) ? PSS_ExtFilePropertyMgr::DropItem(pObj, point) : false);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptExtApp() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::DoInsertExtApp(bool showDialog)
{
    return PSS_ExtAppPropertyMgr::DoInsertExtApp(showDialog);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptExtFile() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::DoInsertExtFile(bool showDialog)
{
    return PSS_ExtFilePropertyMgr::DoInsertExtFile(showDialog);
}
//---------------------------------------------------------------------------
bool PSS_Symbol::HasUnit() const
{
    return false;
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetUnitName() const
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Symbol::GetUnitGUID() const
{
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_Symbol::HasPrestations() const
{
    return false;
}
//---------------------------------------------------------------------------
PSS_Tokenizer PSS_Symbol::GetPrestationsList() const
{
    PSS_Tokenizer token(_T(""));
    return token;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::HasProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::IsPropertiesReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
PSS_DynamicProperties* PSS_Symbol::GetDynamicPropertiesManager()
{
    return m_pDynamicPropManager;
}
//---------------------------------------------------------------------------
bool PSS_Symbol::AcceptVisitor(PSS_BasicSymbolVisitor& visitor)
{
    return visitor.Visit(*this);
}
//---------------------------------------------------------------------------
COLORREF PSS_Symbol::GetCurrentLineColor() const
{
    return m_CurrentLineColor;
}
//---------------------------------------------------------------------------
COLORREF PSS_Symbol::GetCurrentLabelColor() const
{
    return m_CurrentLabelLineColor;
}
//---------------------------------------------------------------------------
COLORREF PSS_Symbol::GetInitialLineColor() const
{
    return m_InitialLineColor;
}
//---------------------------------------------------------------------------
int PSS_Symbol::GetInitialLineWidth() const
{
    return m_InitialLineWidth;
}
//---------------------------------------------------------------------------
COLORREF PSS_Symbol::GetInitialLabelLineColor() const
{
    return m_InitialLabelLineColor;
}
//---------------------------------------------------------------------------
int PSS_Symbol::GetInitialLabelLineWidth() const
{
    return m_InitialLabelLineWidth;
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::IsCopy()
{
    return m_IsCopy;
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetIsCopy(BOOL value)
{
    m_IsCopy = value;
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::FindSymbol(const CString& symbolName)
{
    return FindSymbol(this, symbolName);
}
//---------------------------------------------------------------------------
BOOL PSS_Symbol::RemoveSymbol(CODComponent* pComponent)
{
    return RemoveSymbol(this, pComponent);
}
//---------------------------------------------------------------------------
CODComponent* PSS_Symbol::GetEditBoxAreaComponent()
{
    return PSS_SymbolAttributes::GetEditBoxAreaComponent();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetEditBoxAreaComponent(CODComponent* pEdit)
{
    PSS_SymbolAttributes::SetEditBoxAreaComponent(pEdit);
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_Symbol::GetNameEditTextComponent()
{
    return PSS_SymbolAttributes::GetNameEditTextComponent();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetNameEditTextComponent(CODTextComponent* pEdit)
{
    PSS_SymbolAttributes::SetNameEditTextComponent(pEdit);
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_Symbol::GetCommentEditTextComponent()
{
    return PSS_SymbolAttributes::GetCommentEditTextComponent();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetCommentEditTextComponent(CODTextComponent* pEdit)
{
    PSS_SymbolAttributes::SetCommentEditTextComponent(pEdit);
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_Symbol::GetSplitter1Component()
{
    return PSS_SymbolAttributes::GetSplitter1Component();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetSplitter1Component(CODLineComponent* pSplitter)
{
    PSS_SymbolAttributes::SetSplitter1Component(pSplitter);
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_Symbol::GetSplitter2Component()
{
    return PSS_SymbolAttributes::GetSplitter2Component();
}
//---------------------------------------------------------------------------
void PSS_Symbol::SetSplitter2Component(CODLineComponent* pSplitter)
{
    PSS_SymbolAttributes::SetSplitter2Component(pSplitter);
}
//---------------------------------------------------------------------------

#endif
