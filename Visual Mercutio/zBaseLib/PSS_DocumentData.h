/****************************************************************************
 * ==> PSS_DocumentData ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document data container                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentDataH
#define PSS_DocumentDataH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DocumentData
    #define PSS_DocumentData ZDDocumentData
#endif

// processsoft
#include "PSS_Formula.h"
#include "PSS_Stamp.h"
#include "PSS_StyleManager.h"
#include "PSS_FontManager.h"
#include "PSS_FileLauncher.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif
#ifndef PSS_FileBuffer
    #define PSS_FileBuffer ZBFileBuffer
#endif
#ifndef PSS_PlanFinObject
    #define PSS_PlanFinObject PlanFinObject
#endif
#ifndef PSS_FieldColumn
    #define PSS_FieldColumn ZBFieldColumn
#endif

// forward class declarations
class PSS_Document;
class PSS_FileBuffer;
class PSS_PlanFinObject;
class PSS_FieldRepository;
class PSS_View;

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
* Document data container
*@note This class allows to encapsulate deveral documents data in one file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocumentData : public CObject
{
    DECLARE_SERIAL(PSS_DocumentData)

    public:
        typedef CObject inherited;

        /**
        * Constructor
        *@param pDocument - document, can be NULL
        */
        PSS_DocumentData(PSS_Document* pDocument = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DocumentData(const PSS_DocumentData& other);

        virtual ~PSS_DocumentData();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DocumentData& operator = (const PSS_DocumentData& other);

        /**
        * Gets the object value
        *@param pName - value name to get
        *@return the object value
        */
        virtual double GetObjectValue(char* pName);

        /**
        * Deletes a page
        *@param index - page index to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeletePage(int index);

        /**
        * Copies a page
        *@param pDocumentDst - destination document
        *@param index - page index to copy
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyPage(PSS_DocumentData* pDocumentDst, int index);

        /**
        * Copies the objects contained on a page
        *@param pDocumentDst - destination document
        *@param index - page index to copy
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyPageOnlyObjects(PSS_DocumentData* pDocumentDst, int index);

        /**
        * Copies the formulas contained on a page
        *@param pDocumentDst - destination document
        *@param index - page index to copy
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyPageOnlyFormula(PSS_DocumentData* pDocumentDst, int index);

        /**
        * Checks the multi-columns member fields
        *@param pObj - object
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CheckMultiColumnMemberField(PSS_PlanFinObject* pObj);

        /**
        * Moves the content of a document to the current one
        *@param pDocument - document to move the content to
        *@param copyFormat - if true, format will be copied
        */
        virtual void MoveContents(PSS_DocumentData* pDocument, BOOL copyFormat);

        /**
        * Checks if the style has been deleted
        *@param hStyle - style to check
        */
        virtual void StyleHasBeenDeleted(PSS_Style::Handle hStyle);

        /**
        * Checks the font validity
        */
        virtual void CheckFontValidity();

        /**
        * Gets the object list
        *@return the object list
        */
        virtual inline CObList& GetObjectList();

        /**
        * Gets the element count
        *@return the element count
        */
        virtual inline int GetObjectCount() const;

        /**
        * Gets the object element list head pointer
        *@return the object element list head pointer
        */
        virtual inline PSS_PlanFinObject* GetHead();

        /**
        * Gets the next object element list pointer since the current one
        *@return the next object element list pointer, NULL if not found or on error
        */
        virtual inline PSS_PlanFinObject* GetNext();

        /**
        * Gets the currently assigned schema
        *@return the currently assigned schema, empty string if no assigned schema
        */
        virtual inline CString GetCurrentSchema() const;

        /**
        * Sets the currently assigned schema
        *@param name - schema name to assign
        */
        virtual inline void SetCurrentSchema(const CString& name);

        /**
        * Gets the formula pointed by the object name passed in parameter
        *@return the formula, NULL if not found or on error
        */
        virtual PSS_Formula* GetFormula(const CString& name);

        /**
        * Search the object matching with the name
        *@param name - the object name to search for
        *@return the object, NULL if not found or on error
        */
        virtual PSS_PlanFinObject* GetObject(const CString& name);

        /**
        * Gets the page count
        *@return the page count
        */
        virtual inline int GetMaxPage() const;

        /**
        * Sets the page count
        *@param count - page count
        */
        virtual inline void SetMaxPage(int count);

        /**
        * Gets the current page index
        *@return the current page index
        */
        virtual inline int GetCurrentPage() const;

        /**
        * Sets the current page index
        *@param index - page index
        */
        virtual inline void SetCurrentPage(int index);

        /**
        * Gets the selected object
        *@param checkPage - if TRUE, page will be checked
        *@return the selected object, NULL if no object selected or on error
        */
        virtual PSS_PlanFinObject* GetSelectedObject(BOOL checkPage = TRUE);

        /**
        * Gets the current edited object
        *@return the current edited object, NULL if no edited object or on error
        */
        virtual inline PSS_PlanFinObject* GetEditedObject(BOOL bCheckPage = TRUE);

        /**
        * Sets the current edited object
        *@param pObj - object to select
        */
        virtual inline void SetEditedObject(PSS_PlanFinObject* pObj);

        /**
        * Checks the object formula
        *@param pOld - old object
        *@param pNew - new object
        */
        virtual void CheckFormulaObject(PSS_PlanFinObject* pOld, PSS_PlanFinObject* pNew);

        /**
        * Checks if the object already exists
        *@param name - object name
        *@return TRUE if the object already exists, otherwise FALSE
        */
        virtual BOOL ObjectExist(const CString& name);

        /**
        * Initializes the associations
        */
        virtual void InitializeAllAssociations();

        /**
        * Calculates all the formulas
        *@param pView - view
        *@param allPages - if TRUE, the formulas will be calculated on all the pages
        */
        virtual void CalculateAllFormula(CView* pView = NULL, BOOL allPages = FALSE);

        /**
        * Checks for the clear calculated field
        *@param pView - view
        *@note Called by the frameword or the application. When the fields are calculated and then have
        *      changed they are drawn with a different color, we must after a certain time clear the color
        *      and draw it with their color
        */
        virtual void CheckForClearCalcField(CView* pView = NULL);

        /**
        * Starts the calculation timer
        */
        virtual inline void StartCalcTimer();

        /**
        * Resets the calculation timer
        */
        virtual inline void ResetCalcTimer();

        /**
        * Changes the current schema
        *@param name - schema name
        *@param notify - if TRUE, all the schemas will be notified about the change
        */
        virtual void ChangeCurrentSchema(const CString& name, BOOL notify = FALSE);

        /**
        * Clears all field associations
        */
        virtual void ClearCurrentAssociation();

        /**
        * Changes the field for calculation
        *@note When you change the schema, it is necessary to remove the switch for calculation
        *      of all number fields and to add it for result fields
        */
        virtual void ChangeFieldForCalculation();

        /**
        * Sends a message to the main frame to specify that schema list has changed
        */
        virtual inline void SchemaListHasChanged();

        /**
        * Check if the object is a result object
        *@param pObj - object to check
        *@return TRUE if the object was found and is a result object, otherwise FALSE
        */
        virtual BOOL IsCalculatedFieldInSchema(PSS_PlanFinObject* pObj);

        /**
        * Refreshes the current schema
        */
        virtual void RefreshCurrentSchema();

        /**
        * Changes the calculated field in the association
        *@param pAssociation - association
        *@note When you change the schema, it is necessary to remove the switch for calculation of all
        *      number fields and to add it for result fields
        */
        virtual void ChangeCalculatedFieldInAssociation(PSS_FormulaAssociation* pAssociation);

        /**
        * Replaces the calculated fields
        */
        virtual void ReplaceCalculatedFields();

        /**
        * Assigns the predefined field value in all objects
        */
        virtual void AssignPredefinedField();

        /**
        * Changes the object type
        *@param pObj - object for which type should be changed
        *@param name - name
        *@param finalValue - final value
        *@param propagate - if TRUE, change will be propagated
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ChangeObjectType(PSS_PlanFinObject* pObj,
                                      const CString&     name,
                                      const CString&     finalValue,
                                      BOOL               propagate = FALSE);

        /**
        * Builds the automatic new name
        *@param prefix - prefix
        *@return the built name
        */
        virtual CString BuildAutomaticNewName(const CString& prefix);

        /**
        * Inserts an object
        *@param pObj - object to insert
        *@param pFieldRepository - field repository
        *@param insertInGlobalRepository - if TRUE, the object will be inserted in the global repository
        *@param refresh - if TRUE, repository will be refreshed after inserted
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertObject(PSS_PlanFinObject*   pObj,
                                  PSS_FieldRepository* pFieldRepository         = NULL,
                                  BOOL                 insertInGlobalRepository = FALSE,
                                  BOOL                 refresh                  = FALSE);

        /**
        * Inserts an object on the head
        *@param pObj - object to insert
        *@param pFieldRepository - field repository
        *@param insertInGlobalRepository - if TRUE, the object will be inserted in the global repository
        *@param refresh - if TRUE, repository will be refreshed after inserted
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertObjectAtHead(PSS_PlanFinObject*   pObj,
                                        PSS_FieldRepository* pFieldRepository         = NULL,
                                        BOOL                 insertInGlobalRepository = FALSE,
                                        BOOL                 refresh                  = FALSE);

        /**
        * Deletes an object
        *@param pObj - object to delete
        *@param deleteFromMemory - if TRUE, the object will also be deleted from memory
        *@param refresh - if TRUE, repository will be refreshed after deletion
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteObject(PSS_PlanFinObject* pObj, BOOL deleteFromMemory = TRUE, BOOL refresh = FALSE);

        /**
        * Moves the object in order
        *@param pObj - object
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MoveObjectInOrder(PSS_PlanFinObject* pObj);

        /**
        * Assigns an object value
        *@param name - name
        *@param value - value
        *@param page - page
        *@param propagationMode - propagation mode
        *@param emptyWithZero - if TRUE, value will be emptied by 0
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AssignObjectValue(const CString& name,
                                       const CString& value,
                                       int            page,
                                       int            propagationMode = g_LocateAllPages,
                                       BOOL           emptyWhenZero   = FALSE);

        /**
        * Sets the current page to object
        *@param pObj - object
        */
        virtual void SetCurrentPageToObject(PSS_PlanFinObject* pObj);

        /**
        * Deletes all objects
        */
        virtual void DeleteAllObjects();

        /**
        * Counts and sets all pages
        *@return page count
        */
        virtual int CountAndSetPages();

        /**
        * Clones the selected object
        *@return the cloned object, NULL if no selection or on error
        */
        virtual PSS_PlanFinObject* CloneSelectedObject();

        /**
        * Rebuilds all the automatic numbered
        */
        virtual void RebuildAllAutomaticNumbered();

        /**
        * Sets the current style
        *@param name - name
        */
        virtual void SetCurrentStyle(const CString& name);

        /**
        * Checks if the field in association is calculated
        *@param pObj - object
        *@return TRUE if the field in association is calculated, otherwise FALSE
        */
        virtual BOOL IsCalculatedFieldInAssociation(PSS_PlanFinObject* pObj);

        /**
        * Shows the document
        */
        virtual inline void ShowDocumentData();

        /**
        * Hides the document
        */
        virtual inline void HideDocumentData();

        /**
        * Checks if the document is visible
        *@return TRUE if the document is visible, otherwise FALSE
        */
        virtual inline BOOL DocumentDataIsVisible() const;

        /**
        * Clones the document data
        *@return cloned document data
        */
        virtual inline PSS_DocumentData* Clone() const;

        /**
        * Initializes all the object pointers
        */
        virtual void InitializeAllObjectPointers();

        /**
        * Propagates the field value
        *@param pObj - object
        *@note This function receives the field name and its value. Its role is to propagate
        *      the value within the document data
        */
        virtual void PropagateFieldValue(PSS_PlanFinObject* pObj);

        /**
        * Assigns a new style
        *@param hOldStyle - old style
        *@param hNewStyle - new style
        *@note An old style must be replaced by a new one, all objects refering to this old style
        *      must be redirected to the new style
        */
        virtual void AssignNewStyle(PSS_Style::Handle hOldStyle, PSS_Style::Handle hNewStyle);

        /**
        * Checks if the document is read-only
        *@return TRUE if the document is read-only, otherwise FALSE
        */
        virtual inline BOOL IsReadOnly() const;

        /**
        * Sets the file as read-only
        *@param value - if TRUE, the file will be read-only
        */
        virtual inline void SetAsReadOnly(BOOL value = TRUE);

        /**
        * Checks if the form is standard
        *@return TRUE if the form is standard, otherwise FALSE
        */
        virtual inline BOOL IsStandardForm() const;

        /**
        * Checks if the key is equals to the standard form
        *@return TRUE if the key is equal to the standard form, otherwise FALSE
        */
        virtual inline BOOL IsInternalKeyEqualTo(const CString& key);

        /**
        * Checks if the document data is read-only at runtime
        *@return TRUE if the document data is read-only at runtime, otherwise FALSE
        */
        virtual inline BOOL IsReadOnlyAtRuntime() const;

        /**
        * Sets if the document data is read-only at runtime
        *@param value - if TRUE, the document data will be read-only at runtime
        */
        virtual inline void SetReadOnlyAtRuntime(BOOL value = TRUE);

        /**
        * Creates the class from a file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateBufferFromFile(const CString& fileName);

        /**
        * Creates a file based on the file buffer
        *@param fileName - file name
        *@return the just created file name
        */
        virtual CString CreateFileFromBuffer(const CString& fileName);

        /**
        * Creates a temporary file based on the file buffer
        *@return the just created file name
        */
        virtual CString CreateTemporaryFileFromBuffer();

        /**
        * Clears the class file buffer
        */
        virtual void ClearFileBuffer();

        /**
        * Gets the file buffer
        *@return the file buffer, NULL on error
        */
        virtual inline PSS_FileBuffer* GetFileBuffer();

        /**
        * Checks if is a form data
        *@return TRUE if is a form data, otherwise FALSE
        */
        virtual inline BOOL IsFormData() const;

        /**
        * Checks if is a binary data
        *@return TRUE if is a binary data, otherwise FALSE
        */
        virtual inline BOOL IsBinaryData() const;

        /**
        * Checks if is an external form data
        *@return TRUE if is an external form data, otherwise FALSE
        */
        virtual inline BOOL IsExternalFormData() const;

        /**
        * Checks if is an external binary data
        *@return TRUE if is an external binary data, otherwise FALSE
        */
        virtual inline BOOL IsExternalBinaryData() const;

        /**
        * Checks if is an URL
        *@return TRUE if is an URL, otherwise FALSE
        */
        virtual inline BOOL IsURLData() const;

        /**
        * Checks if the binary data members are valid
        *@return TRUE if the binary data members are valid, otherwise FALSE
        */
        virtual inline BOOL IsBinaryDataValid() const;

        /**
        * Deletes the allocated temporary file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteTemporaryFile();

        /**
        * Draws the document
        *@param pDC - device context to paint to
        *@param pView - view
        *@param drawCalculatedSymbol - if TRUE, calculated symbols will be drawn
        *@param drawHiddenObjects - if TRUE, hidden objects will be drawn
        *@param drawBoundRectObjects - if TRUE, bound rect objects will be drawn
        *@param drawCalculatedRefObject - if TRUE, calculated reference objects will be drawn
        *@param drawTabOrder - if TRUE, the tab order will be drawn
        */
        virtual void OnDraw(CDC*      pDC,
                            PSS_View* pView,
                            BOOL      drawCalculatedSymbol    = TRUE,
                            BOOL      drawHiddenObject        = FALSE,
                            BOOL      drawBoundRectObject     = FALSE,
                            BOOL      drawCalculatedRefObject = FALSE,
                            BOOL      drawTabOrder            = FALSE);

        /**
        * Switches the object matching with the tab order with the provided one
        *@param pObject - object to switch with
        *@param tabOrder - tab order for which the matching object should be switched
        */
        virtual void SwitchTabOrder(PSS_PlanFinObject* pObject, double tabOrder);

        /**
        * Automatically rebuilds the tab orders
        */
        virtual void AutomaticRebuildTabOrder();

        /**
        * Evaluate the last tab order of all objects
        *@return the evaluated last tab order
        */
        virtual double EvaluateLastTabOrder();

        /**
        * Assigns objects which should be a member of a multi-column field
        */
        virtual void AssignMultiColumnMemberFields();

        /**
        * Gets the object field name array
        *@return the object field name array
        */
        virtual inline CStringArray* GetObjectFieldNameArray() const;

        /**
        * Adds a new field name to the field name array, if it still not exists
        *@param fieldName - field name to add
        *@return true on success, otherwise false
        */
        virtual bool AddFieldNameInObectArray(const CString& Fieldname);

        /**
        * Builds the object field name array
        *@return true on success, otherwise false
        */
        virtual bool BuildObjectFieldNameArray();

        /**
        * Gets the file stamp
        *@return the file stamp
        */
        virtual inline PSS_Stamp& GetStamp();

        /**
        * Gets the schema manager
        *@return the schema manager
        */
        virtual inline PSS_SchemaManager& GetSchema();

        /**
        * Gets the document
        *@return the document
        */
        virtual inline PSS_Document* GetDocument();

        /**
        * Sets the document
        *@param pDocument - document
        */
        virtual inline void SetDocument(PSS_Document* pDocument);

        /**
        * Gets the font manager
        *@return the font manager
        */
        virtual inline PSS_FontManager& GetFontManager();

        /**
        * Gets the style manager
        *@return the style manager
        */
        virtual inline PSS_StyleManager& GetStyleManager();

        /**
        * Gets the buffer containing the temporary file created by the deserialized file buffer
        *@return the buffer containing the file
        */
        virtual inline const CString& GetFileBufferTemporaryFile() const;

        /**
        * Gets the file launcher
        *@return the file launcher
        */
        virtual inline PSS_FileLauncher& GetFileLauncher();

        /**
        * Gets the last tab order
        *@return the last tab order
        *@note This member is set when the last tab has been read
        */
        virtual inline const double GetLastTabOrder() const;

        /**
        * Sets the last tab order
        *@param value - the last tab order value
        *@note This member is set when the last tab has been read
        */
        virtual inline void SetLastTabOrder(double value);

        /**
        * Reads the file stamp
        *@param ar - archive containing the file stamp to read
        *@param[out] stamp - read stamp
        *@return the file stamp
        */
        static int SerializeStampRead(CArchive& ar, PSS_Stamp& stamp);

        /**
        * Serializes the document information in read mode
        *@param ar - archive containing the data to read
        */
        virtual void SerializeRead(CArchive& ar);

        /**
        * Writes the file stamp
        *@param ar - archive in which the file stamp should be written
        *@param stamp - stamp to write
        */
        static void SerializeStampWrite(CArchive& ar, PSS_Stamp& stamp);

        /**
        * Serializes the document information in write mode
        *@param ar - archive in which the data should be written
        */
        virtual void SerializeWrite(CArchive& ar);

        /**
        * Serializes the document information
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    protected:
        CTime m_EndCalculateTime;
        int   m_CurrentPage;

        /**
        * Calculates one formula
        *@param pFormula - formula
        *@param pWnd - window
        *@param pDC - device context
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CalculateFormula(PSS_Formula* pFormula, CWnd* pWnd = NULL, CDC* pDC = NULL);

        /**
        * Draws the binary file
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void OnDrawBinary(CDC* pDC, PSS_View* pView);

        /**
        * Draws the external binary file
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void OnDrawExternalBinary(CDC* pDC, PSS_View* pView);

        /**
        * Draws the background picture of a page
        *@param pDC - device context to draw to
        *@param pView - view
        *@param page - page index
        */
        virtual void OnDrawBackgroundPicture(CDC* pDC, PSS_View* pView, int page);

        /**
        * Draws the forms
        *@param pDC - device context to paint to
        *@param pView - view
        *@param drawCalculatedSymbol - if TRUE, calculated symbols will be drawn
        *@param drawHiddenObjects - if TRUE, hidden objects will be drawn
        *@param drawBoundRectObjects - if TRUE, bound rect objects will be drawn
        *@param drawCalculatedRefObject - if TRUE, calculated reference objects will be drawn
        *@param drawTabOrder - if TRUE, the tab order will be drawn
        */
        virtual void OnDrawForms(CDC*      pDC,
                                 PSS_View* pView,
                                 BOOL      drawCalculatedSymbol    = TRUE,
                                 BOOL      drawHiddenObject        = FALSE,
                                 BOOL      drawBoundRectObject     = FALSE,
                                 BOOL      drawCalculatedRefObject = FALSE,
                                 BOOL      drawTabOrder            = FALSE);

        /**
        * Draws the external forms
        *@param pDC - device context to paint to
        *@param pView - view
        *@param drawCalculatedSymbol - if TRUE, calculated symbols will be drawn
        *@param drawHiddenObjects - if TRUE, hidden objects will be drawn
        *@param drawBoundRectObjects - if TRUE, bound rect objects will be drawn
        *@param drawCalculatedRefObject - if TRUE, calculated reference objects will be drawn
        *@param drawTabOrder - if TRUE, the tab order will be drawn
        */
        virtual void OnDrawExternalForms(CDC*      pDC,
                                         PSS_View* pView,
                                         BOOL      drawCalculatedSymbol    = TRUE,
                                         BOOL      drawHiddenObject        = FALSE,
                                         BOOL      drawBoundRectObject     = FALSE,
                                         BOOL      drawCalculatedRefObject = FALSE,
                                         BOOL      drawTabOrder            = FALSE);

        /**
        * Draws the url
        *@param pDC - device context to paint to
        *@param pView - view
        */
        virtual void OnDrawURL(CDC* pDC, PSS_View* pView);

        /**
        * Checks if a field name exists in the object array
        *@return true if a field name exists in the object array, otherwise false
        */
        virtual bool FieldNameExistInObjectArray(const CString& fieldName);

    private:
        PSS_Document*      m_pDocument;
        PSS_FileBuffer*    m_pFileBuffer;
        PSS_Stamp          m_Stamp;
        PSS_SchemaManager  m_Schema;
        PSS_FontManager    m_FontManager;
        PSS_StyleManager   m_StyleManager;
        PSS_PlanFinObject* m_pCurrentEditedObject;
        PSS_FileLauncher   m_FileLauncher;
        CObList            m_ObjElements;
        POSITION           m_pPosition;
        CStringArray       m_FieldNameArray;
        CString            m_CurrentSchema;
        CString            m_FileBufferTemporaryFile;
        CString            m_BinaryDrawMessage;
        double             m_LastTabOrder;
        int                m_PageMax;
        BOOL               m_FlagElapsedTime;
        BOOL               m_IsVisible;
        BOOL               m_ReadOnlyAtRuntime;

        /**
        * Deletes the page objects
        *@param page - page index
        *@param redistribute - if TRUE, the objects will be redistributed
        *@return TRUE on success, otherwise FALSE
        */
        BOOL DeletePageObjects(int page, BOOL redistribute = TRUE);

        /**
        * Copies the page objects
        *@param pDocumentDst - destination document
        *@param page - page index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CopyPageObjects(PSS_DocumentData* pDocumentDst, int page);

        /**
        * Checks the object list
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CheckObjectList();
};

//---------------------------------------------------------------------------
// PSS_DocumentData
//---------------------------------------------------------------------------
CObList& PSS_DocumentData::GetObjectList()
{
    return m_ObjElements;
}
//---------------------------------------------------------------------------
int PSS_DocumentData::GetObjectCount() const
{
    return m_ObjElements.GetCount();
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_DocumentData::GetHead()
{
    m_pPosition = m_ObjElements.GetHeadPosition();

    return (m_pPosition ? (PSS_PlanFinObject*)m_ObjElements.GetHead() : NULL);
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_DocumentData::GetNext()
{
    if (m_pPosition)
    {
        m_ObjElements.GetNext(m_pPosition);

        if (m_pPosition)
            return (PSS_PlanFinObject*)m_ObjElements.GetAt(m_pPosition);
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_DocumentData::GetCurrentSchema() const
{
    return m_CurrentSchema;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetCurrentSchema(const CString& name)
{
    m_CurrentSchema = name;
}
//---------------------------------------------------------------------------
int PSS_DocumentData::GetMaxPage() const
{
    return m_PageMax;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetMaxPage(int page)
{
    m_PageMax = page;
}
//---------------------------------------------------------------------------
int PSS_DocumentData::GetCurrentPage() const
{
    return m_CurrentPage;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetCurrentPage(int page)
{
    m_CurrentPage = page;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_DocumentData::GetEditedObject(BOOL bCheckPage)
{
    return m_pCurrentEditedObject;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetEditedObject(PSS_PlanFinObject* pObj)
{
    m_pCurrentEditedObject = pObj;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::StartCalcTimer()
{
    // start the timer to count the elapsed time
    if (!m_FlagElapsedTime)
    {
        m_EndCalculateTime = CTime::GetCurrentTime();
        m_FlagElapsedTime  = TRUE;
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ResetCalcTimer()
{
    // reset the timer
    m_FlagElapsedTime = FALSE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SchemaListHasChanged()
{
    AfxGetMainWnd()->SendMessageToDescendants(ID_SCHEMALISTHASCHANGED);
    AfxGetMainWnd()->SendMessageToDescendants(ID_SETDEFAULTSCHEMA, 0, LPARAM((const char*)GetCurrentSchema()));
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ShowDocumentData()
{
    m_IsVisible = TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::HideDocumentData()
{
    m_IsVisible = FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::DocumentDataIsVisible() const
{
    return m_IsVisible;
}
//---------------------------------------------------------------------------
PSS_DocumentData* PSS_DocumentData::Clone() const
{
    return new PSS_DocumentData(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsReadOnly() const
{
    return m_Stamp.IsReadOnly();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetAsReadOnly(BOOL value)
{
    m_Stamp.SetAsReadOnly(value);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsStandardForm() const
{
    return m_Stamp.IsStandardForm();
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsInternalKeyEqualTo(const CString& key)
{
    return m_Stamp.IsInternalKeyEqualTo(key);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsReadOnlyAtRuntime() const
{
    return m_ReadOnlyAtRuntime || IsReadOnly();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetReadOnlyAtRuntime(BOOL value)
{
    m_ReadOnlyAtRuntime = value;
}
//---------------------------------------------------------------------------
PSS_FileBuffer* PSS_DocumentData::GetFileBuffer()
{
    return m_pFileBuffer;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsFormData() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_Form;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsBinaryData() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_Binary;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsExternalFormData() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_ExternalForm;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsExternalBinaryData() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_ExternalBinary;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsURLData() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_URL;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsBinaryDataValid() const
{
    return m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_Binary && m_pFileBuffer != NULL;
}
//---------------------------------------------------------------------------
CStringArray* PSS_DocumentData::GetObjectFieldNameArray() const
{
    return (CStringArray*)&m_FieldNameArray;
}
//---------------------------------------------------------------------------
PSS_Stamp& PSS_DocumentData::GetStamp()
{
    return m_Stamp;
}
//---------------------------------------------------------------------------
PSS_SchemaManager& PSS_DocumentData::GetSchema()
{
    return m_Schema;
}
//---------------------------------------------------------------------------
PSS_Document* PSS_DocumentData::GetDocument()
{
    return m_pDocument;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetDocument(PSS_Document* pDocument)
{
    m_pDocument = pDocument;
}
//---------------------------------------------------------------------------
PSS_FontManager& PSS_DocumentData::GetFontManager()
{
    return m_FontManager;
}
//---------------------------------------------------------------------------
PSS_StyleManager& PSS_DocumentData::GetStyleManager()
{
    return m_StyleManager;
}
//---------------------------------------------------------------------------
const CString& PSS_DocumentData::GetFileBufferTemporaryFile() const
{
    return m_FileBufferTemporaryFile;
}
//---------------------------------------------------------------------------
PSS_FileLauncher& PSS_DocumentData::GetFileLauncher()
{
    return m_FileLauncher;
}
//---------------------------------------------------------------------------
const double PSS_DocumentData::GetLastTabOrder() const
{
    return m_LastTabOrder;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetLastTabOrder(double value)
{
    m_LastTabOrder = value;
}
//---------------------------------------------------------------------------

#endif
