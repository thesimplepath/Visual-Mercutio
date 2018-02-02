// SelProcW.h: interface for the ZISelectProcessWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELPROCW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_SELPROCW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

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

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif

#include "zEvent\ZProcess.h"


#ifdef _ZWINUTIL32EXPORT
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


class AFX_EXT_CLASS ZISelectProcessWizard  
{
public:
	ZISelectProcessWizard( ZProcess& Process );
	
	// Start the wizard
	BOOL	PlayWizard();
	CString	GetBaseActivityName() const { return m_BaseActivityName; };
	
	virtual ~ZISelectProcessWizard();


private:
	ZProcess& 		m_Process;
	CString			m_BaseActivityName;

private:

};

#endif // !defined(AFX_SELPROCW_H__B6801F55_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
