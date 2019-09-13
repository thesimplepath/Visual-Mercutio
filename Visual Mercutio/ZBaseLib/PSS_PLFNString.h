/****************************************************************************
 * ==> PSS_PLFNString ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan string object                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNStringH
#define PSS_PLFNStringH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNString
    #define PSS_PLFNString PLFNString
#endif

// processsoft
#include "PSS_PLFNText.h"

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
* Financial plan string object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNString : public PSS_PLFNText
{
    DECLARE_SERIAL(PSS_PLFNString)

    public:
        typedef PSS_PLFNText inherited;

        PSS_PLFNString();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNString(const PSS_PLFNString& other);

        virtual ~PSS_PLFNString();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNString& operator = (const PSS_PLFNString& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNString& operator = (const PSS_PLFNString* pOther);

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
        * Gets the string value
        *@return the string value
        */
        virtual inline CString GetStringValue();

        /**
        * Sets the string value
        *@param value - the string value
        */
        virtual inline void SetStringValue(const CString& str);

        /**
        * Gets the object member address
        *@return the object member address
        */
        virtual inline void* GetObjectAdress() const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

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
};

//---------------------------------------------------------------------------
// PSS_PLFNString
//---------------------------------------------------------------------------
CString PSS_PLFNString::GetStringValue()
{
    return(m_Str);
}
//---------------------------------------------------------------------------
void PSS_PLFNString::SetStringValue(const CString& str)
{
    m_Str = str;
    ClearEmptyObjectFlag();
}
//---------------------------------------------------------------------------
void* PSS_PLFNString::GetObjectAdress() const
{
    return ((void*)&m_Str);
}
//---------------------------------------------------------------------------

#endif
