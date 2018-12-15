//## begin module%345A3B31024E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%345A3B31024E.cm

//## begin module%345A3B31024E.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%345A3B31024E.cp

//## Module: TmplDir%345A3B31024E; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplDir.h

#ifndef TmplDir_h
#define TmplDir_h 1

//## begin module%345A3B31024E.additionalIncludes preserve=no
//## end module%345A3B31024E.additionalIncludes

//## begin module%345A3B31024E.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%345A3B31024E.includes

// TmplFile
#include "TmplFile.h"
// Mfc
#include "Mfc.h"
//## begin module%345A3B31024E.declarations preserve=no
//## end module%345A3B31024E.declarations

//## begin module%345A3B31024E.additionalDeclarations preserve=yes
//## end module%345A3B31024E.additionalDeclarations


//## begin ZDTemplateDir%345A3B3E037A.preface preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end ZDTemplateDir%345A3B3E037A.preface

//## Class: ZDTemplateDir%345A3B3E037A
//    This class manage the template files contained in the
//    template directory.
//## Category: ZUtil library::Templates%3747CDAD02D3
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%345A3BFA0348;ZDTemplateFile { -> }

class AFX_EXT_CLASS ZDTemplateDir : public CObject  //## Inherits: <unnamed>%345B0BB10280
{
  //## begin ZDTemplateDir%345A3B3E037A.initialDeclarations preserve=yes
    DECLARE_DYNCREATE(ZDTemplateDir)
  //## end ZDTemplateDir%345A3B3E037A.initialDeclarations

  public:
    //## Constructors (generated)
      ZDTemplateDir();

    //## Constructors (specified)
      //## Operation: ZDTemplateDir%878377698
      //    Create the object ZDTemplateDir. You must specify the
      //    directory and the object automatically scans it and
      //    initialize correctly the object.
      ZDTemplateDir (CString Directory, CString Title, CString FileExtension);

    //## Destructor (generated)
      virtual ~ZDTemplateDir();


    //## Other Operations (specified)
      //## Operation: FindFile%878329362
      //    This method search a template file. To use this function
      //    you must specify the filename.
      ZDTemplateFile* FindFile (CString Filename);

      //## Operation: FindTitle%878329363
      //    This method search a template file. To use this function
      //    you must specify the title.
      ZDTemplateFile* FindTitle (CString Title);

      //## Operation: Create%878329366
      //    Create the object ZDTemplateDir. You must specify the
      //    directory and the object automatically scans it and
      //    initialize correctly the object.
      BOOL Create (CString Directory, CString Title);

      //## Operation: GetTemplateFileAt%878492725
      //    Returns the template file object at the specified index.
      ZDTemplateFile* GetTemplateFileAt (size_t Index);

      //## Operation: GetSize%878492727
      //    Return the number of template file.
      size_t GetSize () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Directory%345A3B800168
      //    Contains the template directory.
      const CString GetDirectory () const;

      //## Attribute: Title%345B19D100DC
      //    Defines the directory title.
      CString GetTitle ();

      //## Attribute: FileExtension%368FB1EC0212
      const CString GetFileExtension () const;
      void SetFileExtension (CString value);

    // Additional Public Declarations
      //## begin ZDTemplateDir%345A3B3E037A.public preserve=yes
      const CStringArray&    GetTemplateFileList() const { return m_TemplateFileList; };
      //## end ZDTemplateDir%345A3B3E037A.public
  protected:
    // Additional Protected Declarations
      //## begin ZDTemplateDir%345A3B3E037A.protected preserve=yes
      //## end ZDTemplateDir%345A3B3E037A.protected

  private:
    //## Constructors (generated)
      ZDTemplateDir(const ZDTemplateDir &right);

    //## Assignment Operation (generated)
      const ZDTemplateDir & operator=(const ZDTemplateDir &right);


    //## Other Operations (specified)
      //## Operation: FreeList%878377699
      //    Free the list of object.
      void FreeList ();

    // Data Members for Class Attributes

      //## begin ZDTemplateDir::Directory%345A3B800168.attr preserve=no  public: CString {U} 
      CString m_Directory;
      //## end ZDTemplateDir::Directory%345A3B800168.attr

      //## Attribute: DirectoryList%345A3BA803B6
      //    Contains the list of ZDTemplateFile.
      //## begin ZDTemplateDir::DirectoryList%345A3BA803B6.attr preserve=no  public: CObArray {U} 
      CObArray m_DirectoryList;
      //## end ZDTemplateDir::DirectoryList%345A3BA803B6.attr

      //## begin ZDTemplateDir::Title%345B19D100DC.attr preserve=no  public: CString {U} 
      CString m_Title;
      //## end ZDTemplateDir::Title%345B19D100DC.attr

      //## begin ZDTemplateDir::FileExtension%368FB1EC0212.attr preserve=no  public: CString {U} 
      CString m_FileExtension;
      //## end ZDTemplateDir::FileExtension%368FB1EC0212.attr

    // Additional Private Declarations
      //## begin ZDTemplateDir%345A3B3E037A.private preserve=yes
      //## end ZDTemplateDir%345A3B3E037A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZDTemplateDir%345A3B3E037A.implementation preserve=yes
      CStringArray    m_TemplateFileList;
      //## end ZDTemplateDir%345A3B3E037A.implementation
};

//## begin ZDTemplateDir%345A3B3E037A.postscript preserve=yes
//## end ZDTemplateDir%345A3B3E037A.postscript

// Class ZDTemplateDir 


//## Other Operations (inline)
inline ZDTemplateFile* ZDTemplateDir::GetTemplateFileAt (size_t Index)
{
  //## begin ZDTemplateDir::GetTemplateFileAt%878492725.body preserve=yes
    return (Index <= (size_t)m_DirectoryList.GetSize()) ? ((ZDTemplateFile*)(m_DirectoryList[Index])): NULL;
  //## end ZDTemplateDir::GetTemplateFileAt%878492725.body
}

inline size_t ZDTemplateDir::GetSize () const
{
  //## begin ZDTemplateDir::GetSize%878492727.body preserve=yes
    return (size_t)m_DirectoryList.GetSize();
  //## end ZDTemplateDir::GetSize%878492727.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZDTemplateDir::GetDirectory () const
{
  //## begin ZDTemplateDir::GetDirectory%345A3B800168.get preserve=no
  return m_Directory;
  //## end ZDTemplateDir::GetDirectory%345A3B800168.get
}

inline CString ZDTemplateDir::GetTitle ()
{
  //## begin ZDTemplateDir::GetTitle%345B19D100DC.get preserve=no
  return m_Title;
  //## end ZDTemplateDir::GetTitle%345B19D100DC.get
}

inline const CString ZDTemplateDir::GetFileExtension () const
{
  //## begin ZDTemplateDir::GetFileExtension%368FB1EC0212.get preserve=no
  return m_FileExtension;
  //## end ZDTemplateDir::GetFileExtension%368FB1EC0212.get
}

inline void ZDTemplateDir::SetFileExtension (CString value)
{
  //## begin ZDTemplateDir::SetFileExtension%368FB1EC0212.set preserve=no
  m_FileExtension = value;
  //## end ZDTemplateDir::SetFileExtension%368FB1EC0212.set
}

//## begin module%345A3B31024E.epilog preserve=yes
//## end module%345A3B31024E.epilog


#endif
