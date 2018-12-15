//## begin module%374DA4370260.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%374DA4370260.cm

//## begin module%374DA4370260.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%374DA4370260.cp

//## Module: MailMsg%374DA4370260; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\MailMsg.h

#ifndef MailMsg_h
#define MailMsg_h 1

//## begin module%374DA4370260.additionalIncludes preserve=no
//## end module%374DA4370260.additionalIncludes

//## begin module%374DA4370260.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "FileMg.h"
//## end module%374DA4370260.includes

// MFileDsc
#include "MFileDsc.h"
// PersonLs
#include "PersonLs.h"
// Mfc
#include "Mfc.h"
//## begin module%374DA4370260.declarations preserve=no
//## end module%374DA4370260.declarations

//## begin module%374DA4370260.additionalDeclarations preserve=yes
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
//## end module%374DA4370260.additionalDeclarations


//## Class: ZBMailMessage%374D9FC902EB
//    Contains the mail message.
//## Category: ZBaseLib::Mail classes%37B3EF830338
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%374DA84C03D5;ZUMailUserList { -> }
//## Uses: <unnamed>%387F0BED03DE;ZUMailFileDescription { -> }

class AFX_EXT_CLASS ZBMailMessage : public CObject  //## Inherits: <unnamed>%375128F80235
{
  //## begin ZBMailMessage%374D9FC902EB.initialDeclarations preserve=yes
  //## end ZBMailMessage%374D9FC902EB.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZBMailMessage%927831775
      //    Default constructor.
      ZBMailMessage (ZUMailUserList* UserList = NULL, const CString Subject = "", const CString Text = "");

    //## Destructor (generated)
      ~ZBMailMessage();


    //## Other Operations (specified)
      //## Operation: Serialize%928062191
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: AddPerson%927831776
      //    Add a new person.
      BOOL AddPerson (CString PersonName, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%927831777
      //    Add a new person.
      BOOL AddPerson (ZBMailUser& Person, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%927831778
      //    Add a new person.
      BOOL AddPerson (ZUser& Person, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%927831779
      //    Add a new person.
      BOOL AddPerson (MapiRecipDesc* pMapiDesc);

      //## Operation: FillPerson%927831780
      void FillPerson (CStringArray& PersonList, ULONG RecipClass = MAPI_TO);

      //## Operation: FillPerson%927831781
      void FillPerson (ZUUserManager& PersonList, ULONG RecipClass = MAPI_TO);

      //## Operation: FillPerson%927831782
      void FillPerson (lpMapiRecipDesc* pMapiDesc, ULONG Count);

      //## Operation: GetMailUserCount%927831784
      int GetMailUserCount () const;

      //## Operation: GetMapiRecipDescPtr%927831785
      //    Build the mapi recipicient description pointer.
      MapiRecipDesc* GetMapiRecipDescPtr ();

      //## Operation: GetMailUserAt%928062189
      //    Get the person at the position i.
      //    Returns null if not found.
      ZBMailUser* GetMailUserAt (int Index);

      //## Operation: RemoveAllMailUser%928062190
      void RemoveAllMailUser ();

      //## Operation: FillFile%947849678
      void FillFile (CStringArray& FileList, AttachementType AttachType = InsertedFile);

      //## Operation: FillFile%947849679
      void FillFile (ZFileManager& FileList, AttachementType AttachType = InsertedFile);

      //## Operation: AddFile%947849680
      //    Returns true of done.
      BOOL AddFile (CString& File, AttachementType AttachType = InsertedFile);

      //## Operation: AddFile%947849681
      //    Returns true of done.
      BOOL AddFile (ZFile& File, AttachementType AttachType = InsertedFile);

      //## Operation: GetFileCount%947849682
      int GetFileCount () const;

      //## Operation: GetMapiFileDescPtr%947849683
      //    Returns the pointer to a fill structure.
      MapiFileDesc* GetMapiFileDescPtr ();

      //## Operation: RemoveAllFiles%947849684
      void RemoveAllFiles ();

      //## Operation: GetHyperLinkText%947849685
      //    Build the hyper link text of files.
      const CString GetHyperLinkText ();

      //## Operation: GetAttachementType%947849686
      AttachementType GetAttachementType () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Subject%374DA46C0158
      //    Contains the subject
      const CString GetSubject () const;
      void SetSubject (CString value);

      //## Attribute: Text%374DA4F6003E
      //    Contains the message text
      const CString GetText () const;
      void SetText (CString value);

      //## Attribute: pMailFileList%387F08C602BB
      //    The pointer to the file list.
      const ZUMailFileDescription* GetpMailFileList () const;

    // Additional Public Declarations
      //## begin ZBMailMessage%374D9FC902EB.public preserve=yes
      //## end ZBMailMessage%374D9FC902EB.public

  protected:
    // Additional Protected Declarations
      //## begin ZBMailMessage%374D9FC902EB.protected preserve=yes
    DECLARE_SERIAL(ZBMailMessage)
      //## end ZBMailMessage%374D9FC902EB.protected
  private:
    //## Constructors (generated)
      ZBMailMessage(const ZBMailMessage &right);

    //## Assignment Operation (generated)
      const ZBMailMessage & operator=(const ZBMailMessage &right);

    // Data Members for Class Attributes

      //## begin ZBMailMessage::Subject%374DA46C0158.attr preserve=no  public: CString {U} 
      CString m_Subject;
      //## end ZBMailMessage::Subject%374DA46C0158.attr

      //## Attribute: pMailUserList%374DA48F0343
      //    Pointer to a mail user list
      //## begin ZBMailMessage::pMailUserList%374DA48F0343.attr preserve=no  public: ZUMailUserList* {U} 
      ZUMailUserList* m_pMailUserList;
      //## end ZBMailMessage::pMailUserList%374DA48F0343.attr

      //## begin ZBMailMessage::Text%374DA4F6003E.attr preserve=no  public: CString {U} 
      CString m_Text;
      //## end ZBMailMessage::Text%374DA4F6003E.attr

      //## begin ZBMailMessage::pMailFileList%387F08C602BB.attr preserve=no  public: ZUMailFileDescription* {U} 
      ZUMailFileDescription* m_pMailFileList;
      //## end ZBMailMessage::pMailFileList%387F08C602BB.attr

    // Additional Private Declarations
      //## begin ZBMailMessage%374D9FC902EB.private preserve=yes
      //## end ZBMailMessage%374D9FC902EB.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBMailMessage%374D9FC902EB.implementation preserve=yes
      //## end ZBMailMessage%374D9FC902EB.implementation

};

//## begin ZBMailMessage%374D9FC902EB.postscript preserve=yes
//## end ZBMailMessage%374D9FC902EB.postscript

// Class ZBMailMessage 


//## Other Operations (inline)
inline BOOL ZBMailMessage::AddPerson (CString PersonName, ULONG RecipClass)
{
  //## begin ZBMailMessage::AddPerson%927831776.body preserve=yes
    if (!m_pMailUserList)
        m_pMailUserList = new ZUMailUserList;
    return m_pMailUserList->AddPerson( PersonName, RecipClass );
  //## end ZBMailMessage::AddPerson%927831776.body
}

inline BOOL ZBMailMessage::AddPerson (ZBMailUser& Person, ULONG RecipClass)
{
  //## begin ZBMailMessage::AddPerson%927831777.body preserve=yes
    if (!m_pMailUserList)
        m_pMailUserList = new ZUMailUserList;
    return m_pMailUserList->AddPerson( Person, RecipClass );
  //## end ZBMailMessage::AddPerson%927831777.body
}

inline BOOL ZBMailMessage::AddPerson (ZUser& Person, ULONG RecipClass)
{
  //## begin ZBMailMessage::AddPerson%927831778.body preserve=yes
    if (!m_pMailUserList)
        m_pMailUserList = new ZUMailUserList;
    return m_pMailUserList->AddPerson( Person, RecipClass );
  //## end ZBMailMessage::AddPerson%927831778.body
}

inline BOOL ZBMailMessage::AddPerson (MapiRecipDesc* pMapiDesc)
{
  //## begin ZBMailMessage::AddPerson%927831779.body preserve=yes
    if (!m_pMailUserList)
        m_pMailUserList = new ZUMailUserList;
    return m_pMailUserList->AddPerson( pMapiDesc );
  //## end ZBMailMessage::AddPerson%927831779.body
}

inline int ZBMailMessage::GetMailUserCount () const
{
  //## begin ZBMailMessage::GetMailUserCount%927831784.body preserve=yes
    if (m_pMailUserList)
        return m_pMailUserList->GetCount();
    return 0;
  //## end ZBMailMessage::GetMailUserCount%927831784.body
}

inline ZBMailUser* ZBMailMessage::GetMailUserAt (int Index)
{
  //## begin ZBMailMessage::GetMailUserAt%928062189.body preserve=yes
    if (m_pMailUserList)
        return m_pMailUserList->GetAt( Index );
    return NULL;
  //## end ZBMailMessage::GetMailUserAt%928062189.body
}

inline void ZBMailMessage::RemoveAllMailUser ()
{
  //## begin ZBMailMessage::RemoveAllMailUser%928062190.body preserve=yes
    if (m_pMailUserList)
        m_pMailUserList->RemoveAllPersons();
  //## end ZBMailMessage::RemoveAllMailUser%928062190.body
}

inline void ZBMailMessage::FillFile (CStringArray& FileList, AttachementType AttachType)
{
  //## begin ZBMailMessage::FillFile%947849678.body preserve=yes
    if (!m_pMailFileList)
        m_pMailFileList = new ZUMailFileDescription;
    if (m_pMailFileList)
        m_pMailFileList->Fill(FileList, AttachType);
  //## end ZBMailMessage::FillFile%947849678.body
}

inline void ZBMailMessage::FillFile (ZFileManager& FileList, AttachementType AttachType)
{
  //## begin ZBMailMessage::FillFile%947849679.body preserve=yes
    if (!m_pMailFileList)
        m_pMailFileList = new ZUMailFileDescription;
    if (m_pMailFileList)
        m_pMailFileList->Fill(FileList, AttachType);
  //## end ZBMailMessage::FillFile%947849679.body
}

inline BOOL ZBMailMessage::AddFile (CString& File, AttachementType AttachType)
{
  //## begin ZBMailMessage::AddFile%947849680.body preserve=yes
    if (!m_pMailFileList)
        m_pMailFileList = new ZUMailFileDescription;
    if (m_pMailFileList)
        return m_pMailFileList->AddFile(File, AttachType);
    return FALSE;
  //## end ZBMailMessage::AddFile%947849680.body
}

inline BOOL ZBMailMessage::AddFile (ZFile& File, AttachementType AttachType)
{
  //## begin ZBMailMessage::AddFile%947849681.body preserve=yes
    if (!m_pMailFileList)
        m_pMailFileList = new ZUMailFileDescription;
    if (m_pMailFileList)
        return m_pMailFileList->AddFile(File, AttachType);
    return FALSE;
  //## end ZBMailMessage::AddFile%947849681.body
}

inline int ZBMailMessage::GetFileCount () const
{
  //## begin ZBMailMessage::GetFileCount%947849682.body preserve=yes
    if (m_pMailFileList)
        return m_pMailFileList->GetCount();
    return 0;
  //## end ZBMailMessage::GetFileCount%947849682.body
}

inline MapiFileDesc* ZBMailMessage::GetMapiFileDescPtr ()
{
  //## begin ZBMailMessage::GetMapiFileDescPtr%947849683.body preserve=yes
    if (m_pMailFileList)
        return m_pMailFileList->GetMapiFileDescPtr();
    return NULL;
  //## end ZBMailMessage::GetMapiFileDescPtr%947849683.body
}

inline void ZBMailMessage::RemoveAllFiles ()
{
  //## begin ZBMailMessage::RemoveAllFiles%947849684.body preserve=yes
    if (m_pMailFileList)
        m_pMailFileList->RemoveAllFiles();
  //## end ZBMailMessage::RemoveAllFiles%947849684.body
}

inline const CString ZBMailMessage::GetHyperLinkText ()
{
  //## begin ZBMailMessage::GetHyperLinkText%947849685.body preserve=yes
    if (m_pMailFileList)
        return m_pMailFileList->GetHyperLinkText();
    return "";
  //## end ZBMailMessage::GetHyperLinkText%947849685.body
}

inline AttachementType ZBMailMessage::GetAttachementType () const
{
  //## begin ZBMailMessage::GetAttachementType%947849686.body preserve=yes
    if (m_pMailFileList)
        return m_pMailFileList->GetAttachementType();
    return AttachementUndefined;
  //## end ZBMailMessage::GetAttachementType%947849686.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZBMailMessage::GetSubject () const
{
  //## begin ZBMailMessage::GetSubject%374DA46C0158.get preserve=no
  return m_Subject;
  //## end ZBMailMessage::GetSubject%374DA46C0158.get
}

inline void ZBMailMessage::SetSubject (CString value)
{
  //## begin ZBMailMessage::SetSubject%374DA46C0158.set preserve=no
  m_Subject = value;
  //## end ZBMailMessage::SetSubject%374DA46C0158.set
}

inline const CString ZBMailMessage::GetText () const
{
  //## begin ZBMailMessage::GetText%374DA4F6003E.get preserve=no
  return m_Text;
  //## end ZBMailMessage::GetText%374DA4F6003E.get
}

inline void ZBMailMessage::SetText (CString value)
{
  //## begin ZBMailMessage::SetText%374DA4F6003E.set preserve=no
  m_Text = value;
  //## end ZBMailMessage::SetText%374DA4F6003E.set
}

inline const ZUMailFileDescription* ZBMailMessage::GetpMailFileList () const
{
  //## begin ZBMailMessage::GetpMailFileList%387F08C602BB.get preserve=no
  return m_pMailFileList;
  //## end ZBMailMessage::GetpMailFileList%387F08C602BB.get
}

//## begin module%374DA4370260.epilog preserve=yes
//## end module%374DA4370260.epilog


#endif
