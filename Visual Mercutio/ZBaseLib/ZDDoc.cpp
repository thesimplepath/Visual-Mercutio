//## begin module%35CC30710249.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%35CC30710249.cm

//## begin module%35CC30710249.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%35CC30710249.cp

//## Module: ZDDoc%35CC30710249; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZDDoc.cpp

//## begin module%35CC30710249.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%35CC30710249.additionalIncludes

//## begin module%35CC30710249.includes preserve=yes
//## end module%35CC30710249.includes

// ZDDoc
#include "ZDDoc.h"

// DocData
#include "DocData.h"

#include "PlanfObj.h"
#include "ZABnText.h"
#include "ZARadio.h"
#include "ZACheck.h"
#include "ZABitmap.h"
#include "ZASquare.h"
#include "ZAMStr.h"
#include "ZAMultiC.h"
#include "ZANumbrd.h"
#include "Obsolete.h"
#include "MsgBox.h"

#include "ZIView.h"
#include "ZIHtmlView.h"
#include "Edit.h"

// ExpRT
#include "ExpRT.h"

#include "ZAGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 25 avril 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZDDocument, ZDBaseDocument, def_Version )

BEGIN_MESSAGE_MAP( ZDDocument, ZDBaseDocument )
    //{{AFX_MSG_MAP(ZDDocument)
    ON_COMMAND(ID_PAGE_RECALCULATE, OnPageRecalculate)
    ON_COMMAND(ID_PAGE_NEXT, OnPageNext)
    ON_COMMAND(ID_PAGE_PREV, OnPagePrev)
    ON_UPDATE_COMMAND_UI(ID_PAGE_PREV, OnUpdatePagePrev)
    ON_UPDATE_COMMAND_UI(ID_PAGE_NEXT, OnUpdatePageNext)
    ON_COMMAND(ID_PAGE_REFRESH, OnPageRefresh)
    ON_COMMAND(ID_FILE_NEXT, OnFileNext)
    ON_UPDATE_COMMAND_UI(ID_FILE_NEXT, OnUpdateFileNext)
    ON_COMMAND(ID_FILE_PREV, OnFilePrev)
    ON_UPDATE_COMMAND_UI(ID_FILE_PREV, OnUpdateFilePrev)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//## end module%35CC30710249.additionalDeclarations

////////////////////////////////////////////////////////////////////////////////
// Class ZDDocument

ZDDocument::ZDDocument()
    : m_pRealTimeExport            ( NULL ),
      m_ActiveDocumentIndex        ( -1 ),
      m_bShowHiddenField        ( FALSE ),
      m_bPrintLine                ( TRUE ),
      m_VisibleDocumentDataCount( 0 ),
      m_iObjectCounter            ( 0 ),
      m_KeepOnlyFLF                ( FALSE ),
      m_pClipBoardObject        ( NULL ),
      m_strEdit                    ( NULL )
{
}

ZDDocument::~ZDDocument()
{
    if ( m_pRealTimeExport )
    {
        m_pRealTimeExport->EndSynchronization();
        delete m_pRealTimeExport;
    }

    // Delete All created temporary files
    DeleteAllTemporaryFiles();

    // Delete all document data
    RemoveAllDocumentData();

    // Destroy the clipboard
    if ( m_pClipBoardObject )
    {
        delete m_pClipBoardObject;
    }

    // Delete the edit control
    if( m_strEdit )
    {
        delete m_strEdit;
    }
}

BOOL ZDDocument::OpenDocument( const char* pszPathName, BOOL bSetLastLoaded )
{
    ZAGlobal::SetpCurrentDocumentForSerialization( this );

    CWaitCursor Cursor;

    if ( !CDocument::OnOpenDocument( pszPathName ) )
    {
        return FALSE;
    }

    SetPathName( pszPathName );

    // If the list of formula is empty
    // then load the standard list of formula
    if ( GetActiveDocumentData()                &&
         GetActiveDocumentData()->IsFormData()    &&
        !GetActiveDocumentData()->GetSchema().GetFormulaList( GetCurrentSchema() ) )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_FILECORRUPTED, MB_OK );
        return FALSE;
    }

    // Because in the previous versions, the Calculated fields
    // and the Number have different classes, it is necessary
    // to replace calculated fields with number fields with a flag.        
    if ( GetActiveDocumentData() && GetActiveDocumentData()->GetStamp().GetInternalVersion() < 1 )
    {
        ReplaceCalculatedFields();
    }

    if ( !ZAGlobal::OpenFileInSilentMode() )
    {
        CalculateAllFormula( GetMainView(), TRUE );

        // Start the timer for the first time.
        StartCalcTimer();

        // Count all pages for all document data
        DocumentCountAndSetPages();
        SchemaListHasChanged();

        // Initialize the style list
        StyleListHasChanged();

        // Initialize the file list
        FileListHasChanged();

        // Set the current file list
        ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );

        // Go to the first page
        SetCurrentPage( 1 );

        if ( !StartRealTimeExport() )
        {
            // In write mode no chance, file corruption
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_RTEXPORT_CREATIONFAILED );
        }
    }

    return TRUE;
}

//## Other Operations (implementation)
ZAFormula* ZDDocument::GetFormula( const CString& sName, int DocumentIndex )
{
    //## begin ZDDocument::GetFormula%902943940.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetFormula( sName );
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetFormula( sName );
    //## end ZDDocument::GetFormula%902943940.body
}

PlanFinObject* ZDDocument::GetObjectPtr( CString& strName, int DocumentIndex )
{
    //## begin ZDDocument::GetObjectPtr%902943941.body preserve=yes
    if (DocumentIndex == -1)
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetObjectPtr( strName );
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetObjectPtr( strName );
    //## end ZDDocument::GetObjectPtr%902943941.body
}

PlanFinObject* ZDDocument::GetSelectedObject( BOOL bCheckPage, int DocumentIndex )
{
    //## begin ZDDocument::GetSelectedObject%908460235.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->GetSelectedObject( bCheckPage );
        }

        return NULL;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetSelectedObject( bCheckPage );
    }

    return NULL;
    //## end ZDDocument::GetSelectedObject%908460235.body
}

void ZDDocument::CheckFormulaObject( PlanFinObject* pOld, PlanFinObject* pNew, int DocumentIndex )
{
    //## begin ZDDocument::CheckFormulaObject%908620919.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->CheckFormulaObject( pOld, pNew );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->CheckFormulaObject( pOld, pNew );
    }
    //## end ZDDocument::CheckFormulaObject%908620919.body
}

BOOL ZDDocument::ObjectExist( const CString sName, int DocumentIndex )
{
    //## begin ZDDocument::ObjectExist%908620921.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->ObjectExist( sName );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->ObjectExist( sName );
    }

    return FALSE;
    //## end ZDDocument::ObjectExist%908620921.body
}

ZIView* ZDDocument::GetMainView()
{
    //## begin ZDDocument::GetMainView%910434310.body preserve=yes
    POSITION    pos        = GetFirstViewPosition();
    CView*        pView    = GetNextView( pos );

    while ( pView )
    {
        if ( pView->IsKindOf( RUNTIME_CLASS( ZIView ) ) )
        {
            return (ZIView*)pView;
        }

        pView = GetNextView( pos );
    }

    return NULL;
    //## end ZDDocument::GetMainView%910434310.body
}

BOOL ZDDocument::StartRealTimeExport( BOOL Export, BOOL Import )
{
    //## begin ZDDocument::StartRealTimeExport%926842804.body preserve=yes
    // Tests if it is necessary to create a real time synchro
    // No templates
    // ExchangeFeedFile required
    if ( !DocumentIsTemplate() && GetDocOptions().GetIsSynchronizeExchangeFeedFile() )
    {
        if ( !IsRealTimeExported() )
        {
            // Create the real time export process.
            if ( !CreateRealTimeExport() )
            {
                return FALSE;
            }
        }

        if ( Export )
        {
            if ( GetpRealTimeExport() )
            {
                // Export
                GetpRealTimeExport()->Export();
            }
        }

        if ( Import )
        {
            if ( GetpRealTimeExport() )
            {
                // Import
                GetpRealTimeExport()->Import();
            }
        }
    }

    return TRUE;
    //## end ZDDocument::StartRealTimeExport%926842804.body
}

void ZDDocument::DocumentHasBeenModified()
{
    //## begin ZDDocument::DocumentHasBeenModified%911404701.body preserve=yes
    //## end ZDDocument::DocumentHasBeenModified%911404701.body
}

void ZDDocument::FieldHasBeenModified()
{
    //## begin ZDDocument::FieldHasBeenModified%911404702.body preserve=yes
    if ( IsRealTimeExported() )
    {
        GetpRealTimeExport()->SourceHasBeenModified();
    }
    //## end ZDDocument::FieldHasBeenModified%911404702.body
}

void ZDDocument::RemoveAllDocumentData()
{
    //## begin ZDDocument::RemoveAllDocumentData%913885112.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        delete GetDocumentDataAt( i );
    }

    m_DocumentDataArray.RemoveAll();

    // Advise the frame that the file list has changed
    FileListHasChanged();
    //## end ZDDocument::RemoveAllDocumentData%913885112.body
}

ZDStamp& ZDDocument::GetStamp( int DocumentIndex )
{
    //## begin ZDDocument::GetStamp%913885114.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetStamp();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetStamp();
    //## end ZDDocument::GetStamp%913885114.body
}

void ZDDocument::DeleteAllObjects( int DocumentIndex )
{
    //## begin ZDDocument::DeleteAllObjects%914061085.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        GetActiveDocumentData()->DeleteAllObjects();
        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->DeleteAllObjects();
    //## end ZDDocument::DeleteAllObjects%914061085.body
}

int ZDDocument::CountAndSetPages( int DocumentIndex )
{
    //## begin ZDDocument::CountAndSetPages%914061086.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->CountAndSetPages();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->CountAndSetPages();
    //## end ZDDocument::CountAndSetPages%914061086.body
}

int ZDDocument::DocumentCountAndSetPages()
{
    //## begin ZDDocument::DocumentCountAndSetPages%934274802.body preserve=yes
    int Pages = 0;

    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        Pages += GetDocumentDataAt( i )->CountAndSetPages();
    }

    return Pages;
    //## end ZDDocument::DocumentCountAndSetPages%934274802.body
}

void ZDDocument::CalculateForecastedObjectCount()
{
    //## begin ZDDocument::CalculateForecastedObjectCount%914146143.body preserve=yes
    m_iObjectCounter = 0;

    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        m_iObjectCounter += GetDocumentDataAt( i )->GetObjectCount();
    }
    //## end ZDDocument::CalculateForecastedObjectCount%914146143.body
}

void ZDDocument::ShowAllDocumentData()
{
    //## begin ZDDocument::ShowAllDocumentData%914146146.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        GetDocumentDataAt( i )->ShowDocumentData();
    }
    //## end ZDDocument::ShowAllDocumentData%914146146.body
}

void ZDDocument::HideAllDocumentData()
{
    //## begin ZDDocument::HideAllDocumentData%914146147.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        GetDocumentDataAt( i )->HideDocumentData();
    }
    //## end ZDDocument::HideAllDocumentData%914146147.body
}

BOOL ZDDocument::CopyDocumentDataArray( ZDDocument* pDocSrc, BOOL InsertAsReadOnly )
{
    //## begin ZDDocument::CopyDocumentDataArray%914146156.body preserve=yes
    return CopyDocumentDataArray( pDocSrc->GetDocumentDataArray(), InsertAsReadOnly );
    //## end ZDDocument::CopyDocumentDataArray%914146156.body
}

BOOL ZDDocument::CopyDocumentDataArray( CObArray& ArraySrc, BOOL InsertAsReadOnly )
{
    //## begin ZDDocument::CopyDocumentDataArray%914146157.body preserve=yes
    BOOL            Error        = FALSE;
    ZDDocumentData*    pDocData;

    for ( int i = 0; i < ArraySrc.GetSize(); ++i )
    {
        pDocData = ( (ZDDocumentData*)ArraySrc.GetAt( i ) )->Clone();
        pDocData->SetpDocument( this );

        // Set the read-only flag
        pDocData->SetAsReadOnly( InsertAsReadOnly );
        Error |= !AddDocumentData( pDocData );
    }

    return !Error;
    //## end ZDDocument::CopyDocumentDataArray%914146157.body
}

BOOL ZDDocument::CopyDocumentDataArrayAfter( ZDDocument* pDocSrc, int Index, BOOL InsertAsReadOnly )
{
    //## begin ZDDocument::CopyDocumentDataArrayAfter%914146159.body preserve=yes
    return CopyDocumentDataArrayAfter( pDocSrc->GetDocumentDataArray(), Index, InsertAsReadOnly );
    //## end ZDDocument::CopyDocumentDataArrayAfter%914146159.body
}

BOOL ZDDocument::CopyDocumentDataArrayAfter( CObArray& ArraySrc, int Index, BOOL InsertAsReadOnly )
{
    //## begin ZDDocument::CopyDocumentDataArrayAfter%914146160.body preserve=yes
    BOOL            Error        = FALSE;
    ZDDocumentData*    pDocData;

    for ( int i = 0; i < ArraySrc.GetSize(); ++i )
    {
        pDocData = ( (ZDDocumentData*)ArraySrc.GetAt( i ) )->Clone();
        pDocData->SetpDocument( this );

        // Set the read-only flag
        pDocData->SetAsReadOnly( InsertAsReadOnly );
        Error |= !AddDocumentDataAfter( pDocData, Index + i );
    }

    return !Error;
    //## end ZDDocument::CopyDocumentDataArrayAfter%914146160.body
}

void ZDDocument::PropagateFieldValue( PlanFinObject* pObj, int DocumentIndex )
{
    //## begin ZDDocument::PropagateFieldValue%914754357.body preserve=yes
    switch ( DocumentIndex )
    {
        case -2:
        {
            for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
            {
                GetDocumentDataAt( i )->PropagateFieldValue( pObj );
            }

            return;
        }

        case -1:
        {
            if ( GetActiveDocumentData() )
            {
                GetActiveDocumentData()->PropagateFieldValue( pObj );
            }

            return;
        }

        default:
        {
            if ( GetDocumentDataAt( DocumentIndex ) )
            {
                GetDocumentDataAt( DocumentIndex )->PropagateFieldValue( pObj );
            }
        }
    }
    //## end ZDDocument::PropagateFieldValue%914754357.body
}

void ZDDocument::GetDocumentDataName( CStringArray& Array, BOOL OnlyVisible )
{
    //## begin ZDDocument::GetDocumentDataName%914788970.body preserve=yes
    Array.RemoveAll();

    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( !OnlyVisible || ( OnlyVisible && GetDocumentDataAt( i )->DocumentDataIsVisible() ) )
        {
            Array.Add( GetDocumentDataAt( i )->GetStamp().GetTitle() );
        }
    }
    //## end ZDDocument::GetDocumentDataName%914788970.body
}

int ZDDocument::FindDocumentData( const CString& Name )
{
    //## begin ZDDocument::FindDocumentData%915657293.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i )->GetStamp().GetTitle() == Name )
        {
            return i;
        }
    }

    return -1;
    //## end ZDDocument::FindDocumentData%915657293.body
}

BOOL ZDDocument::IsReadOnlyAtRuntime( int DocumentIndex )
{
    //## begin ZDDocument::IsReadOnlyAtRuntime%936298281.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->IsReadOnlyAtRuntime();
        }
        else
        {
            return NULL;
        }
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->IsReadOnlyAtRuntime();
    }

    return NULL;
    //## end ZDDocument::IsReadOnlyAtRuntime%936298281.body
}

void ZDDocument::SetReadOnlyAtRuntime( BOOL value, int DocumentIndex )
{
    //## begin ZDDocument::SetReadOnlyAtRuntime%936298282.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetReadOnlyAtRuntime( value );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetReadOnlyAtRuntime( value );
    }
    //## end ZDDocument::SetReadOnlyAtRuntime%936298282.body
}

void ZDDocument::SetAllDocReadOnlyAtRuntime( BOOL value )
{
    //## begin ZDDocument::SetAllDocReadOnlyAtRuntime%936393294.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) )
        {
            GetDocumentDataAt( i )->SetReadOnlyAtRuntime( value );
        }
    }
    //## end ZDDocument::SetAllDocReadOnlyAtRuntime%936393294.body
}

BOOL ZDDocument::CreateAllTemporaryFileFromBuffer()
{
    //## begin ZDDocument::CreateAllTemporaryFileFromBuffer%938959774.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) )
        {
            GetDocumentDataAt( i )->CreateTemporaryFileFromBuffer();
        }
    }

    return TRUE;
    //## end ZDDocument::CreateAllTemporaryFileFromBuffer%938959774.body
}

BOOL ZDDocument::DeleteAllTemporaryFiles()
{
    //## begin ZDDocument::DeleteAllTemporaryFiles%938959789.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) )
        {
            GetDocumentDataAt( i )->DeleteTemporaryFile();
        }
    }

    return TRUE;
    //## end ZDDocument::DeleteAllTemporaryFiles%938959789.body
}

BOOL ZDDocument::ReadDocument( const CString Filename )
{
    //## begin ZDDocument::ReadDocument%939754013.body preserve=yes
    BOOL            RetValue = FALSE;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument        = this;
    loadArchive.m_bForceFlat    = FALSE;

    TRY
    {
        Serialize( loadArchive );
        RetValue = TRUE;
    }
    CATCH( CArchiveException, e )
    {
        RetValue = FALSE;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // If everything is ok, set the pathname.
    if ( RetValue )
    {
        SetPathName( Filename, FALSE );
    }

    return RetValue;
    //## end ZDDocument::ReadDocument%939754013.body
}

void ZDDocument::OnDraw( CDC* pDC, ZIView* pView, int DocumentIndex )
{
    //## begin ZDDocument::OnDraw%940782408.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->OnDraw( pDC, pView );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->OnDraw( pDC, pView );
    }
    //## end ZDDocument::OnDraw%940782408.body
}

void ZDDocument::SwitchTabOrder( PlanFinObject* pObject, double TabOrder, int DocumentIndex )
{
    //## begin ZDDocument::SwitchTabOrder%947360847.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SwitchTabOrder( pObject, TabOrder );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SwitchTabOrder( pObject, TabOrder );
    }
    //## end ZDDocument::SwitchTabOrder%947360847.body
}

void ZDDocument::AssignMultiColumnMemberFields( int DocumentIndex )
{
    //## begin ZDDocument::AssignMultiColumnMemberFields%948318240.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->AssignMultiColumnMemberFields();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->AssignMultiColumnMemberFields();
    }
    //## end ZDDocument::AssignMultiColumnMemberFields%948318240.body
}

void ZDDocument::AssignAllMultiColumnMemberFields()
{
    //## begin ZDDocument::AssignAllMultiColumnMemberFields%948318242.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) )
        {
            GetDocumentDataAt( i )->AssignMultiColumnMemberFields();
        }
    }
    //## end ZDDocument::AssignAllMultiColumnMemberFields%948318242.body
}

bool ZDDocument::AddFieldNameInObectArray( const CString& Fieldname, int DocumentIndex )
{
    //## begin ZDDocument::AddFieldNameInObectArray%948540879.body preserve=yes
    ZDDocumentData* pDocData = NULL;

    if ( DocumentIndex == -1 )
    {
        pDocData = GetActiveDocumentData();
    }
    else
    {
        pDocData = GetDocumentDataAt( DocumentIndex );
    }

    // If valid document data
    if ( pDocData )
    {
        // Add new field name in the specific document data
        if ( !pDocData->AddFieldNameInObectArray( Fieldname ) )
        {
            return false;
        }

        // Add also the fieldname in the global fieldname array
        if ( !FieldNameExistInObectArray( Fieldname ) )
        {
            m_FieldNameArray.Add( Fieldname );
        }

        // no error
        return true;
    }

    return false;
    //## end ZDDocument::AddFieldNameInObectArray%948540879.body
}

bool ZDDocument::BuildObjectFieldNameArray()
{
    //## begin ZDDocument::BuildObjectFieldNameArray%948540872.body preserve=yes
    // Free the object fieldname array
    m_FieldNameArray.RemoveAll();

    // Run through all documents and 
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) )
        {
            // If elements have been built
            if ( GetDocumentDataAt( i )->BuildObjectFieldNameArray() )
            {
                CStringArray* pFieldNameArrayOfDocData = GetDocumentDataAt( i )->GetObjectFieldNameArray();

                if ( pFieldNameArrayOfDocData == NULL )
                {
                    continue;
                }

                // Now run through all elements and check if exist or not
                // and insert it in the list
                for ( size_t ElementIndex = 0; ElementIndex < pFieldNameArrayOfDocData->GetSize(); ++ElementIndex )
                {
                    if ( !FieldNameExistInObectArray( pFieldNameArrayOfDocData->GetAt( ElementIndex ) ) )
                    {
                        m_FieldNameArray.Add( pFieldNameArrayOfDocData->GetAt( ElementIndex ) );
                    }
                }
            }
        }
    }

    return m_FieldNameArray.GetSize() > 0;
    //## end ZDDocument::BuildObjectFieldNameArray%948540872.body
}

bool ZDDocument::FieldNameExistInObectArray( const CString& Fieldname )
{
    //## begin ZDDocument::FieldNameExistInObectArray%948540877.body preserve=yes
    for ( size_t i = 0; i < (size_t)m_FieldNameArray.GetSize(); ++i )
    {
        if ( Fieldname == m_FieldNameArray.GetAt( i ) )
        {
            return true;
        }
    }

    return false;
    //## end ZDDocument::FieldNameExistInObectArray%948540877.body
}

void ZDDocument::InitializeAllAssociations( int DocumentIndex )
{
    //## begin ZDDocumentRead::InitializeAllAssociations%902853328.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->InitializeAllAssociations();
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->InitializeAllAssociations();
    //## end ZDDocumentRead::InitializeAllAssociations%902853328.body
}

void ZDDocument::CalculateAllFormula( CView* pView, BOOL AllPages, int DocumentIndex )
{
    //## begin ZDDocumentRead::CalculateAllFormula%902943936.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->CalculateAllFormula( pView, AllPages );
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->CalculateAllFormula( pView, AllPages );
    //## end ZDDocumentRead::CalculateAllFormula%902943936.body
}

void ZDDocument::CheckForClearCalcField( CView* pView, int DocumentIndex )
{
    //## begin ZDDocumentRead::CheckForClearCalcField%902943939.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->CheckForClearCalcField( pView );
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->CheckForClearCalcField( pView );
    //## end ZDDocumentRead::CheckForClearCalcField%902943939.body
}

void ZDDocument::ChangeCurrentSchema( const CString& sName, BOOL bNotify, int DocumentIndex )
{
    //## begin ZDDocumentRead::ChangeCurrentSchema%907776825.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ChangeCurrentSchema( sName, bNotify );
        }

        return;
    }

    if ( DocumentIndex == -2 )
    {
        for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
        {
            if ( GetDocumentDataAt( i ) )
            {
                GetDocumentDataAt( i )->ChangeCurrentSchema( sName, bNotify );
            }
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->ChangeCurrentSchema( sName, bNotify );
    //## end ZDDocumentRead::ChangeCurrentSchema%907776825.body
}

void ZDDocument::ClearCurrentAssociation( int DocumentIndex )
{
    //## begin ZDDocumentRead::ClearCurrentAssociation%907776826.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ClearCurrentAssociation();
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->ClearCurrentAssociation();
    //## end ZDDocumentRead::ClearCurrentAssociation%907776826.body
}

void ZDDocument::ChangeFieldForCalculation( int DocumentIndex )
{
    //## begin ZDDocumentRead::ChangeFieldForCalculation%907776827.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ChangeFieldForCalculation();
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->ChangeFieldForCalculation();
    //## end ZDDocumentRead::ChangeFieldForCalculation%907776827.body
}

BOOL ZDDocument::IsCalculatedFieldInSchema( PlanFinObject* pObj, int DocumentIndex )
{
    //## begin ZDDocumentRead::IsCalculatedFieldInSchema%907776829.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->IsCalculatedFieldInSchema( pObj ) : FALSE;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->IsCalculatedFieldInSchema( pObj );
    //## end ZDDocumentRead::IsCalculatedFieldInSchema%907776829.body
}

void ZDDocument::RefreshCurrentSchema( int DocumentIndex )
{
    //## begin ZDDocumentRead::RefreshCurrentSchema%910633442.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->RefreshCurrentSchema();
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->RefreshCurrentSchema();
    //## end ZDDocumentRead::RefreshCurrentSchema%910633442.body
}

void ZDDocument::InitializeAllObjectPointers()
{
    //## begin ZDDocumentRead::InitializeAllObjectPointers%914353651.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        GetDocumentDataAt( i )->InitializeAllObjectPointers();
    }
    //## end ZDDocumentRead::InitializeAllObjectPointers%914353651.body
}

void ZDDocument::ChangeCurrentFile( const CString& Name, BOOL bNotify )
{
    //## begin ZDDocumentRead::ChangeCurrentFile%914877931.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i )->GetStamp().GetTitle() == Name )
        {
            ChangeCurrentFile( i, bNotify );
        }
    }
    //## end ZDDocumentRead::ChangeCurrentFile%914877931.body
}

void ZDDocument::ChangeCurrentFile( size_t FileIndex, BOOL bNotify )
{
    //## begin ZDDocumentRead::ChangeCurrentFile%914877932.body preserve=yes
    if ( GetDocumentDataAt( FileIndex ) )
    {
        if ( GetDocumentDataAt( FileIndex )->IsExternalBinaryData() )
        {
        }
        else if ( GetDocumentDataAt( FileIndex )->IsURLData() )
        {
            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() );
            }

            AfxGetMainWnd()->SendMessageToDescendants( UM_SHOWHTMLVIEW, 0, (LPARAM)this );

            if ( !GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate().IsEmpty() && GetHtmlView() )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_NAVIGATEURL,
                                                           0,
                                                           (LPARAM)( (const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() ) );
            }
        }
        else if ( GetDocumentDataAt( FileIndex )->IsBinaryDataValid() )
        {
            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() );
            }

            AfxGetMainWnd()->SendMessageToDescendants( UM_SHOWHTMLVIEW, 0, (LPARAM)this );

            if ( !GetDocumentDataAt( FileIndex )->GetFileBufferTemporaryFile().IsEmpty() && GetHtmlView() )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_NAVIGATEURL,
                                                           0,
                                                           (LPARAM)( (const char*)GetDocumentDataAt( FileIndex )->GetFileBufferTemporaryFile() ) );
            }
        }
        else
        {
            AfxGetMainWnd()->SendMessageToDescendants( UM_HIDEHTMLVIEW, 0, (LPARAM)this );

            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTitle() );
            }
        }

        SetActiveDocumentIndex( FileIndex );
    }
    //## end ZDDocumentRead::ChangeCurrentFile%914877932.body
}

void ZDDocument::ChangeCurrentFileOpen( const CString& Name, BOOL bNotify )
{
    //## begin ZDDocumentRead::ChangeCurrentFileOpen%940749600.body preserve=yes
    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i )->GetStamp().GetTitle() == Name )
        {
            ChangeCurrentFileOpen( i, bNotify );
        }
    }
    //## end ZDDocumentRead::ChangeCurrentFileOpen%940749600.body
}

void ZDDocument::ChangeCurrentFileOpen( size_t FileIndex, BOOL bNotify )
{
    if ( GetDocumentDataAt( FileIndex ) )
    {
        if ( GetDocumentDataAt( FileIndex )->IsExternalBinaryData() )
        {
        }
        else if ( GetDocumentDataAt( FileIndex )->IsURLData() )
        {
            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() );
            }

            AfxGetMainWnd()->SendMessageToDescendants( UM_SHOWHTMLVIEW, 0, (LPARAM)this );

            if ( !GetDocumentDataAt(FileIndex)->GetStamp().GetTemplate().IsEmpty() && GetHtmlView() )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_NAVIGATEURL,
                                                           0,
                                                           (LPARAM)( (const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() ) );
            }
        }
        else if ( GetDocumentDataAt( FileIndex )->IsBinaryDataValid() )
        {
            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTemplate() );
            }

            AfxGetMainWnd()->SendMessageToDescendants( UM_SHOWHTMLVIEW, 0, (LPARAM)this );

            if ( !GetDocumentDataAt( FileIndex )->GetFileBufferTemporaryFile().IsEmpty() && GetHtmlView() )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_NAVIGATEURL,
                                                           0,
                                                           (LPARAM)( (const char*)GetDocumentDataAt( FileIndex )->GetFileBufferTemporaryFile() ) );
            }
        }
        else
        {
            AfxGetMainWnd()->SendMessageToDescendants( UM_HIDEHTMLVIEW, 0, (LPARAM)this );

            if ( bNotify )
            {
                AfxGetMainWnd()->SendMessageToDescendants( UM_SETDEFAULTFILE,
                                                           0,
                                                           (LPARAM)(const char*)GetDocumentDataAt( FileIndex )->GetStamp().GetTitle() );
            }
        }

        SetActiveDocumentIndex( FileIndex );
    }
}

void ZDDocument::GetStyleArrayName( CStringArray& StyleArray )
{
    ZAStyleManager& Styles = GetStyleManager();

    for ( size_t i = 0; i < Styles.GetElements(); ++i )
    {
        if ( Styles.GetStyle( i ) )
        {
            StyleArray.Add( Styles.GetStyle( i )->GetStyleName() );
        }
    }
}

size_t ZDDocument::CalculateVisibleDocumentDataCount()
{
    // Initialize the counter
    m_VisibleDocumentDataCount = 0;

    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i )->DocumentDataIsVisible() )
        {
            ++m_VisibleDocumentDataCount;
        }
    }

    return m_VisibleDocumentDataCount;
}

int ZDDocument::PreviousVisibleDocumentAvailable( size_t DocumentIndex ) const
{
    int i = DocumentIndex;

    while( --i >= 0 )
    {
        if ( GetDocumentDataAt( i ) && GetDocumentDataAt( i )->DocumentDataIsVisible() )
        {
            return i;
        }
    }

    return -1;
}

int ZDDocument::NextVisibleDocumentAvailable( size_t DocumentIndex ) const
{
    for ( size_t i = DocumentIndex + 1; i < GetDocumentDataCount(); ++i )
    {
        if ( GetDocumentDataAt( i ) && GetDocumentDataAt( i )->DocumentDataIsVisible() )
        {
            return i;
        }
    }

    return -1;
}

void ZDDocument::OnCloseDocument()
{
    ZDBaseDocument::OnCloseDocument();

    if ( !ZAGlobal::OpenFileInSilentMode() )
    {
        // Notify the framework, that this file is closed
        AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTHASBEENSELECTED, 0, (LPARAM)NULL );
    }
}

ZIHtmlView* ZDDocument::GetHtmlView()
{
    POSITION    pos        = GetFirstViewPosition();
    CView*        pView    = GetNextView( pos );

    while ( pView )
    {
        if ( pView->IsKindOf( RUNTIME_CLASS( ZIHtmlView ) ) )
        {
            return (ZIHtmlView*)pView;
        }

        pView = GetNextView( pos );
    }

    return NULL;
}

BOOL ZDDocument::CreateRealTimeExport()
{
    //## begin ZDDocumentReadWrite::CreateRealTimeExport%911381918.body preserve=yes
    // Tests if it is necessary to create a real time synchro
    // No templates
    // ExchangeFeedFile required
    if ( DocumentIsTemplate() || !GetDocOptions().GetIsSynchronizeExchangeFeedFile() )
    {
        return TRUE;
    }

    // Build the synchronization filename.
    CString File = GetDocOptions().BuildSynchronizationFileName( GetPathName() );

    // If the file is empty, out
    if ( File.IsEmpty() )
    {
        return TRUE;
    }

    // Create the object.
    m_pRealTimeExport = new ZUDocumentExport( File,
                                              this,
                                              GetDocOptions().GetSynchronizationHeader(),        // Generate header or not
                                              GetDocOptions().GetSynchronizationSeparator(),    // Separator type
                                              _T( "" ),                                            // Take the current schema
                                              LocateAllPages );

    ASSERT( m_pRealTimeExport );
    m_pRealTimeExport->StartSynchronization( GetDocOptions().GetSynchronizeTimeSequence() );

    return TRUE;
    //## end ZDDocumentReadWrite::CreateRealTimeExport%911381918.body
}

void ZDDocument::ReplaceCalculatedFields( int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::ReplaceCalculatedFields%913885117.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ReplaceCalculatedFields();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->ReplaceCalculatedFields();
    }
    //## end ZDDocumentReadWrite::ReplaceCalculatedFields%913885117.body
}

void ZDDocument::AssignPredefinedField( int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::AssignPredefinedField%913970066.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->AssignPredefinedField();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->AssignPredefinedField();
    }
    //## end ZDDocumentReadWrite::AssignPredefinedField%913970066.body
}

BOOL ZDDocument::ChangeObjectType( PlanFinObject*    obj,
                                   const CString&    sName,
                                   const CString&    sFinalValue,
                                   BOOL                bPropagate,
                                   int                DocumentIndex )
{
    //## begin ZDDocumentReadWrite::ChangeObjectType%913970067.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            return GetActiveDocumentData()->ChangeObjectType( obj, sName, sFinalValue, bPropagate );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        return GetDocumentDataAt( DocumentIndex )->ChangeObjectType( obj, sName, sFinalValue, bPropagate );
    }

    return FALSE;
    //## end ZDDocumentReadWrite::ChangeObjectType%913970067.body
}

CString ZDDocument::BuildAutomaticNewName( const CString& sPrefix, int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::BuildAutomaticNewName%913970074.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->BuildAutomaticNewName( sPrefix );
        }

        return _T( "" );
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->BuildAutomaticNewName( sPrefix );
    }

    return _T( "" );
    //## end ZDDocumentReadWrite::BuildAutomaticNewName%913970074.body
}

BOOL ZDDocument::InsertObject( PlanFinObject*        obj,
                               ZBFieldRepository*    pFieldRepository,
                               BOOL                    InsertInGlobalRepository,
                               int                    DocumentIndex,
                               BOOL                    Refresh                        /*= FALSE*/ )
{
    //## begin ZDDocumentReadWrite::InsertObject%913970068.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            AddFieldNameInObectArray( obj->GetObjectName() );
            return GetActiveDocumentData()->InsertObject( obj, pFieldRepository, InsertInGlobalRepository, Refresh );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        AddFieldNameInObectArray( obj->GetObjectName(), DocumentIndex );
        return GetDocumentDataAt( DocumentIndex )->InsertObject( obj,
                                                                 pFieldRepository,
                                                                 InsertInGlobalRepository,
                                                                 Refresh );
    }

    return FALSE;
    //## end ZDDocumentReadWrite::InsertObject%913970068.body
}

BOOL ZDDocument::InsertObjectAtHead( PlanFinObject*        obj,
                                     ZBFieldRepository*    pFieldRepository,
                                     BOOL                InsertInGlobalRepository,
                                     int                DocumentIndex,
                                     BOOL                Refresh                        /*= FALSE*/ )
{
    //## begin ZDDocumentReadWrite::InsertObject%913970068.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            AddFieldNameInObectArray( obj->GetObjectName() );
            return GetActiveDocumentData()->InsertObjectAtHead( obj,
                                                                pFieldRepository,
                                                                InsertInGlobalRepository,
                                                                Refresh );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        AddFieldNameInObectArray( obj->GetObjectName(), DocumentIndex );
        return GetDocumentDataAt(DocumentIndex)->InsertObjectAtHead( obj,
                                                                     pFieldRepository,
                                                                     InsertInGlobalRepository,
                                                                     Refresh );
    }

    return FALSE;
    //## end ZDDocumentReadWrite::InsertObject%913970068.body
}

BOOL ZDDocument::DeleteObject( PlanFinObject*    obj,
                               BOOL                DeleteFromMemory,
                               int                DocumentIndex,
                               BOOL                Refresh                /*= FALSE*/ )
{
    //## begin ZDDocumentReadWrite::DeleteObject%913970069.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            return GetActiveDocumentData()->DeleteObject( obj, DeleteFromMemory, Refresh );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        return GetDocumentDataAt( DocumentIndex )->DeleteObject( obj, DeleteFromMemory, Refresh );
    }

    return FALSE;
    //## end ZDDocumentReadWrite::DeleteObject%913970069.body
}

BOOL ZDDocument::MoveObjectInOrder( PlanFinObject* obj, int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::MoveObjectInOrder%913970070.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            return GetActiveDocumentData()->MoveObjectInOrder( obj );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        return GetDocumentDataAt( DocumentIndex )->MoveObjectInOrder( obj );
    }

    return FALSE;
    //## end ZDDocumentReadWrite::MoveObjectInOrder%913970070.body
}

void ZDDocument::AssignObjectValue( CString    Name,
                                    CString    Value,
                                    int        Page,
                                    int        PropagationMode,
                                    BOOL    EmptyWhenZero,
                                    int        DocumentIndex )
{
    //## begin ZDDocumentReadWrite::AssignObjectValue%913970071.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            SetModifiedFlag();
            GetActiveDocumentData()->AssignObjectValue( Name, Value, Page, PropagationMode, EmptyWhenZero );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        SetModifiedFlag();
        GetDocumentDataAt( DocumentIndex )->AssignObjectValue( Name, Value, Page, PropagationMode, EmptyWhenZero );
    }
    //## end ZDDocumentReadWrite::AssignObjectValue%913970071.body
}

void ZDDocument::SetCurrentPageToObject( PlanFinObject* obj, int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::SetCurrentPageToObject%913970072.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetCurrentPageToObject( obj );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetCurrentPageToObject( obj );
    }
    //## end ZDDocumentReadWrite::SetCurrentPageToObject%913970072.body
}

BOOL ZDDocument::InsertDocument( const CString FileName, BOOL InsertAsReadOnly, int PropagateValue )
{
    return InsertDocumentAfter( FileName, -1, InsertAsReadOnly );
}

BOOL ZDDocument::InsertDocumentAfter( const CString    FileName,
                                      int            IndexAfter,
                                      BOOL            InsertAsReadOnly,
                                      int            PropagateValue )
{
    // Set silent mode before opening the file
    ZAGlobal::SetOpenFileInSilentMode();

    ZDDocument* p_NewDocument = (ZDDocument*) ZAGlobal::GetpDocTemplate()->OpenDocumentFile( (const char*)FileName );

    if ( !p_NewDocument )
    {
        return FALSE;
    }

    // Only if the document is correct
    // Set the type for Document
    p_NewDocument->GetStamp().SetFileType( DocumentType );

    // Check if all fonts still available
    CheckDocumentFontAndStyle();

    // Before inserting the document, propagate the source document value
    PropagateExternDocumentAllValues( p_NewDocument, LocateAllDocumentsEmptyOnly, FALSE );

    // And then, propagate the document value to the document
    p_NewDocument->PropagateExternDocumentAllValues( this, LocateAllDocumentsEmptyOnly, FALSE );

    if ( IndexAfter == -1 )
    {
        CopyDocumentDataArray( p_NewDocument, InsertAsReadOnly );
    }
    else
    {
        CopyDocumentDataArrayAfter( p_NewDocument, IndexAfter, InsertAsReadOnly );
    }

    p_NewDocument->OnCloseDocument();

    // Set back silent mode after having opened the file
    ZAGlobal::SetOpenFileInSilentMode( FALSE );

    // It is important to initialize all object pointers again.
    InitializeAllObjectPointers();

    // Count all pages for all document data
    DocumentCountAndSetPages();
    
    SetModifiedFlag( TRUE );

    // Set to the previous file directory
    ZAGlobal::SetToFileDirectory();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // Set the current file list
    if ( GetActiveDocumentIndex() == -1 )
    {
        SetActiveDocumentIndex( 0 );
    }

    ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );

    return TRUE;
}

BOOL ZDDocument::InsertExternalDocument( const CString FileName, BOOL InsertAsReadOnly, int PropagateValue )
{
    return InsertExternalDocumentAfter( FileName, -1, InsertAsReadOnly );
}

BOOL ZDDocument::InsertExternalDocumentAfter( const CString    FileName,
                                              int            IndexAfter,
                                              BOOL            InsertAsReadOnly,
                                              int            PropagateValue )
{
    ZDDocumentData* pNewDocData = new ZDDocumentData;

    if ( !pNewDocData )
    {
        return FALSE;
    }

    ZFile File( FileName );

    // Check if file exists
    if ( !File.Exist() )
    {
        return FALSE;
    }

    // Set the type for Document
    pNewDocData->GetStamp().SetFileType( DocumentType );

    // Set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType( ExternalFormDataType );
    pNewDocData->GetStamp().SetTemplate( FileName );

    int NewIndex = 0;

    if ( IndexAfter == -1 )
    {
        AddDocumentData( pNewDocData );
        NewIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter( pNewDocData, IndexAfter );
        NewIndex = IndexAfter + 1;
    }

    SetModifiedFlag( TRUE );

    // Set to the previous file directory
    ZAGlobal::SetToFileDirectory();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // Set the current file list
    if ( NewIndex == -1 )
    {
        SetActiveDocumentIndex( 0 );
    }
    else
    {
        SetActiveDocumentIndex( NewIndex );
    }

    // And now, change the current file displayed
    ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );

    return TRUE;
}

BOOL ZDDocument::InsertBinaryDocument( const CString FileName,
                                       const CString InfoName,
                                       const CString InfoDescription )
{
    return InsertBinaryDocumentAfter( FileName, -1, InfoName, InfoDescription );
}

BOOL ZDDocument::InsertBinaryDocumentAfter( const CString    FileName,
                                            int                IndexAfter,
                                            const CString    InfoName,
                                            const CString    InfoDescription )
{
    ZDDocumentData* pNewDocData = new ZDDocumentData;

    if ( !pNewDocData )
    {
        return FALSE;
    }

    // Set the type for Document
    pNewDocData->GetStamp().SetFileType( DocumentType );

    // Set the document name
    pNewDocData->GetStamp().SetTitle( InfoName );

    // Set the document description
    pNewDocData->GetStamp().SetExplanation( InfoDescription );

    // Create the binary buffer from file
    if ( !pNewDocData->CreateBufferFromFile( FileName ) )
    {
        delete pNewDocData;
        return FALSE;
    }

    int NewIndex = 0;

    if ( IndexAfter == -1 )
    {
        AddDocumentData( pNewDocData );
        NewIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter( pNewDocData, IndexAfter );
        NewIndex = IndexAfter + 1;
    }

    // Count all pages for all document data
    DocumentCountAndSetPages();

    SetModifiedFlag( TRUE );

    // Set to the previous file directory
    ZAGlobal::SetToFileDirectory();

    // Create all file for all file buffered
    CreateAllTemporaryFileFromBuffer();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // Set the current file list
    if ( NewIndex == -1 )
    {
        SetActiveDocumentIndex( 0 );
    }
    else
    {
        SetActiveDocumentIndex( NewIndex );
    }

    // And now, change the current file displayed
    ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );

    return TRUE;
}

BOOL ZDDocument::InsertExternalBinaryDocument( const CString FileName,
                                               const CString InfoName,
                                               const CString InfoDescription )
{
    return InsertExternalBinaryDocumentAfter( FileName, -1, InfoName, InfoDescription );
}

BOOL ZDDocument::InsertExternalBinaryDocumentAfter( const CString    FileName,
                                                    int                IndexAfter,
                                                    const CString    InfoName,
                                                    const CString    InfoDescription )
{
    ZDDocumentData* pNewDocData = new ZDDocumentData;

    if ( !pNewDocData )
    {
        return FALSE;
    }

    ZFile File( FileName );

    // Check if file exists
    if ( !File.Exist() )
    {
        return FALSE;
    }

    // Set the type for Document
    pNewDocData->GetStamp().SetFileType( DocumentType );

    // Set the document name
    pNewDocData->GetStamp().SetTitle( InfoName );

    // Set the document description
    pNewDocData->GetStamp().SetExplanation( InfoDescription );

    // Set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType( ExternalBinaryDataType );
    pNewDocData->GetStamp().SetTemplate( FileName );

    int NewIndex = 0;

    if ( IndexAfter == -1 )
    {
        AddDocumentData( pNewDocData );
        NewIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter( pNewDocData, IndexAfter );
        NewIndex = IndexAfter + 1;
    }

    SetModifiedFlag( TRUE );

    // Set to the previous file directory
    ZAGlobal::SetToFileDirectory();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // Set the current file list
    if ( NewIndex == -1 )
    {
        SetActiveDocumentIndex( 0 );
    }
    else
    {
        SetActiveDocumentIndex( NewIndex );
    }

    // And now, change the current file displayed
    ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );
    
    return TRUE;
}

BOOL ZDDocument::InsertURL( const CString URL )
{
    return InsertURLAfter( URL, -1 );
}

BOOL ZDDocument::InsertURLAfter( const CString URL, int IndexAfter )
{
    ZDDocumentData* pNewDocData = new ZDDocumentData;

    if ( !pNewDocData )
    {
        return FALSE;
    }

    // Set the type for Document
    pNewDocData->GetStamp().SetFileType( DocumentType );

    // Set the document name
    pNewDocData->GetStamp().SetTitle( URL );

    // Set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType( URLDataType );
    pNewDocData->GetStamp().SetTemplate( URL );

    int NewIndex = 0;

    if ( IndexAfter == -1 )
    {
        AddDocumentData( pNewDocData );
        NewIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter( pNewDocData, IndexAfter );
        NewIndex = IndexAfter + 1;
    }

    SetModifiedFlag( TRUE );

    // Set to the previous file directory
    ZAGlobal::SetToFileDirectory();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // Set the current file list
    if ( NewIndex == -1 )
    {
        SetActiveDocumentIndex( 0 );
    }
    else
    {
        SetActiveDocumentIndex( NewIndex );
    }

    // And now, change the current file displayed
    ChangeCurrentFile( GetActiveDocumentIndex(), TRUE );

    return TRUE;
}

BOOL ZDDocument::DeleteDocumentAt( int Index )
{
    if ( Index < GetDocumentDataCount() )
    {
        ZDDocumentData* pDocData = GetDocumentDataAt( Index );

        if ( pDocData )
        {
            delete pDocData;
            m_DocumentDataArray.RemoveAt( Index );

            // Advise the frame that the file list has changed
            FileListHasChanged();

            // If the active document is the deleted document
            // change the active document
            if ( GetActiveDocumentIndex() == Index )
            {
                ChangeCurrentFile( 0, TRUE );
            }

            // Document has changed
            SetModifiedFlag();
            return TRUE;
        }
    }

    return FALSE;
}

BOOL ZDDocument::DeleteDocumentData( ZDDocumentData* pDocData )
{
    int Idx = GetDocumentDataIndex( pDocData );
    return ( Idx != -1 ) ? DeleteDocumentAt( Idx ) : FALSE;
}

int ZDDocument::GetDocumentDataIndex( ZDDocumentData* pDocData )
{
    if ( !pDocData )
    {
        return -1;
    }

    for ( int Idx = 0; Idx < GetDocumentDataCount(); ++Idx )
    {
        ZDDocumentData* pData = GetDocumentDataAt( Idx );

        if ( pData && pData == pDocData )
        {
            return Idx;
        }
    }

    return -1;
}

void ZDDocument::CheckDocumentFontAndStyle()
{
    //## begin ZDDocumentReadWrite::CheckDocumentFontAndStyle%914161846.body preserve=yes
    // Run through the document data array and check the font validity
    for ( size_t Index = 0; Index < GetDocumentDataCount(); ++Index )
    {
        GetDocumentDataAt( Index )->CheckFontValidity();
    }
    //## end ZDDocumentReadWrite::CheckDocumentFontAndStyle%914161846.body
}

BOOL ZDDocument::PropagateDocumentValue( CString    Name,
                                         CString    Value,
                                         int        PropagationMode,
                                         BOOL        EmptyWhenZero,
                                         int        DocumentIndex,
                                         int        Page )
{
    //## begin ZDDocumentReadWrite::PropagateDocumentValue%934014431.body preserve=yes
    ZDDocumentData* pData = NULL;

    // If does not concern all documents
    if ( PropagationMode != LocateAllDocumentsEmptyOnly && PropagationMode != LocateAllDocuments )
    {
        // Retreive the document data pointer
        pData = ( DocumentIndex == -1 ) ? GetActiveDocumentData() : GetDocumentDataAt( DocumentIndex );

        // If not valid, error
        if ( !pData )
        {
            return FALSE;
        }
    }

    // Set modification flag
    SetModifiedFlag();

    switch ( PropagationMode )
    {
        case LocateAllDocumentsEmptyOnly:
        {
            // For each document data, call the document function to change the object value
            for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
            {
                GetDocumentDataAt( i )->AssignObjectValue( Name, Value, 0, LocateAllPagesEmptyOnly, EmptyWhenZero );
            }

            break;
        }

        case LocateAllDocuments:
        {
            // For each document data, call the document function to change the object value
            for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
            {
                GetDocumentDataAt( i )->AssignObjectValue( Name, Value, 0, LocateAllPages, EmptyWhenZero );
            }

            break;
        }

        case LocatePageOnlyEmptyOnly:
        case LocateForwardPageEmptyOnly:
        case LocateAllPagesEmptyOnly:
        case LocatePageOnly:
        case LocateForwardPage:
        case LocateAllPages:
        {
            ASSERT( pData );
            return pData->AssignObjectValue( Name, Value, Page, PropagationMode, EmptyWhenZero );
        }
    }

    // Error, has not been done
    return TRUE;
    //## end ZDDocumentReadWrite::PropagateDocumentValue%934014431.body
}

BOOL ZDDocument::PropagateDocumentValueFromTo( CString    Name,
                                               CString    Value,
                                               int        PropagationMode,
                                               BOOL        EmptyWhenZero,
                                               int        DocumentIndexFrom,
                                               int        DocumentIndexTo,
                                               int        Page )
{
    //## begin ZDDocumentReadWrite::PropagateDocumentValueFromTo%945026902.body preserve=yes
    ZDDocumentData* pData = NULL;

    if ( DocumentIndexTo == -1 )
    {
        DocumentIndexTo = GetDocumentDataCount() - 1;
    }

    // The index should be right
    if ( DocumentIndexFrom > DocumentIndexTo )
    {
        return FALSE;
    }

    // For each document data, call the document function to change the object value
    for ( size_t i = DocumentIndexFrom; i <= DocumentIndexTo; ++i )
    {
        GetDocumentDataAt( i )->AssignObjectValue( Name, Value, 0, PropagationMode, EmptyWhenZero );
    }

    // Set modification flag
    SetModifiedFlag();
    return TRUE;
    //## end ZDDocumentReadWrite::PropagateDocumentValueFromTo%945026902.body
}

BOOL ZDDocument::PropagateExternDocumentAllValues( ZDDocument*    pDoc,
                                                   int            PropagationMode,
                                                   BOOL            EmptyWhenZero,
                                                   int            DocumentIndex,
                                                   int            Page )
{
    //## begin ZDDocumentReadWrite::PropagateExternDocumentAllValues%934145355.body preserve=yes
    // For all fields coming from the extern document, propagate all values.
    // Process only one time per field name
    // For each object, assign the new value
    PlanFinObject *pObj;

    for ( size_t i = 0; i < pDoc->GetDocumentDataCount(); ++i )
    {
        if( ( pObj = pDoc->GetDocumentDataAt( i )->GetHead() ) != NULL )
        {
            do
            {
                // If the object is exportable
                if ( !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAscii ) )            &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) )    &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNTwoStates ) ) )
                {
                    continue;
                }

                if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNText ) ) && ( (PLFNText*)pObj )->GetIsStatic() )
                {
                    continue;
                }

                if ( !PropagateDocumentValue( pObj->GetObjectName(),
                                              pObj->GetUnformatedObject(),
                                              PropagationMode,
                                              EmptyWhenZero,
                                              DocumentIndex,
                                              Page ) )
                {
                    return FALSE;
                }
            }
            while( ( pObj = pDoc->GetDocumentDataAt( i )->GetNext() ) != NULL );
        }
    }

    // Set modification flag
    SetModifiedFlag();
    return TRUE;
    //## end ZDDocumentReadWrite::PropagateExternDocumentAllValues%934145355.body
}

BOOL ZDDocument::PropagateInternalDocumentAllValues( int    IndexFrom,
                                                     int    IndexTo,
                                                     int    PropagationMode,
                                                     BOOL    EmptyWhenZero,
                                                     int    DocumentIndex,
                                                     int    Page )
{
    //## begin ZDDocumentReadWrite::PropagateInternalDocumentAllValues%945006730.body preserve=yes
    // For each object, assign the new value
    PlanFinObject *pObj;

    if ( IndexTo == -1 )
    {
        IndexTo = GetDocumentDataCount() - 1;
    }

    // The index should be right
    if ( IndexFrom > IndexTo )
    {
        return FALSE;
    }

    for ( size_t i = IndexFrom; i <= IndexTo; ++i )
    {
        if( ( pObj = GetDocumentDataAt( i )->GetHead() ) != NULL )
        {
            do
            {
                // If the object is exportable
                if ( !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAscii ) )            &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) )    &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNTwoStates ) ) )
                {
                    continue;
                }

                if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNText ) ) && ( (PLFNText*)pObj )->GetIsStatic() )
                {
                    continue;
                }

                if ( !PropagateDocumentValue( pObj->GetObjectName(),
                                              pObj->GetUnformatedObject(),
                                              PropagationMode,
                                              EmptyWhenZero,
                                              DocumentIndex,
                                              Page ) )
                {
                    return FALSE;
                }
            }
            while( ( pObj = GetDocumentDataAt( i )->GetNext() ) != NULL );
        }
    }

    // Set modification flag
    SetModifiedFlag();
    return TRUE;
    //## end ZDDocumentReadWrite::PropagateInternalDocumentAllValues%945006730.body
}

BOOL ZDDocument::PropagateInternalDocumentOnDocumentValues( int        InIndexFrom,
                                                            int        InIndexTo,
                                                            int        ToIndexFrom,
                                                            int        ToIndexTo,
                                                            int        PropagationMode,
                                                            BOOL    EmptyWhenZero )
{
    //## begin ZDDocumentReadWrite::PropagateInternalDocumentOnDocumentValues%945006731.body preserve=yes
    // For each object, assign the new value
    PlanFinObject  *pObj;

    if ( InIndexTo == -1 )
    {
        InIndexTo = GetDocumentDataCount() - 1;
    }

    // The index should be right
    if ( InIndexFrom > InIndexTo )
    {
        return FALSE;
    }

    for ( size_t i = InIndexFrom; i <= InIndexTo; ++i )
    {
        if( ( pObj = GetDocumentDataAt(i)->GetHead() ) != NULL )
        {
            do
            {
                // If the object is exportable
                if ( !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAscii ) )            &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) )    &&
                     !( (PlanFinObject*)pObj )->IsKindOf( RUNTIME_CLASS( PLFNTwoStates ) ) )
                {
                    continue;
                }

                if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNText ) ) && ( (PLFNText*)pObj )->GetIsStatic() )
                {
                    continue;
                }

                if ( !PropagateDocumentValueFromTo( pObj->GetObjectName(),
                                                    pObj->GetUnformatedObject(),
                                                    PropagationMode,
                                                    EmptyWhenZero,
                                                    ToIndexFrom,
                                                    ToIndexTo ) )
                {
                    return FALSE;
                }
            }
            while( ( pObj = GetDocumentDataAt( i )->GetNext() ) != NULL );
        }
    }

    // Set modification flag
    SetModifiedFlag();
    return TRUE;
    //## end ZDDocumentReadWrite::PropagateInternalDocumentOnDocumentValues%945006731.body
}

CObList& ZDDocument::GetObjectList( int DocumentIndex )
{
    //## begin ZDDocument::GetObjectList%902579795.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetObjectList();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetObjectList();
    //## end ZDDocument::GetObjectList%902579795.body
}

int ZDDocument::GetObjectCount( int DocumentIndex )
{
    //## begin ZDDocument::GetObjectCount%902579796.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetObjectCount() : 0;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetObjectCount();
    }

    return 0;
    //## end ZDDocument::GetObjectCount%902579796.body
}

PlanFinObject* ZDDocument::GetHead( int DocumentIndex )
{
    //## begin ZDDocument::GetHead%902579797.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetHead() : NULL;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetHead();
    }

    return NULL;
    //## end ZDDocument::GetHead%902579797.body
}

PlanFinObject* ZDDocument::GetNext( int DocumentIndex )
{
    //## begin ZDDocument::GetNext%902579798.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetNext() : NULL;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetNext();
    }

    return NULL;
    //## end ZDDocument::GetNext%902579798.body
}

CString ZDDocument::GetStandardSchema() const
{
    //## begin ZDDocument::GetStandardSchema%902579800.body preserve=yes
    return szOriginalSchema;
    //## end ZDDocument::GetStandardSchema%902579800.body
}

CString ZDDocument::GetCurrentSchema( int DocumentIndex ) const
{
    //## begin ZDDocument::GetCurrentSchema%902579801.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetCurrentSchema() : _T( "" );
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetCurrentSchema();
    }

    return _T( "" );
    //## end ZDDocument::GetCurrentSchema%902579801.body
}

void ZDDocument::SetCurrentSchema( const CString& Name, int DocumentIndex )
{
    //## begin ZDDocument::SetCurrentSchema%902853326.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetCurrentSchema( Name );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetCurrentSchema( Name );
    }
    //## end ZDDocument::SetCurrentSchema%902853326.body
}

int ZDDocument::GetMaxPage( int DocumentIndex )
{
    //## begin ZDDocument::GetMaxPage%907776831.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetMaxPage() : 0;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetMaxPage();
    }

    return NULL;
    //## end ZDDocument::GetMaxPage%907776831.body
}

void ZDDocument::SetMaxPage( int iPage, int DocumentIndex )
{
    //## begin ZDDocument::SetMaxPage%907776837.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetMaxPage( iPage );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetMaxPage( iPage );
    }
    //## end ZDDocument::SetMaxPage%907776837.body
}

CString ZDDocument::GetDefaultAssociationString() const
{
    //## begin ZDDocument::GetDefaultAssociationString%908101537.body preserve=yes
    return szDefaultAssociationString;
    //## end ZDDocument::GetDefaultAssociationString%908101537.body
}

int ZDDocument::GetCurrentPage( int DocumentIndex ) const
{
    //## begin ZDDocument::GetCurrentPage%938177643.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetCurrentPage() : -1;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetCurrentPage();
    }

    return -1;
    //## end ZDDocument::GetCurrentPage%938177643.body
}

void ZDDocument::SetCurrentPage( int iPage, int DocumentIndex )
{
    //## begin ZDDocument::SetCurrentPage%908460233.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetCurrentPage( iPage );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetCurrentPage( iPage );
    }
    //## end ZDDocument::SetCurrentPage%908460233.body
}

ZASchemaManager& ZDDocument::GetSchema( int DocumentIndex )
{
    //## begin ZDDocument::GetSchema%913970076.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetSchema();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetSchema();
    //## end ZDDocument::GetSchema%913970076.body
}

void ZDDocument::ShowDocumentData( int DocumentIndex )
{
    //## begin ZDDocument::ShowDocumentData%914146144.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ShowDocumentData();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->ShowDocumentData();
    }
    //## end ZDDocument::ShowDocumentData%914146144.body
}

void ZDDocument::HideDocumentData( int DocumentIndex )
{
    //## begin ZDDocument::HideDocumentData%914146145.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->HideDocumentData();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->HideDocumentData();
    }
    //## end ZDDocument::HideDocumentData%914146145.body
}

BOOL ZDDocument::DocumentDataIsVisible( int DocumentIndex )
{
    //## begin ZDDocument::DocumentDataIsVisible%914146151.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->DocumentDataIsVisible();
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->DocumentDataIsVisible();
    }

    return FALSE;
    //## end ZDDocument::DocumentDataIsVisible%914146151.body
}

ZAFontManager& ZDDocument::GetFontManager( int DocumentIndex )
{
    //## begin ZDDocument::GetFontManager%914353652.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetFontManager();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetFontManager();
    //## end ZDDocument::GetFontManager%914353652.body
}

ZAStyleManager& ZDDocument::GetStyleManager( int DocumentIndex )
{
    //## begin ZDDocument::GetStyleManager%914353653.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        return GetActiveDocumentData()->GetStyleManager();
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetStyleManager();
    //## end ZDDocument::GetStyleManager%914353653.body
}

BOOL ZDDocument::DocumentDataIsReadOnly( int DocumentIndex ) const
{
    //## begin ZDDocument::DocumentDataIsReadOnly%936298275.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->IsReadOnly();
        }

        return TRUE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->IsReadOnly();
    }

    return TRUE;
    //## end ZDDocument::DocumentDataIsReadOnly%936298275.body
}

void ZDDocument::DocumentDataSetAsReadOnly( BOOL value, int DocumentIndex )
{
    //## begin ZDDocument::DocumentDataSetAsReadOnly%936298276.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetAsReadOnly( value );
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->SetAsReadOnly( value );
    }
    //## end ZDDocument::DocumentDataSetAsReadOnly%936298276.body
}

BOOL ZDDocument::DocumentDataIsStandardForm( int DocumentIndex ) const
{
    //## begin ZDDocument::DocumentDataIsStandardForm%936298277.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->IsStandardForm();
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->IsStandardForm();
    }

    return FALSE;
    //## end ZDDocument::DocumentDataIsStandardForm%936298277.body
}

CStringArray* ZDDocument::GetObjectFieldNameArrayOfDocument( int DocumentIndex ) const
{
    //## begin ZDDocument::GetObjectFieldNameArrayOfDocument%948540874.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->GetObjectFieldNameArray();
        }

        return NULL;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->GetObjectFieldNameArray();
    }

    return NULL;
    //## end ZDDocument::GetObjectFieldNameArrayOfDocument%948540874.body
}

bool ZDDocument::BuildObjectFieldNameArrayOfDocument( int DocumentIndex )
{
    //## begin ZDDocument::BuildObjectFieldNameArrayOfDocument%948540875.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->BuildObjectFieldNameArray();
        }

        return false;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->BuildObjectFieldNameArray();
    }

    return false;
    //## end ZDDocument::BuildObjectFieldNameArrayOfDocument%948540875.body
}

BOOL ZDDocument::DocumentDataIsInternalKeyEqualTo( const CString Key, int DocumentIndex )
{
    //## begin ZDDocument::DocumentDataIsInternalKeyEqualTo%936298278.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->IsInternalKeyEqualTo( Key );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->IsInternalKeyEqualTo( Key );
    }

    return FALSE;
    //## end ZDDocument::DocumentDataIsInternalKeyEqualTo%936298278.body
}

inline BOOL ZDDocument::CheckMultiColumnMemberField( PlanFinObject* obj, int DocumentIndex )
{
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            return GetActiveDocumentData()->CheckMultiColumnMemberField( obj );
        }

        return FALSE;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        return GetDocumentDataAt( DocumentIndex )->CheckMultiColumnMemberField( obj );
    }

    return FALSE;
}

void ZDDocument::StartCalcTimer( int DocumentIndex )
{
    //## begin ZDDocumentRead::StartCalcTimer%917889606.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->StartCalcTimer();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->StartCalcTimer();
    }
    //## end ZDDocumentRead::StartCalcTimer%917889606.body
}

void ZDDocument::ResetCalcTimer( int DocumentIndex )
{
    //## begin ZDDocumentRead::ResetCalcTimer%902943942.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->ResetCalcTimer();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetDocumentDataAt( DocumentIndex )->ResetCalcTimer();
    }
    //## end ZDDocumentRead::ResetCalcTimer%902943942.body
}

void ZDDocument::SchemaListHasChanged( int DocumentIndex )
{
    //## begin ZDDocumentRead::SchemaListHasChanged%907776828.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SchemaListHasChanged();
        }

        return;
    }

    if ( GetDocumentDataAt( DocumentIndex ) )
    {
        GetActiveDocumentData()->SchemaListHasChanged();
    }
    //## end ZDDocumentRead::SchemaListHasChanged%907776828.body
}

void ZDDocument::SetEditedObject( PlanFinObject* pObj, int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::SetEditedObject%907776834.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        if ( GetActiveDocumentData() )
        {
            GetActiveDocumentData()->SetEditedObject( pObj );
        }

        return;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    GetDocumentDataAt( DocumentIndex )->SetEditedObject( pObj );
    //## end ZDDocumentReadWrite::SetEditedObject%907776834.body
}

PlanFinObject* ZDDocument::GetEditedObject( BOOL bCheckPage, int DocumentIndex )
{
    //## begin ZDDocumentReadWrite::GetEditedObject%907776835.body preserve=yes
    if ( DocumentIndex == -1 )
    {
        return ( GetActiveDocumentData() ) ? GetActiveDocumentData()->GetEditedObject( bCheckPage ) : NULL;
    }

    ASSERT( GetDocumentDataAt( DocumentIndex ) );
    return GetDocumentDataAt( DocumentIndex )->GetEditedObject( bCheckPage );
    //## end ZDDocumentReadWrite::GetEditedObject%907776835.body
}

void ZDDocument::CreateAutomaticNewName( PlanFinObject* pObj )
{
    pObj->m_strObjName = GetAutomaticNewName( pObj );
}

void ZDDocument::CopyObjectToClipBoard( PlanFinObject* pObj )
{
    if ( pObj )
    {
        m_pClipBoardObject = pObj->Clone();
    }
}

CString ZDDocument::GetAutomaticNewName( PlanFinObject* pObj, int DocumentIndex )
{
    ZDDocumentData* pDocData = NULL;

    if ( DocumentIndex == -1 )
    {
        ASSERT( GetActiveDocumentData() );
        pDocData = GetActiveDocumentData();
    }
    else
    {
        ASSERT( GetDocumentDataAt( DocumentIndex ) );
        pDocData = GetDocumentDataAt( DocumentIndex );
    }

    ASSERT( pDocData );

    // Test the class type
    if( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "ANumbered" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNLine ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Ln" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNRect ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Rct" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNNumbered ) ) )
    {
        ASSERT( FALSE );
        return pDocData->BuildAutomaticNewName( _T( "Numb" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNStatic ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Stc" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNTime ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Tm" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNNumbEdit ) ) )
    {
        ASSERT( FALSE );
        return pDocData->BuildAutomaticNewName( _T( "NumbEdt" ) );
    }
    else if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNMaskString ) ) )
    {
        if ( ( (PLFNString*)pObj )->GetKeepHistory() )
        {
            return pDocData->BuildAutomaticNewName( _T( "MskTxt" ) );
        }

        return pDocData->BuildAutomaticNewName( _T( "MskTxtHist" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNBoundText ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "BndTxt" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNStringHistory ) ) )
    {
        ASSERT( FALSE );
        return pDocData->BuildAutomaticNewName( _T( "StrHist" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNString ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Str" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNNumHistory ) ) )
    {
        ASSERT( FALSE );
        return pDocData->BuildAutomaticNewName( _T( "$NumHist" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNNumbNumEdit ) ) )
    {
        ASSERT( FALSE );
        return pDocData->BuildAutomaticNewName( _T( "$NumbNumEdt" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "$Number" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNSquare ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Squ" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNText ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Text" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNAscii ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Ascii" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNRadio ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Radio" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNCheck ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Chk" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNBitmap ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Bmp" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNGraphic ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "Ascii" ) );
    }
    else if( pObj->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
    {
        return pDocData->BuildAutomaticNewName( _T( "MultiC" ) );
    }
    return _T( "" );
}

void ZDDocument::OnPageRecalculate()
{
    // Check read-only mode
    if ( IsReadOnlyAtRuntime() )
    {
        return;
    }

    AfxGetMainWnd()->SendMessageToDescendants( ID_CALCULATE_MESSAGE, 0, 0 );
}

void ZDDocument::OnPageNext()
{
    if ( GetCurrentPage() + 1 <= GetMaxPage() )
    {
        SetCurrentPage( GetCurrentPage() + 1 );
        CalculateAllFormula( GetMainView() );

        // Kill the current focus if on edit mode
        ::SetFocus( NULL );
        UpdateAllViews(NULL);
    }
}

void ZDDocument::OnPagePrev()
{
    if ( GetCurrentPage() - 1 >= 1 )
    {
        SetCurrentPage( GetCurrentPage() - 1 );
        CalculateAllFormula( GetMainView() );

        // Kill the current focus if on edit mode
        ::SetFocus( NULL );
        UpdateAllViews(NULL);
    }
}

void ZDDocument::OnUpdatePageNext( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( GetCurrentPage() < GetMaxPage() );
}

void ZDDocument::OnUpdatePagePrev( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( GetCurrentPage() > 1 );
}

void ZDDocument::OnFileNext()
{
    int NextIndex = NextVisibleDocumentAvailable( GetActiveDocumentIndex() );

    if ( NextIndex != -1 )
    {
        ChangeCurrentFile( NextIndex, TRUE );
        CalculateAllFormula( GetMainView() );

        // Kill the current focus if on edit mode
        ::SetFocus( NULL );
        UpdateAllViews( NULL );
    }
}

void ZDDocument::OnUpdateFileNext( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( NextVisibleDocumentAvailable( GetActiveDocumentIndex() ) != -1 );
}

void ZDDocument::OnFilePrev()
{
    int PreviousIndex = PreviousVisibleDocumentAvailable( GetActiveDocumentIndex() );

    if ( PreviousIndex != -1 )
    {
        ChangeCurrentFile( PreviousIndex, TRUE );
        CalculateAllFormula( GetMainView() );

        // Kill the current focus if on edit mode
        ::SetFocus( NULL );
        UpdateAllViews( NULL );
    }
}

void ZDDocument::OnUpdateFilePrev( CCmdUI* pCmdUI )
{
    pCmdUI->Enable( PreviousVisibleDocumentAvailable( GetActiveDocumentIndex() ) != -1 );
}

void ZDDocument::OnPageRefresh()
{
    UpdateAllViews( NULL );
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocument diagnostics

#ifdef _DEBUG
void ZDDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void ZDDocument::Dump( CDumpContext& dc ) const
{
    CDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDDocument serialization

void ZDDocument::SerializeDocumentDataArray( CArchive& ar )
{
    //## begin ZDDocumentRead::SerializeDocumentDataArray%914077262.body preserve=yes
    if ( ar.IsStoring() )
    {
        SerializeDocumentDataArrayWrite( ar );
    }
    else
    {
        SerializeDocumentDataArrayRead( ar );
    }
    //## end ZDDocumentRead::SerializeDocumentDataArray%914077262.body
}

void ZDDocument::SerializeDocumentDataArrayRead( CArchive& ar )
{
    //## begin ZDDocumentRead::SerializeDocumentDataArrayRead%914077263.body preserve=yes
    m_DocumentDataArray.Serialize( ar );

    for ( size_t i = 0; i < GetDocumentDataCount(); ++i )
    {
        GetDocumentDataAt( i )->SetpDocument( this );
    }
    //## end ZDDocumentRead::SerializeDocumentDataArrayRead%914077263.body
}

void ZDDocument::SerializeDocumentDataArrayWrite( CArchive& ar )
{
    //## begin ZDDocumentReadWrite::SerializeDocumentDataArrayWrite%914077265.body preserve=yes
    // Do nothing more than serializing the array of pointer.
    m_DocumentDataArray.Serialize( ar );
    //## end ZDDocumentReadWrite::SerializeDocumentDataArrayWrite%914077265.body
}

void ZDDocument::SerializeWrite( CArchive& ar )
{
    //## begin ZDDocumentReadWrite::SerializeWrite%902579794.body preserve=yes
    // It is important to initialize all object pointers again.
    InitializeAllObjectPointers();

    // Check if all fonts still available
    CheckDocumentFontAndStyle();

    // Call the base class for serialization
    ZDBaseDocument::Serialize( ar );

    CalculateForecastedObjectCount();
    
    ar << (WORD)m_iObjectCounter;

    // Serialize the Active Document Index
    // Version 17 directly as int and not WORD
    ar << m_ActiveDocumentIndex;

    // Serialize the document data array
    SerializeDocumentDataArray( ar );

    // Serialize document options
    ar << GetDocOptions();

    // Serialize the history manager
    GetHistoryValueManager().Serialize( ar );

    // Serialize the synchronization filename
    ar << m_SynchronizationFileName;
    //## end ZDDocumentReadWrite::SerializeWrite%902579794.body
}

void ZDDocument::SerializeRead( CArchive& ar )
{
    // Read informations
    // Test if the stamp has been set
    // for next generation of files
    WORD            wStamp            = 0xFFFF;
    CString            SchemaName;
    ZDDocumentData*    pNewDocument    = NULL;

    TRY
    {
        ZDBaseDocument::Serialize( ar );

        WORD wTemp;
        ar >> wTemp;
        m_iObjectCounter = (int)wTemp;

        if ( GetDocumentStamp().GetInternalVersion() < 11 )
        {
            ar >> SchemaName;
        }
    }
    CATCH( CArchiveException, e )
    {
        // Set for more recent file
        if ( e->m_cause == CArchiveException::badSchema )
        {
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_FILEGENERATEDNEWERVER, MB_OK );
            THROW_LAST();
        }

        wStamp                = 0;
        m_iObjectCounter    = (int)wStamp;

        // Put the default schema name
        SchemaName            = szOriginalSchema;
    }
    END_CATCH

    if ( GetDocumentStamp().GetInternalVersion() < 11 )
    {
        pNewDocument = new ZDDocumentData( this );

        // Copy the file stamp.
        pNewDocument->GetStamp() = (ZDStamp&)GetDocumentStamp();
        pNewDocument->SetCurrentSchema( SchemaName );
        
        // Finally, add the document data pointer
        if ( !AddDocumentData( pNewDocument ) )
        {
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_FILECORRUPTED, MB_OK );
        }

        SetActiveDocumentIndex( 0 );
    }

    if ( GetDocumentStamp().GetInternalVersion() >= 11 )
    {
        if ( GetDocumentStamp().GetInternalVersion() < 17 )
        {
            // Serialize the Active Document Index
            WORD wValue;
            ar >> wValue;

            if ( wValue == 0xFFFF )
            {
                m_ActiveDocumentIndex = -1;
            }
            else
            {
                m_ActiveDocumentIndex = (int)wValue;
            }
        }
        else
        {
            ar >> m_ActiveDocumentIndex;
        }

        // Serialize the document data array
        SerializeDocumentDataArray( ar );
    }

    if ( GetDocumentStamp().GetInternalVersion() < 11 && pNewDocument )
    {
        if ( GetDocumentStamp().GetInternalVersion() >= 4 )
        {
            // Serialize the FontManager
            pNewDocument->GetFontManager().Serialize( ar );

            // Serialize the StyleManager
            pNewDocument->GetStyleManager().Serialize( ar );
        }
    }

    if ( GetDocumentStamp().GetInternalVersion() < 11 && pNewDocument )
    {
        TRY
        {
            // Serialize the list
            pNewDocument->GetObjectList().Serialize( ar );
        }
        CATCH( CArchiveException, e )
        {
            if ( wStamp == 0xFFFF )
            {
                MsgBox mbox;
                mbox.DisplayMsgBox( IDS_FILECORRUPTED, MB_OK );
                THROW_LAST();
            }
        }
        END_CATCH
    }

    if ( GetDocumentStamp().GetInternalVersion() < 11 && pNewDocument )
    {
        TRY
        {
            if ( wStamp == 0xFFFF )
            {
                pNewDocument->GetSchema().Serialize( ar );
            }
            else
            {
                pNewDocument->GetSchema().ReadSerializeOldFormat( ar );
            }
        }
        CATCH( CArchiveException, e )
        {
            if ( wStamp == 0xFFFF )
            {
                MsgBox mbox;
                mbox.DisplayMsgBox( IDS_FILECORRUPTED );
                THROW_LAST();
            }

            // Not found then try to initialize the variable
            // by searching certain information in the file
            // to differentiate the type.
            m_wVersionNumber = def_Version;
        }
        END_CATCH
    }

    // Serialize document options
    // Read information
    if ( GetDocumentStamp().GetInternalVersion() >= 5 )
    {
        ar >> m_DocOptions;
    }

    // Serialize the history manager
    if ( GetDocumentStamp().GetInternalVersion() >= 9 )
    {
        GetHistoryValueManager().Serialize( ar );
    }

    // Serialize the synchronization filename
    if ( GetDocumentStamp().GetInternalVersion() >= 10 )
    {
        ar >> m_SynchronizationFileName;
    }

    // CHECKS
    if ( GetDocumentStamp().GetInternalVersion() < 11 && pNewDocument )
    {
        // If the counter does not correspond
        // to the counter list there is a problem
        // Thus signal the user to attach the
        // formulary to a new template.
        if ( GetForecastedObjectCount() != pNewDocument->GetObjectList().GetCount() )
        {
            // Assign the counter list
            SetForecastedObjectCount( pNewDocument->GetObjectCount() );

            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_FILEPROBLEM, MB_OK );
        }

        if ( pNewDocument->GetStamp().GetTemplate().IsEmpty() )
        {
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_TEMPLATEPROBLEM, MB_OK );
        }
    }

    // After having read all elements,
    // do not forget to initialize the associations
    InitializeAllObjectPointers();

    // Create all file for all file buffered
    CreateAllTemporaryFileFromBuffer();

    // Initialize all member of multi-column fields
    AssignAllMultiColumnMemberFields();
}

//## Other Operations (implementation)
void ZDDocument::Serialize( CArchive& ar )
{
    //## begin ZDDocumentReadWrite::Serialize%902579793.body preserve=yes
    if ( ar.IsStoring() )
    {
        SerializeWrite( ar );
    }
    else
    {
        SerializeRead( ar );
    }
    //## end ZDDocumentReadWrite::Serialize%902579793.body
}
