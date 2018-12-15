//## begin module%367B898F009F.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%367B898F009F.cm

//## begin module%367B898F009F.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%367B898F009F.cp

//## Module: FldStamp%367B898F009F; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldStamp.h

#ifndef FldStamp_h
#define FldStamp_h 1

//## begin module%367B898F009F.additionalIncludes preserve=no
//## end module%367B898F009F.additionalIncludes

//## begin module%367B898F009F.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%367B898F009F.includes

// Stamp
#include "Stamp.h"
//## begin module%367B898F009F.declarations preserve=no
//## end module%367B898F009F.declarations

//## begin module%367B898F009F.additionalDeclarations preserve=yes
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
//## end module%367B898F009F.additionalDeclarations


//## Class: ZDFolderStamp%367B892D02BB
//## Category: ZBaseLib::Stamp classes%36F38AA403D8
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZDFolderStamp : public ZDStamp  //## Inherits: <unnamed>%367B893903B2
{
  //## begin ZDFolderStamp%367B892D02BB.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef ZDStamp inherited;
  //## end ZDFolderStamp%367B892D02BB.initialDeclarations

  public:
    //## Constructors (generated)
      ZDFolderStamp();

      ZDFolderStamp(const ZDFolderStamp &right);

    //## Destructor (generated)
      virtual ~ZDFolderStamp();

    //## Assignment Operation (generated)
      const ZDFolderStamp & operator=(const ZDFolderStamp &right);


    //## Other Operations (specified)
      //## Operation: operator >>%914061095
      //    Store from the archive to the object Stamp.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZDFolderStamp& Stamp);

      //## Operation: operator <<%914061096
      //    Store the object Stamp to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, const ZDFolderStamp& Stamp);

      //## Operation: ReadFromFile%927439023
      //    Read the stamp from a given filename.
      virtual BOOL ReadFromFile (CString Filename);

      //## Operation: ClearPassword%936298261
      //    Clear the existing password.
      BOOL ClearPassword ();

      //## Operation: SetPassword%936298262
      //    Set a new password.
      BOOL SetPassword (const CString Password);

      //## Operation: HasPassword%936298263
      //    Return true if the document is password protected.
      BOOL HasPassword () const;

      //## Operation: Clone%939754021
      ZDFolderStamp* Clone ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: FolderName%367B89DC02B2
      //    The folder name.
      const CString GetFolderName () const;
      void SetFolderName (CString value);

      //## Attribute: FolderDescription%367B89FB03CF
      //    The Folder description.
      const CString GetFolderDescription () const;
      void SetFolderDescription (CString value);

      //## Attribute: CreationUserName%367B8A420074
      //    The username for the creation.
      const CString GetCreationUserName () const;
      void SetCreationUserName (CString value);

      //## Attribute: CreationDate%36F38C500239
      //    The date of the creation.
      const ZBDate GetCreationDate () const;
      void SetCreationDate (ZBDate value);

      //## Attribute: ModificationUserName%367B8A6D01DF
      //    The username for the last modification.
      const CString GetModificationUserName () const;
      void SetModificationUserName (CString value);

      //## Attribute: ModificationDate%36F38C2700C8
      //    The date of the last modification.
      const ZBDate GetModificationDate () const;
      void SetModificationDate (ZBDate value);

      //## Attribute: Key1%3818BF1E01CF
      //    Define a private key.
      const CString GetKey1 () const;
      void SetKey1 (CString value);

    // Additional Public Declarations
      //## begin ZDFolderStamp%367B892D02BB.public preserve=yes
      //## end ZDFolderStamp%367B892D02BB.public

  protected:
    // Additional Protected Declarations
      //## begin ZDFolderStamp%367B892D02BB.protected preserve=yes
      //## end ZDFolderStamp%367B892D02BB.protected

  private:
    // Data Members for Class Attributes

      //## begin ZDFolderStamp::FolderName%367B89DC02B2.attr preserve=no  public: CString {U} 
      CString m_FolderName;
      //## end ZDFolderStamp::FolderName%367B89DC02B2.attr

      //## begin ZDFolderStamp::FolderDescription%367B89FB03CF.attr preserve=no  public: CString {U} 
      CString m_FolderDescription;
      //## end ZDFolderStamp::FolderDescription%367B89FB03CF.attr

      //## begin ZDFolderStamp::CreationUserName%367B8A420074.attr preserve=no  public: CString {U} 
      CString m_CreationUserName;
      //## end ZDFolderStamp::CreationUserName%367B8A420074.attr

      //## begin ZDFolderStamp::CreationDate%36F38C500239.attr preserve=no  public: ZBDate {U} 
      ZBDate m_CreationDate;
      //## end ZDFolderStamp::CreationDate%36F38C500239.attr

      //## begin ZDFolderStamp::ModificationUserName%367B8A6D01DF.attr preserve=no  public: CString {U} 
      CString m_ModificationUserName;
      //## end ZDFolderStamp::ModificationUserName%367B8A6D01DF.attr

      //## begin ZDFolderStamp::ModificationDate%36F38C2700C8.attr preserve=no  public: ZBDate {U} 
      ZBDate m_ModificationDate;
      //## end ZDFolderStamp::ModificationDate%36F38C2700C8.attr

      //## Attribute: Password%37CEDEFC01BE
      //    Contains the password
      //## begin ZDFolderStamp::Password%37CEDEFC01BE.attr preserve=no  private: CString {U} 
      CString m_Password;
      //## end ZDFolderStamp::Password%37CEDEFC01BE.attr

      //## begin ZDFolderStamp::Key1%3818BF1E01CF.attr preserve=no  public: CString {U} 
      CString m_Key1;
      //## end ZDFolderStamp::Key1%3818BF1E01CF.attr

    // Additional Private Declarations
      //## begin ZDFolderStamp%367B892D02BB.private preserve=yes
      //## end ZDFolderStamp%367B892D02BB.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZDFolderStamp%367B892D02BB.implementation preserve=yes
      //## end ZDFolderStamp%367B892D02BB.implementation

};

//## begin ZDFolderStamp%367B892D02BB.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZDFolderStamp%367B892D02BB.postscript

// Class ZDFolderStamp 


//## Other Operations (inline)
inline BOOL ZDFolderStamp::HasPassword () const
{
  //## begin ZDFolderStamp::HasPassword%936298263.body preserve=yes
    return m_Password.IsEmpty() == FALSE;
  //## end ZDFolderStamp::HasPassword%936298263.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZDFolderStamp::GetFolderName () const
{
  //## begin ZDFolderStamp::GetFolderName%367B89DC02B2.get preserve=no
  return m_FolderName;
  //## end ZDFolderStamp::GetFolderName%367B89DC02B2.get
}

inline void ZDFolderStamp::SetFolderName (CString value)
{
  //## begin ZDFolderStamp::SetFolderName%367B89DC02B2.set preserve=no
  m_FolderName = value;
  //## end ZDFolderStamp::SetFolderName%367B89DC02B2.set
}

inline const CString ZDFolderStamp::GetFolderDescription () const
{
  //## begin ZDFolderStamp::GetFolderDescription%367B89FB03CF.get preserve=no
  return m_FolderDescription;
  //## end ZDFolderStamp::GetFolderDescription%367B89FB03CF.get
}

inline void ZDFolderStamp::SetFolderDescription (CString value)
{
  //## begin ZDFolderStamp::SetFolderDescription%367B89FB03CF.set preserve=no
  m_FolderDescription = value;
  //## end ZDFolderStamp::SetFolderDescription%367B89FB03CF.set
}

inline const CString ZDFolderStamp::GetCreationUserName () const
{
  //## begin ZDFolderStamp::GetCreationUserName%367B8A420074.get preserve=no
  return m_CreationUserName;
  //## end ZDFolderStamp::GetCreationUserName%367B8A420074.get
}

inline void ZDFolderStamp::SetCreationUserName (CString value)
{
  //## begin ZDFolderStamp::SetCreationUserName%367B8A420074.set preserve=no
  m_CreationUserName = value;
  //## end ZDFolderStamp::SetCreationUserName%367B8A420074.set
}

inline const ZBDate ZDFolderStamp::GetCreationDate () const
{
  //## begin ZDFolderStamp::GetCreationDate%36F38C500239.get preserve=no
  return m_CreationDate;
  //## end ZDFolderStamp::GetCreationDate%36F38C500239.get
}

inline void ZDFolderStamp::SetCreationDate (ZBDate value)
{
  //## begin ZDFolderStamp::SetCreationDate%36F38C500239.set preserve=no
  m_CreationDate = value;
  //## end ZDFolderStamp::SetCreationDate%36F38C500239.set
}

inline const CString ZDFolderStamp::GetModificationUserName () const
{
  //## begin ZDFolderStamp::GetModificationUserName%367B8A6D01DF.get preserve=no
  return m_ModificationUserName;
  //## end ZDFolderStamp::GetModificationUserName%367B8A6D01DF.get
}

inline void ZDFolderStamp::SetModificationUserName (CString value)
{
  //## begin ZDFolderStamp::SetModificationUserName%367B8A6D01DF.set preserve=no
  m_ModificationUserName = value;
  //## end ZDFolderStamp::SetModificationUserName%367B8A6D01DF.set
}

inline const ZBDate ZDFolderStamp::GetModificationDate () const
{
  //## begin ZDFolderStamp::GetModificationDate%36F38C2700C8.get preserve=no
  return m_ModificationDate;
  //## end ZDFolderStamp::GetModificationDate%36F38C2700C8.get
}

inline void ZDFolderStamp::SetModificationDate (ZBDate value)
{
  //## begin ZDFolderStamp::SetModificationDate%36F38C2700C8.set preserve=no
  m_ModificationDate = value;
  //## end ZDFolderStamp::SetModificationDate%36F38C2700C8.set
}

inline const CString ZDFolderStamp::GetKey1 () const
{
  //## begin ZDFolderStamp::GetKey1%3818BF1E01CF.get preserve=no
  return m_Key1;
  //## end ZDFolderStamp::GetKey1%3818BF1E01CF.get
}

inline void ZDFolderStamp::SetKey1 (CString value)
{
  //## begin ZDFolderStamp::SetKey1%3818BF1E01CF.set preserve=no
  m_Key1 = value;
  //## end ZDFolderStamp::SetKey1%3818BF1E01CF.set
}

//## begin module%367B898F009F.epilog preserve=yes
//## end module%367B898F009F.epilog


#endif
