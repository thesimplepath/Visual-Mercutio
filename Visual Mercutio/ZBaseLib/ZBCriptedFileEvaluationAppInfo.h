// ZBCriptedFileEvaluationAppInfo.h: interface for the ZBCriptedFileEvaluationAppInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBCRIPTEDFILEEVALUATIONAPPINFO_H__6EAC9B87_3386_11D4_973F_0000B45D7C6F__INCLUDED_)
#define AFX_ZBCRIPTEDFILEEVALUATIONAPPINFO_H__6EAC9B87_3386_11D4_973F_0000B45D7C6F__INCLUDED_

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


#include "ZBCriptedFileInfo.H"


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



class AFX_EXT_CLASS ZBCriptedFileEvaluationAppInfo : public ZBCriptedFileInfo  
{

public:
	ZBCriptedFileEvaluationAppInfo(const CString Filename = "");
	virtual ~ZBCriptedFileEvaluationAppInfo();

	BOOL	Initialize( const CString Filename );
	BOOL	CreateEmpty( const CString Filename );

	BOOL	InitializeFirstUse( int NumberOfDays = -1 );
	BOOL	CheckProductKey( CString ProductKey );
	BOOL	CheckExpiration();

	CString	LoadProductKey();
	BOOL	WriteProductKey( CString value );

	ZBDate	LoadInstallationDate();
	BOOL	WriteInstallationDate( ZBDate value );

	ZBDate	LoadLastDateUsage();
	BOOL	WriteLastDateUsage( ZBDate value );

	ZBDate	LoadValidDate();
	BOOL	WriteValidDate( ZBDate value );

	int		LoadTotalDays();
	BOOL	WriteTotalDays( int value );

private:
	BOOL	ReadFileInfo();
	BOOL	WriteFileInfo();

	CString	GetProductKey() const { return m_ProductKey; };
	void	SetProductKey( CString	value ) { m_ProductKey = value; };

	ZBDate&	GetInstallationDate() { return m_InstallationDate; };
	void	SetInstallationDate( ZBDate	value ) { m_InstallationDate = value; };

	ZBDate&	GetLastDateUsage() { return m_LastDateUsage; };
	void	SetLastDateUsage( ZBDate	value ) { m_LastDateUsage = value; };

	ZBDate&	GetValidDate() { return m_ValidDate; };
	void	SetValidDate( ZBDate	value ) { m_ValidDate = value; };

	int		GetTotalDays() const { return m_TotalDays; };
	void	SetTotalDays( int value ) { m_TotalDays = value; };


private:
	CString	m_ProductKey;
	ZBDate	m_InstallationDate;
	ZBDate	m_LastDateUsage;
	ZBDate	m_ValidDate;
	int		m_TotalDays;
};

#endif // !defined(AFX_ZBCRIPTEDFILEEVALUATIONAPPINFO_H__6EAC9B87_3386_11D4_973F_0000B45D7C6F__INCLUDED_)
