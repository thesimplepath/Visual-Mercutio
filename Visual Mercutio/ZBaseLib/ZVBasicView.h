#if !defined(AFX_ZVBASICVIEW_H__D650888C_6260_47CE_B9D2_8FB4C710C1E2__INCLUDED_)
#define AFX_ZVBASICVIEW_H__D650888C_6260_47CE_B9D2_8FB4C710C1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVBasicView.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVBasicView view

class AFX_EXT_CLASS ZVBasicView : public CView
{
protected:
	ZVBasicView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ZVBasicView)


// Operations
public:

	  // Return the printer page size
	  BOOL GetPrinterPageSize(CSize &PaperSize, short& StandardSize, short& Orientation);

      //	Set the printer orientation. It is function of the
      //	printer definition.
      void SetPrinterOrientation (short Orientation = DMORIENT_PORTRAIT);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVBasicView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ZVBasicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ZVBasicView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVBASICVIEW_H__D650888C_6260_47CE_B9D2_8FB4C710C1E2__INCLUDED_)
