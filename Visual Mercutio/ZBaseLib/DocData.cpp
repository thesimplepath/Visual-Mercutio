//## begin module%3678E29D0317.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3678E29D0317.cm

//## begin module%3678E29D0317.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3678E29D0317.cp

//## Module: DocData%3678E29D0317; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\DocData.cpp

//## begin module%3678E29D0317.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3678E29D0317.additionalIncludes

//## begin module%3678E29D0317.includes preserve=yes
//## end module%3678E29D0317.includes

// DocData
#include "DocData.h"
//## begin module%3678E29D0317.declarations preserve=no
//## end module%3678E29D0317.declarations

//## begin module%3678E29D0317.additionalDeclarations preserve=yes

#include "ZAObject.h"
#include "PlanFObj.h"
#include "ZABnText.h"
#include "ZARadio.h"
#include "ZACheck.h"
#include "ZABitmap.h"
#include "ZASquare.h"
#include "ZANumbrd.h"
#include "ZAMultiC.h"
#include "Obsolete.h"
#include "PLFNBackImage.h"
#include "ZBFldCol.h"

// FileBuf
#include "FileBuf.h"

// FieldRep
#include "FieldRep.h"

#include "ZBTokenizer.h"
#include "MsgBox.h"

// BObjUtil
#include "PSS_ObjectUtility.h"

#include "ZIView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 24 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZDDocumentData, CObject, g_DefVersion )

#include "ZDDoc.h"
//## end module%3678E29D0317.additionalDeclarations

// Class ZDDocumentData 
ZDDocumentData::ZDDocumentData ( ZDDocument* pDocument )
    : m_bFlagElapsedTime    ( FALSE ),
      m_tmEndCalculateTime    ( CTime::GetCurrentTime() ),
      m_IsVisible            ( TRUE ),
      m_ReadOnlyAtRuntime    ( FALSE ),
      m_pDocument            ( pDocument ),
      m_iPageMax            ( 0 ),
      m_pCurrentEditedObject( NULL ),
      m_iCurrentPage        ( 1 ),
      m_pFileBuffer            ( NULL ),
      m_LastTabOrder        ( 0)
{
    m_BinaryDrawMessage.LoadString( IDS_BINARYDOC_DRAWMESSAGE );
}

ZDDocumentData::~ZDDocumentData()
{
    DeleteAllObjects();
    DeleteTemporaryFile();
}

ZDDocumentData::ZDDocumentData( const ZDDocumentData &right )
{
    *this = right;
}

const ZDDocumentData & ZDDocumentData::operator=( const ZDDocumentData &right )
{
    m_ReadOnlyAtRuntime        = right.m_ReadOnlyAtRuntime;
    m_iCurrentPage            = right.m_iCurrentPage;
    m_tmEndCalculateTime    = right.m_tmEndCalculateTime;
    m_Stamp                    = right.m_Stamp;
    m_Position                = NULL;
    m_Schema                = right.m_Schema;
    m_sCurrentSchema        = right.m_sCurrentSchema;
    m_iPageMax                = right.m_iPageMax;
    m_pCurrentEditedObject    = NULL;
    m_bFlagElapsedTime        = right.m_bFlagElapsedTime;
    m_pDocument                = right.m_pDocument;
    m_IsVisible                = right.m_IsVisible;

    m_FontManager            = right.m_FontManager;
    m_StyleManager            = right.m_StyleManager;

    if ( right.m_pFileBuffer )
    {
        m_pFileBuffer = right.m_pFileBuffer->Clone();
    }
    else
    {
        m_pFileBuffer = NULL;
    }
    
    // Copy elements
    PlanFinObject    *obj;
    POSITION        Position;
    
    Position = ( (ZDDocumentData &)right ).GetObjectList().GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)( (ZDDocumentData &)right ).GetObjectList().GetNext( Position );
        m_ObjElements.AddTail( obj->Clone() );
    }

    return *this;
}

//## Other Operations (implementation)
ZAFormula* ZDDocumentData::GetFormula ( const CString& sName )
{
    //## begin ZDDocumentData::GetFormula%913885081.body preserve=yes
    ZAFormula*    obj;
    POSITION    Position = GetSchema().GetFormulaList( GetCurrentSchema() )->GetHeadPosition();

    while ( Position )
    {
        obj = (ZAFormula*)GetSchema().GetFormulaList( GetCurrentSchema() )->GetNext( Position );

        if ( obj && obj->m_sObjectName == sName )
        {
            return obj;
        }
    }

    return NULL;
    //## end ZDDocumentData::GetFormula%913885081.body
}

PlanFinObject* ZDDocumentData::GetObjectPtr ( CString& strName    )
{
    //## begin ZDDocumentData::GetObjectPtr%913885082.body preserve=yes
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        if ( obj && obj->m_strObjName == strName )
        {
            return( obj );
        }
    }

    return NULL;
    //## end ZDDocumentData::GetObjectPtr%913885082.body
}

PlanFinObject* ZDDocumentData::GetSelectedObject ( BOOL bCheckPage )
{
    //## begin ZDDocumentData::GetSelectedObject%913885089.body preserve=yes
    PlanFinObject    *obj;

    // Retreive the current page
    int                iPage = GetCurrentPage();

    // Search wich element is selected
    if( ( obj = GetHead() ) == NULL )
    {
        return NULL;
    }

    do
    {
        if ( bCheckPage && obj->GetObjectPage() != iPage )
        {
            continue;
        }

        if( obj->IsSelectObject() )
        {
            return obj;
        }
    }
    while( ( obj = GetNext() ) != NULL );

    return GetEditedObject( bCheckPage );
    //## end ZDDocumentData::GetSelectedObject%913885089.body
}

void ZDDocumentData::CheckFormulaObject ( PlanFinObject* pOld, PlanFinObject* pNew )
{
    //## begin ZDDocumentData::CheckFormulaObject%913885106.body preserve=yes
    ZAFormula*    obj;
    POSITION    Position = GetSchema().GetFormulaList( GetCurrentSchema() )->GetHeadPosition();
    
    while ( Position )
    {
        obj = (ZAFormula*)GetSchema().GetFormulaList( GetCurrentSchema() )->GetNext( Position );

        if ( obj && obj->m_ResultObject == pOld )
        {
            obj->m_ResultObject = pNew;
        }
    }
    //## end ZDDocumentData::CheckFormulaObject%913885106.body
}

BOOL ZDDocumentData::ObjectExist ( const CString sName )
{
    //## begin ZDDocumentData::ObjectExist%913885093.body preserve=yes
    POSITION        Position;
    PlanFinObject  *objTemp = NULL;

    if ( ( Position = GetObjectList().GetHeadPosition() ) != NULL )
    {
        while ( Position != NULL )
        {
            objTemp = (PlanFinObject *)GetObjectList().GetNext( Position );

            // If the element has the same, then extract the number
            if ( objTemp->m_strObjName == sName )
            {
                return TRUE;
            }
        }
    }

    return FALSE;
    //## end ZDDocumentData::ObjectExist%913885093.body
}

void ZDDocumentData::InitializeAllAssociations ()
{
    //## begin ZDDocumentData::InitializeAllAssociations%913885095.body preserve=yes
    POSITION        Position;
    PlanFinObject    *objTemp = NULL;

    Position = GetObjectList().GetHeadPosition();

    while ( Position != NULL )
    {
        objTemp = (PlanFinObject *)GetObjectList().GetNext( Position );

        // If the object is a number + has an association
        if ( objTemp->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
        {
            ( (PLFNLong*)objTemp )->GetAssociations().InitializeFormulaAssociations( *this );
        }
    }
    //## end ZDDocumentData::InitializeAllAssociations%913885095.body
}

void ZDDocumentData::CalculateAllFormula ( CView* pView, BOOL AllPages )
{
    //## begin ZDDocumentData::CalculateAllFormula%913885096.body preserve=yes
    if ( !GetSchema().GetFormulaList( GetCurrentSchema() ) )
    {
        return;
    }

    CDC* pDC = NULL;

    if ( pView )
    {
        pDC = pView->GetDC();
        ASSERT( pDC );
    }

    ZAFormula* pFormula;

    if ( pView && ::IsWindow( pView->GetSafeHwnd() ) &&  IsWindowVisible( pView->GetSafeHwnd() ) )
    {
        pView->OnPrepareDC( pDC );
    }

    POSITION Position;

    Position = GetSchema().GetFormulaList( GetCurrentSchema() )->GetHeadPosition();

    while( Position )
    {
        pFormula = (ZAFormula*)GetSchema().GetFormulaList( GetCurrentSchema() )->GetNext( Position );

        // Only if the formula is on the same page
        // it is necessary to recalculate
        if ( AllPages || pFormula->GetPage() == GetCurrentPage() )
        {
            // Check if the field has an association
            if ( pFormula->m_ResultObject && ( (PLFNLong*)pFormula->m_ResultObject )->GetCurrentAssociation() )
            {
                // Run through out the list
                for ( register int i = 0; i < ( (PLFNLong*)pFormula->m_ResultObject )->GetCurrentAssociation()->GetCount(); ++i )
                {
                    ZAFormula*  pAssociationFormula = ( (PLFNLong*)pFormula->m_ResultObject )->GetCurrentAssociation()->GetFormulaAt( i );

                    if ( pAssociationFormula )
                    {
                        CalculateFormula( pAssociationFormula, pView, pDC );
                    }
                }

            }
            else
            {
                // Otherwise calculate with the standard formula
                CalculateFormula( pFormula, pView, pDC );
            }
        }
    }
    // Generate a WM_PAINT message
    if ( pView )
    {
        pView->UpdateWindow();
        VERIFY( pView->ReleaseDC(pDC) );
    }

    // Start the calc timer
    StartCalcTimer();
    //## end ZDDocumentData::CalculateAllFormula%913885096.body
}

BOOL ZDDocumentData::CalculateFormula ( ZAFormula* pFormula, CWnd* pWnd, CDC* pDC )
{
    //## begin ZDDocumentData::CalculateFormula%913885107.body preserve=yes
    Parser prs;

    // Check if the field is a PLFNLong
    // The only way to calculate is on calculated fields
    // Because the user can change the type,
    // it is necessary to test
    // Test if the keep value is set. If it is set do not calculate
    if ( !pFormula->m_ResultObject                                            ||
         !pFormula->m_ResultObject->IsKindOf( RUNTIME_CLASS( PLFNLong ) )    ||
         ( (PLFNLong*)pFormula->m_ResultObject )->KeepTheValue() )
    {
        return( FALSE );
    }

    // Retreive the previous value to compare
    // with the new one. If the value has changed
    // then notify the controler for the change of
    // the field
    double    dPreviousValue    = pFormula->m_ResultObject->GetValue();
    double    dNewValue        = prs.StringParser( (const char *)pFormula->m_sExtractedFormula, &GetObjectList() );

    // To notify the view that on field change
    // Pass the adress of the object
    // then the routine that proceed the message
    // can know wich object has changed
    if( ( (PLFNLong*)pFormula->m_ResultObject )->GetRoundedValue()    &&
          ( (PLFNLong*)pFormula->m_ResultObject )->IsRounded() )
    {
        // Function floor first integer less than
        // Function ceil first integer greater than
        dNewValue = ceil( dNewValue / ( (PLFNLong*)pFormula->m_ResultObject )->GetRoundedValue() ) * ( (PLFNLong*)pFormula->m_ResultObject )->GetRoundedValue();
    }

    if( dNewValue != pFormula->m_ResultObject->GetValue() )
    {
        pFormula->m_ResultObject->SetValue( dNewValue );
        AfxGetMainWnd( )->SendMessageToDescendants( ID_FIELD_CHANGE, 0, (LPARAM)pFormula->m_ResultObject );

        if ( pWnd && pDC && GetCurrentPage() == pFormula->m_ResultObject->GetObjectPage() )
        {
            pFormula->m_ResultObject->InvalidateObjectRect( pDC, pWnd );
        }

        return( TRUE );
    }

    return( FALSE );
    //## end ZDDocumentData::CalculateFormula%913885107.body
}

void ZDDocumentData::CheckForClearCalcField ( CView* pView )
{
    //## begin ZDDocumentData::CheckForClearCalcField%913885097.body preserve=yes
    if ( m_bFlagElapsedTime )
    {
        CTimeSpan tmElapsed = CTime::GetCurrentTime() - m_tmEndCalculateTime;

        if ( tmElapsed.GetSeconds() > 5 )
        {
            // Clear all flags in the field
            PlanFinObject *pObj;

            // Redraw only the that must be refreshed
            CDC* pDC = NULL;

            if ( pView )
            {
                pDC = pView->GetDC();
                ASSERT( pDC );
            }

            if ( pView && ::IsWindow( pView->GetSafeHwnd() ) &&  IsWindowVisible( pView->GetSafeHwnd() ) )
            {
                pView->OnPrepareDC( pDC );
            }

            POSITION Position;
            Position = GetObjectList().GetHeadPosition( );

            while ( Position )
            {
                pObj = (PlanFinObject*)GetObjectList().GetNext( Position );

                if ( pObj->HasBeenChanged() )
                {
                    pObj->SetHasBeenChanged( FALSE );

                    // Redraw the object only if he is 
                    // positionned on the current page
                    if ( pView && pDC && GetCurrentPage() == pObj->GetObjectPage() )
                    {
                        pObj->DrawObject( pDC, (ZIView*)pView );
                    }
                }
            }

            if ( pDC )
            {
                VERIFY( pView->ReleaseDC( pDC ) );
            }
            else
            {
                // If no DC, no update, then update all views
                m_pDocument->UpdateAllViews( NULL );
            }

            ResetCalcTimer();
        }
    }
    //## end ZDDocumentData::CheckForClearCalcField%913885097.body
}

void ZDDocumentData::ChangeCurrentSchema ( const CString& sName, BOOL bNotify )
{
    //## begin ZDDocumentData::ChangeCurrentSchema%913885099.body preserve=yes
    SetCurrentSchema( sName );

    // First, clear the current associations
    ClearCurrentAssociation();

    // Second, change fields for calculation function of the new schema
    ChangeFieldForCalculation();

    if ( bNotify )
    {
        SchemaListHasChanged();
        ASSERT( m_pDocument );
        m_pDocument->UpdateAllViews( NULL );
    }
    //## end ZDDocumentData::ChangeCurrentSchema%913885099.body
}

void ZDDocumentData::ClearCurrentAssociation ()
{
    //## begin ZDDocumentData::ClearCurrentAssociation%913885100.body preserve=yes
    PlanFinObject  *pObjTemp;

    if( ( pObjTemp = GetHead() ) != NULL )
    {
        do
        {
            // If the object is a number
            if ( pObjTemp->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
            {
                // Clear association icon
                ( (PLFNLong*)pObjTemp )->SetIconDisplayType();

                // Check if the field has an association and clear his association
                if ( ( (PLFNLong*)pObjTemp )->GetCurrentAssociation() )
                {
                    ( (PLFNLong*)pObjTemp )->ClearCurrentAssociation();
                }
            }
        }
        while ( (pObjTemp=GetNext() ) != NULL );
    }
    //## end ZDDocumentData::ClearCurrentAssociation%913885100.body
}

void ZDDocumentData::ChangeFieldForCalculation ()
{
    //## begin ZDDocumentData::ChangeFieldForCalculation%913885101.body preserve=yes
    PlanFinObject *pObjTemp;
    
    // Run through the list for long field with no
    // current associations
    if( ( pObjTemp = GetHead() ) != NULL )
    {
        do
        {
            // If the object is a number
            if ( pObjTemp->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
            {
                // Clear association icon
                ( (PLFNLong*)pObjTemp )->SetIconDisplayType();

                // Check if the field has no association
                if ( !( (PLFNLong*)pObjTemp )->GetCurrentAssociation() )
                {
                    // If no assocation do tests
                    // Try to find it within the scenario as a result field
                    if ( IsCalculatedFieldInSchema( pObjTemp ) )
                    {
                        ( (PLFNLong*)pObjTemp )->SetCalculatedField();
                    }
                    else
                    {
                        ( (PLFNLong*)pObjTemp )->SetCalculatedField( FALSE );

                        // Remove the keep value flag
                        ( (PLFNLong*)pObjTemp )->SetKeepTheValue( FALSE );
                    }
                }
            }
        }
        while ( ( pObjTemp = GetNext() ) != NULL );
    }

    // Run through the list for long field with
    // current associations
    if( ( pObjTemp = GetHead() ) != NULL )
    {
        do
        {
            // If the object is a number
            if ( pObjTemp->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
            {
                // Check if the field has an association
                if ( ( (PLFNLong*)pObjTemp )->GetCurrentAssociation() )
                {
                    // First remove calculate field flag
                    ( (PLFNLong*)pObjTemp )->SetCalculatedField( FALSE );

                    // Remove the keep value flag
                    ( (PLFNLong*)pObjTemp )->SetKeepTheValue( FALSE );

                    // If association change field in the association
                    ChangeCalculatedFieldInAssociation( ( (PLFNLong*)pObjTemp )->GetCurrentAssociation() );
                }
            }
        }
        while ( ( pObjTemp = GetNext() ) != NULL );
    }
    //## end ZDDocumentData::ChangeFieldForCalculation%913885101.body
}

BOOL ZDDocumentData::IsCalculatedFieldInSchema ( PlanFinObject* pObj )
{
    //## begin ZDDocumentData::IsCalculatedFieldInSchema%913885103.body preserve=yes
    POSITION    Position;
    ZAFormula*    obj;

    // Run through the list of formula and try to find
    // if the object is a result object
    Position = GetSchema().GetFormulaList( GetCurrentSchema() )->GetHeadPosition();

    while( Position )
    {
        obj = (ZAFormula*)GetSchema().GetFormulaList( GetCurrentSchema() )->GetNext( Position );

        if ( obj->GetResultObjectPointer() == pObj )
        {
            return TRUE;
        }
    }
    return FALSE;
    //## end ZDDocumentData::IsCalculatedFieldInSchema%913885103.body
}

void ZDDocumentData::RefreshCurrentSchema ()
{
    //## begin ZDDocumentData::RefreshCurrentSchema%913885104.body preserve=yes
    // Second, change fields for calculation function of the new schema
    ChangeFieldForCalculation();
    m_pDocument->UpdateAllViews( NULL );
    //## end ZDDocumentData::RefreshCurrentSchema%913885104.body
}

void ZDDocumentData::ChangeCalculatedFieldInAssociation ( ZAFormulaAssociation* pAssociation )
{
    //## begin ZDDocumentData::ChangeCalculatedFieldInAssociation%913885108.body preserve=yes
    // Run through out the list
    for ( register int i = 0; i < pAssociation->GetCount(); ++i )
    {
        ZAFormula* pAssociationFormula = pAssociation->GetFormulaAt( i );

        if ( pAssociationFormula )
        {
            PlanFinObject* pObj = pAssociationFormula->GetResultObjectPointer();

            if ( pObj && pObj->IsKindOf( RUNTIME_CLASS( PLFNLong ) ) )
            {
                ( (PLFNLong*)pObj )->SetCalculatedField();

                // Set association icon.
                ( (PLFNLong*)pObj )->SetIconDisplayType( AssociationIcon );
            }
        }
    }
    //## end ZDDocumentData::ChangeCalculatedFieldInAssociation%913885108.body
}

void ZDDocumentData::ReplaceCalculatedFields ()
{
    CString label;
    label.LoadString(IDS_AMOUNT_CLASS);

    PlanFinObject* pObjTemp;

    if ((pObjTemp = GetHead()) != NULL)
    {
        do
        {
            // If the object have is calculated
            // change it in number
            if ( pObjTemp->IsKindOf( RUNTIME_CLASS( PLFNCalculated ) ) )
            {
                PlanFinObject* pNewObjTemp = PSS_ObjectUtility::BuildObject(label);

                if ( !pNewObjTemp )
                {
                    return;
                }

                (PLFNLong&)*pNewObjTemp = (PLFNLong*)pObjTemp;

                // Copy all the information not contained in PlanFinObject
                ( (PLFNLong*)pNewObjTemp )->SetHasBeenChanged( FALSE );
                ( (PLFNLong*)pNewObjTemp )->SetCalculatedField( TRUE );

                // If this object was stored as a pointer to the list
                // of formula object, change the pointer
                CheckFormulaObject( pObjTemp, pNewObjTemp );

                // Delete the old object
                if ( !DeleteObject( pObjTemp ) )
                {
                    return;
                }

                if ( !InsertObject( pNewObjTemp ) )
                {
                    return;
                }
            }
        }
        while ( ( pObjTemp = GetNext() ) != NULL );
    }
    //## end ZDDocumentData::ReplaceCalculatedFields%913885115.body
}

int ZDDocumentData::SerializeStampRead ( CArchive& ar, ZDStamp& Stamp )
{
    //## begin ZDDocumentData::SerializeStampRead%913885118.body preserve=yes
    WORD wStamp = 0;

    TRY
    {
        ar >> wStamp;
    }
    CATCH( CArchiveException, e )
    {
        return 0;
    }
    END_CATCH

    // Test if the stamp has been set
    // for next generation of files
    if ( wStamp == 0xFFFF )
    {
        ar >> Stamp;
    }

    return wStamp;
    //## end ZDDocumentData::SerializeStampRead%913885118.body
}

void ZDDocumentData::SerializeRead ( CArchive& ar )
{
    //## begin ZDDocumentData::SerializeRead%913885119.body preserve=yes
    // Read informations
    // Test if the stamp has been set
    // for next generation of files
    WORD    wStamp                = 0xFFFF;
    bool    IsInRecoveryMode    = false;
    CString    SchemaName;

    if ( ( wStamp = SerializeStampRead( ar, GetStamp() ) ) == 0xFFFF )
    {
        ar >> SchemaName;
    }
    else
    {
        SchemaName = g_OriginalSchema;    // Put the default schema name
    }

    SetCurrentSchema( SchemaName );

    if ( GetStamp().GetInternalVersion() >= 14 && GetStamp().GetDocumentDataType() == BinaryDataType )
    {
        ar >> m_pFileBuffer;
    }
    else
    {
        if ( GetStamp().GetInternalVersion() >= 4 )
        {
            // Serialize the FontManager
            GetFontManager().Serialize( ar );

            // Serialize the StyleManager
            GetStyleManager().Serialize( ar );
        }

        if ( GetStamp().GetDocumentDataType() != BinaryDataType )
        {
            TRY
            {
                // Serialize the list
                GetObjectList().Serialize( ar );
            }
            CATCH( CArchiveException, e )
            {
                if ( wStamp == 0xFFFF )
                {
                    MsgBox mbox;

                    if ( mbox.DisplayMsgBox( IDS_FILECORRUPTED_RECOVER, MB_YESNO ) == IDNO )
                    {
                        THROW_LAST();
                    }

                    // Otherwise, try to keep existing information
                    IsInRecoveryMode = true;
                }
            }
            END_CATCH

            TRY
            {
                // Do it if we are not in recovery mode
                if ( IsInRecoveryMode == false )
                {
                    if ( wStamp == 0xFFFF )
                    {
                        GetSchema().Serialize( ar );
                    }
                    else
                    {
                        GetSchema().ReadSerializeOldFormat( ar );
                    }
                }
                else
                {
                    // If in recovery, just create the standard schema
                    GetSchema().CreateStandardEmptySchema();
                }

                // After having read all elements,
                // do not forget to initialize the object pointers
                InitializeAllObjectPointers();
            }
            CATCH( CArchiveException, e )
            {
                if ( wStamp == 0xFFFF )
                {
                    MsgBox mbox;

                    if ( mbox.DisplayMsgBox( IDS_FILECORRUPTED_RECOVER, MB_YESNO ) == IDNO )
                    {
                        THROW_LAST();
                    }

                    // Otherwise, try to keep existing information
                    IsInRecoveryMode = true;
                }
            }
            END_CATCH
        }

        // No binary file data pointer
        m_pFileBuffer = NULL;
    }

    // Do it if we are not in recovery mode
    if ( IsInRecoveryMode == false )
    {
        WORD wValue;
        ar >> wValue;
        m_IsVisible = (BOOL)wValue;
    }
    else
    {
        m_IsVisible = TRUE;
    }

    // CHECKS
    // Signal the user to attach the
    // formulary to a new template.
    if ( GetStamp().GetTemplate().IsEmpty() )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_TEMPLATEPROBLEM, MB_OK );
    }

    // Check now that the object list is coherent
    if ( !CheckObjectList() )
    {
        AfxThrowArchiveException( CArchiveException::generic );
    }

    // If we have switched to recovery mode
    // Display a warning
    if ( IsInRecoveryMode == true )
    {
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_FILECORRUPTED_MISSINGINFO, MB_OK );
    }
    //## end ZDDocumentData::SerializeRead%913885119.body
}

void ZDDocumentData::SerializeStampWrite ( CArchive& ar, ZDStamp& Stamp )
{
    //## begin ZDDocumentData::SerializeStampWrite%913885120.body preserve=yes
    // Sets the document type
    Stamp.SetDocumentFileType( FormDocumentFileType );
    Stamp.SetInternalVersion(g_VersionFile);
    WORD wTemp = 0xFFFF;

    // Put the stamp for differentiate
    // the new generation of files
    ar << wTemp;
    ar << Stamp;
    //## end ZDDocumentData::SerializeStampWrite%913885120.body
}

void ZDDocumentData::SerializeWrite ( CArchive& ar )
{
    //## begin ZDDocumentData::SerializeWrite%913885121.body preserve=yes
    // Write informations
    SerializeStampWrite( ar, GetStamp() );
    ar << GetCurrentSchema();        // Save the current schema

    if ( GetStamp().GetDocumentDataType() == BinaryDataType )
    {
        // The file buffer pointer
        ar << m_pFileBuffer;
    }
    else
    {
        // Serialize the FontManager
        GetFontManager().Serialize( ar );

        // Serialize the StyleManager
        GetStyleManager().Serialize( ar );

        TRY
        {
            // Serialize the list
            GetObjectList().Serialize( ar );
        }
        CATCH( CArchiveException, e )
        {
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_FILECORRUPTED, MB_OK );
            THROW_LAST();
        }
        END_CATCH

        TRY
        {
            GetSchema().Serialize( ar );
        }
        CATCH( CArchiveException, e )
        {
            // In write mode no chance, file corruption
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_FILECORRUPTED );
            THROW_LAST();
        }
        END_CATCH
    }

    ar << (WORD)m_IsVisible;
    //## end ZDDocumentData::SerializeWrite%913885121.body
}

void ZDDocumentData::AssignPredefinedField ()
{
    //## begin ZDDocumentData::AssignPredefinedField%913885122.body preserve=yes
    PlanFinObject *obj;
    PlanFinObject *pObj = NULL;

    if( ( obj = GetHead() ) == NULL )
    {
        return;
    }

    do
    {
        // assign the page field
        if (obj->GetObjectName() == g_pPredefinedField[g_PredefinedFieldPage])
            SetCurrentPageToObject(obj);

        // assign the date field
        if (obj->GetObjectName() == g_pPredefinedField[g_PredefinedFieldDate])
            if(obj->IsKindOf(RUNTIME_CLASS(PLFNTime)))
                ((PLFNTime*)obj)->SetToday();
    }
    while( ( obj = GetNext() ) != NULL );
    //## end ZDDocumentData::AssignPredefinedField%913885122.body
}

BOOL ZDDocumentData::ChangeObjectType ( PlanFinObject*    obj,
                                        const CString&    sName,
                                        const CString&    sFinalValue,
                                        BOOL            bPropagate )
{
    //## begin ZDDocumentData::ChangeObjectType%913885123.body preserve=yes
    // if propagate run through the list of objects
    // and find all similar names
    if ( bPropagate )
    {
        PlanFinObject *pObjTemp;

        if( ( pObjTemp = GetHead() ) != NULL )
        {
            do
            {
                // If the object have the same name
                // and it is not the initial object
                // change it
                if ( pObjTemp != obj && pObjTemp->GetObjectName() == obj->GetObjectName() )
                {
                    PlanFinObject* pNewObjTemp = PSS_ObjectUtility::BuildObject(sName);

                    if ( !pNewObjTemp )
                    {
                        return FALSE;
                    }

                    (PlanFinObject&)*pNewObjTemp = (PlanFinObject*)pObjTemp;

                    // Initialize certain parameters
                    pNewObjTemp->SetFormatType(E_FT_Standard);

                    // If this object was stored as a pointer to the list
                    // of formula object, change the pointer
                    CheckFormulaObject( pObjTemp, pNewObjTemp );
                    pNewObjTemp->ConvertFormatedObject( sFinalValue );

                    // Delete the old object
                    if ( !DeleteObject( pObjTemp ) )
                    {
                        return FALSE;
                    }

                    if ( !InsertObject( pNewObjTemp ) )
                    {
                        return FALSE;
                    }
                }
            }
            while ( ( pObjTemp = GetNext() ) != NULL );
        }
    }

    PlanFinObject* pNewObj = PSS_ObjectUtility::BuildObject(sName);

    if ( !pNewObj )
    {
        return FALSE;
    }

    (PlanFinObject&)*pNewObj = (PlanFinObject*)obj;

    // Initialize certain parameters
    pNewObj->SetFormatType(E_FT_Standard);

    // If this object was stored as a pointer to the list
    // of formula object, change the pointer
    CheckFormulaObject( obj, pNewObj );
    pNewObj->ConvertFormatedObject( sFinalValue );

    // Delete the old object
    if ( !DeleteObject( obj ) )
    {
        return FALSE;
    }

    return InsertObject( pNewObj );
    //## end ZDDocumentData::ChangeObjectType%913885123.body
}

CString ZDDocumentData::BuildAutomaticNewName ( const CString& sPrefix )
{
    //## begin ZDDocumentData::BuildAutomaticNewName%913885124.body preserve=yes
    POSITION        Position;
    char            szName[100];
    long            lCounter        = -1L;
    PlanFinObject    *objTemp        = NULL;
    size_t            PrefixLength    = sPrefix.GetLength();

    if ( ( Position = GetObjectList().GetHeadPosition() ) != NULL )
    {
        while ( Position != NULL )
        {
            objTemp = (PlanFinObject *)GetObjectList().GetNext( Position );

            // If the element has the same, then extract the number
            if ( strncmp( objTemp->m_strObjName, sPrefix, PrefixLength ) == 0 )
            {
                lCounter = __max( atol( (const char*)objTemp->m_strObjName + PrefixLength ), lCounter );
            }
        }
    }

    sprintf( szName, _T( "%s%ld" ), (const char*)sPrefix, lCounter + 1L );

    return szName;
    //## end ZDDocumentData::BuildAutomaticNewName%913885124.body
}

BOOL ZDDocumentData::InsertObject ( PlanFinObject*        obj,
                                    ZBFieldRepository*    pFieldRepository,
                                    BOOL                InsertInGlobalRepository,
                                    BOOL                Refresh                        /*= FALSE*/ )
{
    //## begin ZDDocumentData::InsertObject%913885125.body preserve=yes

    // Insert elements in page order
    POSITION Position, ElementPosition;

    if ( ( ElementPosition = Position = GetObjectList().GetHeadPosition() ) == NULL )
    {
        GetObjectList().AddTail( obj );
        return TRUE;
    }

    PlanFinObject *objTemp = NULL;

    // Sort the element by page too
    // but by Y and X coordinates
    // This option is used for auto-edit
    // to go to the next editable field
    while ( Position != NULL )
    {
        // Save the position of the current element objTemp
        ElementPosition    = Position;
        objTemp            = (PlanFinObject *)GetObjectList().GetNext( Position );

        if ( obj->GetObjectPage() == objTemp->GetObjectPage() )
        {
            if ( obj->GetClientRect().bottom == objTemp->GetClientRect().bottom )
            {
                if ( obj->GetClientRect().left < objTemp->GetClientRect().left )
                {
                    break;
                }
            }
            else if ( obj->GetClientRect().bottom < objTemp->GetClientRect().bottom )
            {
                break;
            }
        }
        else if ( obj->GetObjectPage() < objTemp->GetObjectPage() )
        {
            break;
        }
    }

    if ( !Position && !( obj->GetObjectPage() < objTemp->GetObjectPage() ) )
    {
        GetObjectList().AddTail( obj );
    }
    else
    {
        GetObjectList().InsertBefore( ElementPosition, obj );
    }

    // Rebuild automatic tab order
    AutomaticRebuildTabOrder();

    // Test multi-column field
    CheckMultiColumnMemberField( obj );

    // If should refresh the form
    if ( Refresh && m_pDocument )
    {
        m_pDocument->UpdateAllViews( NULL );
    }

    return TRUE;
    //## end ZDDocumentData::InsertObject%913885125.body
}

BOOL ZDDocumentData::InsertObjectAtHead ( PlanFinObject*        obj,
                                          ZBFieldRepository*    pFieldRepository,
                                          BOOL                    InsertInGlobalRepository,
                                          BOOL                    Refresh                        /*= FALSE*/ )
{
    // Insert elements in page order
    POSITION Position, ElementPosition;

    if ( ( ElementPosition = Position = GetObjectList().GetHeadPosition() ) == NULL )
    {
        GetObjectList().AddHead( obj );
        return TRUE;
    }

    PlanFinObject *objTemp = NULL;

    // Sort the element by page too
    // but by Y and X coordinates
    // This option is used for auto-edit
    // to go to the next editable field
    while ( Position != NULL )
    {
        // Save the position of the current element objTemp
        ElementPosition    = Position;
        objTemp            = (PlanFinObject *)GetObjectList().GetNext( Position );

        if ( obj->GetObjectPage() == objTemp->GetObjectPage() )
        {
            if ( obj->GetClientRect().bottom == objTemp->GetClientRect().bottom )
            {
                if ( obj->GetClientRect().left < objTemp->GetClientRect().left )
                {
                    break;
                }
            }
            else if ( obj->GetClientRect().bottom < objTemp->GetClientRect().bottom )
            {
                break;
            }
        }
        else if ( obj->GetObjectPage() < objTemp->GetObjectPage() )
        {
            break;
        }
    }

    if ( !Position && !( obj->GetObjectPage() < objTemp->GetObjectPage() ) )
    {
        GetObjectList().AddHead( obj );
    }
    else
    {
        GetObjectList().InsertBefore( ElementPosition, obj );
    }

    // Rebuild automatic tab order
    AutomaticRebuildTabOrder();

    // Test multi-column field
    CheckMultiColumnMemberField( obj );

    // If should refresh the form
    if ( Refresh && m_pDocument )
    {
        m_pDocument->UpdateAllViews( NULL );
    }

    return TRUE;
    //## end ZDDocumentData::InsertObject%913885125.body
}

BOOL ZDDocumentData::DeleteObject ( PlanFinObject* obj, BOOL DeleteFromMemory, BOOL Refresh /*= FALSE*/ )
{
    //## begin ZDDocumentData::DeleteObject%913885126.body preserve=yes

    // Delete the object
    POSITION Position = GetObjectList().Find( obj );

    if ( Position != NULL )
    {
        if ( DeleteFromMemory )
        {
            // Before free the element
            // if required
            delete obj;
        }

        GetObjectList().RemoveAt( Position );

        // If should refresh the form
        if ( Refresh && m_pDocument )
        {
            m_pDocument->UpdateAllViews( NULL );
        }

        return TRUE;
    }

    return FALSE;
    //## end ZDDocumentData::DeleteObject%913885126.body
}

BOOL ZDDocumentData::MoveObjectInOrder ( PlanFinObject* obj )
{
    //## begin ZDDocumentData::MoveObjectInOrder%913885127.body preserve=yes
    // First delete the object without deleting the object
    // only from the list, not from the memory
    // and after reinsert it at
    // ordered position
    if ( DeleteObject( obj, FALSE ) )
    {
        return InsertObject( obj );
    }

    return FALSE;
    //## end ZDDocumentData::MoveObjectInOrder%913885127.body
}

BOOL ZDDocumentData::AssignObjectValue ( CString    Name,
                                         CString    Value,
                                         int        Page,
                                         int        PropagationMode,
                                         BOOL        EmptyWhenZero )
{
    //## begin ZDDocumentData::AssignObjectValue%913885128.body preserve=yes
    if (PropagationMode == g_LocateAllDocuments || PropagationMode == g_LocateAllDocumentsEmptyOnly)
        return FALSE;

    // Try to locate the object
    PlanFinObject *pObj;

    if( ( pObj = GetHead() ) != NULL )
    {
        do
        {
            // If the same object name
            if ( pObj->GetObjectName() == Name )
            {    
                // Function of propagation mode
                switch ( PropagationMode )
                {
                    case g_LocatePageOnlyEmptyOnly:
                    {
                        // If after the concerned page, end it is finished
                        if ( pObj->GetObjectPage() > Page )
                        {
                            return TRUE;
                        }

                        // If the object is not empty, continue
                        if ( !pObj->IsEmpty() )
                        {
                            continue;
                        }

                        // All conditions are filled, assign the value
                        break;
                    }

                    case g_LocateForwardPageEmptyOnly:
                    {
                        // If before the page, continue
                        if ( pObj->GetObjectPage() < Page )
                        {
                            continue;
                        }

                        // If the object is not empty, continue
                        if ( !pObj->IsEmpty() )
                        {
                            continue;
                        }

                        // All conditions are filled, assign the value
                        break;
                    }

                    case g_LocateAllPagesEmptyOnly:
                    {
                        // If the object is not empty, continue
                        if ( !pObj->IsEmpty() )
                        {
                            continue;
                        }

                        // All conditions are filled, assign the value
                        break;
                    }

                    case g_LocatePageOnly:
                    {
                        // If after the concerned page, end it is finished
                        if ( pObj->GetObjectPage() > Page )
                        {
                            return TRUE;
                        }

                        // All conditions are filled, assign the value
                        break;
                    }

                    case g_LocateForwardPage:
                    {
                        // If before the page, continue
                        if ( pObj->GetObjectPage() < Page )
                        {
                            continue;
                        }

                        // All conditions are filled, assign the value
                        break;
                    }

                    case g_LocateAllPages:
                    {
                        // All conditions are filled, assign the value
                        break;
                    }

                    default:
                    {
                        return FALSE;
                    }
                }

                // Finally, convert the object without changing his format
                if ( pObj->ConvertFormatedObject( Value, FALSE, EmptyWhenZero ) )
                {
                    // Sends message to advise the change for this object.
                    pObj->SetHasBeenChanged( TRUE );
                    GetpDocument()->SetModifiedFlag( TRUE );
                }
            }
        }
        while( (pObj=GetNext( )) != NULL );

    }

    return TRUE;    // No error
    //## end ZDDocumentData::AssignObjectValue%913885128.body
}

void ZDDocumentData::SetCurrentPageToObject ( PlanFinObject* obj )
{
    //## begin ZDDocumentData::SetCurrentPageToObject%913885130.body preserve=yes
    obj->SetValue( (double)obj->GetObjectPage() );
    //## end ZDDocumentData::SetCurrentPageToObject%913885130.body
}

void ZDDocumentData::DeleteAllObjects ()
{
    //## begin ZDDocumentData::DeleteAllObjects%914061087.body preserve=yes
    while ( !GetObjectList().IsEmpty() )
    {
        delete GetObjectList().GetHead();
        GetObjectList().RemoveHead();
    }
    //## end ZDDocumentData::DeleteAllObjects%914061087.body
}

int ZDDocumentData::CountAndSetPages ()
{
    //## begin ZDDocumentData::CountAndSetPages%914061088.body preserve=yes
    // Retreive the page number.
    // This page number is used to display the object
    // on the right page
    // The test here is to assign the greater number of pages
    PlanFinObject *obj;

    if( ( obj = GetHead() ) == NULL )
    {
        return( 0 );
    }

    SetMaxPage( 0 );

    do
    {
        SetMaxPage( __max( obj->GetObjectPage(), GetMaxPage() ) );
    }
    while( ( obj = GetNext() ) != NULL );

    TRACE1( _T( " Max Pages %d" ), GetMaxPage() );

    return( GetMaxPage() );
    //## end ZDDocumentData::CountAndSetPages%914061088.body
}

PlanFinObject* ZDDocumentData::CloneSelectedObject ()
{
    //## begin ZDDocumentData::CloneSelectedObject%914061089.body preserve=yes
    PlanFinObject *pObj = GetSelectedObject();

    if ( pObj == NULL )
    {
        return NULL;
    }

    return pObj->Clone();
    //## end ZDDocumentData::CloneSelectedObject%914061089.body
}

void ZDDocumentData::RebuildAllAutomaticNumbered ()
{
    //## begin ZDDocumentData::RebuildAllAutomaticNumbered%914061090.body preserve=yes
    int        LevelArray[20];
    memset( &LevelArray, 0, sizeof( LevelArray ) );

    PlanFinObject *pObj;

    if( ( pObj = GetHead() ) != NULL )
    {
        do
        {
            // Search all AutoNumbered objects
            if ( pObj->IsKindOf( RUNTIME_CLASS( PLFNAutoNumbered ) ) )
            {
                // Count only if the element is autonumbered
                if ( ( (PLFNAutoNumbered*)pObj )->GetbAutoCalculate() )
                {
                    LevelArray[ ( (PLFNAutoNumbered*)pObj )->GetiLevel() ] =
                        LevelArray[ ( (PLFNAutoNumbered*)pObj )->GetiLevel() ] + 1;

                    // JMR-MODIF - Le 18 mai 2005 - Conversion explicite d'un nombre en chaîne de caractères
                    // exigée par la nouvelle classe CString.
                    char* myBuffer = new char[18];
                    CString sLevelArray = itoa( LevelArray[0], myBuffer, 10 );
                    delete[] myBuffer;

                    CString sText;
                    sText = sLevelArray + '0';

                    for ( int i=0; i < ( (PLFNAutoNumbered*)pObj )->GetiLevel(); ++i )
                    {
                        // JMR-MODIF - Le 18 mai 2005 - Conversion explicite d'un nombre en chaîne de caractères
                        // exigée par la nouvelle classe CString.
                        char* myBuffer = new char[18];
                        CString sLevelArray = itoa( LevelArray[i + 1], myBuffer, 10 );
                        delete[] myBuffer;

                        sText += '.';
                        sText += sLevelArray + '0';
                    }

                    ( (PLFNAutoNumbered*)pObj )->SetStringTextLevel( sText );
                }
            }
        }
        while( ( pObj = GetNext() ) != NULL );
    }
    //## end ZDDocumentData::RebuildAllAutomaticNumbered%914061090.body
}

void ZDDocumentData::SetCurrentStyle ( const CString& sName )
{
    //## begin ZDDocumentData::SetCurrentStyle%914061093.body preserve=yes
    PlanFinObject  *pObjTemp = GetSelectedObject();

    if ( pObjTemp )
    {
        // When assign new style, clear a specific font assigned
        pObjTemp->SethStyle( m_pDocument->GetStyleManager().FindStyle( sName ) );

        // Remove the angle
        pObjTemp->SetiAngle( 0, m_pDocument );

        // Advise object on position and size changed
        pObjTemp->SizePositionHasChanged();
        m_pDocument->UpdateAllViews( NULL );
        m_pDocument->SetModifiedFlag( TRUE );
    }
    //## end ZDDocumentData::SetCurrentStyle%914061093.body
}

BOOL ZDDocumentData::IsCalculatedFieldInAssociation ( PlanFinObject* pObj )
{
    //## begin ZDDocumentData::IsCalculatedFieldInAssociation%914061094.body preserve=yes
    if ( ( (PLFNLong*)pObj )->GetCurrentAssociation()->FindFormula( pObj->GetObjectName() ) )
    {
        return TRUE;
    }

    return FALSE;
    //## end ZDDocumentData::IsCalculatedFieldInAssociation%914061094.body
}

void ZDDocumentData::InitializeAllObjectPointers ()
{
    //## begin ZDDocumentData::InitializeAllObjectPointers%914353650.body preserve=yes
    GetSchema().InitializeSchemaObjectPointer( *this );
    InitializeAllAssociations();
    //## end ZDDocumentData::InitializeAllObjectPointers%914353650.body
}

void ZDDocumentData::PropagateFieldValue ( PlanFinObject* pObj )
{
    if ( pObj->GetObjectName().IsEmpty() )
    {
        return;
    }

    if ( !m_pDocument )
    {
        return;
    }

    ZIView* pView = m_pDocument->GetMainView();
    ASSERT( pView );

    CString            FieldName;
    CString            Member;
    int                RowValue = -1;

    // If is member of multi-colum field,
    // extract the name of the field and the member name
    // extract also the row number of the value
    if ( pObj->IsMemberOfMultiColumn() )
    {
        ZBTokenizer Tokenizer('.');

        // Get fieldname
        FieldName = Tokenizer.GetFirstToken( pObj->GetObjectName() );

        // Get member name
        Member = Tokenizer.GetNextToken();

        RowValue = ( (ZBFieldColumn*)pObj->GetpColumn() )->GetValueRow( pObj->GetUnformatedObject() );
    }

    PlanFinObject  *pTempObj;

    if ( pObj )
    {
        CDC* pDC = pView->GetDC();

        if ( pView->IsWindowVisible() )
        {
            ASSERT( pDC );
            pView->OnPrepareDC( pDC );
        }

        // Retreive the current page
        int iPage = GetCurrentPage();

        // Invalidate the current object
        if ( pView->IsWindowVisible() )
        {
            pObj->InvalidateObjectRect( pDC, pView );
        }

        if ( ( pTempObj = GetHead() ) == NULL )
        {
            if ( pView->IsWindowVisible() )
            {
                VERIFY( pView->ReleaseDC(pDC) );
            }

            return;
        }

        do
        {
            // Find similar object name in the list
            if ( pTempObj != pObj )
            {
                if ( pTempObj->GetObjectName() == pObj->GetObjectName() )
                {
                    // Copy its content
                    if ( pTempObj->ConvertFormatedObject( pObj->GetUnformatedObject(),    // String value
                                                          FALSE ) )                        // Do not locate format
                    {
                        // If the field contents has change, refresh it.
                        if ( iPage == pTempObj->GetObjectPage() )
                        {
                            if ( pView->IsWindowVisible() )
                            {
                                pTempObj->InvalidateObjectRect( pDC, pView );
                            }
                        }
                    }
                }
                else
                {
                    // Check for other multi-column field
                    if ( pTempObj->IsMemberOfMultiColumn() && RowValue != -1 )
                    {
                        ZBTokenizer        Tokenizer('.');
                        CString            CurrentFieldName = Tokenizer.GetFirstToken( pTempObj->GetObjectName() );

                        // If we have the same fieldname
                        if ( FieldName == CurrentFieldName )
                        {
                            CString CurrentFieldMember = Tokenizer.GetNextToken();

                            // Locate the multicolumn fieldname
                            PlanFinObject* pMultiColumn = GetObjectPtr( CurrentFieldName );

                            // No object or not a multi-column field, do nothing
                            if ( pMultiColumn && pMultiColumn->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
                            {
                                // Locate the column name
                                ZBFieldColumn* pColumn =
                                    ( (PLFNMultiColumn*)pMultiColumn )->FindColumn( CurrentFieldMember );

                                // If the column is found, assign the pointer
                                if ( pColumn )
                                {
                                    // Copy its content
                                    if ( pTempObj->ConvertFormatedObject( pColumn->GetValueAt( RowValue ),    // String value
                                                                          FALSE ) )                            // Do not locate format
                                    {
                                        // If the field contents has change, refresh it.
                                        if ( iPage == pTempObj->GetObjectPage() )
                                        {
                                            if ( pView->IsWindowVisible() )
                                            {
                                                pTempObj->InvalidateObjectRect( pDC, pView );
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        while( ( pTempObj = GetNext() ) != NULL );

        if ( pView->IsWindowVisible() )
        {
            VERIFY( pView->ReleaseDC( pDC ) );
        }
    }

    m_pDocument->FieldHasBeenModified();

    // Generate a WM_PAINT message
    pView->UpdateWindow();
    //## end ZDDocumentData::PropagateFieldValue%914754358.body
}

void ZDDocumentData::AssignNewStyle ( HandleStyle hOldStyle, HandleStyle hNewStyle )
{
    //## begin ZDDocumentData::AssignNewStyle%922093646.body preserve=yes
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition();

    // Run through all objects    
    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        // If the object points to the deleted style
        if ( obj->GethStyle() == hOldStyle )
        {
            // Assigns Normal style
            obj->SethStyle( hNewStyle );
        }
    }
    //## end ZDDocumentData::AssignNewStyle%922093646.body
}

CString ZDDocumentData::CreateFileFromBuffer ( const CString Filename )
{
    //## begin ZDDocumentData::CreateFileFromBuffer%938933079.body preserve=yes
    if ( m_pFileBuffer )
    {
        return m_pFileBuffer->CreateFileFromBuffer( Filename );
    }

    return _T( "" );
    //## end ZDDocumentData::CreateFileFromBuffer%938933079.body
}

CString ZDDocumentData::CreateTemporaryFileFromBuffer ()
{
    //## begin ZDDocumentData::CreateTemporaryFileFromBuffer%938959773.body preserve=yes
    if ( IsBinaryDataValid() )
    {
        if ( m_FileBufferTemporaryFile.IsEmpty() )
        {
            // Create the temporary file and saves it.
            m_FileBufferTemporaryFile = m_pFileBuffer->CreateTemporaryFileFromBuffer();
            GetFileLauncher().Initialize( m_FileBufferTemporaryFile );
        }

        return m_FileBufferTemporaryFile;
    }

    // No file buffer
    m_FileBufferTemporaryFile.Empty();

    return _T( "" );
    //## end ZDDocumentData::CreateTemporaryFileFromBuffer%938959773.body
}

void ZDDocumentData::ClearFileBuffer ()
{
    //## begin ZDDocumentData::ClearFileBuffer%938933080.body preserve=yes
    if ( m_pFileBuffer )
    {
        delete m_pFileBuffer;
        m_pFileBuffer = NULL;
    }
    //## end ZDDocumentData::ClearFileBuffer%938933080.body
}

BOOL ZDDocumentData::CreateBufferFromFile ( const CString Filename )
{
    //## begin ZDDocumentData::CreateBufferFromFile%938933078.body preserve=yes
    // If already one, clear it before.
    if ( m_pFileBuffer )
    {
        ClearFileBuffer();
    }

    m_pFileBuffer = new ZBFileBuffer;

    if ( !m_pFileBuffer )
    {
        return FALSE;
    }

    GetStamp().SetDocumentDataType( BinaryDataType );
    GetStamp().SetTemplate( Filename );

    return m_pFileBuffer->CreateBufferFromFile( Filename );
    //## end ZDDocumentData::CreateBufferFromFile%938933078.body
}

BOOL ZDDocumentData::DeleteTemporaryFile ()
{
    //## begin ZDDocumentData::DeleteTemporaryFile%938959790.body preserve=yes
    if ( m_FileBufferTemporaryFile.IsEmpty() )
    {
        return TRUE;
    }

    if ( !::DeleteFile( m_FileBufferTemporaryFile ) )
    {
        return FALSE;
    }

    m_FileBufferTemporaryFile.Empty();

    return TRUE;
    //## end ZDDocumentData::DeleteTemporaryFile%938959790.body
}

void ZDDocumentData::OnDraw ( CDC*        pDC,
                              ZIView*    pView,
                              BOOL        DrawCalculatedSymbol,
                              BOOL        DrawHiddenObject,
                              BOOL        DrawBoundRectObject,
                              BOOL        DrawCalculatedRefObject,
                              BOOL        DrawTabOrder )
{
    //## begin ZDDocumentData::OnDraw%940782409.body preserve=yes
    if ( IsFormData() )
    {
        OnDrawForms( pDC,
                     pView,
                     DrawCalculatedSymbol,
                     DrawHiddenObject,
                     DrawBoundRectObject,
                     DrawCalculatedRefObject,
                     DrawTabOrder );
    }
    else if ( IsExternalFormData() )
    {
        OnDrawExternalForms( pDC,
                             pView,
                             DrawCalculatedSymbol,
                             DrawHiddenObject,
                             DrawBoundRectObject,
                             DrawCalculatedRefObject,
                             DrawTabOrder );
    }
    else if ( IsBinaryDataValid() )
    {
        OnDrawBinary( pDC, pView );
    }
    else if ( IsExternalBinaryData() )
    {
        OnDrawExternalBinary( pDC, pView );
    }
    else if ( IsURLData() )
    {
        OnDrawURL( pDC, pView );
    }
    //## end ZDDocumentData::OnDraw%940782409.body
}

void ZDDocumentData::OnDrawBinary ( CDC* pDC, ZIView* pView )
{
    //## begin ZDDocumentData::OnDrawBinary%940782410.body preserve=yes
    CRect    Rect( 20, 20, 500, 1000 );
    pDC->DrawText( m_BinaryDrawMessage, &Rect, DT_WORDBREAK | DT_LEFT );
    return;
    //## end ZDDocumentData::OnDrawBinary%940782410.body
}

void ZDDocumentData::OnDrawExternalBinary ( CDC* pDC, ZIView* pView )
{
    CRect    Rect( 20, 20, 500, 1000 );
    pDC->DrawText( m_BinaryDrawMessage, &Rect, DT_WORDBREAK | DT_LEFT );
    return;
}

void ZDDocumentData::OnDrawBackgroundPicture( CDC* pDC, ZIView* pView, int iPage )
{
    PlanFinObject *obj;
    POSITION Position = ( GetObjectList() ).GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        if ( iPage == obj->GetObjectPage() && ISA( obj, PLFNBackImage ) )
        {
            if ( obj->GetbIsVisible() || m_pDocument->ShouldShowHiddenField() )
            {
                if ( pDC->IsPrinting() )
                {
                    if ( obj->GetbMustBePrinted() && obj->GetbIsVisible() )
                    {
                        obj->DrawObject( pDC, pView );
                    }
                }
                else
                {
                    obj->DrawObject( pDC, pView );
                }
            }
        }
    }
}

void ZDDocumentData::OnDrawForms ( CDC*        pDC,
                                   ZIView*    pView,
                                   BOOL        DrawCalculatedSymbol,
                                   BOOL        DrawHiddenObject,
                                   BOOL        DrawBoundRectObject,
                                   BOOL        DrawCalculatedRefObject,
                                   BOOL        DrawTabOrder )
{
    // Otherwise, normal formulaires
    int                iPage;
    PlanFinObject    *obj;
    POSITION        Position;

    // Retreive the current page
    iPage = m_pDocument->GetCurrentPage();

    // First draw background picture
    OnDrawBackgroundPicture( pDC, pView, iPage );

    // Optimisation first step
    // call directly the list functions
    Position = (GetObjectList()).GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        // Display object on the right page and if he is visible into the viewport
        // And do not draw background images
        if ( obj && iPage == obj->GetObjectPage() && !ISA( obj, PLFNBackImage ) )
        {
            if ( obj->GetbIsVisible() || m_pDocument->ShouldShowHiddenField() || DrawHiddenObject )
            {
                if ( pDC->IsPrinting() )
                {
                    // When printing test if the object is empty
                    // and if must print empty line
                    // AND if the object must be printed
                    if ( ( obj->GetbMustBePrinted() && obj->GetbIsVisible() ) &&
                         ( !obj->IsEmpty() || m_pDocument->ShouldPrintLine() ) )
                    {
                        obj->DrawObject( pDC, pView );
                    }
                }
                else
                {
                    obj->DrawObject( pDC, pView );

                    if ( DrawCalculatedSymbol )
                    {
                        obj->DrawCalculatedSymbol( pDC );
                    }

                    if ( !obj->GetbMustBePrinted() )
                    {
                        obj->DrawHiddenOnPrintSymbol( pDC );
                    }

                    if ( DrawHiddenObject && !obj->GetbIsVisible() )
                    {
                        obj->DrawHiddenSymbol( pDC );
                    }

                    if ( DrawBoundRectObject )
                    {
                        obj->DrawObjectRectangle( pDC );
                    }

                    if ( DrawTabOrder )
                    {
                        obj->DrawTabOrder( pDC );
                    }

                    if ( DrawCalculatedRefObject )
                    {
                        // Nothing yet implemented
                    }

                    if ( obj->GetNotesPointer() )
                    {
                        obj->DrawNoteSymbol( pDC );
                    }
                }
            }
        }
    }
}

void ZDDocumentData::OnDrawExternalForms ( CDC*        pDC,
                                           ZIView*    pView,
                                           BOOL        DrawCalculatedSymbol,
                                           BOOL        DrawHiddenObject,
                                           BOOL        DrawBoundRectObject,
                                           BOOL        DrawCalculatedRefObject,
                                           BOOL        DrawTabOrder )
{
    // Not yet implemented
}

void ZDDocumentData::OnDrawURL ( CDC* pDC, ZIView* pView )
{
    CRect    Rect( 20, 20, 500, 1000 );
    pDC->DrawText( m_BinaryDrawMessage, &Rect, DT_WORDBREAK | DT_LEFT );
    return;
}

void ZDDocumentData::SwitchTabOrder ( PlanFinObject* pObject, double TabOrder )
{
    //## begin ZDDocumentData::SwitchTabOrder%947360846.body preserve=yes
    PlanFinObject    *obj;
    POSITION        Position;

    Position = (GetObjectList()).GetHeadPosition( );

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        // If we found the tab order that we would like to switch
        if ( obj->GetTabOrder() == TabOrder )
        {
            // Assign the tab order of the found object
            obj->SetTabOrder( pObject->GetTabOrder() );
            break;
        }
    }

    // Finally assign the tab order to the object
    pObject->SetTabOrder( TabOrder );
    //## end ZDDocumentData::SwitchTabOrder%947360846.body
}

void ZDDocumentData::AutomaticRebuildTabOrder ()
{
    //## begin ZDDocumentData::AutomaticRebuildTabOrder%947360849.body preserve=yes
    PlanFinObject    *obj;
    POSITION        Position;

    // Evaluate the last tab order
    EvaluateLastTabOrder();

    Position = ( GetObjectList() ).GetHeadPosition( );

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        // If we found a tab order equal to zero
        if ( obj->GetTabOrder() == 0 )
        {
            // We assign a new value of the tab order by incrementing the last tab order
            obj->SetTabOrder( ++m_LastTabOrder );
        }
    }
    //## end ZDDocumentData::AutomaticRebuildTabOrder%947360849.body
}

double ZDDocumentData::EvaluateLastTabOrder ()
{
    //## begin ZDDocumentData::EvaluateLastTabOrder%947360850.body preserve=yes
    PlanFinObject    *obj;
    POSITION        Position;

    // Initialize last tab order
    m_LastTabOrder = 0;

    Position = (GetObjectList()).GetHeadPosition( );

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        // If we found a tab order equal to zero
        m_LastTabOrder = __max( obj->GetTabOrder(), m_LastTabOrder );
    }

    return m_LastTabOrder;
    //## end ZDDocumentData::EvaluateLastTabOrder%947360850.body
}

void ZDDocumentData::AssignMultiColumnMemberFields ()
{
    //## begin ZDDocumentData::AssignMultiColumnMemberFields%948318241.body preserve=yes
    PlanFinObject  *obj;
    POSITION        Position;

    Position = ( GetObjectList() ).GetHeadPosition( );

    while( Position )
    {
        obj = (PlanFinObject *)(GetObjectList()).GetNext( Position );
        CheckMultiColumnMemberField( obj );
    }
    //## end ZDDocumentData::AssignMultiColumnMemberFields%948318241.body
}

bool ZDDocumentData::AddFieldNameInObectArray ( const CString& Fieldname )
{
    //## begin ZDDocumentData::AddFieldNameInObectArray%948540878.body preserve=yes
    if ( !FieldNameExistInObectArray( Fieldname ) )
    {
        m_FieldNameArray.Add( Fieldname );
    }

    return true;
    //## end ZDDocumentData::AddFieldNameInObectArray%948540878.body
}

bool ZDDocumentData::BuildObjectFieldNameArray ()
{
    //## begin ZDDocumentData::BuildObjectFieldNameArray%948540871.body preserve=yes
    // Free the object fieldname array
    m_FieldNameArray.RemoveAll();

    PlanFinObject    *obj;
    POSITION        Position;

    Position = ( GetObjectList() ).GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)( GetObjectList() ).GetNext( Position );

        if ( obj && !FieldNameExistInObectArray( obj->GetObjectName() ) )
        {
            m_FieldNameArray.Add( obj->GetObjectName() );
        }

        if ( obj && obj->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
        {
            // Add member fieldname
            for ( size_t i = 0; i < ((PLFNMultiColumn*)obj)->GetColumnCount(); ++i )
            {
                CString FullName        = obj->GetObjectName() + _T( "." );
                ZBFieldColumn* pColumn    = ( (PLFNMultiColumn*)obj )->GetColumnAt( i );

                if ( pColumn )
                {
                    FullName += pColumn->GetHeaderName();

                    if ( !FieldNameExistInObectArray( FullName ) )
                    {
                        m_FieldNameArray.Add( FullName );
                    }
                }
            }
        }
    }

    return m_FieldNameArray.GetSize() > 0;
    //## end ZDDocumentData::BuildObjectFieldNameArray%948540871.body
}

bool ZDDocumentData::FieldNameExistInObectArray ( const CString& Fieldname )
{
    //## begin ZDDocumentData::FieldNameExistInObectArray%948540876.body preserve=yes
    for ( size_t i = 0; i < (size_t)m_FieldNameArray.GetSize(); ++i )
    {
        if ( Fieldname == m_FieldNameArray.GetAt( i ) )
        {
            return true;
        }
    }

    return false;
    //## end ZDDocumentData::FieldNameExistInObectArray%948540876.body
}

// Additional Declarations
//## begin ZDDocumentData%3678E27C00F2.declarations preserve=yes
//## end ZDDocumentData%3678E27C00F2.declarations

//## begin module%3678E29D0317.epilog preserve=yes

// GetObjectValue ----------------------------------------------------
//
// Author        :    Aigroz Dominique
// Date            :    14/12/1994
// Description    :    This function run the list of objects and try
//                    try to find the object defined by his name.
//                    After the function return the object value.
//
// Parameters    :    strName        the name to search in the list.
// Return        :    the object value.
//
// Remarks        :    
//
//----------------------------------------------------------------------------

double ZDDocumentData::GetObjectValue( char *cpName )
{
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        if( strcmp( (const char *)obj->m_strObjName, cpName ) == 0 )
        {
            return( obj->GetValue() );
        }
    }

    return( 0 );
}

void ZDDocumentData::MoveContents( ZDDocumentData* pDocument, BOOL bCopyFormat )
{
    PlanFinObject    *pObjSrc;
    PlanFinObject    *pObjDst;
    POSITION        PositionSrc;
    POSITION        PositionDst;

    PositionDst = pDocument->GetObjectList().GetHeadPosition();

    while ( PositionDst )
    {
        pObjDst = (PlanFinObject *)pDocument->GetObjectList().GetNext( PositionDst );

        // For each element find the 
        PositionSrc = GetObjectList().GetHeadPosition();

        while ( PositionSrc )
        {
            pObjSrc = (PlanFinObject *)GetObjectList().GetNext( PositionSrc );

            // Test if both objects are similar
            if ( pObjSrc->GetObjectPage() == pObjDst->GetObjectPage() &&
                 pObjSrc->GetObjectName() == pObjDst->GetObjectName() )
            {
                if ( !pObjSrc->IsEmpty() )
                {
                    if ( bCopyFormat )
                        pObjDst->SetFormatType(pObjSrc->GetFormatType());

                    pObjDst->ConvertFormatedObject( pObjSrc->GetFormatedObject() );
                }

                break;
            }
        }
    }
}

// Because one style has been deleted,
// all objects refering to this style must
// be redirected to Normal style
void ZDDocumentData::StyleHasBeenDeleted( HandleStyle hStyle )
{
    PlanFinObject    *obj;
    POSITION        Position;
    
    Position = GetObjectList().GetHeadPosition();

    // Run through all objects
    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        // If the object points to the deleted style
        if ( obj->GethStyle() == hStyle )
        {
            // Assigns Normal style
            obj->SethStyle( NormalStyle );
        }
    }
}

// Check the validity of all fonts
void ZDDocumentData::CheckFontValidity()
{
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition();

    // Run through all objects    
    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        // If the object points to an undefined font
        if ( obj->GethFont() >= (LONG)GetFontManager().GetElements() )
        {
            // Assigns it to no font, therefore to the style
            obj->SethFont( NoFontDefined );
        }
    }
}

BOOL ZDDocumentData::DeletePage( int iPage )
{
    if ( !DeletePageObjects( iPage ) )
    {
        return FALSE;
    }

    // Delete formulas on all schemas
    if ( !GetSchema().DeletePageFormulas( iPage ) )
    {
        return FALSE;
    }

    SetCurrentPage( CountAndSetPages() );

    m_pDocument->UpdateAllViews( NULL );
    m_pDocument->SetModifiedFlag();

    return TRUE;
}

BOOL ZDDocumentData::DeletePageObjects( int iPage, BOOL bRedistribute )
{
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        // Test the object page
        if ( obj->GetObjectPage() == iPage )
        {
            if ( !DeleteObject( obj ) )
            {
                return FALSE;
            }
        }
    }

    if ( bRedistribute )
    {
        // Test if it is necessary
        // to redistribute the objects' pages
        if ( iPage < GetMaxPage() )
        {
            Position = GetObjectList().GetTailPosition();
            
            while( Position )
            {
                obj = (PlanFinObject *)GetObjectList().GetPrev( Position );

                // Test the object's page if before the deleted page
                if ( obj->GetObjectPage() < iPage )
                {
                    break;
                }

                obj->SetObjectPage( obj->GetObjectPage() - 1 );
            }
        }

        // Reassign the predefined field like pages
        AssignPredefinedField();
    }

    return TRUE;
}

BOOL ZDDocumentData::CopyPage( ZDDocumentData* pDocumentDst, int iPage )
{
    // Delete page objects without redistributing pages
    if ( !pDocumentDst->DeletePageObjects( iPage, FALSE ) )
    {
        return FALSE;
    }

    if ( !CopyPageObjects( pDocumentDst, iPage ) )
    {
        return FALSE;
    }

    // Copy all schema
    CStringArray& SchemaArray = GetSchema().GetFormulaArrayName();

    for ( int i = 0; i < SchemaArray.GetSize(); ++i )
    {
        if ( !GetSchema().CopyPageFormulas( SchemaArray[i], pDocumentDst->GetSchema(), iPage ) )
        {
            return FALSE;
        }
    }

    pDocumentDst->CountAndSetPages();
    pDocumentDst->GetpDocument()->SetModifiedFlag();

    return TRUE;
}

BOOL ZDDocumentData::CopyPageOnlyObjects( ZDDocumentData* pDocumentDst, int iPage )
{
    // Delete page objects without redistributing pages
    if ( !pDocumentDst->DeletePageObjects( iPage, FALSE ) )
    {
        return FALSE;
    }

    if ( !CopyPageObjects( pDocumentDst, iPage ) )
    {
        return FALSE;
    }

    pDocumentDst->CountAndSetPages();
    pDocumentDst->GetpDocument()->SetModifiedFlag();

    return TRUE;
}

BOOL ZDDocumentData::CopyPageOnlyFormula( ZDDocumentData* pDocumentDst, int iPage )
{
    // Copy all schema
    CStringArray&    SchemaArray = GetSchema().GetFormulaArrayName();

    for ( int i = 0; i < SchemaArray.GetSize(); ++i )
    {
        if ( !GetSchema().CopyPageFormulas( SchemaArray[i], pDocumentDst->GetSchema(), iPage ) )
        {
            return FALSE;
        }
    }

    pDocumentDst->GetpDocument()->SetModifiedFlag();

    return TRUE;
}

BOOL ZDDocumentData::CopyPageObjects( ZDDocumentData* pDocumentDst, int iPage )
{
    PlanFinObject    *obj;
    POSITION        Position;

    Position = GetObjectList().GetHeadPosition( );
    
    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );

        // Test the object page
        if ( obj->GetObjectPage() == iPage )
        {
            PlanFinObject* pNewObjTemp = obj->Clone();
            ASSERT( pNewObjTemp );

            // Insert the object into the Destination document
            if ( !pDocumentDst->InsertObject( pNewObjTemp ) )
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL ZDDocumentData::CheckObjectList()
{
    PlanFinObject    *obj;
    PlanFinObject    *similarObject;
    POSITION        Position;
    POSITION        StartPosition;
    POSITION        SavedPosition;

    Position = GetObjectList().GetHeadPosition();

    while( Position )
    {
        obj = (PlanFinObject *)GetObjectList().GetNext( Position );
        StartPosition = Position;

        // From this position, check if another object has the same adress
        while ( StartPosition )
        {
            // Save the previous position for further deletion
            SavedPosition = StartPosition;
            similarObject = (PlanFinObject *)GetObjectList().GetNext( StartPosition );

            if ( similarObject == obj )
            {
                // We found a same reference to the list
                CString prompt;
                AfxFormatString1(prompt, IDS_OBJECTSAMEREFERENCE, obj->GetObjectName());

                MsgBox mbox;

                if ( mbox.DisplayMsgBox( prompt, MB_YESNO ) == IDNO )
                {
                    return FALSE;
                }

                GetObjectList().RemoveAt( SavedPosition );
            }
        }
    }

    return TRUE;
}

BOOL ZDDocumentData::CheckMultiColumnMemberField( PlanFinObject* obj )
{
    ZBTokenizer        Tokenizer('.');
    CString            FieldName = Tokenizer.GetFirstToken( obj->GetObjectName() );
    CString            Member = Tokenizer.GetNextToken();

    // If no member, next field
    if ( Member.IsEmpty() )
    {
        return FALSE;
    }

    // Locate the fieldname
    PlanFinObject* pMultiColumn = GetObjectPtr( FieldName );

    if ( !pMultiColumn )
    {
        return FALSE;
    }

    // No object or not a multi-column field, do nothing
    if ( !pMultiColumn->IsKindOf( RUNTIME_CLASS( PLFNMultiColumn ) ) )
    {
        FALSE;
    }

    // Locate the column name
    ZBFieldColumn* pColumn = ( (PLFNMultiColumn*)pMultiColumn )->FindColumn( Member );

    // If the column is found, assign the pointer
    if ( pColumn )
    {
        obj->SetpColumn( pColumn );
        return TRUE;
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////77
// ZDDocumentData serialization

void ZDDocumentData::Serialize ( CArchive& ar )
{
    //## begin ZDDocumentData::Serialize%913885094.body preserve=yes
    if ( ar.IsStoring() )
    {
        AutomaticRebuildTabOrder();
        SerializeWrite( ar );
    }
    else
    {
        SerializeRead( ar );
        AutomaticRebuildTabOrder();
    }
    //## end ZDDocumentData::Serialize%913885094.body
}

//## end module%3678E29D0317.epilog
