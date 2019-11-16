/****************************************************************************
 * ==> PSS_PLFNText --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan text object                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNText.h"

// processsoft
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNText, PSS_PLFNAscii, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNText
//---------------------------------------------------------------------------
PSS_PLFNText::PSS_PLFNText() :
    PSS_PLFNAscii(),
    m_IsStatic(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNText::PSS_PLFNText(const PSS_PLFNText& other) :
    PSS_PLFNAscii(),
    m_IsStatic(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNText::~PSS_PLFNText()
{}
//---------------------------------------------------------------------------
const PSS_PLFNText& PSS_PLFNText::operator = (const PSS_PLFNText& other)
{
    PSS_PLFNAscii::operator = ((inherited&)other);
    m_Str      = other.m_Str;
    m_IsStatic = other.m_IsStatic;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNText& PSS_PLFNText::operator = (const PSS_PLFNText* pOther)
{
    PSS_PLFNAscii::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_Str.Empty();
        m_IsStatic = FALSE;
    }
    else
    {
        m_Str      = pOther->m_Str;
        m_IsStatic = pOther->m_IsStatic;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNText::Clone() const
{
    return new PSS_PLFNText(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNText::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNText*>(pSrc));
}
//---------------------------------------------------------------------------
CString PSS_PLFNText::GetFormattedObject()
{
    return m_Str;
}
//---------------------------------------------------------------------------
CString PSS_PLFNText::GetUnformattedObject()
{
    return m_Str;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNText::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    // has changed?
    const BOOL result = (m_Str != value);

    // assign the new string
    m_Str = value;
    m_Str.IsEmpty() ? EmptyObject() : ClearEmptyObjectFlag();

    return result;
}
//---------------------------------------------------------------------------
void PSS_PLFNText::GetContains(const CString& line)
{
    int index;

    // get object name
    if ((index = line.ReverseFind(',')) == -1)
        return;

    // extract the iX
    int pos = line.GetLength() - index - 2;

    if (pos > 0)
        m_Str = line.Right(pos);
}
//---------------------------------------------------------------------------
void PSS_PLFNText::Serialize(CArchive& ar)
{
    PSS_PLFNAscii::Serialize(ar);

    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (ar.IsStoring())
    {
        // write the elements, check if template file but not static element. If static, serialize it
        if (pDocument                                                                    &&
            pDocument->GetDocumentStamp().GetFileType() == PSS_Stamp::IE_FD_TemplateType &&
            !m_IsStatic                                                                  &&
            !GetDefaultValue())
        {
            CString str(m_Str);
            m_Str = "";
            ar << m_Str;
            m_Str = str;
        }
        else
            ar << m_Str;

        ar << WORD(m_IsStatic);
    }
    else
    {
        // read the elements
        ar >> m_Str;

        if (pDocument)
        {
            // since version 5
            if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 5)
            {
                WORD wValue;
                ar >> wValue;
                m_IsStatic = BOOL(wValue);
            }

            // before version 12
            if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() < 12)
                m_IsEmpty = m_Str.IsEmpty();
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNText::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNText::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
