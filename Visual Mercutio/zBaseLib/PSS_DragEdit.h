/****************************************************************************
 * ==> PSS_DragEdit --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a base class for drag edit operations             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EditDropTargetH
#define PSS_EditDropTargetH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#ifndef __AFXOLE_H__
    #include <afxole.h>
#endif

// forward class declarations
class PSS_DragEdit;

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
* Edit drop target
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EditDropTarget : public COleDropTarget
{
    public:
        inline PSS_EditDropTarget();

        /**
        * Registers the drop target
        *@param pEdit - target edit
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Register(PSS_DragEdit* pEdit);

        /**
        * Called when a draggable item enters a valid drop target
        *@param pWnd - window
        *@param pDataObject - dropped data object
        *@param keyState - special keys state
        *@param point - point where drag is entered
        *@return drop effect to apply
        */
        virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD keyState, CPoint point);

        /**
        * Called when a draggable item leaves a valid drop target
        *@param pWnd - window
        */
        virtual void OnDragLeave(CWnd* pWnd);

        /**
        * Called when a draggable item hovers a valid drop target
        *@param pWnd - window
        *@param pDataObject - dropped data object
        *@param keyState - special keys state
        *@param point - point where drag is entered
        *@return drop effect to apply
        */
        virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

        /**
        * Called when a draggable item is scrolled into a valid drop target
        *@param pWnd - window
        *@param keyState - special keys state
        *@param point - point where drag is entered
        *@return drop effect to apply
        */
        virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);

        /**
        * Called when an item is dropped on the target
        *@param pWnd - window
        *@param pDataObject - dropped data object
        *@param dropEffect - drop effect
        *@param point - drop point
        *@return TRUE if drop is allowed, otherwise FALSE
        */
        virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

    private:
        PSS_DragEdit* m_pEditCtl;
        BOOL          m_BeginDrop;
};

//---------------------------------------------------------------------------
// PSS_EditDropTarget
//---------------------------------------------------------------------------
PSS_EditDropTarget::PSS_EditDropTarget() :
    COleDropTarget(),
    m_pEditCtl(NULL),
    m_BeginDrop(FALSE)
{}
//---------------------------------------------------------------------------

/**
* Edit data source
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBEditDataSource : public COleDataSource
{};

/**
* Drag edit base
*@author Dominique Aigroz, Jean-Milost Reymond
*/
#define PSS_DragEditBase CEdit

/**
* Drag edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DragEdit : public PSS_DragEditBase
{
    public:
        /**
        * Drag enable type
        *@note These items may be cobmbinated
        */
        enum IEEnableType
        {
            IE_ET_DRAG = 0x1,
            IE_ET_DROP = 0x2
        };

        PSS_DragEdit();
        virtual ~PSS_DragEdit();

        /**
        * Initializes the drag
        *@param flags - flags
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Init(int flags = (IE_ET_DRAG | IE_ET_DROP));

        /**
        * Checks if edit is in dragging
        *@return TRUE if edit is in dragging, otherwise FALSE
        */
        virtual inline BOOL IsInDragging() const;

        /**
        * Sets drop equals drag
        *@param equal - if TRUE, the drop will be equals to drag
        */
        virtual inline void SetDropEqualDrag(BOOL equal);

        /**
        * Sets the drop position
        *@param line - line
        *@param pos - position
        */
        virtual inline void SetDropPos(int line, int pos);

        /**
        * Gets the line and pos information from current selection range
        *@param[out] line1 - first line
        *@param[out] pos1 - first position
        *@param[out] line2 - second line
        *@param[out] pos2 - second position
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetCurRange(int& line1, int& pos1, int& line2, int& pos2) const;

        /**
        * Gets line and position from current cursor position
        *@param[out] line - line
        *@param[out] pos - position
        *@return TRUE if cursor is exactly on a char, FALSE if cursor is on white space area
        */
        virtual BOOL GetLinePosByCursor(int& line, int& pos) const;

        /**
        * Sets the edit caret position by current cursor position
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetCaretByCursor();

        /**
        * Sets the caret position
        *@param line - line
        *@param pos - position
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetCaret(int line, int pos);

        /**
        * Deselects all the texts in the control
        */
        virtual inline void SetSelNone();

        /**
        * Selects all the texts in the control
        */
        virtual inline void SetSelAll();

        /**
        * Draws a caret at current cursor position
        *@return TRUE on success, otherwise FALSE
        *@note This function will not affect the caret position or selection status
        */
        virtual BOOL DrawCaretByCursor() const;

        /**
        * Gets the position from line position
        *@param line - first line
        *@param pos - first position
        *@return the position
        */
        virtual inline CPoint GetPosFromLinePos(int line, int pos) const;

        /**
        * Gets the position from a char
        *@param ch - character
        *@return the position, (-1, -1) if the character is the last one
        *@note this function is reimplemented to fix a SDK bug
        */
        virtual CPoint PosFromChar(UINT ch) const;

        /**
        * Checks if the cursor is within the selection mark
        *@return TRUE if the caret is inside the selection range, otherwise FALSE
        */
        virtual BOOL IsInSelRange() const;

        /**
        * Checks if the dragging is enabled
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL EnableDrag() const;

        /**
        * Checks if the dropping is enabled
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL EnableDrop() const;

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DragEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DragEdit)
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when content is about to be deleted
        */
        void DoDelete();

        /**
        * Notifies the parent
        *@param msg - notification message
        */
        void NotifyParent(UINT msg);

    private:
        static BOOL        m_OleInit;
        ZBEditDataSource   m_DropSource;
        PSS_EditDropTarget m_DropTarget;
        int                m_EnableFlags;
        int                m_DropPtLine;
        int                m_DropPtPos;
        BOOL               m_DragInit;
        BOOL               m_InDragging;
        BOOL               m_DropEqualDrag;

        /**
        * Gets the selected text
        *@param[out] str - string containing the selected text
        *@return TRUE on success, otherwise FALSE
        */
        BOOL GetSelText(CString& str);

        /**
        * Gets the line position from char
        *@param ch - character
        *@param pLine - line
        *@param pPos - position
        */
        inline void CharToLinePos(int ch, int* pLine, int* pPos) const;

        /**
        * Gets the char from line position
        *@param line - line
        *@param pos - position
        *@return the character
        */
        inline int LinePosToChar(int line, int pos) const;

        /**
        * Replaces the selected string by another
        *@param pNew - new string to replace by
        *@param start - selection start position
        *@param stop - selection stop position
        *@param str - string containing the text to replace
        */
        void ReplaceSelString(LPCTSTR pNew, int iStart, int iStop, CString& str) const;
};

//---------------------------------------------------------------------------
// PSS_DragEdit
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::IsInDragging() const
{
    return m_InDragging;
}
//---------------------------------------------------------------------------
void PSS_DragEdit::SetDropEqualDrag(BOOL equal)
{
    m_DropEqualDrag = equal;
}
//---------------------------------------------------------------------------
void PSS_DragEdit::SetDropPos(int line, int pos)
{
    m_DropPtLine = line,
    m_DropPtPos  = pos;
}
//---------------------------------------------------------------------------
void PSS_DragEdit::SetSelNone()
{
    SetSel(-1, 0);
}
//---------------------------------------------------------------------------
void PSS_DragEdit::SetSelAll()
{
    SetSel(0, -1);
}
//---------------------------------------------------------------------------
CPoint PSS_DragEdit::GetPosFromLinePos(int line, int pos) const
{
    return PosFromChar(LinePosToChar(line, pos));
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::EnableDrag() const
{
    return (m_EnableFlags & IE_ET_DRAG);
}
//---------------------------------------------------------------------------
BOOL PSS_DragEdit::EnableDrop() const
{
    return (m_EnableFlags & IE_ET_DROP);
}
//---------------------------------------------------------------------------
void PSS_DragEdit::CharToLinePos(int ch, int* pLine, int* pPos) const
{
    if (ch < 0)
        ch = 0;

    if (pLine)
    {
        *pLine = LineFromChar(ch);

        if (pPos)
            *pPos = ch - LineIndex(*pLine);
    }
}
//---------------------------------------------------------------------------
int PSS_DragEdit::LinePosToChar(int line, int pos) const
{
    return LineIndex(line) + pos;
}
//---------------------------------------------------------------------------

#endif
