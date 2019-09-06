/****************************************************************************
 * ==> PSS_ObsoletePLFNObj -------------------------------------------------*
 ****************************************************************************
 * Description : Provides previous and obsolete versions of the financial   *
 *               plan objects                                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ObsoletePLFNH
#define PSS_ObsoletePLFNH

#ifdef _AFXEXT
    // change the definition of AFX_EXT... to make it import
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_IMPORT
    #define AFX_EXT_API AFX_API_IMPORT
    #define AFX_EXT_DATA AFX_DATA_IMPORT
#endif

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNStringHistory
    #define PSS_PLFNStringHistory PLFNStringHistory
#endif
#ifndef PSS_PLFNNumbered
    #define PSS_PLFNNumbered PLFNNumbered
#endif
#ifndef PSS_PLFNNumbEdit
    #define PSS_PLFNNumbEdit PLFNNumbEdit
#endif
#ifndef PSS_PLFNCalculated
    #define PSS_PLFNCalculated PLFNCalculated
#endif
#ifndef PSS_PLFNNumHistory
    #define PSS_PLFNNumHistory PLFNNumHistory
#endif
#ifndef PSS_PLFNNumbNumEdit
    #define PSS_PLFNNumbNumEdit PLFNNumbNumEdit
#endif

// processsoft
#include "zamath.h"
#include "PSS_PlanFinObj.h"
#include "ZAObject.h"
#include "ZAText.h"
#include "ZAString.h"
#include "PSS_PLFNGraphic.h"
#include "PSS_Formula.h"

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
* Financial plan containing an history string
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNStringHistory : public PLFNString
{
    DECLARE_SERIAL(PSS_PLFNStringHistory)

    public:
        typedef PLFNString inherited;

        PSS_PLFNStringHistory();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNStringHistory(const PSS_PLFNStringHistory& other);

        virtual ~PSS_PLFNStringHistory();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNStringHistory& operator = (const PSS_PLFNStringHistory* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNStringHistory& operator = (const PSS_PLFNStringHistory& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the contains from a line
        *@param line - the line containing the object definition
        */
        virtual void GetContains(const CString& line);

        /**
        * Checks if object is selected
        *@paran point - point to check in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual BOOL IsSelected(const CPoint& point) const;

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

/**
* Financial plan containing a number
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNNumbered : public PSS_PLFNStatic
{
    DECLARE_SERIAL(PSS_PLFNNumbered)

    public:
        int m_Chapter;
        int m_Paragraph;

        typedef PSS_PLFNStatic inherited;

        PSS_PLFNNumbered();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNNumbered(const PSS_PLFNNumbered& other);

        virtual ~PSS_PLFNNumbered();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbered& operator = (const PSS_PLFNNumbered* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbered& operator = (const PSS_PLFNNumbered& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

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

    protected:
        /**
        * Draws the object
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);
};

//---------------------------------------------------------------------------
// PSS_PLFNNumbered
//---------------------------------------------------------------------------
UINT PSS_PLFNNumbered::GetPropertyTabs() const
{
    return PropertyGeneralStaticPage | PropertySizePage;
}
//---------------------------------------------------------------------------

/**
* Financial plan containing an editable number
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNNumbEdit : public PLFNString
{
    friend class PSS_PLFNNumbered;

    DECLARE_SERIAL(PSS_PLFNNumbEdit)

    public:
        int m_Chapter;
        int m_Paragraph;

        typedef PLFNString inherited;

        PSS_PLFNNumbEdit();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNNumbEdit(const PSS_PLFNNumbEdit& other);

        virtual ~PSS_PLFNNumbEdit();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbEdit& operator = (const PSS_PLFNNumbEdit* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbEdit& operator = (const PSS_PLFNNumbEdit& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

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

    protected:
        /**
        * Draws the object
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);
};

//---------------------------------------------------------------------------
// PSS_PLFNNumbEdit
//---------------------------------------------------------------------------
UINT PSS_PLFNNumbEdit::GetPropertyTabs() const
{
    return PropertyGeneralStaticPage | PropertySizePage;
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a calculated result
*@note Valid only in version -1 and 0, Replaced by the PLFNLong with a flag after the version 1
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNCalculated : public PSS_PLFNLong
{
    DECLARE_SERIAL(PSS_PLFNCalculated)

    public:
        typedef PSS_PLFNLong inherited;

        PSS_PLFNCalculated();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNCalculated(const PSS_PLFNCalculated& other);

        virtual ~PSS_PLFNCalculated();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNCalculated& operator = (const PSS_PLFNCalculated* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNCalculated& operator = (const PSS_PLFNCalculated& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the formatted object
        *@return the formatted object
        */
        virtual CString GetFormattedObject();

        /**
        * Recalculates the object content
        *@param pDoc - document
        */
        virtual void Recalculate(ZDDocument* pDoc);

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

/**
* Financial plan containing a numerical history
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNNumHistory : public PSS_PLFNLong
{
    DECLARE_SERIAL(PSS_PLFNNumHistory)

    public:
        typedef PSS_PLFNLong inherited;

        PSS_PLFNNumHistory();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNNumHistory(const PSS_PLFNNumHistory& other);

        virtual ~PSS_PLFNNumHistory();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumHistory& operator = (const PSS_PLFNNumHistory* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumHistory& operator = (const PSS_PLFNNumHistory& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the contains from a line
        *@param line - the line containing the object definition
        */
        virtual void GetContains(const CString& line);

        /**
        * Checks if object is selected
        *@paran point - point to check in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual BOOL IsSelected(const CPoint& point) const;

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
// PSS_PLFNNumHistory
//---------------------------------------------------------------------------
UINT PSS_PLFNNumHistory::GetPropertyTabs() const
{
    return PropertyGeneralStaticPage | PropertySizePage;
}
//---------------------------------------------------------------------------

/**
* Financial plan containing a numerical edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNNumbNumEdit : public PSS_PLFNLong
{
    friend class PSS_PLFNNumbered;

    DECLARE_SERIAL(PSS_PLFNNumbNumEdit)

    public:
        int m_Chapter;
        int m_Paragraph;

        typedef PSS_PLFNLong inherited;

        PSS_PLFNNumbNumEdit();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNNumbNumEdit(const PSS_PLFNNumbNumEdit& other);

        virtual ~PSS_PLFNNumbNumEdit();

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbNumEdit& operator = (const PSS_PLFNNumbNumEdit* pOther);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNNumbNumEdit& operator = (const PSS_PLFNNumbNumEdit& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

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

    protected:
        /**
        * Draws the object
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);
};

//---------------------------------------------------------------------------
// PSS_PLFNNumbNumEdit
//---------------------------------------------------------------------------
UINT PSS_PLFNNumbNumEdit::GetPropertyTabs() const
{
    return PropertyGeneralStaticPage | PropertySizePage;
}
//---------------------------------------------------------------------------

#endif
