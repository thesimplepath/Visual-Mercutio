// ZUGridMercutioRepProcedureNavigation.cpp: implementation of the ZUGridMercutioRepProcedureNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUGridMercutioRepProcedureNavigation.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zReport\ZBOStreamGrid.h"

#include "ColorRefDefinition.h"

#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUGridMercutioRepProcedureNavigation::ZUGridMercutioRepProcedureNavigation( ZDProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                            void*                    pClass    /*= NULL*/ )
    : ZUProcessNavigation( pModel, pClass )
{
}

ZUGridMercutioRepProcedureNavigation::~ZUGridMercutioRepProcedureNavigation()
{
}

bool ZUGridMercutioRepProcedureNavigation::OnStart()
{
    // Start by casting the stream class
    m_postream = static_cast<ZBOStreamGrid*>( m_pClass );

    ASSERT( m_postream->GetGridCore() != NULL );

    // Initialize the normal style for cells
    m_NormalStyle.SetTextColor( defCOLOR_BLACK )
                               .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                               .SetSize( 9 ).SetBold( FALSE ) )
                               .SetInterior( defCOLOR_WHITE );

    // Initialize the normal style for cells
    m_BoldStyle.SetTextColor( defCOLOR_BLACK )
                             .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                             .SetSize( 9 ).SetBold( TRUE ) )
                             .SetInterior( defCOLOR_WHITE );

    // Initialize the blue style for header cells
    m_BlueStyle.SetTextColor( defCOLOR_BLACK )
                             .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                             .SetSize( 10 ).SetBold( FALSE ) )
                             .SetInterior( defCOLOR_BLUEMERCUTIO );

    // Initialize the bold blue style for header cells
    m_BoldBlueStyle.SetTextColor( defCOLOR_BLACK )
                                 .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                                 .SetSize( 10 ).SetBold( TRUE ) )
                                 .SetInterior( defCOLOR_BLUEMERCUTIO );

    // Initialize the blue style for header cells
    m_GrayStyle.SetTextColor( defCOLOR_WHITE )
                             .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                             .SetSize( 10 ).SetBold( TRUE ) )
                             .SetInterior( defCOLOR_GRAY );

    // Initialize the blue style for header cells
    m_LightGrayStyle.SetTextColor( defCOLOR_BLACK )
                                  .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                                  .SetSize( 9 ).SetBold( FALSE ) )
                                  .SetInterior( defCOLOR_LTGRAY );

    // Initialize the black border
    m_BlackBorderStyle.SetBorders( gxBorderAll, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );
    m_LeftOnlyBlackBorderStyle.SetBorders( gxBorderLeft, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );

    // Initialize the different cell formats
    m_PercentFormatStyle.SetFormat( GX_FMT_PERCENT ).SetPlaces( 0 );
    m_NumericCellStyle.SetValueType( GX_VT_NUMERIC ).SetPlaces( 0 );

    // Load string resources
    m_DescriptionLabel.LoadString            ( IDS_DESC_LBLRPT );
    m_UnitLabel.LoadString                    ( IDS_UNIT_LBLRPT );
    m_CombinationLabel.LoadString            ( IDS_COMBINATION_LBLRPT );
    m_RuleListLabel.LoadString                ( IDS_RULELIST_LBLRPT );
    m_TaskListLabel.LoadString                ( IDS_TASKLIST_LBLRPT );
    m_DecisionListLabel.LoadString            ( IDS_DECISIONLIST_LBLRPT );
    m_FormsLabel.LoadString                    ( IDS_FORMS_LBLRPT );
    m_AppsLabel.LoadString                    ( IDS_APP_LBLRPT );
    m_OutputDeliverableLabel.LoadString        ( IDS_OUTPUTDELIVERABLES_LBLRPT );
    m_LateralDeliverableLabel.LoadString    ( IDS_LATERALDELIVERABLES_LBLRPT );

    // Size all cells width one time
    *m_postream << CSize( 70, 0 );    // Set the cell width
    *m_postream << _T( "\t" );
    *m_postream << CSize( 170, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 90, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 90, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 90, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 90, 0 );

    // Sets the default row height for all cells
    m_postream->GetGridCore()->SetDefaultRowHeight( 20 );

/*
    // JMR-MODIF - Le 6 avril 2006 - Suppression du code ci-dessous, car inutile.
    // Change the default properties
    CGXProperties* pProperties = m_postream->GetGridCore()->GetParam()->GetProperties();

    if ( pProperties )
    {
    }
*/

    // Return true or false function of the ostream pointer
    return ( m_postream ) ? true : false;
}

bool ZUGridMercutioRepProcedureNavigation::OnFinish()
{
    int top;
    int left;

    m_postream->GetCurSel( left, top );

    // Sets the grid as read-only
    m_postream->GetGridCore()->SetReadOnly( TRUE );

    return true;
}

bool ZUGridMercutioRepProcedureNavigation::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
    // Not necessary for reference
    if ( !pSymbol->IsLocal() )
    {
        return true;
    }

    ASSERT( m_postream->GetGridCore() != NULL );

    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel( left, top );

    // If not enough, add 60 rows
    if ( ( top + 30 ) > (int)RowCount )
    {
        m_postream->GetGridCore()->SetRowCount( RowCount + 60 );
    }

    // Build the first line with the deliverable reference number and the deliverable name
    m_postream->HomeLeft();
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << m_BlueStyle;
    m_postream->SetCurSelRowHeight( 40 );
    *m_postream << _T( "\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << m_BoldBlueStyle;

    // Set the border
    m_postream->HomeLeft();
    m_postream->GetCurSel( left, top );
    m_postream->SetCurSel( left, top, left + 5, top );
    *m_postream << m_BlackBorderStyle;

    // Build the second line with the unit name
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 1 );
    *m_postream << m_UnitLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
    *m_postream << pSymbol->GetUnitName();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the third line with the procedure description
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 1 );
    *m_postream << m_DescriptionLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
    *m_postream << pSymbol->GetSymbolComment();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the fourth line with the combination label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 1 );
    *m_postream << m_CombinationLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t" );

    // Build the next columns with the combination name, maximum column is limited to 4
    std::size_t Count = min( pSymbol->GetCombinationCount(), 4 );

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << pSymbol->GetCombinationName( i );
        *m_postream << m_LightGrayStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << m_BlackBorderStyle;
        *m_postream << _T( "\t" );
    }

    // Now for each deliverables, build the line. Retreive all entering up deliverables
    CODEdgeArray Edges;

    if ( pSymbol->GetEnteringUpDeliverable( Edges ) > 0 )
    {
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge*                    pIEdge    = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol*    pComp    = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            // Check if null and continue if the case
            if ( !pComp )
            {
                continue;
            }

            // Display the reference number
            *m_postream << _T( "\n" );
            *m_postream << pComp->GetSymbolReferenceNumberStr();
            *m_postream << m_BlueStyle;
            *m_postream << _T( "\t" );

            // Display the deliverable name
            *m_postream << pComp->GetSymbolName();
            *m_postream << m_GrayStyle;
            *m_postream << _T( "\t" );

            bool Found = false;

            // Now, for each column, try to find if the deliverable is part of the combination
            for ( size_t combIndex = 0; combIndex < 4 && Found == false; ++combIndex )
            {
                if ( pSymbol->IsDeliverableInString( pSymbol->GetCombinationDeliverables( combIndex ),
                                                     pComp->GetSymbolName() ) )
                {
                    Found = true;

                    if ( pSymbol->GetCombinationMaster( combIndex ) == pComp->GetSymbolName() )
                    {
                        *m_postream << pComp->GetCombinationMaxPercentage();
                        *m_postream << m_PercentFormatStyle;
                        *m_postream << m_NumericCellStyle;
                    }
                    else
                    {
                        *m_postream << _T( "x" );
                    }

                    *m_postream << m_NormalStyle;
                }

                *m_postream << _T( "\t" );
            }
        }
    }

    // Build the next line with the rule list label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_RuleListLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the rules themselves, at least one empty line
    Count = max( pSymbol->GetRuleCount(), 1 );

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetRuleAt( i );
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the next line with the task list label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_TaskListLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the tasks themselves, at least one empty line
    Count = max( pSymbol->GetTaskCount(), 1 );

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetTaskAt( i );
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the next line with the decision list label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_DecisionListLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the decisions themselves, at least one empty line
    Count = max( pSymbol->GetDecisionCount(), 1 );

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetDecisionAt(i);
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the line with the forms, document label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_FormsLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the forms, document and other
    Count = pSymbol->GetExtFileCount();

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetFileTitle(i);
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the line with the external application label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_AppsLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the forms, document and other
    Count = pSymbol->GetExtAppCount();

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetCommandTitle( i );
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the line with the output deliverables
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_OutputDeliverableLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Now for each deliverables, build the line. Retreive all leaving down deliverables
    if ( pSymbol->GetLeavingDownDeliverable( Edges ) > 0 )
    {
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge*                    pIEdge    = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol*    pComp    = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            // Check if null and continue if the case
            if ( !pComp )
            {
                continue;
            }

            // Display the reference number
            *m_postream << _T( "\n" );
            *m_postream << pComp->GetSymbolReferenceNumberStr();
            *m_postream << m_BlueStyle;
            *m_postream << _T( "\t" );

            // Display the deliverable name
            m_postream->GetCurSel( left, top );
            m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
            *m_postream << pComp->GetSymbolName();
            *m_postream << m_NormalStyle;
            *m_postream << _T( "\t\t\t\t" );

            // Display the output workload deliverable. Test if it is a local symbol
            if ( !pComp->IsLocal() )
            {
                // Locate the local symbol
                CODComponent* pLocal = pComp->GetLocalSymbol();

                if ( pLocal && ISA( pLocal, ZBDeliverableLinkSymbol ) )
                {
                    pComp = dynamic_cast<ZBDeliverableLinkSymbol*>( pLocal );
                }
                else
                {
                    pComp = NULL;
                }
            }

            if ( pComp )
            {
                *m_postream << pComp->GetOutWorkloadPercent();
            }
            else
            {
                *m_postream << _T( "#ERR" );
            }

            *m_postream << m_NormalStyle;
            *m_postream << m_PercentFormatStyle;
            *m_postream << m_NumericCellStyle;
        }
    }

    // Build the line with the lateral deliverables
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_LateralDeliverableLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Now for each deliverables, build the line. Retreive all leaving right deliverables
    if ( pSymbol->GetLeavingRightDeliverable( Edges ) > 0 )
    {
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge*                    pIEdge    = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol*    pComp    = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            // Check if null and continue if the case
            if ( !pComp )
            {
                continue;
            }

            // Display the reference number
            *m_postream << _T( "\n" );
            *m_postream << pComp->GetSymbolReferenceNumberStr();
            *m_postream << m_BlueStyle;
            *m_postream << _T( "\t" );

            // Display the deliverable name
            m_postream->GetCurSel( left, top );
            m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
            *m_postream << pComp->GetSymbolName();
            *m_postream << m_NormalStyle;
            *m_postream << _T( "\t\t\t\t" );

            // Display the output workload deliverable. Test if it is a local symbol
            if ( !pComp->IsLocal() )
            {
                // Locate the local symbol
                CODComponent* pLocal = pComp->GetLocalSymbol();

                if ( pLocal && ISA( pLocal, ZBDeliverableLinkSymbol ) )
                {
                    pComp = dynamic_cast<ZBDeliverableLinkSymbol*>( pLocal );
                }
                else
                {
                    pComp = NULL;
                }
            }

            if ( pComp )
            {
                *m_postream << pComp->GetOutWorkloadPercent();
            }
            else
            {
                *m_postream << _T( "#ERR" );
            }

            *m_postream << m_NormalStyle;
            *m_postream << m_PercentFormatStyle;
            *m_postream << m_NumericCellStyle;
        }
    }

    // Retreive all leaving left deliverables
    if ( pSymbol->GetLeavingLeftDeliverable( Edges ) > 0 )
    {
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge*                    pIEdge    = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol*    pComp    = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            // Check if null and continue if the case
            if ( !pComp )
            {
                continue;
            }

            // Display the reference number
            *m_postream << _T( "\n" );
            *m_postream << pComp->GetSymbolReferenceNumberStr();
            *m_postream << m_BlueStyle;
            *m_postream << _T( "\t" );

            // Display the deliverable name
            m_postream->GetCurSel( left, top );
            m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
            *m_postream << pComp->GetSymbolName();
            *m_postream << m_NormalStyle;
            *m_postream << _T( "\t\t\t\t" );

            // Display the output workload deliverable. Test if it is a local symbol
            if ( !pComp->IsLocal() )
            {
                // Locate the local symbol
                CODComponent* pLocal = pComp->GetLocalSymbol();

                if ( pLocal && ISA( pLocal, ZBDeliverableLinkSymbol ) )
                {
                    pComp = dynamic_cast<ZBDeliverableLinkSymbol*>( pLocal );
                }
                else
                {
                    pComp = NULL;
                }
            }

            if ( pComp )
            {
                *m_postream << pComp->GetOutWorkloadPercent();
            }
            else
            {
                *m_postream << _T( "#ERR" );
            }

            *m_postream << m_NormalStyle;
            *m_postream << m_PercentFormatStyle;
            *m_postream << m_NumericCellStyle;
        }
    }

    *m_postream << _T( "\n" );
    *m_postream << _T( "\n" );

    return true;
}
