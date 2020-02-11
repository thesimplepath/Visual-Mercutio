/****************************************************************************
 * ==> PSS_SpecialHelpWnd --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a special help window                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SpecialHelpWnd.h"

// processsoft
#include "PSS_DrawFunctions.h"
#include "PSS_PlanFinObjects.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
CString near PSS_SpecialHelpWnd::m_ClassName = "";
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpWnd::PSS_SpecialHelpWnd() :
    CWnd(),
    #ifdef _WIN32
        m_pMonthCal(NULL),
    #endif
    m_pObj(NULL),
    m_hCurWizard(NULL),
    m_hCurEmpty(NULL),
    m_hCurProperty(NULL),
    m_hCurScenario(NULL),
    m_hCurNumber(NULL),
    m_hCurCalendar(NULL),
    m_hCurNote(NULL),
    m_BitmapRes(0),
    m_NumberOfButton(3),
    m_AutoCalculateOption(FALSE)
{}
//---------------------------------------------------------------------------
PSS_SpecialHelpWnd::~PSS_SpecialHelpWnd()
{
    #ifdef _WIN32
        if (m_pMonthCal)
            delete m_pMonthCal;
    #endif

    DestroyWindow();
}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpWnd::CreateSpecialHelp(CWnd*              pParentWnd,
                                           CRect*             pRect,
                                           PSS_PlanFinObject* pObj,
                                           UINT               bitmapRes,
                                           std::size_t        numberOfButton,
                                           BOOL               autoCalculateOption)
{
    if (!pRect)
        return FALSE;

    // save the bitmap ID and the number of button
    m_BitmapRes      = bitmapRes;
    m_NumberOfButton = numberOfButton;

    // create the window. Need to register the class?
    if (m_ClassName.IsEmpty())
    {
        // yes, register the class name
        m_ClassName = ::AfxRegisterWndClass(CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW);

        // successful?
        if (m_ClassName.IsEmpty())
            return FALSE;
    }

    // assign the object
    m_pObj                = pObj;
    m_AutoCalculateOption = autoCalculateOption;

    HINSTANCE hInst = ::AfxFindResourceHandle(MAKEINTRESOURCE(m_BitmapRes), RT_BITMAP);
    ::GetSizeOfBitmapFile(MAKEINTRESOURCE(m_BitmapRes), hInst, &m_BitmapSize);

    // create the helper window
    if (CreateEx(0,
                 m_ClassName,
                 "",
                 WS_VISIBLE | WS_CHILD,
                 pRect->left,
                 pRect->bottom,
                 m_BitmapSize.cx,
                 m_BitmapSize.cy,
                 pParentWnd->GetSafeHwnd(),
                 HMENU(NULL)) == FALSE)
        return FALSE;

    SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW);
    ShowWindow(SW_SHOW);
    UpdateWindow();

    // load cursors
    m_hCurWizard   = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_WIZARD));
    m_hCurEmpty    = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_EMPTY));
    m_hCurScenario = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_SCENARIO));
    m_hCurNumber   = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_NUMBER));
    m_hCurProperty = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_PROPERTY_CURSOR));
    m_hCurCalendar = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_CALENDAR));
    m_hCurNote     = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_NOTE));

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpWnd::DestroyWindow()
{
    // call the base to destroy the window
    return CWnd::DestroyWindow();
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnObjectProperty(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_PROPERTYOBJECT, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnAssociationMenu(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_ASSOCIATIONOBJECT, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnWizard(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_WIZARDMENU, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnCalendar(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_CALENDAROBJECT, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnEmpty(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_EMPTYOBJECT, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnNote(const CPoint& point)
{
    AfxGetMainWnd()->SendMessageToDescendants(UM_SPHELP_NOTEOBJECT, 0, LPARAM(m_pObj));
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    // calculate the middle of the area to draw the bitmap
    if (m_BitmapRes)
    {
        HINSTANCE hInst = ::AfxFindResourceHandle(MAKEINTRESOURCE(m_BitmapRes), RT_BITMAP);
        ShowBitmapFile(MAKEINTRESOURCE(m_BitmapRes), dc.m_hDC, hInst, 0, 0);
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    ReleaseCapture();

    // call the virtual class
    LButtonDown(nFlags, point);

    CWnd::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    CWnd::OnMouseMove(nFlags, point);

    // call the virtual class
    MouseMove(nFlags, point);
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpNumberWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpNumberWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpNumberWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpNumberWnd::PSS_SpecialHelpNumberWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpNumberWnd::Create(CWnd* pParentWnd, CRect* pRect, PSS_PlanFinObject* pObj, BOOL autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd,
                                                 pRect,
                                                 pObj,
                                                 IDB_SHHELP_NUMBER_T1,
                                                 3,
                                                 autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0: OnWizard(point); break;
        case 1: OnEmpty(point);  break;
        case 2:
            SetFocus();
            OnNote(point);
            break;

        default: SetFocus();
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0: SetWizardCursor(); break;
        case 1: SetEmptyCursor();  break;
        case 2: SetNoteCursor();   break;
        default:                   break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpNumberDesignerWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpNumberDesignerWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpNumberDesignerWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpNumberDesignerWnd::PSS_SpecialHelpNumberDesignerWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpNumberDesignerWnd::Create(CWnd*              pParentWnd,
                                              CRect*             pRect,
                                              PSS_PlanFinObject* pObj,
                                              BOOL               autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd, pRect, pObj, IDB_SHHELP_NUMBER, 5, autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberDesignerWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0: OnWizard(point); break;
        case 1: OnEmpty(point);  break;
        case 2:
            SetFocus();
            OnObjectProperty(point);
            break;

        default: break;
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberDesignerWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0: SetWizardCursor();   break;
        case 1: SetEmptyCursor();    break;
        case 2: SetPropertyCursor(); break;
        case 3: SetNumberCursor();   break;
        case 4: SetNoteCursor();     break;
        default:                     break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpNumberScenarioWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpNumberScenarioWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpNumberScenarioWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpNumberScenarioWnd::PSS_SpecialHelpNumberScenarioWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpNumberScenarioWnd::Create(CWnd*              pParentWnd,
                                              CRect*             pRect,
                                              PSS_PlanFinObject* pObj,
                                              BOOL               autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd,
                                                 pRect,
                                                 pObj,
                                                 IDB_SHHELP_NUM_SCN_T1,
                                                 4,
                                                 autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberScenarioWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point);          break;
        case 1:  OnEmpty(point);           break;
        case 2:  OnAssociationMenu(point); break;
        case 3:  OnNote(point);            break;
        default: SetFocus();
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberScenarioWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0: SetWizardCursor();   break;
        case 1: SetEmptyCursor();    break;
        case 3: SetScenarioCursor(); break;
        case 2: SetNoteCursor();     break;
        default:                     break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpNumberScenarioDesignerWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpNumberScenarioDesignerWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpNumberScenarioDesignerWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpNumberScenarioDesignerWnd::PSS_SpecialHelpNumberScenarioDesignerWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpNumberScenarioDesignerWnd::Create(CWnd*              pParentWnd,
                                                      CRect*             pRect,
                                                      PSS_PlanFinObject* pObj,
                                                      BOOL               autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd,
                                                 pRect,
                                                 pObj,
                                                 IDB_SHHELP_NUM_SCENARIO,
                                                 6,
                                                 autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberScenarioDesignerWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point);          break;
        case 1:  OnEmpty(point);           break;
        case 2:  OnObjectProperty(point);  break;
        case 3:                            break;
        case 4:  OnAssociationMenu(point); break;
        case 5:  OnNote(point);            break;
        default: SetFocus();
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpNumberScenarioDesignerWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  SetWizardCursor();   break;
        case 1:  SetEmptyCursor();    break;
        case 2:  SetPropertyCursor(); break;
        case 3:  SetNumberCursor();   break;
        case 4:  SetScenarioCursor(); break;
        case 5:  SetNoteCursor();     break;
        default:                      break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpDateWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpDateWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpDateWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpDateWnd::PSS_SpecialHelpDateWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpDateWnd::Create(CWnd* pParentWnd, CRect* pRect, PSS_PlanFinObject* pObj, BOOL autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd, pRect, pObj, IDB_SHHELP_DATE_T1, 4, autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDateWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point);   break;
        case 1:  OnEmpty(point);    break;
        case 2:  OnCalendar(point); break;
        case 3:  OnNote(point);     break;
        default:                    break;
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDateWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  SetWizardCursor();   break;
        case 1:  SetEmptyCursor();    break;
        case 2:  SetCalendarCursor(); break;
        case 3:  SetNoteCursor();     break;
        default:                      break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpDateDesignerWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpDateDesignerWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpDateDesignerWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpDateDesignerWnd::PSS_SpecialHelpDateDesignerWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpDateDesignerWnd::Create(CWnd*              pParentWnd,
                                            CRect*             pRect,
                                            PSS_PlanFinObject* pObj,
                                            BOOL               autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd, pRect, pObj, IDB_SHHELP_DATE, 5, autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDateDesignerWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point);         break;
        case 1:  OnEmpty(point);          break;
        case 2:  OnObjectProperty(point); break;
        case 3:  OnCalendar(point);       break;
        case 4:  OnNote(point);           break;
        default:                          break;
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDateDesignerWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  SetWizardCursor();   break;
        case 1:  SetEmptyCursor();    break;
        case 2:  SetPropertyCursor(); break;
        case 3:  SetCalendarCursor(); break;
        case 4:  SetNoteCursor();     break;
        default:                      break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpDefaultWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpDefaultWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpDefaultWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpDefaultWnd::PSS_SpecialHelpDefaultWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpDefaultWnd::Create(CWnd* pParentWnd, CRect* pRect, PSS_PlanFinObject* pObj, BOOL autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd, pRect, pObj, IDB_SHHELP_T1, 3, autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDefaultWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point); break;
        case 1:  OnEmpty(point);  break;
        case 2:  OnNote(point);   break;
        default:                  break;
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDefaultWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  SetWizardCursor(); break;
        case 1:  SetEmptyCursor();  break;
        case 2:  SetNoteCursor();   break;
        default:                    break;
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SpecialHelpDefaultDesignerWnd, PSS_SpecialHelpWnd)
    //{{AFX_MSG_MAP(PSS_SpecialHelpDefaultDesignerWnd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SpecialHelpDefaultDesignerWnd
//---------------------------------------------------------------------------
PSS_SpecialHelpDefaultDesignerWnd::PSS_SpecialHelpDefaultDesignerWnd() :
    PSS_SpecialHelpWnd()
{}
//---------------------------------------------------------------------------
BOOL PSS_SpecialHelpDefaultDesignerWnd::Create(CWnd*              pParentWnd,
                                               CRect*             pRect,
                                               PSS_PlanFinObject* pObj,
                                               BOOL               autoCalculateOption)
{
    return PSS_SpecialHelpWnd::CreateSpecialHelp(pParentWnd, pRect, pObj, IDB_SHHELP, 4, autoCalculateOption);
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDefaultDesignerWnd::LButtonDown(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  OnWizard(point);         break;
        case 1:  OnEmpty(point);          break;
        case 2:  OnObjectProperty(point); break;
        case 3:  OnNote(point);           break;
        default:                          break;
    }
}
//---------------------------------------------------------------------------
void PSS_SpecialHelpDefaultDesignerWnd::MouseMove(UINT flags, const CPoint& point)
{
    switch (GetButtonPosition(point))
    {
        case 0:  SetWizardCursor();   break;
        case 1:  SetEmptyCursor();    break;
        case 2:  SetPropertyCursor(); break;
        case 3:  SetNoteCursor();     break;
        default:                      break;
    }
}
//---------------------------------------------------------------------------
