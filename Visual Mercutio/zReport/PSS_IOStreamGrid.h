/****************************************************************************
 * ==> PSS_IOStreamGrid ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a input/output stream grid                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_IOStreamGridH
#define PSS_IOStreamGridH

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
#include "PSS_IStreamGrid.h"
#include "PSS_OStreamGrid.h"

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
* Input/output stream grid
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_IOStreamGrid : public PSS_IStreamGrid,
                                       public PSS_OStreamGrid
{
    public:
        /**
        * Constructor
        *@param pGridCore - the grid core
        */
        PSS_IOStreamGrid(CGXGridCore* pGridCore = NULL);

        virtual ~PSS_IOStreamGrid();
};

#endif
