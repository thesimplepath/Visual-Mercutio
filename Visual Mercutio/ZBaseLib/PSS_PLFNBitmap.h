/****************************************************************************
 * ==> PSS_PLFNBitmap ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan bitmap object                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNBitmapH
#define PSS_PLFNBitmapH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNBitmap
    #define PSS_PLFNBitmap PLFNBitmap
#endif

// processsoft
#include "PSS_Bitmap.h"
#include "PSS_PlanFinObject.h"

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
* Financial plan bitmap object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNBitmap : public PSS_PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNBitmap)

    public:
        /**
        * Strike styles
        */
        enum IEDisplayStyles
        {
            IE_DS_InitialSize,
            IE_DS_FitToRect,
            IE_DS_FitToRectProp
        };

        typedef PSS_PlanFinObject inherited;

        PSS_PLFNBitmap();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNBitmap(const PSS_PLFNBitmap& other);

        virtual ~PSS_PLFNBitmap();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNBitmap& operator = (const PSS_PLFNBitmap& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNBitmap& operator = (const PSS_PLFNBitmap* right);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PSS_PlanFinObject* pSrc);

        /**
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

        /**
        * Selects the bitmap file from the disk
        *@param pDC - device context to draw to
        *@return TRUE on sucess, otherwise FALSE
        */
        BOOL SelectBitmapFile(CDC* pDC);

        /**
        * Sets the bitmap file and load the image contained in the file
        *@param fileName - file name
        *@param pDC - device context to draw to
        *@return TRUE on sucess, otherwise FALSE
        */
        BOOL AssignBitmapFile(const CString& fileName, CDC* pDC);

        /**
        * Shows and processes the bitmap file dialog
        *@return the selected file name
        */
        virtual inline CString SelectBitmapFileDialog();

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the bitmap display style
        *@return the bitmap display style
        */
        virtual inline const IEDisplayStyles GetDisplayStyle() const;

        /**
        * Sets the bitmap display style
        *@param value - the bitmap display style
        */
        virtual inline void SetDisplayStyle(IEDisplayStyles value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        PSS_Bitmap        m_Bitmap;
        HBITMAP           m_hBitmap;
        BITMAPINFOHEADER* m_pBitmapInfoHeader;
        BYTE*             m_pBits;
        IEDisplayStyles   m_DisplayStyle;
        std::size_t       m_HeaderSize;
        unsigned long     m_Bytes;

        /**
        * Opens the bitmap file dialog box
        *@return the selected file name
        */
        CString OpenBitmapFileDialog();

        /**
        * Gets the bitmap file content
        *@param fileName - file name
        *@param pDC - device context to draw to
        *@return TRUE on sucess, otherwise FALSE
        */
        BOOL GetBitmapFile(const CString& fileName, CDC* pDC);

        /**
        * Gets the bitmap handle
        *@return the bitmap handle, NULL on error
        */
        inline const HBITMAP GetBitmapHandle() const;

        /**
        * Sets the bitmap handle
        *@Param value - the bitmap handle
        */
        inline void SetBitmapHandle(HBITMAP value);

        /**
        * Gets bitmap length in bytes
        *@return the bitmap length in bytes
        */
        inline const unsigned long GetBytes() const;

        /**
        * Sets bitmap length in bytes
        *@param value - the bitmap length in bytes
        */
        inline void SetBytes(unsigned long value);

        /**
        * Gets the bitmap header length in bytes
        *@return the bitmap header length in bytes
        */
        inline const std::size_t GetHeaderSize() const;

        /**
        * Sets the bitmap header length in bytes
        *@param value - the bitmap header length in bytes
        */
        inline void SetHeaderSize(std::size_t value);
};

//---------------------------------------------------------------------------
// PSS_PLFNBitmap
//---------------------------------------------------------------------------
UINT PSS_PLFNBitmap::GetRightSubMenu() const
{
    return g_BitmapRightSubMenu;
}
//---------------------------------------------------------------------------
CString PSS_PLFNBitmap::SelectBitmapFileDialog()
{
    return OpenBitmapFileDialog();
}
//---------------------------------------------------------------------------
UINT PSS_PLFNBitmap::GetPropertyTabs() const
{
    return (g_PropertyGeneralBasicPage | g_PropertySizePage);
}
//---------------------------------------------------------------------------
const PSS_PLFNBitmap::IEDisplayStyles PSS_PLFNBitmap::GetDisplayStyle() const
{
    return m_DisplayStyle;
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::SetDisplayStyle(IEDisplayStyles value)
{
    m_DisplayStyle = value;
}
//---------------------------------------------------------------------------
const HBITMAP PSS_PLFNBitmap::GetBitmapHandle() const
{
    return m_hBitmap;
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::SetBitmapHandle(HBITMAP value)
{
    m_hBitmap = value;
}
//---------------------------------------------------------------------------
const unsigned long PSS_PLFNBitmap::GetBytes() const
{
    return m_Bytes;
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::SetBytes(unsigned long value)
{
    m_Bytes = value;
}
//---------------------------------------------------------------------------
const std::size_t PSS_PLFNBitmap::GetHeaderSize() const
{
    return m_HeaderSize;
}
//---------------------------------------------------------------------------
void PSS_PLFNBitmap::SetHeaderSize(std::size_t value)
{
    m_HeaderSize = value;
}
//---------------------------------------------------------------------------

#endif
