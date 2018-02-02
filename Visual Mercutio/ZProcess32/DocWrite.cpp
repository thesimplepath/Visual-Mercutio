//## begin module%35CC454D007B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%35CC454D007B.cm

//## begin module%35CC454D007B.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%35CC454D007B.cp

//## Module: DocWrite%35CC454D007B; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\DocWrite.cpp

//## begin module%35CC454D007B.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%35CC454D007B.additionalIncludes

// DocWrite
#include "DocWrite.h"
//## begin module%35CC454D007B.declarations preserve=no
//## end module%35CC454D007B.declarations

//## begin module%35CC454D007B.additionalDeclarations preserve=yes
#include "ZAApp.h"
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\ExpRT.h"
#include "zBaseLib\DocData.h"

#include "zBaseLib\Edit.h"

// FldMng
#include "zBaseLib\FldMng.h"

#include "zWinUtil32\newform.h"
#include "zWinUtil32\FoldInfo.h"

#include "zWinUtil32\DocOptDG.h"

#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	#include "formasc.h"
	#include "shcpydlg.h"
	#include "schcrtdl.h"
	#include "schname.h"
	#include "SelStyle.h"
	#include "styledef.h"
	#include "wzattach.h"
	// FrmMng
	#include "FrmMng.h"
#endif

#include "Resource.h"

// FileDlg
#include "zBaseLib\FileDlg.h"

#include <IO.H>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 11 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZDDocumentReadWrite, ZDDocument, def_Version )

BEGIN_MESSAGE_MAP( ZDDocumentReadWrite, ZDDocument )
	//{{AFX_MSG_MAP(ZDDocumentReadWrite)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_IMPORT, OnImport)
	ON_COMMAND(ID_EXPORT, OnExport)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	ON_COMMAND(ID_FILE_PROPERTY, OnFileProperty)
	ON_COMMAND(ID_FORMULA_SCENARIO_ASSOCIATE, OnFormulaScenarioAssociate)
	ON_COMMAND(ID_FORMULA_SCHEMA_COPY, OnFormulaScenarioCopy)
	ON_COMMAND(ID_FORMULA_SCHEMA_CREATION, OnFormulaScenarioCreation)
	ON_COMMAND(ID_FORMULA_SCHEMA_DELETE, OnFormulaScenarioDelete)
	ON_COMMAND(ID_PAGE_DELETE, OnPageDelete)
	ON_COMMAND(ID_FORM_ATTACH, OnFormAttach)
	ON_COMMAND(ID_FORM_MANAGE, OnFormManage)
	ON_COMMAND(ID_DEFINE_STYLE, OnDefineStyle)
	ON_COMMAND(ID_CHANGE_STYLE, OnChangeStyle)
	ON_COMMAND(ID_INSERTNEWPAGE, OnInsertNewPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//## end module%35CC454D007B.additionalDeclarations

// Class ZDDocumentReadWrite

ZDDocumentReadWrite::ZDDocumentReadWrite()
{
}

ZDDocumentReadWrite::~ZDDocumentReadWrite()
{
	//## begin ZDDocumentReadWrite::~ZDDocumentReadWrite%.body preserve=yes
	//## end ZDDocumentReadWrite::~ZDDocumentReadWrite%.body
}

//## begin ZDDocumentReadWrite%35CC443703C5.declarations preserve=yes

BOOL ZDDocumentReadWrite::OnNewDocument()
{
	ZAGlobal::SetpCurrentDocumentForSerialization( this );
	ZINewForm NewForm( &ZAGlobal::GetTemplateManager(), StartForm, FormType );

	if ( NewForm.DoModal() == IDCANCEL )
	{
		return FALSE;
	}

	if ( !OpenDocument( (const char*)NewForm.GetFileName(), FALSE ) )
	{
		return FALSE;
	}

	// Set the type for Document
	GetDocumentStamp().SetFileType( DocumentType );
	AssignPredefinedField();

	// Set the path name to empty
	m_strPathName.Empty();	// no path name yet
	ChangeCurrentSchema( GetStandardSchema(), TRUE );

	// Initialize the style list
	StyleListHasChanged();

	// Initialize the file list
	FileListHasChanged();

	// Set to the previous file directory
	ZAGlobal::SetToFileDirectory();

	if ( !StartRealTimeExport() )
	{
		// In write mode no chance, file corruption
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_RTEXPORT_CREATIONFAILED );
	}

	return TRUE;
}

BOOL ZDDocumentReadWrite::OnOpenDocument( const char* pszPathName )
{
	return ZDDocument::OnOpenDocument(pszPathName);
}

BOOL ZDDocumentReadWrite::OnSaveDocument( const char* pszPathName )
{
	BOOL bRetValue = TRUE;

	if ( !GetKeepOnlyFLF() )
	{
		// Set the last file name open
		if ( !DocumentIsTemplate() )
		{
			ZAApp::ZAGetApp()->SetLastLoadedFile( pszPathName );
		}

		bRetValue = CDocument::OnSaveDocument( pszPathName );

		// Change the document name
		SetPathName( pszPathName );
	}

	if ( !StartRealTimeExport( TRUE ) )
	{
		// In write mode no chance, file corruption
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_RTEXPORT_CREATIONFAILED );
	}

	return bRetValue;
}

BOOL ZDDocumentReadWrite::SaveModified()
{
	if ( !IsModified() )
	{
		return TRUE;	// ok to continue
	}

	if ( DocumentIsTemplate() )
	{
		return FALSE;
	}

	// get name/title of document
	CString name = m_strPathName;

	if ( name.IsEmpty() )
	{
		name = m_strTitle;

		if ( name.IsEmpty() )
		{
			VERIFY( name.LoadString( AFX_IDS_UNTITLED ) );
		}
	}

	// If this is the normal template, cannot be changed
	if ( m_strPathName.CompareNoCase( ZAApp::ZAGetApp()->GetNormalTemplate() ) == 0 )
	{
		return TRUE;
	}

	CString prompt;

	if ( DocumentIsTemplate() )
	{
		AfxFormatString1( prompt, IDP_ASK_TO_SAVE_TEMPLATE, name );
	}
	else
	{
		AfxFormatString1( prompt, IDP_ASK_TO_SAVE, name );
	}

	MsgBox mbox;

	switch( mbox.DisplayMsgBox( prompt ) )
	{
		case IDYES:
		{
			// If so, either Save or Update, as appropriate.
			if ( _access( m_strPathName, 6 ) != 0 && !GetKeepOnlyFLF() )
			{
				// If no access to the file in Read/Write
				if ( !DoSave( NULL ) )
				{
					// Don't continue.
					return FALSE;
				}
			}
			else
			{
				if ( !DoSave( m_strPathName ) )
				{
					// Don't continue
					return FALSE;
				}
			}

			break;
		}

		case IDNO:
		{
			// If not saving changes, revert the document
			break;
		}

		case IDCANCEL:
		{
			// Don't continue
			return FALSE;
		}

		default:
		{
			ASSERT( FALSE );
			break;
		}
	}

	// Keep going
	return TRUE;
}

void ZDDocumentReadWrite::OnExport()
{
	CString title;
	VERIFY( title.LoadString( IDS_EXPORTFILE_CHOOSETITLE ) );

	// set the "*.txt" files filter
	CString strFilter;
	VERIFY( strFilter.LoadString( IDS_EXPORTFILE_FILTER ) );

	strFilter += (char)'\0';	// next string please
	strFilter += _T( "*.txt" );
	strFilter += (char)'\0';	// last string

	// Append the "*.*" all files filter
	CString allFilter;
	VERIFY( allFilter.LoadString( AFX_IDS_ALLFILTER ) );

	strFilter += allFilter;
	strFilter += (char)'\0';	// next string please
	strFilter += _T( "*.*" );
	strFilter += (char)'\0';	// last string

	ZIFileDialog FileDialog( title, strFilter, 2, ZAApp::ZAGetApp()->GetFileDirectory() );

	if ( FileDialog.DoModal() == IDOK )
	{
		ZUDocumentExport ExportText( FileDialog.GetFilename(),
									 this,
									 GetDocOptions().GetSynchronizationHeader(),
									 GetDocOptions().GetSynchronizationSeparator(),
									 ZAApp::ZAGetApp()->GetExportSchemaName(),
									 ZAApp::ZAGetApp()->GetExportPropagationMode(),
									 ZAApp::ZAGetApp()->GetEmptyWhenZero() );

		ExportText.Export();
	}
}

void ZDDocumentReadWrite::OnImport()
{
	CString title;
	VERIFY( title.LoadString( IDS_IMPORTFILE_CHOOSETITLE ) );

	// set the "*.txt" files filter
	CString strFilter;
	VERIFY( strFilter.LoadString( IDS_EXPORTFILE_FILTER ) );

	strFilter += (char)'\0';	// next string please
	strFilter += _T( "*.txt" );
	strFilter += (char)'\0';	// last string

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY( allFilter.LoadString( AFX_IDS_ALLFILTER ) );

	strFilter += allFilter;
	strFilter += (char)'\0';	// next string please
	strFilter += _T( "*.*" );
	strFilter += (char)'\0';	// last string

	ZIFileDialog FileDialog( title, strFilter, 2, ZAApp::ZAGetApp()->GetFileDirectory() );

	if ( FileDialog.DoModal() == IDOK )
	{
		ZUDocumentExport ExportText( FileDialog.GetFilename(),
									 this,
									 GetDocOptions().GetSynchronizationHeader(),
									 GetDocOptions().GetSynchronizationSeparator(),
									 ZAApp::ZAGetApp()->GetExportSchemaName(),
									 ZAApp::ZAGetApp()->GetExportPropagationMode(),
									 ZAApp::ZAGetApp()->GetEmptyWhenZero() );

		ExportText.Import();

		// Recalculate formulas
		CalculateAllFormula( GetMainView(), TRUE );

		// Refresh the view
		UpdateAllViews( NULL );

		// Has been modified
		SetModifiedFlag();
	}
}

void ZDDocumentReadWrite::OnFileOptions()
{
#if defined( _ZDESIGNER )
	ZADocOptionDLG DocOptionDLG( &GetDocOptions() );

	// If option must be changed
	if ( DocOptionDLG.DoModal() == IDOK )
	{
		SetModifiedFlag( TRUE );
		UpdateAllViews( NULL );
	}
#endif // _ZDESIGNER
}

void ZDDocumentReadWrite::OnFileProperty()
{
	ZIFolderInformation FolderInformation( &GetDocumentStamp(), TRUE );
	FolderInformation.DoModal();
}

void ZDDocumentReadWrite::OnFileSave()
{
	if ( GetKeepOnlyFLF() )
	{
		// Export values
		if ( !StartRealTimeExport( TRUE ) )
		{
			// In write mode no chance, file corruption
			MsgBox mbox;
			mbox.DisplayMsgBox( IDS_RTEXPORT_CREATIONFAILED );
		}

		return;
	}

	CDocument::OnFileSave();

	// Initialize the file list
	FileListHasChanged();
}

void ZDDocumentReadWrite::OnFileSaveAs()
{
	if ( !GetKeepOnlyFLF() )
	{
		CDocument::OnFileSaveAs();
	}

	// Initialize the file list
	FileListHasChanged();
}

void ZDDocumentReadWrite::OnUpdateFileSave( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( IsModified() );
}

void ZDDocumentReadWrite::OnUpdateFileSaveAs( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( !GetKeepOnlyFLF() );
}

void ZDDocumentReadWrite::OnFormulaScenarioAssociate()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	PlanFinObject* pObj = GetSelectedObject();
	ZIFormulaAssociate FormulaAssociate( pObj );
	FormulaAssociate.DoModal();

	// Deselect all objects
	AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_DESELECTALLOBJECT );
#endif
}

void ZDDocumentReadWrite::OnFormulaScenarioCopy()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	ZDSchemaCopyDlg		SchemaCopyDlg;
	BOOL				bContinue;
	BOOL				bHasChanged = FALSE;

	SchemaCopyDlg.m_sCurrentSchema = GetCurrentSchema();

	do
	{
		bContinue = FALSE;

		if ( SchemaCopyDlg.DoModal() == IDOK )
		{
			// Test if the schema already exist
			if ( GetActiveDocumentData()->GetSchema().GetFormulaList( SchemaCopyDlg.m_sNewSchemaName ) )
			{
				MsgBox		mbox;
				CString 	prompt;

				AfxFormatString1( prompt, IDS_ALREADYEXIST_SCENARIO, GetCurrentSchema() );

				if ( mbox.DisplayMsgBox( prompt ) == IDYES )
				{
					bContinue = TRUE;
				}
			}
			else if ( !GetActiveDocumentData()->GetSchema().CopySchema( GetActiveDocumentData()->GetCurrentSchema(),
																		SchemaCopyDlg.m_sNewSchemaName ) )
			{
				MsgBox	mbox;
				CString	prompt;

				AfxFormatString1( prompt, IDS_UNABLETOCOPY_CURRENTSCENARIO, GetCurrentSchema() );

				if ( mbox.DisplayMsgBox( prompt ) == IDYES )
				{
					bContinue = TRUE;
				}
			}

			// Set the type and the description
			ZAFormulaSchema* pSource;
			pSource = (ZAFormulaSchema*)GetActiveDocumentData()->GetSchema().GetFormulaSchema( SchemaCopyDlg.m_sNewSchemaName );
			pSource->SetDescription( SchemaCopyDlg.m_sDescription );

			bHasChanged = TRUE;
		}
	}
	while ( bContinue );

	if ( bHasChanged )
	{
		ChangeCurrentSchema( SchemaCopyDlg.m_sNewSchemaName );
		SchemaListHasChanged();
	}
#endif
}

void ZDDocumentReadWrite::OnFormulaScenarioCreation()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	ZISchemaCreateDlg SchemaCreateDlg;
	
	if ( SchemaCreateDlg.DoModal() == IDOK )
	{
		// Create an empty one
		ZIEnterSchemaName	EnterSchemaName;
		BOOL				bContinue;

		do
		{
			bContinue = FALSE;

			if ( EnterSchemaName.DoModal() == IDOK )
			{
				// Test if the schema already exist
				if ( GetActiveDocumentData()->GetSchema().GetFormulaList( EnterSchemaName.m_sSchemaName ) ||
					 EnterSchemaName.m_sSchemaName.IsEmpty() )
				{
					MsgBox		mbox;
					CString 	prompt;

					AfxFormatString1( prompt, IDS_ALREADYEXIST_SCENARIO, GetCurrentSchema() );

					if ( mbox.DisplayMsgBox( prompt ) == IDYES )
					{
						bContinue = TRUE;
					}
				}
				else
				{
					GetActiveDocumentData()->GetSchema().Create( EnterSchemaName.m_sSchemaName );

					ZAFormulaSchema* pSource;

					pSource = (ZAFormulaSchema*)GetActiveDocumentData()->GetSchema().GetFormulaSchema( EnterSchemaName.m_sSchemaName );
					pSource->SetDescription( EnterSchemaName.m_sDescription );
				}
			}
			else
			{
				return;
			}
		}
		while ( bContinue );

		ChangeCurrentSchema( EnterSchemaName.m_sSchemaName );
		SchemaListHasChanged();
	}
	else
	{
		// Copy before a schema
		OnFormulaScenarioCopy();
	}
#endif
}

void ZDDocumentReadWrite::OnFormulaScenarioDelete()
{
	if ( GetCurrentSchema() == szOriginalSchema )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_CANNOTDELETE_ORIGINALSCENARIO, MB_OK );
	}
	else
	{
		MsgBox		mbox;
		CString 	prompt;

		AfxFormatString1( prompt, IDS_CONFIRMDELETION_CURRENTSCENARIO, GetCurrentSchema() );

		if ( mbox.DisplayMsgBox( prompt ) == IDYES )
		{
			GetActiveDocumentData()->GetSchema().DeleteFormulaList( GetActiveDocumentData()->GetCurrentSchema() );

			// Set the new current schema. By default, the original
			ChangeCurrentSchema( szOriginalSchema );
			SchemaListHasChanged();
		}
	}
}

void ZDDocumentReadWrite::OnChangeStyle()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	PlanFinObject* pObj = GetSelectedObject();

	if ( !pObj )
	{
		// Call the selector tool
		pObj = GetMainView()->ChooseObject();

		if ( pObj == NULL )
		{
			return;
		}
	}

	ZISelectStyleDlg SelectStyleDlg;

	if ( SelectStyleDlg.DoModal() == IDOK )
	{
		pObj->SethStyle( SelectStyleDlg.GetSelectedStyle() );
		UpdateAllViews( NULL );
		SetModifiedFlag();
	}
#endif
}

void ZDDocumentReadWrite::OnPageDelete()
{
	MsgBox mbox;

	switch( mbox.DisplayMsgBox( IDS_CONFIRMCURRENTPAGEDELETION, MB_YESNO ) )
	{
		case IDYES:
		{
			// Continue and delete page
			break;
		}

		case IDNO:
		{
			// Don't continue
			return;
		}

		default:
		{
			ASSERT( FALSE );
			break;
		}
	}

	if ( !DeletePage( GetCurrentPage() ) )
	{
		mbox.DisplayMsgBox( IDS_DELETEPAGE_ERROR );
	}
}

void ZDDocumentReadWrite::OnInsertNewPage()
{
	SetMaxPage( GetMaxPage() + 1 );
	UpdateAllViews( NULL );
}

void ZDDocumentReadWrite::OnDefineStyle()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	ZIStyleDefDlg StyleDefDlg;
	StyleDefDlg.DoModal();

	// Notify the combo to be changed.
	StyleListHasChanged();

	UpdateAllViews( NULL );
	SetModifiedFlag();
#endif
}

// Because one style has been deleted, all objects refering to this style must be redirected to Normal style
void ZDDocumentReadWrite::StyleHasBeenDeleted( HandleStyle hStyle, int DocumentIndex )
{
	if ( DocumentIndex == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		GetActiveDocumentData()->StyleHasBeenDeleted( hStyle );
		return;
	}

	ASSERT( GetDocumentDataAt( DocumentIndex ) );
	GetDocumentDataAt( DocumentIndex )->StyleHasBeenDeleted( hStyle );
}

void ZDDocumentReadWrite::SetCurrentStyle( const CString& sName, int DocumentIndex )
{
	if ( DocumentIndex == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		GetActiveDocumentData()->SetCurrentStyle( sName );
		return;
	}

	ASSERT( GetDocumentDataAt( DocumentIndex ) );
	GetDocumentDataAt( DocumentIndex )->SetCurrentStyle( sName );
}

BOOL ZDDocumentReadWrite::DeletePage( int iPage, int DocumentIndex )
{
	if ( DocumentIndex == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		return GetActiveDocumentData()->DeletePage( iPage );
	}

	ASSERT( GetDocumentDataAt( DocumentIndex ) );
	return GetDocumentDataAt( DocumentIndex )->DeletePage( iPage );
}

BOOL ZDDocumentReadWrite::CopyPage( ZDDocumentReadWrite*	pDocumentDst,
									int						iPage,
									int						DocumentIndexSource,
									int						DocumentIndexDest )
{
	if ( DocumentIndexSource == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		return GetActiveDocumentData()->CopyPage( pDocumentDst->GetDocumentDataAt(DocumentIndexDest), iPage );
	}

	ASSERT( GetDocumentDataAt( DocumentIndexSource ) );
	return GetDocumentDataAt( DocumentIndexSource )->CopyPage( pDocumentDst->GetDocumentDataAt( DocumentIndexDest ),
															   iPage );
}

BOOL ZDDocumentReadWrite::CopyPageOnlyObjects( ZDDocumentReadWrite*	pDocumentDst,
											   int					iPage,
											   int					DocumentIndexSource,
											   int					DocumentIndexDest )
{
	if ( DocumentIndexSource == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		return GetActiveDocumentData()->CopyPageOnlyObjects( pDocumentDst->GetDocumentDataAt( DocumentIndexDest ),
															 iPage );
	}

	ASSERT( GetDocumentDataAt( DocumentIndexSource ) );
	return GetDocumentDataAt( DocumentIndexSource )->CopyPageOnlyObjects( pDocumentDst->GetDocumentDataAt( DocumentIndexDest ), iPage );
}

BOOL ZDDocumentReadWrite::CopyPageOnlyFormula( ZDDocumentReadWrite*	pDocumentDst,
											   int					iPage,
											   int					DocumentIndexSource,
											   int					DocumentIndexDest )
{
	if ( DocumentIndexSource == -1 )
	{
		ASSERT( GetActiveDocumentData() );
		return GetActiveDocumentData()->CopyPageOnlyFormula( pDocumentDst->GetDocumentDataAt( DocumentIndexDest ),
															 iPage );
	}

	ASSERT( GetDocumentDataAt( DocumentIndexSource ) );
	return GetDocumentDataAt( DocumentIndexSource )->CopyPageOnlyFormula( pDocumentDst->GetDocumentDataAt( DocumentIndexDest ), iPage );
}

// Attach a new form
void ZDDocumentReadWrite::OnFormAttach()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	// Before starting the attach, test if the document has been modified.
	// If modified ask to save it
	if ( IsModified() )
	{
		CString	sFormat;
		char	szBuf[500];

		sFormat.LoadString( IDS_DOCUMENTMODIFIED_ASKCONFIRMATION_FORMATTACH );
		sprintf( szBuf, (const char*)sFormat, (const char*)m_strPathName );

		MsgBox mbox;

		switch ( mbox.DisplayMsgBox( szBuf ) )
		{
			case IDYES:
			{
				if ( !DoSave( m_strPathName ) )
				{
					// Don't continue
					return;
				}

				break;
			}

			case IDNO:
			{
				SetModifiedFlag( FALSE );
				break;
			}

			case IDCANCEL:
			{
				// Don't continue
				return;
			}

			default:
			{
				ASSERT( FALSE );
				break;
			}
		}
	}

	ZIWizardAttachForm	WizardAttachForm( this );

	if ( WizardAttachForm.DoModal() != IDOK )
	{
		return;
	}
#endif
}

void ZDDocumentReadWrite::MoveContents( ZDDocumentReadWrite*	pDocument,
										BOOL					bCopyFormat,
										int						DocumentIndexSource,
										int						DocumentIndexDest )
{
	if ( DocumentIndexSource == -1 )
	{
		if ( GetActiveDocumentData() && pDocument->GetActiveDocumentData() )
		{
			GetActiveDocumentData()->MoveContents( pDocument->GetActiveDocumentData(), bCopyFormat );
		}

		return;
	}

	if ( GetDocumentDataAt( DocumentIndexSource ) && pDocument->GetDocumentDataAt( DocumentIndexDest ) )
	{
		GetDocumentDataAt( DocumentIndexSource )->MoveContents( pDocument->GetDocumentDataAt( DocumentIndexDest ),
																bCopyFormat );
	}
}

BOOL ZDDocumentReadWrite::BuildTemplateName( CString& str )
{
	return ZAApp::ZAGetApp()->BuildTemplateName( str, GetActiveDocumentData()->GetStamp() );
}

void ZDDocumentReadWrite::OnFormManage()
{
#if defined( _ZDESIGNER ) || defined( _ZSCRIPTOR )
	ZIManageForms ManageForms;
	ManageForms.DoModal();
#endif
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocumentReadWrite diagnostics

#ifdef _DEBUG
void ZDDocumentReadWrite::AssertValid() const
{
	CDocument::AssertValid();
}

void ZDDocumentReadWrite::Dump( CDumpContext& dc ) const
{
	CDocument::Dump( dc );
}
#endif //_DEBUG
