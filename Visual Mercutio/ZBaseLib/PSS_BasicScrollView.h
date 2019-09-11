/****************************************************************************
 * ==> PSS_BasicScrollView -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic scroll view                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicScrollViewH
#define PSS_BasicScrollViewH

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
#include "ZVSpanView.h"
#include "PSS_DocumentPageSetup.h"

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
* Basic scroll view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicScrollView : public ZVSpanView
{
    DECLARE_DYNCREATE(PSS_BasicScrollView)

    public:
        /**
        * Gets the printer page size
        *@return the printer page size
        */
        virtual PSS_DocumentPageSetup* GetPrinterPageSize();

        /**
        * Sets the printer page size
        *@param paperSize - the paper size
        *@param standardSize - the standard size
        *@param orientation - the page orientation
        */
        virtual void SetPrinterPageSize(const CSize& paperSize, short standardSize, short orientation);

        /**
        * Zooms in the view
        */
        virtual void ViewZoomIn();

        /**
        * Zooms out the view
        */
        virtual void ViewZoomOut();

    protected:
        PSS_BasicScrollView();
        virtual ~PSS_BasicScrollView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_BasicScrollView)
        virtual void OnInitialUpdate();
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_BasicScrollView)
        afx_msg void OnViewZoomIn();
        afx_msg void OnViewZoomOut();
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

    private:
        PSS_DocumentPageSetup m_PageSetup;
};

#endif
