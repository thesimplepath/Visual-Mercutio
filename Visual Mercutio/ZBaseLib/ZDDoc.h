//## begin module%35CC307B0030.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35CC307B0030.cm

//## begin module%35CC307B0030.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%35CC307B0030.cp

//## Module: ZDDoc%35CC307B0030; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZDDoc.h

#ifndef ZDDoc_h
#define ZDDoc_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
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

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS
//## end module%35CC307B0030.additionalDeclarations


//## Class: ZDDocument%35CC2E450326
//## Category: ZBaseLib::Document classes%37E93F0B00CB
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%35CC30BF02EB;ZDFolderStamp { -> }
//## Uses: <unnamed>%35CC4D5702A1;ZDDocumentOptions { -> }
//## Uses: <unnamed>%36348FD801B7;ZAHistoryFieldManager { -> }
//## Uses: <unnamed>%36501B2200AE;ZUDocumentExport { -> }
//## Uses: <unnamed>%3678EEE70284;ZDDocumentData { -> }

class AFX_EXT_CLASS ZDDocument : public PSS_BaseDocument
{
public:
    // Inherited feature
    typedef PSS_BaseDocument inherited;

    void            GetStyleArrayName(CStringArray& StyleArray);
    void            StyleListHasChanged();
    void            FileListHasChanged();
    void            SelectStyleInList(const CString& sStyle);
    const     BOOL     ShouldShowHiddenField() const
    {
        return m_bShowHiddenField;
    };
    void             SetShowHiddenField(BOOL value = TRUE)
    {
        m_bShowHiddenField = value;
    };
    const     BOOL     ShouldPrintLine() const
    {
        return(m_bPrintLine);
    };
    void             SetPrintLine(BOOL value = TRUE)
    {
        m_bPrintLine = value;
    };
    size_t            GetVisibleDocumentDataCount() const;
    int                PreviousVisibleDocumentAvailable(size_t DocumentIndex) const;
    int                NextVisibleDocumentAvailable(size_t DocumentIndex) const;
    BOOL            CheckMultiColumnMemberField(PSS_PlanFinObject* obj, int DocumentIndex = -1);

    virtual ZIHtmlView*        GetHtmlView();

    //## end ZDDocument%35CC2E450326.initialDeclarations

public:
    //## Destructor (generated)
    virtual ~ZDDocument();


    //    Serialize document information.
    virtual void Serialize(CArchive& ar);

    //    Serialize in read mode the document information.
    virtual void SerializeRead(CArchive& ar);

    //    Serialize in write mode the document information.
    virtual void SerializeWrite(CArchive& ar);

    //    Initialize associations.
    void InitializeAllAssociations(int DocumentIndex = -1);

    //    Calculate all formulas.
    void CalculateAllFormula(CView* pView = NULL, BOOL AllPages = FALSE, int DocumentIndex = -1);

    //    Called by the frameword or the application.
    //    When the fields are calculated and then have changed
    //    theyr'e drawn with a different color, we must after a
    //    certain time clear the color and draw it with their
    //    color.
    void CheckForClearCalcField(CView* pView = NULL, int DocumentIndex = -1);

    //    Run through the field list and clear all associations.
    void ClearCurrentAssociation(int DocumentIndex = -1);

    //    When you change the schema, it is necessary to remove
    //    the switch for calculation of all number fields and to
    //    add it for result fields.
    void ChangeFieldForCalculation(int DocumentIndex = -1);

    //    Send a message to the main frame to specify that schema
    //    list has changed
    void SchemaListHasChanged(int DocumentIndex = -1);

    //    Run through the list of formula and try to find if the
    //    object is a result object
    BOOL IsCalculatedFieldInSchema(PSS_PlanFinObject* pObj, int DocumentIndex = -1);

    //    Refresh the current schema.
    void RefreshCurrentSchema(int DocumentIndex = -1);

    void InitializeAllObjectPointers();

    //    Change the current file.
    void ChangeCurrentFile(const CString& Name, BOOL bNotify = FALSE);

    //    Change the current file.
    void ChangeCurrentFile(size_t FileIndex, BOOL bNotify = FALSE);

    //    Change the current file.
    void ChangeCurrentFileOpen(const CString& Name, BOOL bNotify = FALSE);

    //    Change the current file.
    void ChangeCurrentFileOpen(size_t FileIndex, BOOL bNotify = FALSE);

    //## Other Operations (specified)
      //## Operation: GetObjectList%902579795
      //    Returns the object list reference.
    CObList& GetObjectList(int DocumentIndex = -1);

    //## Operation: GetObjectCount%902579796
    //    Returns the number of elements.
    int GetObjectCount(int DocumentIndex = -1);

    //## Operation: GetHead%902579797
    //    Return the head pointer of the object element list.
    PSS_PlanFinObject* GetHead(int DocumentIndex = -1);

    //## Operation: GetNext%902579798
    //    Return the next pointer of the object element list.
    PSS_PlanFinObject* GetNext(int DocumentIndex = -1);

    //## Operation: GetStandardSchema%902579800
    //    Returns the standard schema name.
    CString GetStandardSchema() const;

    //## Operation: GetCurrentSchema%902579801
    //    Returns the current assigned schema.
    CString GetCurrentSchema(int DocumentIndex = -1) const;

    //## Operation: SetCurrentSchema%902853326
    //    Sets the current schema.
    void SetCurrentSchema(const CString& Name, int DocumentIndex = -1);

    //## Operation: GetFormula%902943940
    //    Get the formula pointed by the object name passed in
    //    parameter.
    PSS_Formula* GetFormula(const CString& sName, int DocumentIndex = -1);

    //## Operation: GetObjectPtr%902943941
    //    This function run the list of objects and try to find
    //    the object defined by his name.
    PSS_PlanFinObject* GetObjectPtr(CString& strName, int DocumentIndex = -1);

    //## Operation: GetMaxPage%907776831
    //    Returns the number of pages.
    int GetMaxPage(int DocumentIndex = -1);

    //## Operation: SetMaxPage%907776837
    //    Sets the number of page.
    void SetMaxPage(int iPage, int DocumentIndex = -1);

    //## Operation: GetDefaultAssociationString%908101537
    //    Returns the default association string name.
    CString GetDefaultAssociationString() const;

    //## Operation: GetCurrentPage%938177643
    //    Returns the current page.
    int GetCurrentPage(int DocumentIndex = -1) const;

    //## Operation: SetCurrentPage%908460233
    //    Sets the current page.
    void SetCurrentPage(int iPage, int DocumentIndex = -1);

    //## Operation: GetSelectedObject%908460235
    //    Returns the selected object.
    PSS_PlanFinObject* GetSelectedObject(BOOL bCheckPage = TRUE, int DocumentIndex = -1);

    //## Operation: ObjectExist%908620921
    //    Tests if the object already exists.
    BOOL ObjectExist(const CString sName, int DocumentIndex = -1);

    //## Operation: GetMainView%910434310
    virtual ZIView* GetMainView();

    //## Operation: GetFormulaView%910633444
//      virtual CFormView* GetFormulaView ();

      //## Operation: GetProcessView%915657288
//      virtual CFormView* GetProcessView ();

      //## Operation: StartRealTimeExport%926842804
    BOOL StartRealTimeExport(BOOL Export = FALSE, BOOL Import = FALSE);

    //## Operation: IsRealTimeExported%911381917
    //    Specifies if the document is exported.
    BOOL IsRealTimeExported() const;

    //## Operation: DocumentHasBeenModified%911404701
    //    Called when the document has been modified.
    virtual void DocumentHasBeenModified();

    //## Operation: FieldHasBeenModified%911404702
    //    Called when one or more fields have been modified.
    virtual void FieldHasBeenModified();

    //## Operation: GetActiveDocumentData%913885109
    //    Returns the active document pointer.
    PSS_DocumentData* GetActiveDocumentData() const;

    //## Operation: GetDocumentDataCount%913885110
    //    Returns the number of document data.
    std::size_t GetDocumentDataCount() const;

    //## Operation: GetDocumentDataAt%913885111
    //    Returns the document data pointer depending on the index.
    PSS_DocumentData* GetDocumentDataAt(int DocumentIndex) const;

    //## Operation: RemoveAllDocumentData%913885112
    //    Remove all document data.
    void RemoveAllDocumentData();

    //## Operation: AddDocumentData%913885113
    //    Add a new document data.
    BOOL AddDocumentData(PSS_DocumentData* pDocData);

    //## Operation: AddDocumentDataAfter%914146158
    //    Add a new document data after a specific position.
    BOOL AddDocumentDataAfter(PSS_DocumentData* pDocData, int Index);

    //## Operation: GetStamp%913885114
    //    Returns the stamp of the document data specified by the
    //    DocumentIndex.
    PSS_Stamp& GetStamp(int DocumentIndex = -1);

    //## Operation: GetSchema%913970076
    //    Return the schema manager reference.
    PSS_SchemaManager& GetSchema(int DocumentIndex = -1);

    //## Operation: GetForecastedObjectCount%914146141
    //    Returns the forecasted object count.
    int GetForecastedObjectCount() const;

    //## Operation: SetForecastedObjectCount%914146142
    //    Sets the number of objects contained in the document.
    void SetForecastedObjectCount(int Value);

    //## Operation: CalculateForecastedObjectCount%914146143
    //    Calculates the object count. This function add all
    //    elements from all document data.
    void CalculateForecastedObjectCount();

    //## Operation: ShowDocumentData%914146144
    //    Show the document.
    void ShowDocumentData(int DocumentIndex = -1);

    //## Operation: HideDocumentData%914146145
    //    Hide the document.
    void HideDocumentData(int DocumentIndex = -1);

    //## Operation: ShowAllDocumentData%914146146
    //    Show all documents.
    void ShowAllDocumentData();

    //## Operation: HideAllDocumentData%914146147
    //    Hide all documents.
    void HideAllDocumentData();

    //## Operation: DocumentDataIsVisible%914146151
    //    Is the document visible.
    BOOL DocumentDataIsVisible(int DocumentIndex = -1);

    //## Operation: CopyDocumentDataArray%914146156
    //    Copy document data.
    BOOL CopyDocumentDataArray(ZDDocument* pDocSrc, BOOL InsertAsReadOnly = FALSE);

    //## Operation: CopyDocumentDataArray%914146157
    //    Copy document data.
    BOOL CopyDocumentDataArray(CObArray& ArraySrc, BOOL InsertAsReadOnly = FALSE);

    //## Operation: CopyDocumentDataArrayAfter%914146159
    //    Copy document data.
    BOOL CopyDocumentDataArrayAfter(ZDDocument* pDocSrc, int Index, BOOL InsertAsReadOnly = FALSE);

    //## Operation: CopyDocumentDataArrayAfter%914146160
    //    Copy document data.
    BOOL CopyDocumentDataArrayAfter(CObArray& ArraySrc, int Index, BOOL InsertAsReadOnly = FALSE);

    //## Operation: GetFontManager%914353652
    PSS_FontManager& GetFontManager(int DocumentIndex = -1);

    //## Operation: GetStyleManager%914353653
    PSS_StyleManager& GetStyleManager(int DocumentIndex = -1);

    //## Operation: PropagateFieldValue%914754357
    //    This function receives the field name and its value. Its
    //    role is to propagate the value to all document data.
    void PropagateFieldValue(PSS_PlanFinObject* pObj, int DocumentIndex = -2);

    //## Operation: GetDocumentDataName%914788970
    //    Fill a string array with the document data name.
    void GetDocumentDataName(CStringArray& Array, BOOL OnlyVisible = TRUE);

    //## Operation: FindDocumentData%915657293
    //    Find a document data, function of his name.
    int FindDocumentData(const CString& Name);

    //## Operation: DocumentDataIsReadOnly%936298275
    //    return TRUE if the document is read-only.
    BOOL DocumentDataIsReadOnly(int DocumentIndex = -1) const;

    //## Operation: DocumentDataSetAsReadOnly%936298276
    //    Set the file as read-only.
    void DocumentDataSetAsReadOnly(BOOL value = TRUE, int DocumentIndex = -1);

    //## Operation: DocumentDataIsStandardForm%936298277
    //    return TRUE if the form is standard.
    BOOL DocumentDataIsStandardForm(int DocumentIndex = -1) const;

    //## Operation: DocumentDataIsInternalKeyEqualTo%936298278
    //    return TRUE if the key is equal to the standard form.
    BOOL DocumentDataIsInternalKeyEqualTo(const CString Key, int DocumentIndex = -1);

    //## Operation: IsReadOnlyAtRuntime%936298281
    //    return TRUE if the document data is read-only at runtime.
    BOOL IsReadOnlyAtRuntime(int DocumentIndex = -1);

    //## Operation: SetReadOnlyAtRuntime%936298282
    //    Set the read-only flag at runtime.
    void SetReadOnlyAtRuntime(BOOL value = TRUE, int DocumentIndex = -1);

    //## Operation: SetAllDocReadOnlyAtRuntime%936393294
    //    Set the read-only flag at runtime, for all document data.
    void SetAllDocReadOnlyAtRuntime(BOOL value = TRUE);

    //## Operation: ChangeCurrentSchema%938177642
    //    Change the current schema.
    virtual void ChangeCurrentSchema(const CString& sName, BOOL bNotify = FALSE, int DocumentIndex = -1);

    //## Operation: StartCalcTimer%938177646
    //    Start the calculation timer.
    virtual void StartCalcTimer(int DocumentIndex = -1);

    //## Operation: ResetCalcTimer%938177647
    //    Reset the calculation timer.
    virtual void ResetCalcTimer(int DocumentIndex = -1);

    //## Operation: CreateAllTemporaryFileFromBuffer%938959774
    //    Create a all temporary file based on the file buffer.
    BOOL CreateAllTemporaryFileFromBuffer();

    //## Operation: DeleteAllTemporaryFiles%938959789
    //    Delete all allocated temporary files.
    BOOL DeleteAllTemporaryFiles();

    //## Operation: ReadDocument%939754013
    //    Read the document.
    virtual BOOL ReadDocument(const CString Filename);

    //## Operation: OnDraw%940782408
    //    Process the draw.
    virtual void OnDraw(CDC* pDC, ZIView* pView, int DocumentIndex = -1);

    //## Operation: StartTabOrder%947360844
    //    Clear the Tab Order counter.
    void StartTabOrder();

    //## Operation: IncrementTabOrder%947360845
    //    Increment the Tab Order counter.
    double IncrementTabOrder();

    //## Operation: SwitchTabOrder%947360847
    //    Take the tab order of the object and when found an
    //    object with the specified tab order, switch them
    //    together.
    void SwitchTabOrder(PSS_PlanFinObject* pObject, double TabOrder, int DocumentIndex = -1);

    //## Operation: AssignMultiColumnMemberFields%948318240
    //    Run through the object list and find if the object is a
    //    member of a multi-column field.
    void AssignMultiColumnMemberFields(int DocumentIndex = -1);

    //## Operation: AssignAllMultiColumnMemberFields%948318242
    //    Run through the object list and find if the object is a
    //    member of a multi-column field.
    void AssignAllMultiColumnMemberFields();

    //## Operation: GetObjectFieldNameArray%948540873
    //    Return an array of the object fieldname array.
    CStringArray* GetObjectFieldNameArray() const;

    //## Operation: AddFieldNameInObectArray%948540879
    //    Add a new fieldname to the fieldname array. First, check
    //    if the fieldname does not already exists.
    bool AddFieldNameInObectArray(const CString& Fieldname, int DocumentIndex = -1);

    //## Operation: BuildObjectFieldNameArray%948540872
    //    Build the array of the object fieldname.
    bool BuildObjectFieldNameArray();

    //## Operation: GetObjectFieldNameArrayOfDocument%948540874
    //    Return an array of the object fieldname array.
    CStringArray* GetObjectFieldNameArrayOfDocument(int DocumentIndex = -1) const;

    //## Operation: BuildObjectFieldNameArrayOfDocument%948540875
    //    Build the array of the object fieldname.
    bool BuildObjectFieldNameArrayOfDocument(int DocumentIndex = -1);

    //## Operation: SetFileType%902943943
    //## Operation: SetEditedObject%907776834
    //    Sets the current edited object.
    virtual void SetEditedObject(PSS_PlanFinObject* pObj, int DocumentIndex = -1);

    //## Operation: GetEditedObject%907776835
    //    Returns the current edited object.
    virtual PSS_PlanFinObject* GetEditedObject(BOOL bCheckPage = TRUE, int DocumentIndex = -1);

    //## Operation: GetEditControl%907776836
    //    Returns the pointeur on the edit control.
    virtual PSS_Edit* GetEditControl();

    //## Operation: AssignEditControl%907776838
    //    Assigns a new created edit control.
    void AssignEditControl(PSS_Edit* pEdit);

    //## Operation: CreateAutomaticNewName%908620920
    //    Create automatically a new name.
    void CreateAutomaticNewName(PSS_PlanFinObject* pObj);

    //## Operation: GetClipBoardObject%910355405
    //    Returns the current clipped object.
    PSS_PlanFinObject* GetClipBoardObject();

    //## Operation: CopyObjectToClipBoard%910355406
    //    Take the object and clone it to keep it in the clipboard.
    void CopyObjectToClipBoard(PSS_PlanFinObject* pObj);

    //## Operation: IsClipBoardEmpty%910355407
    //    Tests if the clipboard is empty or not.
    BOOL IsClipBoardEmpty() const;

    //## Operation: AssignPredefinedField%913970066
    //    Run through all objects and assigns predefined field
    //    value.
    void AssignPredefinedField(int DocumentIndex = -1);

    //## Operation: ChangeObjectType%913970067
    //    Change the object type.
    BOOL ChangeObjectType(PSS_PlanFinObject* obj, const CString& sName, const CString& sFinalValue, BOOL bPropagate = FALSE, int DocumentIndex = -1);

    //## Operation: InsertObject%913970068
    BOOL InsertObject(PSS_PlanFinObject* obj, PSS_FieldRepository* pFieldRepository = NULL, BOOL InsertInGlobalRepository = FALSE, int DocumentIndex = -1, BOOL Refresh = FALSE);
    BOOL InsertObjectAtHead(PSS_PlanFinObject* obj, PSS_FieldRepository* pFieldRepository = NULL, BOOL InsertInGlobalRepository = FALSE, int DocumentIndex = -1, BOOL Refresh = FALSE);

    //## Operation: DeleteObject%913970069
    BOOL DeleteObject(PSS_PlanFinObject* obj, BOOL DeleteFromMemory = TRUE, int DocumentIndex = -1, BOOL Refresh = FALSE);

    //## Operation: MoveObjectInOrder%913970070
    BOOL MoveObjectInOrder(PSS_PlanFinObject* obj, int DocumentIndex = -1);

    //## Operation: AssignObjectValue%913970071
    void AssignObjectValue(CString Name, CString Value, int Page, int PropagationMode = g_LocateAllPagesEmptyOnly, BOOL EmptyWhenZero = FALSE, int DocumentIndex = -1);

    //## Operation: SetCurrentPageToObject%913970072
    void SetCurrentPageToObject(PSS_PlanFinObject* obj, int DocumentIndex = -1);

    //    Insert a document file at the end of the document data
    //    array.
    virtual BOOL InsertDocument(const CString FileName, BOOL InsertAsReadOnly = FALSE, int PropagateValue = g_LocateAllDocumentsEmptyOnly);

    //    Insert a document file after a position into the
    //    document data array.
    virtual BOOL InsertDocumentAfter(const CString FileName, int IndexAfter, BOOL InsertAsReadOnly = FALSE, int PropagateValue = g_LocateAllDocumentsEmptyOnly);

    //    Insert a document file at the end of the document data
    //    array.
    virtual BOOL InsertExternalDocument(const CString FileName, BOOL InsertAsReadOnly = FALSE, int PropagateValue = g_LocateAllDocumentsEmptyOnly);

    //    Insert a document file after a position into the
    //    document data array.
    virtual BOOL InsertExternalDocumentAfter(const CString FileName, int IndexAfter, BOOL InsertAsReadOnly = FALSE, int PropagateValue = g_LocateAllDocumentsEmptyOnly);

    //    Insert a binary document file at the end of the document
    //    data array.
    virtual BOOL InsertBinaryDocument(const CString FileName, const CString InfoName = "", const CString InfoDescription = "");

    //    Insert a binary document file after a position into the
    //    document data array.
    virtual BOOL InsertBinaryDocumentAfter(const CString FileName, int IndexAfter, const CString InfoName = "", const CString InfoDescription = "");

    //    Insert a binary document file at the end of the document
    //    data array.
    virtual BOOL InsertExternalBinaryDocument(const CString FileName, const CString InfoName = "", const CString InfoDescription = "");

    //    Insert a binary document file after a position into the
    //    document data array.
    virtual BOOL InsertExternalBinaryDocumentAfter(const CString FileName, int IndexAfter, const CString InfoName = "", const CString InfoDescription = "");

    //    Insert a document file at the end of the document data
    //    array.
    virtual BOOL InsertURL(const CString URL);

    //    Insert a document file after a position into the
    //    document data array.
    virtual BOOL InsertURLAfter(const CString URL, int IndexAfter);

    //    Delete a document data at a specific position 
    virtual BOOL DeleteDocumentAt(int Index);
    //    Delete a document data 
    virtual BOOL DeleteDocumentData(PSS_DocumentData* pDocData);

    //## Operation: PropagateDocumentValue%934014431
    //    Propagate a value into the document.
    BOOL PropagateDocumentValue(CString Name, CString Value, int PropagationMode = g_LocateAllDocumentsEmptyOnly, BOOL EmptyWhenZero = FALSE, int DocumentIndex = -1, int Page = -1);

    //## Operation: PropagateDocumentValueFromTo%945026902
    //    Propagate a value into the document, using the index
    //    range.
    BOOL PropagateDocumentValueFromTo(CString Name, CString Value, int PropagationMode = g_LocateAllPagesEmptyOnly, BOOL EmptyWhenZero = FALSE, int DocumentIndexFrom = 0, int DocumentIndexTo = -1, int Page = -1);

    //## Operation: PropagateExternDocumentAllValues%934145355
    //    Propagate all values coming from a document into this
    //    document.
    BOOL PropagateExternDocumentAllValues(ZDDocument* pDoc, int PropagationMode = g_LocateAllDocumentsEmptyOnly, BOOL EmptyWhenZero = FALSE, int DocumentIndex = -1, int Page = -1);

    //## Operation: PropagateInternalDocumentAllValues%945006730
    //    Propagate all values coming from internal documents into
    //    this document.
    BOOL PropagateInternalDocumentAllValues(int IndexFrom = 0, int IndexTo = -1, int PropagationMode = g_LocateAllDocumentsEmptyOnly, BOOL EmptyWhenZero = FALSE, int DocumentIndex = -1, int Page = -1);

    //## Operation: PropagateInternalDocumentOnDocumentValues%945006731
    //    Propagate all values coming from internal documents into
    //    some internal documents.
    BOOL PropagateInternalDocumentOnDocumentValues(int InIndexFrom = 0, int InIndexTo = -1, int ToIndexFrom = 0, int ToIndexTo = -1, int PropagationMode = g_LocateAllDocumentsEmptyOnly, BOOL EmptyWhenZero = FALSE);

    //    Parse a line string to import the activity.
    virtual BOOL ImportActivityFromLineString(size_t CurrentActivity, CString Line);


    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DocOptions%35CC4CD303BA
      //    Contains the document options.
    PSS_DocumentOptions& GetDocOptions();

    //## Attribute: HistoryValueManager%36348F570175
    //    This is the manager of history field values.
    PSS_HistoryFieldManager& GetHistoryValueManager();

    //## Attribute: SynchronizationFileName%365171060273
    //    Sets the synchronization filename.
    const CString GetSynchronizationFileName() const;
    void SetSynchronizationFileName(CString value);

    //## Attribute: pRealTimeExport%3652AE800319
    //    Points to the real time export object.
    PSS_DocumentExport* GetpRealTimeExport();
    void SetpRealTimeExport(PSS_DocumentExport* value);

    //## Attribute: DocumentDataArray%3678EAF803E5
    //    Contains the documents data.
    CObArray& GetDocumentDataArray();

    //## Attribute: ActiveDocumentIndex%3678EB1D0352
    const int GetActiveDocumentIndex() const;
    void SetActiveDocumentIndex(int value);

    //## Attribute: CurrentElement%367CC3DF01CE
    //    Saves the current element
    const int GetCurrentElement() const;
    void SetCurrentElement(int value);

    //## Attribute: KeepOnlyFLF%382BC142033A
    //    Contains 1 if this document is only saved in FLF file.
    const BOOL GetKeepOnlyFLF() const;
    void SetKeepOnlyFLF(BOOL value);

    //## Attribute: CurrentTabOrder%38779649011C
    //    Represent the current tab order. This is used when
    //    reordering tabs.
    const double GetCurrentTabOrder() const;

    CString GetAutomaticNewName(PSS_PlanFinObject* pObj, int DocumentIndex = 0);

    virtual void OnCloseDocument();


    // Additional Public Declarations
      //## begin ZDDocument%35CC2E450326.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    //## end ZDDocument%35CC2E450326.public
protected:
    //## Constructors (generated)
    ZDDocument();


    //## Other Operations (specified)
    virtual BOOL    OnOpenDocument(const char* pszPathName);

    BOOL             OpenDocument(const char* pszPathName, BOOL bSetLastLoaded = TRUE);

    virtual void SerializeDocumentDataArrayRead(CArchive& ar);

    //    Check the formula for the object.
    void CheckFormulaObject(PSS_PlanFinObject* pOld, PSS_PlanFinObject* pNew, int DocumentIndex = -1);

    //## Operation: CreateRealTimeExport%911381913
    //    Functions of the document option, it is necessary to
    //    create the class for real time export.
    virtual BOOL CreateRealTimeExport();

    //## Operation: DeleteAllObjects%914061085
    //    Delete all objects.
    void DeleteAllObjects(int DocumentIndex = -1);

    //## Operation: CountAndSetPages%914061086
    //    Count all pages.
    int CountAndSetPages(int DocumentIndex = -1);

    //## Operation: DocumentCountAndSetPages%934274802
    //    Count all pages for all document data.
    int DocumentCountAndSetPages();

    //## Operation: FieldNameExistInObectArray%948540877
    //    Run through the fieldname array and find if the object
    //    already exists.
    bool FieldNameExistInObectArray(const CString& Fieldname);

    //## Operation: ReplaceCalculatedFields%913885117
    virtual void ReplaceCalculatedFields(int DocumentIndex = -1);

    //## Operation: SerializeDocumentDataArray%914077264
    virtual void SerializeDocumentDataArray(CArchive& ar);

    //## Operation: SerializeDocumentDataArrayWrite%914077265
    virtual void SerializeDocumentDataArrayWrite(CArchive& ar);

    void    SetCurrentPageToObject(PSS_PlanFinObject *obj);

    //## Operation: CheckDocumentFontAndStyle%914161846
    void CheckDocumentFontAndStyle();

    //## Operation: BuildAutomaticNewName%913970074
    CString BuildAutomaticNewName(const CString& sPrefix, int DocumentIndex = -1);
    CString BuildAutomaticNewName(const CString& sPrefix);

    // Retreive the document data index
    // if not found, return -1
    int GetDocumentDataIndex(PSS_DocumentData* pDocData);

    // Data Members for Class Attributes

      //## Attribute: pClipBoardObject%3642EAD201CB
      //    Points to the current copied object.
      //## begin ZDDocumentReadWrite::pClipBoardObject%3642EAD201CB.attr preserve=no  private: PSS_PlanFinObject* {U} NULL
    PSS_PlanFinObject* m_pClipBoardObject;
    //## end ZDDocumentReadWrite::pClipBoardObject%3642EAD201CB.attr

  // Data Members for Class Attributes

    PSS_Edit* m_strEdit;

    //## begin ZDDocument::DocOptions%35CC4CD303BA.attr preserve=no  public: ZDDocumentOptions {U} 
    PSS_DocumentOptions m_DocOptions;
    //## end ZDDocument::DocOptions%35CC4CD303BA.attr

    //## Attribute: wVersionNumber%35D08226028E
    //    Contains the old file version number.
    //## begin ZDDocument::wVersionNumber%35D08226028E.attr preserve=no  public: WORD {U} 
    WORD m_wVersionNumber;
    //## end ZDDocument::wVersionNumber%35D08226028E.attr

    //## begin ZDDocument::SynchronizationFileName%365171060273.attr preserve=no  public: CString {U} 
    CString m_SynchronizationFileName;
    //## end ZDDocument::SynchronizationFileName%365171060273.attr

    //## begin ZDDocument::pRealTimeExport%3652AE800319.attr preserve=no  public: ZUDocumentExport* {U} NULL
    PSS_DocumentExport* m_pRealTimeExport;
    //## end ZDDocument::pRealTimeExport%3652AE800319.attr

    //## begin ZDDocument::DocumentDataArray%3678EAF803E5.attr preserve=no  public: CObArray {V} 
    CObArray m_DocumentDataArray;
    //## end ZDDocument::DocumentDataArray%3678EAF803E5.attr

    //## begin ZDDocument::ActiveDocumentIndex%3678EB1D0352.attr preserve=no  public: int {V} -1
    int m_ActiveDocumentIndex;
    //## end ZDDocument::ActiveDocumentIndex%3678EB1D0352.attr

    //## Attribute: iObjectCounter%367CC31D007B
    //    Defines the number of elements in the ObjectList.
    //## begin ZDDocument::iObjectCounter%367CC31D007B.attr preserve=no  public: INT {U} 
    INT m_iObjectCounter;
    //## end ZDDocument::iObjectCounter%367CC31D007B.attr

  // Additional Protected Declarations
    //## begin ZDDocument%35CC2E450326.protected preserve=yes
  //{{AFX_MSG(ZDDocument)
    afx_msg void OnPageRecalculate();
    afx_msg void OnPageNext();
    afx_msg void OnPagePrev();
    afx_msg void OnUpdatePagePrev(CCmdUI* pCmdUI);
    afx_msg void OnUpdatePageNext(CCmdUI* pCmdUI);
    afx_msg void OnPageRefresh();
    afx_msg void OnFileNext();
    afx_msg void OnUpdateFileNext(CCmdUI* pCmdUI);
    afx_msg void OnFilePrev();
    afx_msg void OnUpdateFilePrev(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_SERIAL(ZDDocument)

    size_t            CalculateVisibleDocumentDataCount();
    //## end ZDDocument%35CC2E450326.protected
private:
    //## Constructors (generated)
    ZDDocument(const ZDDocument& right);

    //## Assignment Operation (generated)
    const ZDDocument& operator = (const ZDDocument& right);

    // Data Members for Class Attributes

      //## begin ZDDocument::HistoryValueManager%36348F570175.attr preserve=no  public: ZAHistoryFieldManager {U} 
    PSS_HistoryFieldManager m_HistoryValueManager;
    //## end ZDDocument::HistoryValueManager%36348F570175.attr

    //## begin ZDDocument::CurrentElement%367CC3DF01CE.attr preserve=no  public: int {U} 
    int m_CurrentElement;
    //## end ZDDocument::CurrentElement%367CC3DF01CE.attr

    //## begin ZDDocument::KeepOnlyFLF%382BC142033A.attr preserve=no  public: BOOL {U} 
    BOOL m_KeepOnlyFLF;
    //## end ZDDocument::KeepOnlyFLF%382BC142033A.attr

    //## begin ZDDocument::CurrentTabOrder%38779649011C.attr preserve=no  public: double {U} 
    double m_CurrentTabOrder;
    //## end ZDDocument::CurrentTabOrder%38779649011C.attr

    //## Attribute: FieldNameArray%38899E120060
    //    Contains all field names for all document data.
    //## begin ZDDocument::FieldNameArray%38899E120060.attr preserve=no  private: CStringArray {U} 
    CStringArray m_FieldNameArray;
    //## end ZDDocument::FieldNameArray%38899E120060.attr

  // Additional Private Declarations
    //## begin ZDDocument%35CC2E450326.private preserve=yes
    //## end ZDDocument%35CC2E450326.private

private:  //## implementation
  // Additional Implementation Declarations
    //## begin ZDDocument%35CC2E450326.implementation preserve=yes
    BOOL    m_bShowHiddenField;
    BOOL    m_bPrintLine;
    size_t    m_VisibleDocumentDataCount;
    //## end ZDDocument%35CC2E450326.implementation
};

//## begin ZDDocument%35CC2E450326.postscript preserve=yes
//## end ZDDocument%35CC2E450326.postscript

// Class ZDDocument 


//## Other Operations (inline)

inline BOOL ZDDocument::IsRealTimeExported() const
{
    //## begin ZDDocument::IsRealTimeExported%911381917.body preserve=yes
    return m_pRealTimeExport != NULL;
    //## end ZDDocument::IsRealTimeExported%911381917.body
}

inline PSS_DocumentData* ZDDocument::GetActiveDocumentData() const
{
    //## begin ZDDocument::GetActiveDocumentData%913885109.body preserve=yes
    if (GetActiveDocumentIndex() == -1 || GetDocumentDataCount() == 0)
        return NULL;
    return GetDocumentDataAt(GetActiveDocumentIndex());
    //## end ZDDocument::GetActiveDocumentData%913885109.body
}

inline size_t ZDDocument::GetDocumentDataCount() const
{
    //## begin ZDDocument::GetDocumentDataCount%913885110.body preserve=yes
    return m_DocumentDataArray.GetSize();
    //## end ZDDocument::GetDocumentDataCount%913885110.body
}

inline PSS_DocumentData* ZDDocument::GetDocumentDataAt(int DocumentIndex) const
{
    //## begin ZDDocument::GetDocumentDataAt%913885111.body preserve=yes
    if (DocumentIndex < (int)GetDocumentDataCount() && DocumentIndex >= 0)
        return (PSS_DocumentData*)m_DocumentDataArray.GetAt(DocumentIndex);
    return NULL;
    //## end ZDDocument::GetDocumentDataAt%913885111.body
}

inline BOOL ZDDocument::AddDocumentData(PSS_DocumentData* pDocData)
{
    //## begin ZDDocument::AddDocumentData%913885113.body preserve=yes
    return m_DocumentDataArray.Add((CObject*)pDocData) >= 0;
    //## end ZDDocument::AddDocumentData%913885113.body
}

inline BOOL ZDDocument::AddDocumentDataAfter(PSS_DocumentData* pDocData, int Index)
{
    //## begin ZDDocument::AddDocumentDataAfter%914146158.body preserve=yes
    TRY
    {
        m_DocumentDataArray.InsertAt(Index, (CObject*)pDocData);
        return TRUE;
    }
        CATCH(CMemoryException, e)
    {
        return FALSE;
    }
    END_CATCH
        return FALSE;
    //## end ZDDocument::AddDocumentDataAfter%914146158.body
}

inline int ZDDocument::GetForecastedObjectCount() const
{
    //## begin ZDDocument::GetForecastedObjectCount%914146141.body preserve=yes
    return m_iObjectCounter;
    //## end ZDDocument::GetForecastedObjectCount%914146141.body
}

inline void ZDDocument::SetForecastedObjectCount(int Value)
{
    //## begin ZDDocument::SetForecastedObjectCount%914146142.body preserve=yes
    m_iObjectCounter = Value;
    //## end ZDDocument::SetForecastedObjectCount%914146142.body
}


inline void ZDDocument::StartTabOrder()
{
    //## begin ZDDocument::StartTabOrder%947360844.body preserve=yes
    m_CurrentTabOrder = 0;
    //## end ZDDocument::StartTabOrder%947360844.body
}

inline double ZDDocument::IncrementTabOrder()
{
    //## begin ZDDocument::IncrementTabOrder%947360845.body preserve=yes
    ++m_CurrentTabOrder;
    return m_CurrentTabOrder;
    //## end ZDDocument::IncrementTabOrder%947360845.body
}

inline CStringArray* ZDDocument::GetObjectFieldNameArray() const
{
    //## begin ZDDocument::GetObjectFieldNameArray%948540873.body preserve=yes
    return (CStringArray*)&m_FieldNameArray;
    //## end ZDDocument::GetObjectFieldNameArray%948540873.body
}


//## Get and Set Operations for Class Attributes (inline)

inline PSS_DocumentOptions& ZDDocument::GetDocOptions()
{
    //## begin ZDDocument::GetDocOptions%35CC4CD303BA.get preserve=no
    return m_DocOptions;
    //## end ZDDocument::GetDocOptions%35CC4CD303BA.get
}

inline PSS_HistoryFieldManager& ZDDocument::GetHistoryValueManager()
{
    return m_HistoryValueManager;
}

inline const CString ZDDocument::GetSynchronizationFileName() const
{
    //## begin ZDDocument::GetSynchronizationFileName%365171060273.get preserve=no
    return m_SynchronizationFileName;
    //## end ZDDocument::GetSynchronizationFileName%365171060273.get
}

inline void ZDDocument::SetSynchronizationFileName(CString value)
{
    //## begin ZDDocument::SetSynchronizationFileName%365171060273.set preserve=no
    m_SynchronizationFileName = value;
    //## end ZDDocument::SetSynchronizationFileName%365171060273.set
}

inline PSS_DocumentExport* ZDDocument::GetpRealTimeExport()
{
    //## begin ZDDocument::GetpRealTimeExport%3652AE800319.get preserve=no
    return m_pRealTimeExport;
    //## end ZDDocument::GetpRealTimeExport%3652AE800319.get
}

inline void ZDDocument::SetpRealTimeExport(PSS_DocumentExport* value)
{
    //## begin ZDDocument::SetpRealTimeExport%3652AE800319.set preserve=no
    m_pRealTimeExport = value;
    //## end ZDDocument::SetpRealTimeExport%3652AE800319.set
}

inline CObArray& ZDDocument::GetDocumentDataArray()
{
    //## begin ZDDocument::GetDocumentDataArray%3678EAF803E5.get preserve=no
    return m_DocumentDataArray;
    //## end ZDDocument::GetDocumentDataArray%3678EAF803E5.get
}

inline const int ZDDocument::GetActiveDocumentIndex() const
{
    //## begin ZDDocument::GetActiveDocumentIndex%3678EB1D0352.get preserve=no
    return m_ActiveDocumentIndex;
    //## end ZDDocument::GetActiveDocumentIndex%3678EB1D0352.get
}

inline void ZDDocument::SetActiveDocumentIndex(int value)
{
    //## begin ZDDocument::SetActiveDocumentIndex%3678EB1D0352.set preserve=no
    m_ActiveDocumentIndex = value;
    //## end ZDDocument::SetActiveDocumentIndex%3678EB1D0352.set
}

inline const int ZDDocument::GetCurrentElement() const
{
    //## begin ZDDocument::GetCurrentElement%367CC3DF01CE.get preserve=no
    return m_CurrentElement;
    //## end ZDDocument::GetCurrentElement%367CC3DF01CE.get
}

inline void ZDDocument::SetCurrentElement(int value)
{
    //## begin ZDDocument::SetCurrentElement%367CC3DF01CE.set preserve=no
    m_CurrentElement = value;
    //## end ZDDocument::SetCurrentElement%367CC3DF01CE.set
}

inline const BOOL ZDDocument::GetKeepOnlyFLF() const
{
    //## begin ZDDocument::GetKeepOnlyFLF%382BC142033A.get preserve=no
    return m_KeepOnlyFLF;
    //## end ZDDocument::GetKeepOnlyFLF%382BC142033A.get
}

inline void ZDDocument::SetKeepOnlyFLF(BOOL value)
{
    //## begin ZDDocument::SetKeepOnlyFLF%382BC142033A.set preserve=no
    m_KeepOnlyFLF = value;
    //## end ZDDocument::SetKeepOnlyFLF%382BC142033A.set
}

inline const double ZDDocument::GetCurrentTabOrder() const
{
    //## begin ZDDocument::GetCurrentTabOrder%38779649011C.get preserve=no
    return m_CurrentTabOrder;
    //## end ZDDocument::GetCurrentTabOrder%38779649011C.get
}

//## begin module%35CC307B0030.epilog preserve=yes

inline size_t ZDDocument::GetVisibleDocumentDataCount() const
{
    return m_VisibleDocumentDataCount;
}


inline    void        ZDDocument::StyleListHasChanged()
{
    // Send a message to the MDI Page to specify that the style list has changed
    AfxGetMainWnd()->SendMessageToDescendants(ID_STYLELISTHASCHANGED);
}

inline    void        ZDDocument::SelectStyleInList(const CString& sStyle)
{
    // Send a message to the MDI Page to select a style in the style list
    AfxGetMainWnd()->SendMessageToDescendants(ID_SETSTYLEINLIST, 0, (LPARAM)(const char*)sStyle);
}


inline    void        ZDDocument::FileListHasChanged()
{
    CalculateVisibleDocumentDataCount();
    // Send a message to the MDI Page to specify that the file list has changed
    AfxGetMainWnd()->SendMessageToDescendants(UM_FILELISTHASCHANGED);
}


inline BOOL ZDDocument::OnOpenDocument(const char* pszPathName)
{
    return OpenDocument(pszPathName, TRUE);
}


inline PSS_Edit* ZDDocument::GetEditControl()
{
    //## begin ZDDocumentReadWrite::GetEditControl%907776836.body preserve=yes
    return m_strEdit;
    //## end ZDDocumentReadWrite::GetEditControl%907776836.body
}

inline void ZDDocument::AssignEditControl(PSS_Edit* pEdit)
{
    //## begin ZDDocumentReadWrite::AssignEditControl%907776838.body preserve=yes
    m_strEdit = pEdit;
    //## end ZDDocumentReadWrite::AssignEditControl%907776838.body
}

inline PSS_PlanFinObject* ZDDocument::GetClipBoardObject()
{
    //## begin ZDDocumentReadWrite::GetClipBoardObject%910355405.body preserve=yes
    return m_pClipBoardObject;
    //## end ZDDocumentReadWrite::GetClipBoardObject%910355405.body
}

inline BOOL ZDDocument::IsClipBoardEmpty() const
{
    //## begin ZDDocumentReadWrite::IsClipBoardEmpty%910355407.body preserve=yes
    return m_pClipBoardObject == NULL;
    //## end ZDDocumentReadWrite::IsClipBoardEmpty%910355407.body
}

inline BOOL ZDDocument::ImportActivityFromLineString(size_t CurrentActivity, CString Line)
{
    // Base class does nothing
    return FALSE;
}

#endif
