/****************************************************************************
 * ==> Defines -------------------------------------------------------------*
 ****************************************************************************
 * Description : This file define the different type used within the        *
 *               PlanFin application                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef DefineH
#define DefineH

// assign the system zero time
#ifndef _WIN32
    static CTime        m_ZeroTime(1970, 01, 01, 12, 00, 00);
#else
    #include <atlcomtime.h>

    // assign the system zero time
    static COleDateTime m_ZeroTime(1970, 01, 01, 12, 00, 00);
#endif

// windows
#include <atltypes.h>

/**
* Button type enumeration
*/
enum CheckButtonType
{
    Rounded,
    Squared
};

/**
* Class type enumeration
*/
enum ClassType
{
    Rect,
    Line,
    Static,
    Numbered,
    NumbEdit,
    NumbNumEdit,
    String,
    StringHistory,
    NumHistory,
    Time,
    Int,
    Word,
    Long,
    Calculated,
    Nothing,
    AllObjects,
    ExportedSVM,
    Text,
    Graphic
};

/**
* Format type enumeration
*/
enum FormatType
{
    Percentage       = '%',
    Date             = 'd',
    Date1            = '1',
    Date2            = '2',
    Date3            = '3',
    Date4            = '4',
    Date5            = '5',
    Date6            = '6',
    Amount           = 'a',
    Amount1          = 'b',
    Amount2          = 'c',
    Amount1Dash      = 'v',
    Amount2Dash      = 'w',
    Amount1DashTrail = 'x',
    Amount2DashTrail = 'y',
    Standard         = 'n'
};

/**
* Line type enumeration
*/
enum LineType
{
    AutomaticLine,
    NoLine,
    DottedLine,
    SolidLine,
    DashLine,
    SmallLine
};

/**
* Square type enumeration
*/
enum SquareType
{
    NormalSquare,
    TopSquareOnly,
    BottomSquareOnly
};

/**
* Parsing mode type enumeration
*/
enum ParsingModeType
{
    NormalParsing,
    ReplaceDelimiterParsing
};

/**
* Special help type enumeration
*/
enum SpecialHelpType
{
    DesignerSH,
    WriterSH
};

/**
* Option type enumeration
*/
enum OptionType
{
    ApplicationOption,
    YesOption,
    NoOption
};

/**
* Synchronization file type enumeration
*/
enum SynchronizationFileType
{
    AutomaticName,
    FilenameSpecified,
    FolderSpecified
};

/**
* Synchronization separator type enumeration
*/
enum SynchronizationSeparatorType
{
    AutomaticSeparator,
    TabSeparator,
    CommaSeparator,
    SemiColumnSeparator,
    QuoteSeparator
};

/**
* Three state type enumeration
*/
enum ThreeState
{
    FalseState,
    TrueState,
    UndefinedState
};

/**
* Install Component type enumeration
*/
enum InstallComponentType
{
    WindowsDirectory,
    SystemDirectory,
    ApplicationDirectory,
    DefineDirectory
};

/**
* Model notations enumeration
*/
enum ModelNotation
{
    ABCNotation,
    UMLNotation,
    BerylNotation,
    UnknownNotation
};

// file version for the serialization
const UINT def_Version  = 1;
const long lVersionFile = 27; // Version 13 for 32bit compatibility
                              // Version 15 for DocumentType and Key1
                              // Version 16 for DisplayName in ZUser class
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

// default object list
#define def_szObjectKey _T("Object")

const int     def_iObjectCounter                   = 830;

const UINT    NoAlignement                         = 0x8000;

const CString sNormalTemplateFilename              = _T("Normal.plf");
const CString sNormalProcessTemplateFilename       = _T("Normal.wlf");
const CString sNormalModelTemplateFilename         = _T("Normal.mlf");
const CString sSystemSubDirectory                  = _T("System");
const CString sUserDefinitionFilename              = _T("UserDef.txt");
const CString sActivityLogFilename                 = _T("Activity.log");
const CString sActivityLogDatabase                 = _T("Activity.mdb");
const CString sHistoryProcessDatabase              = _T("Process.mdb");
const CString sEventExtension                      = _T(".exp");
const CString sEventMessageExtension               = _T(".mxp");
const CString sEventTemporalExtension              = _T(".txp");
const CString sProcessDataFeedExtension            = _T(".slf");
const CString sProcessExtension                    = _T(".wlf");
const CString sFormExtension                       = _T(".plf");
const CString sModelExtension                      = _T(".mlf");
const CString sReportExtension                     = _T(".rlf");
const CString sWorkspaceExtension                  = _T(".klf");
const CString sRiskTypeExtension                   = _T(".typ");
const CString sRiskImpactExtension                 = _T(".imp");
const CString sRiskProbabilityExtension            = _T(".pro");
const CString sEventExtensionNoDot                 = _T("exp");
const CString sEventMessageExtensionNoDot          = _T("mxp");
const CString sEventDeleteExtensionNoDot           = _T("dxp");
const CString sProcessDataFeedExtensionNoDot       = _T("slf");
const CString sProcessExtensionNoDot               = _T("wlf");
const CString sFormExtensionNoDot                  = _T("plf");
const CString sModelExtensionNoDot                 = _T("mlf");
const CString sReportExtensionNoDot                = _T("rlf");
const CString sWorkspaceExtensionNoDot             = _T("klf");
const CString sDocumentExtensionListNoDot          = _T("doc;xls;ppt;htm;html");
const CString sRiskTypeExtensionNoDot              = _T("typ");
const CString sRiskImpactExtensionNoDot            = _T("imp");
const CString sRiskProbabilityExtensionNoDot       = _T("pro");
const CString sSearchAllProcessExtension           = _T("*.wlf");
const CString sSearchAllFormExtension              = _T("*.plf");
const CString sSearchAllModelExtension             = _T("*.mlf");

const UINT    ResponsibleUserNameIDResource        = 5008;  // IDS_RESPONSIBLEUSERNAMESTR
const UINT    RequestedUserNameIDResource          = 5009;  // IDS_REQUESTUSERNAMESTR

// declares the right sub menu item
const UINT    ObjectRightSubMenu                   = 0;
const UINT    GraphicRightSubMenu                  = 1;
const UINT    AutoNumberedRightSubMenu             = 2;
const UINT    CalculatedRightSubMenu               = 3;
const UINT    NumberRightSubMenu                   = 4;
const UINT    BitmapRightSubMenu                   = 5;
const UINT    TwoStateRightSubMenu                 = 6;
const UINT    BoundTextRightSubMenu                = 7;
const UINT    DateRightSubMenu                     = 8;
const UINT    MaskEditRightSubMenu                 = 9;
const UINT    MultiColumnRightSubMenu              = 10;
const UINT    OnPageRightSubMenu                   = 11;
const UINT    OnDisplayFieldNameSubMenu            = 12;

// INI file implementation
const char    szIniObjectCounterHistEntry[]        = _T("Nb of Obj Historic");
const char    szOriginalSchema[]                   = _T("Standard");
const char    szDefaultAssociationString[]         = _T("Défaut");

// constants used in export files
const char    szExportProcessNameKey[]             = _T("$$ProcessName$$");
const char    szExportTemplateNameKey[]            = _T("$$TemplateName$$");
const char    szExportFolderNameKey[]              = _T("$$FolderName$$");
const char    szExportFileNameKey[]                = _T("$$FileName$$");
const char    szExportProcessExchangeFileNameKey[] = _T("$$ProcessExchangeFileName$$");
const char    szExportKeepOnlyFLFKey[]             = _T("$$KeepOnlyFLF$$");

// this table contains the predefined fields known by the system. They are hard coded, because for each
// new field, the method should be added in the same time, and they are known only at this time
static char*  mszpPredefinedField[]                = { _T("#Page#"), _T("#Date#"), NULL };

// constants to point the right element in the table of predefined fields
const int     PREDFIELD_PAGE                       = 0;
const int     PREDFIELD_DATE                       = 1;

// constants used to load the resources for the Dlls
const int     OBJECT_DLLFILENAME                   = 0;
const int     OBJECT_TITLE                         = 1;
const int     OBJECT_EXPLANATION                   = 2;
const int     OBJECT_COUNTER                       = 3;
const int     OBJECT_STARTDEFINITION               = 4;

// constants used to load the formula resources for the Dlls
const int     FORMULA_COUNTER                      = 0;
const int     FORMULA_STARTDEFINITION              = 1;

const int     LocateAllDocumentsEmptyOnly          = 8;
const int     LocateAllDocuments                   = 7;

const int     LocatePageOnlyEmptyOnly              = 6;
const int     LocateForwardPageEmptyOnly           = 5;
const int     LocateAllPagesEmptyOnly              = 4;

const int     LocatePageOnly                       = 3;
const int     LocateForwardPage                    = 2;
const int     LocateAllPages                       = 1;

const char    szGlobalIniFilename[]                = _T("ZGlobal.ini");
const char    szLocalIniFilename[]                 = _T("ZLocal.ini");
const char    szRiskTypeFilename[]                 = _T("ZRiskTypeDefault.typ");
const char    szRiskImpactFilename[]               = _T("ZRiskImpactDefault.imp");
const char    szRiskProbabilityFilename[]          = _T("ZRiskProbabilityDefault.pro");
const char    szLocalRefDirectory[]                = _T("\\LocalRef\\");
const char    szRiskDirectory[]                    = _T("\\Risks\\");

const char    ActivityLogTableName[]               = _T("[ActivityLog]");
const char    HistoryProcessTableName[]            = _T("[HistoryProcess]");
const char    HistoryProcessStatusTableName[]      = _T("[HistoryProcessStatus]");
const char    HistoryActivityTableName[]           = _T("[HistoryActivity]");
const char    HistoryActivityStatusTableName[]     = _T("[HistoryActivityStatus]");
const char    HistoryFolderStatusTableName[]       = _T("[HistoryFolderStatus]");

// month constant definition
const int     IndexJanuary                         = 0;
const int     IndexFebruary                        = 1;
const int     IndexMarch                           = 2;
const int     IndexApril                           = 3;
const int     IndexMay                             = 4;
const int     IndexJune                            = 5;
const int     IndexJuly                            = 6;
const int     IndexAugust                          = 7;
const int     IndexSeptember                       = 8;
const int     IndexOctober                         = 9;
const int     IndexNovember                        = 10;
const int     IndexDecember                        = 11;

// rows and columns report constants
const int     nbRows                               = 60;
const int     nbColumns                            = 15;

// default page dimensions
const CSize   DefaultPaperSize(204, 280);
const short   DefaultStandardSize                  = DMPAPER_A4;
const short   DefaultOrientation                   = DMORIENT_PORTRAIT;

#endif