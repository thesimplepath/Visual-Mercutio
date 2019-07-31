// EventFl.cpp: implementation of the ZBEventFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventFl.h"
#include "ZEvtRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBEventFile::ZBEventFile()
: m_BufferSize(1000),
  m_pEvent(NULL),
  m_pCurrent(NULL),
  m_pNext(NULL)
{

}
ZBEventFile::~ZBEventFile()
{
    m_pEvent = NULL;
}

BOOL    ZBEventFile::ExportActivityToFile( const CString Filename, ZBEvent* pActivity )
{
    m_Filename = Filename;
    m_pEvent = pActivity;
    if (!OpenFileCreate ())
        return FALSE;
    ExportLine();
    // Close the file
    CloseFile();
    return TRUE;
}


ZBEvent*    ZBEventFile::ImportActivityFromFile( const CString Filename )
{
    m_Filename = Filename;
    m_pEvent = AllocateEventPtr();
    if (!m_pEvent)
        return NULL;
    if (!OpenFileRead ())
        return NULL;
    if (!ImportLine())
    {
        // Close the file
        CloseFile();
        return NULL;
    }
    // Close the file
    CloseFile();
    return m_pEvent;
}


BOOL ZBEventFile::ImportLine()
{
    if (ReadFileBuffer() > 0)
    {
        if (ParseLine())
            return TRUE;
    }
    return FALSE;
}

void ZBEventFile::ExportLine()
{
    char drive[_MAX_DRIVE];
    char dir  [_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext  [_MAX_EXT];

    _splitpath_s((const char*)m_Filename, drive, _tcslen(drive), dir, _tcslen(dir), fname, _tcslen(fname), ext, _tcslen(ext));
    BuildLine(CString(drive) + dir, CString(fname) + ext);
    WriteLine();
}



BOOL ZBEventFile::OpenFileCreate ()
{
    TRY
    {
        // Construct a CFile object in read mode
        if (!m_File.Open( m_Filename, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate ))
            return FALSE;
    }
    CATCH( CFileException, e )
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
        return FALSE;
    }
    END_CATCH
    return TRUE;
}

BOOL ZBEventFile::OpenFileRead ()
{
    TRY
    {
        // Construct a CFile object in read mode
        if (!m_File.Open( m_Filename, CFile::modeRead | CFile::typeBinary ))
            return FALSE;
    }
    CATCH( CFileException, e )
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif
        return FALSE;
    }
    END_CATCH
    return TRUE;
}

BOOL ZBEventFile::CloseFile ()
{
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
    return TRUE;
}


int ZBEventFile::ReadFileBuffer ()
{
      int    ReadChar;
    // Sets current pointer
    m_pCurrent = m_FileBuffer.GetBufferSetLength( m_BufferSize );
    // Read info from the file
    ReadChar = m_File.Read( m_pCurrent, m_BufferSize - 1);
    // Sets end of line
    m_FileBuffer.SetAt(ReadChar, 0x00);
    // Release the buffer
    m_FileBuffer.ReleaseBuffer(-1);
    // If char read
    if (ReadChar == 0)
        // Sets current pointer
        m_pCurrent = NULL;
    // Returns the number of char read    
    return ReadChar;
}



