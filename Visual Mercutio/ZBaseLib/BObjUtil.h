//## begin module%36CE9AB102B0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36CE9AB102B0.cm

//## begin module%36CE9AB102B0.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36CE9AB102B0.cp

//## Module: BObjUtil%36CE9AB102B0; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\BObjUtil.h

#ifndef BObjUtil_h
#define BObjUtil_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

////////////////////////////////////////////////////////////////
// Forward class declaration
class PlanFinObject;

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZBObjectUtility 
{
public:
	
	ZBObjectUtility();
	~ZBObjectUtility();

	// Return the description for this field.
	static const CString GetFieldTypeDescription ( PlanFinObject* pObj );

	// Return the description for this field.
	static const CString GetFieldTypeDescription ( const CString ClassName );

	// Return the string representing the class.
	static const CString GetClassName ( PlanFinObject* pObj );

	// Returns the bitmap of the class name.
	static UINT GetBitmapClass ( const CString className );

	//## Operation: ConstructObject%919498961
	// Construct a specific object by passing the class name.
	static PlanFinObject* ConstructObject ( const CString& sClassName );

	//## Operation: GetClassNameArray%919592604
	static const CStringArray& GetClassNameArray ();

	//## Operation: GetEditionClassNameArray%919592605
	static const CStringArray& GetEditionClassNameArray ();

	//## Operation: InitializeDefinition%937851058
	// Initialize all definitions.
	static BOOL InitializeDefinition ( const CString IniFile );

	//## Operation: LoadFieldDefinition%937851059
	static CString LoadFieldDefinition ( const CString IniFile, const CString FieldKey );

	//## Operation: GetClassNameID%938242424
	// Return the class id.
	static size_t GetClassNameID ( PlanFinObject* pObj );

	// JMR-MODIF - Le 23 août 2005 - Ajout de la fonction Release.
	static void Release();

	// Additional Public Declarations
	//## begin ZBObjectUtility%36CE993103DA.public preserve=yes
	//## end ZBObjectUtility%36CE993103DA.public

protected:

	//## Other Operations (specified)
	//## Operation: GetFieldTypeDescriptionIniFile%919498962
	// Retreive the general description of the field.
	//## Semantics:
	// Read from the ini file the field explanation
	// the section in the ini file is cpKey
	static const CString GetFieldTypeDescriptionIniFile ( const char* cpKey );

	// Additional Protected Declarations
	//## begin ZBObjectUtility%36CE993103DA.protected preserve=yes
	//## end ZBObjectUtility%36CE993103DA.protected

private:
	
	//## Constructors (generated)
	ZBObjectUtility( const ZBObjectUtility &right );

	//## Assignment Operation (generated)
	const ZBObjectUtility & operator=( const ZBObjectUtility &right );

	//## Other Operations (specified)
	//## Operation: LoadResource%919592602
	// Load the resource. Because the resource cannot be loaded
	// at the class construction, do it later.
	static void LoadResource ();

	//## Operation: ResourceNotLoaded%919592603
	// Tests if the resources have not been yet loaded.
	static bool ResourceNotLoaded ();

	// Data Members for Class Attributes

	//## Attribute: ClassNameArray%36CE9C0901CE
	// Contains all class name.
	//## begin ZBObjectUtility::ClassNameArray%36CE9C0901CE.attr preserve=no  public: static CStringArray {V}
	static CStringArray m_ClassNameArray;
	//## end ZBObjectUtility::ClassNameArray%36CE9C0901CE.attr

	//## Attribute: EditionClassNameArray%36CE9C0E0121
	// Contains all class name.
	//## begin ZBObjectUtility::EditionClassNameArray%36CE9C0E0121.attr preserve=no  public: static CStringArray {V} 
	static CStringArray m_EditionClassNameArray;
	//## end ZBObjectUtility::EditionClassNameArray%36CE9C0E0121.attr

	//## Attribute: FieldTypeDescriptionArray%37E67C5B0370
	// Contains the object array field type description.
	//## begin ZBObjectUtility::FieldTypeDescriptionArray%37E67C5B0370.attr preserve=no  private: static CObArray {V} 
	static CObArray m_FieldTypeDescriptionArray;
	//## end ZBObjectUtility::FieldTypeDescriptionArray%37E67C5B0370.attr

	// Additional Private Declarations
	//## begin ZBObjectUtility%36CE993103DA.private preserve=yes
	//## end ZBObjectUtility%36CE993103DA.private

private:  //## implementation
	
	// Additional Implementation Declarations
	//## begin ZBObjectUtility%36CE993103DA.implementation preserve=yes
	static const	UINT	ClassResourceIDArrary[21];
	static const	UINT	EditionClassResourceIDArrary[17];
	static const	UINT	ClassResourceBitmapIDArrary[18];

	class ObjectDefinition
	{
		public:
			ObjectDefinition( const CString Key, const CString Description );
			~ObjectDefinition();

		public:
			CString	m_Key;
			CString	m_Description;
	};
	//## end ZBObjectUtility%36CE993103DA.implementation
};

//## begin ZBObjectUtility%36CE993103DA.postscript preserve=yes
//## end ZBObjectUtility%36CE993103DA.postscript

// Class ZBObjectUtility 

//## Other Operations (inline)
inline bool ZBObjectUtility::ResourceNotLoaded ()
{
	//## begin ZBObjectUtility::ResourceNotLoaded%919592603.body preserve=yes
	return ( m_ClassNameArray.GetSize() <= 0 ) ? true : false;
	//## end ZBObjectUtility::ResourceNotLoaded%919592603.body
}

inline const CStringArray& ZBObjectUtility::GetClassNameArray ()
{
	//## begin ZBObjectUtility::GetClassNameArray%919592604.body preserve=yes
	// First, test if the resource have been loaded
	if ( ResourceNotLoaded() == true )
		LoadResource();

	return m_ClassNameArray;
	//## end ZBObjectUtility::GetClassNameArray%919592604.body
}

inline const CStringArray& ZBObjectUtility::GetEditionClassNameArray ()
{
	//## begin ZBObjectUtility::GetEditionClassNameArray%919592605.body preserve=yes
	// First, test if the resource have been loaded
	if ( ResourceNotLoaded() == true )
		LoadResource();

	return m_EditionClassNameArray;
	//## end ZBObjectUtility::GetEditionClassNameArray%919592605.body
}

//## begin module%36CE9AB102B0.epilog preserve=yes
//## end module%36CE9AB102B0.epilog
#endif