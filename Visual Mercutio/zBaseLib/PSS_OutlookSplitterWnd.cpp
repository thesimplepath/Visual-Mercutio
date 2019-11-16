/****************************************************************************
 * ==> PSS_OutlookSplitterWnd ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an Outlook splitter window                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OutlookSplitterWnd.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Cx_Border 1
#define M_Cy_Border 1
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_OutlookSplitterWnd, CSplitterWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_OutlookSplitterWnd, CSplitterWnd)
    //{{AFX_MSG_MAP(PSS_OutlookSplitterWnd)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_OutlookSplitterWnd
//---------------------------------------------------------------------------
PSS_OutlookSplitterWnd::PSS_OutlookSplitterWnd() :
    CSplitterWnd()
{
    m_ClrBtnHLit = ::GetSysColor(COLOR_BTNHILIGHT);
    m_ClrBtnShad = ::GetSysColor(COLOR_BTNSHADOW);
    m_ClrBtnFace = ::GetSysColor(COLOR_BTNFACE);
}
//---------------------------------------------------------------------------
PSS_OutlookSplitterWnd::~PSS_OutlookSplitterWnd()
{}
//---------------------------------------------------------------------------
void PSS_OutlookSplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
    // no device context, just invalidate
    if (!pDC)
    {
        RedrawWindow(rectArg, NULL, RDW_INVALIDATE | RDW_NOCHILDREN);
        return;
    }

    ASSERT_VALID(pDC);

    CRect rect = rectArg;

    switch (nType)
    {
        case splitBorder:
            pDC->Draw3dRect(rect, m_ClrBtnFace, m_ClrBtnFace);
            rect.InflateRect(-M_Cx_Border, -M_Cy_Border);
            pDC->Draw3dRect(rect, m_ClrBtnShad, m_ClrBtnHLit);
            return;

        case splitIntersection:
            break;

        case splitBox:
            break;

        case splitBar:
            break;

        default:
            // unknown splitter type
            ASSERT(FALSE);
    }

    // fill the middle
    pDC->FillSolidRect(rect, m_ClrBtnFace);
}
//---------------------------------------------------------------------------
void PSS_OutlookSplitterWnd::OnPaint()
{
    ASSERT_VALID(this);
    CPaintDC dc(this);

    CRect rectClient;
    GetClientRect(&rectClient);
    rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

    CRect rectInside;
    GetInsideRect(rectInside);

    // draw the splitter boxes
    if (m_bHasVScroll && m_nRows < m_nMaxRows)
        OnDrawSplitter(&dc,
                       splitBox,
                       CRect(rectInside.right,
                             rectClient.top,
                             rectClient.right,
                             rectClient.top + m_cySplitter));

    if (m_bHasHScroll && m_nCols < m_nMaxCols)
        OnDrawSplitter(&dc,
                       splitBox,
                       CRect(rectClient.left,
                             rectInside.bottom,
                             rectClient.left + m_cxSplitter,
                             rectClient.bottom));

    // extend split bars to window border (past margins)
    DrawAllSplitBars(&dc, rectInside.right, rectInside.bottom);

    // draw splitter intersections (inside only)
    GetInsideRect(rectInside);
    dc.IntersectClipRect(rectInside);

    CRect rect;
    rect.top = rectInside.top;

    for (int row = 0; row < m_nRows - 1; ++row)
    {
        rect.top    += m_pRowInfo[row].nCurSize + m_cyBorderShare;
        rect.bottom  = rect.top                 + m_cySplitter;
        rect.left    = rectInside.left;

        for (int col = 0; col < m_nCols - 1; ++col)
        {
            rect.left  += m_pColInfo[col].nCurSize + m_cxBorderShare;
            rect.right  = rect.left + m_cxSplitter;
            OnDrawSplitter(&dc, splitIntersection, rect);

            rect.left = rect.right + m_cxBorderShare;
        }

        rect.top = rect.bottom + m_cxBorderShare;
    }
}
//---------------------------------------------------------------------------
