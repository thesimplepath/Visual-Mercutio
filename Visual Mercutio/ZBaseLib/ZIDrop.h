// ZIDrop.h: interface for the ZIDrop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIDROP_H__1D4AECEC_8F8C_45D8_B2C3_0B4E512CD812__INCLUDED_)
#define AFX_ZIDROP_H__1D4AECEC_8F8C_45D8_B2C3_0B4E512CD812__INCLUDED_

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


class AFX_EXT_CLASS ZIDrop  
{
public:
	ZIDrop();
	virtual ~ZIDrop();

	virtual bool AcceptDrop() const = 0;

	virtual bool DropItem( CObject* pObj, CPoint pt ) = 0;

	virtual bool AcceptDropItem( CObject* pObj, CPoint pt ) = 0;

};

#endif // !defined(AFX_ZIDROP_H__1D4AECEC_8F8C_45D8_B2C3_0B4E512CD812__INCLUDED_)
