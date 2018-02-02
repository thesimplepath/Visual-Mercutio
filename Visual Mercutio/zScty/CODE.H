/////////////////////////////////////////////////////////////////////////////
//@doc ZICode
//@module Code.h | Interface of the <c ZICode> class.
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
// <nl>Description:  ZICode input code dialog box
//
/////////////////////////////////////////////////////////////////////////////
// code.h : header file
//

#ifndef _ZICode_h__
#define _ZICode_h__ 1


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
// ZICode dialog

class AFX_EXT_CLASS ZICode : public CDialog
{
// Construction
public:
	ZICode(CWnd* pParent = NULL);	// standard constructor

	CString	GetCode() const
	{
		return m_sCode;
	};

private:
// Dialog Data
	//{{AFX_DATA(ZICode)
/*
	enum { IDD = IDD_CODE2INSTALL };
*/
	CString	m_sCode;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(ZICode)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int	m_iCounter;
};




#endif