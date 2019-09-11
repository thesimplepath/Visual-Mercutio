/****************************************************************************
 * ==> PSS_BasicView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicViewH
#define PSS_BasicViewH

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
* Basic view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicView : public CView
{
    DECLARE_DYNCREATE(PSS_BasicView)

    public:
          /**
          * Gets the printer page size
          *@param[out] paperSize - paper size
          *@param[out] standardSize - standard size
          *@param[out] orientation - orientation
          *@return TRUE on success, otherwise FALSE
          */
          virtual BOOL GetPrinterPageSize(CSize& paperSize, short& standardSize, short& orientation);

          /**
          * Sets the printer orientation. It's the printer definition function
          *@param orientation - orientation
          */
          virtual void SetPrinterOrientation(short orientation = DMORIENT_PORTRAIT);

    protected:
        PSS_BasicView();
        virtual ~PSS_BasicView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_BasicView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_BasicView)
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

#endif
