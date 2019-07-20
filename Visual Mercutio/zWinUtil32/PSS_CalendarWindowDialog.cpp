/****************************************************************************
 * ==> PSS_CalendarWindowDialog --------------------------------------------*
 ****************************************************************************
 * Description : Provides a calendar window dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CalendarWindowDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CalendarWindowDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_CalendarWindowDialog)
    ON_WM_ACTIVATE()
    ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCAL, HandleSelChange)
    ON_NOTIFY(MCN_SELECT, IDC_MONTHCAL, HandleSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CalendarWindowDialog
//---------------------------------------------------------------------------
PSS_CalendarWindowDialog::PSS_CalendarWindowDialog(CWnd* pParent) :
    m_pParent(pParent),
    m_ID(-2),
    m_Range(FALSE)
{}
//---------------------------------------------------------------------------
BOOL PSS_CalendarWindowDialog::HandleCalendar(const CPoint& point, BOOL range)
{
    m_ID    = -1;
    m_Range =  range;
    m_Point =  point;
    Create(PSS_CalendarWindowDialog::IDD, m_pParent);

    MSG msg;

    while (GetMessage(&msg, NULL, NULL, NULL) && m_ID == -1)
        if (!IsWindow(GetSafeHwnd()) || !IsDialogMessage(&msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    TRACE("END MODAL");
    return m_ID == 1;
}
//---------------------------------------------------------------------------
void PSS_CalendarWindowDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
void PSS_CalendarWindowDialog::HandleSelChange(NMHDR *pHdr, LRESULT *pRes)
{
    if (!(m_MonthCal.GetStyle() & MCS_MULTISELECT))
        return;

    ::SYSTEMTIME sysTimeStart;
    ::SYSTEMTIME sysTimeEnd;

    m_MonthCal.GetSelRange(&sysTimeStart, &sysTimeEnd);
    m_SelectedStartTime.SetDate(sysTimeStart.wYear, sysTimeStart.wMonth, sysTimeStart.wDay);
    m_SelectedEndTime.SetDate(sysTimeEnd.wYear, sysTimeEnd.wMonth, sysTimeEnd.wDay);

    m_ID = 1;
}
//---------------------------------------------------------------------------
void PSS_CalendarWindowDialog::HandleSelect(NMHDR *pHdr, LRESULT *pRes)
{
    if ((m_MonthCal.GetStyle() & MCS_MULTISELECT))
        return;

    ::SYSTEMTIME sysTime;

    // use SYSTEMTIME because with COleDateTime it is not working.
    m_MonthCal.GetCurSel(&sysTime);
    m_SelectedTime.SetDate(sysTime.wYear, sysTime.wMonth, sysTime.wDay);

    m_ID = 1;
}
//---------------------------------------------------------------------------
BOOL PSS_CalendarWindowDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CRect windowRect;

    CWnd* pFrame = GetDlgItem(IDC_CALENDAR_FRAME);
    pFrame->GetClientRect(windowRect);
    pFrame->DestroyWindow();

    long lStyle = WS_CHILD | WS_VISIBLE;

    if (m_Range)
        lStyle |= MCS_MULTISELECT;

    m_MonthCal.Create(lStyle, CPoint(windowRect.left, windowRect.top), this, IDC_MONTHCAL);
    m_MonthCal.GetClientRect(windowRect);
    windowRect.OffsetRect(m_Point);
    MoveWindow(&windowRect);
    UpdateData(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX Property Pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CalendarWindowDialog::OnActivate(UINT state, CWnd* pWndOther, BOOL minimized)
{
    CDialog::OnActivate(state, pWndOther, minimized);

    // if the window becomes inactive, stop the run.
    if (state == WA_INACTIVE && m_ID == -1)
        m_ID = 0;
}
//---------------------------------------------------------------------------
