/****************************************************************************
 * ==> PSS_Document --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentH
#define PSS_DocumentH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

// processsoft
#include "PSS_DocumentData.h"
#include "PSS_DocumentOptions.h"
#include "PSS_HistoryFieldManager.h"
#include "PSS_BaseDocument.h"
#include "PSS_Formula.h"
#include "PSS_FontManager.h"
#include "PSS_StyleManager.h"

// class name mapping
#ifndef PSS_DocumentData
    #define PSS_DocumentData ZDDocumentData
#endif
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif

// forward class declaration
class ZIHtmlView;
class ZIView;
class PSS_Edit;
class PSS_DocumentExport;
class PSS_DocumentData;
class PSS_PlanFinObject;
class PSS_FieldRepository;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Document : public PSS_BaseDocument
{
    DECLARE_SERIAL(PSS_Document)

    public:
        typedef PSS_BaseDocument inherited;

        virtual ~PSS_Document();

        /**
        * Gets the style array name
        *@param styleArray - style array
        *@return the style array name
        */
        virtual void GetStyleArrayName(CStringArray& styleArray);

        /**
        * Called when the style list has changed
        */
        virtual inline void StyleListHasChanged();

        /**
        * Called when the file list has changed
        */
        virtual inline void FileListHasChanged();

        /**
        * Selects a style
        *@param style - style to select
        */
        virtual inline void SelectStyleInList(const CString& style);

        /**
        * Checks if the hidden field should be shown
        *@return TRUE if the hidden field should be shown, otherwise FALSE
        */
        virtual inline const BOOL ShouldShowHiddenField() const;

        /**
        * Sets if the hidden field should be shown
        *@param value - if TRUE, the hidden field will be shown
        */
        virtual inline void SetShowHiddenField(BOOL value = TRUE);

        /**
        * Checks if the lines should be printed
        *@return TRUE if the lines should be printed, otherwise FALSE
        */
        virtual inline const BOOL ShouldPrintLine() const;

        /**
        * Sets if the lines should be printed
        *@param value - if TRUE, the lines will be printed
        */
        virtual inline void SetPrintLine(BOOL value = TRUE);

        /**
        * Gets the visible document data count
        *@return the visible document data count
        */
        virtual inline std::size_t GetVisibleDocumentDataCount() const;

        /**
        * Gets the available previous visible document index
        *@param documentindex - current document index to search from
        *@return the available previous visible document index, -1 if not found or on error
        */
        virtual int PreviousVisibleDocumentAvailable(std::size_t documentIndex) const;

        /**
        * Gets the available next visible document index
        *@param documentindex - current document index to search from
        *@return the available next visible document index, -1 if not found or on error
        */
        virtual int NextVisibleDocumentAvailable(std::size_t documentIndex) const;

        /**
        * Checks the multi-column member field
        *@param pObj - financial plan object
        *@param documentIndex - document index
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL CheckMultiColumnMemberField(PSS_PlanFinObject* pObj, int documentIndex = -1);

        /**
        * Gets the html view
        *@return the html view
        */
        virtual ZIHtmlView* GetHtmlView();

        /**
        * Initializes all the associations
        *@param documentIndex - document index
        */
        virtual void InitializeAllAssociations(int documentIndex = -1);

        /**
        * Calculates all the formulas
        *@param pView - view
        *@param allPages - if TRUE, all the pages will be calculated
        *@param documentIndex - document index
        */
        virtual void CalculateAllFormula(CView* pView = NULL, BOOL allPages = FALSE, int documentIndex = -1);

        /**
        * Checks for the cleared calculated fields
        *@param pView - view
        *@param documentIndex - document index
        *@note If the fields changed, they're drawn with a different color. After a certain time,
        *      their color should be cleared and reverted to the default one
        */
        virtual void CheckForClearCalcField(CView* pView = NULL, int documentIndex = -1);

        /**
        * Clears all the field associations
        *@param documentIndex - document index
        */
        virtual void ClearCurrentAssociation(int documentIndex = -1);

        /**
        * Changes the fields for calculation
        *@param documentIndex - document index
        *@note When the schema changes, it's necessary to remove the calculation flag in all number fields
        *      and to set it for result fields
        */
        virtual void ChangeFieldForCalculation(int documentIndex = -1);

        /**
        * Sends a message to the main frame to notify that schema list has changed
        *@param documentIndex - document index
        */
        virtual void SchemaListHasChanged(int documentIndex = -1);

        /**
        * Iterates through the formulas and checks if the object is a result object
        *@param pObj - object to check
        *@param documentIndex - document index
        *@return TRUE if the object is a result object, otherwise FALSE
        */
        virtual BOOL IsCalculatedFieldInSchema(PSS_PlanFinObject* pObj, int documentIndex = -1);

        /**
        * Refreshes the current schema
        *@param documentIndex - document index
        */
        virtual void RefreshCurrentSchema(int documentIndex = -1);

        /**
        * Initializes all the objects
        */
        virtual void InitializeAllObjects();

        /**
        * Changes the current file
        *@param name - file name
        *@param notify - if TRUE, all the linked observers will be notified
        */
        virtual void ChangeCurrentFile(const CString& name, BOOL notify = FALSE);

        /**
        * Changes the current file
        *@param fileIndex - file index in resources
        *@param notify - if TRUE, all the linked observers will be notified
        */
        virtual void ChangeCurrentFile(std::size_t fileIndex, BOOL notify = FALSE);

        /**
        * Changes and opens the current file
        *@param name - file name
        *@param notify - if TRUE, all the linked observers will be notified
        */
        virtual void ChangeCurrentFileOpen(const CString& name, BOOL notify = FALSE);

        /**
        * Changes and opens the current file
        *@param fileIndex - file index in resources
        *@param notify - if TRUE, all the linked observers will be notified
        */
        virtual void ChangeCurrentFileOpen(std::size_t fileIndex, BOOL notify = FALSE);

        /**
        * Gets the object list
        *@param documentIndex - document index
        *@return the object list
        */
        virtual CObList& GetObjectList(int documentIndex = -1);

        /**
        * Gets the element count
        *@param documentIndex - document index
        *@return the element count
        */
        virtual int GetObjectCount(int documentIndex = -1);

        /**
        * Gets the head element
        *@param documentIndex - document index
        *@return the head element, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* GetHead(int documentIndex = -1);

        /**
        * Gets the next element
        *@param documentIndex - document index
        *@return the next element, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* GetNext(int documentIndex = -1);

        /**
        * Gets the standard schema name
        *@return the standard schema name
        */
        virtual CString GetStandardSchema() const;

        /**
        * Gets the current assigned schema name
        *@param documentIndex - document index
        *@return the current assigned schema name
        */
        virtual CString GetCurrentSchema(int documentIndex = -1) const;

        /**
        * Sets the current schema
        *@param name - the current assigned schema name
        *@param documentIndex - document index
        */
        virtual void SetCurrentSchema(const CString& name, int documentIndex = -1);

        /**
        * Gets the object formula
        *@param name - object name
        *@param documentIndex - document index
        *@return the object formula, NULL if not found or on error
        */
        virtual PSS_Formula* GetFormula(const CString& name, int documentIndex = -1);

        /**
        * Gets the object matching with name
        *@param name - name
        *@return the object matching with name, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* GetObject(CString& name, int documentIndex = -1);

        /**
        * Gets the page count
        *@param documentIndex - document index
        *@return the page count
        */
        virtual int GetPageCount(int documentIndex = -1);

        /**
        * Sets the page count
        *@param page - the page count
        *@param documentIndex - document index
        */
        virtual void SetPageCount(int page, int documentIndex = -1);

        /**
        * Gets the default association string name
        *@return the default association string name
        */
        virtual CString GetDefaultAssociationString() const;

        /**
        * Gets the current page
        *@param documentIndex - document index
        *@return the current page
        */
        virtual int GetCurrentPage(int documentIndex = -1) const;

        /**
        * Sets the current page
        *@param page - the current page
        *@param documentIndex - document index
        */
        virtual void SetCurrentPage(int page, int documentIndex = -1);

        /**
        * Gets the selected object
        *@param checkPage - if TRUE, the page will be checked
        *@param documentIndex - document index
        *@return the selected object, NULL if no object selected or on error
        */
        virtual PSS_PlanFinObject* GetSelectedObject(BOOL checkPage = TRUE, int documentIndex = -1);

        /**
        * Checks if the object already exists
        *@param name - object name
        *@param documentIndex - document index
        *@return TRUE if the object already exists, otherwise FALSE
        */
        virtual BOOL ObjectExist(const CString& name, int documentIndex = -1);

        /**
        * Gets the main view
        *@return the main view
        */
        virtual ZIView* GetMainView();

        /**
        * Starts the real-time export
        *@param doExport - if TRUE, an export will be processed
        *@param doImport - if TRUE, an import will be processed
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StartRealTimeExport(BOOL doExport = FALSE, BOOL doImport = FALSE);

        /**
        * Gets if the document is exported
        *@return TRUE if the document is exported, otherwise FALSE
        */
        virtual inline BOOL IsRealTimeExported() const;

        /**
        * Called when the document has been modified
        */
        virtual void DocumentHasBeenModified();

        /**
        * Called when one or more fields have been modified
        */
        virtual void FieldHasBeenModified();

        /**
        * Gets the active document data
        *@return the active document data, NULL on error
        */
        virtual inline PSS_DocumentData* GetActiveDocumentData() const;

        /**
        * Gets the document data count
        *@return the document data count
        */
        virtual inline std::size_t GetDocumentDataCount() const;

        /**
        * Gets the document data at index
        *@param documentIndex - document index
        *@return the document data at index
        */
        virtual inline PSS_DocumentData* GetDocumentDataAt(int documentIndex) const;

        /**
        * Removes all document data
        */
        virtual void RemoveAllDocumentData();

        /**
        * Adds a new document data
        *@param pDocData - document data to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddDocumentData(PSS_DocumentData* pDocData);

        /**
        * Adds a new document data at index
        *@param pDocData - document data to add
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddDocumentDataAfter(PSS_DocumentData* pDocData, int index);

        /**
        * Gets the document data stamp specified at index
        *@param documentIndex - document index
        *@return the document data stamp
        */
        virtual PSS_Stamp& GetStamp(int documentIndex = -1);

        /**
        * Gets the schema manager
        *@param documentIndex - document index
        *@return the schema manager
        */
        virtual PSS_SchemaManager& GetSchema(int documentIndex = -1);

        /**
        * Gets the forecasted object count
        *@return the forecasted object count
        */
        virtual inline int GetForecastedObjectCount() const;

        /**
        * Sets the document object count
        *@param value - the document object count
        */
        virtual inline void SetForecastedObjectCount(int value);

        /**
        * Calculates the object count
        *@note This function add all the elements from all document data
        */
        virtual void CalculateForecastedObjectCount();

        /**
        * Shows the document
        *@param documentIndex - document index
        */
        virtual void ShowDocumentData(int documentIndex = -1);

        /**
        * Hides the document
        *@param documentIndex - document index
        */
        virtual void HideDocumentData(int documentIndex = -1);

        /**
        * Shows all documents
        */
        virtual void ShowAllDocumentData();

        /**
        * Hides all documents
        */
        virtual void HideAllDocumentData();

        /**
        * Checks if the document is visible
        *@param documentIndex - document index
        *@return TRUE if the document is visible, otherwise FALSE
        */
        virtual BOOL DocumentDataIsVisible(int documentIndex = -1);

        /**
        * Copies the document data
        *@param pDocSrc - source document
        *@param insertAsReadOnly - if TRUE, the document data will be inserted as read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyDocumentDataArray(PSS_Document* pDocSrc, BOOL insertAsReadOnly = FALSE);

        /**
        * Copies the document data
        *@param arraySrc - source array
        *@param insertAsReadOnly - if TRUE, the document data will be inserted as read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyDocumentDataArray(CObArray& arraySrc, BOOL insertAsReadOnly = FALSE);

        /**
        * Copies the document data at index
        *@param pDocSrc - source document
        *@param index - index
        *@param insertAsReadOnly - if TRUE, the document data will be inserted as read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyDocumentDataArrayAfter(PSS_Document* pDocSrc, int index, BOOL insertAsReadOnly = FALSE);

        /**
        * Copies the document data at index
        *@param arraySrc - source array
        *@param index - index
        *@param insertAsReadOnly - if TRUE, the document data will be inserted as read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyDocumentDataArrayAfter(CObArray& arraySrc, int index, BOOL insertAsReadOnly = FALSE);

        /**
        * Gets the font manager
        *@param documentIndex - document index
        *@return the font manager
        */
        virtual PSS_FontManager& GetFontManager(int documentIndex = -1);

        /**
        * Gets the style manager
        *@param documentIndex - document index
        *@return the style manager
        */
        virtual PSS_StyleManager& GetStyleManager(int documentIndex = -1);

        /**
        * Propagates the value to all document data
        *@param pObj - object containing the value to propagate
        *@param documentIndex - document index
        */
        virtual void PropagateFieldValue(PSS_PlanFinObject* pObj, int documentIndex = -2);

        /**
        * Fills a string array with the document data name
        *@param stringArray - string array
        *@param onlyVisible - if TRUE, only the visible strings will be added
        */
        virtual void GetDocumentDataName(CStringArray& stringArray, BOOL onlyVisible = TRUE);

        /**
        * Finds the document data matching with the name
        *@param name - name
        *@return the document data index
        */
        virtual int FindDocumentData(const CString& name);

        /**
        * Checks if the document data is read-only
        *@param documentIndex - document index
        *@return TRUE if the document data is read-only, otherwise FALSE
        */
        virtual BOOL DocumentDataIsReadOnly(int documentIndex = -1) const;

        /**
        * Sets the document as read-only
        *@param value - if TRUE, the document will be read-only
        *@param documentIndex - document index
        */
        virtual void SetDocumentDataAsReadOnly(BOOL value = TRUE, int documentIndex = -1);

        /**
        * Checks if the form is standard
        *@param documentIndex - document index
        *@return TRUE if the form is standard
        */
        virtual BOOL DocumentDataIsStandardForm(int documentIndex = -1) const;

        /**
        * Checks if the key is equal to the standard form
        *@param key - key
        *@param documentIndex - document index
        *@return TRUE if the key is equal to the standard form, otherwise FALSE
        */
        virtual BOOL DocumentDataIsInternalKeyEqualTo(const CString& key, int documentIndex = -1);

        /**
        * Gets if the document data is read-only at runtime
        *@param documentIndex - document index
        *@return TRUE if the document data is read-only at runtime
        */
        virtual BOOL IsReadOnlyAtRuntime(int documentIndex = -1);

        /**
        * Sets the document data as read-only at runtime
        *@param value - read-only value
        *@param documentIndex - document index
        */
        virtual void SetReadOnlyAtRuntime(BOOL value = TRUE, int documentIndex = -1);

        /**
        * Sets the read-only flag at runtime, for all document data
        *@param value - read-only value
        */
        virtual void SetAllDocReadOnlyAtRuntime(BOOL value = TRUE);

        /**
        * Changes the current schema
        *@param name - the schema name
        *@param notify - if TRUE, all the linked observers will be notified
        *@param documentIndex - document index
        */
        virtual void ChangeCurrentSchema(const CString& name, BOOL notify = FALSE, int documentIndex = -1);

        /**
        * Starts the calculation timer
        *@param documentIndex - document index
        */
        virtual void StartCalcTimer(int documentIndex = -1);

        /**
        * Resets the calculation timer
        *@param documentIndex - document index
        */
        virtual void ResetCalcTimer(int documentIndex = -1);

        /**
        * Creates all the temporary files based on the file buffer
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateAllTemporaryFileFromBuffer();

        /**
        * Deletes all allocated temporary files
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteAllTemporaryFiles();

        /**
        * Reads the document
        *@param fileName - document file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadDocument(const CString& fileName);

        /**
        * Draws the view
        *@param pDC - device context to draw to
        *@param pView - the view
        *@param documentIndex - document index
        */
        virtual void OnDraw(CDC* pDC, ZIView* pView, int documentIndex = -1);

        /**
        * Starts the tab order counter
        */
        virtual inline void StartTabOrder();

        /**
        * Increments the tab order counter
        *@return the current tab order position
        */
        virtual inline double IncrementTabOrder();

        /**
        * Takes the tab order of the object and when found an object with the specified tab order,
        * switch them together
        *@param pObject - object
        *@param tabOrder - tab order
        *@param documentIndex - document index
        */
        virtual void SwitchTabOrder(PSS_PlanFinObject* pObject, double tabOrder, int documentIndex = -1);

        /**
        * Assigns the multi-column member fields
        *@param documentIndex - document index
        */
        virtual void AssignMultiColumnMemberFields(int documentIndex = -1);

        /**
        * Assigns all the multi-column member fields
        */
        virtual void AssignAllMultiColumnMemberFields();

        /**
        * Gets the object field name array
        *@return the object field name array
        */
        virtual inline CStringArray* GetObjectFieldNameArray() const;

        /**
        * Gets the document object field name array
        *@param documentIndex - document index
        *@return the document object field name array
        */
        virtual inline CStringArray* GetObjectFieldNameArrayOfDocument(int documentIndex = -1) const;

        /**
        * Checks if the field name exists and adds it if not
        *@param fieldName - field name
        *@param documentIndex - document index
        *@return true on success, otherwise false
        */
        virtual bool AddFieldNameInObectArray(const CString& fieldName, int documentIndex = -1);

        /**
        * Builds the object field name array
        *@return true on success, otherwise false
        */
        virtual bool BuildObjectFieldNameArray();

        /**
        * Builds the document object field name array
        *@param documentIndex - document index
        *@return true on success, otherwise false
        */
        virtual bool BuildObjectFieldNameArrayOfDocument(int documentIndex = -1);

        /**
        * Gets the edited object
        *@param checkPage - if TRUE, the page will be checked
        *@param documentIndex - document index
        *@return the edited object
        */
        virtual PSS_PlanFinObject* GetEditedObject(BOOL checkPage = TRUE, int documentIndex = -1);

        /**
        * Sets the edited object
        *@param pObj - object
        *@param documentIndex - document index
        */
        virtual void SetEditedObject(PSS_PlanFinObject* pObj, int documentIndex = -1);

        /**
        * Gets the edit control
        *@return the edit control
        */
        virtual inline PSS_Edit* GetEditControl();

        /**
        * Assigns a newly created edit control
        *@param pEdit - edit
        */
        virtual inline void AssignEditControl(PSS_Edit* pEdit);

        /**
        * Creates automatically a new name for the object
        *@param pObj - object
        */
        virtual void CreateAutomaticNewName(PSS_PlanFinObject* pObj);

        /**
        * Gets the clipped object
        *@return the clipped object
        */
        virtual inline PSS_PlanFinObject* GetClipBoardObject();

        /**
        * Copies an object to the clipboard
        *@param pObj - object
        */
        virtual void CopyObjectToClipBoard(PSS_PlanFinObject* pObj);

        /**
        * Checks if the clipboard is empty
        *@return TRUE if the clipboard is empty, otherwise FALSE
        */
        virtual inline BOOL IsClipBoardEmpty() const;

        /**
        * Assigns predefined field to all objects
        *@param documentIndex - document index
        */
        virtual void AssignPredefinedField(int documentIndex = -1);

        /**
        * Changes the object type
        *@param pObj - object for which the type should be changed
        *@param name - the name
        *@param finalValue - the final value
        *@param propagate - if TRUE, the type will be propagated
        *@param documentIndex - document index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ChangeObjectType(PSS_PlanFinObject* pObj,
                                      const CString&     name,
                                      const CString&     finalValue,
                                      BOOL               propagate     =  FALSE,
                                      int                documentIndex = -1);

        /**
        * Inserts an object
        *@param pObj - object to insert
        *@param pFieldRepository - the field repository
        *@param insertInGlobalRepository - if TRUE, the object will be inserted in the global repository
        *@param documentIndex - document index
        *@param refresh - if TRUE, the view will be refreshed
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertObject(PSS_PlanFinObject*   pObj,
                                  PSS_FieldRepository* pFieldRepository         =  NULL,
                                  BOOL                 insertInGlobalRepository =  FALSE,
                                  int                  documentIndex            = -1,
                                  BOOL                 refresh                  =  FALSE);

        /**
        * Inserts the head object
        *@param pObj - object to insert
        *@param pFieldRepository - the field repository
        *@param insertInGlobalRepository - if TRUE, the object will be inserted in the global repository
        *@param documentIndex - document index
        *@param refresh - if TRUE, the view will be refreshed
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertObjectAtHead(PSS_PlanFinObject*   pObj,
                                        PSS_FieldRepository* pFieldRepository         =  NULL,
                                        BOOL                 insertInGlobalRepository =  FALSE,
                                        int                  documentIndex            = -1,
                                        BOOL                 refresh                  =  FALSE);

        /**
        * Deletes an object
        *@param pObj - object to delete
        *@param deleteFromMemory - if TRUE, the object will be deleted from memory
        *@param documentIndex - document index
        *@param refresh - if TRUE, the view will be refreshed
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteObject(PSS_PlanFinObject* pObj, BOOL deleteFromMemory = TRUE, int documentIndex = -1, BOOL refresh = FALSE);

        /**
        * Moves an object in order
        *@param pObj - object to delete
        *@param documentIndex - document index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MoveObjectInOrder(PSS_PlanFinObject* pObj, int documentIndex = -1);

        /**
        * Assigns a value to an object
        *@param name - the object name
        *@param value - the value to assign
        *@param documentIndex - document index
        *@param page - the page
        *@param propagationMode - the propagation mode
        *@param emptyWhenZero - if TRUE, the object will be emptied if set to 0
        *@param documentIndex - document index
        */
        virtual void AssignObjectValue(const CString& name,
                                       const CString& value,
                                       int            page,
                                       int            propagationMode =  g_LocateAllPagesEmptyOnly,
                                       BOOL           emptyWhenZero   =  FALSE,
                                       int            documentIndex   = -1);

        /**
        * Sets the current page to an object
        *@param pObj - the object
        *@param documentIndex - document index
        */
        virtual void SetCurrentPageToObject(PSS_PlanFinObject* obj, int documentIndex = -1);

        /**
        * Inserts a document file
        *@param fileName - document file name
        *@param insertAsReadOnly - if TRUE, the document file will be inserted as read-only
        *@param propagateValue - if TRUE, the read-only value will be propagated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertDocument(const CString& fileName,
                                    BOOL           insertAsReadOnly = FALSE,
                                    int            propagateValue   = g_LocateAllDocumentsEmptyOnly);

        /**
        * Inserts a document file at index
        *@param fileName - document file name
        *@param indexAfter - index after which the file should be inserted
        *@param insertAsReadOnly - if TRUE, the document file will be inserted as read-only
        *@param propagateValue - if TRUE, the read-only value will be propagated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertDocumentAfter(const CString& fileName,
                                         int            indexAfter,
                                         BOOL           insertAsReadOnly = FALSE,
                                         int            propagateValue   = g_LocateAllDocumentsEmptyOnly);

        /**
        * Inserts an external document file
        *@param fileName - document file name
        *@param insertAsReadOnly - if TRUE, the document file will be inserted as read-only
        *@param propagateValue - if TRUE, the read-only value will be propagated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertExternalDocument(const CString& fileName,
                                            BOOL           insertAsReadOnly = FALSE,
                                            int            propagateValue   = g_LocateAllDocumentsEmptyOnly);

        /**
        * Inserts an external document file at index
        *@param fileName - document file name
        *@param indexAfter - index after which the file should be inserted
        *@param insertAsReadOnly - if TRUE, the document file will be inserted as read-only
        *@param propagateValue - if TRUE, the read-only value will be propagated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertExternalDocumentAfter(const CString& fileName,
                                                 int            indexAfter,
                                                 BOOL           insertAsReadOnly = FALSE,
                                                 int            propagateValue   = g_LocateAllDocumentsEmptyOnly);

        /**
        * Inserts a binary document file
        *@param fileName - document file name
        *@param infoName - info name
        *@param infoDescription - info description
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertBinaryDocument(const CString& fileName, const CString& infoName = "", const CString& infoDescription = "");

        /**
        * Inserts a binary document file at index
        *@param fileName - document file name
        *@param indexAfter - index after which the file should be inserted
        *@param infoName - info name
        *@param infoDescription - info description
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertBinaryDocumentAfter(const CString& fileName,
                                               int            indexAfter,
                                               const CString& infoName        = "",
                                               const CString& infoDescription = "");

        /**
        * Inserts an external binary document file
        *@param fileName - document file name
        *@param infoName - info name
        *@param infoDescription - info description
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertExternalBinaryDocument(const CString& fileName,
                                                  const CString& infoName        = "",
                                                  const CString& infoDescription = "");

        /**
        * Inserts an external binary document file at index
        *@param fileName - document file name
        *@param indexAfter - index after which the file should be inserted
        *@param infoName - info name
        *@param infoDescription - info description
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertExternalBinaryDocumentAfter(const CString& fileName,
                                                       int            indexAfter,
                                                       const CString& infoName        = "",
                                                       const CString& infoDescription = "");

        /**
        * Inserts an url
        *@param url - url
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertURL(const CString& url);

        /**
        * Inserts an url at index
        *@param url - url
        *@param indexAfter - index after which the url should be inserted
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertURLAfter(const CString& url, int indexAfter);

        /**
        * Deletes a document data at index
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteDocumentAt(int index);

        /**
        * Deletes a document data
        *@param pDocData - document data to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteDocumentData(PSS_DocumentData* pDocData);

        /**
        * Propagates a value in the document
        *@param name - document name
        *@param value - value to propagate
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, the target element will be emptied if value is zero
        *@param documentIndex - document index
        *@param page - page number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PropagateDocumentValue(const CString& name,
                                            const CString& value,
                                            int            propagationMode =  g_LocateAllDocumentsEmptyOnly,
                                            BOOL           emptyWhenZero   =  FALSE,
                                            int            documentIndex   = -1,
                                            int            page            = -1);

        /**
        * Propagates a value between an index range in the document
        *@param name - document name
        *@param value - value to propagate
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, the target element will be emptied if value is zero
        *@param documentIndexFrom - document index from which the propagation should begin
        *@param documentIndexTo - document index to which the propagation should end
        *@param page - page number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PropagateDocumentValueFromTo(const CString& name,
                                                  const CString& value,
                                                  int            propagationMode   =  g_LocateAllPagesEmptyOnly,
                                                  BOOL           emptyWhenZero     =  FALSE,
                                                  int            documentIndexFrom =  0,
                                                  int            documentIndexTo   = -1,
                                                  int            page              = -1);

        /**
        * Propagates all values from an external document in the current document
        *@param pDoc - the source document containing the values to propagate
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, the target element will be emptied if value is zero
        *@param documentIndex - document index
        *@param page - page number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PropagateExternDocumentAllValues(PSS_Document* pDoc,
                                                      int           propagationMode =  g_LocateAllDocumentsEmptyOnly,
                                                      BOOL          emptyWhenZero   =  FALSE,
                                                      int           documentIndex   = -1,
                                                      int           page            = -1);

        /**
        * Propagates all values between a range from the current document
        *@param indexFrom - the source index from which the values should be propagated
        *@param indexTo - the source index to which the values should be propagated
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, the target element will be emptied if value is zero
        *@param documentIndex - document index
        *@param page - page number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PropagateInternalDocumentAllValues(int  indexFrom       =  0,
                                                        int  indexTo         = -1,
                                                        int  propagationMode =  g_LocateAllDocumentsEmptyOnly,
                                                        BOOL emptyWhenZero   =  FALSE,
                                                        int  documentIndex   = -1,
                                                        int  page            = -1);

        /**
        * Propagates all values coming from internal documents to some internal documents
        *@param srcIndexFrom - the source index from which the values should be propagated
        *@param srcIndexTo - the source index to which the values should be propagated
        *@param dstIndexFrom - the source index from which the values should be propagated
        *@param dstIndexTo - the source index to which the values should be propagated
        *@param propagationMode - propagation mode
        *@param emptyWhenZero - if TRUE, the target element will be emptied if value is zero
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PropagateInternalDocumentOnDocumentValues(int  srcIndexFrom    =  0,
                                                               int  srcIndexTo      = -1,
                                                               int  dstIndexFrom    =  0,
                                                               int  dstIndexTo      = -1,
                                                               int  propagationMode =  g_LocateAllDocumentsEmptyOnly,
                                                               BOOL emptyWhenZero   = FALSE);

        /**
        * Parses a line string to import the activity
        *@param activity - activity index
        *@param line - line to parse
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL ImportActivityFromLineString(std::size_t activity, const CString& line);

        /**
        * Gets the document options
        *@return the document options
        */
        virtual inline PSS_DocumentOptions& GetDocOptions();

        /**
        * Gets the history field value manager
        *@return the history field value manager
        */
        virtual inline PSS_HistoryFieldManager& GetHistoryValueManager();

        /**
        * Gets the synchronization file name
        *@return the synchronization file name
        */
        virtual inline const CString GetSynchronizationFileName() const;

        /**
        * Sets the synchronization file name
        *@param value - the synchronization file name
        */
        virtual inline void SetSynchronizationFileName(const CString& value);

        /**
        * Gets the real time export object
        *@return the real time export object
        */
        virtual inline PSS_DocumentExport* GetRealTimeExport();

        /**
        * Sets the real time export object
        *@param pDocExport - the real time export object
        */
        virtual inline void SetRealTimeExport(PSS_DocumentExport* pDocExport);

        /**
        * Gets the documents data array
        *@return the documents data array
        */
        virtual inline CObArray& GetDocumentDataArray();

        /**
        * Gets the active document index
        *@return the active document index
        */
        virtual inline const int GetActiveDocumentIndex() const;

        /**
        * Sets the active document index
        *@param value - the active document index
        */
        virtual inline void SetActiveDocumentIndex(int value);

        /**
        * Gets the current element
        *@return the current element
        */
        virtual inline const int GetCurrentElement() const;

        /**
        * Sets the current element
        *@param value - the current element
        */
        virtual inline void SetCurrentElement(int value);

        /**
        * Gets if this document is saved in FLF file only
        *@return TRUE if this document is saved in FLF file only, otherwise FALSE
        */
        virtual inline const BOOL GetKeepOnlyFLF() const;

        /**
        * Sets if this document is saved in FLF file only
        *@param value - if TRUE, this document is saved in FLF file only
        */
        virtual inline void SetKeepOnlyFLF(BOOL value);

        /**
        * Gets the current tab order, used when reordering tabs
        *@return the current tab order
        */
        virtual inline const double GetCurrentTabOrder() const;

        /**
        * Gets the automatic new name
        *@param pObj - object for which the new name should be get
        *@param documentIndex - document index
        *@return the automatic new name
        */
        virtual CString GetAutomaticNewName(PSS_PlanFinObject* pObj, int documentIndex = 0);

        /**
        * Called when the document is closed
        */
        virtual void OnCloseDocument();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Serializes the document information in read mode
        *@param ar - archive
        */
        virtual void SerializeRead(CArchive& ar);

        /**
        * Serializes the document information in write mode
        *@param ar - archive
        */
        virtual void SerializeWrite(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_PlanFinObject*  m_pClipBoardObject;
        PSS_Edit*           m_pEdit;
        PSS_DocumentExport* m_pRealTimeExport;
        PSS_DocumentOptions m_DocOptions;
        CObArray            m_DocumentDataArray;
        CString             m_SynchronizationFileName;
        WORD                m_VersionNumber;
        INT                 m_ObjectCounter;
        int                 m_ActiveDocumentIndex;

        PSS_Document();

        /// Generated message map functions
        //{{AFX_MSG(PSS_Document)
        afx_msg void OnPageRecalculate();
        afx_msg void OnPagePrev();
        afx_msg void OnPageNext();
        afx_msg void OnUpdatePagePrev(CCmdUI* pCmdUI);
        afx_msg void OnUpdatePageNext(CCmdUI* pCmdUI);
        afx_msg void OnFilePrev();
        afx_msg void OnFileNext();
        afx_msg void OnUpdateFilePrev(CCmdUI* pCmdUI);
        afx_msg void OnUpdateFileNext(CCmdUI* pCmdUI);
        afx_msg void OnPageRefresh();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the document is opened
        *@param pPathName - path name
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL OnOpenDocument(const char* pPathName);

        /**
        * Opens the document
        *@param pPathName - path name
        *@param setLastLoaded - if TRUE, the document will be set as last loaded
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenDocument(const char* pPathName, BOOL setLastLoaded = TRUE);

        /**
        * Checks the object formula
        *@param pOld - old object to check from
        *@param pNew - new checked object
        *@param documentIndex - document index
        */
        virtual void CheckFormulaObject(PSS_PlanFinObject* pOld, PSS_PlanFinObject* pNew, int documentIndex = -1);

        /**
        * Creates the real time export
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateRealTimeExport();

        /**
        * Deletes all the objects in a document
        *@param documentIndex - document index
        */
        virtual void DeleteAllObjects(int documentIndex = -1);

        /**
        * Counts and sets all pages in a document
        *@param documentIndex - document index
        */
        virtual int CountAndSetPages(int documentIndex = -1);

        /**
        * Counts and sets all pages for all document data
        */
        virtual int DocumentCountAndSetPages();

        /**
        * Checks if the field name exists
        *@param fieldName - field name
        *@return true if the object exists, otherwise false
        */
        virtual bool FieldNameExistInObectArray(const CString& fieldName);

        /**
        * Replaces the calculated fields
        *@param documentIndex - document index
        */
        virtual void ReplaceCalculatedFields(int documentIndex = -1);

        /**
        * Checks the document font and style
        */
        virtual void CheckDocumentFontAndStyle();

        /**
        * Builds the automatic new name
        *@param prefix - prefix
        *@param documentIndex - document index
        *@return the build automatic new name
        */
        virtual CString BuildAutomaticNewName(const CString& prefix, int documentIndex = -1);

        /**
        * Calculates the document data index
        *@return the calculated document data index, -1 if not found or on error
        */
        virtual int GetDocumentDataIndex(PSS_DocumentData* pDocData);

        /**
        * Calculates the visible document data count
        *@return the visible document data count
        */
        virtual std::size_t CalculateVisibleDocumentDataCount();

        /**
        * Serializes the document data array
        *@param ar - archive
        */
        virtual void SerializeDocumentDataArray(CArchive& ar);

        /**
        * Serializes the document data array in read mode
        *@param ar - archive
        */
        virtual void SerializeDocumentDataArrayRead(CArchive& ar);

        /**
        * Serializes the document data array in write mode
        *@param ar - archive
        */
        virtual void SerializeDocumentDataArrayWrite(CArchive& ar);

    private:
        PSS_HistoryFieldManager m_HistoryValueManager;
        CStringArray            m_FieldNameArray;
        std::size_t             m_VisibleDocumentDataCount;
        int                     m_CurrentElement;
        double                  m_CurrentTabOrder;
        BOOL                    m_KeepOnlyFLF;
        BOOL                    m_ShowHiddenField;
        BOOL                    m_PrintLine;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Document(const PSS_Document& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Document& operator = (const PSS_Document& other);
};

//---------------------------------------------------------------------------
// PSS_Document
//---------------------------------------------------------------------------
const BOOL PSS_Document::ShouldShowHiddenField() const
{
    return m_ShowHiddenField;
}
//---------------------------------------------------------------------------
void PSS_Document::SetShowHiddenField(BOOL value)
{
    m_ShowHiddenField = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Document::ShouldPrintLine() const
{
    return m_PrintLine;
}
//---------------------------------------------------------------------------
void PSS_Document::SetPrintLine(BOOL value)
{
    m_PrintLine = value;
}
//---------------------------------------------------------------------------
std::size_t PSS_Document::GetVisibleDocumentDataCount() const
{
    return m_VisibleDocumentDataCount;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CheckMultiColumnMemberField(PSS_PlanFinObject* pObj, int documentIndex)
{
    if (documentIndex == -1)
    {
        if (GetActiveDocumentData())
            return GetActiveDocumentData()->CheckMultiColumnMemberField(pObj);

        return FALSE;
    }

    if (GetDocumentDataAt(documentIndex))
        return GetDocumentDataAt(documentIndex)->CheckMultiColumnMemberField(pObj);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_Document::StyleListHasChanged()
{
    // send a message to the MDI page to specify that the style list has changed
    AfxGetMainWnd()->SendMessageToDescendants(ID_STYLELISTHASCHANGED);
}
//---------------------------------------------------------------------------
void PSS_Document::FileListHasChanged()
{
    CalculateVisibleDocumentDataCount();

    // send a message to the MDI Page to specify that the file list has changed
    AfxGetMainWnd()->SendMessageToDescendants(UM_FILELISTHASCHANGED);
}
//---------------------------------------------------------------------------
void PSS_Document::SelectStyleInList(const CString& style)
{
    // send a message to the MDI Page to select a style in the style list
    AfxGetMainWnd()->SendMessageToDescendants(ID_SETSTYLEINLIST, 0, (LPARAM)(const char*)style);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::IsRealTimeExported() const
{
    return (m_pRealTimeExport != NULL);
}
//---------------------------------------------------------------------------
PSS_DocumentData* PSS_Document::GetActiveDocumentData() const
{
    if (GetActiveDocumentIndex() == -1 || !GetDocumentDataCount())
        return NULL;

    return GetDocumentDataAt(GetActiveDocumentIndex());
}
//---------------------------------------------------------------------------
std::size_t PSS_Document::GetDocumentDataCount() const
{
    return m_DocumentDataArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_DocumentData* PSS_Document::GetDocumentDataAt(int documentIndex) const
{
    if (documentIndex < int(GetDocumentDataCount()) && documentIndex >= 0)
        return (PSS_DocumentData*)m_DocumentDataArray.GetAt(documentIndex);

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::AddDocumentData(PSS_DocumentData* pDocData)
{
    return (m_DocumentDataArray.Add((CObject*)pDocData) >= 0);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::AddDocumentDataAfter(PSS_DocumentData* pDocData, int index)
{
    TRY
    {
        m_DocumentDataArray.InsertAt(index, (CObject*)pDocData);
        return TRUE;
    }
    CATCH(CMemoryException, e)
    {
        return FALSE;
    }
    END_CATCH

    return FALSE;
}
//---------------------------------------------------------------------------
int PSS_Document::GetForecastedObjectCount() const
{
    return m_ObjectCounter;
}
//---------------------------------------------------------------------------
void PSS_Document::SetForecastedObjectCount(int value)
{
    m_ObjectCounter = value;
}
//---------------------------------------------------------------------------
void PSS_Document::StartTabOrder()
{
    m_CurrentTabOrder = 0;
}
//---------------------------------------------------------------------------
double PSS_Document::IncrementTabOrder()
{
    ++m_CurrentTabOrder;
    return m_CurrentTabOrder;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Document::GetObjectFieldNameArray() const
{
    return (CStringArray*)&m_FieldNameArray;
}
//---------------------------------------------------------------------------
PSS_Edit* PSS_Document::GetEditControl()
{
    return m_pEdit;
}
//---------------------------------------------------------------------------
void PSS_Document::AssignEditControl(PSS_Edit* pEdit)
{
    m_pEdit = pEdit;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetClipBoardObject()
{
    return m_pClipBoardObject;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::IsClipBoardEmpty() const
{
    return (m_pClipBoardObject == NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::ImportActivityFromLineString(std::size_t CurrentActivity, const CString& line)
{
    // base class does nothing
    return FALSE;
}
//---------------------------------------------------------------------------
PSS_DocumentOptions& PSS_Document::GetDocOptions()
{
    return m_DocOptions;
}
//---------------------------------------------------------------------------
PSS_HistoryFieldManager& PSS_Document::GetHistoryValueManager()
{
    return m_HistoryValueManager;
}
//---------------------------------------------------------------------------
const CString PSS_Document::GetSynchronizationFileName() const
{
    return m_SynchronizationFileName;
}
//---------------------------------------------------------------------------
void PSS_Document::SetSynchronizationFileName(const CString& value)
{
    m_SynchronizationFileName = value;
}
//---------------------------------------------------------------------------
PSS_DocumentExport* PSS_Document::GetRealTimeExport()
{
    return m_pRealTimeExport;
}
//---------------------------------------------------------------------------
void PSS_Document::SetRealTimeExport(PSS_DocumentExport* pDocExport)
{
    m_pRealTimeExport = pDocExport;
}
//---------------------------------------------------------------------------
CObArray& PSS_Document::GetDocumentDataArray()
{
    return m_DocumentDataArray;
}
//---------------------------------------------------------------------------
const int PSS_Document::GetActiveDocumentIndex() const
{
    return m_ActiveDocumentIndex;
}
//---------------------------------------------------------------------------
void PSS_Document::SetActiveDocumentIndex(int value)
{
    m_ActiveDocumentIndex = value;
}
//---------------------------------------------------------------------------
const int PSS_Document::GetCurrentElement() const
{
    return m_CurrentElement;
}
//---------------------------------------------------------------------------
void PSS_Document::SetCurrentElement(int value)
{
    m_CurrentElement = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Document::GetKeepOnlyFLF() const
{
    return m_KeepOnlyFLF;
}
//---------------------------------------------------------------------------
void PSS_Document::SetKeepOnlyFLF(BOOL value)
{
    m_KeepOnlyFLF = value;
}
//---------------------------------------------------------------------------
const double PSS_Document::GetCurrentTabOrder() const
{
    return m_CurrentTabOrder;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::OnOpenDocument(const char* pPathName)
{
    return OpenDocument(pPathName, TRUE);
}
//---------------------------------------------------------------------------

#endif
