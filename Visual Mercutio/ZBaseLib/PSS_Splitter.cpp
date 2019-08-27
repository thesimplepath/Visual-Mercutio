/****************************************************************************
 * ==> PSS_Splitter --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a splitter                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Splitter.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_Splitter, PSS_OutlookSplitterWnd)
#else
    // in 16bit there is a bug, therefore do not accept moving splitter
    BEGIN_MESSAGE_MAP(PSS_Splitter, CSplitterWnd)
    //{{AFX_MSG_MAP(ZISplitter)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
#endif
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_Splitter
//---------------------------------------------------------------------------
PSS_Splitter::PSS_Splitter() :
    PSS_OutlookSplitterWnd()
{}
//---------------------------------------------------------------------------
PSS_Splitter::~PSS_Splitter()
{}
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_Splitter::OnLButtonDown(UINT nFlags, CPoint point)
    {
        // in 16bit there is a bug, therefore do not accept moving splitter
        //CWnd::OnLButtonDown(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
#ifndef _WIN32
    void PSS_Splitter::OnMouseMove(UINT nFlags, CPoint point)
    {
        // in 16bit there is a bug, therefore do not accept moving splitter
        //CWnd::OnMouseMove(nFlags, point);
    }
#endif
//---------------------------------------------------------------------------
