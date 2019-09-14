/****************************************************************************
 * ==> PSS_GUID ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a global unique identifier helper                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GUIDH
#define PSS_GUIDH

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
* Global unique identifier helper
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GUID
{
    public:
        PSS_GUID();
        virtual ~PSS_GUID();

        /**
        * Creates a new GUID
        *@return the new GUID, empty string on error
        */
        static CString CreateNewGUID();

        /**
        * Checks if the GUID is valid
        *@param guid - guid to check
        *@return true if the GUID is valid, otherwise FALSE
        */
        static bool GUIDIsValid(const CString& guid);
};

#endif
