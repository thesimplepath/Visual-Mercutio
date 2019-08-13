//## begin module%382BBDF40333.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%382BBDF40333.cm

//## begin module%382BBDF40333.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%382BBDF40333.cp

//## Module: FLFDataF%382BBDF40333; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FLFDataF.h

#ifndef FLFDataF_h
#define FLFDataF_h 1

//## begin module%382BBDF40333.additionalIncludes preserve=no
//## end module%382BBDF40333.additionalIncludes

//## begin module%382BBDF40333.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%382BBDF40333.includes

// Export
#include "PSS_Export.h"
//## begin module%382BBDF40333.declarations preserve=no
//## end module%382BBDF40333.declarations

//## begin module%382BBDF40333.additionalDeclarations preserve=yes
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
//## end module%382BBDF40333.additionalDeclarations


//## Class: ZUFLFDataFeed%382BBC9E03AA
//    Used to Import additional information coming from FLF
//    file.
//## Category: ZBaseLib::Data Feed export/import classes%37EB8FB00040
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUFLFDataFeed : public PSS_Export
{
  //## begin ZUFLFDataFeed%382BBC9E03AA.initialDeclarations preserve=yes
  //## end ZUFLFDataFeed%382BBC9E03AA.initialDeclarations

  public:
    //## Constructors (generated)
      ZUFLFDataFeed();

    //## Destructor (generated)
      ~ZUFLFDataFeed();


    //## Other Operations (specified)
      //## Operation: ProcessLine%942391394
      //    Process the line and updates the document.
      virtual BOOL ProcessLine (CString Line);

      //## Operation: ImportAdditionalInfo%942391397
      virtual BOOL ImportAdditionalInfo ();

      //## Operation: PreImport%942391398
      //    This function imports the file to the document.
      virtual BOOL PreImport ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ProcessName%382BBD9602A2
      //    Contains the process name.
      const CString& GetProcessName () const;

      //## Attribute: FormName%382BBDBA007D
      //    Contains the form name.
      const CString& GetFormName () const;

      //## Attribute: FolderName%382BC01E02AE
      //    Contains the folder name.
      const CString& GetFolderName () const;

      //## Attribute: FileName%382BC0200134
      //    Contains the file name.
      const CString& GetFileName () const;

      //## Attribute: ProcessExchangeFileName%38365A1C002C
      //    Contains the process exchange file name.
      const CString& GetProcessExchangeFileName () const;

      //## Attribute: KeepOnlyFLF%382BC03A013B
      //    Contains the flag for keeping or not the source file.
      const BOOL& GetKeepOnlyFLF () const;

    // Additional Public Declarations
      //## begin ZUFLFDataFeed%382BBC9E03AA.public preserve=yes
      //## end ZUFLFDataFeed%382BBC9E03AA.public

  protected:
    // Additional Protected Declarations
      //## begin ZUFLFDataFeed%382BBC9E03AA.protected preserve=yes
      //## end ZUFLFDataFeed%382BBC9E03AA.protected

  private:
    //## Constructors (generated)
      ZUFLFDataFeed(const ZUFLFDataFeed &right);

    //## Assignment Operation (generated)
      const ZUFLFDataFeed & operator=(const ZUFLFDataFeed &right);

    // Data Members for Class Attributes

      //## begin ZUFLFDataFeed::ProcessName%382BBD9602A2.attr preserve=no  public: CString {U} 
      CString m_ProcessName;
      //## end ZUFLFDataFeed::ProcessName%382BBD9602A2.attr

      //## begin ZUFLFDataFeed::FormName%382BBDBA007D.attr preserve=no  public: CString {U} 
      CString m_FormName;
      //## end ZUFLFDataFeed::FormName%382BBDBA007D.attr

      //## begin ZUFLFDataFeed::FolderName%382BC01E02AE.attr preserve=no  public: CString {U} 
      CString m_FolderName;
      //## end ZUFLFDataFeed::FolderName%382BC01E02AE.attr

      //## begin ZUFLFDataFeed::FileName%382BC0200134.attr preserve=no  public: CString {U} 
      CString m_FileName;
      //## end ZUFLFDataFeed::FileName%382BC0200134.attr

      //## begin ZUFLFDataFeed::ProcessExchangeFileName%38365A1C002C.attr preserve=no  public: CString {U} 
      CString m_ProcessExchangeFileName;
      //## end ZUFLFDataFeed::ProcessExchangeFileName%38365A1C002C.attr

      //## begin ZUFLFDataFeed::KeepOnlyFLF%382BC03A013B.attr preserve=no  public: BOOL {U} 
      BOOL m_KeepOnlyFLF;
      //## end ZUFLFDataFeed::KeepOnlyFLF%382BC03A013B.attr

    // Additional Private Declarations
      //## begin ZUFLFDataFeed%382BBC9E03AA.private preserve=yes
      //## end ZUFLFDataFeed%382BBC9E03AA.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUFLFDataFeed%382BBC9E03AA.implementation preserve=yes
      //## end ZUFLFDataFeed%382BBC9E03AA.implementation

};

//## begin ZUFLFDataFeed%382BBC9E03AA.postscript preserve=yes
//## end ZUFLFDataFeed%382BBC9E03AA.postscript

// Class ZUFLFDataFeed 

//## Get and Set Operations for Class Attributes (inline)

inline const CString& ZUFLFDataFeed::GetProcessName () const
{
  //## begin ZUFLFDataFeed::GetProcessName%382BBD9602A2.get preserve=no
  return m_ProcessName;
  //## end ZUFLFDataFeed::GetProcessName%382BBD9602A2.get
}

inline const CString& ZUFLFDataFeed::GetFormName () const
{
  //## begin ZUFLFDataFeed::GetFormName%382BBDBA007D.get preserve=no
  return m_FormName;
  //## end ZUFLFDataFeed::GetFormName%382BBDBA007D.get
}

inline const CString& ZUFLFDataFeed::GetFolderName () const
{
  //## begin ZUFLFDataFeed::GetFolderName%382BC01E02AE.get preserve=no
  return m_FolderName;
  //## end ZUFLFDataFeed::GetFolderName%382BC01E02AE.get
}

inline const CString& ZUFLFDataFeed::GetFileName () const
{
  //## begin ZUFLFDataFeed::GetFileName%382BC0200134.get preserve=no
  return m_FileName;
  //## end ZUFLFDataFeed::GetFileName%382BC0200134.get
}

inline const CString& ZUFLFDataFeed::GetProcessExchangeFileName () const
{
  //## begin ZUFLFDataFeed::GetProcessExchangeFileName%38365A1C002C.get preserve=no
  return m_ProcessExchangeFileName;
  //## end ZUFLFDataFeed::GetProcessExchangeFileName%38365A1C002C.get
}

inline const BOOL& ZUFLFDataFeed::GetKeepOnlyFLF () const
{
  //## begin ZUFLFDataFeed::GetKeepOnlyFLF%382BC03A013B.get preserve=no
  return m_KeepOnlyFLF;
  //## end ZUFLFDataFeed::GetKeepOnlyFLF%382BC03A013B.get
}

//## begin module%382BBDF40333.epilog preserve=yes
//## end module%382BBDF40333.epilog


#endif
