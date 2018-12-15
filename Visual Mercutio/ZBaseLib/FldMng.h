//## begin module%363DC9F601E6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%363DC9F601E6.cm

//## begin module%363DC9F601E6.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%363DC9F601E6.cp

//## Module: FldMng%363DC9F601E6; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldMng.h

#ifndef FldMng_h
#define FldMng_h 1

//## begin module%363DC9F601E6.additionalIncludes preserve=no
//## end module%363DC9F601E6.additionalIncludes

//## begin module%363DC9F601E6.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363DC9F601E6.includes

// FldDesc
#include "FldDesc.h"
// HistFld
#include "HistFld.h"
// Mfc
#include "Mfc.h"
//## begin module%363DC9F601E6.declarations preserve=no
//## end module%363DC9F601E6.declarations

//## begin module%363DC9F601E6.additionalDeclarations preserve=yes
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
//## end module%363DC9F601E6.additionalDeclarations

//## Class: ZAGlobalFieldManager%363DC8B30079
//    Manage the global field container for the document.
//## Category: ZBaseLib::History Field manager%36347B0E0308
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%363DC8B3007B;ZAHistoryField { -> }
//## Uses: <unnamed>%363DC92D0038;ZAObjectDefinition { -> }

class AFX_EXT_CLASS ZAGlobalFieldManager : public CObject  //## Inherits: <unnamed>%363DC8B3007A
{
protected:

    // Additional Protected Declarations
    //## begin ZAGlobalFieldManager%363DC8B30079.protected preserve=yes
    DECLARE_SERIAL( ZAGlobalFieldManager )
    //## end ZAGlobalFieldManager%363DC8B30079.protected

//## begin ZAGlobalFieldManager%363DC8B30079.initialDeclarations preserve=yes
public:

    // Inherited feature
    typedef CObject inherited;
    //## end ZAGlobalFieldManager%363DC8B30079.initialDeclarations

public:
    
    //## Constructors (generated)
    ZAGlobalFieldManager();

    //## Destructor (generated)
    ~ZAGlobalFieldManager();

    //## Other Operations (specified)
    //## Operation: Serialize%910019974
    // Serialization function required for MFC mecanism.
    virtual void Serialize ( CArchive& ar );

    //## Operation: GetCount%910019975
    // Return the number of elements of the Global field
    // manager.
    size_t GetCount ();

    //## Operation: AddField%910019976
    // Add a new field.
    // Returns the index of the added field.
    int AddField ( ZAObjectDefinition* Field );

    //## Operation: DeleteField%910019977
    // Delete a field.
    BOOL DeleteField ( const CString& Name );

    //## Operation: DeleteAllField%919498957
    // Delete all field.
    BOOL DeleteAllField ();

    //## Operation: FindField%910019978
    // Find if a field exists.
    ZAObjectDefinition* FindField ( const CString& Name );

    //## Operation: GetAt%910019979
    // Get the object at a specific location.
    ZAObjectDefinition* GetAt ( int Index );

    //## Operation: GetDescription%910019980
    // Get the description of a field.
    CString GetDescription ( const CString& Name );

    //## Operation: GetClassName%910019981
    // Get the class name of a field.
    CString GetClassName ( const CString& Name );

    //## Operation: GetFieldNameArray%910019982
    // Returns the fieldname array of all fields contained in
    // the manager.
    const CStringArray& GetFieldNameArray ();

    //## Operation: CopyFieldDefinition%910104707
    // Copy the field definition of the ObjectDefinition to the
    // PlanfinObject.
    void CopyFieldDefinition ( const CString Name, PlanFinObject* pObj, ZDDocument* pDoc );

    // Additional Public Declarations
    //## begin ZAGlobalFieldManager%363DC8B30079.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

    //## end ZAGlobalFieldManager%363DC8B30079.public

private:
    
    //## Constructors (generated)
    ZAGlobalFieldManager( const ZAGlobalFieldManager &right );
    
    //## Assignment Operation (generated)
    const ZAGlobalFieldManager & operator=( const ZAGlobalFieldManager &right );

    //## Other Operations (specified)
    //## Operation: FreeList%910019983
    // remove all the fields.
    void FreeList ();

private:    //## Data members

    // Data Members for Class Attributes

    //## Attribute: GlobalFieldArray%363DC8B3008C
    // Contains all fields' definition.
    //## begin ZAGlobalFieldManager::GlobalFieldArray%363DC8B3008C.attr preserve=no  public: CObArray {U} 
    CObArray m_GlobalFieldArray;
    //## end ZAGlobalFieldManager::GlobalFieldArray%363DC8B3008C.attr

    //## Attribute: FieldNameArray%363DD30E00F3
    // A field name array used to store the field names.
    //## begin ZAGlobalFieldManager::FieldNameArray%363DD30E00F3.attr preserve=no  public: CStringArray {U} 
    CStringArray m_FieldNameArray;
    //## end ZAGlobalFieldManager::FieldNameArray%363DD30E00F3.attr

    // Additional Private Declarations
    //## begin ZAGlobalFieldManager%363DC8B30079.private preserve=yes
    //## end ZAGlobalFieldManager%363DC8B30079.private

private:    //## implementation
    
    // Additional Implementation Declarations
    //## begin ZAGlobalFieldManager%363DC8B30079.implementation preserve=yes
    //## end ZAGlobalFieldManager%363DC8B30079.implementation
};

//## begin ZAGlobalFieldManager%363DC8B30079.postscript preserve=yes
//## end ZAGlobalFieldManager%363DC8B30079.postscript

// Class ZAGlobalFieldManager 

//## Other Operations (inline)
inline size_t ZAGlobalFieldManager::GetCount ()
{
    //## begin ZAGlobalFieldManager::GetCount%910019975.body preserve=yes
    return m_GlobalFieldArray.GetSize();
    //## end ZAGlobalFieldManager::GetCount%910019975.body
}

//## begin module%363DC9F601E6.epilog preserve=yes
//## end module%363DC9F601E6.epilog

#endif

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZAGlobalFieldManager%363DC8B30079.preface preserve=no
//## end ZAGlobalFieldManager%363DC8B30079.preface

#endif