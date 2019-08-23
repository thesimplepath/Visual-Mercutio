/****************************************************************************
 * ==> PSS_PaintResources --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a paint resources helper class                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PaintResources.h"

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
CFont  PSS_PaintResources::m_SystemFont;
CFont  PSS_PaintResources::m_SmallSystemFont;
CPen   PSS_PaintResources::m_BlackPen;
CPen   PSS_PaintResources::m_WhitePen;
CPen   PSS_PaintResources::m_BluePen;
CPen   PSS_PaintResources::m_GrayPen;
CPen   PSS_PaintResources::m_YellowPen;
CPen   PSS_PaintResources::m_GreenPen;
CPen   PSS_PaintResources::m_RedPen;
CBrush PSS_PaintResources::m_WhiteBrush;
CBrush PSS_PaintResources::m_LtBlueBrush;
CBrush PSS_PaintResources::m_RedBrush;
CBrush PSS_PaintResources::m_BlackBrush;
CBrush PSS_PaintResources::m_GrayBrush;
CBrush PSS_PaintResources::m_BlueBrush;
//---------------------------------------------------------------------------
// PSS_PaintResources
//---------------------------------------------------------------------------
PSS_PaintResources::PSS_PaintResources()
{}
//---------------------------------------------------------------------------
PSS_PaintResources::PSS_PaintResources(const PSS_PaintResources& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_PaintResources::~PSS_PaintResources()
{}
//---------------------------------------------------------------------------
const PSS_PaintResources& PSS_PaintResources::operator = (const PSS_PaintResources& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_PaintResources::Initialize()
{
    // fonts creation
    m_SystemFont.CreateFont     (14, 10, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, "Arial");
    m_SmallSystemFont.CreateFont(10, 6,  0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, "Arial");

    // pens creation
    m_BlackPen.CreatePen (PS_SOLID, 1, defCOLOR_BLACK);
    m_WhitePen.CreatePen (PS_SOLID, 1, defCOLOR_WHITE);
    m_BluePen.CreatePen  (PS_SOLID, 1, defCOLOR_BLUE);
    m_GrayPen.CreatePen  (PS_SOLID, 1, defCOLOR_GRAY);
    m_RedPen.CreatePen   (PS_SOLID, 1, defCOLOR_RED);
    m_YellowPen.CreatePen(PS_SOLID, 1, defCOLOR_YELLOW);
    m_GreenPen.CreatePen (PS_SOLID, 1, defCOLOR_GREEN);

    // brushes creation
    m_WhiteBrush.CreateSolidBrush (defCOLOR_WHITE);
    m_LtBlueBrush.CreateSolidBrush(defCOLOR_LTBLUE);
    m_RedBrush.CreateSolidBrush   (defCOLOR_RED);
    m_BlackBrush.CreateSolidBrush (defCOLOR_BLACK);
    m_GrayBrush.CreateSolidBrush  (defCOLOR_GRAY);
    m_BlueBrush.CreateSolidBrush  (defCOLOR_BLUE);
}
//---------------------------------------------------------------------------
