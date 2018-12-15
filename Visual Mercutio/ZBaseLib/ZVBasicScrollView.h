// ZVBasicScrollView.h : header file

#if !defined(AFX_ZVBASICSCROLLVIEW_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)
#define AFX_ZVBASICSCROLLVIEW_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZVSpanView.h"
#include "ZVDocumentPageSetup.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVBasicScrollView view

class AFX_EXT_CLASS ZVBasicScrollView : public ZVSpanView
{
protected:

    DECLARE_DYNCREATE( ZVBasicScrollView )

    // Protected constructor used by dynamic creation
    ZVBasicScrollView();

// Operations
public:

    // Return the printer page size
//    BOOL GetPrinterPageSize( CSize &PaperSize, short& StandardSize, short& Orientation );
    ZVDocumentPageSetup*    GetPrinterPageSize();
    void                    SetPrinterPageSize( CSize PaperSize, short StandardSize, short Orientation );

    //    Set the printer orientation. It is function of the
    //    printer definition.
//    void SetPrinterOrientation ( short Orientation = DMORIENT_PORTRAIT );

    // Call back for Zoom In&Out
    virtual void ViewZoomIn();
    virtual void ViewZoomOut();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVBasicScrollView)
    protected:
    virtual void OnDraw(CDC* pDC);    // overridden to draw this view
    virtual void OnInitialUpdate();    // first time after construct
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVBasicScrollView)
    afx_msg void OnViewZoomIn();
    afx_msg void OnViewZoomOut();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual ~ZVBasicScrollView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

private:

    ZVDocumentPageSetup        m_PageSetup;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVBASICSCROLLVIEW_H__12BA3983_74D2_4165_9560_7CAC5F01222B__INCLUDED_)