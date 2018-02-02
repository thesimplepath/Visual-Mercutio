// ZISubject.h: interface for the ZISubject class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZISubject_H__BFF3F9F3_A1DD_4EFA_AF2F_23434EEF5C24__INCLUDED_)
#define AFX_ZISubject_H__BFF3F9F3_A1DD_4EFA_AF2F_23434EEF5C24__INCLUDED_

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
class ZIObserver;
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

class AFX_EXT_CLASS ZISubject
{
public:

	virtual			~ZISubject			();

	virtual void	AttachObserver		( ZIObserver* pObserver );
	virtual void	DetachObserver		( ZIObserver* pObserver );
	virtual void	DetachAllObservers	();
	virtual void	NotifyAllObservers	( ZIObserverMsg* pMsg );

protected:

	ZISubject();

private:

	CObArray m_ObserverSet;
};

#endif // !defined(AFX_ZISubject_H__BFF3F9F3_A1DD_4EFA_AF2F_23434EEF5C24__INCLUDED_)