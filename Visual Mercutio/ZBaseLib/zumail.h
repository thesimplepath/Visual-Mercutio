//## begin module%366D7F640200.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%366D7F640200.cm

//## begin module%366D7F640200.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%366D7F640200.cp

//## Module: ZUMail%366D7F640200; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZUMail.h

#ifndef ZUMail_h
#define ZUMail_h 1

//## begin module%366D7F640200.additionalIncludes preserve=no
//## end module%366D7F640200.additionalIncludes

//## begin module%366D7F640200.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#ifndef _WIN32
    #ifndef Mapi_h
        #define Mapi_h 1
        #include <mapi.h>
    #endif
#else
    #include <mapi.h>
#endif


typedef ULONG (FAR PASCAL *LPMAPILOGON)(ULONG ulUIParam, LPSTR lpszName, LPSTR lpszPassword,
                           FLAGS flFlags, ULONG ulReserved,
                           LPLHANDLE lplhSession);

typedef ULONG (FAR PASCAL *LPMAPILOGOFF)(LHANDLE lhSession, ULONG ulUIParam, FLAGS flFlags,
                            ULONG ulReserved);

typedef ULONG (FAR PASCAL *LPMAPISENDMAIL)(LHANDLE lhSession, ULONG ulUIParam,
                              lpMapiMessage lpMessage, FLAGS flFlags,
                              ULONG ulReserved);

typedef ULONG (FAR PASCAL *LPMAPISENDDOCUMENTS)(ULONG ulUIParam, LPSTR lpszDelimChar,
                                   LPSTR lpszFilePaths, LPSTR lpszFileNames,
                                   ULONG ulReserved);

typedef ULONG (FAR PASCAL *LPMAPIFINDNEXT)(LHANDLE lhSession, ULONG ulUIParam,
                              LPSTR lpszMessageType, LPSTR lpszSeedMessageID,
                              FLAGS flFlags, ULONG ulReserved,
                              LPSTR lpszMessageID);

typedef ULONG (FAR PASCAL *LPMAPIREADMAIL)(LHANDLE lhSession, ULONG ulUIParam,
                              LPSTR lpszMessageID, FLAGS flFlags,
                              ULONG ulReserved, lpMapiMessage FAR *lppMessageOut);

typedef ULONG (FAR PASCAL *LPMAPISAVEMAIL)(LHANDLE lhSession, ULONG ulUIParam,
                              lpMapiMessage pMessage, FLAGS flFlags,
                              ULONG ulReserved, LPSTR lpszMessageID);

typedef ULONG (FAR PASCAL *LPMAPIDELETEMAIL)(LHANDLE lhSession, ULONG ulUIParam,
                                LPSTR lpszMessageID, FLAGS flFlags,
                                ULONG ulReserved);

typedef ULONG (FAR PASCAL *LPMAPIFREEBUFFER)(LPVOID pv);

typedef ULONG (FAR PASCAL *LPMAPIADDRESS)(LHANDLE lhSession, ULONG ulUIParam,
                    LPSTR plszCaption, ULONG nEditFields,
                    LPSTR lpszLabels, ULONG nRecips,
                    lpMapiRecipDesc lpRecips, FLAGS flFlags, ULONG ulReserved, 
                    LPULONG lpnNewRecips, lpMapiRecipDesc FAR *lppNewRecips);

typedef ULONG (FAR PASCAL *LPMAPIDETAILS)(LHANDLE lhSession, ULONG ulUIParam,
                    lpMapiRecipDesc lpRecip, FLAGS flFlags, ULONG ulReserved);

typedef ULONG (FAR PASCAL *LPMAPIRESOLVENAME)(LHANDLE lhSession, ULONG ulUIParam,
                        LPSTR lpszName, FLAGS flFlags,
                        ULONG ulReserved, lpMapiRecipDesc FAR *lppRecip);

/*
extern LPMAPILOGON lpfnMAPILogon; 
extern LPMAPILOGOFF lpfnMAPILogoff; 
extern LPMAPISENDMAIL lpfnMAPISendMail; 
extern LPMAPISENDDOCUMENTS lpfnMAPISendDocuments; 
extern LPMAPIFINDNEXT lpfnMAPIFindNext; 
extern LPMAPIREADMAIL lpfnMAPIReadMail; 
extern LPMAPISAVEMAIL lpfnMAPISaveMail; 
extern LPMAPIDELETEMAIL lpfnMAPIDeleteMail; 
extern LPMAPIFREEBUFFER lpfnMAPIFreeBuffer; 
extern LPMAPIADDRESS lpfnMAPIAddress; 
extern LPMAPIDETAILS lpfnMAPIDetails; 
extern LPMAPIRESOLVENAME lpfnMAPIResolveName; 

#undef MAPILogon 
#undef MAPILogoff 
#undef MAPISendMail 
#undef MAPISendDocuments 
#undef MAPIFindNext 
#undef MAPIReadMail 
#undef MAPISaveMail 
#undef MAPIDeleteMail 
#undef MAPIFreeBuffer 
#undef MAPIAddress 
#undef MAPIDetails 
#undef MAPIResolveName 
#define MAPILogon (*lpfnMAPILogon) 
#define MAPILogoff (*lpfnMAPILogoff) 
#define MAPISendMail (*lpfnMAPISendMail) 
#define MAPISendDocuments (*lpfnMAPISendDocuments) 
#define MAPIFindNext (*lpfnMAPIFindNext) 
#define MAPIReadMail (*lpfnMAPIReadMail) 
#define MAPISaveMail (*lpfnMAPISaveMail) 
#define MAPIDeleteMail (*lpfnMAPIDeleteMail) 
#define MAPIFreeBuffer (*lpfnMAPIFreeBuffer) 
#define MAPIAddress (*lpfnMAPIAddress) 
#define MAPIDetails (*lpfnMAPIDetails) 
#define MAPIResolveName (*lpfnMAPIResolveName) 
 */
 
//## end module%366D7F640200.includes

// PersonLs
#include "PersonLs.h"
// MFileDsc
#include "MFileDsc.h"
// MailMsg
#include "MailMsg.h"
//## begin module%366D7F640200.declarations preserve=no
//## end module%366D7F640200.declarations

//## begin module%366D7F640200.additionalDeclarations preserve=yes
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
//## end module%366D7F640200.additionalDeclarations


//## begin ZUMail%366D7F74031C.preface preserve=yes
//## end ZUMail%366D7F74031C.preface

//## Class: ZUMail%366D7F74031C
//    This utility class allows the user  to send an email.
//## Category: PlanFin::Email classes%36722AB50003
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%366EBBFE0119;ZUMailFileDescription { -> }
//## Uses: <unnamed>%36723174006B;ZUMailUserList { -> }
//## Uses: <unnamed>%374DA3C60358;ZBMailMessage { -> }

class AFX_EXT_CLASS ZUMail 
{
  //## begin ZUMail%366D7F74031C.initialDeclarations preserve=yes
  //## end ZUMail%366D7F74031C.initialDeclarations

  public:
    //## Constructors (generated)
      ZUMail();

    //## Destructor (generated)
      ~ZUMail();


    //## Other Operations (specified)
      //## Operation: SendMail%913142858
      BOOL SendMail (CString Subject = "", CString MessageHeader = "", CString MessageFooter = "", ZUMailUserList* PersonList = NULL);

      //## Operation: SendMail%927831783
      BOOL SendMail (ZBMailMessage& MailMessage);

      //## Operation: SendDocument%913223369
      //    Sends a CDocument.
      BOOL SendDocument (CDocument& Doc, CString Subject = "", CString MessageHeader = "", CString MessageFooter = "", ZUMailUserList* PersonList = NULL);

      //## Operation: SendDocuments%913223376
      //    Sends documents.
      BOOL SendDocuments (ZUMailFileDescription& FileList, CString Subject = "", CString MessageHeader = "", CString MessageFooter = "", ZUMailUserList* PersonList = NULL);

      //## Operation: SendDocuments%913223377
      //    Sends documents.
      BOOL SendDocuments (CStringArray& FileList, CString Subject = "", CString MessageHeader = "", CString MessageFooter = "", ZUMailUserList* PersonList = NULL);

      //## Operation: ResolveName%921575858
      BOOL ResolveName (const CString Name, ZUMailUserList& PersonList, BOOL ShowDialog = FALSE);

      //## Operation: Address%921594740
      BOOL Address (ZUMailUserList& PersonList);

    // Additional Public Declarations
      //## begin ZUMail%366D7F74031C.public preserve=yes
      //## end ZUMail%366D7F74031C.public

  protected:
    // Additional Protected Declarations
      //## begin ZUMail%366D7F74031C.protected preserve=yes
      //## end ZUMail%366D7F74031C.protected

  private:
    //## Constructors (generated)
      ZUMail(const ZUMail &right);

    //## Assignment Operation (generated)
      const ZUMail & operator=(const ZUMail &right);

    // Data Members for Class Attributes

      //## Attribute: InstMail%366EAE9F0013
      //    The mail library instance.
      //## begin ZUMail::InstMail%366EAE9F0013.attr preserve=no  public: static HINSTANCE {V} NULL
      static HINSTANCE m_InstMail;
      //## end ZUMail::InstMail%366EAE9F0013.attr

    // Additional Private Declarations
      //## begin ZUMail%366D7F74031C.private preserve=yes
      //## end ZUMail%366D7F74031C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZUMail%366D7F74031C.implementation preserve=yes
      //## end ZUMail%366D7F74031C.implementation

};

//## begin ZUMail%366D7F74031C.postscript preserve=yes
//## end ZUMail%366D7F74031C.postscript

// Class ZUMail 

//## begin module%366D7F640200.epilog preserve=yes
//## end module%366D7F640200.epilog


#endif
