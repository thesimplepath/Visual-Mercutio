/****************************************************************************
 * ==> PSS_InPlaceListBox --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place list box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InPlaceListBoxH
#define PSS_InPlaceListBoxH

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
#include "zProperty\PSS_InPlaceEdit.h"

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
* In-place list box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlaceListBox : public CWnd,
                                         public PSS_InPlaceEdit
{
    DECLARE_DYNAMIC(PSS_InPlaceListBox)

    public:
        /**
        * Constructor
        *@param isReadOnly - if true, the edit is read-only
        */
        PSS_InPlaceListBox(bool isReadOnly = false);

        virtual inline ~PSS_InPlaceListBox();

        /**
        * Initializes the edit control
        *@param pItem - the item to link with
        *@param initText - the initial text
        *@param pWndParent - the parent window
        *@param rect - the rect surrounding the control
        *@param exStyle - the extended style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               const CString&    initText,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             exStyle = 0);

        /**
        * Gets the edit text
        *@return the edit text
        */
        virtual CString GetEditText() const;

        /**
        * Sets the edit text value
        *@param text - the text
        */
        virtual void SetEditText(const CString& text);

        /**
        * Gets the current selection index
        *@return the current selection index, -1 if not found or on error
        */
        virtual inline int GetCurrentSelection() const;

        /**
        * Sets the current selection
        *@param select - the selection index
        *@param sendSetData - if true, a message about the newly set data will be sent to observers
        */
        virtual int SetCurSel(int select, bool sendSetData = true);

        /**
        * Sets the current selection
        *@param value - the selection value to show
        *@param sendSetData - if true, a message about the newly set data will be sent to observers
        */
        virtual int SetCurSel(const CString& value, bool sendSetData = true);

        /**
        * Gets the data as a text
        *@return the data as a text
        */
        virtual CString GetTextData() const;

        /**
        * Gets the data as a DWORD value
        *@return the data as a DWORD value
        */
        virtual inline DWORD GetDWordData() const;

        /**
        * Adds a string
        *@param pStrText - the string text to add
        *@param data - the data
        *@return the newly added string index, -1 on error
        */
        virtual int AddString(LPCTSTR pStrText, DWORD data = 0);

        /**
        * Checks if the edit control was hit
        *@param point - the hit point to check
        *@return true if the edit control was hit, otherwise false
        */
        virtual bool IsEditCtrlHit(const CPoint& point) const;

        /**
        * Checks if the edit button control was hit
        *@param point - the hit point to check
        *@return true if the edit button control was hit, otherwise false
        */
        virtual bool IsEditButtonCtrlHit(const CPoint& point) const;

        /**
        * Resets the content
        */
        virtual void ResetContent();

        /**
        * Resets the list box height
        */
        virtual void ResetListBoxHeight();

        /**
        * Cancels the edition
        */
        virtual void CancelEdit();

        /**
        * Saves the edition
        */
        virtual void SaveValue();

        /**
        * Notifies the observers about the pressed key on list box
        *@param key - the pressed key
        */
        virtual void NotifyEditKeyPressed(UINT key);

        /**
        * Notifies the observers that an action was performed on list box
        *@param action - the performed action identifier
        */
        virtual void NotifiyListBoxAction(UINT action);

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /**
        * Child edit
        */
        class IEdit : public CEdit
        {
            public:
                IEdit();
                virtual ~IEdit();

                /**
                * Sets the owner list box
                *@param pOwnerList - the owner list box
                */
                virtual inline void SetOwnerListBox(PSS_InPlaceListBox* pOwnerList);

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IEdit)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IEdit)
                afx_msg BOOL OnEraseBkgnd(CDC* pDC);
                afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

            private:
                PSS_InPlaceListBox* m_pOwnerList;

                /**
                * Copy constructor
                *@param other - other object to copy from
                */
                IEdit(const IEdit& d);

                /**
                * Copy operator
                *@param other - other object to copy from
                *@return copy of itself
                */
                IEdit& operator = (const IEdit& d);
        };

        /**
        * Child list box
        */
        class IListBox : public CListBox
        {
            public:
                IListBox();
                virtual ~IListBox();

                /**
                * Sets the owner list box
                *@param pOwnerList - the owner list box
                */
                virtual inline void SetOwnerListBox(PSS_InPlaceListBox* pOwnerList);

            protected:
                /// ClassWizard generated virtual function overrides
                //{{AFX_VIRTUAL(IListBox)
                virtual BOOL PreTranslateMessage(MSG* pMsg);
                //}}AFX_VIRTUAL

                /// Generated message map functions
                //{{AFX_MSG(IListBox)
                afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
                afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
                //}}AFX_MSG
                DECLARE_MESSAGE_MAP()

                void ProcessSelected(bool bProcess = true);

            private:
                PSS_InPlaceListBox* m_pOwnerList;

                /**
                * Copy constructor
                *@param other - other object to copy from
                */
                IListBox(const IListBox& other);

                /**
                * Copy operator
                *@param other - other object to copy from
                *@return copy of itself
                */
                IListBox& operator = (const IListBox& other);
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InPlaceListBox)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlaceListBox)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnPaint();
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnSetFocus(CWnd* pOldWnd);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Hides the list box
        */
        virtual void HideListBox();

        /**
        * Sets the focus to the edit control
        */
        virtual void SetFocusToEdit();

        /**
        * Moves the selection
        *@param key - the selection key
        */
        void MoveSelection(UINT key);

    private:
        static int m_ButtonDx;
        IEdit      m_Edit;
        IListBox   m_Listbox;
        CString    m_InitialValueText;
        int        m_CurrentSelection;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InPlaceListBox(const PSS_InPlaceListBox& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlaceListBox& operator = (const PSS_InPlaceListBox& other);

        /**
        * Sets the current selection to edit
        *@param index - the selection index
        */
        void SetCurSelToEdit(int index);

        /**
        * Applies the list box value to edit
        */
        void ApplyListBoxValueToEdit();
};

//---------------------------------------------------------------------------
// PSS_InPlaceListBox::IEdit
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::IEdit::SetOwnerListBox(PSS_InPlaceListBox* pOwnerList)
{
    m_pOwnerList = pOwnerList;
}
//---------------------------------------------------------------------------
// PSS_InPlaceListBox::IListBox
//---------------------------------------------------------------------------
void PSS_InPlaceListBox::IListBox::SetOwnerListBox(PSS_InPlaceListBox* pOwnerList)
{
    m_pOwnerList = pOwnerList;
}
//---------------------------------------------------------------------------
// PSS_InPlaceListBox
//---------------------------------------------------------------------------
PSS_InPlaceListBox::~PSS_InPlaceListBox()
{}
//---------------------------------------------------------------------------
int PSS_InPlaceListBox::GetCurrentSelection() const
{
    return m_CurrentSelection;
}
//---------------------------------------------------------------------------
DWORD PSS_InPlaceListBox::GetDWordData() const
{
    return m_CurrentSelection != -1 ? m_Listbox.GetItemData(m_CurrentSelection) : 0;
}
//---------------------------------------------------------------------------

#endif
