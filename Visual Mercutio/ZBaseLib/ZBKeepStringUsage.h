/****************************************************************************
 * ==> PSS_KeepStringUsage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a keep string usage class                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_KeepStringUsageH
#define PSS_KeepStringUsageH

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
* Keep string usage class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_KeepStringUsage
{
    public:
        PSS_KeepStringUsage();
        virtual ~PSS_KeepStringUsage();

        /**
        * Checks if a string was already generated, adds it if not
        *@param str - string to check
        *@return true if the string was already generated, otherwise false
        */
        virtual bool StringAlreadyGenerated(const CString& str);

        /**
        * Resets the string array
        */
        virtual inline void ResetStringsArray();

    private:
        CStringArray m_StringsArray;
};

//---------------------------------------------------------------------------
// PSS_KeepStringUsage
//---------------------------------------------------------------------------
void PSS_KeepStringUsage::ResetStringsArray()
{
    m_StringsArray.RemoveAll();
}
//---------------------------------------------------------------------------

#endif
