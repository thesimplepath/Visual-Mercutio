// CalWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CalWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZICalendarWnd dialog


ZICalendarWnd::ZICalendarWnd(CWnd* pParent /*=NULL*/)
    : m_ID(-2), m_Range(FALSE), m_pParent(pParent)
{
    //{{AFX_DATA_INIT(ZICalendarWnd)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZICalendarWnd::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZICalendarWnd)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZICalendarWnd, CDialog)
    //{{AFX_MSG_MAP(ZICalendarWnd)
    ON_WM_ACTIVATE()
    //}}AFX_MSG_MAP
    ON_NOTIFY(MCN_SELCHANGE,IDC_MONTHCAL,HandleSelChange)
    ON_NOTIFY(MCN_SELECT,IDC_MONTHCAL,HandleSelect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZICalendarWnd message handlers

BOOL ZICalendarWnd::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    CWnd *pFrame = GetDlgItem(IDC_CALENDAR_FRAME);
    CRect rcWnd;
    pFrame->GetClientRect( rcWnd );
    pFrame->DestroyWindow(); //pFrame was just a placeholder anyway.
    long lStyle = WS_CHILD | WS_VISIBLE;
    if (m_Range)
        lStyle |= MCS_MULTISELECT;
    m_MonthCal.Create( lStyle, CPoint(rcWnd.left,rcWnd.top), this, IDC_MONTHCAL);
    m_MonthCal.GetClientRect( rcWnd );
    rcWnd.OffsetRect( m_Point );
    MoveWindow( &rcWnd );
    UpdateData(FALSE);
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL    ZICalendarWnd::HandleCalendar(CPoint point, BOOL Range)
{
    m_Range = Range;
    m_Point = point;
    Create( ZICalendarWnd::IDD, m_pParent );

    m_ID = -1;
    MSG    msg;
    while (GetMessage(&msg, NULL, NULL, NULL) && m_ID == -1) 
    { 
        if (!IsWindow(GetSafeHwnd()) || !IsDialogMessage(&msg))
        { 
            TranslateMessage(&msg);         
            DispatchMessage(&msg);     
        } 
    }
    TRACE( "END MODAL" );
    return m_ID == 1;

}

void ZICalendarWnd::HandleSelect(NMHDR *pHdr, LRESULT *pRes)
{
    if ((m_MonthCal.GetStyle() & MCS_MULTISELECT))
        return;
    // Use SYSTEMTIME because with COleDateTime it is not working.
    SYSTEMTIME sysTime;
    m_MonthCal.GetCurSel( &sysTime );
    m_SelectedTime.SetDate( sysTime.wYear, sysTime.wMonth, sysTime.wDay );
    m_ID = 1;
}

void ZICalendarWnd::HandleSelChange(NMHDR *pHdr, LRESULT *pRes)
{
    if (!(m_MonthCal.GetStyle() & MCS_MULTISELECT))
        return;
    SYSTEMTIME sysTimeStart;
    SYSTEMTIME sysTimeEnd;
    m_MonthCal.GetSelRange( &sysTimeStart, &sysTimeEnd );
    m_SelectedStartTime.SetDate( sysTimeStart.wYear, sysTimeStart.wMonth, sysTimeStart.wDay );
    m_SelectedEndTime.SetDate( sysTimeEnd.wYear, sysTimeEnd.wMonth, sysTimeEnd.wDay );
    m_ID = 1;
}


void ZICalendarWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
    CDialog::OnActivate(nState, pWndOther, bMinimized);
    // If the window becomes inactive, stop the run.
    if (nState == WA_INACTIVE && m_ID == -1)
        m_ID = 0;
}
