// Source file: UserQueueManager.cpp

#include <StdAfx.h>

#include "UserQueueManager.h"
#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBUserQueueManager 


ZBUserQueueManager::ZBUserQueueManager()
{}

ZBUserQueueManager::~ZBUserQueueManager()
{}

BOOL ZBUserQueueManager::Create(const CString Directory)
{
    m_Directory = Directory;

    // Make the queue directory lower case.
    m_Directory.MakeLower();

    if (!m_UserDirectoryManager.SetDirectory(Directory))
        return FALSE;
    return TRUE;
}

PSS_ActivityEvent* ZBUserQueueManager::DispatchToUserQueue(const CString fileName)
{
    PSS_ActivityEvent* pEventActivity = (PSS_ActivityEvent*)m_ActivityEventFile.ImportActivityFromFile(fileName);
    if (!pEventActivity)
        return NULL;
    TRACE1("DISPATCH TO USER QUEUE IN WITH FILENAME = %s\n", (const char*)fileName);

    // Check the directory structure
    // of senders and receivers
    if (!CheckDirectory(*pEventActivity))
    {
        delete pEventActivity;
        return NULL;
    }
    if (pEventActivity->GetActivityEventType() == PSS_ActivityEvent::IE_AT_LogEvent)
    {
        // In case of log, do nothing
        return pEventActivity;
    }
    if (pEventActivity->GetActivityEventType() == PSS_ActivityEvent::IE_AT_DeleteToDoEvent)
    {
        ProceedDeleteMessage(*pEventActivity);
        return pEventActivity;
    }
    // Create place the new event to the receiver queue
    ForwardToUserQueue(*pEventActivity);
    if (pEventActivity->GetActivityEventType() == PSS_ActivityEvent::IE_AT_ToDo)
    {
        // Remove the old event if exists, from the sender queue
        RemoveAssociatedEventFromUserQueue(*pEventActivity);
    }
    return pEventActivity;
}


BOOL    ZBUserQueueManager::CheckDirectory(PSS_ActivityEvent& EventActivity)
{
    // For multi-user mode, run through all senders
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetSender());
    while (!Token.IsEmpty())
    {
        // Dispatch to the first
        if (!m_UserDirectoryManager.UserExist(Token))
            m_UserDirectoryManager.CreateUser(Token);
        Token = Tokenizer.GetNextToken();
    }

    // For multi-user mode, run through all receivers
    Token = Tokenizer.GetFirstToken(EventActivity.GetReceiver());
    while (!Token.IsEmpty())
    {
        // Dispatch to the first
        if (!m_UserDirectoryManager.UserExist(Token))
            m_UserDirectoryManager.CreateUser(Token);
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

BOOL    ZBUserQueueManager::ForwardToUserQueue(PSS_ActivityEvent& EventActivity)
{
    // For multi-user mode, run through all receivers
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetReceiver());
    while (!Token.IsEmpty())
    {
        // Dispatch to the 
        CString fileName = BuildUserActivityEventFileName(EventActivity.GetFileName() + EventActivity.GetFileExtension(), Token);
        m_ActivityEventFile.ExportActivityToFile(fileName, &EventActivity);
        TRACE("FORWARDED TO USER QUEUE\n");
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

BOOL    ZBUserQueueManager::RemoveAssociatedEventFromUserQueue(PSS_ActivityEvent& EventActivity)
{
    PSS_ActivityEvent* pEventActivity = NULL;
    // For multi-user mode, run through all senders
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetSender());
    while (!Token.IsEmpty())
    {
        CString fileName = BuildUserActivityEventFileName(EventActivity.GetFileName() + EventActivity.GetFileExtension(PSS_ActivityEvent::IE_AT_ToDo), Token);
        // Import file first
        pEventActivity = (PSS_ActivityEvent*)m_ActivityEventFile.ImportActivityFromFile(fileName);
        // If it is a todo activity, therefore remove the associated message
        if (pEventActivity && pEventActivity->GetActivityEventType() == PSS_ActivityEvent::IE_AT_ToDo &&
            Token != pEventActivity->GetSender())
        {
            TRACE("REMOVE ASSIOCIATED EVENT\n");
            delete pEventActivity;
            pEventActivity = NULL;
            RemoveEventFileName(fileName);
        }
        if (pEventActivity)
            delete pEventActivity;
        Token = Tokenizer.GetNextToken();
    }
    pEventActivity = NULL;

    return TRUE;
}


BOOL    ZBUserQueueManager::RemoveEventFromUserQueue(PSS_ActivityEvent& EventActivity, CString User)
{
    // For multi-user mode, run through all users
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(User);
    while (!Token.IsEmpty())
    {
        if (!RemoveFromUserQueue(EventActivity, Token))
            return FALSE;
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

BOOL    ZBUserQueueManager::RemoveEventFromReceiverQueue(PSS_ActivityEvent& EventActivity)
{
    // For multi-user mode, run through all receiver
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetReceiver());
    while (!Token.IsEmpty())
    {
        if (!RemoveFromUserQueue(EventActivity, Token))
            return FALSE;
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

BOOL    ZBUserQueueManager::RemoveEventFromSenderQueue(PSS_ActivityEvent& EventActivity)
{
    // For multi-user mode, run through all senders
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetSender());
    while (!Token.IsEmpty())
    {
        if (!RemoveFromUserQueue(EventActivity, Token))
            return FALSE;
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

BOOL    ZBUserQueueManager::RemoveFromUserQueue(PSS_ActivityEvent& EventActivity, CString User)
{
    CString fileName = BuildUserActivityEventFileName(EventActivity.GetFileName() + EventActivity.GetFileExtension(), User);
    return RemoveEventFileName(fileName);
}

BOOL    ZBUserQueueManager::ProceedDeleteMessage(PSS_ActivityEvent& EventActivity)
{
    // For multi-user mode, run through all senders
    PSS_Tokenizer    Tokenizer(';');
    CString    Token = Tokenizer.GetFirstToken(EventActivity.GetReceiver());
    while (!Token.IsEmpty())
    {
        CString fileName = BuildUserActivityEventFileName(EventActivity.GetFileName() + EventActivity.GetFileExtension(PSS_ActivityEvent::IE_AT_ToDo), Token);
        RemoveEventFileName(fileName);
        Token = Tokenizer.GetNextToken();
    }
    return TRUE;
}

CString    ZBUserQueueManager::BuildUserActivityEventFileName(CString fileName, const CString User)
{
    CString    Directory = m_UserDirectoryManager.BuildUserDirectory(User);
    return Directory + "\\" + fileName;
}


BOOL    ZBUserQueueManager::RemoveEventFileName(const CString fileName)
{
    // Test if the file exists
    CFileStatus status;
    if (CFile::GetStatus(fileName, status))
    {
        // Physically remove the file
        for (int i = 0; i < 10; ++i)
        {
            TRY
            {
                CFile::Remove(fileName);
                TRACE1("FILENAME REMOVED %s\n", (const char*)fileName);
                return TRUE;
            }
                CATCH(CFileException, e)
            {
                ::Sleep(100);
            }
            END_CATCH
        }
    }
    TRACE1("PROBLEM REMOVEING FILENAME %s\n", (const char*)fileName);
    return FALSE;
}
