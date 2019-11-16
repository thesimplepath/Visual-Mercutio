/****************************************************************************
 * ==> PSS_PLFNBitmap ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan bitmap object                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_PLFNBitmap.h"

 // processsoft
#include "PSS_DrawFunctions.h"
#include "PSS_Bitmap.h"
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PLFNBitmap, PSS_PlanFinObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PLFNBitmap
//---------------------------------------------------------------------------
PSS_PLFNBitmap::PSS_PLFNBitmap() :
    PSS_PlanFinObject(),
    m_hBitmap(NULL),
    m_pBitmapInfoHeader(NULL),
    m_pBits(NULL),
    m_DisplayStyle(IE_DS_InitialSize),
    m_HeaderSize(0),
    m_Bytes(0)
{}
//---------------------------------------------------------------------------
PSS_PLFNBitmap::PSS_PLFNBitmap(const PSS_PLFNBitmap& other) :
    PSS_PlanFinObject(),
    m_DisplayStyle(IE_DS_InitialSize)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PLFNBitmap::~PSS_PLFNBitmap()
{
    if (m_pBits)
        delete m_pBits;

    if (m_pBitmapInfoHeader)
        delete m_pBitmapInfoHeader;

    if (m_hBitmap)
        DeleteObject(m_hBitmap);
}
//---------------------------------------------------------------------------
const PSS_PLFNBitmap& PSS_PLFNBitmap::operator = (const PSS_PLFNBitmap& other)
{
    PSS_PlanFinObject::operator = ((inherited&)other);

    if (m_pBits)
        delete m_pBits;

    if (m_pBitmapInfoHeader)
        delete m_pBitmapInfoHeader;

    if (m_hBitmap)
        DeleteObject(m_hBitmap);

    m_HeaderSize = other.m_HeaderSize;
    m_Bytes      = other.m_Bytes;

    m_pBitmapInfoHeader = PBITMAPINFOHEADER(new char[m_HeaderSize]);
    std::memcpy(m_pBitmapInfoHeader, other.m_pBitmapInfoHeader, m_HeaderSize);

    m_pBits = (BYTE*)new char[m_Bytes];
    std::memcpy(m_pBits, other.m_pBits, m_Bytes);

    m_hBitmap = CreateDIBitmap(AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                               m_pBitmapInfoHeader,
                               CBM_INIT,
                               m_pBits,
                               PBITMAPINFO(m_pBitmapInfoHeader),
                               DIB_RGB_COLORS);

    m_Bitmap.Attach(m_hBitmap);
    m_Bitmap.DDBToDIB(BI_RGB, NULL);

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PLFNBitmap& PSS_PLFNBitmap::operator = (const PSS_PLFNBitmap* pOther)
{
    PSS_PlanFinObject::operator = ((inherited*)pOther);

    if (m_pBits)
        delete m_pBits;

    if (m_pBitmapInfoHeader)
        delete m_pBitmapInfoHeader;

    if (m_hBitmap)
        DeleteObject(m_hBitmap);

    if (!pOther)
    {
        m_hBitmap           = NULL;
        m_pBitmapInfoHeader = NULL;
        m_pBits             = NULL;
        m_DisplayStyle      = IE_DS_InitialSize;
        m_HeaderSize        = 0;
        m_Bytes             = 0;
    }
    else
    {
        m_HeaderSize = pOther->m_HeaderSize;
        m_Bytes      = pOther->m_Bytes;

        m_pBitmapInfoHeader = PBITMAPINFOHEADER(new char[m_HeaderSize]);
        std::memcpy(m_pBitmapInfoHeader, pOther->m_pBitmapInfoHeader, m_HeaderSize);

        m_pBits = (BYTE*)new char[m_Bytes];
        std::memcpy(m_pBits, pOther->m_pBits, m_Bytes);

        m_hBitmap = CreateDIBitmap(AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                                   m_pBitmapInfoHeader,
                                   CBM_INIT,
                                   m_pBits,
                                   (PBITMAPINFO)m_pBitmapInfoHeader,
                                   DIB_RGB_COLORS);

        m_Bitmap.Attach(m_hBitmap);
        m_Bitmap.DDBToDIB(BI_RGB, NULL);
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_PLFNBitmap::Clone() const
{
    return new PSS_PLFNBitmap(*this);
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::CopyObject(PSS_PlanFinObject* pSrc)
{
    operator = (dynamic_cast<PSS_PLFNBitmap*>(pSrc));
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::DrawObject(CDC* pDC, PSS_View* pView)
{
    m_Bitmap.DrawDIB(pDC, NULL, m_ObjectRect.left, m_ObjectRect.top);
    PSS_PlanFinObject::DrawObject(pDC, pView);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNBitmap::SelectBitmapFile(CDC* pDC)
{
    const CString fileName = OpenBitmapFileDialog();

    if (fileName.IsEmpty())
        return FALSE;

    return GetBitmapFile(fileName, pDC);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNBitmap::AssignBitmapFile(const CString& fileName, CDC* pDC)
{
    if (fileName.IsEmpty())
        return FALSE;

    return GetBitmapFile(fileName, pDC);
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::Serialize(CArchive& ar)
{
    PSS_PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements, serialize the bitmap
        ar << DWORD(m_HeaderSize);

        for (int i = 0; i < m_HeaderSize; ++i)
            ar << ((BYTE*)m_pBitmapInfoHeader)[i];

        ar << DWORD(m_Bytes);

        for (int i = 0; i < m_Bytes; ++i)
            ar << ((BYTE*)m_pBits)[i];

        ar << WORD(m_DisplayStyle);
    }
    else
    {
        // read the elements
        DWORD dwValue;
        ar >> dwValue;

        // read the header
        m_HeaderSize = std::size_t(dwValue);

        if (m_pBitmapInfoHeader)
            delete m_pBitmapInfoHeader;

        m_pBitmapInfoHeader = PBITMAPINFOHEADER(new char[m_HeaderSize]);

        BYTE byte;

        for (int i = 0; i < m_HeaderSize; ++i)
        {
            ar >> byte;
            ((BYTE*)m_pBitmapInfoHeader)[i] = byte;
        }

        // read the bits
        ar >> dwValue;

        m_Bytes = std::size_t(dwValue);

        if (m_pBits)
            delete m_pBits;

        m_pBits = (BYTE*)new char[m_Bytes];

        for (int i = 0; i < m_Bytes; ++i)
        {
            ar >> byte;
            ((BYTE*)m_pBits)[i] = byte;
        }

        m_hBitmap = ::CreateDIBitmap(AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                                     m_pBitmapInfoHeader,
                                     CBM_INIT,
                                     m_pBits,
                                     (PBITMAPINFO)m_pBitmapInfoHeader,
                                     DIB_RGB_COLORS);

        m_Bitmap.Attach(m_hBitmap);
        m_Bitmap.DDBToDIB(BI_RGB, NULL);

        if (((PSS_Document*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            WORD wValue;
            ar >> wValue;
            m_DisplayStyle = IEDisplayStyles(wValue);
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNBitmap::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_PLFNBitmap::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
CString PSS_PLFNBitmap::OpenBitmapFileDialog()
{
    OPENFILENAME ofn;
    char         buffer[_MAX_PATH];

    CString title;
    title.LoadString(IDS_SELECTBITMAP_TITLE);
    buffer[0] = 0;

    // set up the open file name structure, then use the appropriate common dialog
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = NULL;
    ofn.hInstance         = AfxGetInstanceHandle();
    ofn.lpstrFilter       = _T("Bitmaps\000 *.BMP\000\000");
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0;
    ofn.nFilterIndex      = 0;
    ofn.lpstrFile         = buffer;
    ofn.nMaxFile          = _MAX_PATH;
    ofn.lpstrFileTitle    = NULL;
    ofn.nMaxFileTitle     = 0;
    ofn.lpstrInitialDir   = _T("");
    ofn.lpstrTitle        = (const char*)title;
    ofn.Flags             = OFN_HIDEREADONLY;
    ofn.nFileOffset       = 0;
    ofn.nFileExtension    = 0;
    ofn.lpstrDefExt       = NULL;
    ofn.lCustData         = 0;
    ofn.lpfnHook          = NULL;
    ofn.lpTemplateName    = NULL;

    if (!::GetOpenFileName(&ofn))
        return _T("");

    return buffer;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNBitmap::GetBitmapFile(const CString& fileName, CDC* pDC)
{
    // open the file. If successful, allocate space for it, and read the content
    int fileHandle = ::_lopen(fileName, OF_READ);

    if (fileHandle == -1)
        return FALSE;

    BITMAPFILEHEADER* pBitmapFileHeader = NULL;

    try
    {
        CFileStatus status;

        if (!CFile::GetStatus(fileName, status))
        {
            ::_lclose(fileHandle);

            return FALSE;
        }

        const int bytes = int(status.m_size);

        // The file content is read in three parts. First the bitmap file header is read, then the bitmap header,
        // along with the color table, then finally the actual bit data. I.e. from a total of nbytes...
        // 1. sizeof (BITMAPFILEHEADER)
        // 2. bfOffBits- sizeof (BITMAPFILEHEADER)
        // 3. (nbytes - bfOffBits)

        // read the bitmap file header, save the offset to bits
        pBitmapFileHeader = PBITMAPFILEHEADER(new char[sizeof(BITMAPFILEHEADER)]);
        ::_lread(fileHandle, LPSTR(pBitmapFileHeader), sizeof(BITMAPFILEHEADER));

        const int offset = pBitmapFileHeader->bfOffBits;

        // read the bitmap info header and the color table right after it. Both BITMAPINFOHEADER and BITMAPINFO needed
        // for CreateDIBitmap()
        m_HeaderSize = offset - sizeof(BITMAPFILEHEADER);
        m_pBitmapInfoHeader = PBITMAPINFOHEADER(new char[m_HeaderSize]);
        ::_lread(fileHandle, LPSTR(m_pBitmapInfoHeader), m_HeaderSize);

        // assign the new object size. Bitmap size becomes object size
        m_ObjectRect.right  = m_ObjectRect.left + m_pBitmapInfoHeader->biWidth;
        m_ObjectRect.bottom = m_ObjectRect.top  + m_pBitmapInfoHeader->biHeight;

        // read the data
        m_Bytes = bytes - offset;
        m_pBits = (BYTE*)new char[m_Bytes];
        ::_lread(fileHandle, (LPSTR)m_pBits, m_Bytes);

        // close the file
        ::_lclose(fileHandle);
        fileHandle = 0;

        m_hBitmap = CreateDIBitmap(pDC->GetSafeHdc(),
                                   m_pBitmapInfoHeader,
                                   CBM_INIT,
                                   m_pBits,
                                   PBITMAPINFO(m_pBitmapInfoHeader),
                                   DIB_RGB_COLORS);

        m_Bitmap.Attach(m_hBitmap);
        m_Bitmap.DDBToDIB(BI_RGB, NULL);
    }
    catch (...)
    {
        // free the memory
        if (pBitmapFileHeader)
            delete pBitmapFileHeader;

        // close the file
        if (fileHandle)
            ::_lclose(fileHandle);

        throw;
    }

    // free the memory
    if (pBitmapFileHeader)
        delete pBitmapFileHeader;

    return TRUE;
}
//---------------------------------------------------------------------------
