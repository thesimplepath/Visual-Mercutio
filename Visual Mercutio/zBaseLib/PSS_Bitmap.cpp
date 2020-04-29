/****************************************************************************
 * ==> PSS_Bitmap ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a bitmap graphic                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Bitmap.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_Bitmap
//---------------------------------------------------------------------------
PSS_Bitmap::PSS_Bitmap() :
    m_hDIB(NULL),
    m_IsValid(false)
{}
//---------------------------------------------------------------------------
PSS_Bitmap::~PSS_Bitmap()
{}
//---------------------------------------------------------------------------
bool PSS_Bitmap::LoadBitmap(UINT resID)
{
    m_IsValid = CBitmap::LoadBitmap(resID);
    LoadSize();
    return m_IsValid;
}
//---------------------------------------------------------------------------
bool PSS_Bitmap::LoadBitmapFromFile(LPCTSTR fileName)
{
    PSS_Assert(fileName);
    DeleteObject();

    HBITMAP hBitmap = HBITMAP(LoadImage(NULL,
                                        fileName,
                                        IMAGE_BITMAP,
                                        0,
                                        0,
                                        LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE));

    // set valid flag
    m_IsValid = Attach(hBitmap);
    LoadSize();
    return m_IsValid;
}
//---------------------------------------------------------------------------
bool PSS_Bitmap::LoadDIBSectionFromFile(LPCTSTR pFileName, LPVOID* pPixels, HANDLE hSection, DWORD offset)
{
    CFile  file;

    if (!file.Open(pFileName, CFile::modeRead))
        return false;

    BITMAPFILEHEADER bmfHeader;
    
    const long fileLen = long(file.GetLength());

    // read file header
    if (file.Read(LPSTR(&bmfHeader), sizeof(bmfHeader)) != sizeof(bmfHeader))
        return false;

    // file type should be 'BM'
    if (bmfHeader.bfType != (WORD('M' << 8) | 'B'))
        return false;

    BITMAPINFO* pBmInfo = (BITMAPINFO*)::GlobalAlloc(GMEM_FIXED, sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 256);

    if (!pBmInfo)
        return false;

    // read the bitmap info
    file.Read(pBmInfo, sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 256);

    LPVOID      pBits;
    BITMAPINFO& bmInfo = *pBmInfo;
    HBITMAP     hBmp   = CreateDIBSection(NULL, pBmInfo, DIB_RGB_COLORS, &pBits, hSection, offset);
    LPBYTE      pDIBBits;

    const int colors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 1 << bmInfo.bmiHeader.biBitCount;

    if (bmInfo.bmiHeader.biBitCount > 8)
        pDIBBits = LPBYTE(LPDWORD(bmInfo.bmiColors            +
                                  bmInfo.bmiHeader.biClrUsed) +
                                ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        pDIBBits = LPBYTE(bmInfo.bmiColors + colors);

    const int bmOffset = sizeof(BITMAPFILEHEADER) + (pDIBBits - LPBYTE(pBmInfo));
    file.Seek(bmOffset, CFile::begin);
    file.Read(LPSTR(pBits), fileLen - bmOffset);

    ::GlobalFree(pBmInfo);

    if (pPixels)
        *pPixels = pBits;

    // set valid flag
    m_IsValid = Attach(hBmp);
    LoadSize();

    return m_IsValid;
}
//---------------------------------------------------------------------------
HANDLE PSS_Bitmap::DDBToDIB(DWORD compression, CPalette* pPal)
{
    PSS_Assert(GetSafeHandle());

    // the function has no arg for bitfields
    if (compression == BI_BITFIELDS)
        return NULL;

    HPALETTE hPal;

    if (!pPal)
        // if no palette was provided, use the default one
        hPal = HPALETTE(::GetStockObject(DEFAULT_PALETTE));
    else
    {
        hPal = HPALETTE(pPal->GetSafeHandle());

        // if the provided palette cannot be used, use the default one instead
        if (!hPal)
            hPal = HPALETTE(::GetStockObject(DEFAULT_PALETTE));
    }

    BITMAP bm;

    // get bitmap information
    GetObject(sizeof(bm), LPSTR(&bm));

    BITMAPINFOHEADER biHeader;

    // initialize the bitmap info header
    biHeader.biSize          = sizeof(BITMAPINFOHEADER);
    biHeader.biWidth         = bm.bmWidth;
    biHeader.biHeight        = bm.bmHeight;
    biHeader.biPlanes        = 1;
    biHeader.biBitCount      = bm.bmPlanes * bm.bmBitsPixel;
    biHeader.biCompression   = compression;
    biHeader.biSizeImage     = 0;
    biHeader.biXPelsPerMeter = 0;
    biHeader.biYPelsPerMeter = 0;
    biHeader.biClrUsed       = 0;
    biHeader.biClrImportant  = 0;

    // compute the size of the info header and the color table
    int colors = (1 << biHeader.biBitCount);

    if (colors > 256)
        colors = 0;

    DWORD len = biHeader.biSize + colors * sizeof(RGBQUAD);
    HDC   hDC = NULL;
    m_hDIB    = NULL;

    try
    {
        // need a device context to get the DIB from
        hDC  = ::GetDC(NULL);
        hPal = ::SelectPalette(hDC, hPal, FALSE);
        ::RealizePalette(hDC);

        // allocate enough memory to hold the bitmap info header and color table
        m_hDIB = ::GlobalAlloc(GMEM_FIXED, len);

        if (!m_hDIB)
        {
            ::SelectPalette(hDC, hPal, FALSE);
            ::ReleaseDC(NULL, hDC);
            return NULL;
        }

        LPBITMAPINFOHEADER pBIHeader = LPBITMAPINFOHEADER(m_hDIB);

        *pBIHeader = biHeader;

        // call GetDIBits with a NULL lpBits param, thus the device driver will calculate the biSizeImage field
        ::GetDIBits(hDC,
                    HBITMAP(GetSafeHandle()),
                    0L,
                    DWORD(biHeader.biHeight),
                    LPBYTE(NULL),
                    LPBITMAPINFO(pBIHeader),
                    DWORD(DIB_RGB_COLORS));

        biHeader = *pBIHeader;

        // if the driver didn't fill the biSizeImage field, compute it. Each image scan line is aligned on a DWORD
        // (32 bit) boundary
        if (!biHeader.biSizeImage)
        {
            biHeader.biSizeImage = ((((biHeader.biWidth * biHeader.biBitCount) + 31) & ~31) / 8) * biHeader.biHeight;

            // if a compression scheme is used, the result may be larger than expected. Increase the size to consider that
            if (compression != BI_RGB)
                biHeader.biSizeImage = (biHeader.biSizeImage * 3) / 2;
        }

        // realloc the buffer so that it can hold all the bits
        len += biHeader.biSizeImage;

        HANDLE handle;

        if (handle = ::GlobalReAlloc(m_hDIB, len, GMEM_MOVEABLE))
            m_hDIB = handle;
        else
        {
            ::GlobalFree(m_hDIB);

            // reselect the original palette
            SelectPalette(hDC, hPal, FALSE);
            ReleaseDC(NULL, hDC);

            return NULL;
        }

        // get the bitmap bits
        pBIHeader = LPBITMAPINFOHEADER(m_hDIB);

        // get the DIB
        const BOOL result = ::GetDIBits(hDC,
                                        HBITMAP(GetSafeHandle()),
                                        0L,
                                        DWORD(biHeader.biHeight),
                                        LPBYTE(pBIHeader) + (biHeader.biSize + colors * sizeof(RGBQUAD)),
                                        LPBITMAPINFO(pBIHeader),
                                        DWORD(DIB_RGB_COLORS));

        if (!result)
        {
            ::GlobalFree(m_hDIB);

            ::SelectPalette(hDC, hPal, FALSE);
            ::ReleaseDC(NULL, hDC);

            return NULL;
        }

        ::SelectPalette(hDC, hPal, FALSE);
        ::ReleaseDC(NULL, hDC);

        // set valid flag
        m_IsValid = m_hDIB;

        LoadSize();
    }
    catch (...)
    {
        if (m_hDIB)
            ::GlobalFree(m_hDIB);

        if (hDC)
        {
            ::SelectPalette(hDC, hPal, FALSE);
            ::ReleaseDC(NULL, hDC);
        }

        throw;
    }

    return m_hDIB;
}
//---------------------------------------------------------------------------
HBITMAP PSS_Bitmap::DIBToDDB(HANDLE hDIB)
{
    if (!hDIB)
        return NULL;

    LPBITMAPINFOHEADER pBIHeader = LPBITMAPINFOHEADER(hDIB);

    const int colors = pBIHeader->biClrUsed ? pBIHeader->biClrUsed : 1 << pBIHeader->biBitCount;

    BITMAPINFO& bmInfo = *(LPBITMAPINFO)hDIB;
    LPVOID      pDIBBits;

    if (bmInfo.bmiHeader.biBitCount > 8)
        pDIBBits = LPVOID(LPDWORD(bmInfo.bmiColors +
                                  bmInfo.bmiHeader.biClrUsed) +
                                ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        pDIBBits = LPVOID(bmInfo.bmiColors + colors);

    CPalette  pal;
    CPalette* pOldPal = NULL;
    CClientDC dc(NULL);

    // create and select a logical palette if needed
    if (colors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        const UINT  size = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * colors);
        LOGPALETTE* pLP = (LOGPALETTE*)new BYTE[size];

        pLP->palVersion    = 0x300;
        pLP->palNumEntries = colors;

        for (int i = 0; i < colors; ++i)
        {
            pLP->palPalEntry[i].peRed   = bmInfo.bmiColors[i].rgbRed;
            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
            pLP->palPalEntry[i].peBlue  = bmInfo.bmiColors[i].rgbBlue;
            pLP->palPalEntry[i].peFlags = 0;
        }

        pal.CreatePalette(pLP);

        delete[] pLP;

        // select and realize the palette
        pOldPal = dc.SelectPalette(&pal, FALSE);
        dc.RealizePalette();
    }

    HBITMAP hBitmap = ::CreateDIBitmap(dc.GetSafeHdc(),
                                       LPBITMAPINFOHEADER(pBIHeader),
                                       LONG(CBM_INIT),
                                       pDIBBits,
                                       LPBITMAPINFO(pBIHeader),
                                       DIB_RGB_COLORS);

    if (pal.GetSafeHandle())
        dc.SelectPalette(pOldPal, FALSE);

    return hBitmap;
}
//---------------------------------------------------------------------------
bool PSS_Bitmap::DIBToDDB()
{
    HANDLE handle = GetDIBHandle();

    if (!handle)
        return false;

    HBITMAP hBmp = DIBToDDB(handle);

    if (hBmp)
    {
        // set valid flag
        m_IsValid = Attach(hBmp);
        LoadSize();

        return m_IsValid;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_Bitmap::DrawBitmap(CDC* pDC, HPALETTE hPal, int x, int y)
{
    BITMAP bm;

    // get logical coordinates
    ::GetObject((HBITMAP)GetSafeHandle(), sizeof(bm), &bm);
    const CPoint size(bm.bmWidth, bm.bmHeight);

    CPoint org(0, 0);
    pDC->DPtoLP(&org);

    CDC memDC;

    // create a memory DC compatible with the destination DC
    memDC.CreateCompatibleDC(pDC);
    memDC.SetMapMode(pDC->GetMapMode());

    HBITMAP hBmOld = HBITMAP(::SelectObject(memDC.m_hDC, HBITMAP(GetSafeHandle())));

    // select and realize the palette
    if (hPal && pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);
        pDC->RealizePalette();
    }

    pDC->BitBlt(x, y, size.x, size.y, &memDC, org.x, org.y, SRCCOPY);

    ::SelectObject(memDC.m_hDC, hBmOld);
}
//---------------------------------------------------------------------------
void PSS_Bitmap::DrawDIB(CDC* pDC, HGLOBAL hDIB, CPalette* pPal, int x, int y)
{
    LPVOID      pDIBBits;
    BITMAPINFO& bmInfo  = *LPBITMAPINFO(hDIB);
    const int   colors  = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 1 << bmInfo.bmiHeader.biBitCount;
    BOOL        success = FALSE;

    // compute bitmap bits address
    if (bmInfo.bmiHeader.biBitCount > 8)
        pDIBBits = LPVOID(LPDWORD(bmInfo.bmiColors +
                                  bmInfo.bmiHeader.biClrUsed) +
                                ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        pDIBBits = LPVOID(bmInfo.bmiColors + colors);

    // select and realize the palette if one supplied and if device supports it
    if (pPal && (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE))
    {
        pDC->SelectPalette(pPal, FALSE);
        pDC->RealizePalette();
    }

    ::StretchDIBits(pDC->m_hDC,
                    x,
                    y,
                    bmInfo.bmiHeader.biWidth,
                    bmInfo.bmiHeader.biHeight,
                    0,
                    0,
                    bmInfo.bmiHeader.biWidth,
                    bmInfo.bmiHeader.biHeight,
                    pDIBBits,
                    LPBITMAPINFO(hDIB),
                    DIB_RGB_COLORS,
                    SRCCOPY);
}
//---------------------------------------------------------------------------
void PSS_Bitmap::DrawDIB(CDC* pDC, CPalette* pPal, int x, int y)
{
    HANDLE handle = GetDIBHandle();

    if (handle)
        DrawDIB(pDC, GetDIBHandle(), pPal, x, y);
}
//---------------------------------------------------------------------------
bool PSS_Bitmap::LoadSize()
{
    if (!IsValid())
        return false;

    BITMAP bm;

    // get logical coordinates
    ::GetObject(HBITMAP(GetSafeHandle()), sizeof(bm), &bm);
    m_Size.cx = bm.bmWidth;
    m_Size.cy = bm.bmHeight;

    return true;
}
//---------------------------------------------------------------------------
