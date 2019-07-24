//## begin module%337899310226.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%337899310226.cm

//## begin module%337899310226.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%337899310226.cp

//## Module: ZABitmap%337899310226; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZABitmap.cpp

//## begin module%337899310226.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%337899310226.additionalIncludes

//## begin module%337899310226.includes preserve=yes
//## end module%337899310226.includes

// ZABitmap
#include "ZABitmap.h"

//## begin module%337899310226.declarations preserve=no
//## end module%337899310226.declarations

//## begin module%337899310226.additionalDeclarations preserve=yes
#include "Draw.h"
#include "ZDDoc.h"
#include "ZBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 septembre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(PLFNBitmap, PlanFinObject, g_DefVersion)
//## end module%337899310226.additionalDeclarations

// Class PLFNBitmap

PLFNBitmap::PLFNBitmap()
      //## begin PLFNBitmap::PLFNBitmap%.hasinit preserve=no
    : m_DisplayStyle        ( InitialSize ),
      //## end PLFNBitmap::PLFNBitmap%.hasinit
      //## begin PLFNBitmap::PLFNBitmap%.initialization preserve=yes
      m_pBits                ( NULL ),
      m_hBitmap                ( NULL ),
      m_pBitmapFileHeader    ( NULL ),
      m_pBitmapInfoHeader    ( NULL )
      //## end PLFNBitmap::PLFNBitmap%.initialization
{
    //## begin PLFNBitmap::PLFNBitmap%.body preserve=yes
    //## end PLFNBitmap::PLFNBitmap%.body
}

PLFNBitmap::PLFNBitmap( const PLFNBitmap &right )
      //## begin PLFNBitmap::PLFNBitmap%copy.hasinit preserve=no
    : m_DisplayStyle( InitialSize )
      //## end PLFNBitmap::PLFNBitmap%copy.hasinit
      //## begin PLFNBitmap::PLFNBitmap%copy.initialization preserve=yes
      //## end PLFNBitmap::PLFNBitmap%copy.initialization
{
    //## begin PLFNBitmap::PLFNBitmap%copy.body preserve=yes
    *this = right;
    //## end PLFNBitmap::PLFNBitmap%copy.body
}

PLFNBitmap::~PLFNBitmap()
{
    //## begin PLFNBitmap::~PLFNBitmap%.body preserve=yes
    if ( m_pBits )
    {
        delete m_pBits;
    }

    if ( m_pBitmapInfoHeader )
    {
        delete m_pBitmapInfoHeader;
    }

    if ( m_hBitmap )
    {
        DeleteObject( m_hBitmap );
    }
    //## end PLFNBitmap::~PLFNBitmap%.body
}

const PLFNBitmap & PLFNBitmap::operator=( const PLFNBitmap &right )
{
    //## begin PLFNBitmap::operator=%.body preserve=yes
    this->PlanFinObject::operator=( (inherited&)right );

    m_nBytes            = right.m_nBytes;
    m_nHeaderSize        = right.m_nHeaderSize;
    m_pBitmapInfoHeader    = (PBITMAPINFOHEADER)new char[m_nHeaderSize];
    memcpy( m_pBitmapInfoHeader, right.m_pBitmapInfoHeader, m_nHeaderSize );

    m_pBits                = (BYTE*)new char[m_nBytes];
    memcpy( m_pBits, right.m_pBits, m_nBytes );

    m_hBitmap            = CreateDIBitmap( AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                                          m_pBitmapInfoHeader,
                                          CBM_INIT,
                                          m_pBits,
                                          (PBITMAPINFO)m_pBitmapInfoHeader,
                                          DIB_RGB_COLORS );

    m_Bitmap.Attach( m_hBitmap );
    m_Bitmap.DDBToDIB( BI_RGB, NULL );

    return *this;
    //## end PLFNBitmap::operator=%.body
}

//## Other Operations (implementation)
const PLFNBitmap& PLFNBitmap::operator = ( const PLFNBitmap* right )
{
    //## begin PLFNBitmap::operator =%863541707.body preserve=yes
    this->PlanFinObject::operator=( (inherited*)right );

    m_nBytes            = right->m_nBytes;
    m_nHeaderSize        = right->m_nHeaderSize;
    m_pBitmapInfoHeader    = (PBITMAPINFOHEADER)new char[m_nHeaderSize];
    memcpy( m_pBitmapInfoHeader, right->m_pBitmapInfoHeader, m_nHeaderSize );

    m_pBits = (BYTE*)new char[m_nBytes];
    memcpy( m_pBits, right->m_pBits, m_nBytes );

    m_hBitmap = CreateDIBitmap( AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                                m_pBitmapInfoHeader,
                                CBM_INIT,
                                m_pBits,
                                (PBITMAPINFO) m_pBitmapInfoHeader,
                                DIB_RGB_COLORS );

    m_Bitmap.Attach( m_hBitmap );
    m_Bitmap.DDBToDIB( BI_RGB, NULL );

    return *this;
    //## end PLFNBitmap::operator =%863541707.body
}

PlanFinObject* PLFNBitmap::Clone()
{
    //## begin PLFNBitmap::Clone%863541709.body preserve=yes
    PLFNBitmap* pObject = new PLFNBitmap( *this );
    return pObject;
    //## end PLFNBitmap::Clone%863541709.body
}

void PLFNBitmap::DrawObject( CDC* pDC, ZIView* pView )
{
    //## begin PLFNBitmap::DrawObject%863541710.body preserve=yes
    m_Bitmap.DrawDIB( pDC, NULL, m_rctObject.left, m_rctObject.top );
    PlanFinObject::DrawObject( pDC, pView );
    //## end PLFNBitmap::DrawObject%863541710.body
}

void PLFNBitmap::CopyObject( PlanFinObject* pSrc )
{
    //## begin PLFNBitmap::CopyObject%863615076.body preserve=yes
    ( (PLFNBitmap*)this )->PLFNBitmap::operator=( (PLFNBitmap*)pSrc );
    //## end PLFNBitmap::CopyObject%863615076.body
}

CString PLFNBitmap::OpenBitmapFileDialog()
{
    //## begin PLFNBitmap::OpenBitmapFileDialog%866485624.body preserve=yes
    OPENFILENAME of;
    char szBuffer [_MAX_PATH];

    CString Title;
    Title.LoadString( IDS_SELECTBITMAP_TITLE );
    szBuffer[0] = 0;

    // Set up the OPENFILE structure,
    // then use the appropriate common dialog
    of.lStructSize            = sizeof (OPENFILENAME);
    of.hwndOwner            = NULL;
    of.hInstance            = AfxGetInstanceHandle();
    of.lpstrFilter            = _T( "Bitmaps\000 *.BMP\000\000" );
    of.lpstrCustomFilter    = NULL;
    of.nMaxCustFilter        = 0;
    of.nFilterIndex            = 0;
    of.lpstrFile            = szBuffer;
    of.nMaxFile                = _MAX_PATH;
    of.lpstrFileTitle        = NULL;
    of.nMaxFileTitle        = 0;
    of.lpstrInitialDir        = _T( "" );
    of.lpstrTitle            = (const char*)Title;
    of.Flags                = OFN_HIDEREADONLY;
    of.nFileOffset            = 0;
    of.nFileExtension        = 0;
    of.lpstrDefExt            = NULL;
    of.lCustData            = 0;
    of.lpfnHook                = NULL;
    of.lpTemplateName        = NULL;

    if ( !GetOpenFileName ( &of ) )
    {
        return _T( "" );
    }

    return szBuffer;
    //## end PLFNBitmap::OpenBitmapFileDialog%866485624.body
}

BOOL PLFNBitmap::GetBitmapFile( CString sFilename, CDC* pDC )
{
    //## begin PLFNBitmap::GetBitmapFile%866485625.body preserve=yes
    int fh;
    int bfOffBits;
    int nbytes;

    // Try to open the file. If successful, then allocate space for it,
    // and read in all of the bytes.
    fh = _lopen( sFilename, OF_READ );

    if ( fh == -1 )
    {
        return FALSE;
    }

    CFileStatus Status;

    if ( CFile::GetStatus( sFilename, Status ) == FALSE )
    {
        _lclose( fh );

        return FALSE;
    }

    nbytes = (int)Status.m_size;

    // The contents of the file are read in here in three parts. First
    // the bitmap file header is read, then the bitmap header along with
    //  the color table, then finally the actual bit data.  I.e. from
    //  a total of nbytes...
    //    1.  sizeof (BITMAPFILEHEADER)
    //    2.  bfOffBits- sizeof (BITMAPFILEHEADER)
    //    3.  (nbytes - bfOffBits)

    // Read in the bitmap file header. Save the offset to bits.
    m_pBitmapFileHeader = (PBITMAPFILEHEADER)new char[sizeof (BITMAPFILEHEADER)];
    _lread( fh, (LPSTR)m_pBitmapFileHeader, sizeof (BITMAPFILEHEADER) );
    bfOffBits = m_pBitmapFileHeader->bfOffBits;

    // Read in the bitmap info header and the color table right after it.
    // Both BITMAPINFOHEADER and BITMAPINFO needed for CreateDIBitmap()
    m_nHeaderSize = bfOffBits - sizeof (BITMAPFILEHEADER);
    m_pBitmapInfoHeader = (PBITMAPINFOHEADER)new char[m_nHeaderSize];
    _lread( fh, (LPSTR)m_pBitmapInfoHeader, m_nHeaderSize );

    // Assign the new size to the object
    // Bitmap size becomes object size
    m_rctObject.right = m_rctObject.left + m_pBitmapInfoHeader->biWidth;
    m_rctObject.bottom = m_rctObject.top + m_pBitmapInfoHeader->biHeight;

    // Finally read in the bit data.
    m_nBytes = nbytes - bfOffBits;
    m_pBits = (BYTE*)new char[m_nBytes];
    _lread( fh, (LPSTR)m_pBits, m_nBytes );
    _lclose( fh);

    m_hBitmap = CreateDIBitmap( pDC->GetSafeHdc(),
                                m_pBitmapInfoHeader,
                                CBM_INIT,
                                m_pBits,
                                (PBITMAPINFO) m_pBitmapInfoHeader,
                                DIB_RGB_COLORS );

    m_Bitmap.Attach( m_hBitmap );
    m_Bitmap.DDBToDIB( BI_RGB, NULL );

    // Free up memory
    if ( m_pBitmapFileHeader )
    {
        delete m_pBitmapFileHeader;
    }

    m_pBitmapFileHeader = NULL;

    return TRUE;
    //## end PLFNBitmap::GetBitmapFile%866485625.body
}

BOOL PLFNBitmap::SelectBitmapFile( CDC* pDC )
{
    //## begin PLFNBitmap::SelectBitmapFile%866485623.body preserve=yes
    CString sFile = OpenBitmapFileDialog();

    if ( sFile.IsEmpty() )
    {
        return FALSE;
    }

    return GetBitmapFile( sFile, pDC );
    //## end PLFNBitmap::SelectBitmapFile%866485623.body
}

BOOL PLFNBitmap::AssignBitmapFile( CString& File, CDC* pDC )
{
    //## begin PLFNBitmap::AssignBitmapFile%901981234.body preserve=yes
    if ( File.IsEmpty() )
    {
        return FALSE;
    }

    return GetBitmapFile( File, pDC );
    //## end PLFNBitmap::AssignBitmapFile%901981234.body
}

// Additional Declarations

//## begin PLFNBitmap%337898F5019A.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// PLFNBitmap diagnostics

#ifdef _DEBUG
void PLFNBitmap::AssertValid() const
{
    CObject::AssertValid();
}

void PLFNBitmap::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

void PLFNBitmap::Serialize( CArchive& ar )
{
    //## begin PLFNBitmap::Serialize%863541708.body preserve=yes
    PlanFinObject::Serialize(ar);

    if (ar.IsStoring())
    {
        // Write the elements
        // Serialize the BITMAP
        ar << DWORD(m_nHeaderSize);

        for (int i = 0; i < m_nHeaderSize; ++i)
            ar << ((BYTE*)m_pBitmapInfoHeader)[i];

        ar << DWORD(m_nBytes);

        for (int i = 0; i < m_nBytes; ++i)
            ar << ((BYTE*)m_pBits)[i];

        ar << WORD(m_DisplayStyle);
    }
    else
    {
        // Read the elements
        DWORD dwTemp;
        ar >> dwTemp;

        // Read the header
        m_nHeaderSize = (size_t)dwTemp;

        if ( m_pBitmapInfoHeader )
        {
            delete m_pBitmapInfoHeader;
        }

        m_pBitmapInfoHeader = (PBITMAPINFOHEADER)new char[m_nHeaderSize];

        BYTE bByte;

        for (int i = 0; i < m_nHeaderSize; ++i)
        {
            ar >> bByte;
            ((BYTE*)m_pBitmapInfoHeader)[i] = bByte;
        }

        // read the bits
        ar >> dwTemp;

        m_nBytes = (size_t)dwTemp;

        if (m_pBits)
            delete m_pBits;

        m_pBits = (BYTE*)new char[m_nBytes];

        for (int i = 0; i < m_nBytes; ++i)
        {
            ar >> bByte;
            ((BYTE*)m_pBits)[i] = bByte;
        }

        m_hBitmap = ::CreateDIBitmap(AfxGetMainWnd()->GetDC()->GetSafeHdc(),
                                     m_pBitmapInfoHeader,
                                     CBM_INIT,
                                     m_pBits,
                                     (PBITMAPINFO)m_pBitmapInfoHeader,
                                     DIB_RGB_COLORS);

        m_Bitmap.Attach( m_hBitmap );
        m_Bitmap.DDBToDIB( BI_RGB, NULL );

        if (((ZDDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 5)
        {
            WORD wTemp;
            ar >> wTemp;
            m_DisplayStyle = DisplayStyles(wTemp);
        }
    }

    //## end PLFNBitmap::Serialize%863541708.body
}
//## end PLFNBitmap%337898F5019A.declarations

//## begin module%337899310226.epilog preserve=yes
//## end module%337899310226.epilog
