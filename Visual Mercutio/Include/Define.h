// This file define the different type used
// within the PlanFin application

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

#ifndef Define_h
#define Define_h 1

#ifndef _WIN32
// Assign the zero time for the system
static CTime		m_ZeroTime( 1970, 01, 01, 12, 00, 00 );
#else
// Assign the zero time for the system
static COleDateTime	m_ZeroTime( 1970, 01, 01, 12, 00, 00 );
#endif

// Define different type for Class PLFNCheck
enum CheckButtonType
{
	Rounded,
	Squared
};

// Define different type
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

// Define different type
enum FormatType
{
	Percentage			= '%',
	Date				= 'd',
	Date1				= '1',
	Date2				= '2',
	Date3				= '3',
	Date4				= '4',
	Date5				= '5',
	Date6				= '6',
	Amount				= 'a',
	Amount1				= 'b',
	Amount2				= 'c',
	Amount1Dash			= 'v',
	Amount2Dash			= 'w',
	Amount1DashTrail	= 'x',
	Amount2DashTrail	= 'y',
	Standard			= 'n'
};

// Define different type of line
enum LineType
{
	AutomaticLine,
	NoLine,
	DottedLine,
	SolidLine,
	DashLine,
	SmallLine
};

// Define different type of squares
enum SquareType
{
	NormalSquare,
	TopSquareOnly,
	BottomSquareOnly
};

// Define different type of squares
enum ParsingModeType
{
	NormalParsing,
	ReplaceDelimiterParsing
};

// Define different special help type
enum SpecialHelpType
{
	DesignerSH,
	WriterSH
};

// Define the three different option types
enum OptionType
{
	ApplicationOption,
	YesOption,
	NoOption
};

// Synchronization filename type
enum SynchronizationFileType
{
	AutomaticName,
	FilenameSpecified,
	FolderSpecified
};

// Synchronization filename type
enum SynchronizationSeparatorType
{
	AutomaticSeparator,
	TabSeparator,
	CommaSeparator,
	SemiColumnSeparator,
	QuoteSeparator
};

// Define the three state type
enum ThreeState
{
	FalseState,
	TrueState,
	UndefinedState
};

// Define the Install Component type
enum InstallComponentType
{
	WindowsDirectory,
	SystemDirectory,
	ApplicationDirectory,
	DefineDirectory
};

// Model Notations
enum ModelNotation
{
	ABCNotation,
	UMLNotation,
	BerylNotation,
	UnknownNotation
};

// Define the version of the file for the serialization
const UINT		def_Version		= 1;
const long		lVersionFile	= 27;	// Version 13 for 32bit compatibility
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

// The default object list
#define			def_szObjectKey							_T( "Object" )

const int		def_iObjectCounter						= 830;

const UINT		NoAlignement							= 0x8000;

const CString	sNormalTemplateFilename					= _T( "Normal.plf" );
const CString	sNormalProcessTemplateFilename			= _T( "Normal.wlf" );
const CString	sNormalModelTemplateFilename			= _T( "Normal.mlf" );
const CString	sSystemSubDirectory						= _T( "System" );
const CString	sUserDefinitionFilename					= _T( "UserDef.txt" );
const CString	sActivityLogFilename					= _T( "Activity.log" );
const CString	sActivityLogDatabase					= _T( "Activity.mdb" );
const CString	sHistoryProcessDatabase					= _T( "Process.mdb" );
const CString	sEventExtension							= _T( ".exp" );
const CString	sEventMessageExtension					= _T( ".mxp" );
const CString	sEventTemporalExtension					= _T( ".txp" );
const CString	sProcessDataFeedExtension				= _T( ".slf" );
const CString	sProcessExtension						= _T( ".wlf" );
const CString	sFormExtension							= _T( ".plf" );
const CString	sModelExtension							= _T( ".mlf" );
const CString	sReportExtension						= _T( ".rlf" );
const CString	sWorkspaceExtension						= _T( ".klf" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension .typ pour les fichiers de type des risques.
const CString	sRiskTypeExtension						= _T( ".typ" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension .imp pour les fichiers d'impact des risques.
const CString	sRiskImpactExtension					= _T( ".imp" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension .pro pour les fichiers de probabilités des risques.
const CString	sRiskProbabilityExtension				= _T( ".pro" );
const CString	sEventExtensionNoDot					= _T( "exp" );
const CString	sEventMessageExtensionNoDot				= _T( "mxp" );
const CString	sEventDeleteExtensionNoDot				= _T( "dxp" );
const CString	sProcessDataFeedExtensionNoDot			= _T( "slf" );
const CString	sProcessExtensionNoDot					= _T( "wlf" );
const CString	sFormExtensionNoDot						= _T( "plf" );
const CString	sModelExtensionNoDot					= _T( "mlf" );
const CString	sReportExtensionNoDot					= _T( "rlf" );
const CString	sWorkspaceExtensionNoDot				= _T( "klf" );
const CString	sDocumentExtensionListNoDot				= _T( "doc;xls;ppt;htm;html" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension typ pour les fichiers de type des risques.
const CString	sRiskTypeExtensionNoDot					= _T( "typ" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension imp pour les fichiers d'impact des risques.
const CString	sRiskImpactExtensionNoDot				= _T( "imp" );
// JMR-MODIF - Le 16 juillet 2007 - Ajout de l'extension pro pour les fichiers de probabilités des risques.
const CString	sRiskProbabilityExtensionNoDot			= _T( "pro" );

const CString	sSearchAllProcessExtension				= _T( "*.wlf" );
const CString	sSearchAllFormExtension					= _T( "*.plf" );
const CString	sSearchAllModelExtension				= _T( "*.mlf" );

const UINT		ResponsibleUserNameIDResource			= 5008;  // IDS_RESPONSIBLEUSERNAMESTR
const UINT		RequestedUserNameIDResource				= 5009;  // IDS_REQUESTUSERNAMESTR

// Declares the right sub menu item
const UINT		ObjectRightSubMenu						= 0;
const UINT		GraphicRightSubMenu						= 1;
const UINT		AutoNumberedRightSubMenu				= 2;
const UINT		CalculatedRightSubMenu					= 3;
const UINT		NumberRightSubMenu						= 4;
const UINT		BitmapRightSubMenu						= 5;
const UINT		TwoStateRightSubMenu					= 6;
const UINT		BoundTextRightSubMenu					= 7;
const UINT		DateRightSubMenu						= 8;
const UINT		MaskEditRightSubMenu					= 9;
const UINT		MultiColumnRightSubMenu					= 10;
const UINT		OnPageRightSubMenu						= 11;
const UINT		OnDisplayFieldNameSubMenu				= 12;

/////////////////////////////////////////////////////////////////////////////
// INI file implementation
const char		szIniObjectCounterHistEntry[]			= _T( "Nb of Obj Historic" );
const char		szOriginalSchema[]						= _T( "Standard" );
const char		szDefaultAssociationString[]			= _T( "Défaut" );

// Constants used in export files
const char		szExportProcessNameKey[]				= _T( "$$ProcessName$$" );
const char		szExportTemplateNameKey[]				= _T( "$$TemplateName$$" );
const char		szExportFolderNameKey[]					= _T( "$$FolderName$$" );
const char		szExportFileNameKey[]					= _T( "$$FileName$$" );
const char		szExportProcessExchangeFileNameKey[]	= _T( "$$ProcessExchangeFileName$$" );
const char		szExportKeepOnlyFLFKey[]				= _T( "$$KeepOnlyFLF$$" );

// This table represent the predefined field
// that the system knows
// This is hard coded only because for each
// new fields you must program the method
// and only in programming method you can
// add new fields.
static char		*mszpPredefinedField[]					= { _T( "#Page#" ), _T( "#Date#" ), NULL };

// This constant points to the right
// element in the table of predefined
// fields.
const int		PREDFIELD_PAGE							= 0;
const int		PREDFIELD_DATE							= 1;

// These constants are used to load object resources
// for object Dlls
const int		OBJECT_DLLFILENAME						= 0;
const int		OBJECT_TITLE							= 1;
const int		OBJECT_EXPLANATION						= 2;
const int		OBJECT_COUNTER							= 3;
const int		OBJECT_STARTDEFINITION					= 4;

// These constants are used to load formula resources
// for object Dlls
const int		FORMULA_COUNTER							= 0;
const int		FORMULA_STARTDEFINITION					= 1;

const int		LocateAllDocumentsEmptyOnly				= 8;
const int		LocateAllDocuments						= 7;

const int		LocatePageOnlyEmptyOnly					= 6;
const int		LocateForwardPageEmptyOnly				= 5;
const int		LocateAllPagesEmptyOnly					= 4;

const int		LocatePageOnly							= 3;
const int		LocateForwardPage						= 2;
const int		LocateAllPages							= 1;

const char		szGlobalIniFilename[]					= _T( "ZGlobal.ini" );
const char		szLocalIniFilename[]					= _T( "ZLocal.ini" );
// JMR-MODIF - Le 8 juillet 2007 - Nouveau fichier pour les entrées utilisateurs du paramètre "Risque"
const char		szRiskTypeFilename[]					= _T( "ZRiskTypeDefault.typ" );
// JMR-MODIF - Le 11 juillet 2007 - Nouveau fichier pour les entrées utilisateurs du paramètre "Impact"
const char		szRiskImpactFilename[]					= _T( "ZRiskImpactDefault.imp" );
// JMR-MODIF - Le 11 juillet 2007 - Nouveau fichier pour les entrées utilisateurs du paramètre "Probabilité"
const char		szRiskProbabilityFilename[]				= _T( "ZRiskProbabilityDefault.pro" );
// JMR-MODIF - Le 16 juillet 2007 - Répertoire pour le référentiel local.
const char		szLocalRefDirectory[]					= _T( "\\LocalRef\\" );
// JMR-MODIF - Le 16 juillet 2007 - Répertoire pour les risques.
const char		szRiskDirectory[]						= _T( "\\Risks\\" );

const char		ActivityLogTableName[]					= _T( "[ActivityLog]" );
const char		HistoryProcessTableName[]				= _T( "[HistoryProcess]" );
const char		HistoryProcessStatusTableName[]			= _T( "[HistoryProcessStatus]" );
const char		HistoryActivityTableName[]				= _T( "[HistoryActivity]" );
const char		HistoryActivityStatusTableName[]		= _T( "[HistoryActivityStatus]" );
const char		HistoryFolderStatusTableName[]			= _T( "[HistoryFolderStatus]" );

/////////////////////////////////////////////////////////////////////////////
// Month constant definition
const int		IndexJanuary							= 0;
const int		IndexFebruary							= 1;
const int		IndexMarch								= 2;
const int		IndexApril								= 3;
const int		IndexMay								= 4;
const int		IndexJune								= 5;
const int		IndexJuly								= 6;
const int		IndexAugust								= 7;
const int		IndexSeptember							= 8;
const int		IndexOctober							= 9;
const int		IndexNovember							= 10;
const int		IndexDecember							= 11;

/////////////////////////////////////////////////////////////////////////////
// Rows and columns report constants.
// JMR-MODIF - Le 29 juin 2005 - Ajout des constantes pour les rapports
const int		nbRows									= 60;
const int		nbColumns								= 15;

/////////////////////////////////////////////////////////////////////////////
// Dimensions des pages par défaut.
// JMR-MODIF - Le 18 juillet 2005 - Ajout des constantes pour les dimensions de pages.
const CSize		DefaultPaperSize						= CSize( 204, 280 );
const short		DefaultStandardSize						= DMPAPER_A4;
const short		DefaultOrientation						= DMORIENT_PORTRAIT;

#endif