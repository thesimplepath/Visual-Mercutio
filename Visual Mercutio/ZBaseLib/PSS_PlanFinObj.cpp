/****************************************************************************
 * ==> PSS_PlanFinObj ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides financial plan objects                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PlanFinObj.h"

// std
#include <float.h>

// processsoft
#include "ZDDoc.h"
#include "ZIView.h"
#include "zamath.h"
#include "PSS_DrawFunctions.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNRect, PLFNGraphic, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNRect
//---------------------------------------------------------------------------
PSS_PLFNRect::PSS_PLFNRect(BOOL round) :
    PLFNGraphic(),
    m_Round(round),
    m_ArcOffset(5)
{}
//---------------------------------------------------------------------------
PSS_PLFNRect::PSS_PLFNRect(const PSS_PLFNRect& other) :
    PLFNGraphic()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNRect::~PSS_PLFNRect()
{}
//---------------------------------------------------------------------------
const PSS_PLFNRect& PSS_PLFNRect::operator = (const PSS_PLFNRect* pOther)
{
    PLFNGraphic::operator = ((inherited*)pOther);

    if (!pOther)
    {
        // set default values
        m_Round     = 0;
        m_ArcOffset = 5;
    }
    else
    {
        m_Round     = pOther->m_Round;
        m_ArcOffset = pOther->m_ArcOffset;
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNRect& PSS_PLFNRect::operator = (const PSS_PLFNRect& other)
{
    PLFNGraphic::operator = ((inherited&)other);

    m_Round     = other.m_Round;
    m_ArcOffset = other.m_ArcOffset;

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNRect::Clone() const
{
    std::unique_ptr< PSS_PLFNRect> pObject(new PSS_PLFNRect(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNRect::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNRect*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNRect::Serialize(CArchive& ar)
{
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        PLFNGraphic::Serialize(ar);
    else
        PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_ArcOffset;
        ar << WORD(m_Round);
    }
    else
    {
        // read the elements
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> m_ArcOffset;

            WORD temp;
            ar >> temp;
            m_Round = BOOL(temp);
        }
        else
            m_Round = FALSE;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNRect::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNRect::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNRect::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CPen  pen;
    CPen* pOldPen = pDC->SelectObject(&GetGraphicPen(pen));

    if (m_Round)
    {
        // draw the square
        pDC->MoveTo(m_rctObject.left  + GetArcOffset(),       m_rctObject.top);
        pDC->LineTo(m_rctObject.right - GetArcOffset() + 1,   m_rctObject.top);
        pDC->Arc   (m_rctObject.left,                         m_rctObject.top,
                    m_rctObject.left  + (GetArcOffset() * 2), m_rctObject.top + (GetArcOffset() * 2),
                    m_rctObject.left  + GetArcOffset(),       m_rctObject.top,
                    m_rctObject.left,                         m_rctObject.top + GetArcOffset() + 1);

        pDC->MoveTo(m_rctObject.right,                        m_rctObject.top    + GetArcOffset());
        pDC->LineTo(m_rctObject.right,                        m_rctObject.bottom - GetArcOffset() + 1);
        pDC->Arc   (m_rctObject.right - (GetArcOffset() * 2), m_rctObject.top,
                    m_rctObject.right,                        m_rctObject.top    + (GetArcOffset() * 2),
                    m_rctObject.right,                        m_rctObject.top    + GetArcOffset(),
                    m_rctObject.right - GetArcOffset(),       m_rctObject.top);

        pDC->MoveTo(m_rctObject.right -  GetArcOffset(),      m_rctObject.bottom);
        pDC->LineTo(m_rctObject.left  +  GetArcOffset() - 1,  m_rctObject.bottom);
        pDC->Arc   (m_rctObject.right - (GetArcOffset() * 2), m_rctObject.bottom - (GetArcOffset() * 2),
                    m_rctObject.right,                        m_rctObject.bottom,
                    m_rctObject.right -  GetArcOffset() - 1,  m_rctObject.bottom,
                    m_rctObject.right,                        m_rctObject.bottom - GetArcOffset());

        pDC->MoveTo(m_rctObject.left,                        m_rctObject.bottom - GetArcOffset());
        pDC->LineTo(m_rctObject.left,                        m_rctObject.top    + GetArcOffset() - 1);
        pDC->Arc   (m_rctObject.left,                        m_rctObject.bottom - (GetArcOffset() * 2),
                    m_rctObject.left + (GetArcOffset() * 2), m_rctObject.bottom,
                    m_rctObject.left,                        m_rctObject.bottom - GetArcOffset(),
                    m_rctObject.left + GetArcOffset() + 1,   m_rctObject.bottom);
    }
    else
    {
        // draw the square
        pDC->MoveTo(m_rctObject.left,  m_rctObject.top);
        pDC->LineTo(m_rctObject.right, m_rctObject.top);
        pDC->LineTo(m_rctObject.right, m_rctObject.bottom);
        pDC->LineTo(m_rctObject.left,  m_rctObject.bottom);
        pDC->LineTo(m_rctObject.left,  m_rctObject.top);
    }

    // draw the shadow only on the screen
    if (!pDC->IsPrinting())
    {
        CPen lightGrayPen(PS_SOLID, 1, defCOLOR_LTLTGRAY);
        pDC->SelectObject(&lightGrayPen);

        if (!m_Round)
        {
            pDC->MoveTo(m_rctObject.right + 1, m_rctObject.top    + 1);
            pDC->LineTo(m_rctObject.right + 1, m_rctObject.bottom + 1);
            pDC->LineTo(m_rctObject.left  - 1, m_rctObject.bottom + 1);
        }
    }

    pDC->SelectObject(pOldPen);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNLine, PLFNGraphic, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNLine
//---------------------------------------------------------------------------
PSS_PLFNLine::PSS_PLFNLine() :
    PLFNGraphic(),
    m_StartPoint(0, 0),
    m_EndPoint(0, 0)
{}
//---------------------------------------------------------------------------
PSS_PLFNLine::PSS_PLFNLine(const PSS_PLFNLine& other) :
    PLFNGraphic()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNLine::~PSS_PLFNLine()
{}
//---------------------------------------------------------------------------
const PSS_PLFNLine& PSS_PLFNLine::operator = (const PSS_PLFNLine* pOther)
{
    PLFNGraphic::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_StartPoint = ZBPoint(0, 0);
        m_EndPoint   = ZBPoint(0, 0);
    }
    else
    {
        m_StartPoint = pOther->m_StartPoint;
        m_EndPoint   = pOther->m_EndPoint;
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNLine& PSS_PLFNLine::operator = (const PSS_PLFNLine& other)
{
    PLFNGraphic::operator = ((inherited&)other);

    m_StartPoint = other.m_StartPoint;
    m_EndPoint   = other.m_EndPoint;

    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNLine::Clone() const
{
    std::unique_ptr< PSS_PLFNLine> pObject(new PSS_PLFNLine(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNLine::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNLine*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNLine::SizePositionHasChanged()
{
    PlanFinObject::SizePositionHasChanged();

    // recalculate all element positions
    m_StartPoint.x = m_rctObject.left;
    m_StartPoint.y = m_rctObject.top;
    m_EndPoint.x   = m_rctObject.right;
    m_EndPoint.y   = m_rctObject.bottom;
}
//---------------------------------------------------------------------------
void PSS_PLFNLine::Serialize(CArchive& ar)
{
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        PLFNGraphic::Serialize(ar);
    else
        PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_StartPoint;
        ar << m_EndPoint;
    }
    else
    {
        // read the elements. If the version is before the version 0, then the line rect should be modified
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 0)
            m_rctObject.bottom = m_rctObject.top;

        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_StartPoint;
            ar >> m_EndPoint;
        }
        else
        {
            m_StartPoint.x = m_rctObject.left;
            m_StartPoint.y = m_rctObject.top;
            m_EndPoint.x   = m_rctObject.right;
            m_EndPoint.y   = m_rctObject.bottom;
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNLine::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNLine::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNLine::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CPen  pen;
    CPen* pOldPen = pDC->SelectObject(&GetGraphicPen(pen));

    pDC->MoveTo(m_rctObject.left, m_rctObject.top);
    pDC->LineTo(m_rctObject.right, m_rctObject.bottom);

    // draw the shadow only on the screen
    if (!pDC->IsPrinting())
    {
        CPen lightGrayPen(PS_SOLID, 1, defCOLOR_LTLTGRAY);
        pDC->SelectObject(&lightGrayPen);
        pDC->MoveTo(m_rctObject.left  + 1, m_rctObject.top    + 1);
        pDC->LineTo(m_rctObject.right + 1, m_rctObject.bottom + 1);
    }

    pDC->SelectObject(pOldPen);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNStatic, PLFNText, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNStatic
//---------------------------------------------------------------------------
PSS_PLFNStatic::PSS_PLFNStatic() :
    PLFNText()
{
    // set as static
    SetIsStatic(TRUE);
}
//---------------------------------------------------------------------------
PSS_PLFNStatic::PSS_PLFNStatic(const PSS_PLFNStatic& other) :
    PLFNText()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNStatic::~PSS_PLFNStatic()
{}
//---------------------------------------------------------------------------
const PSS_PLFNStatic& PSS_PLFNStatic::operator = (const PSS_PLFNStatic* pOther)
{
    PLFNText::operator = ((inherited*)pOther);
    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNStatic& PSS_PLFNStatic::operator = (const PSS_PLFNStatic& other)
{
    PLFNText::operator = ((inherited&)other);
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNStatic::Clone() const
{
    std::unique_ptr< PSS_PLFNStatic> pObject(new PSS_PLFNStatic(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNStatic::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNStatic*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNStatic::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));
    pDC->SetBkMode(TRANSPARENT);

    CSize  sizeText;
    CPoint orgText;

    // text color
    pDC->SetTextColor(GetColor(pView));
    GetTextExtentOrg(pDC, m_Str, sizeText, orgText, GetiAngle());
    m_rctObject.right = m_rctObject.left + sizeText.cx;

    // the alignment to bottom should be changed to remove the alignement issue with different fonts,
    // then the calculation of the text area should be changed
    m_rctObject.top = m_rctObject.bottom - sizeText.cy;
    pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
    pDC->TextOut(m_rctObject.left + orgText.x, m_rctObject.bottom - orgText.y, m_Str);
    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_PLFNStatic::OnAngleChanged(ZDDocument* pDoc)
{
    // rotate the font
    RotateFont(pDoc);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNTime, PSS_PLFNAscii, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNTime
//---------------------------------------------------------------------------
PSS_PLFNTime::PSS_PLFNTime() :
    PSS_PLFNAscii(),
    m_Time(g_ZeroTime)
{}
//---------------------------------------------------------------------------
PSS_PLFNTime::PSS_PLFNTime(const PSS_PLFNTime& other) :
    PSS_PLFNAscii()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNTime::~PSS_PLFNTime()
{}
//---------------------------------------------------------------------------
const PSS_PLFNTime& PSS_PLFNTime::operator = (const PSS_PLFNTime* pOther)
{
    PSS_PLFNAscii::operator = ((inherited*)pOther);

    if (!pOther)
        m_Time = g_ZeroTime;
    else
        m_Time = pOther->m_Time;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNTime& PSS_PLFNTime::operator = (const PSS_PLFNTime& other)
{
    PSS_PLFNAscii::operator = ((inherited&)other);
    m_Time = other.m_Time;
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNTime::Clone() const
{
    std::unique_ptr<PSS_PLFNTime> pObject(new PSS_PLFNTime(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNTime::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNTime*>(pSrc));
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNTime::IsSelected(const CPoint& point) const
{
    return(m_rctObject.PtInRect(point));
}
//---------------------------------------------------------------------------
CString PSS_PLFNTime::GetFormattedObject()
{
    FormatObject(&m_Time);
    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
CString PSS_PLFNTime::GetUnformattedObject()
{
    if (IsEmpty())
        // empty the string
        m_szFormatBuffer[0] = 0x00;
    else
        std::sprintf(m_szFormatBuffer, "%d.%d.%04d", m_Time.GetDay(), m_Time.GetMonth(), m_Time.GetYear());

    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNTime::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    // set the flag for empty or not
    if (value.IsEmpty())
        EmptyObject();
    else
        ClearEmptyObjectFlag();

    // save the old value to know if the value has changed
    #ifndef _WIN32
        CTime        oldTime = m_Time;
    #else
        COleDateTime oldTime = m_Time;
    #endif

    CString temp = value;
    int     index;

    // get the day
    if ((index = temp.FindOneOf("./")) == -1)
    {
        EmptyObject();

        // changed?
        return (oldTime != m_Time);
    }

          CString param = temp.Left(index);
    const int     day    = std::atoi((const char *)param);

    if (day <= 0)
        return FALSE;

    // get the month
    temp = temp.Right(temp.GetLength() - index - 1);

    if ((index = temp.FindOneOf("./")) == -1)
    {
        EmptyObject();

        // changed?
        return (oldTime != m_Time);
    }

    param           = temp.Left(index);
    const int month = std::atoi((const char *)param);

    if (month <= 0)
        return FALSE;

    // get the year
    param    = temp.Right(temp.GetLength() - index - 1);
    int year = std::atoi((const char *)param);

    // 1900 Based date
    if (year < 1900)
        year += 1900;

    #ifndef _WIN32
        CTime        time(year, month, day, 12, 00, 00);
    #else
        COleDateTime time(year, month, day, 12, 00, 00);
    #endif

    m_Time = time;

    // changed?
    return (oldTime != m_Time);
}
//---------------------------------------------------------------------------
CStringArray& PSS_PLFNTime::GetFormatChoice() const
{
    m_FormatChoice.RemoveAll();

    // read the number and format it. Create a copy of the current object and modify the format
    PSS_PLFNTime tmpTime = *this;

    tmpTime.SetFormatType(E_FT_Standard);
    tmpTime.FormatObject(&tmpTime.m_Time);
    m_FormatChoice.Add(CString(tmpTime.GetFormatedBuffer()));

    tmpTime.SetFormatType(E_FT_Date);
    tmpTime.FormatObject(&tmpTime.m_Time);
    m_FormatChoice.Add(CString(tmpTime.GetFormatedBuffer()));

    tmpTime.SetFormatType(E_FT_Date1);
    tmpTime.FormatObject(&tmpTime.m_Time);
    m_FormatChoice.Add(CString(tmpTime.GetFormatedBuffer()));

    tmpTime.SetFormatType(E_FT_Date2);
    tmpTime.FormatObject(&tmpTime.m_Time);
    m_FormatChoice.Add(CString(tmpTime.GetFormatedBuffer()));

    return m_FormatChoice;
}
//---------------------------------------------------------------------------
void PSS_PLFNTime::SetFormatWithChoice(const CString& value)
{
    const INT_PTR formatChoiceCount = m_FormatChoice.GetSize();
          INT_PTR index             = 0;

    // iterate through the array and compare which one is the same
    for (INT_PTR i = 0; i < formatChoiceCount; ++i)
        if (m_FormatChoice[i] == value)
        {
            index = i;
            break;
        }

    // found a format?
    if (index < formatChoiceCount)
        switch (index)
        {
            case 0: m_FormatType = E_FT_Standard; break;
            case 1: m_FormatType = E_FT_Date;     break;
            case 2: m_FormatType = E_FT_Date1;    break;
            case 3: m_FormatType = E_FT_Date2;    break;
        }
}
//---------------------------------------------------------------------------
void PSS_PLFNTime::Serialize(CArchive& ar)
{
    PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
        // write the elements
        ar << m_Time;
    else
    {
        // read the elements. Before version 13
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 13)
        {
            CTime time;
            ar >> time;

            if (time.GetTime() >= 0)
                m_Time.SetDateTime(time.GetYear(),
                                   time.GetMonth(),
                                   time.GetDay(),
                                   time.GetHour(),
                                   time.GetMinute(),
                                   time.GetSecond());

            // before version 12
            if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 12)
            {
                #ifdef _WIN32
                    // build a CTime for comparison
                    CTime zeroTime(g_ZeroTime.GetYear(),
                                   g_ZeroTime.GetMonth(),
                                   g_ZeroTime.GetDay(),
                                   g_ZeroTime.GetHour(),
                                   g_ZeroTime.GetMinute(),
                                   g_ZeroTime.GetSecond());

                    m_IsEmpty = (time == zeroTime);
                #else
                    m_IsEmpty = (time == g_ZeroTime);
                #endif
            }
        }
        else
            ar >> m_Time;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNTime::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNTime::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNTime::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetColor(pView));

        // before drawing the object, format it
        FormatObject(&m_Time);
        pDC->SetTextAlign(0);
        pDC->DrawText(GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()));
    }

    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNLong, PSS_PLFNAscii, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNLong
//---------------------------------------------------------------------------
PSS_PLFNLong::PSS_PLFNLong() :
    PSS_PLFNAscii(),
    m_Long(0.0),
    m_IconDisplayType(IE_DT_NoIcon),
    m_Rounded(0.0),
    m_IsCalculatedField(FALSE),
    m_KeepTheValue(FALSE),
    m_IsRounded(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PLFNLong::PSS_PLFNLong(const PSS_PLFNLong& other) :
    PSS_PLFNAscii()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNLong::~PSS_PLFNLong()
{}
//---------------------------------------------------------------------------
const PSS_PLFNLong& PSS_PLFNLong::operator = (const PSS_PLFNLong* pOther)
{
    PSS_PLFNAscii::operator = ((inherited*)pOther);

    if (!pOther)
    {
        // set default values
        m_Long              = 0.0;
        m_IconDisplayType   = IE_DT_NoIcon;
        m_Rounded           = 0.0;
        m_IsCalculatedField = FALSE;
        m_KeepTheValue      = FALSE;
        m_IsRounded         = FALSE;
    }
    else
    {
        m_Long              = pOther->m_Long;
        m_IconDisplayType   = pOther->m_IconDisplayType;
        m_Rounded           = pOther->m_Rounded;
        m_IsCalculatedField = pOther->m_IsCalculatedField;
        m_KeepTheValue      = pOther->m_KeepTheValue;
        m_IsRounded         = pOther->m_IsRounded;

        m_Associations.AssignContents(pOther->m_Associations);
    }

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNLong& PSS_PLFNLong::operator = (const PSS_PLFNLong& other)
{
    PSS_PLFNAscii::operator = ((inherited&)other);
    m_Long              = other.m_Long;
    m_IconDisplayType   = other.m_IconDisplayType;
    m_Rounded           = other.m_Rounded;
    m_IsCalculatedField = other.m_IsCalculatedField;
    m_KeepTheValue      = other.m_KeepTheValue;
    m_IsRounded         = other.m_IsRounded;
    m_Associations.AssignContents(other.m_Associations);
    return *this;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_PLFNLong::Clone() const
{
    std::unique_ptr<PSS_PLFNLong> pObject(new PSS_PLFNLong(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::CopyObject(PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNLong*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::GetContains(const CString& line)
{
    int index;

    // get the object name
    if ((index = line.ReverseFind(',')) == -1)
        return;

    // get the value string
    CString str;
    int     pos = line.GetLength() - index - 2;

    if (pos > 0)
        str = line.Right(pos);

    m_Long = std::atof(str);
}
//---------------------------------------------------------------------------
CString PSS_PLFNLong::GetFormattedObject()
{
    if (IsEmpty())
        return "";

    FormatObject(m_Long);

    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
CString PSS_PLFNLong::GetUnformattedObject()
{
    if (IsEmpty())
        return "";

    std::sprintf(m_szFormatBuffer, "%lf", m_Long);

    return GetFormatedBuffer();
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNLong::ConvertFormatedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    if (value.IsEmpty())
    {
        EmptyObject();
        return TRUE;
    }

    // save the old value to make comparison
    const double oldValue = m_Long;

    // convert the string to a double and assign the result to the value. Check if the % char exists.
    // If it's the case remove it and divide the number by 100. If the % char exists, the ' char can't
    // exists at the same time
    char* pCpPos = const_cast<char*>(std::strchr((const char*)value, '%'));

    if (pCpPos)
    {
        // check if char ' exists at the same time 
        if (std::strchr((const char*)value, '\''))
        {
            AfxMessageBox(IDS_WZFORMATNUMBERERROR);
            return FALSE;
        }

        // replace the percentage symbol
        *pCpPos = 0x00;
        m_Long  = std::atof((const char*)value) / 100;

        if (locateFormat)
            SetFormatType(E_FT_Percentage);

        // check if it's necessary to empty the object when zeros
        if (emptyWhenZero && !m_Long)
            EmptyObject();

        // has changed?
        return (oldValue != m_Long);
    }

    // detect dash or double-dash
    bool b1Dash = false;
    bool b2Dash = false;

    if (std::strstr((const char*)value, ".--"))
        b2Dash = true;
    else
    if (std::strstr((const char*)value, ".-"))
        b1Dash = true;

    // test if amounts contain a ' char
    if (std::strchr((const char*)value, '\''))
    {
        // remove the ' char
        const char* pBuffer = (const char*)value;
        char        szTemp[100];
        std::size_t index = 0;

        for (int i = 0; *pBuffer; ++pBuffer)
            if (*pBuffer != '\'')
            {
                szTemp[i] = *pBuffer;
                ++i;
                index = i;
            }

        szTemp[index] = 0x00;

        // if dash or double-dash, remove it before converting to number
        if (b2Dash)
            // set artificial end of buffer
            szTemp[index - 2] = 0x00;
        else
        if (b1Dash)
            // set artificial end of buffer
            szTemp[index - 1] = 0x00;

        m_Long = std::atof(szTemp);

        if (locateFormat)
            if (std::strchr((const char*)value, ',') || std::strchr((const char*)value, '.'))
            {
                if (b2Dash)
                    SetFormatType(E_FT_Amount2DashTrail);
                else
                if (b1Dash)
                    SetFormatType(E_FT_Amount1DashTrail);
                else
                    SetFormatType(E_FT_Amount2);
            }
            else
                SetFormatType(E_FT_Amount);
    }
    else
    {
        char      temp[100];
        const int i = value.GetLength() - 1;

        std::strcpy(temp, (const char*)value);

        // if dahs or double-dash, remove it before converting to number
        if (b2Dash)
            // set artificial end of buffer
            temp[i - 2] = 0x00;
        else
        if (b1Dash)
            // set artificial end of buffer
            temp[i - 1] = 0x00;

        m_Long = std::atof(temp);

        if (locateFormat && (std::strchr((const char*)value, ',') || std::strchr((const char*)value, '.')))
            if (b2Dash)
                SetFormatType(E_FT_Amount2Dash);
            else
            if (b1Dash)
                SetFormatType(E_FT_Amount1Dash);
            else
                SetFormatType(E_FT_Amount1);
    }

    // check if it's necessary to empty the object when zeros
    if (emptyWhenZero && !m_Long)
        EmptyObject();
    else
        ClearEmptyObjectFlag();

    // has changed?
    return (oldValue != m_Long);
}
//---------------------------------------------------------------------------
CStringArray& PSS_PLFNLong::GetFormatChoice()
{
    m_FormatChoice.RemoveAll();

    // read the number and format it. Create a copy of the current object and modify the format
    bool         wasEmpty = false;
    PSS_PLFNLong tmpLong  = *this;

    // bug on empty number, set 0 if empty
    if (tmpLong.IsEmpty())
    {
        wasEmpty = true;
        tmpLong.SetValue(1035.25);
    }

    tmpLong.SetFormatType(E_FT_Standard);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount1);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount2);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount1Dash);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount2Dash);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount1DashTrail);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    tmpLong.SetFormatType(E_FT_Amount2DashTrail);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    if (wasEmpty)
        tmpLong.SetValue(0.5845);

    tmpLong.SetFormatType(E_FT_Percentage);
    tmpLong.FormatObject(tmpLong.m_Long);
    m_FormatChoice.Add(CString(tmpLong.GetFormatedBuffer()));

    return m_FormatChoice;
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::SetFormatWithChoice(const CString& value)
{
    const INT_PTR formatChoiceCount = m_FormatChoice.GetSize();
          INT_PTR index             = 0;

    // iterate through the array and search for matching value
    for (INT_PTR i = 0; i < formatChoiceCount; ++i)
        if (m_FormatChoice[i] == value)
        {
            index = i;
            break;
        }

    // found something?
    if (index < m_FormatChoice.GetSize())
        switch (index)
        {
            case 0: m_FormatType = E_FT_Standard;         break;
            case 1: m_FormatType = E_FT_Amount;           break;
            case 2: m_FormatType = E_FT_Amount1;          break;
            case 3: m_FormatType = E_FT_Amount2;          break;
            case 4: m_FormatType = E_FT_Amount1Dash;      break;
            case 5: m_FormatType = E_FT_Amount2Dash;      break;
            case 6: m_FormatType = E_FT_Amount1DashTrail; break;
            case 7: m_FormatType = E_FT_Amount2DashTrail; break;
            case 8: m_FormatType = E_FT_Percentage;       break;
        }
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::Recalculate(ZDDocument* pDoc)
{
    if (!pDoc)
        return;

    PSS_Formula* pFormula = pDoc->GetFormula(GetObjectName());

    if (!pFormula)
        return;

    Parser parser;
    m_Long = parser.StringParser((const char*)pFormula->GetExtractedFormula(), &(pDoc->GetObjectList()));

    if (GetRoundedValue() && IsRounded())
        m_Long = std::ceil(m_Long / GetRoundedValue()) * GetRoundedValue();
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::DrawCalculatedSymbol(CDC* pDC)
{
    if (pDC->IsPrinting())
        return;

    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_CALCBACKASSC), RT_BITMAP);

    if (GetCurrentAssociation())
    {
        if (IsCalculatedField())
        {
            PlanFinObject::DrawBoundRect(pDC);

            // show calculator icon in association mode
            ShowBitmapFile(MAKEINTRESOURCE(IDB_CALCBACKASSC),
                           pDC->m_hDC,
                           hInst,
                           m_rctObject.right,
                           m_rctObject.bottom);
        }
        else
        {
            // show icon in association mode
            ShowBitmapFile(MAKEINTRESOURCE(IDB_BACKASSC),
                           pDC->m_hDC,
                           hInst,
                           m_rctObject.right,
                           m_rctObject.bottom);

            PlanFinObject::DrawRightCorner(pDC);
        }
    }
    else
    {
        if (m_IconDisplayType == IE_DT_AssociationIcon)
        {
            PlanFinObject::DrawBoundRect(pDC);

            // show the field as calculate with association
            ShowBitmapFile(MAKEINTRESOURCE(IDB_CALCWITHASSC),
                           pDC->m_hDC,
                           hInst,
                           m_rctObject.right,
                           m_rctObject.bottom);
        }
        else
        if (IsCalculatedField())
        {
            PlanFinObject::DrawBoundRect(pDC);

            // show the field as protected
            if (KeepTheValue())
                ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_LOCKED),
                                     pDC->m_hDC,
                                     hInst,
                                     m_rctObject.right,
                                     m_rctObject.bottom,
                                     SRCAND);
            else
            if (GetAssociations().GetCount())
                // show calculator icon for association mode
                ShowBitmapFile(MAKEINTRESOURCE(IDB_CALCSHOWASSC),
                               pDC->m_hDC,
                               hInst,
                               m_rctObject.right,
                               m_rctObject.bottom);
            else
                // show the field as calculate
                ShowBitmapFile(MAKEINTRESOURCE(IDB_CALCULATOR),
                               pDC->m_hDC,
                               hInst,
                               m_rctObject.right,
                               m_rctObject.bottom);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_PLFNLong::Serialize(CArchive& ar)
{
    PSS_PLFNAscii::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_Long;
        ar << WORD(m_IsCalculatedField);
        ar << WORD(m_KeepTheValue);
        ar << WORD(m_IsRounded);
        ar << m_Rounded;
        ar << WORD(m_IconDisplayType);
    }
    else
    {
        // read the elements
        ar >> m_Long;

        WORD value;

        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 1)
        {
            m_IsCalculatedField = FALSE;
            m_KeepTheValue = FALSE;
        }
        else
        {
            ar >> value;
            m_IsCalculatedField = value;

            ar >> value;
            m_KeepTheValue = value;
        }

        // since version 2
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 2 && ((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() <= 5)
        {
            CStringArray schemaArray;
            schemaArray.Serialize(ar);
        }

        // since version 5
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> value;
            m_IsRounded = BOOL(value);

            ar >> m_Rounded;
        }

        // since version 6
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 6)
        {
            ar >> value;
            m_IconDisplayType = IEIconDisplayType(value);
        }

        // until version 12
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 12)
        {
            m_IsEmpty = (m_Long == FLT_MAX);

            if (m_Long == FLT_MAX)
                m_Long = 0;
        }
    }

    // serialize associations (since version 6)
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 6)
        m_Associations.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNLong::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNLong::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PLFNLong::DrawObject(CDC* pDC, ZIView* pView)
{
    DrawFillObject(pDC, pView);

    CFont* pOldFont = pDC->SelectObject(GetFont(pView));

    if (IsEmpty())
        DrawEmpty(pDC, pView);
    else
    {
        pDC->SetBkMode(TRANSPARENT);

        const COLORREF color = GetColor(pView);
        pDC->SetTextColor(color);

        // before drawing the object, format it
        FormatObject(m_Long);

        pDC->SetTextAlign(0);
        pDC->DrawText(GetFormatedBuffer(), -1, &m_rctObject, GetJustify(pView->GetDocument()));
    }

    pDC->SelectObject(pOldFont);

    PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
