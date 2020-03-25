/****************************************************************************
 * ==> PSS_GridCheckBox ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid checkbox                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridCheckBox.h"

// resources
#include "zReportRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_GridCheckBox
//---------------------------------------------------------------------------
PSS_GridCheckBox::PSS_GridCheckBox(CGXGridCore* pGrid) :
    CGXCheckBox(pGrid, TRUE, IDB_CHECK_GRID, IDB_CHECK_GRID)
{
    // size of a checkbox
    m_nCheckBoxSize = 16;
}
//---------------------------------------------------------------------------
PSS_GridCheckBox::~PSS_GridCheckBox()
{}
//---------------------------------------------------------------------------
COLORREF PSS_GridCheckBox::GetColorValue(COLORREF rgb, BOOL print)
{
    switch (rgb)
    {
        case RGB(255, 255, 255): return (print ? RGB(255, 255, 255) : ::GetSysColor(COLOR_WINDOW));
        default:                 return  rgb;
    }
}
//---------------------------------------------------------------------------
