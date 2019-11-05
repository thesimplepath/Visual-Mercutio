//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ

#include <StdAfx.h>
#include "ActLogFl.h"

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_Tokenizer.h"

ZUActivityLogFile::ZUActivityLogFile(CString LogFileName)
    : m_LogFileName(LogFileName), m_IsOpen(FALSE)
{}


ZUActivityLogFile::~ZUActivityLogFile()
{}



BOOL ZUActivityLogFile::OpenRead()
{
    TRY
    {
        // Construct a CFile object in read mode
        if (m_LogFileName.IsEmpty() || !m_File.Open(m_LogFileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
        CATCH(CFileException, e)
    {
    #ifdef _DEBUG
        afxDump << "File could not be opened " << e->m_cause << "\n";
    #endif
    }
    END_CATCH
        // Set flag for open
        m_IsOpen = TRUE;
    return TRUE;
}

BOOL ZUActivityLogFile::OpenCreate()
{
    TRY
    {
        // Construct a CFile object in write mode for creation
        if (m_LogFileName.IsEmpty() || !m_File.Open(m_LogFileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
        CATCH(CFileException, e)
    {
    #ifdef _DEBUG
        afxDump << "File could not be opened " << e->m_cause << "\n";
    #endif
    }
    END_CATCH
        // Set flag for open
        m_IsOpen = TRUE;
    return TRUE;
}

BOOL ZUActivityLogFile::OpenWrite()
{
    TRY
    {
        // Construct a CFile object in read mode
        if (m_LogFileName.IsEmpty() || !m_File.Open(m_LogFileName, CFile::modeWrite | CFile::typeBinary))
            return FALSE;
    }
        CATCH(CFileException, e)
    {
    #ifdef _DEBUG
        afxDump << "File could not be opened " << e->m_cause << "\n";
    #endif
    }
    END_CATCH
        // Set flag for open
        m_IsOpen = TRUE;
    return TRUE;
}

BOOL ZUActivityLogFile::Close()
{
    if (!m_IsOpen)
        return TRUE;
    TRY
    {
        m_File.Close();
    }
        CATCH(CFileException, e)
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


BOOL ZUActivityLogFile::WriteLine(CString& Line)
{
    // Go to the end of the file
    m_File.SeekToEnd();
    TRY
    {
        m_File.Write(Line, Line.GetLength());
    }
        CATCH(CFileException, e)
    {
    #ifdef _DEBUG
        afxDump << "File could write to file " << e->m_cause << "\n";
    #endif
        return FALSE;
    }
    END_CATCH
        return TRUE;
}

void ZUActivityLogFile::Create(CString LogFileName)
{
    m_LogFileName = LogFileName;
    if (m_LogFileName.IsEmpty())
        return;
    if (!OpenRead())
        OpenCreate();
    Close();
}

BOOL ZUActivityLogFile::AppendToLog(const PSS_ActivityEvent& activityEvent)
{
    if (!OpenWrite())
        OpenCreate();

    PSS_Date    CurrentDate = PSS_Date::GetToday();
    CString    Line;

    PSS_Tokenizer Tokenizer('\t');

    // The current date
    Tokenizer.AddToken(CurrentDate.GetStandardFormattedDate());

    // The Event type
    Tokenizer.AddToken(activityEvent.GetActivityEventTypeString());

    // The process file
    Tokenizer.AddToken(activityEvent.GetProcessFileName());

    // The data file
    Tokenizer.AddToken(activityEvent.GetExchangeDataFileName());

    // The process data file
    Tokenizer.AddToken(activityEvent.GetProcessExchangeDataFileName());

    // The folder name
    Tokenizer.AddToken(activityEvent.GetFolderName());

    // The process name
    Tokenizer.AddToken(activityEvent.GetProcessName());

    // The process start date
    Tokenizer.AddToken(activityEvent.GetFormattedProcessCreationDate());

    // The process end date
    Tokenizer.AddToken(activityEvent.GetFormattedProcessDueDate());

    // The activity type
    Tokenizer.AddToken(activityEvent.GetActivityType());

    // The activity name    
    Tokenizer.AddToken(activityEvent.GetActivityName());

    // The activity start date
    Tokenizer.AddToken(activityEvent.GetFormattedActivityCreationDate());

    // The activity end date
    Tokenizer.AddToken(activityEvent.GetFormattedActivityDueDate());

    // The status
    Tokenizer.AddToken(activityEvent.GetActivityStatus());

    // The sender
    Tokenizer.AddToken(activityEvent.GetSender());

    // The receiver
    Tokenizer.AddToken(activityEvent.GetReceiver());

    // The comment
    Tokenizer.AddToken(activityEvent.GetComments());

    // Is In Backup mode or not
    if (activityEvent.GetIsInBackup())
        Tokenizer.AddToken("1");
    else
        Tokenizer.AddToken("0");

    if (!WriteLine(Tokenizer.GetString()))
        return FALSE;

    return Close();
}


BOOL ZUActivityLogFile::ClearLog()
{
    return OpenCreate();
}
