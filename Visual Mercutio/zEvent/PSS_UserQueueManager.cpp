/****************************************************************************
 * ==> PSS_UserQueueManager ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user queue manager                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserQueueManager.h"

// std
#include <memory>

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_UserQueueManager
//---------------------------------------------------------------------------
PSS_UserQueueManager::PSS_UserQueueManager()
{}
//---------------------------------------------------------------------------
PSS_UserQueueManager::PSS_UserQueueManager(const PSS_UserQueueManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserQueueManager::~PSS_UserQueueManager()
{}
//---------------------------------------------------------------------------
const PSS_UserQueueManager& PSS_UserQueueManager::operator = (const PSS_UserQueueManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::Create(const CString& directory)
{
    m_Directory = directory;

    // make the queue directory in lower case
    m_Directory.MakeLower();

    return m_UserDirectoryManager.SetDirectory(directory);
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_UserQueueManager::DispatchToUserQueue(const CString& fileName)
{
    PSS_ActivityEvent* pActivityEvent = static_cast<PSS_ActivityEvent*>(m_ActivityEventFile.ImportActivityFromFile(fileName));

    if (!pActivityEvent)
        return NULL;

    TRACE1("DISPATCH TO USER QUEUE IN WITH FILENAME = %s\n", (const char*)fileName);

    // check the senders and receivers directory structure
    if (!CheckDirectory(*pActivityEvent))
        return NULL;

    // in case of log, do nothing
    if (pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IEType::IE_AT_LogEvent)
        return pActivityEvent;

    if (pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IEType::IE_AT_DeleteToDoEvent)
    {
        ProceedDeleteMessage(*pActivityEvent);
        return pActivityEvent;
    }

    // create a new event and and place it to the receiver queue
    ForwardToUserQueue(*pActivityEvent);

    if (pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IEType::IE_AT_ToDo)
        // remove the old event from the sender queue, if exists
        RemoveAssociatedEventFromUserQueue(*pActivityEvent);

    return pActivityEvent;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveEventFromUserQueue(const PSS_ActivityEvent& activityEvent, const CString& user)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(user);

    // for multi-user mode, iterate through all users
    while (!token.IsEmpty())
    {
        if (!RemoveFromUserQueue(activityEvent, token))
            return FALSE;

        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveEventFromReceiverQueue(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetReceiver());

    // for multi-user mode, iterate through all receiver
    while (!token.IsEmpty())
    {
        if (!RemoveFromUserQueue(activityEvent, token))
            return FALSE;

        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveEventFromSenderQueue(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetSender());

    // for multi-user mode, iterate through all senders
    while (!token.IsEmpty())
    {
        if (!RemoveFromUserQueue(activityEvent, token))
            return FALSE;

        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::ForwardToUserQueue(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetReceiver());

    // for multi-user mode, iterate through all receivers
    while (!token.IsEmpty())
    {
        const CString fileName =
                BuildUserActivityEventFileName(activityEvent.GetFileName() + activityEvent.GetFileExtension(), token);
        m_ActivityEventFile.ExportActivityToFile(fileName, const_cast<PSS_ActivityEvent*>(&activityEvent));
        TRACE("FORWARDED TO USER QUEUE\n");
        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveFromUserQueue(const PSS_ActivityEvent& activityEvent, const CString& user)
{
    return RemoveEventFileName(BuildUserActivityEventFileName(activityEvent.GetFileName() + activityEvent.GetFileExtension(), user));
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveAssociatedEventFromUserQueue(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetSender());

    // for multi-user mode, iterate through all senders
    while (!token.IsEmpty())
    {
        const CString fileName = BuildUserActivityEventFileName(activityEvent.GetFileName() +
                                                                activityEvent.GetFileExtension((int)PSS_ActivityEvent::IEType::IE_AT_ToDo),
                                                                token);

        // import file first
        PSS_ActivityEvent* pActivityEvent = static_cast<PSS_ActivityEvent*>(m_ActivityEventFile.ImportActivityFromFile(fileName));

        // if it's a todo activity, therefore remove the associated message
        if (pActivityEvent                                                                  &&
            pActivityEvent->GetActivityEventType() == PSS_ActivityEvent::IEType::IE_AT_ToDo &&
            token != pActivityEvent->GetSender())
        {
            TRACE("REMOVE ASSIOCIATED EVENT\n");
            RemoveEventFileName(fileName);
        }

        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::CheckDirectory(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetSender());

    // for multi-user mode, iterate through all senders
    while (!token.IsEmpty())
    {
        if (!m_UserDirectoryManager.UserExist(token))
            m_UserDirectoryManager.CreateUser(token);

        token = tokenizer.GetNextToken();
    }

    token = tokenizer.GetFirstToken(activityEvent.GetReceiver());

    // for multi-user mode, iterate through all receivers
    while (!token.IsEmpty())
    {
        if (!m_UserDirectoryManager.UserExist(token))
            m_UserDirectoryManager.CreateUser(token);

        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::ProceedDeleteMessage(const PSS_ActivityEvent& activityEvent)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(activityEvent.GetReceiver());

    // for multi-user mode, iterate through all senders
    while (!token.IsEmpty())
    {
        const CString fileName = BuildUserActivityEventFileName(activityEvent.GetFileName() +
                                                                activityEvent.GetFileExtension((int)PSS_ActivityEvent::IEType::IE_AT_ToDo),
                                                                token);
        RemoveEventFileName(fileName);
        token = tokenizer.GetNextToken();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_UserQueueManager::BuildUserActivityEventFileName(const CString& fileName, const CString& user)
{
    return m_UserDirectoryManager.BuildUserDirectory(user) + "\\" + fileName;
}
//---------------------------------------------------------------------------
BOOL PSS_UserQueueManager::RemoveEventFileName(const CString& fileName)
{
    CFileStatus status;

    // check if the file exists
    if (CFile::GetStatus(fileName, status))
        // physically remove the file
        for (int i = 0; i < 10; ++i)
            TRY
            {
                CFile::Remove(fileName);
                TRACE1("FILENAME REMOVED %s\n", (const char*)fileName);
                return TRUE;
            }
            CATCH (CFileException, e)
            {
                ::Sleep(100);
            }
            END_CATCH

    TRACE1("PROBLEM REMOVEING FILENAME %s\n", (const char*)fileName);
    return FALSE;
}
//---------------------------------------------------------------------------
