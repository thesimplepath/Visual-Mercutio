/****************************************************************************
 * ==> PSS_TextZone --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text zone                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TextZone.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_TextZone, CODTextComponent, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_TextZone
//---------------------------------------------------------------------------
PSS_TextZone::PSS_TextZone() :
    CODTextComponent()
{}
//---------------------------------------------------------------------------
PSS_TextZone::~PSS_TextZone()
{}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::InitializeStyle()
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetLineColor(COLORREF value)
{
    return SetValue(OD_PROP_LINE + OD_LINE_COLOR, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetLineTransparent(BOOL value)
{
    return SetValue(OD_PROP_LINE + OD_LINE_TRANSPARENT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetLineWidth(int value)
{
    return SetValue(OD_PROP_LINE + OD_LINE_WIDTH, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetLineStyle(int value)
{
    return SetValue(OD_PROP_LINE + OD_LINE_STYLE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillColor(COLORREF value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_COLOR, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillTransparent(BOOL value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_TRANSPARENT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillStyle(int value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_STYLE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillHatch(int value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_HATCH, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillBackgroundMode(int value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_BKMODE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFillBackgroundColor(COLORREF value)
{
    return SetValue(OD_PROP_FILL + OD_FILL_BKCOLOR, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFont(const CString& value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_FACE_NAME, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFontColor(COLORREF value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_COLOR, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFontSize(int value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_POINT_SIZE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFontHeight(int value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_HEIGHT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetFontWeight(int value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_WEIGHT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetItalic(BOOL value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_ITALIC, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetUnderline(BOOL value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_UNDERLINE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetStrikeout(BOOL value)
{
    return SetValue(OD_PROP_FONT + OD_FONT_STRIKEOUT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetMultiline(BOOL value)
{
    return SetValue(OD_PROP_MULTILINE, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetUseWordbreak(BOOL value)
{
    return SetValue(OD_PROP_WORDBREAK, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetHorizontalAlignement(int value)
{
    return SetValue(OD_PROP_HORZ_ALIGNMENT, value);
}
//---------------------------------------------------------------------------
BOOL PSS_TextZone::SetVerticalAlignement(int value)
{
    return SetValue(OD_PROP_VERT_ALIGNMENT, value);
}
//---------------------------------------------------------------------------
void PSS_TextZone::Serialize(CArchive& ar)
{
    TRACE(_T("PSS_TextZone::Serialize : Start\n"));
    CODTextComponent::Serialize(ar);
    TRACE(_T("PSS_TextZone::Serialize : End\n"));
}
//---------------------------------------------------------------------------
