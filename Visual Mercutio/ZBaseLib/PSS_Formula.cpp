/****************************************************************************
 * ==> PSS_Formula ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a formula and its associated manager and schema   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Formula.h"

// processsoft
#include "PSS_PlanFinObject.h"
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
    CObject(),
    m_pResultObject(NULL),
    m_Page(0)
{}
//---------------------------------------------------------------------------
PSS_Formula::PSS_Formula(ZDDocument& doc, const CString& formula) :
    CObject()
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

    // get the result object pointer
    m_pResultObject = doc.GetObjectPtr(m_ObjectName);
    ASSERT(m_pResultObject);
}
//---------------------------------------------------------------------------
PSS_Formula::PSS_Formula(const PSS_Formula& other) :
    CObject()
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
IMPLEMENT_SERIAL(PSS_FormulaAssociation, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FormulaAssociation
//---------------------------------------------------------------------------
PSS_FormulaAssociation::PSS_FormulaAssociation() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_FormulaAssociation::PSS_FormulaAssociation(const CString& name, const CString& objectNameInitiator) :
    CObject(),
    m_AssociationName(name),
    m_ObjectNameInitiator(objectNameInitiator)
{}
//---------------------------------------------------------------------------
PSS_FormulaAssociation::~PSS_FormulaAssociation()
{
    while (!m_Formulas.IsEmpty())
    {
        delete m_Formulas.GetHead();
        m_Formulas.RemoveHead();
    }
}
//---------------------------------------------------------------------------
PSS_FormulaAssociation* PSS_FormulaAssociation::Clone() const
{
    std::unique_ptr<PSS_FormulaAssociation> pNewAssociation(new PSS_FormulaAssociation());

    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    // clone the formulas
    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);
        pNewAssociation->m_Formulas.AddTail(pObj->Clone());
    }

    // copy members
    pNewAssociation->m_AssociationName     = m_AssociationName;
    pNewAssociation->m_ObjectNameInitiator = m_ObjectNameInitiator;

    return pNewAssociation.release();
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::AddFormula(PSS_Formula* pFormula)
{
    m_Formulas.AddTail(pFormula);
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::DeleteFormula(const CString& name)
{
    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetObjectName() == name)
        {
            DeleteFormula(pObj);
            return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::DeleteFormula(PSS_Formula* pFormula)
{
    POSITION pPosition = m_Formulas.Find(pFormula);

    if (pPosition)
    {
        delete pFormula;

        // remove the object from the list
        m_Formulas.RemoveAt(pPosition);
    }
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_FormulaAssociation::GetFormulaAt(int index)
{
    POSITION pPosition = m_Formulas.FindIndex(index);

    if (pPosition)
        return (PSS_Formula*)m_Formulas.GetAt(pPosition);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_FormulaAssociation::FindFormula(const CString& name)
{
    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetObjectName() == name)
            return pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_FormulaAssociation::FindFormulaFullString(const CString& formula)
{
    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetFormula() == formula)
            return pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
std::size_t PSS_FormulaAssociation::GetFormulaArray(CStringArray& formulaArray)
{
    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    formulaArray.RemoveAll();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);
        formulaArray.Add(pObj->GetFormula());
    }

    // return the element count
    return formulaArray.GetSize();
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociation::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write informations
        ar << m_AssociationName;
        ar << m_ObjectNameInitiator;
    }
    else
    {
        // read informations
        ar >> m_AssociationName;
        ar >> m_ObjectNameInitiator;
    }

    m_Formulas.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaAssociation::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaAssociation::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FormulaAssociationManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FormulaAssociationManager
//---------------------------------------------------------------------------
PSS_FormulaAssociationManager::PSS_FormulaAssociationManager() :
    CObject(),
    m_pCurrentAssociation(NULL)
{}
//---------------------------------------------------------------------------
PSS_FormulaAssociationManager::~PSS_FormulaAssociationManager()
{
    while (!m_Associations.IsEmpty())
    {
        delete m_Associations.GetHead();
        m_Associations.RemoveHead();
    }
}
//---------------------------------------------------------------------------
PSS_FormulaAssociationManager* PSS_FormulaAssociationManager::Clone() const
{
    std::unique_ptr<PSS_FormulaAssociationManager> pNewAssociationManager(new PSS_FormulaAssociationManager());

    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = m_Associations.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaAssociation*)m_Associations.GetNext(pPosition);
        pNewAssociationManager->m_Associations.AddTail(pObj->Clone());
    }

    // set association to null
    pNewAssociationManager->m_pCurrentAssociation = NULL;

    // refresh the dynamic association array
    pNewAssociationManager->RefreshAssociationArray();

    return pNewAssociationManager.release();
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::InitializeFormulaAssociations(PSS_DocumentData& doc)
{
    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = m_Associations.GetHeadPosition();

    // iterate through the list of association and for each association, construct all formula pointers
    while (pPosition)
    {
        pObj = (PSS_FormulaAssociation*)m_Associations.GetNext(pPosition);
        PSS_Formula::ConstructObjectPointer(doc, pObj->GetFormulas());
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::AddAssociation(PSS_FormulaAssociation* pAssociation)
{
    m_Associations.AddTail(pAssociation);
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::DeleteAssociation(const CString& name)
{
    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = m_Associations.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaAssociation*)m_Associations.GetNext(pPosition);

        if (pObj->GetAssociationName() == name)
        {
            DeleteAssociation(pObj);
            return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::DeleteAssociation(PSS_FormulaAssociation* pAssociation)
{
    POSITION pPosition = m_Associations.Find(pAssociation);

    if (pPosition)
    {
        delete pAssociation;

        // remove the object from the list
        m_Associations.RemoveAt(pPosition);
    }
}
//---------------------------------------------------------------------------
PSS_FormulaAssociation* PSS_FormulaAssociationManager::FindAssociation(const CString& name)
{
    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = m_Associations.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaAssociation*)m_Associations.GetNext(pPosition);

        if (pObj->GetAssociationName() == name)
            return pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
CStringArray& PSS_FormulaAssociationManager::RefreshAssociationArray()
{
    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = m_Associations.GetHeadPosition();

    m_AssociationArrayName.RemoveAll();

    while (pPosition)
    {
        pObj = (PSS_FormulaAssociation*)m_Associations.GetNext(pPosition);
        m_AssociationArrayName.Add(pObj->GetAssociationName());
    }
    return m_AssociationArrayName;
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::AssignContents(const PSS_FormulaAssociationManager& managerSource)
{
    // delete the contents
    while (!m_Associations.IsEmpty())
    {
        delete m_Associations.GetHead();
        m_Associations.RemoveHead();
    }

    PSS_FormulaAssociation* pObj;
    POSITION                pPosition = managerSource.m_Associations.GetHeadPosition();

    while (pPosition)
    {
        // read the next element of the source
        pObj = (PSS_FormulaAssociation*)managerSource.m_Associations.GetNext(pPosition);

        // add a clone of the element to the list
        m_Associations.AddTail(pObj->Clone());
    }

    // set Association to null
    m_pCurrentAssociation = NULL;

    // refresh the dynamic association array
    RefreshAssociationArray();
}
//---------------------------------------------------------------------------
void PSS_FormulaAssociationManager::Serialize(CArchive& ar)
{
    m_Associations.Serialize(ar);

    if (ar.IsStoring())
        ar << m_pCurrentAssociation;
    else
    {
        ar >> m_pCurrentAssociation;

        // refresh the dynamic association array
        RefreshAssociationArray();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaAssociationManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaAssociationManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FormulaSchema, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FormulaSchema
//---------------------------------------------------------------------------
PSS_FormulaSchema::PSS_FormulaSchema() :
    CObject(),
    m_FormulaSchemaType(IE_T_User)
{}
//---------------------------------------------------------------------------
PSS_FormulaSchema::~PSS_FormulaSchema()
{
    while (!m_Formulas.IsEmpty())
    {
        delete m_Formulas.GetHead();
        m_Formulas.RemoveHead();
    }
}
//---------------------------------------------------------------------------
PSS_FormulaSchema* PSS_FormulaSchema::Clone() const
{
    std::unique_ptr<PSS_FormulaSchema> pNewFormulaSchema(new PSS_FormulaSchema());

    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        std::unique_ptr<PSS_Formula> pNewFormula(new PSS_Formula());
        (PSS_Formula&)*pNewFormula = (PSS_Formula&)*pObj;
        pNewFormulaSchema->m_Formulas.AddTail(pNewFormula.get());
    }

    // copy the name
    pNewFormulaSchema->m_SchemaName        = m_SchemaName;
    pNewFormulaSchema->m_Description       = m_Description;
    pNewFormulaSchema->m_FormulaSchemaType = m_FormulaSchemaType;

    return pNewFormulaSchema.release();
}
//---------------------------------------------------------------------------
BOOL PSS_FormulaSchema::DeletePageFormulas(int page, BOOL redistribute)
{
    PSS_Formula* pObj;
    POSITION     pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetPage() == page)
        {
            // save the position within the list
            POSITION pElementPosition = m_Formulas.Find(pObj);

            if (!pElementPosition)
                return FALSE;

            // delete the object
            delete pObj;

            // remove the object from the list
            m_Formulas.RemoveAt(pElementPosition);
        }
    }

    if (redistribute)
    {
        // redistribute the object's pages
        pPosition = m_Formulas.GetTailPosition();

        while (pPosition)
        {
            pObj = (PSS_Formula*)m_Formulas.GetPrev(pPosition);

            // test the object's page, if before the deleted page, continue the loop.
            // For formula it impossible to stop the loop because the formulas are not
            // necessary sorted by page
            if (pObj->GetPage() < page)
                continue;

            pObj->SetPage(pObj->GetPage() - 1);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FormulaSchema::CopyPageFormulas(PSS_FormulaSchema* pFormulaDst, int page)
{
    PSS_Formula* pObj;
    POSITION     pPosition;
    POSITION     pInsertedPosition = NULL;
    int          pos;
    BOOL         foundOne          = FALSE;

    // count in the source formula the number of elements before finding the first
    // formula corresponding to the page
    for (pPosition = m_Formulas.GetHeadPosition(), pos = 0; pPosition; ++pos)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetPage() == page)
        {
            foundOne = TRUE;
            break;
        }
    }

    // if nothing found, OK
    if (!foundOne)
        return TRUE;

    pPosition = m_Formulas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Formulas.GetNext(pPosition);

        if (pObj->GetPage() == page)
        {
            // if it's the first element to be inserted, make a loop to count the initial position
            if (!pInsertedPosition)
            {
                if (!pos)
                {
                    pInsertedPosition = pFormulaDst->m_Formulas.AddHead((CObject*)pObj->Clone());
                    continue;
                }
                else
                {
                    pInsertedPosition = pFormulaDst->m_Formulas.GetHeadPosition();

                    for (int searchPosition = 0; pInsertedPosition && searchPosition < pos; ++searchPosition)
                        pFormulaDst->m_Formulas.GetNext(pInsertedPosition);
                }
            }

            pInsertedPosition = pFormulaDst->m_Formulas.InsertAfter(pInsertedPosition, (CObject*)pObj->Clone());
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FormulaSchema::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write informations
        ar << m_SchemaName;
        ar << m_Description;
        ar << WORD(m_FormulaSchemaType);
    }
    else
    {
        // read informations
        ar >> m_SchemaName;

        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_Description;

            WORD temp;
            ar >> temp;
            m_FormulaSchemaType = IEType(temp);
        }
        else
        {
            CString text;
            text.LoadString(IDS_DESCRIPTIONSTANDARDSCHEMA);
            SetDescription(text);
            SetFormulaSchemaType(IE_T_User);
        }
    }

    m_Formulas.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaSchema::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FormulaSchema::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
CStringArray PSS_SchemaManager::m_SchemaNameArray;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SchemaManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SchemaManager
//---------------------------------------------------------------------------
PSS_SchemaManager::PSS_SchemaManager()
{}
//---------------------------------------------------------------------------
PSS_SchemaManager::PSS_SchemaManager(const PSS_SchemaManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SchemaManager::~PSS_SchemaManager()
{
    while (!m_Schemas.IsEmpty())
    {
        delete m_Schemas.GetHead();
        m_Schemas.RemoveHead();
    }
}
//---------------------------------------------------------------------------
const PSS_SchemaManager& PSS_SchemaManager::operator = (const PSS_SchemaManager& other)
{
    PSS_SchemaManager* pObj;
    POSITION           pPosition = ((PSS_SchemaManager&)other).m_Schemas.GetHeadPosition();

    // copy elements
    while (pPosition)
    {
        pObj = (PSS_SchemaManager*)((PSS_SchemaManager&)other).m_Schemas.GetNext(pPosition);
        m_Schemas.AddTail(pObj->Clone());
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_SchemaManager* PSS_SchemaManager::Clone() const
{
    std::unique_ptr<PSS_SchemaManager> pNewManager(new PSS_SchemaManager(*this));
    return pNewManager.release();
}
//---------------------------------------------------------------------------
void PSS_SchemaManager::Create(const CString& name)
{
    // create the original 
    std::unique_ptr<PSS_FormulaSchema> pOriginalSchema(new PSS_FormulaSchema());

    pOriginalSchema->SetSchemaName(name);
    m_Schemas.AddTail(pOriginalSchema.get());
    pOriginalSchema.release();

}
//---------------------------------------------------------------------------
void PSS_SchemaManager::CreateStandardEmptySchema()
{
    // create the original schema
    Create(g_OriginalSchema);
}
//---------------------------------------------------------------------------
void PSS_SchemaManager::InitializeSchemaObjectPointer(PSS_DocumentData& doc)
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);
        PSS_Formula::ConstructObjectPointer(doc, pObj->GetFormulaList());
    }
}
//---------------------------------------------------------------------------
BOOL PSS_SchemaManager::CopySchema(const CString& source, const CString newManager)
{
    PSS_FormulaSchema* pSource = (PSS_FormulaSchema*)GetFormulaSchema(source);

    if (pSource)
    {
        std::unique_ptr<PSS_FormulaSchema> pNewManager(pSource->Clone());
        pNewManager->SetSchemaName(newManager);
        m_Schemas.AddTail(pNewManager.get());
        pNewManager.release();
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
CObList* PSS_SchemaManager::GetFormulaList(const CString& name)
{
    if (name.IsEmpty())
        return NULL;

    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);

        if (pObj->GetSchemaName() == name)
            return &(pObj->GetFormulaList());
    }

    return NULL;
}
//---------------------------------------------------------------------------
CObList* PSS_SchemaManager::GetFormulaSchema(const CString& name)
{
    if (name.IsEmpty())
        return NULL;

    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);

        if (pObj->GetSchemaName() == name)
            return (CObList*)pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_SchemaManager::DeleteFormulaList(const CString& name)
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);

        if (pObj->GetSchemaName() == name)
        {
            // save the position within the list
            pPosition = m_Schemas.Find(pObj);

            // delete the object
            delete pObj;

            // remove the object in the list
            m_Schemas.RemoveAt(pPosition);

            return TRUE;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_SchemaManager::CopyPageFormulas(const CString& name, PSS_SchemaManager& schemaDst, int page)
{
    PSS_FormulaSchema* pFormula    = (PSS_FormulaSchema*)GetFormulaSchema(name);
    PSS_FormulaSchema* pFormulaDst = (PSS_FormulaSchema*)schemaDst.GetFormulaSchema(name);

    if (!pFormula)
        return FALSE;

    if (pFormulaDst)
    {
        // delete the previous formula without redistributing the pages
        if (!pFormulaDst->DeletePageFormulas(page, FALSE))
            return FALSE;
    }
    else
    {
        // if the association does not exist, create it before
        schemaDst.Create(name);
        pFormulaDst = (PSS_FormulaSchema*)schemaDst.GetFormulaSchema(name);
        ASSERT(pFormulaDst);
    }

    return pFormula->CopyPageFormulas(pFormulaDst, page);
}
//---------------------------------------------------------------------------
BOOL PSS_SchemaManager::DeletePageFormulas(const CString& name, int page)
{
    PSS_FormulaSchema* pFormula = (PSS_FormulaSchema*)GetFormulaSchema(name);
    return pFormula->DeletePageFormulas(page);
}
//---------------------------------------------------------------------------
BOOL PSS_SchemaManager::DeletePageFormulas(int page)
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();
    BOOL               result    = FALSE;

    while (pPosition)
    {
        pObj    = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);
        result |= !DeletePageFormulas(pObj->GetSchemaName(), page);
    }

    return !result;
}
//---------------------------------------------------------------------------
CStringArray& PSS_SchemaManager::GetFormulaArrayName()
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);
        m_SchemaNameArray.Add(pObj->GetSchemaName());
    }

    return m_SchemaNameArray;
}
//---------------------------------------------------------------------------
CStringArray& PSS_SchemaManager::GetFormulaUserArrayName()
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);

        if (pObj->GetFormulaSchemaType() == PSS_FormulaSchema::IE_T_User)
            m_SchemaNameArray.Add(pObj->GetSchemaName());
    }

    return m_SchemaNameArray;
}
//---------------------------------------------------------------------------
CStringArray& PSS_SchemaManager::GetFormulaSystemArrayName()
{
    PSS_FormulaSchema* pObj;
    POSITION           pPosition = m_Schemas.GetHeadPosition();

    m_SchemaNameArray.RemoveAll();

    while (pPosition)
    {
        pObj = (PSS_FormulaSchema*)m_Schemas.GetNext(pPosition);

        if (pObj->GetFormulaSchemaType() == PSS_FormulaSchema::IE_T_System)
            m_SchemaNameArray.Add(pObj->GetSchemaName());
    }

    return m_SchemaNameArray;
}
//---------------------------------------------------------------------------
void PSS_SchemaManager::Serialize(CArchive& ar)
{
    m_Schemas.Serialize(ar);
}
//---------------------------------------------------------------------------
void PSS_SchemaManager::ReadSerializeOldFormat(CArchive& ar)
{
    // create the original schema
    Create(g_OriginalSchema);
    GetFormulaList(g_OriginalSchema)->Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SchemaManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_SchemaManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
