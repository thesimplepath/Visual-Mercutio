/****************************************************************************
 * ==> PSS_PLFNBackImage ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan background image                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNBackImageH
#define PSS_PLFNBackImageH

#if _MSC_VER > 1000
    #pragma once
#endif

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

 // old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNBackImage
    #define PSS_PLFNBackImage PLFNBackImage
#endif

// processsoft
#include "PSS_PLFNBitmap.h"

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
* Financial plan background image
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNBackImage : public PSS_PLFNBitmap
{
    DECLARE_SERIAL(PSS_PLFNBackImage)

    public:
        typedef PSS_PLFNBitmap inherited;

        PSS_PLFNBackImage();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNBackImage(const PSS_PLFNBackImage& other);

        virtual ~PSS_PLFNBackImage();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNBackImage& operator = (const PSS_PLFNBackImage& other);
        const PSS_PLFNBackImage& operator = (const PSS_PLFNBackImage* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Gets the right sub-menu identifier
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Copies the object
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject (PlanFinObject* pSrc);

        /**
        * Checks if a hint should be shown
        *@param point - hint point
        *@return TRUE if a hint should be shown, otherwise FALSE
        */
        virtual inline BOOL IsHint(CPoint& point) const;
};

//---------------------------------------------------------------------------
// PSS_PLFNBackImage
//---------------------------------------------------------------------------
UINT PSS_PLFNBackImage::GetRightSubMenu() const
{
    return g_ObjectRightSubMenu;
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNBackImage::IsHint(CPoint& point) const
{
    // can't be selected
    return FALSE;
}
//---------------------------------------------------------------------------

#endif
