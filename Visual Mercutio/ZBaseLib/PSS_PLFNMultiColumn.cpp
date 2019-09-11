/****************************************************************************
 * ==> PSS_PLFNMultiColumn -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan multi-columns object             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNMultiColumn.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNMultiColumn, PSS_PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNMultiColumn
//---------------------------------------------------------------------------
PSS_PLFNMultiColumn::PSS_PLFNMultiColumn() :
    PSS_PlanFinObject(),
    m_ShowHeader(TRUE)
{
    // by default, the multi-column field is not visible
    SetIsVisible(FALSE);
}
//---------------------------------------------------------------------------
PSS_PLFNMultiColumn::PSS_PLFNMultiColumn(const PSS_PLFNMultiColumn& other) :
    PSS_PlanFinObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNMultiColumn::~PSS_PLFNMultiColumn()
{}
//---------------------------------------------------------------------------
const PSS_PLFNMultiColumn& PSS_PLFNMultiColumn::operator = (const PSS_PLFNMultiColumn& other)
{
    PSS_PlanFinObject::operator = ((inherited&)other);
    m_MultiColumnManager = other.m_MultiColumnManager;
    m_ShowHeader         = other.m_ShowHeader;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNMultiColumn& PSS_PLFNMultiColumn::operator = (const PSS_PLFNMultiColumn* pOther)
{
    PSS_PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        // reset the content to default
        m_ShowHeader = FALSE;
        SetIsVisible(FALSE);
    }
    else
        *this = *pOther;

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNMultiColumn::Clone() const
{
    std::unique_ptr<PSS_PLFNMultiColumn> pObject(new PSS_PLFNMultiColumn(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNMultiColumn*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(GetColor(pView));

    // before drawing the object, format it, but it's not necessary in this version
    pDC->SetTextAlign(0);

    pDC->SelectObject(pOldFont);

    // base class draw object
    PSS_PlanFinObject::DrawObject(pDC, pView);
    PSS_PlanFinObject::DrawObjectRectangle(pDC);
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::Serialize(CArchive& ar)
{
    PSS_PlanFinObject::Serialize(ar);

    m_MultiColumnManager.Serialize(ar);

    if (ar.IsStoring())
        // write the elements
        ar << WORD(m_ShowHeader);
    else
    {
        // read the elements
        WORD value;
        ar >> value;
        m_ShowHeader = BOOL(value);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNMultiColumn::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNMultiColumn::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
