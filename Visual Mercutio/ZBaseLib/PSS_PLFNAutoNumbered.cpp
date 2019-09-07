/****************************************************************************
 * ==> PSS_PLFNAutoNumbered ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an financial plan auto-numbered object            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNAutoNumbered.h"

// processsoft
#include "ZDDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNAutoNumbered, PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNAutoNumbered
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::PSS_PLFNAutoNumbered() :
    PlanFinObject(),
    m_pObject(NULL),
    m_TextOffset(20),
    m_SectionNumber(0),
    m_Level(0),
    m_AutoCalculate(TRUE)
{}
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::PSS_PLFNAutoNumbered(const PSS_PLFNAutoNumbered& other) :
    PlanFinObject(),
    m_pObject(NULL),
    m_TextOffset(20),
    m_SectionNumber(0),
    m_Level(0),
    m_AutoCalculate(TRUE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNAutoNumbered::~PSS_PLFNAutoNumbered()
{
    if (m_pObject)
        delete m_pObject;
}
//---------------------------------------------------------------------------
const PSS_PLFNAutoNumbered& PSS_PLFNAutoNumbered::operator = (const PSS_PLFNAutoNumbered& other)
{
    PlanFinObject::operator = ((inherited&)other);
    m_TextLevel     = other.m_TextLevel;
    m_pObject       = other.m_pObject->Clone();
    m_TextOffset    = other.m_TextOffset;
    m_SectionNumber = other.m_SectionNumber;
    m_Level         = other.m_Level;
    m_AutoCalculate = other.m_AutoCalculate;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNAutoNumbered& PSS_PLFNAutoNumbered::operator = (const PSS_PLFNAutoNumbered* pOther)
{
    PlanFinObject::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_pObject       = NULL;
        m_TextOffset    = 20;
        m_SectionNumber = 0;
        m_Level         = 0;
        m_AutoCalculate = TRUE;
    }
    else
    {
        m_TextLevel     = pOther->m_TextLevel;
        m_pObject       = pOther->m_pObject->Clone();
        m_TextOffset    = pOther->m_TextOffset;
        m_SectionNumber = pOther->m_SectionNumber;
        m_Level         = pOther->m_Level;
        m_AutoCalculate = pOther->m_AutoCalculate;
    }

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNAutoNumbered::Clone() const
{
    std::unique_ptr<PSS_PLFNAutoNumbered> pObject(new PSS_PLFNAutoNumbered(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNAutoNumbered*>(pSrc));
}
//---------------------------------------------------------------------------
CString PSS_PLFNAutoNumbered::GetFormattedObject()
{
    if (m_pObject)
        return m_pObject->GetFormattedObject();

    return "";
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNAutoNumbered::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    if (m_pObject)
        return m_pObject->ConvertFormattedObject(value, locateFormat, emptyWhenZero);

    // hasn't changed
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);
    m_TextLevel.DrawObject(pDC, pView);

    // must draw the object
    if (m_pObject)
        m_pObject->DrawObject(pDC, pView);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SizePositionHasChanged()
{
    if (!m_pObject)
        return;

    // call the basic fonction
    PlanFinObject::SizePositionHasChanged();

    // recalculate all element positions.
    GetTextLevel().SetClientRect(m_rctObject);
    m_pObject->SetClientRect(m_rctObject);
    m_pObject->GetClientRect().left += GetTextOffset();

    // if automatic recalculation of section
    if (GetAutoCalculate())
        AfxGetMainWnd()->SendMessageToDescendants(UM_REBUILDAUTOMATICNUMBER);
}
//---------------------------------------------------------------------------
CString PSS_PLFNAutoNumbered::GetUnformattedObject()
{
    if (m_pObject)
        return m_pObject->GetUnformattedObject();

    return "";
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetStyle(HandleStyle hStyle)
{
    if (m_pObject)
        m_pObject->SethStyle(hStyle);
}
//---------------------------------------------------------------------------
const COLORREF PSS_PLFNAutoNumbered::GetFillColor() const
{
    if (m_pObject)
        return m_pObject->GetFillColor();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::SetFillColor(COLORREF value)
{
    if (m_pObject)
        m_pObject->SetFillColor(value);
}
//---------------------------------------------------------------------------
void PSS_PLFNAutoNumbered::Serialize(CArchive& ar)
{
    PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_TextOffset);
        ar << WORD(m_AutoCalculate);
        ar << WORD(m_SectionNumber);
        ar << WORD(m_Level);

        // serialize the defined object
        ar << m_pObject;
    }
    else
    {
        // read the elements
        WORD temp;
        ar >> temp;
        m_TextOffset = temp;

        ar >> temp;
        m_AutoCalculate = temp;

        ar >> temp;
        m_SectionNumber = temp;

        ar >> temp;
        m_Level = temp;

        // serialize the defined object
        ar >> m_pObject;
    }

    // should serialize the static member, serialize the Text Level
    m_TextLevel.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAutoNumbered::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNAutoNumbered::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
