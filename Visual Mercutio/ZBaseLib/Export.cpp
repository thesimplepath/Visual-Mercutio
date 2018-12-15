//## begin module%35BCB05A02BB.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35BCB05A02BB.cm

//## begin module%35BCB05A02BB.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%35BCB05A02BB.cp

//## Module: Export%35BCB05A02BB; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\Export.cpp

//## begin module%35BCB05A02BB.additionalIncludes preserve=no
//## end module%35BCB05A02BB.additionalIncludes

//## begin module%35BCB05A02BB.includes preserve=yes
#include <StdAfx.h>
//## end module%35BCB05A02BB.includes

// Export
#include "Export.h"
//## begin module%35BCB05A02BB.declarations preserve=no
//## end module%35BCB05A02BB.declarations

//## begin module%35BCB05A02BB.additionalDeclarations preserve=yes

#include "MsgBox.h"

// JMR-MODIF - Le 24 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP( ZUExport, CWnd )
    //{{AFX_MSG_MAP(ZUExport)
    ON_WM_TIMER()
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//## end module%35BCB05A02BB.additionalDeclarations

ZUExport::ZUExport ( CString                        Filename,
                     BOOL                            GenerateHeader,
                     SynchronizationSeparatorType    SeparatorType,
                     CString                        Schema,
                     int                            PropagationMode,
                     BOOL                            EmptyWhenZero,
                     ZIStatusBar*                    pStatusBar )
    //## begin ZUExport::ZUExport%901558644.hasinit preserve=no
    : m_pCurrent                    ( NULL ),
      m_TimeSynchronizationValue    ( 5 ),
      m_SourceIsModified            ( FALSE ),
    //## end ZUExport::ZUExport%901558644.hasinit
    //## begin ZUExport::ZUExport%901558644.initialization preserve=yes
      m_Filename                    ( Filename),
      m_GenerateHeader                ( GenerateHeader ),
      m_SeparatorType                ( SeparatorType ),
      m_SchemaName                    ( Schema ),
      m_PropagationMode                ( PropagationMode ),
      m_EmptyWhenZero                ( EmptyWhenZero ),
      m_pStatusBar                    ( pStatusBar )
    //## end ZUExport::ZUExport%901558644.initialization
{
    //## begin ZUExport::ZUExport%901558644.body preserve=yes
    //## end ZUExport::ZUExport%901558644.body
}

ZUExport::~ZUExport()
{
    //## begin ZUExport::~ZUExport%.body preserve=yes
    if ( ::IsWindow( GetSafeHwnd() ) )
    {
        KillTimer( 1 );
    }
    //## end ZUExport::~ZUExport%.body
}

//## Other Operations (implementation)
BOOL ZUExport::Export ()
{
    //## begin ZUExport::Export%901558645.body preserve=yes
    if ( !OpenFileCreate () )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_EXPORTFILE_FAIL, MB_OK );
        return FALSE;
    }
    
    if ( m_pStatusBar )
    {
        m_pStatusBar->BeginAniPercentage();
    }

    // Call the pre export function
    if ( !PreExport() )
    {
        return FALSE;
    }

    // If necessity to generate the header
    if ( GetGenerateHeader() )
    {
        WriteLine ( GetHeaderLine() );
    }

    // Generates additional information
    if ( !ExportAdditionalInfo() )
    {
        return FALSE;
    }

    if ( !DoExportLoop() )
    {
        return FALSE;
    }

    // Call the post export function
    if ( !PostExport() )
    {
        return FALSE;
    }

    // Close the file for further use
    CloseFile();

    if ( m_pStatusBar )
    {
        m_pStatusBar->EndAniPercentage();
    }

    return TRUE;
    //## end ZUExport::Export%901558645.body
}

BOOL ZUExport::Import ()
{
    //## begin ZUExport::Import%901558646.body preserve=yes

    // Initialize variables
    m_pCurrent = m_pNext = NULL;

    if ( !OpenFileRead () )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_IMPORTFILE_NF, MB_OK );
        return FALSE;
    }

    // Call the pre import function
    if ( !PreImport() )
    {
        return FALSE;
    }
    
    BOOL RetValue = TRUE;

    CString    Line;
    CString    HeaderLine;
    double    Count = 0;
    
    if ( m_pStatusBar )
    {
        m_pStatusBar->BeginAniPercentage();
    }

    // If necessity to read the header
    if ( GetGenerateHeader() )
    {
        RetValue = ReadLine( HeaderLine );
    }

    // Imports additional information
    if ( !ImportAdditionalInfo() )
    {
        return FALSE;
    }

    // Retreive the number of objects    
    double dForecastedTotalObject = __max( 1, ForecastedTotalObject() );
    
    while ( RetValue && ReadLine( Line ) )
    {
        if ( !ProcessLine( Line ) )
        {
            RetValue = FALSE;
        }

        if ( m_pStatusBar )
        {
            m_pStatusBar->SetCurrentPercentage( (int) ( ( ++Count / dForecastedTotalObject ) * 100 ) );
        }
    }

    // Close the file for further use
    CloseFile();

    if ( m_pStatusBar )
    {
        m_pStatusBar->EndAniPercentage();
    }

    // Call the post import function
    if ( !PostImport() )
    {
        return FALSE;
    }

    return RetValue;
    //## end ZUExport::Import%901558646.body
}

BOOL ZUExport::Synchronize ()
{
    //## begin ZUExport::Synchronize%901558647.body preserve=yes
    return TRUE;
    //## end ZUExport::Synchronize%901558647.body
}

CString ZUExport::GetExportedLine ( CObject* pObj )
{
    //## begin ZUExport::GetExportedLine%901558648.body preserve=yes
    return "";
    //## end ZUExport::GetExportedLine%901558648.body
}

BOOL ZUExport::IsExportedField ( CObject* pObj ) const
{
    //## begin ZUExport::IsExportedField%901558649.body preserve=yes
    return FALSE;
    //## end ZUExport::IsExportedField%901558649.body
}

int ZUExport::ReadLine ( CString& Line )
{
    //## begin ZUExport::ReadLine%901558650.body preserve=yes

    // Nothing into the buffer
    if ( !m_pCurrent )
    {
        // Reads information from the file and
        // fills the buffer
        if ( ReadFileBuffer() <= 0 )
        {
            return 0;
        }
    }

    // The buffer is filled and we have a new occurence
    if ( m_pCurrent )
    {
        // if next return char found
        if ( ( m_pNext=strchr( m_pCurrent, '\n' ) ) )
        {
            // Where \r is found, put end of string char.
            *( m_pNext - 1 ) = 0x00;

            // Copy the line to buffer
            Line = m_pCurrent;

            // Sets current to the next char after the \n pointer
            m_pCurrent = m_pNext+1;
        }
        else
        {
            // It is necessary to read the next buffer
            // and to merge the previous buffer and the new one
            CString EndLine( m_pCurrent );

            // Reads information from the file and
            // fills the buffer
            if ( ReadFileBuffer() <= 0 )
            {
                return 0;
            }

            // Build the final line with the EndLine + the 
            // beginning of the new buffer read
            
            // Locate the next return char
            if ( !( m_pNext = strchr( m_pCurrent, '\n' ) ) )
            {
                return 0;
            }

            // Where \r is found, put end of string char.
            if ( m_pNext != m_pCurrent )
            {
                *( m_pNext - 1 ) = 0x00;

                // Copy the line to buffer
                Line = EndLine + m_pCurrent;
            }
            else
            {
                // Copy the line to buffer
                Line = EndLine.Left( EndLine.GetLength() - 1 );
            }

            // Sets current to the next char after the \n pointer
            m_pCurrent = m_pNext + 1;
            
        }
    }

    return Line.GetLength();
    //## end ZUExport::ReadLine%901558650.body
}

void ZUExport::WriteLine ( CString& Line )
{
    //## begin ZUExport::WriteLine%901558651.body preserve=yes
    m_File.Write( Line, Line.GetLength() );
    //## end ZUExport::WriteLine%901558651.body
}

BOOL ZUExport::OpenFileCreate ()
{
    //## begin ZUExport::OpenFileCreate%901558652.body preserve=yes
    TRY
    {
        // Construct a CFile object in read mode
        if ( !m_File.Open( m_Filename, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate ) )
        {
            return FALSE;
        }
    }
    CATCH( CFileException, e )
    {
        #ifdef _DEBUG
        afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }
    //## end ZUExport::OpenFileCreate%901558652.body
}

BOOL ZUExport::OpenFileRead ()
{
    //## begin ZUExport::OpenFileRead%901558653.body preserve=yes
    TRY
    {
        // Construct a CFile object in read mode
        if ( !m_File.Open( m_Filename, CFile::modeRead | CFile::typeBinary ) )
        {
            return FALSE;
        }
    }
    CATCH( CFileException, e )
    {
        #ifdef _DEBUG
        afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }

    //## end ZUExport::OpenFileRead%901558653.body
}

BOOL ZUExport::CloseFile ()
{
    //## begin ZUExport::CloseFile%901558654.body preserve=yes
    TRY
    {
        m_File.Close();
    }
    CATCH( CFileException, e )
    {
        #ifdef _DEBUG
        afxDump << _T( "File could not be opened " ) << e->m_cause << _T( "\n" );
        #endif

        return FALSE;
    }
    END_CATCH
    {
        return TRUE;
    }
    //## end ZUExport::CloseFile%901558654.body
}

int ZUExport::ReadFileBuffer ()
{
    //## begin ZUExport::ReadFileBuffer%901641546.body preserve=yes
    int ReadChar;

    // Read info from the file
    ReadChar = m_File.Read( m_FileBuffer, sizeof( m_FileBuffer ) - 1 );

    // If char read
    if ( ReadChar )
    {
        // Sets current pointer
        m_pCurrent = m_FileBuffer;
    }

    // Sets end of line
    m_FileBuffer[ReadChar] = 0x00;

    // Returns the number of char read    
    return ReadChar;
    //## end ZUExport::ReadFileBuffer%901641546.body
}

BOOL ZUExport::ProcessLine ( CString Line )
{
    //## begin ZUExport::ProcessLine%901641547.body preserve=yes
    return FALSE;
    //## end ZUExport::ProcessLine%901641547.body
}

CString ZUExport::GetHeaderLine ()
{
    //## begin ZUExport::GetHeaderLine%903091424.body preserve=yes
    return _T( "" );
    //## end ZUExport::GetHeaderLine%903091424.body
}

BOOL ZUExport::StartSynchronization ( int TimeValue )
{
    //## begin ZUExport::StartSynchronization%911381915.body preserve=yes
    // Initialize the time value
    m_TimeSynchronizationValue = TimeValue;

    CFileStatus Status;

    // If the file does not exists, create it
    if ( CFile::GetStatus( m_Filename, Status ) == 0 )
    {
        // If never exists, do an export first
        Export();

        // Get status again
        if ( CFile::GetStatus( m_Filename, Status ) == 0 )
        {
            return FALSE;
        }
    }

    // Stores the file date.
    m_LastFileDate = Status.m_mtime;

    // Create the window for the timer
    // Register a custom WndClass and create a window.
    // This must be done because CBounceWnd has a custom cursor, and
    //  no icon.
    const char* pszExportClass = AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW );
    CRect rect;
    rect.SetRectEmpty();

    if ( !CreateEx( 0,
                    pszExportClass,
                    _T( "" ),
                    WS_POPUP,
                    rect.left,
                    rect.top,
                    rect.right,
                    rect.bottom,
                    NULL,
                    (HMENU)NULL ) )
    {
        return FALSE;
    }

    return TRUE;
    //## end ZUExport::StartSynchronization%911381915.body
}

void ZUExport::EndSynchronization ()
{
    //## begin ZUExport::EndSynchronization%911381916.body preserve=yes
    KillTimer( 1 );
    //## end ZUExport::EndSynchronization%911381916.body
}

void ZUExport::SourceHasBeenModified ()
{
    //## begin ZUExport::SourceHasBeenModified%911404698.body preserve=yes
    m_SourceIsModified = TRUE;
    //## end ZUExport::SourceHasBeenModified%911404698.body
}

BOOL ZUExport::SynchronizationFileUpdated ()
{
    //## begin ZUExport::SynchronizationFileUpdated%911404699.body preserve=yes
    CFileStatus Status;

    // If the file does not exists, create it
    if ( CFile::GetStatus( m_Filename, Status ) == 0 )
    {
        if ( !OpenFileCreate() )
        {
            return FALSE;
        }

        // Closes the file immediatly
        CloseFile();

        // Get status again
        if ( CFile::GetStatus( m_Filename, Status ) == 0 )
        {
            return FALSE;
        }
    }

    // compared the file date
    return m_LastFileDate < Status.m_mtime;
    //## end ZUExport::SynchronizationFileUpdated%911404699.body
}

void ZUExport::AssignSynchronizationFileDate ()
{
    //## begin ZUExport::AssignSynchronizationFileDate%911404700.body preserve=yes
    CFileStatus Status;

    // If the file does not exists, create it
    if ( CFile::GetStatus( m_Filename, Status ) == 0 )
    {
        return;
    }

    // Stores the file date.
    m_LastFileDate = Status.m_mtime;
    //## end ZUExport::AssignSynchronizationFileDate%911404700.body
}

BOOL ZUExport::ExportAdditionalInfo ()
{
    //## begin ZUExport::ExportAdditionalInfo%916336042.body preserve=yes
    return TRUE;
    //## end ZUExport::ExportAdditionalInfo%916336042.body
}

BOOL ZUExport::ImportAdditionalInfo ()
{
    //## begin ZUExport::ImportAdditionalInfo%916336043.body preserve=yes
    return TRUE;
    //## end ZUExport::ImportAdditionalInfo%916336043.body
}

CString ZUExport::BuildLine ( CString Key, CString Value )
{
    //## begin ZUExport::BuildLine%916336044.body preserve=yes
    CString LineBuffer;

    switch ( GetSeparatorType() )
    {
        case CommaSeparator :
        {
            LineBuffer.Format( _T( "%s,%s\r\n" ), (const char*)Key, (const char*)Value );
            break;
        }

        case SemiColumnSeparator :
        {
            LineBuffer.Format( _T( "%s;%s\r\n" ), (const char*)Key, (const char*)Value );
            break;
        }

        case QuoteSeparator :
        {
            LineBuffer.Format( _T( "\"%s\" \"%s\"\r\n" ), (const char*)Key, (const char*)Value );
            break;
        }

        case AutomaticSeparator :
        case TabSeparator :
        default:
        {
            LineBuffer.Format( _T( "%s\t%s\r\n" ), (const char*)Key, (const char*)Value );
            break;
        }
    }

    return LineBuffer;
    //## end ZUExport::BuildLine%916336044.body
}

BOOL ZUExport::PreImport ()
{
    //## begin ZUExport::PreImport%922203356.body preserve=yes
    return TRUE;
    //## end ZUExport::PreImport%922203356.body
}

BOOL ZUExport::PostImport ()
{
    //## begin ZUExport::PostImport%922203357.body preserve=yes
    return TRUE;
    //## end ZUExport::PostImport%922203357.body
}

double ZUExport::ForecastedTotalObject ()
{
    //## begin ZUExport::ForecastedTotalObject%922203364.body preserve=yes
    return 1;
    //## end ZUExport::ForecastedTotalObject%922203364.body
}

BOOL ZUExport::DoExportLoop ()
{
    //## begin ZUExport::DoExportLoop%922203367.body preserve=yes
    return TRUE;
    //## end ZUExport::DoExportLoop%922203367.body
}

BOOL ZUExport::PreExport ()
{
    //## begin ZUExport::PreExport%933007940.body preserve=yes
    return TRUE;
    //## end ZUExport::PreExport%933007940.body
}

BOOL ZUExport::PostExport ()
{
    //## begin ZUExport::PostExport%933007941.body preserve=yes
    return TRUE;
    //## end ZUExport::PostExport%933007941.body
}

// Additional Declarations
//## begin ZUExport%35BCB0140007.declarations preserve=yes
//## end ZUExport%35BCB0140007.declarations

//## begin module%35BCB05A02BB.epilog preserve=yes
void ZUExport::OnTimer(UINT nIDEvent)
{
    // First of all, we have to test if the feed file has been updated
    if ( SynchronizationFileUpdated() )
    {
        Import();
        AssignSynchronizationFileDate();
    }

    // Next, test if the current file has been updated
    if ( m_SourceIsModified )
    {
        Export();
        m_SourceIsModified = FALSE;
        AssignSynchronizationFileDate();
    }

    CWnd::OnTimer( nIDEvent );
}

int ZUExport::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( CWnd::OnCreate(lpCreateStruct) == -1 )
    {
        return -1;
    }
    
    double Elapsed    = __max( 1000,  m_TimeSynchronizationValue * 1000 );
    Elapsed            = __min( 65000, m_TimeSynchronizationValue * 1000 );

    if ( !SetTimer( 1, UINT(Elapsed) , NULL ) )
    {
        // signal creation failure...
        return -1;
    }

    return 0;
}

//## end module%35BCB05A02BB.epilog