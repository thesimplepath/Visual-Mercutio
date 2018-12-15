//## begin module%368CD37302DA.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%368CD37302DA.cm

//## begin module%368CD37302DA.cp preserve=no
//## end module%368CD37302DA.cp

//## Module: UserLd%368CD37302DA; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\UserLd.h

#ifndef UserLd_h
#define UserLd_h 1

//## begin module%368CD37302DA.additionalIncludes preserve=no
//## end module%368CD37302DA.additionalIncludes

//## begin module%368CD37302DA.includes preserve=yes
//## end module%368CD37302DA.includes

// ExpUser
#include "ExpUser.h"
// UserMng
#include "UserMng.h"
//## begin module%368CD37302DA.declarations preserve=no
//## end module%368CD37302DA.declarations

//## begin module%368CD37302DA.additionalDeclarations preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%368CD37302DA.additionalDeclarations


//## begin ZDUserLoader%368CD2BE0136.preface preserve=yes
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
//## end ZDUserLoader%368CD2BE0136.preface

//## Class: ZDUserLoader%368CD2BE0136
//## Category: PlanFin::Network classes%366D71CA007D
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%368CD52F001E;ZUUserManager { -> }
//## Uses: <unnamed>%36F7CE090148;ZUUserExport { -> }

class AFX_EXT_CLASS ZDUserLoader 
{
  //## begin ZDUserLoader%368CD2BE0136.initialDeclarations preserve=yes
  //## end ZDUserLoader%368CD2BE0136.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZDUserLoader%915200903
      //    The default constructor.
      ZDUserLoader (ZUUserManager* pUserManager = NULL, CString FileName = "");

    //## Destructor (generated)
      ~ZDUserLoader();


    //## Other Operations (specified)
      //## Operation: LoadAllUsers%915200904
      //    From the database or the file, loads all users in memory.
      BOOL LoadAllUsers ();

      //## Operation: SaveAllUsers%915200905
      //    Saves all users to the database or the file.
      BOOL SaveAllUsers ();

      //## Operation: AssignUserManager%915200906
      //    Assigns the user manager to work with.
      void AssignUserManager (ZUUserManager* pUserManager);

      //## Operation: AssignFileName%922203372
      void AssignFileName (CString FileName);

      //## Operation: Create%922203373
      void Create (ZUUserManager* pUserManager, CString FileName);

    // Additional Public Declarations
      //## begin ZDUserLoader%368CD2BE0136.public preserve=yes
      //## end ZDUserLoader%368CD2BE0136.public

  protected:
    // Additional Protected Declarations
      //## begin ZDUserLoader%368CD2BE0136.protected preserve=yes
      //## end ZDUserLoader%368CD2BE0136.protected

  private:
    //## Constructors (generated)
      ZDUserLoader(const ZDUserLoader &right);

    //## Assignment Operation (generated)
      const ZDUserLoader & operator=(const ZDUserLoader &right);

    // Data Members for Class Attributes

      //## Attribute: pUserManager%368CD5000190
      //    The pointer to the user manager to load or save.
      //## begin ZDUserLoader::pUserManager%368CD5000190.attr preserve=no  public: ZUUserManager* {U} 
      ZUUserManager* m_pUserManager;
      //## end ZDUserLoader::pUserManager%368CD5000190.attr

      //## Attribute: UserImport%368CDFFD02E4
      //    The classes used to import users.
      //## begin ZDUserLoader::UserImport%368CDFFD02E4.attr preserve=no  public: ZUUserExport {U} 
      ZUUserExport m_UserImport;
      //## end ZDUserLoader::UserImport%368CDFFD02E4.attr

      //## Attribute: FileName%36F7CFC60116
      //## begin ZDUserLoader::FileName%36F7CFC60116.attr preserve=no  public: CString {U} 
      CString m_FileName;
      //## end ZDUserLoader::FileName%36F7CFC60116.attr

    // Additional Private Declarations
      //## begin ZDUserLoader%368CD2BE0136.private preserve=yes
      //## end ZDUserLoader%368CD2BE0136.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZDUserLoader%368CD2BE0136.implementation preserve=yes
      //## end ZDUserLoader%368CD2BE0136.implementation

};

//## begin ZDUserLoader%368CD2BE0136.postscript preserve=yes
//## end ZDUserLoader%368CD2BE0136.postscript

// Class ZDUserLoader 

inline ZDUserLoader::ZDUserLoader (ZUUserManager* pUserManager, CString FileName)
  //## begin ZDUserLoader::ZDUserLoader%915200903.hasinit preserve=no
  //## end ZDUserLoader::ZDUserLoader%915200903.hasinit
  //## begin ZDUserLoader::ZDUserLoader%915200903.initialization preserve=yes
  : m_pUserManager(pUserManager), m_FileName(FileName)
  //## end ZDUserLoader::ZDUserLoader%915200903.initialization
{
  //## begin ZDUserLoader::ZDUserLoader%915200903.body preserve=yes
  //## end ZDUserLoader::ZDUserLoader%915200903.body
}



//## Other Operations (inline)
inline void ZDUserLoader::Create (ZUUserManager* pUserManager, CString FileName)
{
  //## begin ZDUserLoader::Create%922203373.body preserve=yes
    m_pUserManager = pUserManager;
    m_FileName = FileName;
  //## end ZDUserLoader::Create%922203373.body
}

//## begin module%368CD37302DA.epilog preserve=yes
//## end module%368CD37302DA.epilog


#endif
