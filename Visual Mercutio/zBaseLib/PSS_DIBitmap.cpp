/****************************************************************************
 * ==> PSS_DIBitmap --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a device independent bitmap                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DIBitmap.h"

 // windows
#include "math.h"

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Big_Distance 10000000L
#define M_Dist(r1, g1, b1, r2, g2, b2) \
        long(3L * long(r1 - r2) * long(r1 - r2) + \
             4L * long(g1 - g2) * long(g1 - g2) + \
             2L * long(b1 - b2) * long(b1 - b2))
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static unsigned char g_MaskTable[] =
{
    0x80,
    0x40,
    0x20,
    0x10,
    0x08,
    0x04,
    0x02,
    0x01
};
//---------------------------------------------------------------------------
// PSS_DIBitmap
//---------------------------------------------------------------------------
PSS_DIBitmap::PSS_DIBitmap(HANDLE hDIB, int bits) :
    m_pInfo(NULL),
    m_pRGB(NULL),
    m_pLine(NULL),
    m_pVoid(NULL),
    m_Gamma(0.0f),
    m_OldGamma(0.0f),
    m_Width(0),
    m_Height(0),
    m_Bytes(0),
    m_Bits(0),
    m_Flags(0),
    m_pBits(NULL),
    m_UseGamma(FALSE)
{
    std::memset(&m_QuadCache, 0x0, 256);

    if (hDIB)
        CreateFromHandle(hDIB, bits);
}
//---------------------------------------------------------------------------
PSS_DIBitmap::~PSS_DIBitmap()
{
    // NOTE use full qualified name to avoid to call a pure virtual function accidentally during destruction
    PSS_DIBitmap::DestroyDIB();
}
//---------------------------------------------------------------------------
PSS_DIBitmap& PSS_DIBitmap::operator = (const PSS_DIBitmap& dib)
{
    CopyDIB(dib);
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::Create(int width, int height, int bits)
{
    // delete existing image
    DestroyDIB();

    BITMAPINFOHEADER bmInfo;
    std::memset(&bmInfo, 0, sizeof(BITMAPINFOHEADER));
    bmInfo.biSize        = sizeof(BITMAPINFOHEADER);
    bmInfo.biWidth       = width;
    bmInfo.biHeight      = height;
    bmInfo.biPlanes      = 1;
    bmInfo.biBitCount    = bits;
    bmInfo.biCompression = BI_RGB;

    return Create(bmInfo);
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::Create(const BITMAPINFOHEADER& bmInfo)
{
    m_Bytes  = (bmInfo.biBitCount * bmInfo.biWidth) >> 3;
    m_Width  =  bmInfo.biWidth;
    m_Height =  bmInfo.biHeight;

    while (m_Bytes % 4)
        ++m_Bytes;

    const int size = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize(bmInfo) + m_Bytes * m_Height;
    m_pVoid        = (void*)std::malloc(size);

    if (!m_pVoid)
        return FALSE;

    m_pInfo = (PBITMAPINFO)m_pVoid;
    std::memcpy((void*)&m_pInfo->bmiHeader, (void*)&bmInfo, sizeof(BITMAPINFOHEADER));

    m_pRGB  = (RGBQUAD*)((unsigned char*) m_pVoid  + sizeof(BITMAPINFOHEADER));
    m_pBits =            (unsigned char*)(m_pVoid) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize();
    m_pLine = (BYTE**)std::malloc(sizeof(BYTE*) * m_Height);

    if (!m_pLine)
        return FALSE;

    int    i;
    BYTE** pLine;

    for (i = 0, pLine = m_pLine; i < m_Height; ++i, ++pLine)
        *pLine = m_pBits + (m_Height - i - 1) * m_Bytes;

    m_Flags = 0;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::CreateFromHandle(HANDLE hMem, int bits)
{
    DestroyDIB();

    UCHAR* pVoid = (UCHAR*)::GlobalLock(hMem);

    if (!pVoid)
        return FALSE;

    try
    {
        LPBITMAPINFOHEADER pHead = (LPBITMAPINFOHEADER)pVoid;

        if (!pHead)
            return FALSE;

        m_Width  = pHead->biWidth;
        m_Height = pHead->biHeight;
        m_Bits   = pHead->biBitCount;

        if (pHead->biCompression != BI_RGB)
        {
            ::GlobalUnlock(pVoid);
            return FALSE;
        }

        if (pHead->biBitCount >= 15)
            if (pHead->biBitCount != 24)
            {
                ::GlobalUnlock(pVoid);
                return FALSE;
            }

        if (!Create(*pHead))
        {
            ::GlobalUnlock(pVoid);
            return FALSE;
        }

        RGBQUAD* pRgb = (RGBQUAD*)(pVoid + sizeof(BITMAPINFOHEADER));
        std::memcpy(m_pRGB, pRgb, sizeof(RGBQUAD) * GetPaletteSize());

        UCHAR* pBits = pVoid + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize();
        std::memcpy(m_pBits, pBits, m_Height * m_Bytes);
    }
    catch (...)
    {
        ::GlobalUnlock(pVoid);
        throw;
    }

    ::GlobalUnlock(pVoid);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::DestroyDIB()
{
    if (m_pVoid)
        std::free(m_pVoid);

    m_pVoid = NULL;

    if (m_pLine)
        std::free(m_pLine);

    m_pLine = NULL;
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::InitDIB(COLORREF color)
{
    int            i;
    unsigned char* pLine;

    // 24 bit bitmap?
    if (m_pInfo->bmiHeader.biBitCount == 24)
    {
        // split color into BGR value
        const unsigned char bgr[3] =
        {
            GetBValue(color),
            GetGValue(color),
            GetRValue(color)
        };

        // iterate through lines
        for (i = 0, pLine = m_pBits; i < m_Height; ++i)
        {
            pLine = m_pBits + i * m_Bytes;

            // iterate through line pixels and and set the color
            for (int j = 0; j < m_Width; ++j, pLine += 3)
                std::memcpy(pLine, bgr, 3);
        }
    }
    else
        // iterate through each pixels and set the color
        for (i = 0, pLine = m_pBits; i < m_Height; ++i, pLine += m_Bytes)
            std::memset(pLine, BYTE(color), m_Bytes);
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::CopyDIB(const PSS_DIBitmap& dib)
{
    if (Create(dib.m_pInfo->bmiHeader))
    {
        SetPalette(dib.m_pRGB);
        std::memcpy(m_pBits, dib.m_pBits, m_Height * m_Bytes);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::OpenDIB(const CString& fileName)
{
    return OpenBMP(fileName);
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SaveDIB(const CString& fileName, IEType type)
{
    return SaveBMP(fileName);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::UseGamma(float gamma, BOOL use)
{
    m_UseGamma = use;
    m_OldGamma = m_Gamma;
    m_Gamma    = gamma;
    CreateGammaCurve();
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::ReplaceColor(unsigned char oldColor, unsigned char newColor)
{
    // iterate through lines
    for (int i = 0; i < m_Height; ++i)
    {
        unsigned char* pLine = GetLine(i);

        // is line index out of bounds?
        if (!pLine)
            continue;

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j)
            // if color to replace was found, replaces it by the new one
            if (pLine[j] == oldColor)
                pLine[j] = newColor;
    }
}
//---------------------------------------------------------------------------
HANDLE PSS_DIBitmap::GetDIBits(int startX, int startY, int cx, int cy) const
{
    if (startX == -1)
    {
        startX = startY = 0;
        cx     = m_Width;
        cy     = m_Height;
        
        PSS_DIBitmap dib;
        dib.Create(cx, cy, 8);
        dib.BitBlt(0, 0, cx, cy, *this, 0, 0);
        dib.SetPalette(m_pRGB);
        return dib.DIBHandle();
    }

    return DIBHandle();
}
//---------------------------------------------------------------------------
CBitmap* PSS_DIBitmap::GetBitmap(const CDC& dc) const
{
    ASSERT(m_pVoid);

    // create a bitmap with the device context content
    HBITMAP hBitmap = ::CreateDIBitmap(dc.m_hDC,
                                       PBITMAPINFOHEADER(m_pInfo),
                                       CBM_INIT,
                                       (const void*)m_pBits,
                                       m_pInfo,
                                       DIB_RGB_COLORS);

    if (!hBitmap)
        return NULL;

    std::unique_ptr<CBitmap> pTempBmp(CBitmap::FromHandle(hBitmap));

    if (pTempBmp.get())
    {
        BITMAP bmp;
        pTempBmp->GetBitmap(&bmp);

        LPVOID pVoid = NULL;

        try
        {
            // create a pixel array
            pVoid = std::malloc(bmp.bmWidthBytes * bmp.bmHeight);

            if (!pVoid)
                return NULL;

            // get the source bitmap pixels
            pTempBmp->GetBitmapBits(bmp.bmWidthBytes * bmp.bmHeight, pVoid);

            // create a new compatible bitmap and copy the pixels
            std::unique_ptr<CBitmap> pNewBmp(new CBitmap());
            pNewBmp->CreateBitmapIndirect(&bmp);
            pNewBmp->SetBitmapBits(bmp.bmWidthBytes * bmp.bmHeight, pVoid);

            // release the pixel array
            std::free(pVoid);

            return pNewBmp.release();
        }
        catch (...)
        {
            // release the pixel array
            std::free(pVoid);
            throw;
        }
    }
    
    return NULL;
}
//---------------------------------------------------------------------------
CBitmap* PSS_DIBitmap::GetTempBitmap(const CDC& dc) const
{
    ASSERT(m_pVoid != NULL);

    // create a bitmap with the device context content
    HBITMAP hBitmap = ::CreateDIBitmap(dc.m_hDC,
                                       PBITMAPINFOHEADER(m_pInfo),
                                       CBM_INIT,
                                       (const void*)m_pBits,
                                       m_pInfo,
                                       DIB_RGB_COLORS);

    if (!hBitmap)
        return NULL;

    return CBitmap::FromHandle(hBitmap);
}
//---------------------------------------------------------------------------
DWORD PSS_DIBitmap::GetDIBSize() const
{
    return (sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize() + m_Bytes * m_Height);
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::GetPaletteSize(const BITMAPINFOHEADER& bmInfo) const
{
    switch (bmInfo.biBitCount)
    {
        case 1:  return 2;
        case 4:  return 16;
        case 8:  return 256;
        default: return 0;
    }
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::GetPaletteSize() const
{
    return GetPaletteSize(m_pInfo->bmiHeader);
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::GetColorCount() const
{
    // works only for 256 colors pallettized bitmaps
    ASSERT(GetBitCount() == 8);

    BYTE colors[256];
    std::memset(colors, 0, 256);

    int num = 0;

    // iterate through bitmap lines
    for (int i = 0; i < m_Height; ++i)
    {
        BYTE* pLine = GetLine(i);

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j, ++pLine)
            // was the color index already counted?
            if (!colors[*pLine])
            {
                colors[*pLine] = 1;
                ++num;
            }
    }

    return num;
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::EnumColors(BYTE* pColors) const
{
    // works only for 256 colors pallettized bitmaps
    ASSERT(GetBitCount() == 8);
    ASSERT(pColors);

    // initialize the palette
    std::memset(pColors, 0, 256);

    int num = 0;

    // iterate through bitmap lines
    for (int i = 0; i < m_Height; ++i)
    {
        BYTE* pLine = GetLine(i);

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j, ++pLine)
            // was the color index already found?
            if (!pColors[*pLine])
            {
                pColors[*pLine] = 1;
                ++num;
            }
    }

    return num;
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::CopyLine(int source, int dest)
{
    ASSERT(source <= m_Height && source >= 0);
    ASSERT(dest   <= m_Height && dest   >= 0);

    // nothing to copy?
    if (source == dest)
        return;

    unsigned char* pSrc = GetLine(source);
    unsigned char* pDst = GetLine(dest);

    std::memcpy(pDst, pSrc, m_Bytes);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::SetPalette(unsigned char* pPalette)
{
    if (!pPalette)
        return;

    const int size = GetPaletteSize();

    int      i;
    RGBQUAD* pRgb;

    for (i = 0, pRgb = m_pRGB; i < size; ++i, ++pRgb, pPalette += 3)
    {
        if (m_UseGamma)
        {
            pRgb->rgbRed   = m_GammaCache[pPalette[0]];
            pRgb->rgbGreen = m_GammaCache[pPalette[1]];
            pRgb->rgbBlue  = m_GammaCache[pPalette[2]];
        }
        else
        {
            pRgb->rgbRed   = pPalette[0];
            pRgb->rgbGreen = pPalette[1];
            pRgb->rgbBlue  = pPalette[2];
        }

        pRgb->rgbReserved = BYTE(0);
    }
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::SetPalette(RGBQUAD* pRGB)
{
    if (!pRGB)
        return;

    const int size = GetPaletteSize();

    std::memcpy(m_pRGB, pRGB, size * sizeof(RGBQUAD));
}
//---------------------------------------------------------------------------
COLORREF PSS_DIBitmap::PaletteColor(int index) const
{
    ASSERT(index < 256);

    RGBQUAD* pRGB = m_pRGB + index;

    return RGB(pRGB->rgbRed, pRGB->rgbGreen, pRGB->rgbBlue);
}
//---------------------------------------------------------------------------
COLORREF PSS_DIBitmap::GetPixel(int x, int y) const
{
    ASSERT(x >= 0       && y >= 0);
    ASSERT(x <  m_Width && y <  m_Height);

    unsigned char* pLine = GetLine(y) + (x * 3);
    ASSERT(pLine);

    return RGB(*(pLine + 2), *(pLine + 1), *pLine);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::GetPixel(UINT x, UINT y, int& pixel) const
{
    ASSERT(x < UINT(m_Width));
    ASSERT(y < UINT(m_Height));

    if (x >= UINT(m_Width))
        return;

    if (y >= UINT(m_Height))
        return;

    pixel = GetLine(y)[x];
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::SetPixel(int x, int y, COLORREF color)
{
    ASSERT(x >= 0       && y >= 0);
    ASSERT(x <  m_Width && y <  m_Height);

    unsigned char* pLine = (unsigned char*)(m_pLine[y] + (x * 3));
    ASSERT(pLine);

    *pLine = unsigned char(GetBValue(color)); ++pLine;
    *pLine = unsigned char(GetGValue(color)); ++pLine;
    *pLine = unsigned char(GetRValue(color));
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::SetPixel8(int x, int y, unsigned char color)
{
    ASSERT(x >= 0       && y >= 0);
    ASSERT(x <  m_Width && y <  m_Height);

    unsigned char* pLine = GetLine(y) + x;

    *pLine = color;
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::BitBlt(int                 xDest,
                          int                 yDest,
                          int                 width,
                          int                 height,
                          const PSS_DIBitmap& dibSrc,
                          int                 xSrc,
                          int                 ySrc,
                          BYTE*               pColors)
{
    SetPalette(dibSrc.m_pRGB);

    // set the destination x position if none defined
    if (xDest < 0)
    {
        xSrc  -= xDest;
        width += xDest;
        xDest  = 0;
    }

    // set the destination y position if none defined
    if (yDest < 0)
    {
        ySrc   -= yDest;
        height += yDest;
        yDest   = 0;
    }

    // set the source x position if none defined
    if (xSrc < 0)
    {
        xDest -= xSrc;
        width += xSrc;
        xSrc   = 0;
    }

    // set the source y position if none defined
    if (ySrc < 0)
    {
        yDest  -= ySrc;
        height += ySrc;
        ySrc    = 0;
    }

    // limit the width and height into the limits of the source and destination bitmaps
    width  = xDest + width  > m_Width         ? m_Width         - xDest : width;
    height = yDest + height > m_Height        ? m_Height        - yDest : height;
    width  = xSrc  + width  > dibSrc.m_Width  ? dibSrc.m_Width  - xSrc  : width;
    height = ySrc  + height > dibSrc.m_Height ? dibSrc.m_Height - ySrc  : height;
    width  = __max(0, width);
    height = __max(0, height);

    int i, k, l;

    // are bitmap pallettized?
    if (!pColors)
    {
        // iterate through lines to copy
        for (i = 0, k = ySrc, l = yDest; i < height; ++i, ++k, ++l)
        {
            // do copy line?
            if (k < 0 || l < 0)
                continue;

            unsigned char* pSrcLine  = dibSrc.GetLine(k);
            unsigned char* pDestLine = GetLine(l);

            // copy the line between start and end x position
            std::memcpy(pDestLine + xDest, pSrcLine + xSrc, width);
        }
    }
    else
        // iterate through lines to copy
        for (i = 0, k = ySrc, l = yDest; i < height; ++i, ++k, ++l)
        {
            // do copy line?
            if (k < 0 || l < 0)
                continue;

            unsigned char* pSrcLine  = dibSrc.GetLine(k) + xDest;
            unsigned char* pDestLine = GetLine(l)        + xSrc;

            // iterate through line pixels to copy
            for (int j = 0; j < width; ++j, ++pSrcLine, ++pDestLine)
                if (pColors[*pSrcLine])
                    *pDestLine = *pSrcLine;
        }
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::BitBlt(HDC hDest, int xDest, int yDest, int width, int height, int xSrc, int ySrc) const
{
    ::SetDIBitsToDevice(hDest,
                        xDest,
                        yDest,
                        width,
                        height,
                        xSrc,
                        m_Height - ySrc - height,
                        0,
                        m_Height,
                        m_pBits,
                        m_pInfo,
                        DIB_RGB_COLORS);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::StretchBlt(int                 xDest,
                              int                 yDest,
                              int                 widthDest,
                              int                 heightDest,
                              const PSS_DIBitmap& dibSrc,
                              int                 xSrc,
                              int                 ySrc,
                              int                 widthSrc,
                              int                 heightSrc)
{
    SetPalette(dibSrc.m_pRGB);

    widthDest  = xDest + widthDest  > m_Width  ? m_Width  - xDest : widthDest;
    heightDest = yDest + heightDest > m_Height ? m_Height - yDest : heightDest;

    widthSrc  = xSrc + widthSrc  > dibSrc.m_Width  ? dibSrc.m_Width  - xSrc : widthSrc;
    heightSrc = ySrc + heightSrc > dibSrc.m_Height ? dibSrc.m_Height - ySrc : heightSrc;

    const int xDiv = widthDest / widthSrc;
    const int xMod = widthDest % widthSrc;

    const int yDiv = heightDest / heightSrc;
    const int yMod = heightDest % heightSrc;

    if (!xMod && !yMod && xDiv > 0 && yDiv > 0)
    {
        ExpandBlt(xDest, yDest, xDiv, yDiv, dibSrc, xSrc, ySrc, widthSrc, heightSrc);
        return;
    }

    int i, j, k, l, m, x, y, xErr, yErr;

    unsigned char* pBuffer = (unsigned char*)std::malloc(widthDest + 20);

    try
    {
        for (i = yErr = m = 0; i < heightSrc; ++i)
        {
            unsigned char* pSrcLine = dibSrc.GetLine(i + ySrc) + xSrc;
            unsigned char* pTmpLine = pBuffer;

            for (j = l = xErr = 0; j < widthSrc; ++j, ++pSrcLine)
            {
                k = xDiv;
                xErr += xMod;

                if (xErr >= widthSrc)
                {
                    ++k;
                    xErr %= widthSrc;
                }

                x = 0;

                while (l < widthDest &&  x < k)
                {
                    *pTmpLine = *pSrcLine;
                    ++pTmpLine;
                    ++l;
                    ++x;
                }
            }

            while (l < widthDest)
            {
                *pTmpLine = *pSrcLine;
                ++pTmpLine;
                ++l;
            }

            k     = yDiv;
            yErr += yMod;

            if (yErr >= heightSrc)
            {
                ++k;
                yErr %= heightSrc;
            }

            y = 0;

            while (m < heightDest && y < k)
            {
                unsigned char* pDestLine = GetLine(m + yDest) + xDest;
                std::memcpy(pDestLine, pBuffer, widthDest);
                ++m;
                ++y;
            }
        }

        while (m < heightDest)
        {
            unsigned char* pDestLine = GetLine(m + yDest) + xDest;
            std::memcpy(pDestLine, pBuffer, widthDest);
            ++m;
        }
    }
    catch (...)
    {
        std::free(pBuffer);
        throw;
    }

    std::free(pBuffer);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::StretchBlt(HDC hDest,
                              int xDest,
                              int yDest,
                              int widthDest,
                              int heightDest,
                              int xSrc,
                              int ySrc,
                              int widthSrc,
                              int heightSrc) const
{
    StretchDIBits(hDest,
                  xDest,
                  yDest,
                  widthDest,
                  heightDest,
                  xSrc,
                  ySrc,
                  widthSrc,
                  heightSrc,
                  m_pBits,
                  (CONST BITMAPINFO*)&m_pInfo->bmiHeader,
                  DIB_RGB_COLORS,
                  SRCCOPY);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::ExpandBlt(int                 nXDest,
                             int                 nYDest,
                             int                 xRatio,
                             int                 yRatio,
                             const PSS_DIBitmap& dibSrc,
                             int                 xSrc,
                             int                 ySrc,
                             int                 widthSrc,
                             int                 heightSrc)
{
    SetPalette(dibSrc.m_pRGB);

    widthSrc  = xSrc + widthSrc  > dibSrc.m_Width  ? dibSrc.m_Width  - xSrc : widthSrc;
    heightSrc = ySrc + heightSrc > dibSrc.m_Height ? dibSrc.m_Height - ySrc : heightSrc;

    Expand(nXDest, nYDest, xRatio, yRatio, dibSrc, xSrc, ySrc, widthSrc, heightSrc);
}
//---------------------------------------------------------------------------
unsigned char* PSS_DIBitmap::GetLine(int line) const
{
    return m_pLine[line];
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::Make8Bit(const PSS_DIBitmap& dib)
{
    ASSERT(m_Width  == dib.m_Width);
    ASSERT(m_Height == dib.m_Height);

    const int bits = dib.GetBitCount();

    switch (bits)
    {
        case 1:  return SwitchFromOne(dib);
        case 4:  return SwitchFromFour(dib);
        case 8:  return SwitchPalette(dib);
        case 24: return SwitchFrom24(dib);
        default: return FALSE;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SwitchFromOne(const PSS_DIBitmap& dib)
{
    std::memset(m_Cache, 0, sizeof(m_Cache));

    unsigned char cols[2];
    cols[0] = ClosestColor(dib.m_pRGB);
    cols[1] = ClosestColor(dib.m_pRGB + 1);

    // iterate through lines
    for (int i = 0; i < m_Height; ++i)
    {
        unsigned char* pSrcLine  = dib.GetLine(i);
        unsigned char* pDestLine = GetLine(i);

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j, ++pDestLine)
            if (!(pSrcLine[j >> 3] & g_MaskTable[j & 7]))
                *pDestLine = cols[0];
            else
                *pDestLine = cols[1];
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SwitchFromFour(const PSS_DIBitmap& dib)
{
    std::memset(m_Cache, 0, sizeof(m_Cache));

    unsigned char cols[16];

    // build the color palette
    for (int i = 0; i < 16; ++i)
        cols[i] = ClosestColor(dib.m_pRGB + i);

    // iterate through lines
    for (int i = 0; i < m_Height; ++i)
    {
        unsigned char* pSrcLine  = dib.GetLine(i);
        unsigned char* pDestLine = GetLine(i);

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j, ++pDestLine)
        {
            int n;

            if (!(j & 1))
                n = (*pSrcLine & 0xf0) >> 4;
            else
            {
                n = *pSrcLine & 0x0f;
                ++pSrcLine;
            }

            *pDestLine = cols[n];
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SwitchFrom24(const PSS_DIBitmap& dib)
{
    BYTE* pIndex = (BYTE*)std::malloc(0x7FFF + 1);

    if (!pIndex)
        return FALSE;

    try
    {
        std::memset(m_Cache, 0, sizeof(m_Cache));

        for (int i = 0; i <= 0x7FFF; ++i)
        {
            RGBQUAD rgb;
            rgb.rgbRed   = (((i & 0x7C00) >> 10) << 3) | 0x07;
            rgb.rgbGreen = (((i & 0x3e0)  >> 5)  << 3) | 0x07;
            rgb.rgbBlue  =  ((i & 0x1F)   << 3)        | 0x07;
            pIndex[i]    = ClosestColor(&rgb);
        }

        // iterate through lines
        for (int i = 0; i < m_Height; ++i)
        {
            unsigned char* pSrcLine  = dib.GetLine(i);
            unsigned char* pDestLine = GetLine(i);

            // iterate through line pixels
            for (int j = 0; j < m_Width; ++j, ++pDestLine, pSrcLine += 3)
            {
                const int c = (*pSrcLine >> 3) | ((*(pSrcLine + 1) >> 3) << 5) | ((*(pSrcLine + 2) >> 3) << 10);
                *pDestLine  = pIndex[c];
            }
        }
    }
    catch (...)
    {
        std::free(pIndex);
        throw;
    }

    std::free(pIndex);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SwitchPalette(const PSS_DIBitmap& dib)
{
    std::memset(m_Cache, 0, sizeof(m_Cache));

    unsigned char cols[256];

    // build the color palette
    for (int i = 0; i < 256; ++i)
        cols[i] = ClosestColor(dib.m_pRGB + i);

    // iterate through lines
    for (int i = 0; i < m_Height; ++i)
    {
        unsigned char* pSrcLine  = dib.GetLine(i);
        unsigned char* pDestLine = GetLine(i);

        // iterate through line pixels
        for (int j = 0; j < m_Width; ++j, ++pSrcLine, ++pDestLine)
            *pDestLine = cols[*pSrcLine];
    }

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_DIBitmap::ClosestColor(RGBQUAD* pRgb)
{
    RGBQUAD*  pQuad = m_pRGB;
    const int size  = GetPaletteSize();

    // build the palette cache
    for (int i = 0; i < size; ++i)
        if (m_Cache[i])
            if (!std::memcmp((void*)&m_QuadCache[i], (void*)pRgb, 3))
                return i;

    unsigned dist = M_Big_Distance;
    unsigned c    = 0;

    // iterate through pixels
    for (int i = 0; i < size; ++i, ++pQuad)
    {
        const unsigned d = Distance(*pRgb, *pQuad);

        // found the closest color?
        if (!d)
        {
            m_QuadCache[i] = *pRgb;
            m_Cache[i]     =  1;

            return i;
        }

        if (dist > d)
        {
            c    = i;
            dist = d;
        }
    }

    m_QuadCache[c] = *pRgb;
    m_Cache[c]     =  1;

    return c;
}
//---------------------------------------------------------------------------
unsigned PSS_DIBitmap::Distance(const RGBQUAD& rgb1, const RGBQUAD& rgb2)
{
    unsigned d;
    d  = 3 * unsigned(rgb1.rgbRed   - rgb2.rgbRed)   * unsigned(rgb1.rgbRed   - rgb2.rgbRed);
    d += 4 * unsigned(rgb1.rgbGreen - rgb2.rgbGreen) * unsigned(rgb1.rgbGreen - rgb2.rgbGreen);
    d += 2 * unsigned(rgb1.rgbBlue  - rgb2.rgbBlue)  * unsigned(rgb1.rgbBlue  - rgb2.rgbBlue);
    return d;
}
//---------------------------------------------------------------------------
HANDLE PSS_DIBitmap::DIBHandle() const
{
    const int size = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize() + m_Bytes * m_Height;
    HANDLE    hMem = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, size);

    if (!hMem)
        return NULL;

    UCHAR* pVoid = (UCHAR*)::GlobalLock(hMem);

    if (!pVoid)
        return NULL;

    try
    {
        LPBITMAPINFOHEADER pHead = LPBITMAPINFOHEADER(pVoid);

        if (!pHead)
            return NULL;

        std::memcpy(pHead, &m_pInfo->bmiHeader, sizeof(BITMAPINFOHEADER));

        RGBQUAD* pRgb = (RGBQUAD*)(pVoid + sizeof(BITMAPINFOHEADER));
        std::memcpy(pRgb, m_pRGB, sizeof(RGBQUAD) * GetPaletteSize());

        UCHAR* pBits = pVoid + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize();
        std::memcpy(pBits, m_pBits, m_Height * m_Bytes);
    }
    catch (...)
    {
        ::GlobalUnlock(pVoid);
        throw;
    }

    ::GlobalUnlock(pVoid);

    return hMem;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::OpenBMP(const CString& fileName)
{
    CFile file;

    if (!file.Open(fileName, CFile::modeRead | CFile::typeBinary))
        return FALSE;

    BITMAPFILEHEADER fileHeader;
    file.Read(&fileHeader, sizeof(fileHeader));

    if (std::memcmp((void*)&fileHeader.bfType, "BM", 2))
    {
        file.Close();
        return FALSE;
    }

    BITMAPINFOHEADER infoHeader;
    file.Read(&infoHeader, sizeof(infoHeader));

    if (!Create(infoHeader))
    {
        file.Close();
        return FALSE;
    }

    file.Read(m_pRGB, sizeof(RGBQUAD) * GetPaletteSize());
    file.Seek(fileHeader.bfOffBits, CFile::begin);
    file.Read(m_pBits, m_Height * m_Bytes);
    file.Close();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DIBitmap::SaveBMP(const CString& fileName)
{
    CFile file;

    if (!file.Open(fileName, CFile::modeWrite | CFile::typeBinary))
        return FALSE;

    BITMAPFILEHEADER fileHeader;
    ::ZeroMemory(&fileHeader, sizeof(fileHeader));
    std::memcpy((void*)&fileHeader.bfType, "BM", 2);

    fileHeader.bfSize    = GetDIBSize() + sizeof(fileHeader);
    fileHeader.bfOffBits = sizeof(BITMAPINFOHEADER) + GetPaletteSize() * sizeof(RGBQUAD) + sizeof(BITMAPFILEHEADER);
    file.Write(&fileHeader, sizeof(fileHeader));
    file.Write(m_pVoid, GetDIBSize());
    file.Close();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::CreateGammaCurve()
{
    for (int i = 0; i < 256; ++i)
        m_GammaCache[i] = int(255.0 * std::pow(double(i) / 255.0, double(m_Gamma)) + 0.5);
}
//---------------------------------------------------------------------------
void PSS_DIBitmap::Expand(int                 xDest,
                          int                 yDest,
                          int                 xRatio,
                          int                 yRatio,
                          const PSS_DIBitmap& dibSrc,
                          int                 xSrc,
                          int                 ySrc,
                          int                 widthSrc,
                          int                 heightSrc) const
{
    ASSERT(xRatio);
    ASSERT(yRatio);

    int widthDest  = widthSrc  * xRatio;
    int heightDest = heightSrc * yRatio;

    widthDest  = xDest + widthDest  > m_Width  ? m_Width  - xDest : widthDest;
    heightDest = yDest + heightDest > m_Height ? m_Height - yDest : heightDest;

    const int xNum = widthDest  / xRatio;
    const int yNum = heightDest / yRatio;
    const int xErr = widthDest  % xRatio;
    const int yErr = heightDest % yRatio;

    unsigned char* pBuffer = (unsigned char*)std::malloc(widthDest + 20);

    if (!pBuffer)
        return;

    try
    {
        for (int i = 0; i < yNum; ++i, ++ySrc)
        {
            unsigned char* pSrcLine = dibSrc.GetLine(ySrc) + xSrc;
            unsigned char* pTmpBuffer = pBuffer;
            int            k = 0;

            for (int j = 0; j < xNum; ++j, pTmpBuffer += xRatio)
            {
                std::memset(pTmpBuffer, *(pSrcLine + j), xRatio);
                k = *(pSrcLine + j);
            }

            std::memset(pTmpBuffer, unsigned char(k), xErr);

            for (int j = 0; j < yRatio; ++j, ++yDest)
            {
                unsigned char* pDestLine = GetLine(yDest) + xDest;
                std::memcpy(pDestLine, pBuffer, widthDest);
            }
        }

        for (int j = 0; j < yErr; ++j, ++yDest)
        {
            unsigned char* pDestLine = GetLine(yDest) + xDest;
            std::memcpy(pDestLine, pBuffer, widthDest);
        }
    }
    catch (...)
    {
        std::free(pBuffer);
        throw;
    }

    std::free(pBuffer);
}
//---------------------------------------------------------------------------
