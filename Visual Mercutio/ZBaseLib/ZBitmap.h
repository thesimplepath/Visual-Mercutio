// ZBitmap.h: interface for the ZBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBITMAP_H__8DFB40B0_9E86_11D3_987E_00C04FB4D0D7__INCLUDED_)
#define AFX_ZBITMAP_H__8DFB40B0_9E86_11D3_987E_00C04FB4D0D7__INCLUDED_

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


class AFX_EXT_CLASS ZBitmap : public CBitmap  
{
public:
	ZBitmap();
	virtual ~ZBitmap();

	bool	IsValid() const;

	HANDLE	GetDIBHandle() const;

	CSize	GetSize() const;

	// Load sections
	bool	LoadBitmap(UINT nResID);
	bool	LoadBitmapFromFile( LPCTSTR szFilename );

	bool	LoadDIBSectionFromFile( LPCTSTR lpszFileName, LPVOID *ppvBits=NULL, 
									HANDLE hSection=NULL, DWORD dwOffset=0);

	// Conversion functions
	HANDLE	DDBToDIB( DWORD dwCompression, CPalette* pPal );
	HBITMAP DIBToDDB( HANDLE hDIB );
	bool	DIBToDDB();

	// Draw functions
	void		DrawBitmap( CDC *pDC, HPALETTE hPal = NULL, int xDest = 0, int yDest = 0 );
	void		DrawDIB( CDC* pDC, HGLOBAL hDIB, CPalette *pPal = NULL, int xDest = 0, int yDest = 0 );
	void		DrawDIB( CDC* pDC, CPalette *pPal = NULL, int xDest = 0, int yDest = 0 );


private:
	bool	LoadSize();

private:
	HANDLE			m_hDIB;
	bool			m_IsValid;
	CSize			m_Size;

};


inline bool	ZBitmap::IsValid() const
{
	return m_IsValid;
}

inline HANDLE	ZBitmap::GetDIBHandle() const
{
	return m_hDIB;
}


inline CSize	ZBitmap::GetSize() const
{
	return ((IsValid() == true) ? m_Size : CSize(0,0));
}

#endif // !defined(AFX_ZBITMAP_H__8DFB40B0_9E86_11D3_987E_00C04FB4D0D7__INCLUDED_)
