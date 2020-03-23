/****************************************************************************
 * ==> PSS_InputDurationDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box to input a duration                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputDurationDlgH
#define PSS_InputDurationDlgH

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
#include "zPtyMgrRes.h"

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input a duration dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_InputDurationDlg : public CDialog
{
    public:
        /**
        * Constructor
        *@param days - the days
        *@param hours - the hours
        *@param minutes - the minutes
        *@param seconds - the seconds
        *@param pParent - the parent window, can be NULL
        */
        PSS_InputDurationDlg(int   days    = 0,
                             int   hours   = 0,
                             int   minutes = 0,
                             int   seconds = 0,
                             CWnd* pParent = NULL);

        /**
        * Gets the days
        *@return the days
        */
        virtual inline int GetDays() const;

        /**
        * Gets the hours
        *@return the hours
        */
        virtual inline int GetHours() const;

        /**
        * Gets the minutes
        *@return the minutes
        */
        virtual inline int GetMinutes() const;

        /**
        * Gets the seconds
        *@return the seconds
        */
        virtual inline int GetSeconds() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InputDurationDlg)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_InputDurationDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        virtual void OnCancel();
        afx_msg void OnClose();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_INPUT_DURATION
        };

        CString m_InitialValue;
        CString m_ValueString;
        int     m_Days;
        int     m_Hours;
        int     m_Minutes;
        int     m_Seconds;
};

//---------------------------------------------------------------------------
// PSS_InputDurationDlg
//---------------------------------------------------------------------------
int PSS_InputDurationDlg::GetDays() const
{
    return m_Days;
}
//---------------------------------------------------------------------------
int PSS_InputDurationDlg::GetHours() const
{
    return m_Hours;
}
//---------------------------------------------------------------------------
int PSS_InputDurationDlg::GetMinutes() const
{
    return m_Minutes;
}
//---------------------------------------------------------------------------
int PSS_InputDurationDlg::GetSeconds() const
{
    return m_Seconds;
}
//---------------------------------------------------------------------------

#endif
