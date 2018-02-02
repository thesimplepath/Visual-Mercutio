// ZILog.h: interface for the ZILog class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZILOG_H__A1D53B29_9009_421B_A8BF_3F7FFFE642DD__INCLUDED_)
#define AFX_ZILOG_H__A1D53B29_9009_421B_A8BF_3F7FFFE642DD__INCLUDED_

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

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZILog
{
public:

	ZILog();
	virtual ~ZILog();

	virtual bool	InitializeLog() = 0;
	virtual void	ClearLog() = 0;
	virtual void	AddLine( const CString Line ) = 0;
	virtual size_t	GetCount() const = 0;
	virtual CString	GetLineAt( size_t Index ) const = 0;
	virtual int		GetCurrentSelection() const = 0;
	virtual void	SetCurrentSelection( size_t Index ) = 0;
	virtual void	ClearCurrentSelection() = 0;
	virtual int		GetCurrentItem( CString& s ) const = 0;

	// Debug mode flag
	virtual bool	IsInDebugMode() const = 0;
	virtual void	SetDebugMode( bool value = true ) = 0;

	// Selection mode
	virtual bool	SelectLast() const = 0;
	virtual void	SetSelectLast( bool value = true ) = 0;
};

#endif // !defined(AFX_ZILOG_H__A1D53B29_9009_421B_A8BF_3F7FFFE642DD__INCLUDED_)