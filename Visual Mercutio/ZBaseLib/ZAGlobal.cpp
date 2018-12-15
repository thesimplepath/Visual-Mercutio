//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ

//    Source file: z:\adsoft~1\ZBaseLib\ZAGlobal.cpp

#include <StdAfx.h>

// ZAGlobal
#include "ZAGlobal.h"

#include "ZDHistoricValueDocument.h"

#include "DocTmplEx.h"
#include "ProcessModelDocTmpl.h"

#include "ZBTokenizer.h"

#include "FileDlg.h"

#include "zBaseLibRes.h"

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

UINT LongDayOfWeek[] =
{
    LOCALE_SDAYNAME7,    // Sunday
    LOCALE_SDAYNAME1,
    LOCALE_SDAYNAME2,
    LOCALE_SDAYNAME3,
    LOCALE_SDAYNAME4,
    LOCALE_SDAYNAME5,
    LOCALE_SDAYNAME6    // Saturday
};

UINT ShortDayOfWeek[] =
{
    LOCALE_SABBREVDAYNAME7,    // Sunday
    LOCALE_SABBREVDAYNAME1,
    LOCALE_SABBREVDAYNAME2,
    LOCALE_SABBREVDAYNAME3,
    LOCALE_SABBREVDAYNAME4,
    LOCALE_SABBREVDAYNAME5,
    LOCALE_SABBREVDAYNAME6    // Saturday
};

UINT LongMonths[] =
{
    LOCALE_SMONTHNAME1,        // Long name for January
    LOCALE_SMONTHNAME2,        // Long name for February
    LOCALE_SMONTHNAME3,        // Long name for March
    LOCALE_SMONTHNAME4,        // Long name for April
    LOCALE_SMONTHNAME5,        // Long name for May
    LOCALE_SMONTHNAME6,        // Long name for June
    LOCALE_SMONTHNAME7,        // Long name for July
    LOCALE_SMONTHNAME8,        // Long name for August
    LOCALE_SMONTHNAME9,        // Long name for September
    LOCALE_SMONTHNAME10,    // Long name for October
    LOCALE_SMONTHNAME11,    // Long name for November
    LOCALE_SMONTHNAME12,    // Long name for December
    LOCALE_SMONTHNAME13        // Long name for 13th month (if exists)
};

UINT ShortMonths[] =
{
    LOCALE_SABBREVMONTHNAME1,    // Abreviated name for January
    LOCALE_SABBREVMONTHNAME2,    // Abreviated name for February
    LOCALE_SABBREVMONTHNAME3,    // Abreviated name for March
    LOCALE_SABBREVMONTHNAME4,    // Abreviated name for April
    LOCALE_SABBREVMONTHNAME5,    // Abreviated name for May
    LOCALE_SABBREVMONTHNAME6,    // Abreviated name for June
    LOCALE_SABBREVMONTHNAME7,    // Abreviated name for July
    LOCALE_SABBREVMONTHNAME8,    // Abreviated name for August
    LOCALE_SABBREVMONTHNAME9,    // Abreviated name for September
    LOCALE_SABBREVMONTHNAME10,    // Abreviated name for October
    LOCALE_SABBREVMONTHNAME11,    // Abreviated name for November
    LOCALE_SABBREVMONTHNAME12,    // Abreviated name for December
    LOCALE_SABBREVMONTHNAME13    // Abreviated name for 13th month (if exists)
};

eApplicationType        ZAGlobal::m_AppType                                = zUndef;
BOOL                    ZAGlobal::m_OpenFileInSilentMode                = FALSE;
BOOL                    ZAGlobal::m_IsFormDesigner                        = FALSE;
BOOL                    ZAGlobal::m_ShowAnimation                        = FALSE;
CString                    ZAGlobal::m_ApplicationDirectory                = _T( "" );
CString                    ZAGlobal::m_FileDirectory                        = _T( "" );
CString                    ZAGlobal::m_EventDirectory                        = _T( "" );

BOOL                    ZAGlobal::m_DuringInitialization                = FALSE;
BOOL                    ZAGlobal::m_MaximizeFormOnOpen                    = FALSE;

ZBServer*                ZAGlobal::m_pServer                                = NULL;

ZBHistoricValueManager    ZAGlobal::m_HistoricValueManager;

ZDDocument*                ZAGlobal::m_pCurrentDocumentForSerialization    = NULL;
ZUser*                    ZAGlobal::m_ConnectedUser                        = NULL;
ZDDocTemplateEx*        ZAGlobal::m_pDocTemplate                        = NULL;
ZDDocTemplateEx*        ZAGlobal::m_pProcessDocTemplate                    = NULL;
ZDProcessModelDocTmpl*    ZAGlobal::m_pProcessModelDocumentTemplate        = NULL;
CMultiDocTemplate*        ZAGlobal::m_pReportDocTemplate                    = NULL;

ZDTemplateManager        ZAGlobal::m_TemplateManager;
ZDTemplateManager        ZAGlobal::m_ProcessTemplateManager;
ZDTemplateManager        ZAGlobal::m_ModelTemplateManager;
ZUUserManager            ZAGlobal::m_UserManager;
ZUNetwork                ZAGlobal::m_NetWork;
ZUMail                    ZAGlobal::m_Mail;

CString                    ZAGlobal::m_ResponsibleUserNameKeyString;
CString                    ZAGlobal::m_RequestedUserNameKeyString;

// Contains the yes no strings
CStringArray            ZAGlobal::m_ArrayYesNo;

// Contains the window mode strings
CStringArray            ZAGlobal::m_WindowMode;

// Contains the priority job strings
CStringArray            ZAGlobal::m_PriorityJob;

// Contains the insertion type strings
CStringArray            ZAGlobal::m_InsertionTypeArray;

// Contains the activation type strings
CStringArray            ZAGlobal::m_ActivationTypeArray;

// Months and Days CStringArray sets for multi-lang
ZBFullMonthSet            ZAGlobal::m_FullMonthSet;
ZBShortMonthSet            ZAGlobal::m_ShortMonthSet;
ZBDaySet                ZAGlobal::m_DaySet;

// StringArray for Month, Week and Day string prefixes
CStringArray            ZAGlobal::m_MonthPrefixArray;
CStringArray            ZAGlobal::m_MonthShortPrefixArray;
CStringArray            ZAGlobal::m_WeekPrefixArray;
CStringArray            ZAGlobal::m_WeekShortPrefixArray;
CStringArray            ZAGlobal::m_DayPrefixArray;
CStringArray            ZAGlobal::m_DayShortPrefixArray;
CStringArray            ZAGlobal::m_HourPrefixArray;
CStringArray            ZAGlobal::m_HourShortPrefixArray;

CWnd*                    ZAGlobal::m_pModalDialogCWnd                    = NULL;

// Class ZAGlobal

ZAGlobal::ZAGlobal()
{
    TRACE( _T( "Don't forget to ZAGlobal::Initialize() !!!!!!!!!!" ) );
    TRACE( _T( "Don't forget to call ZAGlobal::InitializeNetwork()!!!!!!!!!!" ) );
}

ZAGlobal::~ZAGlobal()
{
    // JMR-MODIF - Le 25 août 2005 - Destructeur jamais appelé, supprimé et remplaçé par fonction Release.
}

void ZAGlobal::Initialize( ZBServer*        pServer,
                           eApplicationType    AppType,
                           BOOL                IsFormDesigner,
                           BOOL                ShowAnimation,
                           BOOL                MaximizeFormOnOpen,
                           const CString    FileDirectory,
                           const CString    EventDirectory )
{
    m_pServer                = pServer;
    m_AppType                = AppType;
    m_IsFormDesigner        = IsFormDesigner;
    m_ShowAnimation            = ShowAnimation;
    m_MaximizeFormOnOpen    = MaximizeFormOnOpen;
    m_FileDirectory            = FileDirectory;
    m_EventDirectory        = EventDirectory;

    m_ResponsibleUserNameKeyString.LoadString( ResponsibleUserNameIDResource );
    m_RequestedUserNameKeyString.LoadString( RequestedUserNameIDResource );

    // Loads the yes no array
    m_ArrayYesNo.RemoveAll();
    CString s;
    s.LoadString( IDS_NO );
    m_ArrayYesNo.Add( s );
    s.LoadString( IDS_YES );
    m_ArrayYesNo.Add( s );

    // Loads the window mode strings
    s.LoadString( IDS_WINDOW_MODE );
    FillArray( s, m_WindowMode );

    // Loads the priority job strings
    s.LoadString( IDS_PRIORITY_JOB );
    FillArray( s, m_PriorityJob );

    // Loads the insertion type strings
    s.LoadString( IDS_INSERTIONTYPE_ARRAY );
    FillArray( s, m_InsertionTypeArray );

    // Loads the activation type strings
    s.LoadString( IDS_ACTIVATIONTYPE_ARRAY );
    FillArray( s, m_ActivationTypeArray );

    LoadDateArray();
    LoadPrefixArrays();

    TRACE( _T( "ZAGlobal::Initialize() initialized" ) );
}

// JMR-MODIF - Le 25 août 2005 - Ajout de la fonction Release pour permettre le nettoyage des données statiques.
void ZAGlobal::Release()
{
    // Delete all allocated multi-lang CStringArray
    size_t i;

    size_t Count = m_FullMonthSet.GetSize();

    for ( i = 0; i < Count; ++i )
    {
        if ( m_FullMonthSet.GetAt( i ) )
        {
            delete m_FullMonthSet.GetAt( i );
        }
    }

    Count = m_ShortMonthSet.GetSize();

    for ( i = 0; i < Count; ++i )
    {
        if ( m_ShortMonthSet.GetAt( i ) )
        {
            delete m_ShortMonthSet.GetAt( i );
        }
    }

    Count = m_DaySet.GetSize();

    for ( i = 0; i < Count; ++i )
    {
        if ( m_DaySet.GetAt( i ) )
        {
            delete m_DaySet.GetAt( i );
        }
    }

    // Vide toutes les chaînes de caractères.
    m_FileDirectory.Empty();
    m_EventDirectory.Empty();
    m_ApplicationDirectory.Empty();
    m_ResponsibleUserNameKeyString.Empty();
    m_RequestedUserNameKeyString.Empty();

    // Vide tous les tableaux de caractères.
    m_ArrayYesNo.RemoveAll();
    m_WindowMode.RemoveAll();
    m_PriorityJob.RemoveAll();
    m_InsertionTypeArray.RemoveAll();
    m_ActivationTypeArray.RemoveAll();
    m_MonthPrefixArray.RemoveAll();
    m_MonthShortPrefixArray.RemoveAll();
    m_WeekPrefixArray.RemoveAll();
    m_WeekShortPrefixArray.RemoveAll();
    m_DayPrefixArray.RemoveAll();
    m_DayShortPrefixArray.RemoveAll();
    m_HourPrefixArray.RemoveAll();
    m_HourShortPrefixArray.RemoveAll();
}

void ZAGlobal::LoadPrefixArrays()
{
    CString s;

    // Load Month prefixes
    s.LoadString( IDS_MONTH_PREFIX );
    FillArray( s, m_MonthPrefixArray );
    s.LoadString( IDS_MONTH_PREFIX2 );
    FillArray( s, m_MonthShortPrefixArray );

    // Load Week prefixes
    s.LoadString( IDS_WEEK_PREFIX );
    FillArray( s, m_WeekPrefixArray );
    s.LoadString( IDS_WEEK_PREFIX2 );
    FillArray( s, m_WeekShortPrefixArray );

    // Load Day prefixes
    s.LoadString( IDS_DAY_PREFIX );
    FillArray( s, m_DayPrefixArray );
    s.LoadString( IDS_DAY_PREFIX2 );
    FillArray( s, m_DayShortPrefixArray );

    // Load Hour prefixes
    s.LoadString( IDS_HOUR_PREFIX );
    FillArray( s, m_HourPrefixArray );
    s.LoadString( IDS_HOUR_PREFIX2 );
    FillArray( s, m_HourShortPrefixArray );
}

void ZAGlobal::LoadDateArray()
{
    CStringArray* pArray = new CStringArray;
    CString s;

    // Load English full months
    s.LoadString( IDS_ENGLISH_FMONTHS );
    FillArray( s, *pArray );
    m_FullMonthSet.Add( pArray );

    // Load French full months
    pArray = new CStringArray;
    s.LoadString( IDS_FRENCH_FMONTHS );
    FillArray( s, *pArray );
    m_FullMonthSet.Add( pArray );

    // Load English short months
    pArray = new CStringArray;
    s.LoadString( IDS_ENGLISH_SMONTHS );
    FillArray( s, *pArray );
    m_ShortMonthSet.Add( pArray );

    // Load French short months
    pArray = new CStringArray;
    s.LoadString( IDS_FRENCH_SMONTHS );
    FillArray( s, *pArray );
    m_ShortMonthSet.Add( pArray );
    
    // Load English week days
    pArray = new CStringArray;
    s.LoadString( IDS_ENGLISH_DAYS );
    FillArray( s, *pArray );
    m_DaySet.Add( pArray );

    // Load French week days
    pArray = new CStringArray;
    s.LoadString( IDS_FRENCH_DAYS );
    FillArray( s, *pArray );
    m_DaySet.Add( pArray );
}

void ZAGlobal::FillArray( CString str, CStringArray& Array )
{
    // Initialize the token with ; as separator
    ZBTokenizer token( str );
    token.FillArray( Array );
}

bool ZAGlobal::ReadFromFileHistoricValue( const CString Filename )
{
    ZDHistoricValueDocument doc;

    if ( doc.ReadFromFile( Filename ) )
    {
        // Copy the manager
        m_HistoricValueManager = doc.GetHistoricValueManager();
        return true;
    }

    return false;
}

bool ZAGlobal::SaveToFileHistoricValue( const CString Filename )
{
    ZDHistoricValueDocument doc;

    // Copy the manager
    doc.GetHistoricValueManager() = m_HistoricValueManager;

    return doc.SaveToFile( Filename );
}

void ZAGlobal::SetToFileDirectory()
{
    if ( GetFileDirectory().IsEmpty() )
    {
        return;
    }

    SetCurrentDirectory( GetFileDirectory() );
}

CString    ZAGlobal::ChooseFormulaireFile( const CString InitialDir )
{
    CString title;
    VERIFY( title.LoadString( IDS_SELECT_A_FILE ) );

    // Set the "*.plf" files filter
    CString strFilter;

    VERIFY( strFilter.LoadString( IDS_DOCUMENTFILTER ) );
    strFilter += (char)'\0';    // Next string please
    strFilter += _T( "*.plf" );
    strFilter += (char)'\0';    // Last string

    static CString ChoosedFile;
    ZIFileDialog FileDialog( title, strFilter, 1, ( InitialDir.IsEmpty() ) ? GetFileDirectory() : InitialDir );

    if ( FileDialog.DoModal() == IDOK )
    {
        return ChoosedFile = FileDialog.GetFilename();
    }

    return ChoosedFile = _T( "" );
}

const bool ZAGlobal::InitializeNetwork()
{
    TRACE( _T( "ZAGlobal::InitializeNetwork() initialized" ) );

    // Retreive the connected user name
    CString UserName = GetNetWork().GetUserName();

    // Retreive the adequate user pointer
    m_ConnectedUser = GetUserManager().FindUser( UserName );

    return ( m_ConnectedUser ) ? true : false;
}

const CString ZAGlobal::GetConnectedUserName()
{
    if ( m_ConnectedUser )
    {
        return m_ConnectedUser->GetUserName();
    }

    return _T( "" );
}

CString ZAGlobal::GetWindowModeString( int mode )
{
    switch ( mode )
    {
        case SW_SHOWMINIMIZED:
        {
            if ( m_WindowMode.GetSize() > 1 )
            {
                return m_WindowMode.GetAt( 1 );
            }

            break;
        }

        case SW_SHOWMAXIMIZED:
        {
            if ( m_WindowMode.GetSize() > 2 )
            {
                return m_WindowMode.GetAt( 2 );
            }

            break;
        }

        default:
        case SW_SHOWNORMAL:
        {
            if ( m_WindowMode.GetSize() > 0 )
            {
                return m_WindowMode.GetAt( 0 );
            }

            break;
        }
    }

    return _T( "" );
}

int ZAGlobal::GetWindowMode( const CString strMode )
{
    size_t Count = m_WindowMode.GetSize();

    for ( size_t i = 0; i < Count; ++i )
    {
        if ( m_WindowMode.GetAt( i ) == strMode )
        {
            switch ( i )
            {
                case 1:
                {
                    return SW_SHOWMINIMIZED;
                }

                case 2:
                {
                    return SW_SHOWMAXIMIZED;
                }

                default:
                case 0:
                {
                    return SW_SHOWNORMAL;
                }
            }
        }
    }

    // Not found, anyway, return normal mode
    return SW_SHOWNORMAL;
}

CString ZAGlobal::GetJobPriorityString( int Priority )
{
    switch ( Priority )
    {
        case THREAD_PRIORITY_HIGHEST:
        {
            if ( m_PriorityJob.GetSize() > 0 )
            {
                return m_PriorityJob.GetAt( 0 );
            }

            break;
        }

        case THREAD_PRIORITY_ABOVE_NORMAL:
        {
            if ( m_PriorityJob.GetSize() > 1 )
            {
                return m_PriorityJob.GetAt( 1 );
            }

            break;
        }

        case THREAD_PRIORITY_BELOW_NORMAL:
        {
            if ( m_PriorityJob.GetSize() > 3 )
            {
                return m_PriorityJob.GetAt( 3 );
            }

            break;
        }

        case THREAD_PRIORITY_LOWEST:
        {
            if ( m_PriorityJob.GetSize() > 4 )
            {
                return m_PriorityJob.GetAt( 4 );
            }

            break;
        }

        default:
        case THREAD_PRIORITY_NORMAL:
        {
            if ( m_PriorityJob.GetSize() > 2 )
            {
                return m_PriorityJob.GetAt( 2 );
            }

            break;
        }
    }

    return _T( "" );
}

int ZAGlobal::GetJobPriority( const CString strPriority )
{
    size_t Count = m_PriorityJob.GetSize();

    for ( size_t i = 0; i < Count; ++i )
    {
        if ( m_PriorityJob.GetAt(i) == strPriority )
        {
            switch ( i )
            {
                case 0:
                {
                    return THREAD_PRIORITY_HIGHEST;
                }

                case 1:
                {
                    return THREAD_PRIORITY_ABOVE_NORMAL;
                }

                case 3:
                {
                    return THREAD_PRIORITY_BELOW_NORMAL;
                }

                case 4:
                {
                    return THREAD_PRIORITY_LOWEST;
                }

                default:
                case 2:
                {
                    return THREAD_PRIORITY_NORMAL;
                }
            }
        }
    }

    // Not found, anyway, return normal mode
    return SW_SHOWNORMAL;
}

CString ZAGlobal::GetInsertionTypeString( int type )
{
    switch ( type )
    {
        case RIT_Internal:
        {
            if ( m_InsertionTypeArray.GetSize() > 1 )
            {
                return m_InsertionTypeArray.GetAt( 1 );
            }

            break;
        }

        case RIT_External:
        default:
        {
            if ( m_InsertionTypeArray.GetSize() > 0 )
            {
                return m_InsertionTypeArray.GetAt( 0 );
            }

            break;
        }
    }

    return _T( "" );
}

int ZAGlobal::GetInsertionType( const CString strType )
{
    size_t Count = m_InsertionTypeArray.GetSize();

    for ( size_t i = 0; i < Count; ++i )
    {
        if ( m_InsertionTypeArray.GetAt( i ) == strType )
        {
            switch ( i )
            {
                case 1:
                {
                    return RIT_Internal;
                }

                default:
                case 0:
                {
                    return RIT_External;
                }
            }
        }
    }

    // Not found, anyway, return external mode
    return RIT_External;
}

// Job priority methods

CString ZAGlobal::GetActivationTypeString( int type )
{
    switch ( type )
    {
        case RAT_InSymbol:
        {
            if ( m_ActivationTypeArray.GetSize() > 1 )
            {
                return m_ActivationTypeArray.GetAt( 1 );
            }

            break;
        }

        case RAT_InAndBeforeSymbol:
        {
            if ( m_ActivationTypeArray.GetSize() > 2 )
            {
                return m_ActivationTypeArray.GetAt( 2 );
            }

            break;
        }

        case RAT_Always:
        {
            if ( m_ActivationTypeArray.GetSize() > 3 )
            {
                return m_ActivationTypeArray.GetAt( 3 );
            }

            break;
        }

        case RAT_InAndAfterSymbol:
        default:
        {
            if ( m_ActivationTypeArray.GetSize() > 0 )
            {
                return m_ActivationTypeArray.GetAt( 0 );
            }

            break;
        }
    }

    return _T( "" );
}

int ZAGlobal::GetActivationType( const CString strType )
{
    size_t Count = m_ActivationTypeArray.GetSize();

    for ( size_t i = 0; i < Count; ++i )
    {
        if ( m_ActivationTypeArray.GetAt( i ) == strType )
        {
            switch ( i )
            {
                case 1:
                {
                    return RAT_InSymbol;
                }

                case 2:
                {
                    return RAT_InAndBeforeSymbol;
                }

                case 3:
                {
                    return RAT_Always;
                }

                default:
                case 0:
                {
                    return RAT_InAndAfterSymbol;
                }
            }
        }
    }

    // Not found, anyway, return in and after symbol mode
    return RAT_InAndAfterSymbol;
}

size_t ZAGlobal::GetLanguageTableIndex( LCID lcid )
{
    return ZAGlobal::GetLanguageTableIndex( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

size_t ZAGlobal::GetLanguageTableIndex( WORD primaryLID )
{
    switch ( primaryLID )
    {
        case LANG_FRENCH:
        {
            return 1;
        }

        case LANG_GERMAN:
        {
            return 2;
        }

        case LANG_ENGLISH:
        default:
        {
            return 0;
        }
    }

    return 0;
}

const CString ZAGlobal::GetFullMonth( size_t MonthIndex, LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR strMonth[256];

    ::GetLocaleInfo( lcid,                        // Get string for day of the week from system
                     LongMonths[MonthIndex - 1],
                     strMonth,
                     sizeof( strMonth ) );

    return strMonth;
}

const CString ZAGlobal::GetFullMonth( size_t MonthIndex, WORD primaryLID )
{
    return ZAGlobal::GetFullMonth( MonthIndex, ZAGlobal::MakeLCIDFromLanguageID( primaryLID ) );
}

const CString ZAGlobal::GetShortMonth( size_t MonthIndex, LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR strMonth[256];

    ::GetLocaleInfo( lcid,                        // Get string for day of the week from system
                     ShortMonths[MonthIndex - 1],
                     strMonth,
                     sizeof( strMonth ) );

    return strMonth;
}

const CString ZAGlobal::GetShortMonth( size_t MonthIndex, WORD primaryLID )
{
    return ZAGlobal::GetShortMonth( MonthIndex, ZAGlobal::MakeLCIDFromLanguageID( primaryLID ) );
}

const CString ZAGlobal::GetFullDay( size_t DayIndex, LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR strDay[256];

    ::GetLocaleInfo( lcid,                        // Get string for day of the week from system
                     LongDayOfWeek[DayIndex - 1],
                     strDay,
                     sizeof( strDay ) );

    return strDay;
}

const CString ZAGlobal::GetFullDay( size_t DayIndex, WORD primaryLID )
{
    return ZAGlobal::GetFullDay( DayIndex, ZAGlobal::MakeLCIDFromLanguageID( primaryLID ) );
}

const CString ZAGlobal::GetShortDay( size_t DayIndex, LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR strDay[256];

    ::GetLocaleInfo( lcid,                        // Get string for day of the week from system
                     ShortDayOfWeek[DayIndex - 1],
                     strDay,
                     sizeof( strDay ) );

    return strDay;
}

const CString ZAGlobal::GetShortDay( size_t DayIndex, WORD primaryLID )
{
    return ZAGlobal::GetShortDay( DayIndex, ZAGlobal::MakeLCIDFromLanguageID( primaryLID ) );
}

const CString ZAGlobal::GetMonthPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetMonthPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetMonthPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_MonthPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_MonthPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetMonthShortPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetMonthShortPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetMonthShortPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_MonthShortPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_MonthShortPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetWeekPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetWeekPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetWeekPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_WeekPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_WeekPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetWeekShortPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetWeekShortPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetWeekShortPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_WeekShortPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_WeekShortPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetDayPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetDayPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetDayPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_DayPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_DayPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetDayShortPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetDayShortPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetDayShortPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_DayShortPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_DayShortPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetHourPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetHourPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetHourPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_HourPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_HourPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetHourShortPrefix( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    return ZAGlobal::GetHourShortPrefix( ZAGlobal::GetPrimaryLanguageIDFromLCID( lcid ) );
}

const CString ZAGlobal::GetHourShortPrefix( WORD primaryLID )
{
    size_t Index = GetLanguageTableIndex( primaryLID );

    // Check the language Index validity
    if ( Index >= (size_t)m_HourShortPrefixArray.GetSize() )
    {
        return _T( "" );
    }

    return m_HourShortPrefixArray.GetAt( Index );
}

const CString ZAGlobal::GetLocaleCurrency( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR str[256];

    ::GetLocaleInfo( lcid,                // Get string for currency from system
                     LOCALE_SCURRENCY,
                     str,
                     sizeof( str ) );

    return str;
}

const CString ZAGlobal::GetDateSeparator( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR str[256];

    ::GetLocaleInfo( lcid,                // Get string for date separator from system
                     LOCALE_SDATE,
                     str,
                     sizeof( str ) );

    return str;
}

const CString ZAGlobal::GetTimeSeparator( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR str[256];

    ::GetLocaleInfo( lcid,                // Get string for time separator from system
                     LOCALE_STIME,
                     str,
                     sizeof( str ) );

    return str;
}

const CString ZAGlobal::GetDecimalSeparator( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR str[256];

    ::GetLocaleInfo( lcid,                        // Get string for decimal separator from system
                     LOCALE_SMONDECIMALSEP,
                     str,
                     sizeof( str ) );

    return str;
}

const CString ZAGlobal::GetThousandSeparator( LCID lcid /*= LOCALE_USER_DEFAULT*/ )
{
    TCHAR str[256];

    ::GetLocaleInfo( lcid,                        // Get string for thousand separator from system
                     LOCALE_SMONTHOUSANDSEP,
                     str,
                     sizeof( str ) );

    return str;
}
