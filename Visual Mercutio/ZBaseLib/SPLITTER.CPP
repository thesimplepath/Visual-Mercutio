// splitter.cpp : implementation file
//
#include <StdAfx.h>

#include "Splitter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZISplitter

ZISplitter::ZISplitter()
{
}

ZISplitter::~ZISplitter()
{
}


#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZISplitter, ZIOutlookSplitterWnd)
#endif

#ifndef _WIN32    // In 16bit there is a bug, therefore do not accept moving splitter
BEGIN_MESSAGE_MAP(ZISplitter, CSplitterWnd)
#endif

#ifndef _WIN32    // In 16bit there is a bug, therefore do not accept moving splitter
    //{{AFX_MSG_MAP(ZISplitter)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZISplitter message handlers

#ifndef _WIN32    // In 16bit there is a bug, therefore do not accept moving splitter

void ZISplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
//    CWnd::OnLButtonDown(nFlags, point);
}

void ZISplitter::OnMouseMove(UINT nFlags, CPoint point)
{
//    CWnd::OnMouseMove(nFlags, point);
}

#endif
