//## begin module%36F7BD3602A4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36F7BD3602A4.cm

//## begin module%36F7BD3602A4.cp preserve=no
//## end module%36F7BD3602A4.cp

//## Module: ExpUser%36F7BD3602A4; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ExpUser.h

#ifndef ExpUser_h
#define ExpUser_h 1

//## begin module%36F7BD3602A4.additionalIncludes preserve=no
//## end module%36F7BD3602A4.additionalIncludes

//## begin module%36F7BD3602A4.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36F7BD3602A4.includes

// Export
#include "Export.h"
// UserMng
#include "UserMng.h"
//## begin module%36F7BD3602A4.declarations preserve=no
//## end module%36F7BD3602A4.declarations

//## begin module%36F7BD3602A4.additionalDeclarations preserve=yes
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
//## end module%36F7BD3602A4.additionalDeclarations


//## begin ZUUserExport%36F7BC4003CD.preface preserve=yes
//## end ZUUserExport%36F7BC4003CD.preface

//## Class: ZUUserExport%36F7BC4003CD
//	Exports the user table.
//## Category: ZUtil library::Export classes%36F7CCFF024A
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%36F7BEA1031E;ZUUserManager { -> }

class AFX_EXT_CLASS ZUUserExport : public ZUExport  //## Inherits: <unnamed>%36F7BC4E001F
{
  //## begin ZUUserExport%36F7BC4003CD.initialDeclarations preserve=yes
  //## end ZUUserExport%36F7BC4003CD.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZUUserExport%922203348
      //	Constructs an export class with the filename and the
      //	user manager pointer
      ZUUserExport (CString Filename = "", ZUUserManager* pUserManager = NULL, BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

    //## Destructor (generated)
      ~ZUUserExport();


    //## Other Operations (specified)
      //## Operation: GetExportedLine%922203349
      //	Build the export line and return it.
      virtual CString GetExportedLine (CObject* pObj);

      //## Operation: ProcessLine%922203351
      //	Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: GetHeaderLine%922203352
      //	This function builds the header line.
      virtual CString GetHeaderLine ();

      //## Operation: Import%922203353
      //	This function imports the file to the document.
      virtual BOOL Import ();

      //## Operation: Export%922203354
      //	This function exports the records to a file.
      virtual BOOL Export ();

      //## Operation: Create%922203355
      //	Create the export class.
      virtual void Create (CString Filename, ZUUserManager* pUserManager = NULL, BOOL GenerateHeader = FALSE, SynchronizationSeparatorType SeparatorType = AutomaticSeparator, CString Schema = szOriginalSchema, int PropagationMode = LocatePageOnly, BOOL EmptyWhenZero = FALSE, ZIStatusBar* pStatusBar = NULL);

      //## Operation: ForecastedTotalObject%922203369
      //	This function should return the forecasted total object.
      virtual double ForecastedTotalObject ();

      //## Operation: DoExportLoop%922203370
      //	This function do the loop for export.
      virtual BOOL DoExportLoop ();

      //## Operation: PreImport%922203371
      //	This function imports the file to the document.
      virtual BOOL PreImport ();

    // Additional Public Declarations
      //## begin ZUUserExport%36F7BC4003CD.public preserve=yes
      //## end ZUUserExport%36F7BC4003CD.public

  protected:
    // Additional Protected Declarations
      //## begin ZUUserExport%36F7BC4003CD.protected preserve=yes
      //## end ZUUserExport%36F7BC4003CD.protected

  private:
    //## Constructors (generated)
      ZUUserExport(const ZUUserExport &right);

    //## Assignment Operation (generated)
      const ZUUserExport & operator=(const ZUUserExport &right);

    // Data Members for Class Attributes

      //## Attribute: pUserManager%36F7BDCE02B6
      //## begin ZUUserExport::pUserManager%36F7BDCE02B6.attr preserve=no  public: ZUUserManager* {U} 
      ZUUserManager* m_pUserManager;
      //## end ZUUserExport::pUserManager%36F7BDCE02B6.attr

    // Additional Private Declarations
      //## begin ZUUserExport%36F7BC4003CD.private preserve=yes
      //## end ZUUserExport%36F7BC4003CD.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZUUserExport%36F7BC4003CD.implementation preserve=yes
      //## end ZUUserExport%36F7BC4003CD.implementation

};

//## begin ZUUserExport%36F7BC4003CD.postscript preserve=yes
//## end ZUUserExport%36F7BC4003CD.postscript

// Class ZUUserExport 


//## Other Operations (inline)
inline void ZUUserExport::Create (CString Filename, ZUUserManager* pUserManager, BOOL GenerateHeader, SynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
{
  //## begin ZUUserExport::Create%922203355.body preserve=yes
  	m_pUserManager = pUserManager;
	ZUExport::Create (Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar);
  //## end ZUUserExport::Create%922203355.body
}

//## begin module%36F7BD3602A4.epilog preserve=yes
//## end module%36F7BD3602A4.epilog


#endif
