// ZIObserver.h: interface for the ZIObserver class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIObserver_H__57735636_FF28_462A_A977_77CCC74D9EA2__INCLUDED_)
#define AFX_ZIObserver_H__57735636_FF28_462A_A977_77CCC74D9EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// Forward declaration
class ZISubject;
class ZIObserverMsg;

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 19 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZIObserver
{
public:

	virtual ~ZIObserver();

	virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg ) = 0;

protected:

	ZIObserver();
};

#endif // !defined(AFX_ZIObserver_H__57735636_FF28_462A_A977_77CCC74D9EA2__INCLUDED_)