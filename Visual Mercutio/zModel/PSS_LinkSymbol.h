/****************************************************************************
 * ==> PSS_LinkSymbol ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a link symbol                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LinkSymbolH
#define PSS_LinkSymbolH

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
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_MathHelper.h"
#include "zBaseLib\PSS_Bitmap.h"
#include "zBaseLib\PSS_ToolTip.h"
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zBaseSym\PSS_ObjectPath.h"
#include "zBaseSym\PSS_BasicSymbolAcceptVisitor.h"
#include "zBaseSym\PSS_BasicSymbolVisitor.h"
#include "zProperty\ZIProperties.h"
#include "zProperty\ZBPropertyAttributes.h"
#include "zModel\PSS_ExtAppPropertyMgr.h"
#include "zModel\ZBExtFilePropertyMgr.h"
#include "zModel\ZVSymbolAttributes.h"

// forward class declarations
class ZBSymbolEdit;
class ZBPropertyAttributes;

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
* Link symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LinkSymbol : public CODLinkComponent,
                                     public PSS_BasicSymbol,
                                     public PSS_ObjectPath,
                                     public ZIProperties,
                                     public PSS_ExtAppPropertyMgr,
                                     public ZBExtFilePropertyMgr,
                                     public ZVSymbolAttributes,
                                     public PSS_BasicSymbolAcceptVisitor,
                                     public PSS_Subject,
                                     public PSS_Observer,
                                     public PSS_ToolTip
{
    DECLARE_SERIAL(PSS_LinkSymbol)

    public:
        PSS_LinkSymbol();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_LinkSymbol(const PSS_LinkSymbol& other);

        virtual ~PSS_LinkSymbol();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_LinkSymbol& operator = (const PSS_LinkSymbol& other);

        /**
        * Creates the link symbol
        *@param style - the style, ignored if -1
        *@param pointSize - the point size, ignored if -1
        *@param color - the color, ignored if -1
        *@param transparent - the transparency, ignored if -1
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(int style = -1, int pointSize = -1, COLORREF color = -1, int transparent = -1);

        /**
        * Creates the link symbol in an orthogonal way
        *@param style - the style, ignored if -1
        *@param pointSize - the point size, ignored if -1
        *@param color - the color, ignored if -1
        *@param transparent - the transparency, ignored if -1
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateOrthogonal(int style = -1, int pointSize = -1, COLORREF color = -1, int transparent = -1);

        /**
        * Creates a duplicate copy of this object
        *@return the duplicate copy of this object
        */
        virtual CODComponent* Dup() const;

        /**
        * Sets the line property
        *@param style - the style, ignored if -1
        *@param pointSize - the point size, ignored if -1
        *@param color - the color, ignored if -1
        *@param transparent - the transparency, ignored if -1
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLineProperty(int style, int pointSize = -1, COLORREF color = -1, int transparent = -1);

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
        virtual CString GetAttributeString(ZBPropertyAttributes* pAttributes) const;

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
        virtual ZBSymbolEdit* CreateEditText(const CString& areaName,
                                             const CString& editName,
                                             CODComponent*  pParent = NULL);

        /**
        * Creates a new text editor and replaces the existing one
        *@param editName - the edit name
        *@param pParent - the parent component
        *@return the newly created text editor, NULL on error
        */
        virtual ZBSymbolEdit* CreateAndReplaceEditText(const CString& editName, CODComponent* pParent = NULL);

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
        virtual bool Match(const CString&        argument,
                           ZBPropertyAttributes* pPropAttributes = NULL,
                           bool                  caseSensitive   = false,
                           bool                  partialSearch   = false);

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
        * Checks if the symbol is generic
        *@return true if the symbol is generic, otherwise false
        */
        virtual inline BOOL IsGeneric() const;

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
        *@param srcObj - source object
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
        * Checks if the line path between 2 symbols is optimal, updates it if not
        */
        void AdjustLinePath();

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
        virtual bool FillProperties(ZBPropertySet& propSet, bool numericValue = false, bool groupValue = false);

        /**
        * Save the changes to object properties
        *@param propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(ZBPropertySet& propSet);

        /**
        * Fills a symbol property
        *@param[in, out] prop - property to fill, filled property on function ends
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(ZBProperty& prop);

        /**
        * Saves a symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(ZBProperty& prop);

        /**
        * Checks the property value
        *@param prop - property to check
        *@param value - property value
        *@param props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param prop - property
        *@param value - property value
        *@param props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param prop - property
        *@param value - property value
        *@param props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int            menuCmdID,
                                        ZBProperty&    prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh);

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
        virtual inline ZBDynamicProperties* GetDynamicPropertiesManager();

        /**
        * Checks if the object can be visited
        *@param visitor - the visitor
        *@return true if the object can be visited, otherwise false
        */
        virtual inline bool AcceptVisitor(PSS_BasicSymbolVisitor& visitor);

        /**
        * Gets the entering symbol
        *@return the entering symbol, NULL if not found or on error
        */
        virtual CODSymbolComponent* GetEnteringSymbol();

        /**
        * Gets the following symbol
        *@return the following symbol, NULL if not found or on error
        */
        virtual CODSymbolComponent* GetFollowingSymbol();

        /**
        * Updates the graphic from the Risk engine
        *@param color - color
        *@param italic - if true, the text will be shown in italic
        */
        void UpdateGraphicFromRisk(COLORREF color, BOOL italic);

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
        * Gets the current line width
        *@return the current line width
        */
        virtual inline int GetCurrentLineWidth() const;

        /**
        * Sets the current line width
        *@param value - the current line width
        */
        virtual void SetCurrentLineWidth(int value);

        /**
        * Gets the current line style
        *@return the current line style
        */
        virtual inline int GetCurrentLineStyle() const;

        /**
        * Sets the current line style
        *@param value - the current line style
        */
        virtual void SetCurrentLineStyle(int value);

        /**
        * Gets the initial line style
        *@return the initial line style
        */
        virtual inline int GetInitialLineStyle() const;

        /**
        * Sets the initial line style
        *@param value - the initial line style
        */
        virtual void SetInitialLineStyle(int value);

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
        *@param ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is down above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is up above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is double clicked above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnLButtonDblClk(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the right mouse button is down above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller
        *@return true on success, otherwise false
        */
        virtual bool OnRButtonDown(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the right mouse button is up above the symbol
        *@param flags - special keys flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller
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
        * Called when a connection moves
        *@param pConnection - the moving connection
        *@return TRUE if the connection is allowed to move, otherwise FALSE
        */
        virtual BOOL OnConnectionMove(CODConnection* pConnection);

        /**
        * Called when the symbol name changes
        *@param oldName - the old name
        *@param newName - the new name
        */
        virtual void OnSymbolNameChange(const CString& oldName, const CString& newName);

        /**
        * Called when the default attributes are filled
        *@param pAttributes - the attributes
        *@return true if the attributes were filled, otherwise false
        */
        virtual bool OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes);

        /**
        * Called when the attributes change
        *@param pAttributes - the attributes
        *@return true if the attributes changed, otherwise false
        */
        virtual bool OnChangeAttributes(ZBPropertyAttributes* pAttributes);

        /**
        * Called before the property changes
        *@param newValue - the new value
        *@param prop - the changing property
        *@param props - the property set at which the changing property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props);

        /**
        * Called after the property changed
        *@param prop - the changing property
        *@param props - the property set at which the changing property belongs
        *@param refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param srcProperty - the source property
        *@param dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(ZBProperty&    srcProperty,
                                                ZBProperty&    dstProperty,
                                                bool           top2Down,
                                                ZBPropertySet& props);

        /**
        * Called when the symbol name changed
        *@param comp - the symbol component on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnSymbolNameChanged(CODComponent& Comp, const CString& oldName);

        /**
        * Called when the page name changed
        *@param pPage - the page on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnPageNameChanged(ZDProcessGraphPage* pPage, const CString& oldName);

        /**
        * Called when the user entity name changed
        *@param pUserEntity - the user entity on which the name is changing
        *@param oldName - the changing old name
        */
        virtual void OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString& oldName);

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString&                   toolTipText,
                               const CPoint&              point,
                               PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    protected:
        CODSymbolComponent*  m_pReference;
        ZBDynamicProperties* m_DynamicPropManager;
        CString              m_ReferenceName;
        bool                 m_IsInCreationProcess;
        bool                 m_IsLocal;

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

    private:
        static PSS_Bitmap m_ShortcutBitmap;
        CPoint            m_ShortcutBitmapPosition;
        CPoint            m_AllSymbolPosition;
        COLORREF          m_InitialLineColor;
        COLORREF          m_InitialLabelLineColor;
        COLORREF          m_CurrentLineColor;
        COLORREF          m_CurrentLabelLineColor;
        int               m_InitialLineWidth;
        int               m_InitialLabelLineWidth;
        int               m_InitialLineStyle;
        int               m_CurrentLineWidth;
        int               m_CurrentLineStyle;
        BOOL              m_IsCopy;
};

//---------------------------------------------------------------------------
// PSS_LinkSymbol
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetObjectTypeID() const
{
    return -1;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptDynamicAttributes() const
{
    return true;
}
//---------------------------------------------------------------------------
CODComponent* PSS_LinkSymbol::GetEditBoxArea()
{
    return ZVSymbolAttributes::GetEditBoxArea();
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_LinkSymbol::GetCommentTextEdit()
{
    return ZVSymbolAttributes::GetCommentTextEdit();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::CommentTextEditReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_LinkSymbol::GetSymbolNameTextEdit()
{
    return ZVSymbolAttributes::GetSymbolNameTextEdit();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::SymbolNameTextEditReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_LinkSymbol::GetAttributeTextEdit()
{
    return ZVSymbolAttributes::GetAttributeTextEdit();
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_LinkSymbol::GetSplitter1()
{
    return ZVSymbolAttributes::GetSplitter1();
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_LinkSymbol::GetSplitter2()
{
    return ZVSymbolAttributes::GetSplitter2();
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetReferenceName() const
{
    return m_ReferenceName;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetReferenceName(const CString& value)
{
    m_ReferenceName = value;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsLocal() const
{
    return m_IsLocal;
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::IsGeneric() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IncludeNameArea() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IncludeDescriptionArea() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IncludeAttributeArea() const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::ShowNameArea(bool value)
{
    ZVSymbolAttributes::DisplayNameArea(value);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsNameAreaVisible() const
{
    return ZVSymbolAttributes::IsNameAreaVisible();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::ShowDescriptionArea(bool value)
{
    ZVSymbolAttributes::DisplayDescriptionArea(value);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsDescriptionsAreaVisible() const
{
    return ZVSymbolAttributes::IsDescriptionsAreaVisible();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::ShowAttributeArea(bool value)
{
    ZVSymbolAttributes::DisplayAttributeArea(value);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsAttributeAreaVisible() const
{
    return ZVSymbolAttributes::IsAttributeAreaVisible();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptMouseInteraction() const
{
    // yes, in order to manage the attributes' splitters
    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsReferenced() const
{
    return !m_ReferenceName.IsEmpty();
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsReferenceValid() const
{
    return (!m_ReferenceName.IsEmpty() && m_pReference);
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_LinkSymbol::GetSymbolReference() const
{
    return m_pReference;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::CanContainChildModel() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsChildModelRef() const
{
    return false;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetRightSubMenu() const
{
    return -1;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetIconIndex() const
{
    return 0;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::CalculateAbsolutePath()
{
    // no path defined?
    if (GetAbsolutePath().IsEmpty())
        AddMemberToPath(GetSymbolName());
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    return (AcceptExtApp()  && PSS_ExtAppPropertyMgr::AcceptDropItem(pObj, point)) ||
           (AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem(pObj, point));
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::DropItem(CObject* pObj, const CPoint& point)
{
    return ((AcceptExtApp()  && PSS_ExtAppPropertyMgr::AcceptDropItem(pObj, point)) ? PSS_ExtAppPropertyMgr::DropItem(pObj, point)  : false) ||
           ((AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem(pObj, point))  ? ZBExtFilePropertyMgr::DropItem(pObj, point) : false);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptExtApp() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::DoInsertExtApp(bool showDialog)
{
    return PSS_ExtAppPropertyMgr::DoInsertExtApp(showDialog);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptExtFile() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::DoInsertExtFile(bool showDialog)
{
    return ZBExtFilePropertyMgr::DoInsertExtFile(showDialog);
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::HasUnit() const
{
    return false;
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetUnitName() const
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_LinkSymbol::GetUnitGUID() const
{
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::HasProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::IsPropertiesReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
ZBDynamicProperties* PSS_LinkSymbol::GetDynamicPropertiesManager()
{
    return m_DynamicPropManager;
}
//---------------------------------------------------------------------------
bool PSS_LinkSymbol::AcceptVisitor(PSS_BasicSymbolVisitor& visitor)
{
    return visitor.Visit(*this);
}
//---------------------------------------------------------------------------
COLORREF PSS_LinkSymbol::GetCurrentLineColor() const
{
    return m_CurrentLineColor;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetCurrentLineWidth() const
{
    return m_CurrentLineWidth;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetCurrentLineStyle() const
{
    return m_CurrentLineStyle;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetInitialLineStyle() const
{
    return m_InitialLineStyle;
}
//---------------------------------------------------------------------------
COLORREF PSS_LinkSymbol::GetCurrentLabelColor() const
{
    return m_CurrentLabelLineColor;
}
//---------------------------------------------------------------------------
COLORREF PSS_LinkSymbol::GetInitialLineColor() const
{
    return m_InitialLineColor;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetInitialLineWidth() const
{
    return m_InitialLineWidth;
}
//---------------------------------------------------------------------------
COLORREF PSS_LinkSymbol::GetInitialLabelLineColor() const
{
    return m_InitialLabelLineColor;
}
//---------------------------------------------------------------------------
int PSS_LinkSymbol::GetInitialLabelLineWidth() const
{
    return m_InitialLabelLineWidth;
}
//---------------------------------------------------------------------------
BOOL PSS_LinkSymbol::IsCopy()
{
    return m_IsCopy;
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetIsCopy(BOOL value)
{
    m_IsCopy = value;
}
//---------------------------------------------------------------------------
CODComponent* PSS_LinkSymbol::GetEditBoxAreaComponent()
{
    return ZVSymbolAttributes::GetEditBoxAreaComponent();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetEditBoxAreaComponent(CODComponent* pEdit)
{
    ZVSymbolAttributes::SetEditBoxAreaComponent(pEdit);
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_LinkSymbol::GetNameEditTextComponent()
{
    return ZVSymbolAttributes::GetNameEditTextComponent();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetNameEditTextComponent(CODTextComponent* pEdit)
{
    ZVSymbolAttributes::SetNameEditTextComponent(pEdit);
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_LinkSymbol::GetCommentEditTextComponent()
{
    return ZVSymbolAttributes::GetCommentEditTextComponent();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetCommentEditTextComponent(CODTextComponent* pEdit)
{
    ZVSymbolAttributes::SetCommentEditTextComponent(pEdit);
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_LinkSymbol::GetSplitter1Component()
{
    return ZVSymbolAttributes::GetSplitter1Component();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetSplitter1Component(CODLineComponent* pSplitter)
{
    ZVSymbolAttributes::SetSplitter1Component(pSplitter);
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_LinkSymbol::GetSplitter2Component()
{
    return ZVSymbolAttributes::GetSplitter2Component();
}
//---------------------------------------------------------------------------
void PSS_LinkSymbol::SetSplitter2Component(CODLineComponent* pSplitter)
{
    ZVSymbolAttributes::SetSplitter2Component(pSplitter);
}
//---------------------------------------------------------------------------

#endif
