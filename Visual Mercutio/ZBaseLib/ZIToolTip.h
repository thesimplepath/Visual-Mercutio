// ZIToolTip.h: interface for the ZIToolTip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZITOOLTIP_H__2E5A9D5B_E60C_497D_BF19_D731C5B6E3FF__INCLUDED_)
#define AFX_ZITOOLTIP_H__2E5A9D5B_E60C_497D_BF19_D731C5B6E3FF__INCLUDED_

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



class AFX_EXT_CLASS ZIToolTip  
{
public:
	enum ToolTipMode { NormalToolTip, DesignToolTip };

public:
	ZIToolTip();
	virtual ~ZIToolTip();

	// Call by the controller when a tooltip is required
	virtual bool OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip = NormalToolTip ) = 0;

};

#endif // !defined(AFX_ZITOOLTIP_H__2E5A9D5B_E60C_497D_BF19_D731C5B6E3FF__INCLUDED_)
