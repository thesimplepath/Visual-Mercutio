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

IMPLEMENT_SERIAL(ZBBPTextZone, PSS_TextZone, g_DefVersion)

ZBBPTextZone::ZBBPTextZone()
{}

ZBBPTextZone::~ZBBPTextZone()
{}

// Cette fonction permet la création de la zone de texte.
void ZBBPTextZone::Create(const CPoint& ptLog, CClientDC* pDC)
{
    CODTextComponent::Create(ptLog, pDC);

    // load the default text
    CString str = _T("");
    str.LoadString(IDS_TEXTZONE);
    SetText(str);

    SizeToText();

    CRect boxDim   = GetTextBox();
    boxDim.top    -= 25;
    boxDim.left   -= 70;
    boxDim.bottom += 25;
    boxDim.right  += 70;
    SetTextBox(boxDim);
}

// Cette fonction permet d'initialiser le style de la zone de texte.
BOOL ZBBPTextZone::InitializeStyle()
{
    BOOL Result = FALSE;

    Result = SetLineTransparent(TRUE);

    if (Result == FALSE)
    {
        return FALSE;
    }

    Result = SetFillColor(M_TextZoneColor);

    if (Result == FALSE)
    {
        return FALSE;
    }

    Result = SetFont();

    if (Result == FALSE)
    {
        return FALSE;
    }

    Result = SetMultiline(TRUE);

    if (Result == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

void ZBBPTextZone::Serialize(CArchive& ar)
{
    TRACE(_T("ZBBPTextZone::Serialize : Start\n"));
    PSS_TextZone::Serialize(ar);
    TRACE(_T("ZBBPTextZone::Serialize : End\n"));
}
