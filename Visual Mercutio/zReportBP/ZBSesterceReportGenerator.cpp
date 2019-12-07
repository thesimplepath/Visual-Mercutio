// ZBSesterceReportGenerator.cpp: implementation of the ZBSesterceReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSesterceReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPProcessSymbol.h"

#include "zReport\ZDGridDoc.h"

#include "zModelBP\ZUExtractProcessName.h"
#include "ZUGridSesterceProcessNavigation.h"
#include "zModelBP\ZUProcedureCalculateTotals.h"

#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"

#include "zBaseLib\PSS_Global.h"

#include "ColorRefDefinition.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBSesterceReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSesterceReportGenerator::ZBSesterceReportGenerator( ZDGridDocument*            pDoc        /*= NULL*/,
                                                      ZDProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                                     PSS_ProcessGraphModelDoc*    pSourceDoc    /*= NULL*/ )
    : ZBModelBPReportGenerator( pDoc, pModel, pSourceDoc )
{
    // Initialize the style for header cells
    m_HeaderStyle.SetTextColor( defCOLOR_BLACK )
                 .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                 .SetSize( 12 ).SetBold( TRUE ) )
                 .SetInterior( defCOLOR_ROSESESTERCE );

    m_NormalStyle.SetTextColor( defCOLOR_BLACK )
                 .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                 .SetSize( 10 ).SetBold( FALSE ) )
                 .SetInterior( defCOLOR_WHITE );
}

ZBSesterceReportGenerator::~ZBSesterceReportGenerator()
{
}

bool ZBSesterceReportGenerator::FillGrid( CGXGridCore& GridCore, size_t Index )
{
    if ( Index == 0 )
    {
        return FillGridUnit( GridCore );
    }

    return FillGridProcess( GridCore, Index );
}

bool ZBSesterceReportGenerator::FillGridUnit( CGXGridCore& GridCore )
{
    ZBOStreamGrid ostream( &GridCore );

    // Default size
    GridCore.SetRowCount( 60 );        // 60 rows
    GridCore.SetColCount( 15 );        // 15 columns

    // Display header
    CString s;

    ostream << _T( "\n\n" );

    s.LoadString( IDS_UNITNAME_H );
    ostream << s;
    ostream << CSize( 150, 60 );    // Set the cell size
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    s.LoadString( IDS_UNITDES_H );
    ostream << s;
    ostream << CSize( 200, 0 );        // Set the cell width only
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    s.LoadString( IDS_UNITCOST_H );
    ostream << s;
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    s.LoadString( IDS_UNITOWNER_H );
    ostream << s;
    ostream << CSize( 200, 0 );        // Set the cell width only
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    // Then process the group
    FillGridUnitGroup( m_pModel->GetMainUserGroup(), ostream );
    
    // The next following lines are for the resumé of all processes
    ostream << _T( "\n\n\n" );

    s.LoadString( IDS_SYMBOLREF_H );
    ostream << s;
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    s.LoadString( IDS_SYMBOLNAME_H );
    ostream << s;
    ostream << m_HeaderStyle;
    ostream << _T( "\t" );

    s.LoadString( IDS_SYMBOLDES_H );
    ostream << s;
    ostream << m_HeaderStyle;

    // Now, run through all tabs and display the correct information
    size_t Count = m_TabNameArray.GetSize();

    // Start with the second tab. First tab is this one.
    for ( size_t i = 1; i < Count; ++i )
    {
        // Find the right process, function of the model name
        // In case sensitive, and only local symbol
        CODComponentSet* pSet = m_pModel->FindSymbol( m_TabNameArray.GetAt( i ),
                                                      _T( "" ),
                                                      true,
                                                      true,
                                                      true );

        if ( !pSet || pSet->GetSize() <= 0 || pSet->GetAt( 0 ) == NULL ||
             !ISA( pSet->GetAt( 0 ), ZBBPProcessSymbol ) )
        {
            continue;
        }

        ZBBPProcessSymbol* pProcess = dynamic_cast<ZBBPProcessSymbol*>( pSet->GetAt( 0 ) );

        ostream << _T( "\n" );

        ostream << pProcess->GetSymbolReferenceNumberStr();
        ostream << m_NormalStyle;
        ostream << _T( "\t" );

        ostream << pProcess->GetSymbolName();
        ostream << m_NormalStyle;
        ostream << _T( "\t" );

        ostream << pProcess->GetSymbolComment();

        int top;
        int left;

        // Check the number of row
        ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();
        ostream.GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            ostream.GetGridCore()->SetRowCount( RowCount + 5 );
        }
    }

    return true;
}

void ZBSesterceReportGenerator::FillGridUnitGroup( ZBUserGroupEntity* pGroup, ZBOStreamGrid &ostream )
{
    if ( !pGroup )
    {
        return;
    }

    CGXStyle NumericCellStyle;
    NumericCellStyle.SetValueType( GX_VT_NUMERIC );
    
    CGXStyle AmountFormatStyle;
    AmountFormatStyle.SetFormat( GX_FMT_COMMA ).SetPlaces( 0 );

    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();
    ostream.GetCurSel( left, top );

    // If not enough, add 5 rows
    if ( ( top + 10 ) > (int)RowCount )
    {
        ostream.GetGridCore()->SetRowCount( RowCount + 10 );
    }

    // add the group line
    ostream << _T( "\n" );

    ostream << pGroup->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T( "\t" );

    ostream << pGroup->GetEntityDescription();
    ostream << m_NormalStyle;
    ostream << _T( "\t" );

    ostream << pGroup->GetEntityCost();
    ostream << m_NormalStyle;
    ostream << NumericCellStyle;
    ostream << AmountFormatStyle;
    ostream << _T( "\t" );

    if ( pGroup->GetParent() )
    {
        ostream << pGroup->GetParent()->GetEntityName();
    }
    else
    {
        ostream << _T( "" );
    }

    ostream << _T( "\t" );

    if ( pGroup->ContainEntity() )
    {
        int Count = pGroup->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBUserEntity* pEntity = pGroup->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBUserGroupEntity ) )
            {
                FillGridUnitGroup( dynamic_cast<ZBUserGroupEntity*>( pEntity ), ostream );
            }

            if ( ISA( pEntity, ZBUserRoleEntity ) )
            {
                FillGridUnitRole( dynamic_cast<ZBUserRoleEntity*>( pEntity ), ostream );
            }
        }
    }
}

void ZBSesterceReportGenerator::FillGridUnitRole( ZBUserRoleEntity* pRole, ZBOStreamGrid &ostream )
{
    // Add the role line
    ostream << _T( "\n" );

    ostream << pRole->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T( "\t" );

    ostream << pRole->GetEntityDescription();
    ostream << m_NormalStyle;
    ostream << _T( "\t" );

    ostream << _T( "" );    // No cost for a role
    ostream << _T( "\t" );

    if ( pRole->GetParent() )
    {
        ostream << pRole->GetParent()->GetEntityName();
    }
    else
    {
        ostream << _T( "" );
    }

    ostream << m_NormalStyle;
}

bool ZBSesterceReportGenerator::FillGridProcess( CGXGridCore& GridCore, size_t Index )
{
    // Check the index validity
    if ( Index >= (size_t)m_TabNameArray.GetSize() )
    {
        return false;
    }

    // Find the right process, function of the model name
    // RS-MODIF 25.12.05 - Generation rapports Sesterces se retrouve avec
    // un pointeur nul 1 tab sur 2
    // In case sensitive
    //ZDProcessGraphModelMdl* pModel = m_pModel->FindModel( m_TabNameArray.GetAt( Index ), true ); // In case sensitive
    PSS_ProcessGraphModelMdl* pModel =
        (PSS_ProcessGraphModelMdl*)m_pModel->FindModel( m_TabNameArray.GetAt( Index ), true );

    if ( !pModel )
    {
        return false;
    }

    // Construct the output stream grid object
    ZBOStreamGrid ostream( &GridCore );

    // Default size
    GridCore.SetRowCount( 60 );        // 60 rows
    GridCore.SetColCount( 15 );        // 15 columns

    // Construct the navigation grid process
    ZUGridSesterceProcessNavigation ProcessNavigation( pModel, static_cast<void*>( &ostream ) );

    // Now navigate through process symbols
    return ProcessNavigation.Navigate();
}

// To fill the tab array, use a visitor class 
void ZBSesterceReportGenerator::FillTabArray()
{
    // if no doc nor model defined. nothing to do.
    if ( !m_pDoc || !m_pModel )
    {
        return;
    }

    // First, remove all elements
    m_TabNameArray.RemoveAll();

    ZUExtractProcessName ExtractProcessName( m_pModel );

    // First tab is for the model name 
    m_TabNameArray.Add( m_pModel->GetModelName() );

    // JMR-MODIF - Le 29 mars 2006 - Ajout de l'index de tri : On trie la liste depuis l'onglet 1.
    ExtractProcessName.FillProcessNameArray( &m_TabNameArray, 1 );
}

const CString ZBSesterceReportGenerator::GetReportTitle() const
{
    // Build the title function of the model
    CString s;

    if ( m_pDoc )
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString( IDS_SESTERCE_RPT_T );

    s += _T( " [" );
    s += ReportType;
    s += _T( " : " );

    if ( m_pModel )
    {
        s += m_pModel->GetModelName();
    }
    else
    {
        s += _T( "???" );
    }

    s += _T( " ]" );

    return s;
}
