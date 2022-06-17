/****************************************************************************
 * ==> PSS_UserExport ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an interface to import and export the user table  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserExport.h"

// processsoft
#include "PSS_Tokenizer.h"

//---------------------------------------------------------------------------
// PSS_UserExport
//---------------------------------------------------------------------------
PSS_UserExport::PSS_UserExport(const CString&                fileName,
                               PSS_UserManager*              pUserManager,
                               BOOL                          generateHeader,
                               ESynchronizationSeparatorType separatorType,
                               const CString&                schema,
                               int                           propagationMode,
                               BOOL                          emptyWhenZero,
                               PSS_StatusBar*                pStatusBar) :
    PSS_Export(fileName, generateHeader, separatorType, schema, propagationMode, emptyWhenZero, pStatusBar),
    m_pUserManager(pUserManager)
{}
//---------------------------------------------------------------------------
PSS_UserExport::PSS_UserExport(const PSS_UserExport& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserExport::~PSS_UserExport()
{}
//---------------------------------------------------------------------------
const PSS_UserExport& PSS_UserExport::operator = (const PSS_UserExport& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
CString PSS_UserExport::GetExportedLine(CObject* pObj)
{
    PSS_User*     pUser = (PSS_User*)pObj;
    PSS_Tokenizer tokenizer;

    switch (GetSeparatorType())
    {
        case ESynchronizationSeparatorType::E_SS_Comma:     tokenizer.SetSeparator(',');  break;
        case ESynchronizationSeparatorType::E_SS_Semicolon: tokenizer.SetSeparator(';');  break;
        default:                                            tokenizer.SetSeparator('\t'); break;
    }

    // add the user name
    tokenizer.AddToken(pUser->GetUserName());

    // add the description
    tokenizer.AddToken(pUser->GetDescription());

    // add the email address
    tokenizer.AddToken(pUser->GetMailAddress());

    // add the responsible name
    tokenizer.AddToken(pUser->GetResponsible());

    // add the departement
    tokenizer.AddToken(pUser->GetDepartement());

    // add the admin flag
    tokenizer.AddToken(pUser->IsAdministrator() ? _T("1") : _T("0"));

    // add the display username
    tokenizer.AddToken(pUser->GetDisplayName());

    tokenizer.AddToken(_T("\r\n"));

    return tokenizer.GetString();
}
//---------------------------------------------------------------------------
BOOL PSS_UserExport::ProcessLine(const CString& line)
{
    // the line we received is exactly the same we exported
    PSS_Tokenizer tokenizer;

    switch (GetSeparatorType())
    {
        case ESynchronizationSeparatorType::E_SS_Comma:     tokenizer.SetSeparator(',');  break;
        case ESynchronizationSeparatorType::E_SS_Semicolon: tokenizer.SetSeparator(';');  break;
        default:                                            tokenizer.SetSeparator('\t'); break;
    }

    // extract the user
    const CString user = tokenizer.GetFirstToken(line);

    // if no user, end
    if (user.IsEmpty())
        return FALSE;

    // extract the description
    const CString description = tokenizer.GetNextToken();

    // extract the email
    const CString email = tokenizer.GetNextToken();

    // extract the responsible name
    const CString responsible = tokenizer.GetNextToken();

    // extract the departement
    const CString departement = tokenizer.GetNextToken();

    // extract the admin flag
    const CString adminString     = tokenizer.GetNextToken();
    const BOOL    isAdministrator = (adminString == _T("1"));

    // extract the display name
    const CString displayName = tokenizer.GetNextToken();

    // call the user manager
    if (m_pUserManager)
        m_pUserManager->AddUser(user, email, description, responsible, departement, isAdministrator, displayName);

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_UserExport::GetHeaderLine()
{
    PSS_Tokenizer tokenizer;

    switch (GetSeparatorType())
    {
        case ESynchronizationSeparatorType::E_SS_Comma:     tokenizer.SetSeparator(',');  break;
        case ESynchronizationSeparatorType::E_SS_Semicolon: tokenizer.SetSeparator(';');  break;
        default:                                            tokenizer.SetSeparator('\t'); break;
    }

    // add the user name
    tokenizer.AddToken(_T("UserName"));

    // add the description
    tokenizer.AddToken(_T("UserDescription"));

    // add the email address
    tokenizer.AddToken(_T("EMailAddress"));

    // add the responsible name
    tokenizer.AddToken(_T("ResponsibleUser"));

    // add the departement
    tokenizer.AddToken(_T("Departement"));

    // add the admin flag
    tokenizer.AddToken(_T("Administrator"));

    // add the full name
    tokenizer.AddToken(_T("DisplayName"));

    tokenizer.AddToken(_T("\r\n"));

    return tokenizer.GetString();
}
//---------------------------------------------------------------------------
BOOL PSS_UserExport::Export()
{
    return PSS_Export::Export();
}
//---------------------------------------------------------------------------
BOOL PSS_UserExport::Import()
{
    return PSS_Export::Import();
}
//---------------------------------------------------------------------------
double PSS_UserExport::GetForecastedTotalObject() const
{
    if (m_pUserManager)
        return m_pUserManager->GetCount();

    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_UserExport::DoExportLoop()
{
    if (!m_pUserManager)
        return FALSE;

    CString   line;
    const int userCount = m_pUserManager->GetCount();

    for (int i = 0; i < userCount; ++i)
    {
        line = GetExportedLine(m_pUserManager->GetAt(i));
        WriteLine(line);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserExport::PreImport()
{
    if (m_pUserManager)
        m_pUserManager->RemoveAllUsers();

    return TRUE;
}
//---------------------------------------------------------------------------
