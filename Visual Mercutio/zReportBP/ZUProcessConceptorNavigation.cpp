// ZUProcessConceptorNavigation.cpp: implementation of the ZUProcessConceptorNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessConceptorNavigation.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zReport\ZBOStreamGrid.h"

#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessConceptorNavigation::ZUProcessConceptorNavigation( ZDProcessGraphModelMdl*    pModel                    /*= NULL*/,
                                                            void*                    pClass                    /*= NULL*/,
                                                            ZDProcessGraphModelMdl*    pRootModel                /*= NULL*/,
                                                            const CString            domainName                /*= ""*/,
                                                            const CString            unitName                /*= ""*/,
                                                            BOOL                    bIncludeSynthesis        /*= TRUE*/,
                                                            BOOL                    bIncludeDetail            /*= TRUE*/,
                                                            BOOL                    bIncludeDeliverables    /*= TRUE*/ )
    : ZUProcessNavigation    ( pModel, pClass ),
      m_pRootModel            ( pRootModel ),
      m_DomainName            ( domainName ),
      m_UnitName            ( unitName )
{
    m_IncludeSynthesis        = bIncludeSynthesis;
    m_IncludeDetail            = bIncludeDetail;
    m_IncludeDeliverables    = bIncludeDeliverables;
    m_First                    = false;
    m_pPreviousProcess        = NULL;
}

ZUProcessConceptorNavigation::~ZUProcessConceptorNavigation()
{
}

// Cette fonction est appelée lorsque la navigation démarre.
bool ZUProcessConceptorNavigation::OnStart()
{
    // Start by casting the stream class
    m_postream = static_cast<ZBOStreamGrid*>( m_pClass );
    
    m_GrayStyle.SetTextColor( defCOLOR_WHITE )
                             .SetFont( CGXFont().SetFaceName( _T( "Verdana" ) )
                             .SetSize( 9 ).SetBold( FALSE ) )
                             .SetInterior( defCOLOR_GRAY );

    m_BlueStyle.SetTextColor( defCOLOR_BLACK )
                             .SetInterior( RGB( 0, 128, 255 ) );

    m_OrangeStyle.SetTextColor( defCOLOR_BLACK )
                               .SetInterior( RGB( 250, 128, 64 ) );

    // Initialize the black border
    m_BlackBorderStyle.SetBorders            ( gxBorderAll, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );
    m_LeftOnlyBlackBorderStyle.SetBorders    ( gxBorderLeft, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );
    m_RightOnlyBlackBorderStyle.SetBorders    ( gxBorderRight, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );
    m_TopOnlyBlackBorderStyle.SetBorders    ( gxBorderTop, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );
    m_BottomOnlyBlackBorderStyle.SetBorders    ( gxBorderBottom, CGXPen().SetWidth( 1 ).SetColor( defCOLOR_BLACK ) );

    return ( m_postream ) ? true : false;
}

// Cette fonction est appelée lorsque la navigation se termine.
bool ZUProcessConceptorNavigation::OnFinish()
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcedureSymbol dans le modèle.
bool ZUProcessConceptorNavigation::OnProcedureSymbol( ZBBPProcedureSymbol* pProcedure )
{
    // Check the number of row
    int left, top;

    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel( left, top );

    // If not enough, add 30 rows
    if ( ( top + 30 ) > (int)RowCount )
    {
        m_postream->GetGridCore()->SetRowCount( RowCount + 30 );
    }

    // Check if for the same unit
    bool Error;

    CString UnitName = pProcedure->RetreiveUnitName( pProcedure->GetUnitGUID(), Error );

    if ( UnitName != m_UnitName )
    {
        return true;
    }

    // If not yet displayed, display the process section
    if ( m_First == false )
    {
        DisplayProcess();
    }

    CGXStyle WrapStyle;
    WrapStyle.SetWrapText( TRUE );

    CString s = _T( "" );

    // Display the section
    *m_postream << _T( "\n" );
    *m_postream << pProcedure->GetSymbolReferenceNumberStr();
    *m_postream << m_BlueStyle;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << _T( "\t" );

    s.LoadString( IDS_CONCEPTOR_PROCEDURE );
    *m_postream << s;
    *m_postream << m_GrayStyle;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << _T( "\t" );

    *m_postream << pProcedure->GetSymbolName();
    *m_postream << WrapStyle;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << _T( "\n" );

    s.LoadString( IDS_CONCEPTOR_DESCRIPTION );
    *m_postream << s;
    *m_postream << m_BlueStyle;
    *m_postream << _T( "\t" );

    *m_postream << pProcedure->GetSymbolComment();
    *m_postream << WrapStyle;
    *m_postream << _T( "\n" );

    if ( m_IncludeDeliverables )
    {
        s.LoadString( IDS_CONCEPTOR_DELIVERABLE_ENTRY );
        *m_postream << s;
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\n" );

        // Retreive all entering up deliverables
        CODEdgeArray Edges;

        if ( pProcedure->GetEnteringUpDeliverable( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }

        s.LoadString( IDS_CONCEPTOR_DELIVERABLE_LATERAL_OUTPUT );
        *m_postream << s;
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\n" );

        // Retreive all leaving right deliverables
        if ( pProcedure->GetEdgesLeaving_Right( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << WrapStyle;
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }

        // Retreive all leaving left deliverables
        if ( pProcedure->GetEdgesLeaving_Left( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << WrapStyle;
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }

        s.LoadString( IDS_CONCEPTOR_DELIVERABLE_LATERAL_ENTRY );
        *m_postream << s;
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\n" );

        // Retreive all entering right deliverables
        if ( pProcedure->GetEdgesEntering_Right( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << WrapStyle;
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }

        // Retreive all entering left deliverables
        if ( pProcedure->GetEdgesEntering_Left( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << WrapStyle;
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }
    }

    RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel( left, top );

    // If not enough, add 5 rows
    if ( ( top + 20 ) > (int)RowCount )
    {
        m_postream->GetGridCore()->SetRowCount( RowCount + 20 );
    }

    // Rules, decisions, tasks, etc.
    s.LoadString( IDS_CONCEPTOR_RULESLIST );
    *m_postream << s;
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\n" );

    // Build the next lines with the 
    // rules themselves, at least one empty line
    int Count = max( pProcedure->GetRuleCount(), 1 );

    for ( int i = 0; i < Count; ++i )
    {
        s.Format( IDS_CONCEPTOR_RULE_NB, i + 1 );
        *m_postream << s;
        *m_postream << m_BlueStyle;
        *m_postream << _T( "\t" );
        *m_postream << pProcedure->GetRuleAt( i );
        *m_postream << WrapStyle;
        *m_postream << _T( "\n" );

        // Check the number of row
        int left, top;
        ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
        m_postream->GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
        }
    }

    s.LoadString( IDS_CONCEPTOR_TASKSLIST );
    *m_postream << s;
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\n" );

    // Build the next lines with the 
    // tasks themselves, at least one empty line
    Count = max( pProcedure->GetTaskCount(), 1 );

    for ( i = 0; i < Count; ++i )
    {
        s.Format( IDS_CONCEPTOR_TASK_NB, i + 1 );
        *m_postream << s;
        *m_postream << m_BlueStyle;
        *m_postream << _T( "\t" );
        *m_postream << pProcedure->GetTaskAt( i );
        *m_postream << WrapStyle;
        *m_postream << _T( "\n" );

        // Check the number of row
        int left, top;
        ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
        m_postream->GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
        }
    }

    s.LoadString( IDS_CONCEPTOR_DECISIONSLIST );
    *m_postream << s;
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\t" );
    *m_postream << m_GrayStyle;
    *m_postream << _T( "\n" );

    // Build the next lines with the 
    // decisions themselves, at least one empty line
    Count = max( pProcedure->GetDecisionCount(), 1 );

    for ( i = 0; i < Count; ++i )
    {
        s.Format( IDS_CONCEPTOR_DECISION_NB, i + 1 );
        *m_postream << s;
        *m_postream << m_BlueStyle;
        *m_postream << _T( "\t" );
        *m_postream << pProcedure->GetDecisionAt( i );
        *m_postream << WrapStyle;
        *m_postream << _T( "\n" );

        // Check the number of row
        int left, top;
        ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
        m_postream->GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
        }
    }

    if ( m_IncludeDeliverables )
    {
        s.LoadString( IDS_CONCEPTOR_DELIVERABLE_OUTPUT );
        *m_postream << s;
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\n" );

        // Retreive all leaving down deliverables
        CODEdgeArray Edges;

        if ( pProcedure->GetEdgesLeaving_Down( Edges ) > 0 )
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
                *m_postream << pComp->GetSymbolReferenceNumberStr();
                *m_postream << m_BlueStyle;
                *m_postream << _T( "\t" );

                // Display the deliverable name
                *m_postream << pComp->GetSymbolName();
                *m_postream << WrapStyle;
                *m_postream << _T( "\n" );

                // Check the number of row
                int left, top;
                ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
                m_postream->GetCurSel( left, top );

                // If not enough, add 5 rows
                if ( ( top + 5 ) > (int)RowCount )
                {
                    m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
                }
            }
        }
    }

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcessSymbol dans le modèle.
bool ZUProcessConceptorNavigation::OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
    m_pPreviousProcess        = pSymbol;
    m_CurrentProcessName    = pSymbol->GetSymbolName();

    ZDProcessGraphModelMdl* pOwnerModel = (ZDProcessGraphModelMdl*)pSymbol->GetOwnerModel();

    if ( pOwnerModel )
    {
        ZDProcessGraphPage* pPage = m_pRootModel->FindModelPage( pOwnerModel, true );

        if ( pPage )
        {
            m_DomainName = pPage->GetPageName();
        }
        else
        {
            m_DomainName.LoadString( IDS_CONCEPTOR_NOT_FOUND );
        }
    }

    m_First = false;

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBSymbol dans le modèle.
bool ZUProcessConceptorNavigation::OnSymbol( ZBSymbol* pSymbol )
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBLinkSymbol dans le modèle.
bool ZUProcessConceptorNavigation::OnLink( ZBLinkSymbol* pLink )
{
    return true;
}

bool ZUProcessConceptorNavigation::DisplayProcess()
{
    if ( m_pPreviousProcess == NULL )
    {
        return true;
    }

    m_First = true;

    CGXStyle Style;

    Style.SetTextColor( defCOLOR_BLACK )
                       .SetInterior( RGB( 250, 128, 64 ) );

    CGXStyle WrapStyle;
    WrapStyle.SetWrapText( TRUE );

    // Check the number of row
    int left, top;

    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel( left, top );

    // If not enough, add 30 rows
    if ( ( top + 30 ) > (int)RowCount )
    {
        m_postream->GetGridCore()->SetRowCount( RowCount + 30 );
    }

    // Title
    CString s = _T( "" );

    *m_postream << _T( "\n\n" );
    *m_postream << Style;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << m_BottomOnlyBlackBorderStyle;
    *m_postream << m_DomainName;
    *m_postream << _T( "\t" );

    s.LoadString( IDS_CONCEPTOR_PROCESS );
    *m_postream << s;
    *m_postream << m_GrayStyle;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << m_BottomOnlyBlackBorderStyle;
    *m_postream << _T( "\t" );

    *m_postream << Style;
    *m_postream << m_CurrentProcessName;
    *m_postream << Style;
    *m_postream << WrapStyle;
    *m_postream << m_TopOnlyBlackBorderStyle;
    *m_postream << m_BottomOnlyBlackBorderStyle;
    *m_postream << m_RightOnlyBlackBorderStyle;
    *m_postream << _T( "\t\n" );

    CODNodeArray Nodes;

    if ( reinterpret_cast<ZDProcessGraphModelMdlBP*>( ( (ZBSymbol*)m_pPreviousProcess )->GetChildModel() )->GetBPStartSymbols( Nodes, false ) > 0 )
    {
        StartSection( Nodes );
    }

    return true;
}

bool ZUProcessConceptorNavigation::StartSection( CODNodeArray& Nodes )
{
    CGXStyle WrapStyle;
    WrapStyle.SetWrapText( TRUE );

    for ( size_t nNodeIdx = 0; nNodeIdx < (size_t)Nodes.GetSize(); ++nNodeIdx )
    {
        IODNode*            pINode    = Nodes.GetAt( nNodeIdx );
        ZBBPStartSymbol*    pStart    = static_cast<ZBBPStartSymbol*>( pINode );

        if ( !pStart )
        {
            continue;
        }

        // Check the number of row
        int left, top;

        ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
        m_postream->GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
        }

        // Check if for the same unit
        if ( pStart->GetUnitName() != m_UnitName )
        {
            continue;
        }

        // Display the section
        CString s = _T( "" );

        *m_postream << _T( "\n" );
        *m_postream << pStart->GetSymbolReferenceNumberStr();
        *m_postream << m_BlueStyle;
        *m_postream << _T( "\t" );

        s.LoadString( IDS_CONCEPTOR_STARTPOINT );
        *m_postream << s;
        *m_postream << m_GrayStyle;
        *m_postream << _T( "\t" );

        *m_postream << pStart->GetSymbolName();
        *m_postream << _T( "\n" );

        s.LoadString( IDS_CONCEPTOR_DESCRIPTION );
        *m_postream << s;
        *m_postream << m_BlueStyle;
        *m_postream << _T( "\t" );

        *m_postream << pStart->GetSymbolComment();
        *m_postream << WrapStyle;
        *m_postream << _T( "\n" );

        if ( m_IncludeDeliverables )
        {
            // Retreive all leaving down deliverables
            CODEdgeArray Edges;

            if ( pStart->GetEdgesLeaving( Edges ) > 0 )
            {
                ZBDeliverableLinkSymbol* pDeliverable = NULL;

                for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
                {
                    IODEdge* pIEdge    = Edges.GetAt( nEdgeIdx );
                    pDeliverable    = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

                    // Check if null and continue if the case
                    if ( !pDeliverable )
                    {
                        continue;
                    }
                }

                if ( pDeliverable )
                {
                    s.LoadString( IDS_CONCEPTOR_DELIVERABLE );
                    *m_postream << s + _T( " " );
                    *m_postream << pDeliverable->GetSymbolReferenceNumberStr();
                    *m_postream << m_BlueStyle;
                    *m_postream << _T( "\t" );
                    *m_postream << pDeliverable->GetSymbolName();
                    *m_postream << _T( "\n" );
                }
            }
        }

        // Check the number of row
        RowCount = m_postream->GetGridCore()->GetRowCount();
        m_postream->GetCurSel( left, top );

        // If not enough, add 5 rows
        if ( ( top + 5 ) > (int)RowCount )
        {
            m_postream->GetGridCore()->SetRowCount( RowCount + 5 );
        }
    }

    return true;
}
