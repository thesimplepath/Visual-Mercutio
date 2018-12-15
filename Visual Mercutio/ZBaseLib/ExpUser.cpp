//## begin module%36F7BD2B03A2.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36F7BD2B03A2.cm

//## begin module%36F7BD2B03A2.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36F7BD2B03A2.cp

//## Module: ExpUser%36F7BD2B03A2; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ExpUser.cpp

//## begin module%36F7BD2B03A2.additionalIncludes preserve=no
//## end module%36F7BD2B03A2.additionalIncludes

//## begin module%36F7BD2B03A2.includes preserve=yes
#include <StdAfx.h>
//## end module%36F7BD2B03A2.includes

// ExpUser
#include "ExpUser.h"
//## begin module%36F7BD2B03A2.declarations preserve=no
//## end module%36F7BD2B03A2.declarations

//## begin module%36F7BD2B03A2.additionalDeclarations preserve=yes
#include "ZBTokenizer.h"
//## end module%36F7BD2B03A2.additionalDeclarations


// Class ZUUserExport 


ZUUserExport::ZUUserExport (CString Filename, ZUUserManager* pUserManager, BOOL GenerateHeader, SynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
  //## begin ZUUserExport::ZUUserExport%922203348.hasinit preserve=no
  //## end ZUUserExport::ZUUserExport%922203348.hasinit
  //## begin ZUUserExport::ZUUserExport%922203348.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
      m_pUserManager( pUserManager )
  //## end ZUUserExport::ZUUserExport%922203348.initialization
{
  //## begin ZUUserExport::ZUUserExport%922203348.body preserve=yes
  //## end ZUUserExport::ZUUserExport%922203348.body
}


ZUUserExport::~ZUUserExport()
{
  //## begin ZUUserExport::~ZUUserExport%.body preserve=yes
  //## end ZUUserExport::~ZUUserExport%.body
}



//## Other Operations (implementation)
CString ZUUserExport::GetExportedLine (CObject* pObj)
{
  //## begin ZUUserExport::GetExportedLine%922203349.body preserve=yes
    ZUser    *pUser = (ZUser*)pObj;
    ZBTokenizer    Tokenizer;

    switch (GetSeparatorType())
    {
        case CommaSeparator :
        {
            Tokenizer.SetSeparator( ',' );
            break;
        }
        case SemiColumnSeparator :
        {
            Tokenizer.SetSeparator( ';' );
            break;
        }
        case AutomaticSeparator :     
        case TabSeparator :    
        default:
        {
            Tokenizer.SetSeparator( '\t' );
            break;
        }
    }
    // Add the user name
    Tokenizer.AddToken( pUser->GetUserName() );
    // Add the description
    Tokenizer.AddToken( pUser->GetDescription() );
    // Add the email address
    Tokenizer.AddToken( pUser->GetMailAddress() );
    // Add the responsible name
    Tokenizer.AddToken( pUser->GetResponsible() );
    // Add the departement
    Tokenizer.AddToken( pUser->GetDepartement() );
    // Add the admin flag
    Tokenizer.AddToken( (pUser->IsAdministrator()) ? "1" : "0" );
    // Add the display username
    Tokenizer.AddToken( pUser->GetDisplayName() );

    Tokenizer.AddToken( "\r\n" );
    return Tokenizer.GetString();
  //## end ZUUserExport::GetExportedLine%922203349.body
}

BOOL ZUUserExport::ProcessLine (CString Line)
{
  //## begin ZUUserExport::ProcessLine%922203351.body preserve=yes
      // The line we received is exactly the same we exported
    CString    User;
    CString    Email;
    CString    Responsible;
    CString Description;
    CString    Departement;
    CString    DisplayName;
    BOOL    IsAdministrator = FALSE;    // False by default

    ZBTokenizer    Tokenizer;

    switch (GetSeparatorType())
    {
        case CommaSeparator :
        {
            Tokenizer.SetSeparator( ',' );
            break;
        }
        case SemiColumnSeparator :
        {
            Tokenizer.SetSeparator( ';' );
            break;
        }
        case AutomaticSeparator :     
        case TabSeparator :    
        default:
        {
            Tokenizer.SetSeparator( '\t' );
            break;
        }
    }

      // Extract the user
    User = Tokenizer.GetFirstToken( Line );
    // If no user, end
    if (User.IsEmpty())
        return FALSE;
      // Extract the description
    Description = Tokenizer.GetNextToken();
      // Extract the email
    Email = Tokenizer.GetNextToken();
      // Extract the responsible name
    Responsible = Tokenizer.GetNextToken();
      // Extract the departement
    Departement = Tokenizer.GetNextToken();
      // Extract the admin flag
    CString    AdminString = Tokenizer.GetNextToken();
    if (AdminString == "1")
        IsAdministrator = TRUE;
      // Extract the display name
    DisplayName = Tokenizer.GetNextToken();

    // Call the user manager
    if (m_pUserManager)
        m_pUserManager->AddUser( User, Email, Description, Responsible, Departement, IsAdministrator, DisplayName );
    return TRUE;      
  //## end ZUUserExport::ProcessLine%922203351.body
}

CString ZUUserExport::GetHeaderLine ()
{
  //## begin ZUUserExport::GetHeaderLine%922203352.body preserve=yes
    ZBTokenizer    Tokenizer;

    switch (GetSeparatorType())
    {
        case CommaSeparator :
        {
            Tokenizer.SetSeparator( ',' );
            break;
        }
        case SemiColumnSeparator :
        {
            Tokenizer.SetSeparator( ';' );
            break;
        }
        case AutomaticSeparator :     
        case TabSeparator :    
        default:
        {
            Tokenizer.SetSeparator( '\t' );
            break;
        }
    }
    // Add the user name
    Tokenizer.AddToken( "UserName" );
    // Add the description
    Tokenizer.AddToken( "UserDescription" );
    // Add the email address
    Tokenizer.AddToken( "EMailAddress" );
    // Add the responsible name
    Tokenizer.AddToken( "ResponsibleUser" );
    // Add the departement
    Tokenizer.AddToken( "Departement" );
    // Add the admin flag
    Tokenizer.AddToken( "Administrator" );
    // Add the fullname
    Tokenizer.AddToken( "DisplayName" );

    Tokenizer.AddToken( "\r\n" );
    return Tokenizer.GetString();
  //## end ZUUserExport::GetHeaderLine%922203352.body
}

BOOL ZUUserExport::Import ()
{
  //## begin ZUUserExport::Import%922203353.body preserve=yes
      return ZUExport::Import();
  //## end ZUUserExport::Import%922203353.body
}

BOOL ZUUserExport::Export ()
{
  //## begin ZUUserExport::Export%922203354.body preserve=yes
      return ZUExport::Export();
  //## end ZUUserExport::Export%922203354.body
}

double ZUUserExport::ForecastedTotalObject ()
{
  //## begin ZUUserExport::ForecastedTotalObject%922203369.body preserve=yes
    // Call the user manager
    if (m_pUserManager)
        return m_pUserManager->GetCount();
    return 1;
  //## end ZUUserExport::ForecastedTotalObject%922203369.body
}

BOOL ZUUserExport::DoExportLoop ()
{
  //## begin ZUUserExport::DoExportLoop%922203370.body preserve=yes
    // Call the user manager
    if (!m_pUserManager)
        return FALSE;
    CString Line;
    for (int i = 0; i < m_pUserManager->GetCount(); ++i)
    {
        Line = GetExportedLine( (CObject*)m_pUserManager->GetAt(i) );
        WriteLine ( Line );

    }
      return TRUE;
  //## end ZUUserExport::DoExportLoop%922203370.body
}

BOOL ZUUserExport::PreImport ()
{
  //## begin ZUUserExport::PreImport%922203371.body preserve=yes
    // Call the user manager
    if (m_pUserManager)
        m_pUserManager->RemoveAllUsers();
    return TRUE;
  //## end ZUUserExport::PreImport%922203371.body
}

// Additional Declarations
  //## begin ZUUserExport%36F7BC4003CD.declarations preserve=yes
  //## end ZUUserExport%36F7BC4003CD.declarations

//## begin module%36F7BD2B03A2.epilog preserve=yes
//## end module%36F7BD2B03A2.epilog
