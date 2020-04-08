/****************************************************************************
 * ==> PSS_BasicView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicView.h"

// std
#include <Memory>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_BasicView, CView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BasicView, CView)
    //{{AFX_MSG_MAP(PSS_BasicView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BasicView
//---------------------------------------------------------------------------
PSS_BasicView::PSS_BasicView() :
    CView()
{}
//---------------------------------------------------------------------------
PSS_BasicView::~PSS_BasicView()
{}
//---------------------------------------------------------------------------
BOOL PSS_BasicView::GetPrinterPageSize(CSize& paperSize, short& standardSize, short& orientation)
{
    BOOL result = FALSE;

    std::unique_ptr<PRINTDLG> pPrintDlg(new PRINTDLG());

    // get the current printer settings
    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg.get()))
    {
        CDC           pDC;
        DEVNAMES FAR* pDevNames = NULL;
        DEVMODE  FAR* pDevMode  = NULL;

        try
        {
            // get access to the device names
            pDevNames = (DEVNAMES FAR*)::GlobalLock(pPrintDlg->hDevNames);

            if (!pDevNames)
                return FALSE;

            // get access to the device mode
            pDevMode = (DEVMODE FAR*)::GlobalLock(pPrintDlg->hDevMode);

            if (!pDevMode)
            {
                ::GlobalUnlock(pPrintDlg->hDevNames);
                return FALSE;
            }

            // get the specific driver information
            const CString driver(LPTSTR(pDevNames) + pDevNames->wDriverOffset);
            const CString device(LPTSTR(pDevNames) + pDevNames->wDeviceOffset);
            const CString output(LPTSTR(pDevNames) + pDevNames->wOutputOffset);

            // create a printer device context according to the current settings
            pDC.CreateDC(driver, device, output, pDevMode);

            if (!pDC)
            {
                paperSize    = g_DefaultPaperSize;
                standardSize = g_DefaultStandardSize;
                orientation  = g_DefaultOrientation;

                return FALSE;
            }

            // query this CDC object for the current page width and height
            paperSize.cx = pDC.GetDeviceCaps(HORZSIZE);
            paperSize.cy = pDC.GetDeviceCaps(VERTSIZE);

            // get the orientation
            orientation = pDevMode->dmOrientation;

            // get the standard size
            standardSize = pDevMode->dmPaperSize;

            // get rid of the CDC object
            pDC.DeleteDC();
        }
        catch (...)
        {
            // unlock the dev name memory, if required
            if (pDevNames)
                ::GlobalUnlock(pPrintDlg->hDevNames);

            // unlock the dev mode memory, if required
            if (pDevMode)
                ::GlobalUnlock(pPrintDlg->hDevMode);

            throw;
        }

        // unlock the pointers to the settings structures
        ::GlobalUnlock(pPrintDlg->hDevNames);
        ::GlobalUnlock(pPrintDlg->hDevMode);

        result = TRUE;
    }
    else
    {
        paperSize    = g_DefaultPaperSize;
        standardSize = g_DefaultStandardSize;
        orientation  = g_DefaultOrientation;
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_BasicView::SetPrinterOrientation(short orientation)
{}
//---------------------------------------------------------------------------
void PSS_BasicView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();

    // todo -cFeature -oJean: add draw code here
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicView::AssertValid() const
    {
        CView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_BasicView::Dump(CDumpContext& dc) const
    {
        CView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
