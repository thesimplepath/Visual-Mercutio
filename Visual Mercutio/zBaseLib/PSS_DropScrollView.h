/****************************************************************************
 * ==> PSS_DropScrollView --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a drop scroll view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DropScrollViewH
#define PSS_DropScrollViewH

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

// processsoft
#include "PSS_Drop.h"
#include "PSS_BasicScrollView.h"

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
* Drop scroll view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DropScrollView : public PSS_BasicScrollView, public PSS_Drop
{
    DECLARE_DYNCREATE(PSS_DropScrollView)

    public:
        /**
        * Checks if the drop may be accepted
        *@return true if the drop may be accepted, otherwise false
        */
        virtual inline bool AcceptDrop() const;

        /**
        * Drops the item
        *@param pObj - dropped object
        *@param point - drop point
        *@return true on success, otherwise false
        */
        virtual inline bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Checks if the drop item may be accepted
        *@param pObj - dropped object
        *@param point - drop point
        *@return true if the drop item may be accepted, otherwise false
        */
        virtual inline bool AcceptDropItem(CObject* pObj, const CPoint& point);

    protected:
        PSS_DropScrollView();
        virtual ~PSS_DropScrollView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_DropScrollView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_DropScrollView)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

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
// PSS_DropScrollView
//---------------------------------------------------------------------------
bool PSS_DropScrollView::AcceptDrop() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_DropScrollView::DropItem(CObject* pObj, const CPoint& point)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_DropScrollView::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    return false;
}
//---------------------------------------------------------------------------

#endif
