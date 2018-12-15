// sphelp.cpp : implementation file
//

#include "stdafx.h"
#include "PlanfObj.h"
#include "sphelp.h"
#include "draw.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SpecialHelp


CString near SpecialHelp::m_strClassName = "";

SpecialHelp::SpecialHelp()
 : m_NumberOfButton( 3 ), m_uiRes( 0 )
#ifdef _WIN32
 , m_pMonthCal( NULL )
#endif
{
}

SpecialHelp::~SpecialHelp()
{
#ifdef _WIN32
    if (m_pMonthCal)
        delete m_pMonthCal;
    m_pMonthCal = NULL;
#endif
    DestroyWindow();
}

BOOL SpecialHelp::CreateSpecialHelp( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, UINT uiRes, size_t NumberOfButton, BOOL AutoCalculateOption )
{
    // Saves the bitmap ID and the number of button
    m_uiRes = uiRes;
    m_NumberOfButton = NumberOfButton;
    // create the window
    // do we need to register the class?
    if(m_strClassName == "")
    {
        // yes
        
        // register the class name
        m_strClassName = ::AfxRegisterWndClass( CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW );
            
        // we're we successful?
        if(m_strClassName == "")
          return 0;  // return failed
    }
    // Assign the object
      m_pObj = pObj;
    m_AutoCalculateOption = AutoCalculateOption;

    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE (m_uiRes), RT_BITMAP);
    GetSizeOfBitmapFile( MAKEINTRESOURCE (m_uiRes), hInst, &m_BitmapPoint );
    // create the helper window
    if( CreateEx( 0, m_strClassName, "", WS_VISIBLE | WS_CHILD, 
                           rct->left, rct->bottom, m_BitmapPoint.x, m_BitmapPoint.y,
                           pParentWnd->GetSafeHwnd(), (HMENU)NULL) == FALSE )
        return( FALSE );
    SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW );
    ShowWindow( SW_SHOW );
    UpdateWindow();
    // Load cursors
    // AfxFindResourceHandle FAILS ON CURSOR, STRING AND ICONS
    // hInst = AfxFindResourceHandle( MAKEINTRESOURCE (IDC_WIZARD), RT_CURSOR);
    m_hcurWizard = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_WIZARD) );
    m_hcurEmpty = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_EMPTY) );
    m_hcurScenario = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_SCENARIO) );
    m_hcurNumber = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_NUMBER) );
    m_hcurProperty = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_PROPERTY_CURSOR) );
    m_hcurCalendar = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_CALENDAR) );
    m_hcurNote = ::LoadCursor( hInst, MAKEINTRESOURCE (IDC_NOTE) );
    return( TRUE );
}

BOOL SpecialHelp::DestroyWindow()
{
  // call the base to destroy the window
  return CWnd::DestroyWindow();
}


BEGIN_MESSAGE_MAP(SpecialHelp, CWnd)
    //{{AFX_MSG_MAP(SpecialHelp)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelp message handlers


void SpecialHelp::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // Calculate the middle of the area
    // to display the bitmap
    if (m_uiRes)
    {
        HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE (m_uiRes), RT_BITMAP);
        DisplayBitmapFile ( MAKEINTRESOURCE (m_uiRes), dc.m_hDC, hInst, 
                            0, 0 );
    }    
}

void SpecialHelp::OnWizard(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_WIZARDMENU, 0, (LPARAM)m_pObj );
}

void SpecialHelp::OnEmpty(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_EMPTYOBJECT, 0, (LPARAM)m_pObj );
}


void SpecialHelp::OnCalendar(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_CALENDAROBJECT, 0, (LPARAM)m_pObj );
}

void SpecialHelp::OnObjectProperty(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_PROPERTYOBJECT, 0, (LPARAM)m_pObj );
}

void SpecialHelp::OnNote(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_NOTEOBJECT, 0, (LPARAM)m_pObj );
}


void SpecialHelp::OnAssociationMenu(CPoint point)
{
    AfxGetMainWnd( )->SendMessageToDescendants( UM_SPHELP_ASSOCIATIONOBJECT, 0, (LPARAM)m_pObj );

}

void SpecialHelp::OnLButtonDown(UINT nFlags, CPoint point)
{
    ReleaseCapture();
    // Call the virtual class
    LButtonDown(nFlags, point);
    CWnd::OnLButtonDown(nFlags, point);
}

void SpecialHelp::OnMouseMove(UINT nFlags, CPoint point)
{
    CWnd::OnMouseMove(nFlags, point);
    // Call the virtual class
    MouseMove(nFlags, point);
}




/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumber specialized window

SpecialHelpNumber::SpecialHelpNumber()
 : SpecialHelp()
{
}

BOOL SpecialHelpNumber::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_NUMBER_T1, 3, AutoCalculateOption );
}

void SpecialHelpNumber::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Notes
        {
            SetFocus();
            OnNote( point );
            break;
        }
        default:
            SetFocus();
    }
}

void SpecialHelpNumber::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetNoteCursor();
            break;
        }
        default:
        {
            break;
        }
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpNumber, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpNumber)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumber message handlers





/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberDesigner specialized window

SpecialHelpNumberDesigner::SpecialHelpNumberDesigner()
 : SpecialHelp()
{
}

BOOL SpecialHelpNumberDesigner::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_NUMBER, 5, AutoCalculateOption );
}

void SpecialHelpNumberDesigner::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Object property
        {
            SetFocus();
            OnObjectProperty( point );
            break;
        }
        case 3:
        {
            break;
        }
        default:
            break;
    }
}

void SpecialHelpNumberDesigner::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetPropertyCursor();
            break;
        }
        case 3:
        {
            SetNumberCursor();
            break;
        }
        case 4:
        {
            SetNoteCursor();
            break;
        }
        default:    // and 0
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpNumberDesigner, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpNumberDesigner)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberDesigner message handlers



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenario specialized window

SpecialHelpNumberScenario::SpecialHelpNumberScenario()
 : SpecialHelp()
{
}

BOOL SpecialHelpNumberScenario::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_NUM_SCN_T1, 4, AutoCalculateOption );
}

void SpecialHelpNumberScenario::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Scenario
        {
            OnAssociationMenu( point );
            break;
        }
        case 3:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            SetFocus();
    }
}

void SpecialHelpNumberScenario::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 3:
        {
            SetScenarioCursor();
            break;
        }
        case 2:
        {
            SetNoteCursor();
            break;
        }
        default:
        {
            break;
        }
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpNumberScenario, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpNumberScenario)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenario message handlers





/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenarioDesigner specialized window

SpecialHelpNumberScenarioDesigner::SpecialHelpNumberScenarioDesigner()
 : SpecialHelp()
{
}

BOOL SpecialHelpNumberScenarioDesigner::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_NUM_SCENARIO, 6, AutoCalculateOption );
}

void SpecialHelpNumberScenarioDesigner::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Object property
        {
            OnObjectProperty( point );
            break;
        }
        case 3:    // Not implemented
        {
            break;
        }
        case 4:    // Scenario
        {
            OnAssociationMenu( point );
            break;
        }
        case 5:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            SetFocus();
    }
}

void SpecialHelpNumberScenarioDesigner::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetPropertyCursor();
            break;
        }
        case 3:
        {
            SetNumberCursor();
            break;
        }
        case 4:
        {
            SetScenarioCursor();
            break;
        }
        case 5:
        {
            SetNoteCursor();
            break;
        }
        default:    // and 0
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpNumberScenarioDesigner, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpNumberScenarioDesigner)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpNumberScenarioDesigner message handlers




/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDate specialized window

SpecialHelpDate::SpecialHelpDate()
 : SpecialHelp()
{
}

BOOL SpecialHelpDate::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_DATE_T1, 4, AutoCalculateOption );
}

void SpecialHelpDate::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Calendar
        {
            OnCalendar( point );
            break;
        }
        case 3:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            break;
    }
}

void SpecialHelpDate::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetCalendarCursor();
            break;
        }
        case 3:
        {
            SetNoteCursor();
            break;
        }
        default:
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpDate, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpDate)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDate message handlers



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDateDesigner specialized window

SpecialHelpDateDesigner::SpecialHelpDateDesigner()
 : SpecialHelp()
{
}

BOOL SpecialHelpDateDesigner::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_DATE, 5, AutoCalculateOption );
}

void SpecialHelpDateDesigner::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Object property
        {
            OnObjectProperty( point );
            break;
        }
        case 3:    // Calendar
        {
            OnCalendar( point );
            break;
        }
        case 4:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            break;
    }
}

void SpecialHelpDateDesigner::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetPropertyCursor();
            break;
        }
        case 3:
        {
            SetCalendarCursor();
            break;
        }
        case 4:
        {
            SetNoteCursor();
            break;
        }
        default:
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpDateDesigner, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpDateDesigner)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDateDesigner message handlers




/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefault specialized window

SpecialHelpDefault::SpecialHelpDefault()
 : SpecialHelp()
{
}

BOOL SpecialHelpDefault::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP_T1, 3, AutoCalculateOption );
}

void SpecialHelpDefault::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            break;
    }
}

void SpecialHelpDefault::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetNoteCursor();
            break;
        }
        default:
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpDefault, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpDefault)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefault message handlers



/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefaultDesigner specialized window

SpecialHelpDefaultDesigner::SpecialHelpDefaultDesigner()
 : SpecialHelp()
{
}

BOOL SpecialHelpDefaultDesigner::Create( CWnd *pParentWnd, CRect *rct, PlanFinObject* pObj, BOOL AutoCalculateOption )
{
    return SpecialHelp::CreateSpecialHelp( pParentWnd, rct, pObj, IDB_SHHELP, 4, AutoCalculateOption );
}

void SpecialHelpDefaultDesigner::LButtonDown(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:    // Wizard
        {
            OnWizard( point );
            break;
        }
        case 1:    // Empty
        {
            OnEmpty( point );
            break;
        }
        case 2:    // Object property
        {
            OnObjectProperty( point );
            break;
        }
        case 3:    // Notes
        {
            OnNote( point );
            break;
        }
        default:
            break;
    }
}

void SpecialHelpDefaultDesigner::MouseMove(UINT nFlags, CPoint point)
{
    switch (GetButtonPosition(point))
    {
        case 0:
        {
            SetWizardCursor();
            break;
        }
        case 1:
        {
            SetEmptyCursor();
            break;
        }
        case 2:
        {
            SetPropertyCursor();
            break;
        }
        case 3:
        {
            SetNoteCursor();
            break;
        }
        default:
            break;
    }
}

BEGIN_MESSAGE_MAP(SpecialHelpDefaultDesigner, SpecialHelp)
    //{{AFX_MSG_MAP(SpecialHelpDefaultDesigner)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpecialHelpDefaultDesigner message handlers
