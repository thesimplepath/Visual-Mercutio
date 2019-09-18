/****************************************************************************
 * ==> PSS_Edit ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides several edit components                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EditH
#define PSS_EditH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_FieldRepository.h"
#include "PSS_MaskEditBase.h"
#include "ZCGridCtrl.h"
#include "PSS_DragEdit.h"
#include "ZCIntelliEdit.h"
#include "PSS_SpecialHelpWnd.h"

// forward classes declaration
class ZDDocument;

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
* Basic edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Edit
{
    public:
        PSS_Edit();
        virtual ~PSS_Edit();

        /**
        * Pre-creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void PreCreateEdit(BOOL                 designerMode,
                                   CWnd*                pParentWnd,
                                   CDC*                 pDC,
                                   ZDDocument*          pDoc,
                                   PSS_PlanFinObject*   pEditedObj,
                                   PSS_FieldRepository* pFieldRepository    = NULL,
                                   BOOL                 autoCalculateOption = FALSE,
                                   BOOL                 goNextEditOption    = FALSE);

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE) = 0;

        /**
        * Checks the edit bounds
        *@param pDC - device context
        *@param pParentWnd - parent window
        *@param rect - rect to check
        *@return the edit bounds rect
        */
        virtual CRect CheckBounds(CDC* pDC, CWnd *pParentWnd, const CRect& rct);

        /**
        * Gets the specialized help functions
        *@return the specialized help functions
        */
        virtual inline PSS_SpecialHelpWnd* GetSpecialHelp() const;

        /**
        * Gets the client rect
        *@param[out] rect - client rect
        */
        virtual inline void GetClientRect(CRect& Rect) const;

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Sets content is modified flag
        *@param modify - if TRUE, the content will be set as modified
        */
        virtual inline void SetModify(BOOL modify);

        /**
        * Sets the go to next edit flag
        *@param next - if TRUE, the focus will be set to next available edit on exit
        */
        virtual inline void SetGoNext(BOOL next);

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit resources
        */
        virtual void DestroyEdit();

    protected:
        CWnd*                m_pParentWnd;
        PSS_SpecialHelpWnd*  m_pSpecialHelp;
        PSS_PlanFinObject*   m_pEditedObj;
        ZDDocument*          m_pDoc;
        PSS_FieldRepository* m_pFieldRepository;
        CRect                m_Rect;
        BOOL                 m_Save;
        BOOL                 m_GoNext;
        BOOL                 m_AutoCalculateOption;
        BOOL                 m_GoNextEditOption;
        BOOL                 m_ReadOnly;
        BOOL                 m_IsSorted;

        /**
        * Gets the value array
        *@return the value array
        */
        virtual CStringArray* GetArrayOfValues();

        /**
        * Adds string to historic
        *@param str - string to add
        */
        virtual void AddToHistoric(const CString& str);

        /**
        * Loads combobox from historic
        *@param combobox - combobox to populate with historic
        */
        virtual void LoadFromHistoric(CComboBox& combobox);

    private:
        /**
        * Creates the specialized help functions
        *@param designer - if TRUE, edit is opened in designer mode
        */
        void CreateSpecialHelp(BOOL designer = FALSE);
};

//---------------------------------------------------------------------------
// PSS_Edit
//---------------------------------------------------------------------------
PSS_SpecialHelpWnd* PSS_Edit::GetSpecialHelp() const
{
    return m_pSpecialHelp;
}
//---------------------------------------------------------------------------
void PSS_Edit::GetClientRect(CRect& Rect) const
{
    Rect = m_Rect;
}
//---------------------------------------------------------------------------
BOOL PSS_Edit::IsWindowVisible()
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_Edit::SetModify(BOOL modify)
{
    m_Save = modify;
}
//---------------------------------------------------------------------------
void PSS_Edit::SetGoNext(BOOL next)
{
    m_GoNext = next;
}
//---------------------------------------------------------------------------

/**
* String edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StrEdit : public PSS_DragEdit, public PSS_Edit
{
    public:
        /**
        * Constructor
        *@param multiline - if TRUE, the edit component will support the multiline
        *@param maxChar - maximum allowed chars, infinite if -1
        */
        PSS_StrEdit(BOOL multiLine = FALSE, int maxChar = -1);

        virtual ~PSS_StrEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_StrEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        int  m_MaxChar;
        BOOL m_MultiLine;
};

//---------------------------------------------------------------------------
// PSS_StrEdit
//---------------------------------------------------------------------------
BOOL PSS_StrEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && PSS_DragEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_StrEdit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    PSS_DragEdit::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Numeric edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NumEdit : public PSS_DragEdit, public PSS_Edit
{
    public:
        PSS_NumEdit();
        virtual ~PSS_NumEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_NumEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_NumEdit
//---------------------------------------------------------------------------
BOOL PSS_NumEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && PSS_DragEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_NumEdit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    PSS_DragEdit::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Calculation edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CalcEdit : public PSS_DragEdit, public PSS_Edit
{
    public:
        PSS_CalcEdit();
        virtual ~PSS_CalcEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        // Generated message map functions
        //{{AFX_MSG(PSS_CalcEdit)
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_CalcEdit
//---------------------------------------------------------------------------
BOOL PSS_CalcEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && PSS_DragEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_CalcEdit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    PSS_DragEdit::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Time edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TimeEdit : public PSS_DragEdit, public PSS_Edit
{
    public:
        PSS_TimeEdit();
        virtual ~PSS_TimeEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_TimeEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_TimeEdit
//---------------------------------------------------------------------------
BOOL PSS_TimeEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && PSS_DragEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_TimeEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    PSS_DragEdit::MapWindowPoints(pwndTo, lpRect);
}
//---------------------------------------------------------------------------

/**
* Historic edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StrEditHistoric : public ZCIntelliEdit, public PSS_Edit
{
    public:
        /**
        * Constructor
        *@param maxChar - maximum allowed chars, infinite if -1
        */
        PSS_StrEditHistoric(int maxChar = -1);

        virtual ~PSS_StrEditHistoric();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets the maximum char
        *@return the maximum char
        */
        virtual inline int GetMaxChar() const;

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_StrEditHistoric)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        int m_MaxChar;
};

//---------------------------------------------------------------------------
// PSS_StrEditHistoric
//---------------------------------------------------------------------------
int PSS_StrEditHistoric::GetMaxChar() const
{
    return m_MaxChar;
}
//---------------------------------------------------------------------------
BOOL PSS_StrEditHistoric::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_StrEditHistoric::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCIntelliEdit::MapWindowPoints(pwndTo, lpRect);
}
//---------------------------------------------------------------------------

/**
* Numeric historic edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NumEditHistoric : public ZCIntelliEdit, public PSS_Edit
{
    public:
        PSS_NumEditHistoric();
        virtual ~PSS_NumEditHistoric();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_NumEditHistoric)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_NumEditHistoric
//---------------------------------------------------------------------------
BOOL PSS_NumEditHistoric::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_NumEditHistoric::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    ZCIntelliEdit::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Field name edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldNameEdit : public ZCIntelliEdit, public PSS_Edit
{
    public:
        /**
        * Constructor
        *@param maxChar - maximum allowed chars, infinite if -1
        */
        PSS_FieldNameEdit(int maxChar = -1);

        virtual ~PSS_FieldNameEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_FieldNameEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        int m_MaxChar;
};

//---------------------------------------------------------------------------
// PSS_FieldNameEdit
//---------------------------------------------------------------------------
BOOL PSS_FieldNameEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_FieldNameEdit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    ZCIntelliEdit::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Mask edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MaskEdit : public PSS_MaskEditBase, public PSS_Edit
{
    public:
        PSS_MaskEdit();
        virtual ~PSS_MaskEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_MaskEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
// PSS_MaskEdit
//---------------------------------------------------------------------------
BOOL PSS_MaskEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && PSS_MaskEditBase::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_MaskEdit::MapWindowPoints(CWnd* pWndTo, LPRECT pRect)
{
    PSS_MaskEditBase::MapWindowPoints(pWndTo, pRect);
}
//---------------------------------------------------------------------------

/**
* Multi-coluns edit component
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MultiColumnEdit : public ZCGridCtrl, public PSS_Edit
{
    public:
        PSS_MultiColumnEdit();
        virtual ~PSS_MultiColumnEdit();

        /**
        * Creates the edit
        *@param designerMode - if TRUE, the edit will be created in designer mode
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        *@param pEditedObj - edited object
        *@param pFieldRepository - field repository, can be NULL
        *@param autoCalculateOption - if TRUE, the options will be auto-calculated
        *@param goNextEditOption - if TRUE, the focus will be set to next available edit on exit
        */
        virtual void Create(BOOL                 designerMode,
                            CWnd*                pParentWnd,
                            CDC*                 pDC,
                            ZDDocument*          pDoc,
                            PSS_PlanFinObject*   pEditedObj,
                            PSS_FieldRepository* pFieldRepository    = NULL,
                            BOOL                 autoCalculateOption = FALSE,
                            BOOL                 goNextEditOption    = FALSE);

        /**
        * Gets if window is visible
        *@return TRUE if window is visible, otherwise FALSE
        */
        virtual inline BOOL IsWindowVisible();

        /**
        * Maps the window points
        *@param pWndTo - window to point to
        *@param pRect - rect
        */
        virtual inline void MapWindowPoints(CWnd* pWndTo, LPRECT pRect);

        /**
        * Destroys the edit
        */
        virtual void DestroyEdit();

        /**
        * Called before editing the cell
        *@param item - item
        *@param subItem - sub-item
        */
        virtual void OnBeginLabelEdit(int item, int subItem);

        /**
        * Called after having updated the cell
        *@param pText - text
        *@param item - item
        *@param subItem - sub-item
        */
        virtual void OnEndLabelEdit(LPCSTR pText, int item, int subItem);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_MultiColumnEdit)
        afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        int  m_Cx;
        BOOL m_Edit;
        BOOL m_ColumnsBuilt;
        bool m_StartEditCell;

        /**
        * Builds the columns
        */
        void BuildColumns();

        /**
        * Fills the control
        */
        void FillControl();
};

//---------------------------------------------------------------------------
// PSS_MultiColumnEdit
//---------------------------------------------------------------------------
BOOL PSS_MultiColumnEdit::IsWindowVisible()
{
    return (::IsWindow(GetSafeHwnd()) && ZCGridCtrl::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_MultiColumnEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCGridCtrl::MapWindowPoints(pwndTo, lpRect);
}
//---------------------------------------------------------------------------

#endif
