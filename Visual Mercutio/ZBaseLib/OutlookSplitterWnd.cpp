// OutlookSplitterWnd.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookSplitterWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_BORDER   1
#define CY_BORDER   1

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookSplitterWnd - NOTHING FANCY, JUST A QUICK HACK!!!

ZIOutlookSplitterWnd::ZIOutlookSplitterWnd()
{
	m_clrBtnHLit  = ::GetSysColor(COLOR_BTNHILIGHT);
	m_clrBtnShad  = ::GetSysColor(COLOR_BTNSHADOW);
	m_clrBtnFace  = ::GetSysColor(COLOR_BTNFACE);
}

ZIOutlookSplitterWnd::~ZIOutlookSplitterWnd()
{
	// TODO: add destruction code here.
}

IMPLEMENT_DYNAMIC(ZIOutlookSplitterWnd, CSplitterWnd)

BEGIN_MESSAGE_MAP(ZIOutlookSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(ZIOutlookSplitterWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIOutlookSplitterWnd message handlers

void ZIOutlookSplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType,
	const CRect& rectArg)
{
	// if pDC == NULL, then just invalidate
	if (pDC == NULL)
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);

	// otherwise, actually draw
	CRect rect = rectArg;
	switch (nType)
	{
	case splitBorder:
		pDC->Draw3dRect(rect, m_clrBtnFace, m_clrBtnFace);
		rect.InflateRect(-CX_BORDER, -CY_BORDER);
		pDC->Draw3dRect(rect, m_clrBtnShad, m_clrBtnHLit);
		return;

	case splitIntersection:
		break;

	case splitBox:
		break;

	case splitBar:
		break;

	default:
		ASSERT(FALSE);  // unknown splitter type
	}

	// fill the middle
	pDC->FillSolidRect(rect, m_clrBtnFace);
}

void ZIOutlookSplitterWnd::OnPaint() 
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
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectInside.right, rectClient.top,
				rectClient.right, rectClient.top + m_cySplitter));
	}

	if (m_bHasHScroll && m_nCols < m_nMaxCols)
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectClient.left, rectInside.bottom,
				rectClient.left + m_cxSplitter, rectClient.bottom));
	}

	// extend split bars to window border (past margins)
	DrawAllSplitBars(&dc, rectInside.right, rectInside.bottom);

	// draw splitter intersections (inside only)
	GetInsideRect(rectInside);
	dc.IntersectClipRect(rectInside);
	CRect rect;
	rect.top = rectInside.top;
	for (int row = 0; row < m_nRows - 1; row++)
	{
		rect.top += m_pRowInfo[row].nCurSize + m_cyBorderShare;
		rect.bottom = rect.top + m_cySplitter;
		rect.left = rectInside.left;
		for (int col = 0; col < m_nCols - 1; col++)
		{
			rect.left += m_pColInfo[col].nCurSize + m_cxBorderShare;
			rect.right = rect.left + m_cxSplitter;
			OnDrawSplitter(&dc, splitIntersection, rect);
			rect.left = rect.right + m_cxBorderShare;
		}
		rect.top = rect.bottom + m_cxBorderShare;
	}
}

