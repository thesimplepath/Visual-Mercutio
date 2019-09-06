/****************************************************************************
 * ==> PSS_Global ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a global application helper                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Global.h"

// processsoft
#include "ZDHistoricValueDocument.h"
#include "PSS_DocTemplateEx.h"
#include "PSS_ProcessModelDocTmpl.h"
#include "ZBTokenizer.h"
#include "PSS_FileDialog.h"

// resources
#include "zBaseLibRes.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
UINT g_LongDayOfWeek[] =
{
    LOCALE_SDAYNAME7, // sunday
    LOCALE_SDAYNAME1,
    LOCALE_SDAYNAME2,
    LOCALE_SDAYNAME3,
    LOCALE_SDAYNAME4,
    LOCALE_SDAYNAME5,
    LOCALE_SDAYNAME6  // saturday
};

UINT g_ShortDayOfWeek[] =
{
    LOCALE_SABBREVDAYNAME7, // sunday
    LOCALE_SABBREVDAYNAME1,
    LOCALE_SABBREVDAYNAME2,
    LOCALE_SABBREVDAYNAME3,
    LOCALE_SABBREVDAYNAME4,
    LOCALE_SABBREVDAYNAME5,
    LOCALE_SABBREVDAYNAME6  // saturday
};

UINT g_LongMonths[] =
{
    LOCALE_SMONTHNAME1,  // long name for January
    LOCALE_SMONTHNAME2,  // long name for February
    LOCALE_SMONTHNAME3,  // long name for March
    LOCALE_SMONTHNAME4,  // long name for April
    LOCALE_SMONTHNAME5,  // long name for May
    LOCALE_SMONTHNAME6,  // long name for June
    LOCALE_SMONTHNAME7,  // long name for July
    LOCALE_SMONTHNAME8,  // long name for August
    LOCALE_SMONTHNAME9,  // long name for September
    LOCALE_SMONTHNAME10, // long name for October
    LOCALE_SMONTHNAME11, // long name for November
    LOCALE_SMONTHNAME12, // long name for December
    LOCALE_SMONTHNAME13  // long name for 13th month (if exists)
};

UINT g_ShortMonths[] =
{
    LOCALE_SABBREVMONTHNAME1,  // abreviated name for January
    LOCALE_SABBREVMONTHNAME2,  // abreviated name for February
    LOCALE_SABBREVMONTHNAME3,  // abreviated name for March
    LOCALE_SABBREVMONTHNAME4,  // abreviated name for April
    LOCALE_SABBREVMONTHNAME5,  // abreviated name for May
    LOCALE_SABBREVMONTHNAME6,  // abreviated name for June
    LOCALE_SABBREVMONTHNAME7,  // abreviated name for July
    LOCALE_SABBREVMONTHNAME8,  // abreviated name for August
    LOCALE_SABBREVMONTHNAME9,  // abreviated name for September
    LOCALE_SABBREVMONTHNAME10, // abreviated name for October
    LOCALE_SABBREVMONTHNAME11, // abreviated name for November
    LOCALE_SABBREVMONTHNAME12, // abreviated name for December
    LOCALE_SABBREVMONTHNAME13  // abreviated name for 13th month (if exists)
};
//---------------------------------------------------------------------------
// Application global variables
//---------------------------------------------------------------------------
CWnd*                         PSS_Global::m_pModalDialogCWnd                 = NULL;
ZDDocument*                   PSS_Global::m_pCurrentDocumentForSerialization = NULL;
PSS_DocTemplateEx*            PSS_Global::m_pDocTemplate                     = NULL;
PSS_DocTemplateEx*            PSS_Global::m_pProcessDocTemplate              = NULL;
CMultiDocTemplate*            PSS_Global::m_pReportDocTemplate               = NULL;
PSS_ProcessModelDocTmpl*      PSS_Global::m_pProcessModelDocumentTemplate    = NULL;
ZUser*                        PSS_Global::m_ConnectedUser                    = NULL;
ZBServer*                     PSS_Global::m_pServer                          = NULL;
ZBHistoricValueManager        PSS_Global::m_HistoricValueManager;
PSS_TemplateManager           PSS_Global::m_TemplateManager;
PSS_TemplateManager           PSS_Global::m_ProcessTemplateManager;
PSS_TemplateManager           PSS_Global::m_ModelTemplateManager;
PSS_UserManager               PSS_Global::m_UserManager;
ZUNetwork                     PSS_Global::m_NetWork;
ZUMail                        PSS_Global::m_Mail;
PSS_Global::IFullMonthSet     PSS_Global::m_FullMonthSet;
PSS_Global::IShortMonthSet    PSS_Global::m_ShortMonthSet;
PSS_Global::IDaySet           PSS_Global::m_DaySet;
PSS_Global::IEApplicationType PSS_Global::m_AppType = PSS_Global::IE_AT_Undef;
CStringArray                  PSS_Global::m_ArrayYesNo;
CStringArray                  PSS_Global::m_WindowMode;
CStringArray                  PSS_Global::m_PriorityJob;
CStringArray                  PSS_Global::m_InsertionTypeArray;
CStringArray                  PSS_Global::m_ActivationTypeArray;
CStringArray                  PSS_Global::m_MonthPrefixArray;
CStringArray                  PSS_Global::m_MonthShortPrefixArray;
CStringArray                  PSS_Global::m_WeekPrefixArray;
CStringArray                  PSS_Global::m_WeekShortPrefixArray;
CStringArray                  PSS_Global::m_DayPrefixArray;
CStringArray                  PSS_Global::m_DayShortPrefixArray;
CStringArray                  PSS_Global::m_HourPrefixArray;
CStringArray                  PSS_Global::m_HourShortPrefixArray;
CString                       PSS_Global::m_FileDirectory        = _T("");
CString                       PSS_Global::m_EventDirectory       = _T("");
CString                       PSS_Global::m_ApplicationDirectory = _T("");
CString                       PSS_Global::m_ResponsibleUserNameKeyString;
CString                       PSS_Global::m_RequestedUserNameKeyString;
BOOL                          PSS_Global::m_OpenFileInSilentMode = FALSE;
BOOL                          PSS_Global::m_IsFormDesigner       = FALSE;
BOOL                          PSS_Global::m_ShowAnimation        = FALSE;
BOOL                          PSS_Global::m_MaximizeFormOnOpen   = FALSE;
BOOL                          PSS_Global::m_DuringInitialization = FALSE;
//---------------------------------------------------------------------------
// PSS_Global
//---------------------------------------------------------------------------
PSS_Global::PSS_Global()
{
    TRACE( _T( "Don't forget to ZAGlobal::Initialize() !!!!!!!!!!" ) );
    TRACE( _T( "Don't forget to call ZAGlobal::InitializeNetwork()!!!!!!!!!!" ) );
}
//---------------------------------------------------------------------------
PSS_Global::PSS_Global(const PSS_Global& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Global::~PSS_Global()
{}
//---------------------------------------------------------------------------
const PSS_Global& PSS_Global::operator = (const PSS_Global& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_Global::Initialize(ZBServer*         pServer,
                            IEApplicationType appType,
                            BOOL              isFormDesigner,
                            BOOL              showAnimation,
                            BOOL              maximizeFormOnOpen,
                            const CString&    fileDirectory,
                            const CString&    eventDirectory)
{
    m_pServer            = pServer;
    m_AppType            = appType;
    m_FileDirectory      = fileDirectory;
    m_EventDirectory     = eventDirectory;
    m_IsFormDesigner     = isFormDesigner;
    m_ShowAnimation      = showAnimation;
    m_MaximizeFormOnOpen = maximizeFormOnOpen;

    m_ResponsibleUserNameKeyString.LoadString(g_ResponsibleUserNameIDResource);
    m_RequestedUserNameKeyString.LoadString(g_RequestedUserNameIDResource);

    CString s;

    // load the yes/no array
    m_ArrayYesNo.RemoveAll();
    s.LoadString(IDS_NO);
    m_ArrayYesNo.Add(s);
    s.LoadString(IDS_YES);
    m_ArrayYesNo.Add(s);

    // load the window mode strings
    s.LoadString(IDS_WINDOW_MODE);
    FillArray(s, m_WindowMode);

    // load the priority job strings
    s.LoadString(IDS_PRIORITY_JOB);
    FillArray(s, m_PriorityJob);

    // load the insertion type strings
    s.LoadString(IDS_INSERTIONTYPE_ARRAY);
    FillArray(s, m_InsertionTypeArray);

    // load the activation type strings
    s.LoadString(IDS_ACTIVATIONTYPE_ARRAY);
    FillArray(s, m_ActivationTypeArray);

    LoadDateArray();
    LoadPrefixArrays();

    TRACE(_T("ZAGlobal::Initialize() initialized"));
}
//---------------------------------------------------------------------------
const bool PSS_Global::InitializeNetwork()
{
    TRACE(_T("ZAGlobal::InitializeNetwork() initialized"));

    // get the connected user name
    const CString userName = GetNetWork().GetUserName();

    // get the matching user
    m_ConnectedUser = GetUserManager().FindUser(userName);

    return m_ConnectedUser;
}
//---------------------------------------------------------------------------
void PSS_Global::Release()
{
    // delete all allocated multi-lang CStringArray
    std::size_t i;
    std::size_t count = m_FullMonthSet.GetSize();

    for (i = 0; i < count; ++i)
        if (m_FullMonthSet.GetAt(i))
            delete m_FullMonthSet.GetAt(i);

    count = m_ShortMonthSet.GetSize();

    for (i = 0; i < count; ++i)
        if (m_ShortMonthSet.GetAt(i))
            delete m_ShortMonthSet.GetAt(i);

    count = m_DaySet.GetSize();

    for (i = 0; i < count; ++i)
        if (m_DaySet.GetAt(i))
            delete m_DaySet.GetAt(i);

    // empty strings
    m_FileDirectory.Empty();
    m_EventDirectory.Empty();
    m_ApplicationDirectory.Empty();
    m_ResponsibleUserNameKeyString.Empty();
    m_RequestedUserNameKeyString.Empty();

    // empty string arrays
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
//---------------------------------------------------------------------------
bool PSS_Global::ReadFromFileHistoricValue(const CString& fileName)
{
    ZDHistoricValueDocument doc;

    // copy the manager
    if (doc.ReadFromFile(fileName))
    {
        m_HistoricValueManager = doc.GetHistoricValueManager();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_Global::SaveToFileHistoricValue(const CString& fileName)
{
    ZDHistoricValueDocument doc;

    // copy the manager
    doc.GetHistoricValueManager() = m_HistoricValueManager;

    return doc.SaveToFile(fileName);
}
//---------------------------------------------------------------------------
CString PSS_Global::SelectFormFile(const CString& initialDir)
{
    CString title;
    VERIFY(title.LoadString(IDS_SELECT_A_FILE));

    CString filters;

    // set the "*.plf" files filter
    VERIFY(filters.LoadString(IDS_DOCUMENTFILTER));
    filters += char('\0');
    filters += _T("*.plf");
    filters += char('\0');

    static CString selectedFile;
    PSS_FileDialog fileDialog(title, filters, 1, (initialDir.IsEmpty() ? GetFileDirectory() : initialDir));

    if (fileDialog.DoModal() == IDOK)
        return selectedFile = fileDialog.GetFileName();

    return selectedFile = _T("");
}
//---------------------------------------------------------------------------
void PSS_Global::SetToFileDirectory()
{
    if (GetFileDirectory().IsEmpty())
        return;

    SetCurrentDirectory(GetFileDirectory());
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetConnectedUserName()
{
    if (m_ConnectedUser)
        return m_ConnectedUser->GetUserName();

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_Global::GetWindowModeString(int mode)
{
    switch (mode)
    {
        case SW_SHOWMINIMIZED:
            if (m_WindowMode.GetSize() > 1)
                return m_WindowMode.GetAt(1);

            break;

        case SW_SHOWMAXIMIZED:
            if (m_WindowMode.GetSize() > 2)
                return m_WindowMode.GetAt(2);

            break;

        default:
            if (m_WindowMode.GetSize() > 0)
                return m_WindowMode.GetAt(0);

            break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
int PSS_Global::GetWindowMode(const CString& mode)
{
    const std::size_t count = m_WindowMode.GetSize();

    for (std::size_t i = 0; i < count; ++i)
        if (m_WindowMode.GetAt(i) == mode)
            switch (i)
            {
                case 1:  return SW_SHOWMINIMIZED;
                case 2:  return SW_SHOWMAXIMIZED;
                default: return SW_SHOWNORMAL;
            }

    // not found, anyway, return normal mode
    return SW_SHOWNORMAL;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetJobPriorityString(int priority)
{
    switch (priority)
    {
        case THREAD_PRIORITY_HIGHEST:
            if (m_PriorityJob.GetSize() > 0)
                return m_PriorityJob.GetAt(0);

            break;

        case THREAD_PRIORITY_ABOVE_NORMAL:
            if (m_PriorityJob.GetSize() > 1)
                return m_PriorityJob.GetAt(1);

            break;

        case THREAD_PRIORITY_BELOW_NORMAL:
            if (m_PriorityJob.GetSize() > 3)
                return m_PriorityJob.GetAt(3);

            break;

        case THREAD_PRIORITY_LOWEST:
            if (m_PriorityJob.GetSize() > 4)
                return m_PriorityJob.GetAt(4);

            break;

        default:
            if (m_PriorityJob.GetSize() > 2)
                return m_PriorityJob.GetAt(2);

            break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
int PSS_Global::GetJobPriority(const CString& priority)
{
    std::size_t count = m_PriorityJob.GetSize();

    for (std::size_t i = 0; i < count; ++i)
        if (m_PriorityJob.GetAt(i) == priority)
            switch (i)
            {
                case 0:  return THREAD_PRIORITY_HIGHEST;
                case 1:  return THREAD_PRIORITY_ABOVE_NORMAL;
                case 3:  return THREAD_PRIORITY_BELOW_NORMAL;
                case 4:  return THREAD_PRIORITY_LOWEST;
                default: return THREAD_PRIORITY_NORMAL;
            }

    // not found, anyway, return normal mode
    return SW_SHOWNORMAL;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetInsertionTypeString(int type)
{
    switch (type)
    {
        case IE_RI_Internal:
            if (m_InsertionTypeArray.GetSize() > 1)
                return m_InsertionTypeArray.GetAt(1);

            break;

        default:
            if (m_InsertionTypeArray.GetSize() > 0)
                return m_InsertionTypeArray.GetAt(0);

            break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
int PSS_Global::GetInsertionType(const CString& type)
{
    std::size_t count = m_InsertionTypeArray.GetSize();

    for (std::size_t i = 0; i < count; ++i)
        if (m_InsertionTypeArray.GetAt(i) == type)
            switch (i)
            {
                case 1:  return IE_RI_Internal;
                default: return IE_RI_External;
            }

    // not found, anyway, return external mode
    return IE_RI_External;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetActivationTypeString(int type)
{
    switch (type)
    {
        case IE_RA_InSymbol:
            if (m_ActivationTypeArray.GetSize() > 1)
                return m_ActivationTypeArray.GetAt(1);

            break;

        case IE_RA_InAndBeforeSymbol:
            if (m_ActivationTypeArray.GetSize() > 2)
                return m_ActivationTypeArray.GetAt(2);

            break;

        case IE_RA_Always:
            if (m_ActivationTypeArray.GetSize() > 3)
                return m_ActivationTypeArray.GetAt(3);

            break;

        default:
            if (m_ActivationTypeArray.GetSize() > 0)
                return m_ActivationTypeArray.GetAt(0);

            break;
    }

    return _T("");
}
//---------------------------------------------------------------------------
int PSS_Global::GetActivationType(const CString& type)
{
    std::size_t count = m_ActivationTypeArray.GetSize();

    for (std::size_t i = 0; i < count; ++i)
        if (m_ActivationTypeArray.GetAt(i) == type)
            switch (i)
            {
                case 1:  return IE_RA_InSymbol;
                case 2:  return IE_RA_InAndBeforeSymbol;
                case 3:  return IE_RA_Always;
                default: return IE_RA_InAndAfterSymbol;
            }

    // not found, anyway, return in and after symbol mode
    return IE_RA_InAndAfterSymbol;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetFullMonth(std::size_t monthIndex, LCID lcid)
{
    TCHAR month[256];

    // get day of the week string from system
    ::GetLocaleInfo(lcid, g_LongMonths[monthIndex - 1], month, sizeof(month));

    return month;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetFullMonth(std::size_t monthIndex, WORD primaryLID)
{
    return GetFullMonth(monthIndex, MakeLCIDFromLanguageID(primaryLID));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetShortMonth(std::size_t monthIndex, LCID lcid)
{
    TCHAR month[256];

    // get day of the week string from system
    ::GetLocaleInfo(lcid, g_ShortMonths[monthIndex - 1], month, sizeof(month));

    return month;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetShortMonth(std::size_t monthIndex, WORD primaryLID)
{
    return GetShortMonth(monthIndex, MakeLCIDFromLanguageID(primaryLID));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetFullDay(std::size_t dayIndex, LCID lcid)
{
    TCHAR day[256];

    // get day of the week string from system
    ::GetLocaleInfo(lcid, g_LongDayOfWeek[dayIndex - 1], day, sizeof(day));

    return day;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetFullDay(std::size_t dayIndex, WORD primaryLID)
{
    return GetFullDay(dayIndex, MakeLCIDFromLanguageID(primaryLID));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetShortDay(std::size_t dayIndex, LCID lcid)
{
    TCHAR day[256];

    // get day of the week string from system
    ::GetLocaleInfo(lcid, g_ShortDayOfWeek[dayIndex - 1], day, sizeof(day));

    return day;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetShortDay(std::size_t dayIndex, WORD primaryLID)
{
    return GetShortDay(dayIndex, MakeLCIDFromLanguageID(primaryLID));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetMonthPrefix(LCID lcid)
{
    return GetMonthPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetMonthPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language index validity
    if (index >= (size_t)m_MonthPrefixArray.GetSize())
        return _T("");

    return m_MonthPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetMonthShortPrefix(LCID lcid)
{
    return GetMonthShortPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetMonthShortPrefix(WORD primaryLID)
{
    std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language index validity
    if (index >= std::size_t(m_MonthShortPrefixArray.GetSize()))
        return _T("");

    return m_MonthShortPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetWeekPrefix(LCID lcid)
{
    return GetWeekPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetWeekPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language Index validity
    if (index >= std::size_t(m_WeekPrefixArray.GetSize()))
        return _T("");

    return m_WeekPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetWeekShortPrefix(LCID lcid)
{
    return GetWeekShortPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetWeekShortPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language Index validity
    if (index >= std::size_t(m_WeekShortPrefixArray.GetSize()))
        return _T("");

    return m_WeekShortPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDayPrefix(LCID lcid)
{
    return GetDayPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDayPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language index validity
    if (index >= std::size_t(m_DayPrefixArray.GetSize()))
        return _T("");

    return m_DayPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDayShortPrefix(LCID lcid)
{
    return GetDayShortPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDayShortPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language Index validity
    if (index >= std::size_t(m_DayShortPrefixArray.GetSize()))
        return _T("");

    return m_DayShortPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetHourPrefix(LCID lcid)
{
    return GetHourPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetHourPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language Index validity
    if (index >= std::size_t(m_HourPrefixArray.GetSize()))
        return _T("");

    return m_HourPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetHourShortPrefix(LCID lcid)
{
    return GetHourShortPrefix(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetHourShortPrefix(WORD primaryLID)
{
    const std::size_t index = GetLanguageTableIndex(primaryLID);

    // check the language Index validity
    if (index >= std::size_t(m_HourShortPrefixArray.GetSize()))
        return _T("");

    return m_HourShortPrefixArray.GetAt(index);
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetLocaleCurrency(LCID lcid)
{
    TCHAR str[256];

    // get currency string from system
    ::GetLocaleInfo(lcid, LOCALE_SCURRENCY, str, sizeof(str));

    return str;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDateSeparator(LCID lcid)
{
    TCHAR str[256];

    // get date separator string from system
    ::GetLocaleInfo(lcid, LOCALE_SDATE, str, sizeof(str));

    return str;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetTimeSeparator(LCID lcid)
{
    TCHAR str[256];

    // Get time separator string from system
    ::GetLocaleInfo(lcid, LOCALE_STIME, str, sizeof(str));

    return str;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetDecimalSeparator(LCID lcid)
{
    TCHAR str[256];

    // Get decimal separator string from system
    ::GetLocaleInfo(lcid, LOCALE_SMONDECIMALSEP, str, sizeof(str));

    return str;
}
//---------------------------------------------------------------------------
const CString PSS_Global::GetThousandSeparator(LCID lcid)
{
    TCHAR str[256];

    // Get thousand separator string from system
    ::GetLocaleInfo(lcid, LOCALE_SMONTHOUSANDSEP, str, sizeof(str));

    return str;
}
//---------------------------------------------------------------------------
void PSS_Global::FillArray(const CString& str, CStringArray& strArray)
{
    // initialize the token setting ; as separator
    ZBTokenizer token(str);
    token.FillArray(strArray);
}
//---------------------------------------------------------------------------
std::size_t PSS_Global::GetLanguageTableIndex(LCID lcid)
{
    return GetLanguageTableIndex(GetPrimaryLanguageIDFromLCID(lcid));
}
//---------------------------------------------------------------------------
std::size_t PSS_Global::GetLanguageTableIndex(WORD primaryLID)
{
    switch (primaryLID)
    {
        case LANG_FRENCH: return 1;
        case LANG_GERMAN: return 2;
        default:          return 0;
    }
}
//---------------------------------------------------------------------------
void PSS_Global::LoadDateArray()
{
    CString s;

    // load English full months
    std::unique_ptr<CStringArray> pArray(new CStringArray());
    s.LoadString(IDS_ENGLISH_FMONTHS);
    FillArray(s, *pArray);
    m_FullMonthSet.Add(pArray.get());
    pArray.release();

    // load French full months
    pArray.reset(new CStringArray());
    s.LoadString(IDS_FRENCH_FMONTHS);
    FillArray(s, *pArray);
    m_FullMonthSet.Add(pArray.get());
    pArray.release();

    // load English short months
    pArray.reset(new CStringArray());
    s.LoadString(IDS_ENGLISH_SMONTHS);
    FillArray(s, *pArray);
    m_ShortMonthSet.Add(pArray.get());
    pArray.release();

    // load French short months
    pArray.reset(new CStringArray());
    s.LoadString(IDS_FRENCH_SMONTHS);
    FillArray(s, *pArray);
    m_ShortMonthSet.Add(pArray.get());
    pArray.release();

    // load English week days
    pArray.reset(new CStringArray());
    s.LoadString(IDS_ENGLISH_DAYS);
    FillArray(s, *pArray);
    m_DaySet.Add(pArray.get());
    pArray.release();

    // load French week days
    pArray.reset(new CStringArray());
    s.LoadString(IDS_FRENCH_DAYS);
    FillArray(s, *pArray);
    m_DaySet.Add(pArray.get());
    pArray.release();
}
//---------------------------------------------------------------------------
void PSS_Global::LoadPrefixArrays()
{
    CString s;

    // load month prefixes
    s.LoadString(IDS_MONTH_PREFIX);
    FillArray(s, m_MonthPrefixArray);
    s.LoadString(IDS_MONTH_PREFIX2);
    FillArray(s, m_MonthShortPrefixArray);

    // load week prefixes
    s.LoadString(IDS_WEEK_PREFIX);
    FillArray(s, m_WeekPrefixArray);
    s.LoadString(IDS_WEEK_PREFIX2);
    FillArray(s, m_WeekShortPrefixArray);

    // load day prefixes
    s.LoadString(IDS_DAY_PREFIX);
    FillArray(s, m_DayPrefixArray);
    s.LoadString(IDS_DAY_PREFIX2);
    FillArray(s, m_DayShortPrefixArray);

    // load hour prefixes
    s.LoadString(IDS_HOUR_PREFIX);
    FillArray(s, m_HourPrefixArray);
    s.LoadString(IDS_HOUR_PREFIX2);
    FillArray(s, m_HourShortPrefixArray);
}
//---------------------------------------------------------------------------
