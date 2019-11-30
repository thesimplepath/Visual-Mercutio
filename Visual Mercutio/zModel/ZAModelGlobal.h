/****************************************************************************
 * ==> PSS_ModelGlobal -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides the model global property attributes              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelGlobalH
#define PSS_ModelGlobalH

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

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Model global property attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelGlobal
{
    public:
        PSS_ModelGlobal();
        virtual ~PSS_ModelGlobal();

        /**
        * Loads the global property attributes from a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        static inline void SetGlobalPropertyAttributesFileName(const CString& fileName);

        /**
        * Saves the global property attributes to a file
        *@return true on success, otherwise false
        */
        static bool SaveGlobalPropertyAttributes();

        /**
        * Gets the global property attributes
        *@param objectID - the attributes object identifier to get
        *@return the attributes, NULL if not found or on error
        */
        static ZBPropertyAttributes& GetGlobalPropertyAttributes(int ObjectID);

        /**
        * Releases the global property attributes
        */
        static void Release();

    private:
        typedef CCArray_T <ZBPropertyAttributes*, ZBPropertyAttributes*> IPropertyAttributesSet;
        typedef Iterator_T<ZBPropertyAttributes*>                        IPropertyAttributesIterator;

        static IPropertyAttributesSet m_Set;
        static CString                m_FileName;
};

//---------------------------------------------------------------------------
// PSS_ModelGlobal
//---------------------------------------------------------------------------
void PSS_ModelGlobal::SetGlobalPropertyAttributesFileName(const CString& fileName)
{
    m_FileName = fileName;
}
//---------------------------------------------------------------------------

#endif
