/****************************************************************************
 * ==> PSS_PLFNMaskString --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan mask string object               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNMaskStringH
#define PSS_PLFNMaskStringH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNMaskString
    #define PSS_PLFNMaskString PLFNMaskString
#endif

// processsoft
#include "ZAString.h"

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
* Financial plan mask string object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNMaskString : public PLFNString
{
    DECLARE_SERIAL(PSS_PLFNMaskString)

    public:
        typedef PSS_PLFNMaskString inherited;

        PSS_PLFNMaskString();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNMaskString(const PSS_PLFNMaskString& other);

        virtual ~PSS_PLFNMaskString();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNMaskString& operator = (const PSS_PLFNMaskString& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNMaskString& operator = (const PSS_PLFNMaskString* pRight);

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
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Gets the formatted object
        *@return the formatted object
        */
        virtual CString GetFormattedObject();

        /**
        * Checks if it's an empty field
        *@return TRUE if it's an empty field, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the string mask
        *@return the string mask
        */
        virtual inline const CString GetMask() const;

        /**
        * Sets the string mask
        *@param value - the string mask
        */
        virtual inline void SetMask(const CString& value);

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
        CString m_Mask;
};

//---------------------------------------------------------------------------
// PSS_PLFNMaskString
//---------------------------------------------------------------------------
UINT PSS_PLFNMaskString::GetRightSubMenu() const
{
    return g_MaskEditRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNMaskString::GetPropertyTabs() const
{
    return (g_PropertyGeneralTextPage | g_PropertySizePage | g_PropertyMaskTextPage);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNMaskString::IsEmpty() const
{
    return m_Mask.IsEmpty();
}
//---------------------------------------------------------------------------
const CString PSS_PLFNMaskString::GetMask() const
{
    return m_Mask;
}
//---------------------------------------------------------------------------
void PSS_PLFNMaskString::SetMask(const CString& value)
{
    m_Mask = value;
}
//---------------------------------------------------------------------------

#endif
