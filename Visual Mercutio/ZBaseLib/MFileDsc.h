//## begin module%366EBC24022D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%366EBC24022D.cm

//## begin module%366EBC24022D.cp preserve=no
//## end module%366EBC24022D.cp

//## Module: MFileDsc%366EBC24022D; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\MFileDsc.h

#ifndef MFileDsc_h
#define MFileDsc_h 1

//## begin module%366EBC24022D.additionalIncludes preserve=no
//## end module%366EBC24022D.additionalIncludes

//## begin module%366EBC24022D.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%366EBC24022D.includes

// FileMg
#include "FileMg.h"
//## begin module%366EBC24022D.declarations preserve=no
//## end module%366EBC24022D.declarations

//## begin module%366EBC24022D.additionalDeclarations preserve=yes
#ifndef Mapi_h
#define Mapi_h 1
	#include <mapi.h>
#endif

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
//## end module%366EBC24022D.additionalDeclarations


//## Class: ZUMailFileDescription%366EBAA60269
//## Category: PlanFin::Email classes%36722AB50003
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%367553D900F3;ZFileManager { -> }

class AFX_EXT_CLASS ZUMailFileDescription 
{
  //## begin ZUMailFileDescription%366EBAA60269.initialDeclarations preserve=yes
  //## end ZUMailFileDescription%366EBAA60269.initialDeclarations

  public:
    //## Constructors (generated)
      ZUMailFileDescription();

    //## Constructors (specified)
      //## Operation: ZUMailFileDescription%913223370
      ZUMailFileDescription (CStringArray& FileList, AttachementType AttachType = InsertedFile);

      //## Operation: ZUMailFileDescription%913659110
      ZUMailFileDescription (ZFileManager& FileList, AttachementType AttachType = InsertedFile);

    //## Destructor (generated)
      ~ZUMailFileDescription();


    //## Other Operations (specified)
      //## Operation: Fill%913223371
      void Fill (CStringArray& FileList, AttachementType AttachType = InsertedFile);

      //## Operation: Fill%913659108
      void Fill (ZFileManager& FileList, AttachementType AttachType = InsertedFile);

      //## Operation: AddFile%913223372
      //	Returns true of done.
      BOOL AddFile (CString& File, AttachementType AttachType = InsertedFile);

      //## Operation: AddFile%913659109
      //	Returns true of done.
      BOOL AddFile (ZFile& File, AttachementType AttachType = InsertedFile);

      //## Operation: GetCount%913223373
      int GetCount () const;

      //## Operation: GetMapiFileDescPtr%913223374
      //	Returns the pointer to a fill structure.
      MapiFileDesc* GetMapiFileDescPtr ();

      //## Operation: RemoveAllFiles%913223375
      void RemoveAllFiles ();

      //## Operation: GetHyperLinkText%913459630
      //	Build the hyper link text of files.
      const CString& GetHyperLinkText ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: AttachementType%36724CCB01A5
      const AttachementType GetAttachementType () const;
      void SetAttachementType (AttachementType value);

    // Additional Public Declarations
      //## begin ZUMailFileDescription%366EBAA60269.public preserve=yes
      //## end ZUMailFileDescription%366EBAA60269.public

  protected:
    // Additional Protected Declarations
      //## begin ZUMailFileDescription%366EBAA60269.protected preserve=yes
      //## end ZUMailFileDescription%366EBAA60269.protected

  private:
    //## Constructors (generated)
      ZUMailFileDescription(const ZUMailFileDescription &right);

    //## Assignment Operation (generated)
      const ZUMailFileDescription & operator=(const ZUMailFileDescription &right);

    // Data Members for Class Attributes

      //## Attribute: MapiFileDescPtr%366EBBA50180
      //## begin ZUMailFileDescription::MapiFileDescPtr%366EBBA50180.attr preserve=no  private: MapiFileDesc* {U} NULL
      MapiFileDesc* m_MapiFileDescPtr;
      //## end ZUMailFileDescription::MapiFileDescPtr%366EBBA50180.attr

      //## Attribute: FileArray%366EBBC80068
      //## begin ZUMailFileDescription::FileArray%366EBBC80068.attr preserve=no  private: CStringArray {U} 
      CStringArray m_FileArray;
      //## end ZUMailFileDescription::FileArray%366EBBC80068.attr

      //## begin ZUMailFileDescription::AttachementType%36724CCB01A5.attr preserve=no  public: AttachementType {U} 
      AttachementType m_AttachementType;
      //## end ZUMailFileDescription::AttachementType%36724CCB01A5.attr

      //## Attribute: HyperLinkText%367254160196
      //## begin ZUMailFileDescription::HyperLinkText%367254160196.attr preserve=no  public: CString {U} 
      CString m_HyperLinkText;
      //## end ZUMailFileDescription::HyperLinkText%367254160196.attr

    // Additional Private Declarations
      //## begin ZUMailFileDescription%366EBAA60269.private preserve=yes
      //## end ZUMailFileDescription%366EBAA60269.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUMailFileDescription%366EBAA60269.implementation preserve=yes
      //## end ZUMailFileDescription%366EBAA60269.implementation

};

//## begin ZUMailFileDescription%366EBAA60269.postscript preserve=yes
//## end ZUMailFileDescription%366EBAA60269.postscript

// Class ZUMailFileDescription 


//## Other Operations (inline)
inline BOOL ZUMailFileDescription::AddFile (CString& File, AttachementType AttachType)
{
  //## begin ZUMailFileDescription::AddFile%913223372.body preserve=yes
  	m_AttachementType = AttachType;
  	return (m_FileArray.Add( File ) >= 0 );
  //## end ZUMailFileDescription::AddFile%913223372.body
}

inline int ZUMailFileDescription::GetCount () const
{
  //## begin ZUMailFileDescription::GetCount%913223373.body preserve=yes
  	return m_FileArray.GetSize();
  //## end ZUMailFileDescription::GetCount%913223373.body
}

inline void ZUMailFileDescription::RemoveAllFiles ()
{
  //## begin ZUMailFileDescription::RemoveAllFiles%913223375.body preserve=yes
  	m_FileArray.RemoveAll();
  //## end ZUMailFileDescription::RemoveAllFiles%913223375.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const AttachementType ZUMailFileDescription::GetAttachementType () const
{
  //## begin ZUMailFileDescription::GetAttachementType%36724CCB01A5.get preserve=no
  return m_AttachementType;
  //## end ZUMailFileDescription::GetAttachementType%36724CCB01A5.get
}

inline void ZUMailFileDescription::SetAttachementType (AttachementType value)
{
  //## begin ZUMailFileDescription::SetAttachementType%36724CCB01A5.set preserve=no
  m_AttachementType = value;
  //## end ZUMailFileDescription::SetAttachementType%36724CCB01A5.set
}

//## begin module%366EBC24022D.epilog preserve=yes
//## end module%366EBC24022D.epilog


#endif
