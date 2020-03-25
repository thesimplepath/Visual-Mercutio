/****************************************************************************
 * ==> PSS_IStreamGrid -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input stream grid                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IStreamGridH
#define PSS_IStreamGridH

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
#include "PSS_IOSGrid.h"

#ifdef _ZREPORTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input stream grid
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_IStreamGrid : virtual public PSS_IOSGrid
{
    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_IStreamGrid(CGXGridCore* pGridCore = NULL);

        virtual ~PSS_IStreamGrid();
};

#endif
