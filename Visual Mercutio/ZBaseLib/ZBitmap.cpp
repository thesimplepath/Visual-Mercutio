// ZBitmap.cpp: implementation of the ZBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBitmap::ZBitmap()
: m_hDIB(NULL), m_IsValid(false)
{

}

ZBitmap::~ZBitmap()
{

}

bool ZBitmap::LoadBitmap(UINT nResID) 
{ 
    m_IsValid = CBitmap::LoadBitmap( nResID );
    LoadSize();
    return m_IsValid;
}

bool ZBitmap::LoadBitmapFromFile(LPCTSTR szFilename) 
{ 
    ASSERT(szFilename);
    DeleteObject();

    HBITMAP hBitmap = NULL; 
    hBitmap = (HBITMAP)LoadImage(NULL, szFilename, IMAGE_BITMAP, 0, 0, 
        LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE); 
    // Set valid flag
    m_IsValid = Attach(hBitmap); 
    LoadSize();
    return m_IsValid;
}


// LoadDIBSectionFromFile    - Creates a DIB section from BMP file
// lpszFileName            - Name of the BMP file
// ppvBits            - to receive address of bitmap bits
// hSection        - optional handle to a file mapping object
// dwOffset        - offset to the bitmap bit values within hSection
bool ZBitmap::LoadDIBSectionFromFile( LPCTSTR lpszFileName, LPVOID *ppvBits, 
                                      HANDLE hSection, DWORD dwOffset) 
{
    LPVOID lpBits;
    CFile file;
    if (!file.Open( lpszFileName, CFile::modeRead))
        return false;
    
    BITMAPFILEHEADER bmfHeader;
    long nFileLen;
    
    nFileLen = (long)file.GetLength();
    
    // Read file header
    if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
        return false;
    
    // File type should be 'BM'
    if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
        return false;

    BITMAPINFO *pbmInfo;
    pbmInfo = (BITMAPINFO *)::GlobalAlloc(GMEM_FIXED, 
                sizeof(BITMAPINFO) + sizeof(RGBQUAD)*256 );
    if (pbmInfo == NULL)
        return false;
    
    // Read the BITMAPINFO
    file.Read( pbmInfo, sizeof(BITMAPINFO) + sizeof(RGBQUAD)*256 );
    
    BITMAPINFO &bmInfo = *pbmInfo ;
    
    HBITMAP hBmp = CreateDIBSection( NULL, pbmInfo, DIB_RGB_COLORS, &lpBits, 
                        hSection, dwOffset );

    LPBYTE  lpDIBBits;              // Pointer to DIB bits
    int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
                1 << bmInfo.bmiHeader.biBitCount;
    
    if (bmInfo.bmiHeader.biBitCount > 8)
    {
        lpDIBBits = (LPBYTE)((LPDWORD)(bmInfo.bmiColors + 
                                       bmInfo.bmiHeader.biClrUsed) + 
                                       ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    }
    else
        lpDIBBits = (LPBYTE)(bmInfo.bmiColors + nColors);

    int nOffset = sizeof(BITMAPFILEHEADER) + (lpDIBBits - (LPBYTE)pbmInfo);
    file.Seek( nOffset, CFile::begin);
    file.Read((LPSTR)lpBits, nFileLen - nOffset); //bmInfo.biSizeImage ); 

    ::GlobalFree(pbmInfo);

    if( ppvBits )
        *ppvBits = lpBits;
    
    // Set valid flag
    m_IsValid = Attach(hBmp); 
    LoadSize();
    return m_IsValid;
}


// DrawBitmap    - Draws a bitmap (DDB & DIB section) onto a device
// pDC        - Pointer to a device context
// hBitmap    - Handle of the bitmap
// hPal        - Handle of a logical palette associated with the bitmap
// xDest    - x-coordinate of the upper-left corner of the destination rect
// yDest    - y-coordinate of the upper-left corner of the destination rect
void ZBitmap::DrawBitmap( CDC *pDC, HPALETTE hPal, int xDest, int yDest )
{
    // Get logical coordinates
    BITMAP bm;
    ::GetObject( (HBITMAP)GetSafeHandle(), sizeof( bm ), &bm );
    CPoint size( bm.bmWidth, bm.bmHeight );
//    pDC->DPtoLP(&size);

    CPoint org(0,0);
    pDC->DPtoLP(&org);

    // Create a memory DC compatible with the destination DC
    CDC memDC;
    memDC.CreateCompatibleDC( pDC );
    memDC.SetMapMode( pDC->GetMapMode() );
    
    //memDC.SelectObject( &bitmap );
    HBITMAP hBmOld = (HBITMAP)::SelectObject( memDC.m_hDC, (HBITMAP)GetSafeHandle() );
    
    
    // Select and realize the palette
    if( hPal && pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        SelectPalette( pDC->GetSafeHdc(), hPal, FALSE );
        pDC->RealizePalette();
    }
    pDC->BitBlt(xDest, yDest, size.x, size.y, &memDC, org.x, org.y, SRCCOPY);

    ::SelectObject( memDC.m_hDC, hBmOld );
}


// DrawDIB    - Draws a DIB onto a device
// pDC        - Pointer to a device context
// hDIB        - Handle of the device-independent bitmap
// pPal        - Pointer to a palette associated with the DIB
// xDest    - x-coordinate of the upper-left corner of the destination rect
// yDest    - y-coordinate of the upper-left corner of the destination rect
void ZBitmap::DrawDIB( CDC* pDC, HGLOBAL hDIB, CPalette *pPal, int xDest, int yDest )
{
    LPVOID  lpDIBBits;              // Pointer to DIB bits
    BOOL    bSuccess=FALSE;         // Success/fail flag
    
    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
    int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
                1 << bmInfo.bmiHeader.biBitCount;
    
    // Compute the address of the bitmap bits
    if( bmInfo.bmiHeader.biBitCount > 8 )
        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + 
            bmInfo.bmiHeader.biClrUsed) + 
            ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
    
    // Select and realize the palette if one supplied and if device supports it
    if( pPal && (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE) )
    {
        pDC->SelectPalette(pPal, FALSE);
        pDC->RealizePalette();
    }

    ::StretchDIBits(pDC->m_hDC,          // hDC
        xDest,                    // DestX
        yDest,                    // DestY
        bmInfo.bmiHeader.biWidth,                    // nDestWidth
        bmInfo.bmiHeader.biHeight,                    // nDestHeight
        0,                     // SrcX
        0,                     // SrcY
        bmInfo.bmiHeader.biWidth,         // nSrcWidth
        bmInfo.bmiHeader.biHeight,         // nSrcHeight
        lpDIBBits,                 // lpBits
        (LPBITMAPINFO)hDIB,              // lpBitsInfo
        DIB_RGB_COLORS,             // wUsage
        SRCCOPY);
/*
    ::SetDIBitsToDevice(pDC->m_hDC,          // hDC
        xDest,                     // DestX
        yDest,                     // DestY
        bmInfo.bmiHeader.biWidth,         // nDestWidth
        bmInfo.bmiHeader.biHeight,         // nDestHeight
        0,                     // SrcX
        0,                     // SrcY
        0,                     // nStartScan
        bmInfo.bmiHeader.biHeight,         // nNumScans
        lpDIBBits,                 // lpBits
        (LPBITMAPINFO)hDIB,              // lpBitsInfo
        DIB_RGB_COLORS);             // wUsage
*/
}

void    ZBitmap::DrawDIB( CDC* pDC, CPalette *pPal, int xDest, int yDest )
{
    if (GetDIBHandle() != NULL)
        ZBitmap::DrawDIB( pDC, GetDIBHandle(), pPal, xDest, yDest );
}


// DDBToDIB        - Creates a DIB from a DDB
// bitmap        - Device dependent bitmap
// dwCompression    - Type of compression - see BITMAPINFOHEADER
// pPal            - Logical palette
HANDLE ZBitmap::DDBToDIB( DWORD dwCompression, CPalette* pPal ) 
{
    BITMAP            bm;
    BITMAPINFOHEADER    bi;
    LPBITMAPINFOHEADER     lpbi;
    DWORD            dwLen;
    HANDLE            handle;
    HDC             hDC;
    HPALETTE        hPal;


    ASSERT( GetSafeHandle() );

    // The function has no arg for bitfields
    if( dwCompression == BI_BITFIELDS )
        return NULL;

    if (pPal==NULL)
    {
        // If a palette has not been supplied use defaul palette
        hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
    }
    else
    {
        // If a palette has not been supplied use defaul palette
        hPal = (HPALETTE) pPal->GetSafeHandle();
        if (hPal==NULL)
            hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
    }
    // Get bitmap information
    GetObject(sizeof(bm),(LPSTR)&bm);

    // Initialize the bitmapinfoheader
    bi.biSize        = sizeof(BITMAPINFOHEADER);
    bi.biWidth        = bm.bmWidth;
    bi.biHeight         = bm.bmHeight;
    bi.biPlanes         = 1;
    bi.biBitCount        = bm.bmPlanes * bm.bmBitsPixel;
    bi.biCompression    = dwCompression;
    bi.biSizeImage        = 0;
    bi.biXPelsPerMeter    = 0;
    bi.biYPelsPerMeter    = 0;
    bi.biClrUsed        = 0;
    bi.biClrImportant    = 0;

    // Compute the size of the  infoheader and the color table
    int nColors = (1 << bi.biBitCount);
    if( nColors > 256 ) 
        nColors = 0;
    dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

    // We need a device context to get the DIB from
    hDC = GetDC(NULL);
    hPal = SelectPalette(hDC,hPal,FALSE);
    RealizePalette(hDC);

    // Allocate enough memory to hold bitmapinfoheader and color table
    m_hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

    if (!m_hDIB)
    {
        SelectPalette(hDC,hPal,FALSE);
        ReleaseDC(NULL,hDC);
        return NULL;
    }

    lpbi = (LPBITMAPINFOHEADER)m_hDIB;

    *lpbi = bi;

    // Call GetDIBits with a NULL lpBits param, so the device driver 
    // will calculate the biSizeImage field 
    GetDIBits(hDC, (HBITMAP)GetSafeHandle(), 0L, (DWORD)bi.biHeight,
            (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

    bi = *lpbi;

    // If the driver did not fill in the biSizeImage field, then compute it
    // Each scan line of the image is aligned on a DWORD (32bit) boundary
    if (bi.biSizeImage == 0)
    {
        bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
                        * bi.biHeight;

        // If a compression scheme is used the result may infact be larger
        // Increase the size to account for this.
        if (dwCompression != BI_RGB)
            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
    }

    // Realloc the buffer so that it can hold all the bits
    dwLen += bi.biSizeImage;
    if (handle = GlobalReAlloc(m_hDIB, dwLen, GMEM_MOVEABLE))
        m_hDIB = handle;
    else
    {
        GlobalFree(m_hDIB);

        // Reselect the original palette
        SelectPalette(hDC,hPal,FALSE);
        ReleaseDC(NULL,hDC);
        return NULL;
    }

    // Get the bitmap bits
    lpbi = (LPBITMAPINFOHEADER)m_hDIB;

    // FINALLY get the DIB
    BOOL bGotBits = GetDIBits( hDC, (HBITMAP)GetSafeHandle(),
                0L,                // Start scan line
                (DWORD)bi.biHeight,        // # of scan lines
                (LPBYTE)lpbi             // address for bitmap bits
                + (bi.biSize + nColors * sizeof(RGBQUAD)),
                (LPBITMAPINFO)lpbi,        // address of bitmapinfo
                (DWORD)DIB_RGB_COLORS);        // Use RGB for color table

    if( !bGotBits )
    {
        GlobalFree(m_hDIB);
        
        SelectPalette(hDC,hPal,FALSE);
        ReleaseDC(NULL,hDC);
        return NULL;
    }

    SelectPalette(hDC,hPal,FALSE);
    ReleaseDC(NULL,hDC);
    // Sets valid flag
    m_IsValid = (m_hDIB != NULL) ? true : false;
    LoadSize();
    return m_hDIB;
}


HBITMAP ZBitmap::DIBToDDB( HANDLE hDIB )
{
    LPBITMAPINFOHEADER    lpbi;
    HBITMAP         hbm;
    CPalette        pal;
    CPalette*        pOldPal;
    CClientDC        dc(NULL);

    if (hDIB == NULL)
        return NULL;

    lpbi = (LPBITMAPINFOHEADER)hDIB;

    int nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 
                        1 << lpbi->biBitCount;

    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
    LPVOID lpDIBBits;
    if( bmInfo.bmiHeader.biBitCount > 8 )
        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + 
            bmInfo.bmiHeader.biClrUsed) + 
            ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

    // Create and select a logical palette if needed
    if( nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
        LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

        pLP->palVersion = 0x300;
        pLP->palNumEntries = nColors;

        for( int i=0; i < nColors; i++)
        {
            pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
            pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
            pLP->palPalEntry[i].peFlags = 0;
        }

        pal.CreatePalette( pLP );

        delete[] pLP;

        // Select and realize the palette
        pOldPal = dc.SelectPalette( &pal, FALSE );
        dc.RealizePalette();
    }

    
    hbm = CreateDIBitmap(dc.GetSafeHdc(),        // handle to device context
            (LPBITMAPINFOHEADER)lpbi,    // pointer to bitmap info header 
            (LONG)CBM_INIT,            // initialization flag
            lpDIBBits,            // pointer to initialization data 
            (LPBITMAPINFO)lpbi,        // pointer to bitmap info
            DIB_RGB_COLORS );        // color-data usage 

    if (pal.GetSafeHandle())
        dc.SelectPalette(pOldPal,FALSE);

    return hbm;
}



bool    ZBitmap::DIBToDDB()
{
    if (GetDIBHandle() != NULL)
    {
        HBITMAP hBmp = ZBitmap::DIBToDDB( GetDIBHandle() );
        if (hBmp)
        {
            // Set valid flag
            m_IsValid = Attach(hBmp); 
            LoadSize();
            return m_IsValid;
        }
    }
    return false;
}


bool    ZBitmap::LoadSize()
{
    if (!IsValid())
        return false;

    // Get logical coordinates
    BITMAP bm;
    ::GetObject( (HBITMAP)GetSafeHandle(), sizeof( bm ), &bm );
    m_Size.cx = bm.bmWidth;
    m_Size.cy = bm.bmHeight;
    return true;
}
