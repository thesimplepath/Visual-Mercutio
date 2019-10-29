/****************************************************************************
 * ==> PSS_OutputView ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an output view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_ZVOUTPUTVIEW_H__34183E9D_2920_4176_B402_7CD142E62933__INCLUDED_)
#define AFX_ZVOUTPUTVIEW_H__34183E9D_2920_4176_B402_7CD142E62933__INCLUDED_

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

// processsoft
#include "PSS_Log.h"
#include "PSS_Subject.h"
#include "PSS_Observer.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Output view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OutputView : public CWnd,
                                     public PSS_Log,
                                     public PSS_Subject,
                                     public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_OutputView)

    public:
        PSS_OutputView();
        virtual ~PSS_OutputView();

        /**
        * Releases the view
        */
        void Release();

        /**
        * Initializes the logger for the view
        */
        virtual inline bool InitializeLog();

        /**
        * Clears the logger
        */
        virtual inline void ClearLog();

        /**
        * Adds a line to the output
        *@param line - line to add
        */
        virtual inline void AddLine(const CString& line);

        /**
        * Gets the line count
        *@return the line count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Gets the line at index
        *@param index - index
        *@return the line at index, empty string if not found or on error
        */
        virtual inline CString GetLineAt(std::size_t index) const;

        /**
        * Gets the currently selected line index
        *@return the currently selected line index, -1 if not found or on error
        */
        virtual inline int GetCurrentSelection() const;

        /**
        * Sets the currently selected line index
        *@param index - index
        */
        virtual inline void SetCurrentSelection(std::size_t index);

        /**
        * Clears the current selection
        */
        virtual inline void ClearCurrentSelection();

        /**
        * Gets the current item
        *@param[out] str - string containing the current item text
        *@return the current item index
        */
        virtual inline int GetCurrentItem(CString& str) const;

        /**
        * Gets if the view is in debug mode
        *@return true if the view is in debug mode, otherwise false
        */
        virtual inline bool IsInDebugMode() const;

        /**
        * Sets the view in debug mode
        *@param value - if true, the view is in debug mode
        */
        virtual inline void SetDebugMode(bool value = true);

        /**
        * Gets if the last line should be selected
        *@return true if the last line should be selected, otherwise false
        */
        virtual inline bool SelectLast() const;

        /**
        * Sets if the last line should be selected
        *@param value - if true, the last line should be selected
        */
        virtual inline void SetSelectLast(bool value = true);

        /**
        * Called when a message was sent from subject
        *@param pSubject - subject owning the message
        *@param pMsg - message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /**
        * Output view listbox
        */
        class IOutputViewListBox : public CListBox, public PSS_Subject
        {
            public:
                IOutputViewListBox();
                virtual ~IOutputViewListBox();

                /**
                * Called when a command message is received
                *@param id - message identifier
                *@param code - message code
                *@param pExtra - message extra info
                *@param pHandlerInfo - handler info
                *@return TRUE if message was processed, otherwise FALSE
                */
                virtual inline BOOL OnCmdMsg(UINT                id,
                                             int                 code,
                                             void*               pExtra,
                                             AFX_CMDHANDLERINFO* pHandlerInfo);

                /**
                * Called when a Windows message is received
                *@param message - message
                *@param wParam - message word parameter
                *@param lParam - message long parameter
                *@param pResult - message result
                *@return TRUE if message was processed, otherwise FALSE
                */
                virtual inline BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

            protected:
                /// Generated message map functions
                //{{AFX_MSG(IOutputViewListBox)
                afx_msg void OnSelchange();
                afx_msg void OnDblclk();
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()
        };

        /// Generated message map functions
        //{{AFX_MSG(ZVOutputView)
        afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
        virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when the selection changed
        */
        virtual void OnSelChanged();

        /**
        * Called when a double click on the left mouse button was performed
        */
        virtual void OnDoubleClick();

    private:
        IOutputViewListBox* m_pListBox;
        CFont               m_Font;
        COLORREF            m_ClrBtnFace;
        bool                m_SelectLast;
        bool                m_IsInDebugMode;
};

//---------------------------------------------------------------------------
// PSS_OutputView::IOutputViewListBox
//---------------------------------------------------------------------------
BOOL PSS_OutputView::IOutputViewListBox::OnCmdMsg(UINT                id,
                                                  int                 code,
                                                  void*               pExtra,
                                                  AFX_CMDHANDLERINFO* pHandlerInfo)
{
    return CListBox::OnCmdMsg(id, code, pExtra, pHandlerInfo);
}
//---------------------------------------------------------------------------
BOOL PSS_OutputView::IOutputViewListBox::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    return CListBox::OnWndMsg(message, wParam, lParam, pResult);
}
//---------------------------------------------------------------------------
// PSS_OutputView
//---------------------------------------------------------------------------
bool PSS_OutputView::InitializeLog()
{
    ClearLog();
    return true;
}
//---------------------------------------------------------------------------
void PSS_OutputView::ClearLog()
{
    if (!m_pListBox)
        return;

    m_pListBox->ResetContent();

    // immediate update
    UpdateWindow();
}
//---------------------------------------------------------------------------
void PSS_OutputView::AddLine(const CString& line)
{
    if (!m_pListBox)
        return;

    m_pListBox->AddString(line);

    if (m_SelectLast)
        m_pListBox->SelectString(-1, line);

    // immediate update
    UpdateWindow();
}
//---------------------------------------------------------------------------
std::size_t PSS_OutputView::GetCount() const
{
    if (!m_pListBox)
        return 0;

    return m_pListBox->GetCount();
}
//---------------------------------------------------------------------------
CString PSS_OutputView::GetLineAt(std::size_t index) const
{
    if (!m_pListBox)
        return _T("");

    CString str;
    m_pListBox->GetText(index, str);

    return str;
}
//---------------------------------------------------------------------------
int PSS_OutputView::GetCurrentSelection() const
{
    if (!m_pListBox)
        return -1;

    return (m_pListBox->GetCurSel() != LB_ERR ? m_pListBox->GetCurSel() : -1);
}
//---------------------------------------------------------------------------
void PSS_OutputView::SetCurrentSelection(std::size_t index)
{
    if (!m_pListBox)
        return;

    m_pListBox->SetCurSel(index);
}
//---------------------------------------------------------------------------
void PSS_OutputView::ClearCurrentSelection()
{
    if (!m_pListBox)
        return;

    m_pListBox->SetCurSel(-1);
}
//---------------------------------------------------------------------------
int PSS_OutputView::GetCurrentItem(CString& str) const
{
    if (!m_pListBox)
        return 0;

    const int i = m_pListBox->GetCurSel();

    if (i != LB_ERR)
        m_pListBox->GetText(i, str);

    return i;
}
//---------------------------------------------------------------------------
bool PSS_OutputView::IsInDebugMode() const
{
    return m_IsInDebugMode;
}
//---------------------------------------------------------------------------
void PSS_OutputView::SetDebugMode(bool value)
{
    m_IsInDebugMode = value;
}
//---------------------------------------------------------------------------
bool PSS_OutputView::SelectLast() const
{
    return m_SelectLast;
}
//---------------------------------------------------------------------------
void PSS_OutputView::SetSelectLast(bool value)
{
    m_SelectLast = value;
}
//---------------------------------------------------------------------------

#endif
