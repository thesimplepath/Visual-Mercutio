/****************************************************************************
 * ==> PSS_DocumentData ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document data container                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_DocumentData.h"

// processsoft
#include "ZAObject.h"
#include "PSS_PlanFinObj.h"
#include "PSS_PLFNBoundText.h"
#include "ZARadio.h"
#include "PSS_PLFNCheckBtn.h"
#include "PSS_PLFNBitmap.h"
#include "ZASquare.h"
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_PLFNMultiColumn.h"
#include "PSS_ObsoletePLFNObj.h"
#include "PSS_PLFNBackImage.h"
#include "ZBFldCol.h"
#include "PSS_FileBuffer.h"
#include "PSS_FieldRepository.h"
#include "ZBTokenizer.h"
#include "PSS_MsgBox.h"
#include "PSS_ObjectUtility.h"
#include "ZIView.h"
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DocumentData, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DocumentData
//---------------------------------------------------------------------------
PSS_DocumentData::PSS_DocumentData(ZDDocument* pDocument) :
    CObject(),
    m_CurrentPage(1),
    m_EndCalculateTime(CTime::GetCurrentTime()),
    m_pDocument(pDocument),
    m_pFileBuffer(NULL),
    m_pCurrentEditedObject(NULL),
    m_pPosition(NULL),
    m_LastTabOrder(0),
    m_PageMax(0),
    m_FlagElapsedTime(FALSE),
    m_IsVisible(TRUE),
    m_ReadOnlyAtRuntime(FALSE)
{
    m_BinaryDrawMessage.LoadString(IDS_BINARYDOC_DRAWMESSAGE);
}
//---------------------------------------------------------------------------
PSS_DocumentData::PSS_DocumentData(const PSS_DocumentData& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DocumentData::~PSS_DocumentData()
{
    DeleteAllObjects();
    DeleteTemporaryFile();
}
//---------------------------------------------------------------------------
const PSS_DocumentData& PSS_DocumentData::operator = (const PSS_DocumentData& other)
{
    m_CurrentPage          = other.m_CurrentPage;
    m_EndCalculateTime     = other.m_EndCalculateTime;
    m_pDocument            = other.m_pDocument;
    m_Stamp                = other.m_Stamp;
    m_Schema               = other.m_Schema;
    m_FontManager          = other.m_FontManager;
    m_StyleManager         = other.m_StyleManager;
    m_pCurrentEditedObject = NULL;
    m_pPosition            = NULL;
    m_CurrentSchema        = other.m_CurrentSchema;
    m_PageMax              = other.m_PageMax;
    m_FlagElapsedTime      = other.m_FlagElapsedTime;
    m_IsVisible            = other.m_IsVisible;
    m_ReadOnlyAtRuntime    = other.m_ReadOnlyAtRuntime;

    if (other.m_pFileBuffer)
        m_pFileBuffer = other.m_pFileBuffer->Clone();
    else
        m_pFileBuffer = NULL;

    POSITION       pPosition = ((PSS_DocumentData&)other).m_ObjElements.GetHeadPosition();
    PlanFinObject* pObj;

    // copy elements
    while (pPosition)
    {
        pObj = (PlanFinObject*)((PSS_DocumentData&)other).m_ObjElements.GetNext(pPosition);
        m_ObjElements.AddTail(pObj->Clone());
    }

    return *this;
}
//---------------------------------------------------------------------------
double PSS_DocumentData::GetObjectValue(char* pName)
{
    if (!pName)
        return 0.0;

    POSITION       pPosition = m_ObjElements.GetHeadPosition();
    PlanFinObject* pObj;

    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        if (pObj->CompareByName(pName))
            return(pObj->GetValue());
    }

    return 0.0;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::DeletePage(int page)
{
    if (!DeletePageObjects(page))
        return FALSE;

    // delete formulas on all schemas
    if (!m_Schema.DeletePageFormulas(page))
        return FALSE;

    SetCurrentPage(CountAndSetPages());

    m_pDocument->UpdateAllViews(NULL);
    m_pDocument->SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CopyPage(PSS_DocumentData* pDocumentDst, int page)
{
    if (!pDocumentDst)
        return FALSE;

    // delete page objects without redistributing pages
    if (!pDocumentDst->DeletePageObjects(page, FALSE))
        return FALSE;

    if (!CopyPageObjects(pDocumentDst, page))
        return FALSE;

          CStringArray& schemaArray = m_Schema.GetFormulaArrayName();
    const int           schemaCount = schemaArray.GetSize();

    // copy all schema
    for (int i = 0; i < schemaCount; ++i)
        if (!m_Schema.CopyPageFormulas(schemaArray[i], pDocumentDst->m_Schema, page))
            return FALSE;

    pDocumentDst->CountAndSetPages();
    pDocumentDst->GetDocument()->SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CopyPageOnlyObjects(PSS_DocumentData* pDocumentDst, int page)
{
    if (!pDocumentDst)
        return FALSE;

    // delete page objects without redistributing pages
    if (!pDocumentDst->DeletePageObjects(page, FALSE))
        return FALSE;

    if (!CopyPageObjects(pDocumentDst, page))
        return FALSE;

    pDocumentDst->CountAndSetPages();
    pDocumentDst->GetDocument()->SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CopyPageOnlyFormula(PSS_DocumentData* pDocumentDst, int page)
{
    if (!pDocumentDst)
        return FALSE;

          CStringArray& schemaArray = m_Schema.GetFormulaArrayName();
    const int           schemaCount = schemaArray.GetSize();

    // copy all schema
    for (int i = 0; i < schemaCount; ++i)
        if (!m_Schema.CopyPageFormulas(schemaArray[i], pDocumentDst->m_Schema, page))
            return FALSE;

    pDocumentDst->GetDocument()->SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CheckMultiColumnMemberField(PlanFinObject* pObj)
{
    if (!pObj)
        return FALSE;

          ZBTokenizer tokenizer('.');
    const CString     fieldName = tokenizer.GetFirstToken(pObj->GetObjectName());
    const CString     member    = tokenizer.GetNextToken();

    // if no member, next field
    if (member.IsEmpty())
        return FALSE;

    // locate the field name
    PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(GetObject(fieldName));

    // no object or not a multi-column field, do nothing
    if (!pMultiColumn)
        return FALSE;

    // Locate the column name
    ZBFieldColumn* pColumn = pMultiColumn->FindColumn(member);

    // if the column is found, assign the pointer
    if (pColumn)
    {
        pObj->SetpColumn(pColumn);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::MoveContents(PSS_DocumentData* pDocument, BOOL copyFormat)
{
    if (!pDocument)
        return;

    POSITION pPositionDst = pDocument->m_ObjElements.GetHeadPosition();

    while (pPositionDst)
    {
        PlanFinObject* pObjDst = (PlanFinObject*)pDocument->m_ObjElements.GetNext(pPositionDst);

        // for each element find the 
        POSITION pPositionSrc = m_ObjElements.GetHeadPosition();

        while (pPositionSrc)
        {
            PlanFinObject* pObjSrc = (PlanFinObject*)m_ObjElements.GetNext(pPositionSrc);

            // test if both objects are similar
            if (pObjSrc->GetObjectPage() == pObjDst->GetObjectPage() &&
                pObjSrc->GetObjectName() == pObjDst->GetObjectName())
            {
                if (!pObjSrc->IsEmpty())
                {
                    if (copyFormat)
                        pObjDst->SetFormatType(pObjSrc->GetFormatType());

                    pObjDst->ConvertFormattedObject(pObjSrc->GetFormattedObject());
                }

                break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::StyleHasBeenDeleted(HandleStyle hStyle)
{
    if (!hStyle)
        return;

    POSITION       pPosition = m_ObjElements.GetHeadPosition();
    PlanFinObject* pObj;

    // iterate through all objects
    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // if the object points to the deleted style
        if (pObj->GethStyle() == hStyle)
            // Assigns Normal style
            pObj->SethStyle(NormalStyle);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::CheckFontValidity()
{
    POSITION       pPosition = m_ObjElements.GetHeadPosition();
    PlanFinObject* pObj;

    // iterate through all objects
    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // if the object points to an undefined font
        if (pObj->GethFont() >= LONG(m_FontManager.GetCount()))
            // assigns it to no font, therefore to the style
            pObj->SethFont(g_NoFontDefined);
    }
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_DocumentData::GetFormula(const CString& name)
{
    POSITION     pPosition = m_Schema.GetFormulaList(GetCurrentSchema())->GetHeadPosition();
    PSS_Formula* pObj;

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Schema.GetFormulaList(GetCurrentSchema())->GetNext(pPosition);

        if (pObj && pObj->GetObjectName() == name)
            return pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_DocumentData::GetObject(const CString& name)
{
    POSITION       pPosition = m_ObjElements.GetHeadPosition();
    PlanFinObject* pObj;

    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        if (pObj && pObj->GetObjectName() == name)
            return pObj;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_DocumentData::GetSelectedObject(BOOL checkPage)
{
    // get the current page
    const int            page = GetCurrentPage();
          PlanFinObject* pObj;

    // search wich element is selected
    if ((pObj = GetHead()) == NULL)
        return NULL;

    do
    {
        if (checkPage && pObj->GetObjectPage() != page)
            continue;

        if (pObj->IsSelectObject())
            return pObj;
    }
    while ((pObj = GetNext()) != NULL);

    return GetEditedObject(checkPage);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::CheckFormulaObject(PlanFinObject* pOld, PlanFinObject* pNew)
{
    if (!pOld || !pNew)
        return;

    POSITION     pPosition = m_Schema.GetFormulaList(GetCurrentSchema())->GetHeadPosition();
    PSS_Formula* pObj;

    while (pPosition)
    {
        pObj = (PSS_Formula*)m_Schema.GetFormulaList(GetCurrentSchema())->GetNext(pPosition);

        if (pObj && pObj->GetResultObject() == pOld)
            pObj->SetResultObject(pNew);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::ObjectExist(const CString& name)
{
    PlanFinObject* pObjTemp = NULL;
    POSITION       pPosition;

    if ((pPosition = m_ObjElements.GetHeadPosition()) != NULL)
        while (pPosition != NULL)
        {
            pObjTemp = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

            // if the element has the same, then extract the number
            if (pObjTemp->GetObjectName() == name)
                return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::InitializeAllAssociations()
{
    PlanFinObject* pObjTemp  = NULL;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        PSS_PLFNLong* pObjTemp = dynamic_cast<PSS_PLFNLong*>(m_ObjElements.GetNext(pPosition));

        // if the object is a number + has an association
        if (pObjTemp)
            pObjTemp->GetAssociations().InitializeFormulaAssociations(*this);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::CalculateAllFormula(CView* pView, BOOL allPages)
{
    if (!m_Schema.GetFormulaList(GetCurrentSchema()))
        return;

    CDC* pDC = NULL;

    if (pView)
    {
        pDC = pView->GetDC();
        ASSERT(pDC);

        if (::IsWindow(pView->GetSafeHwnd()) && IsWindowVisible(pView->GetSafeHwnd()))
            pView->OnPrepareDC(pDC);
    }

    POSITION     pPosition = m_Schema.GetFormulaList(GetCurrentSchema())->GetHeadPosition();
    PSS_Formula* pFormula;

    while (pPosition)
    {
        pFormula = (PSS_Formula*)m_Schema.GetFormulaList(GetCurrentSchema())->GetNext(pPosition);

        // only if the formula is on the same page, it's necessary to recalculate
        if (allPages || pFormula->GetPage() == GetCurrentPage())
        {
            PSS_PLFNLong* pResultObj = dynamic_cast<PSS_PLFNLong*>(pFormula->GetResultObject());

            // check if the field has an association
            if (pResultObj && pResultObj->GetCurrentAssociation())
            {
                const int associationCount = pResultObj->GetCurrentAssociation()->GetCount();

                // iterate through out the list
                for (register int i = 0; i < pResultObj->GetCurrentAssociation()->GetCount(); ++i)
                {
                    PSS_Formula* pAssociationFormula = pResultObj->GetCurrentAssociation()->GetFormulaAt(i);

                    if (pAssociationFormula)
                        CalculateFormula(pAssociationFormula, pView, pDC);
                }
            }
            else
                // otherwise calculate with the standard formula
                CalculateFormula(pFormula, pView, pDC);
        }
    }

    // generate a WM_PAINT message
    if (pView)
    {
        pView->UpdateWindow();
        VERIFY(pView->ReleaseDC(pDC));
    }

    // start the calc timer
    StartCalcTimer();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::CheckForClearCalcField(CView* pView)
{
    if (m_FlagElapsedTime)
    {
        CTimeSpan elapsedTime = CTime::GetCurrentTime() - m_EndCalculateTime;

        if (elapsedTime.GetSeconds() > 5)
        {
            // clear all flags in the field
            PlanFinObject* pObj;

            // redraw only the that must be refreshed
            CDC* pDC = NULL;

            if (pView)
            {
                pDC = pView->GetDC();
                ASSERT(pDC);

                if (::IsWindow(pView->GetSafeHwnd()) && IsWindowVisible(pView->GetSafeHwnd()))
                    pView->OnPrepareDC(pDC);
            }

            POSITION pPosition = m_ObjElements.GetHeadPosition();

            while (pPosition)
            {
                pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

                if (pObj->HasBeenChanged())
                {
                    pObj->SetHasBeenChanged(FALSE);

                    // redraw the object only if he is positionned on the current page
                    if (pView && pDC && GetCurrentPage() == pObj->GetObjectPage())
                        pObj->DrawObject(pDC, (ZIView*)pView);
                }
            }

            if (pDC)
                VERIFY(pView->ReleaseDC(pDC));
            else
                // if no DC, no update, then update all views
                m_pDocument->UpdateAllViews(NULL);

            ResetCalcTimer();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ChangeCurrentSchema(const CString& name, BOOL notify)
{
    SetCurrentSchema(name);

    // clear the current associations
    ClearCurrentAssociation();

    // change fields for calculation function of the new schema
    ChangeFieldForCalculation();

    if (notify)
    {
        SchemaListHasChanged();
        ASSERT(m_pDocument);
        m_pDocument->UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ClearCurrentAssociation()
{
    PlanFinObject* pObjTemp;

    if ((pObjTemp = GetHead()) != NULL)
        do
        {
            PSS_PLFNLong* pNumber = dynamic_cast<PSS_PLFNLong*>(pObjTemp);

            // is the object a number?
            if (pNumber)
            {
                // clear association icon
                pNumber->SetIconDisplayType();

                // check if the field has an association and clear his association
                if (pNumber->GetCurrentAssociation())
                    pNumber->ClearCurrentAssociation();
            }
        }
        while ((pObjTemp = GetNext()) != NULL);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ChangeFieldForCalculation()
{
    PlanFinObject* pObjTemp;

    // iterate through the list for long field with no current associations
    if ((pObjTemp = GetHead()) != NULL)
        do
        {
            PSS_PLFNLong* pNumber = dynamic_cast<PSS_PLFNLong*>(pObjTemp);

            // if the object is a number
            if (pNumber)
            {
                // clear association icon
                pNumber->SetIconDisplayType();

                // check if the field has no association
                if (!pNumber->GetCurrentAssociation())
                {
                    // if no assocation do tests. Try to find it within the scenario as a result field
                    if (IsCalculatedFieldInSchema(pObjTemp))
                        pNumber->SetCalculatedField();
                    else
                    {
                        pNumber->SetCalculatedField(FALSE);

                        // remove the keep value flag
                        pNumber->SetKeepTheValue(FALSE);
                    }
                }
            }
        }
        while ((pObjTemp = GetNext()) != NULL);

    // iterate through the list for long field with current associations
    if ((pObjTemp = GetHead()) != NULL)
        do
        {
            PSS_PLFNLong* pNumber = dynamic_cast<PSS_PLFNLong*>(pObjTemp);

            // if the object is a number
            if (pNumber)
                // check if the field has an association
                if (pNumber->GetCurrentAssociation())
                {
                    // remove calculate field flag
                    pNumber->SetCalculatedField(FALSE);

                    // remove the keep value flag
                    pNumber->SetKeepTheValue(FALSE);

                    // if association change field in the association
                    ChangeCalculatedFieldInAssociation(pNumber->GetCurrentAssociation());
                }
        }
        while ((pObjTemp = GetNext()) != NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsCalculatedFieldInSchema(PlanFinObject* pObj)
{
    if (!pObj)
        return FALSE;

    POSITION     pPosition = m_Schema.GetFormulaList(GetCurrentSchema())->GetHeadPosition();
    PSS_Formula* pFormula;

    // iterate through formula list and try to find if the object is a result object
    while (pPosition)
    {
        pFormula = (PSS_Formula*)m_Schema.GetFormulaList(GetCurrentSchema())->GetNext(pPosition);

        if (pFormula && pFormula->GetResultObject() == pObj)
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::RefreshCurrentSchema()
{
    // change fields for calculation function of the new schema
    ChangeFieldForCalculation();
    m_pDocument->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ChangeCalculatedFieldInAssociation(PSS_FormulaAssociation* pAssociation)
{
    if (!pAssociation)
        return;

    const register int associationCount = pAssociation->GetCount();

    // iterate through the association list
    for (register int i = 0; i < associationCount; ++i)
    {
        PSS_Formula* pAssociationFormula = pAssociation->GetFormulaAt(i);

        if (pAssociationFormula)
        {
            PSS_PLFNLong* pValue = dynamic_cast<PSS_PLFNLong*>(pAssociationFormula->GetResultObject());

            if (pValue)
            {
                pValue->SetCalculatedField();

                // set association icon.
                pValue->SetIconDisplayType(PSS_PLFNLong::IE_DT_AssociationIcon);
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ReplaceCalculatedFields()
{
    CString label;
    label.LoadString(IDS_AMOUNT_CLASS);

    PlanFinObject* pObjTemp;

    if ((pObjTemp = GetHead()) != NULL)
    {
        do
        {
            PSS_PLFNCalculated* pCalculated = dynamic_cast<PSS_PLFNCalculated*>(pObjTemp);

            // if the object was calculated, convert it in number
            if (pCalculated)
            {
                PlanFinObject* pNewObjTemp = PSS_ObjectUtility::BuildObject(label);

                if (!pNewObjTemp)
                    return;

                (PSS_PLFNLong&)* pNewObjTemp     = pCalculated;
                PSS_PLFNLong*    pNewLongObjTemp = (PSS_PLFNLong*)pNewObjTemp;

                // copy all the information not contained in PlanFinObject
                pNewLongObjTemp->SetHasBeenChanged(FALSE);
                pNewLongObjTemp->SetCalculatedField(TRUE);

                // if this object was stored as a formula list object pointer, change it
                CheckFormulaObject(pObjTemp, pNewObjTemp);

                // delete the old object
                if (!DeleteObject(pObjTemp))
                    return;

                // insert the new one instead
                if (!InsertObject(pNewObjTemp))
                    return;
            }
        }
        while ((pObjTemp = GetNext()) != NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::AssignPredefinedField()
{
    PlanFinObject* pObj = NULL;

    if ((pObj = GetHead()) == NULL)
        return;

    do
    {
        // assign the page field
        if (pObj->GetObjectName() == g_pPredefinedField[g_PredefinedFieldPage])
            SetCurrentPageToObject(pObj);

        // assign the date field
        if (pObj->GetObjectName() == g_pPredefinedField[g_PredefinedFieldDate])
        {
            PSS_PLFNTime* pTime = dynamic_cast<PSS_PLFNTime*>(pObj);

            if (pTime)
                pTime->SetToday();
        }
    }
    while ((pObj = GetNext()) != NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::ChangeObjectType(PlanFinObject* pObj,
                                        const CString& name,
                                        const CString& finalValue,
                                        BOOL           propagate)
{
    if (!pObj)
        return FALSE;

    // if propagate, iterate through the object list and find all similar names
    if (propagate)
    {
        PlanFinObject* pObjTemp;

        if ((pObjTemp = GetHead()) != NULL)
        {
            do
            {
                // if the object contains the same name and is not the initial object, change it
                if (pObjTemp != pObj && pObjTemp->GetObjectName() == pObj->GetObjectName())
                {
                    PlanFinObject* pNewObjTemp = PSS_ObjectUtility::BuildObject(name);

                    if (!pNewObjTemp)
                        return FALSE;

                    (PlanFinObject&)*pNewObjTemp = (PlanFinObject*)pObjTemp;

                    // Initialize certain parameters
                    pNewObjTemp->SetFormatType(E_FT_Standard);

                    // if this object was stored in the formula object list, change it
                    CheckFormulaObject(pObjTemp, pNewObjTemp);
                    pNewObjTemp->ConvertFormattedObject(finalValue);

                    // delete the old object
                    if (!DeleteObject(pObjTemp))
                        return FALSE;

                    // insert the new one instead
                    if (!InsertObject(pNewObjTemp))
                        return FALSE;
                }
            }
            while ((pObjTemp = GetNext()) != NULL);
        }
    }

    PlanFinObject* pNewObj = PSS_ObjectUtility::BuildObject(name);

    if (!pNewObj)
        return FALSE;

    (PlanFinObject&)*pNewObj = (PlanFinObject*)pObj;

    // initialize some parameters
    pNewObj->SetFormatType(E_FT_Standard);

    // if this object was stored in the formula object list, change it
    CheckFormulaObject(pObj, pNewObj);
    pNewObj->ConvertFormattedObject(finalValue);

    // delete the old object
    if (!DeleteObject(pObj))
        return FALSE;

    // insert the new one instead
    return InsertObject(pNewObj);
}
//---------------------------------------------------------------------------
CString PSS_DocumentData::BuildAutomaticNewName(const CString& prefix)
{
          POSITION       pPosition;
          char           name[100];
          long           counter      = -1L;
          PlanFinObject* pObjTemp     = NULL;
    const std::size_t    prefixLength = prefix.GetLength();

    if ((pPosition = m_ObjElements.GetHeadPosition()) != NULL)
        while (pPosition)
        {
            pObjTemp             = (PlanFinObject*)m_ObjElements.GetNext(pPosition);
            const char* pObjName = pObjTemp->GetObjectName();

            // if the same element, extract the number
            if (!std::strncmp(pObjName, prefix, prefixLength))
                counter = __max(std::atol(pObjName + prefixLength), counter);
        }

    std::sprintf(name, _T("%s%ld"), (const char*)prefix, counter + 1L);

    return name;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::InsertObject(PlanFinObject*       pObj,
                                    PSS_FieldRepository* pFieldRepository,
                                    BOOL                 insertInGlobalRepository,
                                    BOOL                 refresh)
{
    if (!pObj)
        return FALSE;

    // insert elements in page order
    POSITION pPosition, pElementPosition;

    if ((pElementPosition = pPosition = m_ObjElements.GetHeadPosition()) == NULL)
    {
        m_ObjElements.AddTail(pObj);
        return TRUE;
    }

    PlanFinObject* pObjTemp = NULL;

    // sort the element by page too, but by Y and X coordinates. This option is used for auto-edit,
    // to go to the next editable field
    while (pPosition)
    {
        // save the current temp object position
        pElementPosition = pPosition;
        pObjTemp         = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        if (pObj->GetObjectPage() == pObjTemp->GetObjectPage())
        {
            if (pObj->GetClientRect().bottom == pObjTemp->GetClientRect().bottom)
            {
                if (pObj->GetClientRect().left < pObjTemp->GetClientRect().left)
                    break;
            }
            else
            if (pObj->GetClientRect().bottom < pObjTemp->GetClientRect().bottom)
                break;
        }
        else
        if (pObj->GetObjectPage() < pObjTemp->GetObjectPage())
            break;
    }

    if (!pPosition && !(pObj->GetObjectPage() < pObjTemp->GetObjectPage()))
        m_ObjElements.AddTail(pObj);
    else
        m_ObjElements.InsertBefore(pElementPosition, pObj);

    // rebuild automatic tab order
    AutomaticRebuildTabOrder();

    // test multi-column field
    CheckMultiColumnMemberField(pObj);

    // if should refresh the form
    if (refresh && m_pDocument)
        m_pDocument->UpdateAllViews(NULL);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::InsertObjectAtHead(PlanFinObject*       pObj,
                                          PSS_FieldRepository* pFieldRepository,
                                          BOOL                 insertInGlobalRepository,
                                          BOOL                 refresh)
{
    if (!pObj)
        return FALSE;

    // insert elements in page order
    POSITION pPosition, pElementPosition;

    if ((pElementPosition = pPosition = m_ObjElements.GetHeadPosition()) == NULL)
    {
        m_ObjElements.AddHead(pObj);
        return TRUE;
    }

    PlanFinObject* pObjTemp = NULL;

    // sort the element by page too, but by Y and X coordinates. This option is used for auto-edit,
    // to go to the next editable field
    while (pPosition)
    {
        // save the position of the current element objTemp
        pElementPosition = pPosition;
        pObjTemp         = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        if (pObj->GetObjectPage() == pObjTemp->GetObjectPage())
        {
            if (pObj->GetClientRect().bottom == pObjTemp->GetClientRect().bottom)
            {
                if (pObj->GetClientRect().left < pObjTemp->GetClientRect().left)
                    break;
            }
            else
            if (pObj->GetClientRect().bottom < pObjTemp->GetClientRect().bottom)
                break;
        }
        else
        if (pObj->GetObjectPage() < pObjTemp->GetObjectPage())
            break;
    }

    if (!pPosition && !(pObj->GetObjectPage() < pObjTemp->GetObjectPage()))
        m_ObjElements.AddHead(pObj);
    else
        m_ObjElements.InsertBefore(pElementPosition, pObj);

    // rebuild automatic tab order
    AutomaticRebuildTabOrder();

    // test multi-column field
    CheckMultiColumnMemberField(pObj);

    // if should refresh the form
    if (refresh && m_pDocument)
        m_pDocument->UpdateAllViews(NULL);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::DeleteObject(PlanFinObject* pObj, BOOL deleteFromMemory, BOOL refresh)
{
    POSITION pPosition = m_ObjElements.Find(pObj);

    // delete the object
    if (pPosition)
    {
        if (deleteFromMemory)
            delete pObj;

        m_ObjElements.RemoveAt(pPosition);

        // if should refresh the form
        if (refresh && m_pDocument)
            m_pDocument->UpdateAllViews(NULL);

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::MoveObjectInOrder(PlanFinObject* pObj)
{
    // delete the object from the list only, not from the memory, and reinsert it at ordered position
    if (DeleteObject(pObj, FALSE))
        return InsertObject(pObj);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::AssignObjectValue(const CString& name,
                                         const CString& value,
                                         int            page,
                                         int            propagationMode,
                                         BOOL           emptyWhenZero)
{
    if (propagationMode == g_LocateAllDocuments || propagationMode == g_LocateAllDocumentsEmptyOnly)
        return FALSE;

    PlanFinObject* pObj;

    // locate the object
    if ((pObj = GetHead()) != NULL)
    {
        do
        {
            // if the same object name
            if (pObj->GetObjectName() == name)
            {
                // search for propagation mode function
                switch (propagationMode)
                {
                    case g_LocatePageOnlyEmptyOnly:
                        // if after the concerned page, end
                        if (pObj->GetObjectPage() > page)
                            return TRUE;

                        // if the object is not empty, continue
                        if (!pObj->IsEmpty())
                            continue;

                        // all conditions are filled, assign the value
                        break;

                    case g_LocateForwardPageEmptyOnly:
                        // if before the page, continue
                        if (pObj->GetObjectPage() < page)
                            continue;

                        // if the object is not empty, continue
                        if (!pObj->IsEmpty())
                            continue;

                        // all conditions are filled, assign the value
                        break;

                    case g_LocateAllPagesEmptyOnly:
                        // if the object is not empty, continue
                        if (!pObj->IsEmpty())
                            continue;

                        // all conditions are filled, assign the value
                        break;

                    case g_LocatePageOnly:
                        // if after the concerned page, end it is finished
                        if (pObj->GetObjectPage() > page)
                            return TRUE;

                        // all conditions are filled, assign the value
                        break;

                    case g_LocateForwardPage:
                        // if before the page, continue
                        if (pObj->GetObjectPage() < page)
                            continue;

                        // all conditions are filled, assign the value
                        break;

                    case g_LocateAllPages:
                        // all conditions are filled, assign the value
                        break;

                    default:
                        return FALSE;
                }

                // convert the object without changing its format
                if (pObj->ConvertFormattedObject(value, FALSE, emptyWhenZero))
                {
                    // send message to notify the change for this object
                    pObj->SetHasBeenChanged(TRUE);
                    GetDocument()->SetModifiedFlag(TRUE);
                }
            }
        }
        while ((pObj = GetNext()) != NULL);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetCurrentPageToObject(PlanFinObject* pObj)
{
    if (!pObj)
        return;

    pObj->SetValue(double(pObj->GetObjectPage()));
}
//---------------------------------------------------------------------------
void PSS_DocumentData::DeleteAllObjects()
{
    while (!m_ObjElements.IsEmpty())
    {
        delete m_ObjElements.GetHead();
        m_ObjElements.RemoveHead();
    }
}
//---------------------------------------------------------------------------
int PSS_DocumentData::CountAndSetPages()
{
    PlanFinObject* pObj;

    // get the page number used to display the object on the right page.
    // The test here is to assign the greater number of pages
    if ((pObj = GetHead()) == NULL)
        return 0;

    SetMaxPage(0);

    do
    {
        SetMaxPage(__max(pObj->GetObjectPage(), GetMaxPage()));
    }
    while ((pObj = GetNext()) != NULL);

    TRACE1(_T(" Max Pages %d"), GetMaxPage());

    return GetMaxPage();
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_DocumentData::CloneSelectedObject()
{
    PlanFinObject* pObj = GetSelectedObject();

    if (!pObj)
        return NULL;

    return pObj->Clone();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::RebuildAllAutomaticNumbered()
{
    int levelArray[20];
    std::memset(&levelArray, 0, sizeof(levelArray));

    PlanFinObject* pObj;

    if ((pObj = GetHead()) != NULL)
    {
        do
        {
            PSS_PLFNAutoNumbered* pAutoNum = dynamic_cast<PSS_PLFNAutoNumbered*>(pObj);

            // search all auto numbered objects
            if (pAutoNum)
                // count only if the element is auto numbered
                if (pAutoNum->GetAutoCalculate())
                {
                    levelArray[pAutoNum->GetLevel()] = levelArray[pAutoNum->GetLevel()] + 1;

                    CString level;
                    char*   pBuffer = NULL;

                    try
                    {
                        pBuffer = new char[18];
                        level   = itoa(levelArray[0], pBuffer, 10);
                    }
                    catch (...)
                    {
                        if (pBuffer)
                            delete[] pBuffer;

                        throw;
                    }

                    if (pBuffer)
                        delete[] pBuffer;

                          CString text       = level + '0';
                    const int     levelCount = pAutoNum->GetLevel();

                    for (int i = 0; i < levelCount; ++i)
                    {
                        level.Empty();
                        pBuffer = NULL;

                        try
                        {
                            pBuffer = new char[18];
                            level   = itoa(levelArray[i + 1], pBuffer, 10);
                        }
                        catch (...)
                        {
                            if (pBuffer)
                                delete[] pBuffer;

                            throw;
                        }

                        text += '.';
                        text += level + '0';
                    }

                    pAutoNum->SetStringTextLevel(text);
                }
        }
        while ((pObj = GetNext()) != NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SetCurrentStyle(const CString& name)
{
    PlanFinObject* pObjTemp = GetSelectedObject();

    if (pObjTemp)
    {
        // when assign new style, clear a specific font assigned
        pObjTemp->SethStyle(m_pDocument->GetStyleManager().FindStyle(name));

        // remove the angle
        pObjTemp->SetiAngle(0, m_pDocument);

        // notify object about change in position and size
        pObjTemp->SizePositionHasChanged();
        m_pDocument->UpdateAllViews(NULL);
        m_pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::IsCalculatedFieldInAssociation(PlanFinObject* pObj)
{
    if (!pObj)
        return FALSE;

    PSS_PLFNLong* pLong = dynamic_cast<PSS_PLFNLong*>(pObj);

    if (pLong && pLong->GetCurrentAssociation()->FindFormula(pLong->GetObjectName()))
        return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::InitializeAllObjectPointers()
{
    m_Schema.InitializeSchemaObjectPointer(*this);
    InitializeAllAssociations();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::PropagateFieldValue(PlanFinObject* pObj)
{
    if (!m_pDocument)
        return;

    if (!pObj)
        return;

    if (pObj->GetObjectName().IsEmpty())
        return;

    ZIView* pView = m_pDocument->GetMainView();
    ASSERT(pView);

    CString fieldName;
    CString member;
    int     rowValue = -1;

    // if is member of multi-colum field, extract the name of the field and the member name.
    // Extract also the value row number
    if (pObj->IsMemberOfMultiColumn())
    {
        ZBTokenizer tokenizer('.');

        // get field name
        fieldName = tokenizer.GetFirstToken(pObj->GetObjectName());

        // get member name
        member = tokenizer.GetNextToken();

        // get row value
        rowValue = ((ZBFieldColumn*)pObj->GetpColumn())->GetValueRow(pObj->GetUnformattedObject());
    }

    PlanFinObject* pTempObj;
    CDC*           pDC = pView->GetDC();

    try
    {
        if (pView->IsWindowVisible())
        {
            ASSERT(pDC);
            pView->OnPrepareDC(pDC);
        }

        // get the current page
        const int page = GetCurrentPage();

        // invalidate the current object
        if (pView->IsWindowVisible())
            pObj->InvalidateObjectRect(pDC, pView);

        if ((pTempObj = GetHead()) == NULL)
        {
            if (pView->IsWindowVisible())
                VERIFY(pView->ReleaseDC(pDC));

            return;
        }

        do
        {
            // find matching object name in the list
            if (pTempObj != pObj)
                if (pTempObj->GetObjectName() == pObj->GetObjectName())
                {
                    // copy its content
                    if (pTempObj->ConvertFormattedObject(pObj->GetUnformattedObject(), FALSE))
                        // if the field contents changed, refresh it
                        if (page == pTempObj->GetObjectPage())
                            if (pView->IsWindowVisible())
                                pTempObj->InvalidateObjectRect(pDC, pView);
                }
                else
                {
                    // check for other multi-column field
                    if (pTempObj->IsMemberOfMultiColumn() && rowValue != -1)
                    {
                        ZBTokenizer tokenizer('.');
                        const CString     currentFieldName = tokenizer.GetFirstToken(pTempObj->GetObjectName());

                        // same field name?
                        if (fieldName == currentFieldName)
                        {
                            const CString currentFieldMember = tokenizer.GetNextToken();

                            // locate the multicolumn fieldname
                            PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(GetObject(currentFieldName));

                            // no object or not a multi-column field, do nothing
                            if (pMultiColumn)
                            {
                                // locate the column name
                                ZBFieldColumn* pColumn = pMultiColumn->FindColumn(currentFieldMember);

                                // if the column was found, copy its content
                                if (pColumn && pTempObj->ConvertFormattedObject(pColumn->GetValueAt(rowValue), FALSE))
                                    // if the field contents changed, refresh it
                                    if (page == pTempObj->GetObjectPage())
                                        if (pView->IsWindowVisible())
                                            pTempObj->InvalidateObjectRect(pDC, pView);
                            }
                        }
                    }
                }
        }
        while ((pTempObj = GetNext()) != NULL);
    }
    catch (...)
    {
        if (pView->IsWindowVisible())
            VERIFY(pView->ReleaseDC(pDC));

        throw;
    }

    if (pView->IsWindowVisible())
        VERIFY(pView->ReleaseDC(pDC));

    m_pDocument->FieldHasBeenModified();

    // Generate a WM_PAINT message
    pView->UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_DocumentData::AssignNewStyle(HandleStyle hOldStyle, HandleStyle hNewStyle)
{
    if (!hOldStyle || !hNewStyle)
        return;

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    // iterate through all objects    
    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // if the object points to the deleted style
        if (pObj->GethStyle() == hOldStyle)
            // assign normal style
            pObj->SethStyle(hNewStyle);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CreateBufferFromFile(const CString& fileName)
{
    // if buffer already exists, clear it before
    if (m_pFileBuffer)
        ClearFileBuffer();

    m_pFileBuffer = new PSS_FileBuffer;

    if (!m_pFileBuffer)
        return FALSE;

    m_Stamp.SetDocumentDataType(PSS_Stamp::IE_DT_Binary);
    m_Stamp.SetTemplate(fileName);

    return m_pFileBuffer->CreateBufferFromFile(fileName);
}
//---------------------------------------------------------------------------
CString PSS_DocumentData::CreateFileFromBuffer(const CString& fileName)
{
    if (m_pFileBuffer)
        return m_pFileBuffer->CreateFileFromBuffer(fileName);

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_DocumentData::CreateTemporaryFileFromBuffer()
{
    if (IsBinaryDataValid())
    {
        if (m_FileBufferTemporaryFile.IsEmpty())
        {
            // create the temporary file and save it
            m_FileBufferTemporaryFile = m_pFileBuffer->CreateTemporaryFileFromBuffer();
            GetFileLauncher().Initialize(m_FileBufferTemporaryFile);
        }

        return m_FileBufferTemporaryFile;
    }

    // no file buffer
    m_FileBufferTemporaryFile.Empty();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_DocumentData::ClearFileBuffer()
{
    if (!m_pFileBuffer)
        return;

    delete m_pFileBuffer;
    m_pFileBuffer = NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::DeleteTemporaryFile()
{
    if (m_FileBufferTemporaryFile.IsEmpty())
        return TRUE;

    if (!::DeleteFile(m_FileBufferTemporaryFile))
        return FALSE;

    m_FileBufferTemporaryFile.Empty();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDraw(CDC*    pDC,
                              ZIView* pView,
                              BOOL    drawCalculatedSymbol,
                              BOOL    drawHiddenObject,
                              BOOL    drawBoundRectObject,
                              BOOL    drawCalculatedRefObject,
                              BOOL    drawTabOrder)
{
    if (IsFormData())
        OnDrawForms(pDC,
                    pView,
                    drawCalculatedSymbol,
                    drawHiddenObject,
                    drawBoundRectObject,
                    drawCalculatedRefObject,
                    drawTabOrder);
    else
    if (IsExternalFormData())
        OnDrawExternalForms(pDC,
                            pView,
                            drawCalculatedSymbol,
                            drawHiddenObject,
                            drawBoundRectObject,
                            drawCalculatedRefObject,
                            drawTabOrder);
    else
    if (IsBinaryDataValid())
        OnDrawBinary(pDC, pView);
    else
    if (IsExternalBinaryData())
        OnDrawExternalBinary(pDC, pView);
    else
    if (IsURLData())
        OnDrawURL(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SwitchTabOrder(PlanFinObject* pObject, double tabOrder)
{
    if (!pObject)
        return;

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)(m_ObjElements).GetNext(pPosition);

        // if we found the tab order that we would like to switch
        if (pObj->GetTabOrder() == tabOrder)
        {
            // get the found object tab order
            pObj->SetTabOrder(pObject->GetTabOrder());
            break;
        }
    }

    // set the object tab order
    pObject->SetTabOrder(tabOrder);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::AutomaticRebuildTabOrder()
{
    // evaluate the last tab order
    EvaluateLastTabOrder();

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)(m_ObjElements).GetNext(pPosition);

        // found a tab order equal to zero?
        if (!pObj->GetTabOrder())
            // assign a tab order new value by incrementing the last tab order
            pObj->SetTabOrder(++m_LastTabOrder);
    }
}
//---------------------------------------------------------------------------
double PSS_DocumentData::EvaluateLastTabOrder()
{
    // initialize last tab order
    m_LastTabOrder = 0;

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)(m_ObjElements).GetNext(pPosition);

        // if we found a tab order equal to zero
        m_LastTabOrder = __max(pObj->GetTabOrder(), m_LastTabOrder);
    }

    return m_LastTabOrder;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::AssignMultiColumnMemberFields()
{
    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)(m_ObjElements).GetNext(pPosition);
        CheckMultiColumnMemberField(pObj);
    }
}
//---------------------------------------------------------------------------
bool PSS_DocumentData::AddFieldNameInObectArray(const CString& fieldname)
{
    if (!FieldNameExistInObjectArray(fieldname))
        m_FieldNameArray.Add(fieldname);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DocumentData::BuildObjectFieldNameArray()
{
    // free the object field name array
    m_FieldNameArray.RemoveAll();

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)(m_ObjElements).GetNext(pPosition);

        if (pObj && !FieldNameExistInObjectArray(pObj->GetObjectName()))
            m_FieldNameArray.Add(pObj->GetObjectName());

        PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(pObj);

        if (pMultiColumn)
        {
            const std::size_t columnCount = pMultiColumn->GetColumnCount();

            // add member field name
            for (std::size_t i = 0; i < columnCount; ++i)
            {
                CString        fullName = pObj->GetObjectName() + _T(".");
                ZBFieldColumn* pColumn  = pMultiColumn->GetColumnAt(i);

                if (pColumn)
                {
                    fullName += pColumn->GetHeaderName();

                    if (!FieldNameExistInObjectArray(fullName))
                        m_FieldNameArray.Add(fullName);
                }
            }
        }
    }

    return m_FieldNameArray.GetSize() > 0;
}
//---------------------------------------------------------------------------
int PSS_DocumentData::SerializeStampRead(CArchive& ar, PSS_Stamp& stamp)
{
    WORD archiveStamp = 0;

    TRY
    {
        ar >> archiveStamp;
    }
    CATCH (CArchiveException, e)
    {
        return 0;
    }
    END_CATCH

    // check if the stamp has been set for next generation of files
    if (archiveStamp == 0xFFFF)
        ar >> stamp;

    return archiveStamp;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SerializeRead(CArchive& ar)
{
    WORD    stamp            = 0xFFFF;
    bool    isInRecoveryMode = false;
    CString schemaName;

    // read informations. Test if the stamp has been set for next generation of files
    if ((stamp = SerializeStampRead(ar, m_Stamp)) == 0xFFFF)
        ar >> schemaName;
    else
        // put the default schema name
        schemaName = g_OriginalSchema;

    SetCurrentSchema(schemaName);

    if (m_Stamp.GetInternalVersion() >= 14 && m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_Binary)
        ar >> m_pFileBuffer;
    else
    {
        if (m_Stamp.GetInternalVersion() >= 4)
        {
            // serialize the font manager
            m_FontManager.Serialize(ar);

            // serialize the style manager
            m_StyleManager.Serialize(ar);
        }

        if (m_Stamp.GetDocumentDataType() != PSS_Stamp::IE_DT_Binary)
        {
            TRY
            {
                // serialize the list
                m_ObjElements.Serialize(ar);
            }
            CATCH (CArchiveException, e)
            {
                if (stamp == 0xFFFF)
                {
                    PSS_MsgBox mBox;

                    if (mBox.Show(IDS_FILECORRUPTED_RECOVER, MB_YESNO) == IDNO)
                        THROW_LAST();

                    // otherwise, try to keep existing information
                    isInRecoveryMode = true;
                }
            }
            END_CATCH

            TRY
            {
                // do it if not in recovery mode
                if (!isInRecoveryMode)
                {
                    if (stamp == 0xFFFF)
                        m_Schema.Serialize(ar);
                    else
                        m_Schema.ReadSerializeOldFormat(ar);
                }
                else
                    // if in recovery, just create the standard schema
                    m_Schema.CreateStandardEmptySchema();

                // after reading all elements, do not forget to initialize the object pointers
                InitializeAllObjectPointers();
            }
            CATCH (CArchiveException, e)
            {
                if (stamp == 0xFFFF)
                {
                    PSS_MsgBox mBox;

                    if (mBox.Show(IDS_FILECORRUPTED_RECOVER, MB_YESNO) == IDNO)
                        THROW_LAST();

                    // otherwise, try to keep existing information
                    isInRecoveryMode = true;
                }
            }
            END_CATCH
        }

        // no binary file data pointer
        m_pFileBuffer = NULL;
    }

    // do it if not in recovery mode
    if (!isInRecoveryMode)
    {
        WORD value;
        ar >> value;
        m_IsVisible = BOOL(value);
    }
    else
        m_IsVisible = TRUE;

    // signal the user to attach the formulary to a new template
    if (m_Stamp.GetTemplate().IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_TEMPLATEPROBLEM, MB_OK);
    }

    // check now that the object list is coherent
    if (!CheckObjectList())
        AfxThrowArchiveException(CArchiveException::generic);

    // if switched to recovery mode, show a warning
    if (isInRecoveryMode == true)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FILECORRUPTED_MISSINGINFO, MB_OK);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SerializeStampWrite(CArchive& ar, PSS_Stamp& stamp)
{
    // set the document type
    stamp.SetDocumentFileType(PSS_Stamp::IE_FT_FormDocument);
    stamp.SetInternalVersion(g_VersionFile);

    const WORD archiveStamp = 0xFFFF;

    // put the stamp for differentiate the new generation of files
    ar << archiveStamp;
    ar << stamp;
}
//---------------------------------------------------------------------------
void PSS_DocumentData::SerializeWrite(CArchive& ar)
{
    // write informations
    SerializeStampWrite(ar, m_Stamp);

    // save the current schema
    ar << GetCurrentSchema();

    if (m_Stamp.GetDocumentDataType() == PSS_Stamp::IE_DT_Binary)
        // the file buffer pointer
        ar << m_pFileBuffer;
    else
    {
        // serialize the font manager
        m_FontManager.Serialize(ar);

        // serialize the style manager
        m_StyleManager.Serialize(ar);

        TRY
        {
            // serialize the list
            m_ObjElements.Serialize(ar);
        }
        CATCH (CArchiveException, e)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILECORRUPTED, MB_OK);
            THROW_LAST();
        }
        END_CATCH

        TRY
        {
            m_Schema.Serialize(ar);
        }
        CATCH (CArchiveException, e)
        {
            // in write mode no chance, file corruption
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILECORRUPTED);
            THROW_LAST();
        }
        END_CATCH
    }

    ar << WORD(m_IsVisible);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        AutomaticRebuildTabOrder();
        SerializeWrite(ar);
    }
    else
    {
        SerializeRead(ar);
        AutomaticRebuildTabOrder();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CalculateFormula(PSS_Formula* pFormula, CWnd* pWnd, CDC* pDC)
{
    if (!pFormula)
        return FALSE;

    PSS_FormulaParser parser;
    PSS_PLFNLong*     pField = dynamic_cast<PSS_PLFNLong*>(pFormula->GetResultObject());

    // check if the field is a PLFNLong. The only way to calculate is on calculated fields. Because
    // the user can change the type, it is necessary to test if the keep value is set. If it is set,
    // do not calculate
    if (!pField || pField->KeepTheValue())
        return(FALSE);

    // get the previous value to compare with the new one. If the value has changed, then notify the
    // controler about the change of the field
    const double previousValue = pField->GetValue();
          double newValue      = parser.StringParser((const char*)pFormula->GetExtractedFormula(), &m_ObjElements);

    // to notify the view that on field change, pass the adress of the object, then the routine that
    // proceed the message can know wich object has changed
    if (pField->GetRoundedValue() && pField->IsRounded())
        // function floor first integer less than, function ceil first integer greater than
        newValue = std::ceil(newValue / pField->GetRoundedValue()) * pField->GetRoundedValue();

    if (newValue != pField->GetValue())
    {
        pField->SetValue(newValue);
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(pField));

        if (pWnd && pDC && GetCurrentPage() == pField->GetObjectPage())
            pField->InvalidateObjectRect(pDC, pWnd);

        return(TRUE);
    }

    return(FALSE);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawBinary(CDC* pDC, ZIView* pView)
{
    if (!pDC)
        return;

    CRect rect(20, 20, 500, 1000);
    pDC->DrawText(m_BinaryDrawMessage, &rect, DT_WORDBREAK | DT_LEFT);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawExternalBinary(CDC* pDC, ZIView* pView)
{
    if (!pDC)
        return;

    CRect rect(20, 20, 500, 1000);
    pDC->DrawText(m_BinaryDrawMessage, &rect, DT_WORDBREAK | DT_LEFT);
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawBackgroundPicture(CDC* pDC, ZIView* pView, int page)
{
    if (!pDC)
        return;

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject *)m_ObjElements.GetNext(pPosition);

        if (page == pObj->GetObjectPage() && ISA(pObj, PSS_PLFNBackImage))
            if (pObj->GetbIsVisible() || m_pDocument->ShouldShowHiddenField())
                if (pDC->IsPrinting())
                {
                    if (pObj->GetbMustBePrinted() && pObj->GetbIsVisible())
                        pObj->DrawObject(pDC, pView);
                }
                else
                    pObj->DrawObject(pDC, pView);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawForms(CDC*    pDC,
                                   ZIView* pView,
                                   BOOL    drawCalculatedSymbol,
                                   BOOL    drawHiddenObject,
                                   BOOL    drawBoundRectObject,
                                   BOOL    drawCalculatedRefObject,
                                   BOOL    drawTabOrder)
{
    if (!pDC)
        return;

    // get the current page
    const int page = m_pDocument->GetCurrentPage();

    // draw background picture
    OnDrawBackgroundPicture(pDC, pView, page);

    PlanFinObject* pObj;

    // optimisation first step, call directly the list functions
    POSITION pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // show object on the right page, and if visible in the viewport, and don't draw background images
        if (pObj && page == pObj->GetObjectPage() && !ISA(pObj, PSS_PLFNBackImage))
            if (pObj->GetbIsVisible() || m_pDocument->ShouldShowHiddenField() || drawHiddenObject)
                if (pDC->IsPrinting())
                {
                    // when printing test if the object is empty, and if must print empty line, and if the
                    // object must be printed
                    if (( pObj->GetbMustBePrinted() && pObj->GetbIsVisible()) &&
                        (!pObj->IsEmpty() || m_pDocument->ShouldPrintLine()))
                        pObj->DrawObject(pDC, pView);
                }
                else
                {
                    pObj->DrawObject(pDC, pView);

                    if (drawCalculatedSymbol)
                        pObj->DrawCalculatedSymbol(pDC);

                    if (!pObj->GetbMustBePrinted())
                        pObj->DrawHiddenOnPrintSymbol(pDC);

                    if (drawHiddenObject && !pObj->GetbIsVisible())
                        pObj->DrawHiddenSymbol(pDC);

                    if (drawBoundRectObject)
                        pObj->DrawObjectRectangle(pDC);

                    if (drawTabOrder)
                        pObj->DrawTabOrder(pDC);

                    if (pObj->GetNotesPointer())
                        pObj->DrawNoteSymbol(pDC);
                }
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawExternalForms(CDC*    pDC,
                                           ZIView* pView,
                                           BOOL    drawCalculatedSymbol,
                                           BOOL    drawHiddenObject,
                                           BOOL    drawBoundRectObject,
                                           BOOL    drawCalculatedRefObject,
                                           BOOL    drawTabOrder)
{}
//---------------------------------------------------------------------------
void PSS_DocumentData::OnDrawURL(CDC* pDC, ZIView* pView)
{
    if (!pDC)
        return;

    CRect rect(20, 20, 500, 1000);
    pDC->DrawText(m_BinaryDrawMessage, &rect, DT_WORDBREAK | DT_LEFT);
}
//---------------------------------------------------------------------------
bool PSS_DocumentData::FieldNameExistInObjectArray(const CString& fieldName)
{
    const std::size_t fieldNameCount = m_FieldNameArray.GetSize();

    for (std::size_t i = 0; i < fieldNameCount; ++i)
        if (fieldName == m_FieldNameArray.GetAt(i))
            return true;

    return false;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::DeletePageObjects(int page, BOOL redistribute)
{
    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // check the object page
        if (pObj->GetObjectPage() == page)
            if (!DeleteObject(pObj))
                return FALSE;
    }

    if (redistribute)
    {
        // check if it is necessary to redistribute the object's pages
        if (page < GetMaxPage())
        {
            pPosition = m_ObjElements.GetTailPosition();

            while (pPosition)
            {
                pObj = (PlanFinObject*)m_ObjElements.GetPrev(pPosition);

                // check if the object's page is before the deleted page
                if (pObj->GetObjectPage() < page)
                    break;

                pObj->SetObjectPage(pObj->GetObjectPage() - 1);
            }
        }

        // reassign the predefined field like pages
        AssignPredefinedField();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CopyPageObjects(PSS_DocumentData* pDocumentDst, int page)
{
    if (!pDocumentDst)
        return FALSE;

    PlanFinObject* pObj;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj = (PlanFinObject*)m_ObjElements.GetNext(pPosition);

        // check the object page
        if (pObj->GetObjectPage() == page)
        {
            PlanFinObject* pNewObjTemp = pObj->Clone();
            ASSERT(pNewObjTemp);

            // insert the object in the destination document
            if (!pDocumentDst->InsertObject(pNewObjTemp))
                return FALSE;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentData::CheckObjectList()
{
    PlanFinObject* pObj;
    PlanFinObject* pSimilarObject;
    POSITION       pStartPosition;
    POSITION       pSavedPosition;
    POSITION       pPosition = m_ObjElements.GetHeadPosition();

    while (pPosition)
    {
        pObj           = (PlanFinObject*)m_ObjElements.GetNext(pPosition);
        pStartPosition = pPosition;

        // from this position, check if another object has the same adress
        while (pStartPosition)
        {
            // save the previous position for further deletion
            pSavedPosition = pStartPosition;
            pSimilarObject = (PlanFinObject*)m_ObjElements.GetNext(pStartPosition);

            if (pSimilarObject == pObj)
            {
                // found a same reference in the list?
                CString prompt;
                AfxFormatString1(prompt, IDS_OBJECTSAMEREFERENCE, pObj->GetObjectName());

                PSS_MsgBox mBox;

                if (mBox.Show(prompt, MB_YESNO) == IDNO)
                    return FALSE;

                m_ObjElements.RemoveAt(pSavedPosition);
            }
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
