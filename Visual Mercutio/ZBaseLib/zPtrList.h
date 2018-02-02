#if !defined(_ZPTRLIST_H)
#define _ZPTRLIST_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// zPtrList.h
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include <afxtempl.h>


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

//////////////////////////////////////////////////////////////////////
// ZTTypedPtrList

template<class BASE_CLASS, class TYPE>
class AFX_EXT_CLASS ZTTypedPtrList : public CTypedPtrList<BASE_CLASS, TYPE>
{
public:
	ZTTypedPtrList(int nBlockSize = 10) 
		: CTypedPtrList<BASE_CLASS, TYPE>(nBlockSize) 
	{
	}

	~ZTTypedPtrList()
	{
		Destroy();
	}

	void Destroy()
	{
		POSITION pos = GetHeadPosition();

		while(pos != NULL)
		{
			TYPE node = GetNext(pos);
			delete node;
		}

		RemoveAll();
	}
};

#endif //!defined(_ZPTRLIST_H)