/****************************************************************************
 * ==> PSS_EmptyView -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an empty form view                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EmptyViewH
#define PSS_EmptyViewH

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

// mfc
#ifndef __AFXEXT_H__
    #include <afxext.h>
#endif

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
* Empty form view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EmptyView : public CFormView
{
    DECLARE_DYNCREATE(PSS_EmptyView)

    public:
        /**
        * Resources
        */
        enum
        {
            IDD = IDD_EMPTYVIEW
        };

    protected:
        PSS_EmptyView();
        virtual ~PSS_EmptyView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZIEmptyView)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(ZIEmptyView)
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
