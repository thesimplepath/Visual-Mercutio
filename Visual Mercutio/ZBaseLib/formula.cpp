// formula.cpp : implementation of the ZAFormula class
//


#include "stdafx.h"

#include "formula.h"

#include "ZAObject.h"
#include "ZDDoc.h"
#include "DocData.h"

#include "msgbox.h"

#include <MATH.H>
#include <IO.H>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


void    ZAFormula::ConstructObjectPointer( ZDDocumentData& Doc, CObList& lstFormula )
{
    ZAFormula*  obj;
    POSITION    Position = lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)lstFormula.GetNext( Position );
        // Get the pointer to the object
        obj->m_ResultObject = Doc.GetObjectPtr( obj->m_sObjectName );

        if (!obj->m_ResultObject)
        {
            CString prompt;
            AfxFormatString1(prompt, IDS_OBJECTMISSING, obj->m_sObjectName);
            MsgBox        mbox;
            mbox.DisplayMsgBox(prompt, MB_OK);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormula
IMPLEMENT_SERIAL(ZAFormula, CObject, g_DefVersion)

ZAFormula::ZAFormula()
 : m_ResultObject( NULL )
{
}

ZAFormula::ZAFormula( ZDDocument& Doc, const CString& str )
{
//                char    szBuf[300];
//                sprintf( szBuf, "%s"    , (const char*)str );
//                AfxMessageBox( szBuf );
    char*        cpFind;
    
    CString        sTemp = str;
    int            iSep;
    VERIFY( (iSep=sTemp.Find(',')) != -1 );
    CString        sPage=sTemp.Left( iSep );
    m_iPage = atoi( sPage );
    m_sFormula = sTemp.Right( sTemp.GetLength()-iSep-1 );

    // extract object Name
    VERIFY(cpFind = const_cast<char*>(std::strchr(m_sFormula, '=')));

    m_sObjectName = m_sFormula.Left( (int)(cpFind-m_sFormula-1) );
    m_sExtractedFormula = cpFind+1;
    // Get the pointer to the object
    m_ResultObject = Doc.GetObjectPtr( m_sObjectName );
    ASSERT( m_ResultObject );
}

ZAFormula* ZAFormula::Clone()
{
    ZAFormula*    pObject = new ZAFormula( *this );
    return pObject;
}

ZAFormula::~ZAFormula()
{
}

ZAFormula::ZAFormula(const ZAFormula &right)
{
      *this = right;
}

const ZAFormula & ZAFormula::operator=(const ZAFormula &right)
{
      m_sFormula = right.m_sFormula;
      m_sExtractedFormula = right.m_sExtractedFormula;
      m_sObjectName = right.m_sObjectName;
      // Not a deep copy
      m_ResultObject = right.m_ResultObject;
      m_iPage = right.m_iPage;
    return *this;
}


/////////////////////////////////////////////////////////////////////////////
// ZAFormula serialization

void ZAFormula::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {    // Write informations
        ar << (WORD)m_iPage;
        ar << m_sFormula;
        ar << m_sExtractedFormula;
        ar << m_sObjectName;
//        ar << m_ResultObject;
    }
    else
    {    // Read informations
        WORD    wTemp;
        ar >> wTemp;
        m_iPage = (int)wTemp;
        ar >> m_sFormula;
        ar >> m_sExtractedFormula;
        ar >> m_sObjectName;
        // Assigns pointer to NULL
        m_ResultObject = NULL;
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormula diagnostics

#ifdef _DEBUG
void ZAFormula::AssertValid() const
{
    CObject::AssertValid();
}

void ZAFormula::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG




/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociation
IMPLEMENT_SERIAL(ZAFormulaAssociation, CObject, g_DefVersion)

ZAFormulaAssociation::ZAFormulaAssociation()
{
}

ZAFormulaAssociation::ZAFormulaAssociation( const CString Name, const CString ObjectNameInitiator )
 : m_AssociationName( Name ),  m_ObjectNameInitiator( ObjectNameInitiator )
{
}


ZAFormulaAssociation::~ZAFormulaAssociation()
{
    while (!m_lstFormula.IsEmpty())
    {
        delete m_lstFormula.GetHead();
        m_lstFormula.RemoveHead();
    }
}


ZAFormulaAssociation*    ZAFormulaAssociation::Clone()
{
    ZAFormulaAssociation*    pNewAssociation = new ZAFormulaAssociation;
    
    ZAFormula*              obj;
    POSITION                Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        pNewAssociation->m_lstFormula.AddTail( obj->Clone() );
    }
    // Copy members
    pNewAssociation->m_AssociationName = m_AssociationName;
    pNewAssociation->m_ObjectNameInitiator = m_ObjectNameInitiator;
    return pNewAssociation;
}

void ZAFormulaAssociation::AddFormula( ZAFormula* pFormula )
{
    m_lstFormula.AddTail( pFormula );
}

void ZAFormulaAssociation::DeleteFormula( const CString& Name )
{
    ZAFormula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetObjectName() == Name)
        {
            DeleteFormula( obj );
            return;
        }
    }
}

void ZAFormulaAssociation::DeleteFormula( ZAFormula* pFormula )
{
    POSITION    Position = m_lstFormula.Find( pFormula );
    
    if (Position)
    {
        delete (ZAFormula*)pFormula;
        // Destroy the object in the list
        m_lstFormula.RemoveAt( Position );
    }
}

ZAFormula*    ZAFormulaAssociation::GetFormulaAt( int Index )
{
    POSITION    Position = m_lstFormula.FindIndex( Index );
    if (Position)
        return (ZAFormula*)m_lstFormula.GetAt( Position );
    return NULL;
}


ZAFormula* ZAFormulaAssociation::FindFormula( const CString& Name )
{
    ZAFormula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetObjectName() == Name)
            return obj;
    }
    return NULL;
}

ZAFormula* ZAFormulaAssociation::FindFormulaFullString( const CString& Formula )
{
    ZAFormula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetFormula() == Formula)
            return obj;
    }
    return NULL;
}


size_t ZAFormulaAssociation::GetFormulaArray( CStringArray& Array )
{
    ZAFormula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition( );
    
    Array.RemoveAll();    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        Array.Add( obj->GetFormula() );
    }
    // Return the number of element
    return Array.GetSize();
}




/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociation serialization

void ZAFormulaAssociation::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {    // Write informations
        ar << m_AssociationName;
        ar << m_ObjectNameInitiator;
    }
    else
    {    // Read informations
        ar >> m_AssociationName;
        ar >> m_ObjectNameInitiator;
    }
    m_lstFormula.Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociation diagnostics

#ifdef _DEBUG
void ZAFormulaAssociation::AssertValid() const
{
    CObject::AssertValid();
}

void ZAFormulaAssociation::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociationManager


IMPLEMENT_SERIAL(ZAFormulaAssociationManager, CObject, g_DefVersion)

ZAFormulaAssociationManager::ZAFormulaAssociationManager()
 : m_pCurrentAssociation( NULL )
{
}

ZAFormulaAssociationManager::~ZAFormulaAssociationManager()
{
    while (!m_lstAssociation.IsEmpty())
    {
        delete m_lstAssociation.GetHead();
        m_lstAssociation.RemoveHead();
    }
}

void ZAFormulaAssociationManager::AssignContents( const ZAFormulaAssociationManager& ManagerSource )
{
    // First delete the contents
    while (!m_lstAssociation.IsEmpty())
    {
        delete m_lstAssociation.GetHead();
        m_lstAssociation.RemoveHead();
    }
    
    ZAFormulaAssociation*      obj;
    POSITION                Position = ManagerSource.m_lstAssociation.GetHeadPosition( );
    
    while (Position)
    {
        // Read the next element of the source
        obj = (ZAFormulaAssociation*)ManagerSource.m_lstAssociation.GetNext( Position );
        // Add a clone of the element to the list
        m_lstAssociation.AddTail( obj->Clone() );
    }
    // Set Association to null
    m_pCurrentAssociation = NULL;
    // Refresh the dynamic association array
    RefreshAssociationArray();
}



ZAFormulaAssociationManager*    ZAFormulaAssociationManager::Clone()
{
    ZAFormulaAssociationManager*    pNewAssociationManager = new ZAFormulaAssociationManager;
    
    ZAFormulaAssociation*      obj;
    POSITION                Position = m_lstAssociation.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext( Position );
        pNewAssociationManager->m_lstAssociation.AddTail( obj->Clone() );
    }
    // Set Association to null
    pNewAssociationManager->m_pCurrentAssociation = NULL;
    // Refresh the dynamic association array
    pNewAssociationManager->RefreshAssociationArray();
    return pNewAssociationManager;
}


void    ZAFormulaAssociationManager::AddAssociation( ZAFormulaAssociation* pAssociation )
{
    m_lstAssociation.AddTail( pAssociation );
}

void    ZAFormulaAssociationManager::DeleteAssociation( ZAFormulaAssociation* pAssociation )
{
    POSITION    Position = m_lstAssociation.Find( pAssociation );
    
    if (Position)
    {
        delete (ZAFormulaAssociation*)pAssociation;
        // Destroy the object in the list
        m_lstAssociation.RemoveAt( Position );
    }
}

void    ZAFormulaAssociationManager::DeleteAssociation( const CString& Name )
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext( Position );
        if (obj->GetAssociationName() == Name)
        {
            DeleteAssociation( obj );
            return;
        }
    }
}

ZAFormulaAssociation*    ZAFormulaAssociationManager::FindAssociation( const CString& Name )
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext( Position );
        if (obj->GetAssociationName() == Name)
            return obj;
    }
    return NULL;
}


CStringArray& ZAFormulaAssociationManager::RefreshAssociationArray()
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition( );
    
    m_AssociationArrayName.RemoveAll();    
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext( Position );
        m_AssociationArrayName.Add( obj->GetAssociationName() );
    }
    return m_AssociationArrayName;
}


// Run through the list of association
// and for each association, construct all formula pointers
void    ZAFormulaAssociationManager::InitializeFormulaAssociations( ZDDocumentData& Doc )
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext( Position );
        ZAFormula::ConstructObjectPointer( Doc, obj->GetFormulaList() );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociationManager serialization

void ZAFormulaAssociationManager::Serialize(CArchive& ar)
{
    m_lstAssociation.Serialize( ar );
    if (ar.IsStoring())
        ar << m_pCurrentAssociation;
    else
    {
        ar >> m_pCurrentAssociation;
        // Refresh the dynamic association array
        RefreshAssociationArray();
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociationManager diagnostics

#ifdef _DEBUG
void ZAFormulaAssociationManager::AssertValid() const
{
    CObject::AssertValid();
}

void ZAFormulaAssociationManager::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// ZAFormulaSchema
IMPLEMENT_SERIAL(ZAFormulaSchema, CObject, g_DefVersion)

ZAFormulaSchema::ZAFormulaSchema()
 : m_sDescription( "" ), m_FormulaSchemaType( UserSchema )
{
}

ZAFormulaSchema::~ZAFormulaSchema()
{
    while (!m_lstFormula.IsEmpty())
    {
        delete m_lstFormula.GetHead();
        m_lstFormula.RemoveHead();
    }
}

ZAFormulaSchema*    ZAFormulaSchema::Clone()
{
    ZAFormulaSchema*    pNewFormulaSchema = new ZAFormulaSchema;
    
    ZAFormula*          obj;
    POSITION            Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        ZAFormula*    pNewFormula = new ZAFormula;
        (ZAFormula&)*pNewFormula = (ZAFormula&)*obj;
        pNewFormulaSchema->m_lstFormula.AddTail( pNewFormula );
    }
    // Copy the name
    pNewFormulaSchema->m_sSchemaName = m_sSchemaName;
    pNewFormulaSchema->m_sDescription = m_sDescription;
    pNewFormulaSchema->m_FormulaSchemaType = m_FormulaSchemaType;
    return pNewFormulaSchema;
}


BOOL        ZAFormulaSchema::DeletePageFormulas( int iPage, BOOL bRedistribute )
{
    ZAFormula*          obj;
    POSITION            Position = m_lstFormula.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetPage() == iPage)
        {
            // Save the position within the list
            POSITION ElementPosition = m_lstFormula.Find( obj ); 
            if (!ElementPosition)
                return FALSE;
            // Destroy the object
            delete (ZAFormula*)obj;
            // Destroy the object in the list
            m_lstFormula.RemoveAt( ElementPosition );
        }
    }

    if (bRedistribute)
    {
        // Redistribute the objects' pages
        Position = m_lstFormula.GetTailPosition( );
            
        while( Position )
        {
            obj = (ZAFormula*)m_lstFormula.GetPrev( Position );
            // Test the object's page, if before the deleted page
            // continue the loop
            // For formula it impossible to stop the loop
            // because the formulas are not necessary sorted
            // by page
            if (obj->GetPage() < iPage)
                continue;
            obj->SetPage( obj->GetPage() - 1 );
        }
    }
    return TRUE;
}

BOOL        ZAFormulaSchema::CopyPageFormulas( ZAFormulaSchema*    pFormulaDst, int iPage )
{
    ZAFormula*          obj;
    POSITION            Position;
    POSITION            InsertedPosition = NULL;
    // Count in the source formula the
    // number of elements before finding the first
    // formula corresponding to the page    
    int        iPos;
    BOOL    bFoundOne = FALSE;
    for (Position = m_lstFormula.GetHeadPosition( ), iPos = 0; Position; ++iPos)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetPage() == iPage)
        {
            bFoundOne = TRUE;
            break;
        }
    }
    // If nothing found, OK
    if (!bFoundOne)
        return TRUE;
        
    Position = m_lstFormula.GetHeadPosition( );
    while (Position)
    {
        obj = (ZAFormula*)m_lstFormula.GetNext( Position );
        if (obj->GetPage() == iPage)
        {
            // If it is the first element to be inserted,
            // make a loop to count the initial position
            if (!InsertedPosition)
            {
                if (!iPos)
                {
                    InsertedPosition = pFormulaDst->m_lstFormula.AddHead( (CObject*)obj->Clone() );
                    continue;
                }
                else
                {
                    InsertedPosition = pFormulaDst->m_lstFormula.GetHeadPosition( );
                    
                    for (int iSearchPosition = 0; InsertedPosition && iSearchPosition < iPos; ++iSearchPosition)
                    {
                        pFormulaDst->m_lstFormula.GetNext( InsertedPosition );
                    }
                }
            }
            InsertedPosition = pFormulaDst->m_lstFormula.InsertAfter( InsertedPosition, (CObject*)obj->Clone() );
        }
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaSchema serialization

void ZAFormulaSchema::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {    // Write informations
        ar << m_sSchemaName;
        ar << m_sDescription;
        ar << (WORD)m_FormulaSchemaType;
    }
    else
    {    // Read informations
        ar >> m_sSchemaName;
        if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_sDescription;
            WORD    wTemp;
            ar >> wTemp;
            m_FormulaSchemaType = (FormulaSchemaType)wTemp;
        }
        else
        {
            CString    sText;
            sText.LoadString( IDS_DESCRIPTIONSTANDARDSCHEMA );
            SetDescription( sText );
            SetFormulaSchemaType( UserSchema );
        }
    }
    m_lstFormula.Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaSchema diagnostics

#ifdef _DEBUG
void ZAFormulaSchema::AssertValid() const
{
    CObject::AssertValid();
}

void ZAFormulaSchema::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG






/////////////////////////////////////////////////////////////////////////////
// ZASchemaManager
CStringArray        ZASchemaManager::m_SchemaNameArray;


IMPLEMENT_SERIAL(ZASchemaManager, CObject, g_DefVersion)

ZASchemaManager::ZASchemaManager()
{
}

ZASchemaManager::ZASchemaManager(const ZASchemaManager &right)
{
      *this = right;
}

ZASchemaManager::~ZASchemaManager()
{
    while (!m_lstSchema.IsEmpty())
    {
        delete m_lstSchema.GetHead();
        m_lstSchema.RemoveHead();
    }
}


const ZASchemaManager & ZASchemaManager::operator=(const ZASchemaManager &right)
{
    // Copy elements      
    ZAFormulaSchema*    obj;
    POSITION            Position;
    
    Position = ((ZASchemaManager &)right).m_lstSchema.GetHeadPosition( );
    while (Position)
    {
        obj = (ZAFormulaSchema *)((ZASchemaManager &)right).m_lstSchema.GetNext( Position );
        m_lstSchema.AddTail( obj->Clone() );
    }
    return *this;
}

ZASchemaManager*    ZASchemaManager::Clone()
{
    ZASchemaManager*    pNewManager = new ZASchemaManager( *this );
    return pNewManager;
}

void ZASchemaManager::InitializeSchemaObjectPointer( ZDDocumentData& Doc )
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        ZAFormula::ConstructObjectPointer( Doc, obj->GetFormulaList() );
    }
}


void ZASchemaManager::CreateStandardEmptySchema()
{
    // Create the original schema
    Create(g_OriginalSchema);
}

void ZASchemaManager::Create( const CString& sName )
{
    // Create the original 
    ZAFormulaSchema*    pOriginalSchema = new ZAFormulaSchema;
    
    pOriginalSchema->SetSchemaName( sName );
    m_lstSchema.AddTail( pOriginalSchema );

}

CObList*        ZASchemaManager::GetFormulaSchema( const CString& sName )
{
    if (sName.IsEmpty())
        return NULL;
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        if (obj->GetSchemaName() == sName)
            return (CObList*)obj;
    }
    return NULL;
}

CObList*    ZASchemaManager::GetFormulaList( const CString& sName )
{
    if (sName.IsEmpty())
        return NULL;
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        if (obj->GetSchemaName() == sName)
            return &(obj->GetFormulaList());
    }
    return NULL;
}

CStringArray&    ZASchemaManager::GetFormulaArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        m_SchemaNameArray.Add( obj->GetSchemaName() );
    }
    return m_SchemaNameArray;
}

CStringArray&    ZASchemaManager::GetFormulaUserArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        if (obj->GetFormulaSchemaType() == UserSchema)
            m_SchemaNameArray.Add( obj->GetSchemaName() );
    }
    return m_SchemaNameArray;
}

CStringArray&    ZASchemaManager::GetFormulaSystemArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        if (obj->GetFormulaSchemaType() == SystemSchema)
            m_SchemaNameArray.Add( obj->GetSchemaName() );
    }
    return m_SchemaNameArray;
}

BOOL    ZASchemaManager::CopySchema( const CString& sSource, const CString sNew )
{
    ZAFormulaSchema*    pSource;
    pSource = (ZAFormulaSchema*)GetFormulaSchema( sSource );
    if (pSource)
    {
        ZAFormulaSchema*    pNew = pSource->Clone();
        pNew->SetSchemaName( sNew );
        m_lstSchema.AddTail( pNew );
        return TRUE;
    }
    return FALSE;
}


BOOL    ZASchemaManager::DeletePageFormulas( int iPage )
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    BOOL                bRetValue = 0;
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        bRetValue |= !DeletePageFormulas( obj->GetSchemaName(), iPage );
    }
    return !bRetValue;
}

BOOL    ZASchemaManager::DeletePageFormulas( const CString& sName, int iPage )
{
    ZAFormulaSchema*    pFormula =     (ZAFormulaSchema*)GetFormulaSchema( sName );
    return pFormula->DeletePageFormulas( iPage );
}

BOOL    ZASchemaManager::CopyPageFormulas( const CString& sName, ZASchemaManager& SchemaDst, int iPage )
{
    ZAFormulaSchema*    pFormula =     (ZAFormulaSchema*)GetFormulaSchema( sName );
    ZAFormulaSchema*    pFormulaDst =     (ZAFormulaSchema*)SchemaDst.GetFormulaSchema( sName );
    // First delete the previous formula.
    // Without redistributing the pages.
    if (pFormulaDst)    // If the Association exist
    {
        if (!pFormulaDst->DeletePageFormulas( iPage, FALSE ))
            return FALSE;
    }
    if (!pFormulaDst)    // If the Association does not exist create it before
    {
        SchemaDst.Create( sName );
        pFormulaDst =     (ZAFormulaSchema*)SchemaDst.GetFormulaSchema( sName );
        ASSERT( pFormulaDst != NULL );
    }
    return pFormula->CopyPageFormulas( pFormulaDst, iPage );
}

BOOL    ZASchemaManager::DeleteFormulaList( const CString& sName )
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition( );
    
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext( Position );
        if (obj->GetSchemaName() == sName)
        {
            // Save the position within the list
            Position = m_lstSchema.Find( obj ); 
            // Destroy the object
            delete (ZAFormulaSchema*)obj;
            // Destroy the object in the list
            m_lstSchema.RemoveAt( Position );
            return TRUE;
        }
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ZASchemaManager serialization

void ZASchemaManager::Serialize(CArchive& ar)
{
    m_lstSchema.Serialize( ar );
}

void ZASchemaManager::ReadSerializeOldFormat(CArchive& ar)
{
    // Create the original schema
    Create(g_OriginalSchema);
    GetFormulaList(g_OriginalSchema)->Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// ZASchemaManager diagnostics

#ifdef _DEBUG
void ZASchemaManager::AssertValid() const
{
    CObject::AssertValid();
}

void ZASchemaManager::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

