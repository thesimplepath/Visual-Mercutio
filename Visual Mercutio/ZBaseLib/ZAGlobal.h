//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//    Source file: z:\adsoft~1\ZBaseLib\ZAGlobal.h

#ifndef ZAGlobal_h
#define ZAGlobal_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZNetWork
#include "ZNetWork.h"

// TmplMng
#include "TmplMng.h"

// ZUMail
#include "ZUMail.h"

// Doc Template Ex
#include "DocTmplEx.h"

// ZBHistoricValueManager
#include "ZBHistoricValueManager.h"

// Forward declaration
class ZDDocument;
class ZDProcessModelDocTmpl;
class ZBServer;

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout de la décoration unicode _T( ), nettoyage du code inutile. (En commentaires)

enum eApplicationType
{
    zUndef,
    zReader,
    zWriter,
    zPublisher,
    zProcess,
    zDesigner,
    zAnalyser,
    zWatcher
};

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

typedef CCArray_T<CStringArray*, CStringArray*> ZBFullMonthSet;
typedef CCArray_T<CStringArray*, CStringArray*> ZBShortMonthSet;
typedef CCArray_T<CStringArray*, CStringArray*> ZBDaySet;

enum ReferenceInsertionType
{
    RIT_External = 0,
    RIT_Internal = 1
};

enum ReferenceActivationType
{
    RAT_InAndAfterSymbol    = 0,
    RAT_InSymbol            = 1,
    RAT_InAndBeforeSymbol    = 2,
    RAT_Always                = 3
};

class AFX_EXT_CLASS ZAGlobal
{
public:

    //## Constructors (generated)
    ZAGlobal();

    //## Destructor (generated)
    ~ZAGlobal();

    // JMR-MODIF - Le 25 août 2005 - Ajout de la fonction Release.
    static void Release();

    static const bool InitializeNetwork ();
    static void Initialize ( ZBServer*            pServer,
                             eApplicationType    AppType,
                             BOOL                IsFormDesigner,
                             BOOL                ShowAnimation,
                             BOOL                MaximizeFormOnOpen,
                             const CString        FileDirectory,
                             const CString        EventDirectory );

    static ZBServer* GetServer()
    {
        return m_pServer;
    }

    // Historic value methods
    static bool ReadFromFileHistoricValue( const CString Filename );
    static bool SaveToFileHistoricValue( const CString Filename );

    static ZBHistoricValueManager& GetHistoricValueManager()
    {
        return m_HistoricValueManager;
    }

    //    Flag used to inform if the application is in
    //    Initialization process.
    static const BOOL IsDuringInitialization();
    static void StartInitialization()
    {
        m_DuringInitialization = TRUE;
    }

    static void EndInitialization()
    {
        m_DuringInitialization = FALSE;
    }

    static eApplicationType GetpType()
    {
        return m_AppType;
    }

    static void SetpType( eApplicationType value )
    {
        m_AppType = value;
    }

    static void SetpCurrentDocumentForSerialization ( ZDDocument* value );
    static ZDDocument* GetpCurrentDocumentForSerialization ();

    static BOOL OpenFileInSilentMode();
    static void SetOpenFileInSilentMode( BOOL value = TRUE );

    static BOOL IsFormDesigner()
    {
        return m_IsFormDesigner;
    }

    static void SetIsFormDesigner( BOOL value )
    {
        m_IsFormDesigner = value;
    }

    static BOOL ShowAnimation()
    {
        return m_ShowAnimation;
    }

    static void SetShowAnimation( BOOL value )
    {
        m_ShowAnimation = value;
    }

    static BOOL MaximizeFormOnOpen()
    {
        return m_MaximizeFormOnOpen;
    }

    static CString ChooseFormulaireFile( const CString InitialDir = _T( "" ) );

    static CString GetApplicationDirectory()
    {
        return m_ApplicationDirectory;
    }

    static void SetApplicationDirectory( const CString value )
    {
        m_ApplicationDirectory = value;
    }

    // Directory methods linked to the ZBServer definition
    static void SetToFileDirectory();
    static CString GetFileDirectory()
    {
        return m_FileDirectory;
    }

    static void SetFileDirectory( const CString value )
    {
        m_FileDirectory = value;
    }

    static CString GetEventDirectory()
    {
        return m_EventDirectory;
    }

    static void SetEventDirectory( const CString value )
    {
        m_EventDirectory = value;
    }

    static CString GetFileExtension();
    static CString GetProcessFileExtension();
    static CString GetModelFileExtension();

    //    The application has a template manager.
    static ZDTemplateManager& GetTemplateManager();

    static ZDTemplateManager& GetProcessTemplateManager();

    static ZDTemplateManager& GetModelTemplateManager();

    //    Keep the pointer on the multi doc template.
    static ZDDocTemplateEx* GetpDocTemplate()
    {
        return m_pDocTemplate;
    }

    static void SetpDocTemplate( ZDDocTemplateEx* value )
    {
        m_pDocTemplate = value;
    }

    //    Keep the pointer on the process multi doc template.
    static ZDDocTemplateEx* GetpProcessDocTemplate()
    {
        return m_pProcessDocTemplate;
    }

    static void SetpProcessDocTemplate( ZDDocTemplateEx* value )
    {
        m_pProcessDocTemplate = value;
    }

    static ZDProcessModelDocTmpl* GetpProcessModelDocumentTemplate()
    {
        return m_pProcessModelDocumentTemplate; 
    }

    static void SetpProcessModelDocumentTemplate ( ZDProcessModelDocTmpl* value )
    {
        m_pProcessModelDocumentTemplate = value;
    }

    // Report document template
    static CMultiDocTemplate* GetpReportDocumentTemplate()
    {
        return m_pReportDocTemplate;
    }

    static void SetpReportDocumentTemplate( CMultiDocTemplate* value )
    {
        m_pReportDocTemplate = value;
    }

    //    The network classes.
    static ZUNetwork& GetNetWork();

    //    The email class.
    static ZUMail& GetMail();

    //    The user manager.
    static ZUUserManager& GetUserManager();

    static const CString& GetResponsibleUserNameKeyString();

    static const CString& GetRequestedUserNameKeyString();

    //    return the name of the connected username.
    static const CString GetConnectedUserName();

    //    Contains the connected user
    static const ZUser* GetConnectedUser();

    static CWnd* GetModalDialogCWnd();
    static void SetModalDialogCWnd( CWnd* pWnd );
    static void ClearModalDialogCWnd();

    // Yes/No methods
    static CStringArray* GetArrayYesNo()
    {
        return &m_ArrayYesNo;
    }

    static CString GetYesFromArrayYesNo()
    {
        ASSERT( m_ArrayYesNo.GetSize() >= 2 );
        return m_ArrayYesNo.GetAt( 1 );
    }

    static CString GetNoFromArrayYesNo()
    {
        ASSERT( m_ArrayYesNo.GetSize() >= 2 );
        return m_ArrayYesNo.GetAt( 0 );
    }

    // Window mode methods
    static CStringArray* GetArrayWindowMode()
    {
        return &m_WindowMode;
    }

    static CString GetWindowModeString( int mode );
    static int GetWindowMode( const CString strMode );

    // Job priority methods
    static CStringArray* GetArrayJobPriority()
    {
        return &m_PriorityJob;
    }

    static CString GetJobPriorityString( int Priority );
    static int GetJobPriority( const CString strPriority );

    // Insertion type methods
    static CStringArray* GetArrayInsertionType()
    {
        return &m_InsertionTypeArray;
    }

    static CString GetInsertionTypeString( int type );
    static int GetInsertionType( const CString strType );

    // Activation type methods
    static CStringArray* GetArrayActivationType()
    {
        return &m_ActivationTypeArray;
    }

    static CString GetActivationTypeString( int type );
    static int GetActivationType( const CString strType );

    // Language methods
    static WORD GetPrimaryLanguageIDFromLCID( LCID lcid );
    static WORD GetSubLanguageIDFromLCID( LCID lcid );
    static WORD GetSortLanguageIDFromLCID( LCID lcid );

    static LCID MakeLCIDFromLanguageID( WORD primaryLID,
                                        WORD subLID            = SUBLANG_DEFAULT,
                                        WORD sortID            = SORT_DEFAULT );

    static void GetLanguageIDsFromLCID( LCID lcid, WORD& primaryLID, WORD& subLID, WORD& sortID );

    // Months and Days string methods
    static const CString GetFullMonth( size_t MonthIndex, LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetFullMonth( size_t MonthIndex, WORD primaryLID );

    static const CString GetShortMonth( size_t MonthIndex, LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetShortMonth( size_t MonthIndex, WORD primaryLID );

    static const CString GetFullDay( size_t DayIndex, LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetFullDay( size_t DayIndex, WORD primaryLID );

    static const CString GetShortDay( size_t DayIndex, LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetShortDay( size_t DayIndex, WORD primaryLID );

    // Month, Week and Day prefix string methods
    static const CString GetMonthPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetMonthPrefix( WORD primaryLID );

    static const CString GetMonthShortPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetMonthShortPrefix( WORD primaryLID );

    static const CString GetWeekPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetWeekPrefix( WORD primaryLID );

    static const CString GetWeekShortPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetWeekShortPrefix( WORD primaryLID );

    static const CString GetDayPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetDayPrefix( WORD primaryLID );

    static const CString GetDayShortPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetDayShortPrefix( WORD primaryLID );

    static const CString GetHourPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetHourPrefix( WORD primaryLID );

    static const CString GetHourShortPrefix( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetHourShortPrefix( WORD primaryLID );

    // Internationalization methods
    static const CString GetLocaleCurrency( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetDateSeparator( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetTimeSeparator( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetDecimalSeparator( LCID lcid = LOCALE_USER_DEFAULT );
    static const CString GetThousandSeparator( LCID lcid = LOCALE_USER_DEFAULT );

    // Utility function used to fill a string array. The source string is delimeted
    // by ; separator
    static void FillArray( CString str, CStringArray& Array );

private:

    ZAGlobal( const ZAGlobal &right );
    const ZAGlobal & operator=( const ZAGlobal &right );

    static size_t GetLanguageTableIndex( LCID lcid );
    static size_t GetLanguageTableIndex( WORD primaryLID );
    static void LoadDateArray();
    static void LoadPrefixArrays();

private:

    static BOOL                        m_OpenFileInSilentMode;
    static BOOL                        m_IsFormDesigner;
    static BOOL                        m_ShowAnimation;
    static BOOL                        m_MaximizeFormOnOpen;
    static BOOL                        m_DuringInitialization;

    static CString                    m_FileDirectory;
    static CString                    m_EventDirectory;
    static CString                    m_ApplicationDirectory;
    static CString                    m_ResponsibleUserNameKeyString;
    static CString                    m_RequestedUserNameKeyString;

    static CStringArray                m_ArrayYesNo;
    static CStringArray                m_WindowMode;
    static CStringArray                m_PriorityJob;
    static CStringArray                m_InsertionTypeArray;
    static CStringArray                m_ActivationTypeArray;
    static CStringArray                m_MonthPrefixArray;
    static CStringArray                m_MonthShortPrefixArray;
    static CStringArray                m_WeekPrefixArray;
    static CStringArray                m_WeekShortPrefixArray;
    static CStringArray                m_DayPrefixArray;
    static CStringArray                m_DayShortPrefixArray;
    static CStringArray                m_HourPrefixArray;
    static CStringArray                m_HourShortPrefixArray;

    static eApplicationType            m_AppType;

    static ZBHistoricValueManager    m_HistoricValueManager;

    static ZDTemplateManager        m_TemplateManager;
    static ZDTemplateManager        m_ProcessTemplateManager;
    static ZDTemplateManager        m_ModelTemplateManager;

    static ZUUserManager            m_UserManager;

    static ZUNetwork                m_NetWork;

    static ZUMail                    m_Mail;

    static ZBFullMonthSet            m_FullMonthSet;

    static ZBShortMonthSet            m_ShortMonthSet;

    static ZBDaySet                    m_DaySet;

    static ZDDocTemplateEx*            m_pDocTemplate;
    static ZDDocTemplateEx*            m_pProcessDocTemplate;

    static CMultiDocTemplate*        m_pReportDocTemplate;

    static ZDProcessModelDocTmpl*    m_pProcessModelDocumentTemplate;

    static ZBServer*                m_pServer;

    static ZDDocument*                m_pCurrentDocumentForSerialization;

    static ZUser*                    m_ConnectedUser;

    static CWnd*                    m_pModalDialogCWnd;
};

inline ZDDocument* ZAGlobal::GetpCurrentDocumentForSerialization()
{
    return m_pCurrentDocumentForSerialization;
}

inline void ZAGlobal::SetpCurrentDocumentForSerialization( ZDDocument* value )
{
    m_pCurrentDocumentForSerialization = value;
}

inline BOOL ZAGlobal::OpenFileInSilentMode()
{
    return m_OpenFileInSilentMode; 
}

inline void ZAGlobal::SetOpenFileInSilentMode( BOOL value /*= TRUE*/ )
{
    m_OpenFileInSilentMode = value; 
}

inline CString ZAGlobal::GetFileExtension()
{
    return g_FormExtensionNoDot;
}

inline CString ZAGlobal::GetProcessFileExtension()
{
    return g_ProcessExtensionNoDot;
}

inline CString ZAGlobal::GetModelFileExtension()
{
    return g_ModelExtensionNoDot;
}

inline const BOOL ZAGlobal::IsDuringInitialization()
{
    return m_DuringInitialization;
}

inline ZDTemplateManager& ZAGlobal::GetTemplateManager()
{
    return m_TemplateManager;
}

inline ZDTemplateManager& ZAGlobal::GetProcessTemplateManager()
{
    return m_ProcessTemplateManager;
}

inline ZDTemplateManager& ZAGlobal::GetModelTemplateManager()
{
    return m_ModelTemplateManager;
}

inline ZUNetwork& ZAGlobal::GetNetWork()
{
    return m_NetWork;
}

inline ZUMail& ZAGlobal::GetMail()
{
    return m_Mail;
}

inline ZUUserManager& ZAGlobal::GetUserManager()
{
    return m_UserManager;
}

inline const ZUser* ZAGlobal::GetConnectedUser()
{
  return m_ConnectedUser;
}

inline WORD ZAGlobal::GetPrimaryLanguageIDFromLCID( LCID lcid )
{
    // Retreive the lang id 
    WORD langID = LANGIDFROMLCID( lcid );

    // returns the primary language id
    return PRIMARYLANGID( langID );
}

inline WORD ZAGlobal::GetSubLanguageIDFromLCID( LCID lcid )
{
    // Retreive the lang id 
    WORD langID = LANGIDFROMLCID( lcid );

    // returns the sub language id
    return SUBLANGID( langID );
}

inline WORD ZAGlobal::GetSortLanguageIDFromLCID( LCID lcid )
{
    // Retreive the sort ID
    return SORTIDFROMLCID( lcid );
}

inline void ZAGlobal::GetLanguageIDsFromLCID( LCID lcid, WORD& primaryLID, WORD& subLID, WORD& sortID )
{
    // Retreive the lang id and the 
    WORD langID = LANGIDFROMLCID( lcid );

    // Retreive the sort ID
    sortID = SORTIDFROMLCID( lcid );

    primaryLID = PRIMARYLANGID( langID );
    subLID = SUBLANGID( langID );
}

inline LCID ZAGlobal::MakeLCIDFromLanguageID( WORD primaryLID,
                                              WORD subLID        /*= SUBLANG_DEFAULT*/,
                                              WORD sortID        /*= SORT_DEFAULT*/ )
{
    WORD langID = MAKELANGID( primaryLID,    // primary language identifier
                              subLID );        // sublanguage identifier

    return MAKELCID( langID, sortID );
}

inline const CString& ZAGlobal::GetResponsibleUserNameKeyString()
{
    return m_ResponsibleUserNameKeyString;
}

inline const CString& ZAGlobal::GetRequestedUserNameKeyString()
{
    return m_RequestedUserNameKeyString;
}

inline CWnd* ZAGlobal::GetModalDialogCWnd()
{
    return m_pModalDialogCWnd;
}

inline void ZAGlobal::SetModalDialogCWnd( CWnd* pWnd )
{
    m_pModalDialogCWnd = pWnd;
}

inline void ZAGlobal::ClearModalDialogCWnd()
{
    m_pModalDialogCWnd = NULL;
}

#endif