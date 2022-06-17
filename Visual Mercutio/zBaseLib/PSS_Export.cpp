/****************************************************************************
 * ==> PSS_Export ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export interface                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Export.h"

// processsoft
#include "PSS_MsgBox.h"

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_Export, CWnd)
    //{{AFX_MSG_MAP(PSS_Export)
    ON_WM_TIMER()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_Export
//---------------------------------------------------------------------------
PSS_Export::PSS_Export(const CString&                fileName,
                       BOOL                          generateHeader,
                       ESynchronizationSeparatorType separatorType,
                       const CString&                schema,
                       int                           propagationMode,
                       BOOL                          emptyWhenZero,
                       PSS_StatusBar*                pStatusBar) :
    CWnd(),
    m_pStatusBar(pStatusBar),
    m_FileName(fileName),
    m_SourceIsModified(FALSE),
    m_SeparatorType(separatorType),
    m_SchemaName(schema),
    m_pCurrent(NULL),
    m_pNext(NULL),
    m_PropagationMode(propagationMode),
    m_TimeSynchronizationValue(5),
    m_GenerateHeader(generateHeader),
    m_EmptyWhenZero(emptyWhenZero)
{
    std::memset(&m_FileBuffer, 0x0, 300);
}
//---------------------------------------------------------------------------
PSS_Export::PSS_Export(const PSS_Export& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Export::~PSS_Export()
{
    if (::IsWindow(GetSafeHwnd()))
        KillTimer(1);
}
//---------------------------------------------------------------------------
const PSS_Export& PSS_Export::operator = (const PSS_Export& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_Export::Export()
{
    if (!OpenFileCreate())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_EXPORTFILE_FAIL, MB_OK);
        return FALSE;
    }

    if (m_pStatusBar)
        m_pStatusBar->BeginAniPercentage();

    // call the pre export function
    if (!PreExport())
        return FALSE;

    // do generate the header?
    if (GetGenerateHeader())
        WriteLine(GetHeaderLine());

    // generate additional information
    if (!ExportAdditionalInfo())
        return FALSE;

    if (!DoExportLoop())
        return FALSE;

    // call the post export function
    if (!PostExport())
        return FALSE;

    // close the file for further use
    CloseFile();

    if (m_pStatusBar)
        m_pStatusBar->EndAniPercentage();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::Import()
{
    // initialize variables
    m_pCurrent = m_pNext = NULL;

    if (!OpenFileRead())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_IMPORTFILE_NF, MB_OK);
        return FALSE;
    }

    // call the pre import function
    if (!PreImport())
        return FALSE;

    BOOL result = TRUE;

    CString line;
    CString headerLine;
    double  count = 0.0;

    if (m_pStatusBar)
        m_pStatusBar->BeginAniPercentage();

    // do read the header?
    if (GetGenerateHeader())
        result = ReadLine(headerLine);

    // import additional information
    if (!ImportAdditionalInfo())
        return FALSE;

    // get the object count
    const double forecastedTotalObject = __max(1, GetForecastedTotalObject());

    while (result && ReadLine(line))
    {
        if (!ProcessLine(line))
            result = FALSE;

        if (m_pStatusBar)
            m_pStatusBar->SetCurrentPercentage(int((double(++count) / forecastedTotalObject) * 100.0));
    }

    // close the file for further use
    CloseFile();

    if (m_pStatusBar)
        m_pStatusBar->EndAniPercentage();

    // call the post import function
    if (!PostImport())
        return FALSE;

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::Synchronize()
{
    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_Export::GetExportedLine(CObject* pObj)
{
    return "";
}
//---------------------------------------------------------------------------
BOOL PSS_Export::IsExportedField(CObject* pObj) const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::ProcessLine(const CString& line)
{
    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_Export::GetHeaderLine()
{
    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_Export::StartSynchronization(int timeValue)
{
    // initialize the time value
    m_TimeSynchronizationValue = timeValue;

    CFileStatus status;

    // file does not exists? Create it if yes
    if (!CFile::GetStatus(m_FileName, status))
    {
        // if not exists, do an export first
        Export();

        // get status again
        if (!CFile::GetStatus(m_FileName, status))
            return FALSE;
    }

    // get the file date
    m_LastFileDate = status.m_mtime;

    // create the timer window, register a custom WndClass and create a window. This must be done
    // because CBounceWnd has a custom cursor, and no icon
    const char* pExportClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

    CRect rect;
    rect.SetRectEmpty();

    return CreateEx(0,
                    pExportClass,
                    _T(""),
                    WS_POPUP,
                    rect.left,
                    rect.top,
                    rect.right,
                    rect.bottom,
                    NULL,
                    HMENU(NULL));
}
//---------------------------------------------------------------------------
void PSS_Export::EndSynchronization()
{
    KillTimer(1);
}
//---------------------------------------------------------------------------
void PSS_Export::SourceHasBeenModified()
{
    m_SourceIsModified = TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::ExportAdditionalInfo()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::ImportAdditionalInfo()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::PreImport()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::PostImport()
{
    return TRUE;
}
//---------------------------------------------------------------------------
double PSS_Export::GetForecastedTotalObject() const
{
    return 1.0;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::DoExportLoop()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::PreExport()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Export::PostExport()
{
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_Export::ReadLine(CString& line)
{
    // empty buffer?
    if (!m_pCurrent)
        // read information from the file and fill the buffer
        if (ReadFileBuffer() <= 0)
            return 0;

    // the buffer is filled and a new occurence was found
    if (m_pCurrent)
    {
        // next return char found?
        if ((m_pNext = std::strchr(m_pCurrent, '\n')))
        {
            // where \r is found, put end of string char
            *(m_pNext - 1) = 0x00;

            // copy the line to buffer
            line = m_pCurrent;

            // set current to the next char after the \n pointer
            m_pCurrent = m_pNext + 1;
        }
        else
        {
            // it's necessary to read the next buffer and to merge the previous and the new one
            CString endLine(m_pCurrent);

            // read information from the file and fill the buffer
            if (ReadFileBuffer() <= 0)
                return 0;

            // build the final line with the EndLine + the  beginning of the new read buffer.
            // Locate the next return char
            if (!(m_pNext = strchr(m_pCurrent, '\n')))
                return 0;

            // where \r is found, put end of string char
            if (m_pNext != m_pCurrent)
            {
                *(m_pNext - 1) = 0x00;

                // copy the line to buffer
                line = endLine + m_pCurrent;
            }
            else
                // copy the line to the buffer
                line = endLine.Left(endLine.GetLength() - 1);

            // set current to the next char after the \n pointer
            m_pCurrent = m_pNext + 1;
        }
    }

    return line.GetLength();
}
//---------------------------------------------------------------------------
void PSS_Export::WriteLine(const CString& line)
{
    m_File.Write(line, line.GetLength());
}
//---------------------------------------------------------------------------
BOOL PSS_Export::OpenFileCreate()
{
    TRY
    {
        // open a CFile object in read mode
        if (!m_File.Open(m_FileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_Export::OpenFileRead()
{
    TRY
    {
        // open a CFile object in read mode
        if (!m_File.Open(m_FileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
    CATCH(CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_Export::CloseFile()
{
    TRY
    {
        m_File.Close();
    }
    CATCH(CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_Export::SynchronizationFileUpdated()
{
    CFileStatus status;

    // the file does not exists? Create it if yes
    if (!CFile::GetStatus(m_FileName, status))
    {
        if (!OpenFileCreate())
            return FALSE;

        // close the file immediatly
        CloseFile();

        // get status again
        if (!CFile::GetStatus(m_FileName, status))
            return FALSE;
    }

    // compared the file date
    return m_LastFileDate < status.m_mtime;
}
//---------------------------------------------------------------------------
void PSS_Export::AssignSynchronizationFileDate()
{
    CFileStatus status;

    // the file does not exists? Create it if yes
    if (!CFile::GetStatus(m_FileName, status))
        return;

    // get the file date
    m_LastFileDate = status.m_mtime;
}
//---------------------------------------------------------------------------
CString PSS_Export::BuildLine(const CString& key, const CString& value)
{
    CString lineBuffer;

    switch (GetSeparatorType())
    {
        case ESynchronizationSeparatorType::E_SS_Comma:     lineBuffer.Format(_T("%s,%s\r\n"),         (const char*)key, (const char*)value); break;
        case ESynchronizationSeparatorType::E_SS_Semicolon: lineBuffer.Format(_T("%s;%s\r\n"),         (const char*)key, (const char*)value); break;
        case ESynchronizationSeparatorType::E_SS_Quote:     lineBuffer.Format(_T("\"%s\" \"%s\"\r\n"), (const char*)key, (const char*)value); break;
        default:                                            lineBuffer.Format(_T("%s\t%s\r\n"),        (const char*)key, (const char*)value); break;
    }

    return lineBuffer;
}
//---------------------------------------------------------------------------
void PSS_Export::OnTimer(UINT nIDEvent)
{
    // check if the feed file has been updated
    if (SynchronizationFileUpdated())
    {
        Import();
        AssignSynchronizationFileDate();
    }

    // check if the current file has been updated
    if (m_SourceIsModified)
    {
        Export();
        m_SourceIsModified = FALSE;
        AssignSynchronizationFileDate();
    }

    CWnd::OnTimer(nIDEvent);
}
//---------------------------------------------------------------------------
int PSS_Export::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    const double elapsed = __min(65000, m_TimeSynchronizationValue * 1000);

    if (!SetTimer(1, UINT(elapsed), NULL))
        // signal creation failure...
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
int PSS_Export::ReadFileBuffer()
{
    // read info from the file
    const int readChar = m_File.Read(m_FileBuffer, sizeof(m_FileBuffer) - 1);

    // char read?
    if (readChar)
        // set current pointer
        m_pCurrent = m_FileBuffer;

    // set end of line
    m_FileBuffer[readChar] = 0x00;

    // return the char read count
    return readChar;
}
//---------------------------------------------------------------------------
