/****************************************************************************
 * ==> PSS_InPlaceTimeEdit -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place time edit                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InPlaceTimeEditH
#define PSS_InPlaceTimeEditH

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
#include "zWinUtil32\PSS_SearchEdit.h"
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
* In-place time edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlaceTimeEdit : public PSS_SearchEdit,
                                          public PSS_InPlaceEdit
{
    DECLARE_DYNAMIC(PSS_InPlaceTimeEdit)

    public:
        /**
        * Constructor
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlaceTimeEdit(bool isReadOnly = false);

        /**
        * Constructor
        *@param timeInitValue - the initial time value
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlaceTimeEdit(const PSS_TimeSpan& timeInitValue, bool isReadOnly = false);

        virtual inline ~PSS_InPlaceTimeEdit();

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
        *@param timeInitValue - the time initial value
        *@param pWndParent - the parent window
        *@param rect - the rect surrounding the control
        *@param exStyle - the extended style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem*   pItem,
                                               const PSS_TimeSpan& timeInitValue,
                                               CWnd*               pWndParent,
                                               const CRect&        rect,
                                               DWORD               exStyle = 0);

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
        * Sets the edit text value
        *@param timeValue - the time value
        */
        virtual void SetEditText(const PSS_TimeSpan& timeValue);

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
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Called when the extended command is processed
        */
        virtual void OnExtendedCommand();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InPlaceTimeEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlaceTimeEdit)
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
        PSS_InPlaceTimeEdit(const PSS_InPlaceTimeEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlaceTimeEdit& operator = (const PSS_InPlaceTimeEdit& other);
};

//---------------------------------------------------------------------------
// PSS_InPlaceTimeEdit
//---------------------------------------------------------------------------
PSS_InPlaceTimeEdit::PSS_InPlaceTimeEdit(bool isReadOnly) :
    PSS_InPlaceEdit(0.0, isReadOnly),
    PSS_SearchEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceTimeEdit::PSS_InPlaceTimeEdit(const PSS_TimeSpan& timeInitValue, bool isReadOnly) :
    PSS_InPlaceEdit(timeInitValue, isReadOnly),
    PSS_SearchEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceTimeEdit::~PSS_InPlaceTimeEdit()
{}
//---------------------------------------------------------------------------

#endif
