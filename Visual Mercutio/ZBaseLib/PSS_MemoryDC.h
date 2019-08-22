/****************************************************************************
 * ==> PSS_MemoryDC --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a memory device context                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#if !defined(AFX_MEMDC_H__CA1D3541_7235_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_MEMDC_H__CA1D3541_7235_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
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
* Memory device context
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_MemoryDC : public CDC
{
    public:
        /**
        * Constructor
        *@param pDC - source device context
        */
        PSS_MemoryDC(CDC* pDC);

        /**
        * Destructor
        *@note The contents of the memory DC will be copied into the original DC
        */
        virtual ~PSS_MemoryDC();

        /**
        * Pointer operator, allow the usage as a pointer
        *@return itself
        */
        inline PSS_MemoryDC* operator -> ();
        /**
        * Pointer operator, allow the usage as a pointer
        *@return itself
        */
        inline PSS_MemoryDC* operator * ();

    private:
        CDC*     m_pDC;
        CBitmap  m_Bitmap;
        CBitmap* m_pOldBitmap;
        CRect    m_Rect;
        BOOL     m_MemDC;
};

//---------------------------------------------------------------------------
// PSS_MemoryDC
//---------------------------------------------------------------------------
PSS_MemoryDC* PSS_MemoryDC::operator -> ()
{
    return this;
}
//---------------------------------------------------------------------------
PSS_MemoryDC* PSS_MemoryDC::operator * ()
{
    return this;
}
//---------------------------------------------------------------------------

#endif
