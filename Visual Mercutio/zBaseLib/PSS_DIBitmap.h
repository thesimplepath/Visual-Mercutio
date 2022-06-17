/****************************************************************************
 * ==> PSS_DIBitmap --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a device independent bitmap                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DIBitmapH
#define PSS_DIBitmapH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Device independent bitmap
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DIBitmap
{
    public:
        /**
        * Bitmap type
        */
        enum class IEType
        {
            IE_BT_BMP,
            IE_BT_GIF,
            IE_BT_TIFF
        };

        /**
        * constructor
        *@param hDIB - device independent bitmap handle
        *@param bits - bit per pixels
        */
        PSS_DIBitmap(HANDLE hDIB = NULL, int bits = 8);

        virtual ~PSS_DIBitmap();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DIBitmap& operator = (const PSS_DIBitmap& dib);

        /**
        * Creates a bitmap
        *@param width - bitmap width in pixels
        *@param height - bitmap height in pixels
        *@param bits - bit per pixels
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(int width, int height, int bits = 24);

        /**
        * Creates a bitmap
        *@param info - bitmap info
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const BITMAPINFOHEADER& info);

        /**
        * Creates a bitmap from handle
        *@param hDIB - device independent bitmap handle
        *@param bits - bits count
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateFromHandle(HANDLE hDIB, int bits);

        /**
        * Destroys the bitmap
        */
        virtual void DestroyDIB();

        /**
        * Initializes the bitmap with a color
        *@param color - color to fill
        */
        virtual void InitDIB(COLORREF color);

        /**
        * Copies from another bitmap
        *@param dib - other bitmap to copy from
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CopyDIB(const PSS_DIBitmap& dib);

        /**
        * Opens a bitmap from a file
        *@param fileName - bitmap file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenDIB(const CString& fileName);

        /**
        * Saves a bitmap to a file
        *@param fileName - bitmap file name
        *@param type - bitmap type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveDIB(const CString& fileName, IEType type);

        /**
        * Checks if bitmap is valid
        *@return TRUE if bitmap is valid, otherwise FALSE
        */
        virtual inline BOOL IsValid() const;

        /**
        * Sets the gamme
        *@param gamma - gamma
        *@param use - if TRUE, the gamma will be used
        */
        virtual void UseGamma(float gamma, BOOL use = TRUE);

        /**
        * Replaces a color to another
        *@param oldCOlor - old color to replace
        *@param newColor - new color to replace by
        */
        virtual void ReplaceColor(unsigned char oldColor, unsigned char newColor);

        /**
        * Gets the bitmap bits
        *@param startX - start x position in pixels, if -1 the first start position will be used
        *@param startY - start y position in pixels, if -1 the first start position will be used
        *@param cx - width in pixels, if -1 the entire width will be used
        *@param cy - height in pixels, if -1 the entire height will be used
        *@return bit array handle
        */
        virtual HANDLE GetDIBits(int startX = -1, int startY = -1, int cx = -1, int cy = -1) const;

        /**
        * Gets the bitmap containing the device context content
        *@param dc - device context
        *@return the bitmap, NULL on error
        */
        virtual CBitmap* GetBitmap(const CDC& dc) const;

        /**
        * Gets a temporary bitmap containing the device context content
        *@param dc - device context
        *@return the bitmap, NULL on error
        */
        virtual CBitmap* GetTempBitmap(const CDC& dc) const;

        /**
        * Gets the device independent bitmap size
        *@return the bitmap size in bytes
        */
        virtual DWORD GetDIBSize() const;

        /**
        * Gets the palette size
        *@param info - bitmap info header
        *@return the palette size in bytes
        */
        virtual int GetPaletteSize(const BITMAPINFOHEADER& info) const;

        /**
        * Gets the palette size
        *@return the palette size in bytes
        */
        virtual int GetPaletteSize() const;

        /**
        * Gets the color count
        *@return the color count in bytes
        */
        virtual int GetColorCount() const;

        /**
        * Enumerates the color
        *@param pColors - colors to enumerate
        *@return the enumerated colors
        */
        virtual int EnumColors(BYTE* pColors) const;

        /**
        * Copies a pixel line
        *@param source - source line index
        *@param dest - destination line index
        */
        virtual void CopyLine(int source, int dest);

        /**
        * Sets the palette
        *@param pPalette - palette
        */
        virtual void SetPalette(unsigned char* pPalette);

        /**
        * Sets the palette
        *@param pRGB - pixel array
        */
        virtual void SetPalette(RGBQUAD* pRGB);

        /**
        * Gets a color from the palette
        *@param index - color index
        *@return the color
        */
        virtual COLORREF PaletteColor(int index) const;

        /**
        * Gets a pixel
        *@param x - x position in pixels
        *@param y - y position in pixels
        *@return the pixel color
        */
        virtual COLORREF GetPixel(int x, int y) const;

        /**
        * Gets a pixel
        *@param x - x position in pixels
        *@param y - y position in pixels
        *@param[out] pixel - the pixel color on the function ends
        */
        virtual void GetPixel(UINT x, UINT y, int& pixel) const;

        /**
        * Sets a pixel
        *@param x - x position in pixels
        *@param y - y position in pixels
        *@param color - pixel color
        */
        virtual void SetPixel(int x, int y, COLORREF color);

        /**
        * Sets a 8 bit (or palettized) pixel
        *@param x - x position in pixels
        *@param y - y position in pixels
        *@param color - pixel color
        */
        virtual void SetPixel8(int x, int y, unsigned char color);

        /**
        * Blits a bitmap area from a source bitmap
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param width - width to copy in pixels
        *@param height - height to copy in pixels
        *@param dibSrc - source bitmap to blit from
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        *@param pColors - color palette, ignored if NULL
        */
        virtual void BitBlt(int                 xDest,
                            int                 yDest,
                            int                 width,
                            int                 height,
                            const PSS_DIBitmap& dibSrc,
                            int                 xSrc,
                            int                 ySrc,
                            BYTE*               pColors = NULL);

        /**
        * Blits a bitmap area to a destination device context
        *@param hDest - destination device context handle to blit to
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param width - width to copy in pixels
        *@param height - height to copy in pixels
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        */
        virtual void BitBlt(HDC hDest, int xDest, int yDest, int width, int height, int xSrc, int ySrc) const;

        /**
        * Stretch blits a bitmap area from a source bitmap
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param widthDest - destination width to copy in pixels
        *@param heightDest - destination height to copy in pixels
        *@param dibSrc - source bitmap to blit from
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        *@param widthSrc - soure width to copy in pixels
        *@param heightSrc - source height to copy in pixels
        */
        virtual void StretchBlt(int                 xDest,
                                int                 yDest,
                                int                 widthDest,
                                int                 heightDest,
                                const PSS_DIBitmap& dibSrc,
                                int                 xSrc,
                                int                 ySrc,
                                int                 widthSrc,
                                int                 heightSrc);

        /**
        * Stretch blits a bitmap area to a destination device context
        *@param hDest - destination device context handle to blit to
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param widthDest - destination width to copy in pixels
        *@param heightDest - destination height to copy in pixels
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        *@param widthSrc - soure width to copy in pixels
        *@param heightSrc - source height to copy in pixels
        */
        virtual void StretchBlt(HDC hDest,
                                int xDest,
                                int yDest,
                                int widthDest,
                                int heightDest,
                                int xSrc,
                                int ySrc,
                                int widthSrc,
                                int heightSrc) const;

        /**
        * Expand blits a bitmap area from a source bitmap
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param xRatio - x ratio to copy in pixels
        *@param yRatio - y ratio to copy in pixels
        *@param dibSrc - source bitmap to blit from
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        *@param widthSrc - soure width to copy in pixels
        *@param heightSrc - source height to copy in pixels
        */
        virtual void ExpandBlt(int                 xDest,
                               int                 yDest,
                               int                 xRatio,
                               int                 yRatio,
                               const PSS_DIBitmap& dibSrc,
                               int                 xSrc,
                               int                 ySrc,
                               int                 widthSrc,
                               int                 heightSrc);

        /**
        * Sets the flags
        *@param flag - flags
        */
        virtual inline void SetFlags(int flag);

        /**
        * Gets the bitmap width
        *@return the bitmap width in pixels
        */
        virtual inline int Width() const;

        /**
        * Gets the bitmap height
        *@return the bitmap height in pixels
        */
        virtual inline int Height() const;

        /**
        * Gets the line pixel array at index
        *@param line - line index
        *@return the line pixel array
        */
        virtual unsigned char* GetLine(int line) const;

        /**
        * Gets the bit count
        *@return the bit count
        */
        virtual inline int GetBitCount() const;

        /**
        * Makes the bitmap 8 bits
        *@param dib - source bitmap to transform from
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Make8Bit(const PSS_DIBitmap& dib);

        /**
        * Switches from monochrome bitmap
        *@param dib - source bitmap
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SwitchFromOne(const PSS_DIBitmap& dib);

        /**
        * Switches from 4 color bitmap
        *@param dib - source bitmap
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SwitchFromFour(const PSS_DIBitmap& dib);

        /**
        * Switches from 24 bit bitmap
        *@param dib - source bitmap
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SwitchFrom24(const PSS_DIBitmap& dib);

        /**
        * Switches from palettized bitmap
        *@param dib - source bitmap
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SwitchPalette(const PSS_DIBitmap& dib);

        /**
        * Gets the closest color
        *@param pRgb - rgb color
        *@return the closest color
        */
        virtual int ClosestColor(RGBQUAD* pRgb);
    
        /**
        * Gets the bitmap info
        *@return the bitmap info
        */
        virtual inline LPBITMAPINFO GetBitmapInfo() const;

        /**
        * Gets the distance between 2 colors
        *@param rgb1 - first color
        *@param rgb2 - second color
        *@return the distance between 2 colors, in pixels
        */
        static unsigned int Distance(const RGBQUAD& rgb1, const RGBQUAD& rgb2);

    protected:
        PBITMAPINFO    m_pInfo;
        RGBQUAD*       m_pRGB;
        RGBQUAD        m_QuadCache[256];
        BYTE**         m_pLine;
        void*          m_pVoid;
        float          m_Gamma;
        float          m_OldGamma;
        int            m_Width;
        int            m_Height;
        int            m_Bytes;
        int            m_Bits;
        int            m_Flags;
        unsigned char* m_pBits;
        unsigned char  m_GammaCache[256];
        char           m_Cache[256];
        BOOL           m_UseGamma;

        /**
        * Gets the bitmap handle
        *@return he bitmap handle
        */
        virtual HANDLE DIBHandle() const;

        /**
        * Opens a bitmap from a file
        *@param fileName - bitmap file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenBMP(const CString& fileName);

        /**
        * Saves a bitmap to a file
        *@param fileName - bitmap file name
        *@param type - bitmap type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveBMP(const CString& fileName);

        /**
        * Creates the gamma curve
        */
        virtual void CreateGammaCurve();

        /**
        * Expands a bitmap area
        *@param xDest - destination x position, in pixels
        *@param yDest - destination y position, in pixels
        *@param xRatio - x ratio to copy in pixels
        *@param yRatio - y ratio to copy in pixels
        *@param dibSrc - source bitmap to expand from
        *@param xSrc - source x position, in pixels
        *@param ySrc - source y position, in pixels
        *@param widthSrc - soure width to copy in pixels
        *@param heightSrc - source height to copy in pixels
        */
        virtual void Expand(int                 xDest,
                            int                 yDest,
                            int                 xRatio,
                            int                 yRatio,
                            const PSS_DIBitmap& dibSrc,
                            int                 xSrc,
                            int                 ySrc,
                            int                 widthSrc,
                            int                 heightSrc) const;
};

//---------------------------------------------------------------------------
// PSS_DIBitmap
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::IsValid() const
{
    return (m_pVoid && Width() && Height());
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::SetFlags(int flag)
{
    m_Flags = flag;
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::Width() const
{
    return m_Width;
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::Height() const
{
    return m_Height;
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::GetBitCount() const
{
    return m_pInfo->bmiHeader.biBitCount;
}
//---------------------------------------------------------------------------
LPBITMAPINFO PSS_DIBitmap::GetBitmapInfo() const
{
    return m_pInfo;
}
//---------------------------------------------------------------------------

#endif
