// ZUModelGenerateImageFiles.cpp: implementation of the ZUModelGenerateImageFiles class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUModelGenerateImageFiles.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ProcGraphModelCtlr.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"

#include "zModel\ZUExtractModelUnitGroupAssigned.h"
#include "zModel\ZUExtractModelLogicalSystemAssigned.h"
// JMR-MODIF - Le 20 février 2006 - Ajout de l'en-tête ZUExtractModelLogicalPrestationsAssigned.
#include "zModel\ZUExtractModelLogicalPrestationsAssigned.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"
#include "zModel\ZBLogicalSystemEntity.h"

// JMR-MODIF - Le 20 février 2006 - Ajout de l'en-tête ZBLogicalPrestationsEntity.
#include "zModel\ZBLogicalPrestationsEntity.h"

// JMR-MODIF - Le 16 janvier 2007 - Ajout de l'en-tête ZBLogicalRulesEntity.
#include "zModel\ZBLogicalRulesEntity.h"

#include "zBaseLib\ZBServer.h"
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\File.h"
#include "zWeb\ZDHtmlFile.h"

#include "zConversion\ZUStringConversion.h"
#include "zBaseLib\ZUStringFormater.h"

#include "zBaseLib\ZAGlobal.h"

#include "zModel\zModelRes.h"
#include "zRMdlBP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 23 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// constant
const CString gLogoImageFile                = _T( "processsoft.jpg" );
const CString gHomeImageFile                = _T( "home.jpg" );
const CString gParentImageFile                = _T( "parent.gif" );
const CString gPrinterImageFile                = _T( "printer.jpg" );
const CString g1pTransImageFile                = _T( "1ptrans.gif" );

const CString gMinusImageFile                = _T( "minus.gif" );
const CString gPlusImageFile                = _T( "plus.gif" );

const CString gUsersImageFile                = _T( "users.gif" );
const CString gLogicalSystemImageFile        = _T( "lgs.gif" );
// JMR-MODIF - Le 21 février 2006 - Ajout de la nouvelle référence au fichier d'image des prestations.
const CString gLogicalPrestationsImageFile    = _T( "prest.gif" );
const CString gTreeCSSFile                    = _T( "tree.css" );
const CString gTreeJSFile                    = _T( "tree.js" );

const CString gAJLibJSFile                    = _T( "ajlib.js" );
const CString gAJPopupJSFile                = _T( "ajpopup.js" );
const CString gAJPopupCSSFile                = _T( "ajpopup.css" );

const CString gWhite                        = _T( "White" );

const CString gPSSRightTarget                = _T( "_pssRightFrame" );
const CString gPSSLeftTarget                = _T( "_pssLeftFrame" );
const CString gPSSMainTarget                = _T( "_pssMain" );
const CString gBlankTarget                    = _T( "_blank" );
const CString gTopTarget                    = _T( "_top" );
const CString gBottomTarget                    = _T( "_bottom" );
const CString gLeftTarget                    = _T( "_left" );
const CString gRightTarget                    = _T( "_right" );

//////////////////////////////////////////////////////////////////////
// static variables
size_t ZUModelGenerateImageFiles::m_IndexItem = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUModelGenerateImageFiles::ZUModelGenerateImageFiles( ZDProcessGraphModelMdl*    pModel            /*= NULL*/,
                                                      void*                        pClass            /*= NULL*/,
                                                      ZBPropertyAttributes*        pPropAttributes    /*= NULL*/ )
    : ZUModelNavigation( pModel, pClass ),
      m_pPropAttributes( pPropAttributes )
{
}

ZUModelGenerateImageFiles::~ZUModelGenerateImageFiles()
{
}

bool ZUModelGenerateImageFiles::OnStart()
{
    // Start by casting the info pointer
    m_pInfo = static_cast<ZBInfoModelGraphicGeneration*>( m_pClass );

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    // Create the image directory
    m_ImageDirectory = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\images" );
    ZDirectory::CreateDirectory( m_ImageDirectory );

    if ( !ZDirectory::Exist( m_ImageDirectory ) )
    {
        return false;
    }

    // Create the image directory
    m_IncludeDirectory = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\includes" );
    ZDirectory::CreateDirectory( m_IncludeDirectory );

    if ( !ZDirectory::Exist( m_IncludeDirectory ) )
    {
        return false;
    }
    
    // Get the web directory
    CString WebDir = ZAGlobal::GetApplicationDirectory() + _T( "\\Web" );

    // Now copy images from the system root directory
    if ( m_pInfo->GetpServer() )
    {
        if ( m_pInfo->GetImageFilename().IsEmpty() )
        {
            ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gLogoImageFile );
            m_InternalLogoFilename.Empty();
        }
        else
        {
            ZFile file( m_pInfo->GetImageFilename() );
            m_InternalLogoFilename = file.GetFileName ();
            ZDirectory::CopyFileFromToDirectory( file.GetFilePath(), m_ImageDirectory, m_InternalLogoFilename );
        }

        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gHomeImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gParentImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gPrinterImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, g1pTransImageFile );

        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gMinusImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gPlusImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gUsersImageFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gLogicalSystemImageFile );
        // JMR-MODIF - Le 20 février 2006 - Ajout du code pour la copie du nouveau fichier image.
        ZDirectory::CopyFileFromToDirectory( WebDir, m_ImageDirectory, gLogicalPrestationsImageFile );

        ZDirectory::CopyFileFromToDirectory( WebDir, m_IncludeDirectory, gTreeCSSFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_IncludeDirectory, gTreeJSFile );

        ZDirectory::CopyFileFromToDirectory( WebDir, m_IncludeDirectory, gAJLibJSFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_IncludeDirectory, gAJPopupJSFile );
        ZDirectory::CopyFileFromToDirectory( WebDir, m_IncludeDirectory, gAJPopupCSSFile );
    }

    if ( !GenerateIndexPage( m_pModel ) )
    {
        return false;
    }

    if ( !GenerateBannerPage( m_pModel ) )
    {
        return false;
    }

    if ( !GenerateEmptyPropertyPage() )
    {
        return false;
    }

    if ( !GenerateModel( m_pModel ) )
    {
        return false;
    }
    
    // Reset all members
    return ( m_pInfo ) ? true : false;
}

bool ZUModelGenerateImageFiles::OnFinish()
{
    // Hide the feedback dialog
    m_FileGenerateWindow.ShowWindow( SW_HIDE );

    return true;
}

bool ZUModelGenerateImageFiles::OnSymbol( ZBSymbol* pSymbol )
{
    ASSERT( m_pInfo );

    // Generate the property html page
    CODModel* pOwnerModel = pSymbol->GetOwnerModel();

    // Build the html filename
    CString HtmlFilename = BuildSymbolPropertyHTMLFilename( pSymbol,
                                                            ( pOwnerModel && ISA( pOwnerModel, ZDProcessGraphModelMdl ) ) ? dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel ) : m_pModel );

    if ( !GeneratePropertyPage( pSymbol, HtmlFilename ) )
    {
        return false;
    }

    if ( pSymbol->GetChildModel() && m_pInfo->GetpDC() && m_pInfo->GetpCtlr() )
    {
        if ( !GenerateModel( dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetChildModel() ) ) )
        {
            return false;
        }

        // Generate the html page contained at the model root
        if ( dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetChildModel() )->GetPageSet() != NULL )
        {
            ZBProcessGraphPageIterator i( dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetChildModel() )->GetPageSet() );

            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Do process itself
                if ( pPage->GetpModel() &&
                     pPage->GetpModel() != dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetChildModel() ) )
                {
                    if ( !GenerateModel( dynamic_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ) ) )
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool ZUModelGenerateImageFiles::OnLink( ZBLinkSymbol* pLink )
{
    ASSERT( m_pInfo );

    // Generate the property html page
    CODModel* pOwnerModel = pLink->GetOwnerModel();

    // Build the html filename
    CString HtmlFilename = BuildSymbolPropertyHTMLFilename( pLink,
                                                            ( pOwnerModel && ISA( pOwnerModel, ZDProcessGraphModelMdl ) ) ? dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel ) : m_pModel );
    
    if ( !GeneratePropertyPage( pLink, HtmlFilename ) )
    {
        return false;
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateModel( ZDProcessGraphModelMdl* pModel )
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
                pVp->ExportModelToImageFile( ImageFilename, *m_pInfo->GetpDC() );
            }

            CreateHtmlPage( pModel, ImageFilename );

            return true;
        }
    }

    return false;
}

CString ZUModelGenerateImageFiles::BuildModelImageFilename( ZDProcessGraphModelMdl* pModel )
{
    // Build the filename using the full object path
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    Filename += ParseModelName( pModel->GetAbsolutePath() );
    Filename += _T( ".jpg" );

    return Filename;
}

CString ZUModelGenerateImageFiles::BuildMainFrameModelHTMLFilename( ZDProcessGraphModelMdl* pModel )
{
    return BuildModelHTMLFilename( pModel, _T( "mainfrm_" ) );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameIndex()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\index.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameBanner()
{
    // Build the main banner html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\banner.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameUserMainFrame()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\users_mainframe.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameSystemMainFrame()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\system_mainframe.htm" );
}

// JMR-MODIF - Le 20 février 2006 - Obtient le nom du fichier principal du système de prestations.
CString ZUModelGenerateImageFiles::BuildModelHTMLFilenamePrestationsMainFrame()
{
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\prestations_mainframe.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameEmptyUser()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\empty_users.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameEmptySystem()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\empty_system.htm" );
}

// JMR-MODIF - Le 20 février 2006 - Obtient le nom de fichier du système de prestations par défaut.
CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameEmptyPrestations()
{
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\empty_prestations.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameEmptyPropertyPage()
{
    // Build the main index html filename 
    return ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\empty_prp.htm" );
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilename( ZDProcessGraphModelMdl*    pModel,
                                                           const CString            Prefix    /*= ""*/ )
{
    // Build the filename using the full object path
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );

    if ( !Prefix.IsEmpty() )
    {
        Filename += Prefix;
    }

    Filename += ParseModelName( pModel->GetAbsolutePath() );
    Filename += _T( ".htm" );

    return Filename;
}

CString ZUModelGenerateImageFiles::BuildModelHTMLFilenameForPrinter( ZDProcessGraphModelMdl* pModel )
{
    // Build the filename using the full object path
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    Filename += ParseModelName( pModel->GetAbsolutePath() );
    Filename += _T( "_prt" );
    Filename += _T( ".htm" );

    return Filename;
}

CString ZUModelGenerateImageFiles::BuildLogicalSystemHTMLFilename( ZBSystemEntity* pSystemEntity )
{
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    CString EntityString;

    do
    {
        EntityString += pSystemEntity->GetEntityName();
        EntityString += _T( "_" );

        // Retreive the parent
        pSystemEntity = pSystemEntity->GetParent();
    }
    while ( pSystemEntity );

    Filename += ParseModelName( EntityString );
    Filename += _T( ".htm" );

    return Filename;
}

// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction de génération des titres de pages pour les prestations.
CString ZUModelGenerateImageFiles::BuildLogicalPrestationsHTMLFilename( ZBPrestationsEntity* pPrestationsEntity )
{
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    CString EntityString;

    do
    {
        EntityString += pPrestationsEntity->GetEntityName();
        EntityString += _T( "_" );

        // Retreive the parent
        pPrestationsEntity = pPrestationsEntity->GetParent();
    }
    while ( pPrestationsEntity );

    Filename += ParseModelName( EntityString );
    Filename += _T( ".htm" );

    return Filename;
}

CString ZUModelGenerateImageFiles::BuildUserHTMLFilename( ZBUserEntity* pUserEntity )
{
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    CString EntityString;

    do
    {
        EntityString += pUserEntity->GetEntityName();
        EntityString += _T( "_" );

        // Retreive the parent
        pUserEntity = pUserEntity->GetParent();
    }
    while ( pUserEntity );

    Filename += ParseModelName( EntityString );
    Filename += _T( ".htm" );

    return Filename;
}

CString ZUModelGenerateImageFiles::BuildSymbolPropertyHTMLFilename( ZIBasicSymbol*            pBasicSymbol,
                                                                    ZDProcessGraphModelMdl*    pModel,
                                                                    const CString            Prefix        /*= ""*/ )
{
    // Build the filename using the full object path + the symbol name and the reference number
    // to avoid collision
    CString Filename = ZDirectory::NormalizeDirectory( m_pInfo->GetURLName() ) + _T( "\\" );
    Filename += _T( "prp_" );

    if ( !Prefix.IsEmpty() )
    {
        Filename += Prefix;
    }

    Filename += ParseModelName( pModel->GetAbsolutePath() );
    Filename += _T( "_" );
    Filename += ParseModelName( pBasicSymbol->GetSymbolName() + pBasicSymbol->GetSymbolReferenceNumberStr() );
    Filename += _T( ".htm" );

    return Filename;
}

// JMR-MODIF - Le 6 mars 2006 - Fonction de génération de nom de fichier valide pour les pages du rapport Conceptor.
CString ZUModelGenerateImageFiles::BuildConceptorHTMLFilename( CString EntityName )
{
    CString sFilename     = _T( "Conceptor_" );
    sFilename            += ParseModelName( EntityName );
    sFilename            += _T( ".htm" );

    return sFilename;
}

// JMR-MODIF - Le 6 mars 2006 - Fonction de génération de nom de fichier valide pour les pages du rapport processus.
CString ZUModelGenerateImageFiles::BuildProcessReportHTMLFilename( CString ProcessName )
{
    CString sFilename     = _T( "ProcessReport_" );
    sFilename            += ParseModelName( ProcessName );
    sFilename            += _T( ".htm" );

    return sFilename;
}

// JMR-MODIF - Le 15 mars 2006 - Fonction de génération de nom de fichier pour les pages du rapport prestations.
CString ZUModelGenerateImageFiles::BuildPrestationsReportHTMLFilename( CString PrestationName )
{
    CString sFilename     = _T( "PrestationsReport_" );
    sFilename            += ParseModelName( PrestationName );
    sFilename            += _T( ".htm" );

    return sFilename;
}

CString ZUModelGenerateImageFiles::ParseModelName( CString ModelName )
{
    return ZUStringConversion::ConvertSpecialChar( ModelName );
}

CString ZUModelGenerateImageFiles::CalculatePath( CString Filename, CString RefFilename )
{
    if ( m_pInfo->GetAbsolutePath() || Filename.IsEmpty() )
    {
        return Filename;
    }

    // If in relative path
    // then, run through the path and replace its location
    ZFile refFile( RefFilename );
    ZFile File( Filename );

    CString sRefFilename( refFile.GetFilePath() );
    LPTSTR pRef = sRefFilename.GetBuffer( sRefFilename.GetLength() );

    CString sFilename( File.GetFilePath() );
    LPTSTR pFile = sFilename.GetBuffer( sFilename.GetLength() );

    CString ShortFilename = File.GetFileName();

    // Run through the directory till different
    while ( *pRef && *pFile && *pRef == *pFile )
    {
        ++pFile;
        ++pRef;
    }

    // If we are in the same directory
    // returns the filename only
    if ( !*pRef && !*pFile )
    {
        sRefFilename.ReleaseBuffer( -1 );
        sFilename.ReleaseBuffer( -1 );
        return ShortFilename;
    }

    // If the ref file is at the end only, then the destination 
    // is just below the initial reference file
    if ( !*pRef )
    {
        CString FinalFile( pFile );
        sRefFilename.ReleaseBuffer( -1 );
        sFilename.ReleaseBuffer( -1 );
        return ReplaceBackSlash( FinalFile + ShortFilename );
    }

    // If the file is at the end only, then the destination is upper
    if ( !*pFile )
    {
        // Now count the remaining directory and replace them by .. backslash
        CString RelativePath;

        while ( *pRef++ )
        {
            if ( *pRef == '\\' )
            {
                RelativePath += _T( "../" );
            }
        }

        sRefFilename.ReleaseBuffer( -1 );
        sFilename.ReleaseBuffer( -1 );

        return ReplaceBackSlash( RelativePath + ShortFilename );
    }

    // Otherwise, we have to go back and after go down
    // Go back to top by replacing directory by .. backslash
    CString RelativePath;

    while ( *pRef++ )
    {
        if ( *pRef == '\\' )
        {
            RelativePath += _T( "../" );
        }
    }

    CString CompletePath = RelativePath + pFile;
    sRefFilename.ReleaseBuffer( -1 );
    sFilename.ReleaseBuffer( -1 );

    return ReplaceBackSlash( CompletePath );
}

CString ZUModelGenerateImageFiles::ReplaceBackSlash( CString CompleteFile )
{
    LPTSTR pFile = CompleteFile.GetBuffer( CompleteFile.GetLength() + 1 );

    for ( ; *pFile; ++pFile )
    {
        if ( *pFile == '\\' )
        {
            *pFile = '/';
        }
    }

    CompleteFile.ReleaseBuffer( -1 );

    return CompleteFile;
}

CString ZUModelGenerateImageFiles::ReplaceSpecialCharInString( CString s )
{
    LPTSTR pStr = s.GetBuffer( s.GetLength() + 1 );

    for ( ; *pStr; ++pStr )
    {
        if ( *pStr == '\t' || *pStr == '\r' || *pStr == '\n' )
        {
            *pStr = ' ';
        }
    }

    s.ReleaseBuffer( -1 );

    return s;
}
//---------------------------------------------------------------------------
bool ZUModelGenerateImageFiles::CreateHtmlPage(ZDProcessGraphModelMdl* pModel, const CString imageFilename)
{
    CString htmlFilename           = BuildModelHTMLFilename(pModel);
    CString htmlFilenameForPrinter = BuildModelHTMLFilenameForPrinter(pModel);
    
    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(htmlFilename);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if (!StringAlreadyGenerated(htmlFilename))
    {
        ZDHtmlFile htmlFile(htmlFilename);
        
        if (!htmlFile.OpenFileCreate())
            return false;

        // write header
        CString s;
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),                        // Model path
                 (const char*)ZBDate::GetToday().GetStandardFormatedDate() );    // Current date
        htmlFile << s;

        // build the CSS filename
        CString ajPopupCSSFilename = m_IncludeDirectory + _T("\\") + gAJPopupCSSFile;
        s.Format(IDS_MODELGENHTML_50,
                 (const char*)CalculatePath(ajPopupCSSFilename, htmlFilename));
        htmlFile << s;

        // build the ajlib javascript filename
        CString ajLibJSFilename = m_IncludeDirectory + _T("\\") + gAJLibJSFile;
        s.Format(IDS_MODELGENHTML_52,
                 (const char*)CalculatePath(ajLibJSFilename, htmlFilename));
        htmlFile << s;

        // build the ajpopup javascript filename
        CString ajPopupJSFilename = m_IncludeDirectory + _T("\\") + gAJPopupJSFile;
        s.Format(IDS_MODELGENHTML_52,
                 (const char*)CalculatePath(ajPopupJSFilename, htmlFilename));
        htmlFile << s;

        // ************************************************************************************************************
        // JMR-MODIF - Le 5 juillet 2005 - Adaptation de la page : L'action du click et l'action du passage
        // sur un objet sont croisées.

        // Build the javascript for onload function
//        s.Format( IDS_MODELGENHTML_73,
//                    (const char*)CalculatePath( BuildModelHTMLFilenameEmptyPropertyPage(), HtmlFilename ));

        // inscrit l'en-tête JavaScript
        s.LoadString(IDS_MODELGENHTML_79);
        htmlFile << s;

        CODComponentSet* pSet = pModel->GetComponents();

        // set the object counter
        int objectCounter = 1;

        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            if (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol))
            {
                s.Format(IDS_MODELGENHTML_86, objectCounter);
                htmlFile << s;
                ++objectCounter;
            }
        }

        s.LoadString(IDS_MODELGENHTML_87);
        htmlFile << s;

        // reset the object counter
        objectCounter = 1;

        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            if (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol))
            {
                s.Format(IDS_MODELGENHTML_82, objectCounter, objectCounter, objectCounter);
                htmlFile << s;
                ++objectCounter;
            }
        }

        s.LoadString(IDS_MODELGENHTML_83);
        htmlFile << s;

        // reset the object counter
        objectCounter = 1;

        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            if (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol))
            {
                // if no sub-model, just the area for the popup
                CODModel* pOwnerModel = dynamic_cast<ZIBasicSymbol*>(pComp)->GetOwnerModel();

                s.Format(IDS_MODELGENHTML_84, objectCounter);

                htmlFile << s;

                s.Format(IDS_MODELGENHTML_88,
                         (const char*)CalculatePath(BuildSymbolPropertyHTMLFilename(dynamic_cast<ZIBasicSymbol*>(pComp),
                                                                                   (pOwnerModel && ISA(pOwnerModel, ZDProcessGraphModelMdl)) ? dynamic_cast<ZDProcessGraphModelMdl*>(pOwnerModel) : pModel),
                                                                                    htmlFilename));

                htmlFile << s;

                s.Format(IDS_MODELGENHTML_89,
                         objectCounter,
                         objectCounter,
                         objectCounter,
                         objectCounter);

                htmlFile << s;

                ++objectCounter;
            }
        }

        // inscrit la fin du bloc JavaScript.
        s.LoadString(IDS_MODELGENHTML_90);
        htmlFile << s;
        // ************************************************************************************************************

        // end of head and body
        s.LoadString(IDS_MODELGENHTML_51);
        htmlFile << s;

        // write the navigation table header
        s.LoadString(IDS_MODELGENHTML_6);
        htmlFile << s;

        CString logoImage;

        // write the parent if there is one
        if (pModel->GetParent())
        {
            // retreive the parent html filename and name
            CString parentHtmlFilename = BuildModelHTMLFilename( pModel->GetParent() );
            CString parentName         = pModel->GetParent()->GetAbsolutePath();
            logoImage                  = m_ImageDirectory + _T("\\") + gParentImageFile;

            s.Format(IDS_MODELGENHTML_11,
                     (const char*)CalculatePath(parentHtmlFilename, htmlFilename), // Root filename
                     (const char*)CalculatePath(logoImage,          htmlFilename), // logo complete filename
                     (const char*)CalculatePath(parentHtmlFilename, htmlFilename), // Root filename
                     (const char*)parentName);                                     // Root name 

            htmlFile << s;
        }
        else
        {
            // retreive the parent html filename and name
            CString parentName = _T("Index");
            logoImage          = m_ImageDirectory + _T("\\") + gHomeImageFile;

            s.Format(IDS_MODELGENHTML_85,
                     (const char*)CalculatePath(m_IndexHtmlFilename, htmlFilename), // Root filename
                     (const char*)CalculatePath(logoImage,           htmlFilename), // logo complete filename
                     (const char*)CalculatePath(m_IndexHtmlFilename, htmlFilename), // Root filename
                     (const char*)parentName);                                      // Root name 

            htmlFile << s;
        }

        // write the print facilities
        logoImage = m_ImageDirectory + _T("\\") + gPrinterImageFile;
        s.Format(IDS_MODELGENHTML_15,
                 (const char*)CalculatePath(htmlFilenameForPrinter, htmlFilename),  // The printable filename
                 (const char*)CalculatePath(logoImage,              htmlFilename)); // logo complete filename
        htmlFile << s;

        // Write the navigation table footer
        s.LoadString(IDS_MODELGENHTML_9);
        htmlFile << s;

        // create all the popups for all symbols

        // Javascript starts here
        s.LoadString(IDS_MODELGENHTML_53);
        htmlFile << s;

        // create a dummy object to avoid copyright on the first object
        if (true)
        {
            s.Format(IDS_MODELGENHTML_55, 0); // Allocate the new popup object
            htmlFile << s;

            s.Format(IDS_MODELGENHTML_57, 0, _T("")); 
            htmlFile << s;

            s.Format(IDS_MODELGENHTML_58, 0, _T("")); 
            htmlFile << s;

            s.Format(IDS_MODELGENHTML_61, 0); // Create the new popup object
            htmlFile << s;
        }

        objectCounter = 1;

        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            // for all symbols, create a popup 
            if (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol))
            {
                s.Format(IDS_MODELGENHTML_55, objectCounter);    // Allocate the new popup object
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_57,
                         objectCounter,    // The header is the symbol name
                         (const char*)ReplaceSpecialCharInString(dynamic_cast<ZIBasicSymbol*>(pComp)->GetSymbolName()));
                htmlFile << s;

                CString dummy;
                dummy.Format(IDS_SYMBOLDESCRIPTION_HTML, dynamic_cast<ZIBasicSymbol*>(pComp)->GetSymbolComment());

                s.Format(IDS_MODELGENHTML_58,
                         objectCounter,    // The text is the symbol description
                         (const char*)ReplaceSpecialCharInString(dummy)); 

                htmlFile << s;

                dummy.Format(IDS_SYMBOLREF_HTML,
                             dynamic_cast<ZIBasicSymbol*>(pComp)->GetSymbolReferenceNumber());

                s.Format(IDS_MODELGENHTML_58,
                         objectCounter,    // The text is the symbol description
                         (const char*)dummy); 

                htmlFile << s;

                // test if has an external document
                if ((ISA(pComp, ZBSymbol)     && dynamic_cast<ZBSymbol*>(pComp)->AcceptExtFile()) ||
                    (ISA(pComp, ZBLinkSymbol) && dynamic_cast<ZBLinkSymbol*>(pComp)->AcceptExtFile()))
                    for (std::size_t idx = 0; idx < dynamic_cast<ZBExtFilePropertyMgr*>(pComp)->GetExtFileCount(); ++idx)
                    {
                        // for each link, create a link with a blank target
                        ZBExtFileProperties* pFileProperty =
                                dynamic_cast<ZBExtFilePropertyMgr*>(pComp)->GetExtFileProperty(idx);

                        if (pFileProperty)
                        {
                            dummy.Format(IDS_SYMBOLEXTFILE_HTML, idx + 1, (const char*)pFileProperty->GetFileTitle());

                            s.Format(IDS_MODELGENHTML_60,
                                     objectCounter,                                               // The object number
                                     (const char*)dummy,                                          // The file title
                                     (const char*)ReplaceBackSlash(pFileProperty->GetFilename()), // The file path
                                     (const char*)gBlankTarget);                                  // The target frame

                            htmlFile << s;
                        }
                    }

                // if has a unit defined, insert the unit link
                if ((ISA(pComp, ZBSymbol)      && dynamic_cast<ZBSymbol*>(pComp)->HasUnit()) ||
                    (ISA(pComp, ZBLinkSymbol ) && dynamic_cast<ZBLinkSymbol*>(pComp)->HasUnit()))
                {
                    ZBUserEntity* pUserEntity =
                            pModel->GetMainUserGroup()->FindGroupByGUID(dynamic_cast<ZIBasicSymbol*>(pComp)->GetUnitGUID(), true);

                    if (pUserEntity && ISA(pUserEntity, ZBUserGroupEntity))
                    {
                        dummy.Format(IDS_SYMBOLUNIT_HTML, (const char*)dynamic_cast<ZIBasicSymbol*>(pComp)->GetUnitName());

                        s.Format(IDS_MODELGENHTML_59,
                                 objectCounter,      // The object number
                                 (const char*)dummy, // The file title
                                 (const char*)CalculatePath(BuildUserHTMLFilename(dynamic_cast<ZBUserGroupEntity*>(pUserEntity)),
                                 htmlFilename)); // The file path

                        htmlFile << s;
                    }
                }

                // if has a system defined, insert the system link
                if ((ISA(pComp, ZBSymbol)     && dynamic_cast<ZBSymbol*>(pComp)->AcceptExtApp()) ||
                    (ISA(pComp, ZBLinkSymbol) && dynamic_cast<ZBLinkSymbol*>(pComp)->AcceptExtApp()))
                    for (std::size_t idx = 0; idx < dynamic_cast<ZBExtAppPropertyMgr*>(pComp)->GetExtAppCount(); ++idx)
                    {
                        // for each link, create a link with a blank target
                        ZBExtAppProperties* pAppProperty = dynamic_cast<ZBExtAppPropertyMgr*>(pComp)->GetExtAppProperty(idx);

                        if (pAppProperty)
                        {
                            ZBSystemEntity* pSystemEntity =
                                    pModel->GetMainLogicalSystem()->FindSystemByGUID(pAppProperty->GetCommandParameters().Right(pAppProperty->GetCommandParameters().GetLength() - gLogicalSystemKey.GetLength()), true);

                            if (pSystemEntity && ISA(pSystemEntity, ZBLogicalSystemEntity))
                            {
                                dummy.Format(IDS_SYMBOLEXTAPP_HTML,
                                             idx + 1,
                                             (const char*)pAppProperty->GetCommandTitle());

                                s.Format(IDS_MODELGENHTML_59,
                                         objectCounter,      // The object number
                                         (const char*)dummy, // The file title
                                         (const char*)CalculatePath(BuildLogicalSystemHTMLFilename(dynamic_cast<ZBLogicalSystemEntity*>(pSystemEntity)), htmlFilename)); // The file path

                                htmlFile << s;
                            }
                        }
                    }

                // if has a sub-model defined, create a link to enter in the symbol child model
                if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel())
                {
                    ZDProcessGraphModelMdl* pSubModel =
                            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel());

                    // retreive the html filename for the reference
                    CString symbolChildModelHtmlFilename = BuildModelHTMLFilename(pSubModel);
                    dummy.Format(IDS_GOINSYMBOL_HTML,
                                 (const char*)dynamic_cast<ZIBasicSymbol*>(pComp)->GetSymbolName());

                    s.Format(IDS_MODELGENHTML_59,
                             objectCounter,      // The object number
                             (const char*)dummy, // The file title
                             (const char*)CalculatePath(symbolChildModelHtmlFilename, htmlFilename)); // The file path

                    htmlFile << s;

                    // check if the symbol has more than one page
                    if (pSubModel->GetPageSet())
                    {
                        ZBProcessGraphPageIterator i(pSubModel->GetPageSet());
                        ZDProcessGraphPage*        pPage = i.GetFirst();

                        if (pPage)
                        {
                            // skip the first page
                            for (pPage = i.GetNext(); pPage; pPage = i.GetNext())
                            {
                                // retreive the html filename for the reference
                                symbolChildModelHtmlFilename = BuildModelHTMLFilename(pPage->GetpModel());
                                dummy.Format(IDS_GOINSYMBOL_HTML, (const char*)pPage->GetPageName());

                                s.Format(IDS_MODELGENHTML_59,
                                         objectCounter,      // The object number
                                         (const char*)dummy, // The file title
                                         (const char*)CalculatePath(symbolChildModelHtmlFilename, htmlFilename)); // The file path

                                htmlFile << s;
                            }
                        }
                    }
                }

                // *********************************************************************************************
                // JMR-MODIF - Le 2 mars 2006 - Ajout du code pour l'intégration des rapports processus.
                if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->IsProcess() && m_pInfo->GetIncludeProcessReport())
                {
                    CString processReportPath =
                            BuildProcessReportHTMLFilename(dynamic_cast<ZIBasicSymbol*>(pComp)->GetSymbolName());

                    // retreive the html filename for the reference
                    dummy.LoadString(IDS_GOINREPORT_HTML);

                    s.Format(IDS_MODELGENHTML_59,
                             objectCounter,                   // The object number
                             (const char*)dummy,              // The file title
                             (const char*)processReportPath); // The file path

                    htmlFile << s;
                }
                // *********************************************************************************************

                s.Format(IDS_MODELGENHTML_61, objectCounter); // Create the new popup object
                htmlFile << s;

                // next object
                ++objectCounter;
            }
        }

        // javascript end here
        s.LoadString(IDS_MODELGENHTML_54);
        htmlFile << s;

        // write the hotspot table header
        s.Format(IDS_MODELGENHTML_2,
                 (const char*)pModel->GetAbsolutePath(),                   // Object name
                 (const char*)CalculatePath(imageFilename, htmlFilename)); // Image file

        htmlFile << s;

        // write all hot spots

        // run throught the model elements and write the hotspot entities
        CString symbolHtmlFilename;
        CRect   symbolCoordinates;

        // Process the model components
        pSet = pModel->GetComponents();

        // set the object counter
        objectCounter = 1;

        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            if (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol))
            {
                // if no sub-model, just the area for the popup
                CODModel* pOwnerModel = dynamic_cast<ZIBasicSymbol*>(pComp)->GetOwnerModel();

                // and then, retreive the symbol position
                if (ISA(pComp, ZBSymbol))
                    symbolCoordinates = pComp->GetBaseRgn().GetBounds();
                else
                if (dynamic_cast<ZBLinkSymbol*>(pComp)->GetNumLabels() > 0)
                    symbolCoordinates = dynamic_cast<ZBLinkSymbol*>(pComp)->GetLabel(0)->GetBounds();
                else
                    symbolCoordinates = dynamic_cast<ZBLinkSymbol*>(pComp)->GetBaseRgn().GetBounds();

                // ****************************************************************************************************
                // JMR-MODIF - Le 5 juillet 2005 - Adaptation de la page : L'action du click et l'action du passage
                // sur un objet sont croisées.
/*                s.Format( IDS_MODELGENHTML_74, ObjectCounter, // The object number
                                               ObjectCounter, // The object number
                                               (const char*)CalculatePath( 
                                                                BuildSymbolPropertyHTMLFilename( dynamic_cast<ZIBasicSymbol*>(pComp), 
                                                                                                (pOwnerModel && ISA(pOwnerModel,ZDProcessGraphModelMdl)) ? dynamic_cast<ZDProcessGraphModelMdl*>(pOwnerModel) : pModel ),
                                                                HtmlFilename
                                                                         ),    // The property file
                                               (const char*)gPSSLeftTarget, // The target frame
                                               SymbolCoordinates.left,    // The coordinates
                                               SymbolCoordinates.top,
                                               SymbolCoordinates.right,
                                               SymbolCoordinates.bottom );
*/
                s.Format(IDS_MODELGENHTML_91,
                         objectCounter,               // The object number
                         objectCounter,               // The object number
                         (const char*)gPSSLeftTarget, // The target frame
                         symbolCoordinates.left,      // The coordinates
                         symbolCoordinates.top,
                         symbolCoordinates.right,
                         symbolCoordinates.bottom);
                // ****************************************************************************************************

                htmlFile << s;

                // Next object
                ++objectCounter;
            }
        }

        // write the hotspot table footer
        s.LoadString(IDS_MODELGENHTML_4);
        htmlFile << s;

        // write the footer
        s.LoadString( IDS_MODELGENHTML_5 );
        htmlFile << s;

        htmlFile.CloseFile();
    }

    // check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if (!StringAlreadyGenerated(htmlFilenameForPrinter))
    {
        // Refresh Setup Copyfile Window
        m_FileGenerateWindow.SetDestination(htmlFilenameForPrinter);
        m_FileGenerateWindow.UpdateWindow();

        if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
        {
            ::GetMessage(&msg, NULL, NULL, NULL);
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        // now create the printable HTML file
        ZDHtmlFile printableHtmlFile(htmlFilenameForPrinter);

        if (!printableHtmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),                     // Model path
                 (const char*)ZBDate::GetToday().GetStandardFormatedDate()); // Current date
        printableHtmlFile << s;

        s.Format(IDS_MODELGENHTML_16,
                 (const char*)CalculatePath(imageFilename, htmlFilename)); // The model image
        printableHtmlFile << s;

        // write the footer
        s.LoadString(IDS_MODELGENHTML_5);
        printableHtmlFile << s;

        printableHtmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool ZUModelGenerateImageFiles::GenerateIndexPage( ZDProcessGraphModelMdl* pModel )
{
    // Saves the root html filename
    m_RootHtmlFilename = BuildModelHTMLFilename( pModel, _T( "Index_" ) );
    m_RootName = pModel->GetAbsolutePath();

    // Saves the main index.htm pages
    m_IndexHtmlFilename = BuildModelHTMLFilenameIndex();

    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( m_IndexHtmlFilename );
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
    if ( !StringAlreadyGenerated( m_IndexHtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( m_IndexHtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write the complete html file with
        // reference to the main banner and the main index pages
        CString s;
        s.Format( IDS_MODELGENHTML_66,
                  (const char*)CalculatePath( BuildModelHTMLFilenameBanner(), m_RootHtmlFilename ),    // Main banner
                  (const char*)CalculatePath( m_RootHtmlFilename, m_RootHtmlFilename ) );            // Index pages

        HtmlFile << s;

        HtmlFile.CloseFile();
    }
    
    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( m_RootHtmlFilename );
    m_FileGenerateWindow.UpdateWindow();

    if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
    {
        GetMessage( &msg, NULL, NULL, NULL );
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if ( !StringAlreadyGenerated( m_RootHtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( m_RootHtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_1,
                  (const char*)pModel->GetAbsolutePath(),                        // Model path
                  (const char*)ZBDate::GetToday().GetStandardFormatedDate() );    // Current date

        HtmlFile << s;

        s.Format( IDS_MODELGENHTML_68, (const char*)gWhite );
        HtmlFile << s;

        // JMR-MODIF - Le 3 avril 2006 - "Domaine principal du modèle" ne doit plus apparaître sur la 1ere page.
        // Write the model name table header
//        s.LoadString( IDS_MODELGENHTML_18 );
        s.LoadString( IDS_MODELGENHTML_18a );
        HtmlFile << s;

        // Model name
        HtmlFile << pModel->GetModelName();

        // Write the model name table footer
        s.LoadString( IDS_MODELGENHTML_22 );
        HtmlFile << s;

        // Write all links to all root pages

        // Write the table header
        s.LoadString( IDS_MODELGENHTML_19 );
        HtmlFile << s;

        // Run throught the model pages 
        CString SubModelHtmlFilename;

        // Process the model components

        // Run through all pages if there are
        if ( pModel->GetPageSet() != NULL )
        {
            ZBProcessGraphPageIterator i( pModel->GetPageSet() );

            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                if ( pPage->GetpModel() )
                {
                    GenerateModel( reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ) );

                    // Retreive the html filename for the reference
                    SubModelHtmlFilename = BuildModelHTMLFilename( reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ) );

                    s.LoadString( IDS_MODELGENHTML_20 );
                    HtmlFile << s;

                    s.LoadString( IDS_MODELGENHTML_24 );
                    HtmlFile << s;

                    if ( !GenerateFrameMainModelPage( reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ),
                                                      SubModelHtmlFilename ) )
                    {
                        return false;
                    }

                    // JMR-MODIF - le 10 août 2005 - Modifié inscription du nom de page : Le nom de la page doit être
                    // inscrit, et non pas le nom du modèle.
                    //s.Format( IDS_MODELGENHTML_25, (const char*)CalculatePath( BuildMainFrameModelHTMLFilename( reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ) ), m_RootHtmlFilename ),
                    //                               (const char*)reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() )->GetModelName() );
                    s.Format( IDS_MODELGENHTML_25, (const char*)CalculatePath( BuildMainFrameModelHTMLFilename( reinterpret_cast<ZDProcessGraphModelMdl*>( pPage->GetpModel() ) ), m_RootHtmlFilename ),
                                                   (const char*)pPage->GetPageName() );
                    HtmlFile << s;
                }
            }
        }

        // Write blank lines
        s.LoadString( IDS_MODELGENHTML_75 );
        HtmlFile << s;

        // If a main user group is defined,
        // then generate the user group page
        if ( pModel->GetMainUserGroup() )
        {
            // Generates the frame for the system page
            if ( !GenerateFrameEmptyUserPage() )
            {
                return false;
            }

            if ( !GenerateFrameUserPage( pModel ) )
            {
                return false;
            }

            s.LoadString( IDS_MODELGENHTML_28 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_20 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_24 );
            HtmlFile << s;

            // Retreive the html filename for the reference
            CString HtmlFilename = BuildModelHTMLFilenameUserMainFrame();

            s.Format( IDS_MODELGENHTML_25, (const char*)CalculatePath( HtmlFilename, m_RootHtmlFilename ),
                                           (const char*)pModel->GetMainUserGroup()->GetEntityName() );
            HtmlFile << s;

            if ( !GenerateUnitGroupPage( pModel ) )
            {
                return false;
            }
        }

        // Write blank lines
        s.LoadString( IDS_MODELGENHTML_75 );
        HtmlFile << s;

        // If a main logical system is defined,
        // then generate the logical system page
        if ( pModel->GetMainLogicalSystem() )
        {
            // Generates the frame for the system page
            if ( !GenerateFrameEmptySystemPage() )
            {
                return false;
            }

            if ( !GenerateFrameSystemPage( pModel ) )
            {
                return false;
            }

            s.LoadString( IDS_MODELGENHTML_29 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_20 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_24 );
            HtmlFile << s;

            // Retreive the html filename for the reference
            CString HtmlFilename = BuildModelHTMLFilenameSystemMainFrame();

            s.Format( IDS_MODELGENHTML_25, (const char*)CalculatePath( HtmlFilename, m_RootHtmlFilename ),
                                           (const char*)pModel->GetMainLogicalSystem()->GetEntityName() );
            HtmlFile << s;

            if ( !GenerateLogicalSystemPage( pModel ) )
            {
                return false;
            }
        }

        // Write blank lines
        s.LoadString( IDS_MODELGENHTML_75 );
        HtmlFile << s;

        // *******************************************************************************************************
        // JMR-MODIF - Le 20 février 2006 - Ajout de la génération du système de prestations.

        // If a main logical prestations is defined,
        // then generate the logical prestations page
        if ( pModel->GetMainLogicalPrestations() )
        {
            // Generates the frame for the prestations page
            if ( !GenerateFrameEmptyPrestationsPage() )
            {
                return false;
            }

            if ( !GenerateFramePrestationsPage( pModel ) )
            {
                return false;
            }

            s.LoadString( IDS_MODELGENHTML_80 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_20 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_24 );
            HtmlFile << s;

            // Retreive the html filename for the reference
            CString HtmlFilename = BuildModelHTMLFilenamePrestationsMainFrame();

            s.Format( IDS_MODELGENHTML_25, (const char*)CalculatePath( HtmlFilename, m_RootHtmlFilename ),
                                           (const char*)pModel->GetMainLogicalPrestations()->GetEntityName() );
            HtmlFile << s;

            if ( !GenerateLogicalPrestationsPage( pModel ) )
            {
                return false;
            }
        }

        // Write blank lines
        s.LoadString( IDS_MODELGENHTML_75 );
        HtmlFile << s;
        // *******************************************************************************************************

        // *******************************************************************************************************
        // JMR-MODIF - Le 16 janvier 2007 - Ajout du lien vers le livre des règles dans la page d'index.

        // If a main logical rule is defined, then generate the rule book.
        if ( pModel->GetMainLogicalRules() && m_pInfo->GetIncludeRuleBook() )
        {
            s.LoadString( IDS_RULEBOOK_MTL_HTML_1 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_20 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_24 );
            HtmlFile << s;

            s.Format( IDS_MODELGENHTML_25, (const char*)_T( "RuleBook.htm" ),
                                           (const char*)pModel->GetMainLogicalRules()->GetEntityName() );
            HtmlFile << s;

            // JMR-MODIF - Le 29 avril 2007 - Ajout de l'entrée pour le deuxième rapport du livre des règles.
            s.LoadString( IDS_MODELGENHTML_20 );
            HtmlFile << s;

            s.LoadString( IDS_MODELGENHTML_24 );
            HtmlFile << s;

            CString RuleBookDetailsTitle = _T( "" );
            RuleBookDetailsTitle.LoadString( IDS_RULEBOOKDETAILS_MTL_HTML_6 );

            s.Format( IDS_MODELGENHTML_25, (const char*)_T( "RuleBookDetails.htm" ),
                                           (const char*)RuleBookDetailsTitle );
            HtmlFile << s;
        }

        // Write blank lines
        s.LoadString( IDS_MODELGENHTML_75 );
        HtmlFile << s;
        // *******************************************************************************************************

        // Write the table footer and end of html file
        s.LoadString( IDS_MODELGENHTML_21 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateFrameMainModelPage( ZDProcessGraphModelMdl* pModel, CString ModelHtmlPage )
{
    // First, generates the main frame html page for the model
    CString HtmlFilename = BuildMainFrameModelHTMLFilename( pModel );

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_69,
                  (const char*)CalculatePath( BuildModelHTMLFilenameEmptyPropertyPage(), m_RootHtmlFilename ),    // User left pane
                  (const char*)CalculatePath( ModelHtmlPage, m_RootHtmlFilename ) );                            // Empty user right pane

        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateFrameUserPage( ZDProcessGraphModelMdl* pModel )
{
    // First, generates the main banner.htm pages
    CString HtmlFilename = BuildModelHTMLFilenameUserMainFrame();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_69,
                  (const char*)CalculatePath( BuildModelHTMLFilenameUnit( pModel ), m_RootHtmlFilename ),    // User left pane
                  (const char*)CalculatePath( BuildModelHTMLFilenameEmptyUser(), m_RootHtmlFilename ) );    // Empty user right pane

        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateFrameSystemPage( ZDProcessGraphModelMdl* pModel )
{
    // First, generates the main banner.htm pages
    CString HtmlFilename = BuildModelHTMLFilenameSystemMainFrame();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_69,
                  (const char*)CalculatePath( BuildModelHTMLFilenameSystem( pModel ), m_RootHtmlFilename ),    // System left pane
                  (const char*)CalculatePath( BuildModelHTMLFilenameEmptySystem(), m_RootHtmlFilename ) );    // Empty system right pane
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction de génération des pages des prestations.
bool ZUModelGenerateImageFiles::GenerateFramePrestationsPage( ZDProcessGraphModelMdl* pModel )
{
    // First, generates the main banner.htm pages
    CString HtmlFilename = BuildModelHTMLFilenamePrestationsMainFrame();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_78,
                  (const char*)CalculatePath( BuildModelHTMLFilenamePrestations( pModel ), m_RootHtmlFilename ),    // Prestations left pane
                  (const char*)CalculatePath( BuildModelHTMLFilenameEmptyPrestations(), m_RootHtmlFilename ) );        // Empty prestations right pane
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateFrameEmptyUserPage()
{
    // First, generates the empty user page
    CString HtmlFilename = BuildModelHTMLFilenameEmptyUser();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.LoadString( IDS_MODELGENHTML_70 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateFrameEmptySystemPage()
{
    // First, generates the empty user page
    CString HtmlFilename = BuildModelHTMLFilenameEmptySystem();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.LoadString( IDS_MODELGENHTML_71 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

// JMR-MODIF - Le 20 février 2006 - Fonction de génération pour les modèles de page des prestations.
bool ZUModelGenerateImageFiles::GenerateFrameEmptyPrestationsPage()
{
    // First, generates the empty user page
    CString HtmlFilename = BuildModelHTMLFilenameEmptyPrestations();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.LoadString( IDS_MODELGENHTML_81 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateEmptyPropertyPage()
{
    // First, generates the empty user page
    CString HtmlFilename = BuildModelHTMLFilenameEmptyPropertyPage();

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.LoadString( IDS_MODELGENHTML_72 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateBannerPage( ZDProcessGraphModelMdl* pModel )
{
    // First, generates the main banner.htm pages
    CString BannerHtmlFilename = BuildModelHTMLFilenameBanner();

    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( BannerHtmlFilename );
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
    if ( !StringAlreadyGenerated( BannerHtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( BannerHtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;
        s.Format( IDS_MODELGENHTML_1,
                  (const char*)pModel->GetAbsolutePath(),                        // Model path
                  (const char*)ZBDate::GetToday().GetStandardFormatedDate() );    // Current date
        HtmlFile << s;

        s.Format( IDS_MODELGENHTML_68, (const char*)gWhite );
        HtmlFile << s;

        // Write the copyright table with the processsoft image jpg
        s.LoadString( IDS_MODELGENHTML_12 );
        HtmlFile << s;

        // Build the logo image filename
        CString LogoImage = m_ImageDirectory + _T( "\\" );
        LogoImage    += ( m_InternalLogoFilename.IsEmpty() )  ? gLogoImageFile : m_InternalLogoFilename;
        CString HRef = ( m_pInfo->GetHyperLink().IsEmpty() ) ? _T( "http://www.processsoft.com" ) : m_pInfo->GetHyperLink();
        s.Format( IDS_MODELGENHTML_13,
                  (const char*)HRef,
                  (const char*)CalculatePath( LogoImage, m_RootHtmlFilename ) ); // Logo complete filename
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_14 );
        HtmlFile << s;

        // Write the navigation table header
        s.LoadString( IDS_MODELGENHTML_6 );
        HtmlFile << s;

        // Write the ref to root
        LogoImage = m_ImageDirectory + _T( "\\" ) + gHomeImageFile;

        CString dummy;
        dummy.LoadString( IDS_INDEXPAGE_HTML );
        s.Format( IDS_MODELGENHTML_7,
                  (const char*)CalculatePath( m_RootHtmlFilename, m_RootHtmlFilename ),    // Root filename
                  (const char*)gPSSMainTarget,                                            // The target frame
                  (const char*)CalculatePath( LogoImage, m_RootHtmlFilename ),            // logo complete filename
                  (const char*)CalculatePath( m_RootHtmlFilename, m_RootHtmlFilename ),    // Root filename
                  (const char*)gPSSMainTarget,                                            // The target frame
                  (const char*)dummy );                                                    //m_RootName); // Root name 

        HtmlFile << s;

        // Write the navigation table header
        s.LoadString( IDS_MODELGENHTML_8 );
        HtmlFile << s;

        // Write the model name table footer
        s.LoadString( IDS_MODELGENHTML_9 );
        HtmlFile << s;

        // Write the table footer and end of html file
        s.LoadString( IDS_MODELGENHTML_21 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateUnitGroupPage( ZDProcessGraphModelMdl* pModel )
{
    // Build the html filename
    CString HtmlFilename = BuildModelHTMLFilenameUnit( pModel );
    
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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;

        // Retreive the style and the javascript filenames
        CString CSSHtmlFilename = m_IncludeDirectory + _T( "\\" ) + gTreeCSSFile;
        CString JSHtmlFilename  = m_IncludeDirectory + _T( "\\" ) + gTreeJSFile;

        s.Format( IDS_MODELGENHTML_23, (const char*)CalculatePath( CSSHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( JSHtmlFilename, m_RootHtmlFilename ) );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_26 );
        HtmlFile << s;

        // Add the style to the oMenu
        CString PlusHtmlFilename  = m_ImageDirectory + _T( "\\" ) + gPlusImageFile;
        CString MinusHtmlFilename = m_ImageDirectory + _T( "\\" ) + gMinusImageFile;
        CString UserHtmlFilename  = m_ImageDirectory + _T( "\\" ) + gUsersImageFile;

        s.Format( IDS_MODELGENHTML_64, (const char*)CalculatePath( UserHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( MinusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( PlusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)gPSSRightTarget);

        HtmlFile << s;

        if ( !GenerateUnitObjects( pModel->GetMainUserGroup(), &HtmlFile ) )
        {
            HtmlFile.CloseFile();
            return false;
        }

        // Body and end of html
        s.Format( IDS_MODELGENHTML_27, (const char*)gWhite );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_53 );
        HtmlFile << s;

        // Generate the tree control
        s.LoadString( IDS_MODELGENHTML_67 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_54 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_65 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateUnitObjects( ZBUserGroupEntity* pGroupEntity, ZDHtmlFile* pHtmlFile )
{
    if ( !pGroupEntity || !pHtmlFile )
    {
        return false;
    }
    
    m_IndexItem = 0;

    return _GenerateUnitGroupObjects( pGroupEntity, pHtmlFile, m_IndexItem );
}

bool ZUModelGenerateImageFiles::_GenerateUnitGroupObjects( ZBUserGroupEntity*    pGroupEntity,
                                                           ZDHtmlFile*            pHtmlFile,
                                                           size_t                ParentID )
{
    ++m_IndexItem;
    size_t CurrentItem = m_IndexItem;

    CString RefFile = GenerateUserGroupList( pGroupEntity );

    CString s;

    s.Format( IDS_MODELGENHTML_30, m_IndexItem,
                                   ParentID,
                                   (const char*)pGroupEntity->GetEntityName(),
                                   ( RefFile.IsEmpty() ) ?
                                        _T( "null" ) : (const char*)CalculatePath( RefFile, m_RootHtmlFilename ) );

    *pHtmlFile << s;

    if ( pGroupEntity->ContainEntity() )
    {
        int Count = pGroupEntity->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBUserEntity* pEntity = pGroupEntity->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBUserGroupEntity ) )
            {
                _GenerateUnitGroupObjects( dynamic_cast<ZBUserGroupEntity*>(pEntity), pHtmlFile, CurrentItem );
            }

            if ( ISA( pEntity, ZBUserRoleEntity ) )
            {
                 _GenerateUnitRoleObjects( dynamic_cast<ZBUserRoleEntity*>(pEntity), pHtmlFile, CurrentItem );
            }
        }
    }

    return true;
}

bool ZUModelGenerateImageFiles::_GenerateUnitRoleObjects( ZBUserRoleEntity*    pRoleEntity,
                                                          ZDHtmlFile*        pHtmlFile,
                                                          size_t            ParentID )
{
    ++m_IndexItem;

    CString s;
    s.Format( IDS_MODELGENHTML_30, m_IndexItem,
                                   ParentID,
                                   (const char*)pRoleEntity->GetEntityName(),
                                   _T( "null" ) );
    *pHtmlFile << s;

    return true;
}

bool ZUModelGenerateImageFiles::GenerateLogicalSystemPage( ZDProcessGraphModelMdl* pModel )
{
    // Build the html filename
    CString HtmlFilename = BuildModelHTMLFilenameSystem( pModel );
    
    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( HtmlFilename );
    m_FileGenerateWindow.UpdateWindow();
    MSG    msg;

    if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
    {
        GetMessage( &msg, NULL, NULL, NULL );
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;

        // Retreive the style and the javascript filenames
        CString CSSHtmlFilename = m_IncludeDirectory + _T( "\\" ) + gTreeCSSFile;
        CString JSHtmlFilename  = m_IncludeDirectory + _T( "\\" ) + gTreeJSFile;

        s.Format( IDS_MODELGENHTML_23, (const char*)CalculatePath( CSSHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( JSHtmlFilename, m_RootHtmlFilename ) );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_26 );
        HtmlFile << s;

        CString PlusHtmlFilename    = m_ImageDirectory + _T( "\\" ) + gPlusImageFile;
        CString MinusHtmlFilename    = m_ImageDirectory + _T( "\\" ) + gMinusImageFile;
        CString SystemHtmlFilename    = m_ImageDirectory + _T( "\\" ) + gLogicalSystemImageFile;

        s.Format( IDS_MODELGENHTML_64, (const char*)CalculatePath( SystemHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( MinusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( PlusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)gPSSRightTarget);
        HtmlFile << s;

        if ( !GenerateLogicalSystemObjects( pModel->GetMainLogicalSystem(), &HtmlFile ) )
        {
            HtmlFile.CloseFile();
            return false;
        }

        // Body and end of html
        s.Format( IDS_MODELGENHTML_27, (const char*)gWhite );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_53 );
        HtmlFile << s;

        // Generate the tree control
        s.LoadString( IDS_MODELGENHTML_67 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_54 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_65 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

bool ZUModelGenerateImageFiles::GenerateLogicalSystemObjects( ZBLogicalSystemEntity*    pSystemEntity,
                                                              ZDHtmlFile*                pHtmlFile )
{
    if ( !pSystemEntity || !pHtmlFile )
    {
        return false;
    }
    
    m_IndexItem = 0;

    return _GenerateLogicalSystemObjects( pSystemEntity, pHtmlFile, m_IndexItem );
}

bool ZUModelGenerateImageFiles::_GenerateLogicalSystemObjects( ZBLogicalSystemEntity*    pSystemEntity,
                                                               ZDHtmlFile*                pHtmlFile,
                                                               size_t                    ParentID )
{
    ++m_IndexItem;
    size_t CurrentItem = m_IndexItem;

    CString RefFile = GenerateLogicalSystemList( pSystemEntity );

    CString s;
    s.Format( IDS_MODELGENHTML_30, m_IndexItem,
                                   ParentID,
                                   (const char*)pSystemEntity->GetEntityName(),
                                   ( RefFile.IsEmpty() ) ? _T( "null" ) : (const char*)CalculatePath( RefFile, m_RootHtmlFilename ) );

    *pHtmlFile << s;

    if ( pSystemEntity->ContainEntity() )
    {
        int Count = pSystemEntity->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBSystemEntity* pEntity = pSystemEntity->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBLogicalSystemEntity ) )
            {
                _GenerateLogicalSystemObjects( dynamic_cast<ZBLogicalSystemEntity*>( pEntity ),
                                               pHtmlFile,
                                               CurrentItem );
            }
        }
    }

    return true;
}

// JMR-MODIF - Le 20 février 2006 - Ajout de la fonction de génération des pages de prestations.
bool ZUModelGenerateImageFiles::GenerateLogicalPrestationsPage( ZDProcessGraphModelMdl* pModel )
{
    // Build the html filename
    CString HtmlFilename = BuildModelHTMLFilenamePrestations( pModel );
    
    // Refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination( HtmlFilename );
    m_FileGenerateWindow.UpdateWindow();
    MSG    msg;

    if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
    {
        GetMessage( &msg, NULL, NULL, NULL );
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Check if the html file has already been generated
    // this is to avoid generating twice the same html file
    // it takes time and it will optimize the generation
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Write header
        CString s;

        // Retreive the style and the javascript filenames
        CString CSSHtmlFilename = m_IncludeDirectory + _T( "\\" ) + gTreeCSSFile;
        CString JSHtmlFilename  = m_IncludeDirectory + _T( "\\" ) + gTreeJSFile;

        s.Format( IDS_MODELGENHTML_23, (const char*)CalculatePath( CSSHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( JSHtmlFilename, m_RootHtmlFilename ) );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_26 );
        HtmlFile << s;

        CString PlusHtmlFilename        = m_ImageDirectory + _T( "\\" ) + gPlusImageFile;
        CString MinusHtmlFilename        = m_ImageDirectory + _T( "\\" ) + gMinusImageFile;
        CString PrestationsHtmlFilename    = m_ImageDirectory + _T( "\\" ) + gLogicalPrestationsImageFile;

        s.Format( IDS_MODELGENHTML_64, (const char*)CalculatePath( PrestationsHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( MinusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)CalculatePath( PlusHtmlFilename, m_RootHtmlFilename ),
                                       (const char*)gPSSRightTarget);
        HtmlFile << s;

        if ( !GenerateLogicalPrestationsObjects( pModel->GetMainLogicalPrestations(), &HtmlFile ) )
        {
            HtmlFile.CloseFile();
            return false;
        }

        // Body and end of html
        s.Format( IDS_MODELGENHTML_27, (const char*)gWhite );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_53 );
        HtmlFile << s;

        // Generate the tree control
        s.LoadString( IDS_MODELGENHTML_67 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_54 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_65 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return true;
}

// JMR-MODIF - Le 20 février 2006 - Inclusion des objets de type prestations.
bool ZUModelGenerateImageFiles::GenerateLogicalPrestationsObjects( ZBLogicalPrestationsEntity*    pPrestationsEntity,
                                                                   ZDHtmlFile*                    pHtmlFile )
{
    if ( !pPrestationsEntity || !pHtmlFile )
    {
        return false;
    }
    
    m_IndexItem = 0;

    return _GenerateLogicalPrestationsObjects( pPrestationsEntity, pHtmlFile, m_IndexItem );
}

// JMR-MODIF - Le 20 février 2006 - Sous-routine d'inclusion des objets de type prestations.
bool ZUModelGenerateImageFiles::_GenerateLogicalPrestationsObjects( ZBLogicalPrestationsEntity*    pPrestationsEntity,
                                                                    ZDHtmlFile*                    pHtmlFile,
                                                                    size_t                        ParentID )
{
    ++m_IndexItem;
    size_t CurrentItem = m_IndexItem;

    CString RefFile = GenerateLogicalPrestationsList( pPrestationsEntity );

    CString s;
    s.Format( IDS_MODELGENHTML_30, m_IndexItem,
                                   ParentID,
                                   (const char*)pPrestationsEntity->GetEntityName(),
                                   ( RefFile.IsEmpty() ) ? _T( "null" ) : (const char*)CalculatePath( RefFile, m_RootHtmlFilename ) );

    *pHtmlFile << s;

    if ( pPrestationsEntity->ContainEntity() )
    {
        int Count = pPrestationsEntity->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBPrestationsEntity* pEntity = pPrestationsEntity->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBLogicalPrestationsEntity ) )
            {
                _GenerateLogicalPrestationsObjects( dynamic_cast<ZBLogicalPrestationsEntity*>( pEntity ),
                                                    pHtmlFile,
                                                    CurrentItem );
            }
        }
    }

    return true;
}

CString ZUModelGenerateImageFiles::GenerateUserGroupList( ZBUserGroupEntity* pGroupEntity )
{
    // Extract the symbols for which this user group is assigned to
    ZUExtractModelUnitGroupAssigned extract( m_pModel, pGroupEntity );
    extract.Navigate();

    // Build the html filename
    CString HtmlFilename = BuildUserHTMLFilename( pGroupEntity );

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return _T( "" );
        }

        // Write header
        CString s;
        CString s1;

        // The document title
        s1.LoadString( IDS_USERGROUP_HTML );
        s.Format( IDS_MODELGENHTML_31, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_36 );
        HtmlFile << s;

        s.Format( IDS_MODELGENHTML_37, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_38 );
        HtmlFile << s;

        // JMR-MODIF - Le 16 août 2005 - Ajout de la gestion de l'option permettant d'inclure le rapport Conceptor.
        CString sEntityname = (const char*)pGroupEntity->GetEntityName();

        if ( m_pInfo->GetIncludeConceptor() == true )
        {
            /**************************************************************************************************
            // JMR-MODIF - Le 6 mars 2006 - Mise à jour du système de génération des noms de fichier Conceptor.

            // Génération du nom de fichier selon le même principe que plus tard, lors de la
            // génération des pages du rapport.
            CString sFilename    = _T( "Conceptor_" );

            for ( int i = 0; i < sEntityname.GetLength(); i++ )
            {
                if ( sEntityname.GetAt( i ) == ' ' )
                {
                    sEntityname.SetAt( i, '_' );
                }
            }

            sFilename += sEntityname;
            sFilename += _T( ".htm" );*/

            CString sFilename = BuildConceptorHTMLFilename( sEntityname );
            //**************************************************************************************************

            HtmlFile << _T( "<a href=\"" ) + sFilename + _T( "\">" );
            HtmlFile << sEntityname;
            HtmlFile << _T( "</a>" );
        }
        else
        {
            // Write the unit name
            HtmlFile << pGroupEntity->GetEntityName();
        }

        s.LoadString( IDS_MODELGENHTML_76 );
        HtmlFile << s;

        // Write the model name
        HtmlFile << m_pModel->GetAbsolutePath();

        s.LoadString( IDS_MODELGENHTML_32 );
        HtmlFile << s;

        // Now, run through the list of symbols and build the page
        CODComponentIterator i( &extract.GetComponentSet() );

        for ( CODComponent* pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext() )
        {
            if ( ISA( pComp, ZBSymbol ) || ISA( pComp, ZBLinkSymbol ) )
            {
                CString HtmlFilenameOwnerModel;
                CString SymbolPath( _T( "#NA" ) );
                CODModel* pOwnerModel = dynamic_cast<ZIBasicSymbol*>( pComp )->GetOwnerModel();

                if ( pOwnerModel && ISA( pOwnerModel, ZDProcessGraphModelMdl ) )
                {
                    HtmlFilenameOwnerModel = BuildModelHTMLFilename( dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel ) );
                    SymbolPath = dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel )->GetAbsolutePath();
                }

                // If no ref
                if ( HtmlFilenameOwnerModel.IsEmpty() )
                {
                    s.Format( IDS_MODELGENHTML_35, (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath);
                }
                else
                {
                    s.Format( IDS_MODELGENHTML_33, (const char*)CalculatePath( HtmlFilenameOwnerModel, m_RootHtmlFilename ),
                                                   (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath );
                }

                HtmlFile << s;
            }
        }

        s.LoadString( IDS_MODELGENHTML_34 );
        HtmlFile << s;

        HtmlFile.CloseFile();
    }

    return HtmlFilename;
}

CString ZUModelGenerateImageFiles::GenerateLogicalSystemList( ZBLogicalSystemEntity* pSystemEntity )
{
    // Extract the symbols for which this logical system is assigned to
    ZUExtractModelLogicalSystemAssigned extract( m_pModel, pSystemEntity );
    extract.Navigate();

    // Build the html filename
    CString HtmlFilename = BuildLogicalSystemHTMLFilename( pSystemEntity );

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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return _T( "" );
        }

        // Write header
        CString s;
        CString s1;

        // The document title
        s1.LoadString( IDS_LOGICALSYSTEM_HTML );
        s.Format( IDS_MODELGENHTML_31, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_36 );
        HtmlFile << s;

        s.Format( IDS_MODELGENHTML_37, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_38 );
        HtmlFile << s;

        // Write the unit name
        HtmlFile << pSystemEntity->GetEntityName();
        s.LoadString( IDS_MODELGENHTML_76 );
        HtmlFile << s;

        // Write the model name
        HtmlFile << m_pModel->GetAbsolutePath();

        s.LoadString( IDS_MODELGENHTML_32 );
        HtmlFile << s;

        // Now, run through the list of symbols and build the page
        CODComponentIterator i( &extract.GetComponentSet() );

        for ( CODComponent* pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext() )
        {
            if ( ISA( pComp, ZBSymbol ) || ISA( pComp, ZBLinkSymbol ) )
            {
                CString HtmlFilenameOwnerModel;
                CString SymbolPath( _T( "#NA" ) );
                CODModel* pOwnerModel = dynamic_cast<ZIBasicSymbol*>( pComp )->GetOwnerModel();

                if ( pOwnerModel && ISA( pOwnerModel, ZDProcessGraphModelMdl ) )
                {
                    HtmlFilenameOwnerModel = BuildModelHTMLFilename( dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel ) );
                    SymbolPath = dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel )->GetAbsolutePath();
                }

                // If no ref
                if ( HtmlFilenameOwnerModel.IsEmpty() )
                {
                    s.Format( IDS_MODELGENHTML_35, (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath );
                }
                else
                {
                    s.Format( IDS_MODELGENHTML_33, (const char*)CalculatePath( HtmlFilenameOwnerModel, m_RootHtmlFilename ),
                                                   (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath );
                }

                HtmlFile << s;
            }
        }

        s.LoadString( IDS_MODELGENHTML_34 );
        HtmlFile << s;

        HtmlFile.CloseFile();

    }

    return HtmlFilename;
}

// JMR-MODIF - Le 20 février 2006 - Fonction de génération de la liste des prestations.
CString ZUModelGenerateImageFiles::GenerateLogicalPrestationsList( ZBLogicalPrestationsEntity* pPrestationsEntity )
{
    // Extrait les symboles pour lesquels cette prestation est assignée.
    ZUExtractModelLogicalPrestationsAssigned extract( m_pModel, pPrestationsEntity );
    extract.Navigate();

    // Construit le nom du fichier HTML.
    CString HtmlFilename = BuildLogicalPrestationsHTMLFilename( pPrestationsEntity );

    // Rafraîchit la fenêtre d'information.
    m_FileGenerateWindow.SetDestination( HtmlFilename );
    m_FileGenerateWindow.UpdateWindow();
    MSG msg;

    if ( PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ) )
    {
        GetMessage( &msg, NULL, NULL, NULL );
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    // Teste si le fichier HTML a déjà été généré, afin d'éviter de générer deux fois le même fichier HTML.
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return _T( "" );
        }

        // Ecrit les en-têtes.
        CString s;
        CString s1;

        // Ecrit le titre du document.
        s1.LoadString( IDS_LOGICALPRESTATIONS_HTML );
        s.Format( IDS_MODELGENHTML_31, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_36 );
        HtmlFile << s;

        s.Format( IDS_MODELGENHTML_37, (const char*)s1 );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_38 );
        HtmlFile << s;

        // JMR-MODIF - Le 15 mars 2006 - Ajout du lien hypertexte vers le nouveau rapport détaillé des prestations.
        // Ecrit le nom de la prestation
        s.Format( IDS_MODELGENHTML_92,
                  BuildPrestationsReportHTMLFilename( pPrestationsEntity->GetEntityName() ),
                  pPrestationsEntity->GetEntityName() );
        HtmlFile << s;

        s.LoadString( IDS_MODELGENHTML_76 );
        HtmlFile << s;

        // Ecrit le nom du modèle
        HtmlFile << m_pModel->GetAbsolutePath();

        s.LoadString( IDS_MODELGENHTML_32 );
        HtmlFile << s;

        // Passe en revue la liste des symboles et construit la page.
        CODComponentIterator i( &extract.GetComponentSet() );

        for ( CODComponent* pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext() )
        {
            if ( ISA( pComp, ZBSymbol ) || ISA( pComp, ZBLinkSymbol ) )
            {
                CString HtmlFilenameOwnerModel;
                CString SymbolPath( _T( "#NA" ) );
                CODModel* pOwnerModel = dynamic_cast<ZIBasicSymbol*>( pComp )->GetOwnerModel();

                if ( pOwnerModel && ISA( pOwnerModel, ZDProcessGraphModelMdl ) )
                {
                    HtmlFilenameOwnerModel = BuildModelHTMLFilename( dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel ) );
                    SymbolPath = dynamic_cast<ZDProcessGraphModelMdl*>( pOwnerModel )->GetAbsolutePath();
                }

                // Si aucun référenciel n'est défini.
                if ( HtmlFilenameOwnerModel.IsEmpty() )
                {
                    s.Format( IDS_MODELGENHTML_35, (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath );
                }
                else
                {
                    s.Format( IDS_MODELGENHTML_33, (const char*)CalculatePath( HtmlFilenameOwnerModel, m_RootHtmlFilename ),
                                                   (const char*)dynamic_cast<ZIBasicSymbol*>( pComp )->GetSymbolName(),
                                                   (const char*)SymbolPath );
                }

                HtmlFile << s;
            }
        }

        s.LoadString( IDS_MODELGENHTML_34 );
        HtmlFile << s;

        HtmlFile.CloseFile();

    }

    return HtmlFilename;
}

bool ZUModelGenerateImageFiles::GeneratePropertyPage( ZIProperties* pPropertiesObject, CString HtmlFilename )
{
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
    if ( !StringAlreadyGenerated( HtmlFilename ) )
    {
        ZDHtmlFile HtmlFile( HtmlFilename );
        
        if ( !HtmlFile.OpenFileCreate() )
        {
            return false;
        }

        // Retrieve the property set from object
        ZBPropertySet PropSet;
        pPropertiesObject->FillProperties( PropSet );

        // Write header
        CString s;
        CString s1;

        // The document title
        s1.LoadString( IDS_SYMBOLPROPERTY_HTML );
        s.Format( IDS_MODELGENHTML_39, (const char*)s1 );
        HtmlFile << s;
        
        bool OneAtLeast = false;

        // Run through the property set
        ZBPropertyIterator i( &PropSet );
        ZBProperty* pProp;
        CString PreviousCategory;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp->GetEnable() == false )
            {
                continue;
            }

            // Check if we want filter property attributes to display
            if ( m_pPropAttributes )
            {
                // Check if he is defined
                if ( !m_pPropAttributes->FindAttribute( pProp->GetCategoryID(), pProp->GetItemID() ) )
                {
                    continue;
                }
            }

            // Flag for closing properly the html
            OneAtLeast = true;

            CString Value;
            CString Format;

            if ( pProp->GetCategory() != PreviousCategory )
            {
                if ( !PreviousCategory.IsEmpty() )
                {
                    // If we had a previous section, close the table section
                    s.LoadString( IDS_MODELGENHTML_43 );
                    HtmlFile << s;
                }

                // Add the section name
                s.LoadString( IDS_MODELGENHTML_40 );
                HtmlFile << s;

                s.Format( IDS_MODELGENHTML_41, (const char*)pProp->GetCategory() );
                HtmlFile << s;

                s.LoadString( IDS_MODELGENHTML_42 );
                HtmlFile << s;

                // Save the category for checking changes in categories
                PreviousCategory = pProp->GetCategory();
            }

            // Retreive the formatted value
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_DOUBLE:
                {
                    Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDouble(), pProp->GetStringFormat() );
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueFloat(), pProp->GetStringFormat() );
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    // JMR-MODIF - Le 23 septembre 2005 - Cast implicite pour obtenir le bon lien objet.
//                    Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDate(), pProp->GetStringFormat() );
                    Value = ZUStringFormatter::GetFormattedBuffer( (ZBDate&)pProp->GetValueDate(),
                                                                   pProp->GetStringFormat() );
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    // JMR-MODIF - Le 23 septembre 2005 - Cast implicite pour obtenir le bon lien objet.
//                    Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueTimeSpan(), pProp->GetStringFormat() );
                    Value = ZUStringFormatter::GetFormattedBuffer( (ZBTimeSpan&)pProp->GetValueTimeSpan(),
                                                                   pProp->GetStringFormat() );
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    // JMR-MODIF - Le 23 septembre 2005 - Cast implicite pour obtenir le bon lien objet.
//                    Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDuration(), pProp->GetStringFormat() );
                    Value = ZUStringFormatter::GetFormattedBuffer( (ZBDuration&)pProp->GetValueDuration(),
                                                                   pProp->GetStringFormat() );
                    break;
                }

                case ZBProperty::PT_STRING:
                {
                    Value = pProp->GetValueString();
                    break;
                }

                default:
                {
                    break;
                }
            }

            // JMR-MODIF - Le 12 août 2007 - Supprime les espaces vides dans la publication des propriétés.
            if ( !Value.IsEmpty() )
            {
                // Add the label
                s.LoadString( IDS_MODELGENHTML_44 );
                HtmlFile << s;

                s.Format( IDS_MODELGENHTML_45, (const char*)pProp->GetLabel() );
                HtmlFile << s;

                // Add the value
                s.LoadString( IDS_MODELGENHTML_46 );
                HtmlFile << s;

                // *******************************************************************************************************
                // JMR-MODIF - Le 12 août 2007 - Le test ci-dessous n'est plus valide, puisque les lignes avec des valeurs
                // vides ne sont plus affichées du tout.

                // If value is not empty
//                if ( !Value.IsEmpty() )
//                {
                    s.Format( IDS_MODELGENHTML_47, (const char*)Value );
//                }
                /*
                else
                {
                    // If empty, insert a blank image to avoid the table border
                    // not displayed
                    CString LogoImage = m_ImageDirectory + _T( "\\" ) + g1pTransImageFile;
                    s.Format( IDS_MODELGENHTML_77, (const char*)CalculatePath( LogoImage, m_RootHtmlFilename ) );
                }
                */
                // *******************************************************************************************************

                HtmlFile << s;
            }
        }

        // Close the table if once have been opened
        if ( OneAtLeast )
        {
            s.LoadString( IDS_MODELGENHTML_43 );
            HtmlFile << s;
        }

        // End of HTML
        s.LoadString( IDS_MODELGENHTML_49 );
        HtmlFile << s;

        HtmlFile.CloseFile();

        // Remove all properties
        ZBPropertyIterator j( &PropSet );

        for ( pProp = j.GetFirst(); pProp; pProp = j.GetNext() )
        {
            delete pProp;
        }

        PropSet.RemoveAll();
    }

    return true;
}
