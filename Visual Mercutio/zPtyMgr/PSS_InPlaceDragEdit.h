/****************************************************************************
 * ==> PSS_InPlaceDragEdit -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an in-place draggable edit control and several    *
 *               controls based on it                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InPlaceDragEditH
#define PSS_InPlaceDragEditH

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
#include "zBaseLib\PSS_DragEdit.h"
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
* In-place drag edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlaceDragEdit : public PSS_DragEdit,
                                          public PSS_InPlaceEdit
{
    DECLARE_DYNAMIC(PSS_InPlaceDragEdit)

    public:
        inline PSS_InPlaceDragEdit();

        /**
        * Constructor
        *@param initText - the initial text
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlaceDragEdit(const CString& initText, bool isReadOnly = false);

        /**
        * Constructor
        *@param initValue - the initial value
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlaceDragEdit(float  initValue, bool isReadOnly = false);
        inline PSS_InPlaceDragEdit(double initValue, bool isReadOnly = false);

        virtual inline ~PSS_InPlaceDragEdit();

        /**
        * Create the edit control
        *@param initText - the initial text
        *@param pWndParent - the parent window
        *@param rect - the rect surrounding the control
        *@param exStyle - the extended style
        *@return the newly created control, NULL on error
        */
        virtual CWnd* CreateInPlaceEditCtrl(const CString& initText, CWnd* pWndParent, CRect& rect, DWORD exStyle = 0);

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
                                               double            initValue,
                                               CWnd*             pWndParent,
                                               const CRect&      rect,
                                               DWORD             exStyle = 0);
        virtual BOOL InitializeInPlaceEditCtrl(PSS_PropertyItem* pItem,
                                               float             initValue,
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
        * Sets the edit text value
        *@param dateValue - the date value
        */
        virtual void SetEditText(float  value);
        virtual void SetEditText(double value);

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

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InPlaceDragEdit)
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlaceDragEdit)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InPlaceDragEdit(const PSS_InPlaceDragEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlaceDragEdit& operator = (const PSS_InPlaceDragEdit& other);
};

//---------------------------------------------------------------------------
// PSS_InPlaceDragEdit
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::PSS_InPlaceDragEdit() :
    PSS_InPlaceEdit(),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::PSS_InPlaceDragEdit(const CString& initText, bool IsReadOnly) :
    PSS_InPlaceEdit(initText, IsReadOnly),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::PSS_InPlaceDragEdit(double initValue, bool isReadOnly) :
    PSS_InPlaceEdit(initValue, isReadOnly),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::PSS_InPlaceDragEdit(float initValue, bool isReadOnly) :
    PSS_InPlaceEdit(initValue, isReadOnly),
    PSS_DragEdit()
{}
//---------------------------------------------------------------------------
PSS_InPlaceDragEdit::~PSS_InPlaceDragEdit()
{}
//---------------------------------------------------------------------------

/**
* In-place property item string edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlacePropItemStringEdit : public PSS_InPlaceDragEdit
{
    DECLARE_DYNAMIC(PSS_InPlacePropItemStringEdit)

    public:
        /**
        * Constructor
        *@param initText - the initial text
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlacePropItemStringEdit(const CString initText = _T(""), bool isReadOnly = false);

        virtual inline ~PSS_InPlacePropItemStringEdit();

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
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlacePropItemStringEdit)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InPlacePropItemStringEdit(const PSS_InPlacePropItemStringEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlacePropItemStringEdit& operator = (const PSS_InPlacePropItemStringEdit& other);
};

//---------------------------------------------------------------------------
// PSS_InPlaceDragEdit
//---------------------------------------------------------------------------
PSS_InPlacePropItemStringEdit::PSS_InPlacePropItemStringEdit(const CString initText, bool isReadOnly) :
    PSS_InPlaceDragEdit(initText, isReadOnly)
{}
//---------------------------------------------------------------------------
PSS_InPlacePropItemStringEdit::~PSS_InPlacePropItemStringEdit()
{}
//---------------------------------------------------------------------------

/**
* In-place property item number edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InPlacePropItemNumberEdit : public PSS_InPlaceDragEdit
{
    DECLARE_DYNAMIC(PSS_InPlacePropItemNumberEdit)

    public:
        /**
        * Constructor
        *@param value - the initial value
        *@param isReadOnly - if true, the edit is read-only
        */
        inline PSS_InPlacePropItemNumberEdit(float  value,       bool isReadOnly = false);
        inline PSS_InPlacePropItemNumberEdit(double value = 0.0, bool isReadOnly = false);

        virtual inline ~PSS_InPlacePropItemNumberEdit();

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
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_InPlacePropItemNumberEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InPlacePropItemNumberEdit(const PSS_InPlacePropItemNumberEdit& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InPlacePropItemNumberEdit& operator = (const PSS_InPlacePropItemNumberEdit& other);
};

//---------------------------------------------------------------------------
// PSS_InPlacePropItemNumberEdit
//---------------------------------------------------------------------------
PSS_InPlacePropItemNumberEdit::PSS_InPlacePropItemNumberEdit(float value, bool isReadOnly) :
    PSS_InPlaceDragEdit(value, isReadOnly)
{}
//---------------------------------------------------------------------------
PSS_InPlacePropItemNumberEdit::PSS_InPlacePropItemNumberEdit(double value, bool isReadOnly) :
    PSS_InPlaceDragEdit(value, isReadOnly)
{}
//---------------------------------------------------------------------------
PSS_InPlacePropItemNumberEdit::~PSS_InPlacePropItemNumberEdit()
{}
//---------------------------------------------------------------------------

#endif
