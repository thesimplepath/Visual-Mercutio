/****************************************************************************
 * ==> PSS_NavigableSymbol -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol navigation interface                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NavigableSymbolH
#define PSS_NavigableSymbolH

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
* Symbol navigation interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NavigableSymbol
{
    public:
        PSS_NavigableSymbol();
        virtual ~PSS_NavigableSymbol();

        /**
        * Gets the entering symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEnteringSymbols(CODNodeArray& nodes) = 0;

        /**
        * Gets the entering left symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEnteringSymbols_Left(CODNodeArray& nodes) = 0;

        /**
        * Gets the entering right symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEnteringSymbols_Right(CODNodeArray& nodes) = 0;

        /**
        * Gets the entering up symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEnteringSymbols_Up(CODNodeArray& nodes) = 0;

        /**
        * Gets the entering down symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEnteringSymbols_Down(CODNodeArray& nodes) = 0;

        /**
        * Gets the following symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetFollowingSymbols(CODNodeArray& nodes) = 0;

        /**
        * Gets the following left symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetFollowingSymbols_Left(CODNodeArray& nodes) = 0;

        /**
        * Gets the following right symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetFollowingSymbols_Right(CODNodeArray& nodes) = 0;

        /**
        * Gets the following up symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetFollowingSymbols_Up(CODNodeArray& nodes) = 0;

        /**
        * Gets the following down symbols
        *@param[out] nodes - node array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetFollowingSymbols_Down(CODNodeArray& nodes) = 0;

        /**
        * Gets the edge entering symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesEntering(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge entering left symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesEntering_Left(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge entering right symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesEntering_Right(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge entering up symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesEntering_Up(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge entering down symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesEntering_Down(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge leaving symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesLeaving(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge leaving left symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesLeaving_Left(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge leaving right symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesLeaving_Right(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge leaving up symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesLeaving_Up(CODEdgeArray& edges) = 0;

        /**
        * Gets the edge leaving down symbols
        *@param[out] edges - edge array to populate with found symbols
        *@return found symbol count
        */
        virtual std::size_t GetEdgesLeaving_Down(CODEdgeArray& edges) = 0;
};

#endif
