/****************************************************************************
 * ==> PSS_IntelliMultiLineEditBox -----------------------------------------*
 ****************************************************************************
 * Description : Provides an intellisense multiline edit box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IntelliMultiLineEditBoxH
#define PSS_IntelliMultiLineEditBoxH

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

// forward class declaration
class PSS_MultiLineEdit;

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
* Intellisense multiline edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_IntelliMultiLineEditBox : public CWnd
{
    DECLARE_DYNAMIC(PSS_IntelliMultiLineEditBox);

    public:
        /**
        * Constructor
        *@param pEditCtrl - parent edit control, can be NULL
        *@param pSize - edit box size
        */
        PSS_IntelliMultiLineEditBox(PSS_MultiLineEdit* pEditCtrl = NULL, CSize* pSize = NULL);

        virtual ~PSS_IntelliMultiLineEditBox();

        /**
        * Creates the control
        *@param pEditCtrl - parent edit control
        *@param pSize - edit box size
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_MultiLineEdit* pEditCtrl, CSize* pSize = NULL);

        /**
        * Sets the parent edit control
        *@param pEditCtrl - parent edit control
        *@param pSize - edit box size
        *@return TRUE on success, otherwise FALSE
        */
        virtual void SetEditControl(PSS_MultiLineEdit* pEditCtrl, CSize* pSize = NULL);

        /**
        * Checks if undo function is enabled
        *@return TRUE if undo function is enabled, otherwise FALSE
        */
        virtual inline BOOL CanUndo() const;

        /**
        * Gets if the edit content was modified
        *@return TRUE if the edit content was modified, otherwise FALSE
        */
        virtual inline BOOL GetModify() const;

        /**
        * Sets if the edit content was modified
        *@param modified - if TRUE, the edit content was modified
        */
        virtual inline void SetModify(BOOL modified = TRUE);

        /**
        * Gets the bounding rectangle
        *@param pRect - rectangle structure in which the bounding rectangle will be written
        */
        virtual inline void GetRect(LPRECT pRect) const;

        /**
        * Sets the bounding rectangle
        *@param pRect - the bounding rectangle to set
        */
        virtual inline void SetRect(LPCRECT pRect);

        /**
        * Gets the selection
        *@return the index where the selection begins
        */
        virtual inline DWORD GetSel() const;

        /**
        * Gets the selection
        *@param[out] startChar - the selection start char index on function ends
        *@param[out] endChar - the selection end char index on function ends
        */
        virtual inline void GetSel(int& startChar, int& endChar) const;

        /**
        * Sets the selection
        *@param selection - selection index
        *@param noScroll - if TRUE, the scroll will be disabled
        */
        virtual inline void SetSel(DWORD selection, BOOL noScroll = FALSE);

        /**
        * Sets the selection
        *@param startChar - the selection start char index
        *@param endChar - the selection end char index
        *@param noScroll - if TRUE, the scroll will be disabled
        */
        virtual inline void SetSel(int startChar, int endChar, BOOL noScroll = FALSE);

        /**
        * Gets the handle
        *@return the handle
        */
        virtual inline HLOCAL GetHandle() const;

        /**
        * Sets the handle
        *@param hHandle - the handle
        */
        virtual inline void SetHandle(HLOCAL hHandle);

        /**
        * Gets the margins
        *@return the margins
        */
        #if (WINVER >= 0x400)
            virtual inline DWORD GetMargins() const;
        #endif

        /**
        * Sets the margins
        *@param left - the left margin
        *@param right - the right margin
        */
        #if (WINVER >= 0x400)
            virtual inline void SetMargins(UINT left, UINT right);
        #endif

        /**
        * Gets the limit text
        *@return the limit text
        */
        #if (WINVER >= 0x400)
            virtual inline UINT GetLimitText() const;
        #endif

        /**
        * Sets the limit text
        *@param max - the max limit text
        */
        #if (WINVER >= 0x400)
            virtual inline void SetLimitText(UINT nMax);
        #endif

        /**
        * Gets the position at which a char is located
        *@param ch - the char for which the position should be get
        *@return the char position
        */
        #if (WINVER >= 0x400)
            virtual inline CPoint PosFromChar(UINT ch) const;
        #endif

        /**
        * Gets the closest char from a position
        *@param pt - the position
        *@return the char
        */
        #if (WINVER >= 0x400)
            virtual inline int CharFromPos(CPoint pt) const;
        #endif

        /**
        * Gets the line
        *@param index - the line index
        *@param pBuffer - the buffer containing the line text
        *@return the line buffer length
        */
        virtual inline int GetLine(int index, LPTSTR pBuffer) const;

        /**
        * Gets the line
        *@param index - the line index
        *@param pBuffer - the buffer containing the line text
        *@param maxLength - the line buffer max length
        *@return the line buffer length
        */
        virtual inline int GetLine(int index, LPTSTR pBuffer, int maxLength) const;

        /**
        * Gets the line count
        *@return the line count
        */
        virtual inline int GetLineCount() const;

        /**
        * Empties the undo buffer
        */
        virtual inline void EmptyUndoBuffer();

        /**
        * Formats the line
        *@param addEOL - if TRUE, the end of line char will be added
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL FmtLines(BOOL addEOL);

        /**
        * Limits the text
        *@param chars - maximum char count allowed for the text, no limit if 0
        */
        virtual inline void LimitText(int chars = 0);

        /**
        * Gets the line index from a char index
        *@param index - the char index
        *@return the line index
        */
        virtual inline int LineFromChar(int index = -1) const;

        /**
        * Gets the first character index of a line
        *@param line - the line index
        *@return the first character index
        */
        virtual inline int LineIndex(int line = -1) const;

        /**
        * Gets the line length
        *@param line - the line index
        *@return the line length
        */
        virtual inline int LineLength(int line = -1) const;

        /**
        * Sets the number of lines to scroll vertically, and the number of chars to scroll horizontally
        *@param lines - the number of lines to scroll vertically
        *@param chars - the number of chars to scroll horizontally
        */
        virtual inline void LineScroll(int lines, int chars = 0);

        /**
        * Replaces the selection
        *@param pNewText - the new text to replace by
        *@param canUndo - if TRUE, the action can be undoed
        */
        virtual inline void ReplaceSel(LPCTSTR pNewText, BOOL canUndo = FALSE);

        /**
        * Gets the password char
        *@return the password char
        */
        virtual inline TCHAR GetPasswordChar() const;

        /**
        * Sets the password char
        *@param ch - the password char
        */
        virtual inline void SetPasswordChar(TCHAR ch);

        /**
        * Set the formatting rectangle
        *@param pRect - the formatting rectangle
        */
        virtual inline void SetRectNP(LPCRECT pRect);

        /**
        * Sets the tab stops
        *@param tabStopCount - the tab stop array item count
        *@param tabStops - the tab stop array
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetTabStops(int tabStopCount, LPINT tabStops);

        /**
        * Sets the tab stops
        */
        virtual inline void SetTabStops();

        /**
        * Sets the tab stops
        *@param[in, out] eachStop - each tab stop
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetTabStops(const int& eachStop);

        /**
        * Undoes the last action
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL Undo();

        /**
        * Clears the component content
        */
        virtual inline void Clear();

        /**
        * Copies the component content to the clipboard
        */
        virtual inline void Copy();

        /**
        * Cuts the component content and moves it to the clipboard
        */
        virtual inline void Cut();

        /**
        * Pastes the text from the clipboard to the component
        */
        virtual inline void Paste();

        /**
        * Sets the component as read-only
        *@param readOnly - if TRUE, the component is read-only
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL SetReadOnly(BOOL readOnly = TRUE);

        /**
        * Gets the first visible line index
        *@return the first visible line index
        */
        virtual inline int GetFirstVisibleLine() const;

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_IntelliMultiLineEditBox)
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Multiline edit box
        */
        class IMultiLineEdit : public CEdit
        {
            public:
                /**
                * Constructor
                *@param pEditCtrl - edit control, can be NULL
                *@param pParent - parent component, can be NULL
                */
                IMultiLineEdit(PSS_MultiLineEdit* pEditCtrl = NULL, PSS_IntelliMultiLineEditBox* pParent = NULL);

                virtual ~IMultiLineEdit();

                /**
                * Sets the edit control
                *@param pEditCtrl - edit control
                *@param pParent - parent component, can be NULL
                */
                void SetEditControl(PSS_MultiLineEdit* pEditCtrl, PSS_IntelliMultiLineEditBox* pParent = NULL);

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IMultiLineEdit)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IMultiLineEdit)
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                PSS_IntelliMultiLineEditBox* m_pParent;
                PSS_MultiLineEdit*           m_pEditCtrl;

                /**
                * Translates the selection to edit control
                */
                void TranslateSelectionToEditControl();
        };

        static CString near m_ClassName;
        IMultiLineEdit      m_Edit;
        PSS_MultiLineEdit*  m_pEditCtrl;
        CSize               m_Size;
        int                 m_MultiLineEditBoxHeight;

        /**
        * Gets the next identifier from a window
        *@param pWnd - window
        *@return the next identifier
        */
        UINT GetNextID(CWnd* pWnd) const;
};

//---------------------------------------------------------------------------
// PSS_IntelliMultiLineEditBox
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::CanUndo() const
{
    return m_Edit.CanUndo();
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::GetModify() const
{
    return m_Edit.GetModify();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetModify(BOOL modified)
{
    m_Edit.SetModify(modified);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::GetRect(LPRECT pRect) const
{
    m_Edit.GetRect(pRect);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetRect(LPCRECT pRect)
{
    m_Edit.SetRect(pRect);
}
//---------------------------------------------------------------------------
DWORD PSS_IntelliMultiLineEditBox::GetSel() const
{
    return m_Edit.GetSel();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::GetSel(int& startChar, int& endChar) const
{
    m_Edit.GetSel(startChar, endChar);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetSel(DWORD selection, BOOL noScroll)
{
    m_Edit.SetSel(selection, noScroll);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetSel(int startChar, int endChar, BOOL noScroll)
{
    m_Edit.SetSel(startChar, endChar, noScroll);
}
//---------------------------------------------------------------------------
HLOCAL PSS_IntelliMultiLineEditBox::GetHandle() const
{
    return m_Edit.GetHandle();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetHandle(HLOCAL hHandle)
{
    m_Edit.SetHandle(hHandle);
}
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    DWORD PSS_IntelliMultiLineEditBox::GetMargins() const
    {
        return m_Edit.GetMargins();
    }
#endif
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    void PSS_IntelliMultiLineEditBox::SetMargins(UINT left, UINT right)
    {
        m_Edit.SetMargins(left, right);
    }
#endif
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    UINT PSS_IntelliMultiLineEditBox::GetLimitText() const
    {
        return m_Edit.GetLimitText();
    }
#endif
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    void PSS_IntelliMultiLineEditBox::SetLimitText(UINT nMax)
    {
        m_Edit.SetLimitText(nMax);
    }
#endif
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    CPoint PSS_IntelliMultiLineEditBox::PosFromChar(UINT ch) const
    {
        return m_Edit.PosFromChar(ch);
    }
#endif
//---------------------------------------------------------------------------
#if (WINVER >= 0x400)
    int PSS_IntelliMultiLineEditBox::CharFromPos(CPoint pt) const
    {
        return m_Edit.CharFromPos(pt);
    }
#endif
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::GetLine(int index, LPTSTR pBuffer) const
{
    return m_Edit.GetLine(index, pBuffer);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::GetLine(int index, LPTSTR pBuffer, int maxLength) const
{
    return m_Edit.GetLine(index, pBuffer, maxLength);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::GetLineCount() const
{
    return m_Edit.GetLineCount();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::EmptyUndoBuffer()
{
    m_Edit.EmptyUndoBuffer();
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::FmtLines(BOOL addEOL)
{
    return m_Edit.FmtLines(addEOL);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::LimitText(int chars)
{
    m_Edit.LimitText(chars);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::LineFromChar(int index) const
{
    return m_Edit.LineFromChar(index);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::LineIndex(int line) const
{
    return m_Edit.LineIndex(line);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::LineLength(int line) const
{
    return m_Edit.LineLength(line);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::LineScroll(int lines, int chars)
{
    m_Edit.LineScroll(lines, chars);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::ReplaceSel(LPCTSTR pNewText, BOOL canUndo)
{
    m_Edit.ReplaceSel(pNewText, canUndo);
}
//---------------------------------------------------------------------------
TCHAR PSS_IntelliMultiLineEditBox::GetPasswordChar() const
{
    return m_Edit.GetPasswordChar();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetPasswordChar(TCHAR ch)
{
    m_Edit.SetPasswordChar(ch);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetRectNP(LPCRECT pRect)
{
    m_Edit.SetRectNP(pRect);
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::SetTabStops(int tabStopCount, LPINT tabStops)
{
    return m_Edit.SetTabStops(tabStopCount, tabStops);
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::SetTabStops()
{
    m_Edit.SetTabStops();
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::SetTabStops(const int& eachStop)
{
    return m_Edit.SetTabStops(eachStop);
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::Undo()
{
    return m_Edit.Undo();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::Clear()
{
    m_Edit.Clear();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::Copy()
{
    m_Edit.Copy();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::Cut()
{
    m_Edit.Cut();
}
//---------------------------------------------------------------------------
void PSS_IntelliMultiLineEditBox::Paste()
{
    m_Edit.Paste();
}
//---------------------------------------------------------------------------
BOOL PSS_IntelliMultiLineEditBox::SetReadOnly(BOOL readOnly)
{
    return m_Edit.SetReadOnly(readOnly);
}
//---------------------------------------------------------------------------
int PSS_IntelliMultiLineEditBox::GetFirstVisibleLine() const
{
    return m_Edit.GetFirstVisibleLine();
}
//---------------------------------------------------------------------------

#endif
