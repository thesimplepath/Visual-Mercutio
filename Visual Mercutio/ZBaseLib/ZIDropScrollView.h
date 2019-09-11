#if !defined(AFX_ZIDropScrollView_H__96365A05_C418_4569_836C_1CC5162A7DCA__INCLUDED_)
#define AFX_ZIDropScrollView_H__96365A05_C418_4569_836C_1CC5162A7DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIDropScrollView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZIDrop.h"
#include "PSS_BasicScrollView.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


/////////////////////////////////////////////////////////////////////////////
// ZIDropScrollView view

class AFX_EXT_CLASS ZIDropScrollView : public PSS_BasicScrollView, public ZIDrop
{
    DECLARE_DYNCREATE(ZIDropScrollView)

public:
    virtual bool AcceptDrop() const { return false; };

    virtual bool DropItem( CObject* pObj, CPoint pt ) { return false; };

    virtual bool AcceptDropItem( CObject* pObj, CPoint pt ) { return false; };

protected:
    ZIDropScrollView();
    virtual ~ZIDropScrollView();

    /// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIDropScrollView)
    virtual void OnDraw(CDC* pDC);
    //}}AFX_VIRTUAL

    /// Generated message map functions
    //{{AFX_MSG(ZIDropScrollView)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif
