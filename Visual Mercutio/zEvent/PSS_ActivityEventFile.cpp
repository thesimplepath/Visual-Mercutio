/****************************************************************************
 * ==> PSS_ActivityEventFile -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event file                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ActivityEventFile.h"

// processsoft
#include "ZEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ActivityEventFile
//---------------------------------------------------------------------------
PSS_ActivityEventFile::PSS_ActivityEventFile() :
    PSS_EventFile()
{}
//---------------------------------------------------------------------------
PSS_ActivityEventFile::PSS_ActivityEventFile(const PSS_ActivityEventFile& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
const PSS_ActivityEventFile& PSS_ActivityEventFile::operator = (const PSS_ActivityEventFile& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ActivityEventFile::BuildLine(const CString& path, const CString& fileName)
{
    PSS_ActivityEvent* pActivityEvent = dynamic_cast<PSS_ActivityEvent*>(m_pEvent);
    PSS_Assert(pActivityEvent);

    m_FileBuffer.Format("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\r\n",
                        (const char*)pActivityEvent->GetActivityEventTypeString(),
                        (const char*)pActivityEvent->GetFileName(),
                        (const char*)pActivityEvent->GetFolderName(),
                        (const char*)pActivityEvent->GetProcessName(),
                        (const char*)pActivityEvent->GetFormattedProcessCreationDate(),
                        (const char*)pActivityEvent->GetFormattedProcessDueDate(),
                        (const char*)pActivityEvent->GetActivityType(),
                        (const char*)pActivityEvent->GetActivityName(),
                        (const char*)pActivityEvent->GetFormattedActivityCreationDate(),
                        (const char*)pActivityEvent->GetFormattedActivityDueDate(),
                        (const char*)pActivityEvent->GetSender(),
                        (const char*)pActivityEvent->GetReceiver(),
                        (const char*)pActivityEvent->GetProcessFileName(),
                        (const char*)pActivityEvent->GetExchangeDataFileName(),
                        (const char*)pActivityEvent->GetProcessExchangeDataFileName(),
                        (const char*)pActivityEvent->GetActivityStatus(),
                        (const char*)pActivityEvent->GetComments(),
                                     pActivityEvent->GetIsInBackup() ? "1" : "0");
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventFile::ParseLine()
{
    const char separatorChar = '\t';

    // the received line is exactly the same as exported
    char* pCurrent = m_FileBuffer.GetBuffer(m_BufferSize);

    // extract the event type. Locate the separator char 
    char* pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    PSS_ActivityEvent* pActivityEvent = dynamic_cast<PSS_ActivityEvent*>(m_pEvent);
    PSS_Assert(pActivityEvent);

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityEventType(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the file name. Locate the separator char 
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetFileName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the folder name. Locate the separator char 
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetFolderName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the process name. Locate the separator char 
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetProcessName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the process creation date
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetProcessCreationDate(CString(pCurrent));

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // wxtract the process due date
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetProcessDueDate(CString(pCurrent));

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the activity type
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityType(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the activity name
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the activity creation date
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityCreationDate(CString(pCurrent));

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the Activity due date
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityDueDate(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the sender
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetSender(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the receiver
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetReceiver(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the process file name
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetProcessFileName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the Exchange file name
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetExchangeDataFileName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the process Exchange file name
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetProcessExchangeDataFileName(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the activity status
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetActivityStatus(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the comment
    pNext = strchr(pCurrent, separatorChar);

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetComments(pCurrent);

    // set the current pointer to the next char after the next pointer
    pCurrent = ++pNext;

    // extract the flag for backup
    pNext = strchr(pCurrent, '\r');

    if (!pNext)
        return FALSE;

    // where next is found, put end of string char
    *pNext = 0x00;

    pActivityEvent->SetIsInBackup(pCurrent);

    return TRUE;
}
//---------------------------------------------------------------------------
