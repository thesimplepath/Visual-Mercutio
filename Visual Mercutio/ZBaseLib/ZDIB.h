#ifndef __ZDIB_h
#define __ZDIB_h

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


class AFX_EXT_CLASS ZDIB 
{
public:
	enum BitmapType
	{
		BMP,
		GIF,
		TIFF
	};
	ZDIB(HANDLE hDib=NULL,int nBits=8);
	virtual ~ZDIB();
	ZDIB& operator=(ZDIB& dib);
	BOOL IsValid() { return (m_pVoid && Width() && Height());};
	void UseGamma(float fg,BOOL bUse=TRUE);
	BOOL CreateFromHandle(HANDLE hDib,int nBits);
	BOOL Create(int width,int height,int bits=24);
	BOOL Create(BITMAPINFOHEADER& bmInfo);
	BOOL CopyDIB(ZDIB& dib);
	BOOL OpenDIB(const CString& fileName);
	BOOL SaveDIB(CString& fileName,BitmapType type);
	void ReplaceColor(unsigned char oldColor,unsigned char newColor);
	HANDLE GetDIBits(int nStartX=-1,int nStartY=-1,int nCx=-1,int nCy=-1);
	CBitmap *GetBitmap(CDC& dc);
	CBitmap *GetTempBitmap(CDC& dc);
	DWORD GetDIBSize();
	int GetPaletteSize(BITMAPINFOHEADER& bmInfo);
	int GetPaletteSize();
	int CountColors();
	int EnumColors(BYTE *colors);
	void InitDIB(COLORREF color);
	void CopyLine(int source,int dest);
	void DestroyDIB();
	void SetPalette(unsigned char *palette);
	void SetPalette(RGBQUAD *pRGB);
	COLORREF PaletteColor(int index);
	void SetPixel(int x,int y,COLORREF color);
	void SetPixel8(int x,int y,unsigned char color);
	COLORREF GetPixel(int x,int y);
	void GetPixel(UINT x,UINT y,int& pixel);
	void BitBlt(HDC hDest,int nXDest,int nYDest,int nWidth,int nHeight,int xSrc,int ySrc);
	void BitBlt(int nXDest,int nYDest,int nWidth,int nHeight,ZDIB& dibSrc,int nSrcX,int nSrcY,BYTE *colors=NULL);
	void StretchBlt(HDC hDest,int nXDest,int nYDest,int nDWidth,int nDHeight,int xSrc,int ySrc,int  nSWidth,int nSHeight);
	void StretchBlt(int nXDest,int nYDest,int nDWidth,int nDHeight,ZDIB& dibSrc,int xSrc,int ySrc,int  nSWidth,int nSHeight);
	void ExpandBlt(int nXDest,int nYDest,int xRatio,int yRatio,ZDIB& dibSrc,int xSrc,int ySrc,int  nSWidth,int nSHeight);
	void SetFlags(int flag) { m_nFlags = flag; };
	int Height() { return height ; };
	int Width() { return width ; };
	unsigned char *GetLinePtr(int line);	
	inline int GetBitCount() {return m_pInfo->bmiHeader.biBitCount;};
	BOOL Make8Bit(ZDIB& dib);
	BOOL SwitchFromOne(ZDIB& dib);
	BOOL SwitchFromFour(ZDIB& dib);
	BOOL SwitchFrom24(ZDIB& dib);
	BOOL SwitchPalette(ZDIB& dib);
	int  ClosestColor(RGBQUAD *pRgb);
	LPBITMAPINFO GetBitmapInfo() { return m_pInfo;};
	static unsigned int Distance(RGBQUAD& rgb1,RGBQUAD& rgb2);
protected :
	HANDLE DIBHandle();
	BOOL OpenBMP(const CString& csFileName);
	BOOL SaveBMP(CString& csFileName);
	void CreateGammaCurve();
	void Expand(int nXDest,int nYDest,int xRatio,int yRatio,ZDIB& dibSrc,int xSrc,int ySrc,int  nSWidth,int nSHeight);
	unsigned char *m_pBits;
	PBITMAPINFO m_pInfo;
	RGBQUAD *m_pRGB;
	void *m_pVoid; 
	BYTE **m_pLinePtr;
	int height,bytes,width,m_nBits;
	int m_nFlags;
	BOOL m_bUseGamma;
	float m_fGamma;
	float m_fOldGamma;
	unsigned char Gamma[256];
	RGBQUAD CacheQuad[256];
	char CachePtr[256];
};


#endif	// __ZDIB_h