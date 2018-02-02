// ZIObserverMsg.h: interface for the ZIObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIOBSERVERMSG_H__16115A8A_1A36_4F89_B8D2_FE7E2BAB2749__INCLUDED_)
#define AFX_ZIOBSERVERMSG_H__16115A8A_1A36_4F89_B8D2_FE7E2BAB2749__INCLUDED_

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

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

class AFX_EXT_CLASS ZIObserverMsg : public CObject
{
	DECLARE_DYNAMIC( ZIObserverMsg )

public:

	virtual ~ZIObserverMsg();

protected:

	ZIObserverMsg();
};

#endif // !defined(AFX_ZIOBSERVERMSG_H__16115A8A_1A36_4F89_B8D2_FE7E2BAB2749__INCLUDED_)