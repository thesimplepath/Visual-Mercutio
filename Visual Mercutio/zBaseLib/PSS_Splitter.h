/****************************************************************************
 * ==> PSS_Splitter --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a splitter                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplitterH
#define PSS_SplitterH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_OutlookSplitterWnd.h"

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
* Splitter
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Splitter : public PSS_OutlookSplitterWnd
{
    public:
        PSS_Splitter();
        virtual ~PSS_Splitter();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_Splitter)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif
