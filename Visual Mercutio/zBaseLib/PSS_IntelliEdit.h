/****************************************************************************
 * ==> PSS_IntelliEdit -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense edit box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IntelliEditH
#define PSS_IntelliEditH

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
#include "PSS_IntelliListBox.h"
#include "PSS_DragEdit.h"

// forward class declaration
class PSS_IntelliEdit;

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
* Intellisense edit button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_IntelliEditBtn : public CButton
{
    public:
        PSS_IntelliEditBtn();
        virtual ~PSS_IntelliEditBtn();

        /**
        * Creates the component
        *@param pEdit - parent edit
        *@param pArrayOfValues - array of values
        *@param pSize - size
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_IntelliEdit* pEdit, CStringArray* pArrayOfValues, CSize* pSize = NULL);

        /**
        * Gets the next component identifier
        *@param pWnd - parent window owning the components
        *@return the next component identifier
        */
        virtual UINT GetNextID(CWnd* pWnd) const;

        /**
        * Gets the listbox window
        *@return the listbox window
        */
        virtual inline CWnd* GetListBoxWnd() const;

        /**
        * Sets the array of values
        *@param pArrayOfValues - array of values
        *@param reload - if true, the array of values will be reloaded immediately
        */
        virtual void SetArrayOfValues(CStringArray* pArrayOfValues, bool reload = true);

        /**
        * Reloads the array of values
        *@param pArrayOfValues - array of values
        *@param reload - if true, the array of values will be reloaded immediately
        */
        virtual void ReloadListOfValues();

        /**
        * Sets the listbox size
        *@param size - size
        */
        virtual inline void SetListBoxSize(const CSize& size);

        /**
        * Gets the listbox selection
        *@return the listbox selection
        */
        virtual inline int GetListBoxCurSel();

        /**
        * Sets the listbox selection
        *@param selection - the listbox selection index
        */
        virtual inline void SetListBoxCurSel(int selection);

        /**
        * Gets the listbox text selection
        *@param[out] text - the listbox text selection on function ends
        */
        virtual inline void GetListBoxTextCurSel(CString& text);

        /**
        * Selects the listbox item matching with the string
        *@param pStr - the listbox item string to search
        *@param startAfter - index from which the search should begin, ignored if -1
        */
        virtual inline void ListBoxSelectString(LPCTSTR pStr, int startAfter = -1);

        /**
        * Checks if floating list is visible
        *@return true if floating list is visible, otherwise false
        */
        virtual inline bool IsFloatingListVisible() const;

        /**
        * Shows the listbox
        */
        virtual inline void ShowListBox();

        /**
        * Hides the listbox
        */
        virtual inline void HideListBox();

    protected:
        PSS_IntelliEdit* m_pEdit;
        CFont            m_Font;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_IntelliEditBtn)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        // Generated message map functions
        //{{AFX_MSG(PSS_IntelliEditBtn)
        afx_msg void OnClicked();
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CStringArray*      m_pArrayOfValues;
        PSS_IntelliListBox m_ListBoxOfValues;
        CSize              m_Size;
        int                m_ListBoxHeight;

        /**
        * Calculates the size and position
        */
        void CalculateSizeAndPosition();

        /**
        * Manages the entries
        */
        void ManageEntries();
};

//---------------------------------------------------------------------------
// PSS_IntelliEditBtn
//---------------------------------------------------------------------------
CWnd* PSS_IntelliEditBtn::GetListBoxWnd() const
{
    return (CWnd*)&m_ListBoxOfValues;
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::SetListBoxSize(const CSize& size)
{
    m_Size = size;
}
//---------------------------------------------------------------------------
int PSS_IntelliEditBtn::GetListBoxCurSel()
{
    if (!IsFloatingListVisible())
        return LB_ERR;

    return m_ListBoxOfValues.GetCurSel();
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::SetListBoxCurSel(int selection)
{
    if (!IsFloatingListVisible())
        return;

    m_ListBoxOfValues.SetCurSel(selection);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::GetListBoxTextCurSel(CString& text)
{
    const int selection = GetListBoxCurSel();

    if (selection == LB_ERR)
    {
        text = "";
        return;
    }

    m_ListBoxOfValues.GetText(selection, text);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::ListBoxSelectString(LPCTSTR pStr, int startAfter)
{
    m_ListBoxOfValues.SelectString(startAfter, pStr);
}
//---------------------------------------------------------------------------
bool PSS_IntelliEditBtn::IsFloatingListVisible() const
{
    return (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()) && m_ListBoxOfValues.IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::ShowListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    m_ListBoxOfValues.ShowWindow(SW_SHOW);
}
//---------------------------------------------------------------------------
void PSS_IntelliEditBtn::HideListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    m_ListBoxOfValues.ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------

/**
* Intellisense edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_IntelliEdit : public PSS_DragEdit
{
    public:
        /**
        * Constructor
        *@param pArrayOfValues - array of values
        *@param pSize - size
        */
        PSS_IntelliEdit(CStringArray* pArrayOfValues = NULL, CSize* pSize = NULL);

        virtual ~PSS_IntelliEdit();

        /**
        * Initializes the component
        *@param pArrayOfValues - array of values
        *@param pSize - size
        */
        virtual void Initialize(CStringArray* pArrayOfValues, CSize* pSize = NULL);

        /**
        * Initializes the component
        */
        virtual void Initialize();

        /**
        * Sets the array of values
        *@param pArrayOfValues - array of values
        *@param reload - if true, the array of values will be reloaded immediately
        */
        virtual void SetArrayOfValues(CStringArray* pArrayOfValues, bool Reload = true);

        /**
        * Reloads the array of values
        *@param pArrayOfValues - array of values
        *@param reload - if true, the array of values will be reloaded immediately
        */
        virtual inline void ReloadListOfValues();

        /**
        * Gets the extended size
        *@return the extended size
        */
        virtual inline CSize GetExtendedSize() const;

        /**
        * Called when the extended size has changed
        *@param cx - width
        *@param cy - height
        */
        virtual void OnExtendedSizeHasChanged(int cx, int cy);

        /**
        * Checks if the component has the focus
        *@return true if the component has the focus, otherwise false
        */
        virtual inline bool HasFocus() const;

        /**
        * Checks if floating list is visible
        *@return true if floating list is visible, otherwise false
        */
        virtual inline bool IsFloatingListVisible() const;

        /**
        * Shows the listbox
        */
        virtual inline void ShowListBox();

        /**
        * Hides the listbox
        */
        virtual inline void HideListBox();

        /**
        * Checks if the history floating list is visible
        *@return true if the history floating list is visible, otherwise false
        */
        virtual inline bool IsHistoryFloatingListVisible() const;

        /**
        * Shows the history listbox
        */
        virtual inline void ShowHistoryListBox();

        /**
        * Hides the history listbox
        */
        virtual inline void HideHistoryListBox();

        /**
        * Validates the typed char
        *@param ch - the char to validate
        *@param editText - the edit text
        *@return true if the typed char is allowed, otherwise false
        */
        virtual bool ValidateChar(UINT ch, const CString& editText) const;

        /**
        * Called when an item is selected in list
        */
        virtual void OnItemSelectedFromList();

        /**
        * Called when enter key is pressed
        */
        virtual void OnEnter();

        /**
        * Called when escape key is pressed
        */
        virtual void OnEscape();

    protected:
        PSS_IntelliEditBtn m_Button;
        CStringArray*      m_pArrayOfValues;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_IntelliEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_IntelliEdit)
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Destroys the component
        */
        virtual void DestroyEdit();

    private:
        PSS_IntelliListBox m_ListBoxOfValues;
        CSize              m_Size;
        int                m_ListBoxHeight;
        bool               m_HasFocus;
        bool               m_BeingResized;

        /**
        * Builds the similar list
        *@param editText - edit text
        *@return the list count
        */
        int BuildSimilarList(const CString& editText);

        /**
        * Checks if the partial text may be found in the full text
        *@param partialText - partial text
        *@param fullText - full text
        *@return true if the partial text may be found in the full text, otherwise false
        */
        bool CompareSimilar(const CString& partialText, const CString& fullText);

        /**
        * Calculates the size and position
        */
        void CalculateSizeAndPosition();

        /**
        * Gets the listbox selection
        *@return the listbox selection
        */
        inline int GetListBoxCurSel() const;

        /**
        * Sets the listbox selection
        *@param selection - the listbox selection index
        */
        inline void SetListBoxCurSel(int selection);

        /**
        * Gets the listbox text selection
        *@param[out] text - the listbox text selection on function ends
        */
        inline void GetListBoxTextCurSel(CString& text) const;

        /**
        * Selects the listbox item matching with the string
        *@param pStr - the listbox item string to search
        *@param startAfter - index from which the search should begin, ignored if -1
        */
        inline void ListBoxSelectString(LPCTSTR pStr, int startAfter = -1);

        /**
        * Gets the history listbox selection
        *@return the history listbox selection
        */
        inline int GetHistoryListBoxCurSel();

        /**
        * Sets the history listbox selection
        *@param selection - the history listbox selection index
        */
        inline void SetHistoryListBoxCurSel(int selection);

        /**
        * Gets the history listbox text selection
        *@param[out] text - the history listbox text selection on function ends
        */
        inline void GetHistoryListBoxTextCurSel(CString& text);

        /**
        * Selects the history listbox item matching with the string
        *@param pStr - the history listbox item string to search
        *@param startAfter - index from which the search should begin, ignored if -1
        */
        inline void HistoryListBoxSelectString(LPCTSTR pStr, int startAfter = -1);
};

//---------------------------------------------------------------------------
// PSS_IntelliEdit
//---------------------------------------------------------------------------
void PSS_IntelliEdit::ReloadListOfValues()
{
    if (!::IsWindow(m_Button.GetSafeHwnd()))
        return;

    m_Button.ReloadListOfValues();
}
//---------------------------------------------------------------------------
CSize PSS_IntelliEdit::GetExtendedSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------
bool PSS_IntelliEdit::HasFocus() const
{
    return m_HasFocus;
}
//---------------------------------------------------------------------------
bool PSS_IntelliEdit::IsFloatingListVisible() const
{
    return (::IsWindow(m_ListBoxOfValues.GetSafeHwnd()) && m_ListBoxOfValues.IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::ShowListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    m_ListBoxOfValues.ShowWindow(SW_SHOW);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::HideListBox()
{
    if (!::IsWindow(m_ListBoxOfValues.GetSafeHwnd()))
        return;

    m_ListBoxOfValues.ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
bool PSS_IntelliEdit::IsHistoryFloatingListVisible() const
{
    return m_Button.IsFloatingListVisible();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::ShowHistoryListBox()
{
    m_Button.ShowListBox();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::HideHistoryListBox()
{
    m_Button.HideListBox();
}
//---------------------------------------------------------------------------
int PSS_IntelliEdit::GetListBoxCurSel() const
{
    if (!IsFloatingListVisible())
        return LB_ERR;

    return m_ListBoxOfValues.GetCurSel();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::SetListBoxCurSel(int selection)
{
    if (!IsFloatingListVisible())
        return;

    m_ListBoxOfValues.SetCurSel(selection);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::GetListBoxTextCurSel(CString& text) const
{
    const int selection = GetListBoxCurSel();

    if (selection == LB_ERR)
    {
        text = "";
        return;
    }

    m_ListBoxOfValues.GetText(selection, text);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::ListBoxSelectString(LPCTSTR pItem, int startAfter)
{
    m_ListBoxOfValues.SelectString(startAfter, pItem);
}
//---------------------------------------------------------------------------
int PSS_IntelliEdit::GetHistoryListBoxCurSel()
{
    return m_Button.GetListBoxCurSel();
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::SetHistoryListBoxCurSel(int selection)
{
    m_Button.SetListBoxCurSel(selection);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::GetHistoryListBoxTextCurSel(CString& text)
{
    m_Button.GetListBoxTextCurSel(text);
}
//---------------------------------------------------------------------------
void PSS_IntelliEdit::HistoryListBoxSelectString(LPCTSTR pStr, int startAfter)
{
    m_Button.ListBoxSelectString(pStr, startAfter);
}
//---------------------------------------------------------------------------

#endif
