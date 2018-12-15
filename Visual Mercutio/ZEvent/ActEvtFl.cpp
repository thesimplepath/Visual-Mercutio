// ActEvtFl.cpp: implementation of the ZBEventActivityFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ActEvtFl.h"
#include "ZEvtRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBEventActivityFile::ZBEventActivityFile()
{

}

void ZBEventActivityFile::BuildLine ( const CString Path, const CString Filename )
{
    ASSERT( m_pEvent );
    m_FileBuffer.Format( "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\r\n", 
            (const char*)((ZBEventActivity*)m_pEvent)->GetActivityEventTypeString(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFilename(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFolderName(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetProcessName(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFormatedProcessCreationDate(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFormatedProcessDueDate(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetActivityType(),
            (const char*)((ZBEventActivity*)m_pEvent)->GetActivityName(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFormatedActivityCreationDate(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetFormatedActivityDueDate(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetSender(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetReceiver(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetProcessFilename(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetExchangeDataFilename(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetProcessExchangeDataFilename(),
            (const char*)((ZBEventActivity*)m_pEvent)->GetActivityStatus(), 
            (const char*)((ZBEventActivity*)m_pEvent)->GetComments(),
            (((ZBEventActivity*)m_pEvent)->GetIsInBackup()) ? "1" : "0");
}

BOOL ZBEventActivityFile::ParseLine()
{
      // The line we received is exactly the same we exported
      char*    pCurrent = m_FileBuffer.GetBuffer(m_BufferSize);
    char*    pNext;      

    char    SeparatorChar = '\t';

      // Extract the event type
    // Locates the separator char 
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)((ZBEventActivity*)m_pEvent))->SetActivityEventType( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the file name
    // Locates the separator char 
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)((ZBEventActivity*)m_pEvent))->SetFilename( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

    // Extract the folder name
    // Locates the separator char 
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)((ZBEventActivity*)m_pEvent))->SetFolderName( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

    // Extract the process name
    // Locates the separator char 
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)((ZBEventActivity*)m_pEvent))->SetProcessName( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Process creation date
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetProcessCreationDate( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Process due date
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetProcessDueDate( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

    // Extract the activity type
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetActivityType( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;
    
      // Extract the Activity name
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetActivityName( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Activity creation date
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetActivityCreationDate( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Activity due date
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetActivityDueDate( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the sender
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetSender( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the receiver
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetReceiver( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Proess Filename
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetProcessFilename( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Exchange Filename
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetExchangeDataFilename( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Process Exchange Filename
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetProcessExchangeDataFilename( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the Activity status
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetActivityStatus( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;


      // Extract the comment
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetComments( pCurrent );
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

      // Extract the flag for backup
    pNext = strchr( pCurrent, '\r' );
    if (!pNext)
        return FALSE;
    // Where next is found, put end of string char.
    *pNext = 0x00;
    ((ZBEventActivity*)m_pEvent)->SetIsInBackup( pCurrent );

    return TRUE;      
}




