//---------------------------------------------------------------------------
// Author    : Dominique Aigroz            
// HeaderFile: edit.h
// Created   : 14.12.1994
// Modify    :           
//
//
//                 Classes Edit,  StrEdit, StrEditHistoric
//                    in charge of edition.
//
//---------------------------------------------------------------------------

#if !defined(__EDIT_H)
#define __EDIT_H

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// FieldRep
#include "FieldRep.h"
#include "MskEdit.h"
#include "ZCGridCtrl.h"
#include "ZBDragEdit.h"
#include "ZCIntelliEdit.h"

#include "sphelp.h"

// Forward declaration
class ZDDocument;

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Edit window

class AFX_EXT_CLASS Edit
{
// Construction
public:

    Edit();
    virtual ~Edit();

    void PreCreateEdit( BOOL                DesignerMode,
                        CWnd*                pParentWnd,
                        CDC*                pDC,
                        ZDDocument*            pDoc,
                        PlanFinObject*        pEditedObj,
                        ZBFieldRepository*    pFieldRepository    = NULL,
                        BOOL                AutoCalculateOption    = FALSE,
                        BOOL                GoNextEditOption    = FALSE );

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE ) = 0;

    virtual CRect CheckBounds( CDC* pDC, CWnd *pParentWnd, CRect& rct );

    // Special help functions
    SpecialHelp* GetSpecialHelp() const
    {
        return m_pSpecialHelp;
    };

    void GetClientRect( CRect& Rect ) const
    {
        Rect = m_Rect;
    };

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible()
    {
        return FALSE;
    };

    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
    {
    };

// Implementation
public:

    void SetModify( BOOL bModify );

    void SetGoNext( BOOL bNext )
    {
        m_GoNext = bNext;
    };

    virtual void DestroyEdit()
    {
    };

protected:

    CStringArray*    GetArrayOfValues();
    void             AddToHistoric( CString str );
    void            LoadFromHistoric( CComboBox& Combo );

// Operations
private:

    void CreateSpecialHelp( BOOL Designer = FALSE );

// Attributes
protected:

    CWnd*                    m_pParentWnd;
     SpecialHelp*            m_pSpecialHelp;            // The specialized helper
     BOOL                    m_Save;                    // Flag to say if save is necessary or not
    BOOL                    m_GoNext;                // Flag to say if it is necessary
                                                    // to go directly to the next editable
                                                    // field
    PlanFinObject*            m_pEditedObj;            // Pointer to the Edited Object
    ZDDocument*                m_pDoc;                    // Pointer to the current document
    ZBFieldRepository*        m_pFieldRepository;        // Saves the pointer of the field repository
    BOOL                    m_AutoCalculateOption;
    BOOL                    m_GoNextEditOption;
    BOOL                    m_ReadOnly;
    BOOL                    m_IsSorted;
    CRect                    m_Rect;
};

// inline functions ----------------------------------------------------------

inline void Edit::SetModify( BOOL bModify )
{
    m_Save = bModify;
}

/////////////////////////////////////////////////////////////////////////////
// StrEdit window

class AFX_EXT_CLASS StrEdit : public ZBDragEdit, public Edit
{
// Construction
public:

    StrEdit( BOOL bMultiLine = FALSE, int iMaxChar = -1 );
    virtual ~StrEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

// Attributes
private:

    BOOL    m_bMultiLine;
    int        m_iMaxChar;

// Operations
protected:

    // Generated message map functions
    //{{AFX_MSG(StrEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

inline BOOL StrEdit::IsWindowVisible()
{
    if ( ::IsWindow( GetSafeHwnd() ) && ZBDragEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void StrEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZBDragEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// NumEdit window

class AFX_EXT_CLASS NumEdit : public ZBDragEdit, public Edit
{
// Construction
public:

    NumEdit();
    virtual ~NumEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZBDragEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void NumEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZBDragEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// CalcEdit window

class AFX_EXT_CLASS CalcEdit : public ZBDragEdit, public Edit
{
// Construction
public:

    CalcEdit();
    virtual ~CalcEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZBDragEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void CalcEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZBDragEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// TimeEdit window

class AFX_EXT_CLASS TimeEdit : public ZBDragEdit, public Edit
{
// Construction
public:

    TimeEdit();
    virtual ~TimeEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZBDragEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void TimeEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZBDragEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// StrEditHistoric window

class AFX_EXT_CLASS StrEditHistoric : public ZCIntelliEdit, public Edit
{
// Construction
public:

    StrEditHistoric( int iMaxChar = -1 );
    virtual ~StrEditHistoric();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    int GetMaxChar() const
    {
        return m_iMaxChar;
    };

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZCIntelliEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void StrEditHistoric::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZCIntelliEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS NumEditHistoric : public ZCIntelliEdit, public Edit
{
// Construction
public:

    NumEditHistoric();
    virtual ~NumEditHistoric();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZCIntelliEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void NumEditHistoric::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZCIntelliEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// FieldNameEdit window

class AFX_EXT_CLASS FieldNameEdit : public ZCIntelliEdit, public Edit
{
// Construction
public:

    FieldNameEdit( int iMaxChar = -1 );
    virtual ~FieldNameEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZCIntelliEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void FieldNameEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZCIntelliEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// MaskEdit window

class AFX_EXT_CLASS MaskEdit : public ZMaskEdit, public Edit
{
// Construction
public:

    MaskEdit();
    virtual ~MaskEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZMaskEdit::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void MaskEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZMaskEdit::MapWindowPoints( pwndTo, lpRect );
}

/////////////////////////////////////////////////////////////////////////////
// MultiColumnEdit window

class AFX_EXT_CLASS MultiColumnEdit : public ZCGridCtrl, public Edit
{
// Construction
public:

    MultiColumnEdit();
    virtual ~MultiColumnEdit();

    virtual void Create( BOOL                DesignerMode,
                         CWnd*                pParentWnd,
                         CDC*                pDC,
                         ZDDocument*        pDoc,
                         PlanFinObject*        pEditedObj,
                         ZBFieldRepository*    pFieldRepository    = NULL,
                         BOOL                AutoCalculateOption    = FALSE,
                         BOOL                GoNextEditOption    = FALSE );

    virtual void DestroyEdit();

    // Virtual function used for base access class
    virtual BOOL IsWindowVisible();
    virtual void MapWindowPoints( CWnd* pwndTo, LPRECT lpRect );

    // Called before editing the cell
    virtual void OnBeginLabelEdit( int iItem, int iSubItem );

    // Called after having updated the cell
    virtual void OnEndLabelEdit( LPCSTR pszText, int iItem, int iSubItem );

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
    if ( ::IsWindow( GetSafeHwnd() ) && ZCGridCtrl::IsWindowVisible() )
    {
        return TRUE;
    }

    return FALSE;
}

inline void MultiColumnEdit::MapWindowPoints( CWnd* pwndTo, LPRECT lpRect )
{
    ZCGridCtrl::MapWindowPoints( pwndTo, lpRect );
}

#endif // __EDIT_H