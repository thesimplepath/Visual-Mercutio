//## begin module%36500BE50072.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36500BE50072.cm

//## begin module%36500BE50072.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%36500BE50072.cp

//## Module: ExpRT%36500BE50072; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ExpRT.h

#ifndef ExpRT_h
#define ExpRT_h 1

//## begin module%36500BE50072.additionalIncludes preserve=no
//## end module%36500BE50072.additionalIncludes

//## begin module%36500BE50072.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

class ZDDocument;
//## end module%36500BE50072.includes

// Export
#include "Export.h"
//## begin module%36500BE50072.declarations preserve=no
//## end module%36500BE50072.declarations

//## begin module%36500BE50072.additionalDeclarations preserve=yes
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
//## end module%36500BE50072.additionalDeclarations


//## Class: ZUDocumentExport%36500BAE01A9
//    Export and Import ZDDocument information.
//## Category: ZBaseLib::Data Feed export/import classes%37EB8FB00040
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUDocumentExport : public ZUExport  //## Inherits: <unnamed>%36500BAE01AA
{
  //## begin ZUDocumentExport%36500BAE01A9.initialDeclarations preserve=yes
  //## end ZUDocumentExport%36500BAE01A9.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZUDocumentExport%911215686
      //    Constructs an export class with the filename and the
      //    document pointer
      ZUDocumentExport (CString Filename = "", ZDDocument* pDoc = NULL, BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

    //## Destructor (generated)
      ~ZUDocumentExport();


    //## Other Operations (specified)
      //## Operation: GetExportedLine%911215687
      //    Build the export line and return it.
      virtual CString GetExportedLine (CObject* pObj);

      //## Operation: IsExportedField%911215688
      //    Tests if the field is to be exported.
      virtual BOOL IsExportedField (CObject* pObj) const;

      //## Operation: ProcessLine%911215689
      //    Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: GetHeaderLine%911215690
      //    This function builds the header line.
      virtual CString GetHeaderLine ();

      //## Operation: Create%922203343
      //    Create the export class.
      virtual void Create (CString Filename, ZDDocument* pDoc, BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

      //## Operation: Import%922203344
      //    This function imports the file to the document.
      virtual BOOL Import ();

      //## Operation: Export%922203345
      //    This function exports the records to a file.
      virtual BOOL Export ();

      //## Operation: ExportAdditionalInfo%922203346
      virtual BOOL ExportAdditionalInfo ();

      //## Operation: ImportAdditionalInfo%922203347
      virtual BOOL ImportAdditionalInfo ();

      //## Operation: PreImport%922203360
      //    This function imports the file to the document.
      virtual BOOL PreImport ();

      //## Operation: PostImport%922203361
      //    This function imports the file to the document.
      virtual BOOL PostImport ();

      //## Operation: ForecastedTotalObject%922203366
      //    This function should return the forecasted total object.
      virtual double ForecastedTotalObject ();

      //## Operation: DoExportLoop%922203368
      //    This function do the loop for export.
      virtual BOOL DoExportLoop ();

    // Additional Public Declarations
      //## begin ZUDocumentExport%36500BAE01A9.public preserve=yes
      //## end ZUDocumentExport%36500BAE01A9.public

  protected:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ObjectCounter%36F7B9160291
      //    This object counter is automatically incremented by the
      //    export function for each object.
      const int GetObjectCounter () const;

    // Data Members for Class Attributes

      //## Attribute: pDoc%36F7B5B203B6
      //    The pointer to the document.
      //## begin ZUDocumentExport::pDoc%36F7B5B203B6.attr preserve=no  protected: ZDDocument* {U} 
      ZDDocument* m_pDoc;
      //## end ZUDocumentExport::pDoc%36F7B5B203B6.attr

      //## begin ZUDocumentExport::ObjectCounter%36F7B9160291.attr preserve=no  protected: int {U} 
      int m_ObjectCounter;
      //## end ZUDocumentExport::ObjectCounter%36F7B9160291.attr

    // Additional Protected Declarations
      //## begin ZUDocumentExport%36500BAE01A9.protected preserve=yes
      //## end ZUDocumentExport%36500BAE01A9.protected

  private:
    //## Constructors (generated)
      ZUDocumentExport(const ZUDocumentExport &right);

    //## Assignment Operation (generated)
      const ZUDocumentExport & operator=(const ZUDocumentExport &right);

    // Data Members for Class Attributes

      //## Attribute: PreviousSchema%36F7C4660386
      //## begin ZUDocumentExport::PreviousSchema%36F7C4660386.attr preserve=no  public: CString {U} 
      CString m_PreviousSchema;
      //## end ZUDocumentExport::PreviousSchema%36F7C4660386.attr

    // Additional Private Declarations
      //## begin ZUDocumentExport%36500BAE01A9.private preserve=yes
      //## end ZUDocumentExport%36500BAE01A9.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUDocumentExport%36500BAE01A9.implementation preserve=yes
      //## end ZUDocumentExport%36500BAE01A9.implementation

};

//## begin ZUDocumentExport%36500BAE01A9.postscript preserve=yes
//## end ZUDocumentExport%36500BAE01A9.postscript

// Class ZUDocumentExport 


//## Other Operations (inline)
inline void ZUDocumentExport::Create (CString Filename, ZDDocument* pDoc, BOOL GenerateHeader, SynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
{
  //## begin ZUDocumentExport::Create%922203343.body preserve=yes
      m_pDoc = pDoc;
    ZUExport::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUDocumentExport::Create%922203343.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const int ZUDocumentExport::GetObjectCounter () const
{
  //## begin ZUDocumentExport::GetObjectCounter%36F7B9160291.get preserve=no
  return m_ObjectCounter;
  //## end ZUDocumentExport::GetObjectCounter%36F7B9160291.get
}

//## begin module%36500BE50072.epilog preserve=yes
//## end module%36500BE50072.epilog


#endif
