/****************************************************************************
 * ==> PSS_FTPSymbolLoader -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a ftp symbol loader                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FTPSymbolLoaderH
#define PSS_FTPSymbolLoaderH

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
#include "PSS_SymbolEntity.h"

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
* FTP symbol loader
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FTPSymbolLoader
{
    public:
        PSS_FTPSymbolLoader();
        virtual ~PSS_FTPSymbolLoader();

        /**
        * Loads the symbol
        *@param location - the location
        *@param[out] compSet - the component set to populate with the result
        *@return the loaded element count, 0 if no element loaded
        */
        static int LoadSymbol(const CString& location, PSS_SymbolEntity::IEntitySet& compSet);

        /**
        * Loads the symbol
        *@param location - the location
        *@param[out] compSet - the component set to populate with the result
        *@param loadSubFolders - if true, the load will include the sub-folders
        *@return the loaded element count, 0 if no element loaded
        */
        static int LoadSymbols(const CString& location, PSS_SymbolEntity::IEntitySet& compSet, bool loadSubFolders = false);
};

#endif
