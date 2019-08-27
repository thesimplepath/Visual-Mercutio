//## begin module%345A3A5503B6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%345A3A5503B6.cm

//## begin module%345A3A5503B6.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%345A3A5503B6.cp

//## Module: TmplFile%345A3A5503B6; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplFile.h

#ifndef TmplFile_h
#define TmplFile_h 1

//## begin module%345A3A5503B6.additionalIncludes preserve=no
//## end module%345A3A5503B6.additionalIncludes

//## begin module%345A3A5503B6.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


//## end module%345A3A5503B6.includes

// FldStamp
#include "PSS_FolderStamp.h"
//## begin module%345A3A5503B6.declarations preserve=no
//## end module%345A3A5503B6.declarations

//## begin module%345A3A5503B6.additionalDeclarations preserve=yes
//## end module%345A3A5503B6.additionalDeclarations


//## begin ZDTemplateFile%345A3A01035C.preface preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end ZDTemplateFile%345A3A01035C.preface

//## Class: ZDTemplateFile%345A3A01035C
//    This classe encapsulate information of a template file.
//## Category: ZUtil library::Templates%3747CDAD02D3
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%345AFB23024E;ZDFolderStamp { -> }

class AFX_EXT_CLASS ZDTemplateFile : public CObject
{
  //## begin ZDTemplateFile%345A3A01035C.initialDeclarations preserve=yes
  //## end ZDTemplateFile%345A3A01035C.initialDeclarations

  public:
    //## Constructors (generated)
      ZDTemplateFile(const ZDTemplateFile &right);

    //## Constructors (specified)
      //## Operation: ZDTemplateFile%878377696
      //    Create the object. You must specify the filename.
      ZDTemplateFile (CString Filename = "");

    //## Destructor (generated)
      virtual ~ZDTemplateFile();

    //## Assignment Operation (generated)
      const ZDTemplateFile & operator=(const ZDTemplateFile &right);


    //## Other Operations (specified)
      //## Operation: GetDescription%878377695
      //    Returns the description contained in ZDStamp member.
      CString GetDescription () const;

      //## Operation: Create%878377697
      //    Create the object. You must specify the filename.
      BOOL Create (CString Filename);

      //## Operation: IsPersistent%878377700
      //    Return the Persistent class member.
      BOOL IsPersistent () const;

      //## Operation: GetTitle%878492726
      //    Returns the title contained in ZDStamp member.
      CString GetTitle () const;

      //## Operation: operator >>%927987842
      //    Store from the archive to the object Stamp.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZDTemplateFile& TemplateFile);

      //## Operation: operator <<%927987843
      //    Store the object Stamp to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZDTemplateFile& TemplateFile);

      //## Operation: Clone%927987844
      //    Clone this object
      ZDTemplateFile* Clone ();

      //## Operation: Serialize%927987848
      //    Serialize document information.
      virtual void Serialize (CArchive& ar);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Filename%345A3A8403C0
      //    Defines the template filename.
      const CString GetFilename () const;

      //## Attribute: Stamp%345A3AB10122
      //    Defines the template stamp contained in the template
      //    filename.
      const PSS_FolderStamp GetStamp () const;

    // Additional Public Declarations
      //## begin ZDTemplateFile%345A3A01035C.public preserve=yes
      //## end ZDTemplateFile%345A3A01035C.public

  protected:
    // Additional Protected Declarations
      //## begin ZDTemplateFile%345A3A01035C.protected preserve=yes
    DECLARE_SERIAL(ZDTemplateFile)
      //## end ZDTemplateFile%345A3A01035C.protected

  private:
    // Data Members for Class Attributes

      //## begin ZDTemplateFile::Filename%345A3A8403C0.attr preserve=no  public: CString {V} 
      CString m_Filename;
      //## end ZDTemplateFile::Filename%345A3A8403C0.attr

      //## begin ZDTemplateFile::Stamp%345A3AB10122.attr preserve=no  public: ZDFolderStamp {V} 
      PSS_FolderStamp m_Stamp;
      //## end ZDTemplateFile::Stamp%345A3AB10122.attr

      //## Attribute: Persistent%345B01600294
      //    Determine if the object is correctly constructed.
      //## begin ZDTemplateFile::Persistent%345B01600294.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_Persistent;
      //## end ZDTemplateFile::Persistent%345B01600294.attr

    // Additional Private Declarations
      //## begin ZDTemplateFile%345A3A01035C.private preserve=yes
      //## end ZDTemplateFile%345A3A01035C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZDTemplateFile%345A3A01035C.implementation preserve=yes
      //## end ZDTemplateFile%345A3A01035C.implementation

};

//## begin ZDTemplateFile%345A3A01035C.postscript preserve=yes
//## end ZDTemplateFile%345A3A01035C.postscript

// Class ZDTemplateFile 


//## Other Operations (inline)
inline CString ZDTemplateFile::GetDescription () const
{
  //## begin ZDTemplateFile::GetDescription%878377695.body preserve=yes
      return m_Stamp.GetDescription();
  //## end ZDTemplateFile::GetDescription%878377695.body
}

inline BOOL ZDTemplateFile::IsPersistent () const
{
  //## begin ZDTemplateFile::IsPersistent%878377700.body preserve=yes
      return m_Persistent;
  //## end ZDTemplateFile::IsPersistent%878377700.body
}

inline CString ZDTemplateFile::GetTitle () const
{
  //## begin ZDTemplateFile::GetTitle%878492726.body preserve=yes
      return m_Stamp.GetTitle();
  //## end ZDTemplateFile::GetTitle%878492726.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZDTemplateFile::GetFilename () const
{
  //## begin ZDTemplateFile::GetFilename%345A3A8403C0.get preserve=no
  return m_Filename;
  //## end ZDTemplateFile::GetFilename%345A3A8403C0.get
}

inline const PSS_FolderStamp ZDTemplateFile::GetStamp () const
{
  //## begin ZDTemplateFile::GetStamp%345A3AB10122.get preserve=no
  return m_Stamp;
  //## end ZDTemplateFile::GetStamp%345A3AB10122.get
}

#endif
