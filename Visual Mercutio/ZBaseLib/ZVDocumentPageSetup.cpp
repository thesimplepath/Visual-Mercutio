// **********************************************************************************************************
// *                                          Classe ZVDocumentPageSetup                                    *
// **********************************************************************************************************
// * Cette classe permet la gestion du format de page du document. Elle permet de paramétrer une page,        *
// * et elle prend également en charge le contrôle de la validité de cette page par rapport au device        *
// * d'impression.                                                                                            *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZVDocumentPageSetup.h"

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// **********************************************************************************************************
// *                                        Constructeur(s) et destructeur                                    *
// **********************************************************************************************************

// Constructeur par défaut de la classe ZVDocumentPageSetup.
ZVDocumentPageSetup::ZVDocumentPageSetup()
{
    sBkGndName            = _T( "" );

    m_StandardSize        = DefaultStandardSize;
    m_Orientation        = DefaultOrientation;
    m_PaperSize            = DefaultPaperSize;

    bIsFormatDefined    = FALSE;
    bIsCancelled        = FALSE;
    bCanPrint            = FALSE;
    bIsChecked            = FALSE;
}

// Destructeur de la classe ZVDocumentPageSetup.
ZVDocumentPageSetup::~ZVDocumentPageSetup()
{
}

// **********************************************************************************************************
// *                               Fonctions privées de la classe ZVDocumentPageSetup                        *
// **********************************************************************************************************

/* Cette fonction permet de récupérer les données de pages, nécessaires au document, depuis le driver d'impression.
   Retourne TRUE si un driver existe, sinon retourne FALSE.*/
BOOL ZVDocumentPageSetup::GetPrinterSettings( CSize& PaperSize, short& StandardSize, short& Orientation )
{
    BOOL bRet = FALSE;

    PRINTDLG FAR * pPrintDlg = new PRINTDLG;

    if ( pPrintDlg == NULL )
    {
        return FALSE;
    }

    // Recherche une imprimante par défaut.
    if ( AfxGetApp()->GetPrinterDeviceDefaults( pPrintDlg ) )
    {
        // Obtient les pointeurs vers les deux structures de paramètres.
        DEVNAMES FAR *lpDevNames    = (DEVNAMES FAR *)::GlobalLock( pPrintDlg->hDevNames );
        DEVMODE FAR  *lpDevMode        = (DEVMODE FAR  *)::GlobalLock( pPrintDlg->hDevMode );

        // Obtient les informations spécifiques au Driver.
        CString szDriver( (LPTSTR)lpDevNames + lpDevNames->wDriverOffset );
        CString szDevice( (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset );
        CString szOutput( (LPTSTR)lpDevNames + lpDevNames->wOutputOffset );

        // Crée un objet CDC basé sur les paramètres courants.
        CDC pDC;
        pDC.CreateDC( szDriver, szDevice, szOutput, lpDevMode );

        // JMR-MODIF - Le 24 avril 2006 - Teste la validité de la variable pDC avant de l'utiliser.
        if ( pDC == NULL )
        {
            PaperSize        = DefaultPaperSize;
            StandardSize    = DefaultStandardSize;
            Orientation        = DefaultOrientation;

            delete pPrintDlg;

            return FALSE;
        }

        // Obtient l'orientation du papier.
        Orientation        = lpDevMode->dmOrientation;

        // Obtient la taille standard.
        StandardSize    = lpDevMode->dmPaperSize;

        // Utilise l'objet CDC pour retrouver la hauteur et la largeur de la page courante.
        PaperSize.cx    = pDC.GetDeviceCaps( HORZSIZE );
        PaperSize.cy    = pDC.GetDeviceCaps( VERTSIZE );

        // Désalloue le pointeur du CDC.
        pDC.DeleteDC();

        // Déverouille les pointeurs vers les structures de paramètres.
        ::GlobalUnlock( pPrintDlg->hDevNames );
        ::GlobalUnlock( pPrintDlg->hDevMode );

        bRet = TRUE;
    }
    else
    {
        PaperSize        = DefaultPaperSize;
        StandardSize    = DefaultStandardSize;
        Orientation        = DefaultOrientation;
    }

    delete pPrintDlg;

    return bRet;
}

// Cette fonction modifie les paramètres par défaut du driver d'impression.
void ZVDocumentPageSetup::ChangePrinterSettings( short StandardSize, short Orientation )
{
#ifdef _WIN32

    PRINTDLG pd;

    pd.lStructSize = (DWORD) sizeof( PRINTDLG );

    // Recherche une imprimante par défaut.
    if ( AfxGetApp()->GetPrinterDeviceDefaults( &pd ) )
    {
        // Verouille les accès mémoires.
        DEVMODE FAR*    pDevMode = (DEVMODE FAR*)::GlobalLock( pd.hDevMode );
        LPDEVNAMES        lpDevNames;
        LPTSTR            lpszDriverName, lpszDeviceName, lpszPortName;
        HANDLE            hPrinter;

        if ( pDevMode )
        {
            // Change les propriétés de l'imprimante.
            pDevMode->dmPaperSize    = StandardSize;
            pDevMode->dmOrientation    = Orientation;

            // Libère les accès mémoire.
            lpDevNames = (LPDEVNAMES)GlobalLock( pd.hDevNames );
            lpszDriverName = (LPTSTR)lpDevNames + lpDevNames->wDriverOffset;
            lpszDeviceName = (LPTSTR)lpDevNames + lpDevNames->wDeviceOffset;
            lpszPortName   = (LPTSTR)lpDevNames + lpDevNames->wOutputOffset;

            OpenPrinter( lpszDeviceName, &hPrinter, NULL );

            DocumentProperties( NULL,
                                hPrinter,
                                lpszDeviceName,
                                pDevMode,
                                pDevMode,
                                DM_IN_BUFFER | DM_OUT_BUFFER );

            // Synchronise l'objet pDevMode.
            // Voir le SDK help sous DocumentProperties pour plus d'informations.
            ClosePrinter( hPrinter );

            GlobalUnlock( pd.hDevNames );
            GlobalUnlock( pd.hDevMode );
        }
    }

#endif // _WIN32
}

// **********************************************************************************************************
// *                              Fonctions publiques de la classe ZVDocumentPageSetup                        *
// **********************************************************************************************************

// Cette fonction permet d'obtenir la dimension de la page du document, si aucun driver n'est installé.
CSize ZVDocumentPageSetup::GetDefaultPageDim( CRect Margins )
{
    CSize PageDim;

    if ( m_Orientation == DMORIENT_PORTRAIT )
    {
        PageDim.cx = 793  - Margins.right - Margins.left;        /*210 cm*/
        PageDim.cy = 1122 - Margins.top - Margins.bottom;        /*297 cm*/
    }
    else
    {
        PageDim.cx = 1122 - Margins.top - Margins.bottom;        /*297 cm*/
        PageDim.cy = 793  - Margins.right - Margins.left;        /*210 cm*/
    }

    return PageDim;
}

/*    Cette fonction permet à l'utilisateur de définir un format de page. La fonction retourne TRUE si
    l'utilisateur accepte le format, ou FALSE si l'utilisateur clique sur Abandonner.*/
void ZVDocumentPageSetup::OnUserDefinePageFormat()
{
    // Ces deux conditions évitent une répétition de l'apparition de la boîte de dialogue.
    if ( bIsFormatDefined == TRUE || bIsCancelled == TRUE ) return;

    CSize    PaperSize;
    short    StandardSize;
    short    Orientation;

    BOOL    bIsPrinterExists = GetPrinterSettings( PaperSize, StandardSize, Orientation );

    if ( !bIsPrinterExists )
    {
        CString m_MsgStr = _T( "" );
        m_MsgStr.LoadString( IDS_NO_PRINTER_BY_DEFAULT );

        AfxMessageBox( m_MsgStr, MB_ICONWARNING );

        m_PageSetupDlg.SetPaperSize            ( DefaultPaperSize );
        m_PageSetupDlg.SetStandardSize        ( DefaultStandardSize );
        m_PageSetupDlg.SetOrientation        ( DefaultOrientation );

        bCanPrint = FALSE;
    }
    else
    {
        if ( StandardSize != DMPAPER_A4 )
        {
            m_PageSetupDlg.SetPaperSize        ( PaperSize );
            m_PageSetupDlg.SetStandardSize    ( StandardSize );

            // JMR-MODIF - Le 23 février 2006 - Le test d'impression ne doit plus afficher ce message.
/*            AfxMessageBox( _T( "Votre imprimante n'est pas configurée au même format que le document. Tant que la configuration par défaut de votre imprimante ne correspondra pas au format du document, vous ne pourrez pas imprimer." ),
                           MB_ICONWARNING );
*/

            bCanPrint = FALSE;
        }
        else
        {
            m_PageSetupDlg.SetPaperSize        ( PaperSize );
            m_PageSetupDlg.SetStandardSize    ( StandardSize );

            bCanPrint = TRUE;
        }

        m_PageSetupDlg.SetOrientation        ( Orientation );
    }

    if ( m_PageSetupDlg.DoModal() == IDCANCEL )
    {
        bIsCancelled    = TRUE;
        return;
    }

    m_PaperSize            = m_PageSetupDlg.GetPaperSize();
    m_StandardSize        = m_PageSetupDlg.GetStandardSize();
    m_Orientation        = m_PageSetupDlg.GetOrientation();

    sBkGndName            = m_PageSetupDlg.GetBackGroundFilename();

    if ( bIsPrinterExists )
    {
        ChangePrinterSettings( m_StandardSize, m_Orientation );
    }

    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de mettre à jour le driver d'impression en fonction des dernières modifications entrées.
void ZVDocumentPageSetup::OnUpdatePrinterSettings()
{
    ChangePrinterSettings( m_StandardSize, m_Orientation );
}

// Cette fonction permet de définir la dimension du papier.
void ZVDocumentPageSetup::SetPaperSize( CSize PaperSize )
{
    m_PaperSize            = PaperSize;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de définir la taille standard du papier.
void ZVDocumentPageSetup::SetStandardSize( short StandardSize )
{
    m_StandardSize        = StandardSize;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet de définir l'orientation du papier.
void ZVDocumentPageSetup::SetOrientation( short Orientation )
{
    m_Orientation        = Orientation;
    bIsFormatDefined    = TRUE;
}

// Cette fonction permet d'obtenir la dimension courante du papier.
CSize ZVDocumentPageSetup::GetPaperSize()
{
    return m_PaperSize;
}

// Cette fonction permet d'obtenir la taille standard du papier.
short ZVDocumentPageSetup::GetStandardSize()
{
    return m_StandardSize;
}

// Cette fonction permet d'obtenir l'orientation du papier.
short ZVDocumentPageSetup::GetOrientation()
{
    return m_Orientation;
}

// Cette fonction permet de savoir si le format de page a déjà été défini.
BOOL ZVDocumentPageSetup::IsFormatDefined()
{
    return bIsFormatDefined;
}

// Cette fonction permet de savoir si l'utilisateur à quitté la boîte de dialogue sans valider.
BOOL ZVDocumentPageSetup::IsCancelled()
{
    return bIsCancelled;
}

// Cette fonction permet de savoir si le format entré en paramètre est supporté par le driver d'impression.
BOOL ZVDocumentPageSetup::IsSupported( short StandardSize )
{
    if ( bIsChecked == TRUE )
    {
        return bCanPrint;
    }

    CSize    PaperSize;
    short    StandardSizeFromPrinter;
    short    Orientation;

    BOOL    bIsPrinterExists = GetPrinterSettings( PaperSize, StandardSizeFromPrinter, Orientation );

    if ( bIsPrinterExists != TRUE )
    {
        CString m_MsgStr = _T( "" );
        m_MsgStr.LoadString( IDS_NO_PRINTER_BY_DEFAULT );

        AfxMessageBox( m_MsgStr, MB_ICONWARNING );

        bCanPrint = FALSE;
    }
    else if ( StandardSize != StandardSizeFromPrinter )
    {
        // JMR-MODIF - Le 23 février 2006 - Le test d'impression ne doit plus afficher ce message.
/*        AfxMessageBox( _T( "Votre imprimante n'est pas configurée au même format que le document. Tant que la configuration par défaut de votre imprimante ne correspondra pas au format du document, vous ne pourrez pas imprimer." ),
                       MB_ICONWARNING );
*/

        bCanPrint = FALSE;
    }
    else
    {
        bCanPrint = TRUE;
    }

    bIsChecked = TRUE;

    return bCanPrint;
}

// Cette fonction permet de savoir si le document peut être imprimé.
BOOL ZVDocumentPageSetup::CanPrint()
{
    return bCanPrint;
}

// Cette fonction permet d'obtenir le nom du fichier pour la trame de fond, s'il a été défini par l'utilisateur.
CString ZVDocumentPageSetup::GetBackGroundFilename()
{
    return sBkGndName;
}
