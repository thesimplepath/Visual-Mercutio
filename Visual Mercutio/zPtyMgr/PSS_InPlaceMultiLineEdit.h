/****************************************************************************
 * ==> PSS_InPlaceMultiLineEdit --------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place multiline edit                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InPlaceMultiLineEditH
#define PSS_InPlaceMultiLineEditH

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
#include "zBaseLib\PSS_MultiLineEdit.h"
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
* In-place multiline edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlaceMultiLineEdit : public PSS_MultiLineEdit,
                                               public PSS_InPlaceEdit
{
    DECLARE_DYNAMIC(PSS_InPlaceMultiLineEdit)

    public:
        /**
        * Constructor
        *@param isReadOnly - if true, the edit is read-only
        */
        PSS_InPlaceMultiLineEdit(bool isReadOnly = false);

        virtual inline ~PSS_InPlaceMultiLineEdit();

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
        * Initializes the edit control
        *@param pItem - the item to link with
        *@param initValue - the initial value
        *@param pWndParent - the parent window
        *@param rect - the rect surrounding the control
        *@param exStyle - the extended style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               float             initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             exStyle = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               double            initValue,
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
        virtual void SetEditText(const CString& strText);

        /**
        * Sets the edit text value
        *@param value - the value
        */
        virtual void SetEditText(float  value);
        virtual void SetEditText(double value);

        /**
        * Checks if the edit control was hit
        *@param point - the hit point to check
        *@return true if the edit control was hit, otherwise false
        */
        virtual bool IsEditCtrlHit(const CPoint& point) const;

        /**
        * Cancels the edition
        */
        virtual void CancelEdit();

        /**
        * Saves the edition
        */
        virtual void SaveValue();

        /**
        * Gets the edit extended size
        *@return the edit extended size
        */
        virtual inline CSize GetExtendedSize() const;

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Called when the extended command is processed
        */
        virtual void OnExtendedCommand();

        /**
        * Called when the edit text changed
        */
        virtual void OnEditTextChanged();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InPlaceMultiLineEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlaceMultiLineEdit)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnSetFocus(CWnd* pOldWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InPlaceMultiLineEdit(const PSS_InPlaceMultiLineEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlaceMultiLineEdit& operator = (const PSS_InPlaceMultiLineEdit& other);
};

//---------------------------------------------------------------------------
// PSS_InPlaceMultiLineEdit
//---------------------------------------------------------------------------
PSS_InPlaceMultiLineEdit::~PSS_InPlaceMultiLineEdit()
{}
//---------------------------------------------------------------------------
CSize PSS_InPlaceMultiLineEdit::GetExtendedSize() const
{
    return PSS_MultiLineEdit::GetExtendedSize();
}
//---------------------------------------------------------------------------

#endif
