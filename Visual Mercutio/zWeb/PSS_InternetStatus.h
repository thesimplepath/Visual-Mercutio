/****************************************************************************
 * ==> PSS_InternetStatus --------------------------------------------------*
 ****************************************************************************
 * Description : Internet status helper class                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InternetStatusH
#define PSS_InternetStatusH

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

#ifdef _ZWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Internet status helper class
*@author Dominique Aigroz, Jean-Milost Reymonbd
*/
class AFX_EXT_CLASS PSS_InternetStatus
{
    public:

        PSS_InternetStatus();
        virtual ~PSS_InternetStatus();

        /**
        * Checks if web is connected
        *@return true if web is connected, otherwise false
        */
        virtual bool IsConnected() const;
};

#endif
