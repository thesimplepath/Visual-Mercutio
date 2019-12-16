// ZUGridMercutioRepDeliverableNavigation.cpp: implementation of the ZUGridMercutioRepDeliverableNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUGridMercutioRepDeliverableNavigation.h"

#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

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

ZUGridMercutioRepDeliverableNavigation::ZUGridMercutioRepDeliverableNavigation(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                                void*                    pClass    /*= NULL*/ )
    : ZUProcessNavigation( pModel, pClass )
{
}

ZUGridMercutioRepDeliverableNavigation::~ZUGridMercutioRepDeliverableNavigation()
{
}

bool ZUGridMercutioRepDeliverableNavigation::OnStart()
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
                             .SetInterior(defCOLOR_WHITE);

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

    // Load string resources
    m_DescriptionLabel.LoadString            ( IDS_DESC_LBLRPT );
    m_RuleListLabel.LoadString                ( IDS_RULELIST_LBLRPT );
    m_KeyInfoLabel.LoadString                ( IDS_KEYINFO_LBLRPT );
    m_FormListLabel.LoadString                ( IDS_FORMLST_LBLRPT );
    m_InputProcedureLabel.LoadString        ( IDS_INPUTPROC_LBLRPT );
    m_OutputProcedureLabel.LoadString        ( IDS_OUTPUTPROC_LBLRPT );
    m_ComingFromProcedureLabel.LoadString    ( IDS_COMINGFROMPROC_LBLRPT );
    m_GoingToProcedureLabel.LoadString        ( IDS_GOINGTOPROC_LBLRPT );
    m_InitialProcedureLabel.LoadString        ( IDS_INITIALPROC_LBLRPT );
    m_FinalProcedureLabel.LoadString        ( IDS_FINALPROC_LBLRPT );

    // Size all cells width one time
    *m_postream << CSize( 70, 0 );    // Set the cell width
    *m_postream << _T( "\t" );
    *m_postream << CSize( 100, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 100, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 100, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 100, 0 );
    *m_postream << _T( "\t" );
    *m_postream << CSize( 100, 0 );

    // Sets the default row height for all cells
    m_postream->GetGridCore()->SetDefaultRowHeight( 20 );

/*
    // JMR-MODIF - Le 6 avril 2006 - Suppression du code ci-dessous, car inutile.
    // Change the default properties
    CGXProperties* pProperties = m_postream->GetGridCore()->GetParam()->GetProperties();

    if (pProperties)
    {
    }
*/

    // Return true or false function of the ostream pointer
    return ( m_postream ) ? true : false;
}

bool ZUGridMercutioRepDeliverableNavigation::OnFinish()
{
    int top;
    int left;

    m_postream->GetCurSel( left, top );

    // Sets the grid as read-only
    m_postream->GetGridCore()->SetReadOnly( TRUE );

    return true;
}

bool ZUGridMercutioRepDeliverableNavigation::OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
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

    // Build the first line with the deliverable reference number and the deliverable name.
    m_postream->HomeLeft();

    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << m_BlueStyle;
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

    // Build the second line with the deliverable description
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

    // Build the third line with the key info label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_KeyInfoLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next lines with the key info itself, at least one empty line
    std::size_t Count = max( pSymbol->GetTextItemCount(), 1 );

    for (std::size_t i = 0; i < Count; ++i)
    {
        *m_postream << _T( "\n" );
        *m_postream << m_BlueStyle;
        *m_postream << m_LeftOnlyBlackBorderStyle;
        *m_postream << _T( "\t" );

        m_postream->GetCurSel( left, top );
        m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 4 );
        *m_postream << pSymbol->GetTextItemAt( i );
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
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
        *m_postream << pSymbol->GetRuleAt(i);
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }

    // Build the third line with the forms, document label
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 5 );
    *m_postream << m_FormListLabel;
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

    // Build the third line with the input procedure name
    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
    *m_postream << m_InputProcedureLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 1 );
    *m_postream << m_GoingToProcedureLabel;
    *m_postream << m_LightGrayStyle;
    *m_postream << m_BlackBorderStyle;

    CString ProcedureNumber;
    CString ProcedureName;
    CString ProcessName;

    // Empty the process name
    ProcessName.Empty();

    // Retrieve the output procedure name
    ZBBPProcedureSymbol* pProcedure = pSymbol->GetTargetProcedure();
    ZBBPProcessSymbol* pProcess = pSymbol->GetComingFromProcess();

    if ( pProcess )
    {
        ProcedureNumber    = pProcess->GetSymbolReferenceNumberStr();
        ProcessName        = pProcess->GetSymbolName();
    }

    if ( pProcedure )
    {
        ProcedureNumber    = pProcedure->GetSymbolReferenceNumberStr();
        ProcedureName    = pProcedure->GetSymbolName();
    }
    else if ( pSymbol->IsFinal() )
    {
        ProcedureNumber    = m_FinalProcedureLabel;
        ProcedureName    = _T( "" );
        ProcessName        = _T( "" );
    }

    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left );
    *m_postream << ProcedureNumber;
    *m_postream << m_BlueStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left + 2 );
    *m_postream << ProcedureName;
    *m_postream << m_BoldStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left + 1 );
    *m_postream << ProcessName;
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;

    // Build the next line with the output procedure name
    *m_postream << _T( "\n\n" );    // Two newline, since we have written information on two lines
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 3 );
    *m_postream << m_OutputProcedureLabel;
    *m_postream << m_GrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top, left + 1 );
    *m_postream << m_ComingFromProcedureLabel;
    *m_postream << m_LightGrayStyle;
    *m_postream << m_BlackBorderStyle;

    // Empty the process name
    ProcessName.Empty();

    // Retrieve the input procedure name
    pProcedure    = pSymbol->GetSourceProcedure();
    pProcess    = pSymbol->GetComingFromProcess();

    if ( pProcess )
    {
        ProcedureNumber    = pProcess->GetSymbolReferenceNumberStr();
        ProcessName        = pProcess->GetSymbolName();
    }

    if ( pProcedure )
    {
        ProcedureNumber    = pProcedure->GetSymbolReferenceNumberStr();
        ProcedureName    = pProcedure->GetSymbolName();
    }
    else if ( pSymbol->IsInitial() )
    {
        // Locate if an inter-process deliverable
        ProcedureNumber    = m_InitialProcedureLabel;
        ProcedureName    = _T( "" );
        ProcessName        = _T( "" );
    }

    *m_postream << _T( "\n" );
    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left );
    *m_postream << ProcedureNumber;
    *m_postream << m_BlueStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left + 2 );
    *m_postream << ProcedureName;
    *m_postream << m_BoldStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\t\t\t" );

    m_postream->GetCurSel( left, top );
    m_postream->GetGridCore()->SetCoveredCellsRowCol( top, left, top + 1, left + 1 );
    *m_postream << ProcessName;
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T( "\n\n" );

    *m_postream << _T( "\n" );
    *m_postream << _T( "\n" );

    return true;
}
