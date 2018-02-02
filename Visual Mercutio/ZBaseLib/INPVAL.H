// InpVal.h : header file
//

#ifndef InpVal_h
#define InpVal_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZIDialog.h"
#include "zRes32\ZRes.h"



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
// ZIInputValue dialog

class AFX_EXT_CLASS ZIInputValue : public ZIDialog
{
// Construction
public:
	ZIInputValue(CString Title="", CString Value="", CWnd* pParent = NULL);	// standard constructor
	ZIInputValue(UINT nTitleID, CString Value="", CWnd* pParent = NULL);

	CString		GetValue() { return m_sValue; };
	
private:
// Dialog Data
	//{{AFX_DATA(ZIInputValue)
	enum { IDD = IDD_INPUT_VALUE };
	CString	m_sValue;
	//}}AFX_DATA

private:
	CString	m_Title;
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(ZIInputValue)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif
