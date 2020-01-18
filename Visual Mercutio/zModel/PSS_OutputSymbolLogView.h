/****************************************************************************
 * ==> PSS_OutputSymbolLogView ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an output symbol log view                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_OutputSymbolLogViewH
#define PSS_OutputSymbolLogViewH

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
#include "zBaseLib\PSS_OutputView.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Output symbol log view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_OutputSymbolLogView : public PSS_OutputView
{
    DECLARE_DYNAMIC(PSS_OutputSymbolLogView)

    public:
        PSS_OutputSymbolLogView();
        virtual ~PSS_OutputSymbolLogView();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_OutputSymbolLogView)
        virtual void OnSelChanged();
        virtual void OnDoubleClick();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
