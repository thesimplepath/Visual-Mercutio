/****************************************************************************
 * ==> PSS_PLFNText --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan text object                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNTextH
#define PSS_PLFNTextH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNText
    #define PSS_PLFNText PLFNText
#endif

// processsoft
#include "PSS_PLFNAscii.h"

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
* Financial plan text object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNText : public PSS_PLFNAscii
{
    DECLARE_SERIAL(PSS_PLFNText)

    public:
        typedef PSS_PLFNAscii inherited;

        PSS_PLFNText();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNText(const PSS_PLFNText& other);

        virtual ~PSS_PLFNText();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNText& operator = (const PSS_PLFNText& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNText& operator = (const PSS_PLFNText* pOther);

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
        * Gets a formatted string containing the object attributes
        *@return the formatted string, empty string if object is empty or on error
        */
        virtual CString GetFormattedObject();

        /**
        * Gets the unformatted string of the object image
        *@return the unformatted string of the object image
        */
        virtual CString GetUnformattedObject();

        /**
        * Converts a formatted object to numeric, date, string, etc.
        *@param value - value
        *@param locateFormat - if TRUE, format will use the locale
        *@param emptyWhenZero - if TRUE, the field will be emptied if the value is empty
        *@return TRUE if the value has changed, otherwise FALSE
        */
        virtual BOOL ConvertFormattedObject(const CString& value, BOOL locateFormat = TRUE, BOOL emptyWhenZero = FALSE);

        /**
        * Checks if the object is selected
        *@param point - hit point in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Gets the contains from a line
        *@param line - the line containing the object definition
        */
        virtual void GetContains(const CString& line);

        /**
        * Gets the text string
        *@return the text string
        */
        virtual inline const CString& GetStr() const;

        /**
        * Sets the text string
        *@param value - the text string
        */
        virtual inline void SetStr(const CString& value);

        /**
        * Gets if the field is static
        *@return TRUE if the field is static, otherwise FALSE
        */
        virtual inline const BOOL GetIsStatic() const;

        /**
        * Sets if the field is static
        *@param value - if TRUE, the field is static
        */
        virtual inline void SetIsStatic(BOOL value);

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

    protected:
        CString m_Str;

    private:
        BOOL m_IsStatic;
};

//---------------------------------------------------------------------------
// PSS_PLFNText
//---------------------------------------------------------------------------
BOOL PSS_PLFNText::IsSelected(const CPoint& point) const
{
    return(m_ObjectRect.PtInRect(point));
}
//---------------------------------------------------------------------------
const CString& PSS_PLFNText::GetStr() const
{
    return m_Str;
}
//---------------------------------------------------------------------------
void PSS_PLFNText::SetStr(const CString& value)
{
    m_Str = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNText::GetIsStatic() const
{
    return m_IsStatic;
}
//---------------------------------------------------------------------------
void PSS_PLFNText::SetIsStatic(BOOL value)
{
    m_IsStatic = value;
}
//---------------------------------------------------------------------------

#endif
