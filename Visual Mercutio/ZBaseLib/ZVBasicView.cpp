// ZVBasicView.cpp : implementation file
//

#include "stdafx.h"
#include "ZVBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVBasicView

IMPLEMENT_DYNCREATE(ZVBasicView, CView)

ZVBasicView::ZVBasicView()
{
}

ZVBasicView::~ZVBasicView()
{
}


BOOL ZVBasicView::GetPrinterPageSize(CSize &PaperSize, short& StandardSize, short& Orientation)
{
    BOOL bRet = FALSE;

    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    // Get the current printer's settings.

    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg))
    {

  // Get pointers to the two setting structures.

        DEVNAMES FAR *lpDevNames =
        (DEVNAMES FAR *)::GlobalLock(pPrintDlg->hDevNames);

        DEVMODE FAR *lpDevMode =
        (DEVMODE FAR *)::GlobalLock(pPrintDlg->hDevMode);

  // Get the specific driver information.

        CString szDriver((LPTSTR)lpDevNames +
                             lpDevNames->wDriverOffset);
        CString szDevice((LPTSTR)lpDevNames +
                             lpDevNames->wDeviceOffset);
        CString szOutput((LPTSTR)lpDevNames +
                             lpDevNames->wOutputOffset);

        // Create a CDC object according to the current settings.

        CDC pDC;
        pDC.CreateDC(szDriver, szDevice, szOutput, lpDevMode);

        // Query this CDC object for the width and height of the current
        // page.

        PaperSize.cx = pDC.GetDeviceCaps(HORZSIZE);
        PaperSize.cy = pDC.GetDeviceCaps(VERTSIZE);

        // Return the orientation
        Orientation = lpDevMode->dmOrientation;

        // Return the standard size
        StandardSize = lpDevMode->dmPaperSize;

        // Get rid of the CDC object.

        pDC.DeleteDC();

        // Unlock the pointers to the setting structures.

        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);

      bRet = TRUE;
    }
    delete pPrintDlg;

    return bRet;
}


void ZVBasicView::SetPrinterOrientation (short Orientation /*= DMORIENT_PORTRAIT*/)
{
//    ZAApp:ZAGetApp()->SetPrinterOrientation( GetPageOrientation() == portrait );
}


BEGIN_MESSAGE_MAP(ZVBasicView, CView)
    //{{AFX_MSG_MAP(ZVBasicView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVBasicView drawing

void ZVBasicView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// ZVBasicView diagnostics

#ifdef _DEBUG
void ZVBasicView::AssertValid() const
{
    CView::AssertValid();
}

void ZVBasicView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZVBasicView message handlers
