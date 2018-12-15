// ZVBasicScrollView.cpp : implementation file

#include "stdafx.h"
#include "ZVBasicScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVBasicScrollView

IMPLEMENT_DYNCREATE( ZVBasicScrollView, ZVSpanView )

BEGIN_MESSAGE_MAP( ZVBasicScrollView, ZVSpanView )
    //{{AFX_MSG_MAP(ZVBasicScrollView)
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVBasicScrollView::ZVBasicScrollView()
{
}

ZVBasicScrollView::~ZVBasicScrollView()
{
}

// JMR-MODIF - Le 13 juillet 2005 - Nouvelle implémentation de la fonction GetPrinterPageSize.
ZVDocumentPageSetup* ZVBasicScrollView::GetPrinterPageSize()
{
    // Si le format n'est pas encore défini, définit le format.
    m_PageSetup.OnUserDefinePageFormat();
    return &m_PageSetup;
}

// JMR-MODIF - Le 15 juillet 2005 - Ajouté nouvelle fonction SetPrinterPageSize.
void ZVBasicScrollView::SetPrinterPageSize( CSize PaperSize, short StandardSize, short Orientation )
{
    m_PageSetup.SetPaperSize            ( PaperSize );
    m_PageSetup.SetStandardSize            ( StandardSize );
    m_PageSetup.SetOrientation            ( Orientation );

    m_PageSetup.OnUpdatePrinterSettings    ();

    m_PageSetup.IsSupported                ( StandardSize );
}

// JMR-MODIF - Le 13 juillet 2005 - Supprimé ancienne implémentation de la fonction GetPrinterPageSize.
/*BOOL ZVBasicScrollView::GetPrinterPageSize( CSize &PaperSize, short& StandardSize, short& Orientation )
{
    BOOL bRet = FALSE;

    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    // Get the current printer's settings.
    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg))
    {
        // Get pointers to the two setting structures.
        DEVNAMES FAR *lpDevNames    = (DEVNAMES FAR *)::GlobalLock(pPrintDlg->hDevNames);
        DEVMODE FAR *lpDevMode        = (DEVMODE FAR *)::GlobalLock(pPrintDlg->hDevMode);

        // Get the specific driver information.
        CString szDriver( (LPTSTR)lpDevNames + lpDevNames->wDriverOffset );
        CString szDevice( (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset );
        CString szOutput( (LPTSTR)lpDevNames + lpDevNames->wOutputOffset );

        // Create a CDC object according to the current settings.
        CDC pDC;
        pDC.CreateDC(szDriver, szDevice, szOutput, lpDevMode);

        // Query this CDC object for the width and height of the current page.
        PaperSize.cx = pDC.GetDeviceCaps(HORZSIZE);
        PaperSize.cy = pDC.GetDeviceCaps(VERTSIZE);

        // RS-MODIF 14.12.04 set the value to A4 paper (override windows function getdevicecaps)
        //PaperSize.cx = 210;
        //PaperSize.cy = 296;

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
    else
    {
        // JMR-MODIF - Le 12 juillet 2005 - S'il n'y a pas d'imprimante installée, force le format par défaut à A4 portrait.
        PaperSize.cx    = 203;
        PaperSize.cy    = 271;

        StandardSize    = DMPAPER_A4;
        Orientation        = DMORIENT_PORTRAIT;

        bRet = TRUE;
    }

    delete pPrintDlg;

    return bRet;
}*/

// JMR-MODIF - Le 14 juillet 2005 - Supprimé les fonctions de modification des paramètres de l'imprimante,
// car ces fonctions sont maintenant gérées ailleurs dans le programme.
/*void ZVBasicScrollView::SetPrinterOrientation (short Orientation *//*= DMORIENT_PORTRAIT*//*)
{
//    ZAApp:ZAGetApp()->SetPrinterOrientation( GetPageOrientation() == portrait );
}*/

/////////////////////////////////////////////////////////////////////////////
// ZVBasicScrollView message handlers

// JMR-MODIF - Le 14 juillet 2005 - Nouvelle implémentation de la fonction OnInitialUpdate.
void ZVBasicScrollView::OnInitialUpdate()
{
    ZVDocumentPageSetup* m_pPageSetup = GetPrinterPageSize();

    if ( m_pPageSetup->IsFormatDefined() )
    {
        SetScrollSizes( MM_TEXT, m_pPageSetup->GetPaperSize() );
    }

    ZVSpanView::OnInitialUpdate();
}

// JMR-MODIF - Le 14 juillet 2005 - Supprimé ancienne implémentation de la fonction OnInitialUpdate.
/*void ZVBasicScrollView::OnInitialUpdate()
{
    CSize PaperSizeOnPrinter;
    CSize PaperSizeOnScreen;
    short StandardSize;
    short Orientation;

    if ( GetPrinterPageSize ( PaperSizeOnPrinter, PaperSizeOnScreen, StandardSize, Orientation ) )
    {
        SetScrollSizes( MM_TEXT, PaperSizeOnPrinter );
        //Turn on zooming, default is zooming off.
//        SetZoomMode(SEC_ZOOMNORMAL); //SECZoomView
    }

    ZVSpanView::OnInitialUpdate();
}*/

void ZVBasicScrollView::OnDraw( CDC* pDC )
{
    CDocument* pDoc = GetDocument();
}

void ZVBasicScrollView::ViewZoomIn()
{
}

void ZVBasicScrollView::ViewZoomOut()
{
}

void ZVBasicScrollView::OnViewZoomIn()
{
}

void ZVBasicScrollView::OnViewZoomOut()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZVBasicScrollView diagnostics

#ifdef _DEBUG
void ZVBasicScrollView::AssertValid() const
{
    ZVSpanView::AssertValid();
}

void ZVBasicScrollView::Dump( CDumpContext& dc ) const
{
    ZVSpanView::Dump(dc);
}
#endif //_DEBUG
