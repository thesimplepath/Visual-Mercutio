// ZBTokenizer.h: interface for the ZBTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBTOKENIZER_H__0DD19906_2D2B_11D3_95CD_0000B45D7C6F__INCLUDED_)
#define AFX_ZBTOKENIZER_H__0DD19906_2D2B_11D3_95CD_0000B45D7C6F__INCLUDED_

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

class AFX_EXT_CLASS ZBTokenizer  
{
public:

	ZBTokenizer					( const char SeparatorChar = ';' );
	ZBTokenizer					( const CString Line, const char SeparatorChar = ';' );
	virtual ~ZBTokenizer		();

	void		SetSeparator	( const char SeparatorChar );
	void		InitializeString( const CString Line );

	CString		GetFirstToken	( const CString Line) ;
	CString		GetNextToken	();
	BOOL		ClearAllTokens	();
	CString		GetString		();

	// Add token of different types
	BOOL		AddToken		( const CString Token );
	BOOL		AddToken		( int iValue );
	BOOL		AddToken		( float fValue );
	BOOL		AddToken		( double dValue );

	// Management methods
	size_t		GetTokenCount	();
	BOOL		GetTokenAt		( size_t Index, CString& Value );

	BOOL		TokenExist		( const CString Token );
	BOOL		TokenExist		( int iValue );
	BOOL		TokenExist		( float fValue );
	BOOL		TokenExist		( double dValue );

	BOOL		AddUniqueToken	( const CString Token );
	BOOL		AddUniqueToken	( int iValue );
	BOOL		AddUniqueToken	( float fValue );
	BOOL		AddUniqueToken	( double dValue );

	BOOL		RemoveToken		( const CString Token );
	BOOL		RemoveToken		( int iValue );
	BOOL		RemoveToken		( float fValue );
	BOOL		RemoveToken		( double dValue );

	void		FillArray( CStringArray& Array );

private:

	CString		_GetFirstToken();

private:

	char	m_SeparatorChar;

	char*	m_pCurrent;
	char*	m_pNext;  	

	CString	m_Line;
};

inline	void ZBTokenizer::SetSeparator( const char SeparatorChar )
{
	m_SeparatorChar = SeparatorChar;
}

inline CString ZBTokenizer::_GetFirstToken()
{
	m_pNext = NULL;
	m_pCurrent = m_Line.GetBuffer( m_Line.GetLength() + 2 );

	return GetNextToken();
}

#endif // !defined(AFX_ZBTOKENIZER_H__0DD19906_2D2B_11D3_95CD_0000B45D7C6F__INCLUDED_)