// **********************************************************************************************************
// *                                          Classe ZBTextZone                                                *
// **********************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Ajout de la classe ZBTextZone.                                            *
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage d'une zone de texte personnalisée.                        *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZBTextZone.h"

// ******************************* Construction / destruction / implémentation ******************************

IMPLEMENT_SERIAL(ZBTextZone, CODTextComponent, g_DefVersion)

ZBTextZone::ZBTextZone()
{
}

ZBTextZone::~ZBTextZone()
{
}

// ****************************************** Propriétés des lignes *****************************************

// Cette fonction permet de définir la couleur de la ligne entourant la zone de texte.
BOOL ZBTextZone::SetLineColor( COLORREF Value /*= RGB( 0, 0, 0)*/ )
{
    return SetValue( OD_PROP_LINE + OD_LINE_COLOR, Value );
}

// Cette fonction permet de définir le mode de transparence de la ligne entourant la zone de texte.
BOOL ZBTextZone::SetLineTransparent( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_LINE + OD_LINE_TRANSPARENT, Value );
}

// Cette fonction permet de définir l'épaisseur de la ligne entourant la zone de texte.
BOOL ZBTextZone::SetLineWidth( int Value /*= 1*/ )
{
    return SetValue( OD_PROP_LINE + OD_LINE_WIDTH, Value );
}

// Cette fonction permet de définir le style de la ligne entourant la zone de texte.
BOOL ZBTextZone::SetLineStyle( int Value /*= PS_SOLID*/ )
{
    return SetValue( OD_PROP_LINE + OD_LINE_STYLE, Value );
}

// **************************************** Propriétés du remplissage ***************************************

// Cette fonction permet de définir la couleur de remplissage de la zone de texte.
BOOL ZBTextZone::SetFillColor( COLORREF Value /*= RGB( 255, 255, 255 )*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_COLOR, Value );
}

// Cette fonction permet de définir le mode de transparence du remplissage de la zone de texte.
BOOL ZBTextZone::SetFillTransparent( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_TRANSPARENT, Value );
}

// Cette fonction permet de définir le style de remplissage de la zone de texte.
BOOL ZBTextZone::SetFillStyle( int Value /*= BS_SOLID*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_STYLE, Value );
}

// Cette fonction permet de définir le style des hachures du remplissage de la zone de texte.
BOOL ZBTextZone::SetFillHatch( int Value /*= HS_BDIAGONAL*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_HATCH, Value );
}

// Cette fonction permet de définir le mode de remplissage d'arrière plan de la zone de texte.
BOOL ZBTextZone::SetFillBackgroundMode( int Value /*= TRANSPARENT*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_BKMODE, Value );
}

// Cette fonction permet de définir la couleur de remplissage d'arrière plan de la zone de texte.
BOOL ZBTextZone::SetFillBackgroundColor( COLORREF Value /*= RGB( 255, 255, 255 )*/ )
{
    return SetValue( OD_PROP_FILL + OD_FILL_BKCOLOR, Value );
}

// ***************************************** Propriétés des polices *****************************************

// Cette fonction permet de changer le type de police de la zone de texte.
BOOL ZBTextZone::SetFont( CString Value /*= _T( "Arial" )*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_FACE_NAME, Value );
}

// Cette fonction permet de changer la couleur de la police de la zone de texte.
BOOL ZBTextZone::SetFontColor( COLORREF Value /*= RGB( 0, 0, 0 )*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_COLOR, Value );
}

// Cette fonction permet de changer la taille de la police de la zone de texte.
BOOL ZBTextZone::SetFontSize( int Value /*= 10*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_POINT_SIZE, Value );
}

// Cette fonction permet de changer la hauteur de la police de la zone de texte.
BOOL ZBTextZone::SetFontHeight( int Value /*= 10*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_HEIGHT, Value );
}

// Cette fonction permet de changer l'espacement de la police de la zone de texte.
BOOL ZBTextZone::SetFontWeight( int Value /*= FW_NORMAL*/)
{
    return SetValue( OD_PROP_FONT + OD_FONT_WEIGHT, Value );
}

// Cette fonction permet d'afficher le texte en italique.
BOOL ZBTextZone::SetItalic( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_ITALIC, Value );
}

// Cette fonction permet d'afficher le texte en souligné.
BOOL ZBTextZone::SetUnderline( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_UNDERLINE, Value );
}

// Cette fonction permet d'afficher le texte en barré.
BOOL ZBTextZone::SetStrikeout( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_FONT + OD_FONT_STRIKEOUT, Value );
}

// ************************************* Propriétés de la zone de texte *************************************

// Cette fonction permets de définir si la zone de texte utilise plusieurs lignes.
BOOL ZBTextZone::SetMultiline( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_MULTILINE, Value );
}

// Cette fonction permets de définir si la zone de texte utilise la coupure de mots automatique.
BOOL ZBTextZone::SetUseWordbreak( BOOL Value /*= FALSE*/ )
{
    return SetValue( OD_PROP_WORDBREAK, Value );
}

// Cette fonction permets de définir l'alignement vertical de la zone de texte.
BOOL ZBTextZone::SetVerticalAlignement( int Value /*= DT_VCENTER*/ )
{
    return SetValue( OD_PROP_VERT_ALIGNMENT, Value );
}

// Cette fonction permets de définir l'alignement horizontal de la zone de texte.
BOOL ZBTextZone::SetHorizontalAlignement( int Value /*= DT_CENTER*/ )
{
    return SetValue( OD_PROP_HORZ_ALIGNMENT, Value );
}

// ********************************************* Sérialisation **********************************************

// Sérialisation des données
void ZBTextZone::Serialize( CArchive& ar )
{
    TRACE( _T( "ZBTextZone::Serialize : Start\n" ) );

    CODTextComponent::Serialize( ar );

    TRACE( _T( "ZBTextZone::Serialize : End\n" ) );
}
