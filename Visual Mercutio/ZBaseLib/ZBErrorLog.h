// ZBErrorLog.h: interface for the ZBErrorLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBERRORLOG_H__5CEA9E36_F1D5_4031_B447_85C760C6BFC0__INCLUDED_)
#define AFX_ZBERRORLOG_H__5CEA9E36_F1D5_4031_B447_85C760C6BFC0__INCLUDED_

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


#include "ZILog.h"


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


class AFX_EXT_CLASS ZBErrorLog : public ZILog  
{
public:
	ZBErrorLog();
	virtual ~ZBErrorLog();

	virtual bool	InitializeLog()
	{
		// Do nothing
		return true;
	};
	virtual void	ClearLog()
	{
		m_LogArray.RemoveAll();
	};
	virtual void	AddLine( const CString Line )
	{
		m_LogArray.Add( Line );
	};
	virtual size_t	GetCount() const
	{
		return m_LogArray.GetSize();
	};
	virtual CString GetLineAt( size_t Index ) const
	{
		return m_LogArray.GetAt( Index );
	};
	virtual int		GetCurrentSelection() const
	{
		return m_CurrentSelection;
	};
	virtual void	SetCurrentSelection(size_t Index)
	{
		m_CurrentSelection = Index;
	};
	virtual void	ClearCurrentSelection()
	{
		m_CurrentSelection = -1;
	};
	virtual int		GetCurrentItem(CString& s) const
	{
		int i = GetCurrentSelection();
		if (i != LB_ERR) 
			s = GetLineAt( i );
		return i;
	};

	virtual bool	SelectLast() const
	{
		return false;
	};
	virtual void	SetSelectLast( bool value = true )
	{
		// Do nothing
	};

private:
	CStringArray m_LogArray;
	int m_CurrentSelection;
};

#endif // !defined(AFX_ZBERRORLOG_H__5CEA9E36_F1D5_4031_B447_85C760C6BFC0__INCLUDED_)
