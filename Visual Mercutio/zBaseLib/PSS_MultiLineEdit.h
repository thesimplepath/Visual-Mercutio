/****************************************************************************
 * ==> PSS_MultiLineEdit ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a multiline edit box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MultiLineEditH
#define PSS_MultiLineEditH

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
#include "PSS_IntelliMultiLineEditBox.h"
#include "PSS_DragEdit.h"

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
* Multiline edit button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MultiLineEditBtn : public CButton
{
    public:
        PSS_MultiLineEditBtn();
        virtual ~PSS_MultiLineEditBtn();

        /**
        * Creates the component
        *@param pEdit - parent edit
        *@param pSize - size
        *@param expanded - if true, the button will be expanded
        *@param resizeParent - if true, the parent may be resized to fit the button
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_MultiLineEdit* pEdit, CSize* pSize = NULL, bool expanded = true, bool resizeParent = true);

        /**
        * Gets the next component identifier
        *@param pWnd - parent window owning the components
        *@return the next component identifier
        */
        virtual UINT GetNextID(CWnd* pWnd) const;

        /**
        * Sets the multiline edit box size
        *@param size - size
        */
        virtual inline void SetMultiLineEditBoxSize(const CSize& size);

    protected:
        PSS_MultiLineEdit* m_pEdit;
        CFont              m_Font;
        CSize              m_Size;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_MultiLineEditBtn)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_MultiLineEditBtn)
        afx_msg void OnClicked();
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_MultiLineEditBtn
//---------------------------------------------------------------------------
void PSS_MultiLineEditBtn::SetMultiLineEditBoxSize(const CSize& size)
{
    m_Size = size;
}
//---------------------------------------------------------------------------

/**
* Expanded multiline edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ExpandedMultiLineEdit : public PSS_DragEdit
{
    public:
        /**
        * Constructor
        *@param pEditCtrl - parent edit control, can be NULL
        *@param size - size
        */
        PSS_ExpandedMultiLineEdit(PSS_MultiLineEdit* pEditCtrl = NULL, const CSize& size = CSize(0, 0));

        virtual ~PSS_ExpandedMultiLineEdit();

        /**
        * Creates the component
        *@param pEditCtrl - parent edit control
        *@param size - size
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_MultiLineEdit* pEditCtrl, const CSize& size = CSize(0, 0));

        /**
        * Sets the edit control
        *@param pEditCtrl - parent edit control
        *@param size - size
        */
        virtual void SetEditControl(PSS_MultiLineEdit* pEditCtrl, const CSize& size = CSize(0, 0));

        /**
        * Gets the extended size
        *@return the extended size
        */
        virtual inline CSize GetExtendedSize() const;

    protected:
        CString m_EditValue;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ExpandedMultiLineEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ExpandedMultiLineEdit)
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_MultiLineEdit* m_pEditCtrl;
        CSize              m_Size;
        int                m_MultiLineEditBoxHeight;
        bool               m_BeingResized;
};

//---------------------------------------------------------------------------
// PSS_ExpandedMultiLineEdit
//---------------------------------------------------------------------------
CSize PSS_ExpandedMultiLineEdit::GetExtendedSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------

/**
* Multiline edit box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MultiLineEdit : public PSS_DragEdit
{
    public:
        /**
        * Constructor
        *@param editValue - edit text value
        *@param pSize - size
        */
        PSS_MultiLineEdit(const CString& editValue = "", CSize* pSize = NULL);

        virtual ~PSS_MultiLineEdit();

        /**
        * Initializes the component
        *@param editValue - edit text value
        *@param pSize - size
        */
        virtual void Initialize(const CString& editValue, CSize* pSize = NULL);

        /**
        * Initializes the component
        *@param size - size
        */
        virtual void Initialize(const CSize& size);

        /**
        * Initializes the component
        */
        virtual void Initialize();

        /**
        * Sets the edit text
        *@param editValue - edit text value
        *@param reload - if true, the text will be reloaded immediately
        */
        virtual void SetEditText(const CString& editValue, bool reload = true);

        /**
        * Sets the multiline edit text
        *@param editValue - edit text value
        */
        virtual inline void SetMultiLineEditBoxText(const CString& editValue);

        /**
        * Expands the base edit
        */
        virtual void ExpandBaseEdit();

        /**
        * Collapses the base edit
        *@param copyTextBack - if true, the text will be copied back
        */
        virtual void CollapseBaseEdit(bool copyTextBack = true);

        /**
        * Checks if edit is expanded
        *@return true if edit is expanded, otherwise false
        */
        virtual inline bool EditIsExpanded() const;

        /**
        * Gets the extended size
        *@return the extended size
        */
        virtual inline CSize GetExtendedSize() const;

        /**
        * Called when the extended size has changed
        *@param cx - new width
        *@param cy - new height
        */
        virtual void OnExtendedSizeHasChanged(int cx, int cy);

        /**
        * Checks if the component has the focus
        *@return true if the component has the focus, otherwise false
        */
        virtual inline bool HasFocus() const;

        /**
        * Checks if the multiline edit box is visible
        *@return true if the multiline edit box is visible, otherwise false
        */
        virtual inline bool IsMultiLineEditBoxVisible() const;

        /**
        * Shows the multiline edit box
        */
        virtual inline void ShowMultiLineEditBox();

        /**
        * Hidesthe multiline edit box
        */
        virtual inline void HideMultiLineEditBox();

        /**
        * Called when the multiline edit box enters
        */
        virtual void OnMultiLineEditBoxEnter();

        /**
        * Called when the multiline edit box escapes
        */
        virtual void OnMultiLineEditBoxEscape();

        /**
        * Validates the typed char
        *@param ch - the char to validate
        *@param editText - the edit text
        *@return true if the typed char is allowed, otherwise false
        */
        virtual bool ValidateChar(UINT ch, const CString& editText) const;

        /**
        * Called when the edit text changed
        */
        virtual void OnEditTextChanged();

        /**
        * Called when enter key is pressed
        */
        virtual void OnEnter();

        /**
        * Called when escape key is pressed
        */
        virtual void OnEscape();

    protected:
        PSS_MultiLineEditBtn m_ExpandedButton;
        PSS_MultiLineEditBtn m_CollapsedButton;
        CString              m_EditValue;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_MultiLineEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_MultiLineEdit)
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Sets the new style
        *@param styleMask - style mask
        *@param setBits - if TRUE, the bits will be set
        */
        virtual void SetNewStyle(long lStyleMask, BOOL bSetBits);

        /**
        * Destroys the component
        */
        virtual void DestroyEdit();

    private:
        PSS_ExpandedMultiLineEdit m_ExpandedEditBox;
        CRect                     m_InitialRect;
        CSize                     m_Size;
        int                       m_MultiLineEditBoxHeight;
        bool                      m_HasFocus;
        bool                      m_BeingResized;
        bool                      m_InCreationProcess;
        bool                      m_EditIsExpanded;

        /**
        * Calculates the size and position
        */
        void CalculateSizeAndPosition();

        /**
        * Gets the multiline edit text selection
        *@param[out] text - the multiline edit text selection on function ends
        */
        inline void GetMultiLineEditBoxText(CString& text);
};

//---------------------------------------------------------------------------
// PSS_MultiLineEdit
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::SetMultiLineEditBoxText(const CString& editValue)
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;

    m_ExpandedEditBox.SetWindowText(editValue);
}
//---------------------------------------------------------------------------
bool PSS_MultiLineEdit::EditIsExpanded() const
{
    return m_EditIsExpanded;
}
//---------------------------------------------------------------------------
CSize PSS_MultiLineEdit::GetExtendedSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------
bool PSS_MultiLineEdit::HasFocus() const
{
    return m_HasFocus;
}
//---------------------------------------------------------------------------
bool PSS_MultiLineEdit::IsMultiLineEditBoxVisible() const
{
    return (::IsWindow(m_ExpandedEditBox.GetSafeHwnd()) && m_ExpandedEditBox.IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::ShowMultiLineEditBox()
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;

    m_ExpandedEditBox.ShowWindow(SW_SHOW);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::HideMultiLineEditBox()
{
    if (!::IsWindow(m_ExpandedEditBox.GetSafeHwnd()))
        return;

    m_ExpandedEditBox.ShowWindow(SW_HIDE);
}
//---------------------------------------------------------------------------
void PSS_MultiLineEdit::GetMultiLineEditBoxText(CString& text)
{
    m_ExpandedEditBox.GetWindowText(text);
}
//---------------------------------------------------------------------------

#endif
