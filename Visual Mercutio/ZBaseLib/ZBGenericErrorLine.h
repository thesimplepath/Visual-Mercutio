// ZBGenericErrorLine.h: interface for the ZBGenericErrorLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBGENERICERRORLINE_H__74469948_01E4_477F_AE8E_F83A38064EE6__INCLUDED_)
#define AFX_ZBGENERICERRORLINE_H__74469948_01E4_477F_AE8E_F83A38064EE6__INCLUDED_

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


#include "ZIErrorLine.h"

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


class AFX_EXT_CLASS ZBGenericErrorLine : public ZIErrorLine
								  
{
public:
	ZBGenericErrorLine( const CString message = "", 
						int line = -1, 
						int error = -1, 
						int type = -1 );
	virtual ~ZBGenericErrorLine();

	ZBGenericErrorLine(const ZBGenericErrorLine& src);
	ZBGenericErrorLine& operator=(const ZBGenericErrorLine& src);

protected:
	virtual void BuildString();
	virtual void Parse();

};

#endif // !defined(AFX_ZBGENERICERRORLINE_H__74469948_01E4_477F_AE8E_F83A38064EE6__INCLUDED_)
