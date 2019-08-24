/****************************************************************************
 * ==> PSS_ObsoletePLFNObj -------------------------------------------------*
 ****************************************************************************
 * Description : Provides previous and obsolete versions of the financial   *
 *               plan objects                                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ObsoletePLFNObj.h"

// processsoft
#include "PSS_DrawFunctions.h"
#include "ZIView.h"
#include "ZDDoc.h"

// windows
#include <float.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNStringHistory, PLFNString, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNStringHistory
//---------------------------------------------------------------------------
PSS_PLFNStringHistory::PSS_PLFNStringHistory() :
    PLFNString()
{}
//---------------------------------------------------------------------------
PSS_PLFNStringHistory::PSS_PLFNStringHistory(const PSS_PLFNStringHistory& other) :
    PLFNString()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNStringHistory::~PSS_PLFNStringHistory()
{}
//---------------------------------------------------------------------------
const PSS_PLFNStringHistory& PSS_PLFNStringHistory::operator = (const PSS_PLFNStringHistory* pOther)
{
    PLFNString::operator = ((inherited*)pOther);

    if (!pOther)
        m_Str.Empty();
    else
        m_Str = pOther->m_Str;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNStringHistory& PSS_PLFNStringHistory::operator = (const PSS_PLFNStringHistory& other)
{
    PLFNString::operator = ((inherited&)other);
    m_Str = other.m_Str;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNStringHistory::Clone() const
{
    std::unique_ptr<PSS_PLFNStringHistory> pObject(new PSS_PLFNStringHistory(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNStringHistory::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNStringHistory::operator = (dynamic_cast<PSS_PLFNStringHistory*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNStringHistory::GetContains(const CString& line)
{
    PLFNString::GetContains(line);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNStringHistory::IsSelected(const CPoint& point) const
{
    return(m_rctObject.PtInRect(point));
}
//---------------------------------------------------------------------------
void PSS_PLFNStringHistory::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNStringHistory::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNStringHistory::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNNumbered, PLFNStatic, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNNumbered
//---------------------------------------------------------------------------
PSS_PLFNNumbered::PSS_PLFNNumbered() :
    PLFNStatic()
{}
//---------------------------------------------------------------------------
PSS_PLFNNumbered::PSS_PLFNNumbered(const PSS_PLFNNumbered& other) :
    PLFNStatic()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNNumbered::~PSS_PLFNNumbered()
{}
//---------------------------------------------------------------------------
const PSS_PLFNNumbered& PSS_PLFNNumbered::operator = (const PSS_PLFNNumbered* pOther)
{
    PLFNStatic::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_Chapter   = 0;
        m_Paragraph = 0;
    }
    else
    {
        m_Chapter   = pOther->m_Chapter;
        m_Paragraph = pOther->m_Paragraph;
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNNumbered& PSS_PLFNNumbered::operator = (const PSS_PLFNNumbered& other)
{
    PLFNStatic::operator = ((inherited&)other);
    m_Chapter   = other.m_Chapter;
    m_Paragraph = other.m_Paragraph;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNNumbered::Clone() const
{
    std::unique_ptr<PSS_PLFNNumbered> pObject(new PSS_PLFNNumbered(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbered::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNNumbered::operator = (dynamic_cast<PSS_PLFNNumbered*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbered::Serialize(CArchive& ar)
{
    PLFNStatic::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_Paragraph);
        ar << WORD(m_Chapter);
    }
    else
    {
        // read the elements
        WORD temp;

        ar >> temp;
        m_Paragraph = int(temp);

        ar >> temp;
        m_Chapter = int(temp);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbered::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbered::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNNumbered::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(GetColor(pView));
    pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);

    CSize textSize    = pDC->GetTextExtent(m_Str, m_Str.GetLength());
    m_rctObject.right = m_rctObject.left + textSize.cx;

    // the alignement is changed to bottom to remove the alignment issue with different fonts,
    // then the text area calculation should be changed
    m_rctObject.top = m_rctObject.bottom - textSize.cy;

    char buffer[100];

    // format the chapter and paragraph number
    if (m_Paragraph)
        std::sprintf(buffer, "%d.%d ", m_Chapter, m_Paragraph);
    else
        std::sprintf(buffer, "%d ", m_Chapter);

    textSize = pDC->GetTextExtent(buffer, std::strlen(buffer));
    pDC->TextOut(m_rctObject.left - textSize.cx, m_rctObject.bottom, buffer);

    FormatObject(m_Str);
    pDC->SetTextAlign(0);
    pDC->DrawText(GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()));

    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNNumbEdit, PLFNString, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNNumbEdit
//---------------------------------------------------------------------------
PSS_PLFNNumbEdit::PSS_PLFNNumbEdit() :
    PLFNString()
{}
//---------------------------------------------------------------------------
PSS_PLFNNumbEdit::PSS_PLFNNumbEdit(const PSS_PLFNNumbEdit& other) :
    PLFNString()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNNumbEdit::~PSS_PLFNNumbEdit()
{}
//---------------------------------------------------------------------------
const PSS_PLFNNumbEdit& PSS_PLFNNumbEdit::operator = (const PSS_PLFNNumbEdit* pOther)
{
    PLFNString::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_Chapter   = 0;
        m_Paragraph = 0;
    }
    else
    {
        m_Chapter   = pOther->m_Chapter;
        m_Paragraph = pOther->m_Paragraph;
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNNumbEdit& PSS_PLFNNumbEdit::operator = (const PSS_PLFNNumbEdit& other)
{
    PLFNString::operator = ((inherited&)other);
    m_Chapter   = other.m_Chapter;
    m_Paragraph = other.m_Paragraph;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNNumbEdit::Clone() const
{
    std::unique_ptr<PSS_PLFNNumbEdit> pObject(new PSS_PLFNNumbEdit(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbEdit::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNNumbEdit::operator = (dynamic_cast<PSS_PLFNNumbEdit*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbEdit::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_Paragraph);
        ar << WORD(m_Chapter);
    }
    else
    {
        // read the elements
        WORD temp;

        ar >> temp;
        m_Paragraph = int(temp);

        ar >> temp;
        m_Chapter = int(temp);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbEdit::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbEdit::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNNumbEdit::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
    pDC->SetTextColor(GetColor(pView));

    char buffer[100];

    // format the chapter and paragraph number
    if (m_Paragraph)
        std::sprintf(buffer, "%d.%d ", m_Chapter, m_Paragraph);
    else
        std::sprintf(buffer, "%d ", m_Chapter);

    const CSize sizeText = pDC->GetTextExtent(buffer, std::strlen(buffer));
    pDC->TextOut(m_rctObject.left - sizeText.cx, m_rctObject.bottom, buffer);

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        FormatObject(m_Str);
        pDC->SetTextAlign(0);
        pDC->DrawText(GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()));
    }

    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNCalculated, PLFNLong, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNCalculated
//---------------------------------------------------------------------------
PSS_PLFNCalculated::PSS_PLFNCalculated() :
    PLFNLong()
{}
//---------------------------------------------------------------------------
PSS_PLFNCalculated::PSS_PLFNCalculated(const PSS_PLFNCalculated& other) :
    PLFNLong()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNCalculated::~PSS_PLFNCalculated()
{}
//---------------------------------------------------------------------------
const PSS_PLFNCalculated& PSS_PLFNCalculated::operator = (const PSS_PLFNCalculated* pOther)
{
    this->PLFNLong::operator = ((inherited*)pOther);

    if (!pOther)
        m_Long = 0.0;
    else
        m_Long = pOther->m_Long;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNCalculated& PSS_PLFNCalculated::operator = (const PSS_PLFNCalculated& other)
{
    PLFNLong::operator = ((inherited&)other);
    m_Long = other.m_Long;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNCalculated::Clone() const
{
    std::unique_ptr< PSS_PLFNCalculated> pObject(new PSS_PLFNCalculated(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNCalculated::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNCalculated::operator = (dynamic_cast<PSS_PLFNCalculated*>(pSrc));
}
//---------------------------------------------------------------------------
CString PSS_PLFNCalculated::GetFormattedObject()
{
    if (IsEmpty())
        FormatObject(0.0);
    else
        FormatObject(m_Long);

    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
void PSS_PLFNCalculated::Recalculate(ZDDocument* pDoc)
{
    if (!pDoc)
        return;

    // find the right formula for the current field in the document
    PSS_Formula* pFormula = pDoc->GetFormula(GetObjectName());

    if (!pFormula)
        return;

    Parser parser;

    m_Long = parser.StringParser((const char *)pFormula->GetExtractedFormula(), &(pDoc->GetObjectList()));
}
//---------------------------------------------------------------------------
void PSS_PLFNCalculated::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNCalculated::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNCalculated::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNNumHistory, PLFNLong, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNNumHistory
//---------------------------------------------------------------------------
PSS_PLFNNumHistory::PSS_PLFNNumHistory() :
    PLFNLong()
{}
//---------------------------------------------------------------------------
PSS_PLFNNumHistory::PSS_PLFNNumHistory(const PSS_PLFNNumHistory& other) :
    PLFNLong()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNNumHistory::~PSS_PLFNNumHistory()
{}
//---------------------------------------------------------------------------
const PSS_PLFNNumHistory& PSS_PLFNNumHistory::operator = (const PSS_PLFNNumHistory* pOther)
{
    PLFNLong::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNNumHistory& PSS_PLFNNumHistory::operator = (const PSS_PLFNNumHistory& other)
{
    PLFNLong::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNNumHistory::Clone() const
{
    std::unique_ptr<PSS_PLFNNumHistory> pObject(new PSS_PLFNNumHistory(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNNumHistory::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNNumHistory::operator = (dynamic_cast<PSS_PLFNNumHistory*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNNumHistory::GetContains(const CString& line)
{
    PLFNLong::GetContains(line);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNNumHistory::IsSelected(const CPoint& point) const
{
    return(m_rctObject.PtInRect(point));
}
//---------------------------------------------------------------------------
void PSS_PLFNNumHistory::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumHistory::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumHistory::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNNumbNumEdit, PLFNLong, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNNumbNumEdit
//---------------------------------------------------------------------------
PSS_PLFNNumbNumEdit::PSS_PLFNNumbNumEdit() :
    PLFNLong()
{}
//---------------------------------------------------------------------------
PSS_PLFNNumbNumEdit::PSS_PLFNNumbNumEdit(const PSS_PLFNNumbNumEdit& other) :
    PLFNLong()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNNumbNumEdit::~PSS_PLFNNumbNumEdit()
{}
//---------------------------------------------------------------------------
const PSS_PLFNNumbNumEdit& PSS_PLFNNumbNumEdit::operator = (const PSS_PLFNNumbNumEdit* pOther)
{
    PLFNLong::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_Chapter   = 0;
        m_Paragraph = 0;
    }
    else
    {
        m_Chapter   = pOther->m_Chapter;
        m_Paragraph = pOther->m_Paragraph;
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNNumbNumEdit& PSS_PLFNNumbNumEdit::operator = (const PSS_PLFNNumbNumEdit& other)
{
    PLFNLong::operator = ((inherited&)other);
    m_Chapter   = other.m_Chapter;
    m_Paragraph = other.m_Paragraph;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNNumbNumEdit::Clone() const
{
    std::unique_ptr<PSS_PLFNNumbNumEdit> pObject(new PSS_PLFNNumbNumEdit(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbNumEdit::CopyObject(PlanFinObject* pSrc)
{
    PSS_PLFNNumbNumEdit::operator = (dynamic_cast<PSS_PLFNNumbNumEdit*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNNumbNumEdit::Serialize(CArchive& ar)
{
    PLFNLong::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_Paragraph);
        ar << WORD(m_Chapter);
    }
    else
    {
        // read the elements
        WORD temp;

        ar >> temp;
        m_Paragraph = int(temp);

        ar >> temp;
        m_Chapter = int(temp);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbNumEdit::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNNumbNumEdit::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNNumbNumEdit::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
    pDC->SetTextColor(GetColor(pView));

    char buffer[70];

    // format the chapter and paragraph number
    if (m_Paragraph)
        std::sprintf(buffer, "%d.%d ", m_Chapter, m_Paragraph);
    else
        std::sprintf(buffer, "%d ", m_Chapter);

    CSize textSize = pDC->GetTextExtent(buffer, std::strlen(buffer));
    pDC->TextOut(m_rctObject.left - textSize.cx, m_rctObject.bottom, buffer);

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        // before showing the object, format it
        FormatObject(m_Long);

        pDC->SetTextAlign(0);
        pDC->DrawText(GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()));
    }

    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
