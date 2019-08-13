//## begin module%37E7FBA501A6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%37E7FBA501A6.cm

//## begin module%37E7FBA501A6.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%37E7FBA501A6.cp

//## Module: GFDataF%37E7FBA501A6; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\GFDataF.h

#ifndef GFDataF_h
#define GFDataF_h 1

//## begin module%37E7FBA501A6.additionalIncludes preserve=no
//## end module%37E7FBA501A6.additionalIncludes

//## begin module%37E7FBA501A6.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%37E7FBA501A6.includes

// Export
#include "PSS_Export.h"
//## begin module%37E7FBA501A6.declarations preserve=no
//## end module%37E7FBA501A6.declarations

//## begin module%37E7FBA501A6.additionalDeclarations preserve=yes
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

//## end module%37E7FBA501A6.additionalDeclarations


//## Class: ZUFieldDefinitionDataFeed%37E7FA7C02FD
//    Data feed for field definition.
//## Category: ZUtil library::Data feed \rclasses%36F7CCFF024A
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUFieldDefinitionDataFeed : public PSS_Export
{
  //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.initialDeclarations preserve=yes
  //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZUFieldDefinitionDataFeed%937950157
      //    Constructs an export class with the filename and the
      //    field definition manager.
      ZUFieldDefinitionDataFeed (CString Filename = "", PSS_FieldRepository* pFieldRepository = NULL, ZAObjectDefinition* pObjectDefinition = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: ZUFieldDefinitionDataFeed%938030360
      //    Constructs an export class with the filename and the
      //    field definition manager.
      ZUFieldDefinitionDataFeed (CString Filename, PSS_FieldRepository* pFieldRepository, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

    //## Destructor (generated)
      ~ZUFieldDefinitionDataFeed();


    //## Other Operations (specified)
      //## Operation: GetExportedLine%937950158
      //    Build the export line and return it.
      virtual CString GetExportedLine (CObject* pObj);

      //## Operation: ProcessLine%937950159
      //    Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: GetHeaderLine%937950160
      //    This function builds the header line.
      virtual CString GetHeaderLine ();

      //## Operation: Create%937950163
      //    Create the export class.
      virtual void Create (CString Filename, PSS_FieldRepository* pFieldRepository = NULL, ZAObjectDefinition* pObjectDefinition = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: Create%938030361
      //    Create the export class.
      virtual void Create (CString Filename, PSS_FieldRepository* pFieldRepository = NULL, BOOL GenerateHeader = FALSE, ESynchronizationSeparatorType SeparatorType = E_SS_Automatic, CString Schema = g_OriginalSchema, int PropagationMode = g_LocatePageOnly, BOOL EmptyWhenZero = FALSE, PSS_StatusBar* pStatusBar = NULL);

      //## Operation: ForecastedTotalObject%937950164
      //    This function should return the forecasted total object.
      virtual double ForecastedTotalObject ();

      //## Operation: DoExportLoop%937950165
      //    This function do the loop for export.
      virtual BOOL DoExportLoop ();

      //## Operation: PreImport%937950166
      //    This function imports the file to the document.
      virtual BOOL PreImport ();

      //## Operation: PostImport%938372467
      //    This function imports the file to the document.
      virtual BOOL PostImport ();

    // Additional Public Declarations
      //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.public preserve=yes
      //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.public

  protected:
    // Additional Protected Declarations
      //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.protected preserve=yes
      //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.protected

  private:
    //## Constructors (generated)
      ZUFieldDefinitionDataFeed(const ZUFieldDefinitionDataFeed &right);

    //## Assignment Operation (generated)
      const ZUFieldDefinitionDataFeed & operator=(const ZUFieldDefinitionDataFeed &right);


    //## Other Operations (specified)
      //## Operation: DeleteLineArray%938372466
      void DeleteLineArray ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: pSourceFieldRepository%37E7FB280015
      //    Points to the field repository.
      const PSS_FieldRepository* GetpSourceFieldRepository () const;
      void SetpSourceFieldRepository (PSS_FieldRepository* value);

      //## Attribute: pImportedFieldRepository%37F91127027B
      //    Points to the field repository.
      const PSS_FieldRepository* GetpImportedFieldRepository () const;
      void SetpImportedFieldRepository (PSS_FieldRepository* value);

    // Data Members for Class Attributes

      //## Attribute: LineArray%37E934EE038F
      //    Contains all imported lines.
      //## begin ZUFieldDefinitionDataFeed::LineArray%37E934EE038F.attr preserve=no  private: CObArray {U} 
      CObArray m_LineArray;
      //## end ZUFieldDefinitionDataFeed::LineArray%37E934EE038F.attr

      //## Attribute: pObjectDefinition%37E9361102C5
      //    Containe the object to export.
      //## begin ZUFieldDefinitionDataFeed::pObjectDefinition%37E9361102C5.attr preserve=no  private: ZAObjectDefinition* {U} 
      ZAObjectDefinition* m_pObjectDefinition;
      //## end ZUFieldDefinitionDataFeed::pObjectDefinition%37E9361102C5.attr

    // Additional Private Declarations
      //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.private preserve=yes
      class    FieldExport
      {
        public:
          FieldExport( const CString Key = "", const CString Value = "");
          ~FieldExport();
          CString    m_Key;
          CString    m_Value;
      };
      //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.private
  private:  //## implementation
    // Data Members for Class Attributes

      //## begin ZUFieldDefinitionDataFeed::pSourceFieldRepository%37E7FB280015.attr preserve=no  private: ZBFieldRepository* {U} 
      PSS_FieldRepository* m_pSourceFieldRepository;
      //## end ZUFieldDefinitionDataFeed::pSourceFieldRepository%37E7FB280015.attr

      //## begin ZUFieldDefinitionDataFeed::pImportedFieldRepository%37F91127027B.attr preserve=no  private: ZBFieldRepository* {U} 
      PSS_FieldRepository* m_pImportedFieldRepository;
      //## end ZUFieldDefinitionDataFeed::pImportedFieldRepository%37F91127027B.attr

    // Additional Implementation Declarations
      //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.implementation preserve=yes
      //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.implementation

};

//## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.postscript preserve=yes
//## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.postscript

// Class ZUFieldDefinitionDataFeed 


//## Other Operations (inline)
inline void ZUFieldDefinitionDataFeed::Create (CString Filename, PSS_FieldRepository* pFieldRepository, ZAObjectDefinition* pObjectDefinition, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, PSS_StatusBar* pStatusBar)
{
  //## begin ZUFieldDefinitionDataFeed::Create%937950163.body preserve=yes
      m_pSourceFieldRepository = pFieldRepository;
    m_pObjectDefinition = pObjectDefinition;
    PSS_Export::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUFieldDefinitionDataFeed::Create%937950163.body
}

inline void ZUFieldDefinitionDataFeed::Create (CString Filename, PSS_FieldRepository* pFieldRepository, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, PSS_StatusBar* pStatusBar)
{
  //## begin ZUFieldDefinitionDataFeed::Create%938030361.body preserve=yes
      m_pSourceFieldRepository = pFieldRepository;
    m_pObjectDefinition = NULL;
    PSS_Export::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUFieldDefinitionDataFeed::Create%938030361.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const PSS_FieldRepository* ZUFieldDefinitionDataFeed::GetpSourceFieldRepository () const
{
  //## begin ZUFieldDefinitionDataFeed::GetpSourceFieldRepository%37E7FB280015.get preserve=no
  return m_pSourceFieldRepository;
  //## end ZUFieldDefinitionDataFeed::GetpSourceFieldRepository%37E7FB280015.get
}

inline void ZUFieldDefinitionDataFeed::SetpSourceFieldRepository (PSS_FieldRepository* value)
{
  //## begin ZUFieldDefinitionDataFeed::SetpSourceFieldRepository%37E7FB280015.set preserve=no
  m_pSourceFieldRepository = value;
  //## end ZUFieldDefinitionDataFeed::SetpSourceFieldRepository%37E7FB280015.set
}

inline const PSS_FieldRepository* ZUFieldDefinitionDataFeed::GetpImportedFieldRepository () const
{
  //## begin ZUFieldDefinitionDataFeed::GetpImportedFieldRepository%37F91127027B.get preserve=no
  return m_pImportedFieldRepository;
  //## end ZUFieldDefinitionDataFeed::GetpImportedFieldRepository%37F91127027B.get
}

inline void ZUFieldDefinitionDataFeed::SetpImportedFieldRepository (PSS_FieldRepository* value)
{
  //## begin ZUFieldDefinitionDataFeed::SetpImportedFieldRepository%37F91127027B.set preserve=no
  m_pImportedFieldRepository = value;
  //## end ZUFieldDefinitionDataFeed::SetpImportedFieldRepository%37F91127027B.set
}

//## begin module%37E7FBA501A6.epilog preserve=yes
//## end module%37E7FBA501A6.epilog


#endif


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZUFieldDefinitionDataFeed::GetImportedFieldRepository%939069931.body preserve=no
    return m_pImportedFieldRepository;
//## end ZUFieldDefinitionDataFeed::GetImportedFieldRepository%939069931.body

#endif
