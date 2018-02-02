/////////////////////////////////////////////////////////////////////////////
//@doc ZIEvalWarning
//@module Eval.h | Interface of the <c ZIEvalWarning> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:devzone@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zADS library.
// See these sources for detailed information regarding
// zADS libraries.
//
// <nl>Created:		 03/2000
// <nl>Description:  ZIEvalWarning evaluation dialog box
//
/////////////////////////////////////////////////////////////////////////////


#ifndef _ZIEvalWarning_h__
#define _ZIEvalWarning_h__ 1


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZSCTYEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZIEvalWarning dialog


class AFX_EXT_CLASS ZIEvalWarning : public CDialog
{
// Construction
public:
	ZIEvalWarning(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(ZIEvalWarning)
/*
	enum { IDD = IDD_EVALUATIONWARNING };
*/
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(ZIEvalWarning)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif