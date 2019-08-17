/****************************************************************************
 * ==> PSS_Formula ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a formula and its associated manager and schema   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "formula.h"

// processsoft
#include "ZAObject.h"
#include "ZDDoc.h"
#include "PSS_DocumentData.h"
#include "PSS_MsgBox.h"

// Windows
#include <Math.h>
#include <IO.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Formula, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Formula
//---------------------------------------------------------------------------
PSS_Formula::PSS_Formula() :
    m_pResultObject(NULL),
    m_Page(0)
{}
//---------------------------------------------------------------------------
PSS_Formula::PSS_Formula(ZDDocument& doc, const CString& formula)
{
    const CString  temp = formula;
    int            sep;
    VERIFY((sep = temp.Find(',')) != -1);

    const CString page = temp.Left(sep);
    m_Page             = std::atoi(page);
    m_Formula          = temp.Right(temp.GetLength() - sep - 1);

    char* pFind;

    // extract the object name
    VERIFY(pFind = const_cast<char*>(std::strchr(m_Formula, '=')));

    m_ObjectName       = m_Formula.Left(int(pFind - m_Formula - 1));
    m_ExtractedFormula = pFind + 1;

    // get the pointer to the object
    m_pResultObject = doc.GetObjectPtr(m_ObjectName);
    ASSERT(m_pResultObject);
}
//---------------------------------------------------------------------------
PSS_Formula::PSS_Formula(const PSS_Formula& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Formula::~PSS_Formula()
{}
//---------------------------------------------------------------------------
const PSS_Formula& PSS_Formula::operator = (const PSS_Formula& other)
{
    m_Formula          = other.m_Formula;
    m_ExtractedFormula = other.m_ExtractedFormula;
    m_ObjectName       = other.m_ObjectName;
    m_Page             = other.m_Page;

    // not a deep copy
    m_pResultObject = other.m_pResultObject;

    return *this;
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_Formula::Clone() const
{
    std::unique_ptr<PSS_Formula> pFormula(new PSS_Formula(*this));
    return pFormula.release();
}
//---------------------------------------------------------------------------
void PSS_Formula::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write informations
        ar << WORD(m_Page);
        ar << m_Formula;
        ar << m_ExtractedFormula;
        ar << m_ObjectName;
    }
    else
    {
        // read informations
        WORD temp;
        ar >> temp;
        m_Page = int(temp);

        ar >> m_Formula;
        ar >> m_ExtractedFormula;
        ar >> m_ObjectName;

        // assign the result object pointer to NULL
        m_pResultObject = NULL;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Formula::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Formula::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_Formula::ConstructObjectPointer(PSS_DocumentData& doc, CObList& formulas)
{
    PSS_Formula* pObj;
    POSITION     pPosition = formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)formulas.GetNext(pPosition);
        ASSERT(pObj);

        // get the object
        pObj->m_pResultObject = doc.GetObject(pObj->m_ObjectName);

        if (!pObj->m_pResultObject)
        {
            CString prompt;
            AfxFormatString1(prompt, IDS_OBJECTMISSING, pObj->m_ObjectName);

            PSS_MsgBox mBox;
            mBox.Show(prompt, MB_OK);
        }
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(ZAFormulaAssociation, CObject, g_DefVersion)

ZAFormulaAssociation::ZAFormulaAssociation()
{}

ZAFormulaAssociation::ZAFormulaAssociation(const CString& Name, const CString& ObjectNameInitiator)
    : m_AssociationName(Name), m_ObjectNameInitiator(ObjectNameInitiator)
{}


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

    PSS_Formula*              obj;
    POSITION                Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        pNewAssociation->m_lstFormula.AddTail(obj->Clone());
    }
    // Copy members
    pNewAssociation->m_AssociationName = m_AssociationName;
    pNewAssociation->m_ObjectNameInitiator = m_ObjectNameInitiator;
    return pNewAssociation;
}

void ZAFormulaAssociation::AddFormula(PSS_Formula* pFormula)
{
    m_lstFormula.AddTail(pFormula);
}

void ZAFormulaAssociation::DeleteFormula(const CString& Name)
{
    PSS_Formula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetObjectName() == Name)
        {
            DeleteFormula(obj);
            return;
        }
    }
}

void ZAFormulaAssociation::DeleteFormula(PSS_Formula* pFormula)
{
    POSITION    Position = m_lstFormula.Find(pFormula);

    if (Position)
    {
        delete (PSS_Formula*)pFormula;
        // Destroy the object in the list
        m_lstFormula.RemoveAt(Position);
    }
}

PSS_Formula*    ZAFormulaAssociation::GetFormulaAt(int Index)
{
    POSITION    Position = m_lstFormula.FindIndex(Index);
    if (Position)
        return (PSS_Formula*)m_lstFormula.GetAt(Position);
    return NULL;
}


PSS_Formula* ZAFormulaAssociation::FindFormula(const CString& Name)
{
    PSS_Formula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetObjectName() == Name)
            return obj;
    }
    return NULL;
}

PSS_Formula* ZAFormulaAssociation::FindFormulaFullString(const CString& Formula)
{
    PSS_Formula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetFormula() == Formula)
            return obj;
    }
    return NULL;
}


size_t ZAFormulaAssociation::GetFormulaArray(CStringArray& Array)
{
    PSS_Formula*  obj;
    POSITION    Position = m_lstFormula.GetHeadPosition();

    Array.RemoveAll();
    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        Array.Add(obj->GetFormula());
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
    m_lstFormula.Serialize(ar);
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
    : m_pCurrentAssociation(NULL)
{}

ZAFormulaAssociationManager::~ZAFormulaAssociationManager()
{
    while (!m_lstAssociation.IsEmpty())
    {
        delete m_lstAssociation.GetHead();
        m_lstAssociation.RemoveHead();
    }
}

void ZAFormulaAssociationManager::AssignContents(const ZAFormulaAssociationManager& ManagerSource)
{
    // First delete the contents
    while (!m_lstAssociation.IsEmpty())
    {
        delete m_lstAssociation.GetHead();
        m_lstAssociation.RemoveHead();
    }

    ZAFormulaAssociation*      obj;
    POSITION                Position = ManagerSource.m_lstAssociation.GetHeadPosition();

    while (Position)
    {
        // Read the next element of the source
        obj = (ZAFormulaAssociation*)ManagerSource.m_lstAssociation.GetNext(Position);
        // Add a clone of the element to the list
        m_lstAssociation.AddTail(obj->Clone());
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
    POSITION                Position = m_lstAssociation.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext(Position);
        pNewAssociationManager->m_lstAssociation.AddTail(obj->Clone());
    }
    // Set Association to null
    pNewAssociationManager->m_pCurrentAssociation = NULL;
    // Refresh the dynamic association array
    pNewAssociationManager->RefreshAssociationArray();
    return pNewAssociationManager;
}


void    ZAFormulaAssociationManager::AddAssociation(ZAFormulaAssociation* pAssociation)
{
    m_lstAssociation.AddTail(pAssociation);
}

void    ZAFormulaAssociationManager::DeleteAssociation(ZAFormulaAssociation* pAssociation)
{
    POSITION    Position = m_lstAssociation.Find(pAssociation);

    if (Position)
    {
        delete (ZAFormulaAssociation*)pAssociation;
        // Destroy the object in the list
        m_lstAssociation.RemoveAt(Position);
    }
}

void    ZAFormulaAssociationManager::DeleteAssociation(const CString& Name)
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext(Position);
        if (obj->GetAssociationName() == Name)
        {
            DeleteAssociation(obj);
            return;
        }
    }
}

ZAFormulaAssociation*    ZAFormulaAssociationManager::FindAssociation(const CString& Name)
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext(Position);
        if (obj->GetAssociationName() == Name)
            return obj;
    }
    return NULL;
}


CStringArray& ZAFormulaAssociationManager::RefreshAssociationArray()
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition();

    m_AssociationArrayName.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext(Position);
        m_AssociationArrayName.Add(obj->GetAssociationName());
    }
    return m_AssociationArrayName;
}


// Run through the list of association
// and for each association, construct all formula pointers
void ZAFormulaAssociationManager::InitializeFormulaAssociations(PSS_DocumentData& doc)
{
    ZAFormulaAssociation*  obj;
    POSITION            Position = m_lstAssociation.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaAssociation*)m_lstAssociation.GetNext(Position);
        PSS_Formula::ConstructObjectPointer(doc, obj->GetFormulaList());
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZAFormulaAssociationManager serialization

void ZAFormulaAssociationManager::Serialize(CArchive& ar)
{
    m_lstAssociation.Serialize(ar);
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
    : m_sDescription(""), m_FormulaSchemaType(UserSchema)
{}

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

    PSS_Formula*          obj;
    POSITION            Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        PSS_Formula*    pNewFormula = new PSS_Formula;
        (PSS_Formula&)*pNewFormula = (PSS_Formula&)*obj;
        pNewFormulaSchema->m_lstFormula.AddTail(pNewFormula);
    }
    // Copy the name
    pNewFormulaSchema->m_sSchemaName = m_sSchemaName;
    pNewFormulaSchema->m_sDescription = m_sDescription;
    pNewFormulaSchema->m_FormulaSchemaType = m_FormulaSchemaType;
    return pNewFormulaSchema;
}


BOOL        ZAFormulaSchema::DeletePageFormulas(int iPage, BOOL bRedistribute)
{
    PSS_Formula*          obj;
    POSITION            Position = m_lstFormula.GetHeadPosition();

    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetPage() == iPage)
        {
            // Save the position within the list
            POSITION ElementPosition = m_lstFormula.Find(obj);
            if (!ElementPosition)
                return FALSE;
            // Destroy the object
            delete (PSS_Formula*)obj;
            // Destroy the object in the list
            m_lstFormula.RemoveAt(ElementPosition);
        }
    }

    if (bRedistribute)
    {
        // Redistribute the objects' pages
        Position = m_lstFormula.GetTailPosition();

        while (Position)
        {
            obj = (PSS_Formula*)m_lstFormula.GetPrev(Position);
            // Test the object's page, if before the deleted page
            // continue the loop
            // For formula it impossible to stop the loop
            // because the formulas are not necessary sorted
            // by page
            if (obj->GetPage() < iPage)
                continue;
            obj->SetPage(obj->GetPage() - 1);
        }
    }
    return TRUE;
}

BOOL        ZAFormulaSchema::CopyPageFormulas(ZAFormulaSchema*    pFormulaDst, int iPage)
{
    PSS_Formula*          obj;
    POSITION            Position;
    POSITION            InsertedPosition = NULL;
    // Count in the source formula the
    // number of elements before finding the first
    // formula corresponding to the page    
    int        iPos;
    BOOL    bFoundOne = FALSE;
    for (Position = m_lstFormula.GetHeadPosition(), iPos = 0; Position; ++iPos)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetPage() == iPage)
        {
            bFoundOne = TRUE;
            break;
        }
    }
    // If nothing found, OK
    if (!bFoundOne)
        return TRUE;

    Position = m_lstFormula.GetHeadPosition();
    while (Position)
    {
        obj = (PSS_Formula*)m_lstFormula.GetNext(Position);
        if (obj->GetPage() == iPage)
        {
            // If it is the first element to be inserted,
            // make a loop to count the initial position
            if (!InsertedPosition)
            {
                if (!iPos)
                {
                    InsertedPosition = pFormulaDst->m_lstFormula.AddHead((CObject*)obj->Clone());
                    continue;
                }
                else
                {
                    InsertedPosition = pFormulaDst->m_lstFormula.GetHeadPosition();

                    for (int iSearchPosition = 0; InsertedPosition && iSearchPosition < iPos; ++iSearchPosition)
                    {
                        pFormulaDst->m_lstFormula.GetNext(InsertedPosition);
                    }
                }
            }
            InsertedPosition = pFormulaDst->m_lstFormula.InsertAfter(InsertedPosition, (CObject*)obj->Clone());
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
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_sDescription;
            WORD    wTemp;
            ar >> wTemp;
            m_FormulaSchemaType = (FormulaSchemaType)wTemp;
        }
        else
        {
            CString    sText;
            sText.LoadString(IDS_DESCRIPTIONSTANDARDSCHEMA);
            SetDescription(sText);
            SetFormulaSchemaType(UserSchema);
        }
    }
    m_lstFormula.Serialize(ar);
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
{}

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

    Position = ((ZASchemaManager &)right).m_lstSchema.GetHeadPosition();
    while (Position)
    {
        obj = (ZAFormulaSchema *)((ZASchemaManager &)right).m_lstSchema.GetNext(Position);
        m_lstSchema.AddTail(obj->Clone());
    }
    return *this;
}

ZASchemaManager*    ZASchemaManager::Clone()
{
    ZASchemaManager*    pNewManager = new ZASchemaManager(*this);
    return pNewManager;
}

void ZASchemaManager::InitializeSchemaObjectPointer(PSS_DocumentData& Doc)
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        PSS_Formula::ConstructObjectPointer(Doc, obj->GetFormulaList());
    }
}


void ZASchemaManager::CreateStandardEmptySchema()
{
    // Create the original schema
    Create(g_OriginalSchema);
}

void ZASchemaManager::Create(const CString& sName)
{
    // Create the original 
    ZAFormulaSchema*    pOriginalSchema = new ZAFormulaSchema;

    pOriginalSchema->SetSchemaName(sName);
    m_lstSchema.AddTail(pOriginalSchema);

}

CObList*        ZASchemaManager::GetFormulaSchema(const CString& sName)
{
    if (sName.IsEmpty())
        return NULL;
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        if (obj->GetSchemaName() == sName)
            return (CObList*)obj;
    }
    return NULL;
}

CObList*    ZASchemaManager::GetFormulaList(const CString& sName)
{
    if (sName.IsEmpty())
        return NULL;
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        if (obj->GetSchemaName() == sName)
            return &(obj->GetFormulaList());
    }
    return NULL;
}

CStringArray&    ZASchemaManager::GetFormulaArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        m_SchemaNameArray.Add(obj->GetSchemaName());
    }
    return m_SchemaNameArray;
}

CStringArray&    ZASchemaManager::GetFormulaUserArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        if (obj->GetFormulaSchemaType() == UserSchema)
            m_SchemaNameArray.Add(obj->GetSchemaName());
    }
    return m_SchemaNameArray;
}

CStringArray&    ZASchemaManager::GetFormulaSystemArrayName()
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        if (obj->GetFormulaSchemaType() == SystemSchema)
            m_SchemaNameArray.Add(obj->GetSchemaName());
    }
    return m_SchemaNameArray;
}

BOOL    ZASchemaManager::CopySchema(const CString& sSource, const CString sNew)
{
    ZAFormulaSchema*    pSource;
    pSource = (ZAFormulaSchema*)GetFormulaSchema(sSource);
    if (pSource)
    {
        ZAFormulaSchema*    pNew = pSource->Clone();
        pNew->SetSchemaName(sNew);
        m_lstSchema.AddTail(pNew);
        return TRUE;
    }
    return FALSE;
}


BOOL    ZASchemaManager::DeletePageFormulas(int iPage)
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();
    BOOL                bRetValue = 0;
    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        bRetValue |= !DeletePageFormulas(obj->GetSchemaName(), iPage);
    }
    return !bRetValue;
}

BOOL    ZASchemaManager::DeletePageFormulas(const CString& sName, int iPage)
{
    ZAFormulaSchema*    pFormula = (ZAFormulaSchema*)GetFormulaSchema(sName);
    return pFormula->DeletePageFormulas(iPage);
}

BOOL    ZASchemaManager::CopyPageFormulas(const CString& sName, ZASchemaManager& SchemaDst, int iPage)
{
    ZAFormulaSchema*    pFormula = (ZAFormulaSchema*)GetFormulaSchema(sName);
    ZAFormulaSchema*    pFormulaDst = (ZAFormulaSchema*)SchemaDst.GetFormulaSchema(sName);
    // First delete the previous formula.
    // Without redistributing the pages.
    if (pFormulaDst)    // If the Association exist
    {
        if (!pFormulaDst->DeletePageFormulas(iPage, FALSE))
            return FALSE;
    }
    if (!pFormulaDst)    // If the Association does not exist create it before
    {
        SchemaDst.Create(sName);
        pFormulaDst = (ZAFormulaSchema*)SchemaDst.GetFormulaSchema(sName);
        ASSERT(pFormulaDst != NULL);
    }
    return pFormula->CopyPageFormulas(pFormulaDst, iPage);
}

BOOL    ZASchemaManager::DeleteFormulaList(const CString& sName)
{
    ZAFormulaSchema*      obj;
    POSITION            Position = m_lstSchema.GetHeadPosition();

    while (Position)
    {
        obj = (ZAFormulaSchema*)m_lstSchema.GetNext(Position);
        if (obj->GetSchemaName() == sName)
        {
            // Save the position within the list
            Position = m_lstSchema.Find(obj);
            // Destroy the object
            delete (ZAFormulaSchema*)obj;
            // Destroy the object in the list
            m_lstSchema.RemoveAt(Position);
            return TRUE;
        }
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ZASchemaManager serialization

void ZASchemaManager::Serialize(CArchive& ar)
{
    m_lstSchema.Serialize(ar);
}

void ZASchemaManager::ReadSerializeOldFormat(CArchive& ar)
{
    // Create the original schema
    Create(g_OriginalSchema);
    GetFormulaList(g_OriginalSchema)->Serialize(ar);
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

