#if !defined(AFX_CALWND_H__E7E81473_FE5B_11D2_9573_0000B45D7C6F__INCLUDED_)
#define AFX_CALWND_H__E7E81473_FE5B_11D2_9573_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalWnd.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "zWinUtil32\ZWinUtil32.h"


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// ZICalendarWnd dialog

class AFX_EXT_CLASS ZICalendarWnd : public CDialog
{
// Construction
public:
    ZICalendarWnd(CWnd* pParent = NULL);   // standard constructor
    BOOL            HandleCalendar(CPoint point, BOOL Range = FALSE);
    COleDateTime    GetDate() const { return m_SelectedTime; };
    COleDateTime    GetStartDate() const { return m_SelectedStartTime; };
    COleDateTime    GetEndDate() const { return m_SelectedEndTime; };

// Dialog Data
    //{{AFX_DATA(ZICalendarWnd)
    enum { IDD = IDD_CALENDAR };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZICalendarWnd)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

private:
    CMonthCalCtrl    m_MonthCal;
    COleDateTime    m_SelectedTime;
    COleDateTime    m_SelectedStartTime;
    COleDateTime    m_SelectedEndTime;
    CWnd*            m_pParent;
    CPoint            m_Point;
    BOOL            m_Range;
    int                m_ID;
// Implementation
protected:
    void HandleSelChange(NMHDR *pHdr, LRESULT *pRes);
    void HandleSelect(NMHDR *pHdr, LRESULT *pRes);

    // Generated message map functions
    //{{AFX_MSG(ZICalendarWnd)
    virtual BOOL OnInitDialog();
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALWND_H__E7E81473_FE5B_11D2_9573_0000B45D7C6F__INCLUDED_)
