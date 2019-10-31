/****************************************************************************
 * ==> Defines -------------------------------------------------------------*
 ****************************************************************************
 * Description : This file define the different type used within the        *
 *               PlanFin application                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef DefineH
#define DefineH

 // windows
#include <atltypes.h>

// assign the system zero time
#ifndef _WIN32
    static CTime g_ZeroTime(1970, 01, 01, 12, 00, 00);
#else
    #include <atlcomtime.h>

    // assign the system zero time
    static COleDateTime g_ZeroTime(1970, 01, 01, 12, 00, 00);
#endif

/**
* Button type enumeration
*/
enum ECheckButtonType
{
    E_CB_Rounded,
    E_CB_Squared
};

/**
* Class type enumeration
*/
enum EClassType
{
    E_CT_Rect,
    E_CT_Line,
    E_CT_Static,
    E_CT_Numbered,
    E_CT_NumbEdit,
    E_CT_NumbNumEdit,
    E_CT_String,
    E_CT_StringHistory,
    E_CT_NumHistory,
    E_CT_Time,
    E_CT_Int,
    E_CT_Word,
    E_CT_Long,
    E_CT_Calculated,
    E_CT_Nothing,
    E_CT_AllObjects,
    E_CT_ExportedSVM,
    E_CT_Text,
    E_CT_Graphic
};

/**
* Format type enumeration
*/
enum EFormatType
{
    E_FT_Percentage       = '%',
    E_FT_Date             = 'd',
    E_FT_Date1            = '1',
    E_FT_Date2            = '2',
    E_FT_Date3            = '3',
    E_FT_Date4            = '4',
    E_FT_Date5            = '5',
    E_FT_Date6            = '6',
    E_FT_Amount           = 'a',
    E_FT_Amount1          = 'b',
    E_FT_Amount2          = 'c',
    E_FT_Amount1Dash      = 'v',
    E_FT_Amount2Dash      = 'w',
    E_FT_Amount1DashTrail = 'x',
    E_FT_Amount2DashTrail = 'y',
    E_FT_Standard         = 'n'
};

/**
* Line type enumeration
*/
enum ELineType
{
    E_LT_Automatic,
    E_LT_No,
    E_LT_Dotted,
    E_LT_Solid,
    E_LT_Dash,
    E_LT_Small
};

/**
* Square type enumeration
*/
enum ESquareType
{
    E_SQ_Normal,
    E_SQ_TopOnly,
    E_SQ_BottomOnly
};

/**
* Parsing mode type enumeration
*/
enum EParsingModeType
{
    E_PM_Normal,
    E_PM_ReplaceDelimiter
};

/**
* Special help type enumeration
*/
enum ESpecialHelpType
{
    E_SH_Designer,
    E_SH_Writer
};

/**
* Option type enumeration
*/
enum EOptionType
{
    E_OT_Application,
    E_OT_Yes,
    E_OT_No
};

/**
* Synchronization file type enumeration
*/
enum ESynchronizationFileType
{
    E_ST_AutomaticName,
    E_ST_FileNameSpecified,
    E_ST_FolderSpecified
};

/**
* Synchronization separator type enumeration
*/
enum ESynchronizationSeparatorType
{
    E_SS_Automatic,
    E_SS_Tab,
    E_SS_Comma,
    E_SS_SemiColumn,
    E_SS_Quote
};

/**
* Three state type enumeration
*/
enum EThreeState
{
    E_TS_False,
    E_TS_True,
    E_TS_Undefined
};

/**
* Install Component type enumeration
*/
enum EInstallComponentType
{
    E_IC_WindowsDirectory,
    E_IC_SystemDirectory,
    E_IC_ApplicationDirectory,
    E_IC_DefineDirectory
};

/**
* Model notations enumeration
*/
enum EModelNotation
{
    E_MN_ABC,
    E_MN_UML,
    E_MN_Beryl,
    E_MN_Unknown
};

// file version for the serialization
const UINT g_DefVersion = 1;

// Version 13 for 32bit compatibility
// Version 15 for DocumentType and Key1
// Version 16 for DisplayName in PSS_User class
// Version 17 for model compatibility and multi-activities
// Version 18 for zForms.01 Beta 2
// Version 18 for Conceptor Beta 1
// Version 19 for Conceptor Beta 2
// Version 20 for Conceptor Beta 3 and Release Conceptor/Sesterces
// Version 21 for Conceptor/Messenger Beta 1
// Version 22 for Conceptor Release 2005 - SP1
// Version 23 for Conceptor Release 2005 - SP2
// Version 24 for Conceptor Release 2006 - SP1
// Version 25 for Conceptor Release 2006 - SP2
// Version 26 for Conceptor Release 2007 - SP1 Prima
// Version 27 for Conceptor Release 2007 - SP1
const long g_VersionFile = 27;

// default object list
#define def_szObjectKey _T("Object")

const int     g_DefObjectCounter                   = 830;

const UINT    g_NoAlignement                       = 0x8000;

const CString g_NormalTemplateFileName             = _T("Normal.plf");
const CString g_NormalProcessTemplateFileName      = _T("Normal.wlf");
const CString g_NormalModelTemplateFileName        = _T("Normal.mlf");
const CString g_SystemSubDirectory                 = _T("System");
const CString g_UserDefinitionFileName             = _T("UserDef.txt");
const CString g_ActivityLogFileName                = _T("Activity.log");
const CString g_ActivityLogDatabase                = _T("Activity.mdb");
const CString g_HistoryProcessDatabase             = _T("Process.mdb");
const CString g_EventExtension                     = _T(".exp");
const CString g_EventMessageExtension              = _T(".mxp");
const CString g_EventTemporalExtension             = _T(".txp");
const CString g_ProcessDataFeedExtension           = _T(".slf");
const CString g_ProcessExtension                   = _T(".wlf");
const CString g_FormExtension                      = _T(".plf");
const CString g_ModelExtension                     = _T(".mlf");
const CString g_ReportExtension                    = _T(".rlf");
const CString g_WorkspaceExtension                 = _T(".klf");
const CString g_RiskTypeExtension                  = _T(".typ");
const CString g_RiskImpactExtension                = _T(".imp");
const CString g_RiskProbabilityExtension           = _T(".pro");
const CString g_EventExtensionNoDot                = _T("exp");
const CString g_EventMessageExtensionNoDot         = _T("mxp");
const CString g_EventDeleteExtensionNoDot          = _T("dxp");
const CString g_ProcessDataFeedExtensionNoDot      = _T("slf");
const CString g_ProcessExtensionNoDot              = _T("wlf");
const CString g_FormExtensionNoDot                 = _T("plf");
const CString g_ModelExtensionNoDot                = _T("mlf");
const CString g_ReportExtensionNoDot               = _T("rlf");
const CString g_WorkspaceExtensionNoDot            = _T("klf");
const CString g_DocumentExtensionListNoDot         = _T("doc;xls;ppt;htm;html");
const CString g_RiskTypeExtensionNoDot             = _T("typ");
const CString g_RiskImpactExtensionNoDot           = _T("imp");
const CString g_RiskProbabilityExtensionNoDot      = _T("pro");
const CString g_SearchAllProcessExtension          = _T("*.wlf");
const CString g_SearchAllFormExtension             = _T("*.plf");
const CString g_SearchAllModelExtension            = _T("*.mlf");

const UINT    g_ResponsibleUserNameIDResource      = 5008;  // IDS_RESPONSIBLEUSERNAMESTR
const UINT    g_RequestedUserNameIDResource        = 5009;  // IDS_REQUESTUSERNAMESTR

// declares the right sub menu item
const UINT    g_ObjectRightSubMenu                 = 0;
const UINT    g_GraphicRightSubMenu                = 1;
const UINT    g_AutoNumberedRightSubMenu           = 2;
const UINT    g_CalculatedRightSubMenu             = 3;
const UINT    g_NumberRightSubMenu                 = 4;
const UINT    g_BitmapRightSubMenu                 = 5;
const UINT    g_TwoStateRightSubMenu               = 6;
const UINT    g_BoundTextRightSubMenu              = 7;
const UINT    g_DateRightSubMenu                   = 8;
const UINT    g_MaskEditRightSubMenu               = 9;
const UINT    g_MultiColumnRightSubMenu            = 10;
const UINT    g_OnPageRightSubMenu                 = 11;
const UINT    g_OnDisplayFieldNameSubMenu          = 12;

// INI file implementation
const char    g_IniObjectCounterHistEntry[]        = _T("Nb of Obj Historic");
const char    g_OriginalSchema[]                   = _T("Standard");
const char    g_DefaultAssociationString[]         = _T("Défaut");

// constants used in export files
const char    g_ExportProcessNameKey[]             = _T("$$ProcessName$$");
const char    g_ExportTemplateNameKey[]            = _T("$$TemplateName$$");
const char    g_ExportFolderNameKey[]              = _T("$$FolderName$$");
const char    g_ExportFileNameKey[]                = _T("$$FileName$$");
const char    g_ExportProcessExchangeFileNameKey[] = _T("$$ProcessExchangeFileName$$");
const char    g_ExportKeepOnlyFLFKey[]             = _T("$$KeepOnlyFLF$$");

// this table contains the predefined fields known by the system. They are hard coded, because for each
// new field, the method should be added in the same time, and they are known only at this time
static char*  g_pPredefinedField[]                 = { _T("#Page#"), _T("#Date#"), NULL };

// constants to point the right element in the table of predefined fields
const int     g_PredefinedFieldPage                = 0;
const int     g_PredefinedFieldDate                = 1;

// constants used to load the resources for the Dlls
const int     g_ObjectDllFileName                  = 0;
const int     g_ObjectTitle                        = 1;
const int     g_ObjectExplanation                  = 2;
const int     g_ObjectCounter                      = 3;
const int     g_ObjectStartDefinition              = 4;

// constants used to load the formula resources for the Dlls
const int     g_FormulaCounter                     = 0;
const int     g_FormulaStartDefinition             = 1;

const int     g_LocateAllDocumentsEmptyOnly        = 8;
const int     g_LocateAllDocuments                 = 7;

const int     g_LocatePageOnlyEmptyOnly            = 6;
const int     g_LocateForwardPageEmptyOnly         = 5;
const int     g_LocateAllPagesEmptyOnly            = 4;

const int     g_LocatePageOnly                     = 3;
const int     g_LocateForwardPage                  = 2;
const int     g_LocateAllPages                     = 1;

const char    g_GlobalIniFileName[]                = _T("ZGlobal.ini");
const char    g_LocalIniFileName[]                 = _T("ZLocal.ini");
const char    g_RiskTypeFileName[]                 = _T("ZRiskTypeDefault.typ");
const char    g_RiskImpactFileName[]               = _T("ZRiskImpactDefault.imp");
const char    g_RiskProbabilityFileName[]          = _T("ZRiskProbabilityDefault.pro");
const char    g_LocalRefDirectory[]                = _T("\\LocalRef\\");
const char    g_RiskDirectory[]                    = _T("\\Risks\\");

const char    g_ActivityLogTableName[]             = _T("[ActivityLog]");
const char    g_HistoryProcessTableName[]          = _T("[HistoryProcess]");
const char    g_HistoryProcessStatusTableName[]    = _T("[HistoryProcessStatus]");
const char    g_HistoryActivityTableName[]         = _T("[HistoryActivity]");
const char    g_HistoryActivityStatusTableName[]   = _T("[HistoryActivityStatus]");
const char    g_HistoryFolderStatusTableName[]     = _T("[HistoryFolderStatus]");

// month constant definition
const int     g_IndexJanuary                       = 0;
const int     g_IndexFebruary                      = 1;
const int     g_IndexMarch                         = 2;
const int     g_IndexApril                         = 3;
const int     g_IndexMay                           = 4;
const int     g_IndexJune                          = 5;
const int     g_IndexJuly                          = 6;
const int     g_IndexAugust                        = 7;
const int     g_IndexSeptember                     = 8;
const int     g_IndexOctober                       = 9;
const int     g_IndexNovember                      = 10;
const int     g_IndexDecember                      = 11;

// rows and columns report constants
const int     g_NbRows                             = 60;
const int     g_NbColumns                          = 15;

// default page dimensions
const CSize   g_DefaultPaperSize(204, 280);
const short   g_DefaultStandardSize                = DMPAPER_A4;
const short   g_DefaultOrientation                 = DMORIENT_PORTRAIT;

#endif
