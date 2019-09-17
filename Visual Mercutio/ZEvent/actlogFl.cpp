//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ

#include <StdAfx.h>
// ActLog
#include "ActLogFl.h"
#include "zBaseLib\ZBDate.h"

#include "zBaseLib\ZBTokenizer.h"






// Class ZUActivityLogFile 



ZUActivityLogFile::ZUActivityLogFile (CString LogFileName)
  : m_LogFileName(LogFileName), m_IsOpen(FALSE)
{
}


ZUActivityLogFile::~ZUActivityLogFile()
{
}



BOOL ZUActivityLogFile::OpenRead ()
{
TRY
{
    // Construct a CFile object in read mode
    if (m_LogFileName.IsEmpty() || !m_File.Open( m_LogFileName, CFile::modeRead | CFile::typeBinary ))
        return FALSE;
}
CATCH( CFileException, e )
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

BOOL ZUActivityLogFile::OpenCreate ()
{
TRY
{
    // Construct a CFile object in write mode for creation
    if (m_LogFileName.IsEmpty() || !m_File.Open( m_LogFileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate ))
        return FALSE;
}
CATCH( CFileException, e )
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

BOOL ZUActivityLogFile::OpenWrite ()
{
TRY
{
    // Construct a CFile object in read mode
    if (m_LogFileName.IsEmpty() || !m_File.Open( m_LogFileName, CFile::modeWrite | CFile::typeBinary ))
        return FALSE;
}
CATCH( CFileException, e )
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

BOOL ZUActivityLogFile::Close ()
{
    if (!m_IsOpen)
        return TRUE;
TRY
{
    m_File.Close();
}
CATCH( CFileException, e )
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


BOOL ZUActivityLogFile::WriteLine (CString& Line)
{
    // Go to the end of the file
    m_File.SeekToEnd();
TRY
{
    m_File.Write( Line, Line.GetLength() );
}
CATCH( CFileException, e )
{
    #ifdef _DEBUG
        afxDump << "File could write to file " << e->m_cause << "\n";
    #endif
    return FALSE;
}
END_CATCH
    return TRUE;
}

void ZUActivityLogFile::Create (CString LogFileName)
{
      m_LogFileName = LogFileName;
      if (m_LogFileName.IsEmpty())
          return;
      if (!OpenRead())
          OpenCreate();
    Close();
}

BOOL ZUActivityLogFile::AppendToLog (ZBEventActivity& EventActivity)
{
    if (!OpenWrite())
        OpenCreate();

    PSS_Date    CurrentDate = PSS_Date::GetToday();
    CString    Line;

    ZBTokenizer    Tokenizer( '\t' );

    // The current date
    Tokenizer.AddToken( CurrentDate.GetStandardFormattedDate() );

    // The Event type
    Tokenizer.AddToken( EventActivity.GetActivityEventTypeString() );

    // The process file
      Tokenizer.AddToken( EventActivity.GetProcessFilename() );

    // The data file
    Tokenizer.AddToken( EventActivity.GetExchangeDataFilename() );
    
    // The process data file
    Tokenizer.AddToken( EventActivity.GetProcessExchangeDataFilename() );

    // The folder name
    Tokenizer.AddToken( EventActivity.GetFolderName() );

    // The process name
    Tokenizer.AddToken( EventActivity.GetProcessName() );

    // The process start date
    Tokenizer.AddToken( EventActivity.GetFormattedProcessCreationDate() );

    // The process end date
    Tokenizer.AddToken( EventActivity.GetFormattedProcessDueDate() );

    // The activity type
    Tokenizer.AddToken( EventActivity.GetActivityType() );

    // The activity name    
    Tokenizer.AddToken( EventActivity.GetActivityName() );

    // The activity start date
    Tokenizer.AddToken( EventActivity.GetFormattedActivityCreationDate() );

    // The activity end date
    Tokenizer.AddToken( EventActivity.GetFormattedActivityDueDate() );

    // The status
      Tokenizer.AddToken( EventActivity.GetActivityStatus() );

    // The sender
      Tokenizer.AddToken( EventActivity.GetSender() );

    // The receiver
      Tokenizer.AddToken( EventActivity.GetReceiver() );

    // The comment
      Tokenizer.AddToken( EventActivity.GetComments() );

    // Is In Backup mode or not
    if (EventActivity.GetIsInBackup())
        Tokenizer.AddToken( "1" );
    else
        Tokenizer.AddToken( "0" );

    if (!WriteLine( Tokenizer.GetString() ))
        return FALSE;
    
      return Close();
}


BOOL ZUActivityLogFile::ClearLog ()
{
    return OpenCreate();
}
