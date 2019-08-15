//## begin module%382125B00190.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%382125B00190.cm

//## begin module%382125B00190.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%382125B00190.cp

//## Module: GFValueF%382125B00190; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\GFValueF.h

#ifndef GFValueF_h
#define GFValueF_h 1

//## begin module%382125B00190.additionalIncludes preserve=no
//## end module%382125B00190.additionalIncludes

//## begin module%382125B00190.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%382125B00190.includes

// Export
#include "PSS_Export.h"
//## begin module%382125B00190.declarations preserve=no
//## end module%382125B00190.declarations

//## begin module%382125B00190.additionalDeclarations preserve=yes
// FieldRep
#include "PSS_FieldRepository.h"

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

//## end module%382125B00190.additionalDeclarations


//## Class: ZUFieldValueDataFeed%38212538024B
//    Data feed for field values only.
//## Category: ZUtil library::Data feed \rclasses%36F7CCFF024A
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUFieldValueDataFeed : public PSS_Export
{
  //## begin ZUFieldValueDataFeed%38212538024B.initialDeclarations preserve=yes
  //## end ZUFieldValueDataFeed%38212538024B.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZUFieldValueDataFeed%941696498
      //    Constructs an export class with the filename and the
      //    field definition manager.
      ZUFieldValueDataFeed (CString Filename = "", PSS_FieldRepository* pFieldRepository = NULL, PSS_FieldObjectDefinition* pObjectDefinition = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: ZUFieldValueDataFeed%941696510
      //    Constructs an import class with the filename and a
      //    string array.
      ZUFieldValueDataFeed (CString Filename, CStringArray* pValueArray, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

    //## Destructor (generated)
      ~ZUFieldValueDataFeed();


    //## Other Operations (specified)
      //## Operation: GetExportedLine%941696500
      //    Build the export line and return it.
      virtual CString GetExportedLine (CObject* pObj);

      //## Operation: ProcessLine%941696501
      //    Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: GetHeaderLine%941696502
      //    This function builds the header line.
      virtual CString GetHeaderLine ();

      //## Operation: Create%941696503
      //    Create the export class.
      virtual void Create (CString Filename, PSS_FieldRepository* pFieldRepository = NULL, PSS_FieldObjectDefinition* pObjectDefinition = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: Create%941696511
      //    Create the export class.
      virtual void Create (CString Filename, CStringArray* pValueArray = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: ForecastedTotalObject%941696505
      //    This function should return the forecasted total object.
      virtual double ForecastedTotalObject ();

      //## Operation: DoExportLoop%941696506
      //    This function do the loop for export.
      virtual BOOL DoExportLoop ();

    // Additional Public Declarations
      //## begin ZUFieldValueDataFeed%38212538024B.public preserve=yes
      //## end ZUFieldValueDataFeed%38212538024B.public

  protected:
    // Additional Protected Declarations
      //## begin ZUFieldValueDataFeed%38212538024B.protected preserve=yes
      //## end ZUFieldValueDataFeed%38212538024B.protected

  private:
    //## Constructors (generated)
      ZUFieldValueDataFeed(const ZUFieldValueDataFeed &right);

    //## Assignment Operation (generated)
      const ZUFieldValueDataFeed & operator=(const ZUFieldValueDataFeed &right);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: pSourceFieldRepository%382129F7011C
      //    Points to the field repository.
      const PSS_FieldRepository* GetpSourceFieldRepository () const;
      void SetpSourceFieldRepository (PSS_FieldRepository* value);

    // Data Members for Class Attributes

      //## Attribute: pObjectDefinition%38212538027F
      //    Containe the object to export.
      //## begin ZUFieldValueDataFeed::pObjectDefinition%38212538027F.attr preserve=no  private: ZAObjectDefinition* {U} 
      PSS_FieldObjectDefinition* m_pObjectDefinition;
      //## end ZUFieldValueDataFeed::pObjectDefinition%38212538027F.attr

      //## Attribute: pValueArray%3821408B014F
      //    The value array that will contain values imported.
      //## begin ZUFieldValueDataFeed::pValueArray%3821408B014F.attr preserve=no  private: CStringArray* {U} 
      CStringArray* m_pValueArray;
      //## end ZUFieldValueDataFeed::pValueArray%3821408B014F.attr

    // Additional Private Declarations
      //## begin ZUFieldValueDataFeed%38212538024B.private preserve=yes
      //## end ZUFieldValueDataFeed%38212538024B.private

  private:  //## implementation
    // Data Members for Class Attributes

      //## begin ZUFieldValueDataFeed::pSourceFieldRepository%382129F7011C.attr preserve=no  private: ZBFieldRepository* {U} 
      PSS_FieldRepository* m_pSourceFieldRepository;
      //## end ZUFieldValueDataFeed::pSourceFieldRepository%382129F7011C.attr

    // Additional Implementation Declarations
      //## begin ZUFieldValueDataFeed%38212538024B.implementation preserve=yes
      //## end ZUFieldValueDataFeed%38212538024B.implementation

};

//## begin ZUFieldValueDataFeed%38212538024B.postscript preserve=yes
//## end ZUFieldValueDataFeed%38212538024B.postscript

// Class ZUFieldValueDataFeed 


//## Other Operations (inline)
inline void ZUFieldValueDataFeed::Create (CString Filename, PSS_FieldRepository* pFieldRepository, PSS_FieldObjectDefinition* pObjectDefinition, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, PSS_StatusBar* pStatusBar)
{
  //## begin ZUFieldValueDataFeed::Create%941696503.body preserve=yes
    m_pSourceFieldRepository = pFieldRepository;
    m_pObjectDefinition = pObjectDefinition;
    PSS_Export::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUFieldValueDataFeed::Create%941696503.body
}

inline void ZUFieldValueDataFeed::Create (CString Filename, CStringArray* pValueArray, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, PSS_StatusBar* pStatusBar)
{
  //## begin ZUFieldValueDataFeed::Create%941696511.body preserve=yes
    m_pValueArray = pValueArray;
    PSS_Export::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUFieldValueDataFeed::Create%941696511.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const PSS_FieldRepository* ZUFieldValueDataFeed::GetpSourceFieldRepository () const
{
  //## begin ZUFieldValueDataFeed::GetpSourceFieldRepository%382129F7011C.get preserve=no
  return m_pSourceFieldRepository;
  //## end ZUFieldValueDataFeed::GetpSourceFieldRepository%382129F7011C.get
}

inline void ZUFieldValueDataFeed::SetpSourceFieldRepository (PSS_FieldRepository* value)
{
  //## begin ZUFieldValueDataFeed::SetpSourceFieldRepository%382129F7011C.set preserve=no
  m_pSourceFieldRepository = value;
  //## end ZUFieldValueDataFeed::SetpSourceFieldRepository%382129F7011C.set
}

//## begin module%382125B00190.epilog preserve=yes
//## end module%382125B00190.epilog


#endif
