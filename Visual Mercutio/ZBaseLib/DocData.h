//## begin module%3678E2A3038D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3678E2A3038D.cm

//## begin module%3678E2A3038D.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%3678E2A3038D.cp

//## Module: DocData%3678E2A3038D; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\DocData.h

#ifndef DocData_h
#define DocData_h 1

//## begin module%3678E2A3038D.additionalIncludes preserve=no
//## end module%3678E2A3038D.additionalIncludes

//## begin module%3678E2A3038D.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "Formula.h"

// Stamp
#include "Stamp.h"

// ZAStylMg
#include "ZAStylMg.h"

// ZAFontMg
#include "ZAFontMg.h"

#include "ZUFileLauncher.h"

///////////////////////////////////////////////////////////////////
// Forward declaration
class ZDDocument;
class ZBFileBuffer;
class PlanFinObject;
class ZBFieldRepository;
class ZIView;

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%3678E2A3038D.additionalDeclarations

// JMR-MODIF - Le 16 janvier 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZDDocumentData%3678E27C00F2
// This classe encapsulates the document data. Therefore,
// we can have several document data in one file.
//## Category: ZBaseLib::Document classes%37E93F0B00CB
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3678F71703B5;ZDStamp { -> }
//## Uses: <unnamed>%35D0788E00C0;ZAStyleManager { -> }
//## Uses: <unnamed>%35D0788A036D;ZAFontManager { -> }
//## Uses: <unnamed>%37F7055B0015;ZBFileBuffer { -> }

// Class ZDDocumentData
class AFX_EXT_CLASS ZDDocumentData : public CObject  //## Inherits: <unnamed>%3678F367029F
{
protected:

	// Additional Protected Declarations
	//## begin ZDDocumentData%3678E27C00F2.protected preserve=yes
	DECLARE_SERIAL( ZDDocumentData )
	//## end ZDDocumentData%3678E27C00F2.protected

public:

	//## begin ZDDocumentData%3678E27C00F2.initialDeclarations preserve=yes
	// Inherited feature
	typedef CObject inherited;
	//## end ZDDocumentData%3678E27C00F2.initialDeclarations

public:

	//## Constructors (generated)
	ZDDocumentData( const ZDDocumentData &right );

	//## Constructors (specified)
	//## Operation: ZDDocumentData%913885072
	// The default constructor.
	ZDDocumentData ( ZDDocument* pDocument = NULL );

	//## Destructor (generated)
	virtual ~ZDDocumentData();

public:

	//## Assignment Operation (generated)
	const ZDDocumentData & operator=( const ZDDocumentData &right );

public:

	double	GetObjectValue( char *cpName );

	BOOL	DeletePage( int iPage );
	BOOL	CopyPage( ZDDocumentData* pDocumentDst, int iPage );
	BOOL	CopyPageOnlyObjects( ZDDocumentData* pDocumentDst, int iPage );
	BOOL	CopyPageOnlyFormula( ZDDocumentData* pDocumentDst, int iPage );
	BOOL	CheckMultiColumnMemberField( PlanFinObject* obj );

	void	MoveContents( ZDDocumentData* pDocument, BOOL bCopyFormat );
	void	StyleHasBeenDeleted( HandleStyle hStyle );
	void	CheckFontValidity();

	//## Other Operations (specified)
	//## Operation: GetObjectList%913885073
	// Returns the object list reference.
	CObList& GetObjectList();

	//## Operation: GetObjectCount%913885074
	// Returns the number of elements.
	int GetObjectCount();

	//## Operation: GetHead%913885075
	// Return the head pointer of the object element list.
	PlanFinObject* GetHead();

	//## Operation: GetNext%913885076
	// Return the next pointer of the object element list.
	PlanFinObject* GetNext();

	//## Operation: GetCurrentSchema%913885078
	// Returns the current assigned schema.
	CString GetCurrentSchema() const;

	//## Operation: SetCurrentSchema%913885079
	// Sets the current schema.
	void SetCurrentSchema( const CString& Name );

	//## Operation: GetFormula%913885081
	// Get the formula pointed by the object name passed in
	// parameter.
	ZAFormula* GetFormula( const CString& sName );

	//## Operation: GetObjectPtr%913885082
	// This function run the list of objects and try to find
	// the object defined by his name.
	PlanFinObject* GetObjectPtr( CString& strName );

	//## Operation: GetMaxPage%913885083
	// Returns the number of pages.
	int GetMaxPage();

	//## Operation: SetMaxPage%913885084
	// Sets the number of page.
	void SetMaxPage( int iPage );

	//## Operation: GetCurrentPage%913885087
	// Returns the current page.
	int GetCurrentPage() const;

	//## Operation: SetCurrentPage%913885088
	// Sets the current page.
	void SetCurrentPage( int iPage );

	//## Operation: GetSelectedObject%913885089
	// Returns the selected object.
	PlanFinObject* GetSelectedObject( BOOL bCheckPage = TRUE );

	//## Operation: SetEditedObject%913885090
	// Sets the current edited object.
	virtual void SetEditedObject( PlanFinObject* pObj );

	//## Operation: GetEditedObject%913885091
	// Returns the current edited object.
	virtual PlanFinObject* GetEditedObject( BOOL bCheckPage = TRUE );

	//## Operation: CheckFormulaObject%913885106
	// Check the formula for the object.
	void CheckFormulaObject( PlanFinObject* pOld, PlanFinObject* pNew );

	//## Operation: ObjectExist%913885093
	//	Tests if the object already exists.
	BOOL ObjectExist( const CString sName );

	//## Operation: InitializeAllAssociations%913885095
	// Initialize associations.
	void InitializeAllAssociations();

	//## Operation: CalculateAllFormula%913885096
	// Calculate all formulas.
	void CalculateAllFormula( CView* pView = NULL, BOOL AllPages = FALSE );

	//## Operation: CheckForClearCalcField%913885097
	// Called by the frameword or the application.
	// When the fields are calculated and then have changed
	// theyr'e drawn with a different color, we must after a
	// certain time clear the color and draw it with their
	// color.
	void CheckForClearCalcField( CView* pView = NULL );

	//## Operation: StartCalcTimer%917889605
	// Start the calculation timer.
	void StartCalcTimer();

	//## Operation: ResetCalcTimer%913885098
	// Reset the calculation timer.
	void ResetCalcTimer();

	//## Operation: ChangeCurrentSchema%913885099
	// Change the current schema.
	void ChangeCurrentSchema( const CString& sName, BOOL bNotify = FALSE );

	//## Operation: ClearCurrentAssociation%913885100
	// Run through the field list and clear all associations.
	void ClearCurrentAssociation();

	//## Operation: ChangeFieldForCalculation%913885101
	// When you change the schema, it is necessary to remove
	// the switch for calculation of all number fields and to
	// add it for result fields.
	void ChangeFieldForCalculation();

	//## Operation: SchemaListHasChanged%913885102
	// Send a message to the main frame to specify that schema
	// list has changed
	void SchemaListHasChanged();

	//## Operation: IsCalculatedFieldInSchema%913885103
	// Run through the list of formula and try to find if the
	// object is a result object
	BOOL IsCalculatedFieldInSchema( PlanFinObject* pObj );

	//## Operation: RefreshCurrentSchema%913885104
	// Refresh the current schema.
	void RefreshCurrentSchema();

	//## Operation: ChangeCalculatedFieldInAssociation%913885108
	// When you change the schema, it is necessary to remove
	// the switch for calculation of all number fields and to
	// add it for result fields.
	void ChangeCalculatedFieldInAssociation( ZAFormulaAssociation* pAssociation );

	//## Operation: ReplaceCalculatedFields%913885115
	void ReplaceCalculatedFields();

	//## Operation: AssignPredefinedField%913885122
	// Run through all objects and assigns predefined field
	// value.
	void AssignPredefinedField();

	//## Operation: ChangeObjectType%913885123
	// Change the object type.
	BOOL ChangeObjectType( PlanFinObject* obj, const CString& sName, const CString& sFinalValue, BOOL bPropagate = FALSE );

	//## Operation: BuildAutomaticNewName%913885124
	CString BuildAutomaticNewName( const CString& sPrefix );

	//## Operation: InsertObject%913885125
	BOOL InsertObject( PlanFinObject*		obj,
					   ZBFieldRepository*	pFieldRepository			= NULL,
					   BOOL					InsertInGlobalRepository	= FALSE,
					   BOOL					Refresh						= FALSE );

	BOOL InsertObjectAtHead( PlanFinObject*		obj,
							 ZBFieldRepository*	pFieldRepository			= NULL,
							 BOOL				InsertInGlobalRepository	= FALSE,
							 BOOL				Refresh						= FALSE );

	//## Operation: DeleteObject%913885126
	BOOL DeleteObject( PlanFinObject* obj, BOOL DeleteFromMemory = TRUE, BOOL Refresh = FALSE );

	//## Operation: MoveObjectInOrder%913885127
	BOOL MoveObjectInOrder( PlanFinObject* obj );

	//## Operation: AssignObjectValue%913885128
	// Return false if something is incoherent.
	BOOL AssignObjectValue( CString	Name,
							CString	Value,
							int		Page,
							int		PropagationMode	= LocateAllPages,
							BOOL	EmptyWhenZero	= FALSE );

	//## Operation: SetCurrentPageToObject%913885130
	void SetCurrentPageToObject( PlanFinObject* obj );

	//## Operation: DeleteAllObjects%914061087
	// Delete all objects.
	void DeleteAllObjects();

	//## Operation: CountAndSetPages%914061088
	// Count all pages.
	int CountAndSetPages();

	//## Operation: CloneSelectedObject%914061089
	PlanFinObject* CloneSelectedObject();

	//## Operation: RebuildAllAutomaticNumbered%914061090
	void RebuildAllAutomaticNumbered();

	//## Operation: SetCurrentStyle%914061093
	void SetCurrentStyle( const CString& sName );

	//## Operation: IsCalculatedFieldInAssociation%914061094
	BOOL IsCalculatedFieldInAssociation( PlanFinObject* pObj );

	//## Operation: ShowDocumentData%914146148
	// Show the document.
	void ShowDocumentData();

	//## Operation: HideDocumentData%914146149
	// Hide the document.
	void HideDocumentData();

	//## Operation: DocumentDataIsVisible%914146150
	// Is the document visible.
	BOOL DocumentDataIsVisible();

	//## Operation: Clone%914146161
	// Clone the Document Data.
	ZDDocumentData* Clone();

	//## Operation: InitializeAllObjectPointers%914353650
	void InitializeAllObjectPointers();

	//## Operation: PropagateFieldValue%914754358
	// This function receives the field name and its value. Its
	// role is to propagate the value within the document data.
	void PropagateFieldValue( PlanFinObject* pObj );

	//## Operation: AssignNewStyle%922093646
	// An old style must be replaced by a new one, all objects
	// refering to this old style must be redirected to the new
	// style.
	void AssignNewStyle( HandleStyle hOldStyle, HandleStyle hNewStyle );

	//## Operation: IsReadOnly%936298264
	// return TRUE if the document is read-only.
	BOOL IsReadOnly() const;

	//## Operation: SetAsReadOnly%936298265
	// Set the file as read-only.
	void SetAsReadOnly( BOOL value = TRUE );

	//## Operation: IsStandardForm%936298266
	// return TRUE if the form is standard.
	BOOL IsStandardForm() const;

	//## Operation: IsInternalKeyEqualTo%936298267
	// return TRUE if the key is equal to the standard form.
	BOOL IsInternalKeyEqualTo( const CString Key );

	//## Operation: IsReadOnlyAtRuntime%936298279
	// return TRUE if the document data is read-only at runtime.
	BOOL IsReadOnlyAtRuntime();

	//## Operation: SetReadOnlyAtRuntime%936298280
	// Set the read-only flag at runtime.
	void SetReadOnlyAtRuntime( BOOL value = TRUE );

	//## Operation: CreateBufferFromFile%938933078
	// From a file, create the class.
	BOOL CreateBufferFromFile( const CString Filename );

	//## Operation: CreateFileFromBuffer%938933079
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateFileFromBuffer( const CString Filename );

	//## Operation: CreateTemporaryFileFromBuffer%938959773
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateTemporaryFileFromBuffer();

	//## Operation: ClearFileBuffer%938933080
	// Clear the class.
	void ClearFileBuffer();

	//## Operation: GetFileBufferPointer%938933081
	// Returns the file buffer pointer.
	ZBFileBuffer* GetFileBufferPointer();

	// Return TRUE if it is a form data.
	BOOL IsFormData() const;

	// Return TRUE if it is a binary data.
	BOOL IsBinaryData() const;

	// Return TRUE if it is an external form data.
	BOOL IsExternalFormData() const;

	// Return TRUE if it is an external binary data.
	BOOL IsExternalBinaryData() const;

	// Return TRUE if it is an URL.
	BOOL IsURLData() const;

	// Return TRUE if the binary data member is valid.
	BOOL IsBinaryDataValid() const;

	//## Operation: DeleteTemporaryFile%938959790
	// Delete allocated temporary file.
	BOOL DeleteTemporaryFile();

	//## Operation: OnDraw%940782409
	// Process the draw.
	virtual void OnDraw( CDC*		pDC,
						 ZIView*	pView,
						 BOOL		DrawCalculatedSymbol	= TRUE,
						 BOOL		DrawHiddenObject		= FALSE,
						 BOOL		DrawBoundRectObject		= FALSE,
						 BOOL		DrawCalculatedRefObject	= FALSE,
						 BOOL		DrawTabOrder			= FALSE );

	//## Operation: SwitchTabOrder%947360846
	// Take the tab order of the object and when found an
	// object with the specified tab order, switch them
	// together.
	void SwitchTabOrder( PlanFinObject* pObject, double TabOrder );

	//## Operation: AutomaticRebuildTabOrder%947360849
	// Automatically rebuild the tab order.
	void AutomaticRebuildTabOrder();

	//## Operation: EvaluateLastTabOrder%947360850
	// Run through all objects and evaluate the last tab order.
	double EvaluateLastTabOrder();

	//## Operation: AssignMultiColumnMemberFields%948318241
	// Run through the object list and find if the object is a
	// member of a multi-column field.
	void AssignMultiColumnMemberFields();

	//## Operation: GetObjectFieldNameArray%948540870
	// Return an array of the object fieldname array.
	CStringArray* GetObjectFieldNameArray() const;

	//## Operation: AddFieldNameInObectArray%948540878
	//	Add a new fieldname to the fieldname array. First, check
	//	if the fieldname does not already exists.
	bool AddFieldNameInObectArray( const CString& Fieldname );

	//## Operation: BuildObjectFieldNameArray%948540871
	// Build the array of the object fieldname.
	bool BuildObjectFieldNameArray();

	//## Get and Set Operations for Class Attributes (generated)

	//## Attribute: Stamp%3678F1340014
	// Contains the file stamp.
	ZDStamp& GetStamp();

	//## Attribute: Schema%3678E34A0275
	// The schema manager.
	ZASchemaManager& GetSchema();

	//## Attribute: pDocument%3678E63E02F4
	// A pointer to the document.
	ZDDocument* GetpDocument();
	void SetpDocument( ZDDocument* value );

	//## Attribute: FontManager%367FF58803CE
	// The manager that contains the fonts.
	ZAFontManager& GetFontManager();

	//## Attribute: StyleManager%367FF58F02AC
	// The manager of styles.
	ZAStyleManager& GetStyleManager();

	//## Attribute: FileBufferTemporaryFile%37F762B9004B
	// Contains the temporary file created by the FileBuffer
	// deserialized.
	const CString& GetFileBufferTemporaryFile() const;

	//## Attribute: FileLauncher%37F780D50095
	// The file launcher.
	ZUFileLauncher& GetFileLauncher();

	//## Attribute: LastTabOrder%3877A3200079
	// Contains the last tab order. This member is set when the
	// has been read.
	const double GetLastTabOrder() const;
	void SetLastTabOrder( double value );

	//## Operation: SerializeStampRead%913885118
	// Read the file stamp.
	static int SerializeStampRead( CArchive& ar, ZDStamp& Stamp );

	//## Operation: SerializeRead%913885119
	// Serialize in read mode the document information.
	virtual void SerializeRead( CArchive& ar );

	//## Operation: SerializeStampWrite%913885120
	// Write the file stamp.
	static void SerializeStampWrite( CArchive& ar, ZDStamp& Stamp );

	//## Operation: SerializeWrite%913885121
	//	Serialize in write mode the document information.
	virtual void SerializeWrite( CArchive& ar );

	//## Operation: Serialize%913885094
	// Serialize document information.
	virtual void Serialize( CArchive& ar );

	// Additional Public Declarations
	//## begin ZDDocumentData%3678E27C00F2.public preserve=yes
	//## end ZDDocumentData%3678E27C00F2.public

protected:

	//## Other Operations (specified)
	//## Operation: CalculateFormula%913885107
	// Calculate one formula.
	BOOL CalculateFormula( ZAFormula* pFormula, CWnd* pWnd = NULL, CDC* pDC = NULL );

	//## Operation: OnDrawBinary%940782410
	// Process the draw.
	virtual void OnDrawBinary( CDC* pDC, ZIView* pView );

	// Process the draw.
	virtual void OnDrawExternalBinary( CDC* pDC, ZIView* pView );

	//## Operation: OnDrawForms%940782411
	// Just draw the background picture of a page
	void OnDrawBackgroundPicture( CDC* pDC, ZIView* pView, int iPage );

	// Process the draw.
	virtual void OnDrawForms( CDC*		pDC,
							  ZIView*	pView,
							  BOOL		DrawCalculatedSymbol	= TRUE,
							  BOOL		DrawHiddenObject		= FALSE,
							  BOOL		DrawBoundRectObject		= FALSE,
							  BOOL		DrawCalculatedRefObject	= FALSE,
							  BOOL		DrawTabOrder			= FALSE );

	// Process the draw.
	virtual void OnDrawExternalForms( CDC*		pDC,
									  ZIView*	pView,
									  BOOL		DrawCalculatedSymbol	= TRUE,
									  BOOL		DrawHiddenObject		= FALSE,
									  BOOL		DrawBoundRectObject		= FALSE,
									  BOOL		DrawCalculatedRefObject	= FALSE,
									  BOOL		DrawTabOrder			= FALSE );

	// Process the draw.
	virtual void OnDrawURL( CDC* pDC, ZIView* pView );

	//## Operation: FieldNameExistInObectArray%948540876
	// Run through the fieldname array and find if the object
	// already exists.
	bool FieldNameExistInObectArray( const CString& Fieldname );

//## implementation
private:

	// Additional Implementation Declarations
	//## begin ZDDocumentData%3678E27C00F2.implementation preserve=yes
	BOOL DeletePageObjects( int iPage, BOOL bRedistribute = TRUE );
	BOOL CopyPageObjects( ZDDocumentData* pDocumentDst, int iPage );
	BOOL CheckObjectList();
	//## end ZDDocumentData%3678E27C00F2.implementation

// Data Members for Class Attributes
protected:

	//## Attribute: iCurrentPage%3678E36D0031
	// Track the current page.
	//## begin ZDDocumentData::iCurrentPage%3678E36D0031.attr preserve=no  public: int {U} 
	int m_iCurrentPage;
	//## end ZDDocumentData::iCurrentPage%3678E36D0031.attr

	//## Attribute: tmEndCalculateTime%3678E4F90365
	// The time used to know the elpased time after one
	// calculation.
	//## begin ZDDocumentData::tmEndCalculateTime%3678E4F90365.attr preserve=no  protected: CTime {U} CTime::GetCurrentTime()
	CTime m_tmEndCalculateTime;
	//## end ZDDocumentData::tmEndCalculateTime%3678E4F90365.attr

// Data Members for Class Attributes
private:

	//## begin ZDDocumentData::Stamp%3678F1340014.attr preserve=no  public: ZDStamp {U} 
	ZDStamp m_Stamp;
	//## end ZDDocumentData::Stamp%3678F1340014.attr

	//## Attribute: ObjElements%3678E32D01A1
	// Contains all document elements.
	//## begin ZDDocumentData::ObjElements%3678E32D01A1.attr preserve=no  public: CObList {U} 
	CObList m_ObjElements;
	//## end ZDDocumentData::ObjElements%3678E32D01A1.attr

	//## Attribute: Position%3678E3330005
	// Used to run through the list.
	//## begin ZDDocumentData::Position%3678E3330005.attr preserve=no  private: POSITION {U} 
	POSITION m_Position;
	//## end ZDDocumentData::Position%3678E3330005.attr

	//## begin ZDDocumentData::Schema%3678E34A0275.attr preserve=no  public: ZASchemaManager {U} 
	ZASchemaManager m_Schema;
	//## end ZDDocumentData::Schema%3678E34A0275.attr

	//## Attribute: sCurrentSchema%3678E3580153
	// The name of the current schema
	//## begin ZDDocumentData::sCurrentSchema%3678E3580153.attr preserve=no  public: CString {U} 
	CString m_sCurrentSchema;
	//## end ZDDocumentData::sCurrentSchema%3678E3580153.attr

	//## Attribute: iPageMax%3678E35E0332
	// Has the number of page.
	//## begin ZDDocumentData::iPageMax%3678E35E0332.attr preserve=no  public: int {U} 
	int m_iPageMax;
	//## end ZDDocumentData::iPageMax%3678E35E0332.attr

	//## Attribute: pCurrentEditedObject%3678E4D10386
	// Points to the current object being edited.
	//## begin ZDDocumentData::pCurrentEditedObject%3678E4D10386.attr preserve=no  private: PlanFinObject* {U} 
	PlanFinObject* m_pCurrentEditedObject;
	//## end ZDDocumentData::pCurrentEditedObject%3678E4D10386.attr

	//## Attribute: bFlagElapsedTime%3678E4F400B5
	//## begin ZDDocumentData::bFlagElapsedTime%3678E4F400B5.attr preserve=no  protected: BOOL {U} FALSE
	BOOL m_bFlagElapsedTime;
	//## end ZDDocumentData::bFlagElapsedTime%3678E4F400B5.attr

	//## begin ZDDocumentData::pDocument%3678E63E02F4.attr preserve=no  public: ZDDocument* {U} 
	ZDDocument* m_pDocument;
	//## end ZDDocumentData::pDocument%3678E63E02F4.attr

	//## Attribute: IsVisible%367CD0F30345
	// Defines if the formulaires is visible or not.
	//## begin ZDDocumentData::IsVisible%367CD0F30345.attr preserve=no  public: BOOL {U} TRUE
	BOOL m_IsVisible;
	//## end ZDDocumentData::IsVisible%367CD0F30345.attr

	//## begin ZDDocumentData::FontManager%367FF58803CE.attr preserve=no  public: ZAFontManager {U} 
	ZAFontManager m_FontManager;
	//## end ZDDocumentData::FontManager%367FF58803CE.attr

	//## begin ZDDocumentData::StyleManager%367FF58F02AC.attr preserve=no  public: ZAStyleManager {U} 
	ZAStyleManager m_StyleManager;
	//## end ZDDocumentData::StyleManager%367FF58F02AC.attr

	//## Attribute: ReadOnlyAtRuntime%37CEE52C022A
	// is TRUE if the document is read-only at runtime.
	//## begin ZDDocumentData::ReadOnlyAtRuntime%37CEE52C022A.attr preserve=no  public: BOOL {U} 
	BOOL m_ReadOnlyAtRuntime;
	//## end ZDDocumentData::ReadOnlyAtRuntime%37CEE52C022A.attr

	//## Attribute: pFileBuffer%37F63D5D00EA
	// Point to the file buffer. Only valid when the document
	// data type is equal to BinaryDataType.
	//## begin ZDDocumentData::pFileBuffer%37F63D5D00EA.attr preserve=no  private: ZBFileBuffer* {U} 
	ZBFileBuffer* m_pFileBuffer;
	//## end ZDDocumentData::pFileBuffer%37F63D5D00EA.attr

	//## begin ZDDocumentData::FileBufferTemporaryFile%37F762B9004B.attr preserve=no  public: CString {U} 
	CString m_FileBufferTemporaryFile;
	//## end ZDDocumentData::FileBufferTemporaryFile%37F762B9004B.attr

	//## begin ZDDocumentData::FileLauncher%37F780D50095.attr preserve=no  public: ZUFileLauncher {U} 
	ZUFileLauncher m_FileLauncher;
	//## end ZDDocumentData::FileLauncher%37F780D50095.attr

	//## Attribute: BinaryDrawMessage%381334F90046
	// Contains the message for external documents.
	//## begin ZDDocumentData::BinaryDrawMessage%381334F90046.attr preserve=no  private: CString {U} 
	CString m_BinaryDrawMessage;
	//## end ZDDocumentData::BinaryDrawMessage%381334F90046.attr

	//## begin ZDDocumentData::LastTabOrder%3877A3200079.attr preserve=no  public: double {U} 
	double m_LastTabOrder;
	//## end ZDDocumentData::LastTabOrder%3877A3200079.attr

	//## Attribute: FieldNameArray%38899E6500B0
	// Contains all field names for all document data.
	//## begin ZDDocumentData::FieldNameArray%38899E6500B0.attr preserve=no  private: CStringArray {U} 
	CStringArray m_FieldNameArray;
	//## end ZDDocumentData::FieldNameArray%38899E6500B0.attr

	// Additional Private Declarations
	//## begin ZDDocumentData%3678E27C00F2.private preserve=yes
	//## end ZDDocumentData%3678E27C00F2.private
};

//## begin ZDDocumentData%3678E27C00F2.postscript preserve=yes
//## end ZDDocumentData%3678E27C00F2.postscript

//## Other Operations (inline)
inline CObList& ZDDocumentData::GetObjectList()
{
	//## begin ZDDocumentData::GetObjectList%913885073.body preserve=yes
	return m_ObjElements;
	//## end ZDDocumentData::GetObjectList%913885073.body
}

inline int ZDDocumentData::GetObjectCount()
{
	//## begin ZDDocumentData::GetObjectCount%913885074.body preserve=yes
	return m_ObjElements.GetCount();
	//## end ZDDocumentData::GetObjectCount%913885074.body
}

inline PlanFinObject* ZDDocumentData::GetHead()
{
	//## begin ZDDocumentData::GetHead%913885075.body preserve=yes
	m_Position = m_ObjElements.GetHeadPosition();

	return ( m_Position != NULL ) ? ( (PlanFinObject*)m_ObjElements.GetHead( ) ) : NULL;
	//## end ZDDocumentData::GetHead%913885075.body
}

inline PlanFinObject* ZDDocumentData::GetNext()
{
	//## begin ZDDocumentData::GetNext%913885076.body preserve=yes
	if ( m_Position )
	{
		m_ObjElements.GetNext( m_Position );

		if ( m_Position )
		{
			return( (PlanFinObject*)m_ObjElements.GetAt( m_Position ) );
		}
	}

	return( NULL );
	//## end ZDDocumentData::GetNext%913885076.body
}

inline CString ZDDocumentData::GetCurrentSchema() const
{
	//## begin ZDDocumentData::GetCurrentSchema%913885078.body preserve=yes
	return m_sCurrentSchema;
	//## end ZDDocumentData::GetCurrentSchema%913885078.body
}

inline void ZDDocumentData::SetCurrentSchema( const CString& Name )
{
	//## begin ZDDocumentData::SetCurrentSchema%913885079.body preserve=yes
	m_sCurrentSchema = Name;
	//## end ZDDocumentData::SetCurrentSchema%913885079.body
}

inline int ZDDocumentData::GetMaxPage()
{
	//## begin ZDDocumentData::GetMaxPage%913885083.body preserve=yes
	return m_iPageMax;
	//## end ZDDocumentData::GetMaxPage%913885083.body
}

inline void ZDDocumentData::SetMaxPage( int iPage )
{
	//## begin ZDDocumentData::SetMaxPage%913885084.body preserve=yes
	m_iPageMax = iPage;
	//## end ZDDocumentData::SetMaxPage%913885084.body
}

inline int ZDDocumentData::GetCurrentPage() const
{
	//## begin ZDDocumentData::GetCurrentPage%913885087.body preserve=yes
	return( m_iCurrentPage );
	//## end ZDDocumentData::GetCurrentPage%913885087.body
}

inline void ZDDocumentData::SetCurrentPage( int iPage )
{
	//## begin ZDDocumentData::SetCurrentPage%913885088.body preserve=yes
	m_iCurrentPage = iPage;
	//## end ZDDocumentData::SetCurrentPage%913885088.body
}

inline void ZDDocumentData::SetEditedObject( PlanFinObject* pObj )
{
	//## begin ZDDocumentData::SetEditedObject%913885090.body preserve=yes
	m_pCurrentEditedObject = pObj;;
	//## end ZDDocumentData::SetEditedObject%913885090.body
}

inline PlanFinObject* ZDDocumentData::GetEditedObject( BOOL bCheckPage )
{
	//## begin ZDDocumentData::GetEditedObject%913885091.body preserve=yes
	return m_pCurrentEditedObject;
	//## end ZDDocumentData::GetEditedObject%913885091.body
}

inline void ZDDocumentData::StartCalcTimer()
{
	//## begin ZDDocumentData::StartCalcTimer%917889605.body preserve=yes
	// Start the timer
	// to count the elapsed time
	if( !m_bFlagElapsedTime )
	{
		m_tmEndCalculateTime = CTime::GetCurrentTime();
		m_bFlagElapsedTime = TRUE;
	}
	//## end ZDDocumentData::StartCalcTimer%917889605.body
}

inline void ZDDocumentData::ResetCalcTimer()
{
	//## begin ZDDocumentData::ResetCalcTimer%913885098.body preserve=yes
	// Reset the timer
	m_bFlagElapsedTime = FALSE;
	//## end ZDDocumentData::ResetCalcTimer%913885098.body
}

inline void ZDDocumentData::SchemaListHasChanged()
{
	//## begin ZDDocumentData::SchemaListHasChanged%913885102.body preserve=yes
	AfxGetMainWnd()->SendMessageToDescendants( ID_SCHEMALISTHASCHANGED );
	AfxGetMainWnd()->SendMessageToDescendants( ID_SETDEFAULTSCHEMA, 0, (LPARAM)(const char*)GetCurrentSchema() );
	//## end ZDDocumentData::SchemaListHasChanged%913885102.body
}

inline void ZDDocumentData::ShowDocumentData()
{
	//## begin ZDDocumentData::ShowDocumentData%914146148.body preserve=yes
	m_IsVisible = TRUE;
	//## end ZDDocumentData::ShowDocumentData%914146148.body
}

inline void ZDDocumentData::HideDocumentData()
{
	//## begin ZDDocumentData::HideDocumentData%914146149.body preserve=yes
	m_IsVisible = FALSE;
	//## end ZDDocumentData::HideDocumentData%914146149.body
}

inline BOOL ZDDocumentData::DocumentDataIsVisible()
{
	//## begin ZDDocumentData::DocumentDataIsVisible%914146150.body preserve=yes
	return m_IsVisible;
	//## end ZDDocumentData::DocumentDataIsVisible%914146150.body
}

inline ZDDocumentData* ZDDocumentData::Clone()
{
	//## begin ZDDocumentData::Clone%914146161.body preserve=yes
	ZDDocumentData*	pDocData = new ZDDocumentData( *this );
	return pDocData;
	//## end ZDDocumentData::Clone%914146161.body
}

inline BOOL ZDDocumentData::IsReadOnly() const
{
	//## begin ZDDocumentData::IsReadOnly%936298264.body preserve=yes
	return m_Stamp.IsReadOnly();
	//## end ZDDocumentData::IsReadOnly%936298264.body
}

inline void ZDDocumentData::SetAsReadOnly( BOOL value )
{
	//## begin ZDDocumentData::SetAsReadOnly%936298265.body preserve=yes
	GetStamp().SetAsReadOnly( value );
	//## end ZDDocumentData::SetAsReadOnly%936298265.body
}

inline BOOL ZDDocumentData::IsStandardForm() const
{
	//## begin ZDDocumentData::IsStandardForm%936298266.body preserve=yes
	return m_Stamp.IsStandardForm();
	//## end ZDDocumentData::IsStandardForm%936298266.body
}

inline BOOL ZDDocumentData::IsInternalKeyEqualTo( const CString Key )
{
	//## begin ZDDocumentData::IsInternalKeyEqualTo%936298267.body preserve=yes
	return GetStamp().IsInternalKeyEqualTo( Key );
	//## end ZDDocumentData::IsInternalKeyEqualTo%936298267.body
}

inline BOOL ZDDocumentData::IsReadOnlyAtRuntime()
{
	//## begin ZDDocumentData::IsReadOnlyAtRuntime%936298279.body preserve=yes
	return m_ReadOnlyAtRuntime || IsReadOnly();
	//## end ZDDocumentData::IsReadOnlyAtRuntime%936298279.body
}

inline void ZDDocumentData::SetReadOnlyAtRuntime( BOOL value )
{
	//## begin ZDDocumentData::SetReadOnlyAtRuntime%936298280.body preserve=yes
	m_ReadOnlyAtRuntime = value;
	//## end ZDDocumentData::SetReadOnlyAtRuntime%936298280.body
}

inline ZBFileBuffer* ZDDocumentData::GetFileBufferPointer()
{
	//## begin ZDDocumentData::GetFileBufferPointer%938933081.body preserve=yes
	return m_pFileBuffer;
	//## end ZDDocumentData::GetFileBufferPointer%938933081.body
}

inline BOOL ZDDocumentData::IsFormData() const
{
	return m_Stamp.GetDocumentDataType() == FormDataType;
}

inline BOOL ZDDocumentData::IsBinaryData() const
{
	return m_Stamp.GetDocumentDataType() == BinaryDataType;
}

inline BOOL ZDDocumentData::IsExternalFormData() const
{
	return m_Stamp.GetDocumentDataType() == ExternalFormDataType;
}

inline BOOL ZDDocumentData::IsExternalBinaryData() const
{
	return m_Stamp.GetDocumentDataType() == ExternalBinaryDataType;
}

inline BOOL ZDDocumentData::IsURLData() const
{
	return m_Stamp.GetDocumentDataType() == URLDataType;
}

inline BOOL ZDDocumentData::IsBinaryDataValid() const
{
	//## begin ZDDocumentData::IsBinaryDataValid%938933082.body preserve=yes
	return m_Stamp.GetDocumentDataType() == BinaryDataType && m_pFileBuffer != NULL;
	//## end ZDDocumentData::IsBinaryDataValid%938933082.body
}

inline CStringArray* ZDDocumentData::GetObjectFieldNameArray() const
{
	//## begin ZDDocumentData::GetObjectFieldNameArray%948540870.body preserve=yes
	return (CStringArray*)&m_FieldNameArray;
	//## end ZDDocumentData::GetObjectFieldNameArray%948540870.body
}

//## Get and Set Operations for Class Attributes (inline)

inline ZDStamp& ZDDocumentData::GetStamp()
{
	//## begin ZDDocumentData::GetStamp%3678F1340014.get preserve=no
	return m_Stamp;
	//## end ZDDocumentData::GetStamp%3678F1340014.get
}

inline ZASchemaManager& ZDDocumentData::GetSchema()
{
	//## begin ZDDocumentData::GetSchema%3678E34A0275.get preserve=no
	return m_Schema;
	//## end ZDDocumentData::GetSchema%3678E34A0275.get
}

inline ZDDocument* ZDDocumentData::GetpDocument()
{
	//## begin ZDDocumentData::GetpDocument%3678E63E02F4.get preserve=no
	return m_pDocument;
	//## end ZDDocumentData::GetpDocument%3678E63E02F4.get
}

inline void ZDDocumentData::SetpDocument( ZDDocument* value )
{
	//## begin ZDDocumentData::SetpDocument%3678E63E02F4.set preserve=no
	m_pDocument = value;
	//## end ZDDocumentData::SetpDocument%3678E63E02F4.set
}

inline ZAFontManager& ZDDocumentData::GetFontManager()
{
	//## begin ZDDocumentData::GetFontManager%367FF58803CE.get preserve=no
	return m_FontManager;
	//## end ZDDocumentData::GetFontManager%367FF58803CE.get
}

inline ZAStyleManager& ZDDocumentData::GetStyleManager()
{
	//## begin ZDDocumentData::GetStyleManager%367FF58F02AC.get preserve=no
	return m_StyleManager;
	//## end ZDDocumentData::GetStyleManager%367FF58F02AC.get
}

inline const CString& ZDDocumentData::GetFileBufferTemporaryFile() const
{
	//## begin ZDDocumentData::GetFileBufferTemporaryFile%37F762B9004B.get preserve=no
	return m_FileBufferTemporaryFile;
	//## end ZDDocumentData::GetFileBufferTemporaryFile%37F762B9004B.get
}

inline ZUFileLauncher& ZDDocumentData::GetFileLauncher()
{
	//## begin ZDDocumentData::GetFileLauncher%37F780D50095.get preserve=no
	return m_FileLauncher;
	//## end ZDDocumentData::GetFileLauncher%37F780D50095.get
}

inline const double ZDDocumentData::GetLastTabOrder() const
{
	//## begin ZDDocumentData::GetLastTabOrder%3877A3200079.get preserve=no
	return m_LastTabOrder;
	//## end ZDDocumentData::GetLastTabOrder%3877A3200079.get
}

inline void ZDDocumentData::SetLastTabOrder( double value )
{
	//## begin ZDDocumentData::SetLastTabOrder%3877A3200079.set preserve=no
	m_LastTabOrder = value;
	//## end ZDDocumentData::SetLastTabOrder%3877A3200079.set
}

//## begin module%3678E2A3038D.epilog preserve=yes
//## end module%3678E2A3038D.epilog

#endif