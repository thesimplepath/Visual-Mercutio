/****************************************************************************
 * ==> PSS_ActivityResources -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the resources for an activity                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityResources.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "PSS_Process.h"

// resources
#include "zRes32\ZRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ActivityResources, CObject)
//---------------------------------------------------------------------------
// PSS_ActivityResources
//---------------------------------------------------------------------------
PSS_ActivityResources::PSS_ActivityResources() :
    CObject(),
    m_UserType(IEUserType::IE_UT_Users)
{}
//---------------------------------------------------------------------------
PSS_ActivityResources::PSS_ActivityResources(const PSS_ActivityResources& other) :
    CObject(),
    m_UserType(IEUserType::IE_UT_Users)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ActivityResources::~PSS_ActivityResources()
{}
//---------------------------------------------------------------------------
const PSS_ActivityResources& PSS_ActivityResources::operator = (const PSS_ActivityResources& other)
{
    m_UserType = other.m_UserType;

    const std::size_t userCount = other.GetUserCount();

    for (std::size_t i = 0; i < userCount; ++i)
        AddUser(other.GetUserAt(i));

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_ActivityResources& ActivityResource)
{
    WORD wValue;
    ar >> wValue;
    ActivityResource.m_UserType = PSS_ActivityResources::IEUserType(wValue);

    ActivityResource.m_UserArray.Serialize(ar);
    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_ActivityResources& ActivityResource)
{
    ar << WORD(ActivityResource.m_UserType);
    const_cast<PSS_ActivityResources&>(ActivityResource).m_UserArray.Serialize(ar);
    return ar;
}
//---------------------------------------------------------------------------
PSS_ActivityResources* PSS_ActivityResources::Clone()
{
    return new PSS_ActivityResources(*this);
}
//---------------------------------------------------------------------------
void PSS_ActivityResources::AddUser(const CString& userName)
{
    if (UserExist(userName))
        return;

    m_UserArray.Add(userName);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityResources::AddUsers(const CString& userNames)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(userNames);

    // iterate through the user delimiter string and build the persons
    while (!token.IsEmpty())
    {
        AddUser(token);

        // next token
        token = tokenizer.GetNextToken();
    }
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityResources::RemoveUser(const CString& userName)
{
    const std::size_t userCount = GetUserCount();

    for (std::size_t i = 0; i < userCount; ++i)
        if (GetUserAt(i) == userName)
        {
            m_UserArray.RemoveAt(i);
            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityResources::UserExist(const CString& userName) const
{
    const std::size_t userCount = GetUserCount();

    for (std::size_t i = 0; i < userCount; ++i)
        if (GetUserAt(i) == userName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_ActivityResources::CreatePersonList(PSS_Process*           pMainProcess,
                                                          const PSS_UserManager& userManager,
                                                          const CString&         connectedUser)
{
    // responsible requested?
    if (GetUserType() == IEUserType::IE_UT_ResponsibleOfUser)
    {
        // search the connected user
        PSS_User* pUser = userManager.FindUser(connectedUser);

        if (pUser)
        {
            std::unique_ptr<PSS_MailUserList> pPersonList(new PSS_MailUserList());

            // search the matching responsible user
            pUser = userManager.FindUser(pUser->GetResponsible());

            if (pUser)
            {
                pPersonList->AddPerson(*pUser);
                return pPersonList.release();
            }
        }
    }
    else
    // if user of an activity requested
    if (GetUserType() == IEUserType::IE_UT_UserFromActivity)
    {
        if (GetUserCount() > 0 && pMainProcess)
        {
            const CString activityName = GetUserAt(0);

            if (activityName.IsEmpty())
                return NULL;

            PSS_BaseActivity* pActivity = pMainProcess->FindBaseActivity(activityName);

            if (!pActivity)
                return NULL;

            // get the initiator if the activity has been done
            if (!pActivity->GetInitiator().IsEmpty())
            {
                std::unique_ptr<PSS_MailUserList> pPersonList(new PSS_MailUserList());
                pPersonList->AddPerson(pActivity->GetInitiator());
                return pPersonList.release();
            }

            // get activity the person list
            return pActivity->ActivityCreatePersonList(userManager, connectedUser);
        }
    }
    else
    if (GetUserCount())
    {
        std::unique_ptr<PSS_MailUserList> pPersonList(new PSS_MailUserList());
        const std::size_t userCount = GetUserCount();

        // iterate through the user list and build the person
        for (std::size_t i = 0; i < userCount; ++i)
        {
            PSS_User* pUser = userManager.FindUser(GetUserAt(i));

            // if the user was found, add it, otherwise add the string directly
            if (pUser)
                pPersonList->AddPerson(*pUser);
            else
                pPersonList->AddPerson(GetUserAt(i));
        }

        return pPersonList.release();
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityResources::FillPersonArray(PSS_Process*           pMainProcess,
                                            const PSS_UserManager& userManager,
                                            CStringArray&          userArray,
                                            const CString&         connectedUser)
{
    // responsible requested?
    if (GetUserType() == IEUserType::IE_UT_ResponsibleOfUser)
    {
        // search the connected user
        PSS_User* pUser = userManager.FindUser(connectedUser);

        if (pUser)
        {
            userArray.RemoveAll();

            // search the matching responsible user ptr
            pUser = userManager.FindUser(pUser->GetResponsible());

            if (pUser)
            {
                userArray.Add(pUser->GetUserName());
                return TRUE;
            }
        }
    }
    else
    // if user of an activity requested
    if (GetUserType() == IEUserType::IE_UT_UserFromActivity)
    {
        if (GetUserCount() > 0 && pMainProcess)
        {
            const CString activityName = GetUserAt(0);

            if (activityName.IsEmpty())
                return FALSE;

            PSS_BaseActivity* pActivity = pMainProcess->FindBaseActivity(activityName);

            if (!pActivity)
                return FALSE;

            // get the initiator if the activity has been done
            if (!pActivity->GetInitiator().IsEmpty())
            {
                userArray.RemoveAll();
                userArray.Add(pActivity->GetInitiator());
                return TRUE;
            }

            // get the resource of the activity
            return pActivity->ActivityFillPersonArray(userManager, userArray, connectedUser);
        }
    }
    else
    if (GetUserCount())
    {
        userArray.RemoveAll();

        const std::size_t userCount = GetUserCount();

        // iterate through the user list and build the person
        for (std::size_t i = 0; i < userCount; ++i)
        {
            PSS_User* pUser = userManager.FindUser(GetUserAt(i));

            // if the user is found, add it, otherwise add the string directly
            if (pUser)
                userArray.Add(pUser->GetUserName());
            else
                userArray.Add(GetUserAt(i));
        }

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_ActivityResources::CreatePersonDelimStr(PSS_Process*           pMainProcess,
                                                    const PSS_UserManager& userManager,
                                                    const CString&         connectedUser,
                                                    const CString&         delimiter)
{
    // responsible requested?
    if (GetUserType() == IEUserType::IE_UT_ResponsibleOfUser)
    {
        // search the connected user
        PSS_User* pUser = userManager.FindUser(connectedUser);

        if (pUser)
        {
            // search the matching responsible user
            pUser = userManager.FindUser(pUser->GetResponsible());

            if (pUser)
                return pUser->GetUserName();
        }
    }
    else
    // if user of an activity requested
    if (GetUserType() == IEUserType::IE_UT_UserFromActivity)
    {
        if (GetUserCount() > 0 && pMainProcess)
        {
            const CString activityName = GetUserAt(0);

            if (activityName.IsEmpty())
                return "";

            PSS_BaseActivity* pActivity = pMainProcess->FindBaseActivity(activityName);

            if (!pActivity)
                return "";

            // get the initiator if the activity has been done
            if (!pActivity->GetInitiator().IsEmpty())
                return pActivity->GetInitiator();

            // get the resource of the activity
            return pActivity->ActivityCreatePersonDelimStr(userManager, connectedUser, delimiter);
        }
    }
    else
    if (GetUserCount())
    {
        const std::size_t userCount = GetUserCount();
        CString           receiverString;

        // iterate through the user list and build the person
        for (std::size_t i = 0; i < userCount; ++i)
        {
            PSS_User* pUser = userManager.FindUser(GetUserAt(i));

            // if the user is found, add it, otherwise add directly the string
            if (pUser)
            {
                // build the string with trailing char
                receiverString += pUser->GetUserName();
                receiverString += delimiter;
            }
            else
            {
                receiverString += GetUserAt(i);
                receiverString += delimiter;
            }
        }

        // remove the last trail char
        receiverString = receiverString.Left(receiverString.GetLength() - delimiter.GetLength());

        return receiverString;
    }

    return "";
}
//---------------------------------------------------------------------------
