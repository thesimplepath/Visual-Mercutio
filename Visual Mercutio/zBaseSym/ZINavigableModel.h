/****************************************************************************
 * ==> PSS_NavigableModel --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a model navigation interface                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NavigableModelH
#define PSS_NavigableModelH

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

#ifdef _ZBASESYMEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Model navigation interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NavigableModel
{
    public:
        PSS_NavigableModel();
        virtual ~PSS_NavigableModel();

        /**
        * Gets the start symbols
        *@param[out] nodes - node array to populate with found symbols
        *@param deep - if true, children nodes will also be included in the search
        *@return found symbol count
        */
        virtual std::size_t GetStartSymbols(CODNodeArray& nodes, bool deep = false) = 0;
};

#endif
