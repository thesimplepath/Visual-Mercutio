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
#include "FieldRep.h"
#include "MskEdit.h"
#include "ZCGridCtrl.h"
#include "ZBDragEdit.h"
#include "ZCIntelliEdit.h"
#include "sphelp.h"

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
        virtual void PreCreateEdit(BOOL               designerMode,
                                   CWnd*              pParentWnd,
                                   CDC*               pDC,
                                   ZDDocument*        pDoc,
                                   PlanFinObject*     pEditedObj,
                                   ZBFieldRepository* pFieldRepository    = NULL,
                                   BOOL               autoCalculateOption = FALSE,
                                   BOOL               goNextEditOption    = FALSE);

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
        virtual void Create(BOOL               designerMode,
                            CWnd*              pParentWnd,
                            CDC*               pDC,
                            ZDDocument*        pDoc,
                            PlanFinObject*     pEditedObj,
                            ZBFieldRepository* pFieldRepository    = NULL,
                            BOOL               autoCalculateOption = FALSE,
                            BOOL               goNextEditOption    = FALSE) = 0;

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
        virtual inline SpecialHelp* GetSpecialHelp() const;

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
        CWnd*              m_pParentWnd;
        SpecialHelp*       m_pSpecialHelp;
        PlanFinObject*     m_pEditedObj;
        ZDDocument*        m_pDoc;
        ZBFieldRepository* m_pFieldRepository;
        CRect              m_Rect;
        BOOL               m_Save;
        BOOL               m_GoNext;
        BOOL               m_AutoCalculateOption;
        BOOL               m_GoNextEditOption;
        BOOL               m_ReadOnly;
        BOOL               m_IsSorted;

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
SpecialHelp* PSS_Edit::GetSpecialHelp() const
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
class AFX_EXT_CLASS PSS_StrEdit : public ZBDragEdit, public PSS_Edit
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
        virtual void Create(BOOL               designerMode,
                            CWnd*              pParentWnd,
                            CDC*               pDC,
                            ZDDocument*        pDoc,
                            PlanFinObject*     pEditedObj,
                            ZBFieldRepository* pFieldRepository = NULL,
                            BOOL               autoCalculateOption = FALSE,
                            BOOL               goNextEditOption = FALSE);

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
        virtual inline void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

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
    return (::IsWindow(GetSafeHwnd()) && ZBDragEdit::IsWindowVisible());
}
//---------------------------------------------------------------------------
void PSS_StrEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZBDragEdit::MapWindowPoints(pwndTo, lpRect);
}
//---------------------------------------------------------------------------

class AFX_EXT_CLASS NumEdit : public ZBDragEdit, public PSS_Edit
{
    // Construction
public:

    NumEdit();
    virtual ~NumEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(NumEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL NumEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZBDragEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void NumEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZBDragEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// CalcEdit window

class AFX_EXT_CLASS CalcEdit : public ZBDragEdit, public PSS_Edit
{
    // Construction
public:

    CalcEdit();
    virtual ~CalcEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CalcEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL CalcEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZBDragEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void CalcEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZBDragEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// TimeEdit window

class AFX_EXT_CLASS TimeEdit : public ZBDragEdit, public PSS_Edit
{
    // Construction
public:

    TimeEdit();
    virtual ~TimeEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(TimeEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL TimeEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZBDragEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void TimeEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZBDragEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// StrEditHistoric window

class AFX_EXT_CLASS StrEditHistoric : public ZCIntelliEdit, public PSS_Edit
{
    // Construction
public:

    StrEditHistoric(int iMaxChar = -1);
    virtual ~StrEditHistoric();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    int GetMaxChar() const
    {
        return m_iMaxChar;
    };

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(StrEditHistoric)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Attributes
private:

    int m_iMaxChar;
};

inline BOOL StrEditHistoric::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void StrEditHistoric::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCIntelliEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS NumEditHistoric : public ZCIntelliEdit, public PSS_Edit
{
    // Construction
public:

    NumEditHistoric();
    virtual ~NumEditHistoric();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(NumEditHistoric)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL NumEditHistoric::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void NumEditHistoric::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCIntelliEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// FieldNameEdit window

class AFX_EXT_CLASS FieldNameEdit : public ZCIntelliEdit, public PSS_Edit
{
    // Construction
public:

    FieldNameEdit(int iMaxChar = -1);
    virtual ~FieldNameEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Operations
protected:
    // Generated message map functions
    //{{AFX_MSG(FieldNameEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Attributes
private:

    int m_iMaxChar;
};

inline BOOL FieldNameEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZCIntelliEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void FieldNameEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCIntelliEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// MaskEdit window

class AFX_EXT_CLASS MaskEdit : public ZMaskEdit, public PSS_Edit
{
    // Construction
public:

    MaskEdit();
    virtual ~MaskEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Operations
protected:

    // Generated message map functions
    //{{AFX_MSG(MaskEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL MaskEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZMaskEdit::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void MaskEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZMaskEdit::MapWindowPoints(pwndTo, lpRect);
}

/////////////////////////////////////////////////////////////////////////////
// MultiColumnEdit window

class AFX_EXT_CLASS MultiColumnEdit : public ZCGridCtrl, public PSS_Edit
{
    // Construction
public:

    MultiColumnEdit();
    virtual ~MultiColumnEdit();

    virtual void Create(BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*        pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository = NULL,
                        BOOL                AutoCalculateOption = FALSE,
                        BOOL                GoNextEditOption = FALSE);

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints(CWnd* pwndTo, LPRECT lpRect);

    // Called before editing the cell
    virtual void OnBeginLabelEdit(int iItem, int iSubItem);

    // Called after having updated the cell
    virtual void OnEndLabelEdit(LPCSTR pszText, int iItem, int iSubItem);

    // Operations
protected:

    // Generated message map functions
    //{{AFX_MSG(MultiColumnEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void BuildColumns();
    void FillControl();

    // Attributes
private:

    int        m_cx;
    BOOL    m_nEdit;
    BOOL    m_ColumnsBuilt;
    bool    m_StartEditCell;
};

inline BOOL MultiColumnEdit::IsWindowVisible()
{
    if (::IsWindow(GetSafeHwnd()) && ZCGridCtrl::IsWindowVisible())
    {
        return TRUE;
    }

    return FALSE;
}

inline void MultiColumnEdit::MapWindowPoints(CWnd* pwndTo, LPRECT lpRect)
{
    ZCGridCtrl::MapWindowPoints(pwndTo, lpRect);
}

#endif
