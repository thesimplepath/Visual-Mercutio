// ActEvtFl.h: interface for the ZBEventActivityFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBEventActivityFile_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBEventActivityFile_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_

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


#include "ActEvent.h"
#include "EventFl.h"

#ifdef _ZEVENTEXPORT
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


class AFX_EXT_CLASS ZBEventActivityFile : public ZBEventFile
{
public:
	ZBEventActivityFile();

private:
    ZBEventActivityFile(const ZBEventActivityFile &right);
    const ZBEventActivityFile & operator=(const ZBEventActivityFile &right);

protected:
	virtual void	BuildLine(const CString Path, const CString Filename);
	virtual BOOL	ParseLine();
	virtual ZBEvent*	AllocateEventPtr();
};


//#undef  AFX_DATA
//#define AFX_DATA


inline ZBEvent*	ZBEventActivityFile::AllocateEventPtr()
{
	ZBEventActivity*	pEvent = new ZBEventActivity;
	return pEvent;
}


#endif // !defined(AFX_ZBEventActivityFile_H__0F4A8AF0_0EAC_11D3_9810_00C04FB4D0D7__INCLUDED_)
