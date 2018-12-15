// ZCGridGroup.cpp: implementation of the ZCGridGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZCGridGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZCGridGroup, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZCGridGroup::ZCGridGroup( CGXGridCore* pGrid /*= NULL*/ )
    : m_pGrid            ( pGrid ),
      m_CoveringCells    ( 0 ),
      m_Row                ( 0 ),
      m_Col                ( 0 ),
      m_Horizontal        ( true ),
      m_Collapsed        ( false )
{
}

ZCGridGroup::ZCGridGroup( CGXGridCore*    pGrid,
                          ROWCOL        Row,
                          ROWCOL        Col,
                          int            CoveringCells,
                          bool            Horizontal,
                          bool            Collapsed,
                          const CString    Label            /*= ""*/,
                          const CString    ToolTipText        /*= ""*/ )
    : m_pGrid            ( pGrid ),
      m_CoveringCells    ( CoveringCells ),
      m_Row                ( Row ),
      m_Col                ( Col ),
      m_Horizontal        ( Horizontal ),
      m_Label            ( Label ),
      m_ToolTipText        ( ToolTipText ),
      m_Collapsed        ( Collapsed )
{
    CreateControl();
}

ZCGridGroup::~ZCGridGroup()
{
}

void ZCGridGroup::SetCollapsed( bool value )
{
    if ( !m_pGrid )
    {
        return;
    }

    // If no change, return
    if ( m_Collapsed == value )
    {
        return;
    }

    m_Collapsed = value;
    ApplyState();
}

void ZCGridGroup::ApplyState()
{
    // If must collpase, then hide cells
    if ( m_Collapsed )
    {
        if ( m_Horizontal )
        {
            m_pGrid->HideCols( m_Col + 1, m_Col + m_CoveringCells, TRUE );
        }
        else
        {
            m_pGrid->HideRows( m_Row + 1, m_Row + m_CoveringCells, TRUE );
        }
    }
    else
    {
        // Otherwise, unhide cells
        if ( m_Horizontal )
        {
            m_pGrid->HideCols( m_Col+1, m_Col+m_CoveringCells, FALSE );
        }
        else
        {
            m_pGrid->HideRows( m_Row+1, m_Row+m_CoveringCells, FALSE );
        }
    }
}

void ZCGridGroup::CreateControl()
{
    if ( !m_pGrid )
    {
        return;
    }

    if ( m_Row > m_pGrid->GetRowCount() )
    {
        m_pGrid->SetRowCount( m_Row + 5 );
    }

    if ( m_Col > m_pGrid->GetColCount() )
    {
        m_pGrid->SetColCount( m_Col + 5 );
    }

    m_pGrid->SetStyleRange( CGXRange( m_Row, m_Col ),
                            CGXStyle()
                           .SetControl( GX_IDS_CTRL_CHECKBOX )
                           .SetValue( ( m_Collapsed == true ) ? 0L : 1L )
                           .SetChoiceList( m_Label )
                           .SetUserAttribute( GX_IDS_UA_TOOLTIPTEXT, m_ToolTipText )
                           .SetVerticalAlignment( DT_VCENTER ) );

    // If the initial state is collapsed, apply the state
    if ( m_Collapsed )
    {
        ApplyState();
    }
}

void ZCGridGroup::CreateControl( ROWCOL            Row,
                                 ROWCOL            Col,
                                 int            CoveringCells,
                                 bool            Horizontal,
                                 bool            Collapsed,
                                 const CString    Label            /*= ""*/,
                                 const CString    ToolTipText        /*= ""*/ )
{
    m_CoveringCells    = CoveringCells;
    m_Row            = Row;
    m_Col            = Col;
    m_Horizontal    = Horizontal;
    m_Collapsed        = Collapsed;
    m_Label            = Label;
    m_ToolTipText    = ToolTipText;

    ZCGridGroup::CreateControl();
}

/////////////////////////////////////////////////////////////////////////////
// ZCGridGroup diagnostics

#ifdef _DEBUG
void ZCGridGroup::AssertValid() const
{
    CObject::AssertValid();
}

void ZCGridGroup::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZCGridGroup serialisation

void ZCGridGroup::Serialize ( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_CoveringCells;
        ar << m_Row;
        ar << m_Col;

        ar << (WORD)m_Horizontal;
        ar << (WORD)m_Collapsed;

        ar << m_Label;
        ar << m_ToolTipText;
    }
    else
    {
        ar >> m_CoveringCells;
        ar >> m_Row;
        ar >> m_Col;

        WORD wValue;
        ar >> wValue;
        m_Horizontal = ( wValue == 1 ) ? true : false;

        ar >> wValue;
        m_Collapsed = ( wValue == 1 ) ? true : false;

        ar >> m_Label;
        ar >> m_ToolTipText;
    }
}
