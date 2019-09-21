/****************************************************************************
 * ==> PSS_Bitmap ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a bitmap graphic                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BitmapH
#define PSS_BitmapH

#if _MSC_VER > 1000
    #pragma once
#endif

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
* Bitmap graphic
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Bitmap : public CBitmap
{
    public:
        PSS_Bitmap();
        virtual ~PSS_Bitmap();

        /**
        * Checks if the bitmap is valid
        *@return true if the bitmap is valid, otherwise false
        */
        virtual inline bool IsValid() const;

        /**
        * Gets the device independent bitmap handle
        *@return the device independent bitmap handle
        */
        virtual inline HANDLE GetDIBHandle() const;

        /**
        * Gets the bitmap size
        *@return the bitmap size
        */
        virtual inline CSize GetSize() const;

        /**
        * Loads a bitmap from resources
        *@param resID - bitmap resource identifier
        *@return true on success, otherwise false
        */
        virtual bool LoadBitmap(UINT resID);

        /**
        * Loads a bitmap from file
        *@param fileName - bitmap file name
        *@return true on success, otherwise false
        */
        virtual bool LoadBitmapFromFile(LPCTSTR fileName);

        /**
        * Loads a device independent bitmap from file
        *@param pFileName - bitmap file name
        *@param pPixels - on success, will contain the bitmap pixels on fucntion ends, ignored if NULL
        *@param hSection - section handle
        *@param offset - offset
        *@return true on success, otherwise false
        */
        virtual bool LoadDIBSectionFromFile(LPCTSTR pFileName, LPVOID* pPixels = NULL, HANDLE hSection = NULL, DWORD offset = 0);

        /**
        * Converts a bitmap to device independent bitmap
        *@param compression - compression level
        *@param pPal - palette
        *@return device independent bitmap handle, NULL on error
        */
        virtual HANDLE DDBToDIB(DWORD compression, CPalette* pPal);

        /**
        * Converts a device independent bitmap to bitmap
        *@param hDIB - device independent bitmap handle
        *@return bitmap handle, NULL on error
        */
        virtual HBITMAP DIBToDDB(HANDLE hDIB);

        /**
        * Converts the device independent bitmap to bitmap
        *@return true on success, otherwise false
        */
        virtual bool DIBToDDB();

        /**
        * Draws the bitmap to a device context
        *@param pDC - device context to draw to
        *@param hPal - palette handle, NULL if not used
        *@param x - x position to draw on destination, in pixels
        *@param y - y position to draw on destination, in pixels
        */
        virtual void DrawBitmap(CDC* pDC, HPALETTE hPal = NULL, int x = 0, int y = 0);

        /**
        * Draws a device independent bitmap to a device context
        *@param pDC - device context to draw to
        *@param hDIB - device independent bitmap handle to draw
        *@param hPal - palette handle, NULL if not used
        *@param x - x position to draw on destination, in pixels
        *@param y - y position to draw on destination, in pixels
        */
        virtual void DrawDIB(CDC* pDC, HGLOBAL hDIB, CPalette* pPal = NULL, int x = 0, int y = 0);

        /**
        * Draws the device independent bitmap to a device context
        *@param pDC - device context to draw to
        *@param hDIB - device independent bitmap handle to draw
        *@param hPal - palette handle, NULL if not used
        *@param x - x position to draw on destination, in pixels
        *@param y - y position to draw on destination, in pixels
        */
        virtual void DrawDIB(CDC* pDC, CPalette* pPal = NULL, int x = 0, int y = 0);

    private:
        HANDLE m_hDIB;
        CSize  m_Size;
        bool   m_IsValid;

        /**
        * Loads the size
        *@return true on success, otherwise false
        */
        bool LoadSize();
};

//---------------------------------------------------------------------------
// PSS_Bitmap
//---------------------------------------------------------------------------
bool PSS_Bitmap::IsValid() const
{
    return m_IsValid;
}
//---------------------------------------------------------------------------
HANDLE PSS_Bitmap::GetDIBHandle() const
{
    return m_hDIB;
}
//---------------------------------------------------------------------------
CSize PSS_Bitmap::GetSize() const
{
    return (IsValid() ? m_Size : CSize(0, 0));
}
//---------------------------------------------------------------------------

#endif
