// ******************************************************************************************************
// *                                 Classe ZVPublishPrestationsReport                                    *
// ******************************************************************************************************
// * JMR-MODIF - Le 1er mars 2006 - Création de la nouvelle classe ZVPublishProcessReport.                *
// ******************************************************************************************************
// * Cette classe effectue la publication du rapport processus en tant que pages Internet.                *
// ******************************************************************************************************

#include "stdafx.h"
#include "ZVPublishPrestationsReport.h"

#include "zReportWebRes.h"
#include "PSS_ModelResIDs.h"

// ******************************************************************************************************
// *                                   Construction et destruction                                        *
// ******************************************************************************************************

// Constructeur de la classe ZVPublishProcessReport.
ZVPublishPrestationsReport::ZVPublishPrestationsReport( ZDProcessGraphModelMdlBP* pModel /*= NULL*/ )
{
    m_pRootModel = pModel;
}

// Destructeur de la classe ZVPublishProcessReport.
ZVPublishPrestationsReport::~ZVPublishPrestationsReport()
{
}

// ******************************************************************************************************
// *                     Fonctions publiques de la classe ZVPublishPrestationsReport                    *
// ******************************************************************************************************

// Cette fonction permet de publier le rapport dans le répertoire fourni en entrée.
bool ZVPublishPrestationsReport::Publish( CString Directory )
{
    // if no doc nor model defined. nothing to do.
    if ( !m_pRootModel )
    {
        return false;
    }

    // Create the window for file generation feedback
    m_FileGenerateWindow.Create();

    if ( !CreateFileSystem( m_pRootModel->GetMainLogicalPrestations(), Directory ) )
    {
        // Hide the feedback dialog
        m_FileGenerateWindow.ShowWindow( SW_HIDE );

        return false;
    }

    // Hide the feedback dialog
    m_FileGenerateWindow.ShowWindow( SW_HIDE );

    return true;
}

// ******************************************************************************************************
// *                    Fonctions privées de la classe ZVPublishPrestationsReport                        *
// ******************************************************************************************************

// Retrouve et publie les procédures, avec leurs groupes associés, dans les pages enfants d'un processus.
void ZVPublishPrestationsReport::FindProcedures( CString ProcessName, ZDProcessGraphModelMdlBP* m_StartModel )
{
    if ( m_StartModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        ZBProcessGraphPageSet* pSet = m_StartModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contrôleur de modèle de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'une procédure.
                            if ( pComponent && ISA( pComponent, ZBBPProcedureSymbol ) )
                            {
                                ZBBPProcedureSymbol* m_Procedure = dynamic_cast<ZBBPProcedureSymbol*>( pComponent );

                                ZBPropertySet PropSet;
                                m_Procedure->FillProperties( PropSet );

                                ZBPropertyIterator k( &PropSet );
                                ZBProperty* pProp;

                                for ( pProp = k.GetFirst(); pProp; pProp = k.GetNext() )
                                {
                                    // Si la catégorie est nouvelle, on crée une nouvelle section.
                                    if ( pProp->GetCategoryID() == ZS_BP_PROP_UNIT &&
                                         pProp->GetItemID()        == Z_UNIT_NAME )
                                    {
                                        GenerateHTMLSectionLine( pProp->GetValueString(),
                                                                 ProcessName,
                                                                 m_Procedure->GetSymbolName() );

                                        // JMR-MODIF - Le 28 mars 2006 - Finalement, on ne publie plus les enfants.
                                        /*FindUnitGroupChilds( m_pRootModel->GetMainUserGroup(),
                                                             pProp->GetValueString(),
                                                             ProcessName,
                                                             m_Procedure->GetSymbolName() );*/
                                    }
                                }

                                for ( pProp = k.GetFirst(); pProp; pProp = k.GetNext() )
                                {
                                    if ( pProp != NULL )
                                    {
                                        delete pProp;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Explore le document, recherche les processus contenus, et teste s'ils contiennent la prestation demandée.
void ZVPublishPrestationsReport::ExploreProcessHierarchy( CString                    PrestationName,
                                                          ZDProcessGraphModelMdlBP*    m_StartRootModel    /*= NULL*/ )
{
    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if ( m_StartRootModel == NULL )
    {
        // Obtient le contrôleur de modèles du document.
        m_StartRootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pRootModel );
    }

    if ( m_StartRootModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        ZBProcessGraphPageSet* pSet = m_StartRootModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contrôleur de modèle de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if ( pComponent && ISA( pComponent, ZBBPProcessSymbol ) )
                            {
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>( pComponent );

                                if ( m_Process != NULL )
                                {
                                    // Obtient le contrôleur de modèles enfant du processus.
                                    ZDProcessGraphModelMdlBP* m_ChildModel =
                                        dynamic_cast<ZDProcessGraphModelMdlBP*>( m_Process->GetpModel() );

                                    // Si le contrôleur de modèles existe, fait un appel récursif sur celui-ci,
                                    // afin de passer en revue toutes les pages du document.
                                    if ( m_ChildModel != NULL )
                                    {
                                        ExploreProcessHierarchy( PrestationName, m_ChildModel );
                                    }

                                    PSS_Tokenizer m_PrestationsList = m_Process->GetPrestationsList();

                                    for ( size_t k = 0; k < m_PrestationsList.GetTokenCount(); k++ )
                                    {
                                        CString ProcessPrestationName = _T( "" );
                                        m_PrestationsList.GetTokenAt( k, ProcessPrestationName );

                                        if ( ProcessPrestationName == PrestationName )
                                        {
                                            FindProcedures( m_Process->GetSymbolName(), m_ChildModel );
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// JMR-MODIF - Le 28 mars 2006 - !!! Cette fonction n'est plus utilisée depuis ce jour, car abandon de la
// publication des enfants. Voir dans le futur si cette fonction pouuvait être utile, sinon la supprimer.
// Cette fonction permet de retrouver les groupes enfants associés au groupe demandé, et de les intégere au rapport.
void ZVPublishPrestationsReport::FindUnitGroupChilds( ZBUserGroupEntity*    pGroup,
                                                      CString                PropertyName,
                                                      CString                ProcessName,
                                                      CString                ProcedureName,
                                                      BOOL                    ChildMode,        /*= FALSE*/
                                                      int                    ChildLevel        /*= 0*/ )
{
    if ( pGroup == NULL )
    {
        return;
    }

    CString GroupName = pGroup->GetEntityName();

    if ( GroupName == PropertyName || ChildMode == TRUE )
    {
        if ( ChildMode == TRUE )
        {
            CString ChildGroupName = _T( "" );

            for ( int i = 0; i < ChildLevel; i++ )
            {
                ChildGroupName += _T( "---" );
            }

            ChildGroupName += _T( ">" );
            ChildGroupName += GroupName;

            GenerateHTMLSectionLine( ChildGroupName, ProcessName, ProcedureName );
        }
        else
        {
            GenerateHTMLSectionLine( GroupName, ProcessName, ProcedureName );
            ChildMode = TRUE;
        }
    }

    // Teste si le groupe contient des groupes enfants.
    if ( pGroup->ContainEntity() )
    {
        int Count = pGroup->GetEntityCount();

        for ( int j = 0; j < Count; ++j )
        {
            ZBUserEntity* pEntity = pGroup->GetEntityAt( j );

            if ( !pEntity )
            {
                continue;
            }

            // Teste si l'objet enfant est bien un objet de type ZBLogicalPrestationsEntity.
            if ( ISA( pEntity, ZBUserGroupEntity ) )
            {
                int ChildLevelCount = ChildLevel;

                if ( ChildMode == TRUE )
                {
                    ChildLevelCount++;
                }

                FindUnitGroupChilds( dynamic_cast<ZBUserGroupEntity*>( pEntity ),
                                     PropertyName,
                                     ProcessName,
                                     ProcedureName,
                                     ChildMode,
                                     ChildLevelCount );
            }
        }
    }
}

// Cette fonction permet de créer le système de fichiers.
bool ZVPublishPrestationsReport::CreateFileSystem( ZBLogicalPrestationsEntity* pPrestations, CString Directory )
{
    if ( pPrestations == NULL )
    {
        return false;
    }

    // Obtient le nom de la prestation.
    CString PrestationName = pPrestations->GetEntityName();
    CString PrestationDesc = pPrestations->GetEntityDescription();

    if ( !HtmlFile.Create( GenerateFilename( Directory, PrestationName ) ) )
    {
        return false;
    }

    m_FileGenerateWindow.SetDestination( GenerateFilename( Directory, PrestationName ) );
    m_FileGenerateWindow.UpdateWindow();

    GenerateHTMLPageHead( PrestationName );

    GenerateHTMLTableHead();
    GenerateHTMLReportTitle( PrestationName, PrestationDesc );
    GenerateHTMLTableFoot();

    GenerateHTMLTableHead();
    CreateReport( PrestationName );
    GenerateHTMLTableFoot();

    GenerateHTMLPageFoot();

    HtmlFile.CloseFile();

    // Teste si la prestation contient des prestations enfants.
    if ( pPrestations->ContainEntity() )
    {
        int Count = pPrestations->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBPrestationsEntity* pEntity = pPrestations->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            // Teste si l'objet enfant est bien un objet de type ZBLogicalPrestationsEntity.
            if ( ISA( pEntity, ZBLogicalPrestationsEntity ) )
            {
                CreateFileSystem( dynamic_cast<ZBLogicalPrestationsEntity*>( pEntity ), Directory );
            }
        }
    }

    return true;
}

// Cette fonction permet de publier les données du rapport.
void ZVPublishPrestationsReport::CreateReport( CString PrestationName )
{
    GenerateHTMLSectionTitle();
    ExploreProcessHierarchy( PrestationName );
}

// Cette fonction permet de créer le nom de fichier correct pour chaque page du rapport.
CString ZVPublishPrestationsReport::GenerateFilename( CString Directory, CString PrestationName )
{
    CString sFilename     = Directory;
    sFilename            += _T( "PrestationsReport_" );
    sFilename            += PSS_StringTools::ConvertSpecialChar( PrestationName );
    sFilename            += _T( ".htm" );

    return sFilename;
}

// Cette fonction permet la génération d'un en-tête standard HTML.
void ZVPublishPrestationsReport::GenerateHTMLPageHead( CString Title )
{
    CString Output = _T( "" );

    Output.Format( IDS_PRESTATIONSREPORT_HTML_1, Title );

    WriteLine( Output );
}

// Cette fonction permet la génération d'un pied de page standard HTML.
void ZVPublishPrestationsReport::GenerateHTMLPageFoot()
{
    WriteLine( IDS_PRESTATIONSREPORT_HTML_2 );
}

// Cette fonction permet de générer un en-tête pour un tableau dans la page HTML.
void ZVPublishPrestationsReport::GenerateHTMLTableHead()
{
    WriteLine( IDS_PRESTATIONSREPORT_HTML_3 );
}

// Cette fonction permet de générer une fin pour un tableau dans la page HTML.
void ZVPublishPrestationsReport::GenerateHTMLTableFoot()
{
    WriteLine( IDS_PRESTATIONSREPORT_HTML_4 );
}

// Cette fonction permet de générer le titre du rapport dans la page HTML.
void ZVPublishPrestationsReport::GenerateHTMLReportTitle( CString PrestationName, CString Description )
{
    CString Output                = _T( "" );
    CString DescriptionTitle    = _T( "" );

    DescriptionTitle.LoadString( IDS_PRESTATIONSREPORT_MTL_HTML_1 );

    Output.Format( IDS_PRESTATIONSREPORT_HTML_5,
                   PrestationName,
                   DescriptionTitle,
                   Description );

    WriteLine( Output );
}

// Cette fonction permet de générer un titre de section dans la page HTML.
void ZVPublishPrestationsReport::GenerateHTMLSectionTitle()
{
    CString Output            = _T( "" );
    CString GroupNameTitle    = _T( "" );
    CString ProcessTitle    = _T( "" );
    CString ProcedureTitle    = _T( "" );

    GroupNameTitle.LoadString    ( IDS_PRESTATIONSREPORT_MTL_HTML_2 );
    ProcessTitle.LoadString        ( IDS_PRESTATIONSREPORT_MTL_HTML_5 );
    ProcedureTitle.LoadString    ( IDS_PRESTATIONSREPORT_MTL_HTML_3 );

    Output.Format( IDS_PRESTATIONSREPORT_HTML_6, GroupNameTitle, ProcessTitle, ProcedureTitle );

    WriteLine( Output );
}

// Cette fonction permet de générer une ligne de section dans la page HTML.
void ZVPublishPrestationsReport::GenerateHTMLSectionLine( CString Group, CString Processus, CString Procedure )
{
    CString Output = _T( "" );

    if ( Group == _T( "" ) )
    {
        Group.LoadString( IDS_PRESTATIONSREPORT_MTL_HTML_4 );
    }

    if ( Processus == _T( "" ) )
    {
        Processus.LoadString( IDS_PRESTATIONSREPORT_MTL_HTML_4 );
    }

    if ( Procedure == _T( "" ) )
    {
        Procedure.LoadString( IDS_PRESTATIONSREPORT_MTL_HTML_4 );
    }

    Output.Format( IDS_PRESTATIONSREPORT_HTML_7, Group, Processus, Procedure );

    WriteLine( Output );
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque, en provenance d'un ID.
void ZVPublishPrestationsReport::WriteLine( int nID )
{
    CString Output = _T( "" );

    Output.LoadString( nID );

    if ( Output != _T( "" ) )
    {
        HtmlFile << Output;
    }
}

// Cette fonction permet d'écrire une chaîne de caractères sur le disque.
void ZVPublishPrestationsReport::WriteLine( CString Text )
{
    if ( Text != _T( "" ) )
    {
        HtmlFile << Text;
    }
}
