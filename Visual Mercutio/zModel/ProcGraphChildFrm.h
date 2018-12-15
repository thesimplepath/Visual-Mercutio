// ProcGraphChildFrm.h : interface of the ZIProcessGraphChildFrame class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ProcGraphChildFrm_H__4B1BEB8D_8452_4F59_A51D_BE57E94FD6E1__INCLUDED_)
#define AFX_ProcGraphChildFrm_H__4B1BEB8D_8452_4F59_A51D_BE57E94FD6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

class AFX_EXT_CLASS ZIProcessGraphChildFrame : public SECMDIChildWnd
{
    DECLARE_DYNCREATE( ZIProcessGraphChildFrame )

public:

    ZIProcessGraphChildFrame();

// Overrides
public:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIProcessGraphChildFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual ~ZIProcessGraphChildFrame();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
protected:

    //{{AFX_MSG(ZIProcessGraphChildFrame)
    afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual void OnUpdateFrameTitle( BOOL bAddToTitle );

private:

    static CDocument* m_pLastDocumentActivated;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ProcGraphChildFrm_H__4B1BEB8D_8452_4F59_A51D_BE57E94FD6E1__INCLUDED_)
