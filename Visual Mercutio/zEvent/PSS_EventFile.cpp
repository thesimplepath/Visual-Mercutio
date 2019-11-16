/****************************************************************************
 * ==> PSS_EventFile -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event file                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_EventFile.h"

// resources
#include "zEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_EventFile
//---------------------------------------------------------------------------
PSS_EventFile::PSS_EventFile() :
    m_pEvent(NULL),
    m_pCurrent(NULL),
    m_pNext(NULL),
    m_BufferSize(1000),
    m_LocalEvent(false)
{}
//---------------------------------------------------------------------------
PSS_EventFile::PSS_EventFile(const PSS_EventFile& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_EventFile::~PSS_EventFile()
{
    if (m_LocalEvent && m_pEvent)
        delete m_pEvent;
}
//---------------------------------------------------------------------------
const PSS_EventFile& PSS_EventFile::operator = (const PSS_EventFile& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Event* PSS_EventFile::ImportActivityFromFile(const CString& fileName)
{
    m_FileName   = fileName;
    m_pEvent     = AllocateEvent();
    m_LocalEvent = true;

    if (!m_pEvent)
        return NULL;

    if (!OpenFileRead())
        return NULL;

    if (!ImportLine())
    {
        CloseFile();
        return NULL;
    }

    CloseFile();
    return m_pEvent;
}
//---------------------------------------------------------------------------
BOOL PSS_EventFile::ExportActivityToFile(const CString& fileName, PSS_Event* pActivity)
{
    m_FileName   = fileName;
    m_pEvent     = pActivity;
    m_LocalEvent = false;

    if (!OpenFileCreate())
        return FALSE;

    ExportLine();
    CloseFile();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventFile::OpenFileCreate()
{
    TRY
    {
        // open the file in read mode, creates it if still not exists
        if (!m_File.Open(m_FileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventFile::OpenFileRead()
{
    TRY
    {
        // open the file in read mode
        if (!m_File.Open(m_FileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EventFile::CloseFile()
{
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

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_EventFile::ReadFileBuffer()
{
    // set the current pointer
    m_pCurrent = m_FileBuffer.GetBufferSetLength(m_BufferSize);

    // read info from the file
    const int readChar = m_File.Read(m_pCurrent, m_BufferSize - 1);

    // set the end of line
    m_FileBuffer.SetAt(readChar, 0x00);

    // release the buffer
    m_FileBuffer.ReleaseBuffer(-1);

    // a char was read?
    if (!readChar)
        // set the current pointer
        m_pCurrent = NULL;

    // return the read char count
    return readChar;
}
//---------------------------------------------------------------------------
BOOL PSS_EventFile::ImportLine()
{
    if (ReadFileBuffer() > 0)
        if (ParseLine())
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_EventFile::ExportLine()
{
    char drive   [_MAX_DRIVE];
    char dir     [_MAX_DIR];
    char fileName[_MAX_FNAME];
    char ext     [_MAX_EXT];

    ::_splitpath_s((const char*)m_FileName,
                   drive,
                   ::_tcslen(drive),
                   dir,
                   ::_tcslen(dir),
                   fileName,
                   ::_tcslen(fileName),
                   ext,
                   ::_tcslen(ext));

    BuildLine(CString(drive) + dir, CString(fileName) + ext);
    WriteLine();
}
//---------------------------------------------------------------------------
