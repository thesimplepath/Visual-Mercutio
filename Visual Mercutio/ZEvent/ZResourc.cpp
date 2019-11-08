//## begin module%374C3A9E019A.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%374C3A9E019A.cm

//## begin module%374C3A9E019A.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%374C3A9E019A.cp

//## Module: ZResourc%374C3A9E019A; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZResourc.cpp

//## begin module%374C3A9E019A.additionalIncludes preserve=no
//## end module%374C3A9E019A.additionalIncludes

//## begin module%374C3A9E019A.includes preserve=yes
#include <StdAfx.h>
//## end module%374C3A9E019A.includes

// ZResourc
#include "ZResourc.h"
//## begin module%374C3A9E019A.declarations preserve=no
//## end module%374C3A9E019A.declarations

//## begin module%374C3A9E019A.additionalDeclarations preserve=yes
#include "zRes32\ZRes.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "zBaseLib\PSS_Tokenizer.h"

#include "ZProcess.h"


IMPLEMENT_DYNAMIC(ZBResources, CObject)
//## end module%374C3A9E019A.additionalDeclarations


// Class ZBResources 



ZBResources::ZBResources()
  //## begin ZBResources::ZBResources%.hasinit preserve=no
      : m_UserType(Users)
  //## end ZBResources::ZBResources%.hasinit
  //## begin ZBResources::ZBResources%.initialization preserve=yes
  //## end ZBResources::ZBResources%.initialization
{
  //## begin ZBResources::ZBResources%.body preserve=yes
  //## end ZBResources::ZBResources%.body
}

ZBResources::ZBResources(const ZBResources &right)
  //## begin ZBResources::ZBResources%copy.hasinit preserve=no
      : m_UserType(Users)
  //## end ZBResources::ZBResources%copy.hasinit
  //## begin ZBResources::ZBResources%copy.initialization preserve=yes
  //## end ZBResources::ZBResources%copy.initialization
{
  //## begin ZBResources::ZBResources%copy.body preserve=yes
    *this = right;
  //## end ZBResources::ZBResources%copy.body
}


ZBResources::~ZBResources()
{
  //## begin ZBResources::~ZBResources%.body preserve=yes
  //## end ZBResources::~ZBResources%.body
}


const ZBResources & ZBResources::operator=(const ZBResources &right)
{
  //## begin ZBResources::operator=%.body preserve=yes
      for (size_t i = 0; i < right.GetUserCount(); ++i)
          AddUser( right.GetUserAt(i) );
    m_UserType = right.m_UserType;
    return *this;
  //## end ZBResources::operator=%.body
}



//## Other Operations (implementation)
CArchive& operator >> (CArchive& ar, ZBResources& ActivityResource)
{
  //## begin ZBResources::operator >>%927742723.body preserve=yes
       WORD    wValue;
    ar >> wValue;
    ActivityResource.m_UserType = (ActivityUserType)wValue;

    ActivityResource.m_UserArray.Serialize( ar );
    return ar;
  //## end ZBResources::operator >>%927742723.body
}

CArchive& operator << (CArchive& ar, const ZBResources& ActivityResource)
{
    ar << WORD(ActivityResource.m_UserType);
    const_cast<ZBResources&>(ActivityResource).m_UserArray.Serialize(ar);
    return ar;
}

void ZBResources::AddUser (const CString UserName)
{
  //## begin ZBResources::AddUser%927742725.body preserve=yes
      if (UserExist( UserName ))
          return;
    m_UserArray.Add( UserName );
  //## end ZBResources::AddUser%927742725.body
}

BOOL ZBResources::RemoveUser (const CString& UserName)
{
  //## begin ZBResources::RemoveUser%927742726.body preserve=yes
      for (size_t i = 0; i < GetUserCount(); ++i)
          if (GetUserAt(i) == UserName)
          {
              m_UserArray.RemoveAt(i);
              return TRUE;
          }
      return FALSE;
  //## end ZBResources::RemoveUser%927742726.body
}

BOOL ZBResources::UserExist (const CString& UserName)
{
  //## begin ZBResources::UserExist%927742727.body preserve=yes
      for (size_t i = 0; i < GetUserCount(); ++i)
          if (GetUserAt(i) == UserName)
              return TRUE;
      return FALSE;
  //## end ZBResources::UserExist%927742727.body
}

PSS_MailUserList* ZBResources::CreatePersonList (ZProcess* pMainProcess, const PSS_UserManager& UserManager, const CString& ConnectedUser)
{
  //## begin ZBResources::CreatePersonList%927742730.body preserve=yes
    // If responsible requested
    if (GetUserType() == ResponsibleOfUser)
    {
        // Search the connected user
        PSS_User* pUser = UserManager.FindUser ( ConnectedUser );
        if (pUser)
        {
            PSS_MailUserList*    pPersonList = new PSS_MailUserList;
            // Search the corresponding responsible user ptr
            pUser = UserManager.FindUser ( pUser->GetResponsible() );
            if (pUser)
            {
                pPersonList->AddPerson( *pUser );
                return pPersonList;
            }
        }
    }
    else
        // If user of an activity requested
        if (GetUserType() == UserFromActivity)
        {
            if (GetUserCount() > 0 && pMainProcess)
            {
                CString    ActivityName = GetUserAt(0);
                if (ActivityName.IsEmpty())
                    return NULL;
                ZBaseActivity* pActivity = pMainProcess->FindBaseActivity( ActivityName );
                if (!pActivity)
                    return NULL;
                // Return the initiator if the activity has been done.
                if (!pActivity->GetInitiator().IsEmpty())
                {
                    PSS_MailUserList*    pPersonList = new PSS_MailUserList;
                    pPersonList->AddPerson( pActivity->GetInitiator() );
                    return pPersonList;
                }
                else
                {
                    // Return the person list of the activity.
                    return pActivity->ActivityCreatePersonList( UserManager, ConnectedUser );
                }
            }
        }
        else
            if (GetUserCount())
            {
                PSS_MailUserList*    pPersonList = new PSS_MailUserList;
                // Run through the user list and build the person
                for (size_t i = 0; i < GetUserCount(); ++i)
                {
                    PSS_User* pUser = UserManager.FindUser ( GetUserAt(i) );
                    // If the user is found add the user,
                    // otherwise add directly the string
                    if (pUser)
                        pPersonList->AddPerson( *pUser );
                    else
                        pPersonList->AddPerson( GetUserAt(i) );
                }
                // OK
                return pPersonList;
            }
    return NULL;
  //## end ZBResources::CreatePersonList%927742730.body
}

BOOL ZBResources::FillPersonArray(ZProcess* pMainProcess, const PSS_UserManager& UserManager, CStringArray& UserArray, CString ConnectedUser)
{
  //## begin ZBResources::FillPersonArray%927742731.body preserve=yes
    // If responsible requested
    if (GetUserType() == ResponsibleOfUser)
    {
        // Search the connected user
        PSS_User* pUser = UserManager.FindUser ( ConnectedUser );
        if (pUser)
        {
            UserArray.RemoveAll();
            // Search the corresponding responsible user ptr
            pUser = UserManager.FindUser ( pUser->GetResponsible() );
            if (pUser)
            {
                UserArray.Add( pUser->GetUserName() );
                return TRUE;
            }
        }
    }
    else
        // If user of an activity requested
        if (GetUserType() == UserFromActivity)
        {
            if (GetUserCount() > 0 && pMainProcess)
            {
                CString    ActivityName = GetUserAt(0);
                if (ActivityName.IsEmpty())
                    return FALSE;
                ZBaseActivity* pActivity = pMainProcess->FindBaseActivity( ActivityName );
                if (!pActivity)
                    return FALSE;
                // Return the initiator if the activity has been done.
                if (!pActivity->GetInitiator().IsEmpty())
                {
                    UserArray.RemoveAll();
                    UserArray.Add( pActivity->GetInitiator() );
                    return TRUE;
                }
                else
                    // Return the resource of the activity.
                    return pActivity->ActivityFillPersonArray( UserManager, UserArray, ConnectedUser );
            }
        }
        else
            if (GetUserCount())
            {
                UserArray.RemoveAll();
                // Run through the user list and build the person
                for (size_t i = 0; i < GetUserCount(); ++i)
                {
                    PSS_User* pUser = UserManager.FindUser ( GetUserAt(i) );
                    // If the user is found add the user,
                    // otherwise add directly the string
                    if (pUser)
                        UserArray.Add( pUser->GetUserName() );
                    else
                        UserArray.Add( GetUserAt(i) );
                }
                // OK
                return TRUE;
            }
    return FALSE;
  //## end ZBResources::FillPersonArray%927742731.body
}

BOOL ZBResources::AddUsers (CString DelimiterString)
{
    // Run through the user delimiter string and build the person
    PSS_Tokenizer    Tokenizer( ';' );
    CString    Token = Tokenizer.GetFirstToken( DelimiterString );
    while (!Token.IsEmpty())
    {
        AddUser( Token );
        // Next token
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

CString ZBResources::CreatePersonDelimStr (ZProcess* pMainProcess, const PSS_UserManager& UserManager, const CString& ConnectedUser, const CString& Delimiter)
{
  //## begin ZBResources::CreatePersonDelimStr%927742732.body preserve=yes
    // If responsible requested
    if (GetUserType() == ResponsibleOfUser)
    {
        // Search the connected user
        PSS_User* pUser = UserManager.FindUser ( ConnectedUser );
        if (pUser)
        {
            // Search the corresponding responsible user ptr
            pUser = UserManager.FindUser ( pUser->GetResponsible() );
            if (pUser)
                return pUser->GetUserName();
        }
    }
    else
        // If user of an activity requested
        if (GetUserType() == UserFromActivity)
        {
            if (GetUserCount() > 0 && pMainProcess)
            {
                CString    ActivityName = GetUserAt(0);
                if (ActivityName.IsEmpty())
                    return "";
                ZBaseActivity* pActivity = pMainProcess->FindBaseActivity( ActivityName );
                if (!pActivity)
                    return "";
                // Return the initiator if the activity has been done.
                if (!pActivity->GetInitiator().IsEmpty())
                    return pActivity->GetInitiator();
                else
                    // Return the resource of the activity.
                    return pActivity->ActivityCreatePersonDelimStr( UserManager, ConnectedUser, Delimiter );
            }
        }
        else
            if (GetUserCount())
            {
                  CString    ReceiverString;
                // Run through the user list and build the person
                for (size_t i = 0; i < GetUserCount(); ++i)
                {
                    PSS_User* pUser = UserManager.FindUser ( GetUserAt(i) );
                    // If the user is found add the user,
                    // otherwise add directly the string
                    if (pUser)
                    {
                        // Build the string with trailing char
                        ReceiverString += pUser->GetUserName();
                        ReceiverString += Delimiter;
                    }
                    else
                    {
                        ReceiverString += GetUserAt(i);
                        ReceiverString += Delimiter;
                    }
                }
                // Remove the last trail char
                ReceiverString = ReceiverString.Left( ReceiverString.GetLength() - Delimiter.GetLength() );
                // OK
                return ReceiverString;
            }
    return "";
  //## end ZBResources::CreatePersonDelimStr%927742732.body
}

ZBResources* ZBResources::Clone ()
{
  //## begin ZBResources::Clone%927742733.body preserve=yes
    ZBResources*    pResources = new ZBResources( *this );
    return pResources;
  //## end ZBResources::Clone%927742733.body
}

// Additional Declarations
  //## begin ZBResources%374C378F0049.declarations preserve=yes
  //## end ZBResources%374C378F0049.declarations

//## begin module%374C3A9E019A.epilog preserve=yes
//## end module%374C3A9E019A.epilog
