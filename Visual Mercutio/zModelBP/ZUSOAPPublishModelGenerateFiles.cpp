// ZUSOAPPublishModelGenerateFiles.cpp: implementation of the ZUSOAPPublishModelGenerateFiles class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSOAPPublishModelGenerateFiles.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ProcGraphModelCtlr.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"

#include "ZBPublishMessengerModelInformation.h"
#include "zSOAP\pPublishSettings.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "ZBBPStartSymbol.h"

#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\File.h"
#include "zWeb\ZDHtmlFile.h"

#include "zConversion\PSS_StringTools.h"

#include "zBaseLib\ZBServer.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// constant
const CString gHomeImageFile    = _T( "home.jpg" );
const CString gParentImageFile    = _T( "parent.gif" );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSOAPPublishModelGenerateFiles::ZUSOAPPublishModelGenerateFiles( ZDProcessGraphModelMdl*                pModel    /*= NULL*/,
                                                                  void*                                    pClass    /*= NULL*/,
                                                                  ZBPublishMessengerModelInformation*    pInfo    /*= NULL*/ )
    : ZUModelNavigation    ( pModel, pClass ),
      m_pModelInfo        ( pInfo )
{
}

ZUSOAPPublishModelGenerateFiles::~ZUSOAPPublishModelGenerateFiles()
{
}

bool ZUSOAPPublishModelGenerateFiles::OnStart()
{
    // Start by casting the info pointer
    m_pInfo = static_cast<ZBInfoModelGraphicGeneration*>( m_pClass );

    if ( m_pModelInfo )
    {
        // Sets the correct address
        pPublishSettings::m_Url = (const char*)m_pModelInfo->m_MessengerAddress;
    }

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    // Create the temp directory
    char szWindowsDirectory[512];
    GetWindowsDirectory( szWindowsDirectory, sizeof( szWindowsDirectory ) );
    m_TargetDirectory = ZDirectory::NormalizeDirectory( szWindowsDirectory ) + _T( "\\tempPSS" );

    ZDirectory::CreateDirectory( m_TargetDirectory );

    // If it doesn't exist, then problem
    if ( !ZDirectory::Exist( m_TargetDirectory ) )
    {
        return false;
    }

    // Change the current directory
    if ( !ZDirectory::ChangeCurrentDirectory( m_TargetDirectory ) )
    {
        return false;
    }

    if ( ZFile::Exist( ZDirectory::NormalizeDirectory( m_pInfo->GetpServer()->GetSystemDirectory() ) + _T( "\\" ) + gHomeImageFile ) )
    {
        if ( m_pf.pubFile( pfile( pfile::publicFolder,
                                  1,
                                  (const char*)m_pInfo->GetpServer()->GetSystemDirectory(),
                                  (const char*)gHomeImageFile ) ) == false )
        {
            TRACE( _T( "Problem publishing gHomeImageFile\n" ) );
        }
    }

    if ( ZFile::Exist( ZDirectory::NormalizeDirectory( m_pInfo->GetpServer()->GetSystemDirectory() ) + _T( "\\" ) + gParentImageFile ) )
    {
        if ( m_pf.pubFile( pfile( pfile::publicFolder,
                                  1,
                                  (const char*)m_pInfo->GetpServer()->GetSystemDirectory(),
                                  (const char*)gParentImageFile ) ) == false )
        {
            TRACE( _T( "Problem publishing gParentImageFile\n" ) );
        }
    }

    // Reset the array of generated filenames
    ResetStringsArray();

    if ( !GenerateModel( m_pModel ) )
    {
        return false;
    }

    // Saves the root html filename
    m_RootHtmlFilename    = BuildModelHTMLFilename( m_pModel );
    m_RootName            = m_pModel->GetAbsolutePath();

    return true;
}

bool ZUSOAPPublishModelGenerateFiles::OnFinish()
{
    // Clean the directory used to generate the files
    ZDirectory::DeleteDirectory( m_TargetDirectory, TRUE, TRUE );

    // Hide the feedback dialog
    m_FileGenerateWindow.ShowWindow( SW_HIDE );

    return true;
}

bool ZUSOAPPublishModelGenerateFiles::OnSymbol( ZBSymbol* pSymbol )
{
    ASSERT( m_pInfo );

    if ( pSymbol->GetChildModel() && m_pInfo->GetpDC() && m_pInfo->GetpCtlr() )
    {
        if ( !GenerateModel( dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetChildModel() ) ) )
        {
            return false;
        }
    }

    return true;
}

bool ZUSOAPPublishModelGenerateFiles::OnLink( ZBLinkSymbol* pLink )
{
    ASSERT( m_pInfo );

    return true;
}

bool ZUSOAPPublishModelGenerateFiles::GenerateModel( ZDProcessGraphModelMdl* pModel )
{
    ASSERT( m_pInfo );

    if ( pModel && m_pInfo->GetpDC() && m_pInfo->GetpCtlr() )
    {
        // Retreive the viewport
        ZIProcessGraphModelViewport* pVp = m_pInfo->GetpCtlr()->BrowseModel( pModel, pModel->GetParent() );

        // If a valid viewport, then generate the filename
        if ( pVp )
        {
            // Export the model to the image filename
            CString ImageFilename = BuildModelImageFilename( pModel );

            // Refresh Setup Copyfile Window
            m_FileGenerateWindow.SetDestination( ImageFilename );
            m_FileGenerateWindow.UpdateWindow();
            MSG msg;

            if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
            {
                GetMessage( &msg, NULL, NULL, NULL );
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }

            // Check if the image has already been generated
            // this is to avoid generating twice the same image
            // it takes time and it will optimize the generation
            if ( !StringAlreadyGenerated( ImageFilename ) )
            {
                // Generate the file
                if ( pVp->ExportModelToImageFile( ImageFilename, *m_pInfo->GetpDC() ) )
                {
                    ZFile file( ImageFilename );

                    // Now publish the filename
                     if ( m_pf.pubFile( pfile( pfile::publicFolder,
                                              1,
                                              (const char*)m_TargetDirectory,
                                              (const char*)file.GetFileName() ) ) == false )
                    {
                        TRACE1( _T( "Problem publishing the file %s\n" ), (const char*)ImageFilename );
                    }
                }
                else
                {
                    TRACE1( _T( "Problem exporting the file %s\n" ), (const char*)ImageFilename );
                }
            }

            // Create the html page
            CreateHtmlPage( pModel, ImageFilename );

            return true;
        }
    }

    return false;
}

CString ZUSOAPPublishModelGenerateFiles::BuildModelImageFilename( ZDProcessGraphModelMdl* pModel )
{
    // Build the filename using the full object path
    CString Filename = ZDirectory::NormalizeDirectory( m_TargetDirectory ) + _T( "\\" );
    Filename        += ParseModelName( pModel->GetAbsolutePath() );
    Filename        += _T( ".jpg" );

    return Filename;
}

CString ZUSOAPPublishModelGenerateFiles::BuildModelHTMLFilename( ZDProcessGraphModelMdl* pModel )
{
    // Build the filename using the full object path
    CString Filename = ZDirectory::NormalizeDirectory( m_TargetDirectory ) + _T( "\\" );
    Filename        += ParseModelName( pModel->GetAbsolutePath() );
    Filename        += _T( ".htm" );

    return Filename;
}

CString ZUSOAPPublishModelGenerateFiles::ParseModelName( CString ModelName )
{
    return PSS_StringTools::ConvertSpecialChar( ModelName );
}

bool ZUSOAPPublishModelGenerateFiles::CreateHtmlPage( ZDProcessGraphModelMdl* pModel, const CString ImageFilename )
{
    CString HtmlFilename = BuildModelHTMLFilename( pModel );
    ZFile htmlFile( HtmlFilename );
    ZFile rootHtmlFile( m_RootHtmlFilename );

    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( HtmlFilename );
    m_FileGenerateWindow.UpdateWindow();
    MSG msg;

    if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
    {
        GetMessage( &msg, NULL, NULL, NULL );
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if ( StringAlreadyGenerated( HtmlFilename ) )
    {
        return true;
    }

    ZDHtmlFile HtmlFile( HtmlFilename );
    
    if ( !HtmlFile.OpenFileCreate() )
    {
        return false;
    }

    // Write header
    CString s;

    s.Format( IDS_SOAPMODELGENHTML_1,
              (const char*)pModel->GetAbsolutePath(),                        // Model path
              (const char*)ZBDate::GetToday().GetStandardFormatedDate() );    // Current date

    HtmlFile << s;

    s.LoadString( IDS_SOAPMODELGENHTML_14 );
    HtmlFile << s;

    // Write the navigation table header
    s.LoadString( IDS_SOAPMODELGENHTML_6 );
    HtmlFile << s;

    // Write the ref to root
    s.Format( IDS_SOAPMODELGENHTML_7,
              (const char*)rootHtmlFile.GetFileName(),    // Root filename
              (const char*)gHomeImageFile,                // Logo filename
              (const char*)rootHtmlFile.GetFileName(),    // Root filename
              (const char*)m_RootName );                // Root name

    HtmlFile << s;

    // Write the parent if there is one
    if ( pModel->GetParent() )
    {
        // Retreive the parent html filename and name
        CString ParentHtmlFilename = BuildModelHTMLFilename( pModel->GetParent() );
        ZFile parentHtmlFile( ParentHtmlFilename );

        CString ParentName = pModel->GetParent()->GetAbsolutePath();

        s.Format( IDS_SOAPMODELGENHTML_11,
                  (const char*)parentHtmlFile.GetFileName(),    // Root filename
                  (const char*)gParentImageFile,                // Logo filename
                  (const char*)parentHtmlFile.GetFileName(),    // Root filename
                  (const char*)ParentName );                    // Root name

        HtmlFile << s;
    }
    else
    {
        s.LoadString( IDS_SOAPMODELGENHTML_8 );
        HtmlFile << s;
    }

    // Write the navigation table footer
    s.LoadString( IDS_SOAPMODELGENHTML_9 );
    HtmlFile << s;

    // Write the break line
    s.LoadString( IDS_SOAPMODELGENHTML_10 );
    HtmlFile << s;

    // Write the hotspot table header
    ZFile image( ImageFilename );

    s.Format( IDS_SOAPMODELGENHTML_2,
              (const char*)pModel->GetAbsolutePath(),    // Object name
              (const char*)image.GetFileName() );        // Image file

    HtmlFile << s;

    // Write all hot spots. Run throught the model elements and write the hotspot entities
    CString    SymbolHtmlFilename;
    CRect    SymbolCoordinates;

    // Process the model components
    CODComponentSet* pSet = pModel->GetComponents();

    for ( int i = 0; i < pSet->GetSize(); ++i )
    {
        CODComponent* pComp = pSet->GetAt( i );

        if ( !pComp )
        {
            continue;
        }

        // If has a sub-model defined
        if ( ISA( pComp, ZBSymbol ) && ( (ZBSymbol*)pComp )->GetChildModel() )
        {
            // Retreive the html filename for the reference
            SymbolHtmlFilename =
                BuildModelHTMLFilename( reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pComp )->GetChildModel() ) );

            ZFile symbol( SymbolHtmlFilename );

            // And then, retreive the symbol position
            SymbolCoordinates = pComp->GetBaseRgn().GetBounds();

            s.Format( IDS_SOAPMODELGENHTML_3,
                      SymbolCoordinates.left,
                      SymbolCoordinates.top,
                      SymbolCoordinates.right,
                      SymbolCoordinates.bottom,
                      (const char*)symbol.GetFileName() );

            HtmlFile << s;
        }
        // If it is a start symbol, then create the hot spot for starting a new process
        else if ( ISA( pComp, ZBSymbol ) && ISA( pComp, ZBBPStartSymbol ) )
        {
            // And then, retreive the symbol position
            SymbolCoordinates = pComp->GetBaseRgn().GetBounds();

            s.Format( IDS_SOAPMODELGENHTML_17,
                      SymbolCoordinates.left,
                      SymbolCoordinates.top,
                      SymbolCoordinates.right,
                      SymbolCoordinates.bottom,
                      dynamic_cast<ZBBPStartSymbol*>( pComp )->GetSymbolReferenceNumber() );

            HtmlFile << s;
        }
    }

    // Write the hotspot table footer
    s.LoadString( IDS_SOAPMODELGENHTML_4 );
    HtmlFile << s;

    // Write the footer
    s.LoadString( IDS_SOAPMODELGENHTML_5 );
    HtmlFile << s;

    HtmlFile.CloseFile();

#ifdef _DEBUG
    s.Format( _T( " HTML File = %s\n" ), (const char*)HtmlFilename );
    TRACE( s );
#endif

    // Now publish the filename
    if ( m_pLog && m_pLog->IsInDebugMode() )
    {
        CString message;
        message.Format( IDS_AL_PUBLISHHTMLFILE, (const char*)HtmlFilename );
        ZBGenericSymbolErrorLine e( message );
        m_pLog->AddLine( e );
    }

    ZFile file( HtmlFilename );

     if ( m_pf.pubFile( pfile( pfile::publicFolder,
                              1,
                              (const char*)m_TargetDirectory,
                              (const char*)file.GetFileName() ) ) == false )
    {
        TRACE( _T( "Problem publishing gPrinterImageFile\n" ) );
    }

    return true;
}
