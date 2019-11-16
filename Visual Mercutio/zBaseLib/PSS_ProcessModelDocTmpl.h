/****************************************************************************
 * ==> PSS_ProcessModelDocTmpl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model document template                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessModelDocTmplH
#define PSS_ProcessModelDocTmplH

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
#include "PSS_DocTemplateEx.h"

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
* Extended document template
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessModelDocTmpl : public PSS_DocTemplateEx
{
    DECLARE_DYNAMIC(PSS_ProcessModelDocTmpl)

    public:
        /**
        * Constructor
        *@param resourceID - resource identifier
        *@param pDocClass - document class
        *@param pFrameClass - frame class
        *@param pViewClass - view class
        *@param menuID - menu identifier
        *@param maxMRU - maximum MRU count
        */
        PSS_ProcessModelDocTmpl(UINT           resourceID,
                                CRuntimeClass* pDocClass,
                                CRuntimeClass* pFrameClass,
                                CRuntimeClass* pViewClass,
                                WORD           menuID = 0,
                                UINT           maxMRU = _AFX_MRU_COUNT);

        virtual ~PSS_ProcessModelDocTmpl();
};

#endif
