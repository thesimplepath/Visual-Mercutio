/****************************************************************************
 * ==> PSS_String16 --------------------------------------------------------*
 ****************************************************************************
 * Description : Shim class that converts both 8-bit (foreign) and 16-bit   *
 *               (native) strings to 16-bit wideness                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_String16H
#define PSS_String16H

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <string>

#ifdef _ZCONVERSIONEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Shim class that converts both 8-bit (foreign) and 16-bit (native) strings to 16-bit wideness
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_String16
{
    public:
        /**
        * Constructor
        *@param p8 - 8 bit string
        */
        inline PSS_String16(const char* p8);

        /**
        * Constructor
        *@param p16 - 16 bit string
        */
        inline PSS_String16(const wchar_t* p16);

        /**
        * Constructor
        *@param ref - reference string to copy from
        */
        inline PSS_String16(const PSS_String16& ref);

        /**
        * Destructor
        *@note Non-virtual destructor (this class is concrete)
        */
        inline ~PSS_String16();

        /**
        * Pointer operator
        *@return pointer to string
        */
        inline operator const wchar_t * () const;

        /**
        * Sets char at position
        *@param i - char index to set
        *@param c - char to set
        */
        inline void SetAt(std::size_t i, char c)
        {
            ASSERT(i < Length());
            m_pSz[i] = c;
        }

        /**
        * Gets string length
        *@return string length
        */
        inline std::size_t Length() const
        {
            return wcslen(m_pSz);
        }

    private:
        wchar_t* m_pSz;
        BOOL     m_IsForeign;
};

//---------------------------------------------------------------------------
// PSS_String16
//---------------------------------------------------------------------------
PSS_String16::PSS_String16(const char* p8) :
    m_pSz(NULL),
    m_IsForeign(TRUE)
{
    // calculate the string length
    std::size_t len = strlen(p8);
    std::size_t size;

    // calculate required buffer size (some characters may already occupy 16-bits under DBCS)
    mbstowcs_s(&size, 0, 0, p8, len);
    ++size;

    // alloc native string and convert
    if (m_pSz = new wchar_t[size])
        mbstowcs_s(0, m_pSz, size, p8, size - 1);
}
//---------------------------------------------------------------------------
PSS_String16::PSS_String16(const wchar_t* p16) :
    m_pSz((wchar_t *)p16),
    m_IsForeign(FALSE)
{}
//---------------------------------------------------------------------------
PSS_String16::PSS_String16(const PSS_String16& ref) :
    m_pSz((wchar_t *)ref.m_pSz),
    m_IsForeign(FALSE)
{}
//---------------------------------------------------------------------------
PSS_String16::~PSS_String16()
{
    if (m_IsForeign && m_pSz)
        delete[] m_pSz;
}
//---------------------------------------------------------------------------
PSS_String16::operator const wchar_t * () const
{
    return m_pSz;
}
//---------------------------------------------------------------------------

#endif