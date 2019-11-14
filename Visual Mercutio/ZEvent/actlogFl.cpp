/****************************************************************************
 * ==> PSS_ActivityLogFile -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity log file                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "ActLogFl.h"

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_Tokenizer.h"

//---------------------------------------------------------------------------
// PSS_ActivityLogFile
//---------------------------------------------------------------------------
PSS_ActivityLogFile::PSS_ActivityLogFile(const CString& fileName) :
    m_LogFileName(fileName),
    m_IsOpen(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ActivityLogFile::PSS_ActivityLogFile(const PSS_ActivityLogFile& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityLogFile::~PSS_ActivityLogFile()
{}
//---------------------------------------------------------------------------
const PSS_ActivityLogFile& PSS_ActivityLogFile::operator = (const PSS_ActivityLogFile& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ActivityLogFile::Create(const CString& fileName)
{
    m_LogFileName = fileName;

    if (m_LogFileName.IsEmpty())
        return;

    if (!OpenRead())
        OpenCreate();

    Close();
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::WriteLine(const CString& Line)
{
    // seek to file end
    m_File.SeekToEnd();

    TRY
    {
        m_File.Write(line, line.GetLength());
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could write to file " << e->m_cause << "\n";
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::AppendToLog(const PSS_ActivityEvent& activityEvent)
{
    if (!OpenWrite())
        OpenCreate();

    PSS_Date currentDate = PSS_Date::GetToday();
    CString  line;

    PSS_Tokenizer tokenizer('\t');
    tokenizer.AddToken(currentDate.GetStandardFormattedDate());
    tokenizer.AddToken(activityEvent.GetActivityEventTypeString());
    tokenizer.AddToken(activityEvent.GetProcessFileName());
    tokenizer.AddToken(activityEvent.GetExchangeDataFileName());
    tokenizer.AddToken(activityEvent.GetProcessExchangeDataFileName());
    tokenizer.AddToken(activityEvent.GetFolderName());
    tokenizer.AddToken(activityEvent.GetProcessName());
    tokenizer.AddToken(activityEvent.GetFormattedProcessCreationDate());
    tokenizer.AddToken(activityEvent.GetFormattedProcessDueDate());
    tokenizer.AddToken(activityEvent.GetActivityType());
    tokenizer.AddToken(activityEvent.GetActivityName());
    tokenizer.AddToken(activityEvent.GetFormattedActivityCreationDate());
    tokenizer.AddToken(activityEvent.GetFormattedActivityDueDate());
    tokenizer.AddToken(activityEvent.GetActivityStatus());
    tokenizer.AddToken(activityEvent.GetSender());
    tokenizer.AddToken(activityEvent.GetReceiver());
    tokenizer.AddToken(activityEvent.GetComments());

    // is in backup mode?
    if (activityEvent.GetIsInBackup())
        tokenizer.AddToken("1");
    else
        tokenizer.AddToken("0");

    if (!WriteLine(tokenizer.GetString()))
        return FALSE;

    return Close();
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::ClearLog()
{
    return OpenCreate();
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::Close()
{
    if (!m_IsOpen)
        return TRUE;

    TRY
    {
        m_File.Close();
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
 
        return FALSE;
    }
    END_CATCH

    m_IsOpen = FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::OpenCreate()
{
    TRY
    {
        // open a file in write mode, create it if still not exists
        if (m_LogFileName.IsEmpty() ||
           !m_File.Open(m_LogFileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
    }
    END_CATCH

    m_IsOpen = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::OpenRead()
{
    TRY
    {
        // open a file in read mode
        if (m_LogFileName.IsEmpty() || !m_File.Open(m_LogFileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
    }
    END_CATCH

    m_IsOpen = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityLogFile::OpenWrite()
{
    TRY
    {
        // open a file in write mode
        if (m_LogFileName.IsEmpty() || !m_File.Open(m_LogFileName, CFile::modeWrite | CFile::typeBinary))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
    }
    END_CATCH

    m_IsOpen = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
