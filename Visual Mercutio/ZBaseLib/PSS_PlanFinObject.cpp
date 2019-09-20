/****************************************************************************
 * ==> PSS_PlanFinObject ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan object                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PlanFinObject.h"

// processsoft
#include "ZIView.h"
#include "ZDDoc.h"
#include "PSS_DrawFunctions.h"
#include "PSS_PaintResources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
// add this one because Microsoft is unable to support the locale correctly
static char* g_Months[] =
{
    _T("janvier"),
    _T("février"),
    _T("mars"),
    _T("avril"),
    _T("mai"),
    _T("juin"),
    _T("juillet"),
    _T("août"),
    _T("septembre"),
    _T("octobre"),
    _T("novembre"),
    _T("décembre")
};

static char* g_Days[] =
{
    _T("dimanche"),
    _T("lundi"),
    _T("mardi"),
    _T("mercredi"),
    _T("jeudi"),
    _T("vendredi"),
    _T("samedi")
};
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PlanFinObject, PSS_FormulaObjectParser, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PlanFinObject
//---------------------------------------------------------------------------
CStringArray PSS_PlanFinObject::m_FormatChoice;
char         PSS_PlanFinObject::m_FormatBuffer[300] = _T("");
//---------------------------------------------------------------------------
PSS_PlanFinObject::PSS_PlanFinObject() :
    PSS_FormulaObjectParser(),
    m_pNotes(NULL),
    m_FormatType(E_FT_Standard),
    m_ObjectRect(0, 0, 0, 0),
    m_IsEmpty(TRUE),
    m_pColumn(NULL),
    m_pRectTracker(NULL),
    m_pBorder(NULL),
    m_hFont(-1),
    m_hStyle(g_NormalStyle),
    m_EmptyStyle(E_LT_Automatic),
    m_Color(-1),
    m_FillColor(-1),
    m_LineNumber(0),
    m_GroupNumber(0),
    m_TabOrder(0.0),
    m_Angle(0),
    m_Page(0),
    m_Selected(FALSE),
    m_IsVisible(TRUE),
    m_MustBePrinted(TRUE),
    m_DefaultValue(FALSE),
    m_HasBeenChanged(FALSE),
    m_ReadOnly(FALSE),
    m_ReadOnlyAtRuntime(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PlanFinObject::PSS_PlanFinObject(const PSS_PlanFinObject& other) :
    PSS_FormulaObjectParser(),
    m_pNotes(NULL),
    m_FormatType(E_FT_Standard),
    m_ObjectRect(0, 0, 0, 0),
    m_IsEmpty(TRUE),
    m_pColumn(NULL),
    m_pRectTracker(NULL),
    m_pBorder(NULL),
    m_hFont(-1),
    m_hStyle(g_NormalStyle),
    m_EmptyStyle(E_LT_Automatic),
    m_Color(-1),
    m_FillColor(-1),
    m_LineNumber(0),
    m_GroupNumber(0),
    m_TabOrder(0.0),
    m_Angle(0),
    m_Page(0),
    m_Selected(FALSE),
    m_IsVisible(TRUE),
    m_MustBePrinted(TRUE),
    m_DefaultValue(FALSE),
    m_HasBeenChanged(FALSE),
    m_ReadOnly(FALSE),
    m_ReadOnlyAtRuntime(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject::~PSS_PlanFinObject()
{
    if (m_pRectTracker)
        delete m_pRectTracker;

    if (m_pBorder)
        delete m_pBorder;

    if (m_pNotes)
        delete m_pNotes;
}
//---------------------------------------------------------------------------
const PSS_PlanFinObject& PSS_PlanFinObject::operator = (const PSS_PlanFinObject& other)
{
    PSS_FormulaObjectParser::operator = ((inherited&)other);
    m_FormatType     = other.m_FormatType;
    m_ObjectRect     = other.m_ObjectRect;
    m_IsEmpty        = other.m_IsEmpty;
    m_hFont          = other.m_hFont;
    m_hStyle         = other.m_hStyle;
    m_EmptyStyle     = other.m_EmptyStyle;
    m_Color          = other.m_Color;
    m_FillColor      = other.m_FillColor;
    m_UserHelp       = other.m_UserHelp;
    m_LineNumber     = other.m_LineNumber;
    m_GroupNumber    = other.m_GroupNumber;
    m_TabOrder       = other.m_TabOrder;
    m_Angle          = other.m_Angle;
    m_Page           = other.m_Page;
    m_Selected       = other.m_Selected;
    m_IsVisible      = other.m_IsVisible;
    m_MustBePrinted  = other.m_MustBePrinted;
    m_DefaultValue   = other.m_DefaultValue;
    m_HasBeenChanged = other.m_HasBeenChanged;
    m_ReadOnly       = other.m_ReadOnly;

    if (other.m_pNotes)
        m_pNotes = other.m_pNotes->Clone();
    else
        m_pNotes = NULL;

    if (other.m_pRectTracker)
        m_pRectTracker = new CRectTracker(other.m_pRectTracker->m_rect,
                                          CRectTracker::dottedLine | CRectTracker::resizeInside);
    else
        m_pRectTracker = NULL;

    if (other.m_pBorder)
        m_pBorder = new PSS_Border(*other.m_pBorder);
    else
        m_pBorder = NULL;

    // copy the multi-column pointer
    m_pColumn = other.m_pColumn;

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PlanFinObject& PSS_PlanFinObject::operator = (const PSS_PlanFinObject* pOther)
{
    PSS_FormulaObjectParser::operator = ((inherited*)pOther);

    if (!pOther)
    {
        m_pNotes         =  NULL;
        m_FormatType     =  E_FT_Standard;
        m_ObjectRect     =  0, 0, 0, 0;
        m_IsEmpty        =  TRUE;
        m_pColumn        =  NULL;
        m_pRectTracker   =  NULL;
        m_pBorder        =  NULL;
        m_hFont          = -1;
        m_hStyle         =  g_NormalStyle;
        m_EmptyStyle     =  E_LT_Automatic;
        m_Color          = -1;
        m_FillColor      = -1;
        m_LineNumber     =  0;
        m_GroupNumber    =  0;
        m_TabOrder       =  0.0;
        m_Angle          =  0;
        m_Page           =  0;
        m_Selected       =  FALSE;
        m_IsVisible      =  TRUE;
        m_MustBePrinted  =  TRUE;
        m_DefaultValue   =  FALSE;
        m_HasBeenChanged =  FALSE;
        m_ReadOnly       =  FALSE;
    }
    else
    {
        m_FormatType     = pOther->m_FormatType;
        m_ObjectRect     = pOther->m_ObjectRect;
        m_IsEmpty        = pOther->m_IsEmpty;
        m_hFont          = pOther->m_hFont;
        m_hStyle         = pOther->m_hStyle;
        m_EmptyStyle     = pOther->m_EmptyStyle;
        m_Color          = pOther->m_Color;
        m_FillColor      = pOther->m_FillColor;
        m_UserHelp       = pOther->m_UserHelp;
        m_LineNumber     = pOther->m_LineNumber;
        m_GroupNumber    = pOther->m_GroupNumber;
        m_TabOrder       = pOther->m_TabOrder;
        m_Angle          = pOther->m_Angle;
        m_Page           = pOther->m_Page;
        m_Selected       = pOther->m_Selected;
        m_IsVisible      = pOther->m_IsVisible;
        m_MustBePrinted  = pOther->m_MustBePrinted;
        m_DefaultValue   = pOther->m_DefaultValue;
        m_HasBeenChanged = pOther->m_HasBeenChanged;
        m_ReadOnly       = pOther->m_ReadOnly;

        if (pOther->m_pNotes)
            m_pNotes = pOther->m_pNotes->Clone();
        else
            m_pNotes = NULL;

        if (pOther->m_pRectTracker)
            m_pRectTracker = new CRectTracker(pOther->m_pRectTracker->m_rect,
                                              CRectTracker::dottedLine | CRectTracker::resizeInside);
        else
            m_pRectTracker = NULL;

        if (pOther->m_pBorder)
            m_pBorder = new PSS_Border(*pOther->m_pBorder);
        else
            m_pBorder = NULL;

        // copy the multi-column pointer
        m_pColumn = pOther->m_pColumn;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PlanFinObject::Clone() const
{
    return new PSS_PlanFinObject(*this);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PlanFinObject*>(pSrc));
}
//---------------------------------------------------------------------------
double PSS_PlanFinObject::GetRealValue() const
{
    return 0;
}
//---------------------------------------------------------------------------
const BOOL PSS_PlanFinObject::GetIsStatic() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetIsStatic(BOOL value)
{}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SelectObject(CWnd* pWnd, CDC* pDC, BOOL state, BOOL erase)
{
    if (m_Selected == state)
        return;

    m_Selected = state;
    CRect rect = m_ObjectRect;

    pDC->LPtoDP(&rect);

    if (m_Selected && !m_pRectTracker)
    {
        // create a rect tracker object
        m_pRectTracker = new CRectTracker(&rect, CRectTracker::dottedLine | CRectTracker::resizeInside);
        ASSERT(m_pRectTracker);
    }
    else
    if (m_pRectTracker)
    {
        // delete the rect tracker object
        delete m_pRectTracker;
        m_pRectTracker = NULL;
    }

    // refresh the modified area
    rect.InflateRect(10, 10);

    if (pWnd)
        pWnd->InvalidateRect(&rect, erase);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::FormatObject(const char* pStr)
{
    if (!pStr)
    {
        m_FormatBuffer[0] = 0x0;
        return;
    }

    std::strcpy(m_FormatBuffer, pStr);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::FormatObject(CTime* pTime)
{
    if (!pTime)
    {
        m_FormatBuffer[0] = 0x0;
        return;
    }

    switch (GetFormatType())
    {
        case E_FT_Date:
            std::sprintf(m_FormatBuffer,
                         _T("%d %s, %04d"),
                         pTime->GetDay(),
                         g_Months[pTime->GetMonth() - 1],
                         pTime->GetYear());

            break;

        case E_FT_Date1:
            std::sprintf(m_FormatBuffer,
                         _T("%s, %d %s %04d"),
                         g_Days[pTime->GetDayOfWeek() - 1],
                         pTime->GetDay(),
                         g_Months[pTime->GetMonth() - 1],
                         pTime->GetYear());

            break;

        case E_FT_Date2:
            std::sprintf(m_FormatBuffer,
                         _T("%d.%d.%04d %dh%d"),
                         pTime->GetDay(),
                         pTime->GetMonth(),
                         pTime->GetYear(),
                         pTime->GetHour(),
                         pTime->GetSecond());

            break;

        default:
            std::sprintf(m_FormatBuffer,
                         _T("%d.%d.%04d"),
                         pTime->GetDay(),
                         pTime->GetMonth(),
                         pTime->GetYear());
    }
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::FormatObject(COleDateTime* pDateTime)
{
    if (!pDateTime)
    {
        m_FormatBuffer[0] = 0x0;
        return;
    }

    switch (GetFormatType())
    {
        case E_FT_Date:
            std::sprintf(m_FormatBuffer,
                         _T("%d %s, %04d"),
                         pDateTime->GetDay(),
                         g_Months[pDateTime->GetMonth() - 1],
                         pDateTime->GetYear());

            break;

        case E_FT_Date1:
            std::sprintf(m_FormatBuffer,
                         _T("%s, %d %s %04d"),
                         g_Days[pDateTime->GetDayOfWeek() - 1],
                         pDateTime->GetDay(),
                         g_Months[pDateTime->GetMonth() - 1],
                         pDateTime->GetYear());

            break;

        case E_FT_Date2:
            std::sprintf(m_FormatBuffer,
                         _T("%d.%d.%04d %dh%d"),
                         pDateTime->GetDay(),
                         pDateTime->GetMonth(),
                         pDateTime->GetYear(),
                         pDateTime->GetHour(),
                         pDateTime->GetSecond());

            break;

        default:
            std::sprintf(m_FormatBuffer,
                         _T("%d.%d.%04d"),
                         pDateTime->GetDay(),
                         pDateTime->GetMonth(),
                         pDateTime->GetYear());
    }
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::FormatObject(DOUBLE value)
{
    switch (GetFormatType())
    {
        case E_FT_Percentage:
            std::sprintf(m_FormatBuffer, _T("%3.3lg%c"), value * 100.0, _T('%'));
            break;

        case E_FT_Amount:
        {
            // use lf to remove the exponent notation and .0 to remove the decimals
            char  temp[100];
            char* pP = temp;
            std::sprintf(pP, _T("%.0lf"), value);

            // introduce the ' symbol
            int len   = std::strlen(pP);
            int i     = 0;
            int count = 0;

            // check if negative, go to next char
            if (value < 0)
            {
                --len;
                ++pP;
                m_FormatBuffer[i] = _T('-');
                ++i;
            }

            for (; *pP; ++i, ++count, ++pP)
            {
                // add the ' char every 3 digits, calculate if third digit by substracting i from the length
                if (count && ((len - count) % 3) == 0)
                {
                    m_FormatBuffer[i] = _T('\'');
                    ++i;
                }

                m_FormatBuffer[i] = *pP;
            }

            m_FormatBuffer[i] = 0x00;
            break;
        }

        case E_FT_Amount2:
        {
            // use lf to remove the exponent notation
            char  temp[100];
            char* pP = temp;
            std::sprintf(pP, _T("%.2lf"), value);

            // introduce the ' symbol
            int len   = std::strlen(pP);
            int i     = 0;
            int count = 0;

            // check if negative, go to next char
            if (value < 0)
            {
                --len;
                ++pP;
                m_FormatBuffer[i] = _T('-');
                ++i;
            }

            // until the end of the string or when encounter the decimal point
            for (; *pP && (*pP != _T('.')); ++i, ++count, ++pP)
            {
                // add the ' char every 3 digits, calculate if third digit by substracting i from the length
                if (count && ((len - count) % 3) == 0)
                {
                    m_FormatBuffer[i] = _T('\'');
                    ++i;
                }

                m_FormatBuffer[i] = *pP;
            }

            while (*pP)
            {
                m_FormatBuffer[i] = *pP;
                ++pP;
                ++i;
            }

            m_FormatBuffer[i] = 0x00;
            break;
        }

        case E_FT_Standard:
            // default case, just copy the source. Use lf to remove the exponent notation
            // and .0 to remove the decimals
            std::sprintf(m_FormatBuffer, _T("%.0lf"), value);
            break;

        case E_FT_Amount1:
            // use lf to remove the exponent notation and .0 to remove the decimals
            std::sprintf(m_FormatBuffer, _T("%.2lf"), value);
            break;

        case E_FT_Amount1Dash:
            // use lf to remove the exponent notation and .0 to remove the decimals + add .-
            std::sprintf(m_FormatBuffer, _T("%.0lf.-"), value);
            break;

        case E_FT_Amount2Dash:
            // use lf to remove the exponent notation and .0 to remove the decimals + add .--
            std::sprintf(m_FormatBuffer, _T("%.0lf.--"), value);
            break;

        case E_FT_Amount1DashTrail:
        {
            // use lf to remove the exponent notation and .0 to remove the decimals
            char  temp[100];
            char* pP = temp;
            std::sprintf(pP, _T("%.0lf"), value);

            // introduce the ' symbol
            int len   = std::strlen(pP);
            int i     = 0;
            int count = 0;

            // check if negative, go to next char
            if (value < 0)
            {
                --len;
                ++pP;
                m_FormatBuffer[i] = _T('-');
                ++i;
            }

            for (; *pP; ++i, ++count, ++pP)
            {
                // add the ' char every 3 digits, calculate if third digit by substracting i from the length
                if (count && ((len - count) % 3) == 0)
                {
                    m_FormatBuffer[i] = _T('\'');
                    ++i;
                }

                m_FormatBuffer[i] = *pP;
            }

            m_FormatBuffer[i] = _T('.'); ++i;
            m_FormatBuffer[i] = _T('-'); ++i;
            m_FormatBuffer[i] = 0x00;

            break;
        }

        case E_FT_Amount2DashTrail:
        {
            // use lf to remove the exponent notation and .0 to remove the decimals
            char  temp[100];
            char* pP = temp;
            std::sprintf(pP, _T("%.0lf"), value);

            // introduce the ' symbol
            int len   = std::strlen(pP);
            int i     = 0;
            int count = 0;

            // check if negative, go to next char
            if (value < 0)
            {
                --len;
                ++pP;
                m_FormatBuffer[i] = _T('-');
                ++i;
            }

            for (; *pP; ++i, ++count, ++pP)
            {
                // add the ' char every 3 digits, calculate if third digit by substracting i from the length
                if (count && ((len - count) % 3) == 0)
                {
                    m_FormatBuffer[i] = _T('\'');
                    ++i;
                }

                m_FormatBuffer[i] = *pP;
            }

            m_FormatBuffer[i] = _T('.'); ++i;
            m_FormatBuffer[i] = _T('-'); ++i;
            m_FormatBuffer[i] = _T('-'); ++i;
            m_FormatBuffer[i] = 0x00;

            break;
        }

        default:
            m_FormatBuffer[0] = 0x00;
    }
}
//---------------------------------------------------------------------------
CString PSS_PlanFinObject::GetFormattedObject()
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_PlanFinObject::GetUnformattedObject()
{
    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::ConvertFormattedObject(const CString& value, BOOL locateFormat, BOOL emptyWhenZero)
{
    // hasn't changed
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetOrigin(CPoint& point)
{
    const int width  = m_ObjectRect.Width();
    const int height = m_ObjectRect.Height();

    m_ObjectRect.left   = point.x;
    m_ObjectRect.top    = point.y;
    m_ObjectRect.right  = m_ObjectRect.left + width;
    m_ObjectRect.bottom = m_ObjectRect.top  + height;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawObject(CDC* pDC, ZIView* pView)
{
    if (IsObjectSelected() && m_pRectTracker)
    {
        CRect rect = m_ObjectRect;
        pDC->LPtoDP(&rect);
        GetRectTracker()->m_rect = rect;
        m_pRectTracker->Draw(pDC);
    }

    // draw the border if exists
    PSS_Border* pBorder = (PSS_Border*)GetBorder(pView);

    if (pBorder)
        pBorder->DrawBorderRect(pDC, m_ObjectRect);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawEmpty(CDC* pDC, ZIView* pView)
{
    // if printing and the empty style shouldn't be printed, just return
    if (pDC->IsPrinting() && !pView->GetDocument()->GetDocOptions().GetPrintEmptyStyleWhenEmpty())
        return;

    // draw the dotted line without the dotted line style, because it's bugged
    CPen  pen(PS_SOLID, 1, GetColor(pView));
    CPen* pOldPen = pDC->SelectObject(&pen);

    switch (pView->GetDocument()->GetDocOptions().GetEmptyStyle())
    {
        case E_LT_Dotted:
            for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 2)
            {
                pDC->MoveTo(i,     m_ObjectRect.bottom - 2);
                pDC->LineTo(i + 1, m_ObjectRect.bottom - 2);
            }

            break;

        case E_LT_Small:
            for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 8)
            {
                pDC->MoveTo(i,     m_ObjectRect.bottom - 2);
                pDC->LineTo(i + 4, m_ObjectRect.bottom - 2);
            }

            break;

        case E_LT_Solid:
            pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.bottom - 2);
            pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom - 2);

            break;

        case E_LT_Dash:
            for (int i = m_ObjectRect.left; i < m_ObjectRect.right; i += 4)
            {
                pDC->MoveTo(i,     m_ObjectRect.bottom - 2);
                pDC->LineTo(i + 2, m_ObjectRect.bottom - 2);
            }

            break;
    }

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawHiddenSymbol(CDC* pDC)
{
    // draw the object rectangle
    DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_HIDDEN),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_HIDDEN), RT_BITMAP),
                         m_ObjectRect.right,
                         m_ObjectRect.bottom,
                         SRCAND);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawHiddenOnPrintSymbol(CDC* pDC)
{
    // draw the object rectangle
    DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_PRINTER),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PRINTER), RT_BITMAP),
                         m_ObjectRect.right,
                         m_ObjectRect.bottom,
                         SRCAND);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawCalculatedSymbol(CDC* pDC)
{}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawNoteSymbol(CDC* pDC)
{
    // draw the object rectangle
    DrawBoundRect(pDC);

    ShowBitmapFileExtent(MAKEINTRESOURCE(IDB_NOTES),
                         pDC->m_hDC,
                         AfxFindResourceHandle(MAKEINTRESOURCE(IDB_NOTES), RT_BITMAP),
                         m_ObjectRect.right,
                         m_ObjectRect.bottom,
                         SRCAND);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawObjectRectangle(CDC* pDC)
{
    CPen  pen(PS_DOT, 1, defCOLOR_BLACK);
    CPen* pOldPen = pDC->SelectObject(&pen);

    pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawTabOrder(CDC* pDC)
{
    // draw the object
    CFont* pOldFont = pDC->SelectObject(&PSS_PaintResources::GetSmallSystemFont());

    CString buffer;
    std::sprintf(buffer.GetBufferSetLength(7), _T("%g"), GetTabOrder());
    buffer.ReleaseBuffer();

    CSize sizeText;
    sizeText     = pDC->GetTextExtent(buffer, buffer.GetLength());
    sizeText.cx += 10;
    sizeText.cy += 5;

    // calculate the position of the main bubble
    const int middleX = m_ObjectRect.left + (m_ObjectRect.Width() / 2);
    const int bottomY = __max(m_ObjectRect.bottom, sizeText.cy + m_ObjectRect.top);

    CRect rect(middleX - (sizeText.cx / 2),
               m_ObjectRect.top,
               middleX + (sizeText.cx / 2),
               bottomY);

    // draw the object rectangle in blue
    CPen* pOldPen = pDC->SelectObject(&PSS_PaintResources::GetGrayPen());

    pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);

    // after drawing the bubble with the name
    CBrush* pOldBrush = pDC->SelectObject(&PSS_PaintResources::GetGrayBrush());

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(defCOLOR_BLACK);
    pDC->SetTextAlign(0);
    pDC->Rectangle(&rect);
    pDC->DrawText(buffer, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // draw Shadow
    pDC->SelectObject(&PSS_PaintResources::GetBlackPen());
    pDC->MoveTo(m_ObjectRect.right + 1, m_ObjectRect.top    + 1);
    pDC->LineTo(m_ObjectRect.right + 1, m_ObjectRect.bottom + 1);
    pDC->LineTo(m_ObjectRect.left  + 1, m_ObjectRect.bottom + 1);
    pDC->MoveTo(rect.right,             rect.top            + 1);
    pDC->LineTo(rect.right,             rect.bottom);
    pDC->LineTo(rect.left          + 1, rect.bottom);

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldFont);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawBoundRect(CDC* pDC)
{
    CPen  pen(PS_DOT, 1, defCOLOR_GRAY);
    CPen* pOldPen = pDC->SelectObject(&pen);

    pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->SelectObject(pOldPen);

    DrawRightCorner(pDC);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawFillObject(CDC* pDC, ZIView* pView)
{
    COLORREF color = GetFillColor(pView);

    if (color != -1)
    {
        CPen  pen(PS_SOLID, 1, color);
        CPen* pOldPen = pDC->SelectObject(&pen);

        CBrush  brush(color);
        CBrush* pOldBrush = pDC->SelectObject(&brush);

        pDC->Rectangle(&m_ObjectRect);
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
    }
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DisplayCodeName(CDC* pDC, ZIView* pView, BOOL display, CWnd* pWnd)
{
    // draw the object
    CFont* pOldFont = pDC->SelectObject(&PSS_PaintResources::GetSmallSystemFont());

    CSize sizeText;
    sizeText     = pDC->GetTextExtent(GetObjectName(), GetObjectName().GetLength());
    sizeText.cx += 10;
    sizeText.cy += 5;

    // calculate the position of the main bubble
    const int middleX = m_ObjectRect.left + (m_ObjectRect.Width() / 2);
    const int topY    = m_ObjectRect.top  - 15;

    CRect rect(middleX - (sizeText.cx / 2),
               topY    -  sizeText.cy,
               middleX + (sizeText.cx / 2),
               topY);

    // draw the bubble
    if (display)
    {
        DrawObject(pDC, pView);

        // draw the object rectangle in blue
        CPen* pOldPen = pDC->SelectObject(&PSS_PaintResources::GetBluePen());

        pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
        pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
        pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
        pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
        pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);

        // after drawing the bubble with the name
        CBrush* pOldBrush = pDC->SelectObject(&PSS_PaintResources::GetLtBlueBrush());

        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(GetFont(pView)->GetFontColor());
        pDC->SetTextAlign(0);
        pDC->Rectangle(&rect);
        pDC->DrawText(GetObjectName(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // draw small bubble
        CRect bigElipseRect  (0, 0, 12, 6);
        CRect smallElipseRect(0, 0, 8, 4);

        bigElipseRect.OffsetRect(middleX - 6, topY + 2);
        pDC->Ellipse(&bigElipseRect);

        smallElipseRect.OffsetRect(middleX - 4, topY + 10);
        pDC->Ellipse(&smallElipseRect);

        // draw shadow
        pDC->SelectObject(&PSS_PaintResources::GetBlackPen());
        pDC->MoveTo(m_ObjectRect.right + 1, m_ObjectRect.top    + 1);
        pDC->LineTo(m_ObjectRect.right + 1, m_ObjectRect.bottom + 1);
        pDC->LineTo(m_ObjectRect.left  + 1, m_ObjectRect.bottom + 1);
        pDC->MoveTo(rect.right,             rect.top            + 1);
        pDC->LineTo(rect.right,             rect.bottom);
        pDC->LineTo(rect.left          + 1, rect.bottom);

        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
    }
    else
    {
        CRect regionRect;
        regionRect.left   = __min(rect.left,   m_ObjectRect.left)   - 5;
        regionRect.right  = __max(rect.right,  m_ObjectRect.right)  + 5;
        regionRect.top    = __min(rect.top,    m_ObjectRect.top)    - 5;
        regionRect.bottom = __max(rect.bottom, m_ObjectRect.bottom) + 5;
        pDC->LPtoDP(&regionRect);

        pWnd->InvalidateRect(&regionRect);
        pWnd->UpdateWindow();
    }

    pDC->SelectObject(pOldFont);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::InvalidateObjectRect(CDC* pDC, CWnd* pWnd, CRect* pRect)
{
    if (!pRect)
    {
        CRect objRect(m_ObjectRect);
        pDC->LPtoDP(&objRect);
        pWnd->InvalidateRect(&objRect);
    }
    else
    {
        pDC->LPtoDP(pRect);
        pWnd->InvalidateRect(pRect);
    }
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::ShowColorForNumber(CDC* pDC, ZIView* pView)
{
    // draw the object
    DrawObject(pDC, pView);

    // draw the object rectangle in blue
    CPen* pOldPen = pDC->SelectObject(&PSS_PaintResources::GetRedPen());

    pDC->MoveTo(m_ObjectRect.left,  m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.bottom);
    pDC->LineTo(m_ObjectRect.right, m_ObjectRect.top);
    pDC->LineTo(m_ObjectRect.left,  m_ObjectRect.top);

    // draw shadow
    pDC->SelectObject(&PSS_PaintResources::GetBlackPen());
    pDC->MoveTo(m_ObjectRect.right + 1, m_ObjectRect.top    + 1);
    pDC->LineTo(m_ObjectRect.right + 1, m_ObjectRect.bottom + 1);
    pDC->LineTo(m_ObjectRect.left  + 1, m_ObjectRect.bottom + 1);

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::ShowObjectName(CDC* pDC)
{
    CFont* pOldFont = pDC->SelectObject(&PSS_PaintResources::GetSmallSystemFont());

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(defCOLOR_BLACK);
    pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
    pDC->TextOut(m_ObjectRect.left, m_ObjectRect.bottom, GetObjectName());
    pDC->SelectObject(pOldFont);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SizePositionHasChanged()
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_MOVEOBJECTINORDER, 0, LPARAM(this));
}
//---------------------------------------------------------------------------
PSS_Font* PSS_PlanFinObject::GetFont(ZIView* pView)
{
    ZDDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        // return the specific Font assigned directly
        if (m_hFont != g_NoFontDefined)
            return pDoc->GetFontManager().GetFont(m_hFont);

        if (!pDoc->GetStyleManager().GetStyle(m_hStyle))
            return NULL;

        // return the Font of the style
        return pDoc->GetFontManager().GetFont(pDoc->GetStyleManager().GetStyle(m_hStyle)->GetFontHandle());
    }

    return NULL;
}
//---------------------------------------------------------------------------
COLORREF PSS_PlanFinObject::GetColor(ZIView* pView)
{
    ZDDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        // if the object has changed
        if (HasBeenChanged())
            // if the color is red, change and draw with blue color
            return (m_Color == defCOLOR_RED) ? defCOLOR_BLUE : defCOLOR_RED;

        // return the assigned color if there is one defined
        if (m_Color != -1)
            return m_Color;

        // otherwise return the font color defined in the font or in the style
        return (GetFont(pView)) ? GetFont(pView)->GetFontColor() : defCOLOR_BLACK;
    }

    return -1;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::SetStyle(PSS_Style::Handle value)
{
    m_hStyle = value;

    // remove the no font object format attribute
    SetFont(g_NoFontDefined);

    // no Color
    SetColor(-1);

    // no Fill Color
    SetFillColor(-1);

    // no Justification
    SetJustify(g_NoAlignement);

    // no Border
    SetBorder(NULL);
}
//---------------------------------------------------------------------------
CSize PSS_PlanFinObject::GetTextExtent(CDC* pDC, const CString& str, int angle)
{
    const CSize textSize = pDC->GetTextExtent(str, str.GetLength());

    if (!angle)
        return textSize;

    // angle must be positive
    while (angle < 0)
        angle += 3600;

    // convert in radian
    const double radianAngle = (double(angle) * std::atan(1.0) * 4) / 1800;

    CSize modifiedTextSize;
    modifiedTextSize.cx = std::abs(int(double(textSize.cx) * std::cos(radianAngle))) + std::abs(int(double(textSize.cy) * std::sin(radianAngle)));
    modifiedTextSize.cy = std::abs(int(double(textSize.cx) * std::sin(radianAngle))) + std::abs(int(double(textSize.cy) * std::cos(radianAngle)));

    return modifiedTextSize;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::GetTextExtentOrg(CDC* pDC, const CString& str, CSize& size, CPoint& org, int angle)
{
    // angle must be positive
    ASSERT(angle >= 0);

    const CSize textSize = pDC->GetTextExtent(str, str.GetLength());

    if (!angle)
    {
        size  = textSize;
        org.x = org.y = 0;

        return;
    }

    // convert in radian
    const double radianAngle = (double(angle) * std::atan(1.0) * 4) / 1800;

    // calculate the text size
    size.cx = std::abs(int(double(textSize.cx) * std::cos(radianAngle))) + std::abs(int(double(textSize.cy) * std::sin(radianAngle)));
    size.cy = std::abs(int(double(textSize.cx) * std::sin(radianAngle))) + std::abs(int(double(textSize.cy) * std::cos(radianAngle)));

    // calculate the text origin
    if (angle < 900)
    {
        org.y = 0;
        org.x = std::abs(int(double(textSize.cy) * std::sin(radianAngle)));
    }
    else
    if (angle < 1800)
    {
        org.y = std::abs(int(double(textSize.cy) * std::cos(radianAngle)));
        org.x = size.cx;
    }
    else
    if (angle < 2700)
    {
        org.y = size.cy;
        org.x = std::abs(int(double(textSize.cx) * std::sin(radianAngle - 900)));
    }
    else
    {
        org.y = std::abs(int(double(textSize.cx) * std::cos(radianAngle - 900)));
        org.x = 0;
    }
}
//---------------------------------------------------------------------------
COLORREF PSS_PlanFinObject::GetFillColor(ZIView* pView) const
{
    if (m_FillColor != -1)
        return m_FillColor;

    // get the style back color
    return (pView->GetDocument()->GetStyleManager().GetStyle(m_hStyle) ?
            pView->GetDocument()->GetStyleManager().GetStyle(m_hStyle)->GetBackColor() : defCOLOR_WHITE);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::MoveObject(CPoint& point, BOOL relativeMove)
{
    if (relativeMove)
        m_ObjectRect.OffsetRect(point);
    else
    {
        // save the object width and height
        const int width  = m_ObjectRect.Width();
        const int height = m_ObjectRect.Height();

        // assign new starting point
        m_ObjectRect.left = point.x;
        m_ObjectRect.top  = point.y;

        // assign the size
        m_ObjectRect.right  = m_ObjectRect.left + width;
        m_ObjectRect.bottom = m_ObjectRect.top  + height;
    }
}
//---------------------------------------------------------------------------
const PSS_Border* PSS_PlanFinObject::GetBorder(ZIView* pView) const
{
    if (m_pBorder)
        return m_pBorder;

    // get the style back color
    return (pView->GetDocument()->GetStyleManager().GetStyle(m_hStyle) ?
            pView->GetDocument()->GetStyleManager().GetStyle(m_hStyle)->GetBorder() : NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_PlanFinObject::AddNotes(const CString& comment, const CString& userName)
{
    if (!m_pNotes)
        m_pNotes = new ZBNotes;

    m_pNotes->SetComment (comment);
    m_pNotes->SetUsername(userName);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DeleteNotes()
{
    if (m_pNotes)
        delete m_pNotes;

    m_pNotes = NULL;
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::Serialize(CArchive& ar)
{
    ZDDocument* pDoc = dynamic_cast<ZDDocument*>(ar.m_pDocument);

    // increment the element counter
    if (pDoc)
        pDoc->SetCurrentElement(pDoc->GetCurrentElement() + 1);

    if (ar.IsStoring())
    {
        // write the elements
        ar << m_ObjectRect;
        ar << CString(GetObjectName());
        ar << WORD(m_Page);

        // to keep the serialization as before, do the following
        ar << WORD(m_FormatType);
        ar << WORD(m_IsVisible);
        ar << WORD(m_MustBePrinted);

        // version 2
        ar << m_Color;
        ar << m_FillColor;

        // version 3
        ar << m_GroupNumber;

        // version 4
        ar << m_hFont;
        ar << WORD(m_hStyle);
        ar << WORD(m_Angle);
        ar << WORD(m_EmptyStyle);
        ar << m_TabOrder;

        // serialize the font
        ar << m_pBorder;

        // serialize the default value
        ar << WORD(m_DefaultValue);

        // check if template
        if (pDoc && pDoc->GetDocumentStamp().GetFileType() == PSS_Stamp::IE_FD_TemplateType && !GetDefaultValue() && !GetIsStatic())
            m_IsEmpty = TRUE;

        ar << WORD(m_IsEmpty);
        ar << WORD(m_ReadOnly); // version 14
        ar << m_pNotes;         // version 14
        ar << m_UserHelp;       // version 17
    }
    else
    {
        // read the elements
        ar >> m_ObjectRect;

        CString str;
        ar >> str;
        SetObjectName(str);

        ASSERT(!m_strObjName.IsEmpty());

        PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);
        WORD              wValue;

        // if before Version 4 read the FontType
        // And assign the font
        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() < 4)
            ar >> wValue;

        ar >> wValue;
        m_Page = int(wValue);
        ASSERT(m_Page >= 0);

        ar >> wValue;

        // to keep the serialization as before, do the following
        m_FormatType = EFormatType(wValue);

        if (!pBaseDoc)
            return;

        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 1)
        {
            ar >> wValue;
            m_IsVisible = int(wValue);

            ar >> wValue;
            m_MustBePrinted = int(wValue);
        }

        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 2)
        {
            ar >> m_Color;
            ar >> m_FillColor;
        }

        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 3)
            ar >> m_GroupNumber;

        // version 4
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 4)
        {
            ar >> m_hFont;

            ar >> wValue;
            m_hStyle = int(wValue);

            ar >> wValue;
            m_Angle = int(wValue);
        }

        // version 5
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            ar >> wValue;
            m_EmptyStyle = ELineType(wValue);
            ar >> m_TabOrder;
        }

        // version 7
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 7)
            // deserialize the font
            ar >> m_pBorder;

        // version 8
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 8)
        {
            // deserialize the default value
            ar >> wValue;
            m_DefaultValue = BOOL(wValue);
        }

        // version 12
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 12)
        {
            // deserialize the empty value
            ar >> wValue;
            m_IsEmpty = BOOL(wValue);
        }

        // version 14
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 14)
        {
            // deserialize the read-only value
            ar >> wValue;
            m_ReadOnly = BOOL(wValue);
            ar >> (CObject*&)m_pNotes;
        }

        // version 17
        if (pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 17)
            ar >> m_UserHelp;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PlanFinObject::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PlanFinObject::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_PlanFinObject::OnAngleChanged(ZDDocument* pDoc)
{
    // does nothing. Each object must implement themselve this method
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::RotateFont(ZDDocument* pDoc)
{
    if (pDoc)
    {
        PSS_Font::Handle hFont;

        if (GetFont() != g_NoFontDefined)
            hFont = GetFont();
        else
            hFont = (pDoc->GetStyleManager().GetStyle(m_hStyle) ? pDoc->GetStyleManager().GetStyle(m_hStyle)->GetFontHandle() : NULL);

        if (hFont)
            SetFont(pDoc->GetFontManager().RotateFont(hFont, m_Angle));
    }
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DrawRightCorner(CDC* pDC)
{
    CPen* pOldPen = pDC->SelectObject(&PSS_PaintResources::GetBlackPen());

    // draw small shadow
    pDC->MoveTo(m_ObjectRect.right + 1, m_ObjectRect.bottom - 4);
    pDC->LineTo(m_ObjectRect.right + 1, m_ObjectRect.bottom + 1);
    pDC->LineTo(m_ObjectRect.right - 4, m_ObjectRect.bottom + 1);
    pDC->MoveTo(m_ObjectRect.right + 2, m_ObjectRect.bottom - 3);
    pDC->LineTo(m_ObjectRect.right + 2, m_ObjectRect.bottom + 2);
    pDC->LineTo(m_ObjectRect.right - 3, m_ObjectRect.bottom + 2);
    pDC->MoveTo(m_ObjectRect.right + 1, m_ObjectRect.bottom - 4);
    pDC->LineTo(m_ObjectRect.right - 4, m_ObjectRect.bottom + 1);

    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::AssignFont()
{}
//---------------------------------------------------------------------------
void PSS_PlanFinObject::DCDrawMoveObject(CDC* pDC)
{
    TRACE(_T("DRAW DC"));

    CBrush brush;
    CPen   pen;

    brush.CreateHatchBrush(HS_BDIAGONAL, defCOLOR_BLACK);
    pen.CreatePen(PS_SOLID, 1, defCOLOR_BLACK);

    CBrush* pOldBrush = pDC->SelectObject(&brush);
    CPen*   pOldPen = pDC->SelectObject(&pen);

    CRect rect;
    GetRectTop(&rect);
    pDC->Rectangle(&rect);

    GetRectBottom(&rect);
    pDC->Rectangle(&rect);

    GetRectLeft(&rect);
    pDC->Rectangle(&rect);

    GetRectRight(&rect);
    pDC->Rectangle(&rect);

    pDC->FrameRect(m_ObjectRect, &brush);
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
}
//---------------------------------------------------------------------------
