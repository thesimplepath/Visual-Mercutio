/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:devzone@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zADS library.
// See these sources for detailed information regarding
// zADS libraries.
//
// <nl>Created:		 03/2000
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////


#ifndef _Security_h__
#define _Security_h__ 1



//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _WIN32
	#include <winver.h>
#else
	#include <ver.h>
#endif // _WIN32

#include <SHELLAPI.H>
#include <direct.h>
#include <dos.h>
#include <fstream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Constant definition

const	int		iCurrentVersion = 1;

const	int		iPosDateStart = 2;
const	int		iPosDateLast  = 8;
const	int		iPosCounterStart = 11;
const	int		iPosCounterLast = 17;
const	int		iPosVersion = 18;
const	CString	sLastDate = "LastDate";
const	CString	sLastCounter = "LastCounter";
const	CString	sInitialValue = "@@Initial$$Value";
const	CString	sCheckString = "VERS";


#ifdef _ZSCTYEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif



class AFX_EXT_CLASS ZASecurityEntity 
{
  //## begin ZASecurityEntity.initialDeclarations preserve=yes
  //## end ZASecurityEntity.initialDeclarations

  public:
    //## Constructors (generated)
      ZASecurityEntity();
      ZASecurityEntity( const CString s );

    //## Destructor (generated)
      ~ZASecurityEntity();


    //## Other Operations (specified)
      //## Operation: GenerateRandomEntity%811984121
      //	This function generates a random key.
      CString GenerateRandomEntity();

      //## Operation: GenerateDate%812250686
      CString GenerateDate(CTime tmDate);

      //## Operation: GenerateCounter%812250687
      CString GenerateCounter(int iCounter);

      //## Operation: GetCounter%812250688
      //	Decript the counter and return it.
      int GetCounter();

      //## Operation: GetDate%812250689
      //	Decript the date and return it.
      CTime GetDate();

      //## Operation: GetVersion%855298592
      //	Extract the version from the entity.
      int GetVersion();

      //## Operation: GenerateVersion%855298593
      CString GenerateVersion(int iVersion);

      //	Take the key and cript it.
      void CriptEntity();

      //## Documentation ZASecurityEntity::sEntity.has
      //	The entity
      const CString GetsEntity() const;
      void SetsEntity(const CString value);



  protected:
    // Additional Protected Declarations
      //## begin ZASecurityEntity.protected preserve=yes
      //## end ZASecurityEntity.protected


  private:
    // Additional Private Declarations
      //## begin ZASecurityEntity.private preserve=yes
      //## end ZASecurityEntity.private


  private:  //## implementation

      //## begin ZASecurityEntity::sEntity.has preserve=no  public: CString {1 -> 1VO}
      CString m_sEntity;
      //## end ZASecurityEntity::sEntity.has

    // Additional Implementation Declarations
      //## begin ZASecurityEntity.implementation preserve=yes
      //## end ZASecurityEntity.implementation

};



//## Class: ZASecurity
//	This classes is responsible to provide methods for
//	security checking.
//## Category: Security classes
//## Subsystem: Security Modules
//## Persistence: Transient
//## Cardinality/Multiplicity: n


class AFX_EXT_CLASS ZASecurity 
{
  //## begin ZASecurity.initialDeclarations preserve=yes
  public:
  		int	GetCurrentVersion();
  //## end ZASecurity.initialDeclarations

  public:
    //## Constructors (generated)
      ZASecurity();

    //## Constructors (specified)
      //## Operation: ZASecurity%812250694
      ZASecurity(const CString&  sFileName, const CString ApplicationRegistryKey = "", const CString ApplicationPID = "");

    //## Destructor (generated)
      ~ZASecurity();


    //## Other Operations (specified)
      //## Operation: SetLastUseDate%812250691
      BOOL SetLastUseDate(CTime tmDate);

      //## Operation: SetLastUseCounter%812250692
      BOOL SetLastUseCounter(int iCounter);

      //## Operation: GetCounterSpan%812506908
      //	Return the difference between the initial counter and
      //	the last counter.
      int GetCounterSpan();

      //## Operation: GetTimeSpan%812506909
      CTimeSpan GetTimeSpan();

      //## Operation: IncrementCounter%812682976
      //	Increment the counter.
      BOOL IncrementCounter();

      //## Operation: GetVersion%854929698
      //	Return the version of the license file.
      int GetVersion();

      //## Operation: DisplayWarning%854929699
      //	Display a warning box.
      void DisplayWarning();

      //## Operation: DisplayStopWnd%855119248
      void DisplayStopWnd();

      //## Operation: SetVersion%855298594
      //	Change the version number
      BOOL SetVersion(int iVersion);

    //## Get and Set Operations for Has Relationships (generated)

      //## Documentation ZASecurity::SecurityFile.has
//      const fstream GetSecurityFile() const;

      //## Documentation ZASecurity::sFilename.has
      const CString GetsFilename() const;
      void SetsFilename(const CString value);

    // Additional Public Declarations
      //## begin ZASecurity.public preserve=yes
      //## end ZASecurity.public


  protected:

    //## Other Operations (specified)
      //## Operation: Create%811976842
      //	Create the security filename with the creation date and
      //	counters.
      BOOL Create();

    //## Get and Set Operations for Has Relationships (generated)

      //## Documentation ZASecurity::bError.has
      //	Error flag
      const BOOL GetbError() const;
      void SetbError(const BOOL value);

    // Data Members for Has Relationships

      //## begin ZASecurity::sFilename.has preserve=no  public: CString {1 -> 1VO}
      CString m_sFilename;
      //## end ZASecurity::sFilename.has

    // Additional Protected Declarations
      //## begin ZASecurity.protected preserve=yes
      //## end ZASecurity.protected




  private:  //## implementation

      CString GetSecurityFilename() const;

      // Write the entity table to disk.
      BOOL WriteEntityTable();
	  // Load the security entities from the file to the table.
      BOOL LoadSecurityTable();

protected:
	CString	m_sKey;
	CString	m_sPID;

private:
	CStdioFile m_SecurityFile;

	ZASecurityEntity  m_SecurityEntityTable[20];

	BOOL m_bError;


};



// Class ZASecurity 

//## Get and Set Operations for Has Relationships (inline)

// JMR-MODIF - Le 19 mai 2005 - Fonction inline supprimée car incompatible, et apparamment inutilisée.
//inline const fstream ZASecurity::GetSecurityFile() const
//{
//  //## begin ZASecurity::GetSecurityFile%.get preserve=no
//  return m_SecurityFile;
//  //## end ZASecurity::GetSecurityFile%.get
//}

inline const CString ZASecurity::GetsFilename() const
{
  //## begin ZASecurity::GetsFilename%.get preserve=no
  return m_sFilename;
  //## end ZASecurity::GetsFilename%.get
}

inline void ZASecurity::SetsFilename(const CString value)
{
  //## begin ZASecurity::SetsFilename%.set preserve=no
  m_sFilename = value;
  //## end ZASecurity::SetsFilename%.set
}

inline const BOOL ZASecurity::GetbError() const
{
  //## begin ZASecurity::GetbError%.get preserve=no
  return m_bError;
  //## end ZASecurity::GetbError%.get
}

inline void ZASecurity::SetbError(const BOOL value)
{
  //## begin ZASecurity::SetbError%.set preserve=no
  m_bError = value;
  //## end ZASecurity::SetbError%.set
}





// Class ZASecurityEntity 

//## Get and Set Operations for Has Relationships (inline)

inline const CString ZASecurityEntity::GetsEntity() const
{
  //## begin ZASecurityEntity::GetsEntity%.get preserve=no
  return m_sEntity;
  //## end ZASecurityEntity::GetsEntity%.get
}

inline void ZASecurityEntity::SetsEntity(const CString value)
{
  //## begin ZASecurityEntity::SetsEntity%.set preserve=no
  m_sEntity = value;
  //## end ZASecurityEntity::SetsEntity%.set
}





#endif


