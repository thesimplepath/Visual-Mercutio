/****************************************************************************
 * ==> PSS_TextZoneBP ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text zone for banking process                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TextZoneBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_TextZoneBP, PSS_TextZone, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_TextZoneBP
//---------------------------------------------------------------------------
PSS_TextZoneBP::PSS_TextZoneBP() :
    PSS_TextZone()
{}
//---------------------------------------------------------------------------
PSS_TextZoneBP::~PSS_TextZoneBP()
{}
//---------------------------------------------------------------------------
void PSS_TextZoneBP::Create(const CPoint& ptLog, CClientDC* pDC)
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
//---------------------------------------------------------------------------
BOOL PSS_TextZoneBP::InitializeStyle()
{
    if (!SetLineTransparent(TRUE))
        return FALSE;

    if (!SetFillColor(M_TextZoneColor))
        return FALSE;

    if (!SetFont())
        return FALSE;

    if (!SetMultiline(TRUE))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_TextZoneBP::Serialize(CArchive& ar)
{
    TRACE(_T("PSS_TextZoneBP::Serialize - Start\n"));
    PSS_TextZone::Serialize(ar);
    TRACE(_T("PSS_TextZoneBP::Serialize - End\n"));
}
//---------------------------------------------------------------------------
