/****************************************************************************
 * ==> PSS_PLFNMaskString --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan mask string object               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNMaskString.h"

#include "ZDDoc.h"
#include "ZIView.h"
#include "PSS_MaskEditBase.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNMaskString, PLFNString, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNMaskString
//---------------------------------------------------------------------------
PSS_PLFNMaskString::PSS_PLFNMaskString() :
    PLFNString()
{}
//---------------------------------------------------------------------------
PSS_PLFNMaskString::PSS_PLFNMaskString(const PSS_PLFNMaskString& other) :
    PLFNString()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNMaskString::~PSS_PLFNMaskString()
{}
//---------------------------------------------------------------------------
const PSS_PLFNMaskString& PSS_PLFNMaskString::operator = (const PSS_PLFNMaskString& other)
{
    PLFNString::operator = ((inherited&)other);
    m_Mask = other.m_Mask;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNMaskString& PSS_PLFNMaskString::operator = (const PSS_PLFNMaskString* pOther)
{
    PLFNString::operator = ((inherited*)pOther);

    if (!pOther)
        m_Mask.Empty();
    else
        *this = *pOther;

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNMaskString::Clone() const
{
    std::unique_ptr<PSS_PLFNMaskString> pObject(new PSS_PLFNMaskString(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNMaskString::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNMaskString*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNMaskString::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        // if printing and the content is empty, and it is not necessary to print the empty style, just return
        if (!(pDC->IsPrinting() && PLFNText::IsEmpty() && !pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty()))
        {
            CFont* pOldFont = pDC->SelectObject(GetFont(pView));
            pDC->SetBkMode(TRANSPARENT);
            pDC->SetTextColor(GetColor(pView));

            // before drawing the object, format it, but for string it is not necessary in this version
            pDC->SetTextAlign(0);
            pDC->DrawText(GetFormattedObject(), -1, &m_rctObject, GetJustify(pView->GetDocument()));
            pDC->SelectObject(pOldFont);
        }
    }

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
CString PSS_PLFNMaskString::GetFormattedObject()
{
    PSS_MaskEditBase maskEdit;
    return maskEdit.GetFormattedBuffer(m_Mask, m_Str);
}
//---------------------------------------------------------------------------
void PSS_PLFNMaskString::Serialize(CArchive& ar)
{
    PLFNString::Serialize(ar);

    if (ar.IsStoring())
        // write the elements
        ar << m_Mask;
    else
        // read the elements
        ar >> m_Mask;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNMaskString::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNMaskString::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
