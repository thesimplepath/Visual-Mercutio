//## begin module%345A3C3800BE.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%345A3C3800BE.cm

//## begin module%345A3C3800BE.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%345A3C3800BE.cp

//## Module: TmplMng%345A3C3800BE; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\TmplMng.h

#ifndef TmplMng_h
#define TmplMng_h 1

//## begin module%345A3C3800BE.additionalIncludes preserve=no
//## end module%345A3C3800BE.additionalIncludes

//## begin module%345A3C3800BE.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%345A3C3800BE.includes

// TmplDir
#include "TmplDir.h"
//## begin module%345A3C3800BE.declarations preserve=no
//## end module%345A3C3800BE.declarations

//## begin module%345A3C3800BE.additionalDeclarations preserve=yes
//## end module%345A3C3800BE.additionalDeclarations


//## begin ZDTemplateManager%345A3E310190.preface preserve=yes
#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end ZDTemplateManager%345A3E310190.preface

//## Class: ZDTemplateManager%345A3E310190
//    The template manager manages all templates contained in
//    sub-directories.
//## Category: ZUtil library::Templates%3747CDAD02D3
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%345A3F4C0104;ZDTemplateDir { -> }

class AFX_EXT_CLASS ZDTemplateManager 
{
  //## begin ZDTemplateManager%345A3E310190.initialDeclarations preserve=yes
  //## end ZDTemplateManager%345A3E310190.initialDeclarations

  public:
    //## Constructors (generated)
      ZDTemplateManager();

    //## Constructors (specified)
      //## Operation: ZDTemplateManager%878377701
      //    Create the object ZDTemplateManager. You must specify
      //    the directory and the object automatically scans all
      //    sub-template directories and initialize correctly the
      //    manager.
      ZDTemplateManager (CString RootDirectory, CString FileExtension);

    //## Destructor (generated)
      virtual ~ZDTemplateManager();


    //## Other Operations (specified)
      //## Operation: Create%878329367
      //    Create the object ZDTemplateManager. You must specify
      //    the root template directory and the object automatically
      //    scans all directories and initialize all ZDTemplateDir
      //    objects correctly.
      BOOL Create (CString RootDirectory, CString FileExtension);

      //## Operation: Scan%878329368
      //    REScans all directories and reinitialize all ZDTemplate
      //    Dir objects.
      BOOL Scan ();

      //## Operation: GetSize%878329369
      //    Return the number of template directory.
      size_t GetSize () const;

      //## Operation: GetTemplateDirAt%878329370
      //    Returns the template directory object at the specified
      //    index.
      ZDTemplateDir* GetTemplateDirAt (size_t Index);

      //## Operation: FindTemplateDir%878492724
      //    Finds the template directory object corresponding to the
      //    template directory name.
      ZDTemplateDir* FindTemplateDir (CString TemplateDir);

      //## Operation: FindTemplate%915657290
      //    Finds the template file corresponding to the template
      //    name.
      ZDTemplateFile* FindTemplate (CString TemplateName);

      //## Operation: GetRootCaption%902335798
      //    Returns the root caption equivalent to the root
      //    directory.
      CString GetRootCaption ();

      //## Operation: MoveTemplateFile%902335799
      //    This method move one template file from one template to
      //    another.
      BOOL MoveTemplateFile (CString Filename, CString SourceTemplateDir, CString DestinationTemplateDir);

      //## Operation: MoveTemplateFile%902335800
      //    This method move one template file from one template to
      //    another.
      BOOL MoveTemplateFile (ZDTemplateFile& Filename, ZDTemplateDir& SourceTemplateDir, ZDTemplateDir& DestinationTemplateDir);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: RootDirectory%345B0D8200C8
      const CString& GetRootDirectory () const;

      //## Attribute: FileExtension%368FB40B0384
      //    The file extension type.
      const CString GetFileExtension () const;
      void SetFileExtension (CString value);

    // Additional Public Declarations
      //## begin ZDTemplateManager%345A3E310190.public preserve=yes
      const CStringArray&    GetTemplateDirList() const { return m_TemplateDirList; };
      //## end ZDTemplateManager%345A3E310190.public
  protected:
    // Additional Protected Declarations
      //## begin ZDTemplateManager%345A3E310190.protected preserve=yes
      //## end ZDTemplateManager%345A3E310190.protected

  private:
    //## Constructors (generated)
      ZDTemplateManager(const ZDTemplateManager &right);

    //## Assignment Operation (generated)
      const ZDTemplateManager & operator=(const ZDTemplateManager &right);


    //## Other Operations (specified)
      //## Operation: FreeList%878377702
      //    Free the list of object.
      void FreeList ();

    // Data Members for Class Attributes

      //## Attribute: TemplateList%345A3F5F0366
      //    Contains the list of ZDTemplateDir.
      //## begin ZDTemplateManager::TemplateList%345A3F5F0366.attr preserve=no  public: CObArray {V} 
      CObArray m_TemplateList;
      //## end ZDTemplateManager::TemplateList%345A3F5F0366.attr

      //## begin ZDTemplateManager::RootDirectory%345B0D8200C8.attr preserve=no  public: CString {U} 
      CString m_RootDirectory;
      //## end ZDTemplateManager::RootDirectory%345B0D8200C8.attr

      //## begin ZDTemplateManager::FileExtension%368FB40B0384.attr preserve=no  public: CString {U} 
      CString m_FileExtension;
      //## end ZDTemplateManager::FileExtension%368FB40B0384.attr

    // Additional Private Declarations
      //## begin ZDTemplateManager%345A3E310190.private preserve=yes
      //## end ZDTemplateManager%345A3E310190.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZDTemplateManager%345A3E310190.implementation preserve=yes
      CStringArray    m_TemplateDirList;
      //## end ZDTemplateManager%345A3E310190.implementation
};

//## begin ZDTemplateManager%345A3E310190.postscript preserve=yes
//## end ZDTemplateManager%345A3E310190.postscript

// Class ZDTemplateManager 


//## Other Operations (inline)
inline size_t ZDTemplateManager::GetSize () const
{
  //## begin ZDTemplateManager::GetSize%878329369.body preserve=yes
      return (size_t)m_TemplateList.GetSize();
  //## end ZDTemplateManager::GetSize%878329369.body
}

inline ZDTemplateDir* ZDTemplateManager::GetTemplateDirAt (size_t Index)
{
  //## begin ZDTemplateManager::GetTemplateDirAt%878329370.body preserve=yes
    return (Index <= (size_t)m_TemplateList.GetSize()) ? ((ZDTemplateDir*)(m_TemplateList[Index])): NULL;
  //## end ZDTemplateManager::GetTemplateDirAt%878329370.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString& ZDTemplateManager::GetRootDirectory () const
{
  //## begin ZDTemplateManager::GetRootDirectory%345B0D8200C8.get preserve=no
  return m_RootDirectory;
  //## end ZDTemplateManager::GetRootDirectory%345B0D8200C8.get
}

inline const CString ZDTemplateManager::GetFileExtension () const
{
  //## begin ZDTemplateManager::GetFileExtension%368FB40B0384.get preserve=no
  return m_FileExtension;
  //## end ZDTemplateManager::GetFileExtension%368FB40B0384.get
}

inline void ZDTemplateManager::SetFileExtension (CString value)
{
  //## begin ZDTemplateManager::SetFileExtension%368FB40B0384.set preserve=no
  m_FileExtension = value;
  //## end ZDTemplateManager::SetFileExtension%368FB40B0384.set
}

//## begin module%345A3C3800BE.epilog preserve=yes
//## end module%345A3C3800BE.epilog


#endif
