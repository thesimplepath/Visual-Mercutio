/****************************************************************************
 * ==> PSS_AnimateDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an animate dialog                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_AnimateDialog.h"

// processsoft
#include "zBaseLib\draw.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const UINT g_LastID  = IDB_BITMAP17;
const UINT g_FirstID = IDB_BITMAP1;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_AnimateDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_AnimateDialog)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_AnimateDialog
//---------------------------------------------------------------------------
PSS_AnimateDialog::PSS_AnimateDialog(CWnd* pParent) :
    CDialog(),
    m_ID(g_FirstID),
    m_Stop(FALSE)
{
    CPoint pt;

    // calculate the bitmap image rect (used later for invalidation)
    #ifndef _WIN32
        // 16 bit only
        GetSizeOfBitmapFile(MAKEINTRESOURCE(g_FirstID), g_zWinUtilDLL.hModule, &pt);
    #else
        // 32 bit only
        GetSizeOfBitmapFile(MAKEINTRESOURCE(g_FirstID), g_zWinUtil32DLL.hModule, &pt);
    #endif

    m_ImageRect.left   = 10;
    m_ImageRect.top    = 10;
    m_ImageRect.right  = m_ImageRect.left + pt.x;
    m_ImageRect.bottom = m_ImageRect.top + pt.y;
    Create(IDD_ANIMATEDLG, pParent);
    ShowWindow(SW_SHOW);
}
//---------------------------------------------------------------------------
BOOL PSS_AnimateDialog::ShowNext()
{
    if (m_Stop)
    {
        CloseAnimation();
        return FALSE;
    }

    m_ID = (m_ID > g_LastID) ? g_FirstID : m_ID + 1;
    
    CDC* pDC = GetDC();
    ASSERT(pDC);

    #ifndef _WIN32
        // 16 bit only
        DisplayBitmapFile(MAKEINTRESOURCE(m_ID), pDC->m_hDC, g_zWinUtilDLL.hModule, 10, 10);
    #else
        // 32 bit only
        DisplayBitmapFile(MAKEINTRESOURCE(m_ID), pDC->m_hDC, g_zWinUtil32DLL.hModule, 10, 10);
    #endif

    VERIFY(ReleaseDC(pDC));
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_AnimateDialog::CloseAnimation()
{
    DestroyWindow();
}
//---------------------------------------------------------------------------
void PSS_AnimateDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_AnimateDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CRect rect;
    GetClientRect(&rect);

    // put the window in the center of the screen    
    const UINT screenX = ::GetSystemMetrics(SM_CXFULLSCREEN);
    const UINT screenY = ::GetSystemMetrics(SM_CYFULLSCREEN);
    SetWindowPos(NULL, (screenX - rect.right) / 2, (screenY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_AnimateDialog::OnEraseBkgnd(CDC* pDC)
{
    ASSERT_VALID(pDC);

    CBrush  backBrush(defCOLOR_LTGRAY);
    CBrush* pOldBrush = pDC->SelectObject(&backBrush);

    CRect rect;

    // erase the area needed, fill background with APPWORKSPACE
    pDC->GetClipBox(&rect);
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_AnimateDialog::OnCancel()
{
    m_Stop = TRUE;
}
//---------------------------------------------------------------------------
