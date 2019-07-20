/****************************************************************************
 * ==> PSS_CalendarWindowDialog --------------------------------------------*
 ****************************************************************************
 * Description : Provides a calendar window dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CalendarWindowDialogH
#define PSS_CalendarWindowDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Calendar window dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CalendarWindowDialog : public CDialog
{
    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_CALENDAR
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_CalendarWindowDialog(CWnd* pParent = NULL);

        /**
        * Handles the calendar
        *@param point - point
        *@param range - range
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL HandleCalendar(const CPoint& point, BOOL range = FALSE);

        /**
        * Gets the selected date
        *@return the selected date
        */
        virtual inline COleDateTime GetDate() const;

        /**
        * Gets the start date
        *@return the start date
        */
        virtual inline COleDateTime GetStartDate() const;

        /**
        * Gets the end date
        *@return the end date
        */
        virtual inline COleDateTime GetEndDate() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZICalendarWnd)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /**
        * Handles the selection change
        *@param pHandler - handler
        *@param pResult - result
        */
        virtual void HandleSelChange(NMHDR* pHandler, LRESULT* pResult);

        /**
        * Handles the selection
        *@param pHandler - handler
        *@param pResult - result
        */
        virtual void HandleSelect(NMHDR* pHandler, LRESULT* pResult);

        // Generated message map functions
        //{{AFX_MSG(ZICalendarWnd)
        virtual BOOL OnInitDialog();
        afx_msg void OnActivate(UINT state, CWnd* pWndOther, BOOL minimized);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd*         m_pParent;
        CMonthCalCtrl m_MonthCal;
        COleDateTime  m_SelectedTime;
        COleDateTime  m_SelectedStartTime;
        COleDateTime  m_SelectedEndTime;
        CPoint        m_Point;
        int           m_ID;
        BOOL          m_Range;
};

//---------------------------------------------------------------------------
// PSS_CalendarWindowDialog
//---------------------------------------------------------------------------
COleDateTime PSS_CalendarWindowDialog::GetDate() const
{
    return m_SelectedTime;
}
//---------------------------------------------------------------------------
COleDateTime PSS_CalendarWindowDialog::GetStartDate() const
{
    return m_SelectedStartTime;
}
//---------------------------------------------------------------------------
COleDateTime PSS_CalendarWindowDialog::GetEndDate() const
{
    return m_SelectedEndTime;
}
//---------------------------------------------------------------------------

#endif
