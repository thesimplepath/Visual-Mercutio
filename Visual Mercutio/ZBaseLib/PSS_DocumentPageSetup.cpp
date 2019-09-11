/****************************************************************************
 * ==> PSS_DocumentPageSetup -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a printer document page setup                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocumentPageSetup.h"

//---------------------------------------------------------------------------
// PSS_DocumentPageSetup
//---------------------------------------------------------------------------
PSS_DocumentPageSetup::PSS_DocumentPageSetup() :
    m_PaperSize(g_DefaultPaperSize),
    m_StandardSize(g_DefaultStandardSize),
    m_Orientation(g_DefaultOrientation),
    m_IsFormatDefined(FALSE),
    m_IsCancelled(FALSE),
    m_CanPrint(FALSE),
    m_IsChecked(FALSE)
{}
//---------------------------------------------------------------------------
PSS_DocumentPageSetup::~PSS_DocumentPageSetup()
{}
//---------------------------------------------------------------------------
CString PSS_DocumentPageSetup::GetBackgroundFileName() const
{
    return m_BkGndName;
}
//---------------------------------------------------------------------------
CSize PSS_DocumentPageSetup::GetDefaultPageSize(const CRect& margins) const 
{
    CSize pageSize;

    if (m_Orientation == DMORIENT_PORTRAIT)
    {
        // 210 * 297 cm
        pageSize.cx = 793  - margins.right - margins.left;
        pageSize.cy = 1122 - margins.top   - margins.bottom;
    }
    else
    {
        // 297 * 210 cm
        pageSize.cx = 1122 - margins.top   - margins.bottom;
        pageSize.cy = 793  - margins.right - margins.left;
    }

    return pageSize;
}
//---------------------------------------------------------------------------
CSize PSS_DocumentPageSetup::GetPaperSize() const
{
    return m_PaperSize;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetup::SetPaperSize(const CSize& paperSize)
{
    m_PaperSize       = paperSize;
    m_IsFormatDefined = TRUE;
}
//---------------------------------------------------------------------------
short PSS_DocumentPageSetup::GetStandardSize()
{
    return m_StandardSize;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetup::SetStandardSize(short standardSize)
{
    m_StandardSize    = standardSize;
    m_IsFormatDefined = TRUE;
}
//---------------------------------------------------------------------------
short PSS_DocumentPageSetup::GetOrientation()
{
    return m_Orientation;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetup::SetOrientation(short orientation)
{
    m_Orientation     = orientation;
    m_IsFormatDefined = TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetup::OnUserDefinePageFormat()
{
    // dialog box was already shown?
    if (m_IsFormatDefined || m_IsCancelled)
        return;

    CSize      paperSize;
    short      standardSize;
    short      orientation;
    const BOOL printerExists = GetPrinterSettings(paperSize, standardSize, orientation);

    if (!printerExists)
    {
        CString msgStr;
        msgStr.LoadString(IDS_NO_PRINTER_BY_DEFAULT);

        AfxMessageBox(msgStr, MB_ICONWARNING);

        m_PageSetupDlg.SetPaperSize(g_DefaultPaperSize);
        m_PageSetupDlg.SetStandardSize(g_DefaultStandardSize);
        m_PageSetupDlg.SetOrientation(g_DefaultOrientation);

        m_CanPrint = FALSE;
    }
    else
    {
        if (standardSize != DMPAPER_A4)
        {
            m_PageSetupDlg.SetPaperSize(paperSize);
            m_PageSetupDlg.SetStandardSize(standardSize);

            m_CanPrint = FALSE;
        }
        else
        {
            m_PageSetupDlg.SetPaperSize(paperSize);
            m_PageSetupDlg.SetStandardSize(standardSize);

            m_CanPrint = TRUE;
        }

        m_PageSetupDlg.SetOrientation(orientation);
    }

    if (m_PageSetupDlg.DoModal() == IDCANCEL)
    {
        m_IsCancelled = TRUE;
        return;
    }

    m_PaperSize    = m_PageSetupDlg.GetPaperSize();
    m_StandardSize = m_PageSetupDlg.GetStandardSize();
    m_Orientation  = m_PageSetupDlg.GetOrientation();
    m_BkGndName    = m_PageSetupDlg.GetBackGroundFilename();

    if (printerExists)
        ChangePrinterSettings(m_StandardSize, m_Orientation);

    m_IsFormatDefined = TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetup::OnUpdatePrinterSettings()
{
    ChangePrinterSettings(m_StandardSize, m_Orientation);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetup::IsSupported(short standardSize)
{
    // todo -cCheck -oJean: what will happen if another standard size than the previous one should be tested?
    if (m_IsChecked)
        return m_CanPrint;

    CSize paperSize;
    short standardSizeFromPrinter;
    short orientation;

    if (!GetPrinterSettings(paperSize, standardSizeFromPrinter, orientation))
    {
        CString msgStr = _T("");
        msgStr.LoadString(IDS_NO_PRINTER_BY_DEFAULT);

        AfxMessageBox(msgStr, MB_ICONWARNING);

        m_CanPrint = FALSE;
    }
    else
    if (standardSize != standardSizeFromPrinter)
        m_CanPrint = FALSE;
    else
        m_CanPrint = TRUE;

    m_IsChecked = TRUE;

    return m_CanPrint;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetup::IsFormatDefined()
{
    return m_IsFormatDefined;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetup::IsCancelled()
{
    return m_IsCancelled;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetup::CanPrint()
{
    return m_CanPrint;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetup::GetPrinterSettings(CSize& paperSize, short& standardSize, short& orientation)
{
    BOOL result = FALSE;

    std::unique_ptr<PRINTDLG> pPrintDlg(new PRINTDLG());

    // search for a default printer
    if (AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg.get()))
    {
        CDC           pDC;
        DEVNAMES FAR* pDevNames = NULL;
        DEVMODE  FAR* pDevMode  = NULL;

        try
        {
            // get the device parameter structs
            pDevNames = (DEVNAMES FAR*)::GlobalLock(pPrintDlg->hDevNames);
            pDevMode  = (DEVMODE  FAR*)::GlobalLock(pPrintDlg->hDevMode);

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
void PSS_DocumentPageSetup::ChangePrinterSettings(short standardSize, short orientation)
{
    #ifdef _WIN32
        PRINTDLG printDialog;
        printDialog.lStructSize = DWORD(sizeof(PRINTDLG));

        // search for a default printer
        if (!AfxGetApp()->GetPrinterDeviceDefaults(&printDialog))
            return;

        DEVMODE  FAR* pDevMode  = NULL;
        LPDEVNAMES    pDevNames = NULL;

        try
        {
            // get the device mode struct
            pDevMode = (DEVMODE FAR*)::GlobalLock(printDialog.hDevMode);

            if (pDevMode)
            {
                // change the printer settings
                pDevMode->dmPaperSize   = standardSize;
                pDevMode->dmOrientation = orientation;

                // get the device name struct
                pDevNames = LPDEVNAMES(GlobalLock(printDialog.hDevNames));

                LPTSTR pDriverName = LPTSTR(pDevNames) + pDevNames->wDriverOffset;
                LPTSTR pDeviceName = LPTSTR(pDevNames) + pDevNames->wDeviceOffset;
                LPTSTR pPortName   = LPTSTR(pDevNames) + pDevNames->wOutputOffset;
                HANDLE hPrinter;

                // open the printer
                ::OpenPrinter(pDeviceName, &hPrinter, NULL);

                // set the document properties
                ::DocumentProperties(NULL,
                                        hPrinter,
                                        pDeviceName,
                                        pDevMode,
                                        pDevMode,
                                        DM_IN_BUFFER | DM_OUT_BUFFER);

                // synchronize the device mode struct, see the MSDN help under Document Properties for further info
                ::ClosePrinter(hPrinter);
            }
        }
        catch (...)
        {
            if (pDevNames)
                ::GlobalUnlock(printDialog.hDevNames);

            if (pDevMode)
                ::GlobalUnlock(printDialog.hDevMode);

            throw;
        }

        if (pDevNames)
            ::GlobalUnlock(printDialog.hDevNames);

        if (pDevMode)
            ::GlobalUnlock(printDialog.hDevMode);
    #endif
}
//---------------------------------------------------------------------------
