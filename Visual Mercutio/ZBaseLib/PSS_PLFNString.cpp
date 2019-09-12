/****************************************************************************
 * ==> PSS_PLFNString ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan string object                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNString.h"

// processsoft
#include "ZDDoc.h"
#include "ZIView.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNString, PLFNText, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNString
//---------------------------------------------------------------------------
PSS_PLFNString::PSS_PLFNString() :
    PLFNText()
{}
//---------------------------------------------------------------------------
PSS_PLFNString::PSS_PLFNString(const PSS_PLFNString& other) :
    PLFNText()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNString::~PSS_PLFNString()
{}
//---------------------------------------------------------------------------
const PSS_PLFNString& PSS_PLFNString::operator = (const PSS_PLFNString& other)
{
    PLFNText::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNString& PSS_PLFNString::operator = (const PSS_PLFNString* pOther)
{
    PLFNText::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNString::Clone() const
{
    std::unique_ptr<PSS_PLFNString> pObject(new PSS_PLFNString(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNString::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNString*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNString::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        CFont* pOldFont = pDC->SelectObject(GetFont(pView));
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));
        pDC->SetTextAlign(0);
        pDC->DrawText(m_Str, -1, &m_ObjectRect, GetJustify(pView->GetDocument()));
        pDC->SelectObject(pOldFont);
    }

    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNString::Serialize(CArchive& ar)
{
    PLFNText::Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNString::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNString::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
