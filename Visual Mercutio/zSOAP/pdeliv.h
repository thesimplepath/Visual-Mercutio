/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:		 03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PDELIV_HDR_
#define __PDELIV_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"
string convertTo( String16 inStr );

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS pdeliv
{
public:

	pdeliv()
	{
	}

	pdeliv( int			delivid,
			int			procidsrc,
			int			procidtrg,
			String16	delivname,
			int			lateral,
			int			lateraldirection,
			int			doublesign )
	{
		this->delivid			= delivid;
		this->procidsrc			= procidsrc;
		this->procidtrg			= procidtrg;
		this->delivname			= convertTo( delivname );
		this->lateral			= lateral;
		this->lateraldirection	= lateraldirection;
		this->doublesign		= doublesign;
	}

	int		delivid;
	int		procidsrc;
	int		procidtrg;
	string	delivname;

	/*
	 * 0 = normal
	 * 1 = lateral starts here
	*/
	int		lateral;
	int		lateraldirection;	// 0 : top, 1 : right,     2 : bottom, 3 : left
	int		doublesign;			// 0 : no,  1 : employees, 2 : chiefs
};

#endif