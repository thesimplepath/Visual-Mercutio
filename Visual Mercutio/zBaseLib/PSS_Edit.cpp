/****************************************************************************
 * ==> PSS_Edit ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several edit components                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Edit.h"

// processsoft
#include "PSS_PlanFinObjects.h"
#include "PSS_Document.h"
#include "PSS_PLFNMaskString.h"
#include "PSS_PLFNMultiColumn.h"
#include "PSS_Interfaces.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
const int g_MinEditWidth  = 150;
const int g_MinEditHeight = 20;
//---------------------------------------------------------------------------
// PSS_Edit
//---------------------------------------------------------------------------
PSS_Edit::PSS_Edit() :
    m_pParentWnd(NULL),
    m_pSpecialHelp(NULL),
    m_pEditedObj(NULL),
    m_pDoc(NULL),
    m_pFieldRepository(NULL),
    m_Save(FALSE),
    m_GoNext(FALSE),
    m_AutoCalculateOption(FALSE),
    m_GoNextEditOption(FALSE),
    m_ReadOnly(FALSE),
    m_IsSorted(FALSE)
{}
//---------------------------------------------------------------------------
PSS_Edit::~PSS_Edit()
{
    if (m_pSpecialHelp)
        delete m_pSpecialHelp;
}
//---------------------------------------------------------------------------
void PSS_Edit::PreCreateEdit(BOOL                 designerMode,
                             CWnd*                pParentWnd,
                             CDC*                 pDC,
                             PSS_Document*        pDoc,
                             PSS_PlanFinObject*   pEditedObj,
                             PSS_FieldRepository* pFieldRepository,
                             BOOL                 autoCalculateOption,
                             BOOL                 goNextEditOption)
{
    m_pParentWnd          = pParentWnd;
    m_pEditedObj          = pEditedObj;
    m_pDoc                = pDoc;
    m_pFieldRepository    = pFieldRepository;
    m_AutoCalculateOption = autoCalculateOption;
    m_GoNextEditOption    = goNextEditOption;

    PSS_HistoryField* pField = NULL;

    if (m_pFieldRepository && (pField = m_pFieldRepository->FindFieldHistory(m_pEditedObj->GetObjectName())))
        m_ReadOnly = pField->IsReadOnly();

    PSS_FieldObjectDefinition* pObjectDefinition = NULL;

    if (m_pFieldRepository && (pObjectDefinition = m_pFieldRepository->FindField(m_pEditedObj->GetObjectName())))
        m_IsSorted = pObjectDefinition->IsSorted();

    AfxGetMainWnd()->SendMessageToDescendants(UM_NOTIFY_OBJECTSELECTED,
                                              UM_NOTIFY_OBJECTSELECTED,
                                              LPARAM(m_pEditedObj));

    m_Rect = CheckBounds(pDC, pParentWnd, m_pEditedObj->GetClientRect());

    if (!m_ReadOnly)
        CreateSpecialHelp(designerMode);
}
//---------------------------------------------------------------------------
CRect PSS_Edit::CheckBounds(CDC* pDC, CWnd *pParentWnd, const CRect& rect)
{
    m_GoNext = FALSE;
    SetModify(TRUE);

    // translate the rectangle in device coordinates
    CRect bounds(rect);

    // check if the rectangle is not too small. If necessary change it before creating the edit box
    if (bounds.Width() < g_MinEditWidth)
        bounds.right = bounds.left + g_MinEditWidth;

    if (bounds.Height() < g_MinEditHeight)
        bounds.top = bounds.bottom - g_MinEditHeight;

    pDC->LPtoDP(&bounds);

    return bounds;
}
//---------------------------------------------------------------------------
void PSS_Edit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{}
//---------------------------------------------------------------------------
void PSS_Edit::DestroyEdit()
{}
//---------------------------------------------------------------------------
CStringArray* PSS_Edit::GetArrayOfValues()
{
    // if global historic field value manager is defined, try to add the field value there
    if (m_pFieldRepository && m_pFieldRepository->FindFieldHistory(m_pEditedObj->GetObjectName()))
        return m_pFieldRepository->GetFieldHistory(m_pEditedObj->GetObjectName());
    else
    {
        if (m_pEditedObj->IsMemberOfMultiColumn())
        {
            // force the read only for member of multi-column field
            m_ReadOnly = TRUE;

            return (CStringArray*)&(m_pEditedObj->GetColumn()->GetValueArray());
        }
        else
            // if not found nor does not exists
            return m_pDoc->GetHistoryValueManager().GetFieldHistory(m_pEditedObj->GetObjectName());
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Edit::AddToHistoric(const CString& str)
{
    // if global historic field value manager is defined, try to add the field value there
    if (m_pFieldRepository && m_pFieldRepository->FindFieldHistory(m_pEditedObj->GetObjectName()))
    {
        // field exists in the global histo value and is not read only
        if (!m_ReadOnly)
            m_pFieldRepository->AddFieldHistoryValue(m_pEditedObj->GetObjectName(), str);

        return;
    }

    // if not found nor does not exists, add it to the local file
    m_pDoc->GetHistoryValueManager().AddFieldHistoryValue(m_pEditedObj->GetObjectName(), str);
}
//---------------------------------------------------------------------------
void PSS_Edit::LoadFromHistoric(CComboBox& combobox)
{
    CStringArray* pValueArray = GetArrayOfValues();

    // no values found neither in global historic manager nor in local historic manager
    if (!pValueArray)
        return;

    const register int valueCount = pValueArray->GetSize();

    for (register int i = 0; i < valueCount; ++i)
        if (!pValueArray->GetAt(i).IsEmpty())
            combobox.AddString(pValueArray->GetAt(i));
}
//---------------------------------------------------------------------------
void PSS_Edit::CreateSpecialHelp(BOOL designer)
{
    ASSERT(m_pEditedObj);

    if (m_pEditedObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTime)))
    {
        if (designer)
            m_pSpecialHelp = new PSS_SpecialHelpDateDesignerWnd();
        else
            m_pSpecialHelp = new PSS_SpecialHelpDateWnd();
    }
    else
    {
        PSS_PLFNLong* pLong = dynamic_cast<PSS_PLFNLong*>(m_pEditedObj);

        if (pLong)
        {
            if (pLong->GetAssociations().GetCount())
            {
                if (designer)
                    m_pSpecialHelp = new PSS_SpecialHelpNumberScenarioDesignerWnd();
                else
                    m_pSpecialHelp = new PSS_SpecialHelpNumberScenarioWnd();
            }
            else
            if (designer)
                m_pSpecialHelp = new PSS_SpecialHelpNumberDesignerWnd();
            else
                m_pSpecialHelp = new PSS_SpecialHelpNumberWnd();
        }
        else
        if (designer)
            m_pSpecialHelp = new PSS_SpecialHelpDefaultDesignerWnd();
        else
            m_pSpecialHelp = new PSS_SpecialHelpDefaultWnd();
    }

    // create the special helper
    m_pSpecialHelp->Create(m_pParentWnd, &m_Rect, m_pEditedObj, m_AutoCalculateOption);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_StrEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_StrEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_StrEdit
//---------------------------------------------------------------------------
PSS_StrEdit::PSS_StrEdit(BOOL multiLine, int maxChar) :
    PSS_Edit(),
    PSS_DragEdit(),
    m_MaxChar(maxChar),
    m_MultiLine(multiLine)
{}
//---------------------------------------------------------------------------
PSS_StrEdit::~PSS_StrEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    // because of multiple inheritance
    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_StrEdit::Create(BOOL                 designerMode,
                         CWnd*                pParentWnd,
                         CDC*                 pDC,
                         PSS_Document*        pDoc,
                         PSS_PlanFinObject*   pEditedObj,
                         PSS_FieldRepository* pFieldRepository,
                         BOOL                 autoCalculateOption,
                         BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style;

    if (m_MultiLine)
        style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE;
    else
        style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (m_ReadOnly)
        style |= ES_READONLY;

    if (!PSS_DragEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    // initialize drag & drop facilities
    PSS_DragEdit::Init();

    SetWindowText(m_pEditedObj->GetFormattedObject());
    SetSel(0, -1);
    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_StrEdit::DestroyEdit()
{
    // save only if required
    if (m_Save)
    {
        CString strTemp;

        GetWindowText(strTemp);
        m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_StrEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    // check if necessary to check the length, do not check if backspace
    if (m_MaxChar > 0 && nChar != 0x08)
    {
        CString strTemp;
        GetWindowText(strTemp);

        // if the maximum char was exceeded, play a sound and ignore the typed char
        if (strTemp.GetLength() + 1 > m_MaxChar)
        {
            ::MessageBeep(MB_ICONEXCLAMATION);
            return;
        }
    }

    PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_StrEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
    DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_NumEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_NumEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_NumEdit
//---------------------------------------------------------------------------
PSS_NumEdit::PSS_NumEdit() :
    PSS_Edit(),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_NumEdit::~PSS_NumEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_NumEdit::Create(BOOL                 designerMode,
                         CWnd*                pParentWnd,
                         CDC*                 pDC,
                         PSS_Document*        pDoc,
                         PSS_PlanFinObject*   pEditedObj,
                         PSS_FieldRepository* pFieldRepository,
                         BOOL                 autoCalculateOption,
                         BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (m_ReadOnly)
        style |= ES_READONLY;

    if (!PSS_DragEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    SetWindowText(m_pEditedObj->GetFormattedObject());

    // initialize drag & drop facilities
    PSS_DragEdit::Init();

    SetSel(0, -1);
    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_NumEdit::DestroyEdit()
{
    // save only if required
    if (m_Save)
    {
        CString strTemp;
        GetWindowText(strTemp);

        if (strTemp.IsEmpty())
            m_pEditedObj->EmptyObject();
        else
            m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);

        if (m_AutoCalculateOption)
            AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//----------------------------------------------------------------------------
void PSS_NumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    // check the char validity
    if (!::isdigit(nChar) &&
        nChar != '.'      &&
        nChar != '-'      &&
        nChar != '+'      &&
        nChar != '\''     &&
        nChar != ','      &&
        nChar != '%'      &&
        nChar != 0x08)
        return;

    PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_NumEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
    DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CalcEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_CalcEdit)
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CalcEdit
//---------------------------------------------------------------------------
PSS_CalcEdit::PSS_CalcEdit() :
    PSS_Edit(),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_CalcEdit::~PSS_CalcEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_CalcEdit::Create(BOOL                 designerMode,
                          CWnd*                pParentWnd,
                          CDC*                 pDC,
                          PSS_Document*        pDoc,
                          PSS_PlanFinObject*   pEditedObj,
                          PSS_FieldRepository* pFieldRepository,
                          BOOL                 autoCalculateOption,
                          BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD;

    if (m_ReadOnly)
        style |= ES_READONLY;

    if (!PSS_DragEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    // initialize drag & drop facilities
    PSS_DragEdit::Init();

    SetFocus();
}
//---------------------------------------------------------------------------
void PSS_CalcEdit::DestroyEdit()
{
    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_CalcEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
    DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TimeEdit, PSS_DragEdit)
    //{{AFX_MSG_MAP(PSS_TimeEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TimeEdit
//---------------------------------------------------------------------------
PSS_TimeEdit::PSS_TimeEdit() :
    PSS_Edit(),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_TimeEdit::~PSS_TimeEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_TimeEdit::Create(BOOL                 designerMode,
                          CWnd*                pParentWnd,
                          CDC*                 pDC,
                          PSS_Document*        pDoc,
                          PSS_PlanFinObject*   pEditedObj,
                          PSS_FieldRepository* pFieldRepository,
                          BOOL                 autoCalculateOption,
                          BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (m_ReadOnly)
        style |= ES_READONLY;

    if (!PSS_DragEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    CString strFormat(_T(" "));

    PSS_PLFNTime* pTime = dynamic_cast<PSS_PLFNTime*>(m_pEditedObj);

    if (pTime && !pTime->IsEmpty())
    {
        std::sprintf(strFormat.GetBuffer(100),
                     _T("%d.%d.%04d"),
                     pTime->GetTime().GetDay(),
                     pTime->GetTime().GetMonth(),
                     pTime->GetTime().GetYear());

        strFormat.ReleaseBuffer();
    }

    SetWindowText((const char*)strFormat);

    // initialize drag & drop facilities
    PSS_DragEdit::Init();

    SetSel(0, -1);
    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_TimeEdit::DestroyEdit()
{
    // save only if required
    while (m_Save)
    {
        CString strTemp;
        GetWindowText(strTemp);

        if (strTemp.IsEmpty())
            m_pEditedObj->EmptyObject();
        else
            m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));

        break;
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_TimeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    // check the char validity
    if (!::isdigit(nChar) && nChar != '.' && nChar != '/' && nChar != 0x08)
        return;

    PSS_DragEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_TimeEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DragEdit::OnKillFocus(pNewWnd);
    DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_StrEditHistoric, PSS_IntelliEdit)
    //{{AFX_MSG_MAP(PSS_StrEditHistoric)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_StrEditHistoric
//---------------------------------------------------------------------------
PSS_StrEditHistoric::PSS_StrEditHistoric(int maxChar) :
    PSS_Edit(),
    PSS_IntelliEdit(),
    m_MaxChar(maxChar)
{}
//---------------------------------------------------------------------------
PSS_StrEditHistoric::~PSS_StrEditHistoric()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_StrEditHistoric::Create(BOOL                 designerMode,
                                 CWnd*                pParentWnd,
                                 CDC*                 pDC,
                                 PSS_Document*        pDoc,
                                 PSS_PlanFinObject*   pEditedObj,
                                 PSS_FieldRepository* pFieldRepository,
                                 BOOL                 autoCalculateOption,
                                 BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (!PSS_IntelliEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    PSS_IntelliEdit::Initialize(GetArrayOfValues());

    CString str = m_pEditedObj->GetFormattedObject();
    SetWindowText(str);

    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_StrEditHistoric::DestroyEdit()
{
    // only if required
    if (m_Save)
    {
        CString strTemp;
        GetWindowText(strTemp);
        m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);

        // keep the historical changes
        AddToHistoric(strTemp);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_StrEditHistoric::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            // go in only if read only on return
            PSS_Edit::SetModify(TRUE);
            SetGoNext(TRUE);
            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            SetGoNext(TRUE);
            DestroyEdit();
            return;

        case 0x1B:
            // on Esc
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    // check if necessary to check the length, do not check if backspace
    if (GetMaxChar() > 0 && nChar != 0x08)
    {
        CString strTemp;
        GetWindowText(strTemp);

        // if the maximum char count was exceeded, play a sound and ignore the typed char
        if (strTemp.GetLength() + 1 > GetMaxChar())
        {
            ::MessageBeep(MB_ICONEXCLAMATION);
            return;
        }
    }

    PSS_IntelliEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_StrEditHistoric::OnKillFocus(CWnd* pNewWnd)
{
    PSS_IntelliEdit::OnKillFocus(pNewWnd);

    if (!HasFocus())
        DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_NumEditHistoric, PSS_IntelliEdit)
    //{{AFX_MSG_MAP(PSS_NumEditHistoric)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_NumEditHistoric
//---------------------------------------------------------------------------
PSS_NumEditHistoric::PSS_NumEditHistoric() :
    PSS_Edit(),
    PSS_IntelliEdit()
{}
//---------------------------------------------------------------------------
PSS_NumEditHistoric::~PSS_NumEditHistoric()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_NumEditHistoric::Create(BOOL                 designerMode,
                                 CWnd*                pParentWnd,
                                 CDC*                 pDC,
                                 PSS_Document*        pDoc,
                                 PSS_PlanFinObject*   pEditedObj,
                                 PSS_FieldRepository* pFieldRepository,
                                 BOOL                 autoCalculateOption,
                                 BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (!PSS_IntelliEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    PSS_IntelliEdit::Initialize(GetArrayOfValues());

    CString str = m_pEditedObj->GetFormattedObject();
    SetWindowText(str);

    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_NumEditHistoric::DestroyEdit()
{
    // only if required
    if (m_Save)
    {
        CString strTemp;
        GetWindowText(strTemp);

        if (strTemp.IsEmpty())
            m_pEditedObj->EmptyObject();
        else
        {
            // keep the historical changes
            AddToHistoric(strTemp);
            m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);
        }

        // notify the application that a number changed
        if (m_AutoCalculateOption)
            AfxGetMainWnd()->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_NumEditHistoric::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            // go in only if read only on return
            PSS_Edit::SetModify(TRUE);
            SetGoNext(TRUE);
            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            SetGoNext(TRUE);
            DestroyEdit();
            return;

        case 0x1B:
            // on Esc
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    // check the validity of the char
    if (!::isdigit(nChar) && nChar != '.' && nChar != ',' && nChar != '\'' && nChar != '%' && nChar != 0x08)
        return;

    PSS_IntelliEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_NumEditHistoric::OnKillFocus(CWnd* pNewWnd)
{
    PSS_IntelliEdit::OnKillFocus(pNewWnd);

    if (!HasFocus())
        DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FieldNameEdit, PSS_IntelliEdit)
    //{{AFX_MSG_MAP(PSS_FieldNameEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FieldNameEdit
//---------------------------------------------------------------------------
PSS_FieldNameEdit::PSS_FieldNameEdit(int maxChar) :
    PSS_Edit(),
    PSS_IntelliEdit(),
    m_MaxChar(maxChar)
{}
//---------------------------------------------------------------------------
PSS_FieldNameEdit::~PSS_FieldNameEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_FieldNameEdit::Create(BOOL                 designerMode,
                               CWnd*                pParentWnd,
                               CDC*                 pDC,
                               PSS_Document*        pDoc,
                               PSS_PlanFinObject*   pEditedObj,
                               PSS_FieldRepository* pFieldRepository,
                               BOOL                 autoCalculateOption,
                               BOOL                 goNextEditOption)
{
    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (!PSS_IntelliEdit::Create(style, m_Rect, pParentWnd, 0))
        return;

    PSS_IntelliEdit::Initialize(pDoc->GetObjectFieldNameArray());

    SetWindowText(m_pEditedObj->GetObjectName());
    SetSel(0, -1);
    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_FieldNameEdit::DestroyEdit()
{
    // save only if required
    if (m_Save)
    {
        CString strTemp;
        GetWindowText(strTemp);
        m_pEditedObj->SetObjectName(strTemp);

        // check field name
        m_pDoc->CheckMultiColumnMemberField(m_pEditedObj);
        m_pDoc->AddFieldNameInObectArray(strTemp);

        // save only one time
        m_Save = FALSE;
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_FieldNameEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    PSS_IntelliEdit::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_FieldNameEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_IntelliEdit::OnKillFocus(pNewWnd);

    // check if the control still have the focus, if not, destroy the edit
    if (!HasFocus())
        DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MaskEdit, PSS_MaskEditBase)
    //{{AFX_MSG_MAP(PSS_MaskEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MaskEdit
//---------------------------------------------------------------------------
PSS_MaskEdit::PSS_MaskEdit() :
    PSS_Edit(),
    PSS_MaskEditBase()
{}
//---------------------------------------------------------------------------
PSS_MaskEdit::~PSS_MaskEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_MaskEdit::Create(BOOL                 designerMode,
                          CWnd*                pParentWnd,
                          CDC*                 pDC,
                          PSS_Document*        pDoc,
                          PSS_PlanFinObject*   pEditedObj,
                          PSS_FieldRepository* pFieldRepository,
                          BOOL                 autoCalculateOption,
                          BOOL                 goNextEditOption)
{
    PSS_PLFNMaskString* pMaskString = dynamic_cast<PSS_PLFNMaskString*>(m_pEditedObj);

    if (!pMaskString)
        return;

    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

    if (m_ReadOnly)
        style |= ES_READONLY;

    if (!PSS_MaskEditBase::Create(style, m_Rect, pParentWnd, 0))
        return;

    PSS_MaskEditBase::Init(pMaskString->GetMask(), m_pEditedObj->GetUnformattedObject());
    SetSel(0, -1);
    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();
}
//---------------------------------------------------------------------------
void PSS_MaskEdit::DestroyEdit()
{
    // save only if required
    if (m_Save)
    {
        CString strTemp = GetData();
        m_pEditedObj->ConvertFormattedObject(strTemp, FALSE);

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_MaskEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    PSS_MaskEditBase::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_MaskEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_MaskEditBase::OnKillFocus(pNewWnd);
    DestroyEdit();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_MultiColumnEdit, PSS_GridCtrl)
    //{{AFX_MSG_MAP(PSS_MultiColumnEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_MultiColumnEdit
//---------------------------------------------------------------------------
PSS_MultiColumnEdit::PSS_MultiColumnEdit() :
    PSS_Edit(),
    PSS_GridCtrl(),
    m_Cx(0),
    m_Edit(-1),
    m_ColumnsBuilt(FALSE),
    m_StartEditCell(false)
{}
//---------------------------------------------------------------------------
PSS_MultiColumnEdit::~PSS_MultiColumnEdit()
{
    if (::IsWindow(GetSafeHwnd()))
        HideCaret();

    PSS_Edit::~PSS_Edit();
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::Create(BOOL                 designerMode,
                                 CWnd*                pParentWnd,
                                 CDC*                 pDC,
                                 PSS_Document*        pDoc,
                                 PSS_PlanFinObject*   pEditedObj,
                                 PSS_FieldRepository* pFieldRepository,
                                 BOOL                 autoCalculateOption,
                                 BOOL                 goNextEditOption)
{
    if (!pEditedObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNMultiColumn)))
        return;

    PreCreateEdit(designerMode,
                  pParentWnd,
                  pDC,
                  pDoc,
                  pEditedObj,
                  pFieldRepository,
                  autoCalculateOption,
                  goNextEditOption);

    DWORD style = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;

    // if not read only, allow edit labels
    if (!m_ReadOnly)
        style |= LVS_EDITLABELS;

    if (!PSS_GridCtrl::Create(style, m_Rect, pParentWnd, 0))
        return;

    // set the extended styles
    SetExtendedStyle(LVS_EX_GRIDLINES);

    PSS_MultiColumnEdit::BuildColumns();
    PSS_MultiColumnEdit::FillControl();

    ShowWindow(SW_SHOW);
    SetFocus();
    ShowCaret();

    // initialize the cell edition flag
    m_StartEditCell = false;
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::DestroyEdit()
{
    // save only if required
    if (m_Save)
    {
        // get the size of each header
        CHeaderCtrl* pHeader = GetHeaderCtrl();
        ASSERT(pHeader);

        PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(m_pEditedObj);
        ASSERT(pMultiColumn);

        const int colCount = pHeader->GetItemCount();

        // saves the column width
        for (int i = 0; i < colCount; ++i)
        {
            PSS_FieldColumn* pColumn = pMultiColumn->GetColumnAt(i);

            if (pColumn)
                pColumn->SetWidth(GetColumnWidth(i));
        }

        // to notify the view that the field changed, pass the adress of the object,
        // thus the routine that proceed the message can know which object has changed
        AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_CHANGE, 0, LPARAM(m_pEditedObj));

        // save only one time
        m_Save = FALSE;

        if (m_GoNext)
            AfxGetMainWnd()->SendMessageToDescendants(ID_FIELD_EDITNEXT, 0, LPARAM(m_pEditedObj));
    }

    // hide the window, the DestroyWindow() function will be used in the destructor
    ShowWindow(SW_HIDE);

    if (m_pSpecialHelp)
        m_pSpecialHelp->ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::OnBeginLabelEdit(int item, int subItem)
{
    m_StartEditCell = true;
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::OnEndLabelEdit(LPCSTR pText, int item, int subItem)
{
    // Set the object value
    ((PSS_PLFNMultiColumn*)m_pEditedObj)->SetCellValue(subItem, item, pText);
    m_StartEditCell = false;
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
        case 0x0D:
            PSS_Edit::SetModify(TRUE);

            if (m_GoNextEditOption)
                m_GoNext = TRUE;

            DestroyEdit();
            return;

        case 0x09:
            // tab key was pressed, focus next component
            PSS_Edit::SetModify(TRUE);
            m_GoNext = TRUE;
            DestroyEdit();
            return;

        case 0x1B:
            PSS_Edit::SetModify(FALSE);
            DestroyEdit();
            return;
    }

    PSS_GridCtrl::OnChar(nChar, nRepCnt, nFlags);
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::OnKillFocus(CWnd* pNewWnd)
{
    PSS_GridCtrl::OnKillFocus(pNewWnd);

    // only if not editing
    if (!m_StartEditCell)
        DestroyEdit();
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(m_pEditedObj);
    ASSERT(pMultiColumn);

    if (pMultiColumn->GetColumnCount() > 0)
    {
        LV_COLUMN lvColumn;
        lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvColumn.fmt  = LVCFMT_LEFT;

        // set up columns
        for (std::size_t i = 0; i < pMultiColumn->GetColumnCount(); i++)
        {
            PSS_FieldColumn* pColumn = pMultiColumn->GetColumnAt(i);

            if (pColumn)
            {
                // get the width
                lvColumn.cx = pColumn->GetWidth();

                // get the column name
                int     len     = pColumn->GetHeaderName().GetLength();
                CString temp    = pColumn->GetHeaderName();
                TCHAR*  pBuffer = NULL;

                try
                {
                    pBuffer = new TCHAR[len + 1];

                    std::strcpy(pBuffer, temp.GetBuffer(len));
                    temp.ReleaseBuffer();

                    lvColumn.pszText = pBuffer;

                    // insert column
                    InsertColumn(i, &lvColumn);
                }
                catch (...)
                {
                    if (pBuffer)
                        delete[] pBuffer;

                    throw;
                }

                if (pBuffer)
                    delete[] pBuffer;
            }
        }
    }

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::FillControl()
{
    PSS_PLFNMultiColumn* pMultiColumn = dynamic_cast<PSS_PLFNMultiColumn*>(m_pEditedObj);
    ASSERT(pMultiColumn);

    if (pMultiColumn->GetColumnCount() <= 0)
        return;

    const std::size_t rowCount = pMultiColumn->GetColumnAt(0)->GetValueCount();

    // fill all columns with all values, set up columns
    for (std::size_t i = 0; i < rowCount; ++i)
    {
        CStringArray values;
        pMultiColumn->GetRowValues(values, i);

        std::unique_ptr<PSS_GridCtrl::IItemInfo> pItemInfo(new PSS_GridCtrl::IItemInfo());
        std::size_t                              item = 0;

        // sdd item text
        pItemInfo->SetItemText(values.GetAt(item));

        const std::size_t valueCount = values.GetSize();

        for (++item; item < valueCount; ++item)
            pItemInfo->SetSubItemText(item - 1, values.GetAt(item), -1);

        InsertRootItem(pItemInfo.get());
        pItemInfo.release();
    }
}
//---------------------------------------------------------------------------
