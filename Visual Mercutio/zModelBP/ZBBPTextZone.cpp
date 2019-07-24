// **********************************************************************************************************
// *                                         Classe ZBBPTextZone                                            *
// **********************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Ajout de la classe ZBBPTextZone.                                            *
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage d'une zone de texte personnalisée.                        *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZBBPTextZone.h"

#include "zModelBPRes.h"

IMPLEMENT_SERIAL(ZBBPTextZone, ZBTextZone, g_DefVersion)

ZBBPTextZone::ZBBPTextZone()
{
}

ZBBPTextZone::~ZBBPTextZone()
{
}

// Cette fonction permet la création de la zone de texte.
void ZBBPTextZone::Create( CPoint ptLog, CClientDC* dc )
{
    CODTextComponent::Create( ptLog, dc );

    // Change le texte par défaut.
    CString s_Default = _T( "" );
    s_Default.LoadString( IDS_TEXTZONE );
    SetText( s_Default );

    SizeToText();

    CRect m_BoxDim    = GetTextBox();

    m_BoxDim.top    -= 25;
    m_BoxDim.left    -= 70;
    m_BoxDim.bottom    += 25;
    m_BoxDim.right    += 70;

    SetTextBox( m_BoxDim );
}

// Cette fonction permet d'initialiser le style de la zone de texte.
BOOL ZBBPTextZone::InitializeStyle()
{
    BOOL Result = FALSE;

    Result = SetLineTransparent( TRUE );

    if ( Result == FALSE )
    {
        return FALSE;
    }

    Result = SetFillColor( TEXTZONE_COLOR );

    if ( Result == FALSE )
    {
        return FALSE;
    }

    Result = SetFont();

    if ( Result == FALSE )
    {
        return FALSE;
    }

    Result = SetMultiline( TRUE );

    if ( Result == FALSE )
    {
        return FALSE;
    }

    return TRUE;
}

void ZBBPTextZone::Serialize( CArchive& ar )
{
    TRACE( _T( "ZBBPTextZone::Serialize : Start\n" ) );

    ZBTextZone::Serialize( ar );

    TRACE( _T( "ZBBPTextZone::Serialize : End\n" ) );
}
