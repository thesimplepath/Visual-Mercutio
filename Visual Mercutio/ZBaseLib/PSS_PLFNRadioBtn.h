/****************************************************************************
 * ==> PSS_PLFNRadioBtn ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan radio button object              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNRadioBtnH
#define PSS_PLFNRadioBtnH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNRadioBtn
    #define PSS_PLFNRadioBtn PLFNRadio
#endif

// processsoft
#include "ZATwoSts.h"

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
* Financial plan radio button object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNRadioBtn : public PLFNTwoStates
{
    DECLARE_SERIAL(PSS_PLFNRadioBtn)

    public:
        typedef PLFNTwoStates inherited;

        PSS_PLFNRadioBtn();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNRadioBtn(const PSS_PLFNRadioBtn& other);

        virtual ~PSS_PLFNRadioBtn();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNRadioBtn& operator = (const PSS_PLFNRadioBtn& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNRadioBtn& operator = (const PSS_PLFNRadioBtn* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PlanFinObject* Clone() const ;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PSS_PlanFinObject* pSrc);

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

        /**
        * Edits the object
        *@param pParentWnd - parent window
        *@param pDC - device context to draw to
        *@param pDoc - document
        */
        virtual void EditObject(CWnd* pParentWnd, CDC* pDC, ZDDocument* pDoc);

        /**
        * Checks if this object is selected
        *@param point - hit point
        *@return TRUE if this object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

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
// PSS_PLFNRadioBtn
//---------------------------------------------------------------------------
BOOL PSS_PLFNRadioBtn::IsSelected(const CPoint& point) const
{
    return(m_ObjectRect.PtInRect(point));
}
//---------------------------------------------------------------------------
UINT PSS_PLFNRadioBtn::GetPropertyTabs() const
{
    return (g_PropertyGeneralBasicPage | g_PropertySizePage | g_PropertyRadioPage);
}
//---------------------------------------------------------------------------

#endif
